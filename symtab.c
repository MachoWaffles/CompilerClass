/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable and function declarations across scopes.
 * The scope field in each Symbol differentiates global variables
 * (scope = "global") from function-local variables (scope = funcName).
 * Lookups always check the current scope first, then fall back to global,
 * which mirrors standard lexical scoping rules.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

static SymbolTable symtab;
static FuncTable   functab;

/* Active compilation scope — "global" at program start, set to a function
 * name when the semantic analyzer enters a function body. */
static char currentScope[256] = "global";

/* ── SCOPE CONTROL ───────────────────────────────────────────────────────── */
void setScope(const char* scope) {
    strncpy(currentScope, scope, sizeof(currentScope) - 1);
    /* Reset the local offset counter each time we enter a new function scope
     * so local variable offsets always start from 0 within the function frame. */
    symtab.nextLocalOffset = 0;
}

const char* getCurrentScope() {
    return currentScope;
}

/* ── INITIALIZATION ──────────────────────────────────────────────────────── */
void initSymTab() {
    symtab.count             = 0;
    symtab.nextGlobalOffset  = 0;
    symtab.nextLocalOffset   = 0;
    strncpy(currentScope, "global", sizeof(currentScope) - 1);
    printf("SYMBOL TABLE: Initialized\n");
    printSymTab();
}

void initFuncTab() {
    functab.count = 0;
}

/* ── ADD VARIABLE ─────────────────────────────────────────────────────────── */
/* Adds a variable in the current scope. Returns its stack offset or -1 on
 * duplicate. The offset is relative to that scope's stack frame base. */
int addVar(char* name, char* type) {
    /* Duplicate check within the same scope only — a local may shadow a global */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0) {
            fprintf(stderr,
                "SYMBOL TABLE ERROR: '%s' already declared in scope '%s'\n",
                name, currentScope);
            return -1;
        }
    }

    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "SYMBOL TABLE ERROR: Maximum variable limit reached\n");
        return -1;
    }

    int offset;
    /* Determine byte size of this type for stack offset advancement.
     * All types currently use 4 bytes on the stack for alignment.
     * TODO: chars and bools could use 1 byte with proper alignment padding. */
    int byteSize = 4;

    if (strcmp(currentScope, "global") == 0) {
        offset = symtab.nextGlobalOffset;
        symtab.nextGlobalOffset += byteSize;
    } else {
        offset = symtab.nextLocalOffset;
        symtab.nextLocalOffset += byteSize;
    }

    symtab.vars[symtab.count].name   = strdup(name);
    symtab.vars[symtab.count].type   = strdup(type);
    symtab.vars[symtab.count].scope  = strdup(currentScope);
    symtab.vars[symtab.count].offset = offset;
    symtab.count++;

    printf("SYMBOL TABLE: Added '%s' (type: %s, scope: %s, offset: %d)\n",
           name, type, currentScope, offset);
    printSymTab();
    return offset;
}

/* ── ADD OR REUSE VARIABLE ───────────────────────────────────────────────── */
/* Used exclusively by for-loop init. If the variable is already declared in
 * the current scope (e.g. a second loop also uses 'int i'), silently reuse
 * its existing offset instead of erroring. This avoids requiring block-level
 * scoping for the common pattern of reusing a loop counter name. */
int addOrReuseVar(char* name, char* type) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0) {
            printf("SYMBOL TABLE: Reusing '%s' (type: %s, scope: %s, offset: %d)\n",
                   name, type, currentScope, symtab.vars[i].offset);
            return symtab.vars[i].offset;
        }
    }
    /* Not yet declared — fall through to normal addVar */
    return addVar(name, type);
}

/* ── ADD ARRAY ───────────────────────────────────────────────────────────── */
/* Registers an array's base offset and reserves size*4 bytes so that
 * subsequent variables don't overlap the array's storage. */
int addArray(char* name, char* type, int size) {
    /* Duplicate check */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0) {
            fprintf(stderr,
                "SYMBOL TABLE ERROR: Array '%s' already declared in scope '%s'\n",
                name, currentScope);
            return -1;
        }
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "SYMBOL TABLE ERROR: Maximum variable limit reached\n");
        return -1;
    }

    int offset;
    int byteSize = size * 4;  /* reserve all elements at once */

    if (strcmp(currentScope, "global") == 0) {
        offset = symtab.nextGlobalOffset;
        symtab.nextGlobalOffset += byteSize;
    } else {
        offset = symtab.nextLocalOffset;
        symtab.nextLocalOffset += byteSize;
    }

    symtab.vars[symtab.count].name   = strdup(name);
    symtab.vars[symtab.count].type   = strdup(type);
    symtab.vars[symtab.count].scope  = strdup(currentScope);
    symtab.vars[symtab.count].offset = offset;
    symtab.count++;

    printf("SYMBOL TABLE: Array '%s' (type: %s[%d], scope: %s, base offset: %d)\n",
           name, type, size, currentScope, offset);
    return offset;
}
/* Searches current scope first, then global. Returns offset or -1. */
int getVarOffset(char* name) {
    /* Current scope first */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0) {
            return symtab.vars[i].offset;
        }
    }
    /* Fall back to global */
    if (strcmp(currentScope, "global") != 0) {
        for (int i = 0; i < symtab.count; i++) {
            if (strcmp(symtab.vars[i].name,  name) == 0 &&
                strcmp(symtab.vars[i].scope, "global") == 0) {
                return symtab.vars[i].offset;
            }
        }
    }
    return -1;
}

int isVarDeclared(char* name) {
    return getVarOffset(name) != -1;
}

/* Returns the declared type of a variable, or NULL if not found. */
const char* getVarType(char* name) {
    /* Current scope first */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0) {
            return symtab.vars[i].type;
        }
    }
    /* Fall back to global */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, "global") == 0) {
            return symtab.vars[i].type;
        }
    }
    return NULL;
}

/* ── PRINT ────────────────────────────────────────────────────────────────── */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d  Global offset: %d  Local offset: %d  Scope: %s\n",
           symtab.count, symtab.nextGlobalOffset,
           symtab.nextLocalOffset, currentScope);
    if (symtab.count == 0) {
        printf("(empty)\n");
    } else {
        for (int i = 0; i < symtab.count; i++) {
            printf("  [%d] %s %s  scope='%s'  offset=%d\n", i,
                   symtab.vars[i].type,  symtab.vars[i].name,
                   symtab.vars[i].scope, symtab.vars[i].offset);
        }
    }
    printf("==========================\n\n");
}


/* ── READ-ONLY ACCESSORS ─────────────────────────────────────────────────── */
int getVarCount() { return symtab.count; }

char* getVarNameAt(int i) {
    return (i >= 0 && i < symtab.count) ? symtab.vars[i].name : NULL;
}

char* getVarScopeAt(int i) {
    return (i >= 0 && i < symtab.count) ? symtab.vars[i].scope : NULL;
}

int getVarOffsetAt(int i) {
    return (i >= 0 && i < symtab.count) ? symtab.vars[i].offset : -1;
}

/* Returns bytes used by the current scope (global or local). */
int getStackUsage() {
    return strcmp(currentScope, "global") == 0
        ? symtab.nextGlobalOffset
        : symtab.nextLocalOffset;
}

/* Returns 1 if the named variable lives in global scope, 0 otherwise.
 * Follows the same search order as getVarOffset (current scope first, then
 * global fallback) so that a local that shadows a global is handled correctly.
 * Used by codegen to decide whether to address via $sp (global) or $fp (local).
 */
int isVarGlobal(const char* name) {
    /* Current scope first */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, currentScope) == 0)
            return strcmp(symtab.vars[i].scope, "global") == 0;
    }
    /* Fall back to global */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name,  name) == 0 &&
            strcmp(symtab.vars[i].scope, "global") == 0)
            return 1;
    }
    return 0;
}

/* ── FUNCTION TABLE ───────────────────────────────────────────────────────── */
/* Registers a function name and return type. Returns 0 on success, -1 if
 * a function with that name already exists. */
int addFunc(char* name, char* returnType) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0) {
            fprintf(stderr,
                "FUNCTION TABLE ERROR: Function '%s' already declared\n", name);
            return -1;
        }
    }
    if (functab.count >= MAX_FUNCS) {
        fprintf(stderr, "FUNCTION TABLE ERROR: Maximum function limit reached\n");
        return -1;
    }
    int idx = functab.count++;
    functab.funcs[idx].name       = strdup(name);
    functab.funcs[idx].returnType = strdup(returnType);
    functab.funcs[idx].paramCount = 0;
    printf("FUNCTION TABLE: Registered '%s' returns %s\n", name, returnType);
    return 0;
}

/* Adds one parameter to an already-registered function. */
int addFuncParam(char* funcName, char* paramType, char* paramName) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, funcName) == 0) {
            int p = functab.funcs[i].paramCount;
            if (p >= MAX_PARAMS) {
                fprintf(stderr,
                    "FUNCTION TABLE ERROR: Too many parameters for '%s'\n", funcName);
                return -1;
            }
            functab.funcs[i].paramTypes[p] = strdup(paramType);
            functab.funcs[i].paramNames[p] = strdup(paramName);
            functab.funcs[i].paramCount++;
            return 0;
        }
    }
    fprintf(stderr,
        "FUNCTION TABLE ERROR: Cannot add param — function '%s' not found\n", funcName);
    return -1;
}

int isFuncDeclared(char* name) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0) return 1;
    }
    return 0;
}

char* getFuncReturnType(char* name) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0)
            return functab.funcs[i].returnType;
    }
    return NULL;
}

int getFuncParamCount(char* name) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0)
            return functab.funcs[i].paramCount;
    }
    return -1;
}

char* getFuncParamType(char* name, int idx) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0) {
            if (idx < 0 || idx >= functab.funcs[i].paramCount) return NULL;
            return functab.funcs[i].paramTypes[idx];
        }
    }
    return NULL;
}

char* getFuncParamName(char* name, int idx) {
    for (int i = 0; i < functab.count; i++) {
        if (strcmp(functab.funcs[i].name, name) == 0) {
            if (idx < 0 || idx >= functab.funcs[i].paramCount) return NULL;
            return functab.funcs[i].paramNames[idx];
        }
    }
    return NULL;
}

/* ═══════════════════════════════════════════════════════════════════════════
 * STRUCT TYPE TABLE
 * ═══════════════════════════════════════════════════════════════════════════ */

static StructTable structtab;

void initStructTab() {
    structtab.count = 0;
}

int addStructDef(char* name) {
    for (int i = 0; i < structtab.count; i++) {
        if (strcmp(structtab.defs[i].name, name) == 0) {
            fprintf(stderr,
                "STRUCT TABLE ERROR: Struct '%s' already defined\n", name);
            return -1;
        }
    }
    if (structtab.count >= MAX_STRUCTS) {
        fprintf(stderr, "STRUCT TABLE ERROR: Max struct definitions reached\n");
        return -1;
    }
    StructDef* d = &structtab.defs[structtab.count++];
    d->name       = strdup(name);
    d->fieldCount = 0;
    return 0;
}

int addStructField(char* structName, char* fieldType, char* fieldName) {
    for (int i = 0; i < structtab.count; i++) {
        if (strcmp(structtab.defs[i].name, structName) == 0) {
            StructDef* d = &structtab.defs[i];
            if (d->fieldCount >= MAX_FIELDS) {
                fprintf(stderr,
                    "STRUCT TABLE ERROR: Too many fields in '%s'\n", structName);
                return -1;
            }
            /* Duplicate field check */
            for (int j = 0; j < d->fieldCount; j++) {
                if (strcmp(d->fieldNames[j], fieldName) == 0) {
                    fprintf(stderr,
                        "STRUCT TABLE ERROR: Field '%s' already in '%s'\n",
                        fieldName, structName);
                    return -1;
                }
            }
            d->fieldTypes[d->fieldCount] = strdup(fieldType);
            d->fieldNames[d->fieldCount] = strdup(fieldName);
            d->fieldCount++;
            return 0;
        }
    }
    fprintf(stderr,
        "STRUCT TABLE ERROR: Struct '%s' not defined\n", structName);
    return -1;
}

int isStructDefined(char* name) {
    for (int i = 0; i < structtab.count; i++)
        if (strcmp(structtab.defs[i].name, name) == 0) return 1;
    return 0;
}

int getStructFieldCount(char* name) {
    for (int i = 0; i < structtab.count; i++)
        if (strcmp(structtab.defs[i].name, name) == 0)
            return structtab.defs[i].fieldCount;
    return 0;
}

char* getStructFieldType(char* name, int idx) {
    for (int i = 0; i < structtab.count; i++)
        if (strcmp(structtab.defs[i].name, name) == 0)
            return structtab.defs[i].fieldTypes[idx];
    return NULL;
}

char* getStructFieldName(char* name, int idx) {
    for (int i = 0; i < structtab.count; i++)
        if (strcmp(structtab.defs[i].name, name) == 0)
            return structtab.defs[i].fieldNames[idx];
    return NULL;
}

/* Returns the byte offset of fieldName within structName (field index * 4).
 * Returns -1 if the struct or field is not found. */
int getStructFieldOffset(char* structName, char* fieldName) {
    for (int i = 0; i < structtab.count; i++) {
        if (strcmp(structtab.defs[i].name, structName) == 0) {
            StructDef* d = &structtab.defs[i];
            for (int j = 0; j < d->fieldCount; j++) {
                if (strcmp(d->fieldNames[j], fieldName) == 0)
                    return j * 4;
            }
            return -1;
        }
    }
    return -1;
}

int getStructSize(char* name) {
    for (int i = 0; i < structtab.count; i++)
        if (strcmp(structtab.defs[i].name, name) == 0)
            return structtab.defs[i].fieldCount * 4;
    return 0;
}

/* Registers a struct variable in the variable symbol table, reserving
 * fieldCount * 4 bytes (one word per field, same layout as arrays).
 * The type stored is the struct type name so getVarType() returns it. */
int addStructVar(char* varName, char* structTypeName) {
    if (!isStructDefined(structTypeName)) {
        fprintf(stderr,
            "SYMBOL TABLE ERROR: Struct type '%s' not defined\n", structTypeName);
        return -1;
    }
    int size = getStructSize(structTypeName);
    /* Reuse addArray logic: it reserves size bytes starting at a base offset */
    return addArray(varName, structTypeName, size / 4);
}
