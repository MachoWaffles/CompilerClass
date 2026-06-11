/* SEMANTIC ANALYZER IMPLEMENTATION
 * Walks the AST and performs meaning-level checks that the grammar cannot
 * express — e.g. "was this variable declared?" or "does the return type
 * match the function's signature?".
 *
 * Key design choices for Project 3:
 *   - A separate function table (in symtab) is populated during a first pass
 *     so that mutually-recursive calls can be detected correctly.
 *   - The active "scope" is switched to each function's name while its body
 *     is analyzed, then restored to "global" afterward.
 *   - Type compatibility follows the class notes: a value of a smaller type
 *     can be widened to a larger type (int → float), but not the reverse.
 *   - Master() must be declared; its absence is a fatal semantic error.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symtab.h"

extern int yylineno;

int semanticErrors = 0;

/* Tracks which variables have been assigned at least once. */
static char* initializedVars[200];
static int   initializedCount = 0;

/* Set to 1 while analyzing a for-loop init clause so DEC_ASSIGN uses
 * addOrReuseVar instead of addVar — prevents false "already declared"
 * errors when two loops in the same function both use e.g. int i. */
static int inForInit = 0;

/* The return type expected by the function currently being analyzed.
 * NULL when analyzing global scope. */
static const char* currentFuncReturnType = NULL;

/* ── HELPERS ─────────────────────────────────────────────────────────────── */

static void markInitialized(const char* name) {
    for (int i = 0; i < initializedCount; i++) {
        if (strcmp(initializedVars[i], name) == 0) return;
    }
    if (initializedCount < 200)
        initializedVars[initializedCount++] = strdup(name);
}

static int isInitialized(const char* name) {
    for (int i = 0; i < initializedCount; i++) {
        if (strcmp(initializedVars[i], name) == 0) return 1;
    }
    return 0;
}

void reportSemanticError(const char* msg) {
    fprintf(stderr, "✗ SEMANTIC ERROR (near line %d): %s\n", yylineno, msg);
    semanticErrors++;
}

void initSemantic() {
    semanticErrors = 0;
}

static void reportSemanticWarning(const char* msg) {
    printf("⚠ SEMANTIC WARNING (near line %d): %s\n", yylineno, msg);
}

/* Returns 1 if assigning a value of type `src` to a variable of type `dst`
 * is legal. Widening (int → float) is permitted; narrowing is not.
 *
 * Class notes: "types can be bigger than themselves, but they can't shrink." */
static int typesCompatible(const char* dst, const char* src) {
    if (!dst || !src) return 1;          /* unknown type — give benefit of doubt */
    if (strcmp(dst, src) == 0) return 1; /* exact match */
    /* Widening: int is promotable to float */
    if (strcmp(dst, "float") == 0 && strcmp(src, "int") == 0) return 1;
    return 0;
}

/* Infer the result type of an expression. Used for assignment and return
 * type checking. Returns a static string or NULL. */
const char* getExprType(ASTNode* node) {
    if (!node) return "nothing";
    switch (node->type) {
        case NODE_NUM:       return "int";
        case NODE_FLOAT_LIT: return "float";
        case NODE_CHAR_LIT:  return "char";
        case NODE_BOOL_LIT:  return "bool";
        case NODE_VAR:       return getVarType(node->data.name);   /* symtab lookup */
        case NODE_ARRAY_ACCESS: return getVarType(node->data.arrayAccess.name); /* symtab lookup */
        case NODE_FIELD_ACCESS: {
            /* Look up the struct variable type, then find the field type */
            const char* vtype = getVarType(node->data.fieldAccess.varName);
            if (!vtype) return "unknown";
            int idx = -1;
            int fc  = getStructFieldCount((char*)vtype);
            for (int i = 0; i < fc; i++) {
                if (strcmp(getStructFieldName((char*)vtype, i),
                           node->data.fieldAccess.fieldName) == 0) {
                    idx = i; break;
                }
            }
            if (idx == -1) return "unknown";
            return getStructFieldType((char*)vtype, idx);
        }
            
        case NODE_BINOP: {
            const char* lt = getExprType(node->data.binop.left);
            const char* rt = getExprType(node->data.binop.right);
            char op = node->data.binop.op;
            /* Comparison operators always produce a bool result */
            if (op == '<' || op == '>' || op == 'L' || op == 'G' ||
                op == 'E' || op == 'N') return "bool";
            /* Arithmetic: if either operand is float, result is float */
            if (lt && strcmp(lt, "float") == 0) return "float";
            if (rt && strcmp(rt, "float") == 0) return "float";
            return "int";
        }
        case NODE_FUNC_CALL:
            return getFuncReturnType(node->data.funcCall.name);
        default:
            return "unknown";
    }
}

/* ── RECURSIVE LIST-WALKING HELPERS ─────────────────────────────────────── */
/* Forward declarations needed by checkArgs */
void analyzeExpr(ASTNode* node);
const char* getExprType(ASTNode* node);
/* The parser builds param lists and field lists as left-leaning binary trees:
 *   createStmtList(createStmtList(a, b), c)
 * A flat while-loop that peels one level at a time only ever reaches the
 * right-most sibling — every item on the left subtree is missed after the
 * first NODE_STMT_LIST whose .stmt is itself another NODE_STMT_LIST.
 * These three helpers recurse into both children so every leaf is visited. */

/* Register all params of funcName into the function table (first pass). */
static void registerParams(char* funcName, ASTNode* p) {
    if (!p) return;
    if (p->type == NODE_PARAM_DECL) {
        addFuncParam(funcName, p->data.param.paramType, p->data.param.name);
    } else if (p->type == NODE_STMT_LIST) {
        registerParams(funcName, p->data.stmtlist.stmt);
        registerParams(funcName, p->data.stmtlist.next);
    }
}

/* Add all params of funcName as local variables in the current scope (second pass). */
static void addParamsAsLocals(ASTNode* p, const char* fname) {
    if (!p) return;
    if (p->type == NODE_PARAM_DECL) {
        int off = addVar(p->data.param.name, p->data.param.paramType);
        if (off != -1) {
            markInitialized(p->data.param.name);
            printf("  ✓ Parameter '%s' (type: %s) added to scope '%s'\n",
                   p->data.param.name, p->data.param.paramType, fname);
        }
    } else if (p->type == NODE_STMT_LIST) {
        addParamsAsLocals(p->data.stmtlist.stmt, fname);
        addParamsAsLocals(p->data.stmtlist.next, fname);
    }
}

/* Register all fields of a struct definition. */
static void registerStructFields(char* sname, ASTNode* flist) {
    if (!flist) return;
    if (flist->type == NODE_DECL) {
        addStructField(sname,
                       flist->data.decl.varType,
                       flist->data.decl.name);
        printf("  ✓ Struct '%s' field '%s' (type: %s)\n",
               sname, flist->data.decl.name, flist->data.decl.varType);
    } else if (flist->type == NODE_STMT_LIST) {
        registerStructFields(sname, flist->data.stmtlist.stmt);
        registerStructFields(sname, flist->data.stmtlist.next);
    }
}

/* Recursively walk an arg list, type-checking each leaf expression against
 * the declared parameter types and incrementing *count / *idx. */
static void checkArgs(const char* fname, ASTNode* arg,
                      int* count, int* idx) {
    if (!arg) return;
    if (arg->type == NODE_STMT_LIST) {
        checkArgs(fname, arg->data.stmtlist.stmt, count, idx);
        checkArgs(fname, arg->data.stmtlist.next, count, idx);
    } else {
        /* Leaf — this is an actual argument expression */
        (*count)++;
        const char* argType   = getExprType(arg);
        const char* paramType = getFuncParamType((char*)fname, *idx);
        if (paramType && argType && !typesCompatible(paramType, argType)) {
            char msg[512];
            snprintf(msg, sizeof(msg),
                "Argument %d to '%s': expected %s, got %s",
                *idx + 1, fname, paramType, argType);
            reportSemanticError(msg);
        }
        analyzeExpr(arg);
        (*idx)++;
    }
}

/* ── FIRST PASS: Register all function declarations ──────────────────────── */
static void registerFunctions(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        registerFunctions(node->data.stmtlist.stmt);
        registerFunctions(node->data.stmtlist.next);
        return;
    }
    if (node->type == NODE_FUNC_DECL) {
        addFunc(node->data.funcDecl.name, node->data.funcDecl.returnType);
        /* Register parameters — walk the left-leaning STMT_LIST tree recursively
         * so that functions with any number of params are handled correctly. */
        registerParams(node->data.funcDecl.name, node->data.funcDecl.params);
    }
}


/* ── EXPRESSION ANALYSIS ─────────────────────────────────────────────────── */
void analyzeExpr(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_NUM:
        case NODE_FLOAT_LIT:
        case NODE_CHAR_LIT:
        case NODE_BOOL_LIT:
            break;  /* literals are always valid */

        case NODE_VAR: {
            if (!isVarDeclared(node->data.name)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Variable '%s' used before declaration", node->data.name);
                reportSemanticError(msg);
            } else {
                printf("  ✓ Variable '%s' is declared\n", node->data.name);
                if (!isInitialized(node->data.name)) {
                    char warn[256];
                    snprintf(warn, sizeof(warn),
                        "Variable '%s' may be used before being assigned a value",
                        node->data.name);
                    reportSemanticWarning(warn);
                }
            }
            break;
        }

        case NODE_ARRAY_ACCESS: {
            if (!isVarDeclared(node->data.arrayAccess.name)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Array '%s' used before declaration",
                         node->data.arrayAccess.name);
                reportSemanticError(msg);
            } else {
                printf("  ✓ Array '%s' is declared\n",
                       node->data.arrayAccess.name);
            }

            analyzeExpr(node->data.arrayAccess.index);
            break;
        }

        case NODE_FIELD_ACCESS: {
            char* vname = node->data.fieldAccess.varName;
            char* fname = node->data.fieldAccess.fieldName;
            if (!isVarDeclared(vname)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Variable '%s' not declared (in field access '%s.%s')",
                    vname, vname, fname);
                reportSemanticError(msg);
            } else {
                const char* vtype = getVarType(vname);
                if (vtype && getStructFieldOffset((char*)vtype, fname) == -1) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                        "Struct '%s' has no field '%s'", vtype, fname);
                    reportSemanticError(msg);
                } else {
                    printf("  ✓ Field access '%s.%s' is valid\n", vname, fname);
                }
            }
            break;
        }

        case NODE_BINOP:
            /* Compile-time division-by-zero check (for when '/' is added) */
            if (node->data.binop.op == '/') {
                if (node->data.binop.right &&
                    node->data.binop.right->type == NODE_NUM &&
                    node->data.binop.right->data.num == 0) {
                    reportSemanticError(
                        "Division by zero: dividing by the constant 0 is undefined");
                }
            }
            analyzeExpr(node->data.binop.left);
            analyzeExpr(node->data.binop.right);
            break;

        case NODE_FUNC_CALL: {
            const char* fname = node->data.funcCall.name;
            if (!isFuncDeclared((char*)fname)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Call to undeclared function '%s'", fname);
                reportSemanticError(msg);
                break;
            }
            printf("  ✓ Function '%s' is declared\n", fname);

            /* Count and type-check arguments.
             * The arg list is a left-leaning STMT_LIST tree — use the same
             * recursive helper pattern to flatten it before checking. */
            int expectedCount = getFuncParamCount((char*)fname);
            int actualCount   = 0;
            int argIdx        = 0;
            checkArgs(fname, node->data.funcCall.args,
                      &actualCount, &argIdx);

            if (actualCount != expectedCount) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Function '%s' expects %d argument(s) but got %d",
                    fname, expectedCount, actualCount);
                reportSemanticError(msg);
            }
            break;
        }

        default:
            break;
    }
}

/* ── STATEMENT ANALYSIS ──────────────────────────────────────────────────── */
void analyzeStmt(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        case NODE_DECL: {
            int offset = addVar(node->data.decl.name, node->data.decl.varType);
            if (offset != -1) {
                printf("  ✓ Variable '%s' (type: %s) declared\n",
                       node->data.decl.name, node->data.decl.varType);
            } else {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Variable '%s' already declared in this scope",
                    node->data.decl.name);
                reportSemanticError(msg);
            }
            break;
        }
        case NODE_ARRAY_DECL: {
            int offset = addVar(node->data.arrayDecl.name,
                                node->data.arrayDecl.type);

            if (offset != -1) {
                printf("  ✓ Array '%s' (type: %s, size: %d) declared\n",
                       node->data.arrayDecl.name,
                       node->data.arrayDecl.type,
                       node->data.arrayDecl.size);

                markInitialized(node->data.arrayDecl.name);
            } else {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Array '%s' already declared in this scope",
                         node->data.arrayDecl.name);
                reportSemanticError(msg);
            }

            break;
        }


        case NODE_ASSIGN: {
            if (!isVarDeclared(node->data.assign.var)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Cannot assign to undeclared variable '%s'",
                    node->data.assign.var);
                reportSemanticError(msg);
            } else {
                printf("  ✓ Assignment to '%s'\n", node->data.assign.var);
                markInitialized(node->data.assign.var);

                /* Type compatibility check */
                const char* varType  = getVarType(node->data.assign.var);
                const char* exprType = getExprType(node->data.assign.value);
                if (varType && exprType &&
                    !typesCompatible(varType, exprType)) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                        "Type mismatch: cannot assign %s expression to %s variable '%s'",
                        exprType, varType, node->data.assign.var);
                    reportSemanticError(msg);
                }
            }
            analyzeExpr(node->data.assign.value);
            break;
        }

        case NODE_ARRAY_ASSIGN: {
            if (!isVarDeclared(node->data.arrayAssign.name)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Cannot assign to undeclared array '%s'",
                         node->data.arrayAssign.name);
                reportSemanticError(msg);
            } else {
                printf("  ✓ Assignment to array '%s'\n",
                       node->data.arrayAssign.name);

                markInitialized(node->data.arrayAssign.name);

                const char* arrayType = getVarType(node->data.arrayAssign.name);
                const char* valueType = getExprType(node->data.arrayAssign.value);

                if (arrayType && valueType &&
                    !typesCompatible(arrayType, valueType)) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                             "Type mismatch: cannot assign %s value to %s array '%s'",
                             valueType, arrayType, node->data.arrayAssign.name);
                    reportSemanticError(msg);
                }
            }

            analyzeExpr(node->data.arrayAssign.index);
            analyzeExpr(node->data.arrayAssign.value);
            break;
        }

        case NODE_DEC_ASSIGN: {
            int offset = inForInit
                ? addOrReuseVar(node->data.DecAssignNode.name,
                                node->data.DecAssignNode.varType)
                : addVar(node->data.DecAssignNode.name,
                         node->data.DecAssignNode.varType);

            if (offset != -1) {
                printf("  ✓ Variable '%s' (type: %s) declared and assigned\n",
                       node->data.DecAssignNode.name,
                       node->data.DecAssignNode.varType);

                markInitialized(node->data.DecAssignNode.name);

                const char* varType = node->data.DecAssignNode.varType;
                const char* exprType = getExprType(node->data.DecAssignNode.value);

                if (!typesCompatible(varType, exprType)) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                             "Type mismatch: cannot initialize %s variable '%s' with %s value",
                             varType,
                             node->data.DecAssignNode.name,
                             exprType);
                    reportSemanticError(msg);
                }
            } else {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Variable '%s' already declared in this scope",
                         node->data.DecAssignNode.name);
                reportSemanticError(msg);
            }

            analyzeExpr(node->data.DecAssignNode.value);
            break;
        }

        case NODE_PRINT:
            printf("  Checking print expression:\n");
            analyzeExpr(node->data.expr);
            break;

        case NODE_RETURN: {
            /* Must be inside a function */
            if (strcmp(getCurrentScope(), "global") == 0) {
                reportSemanticError("'return' used outside of a function");
                break;
            }
            const char* expected = currentFuncReturnType;
            if (!expected) break;

            if (node->data.returnExpr == NULL) {
                /* Void return */
                if (strcmp(expected, "nothing") != 0) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                        "Function '%s' must return a value of type '%s', not void",
                        getCurrentScope(), expected);
                    reportSemanticError(msg);
                }
            } else {
                const char* actualType = getExprType(node->data.returnExpr);
                if (!typesCompatible(expected, actualType)) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                        "Return type mismatch in '%s': declared '%s', returning '%s'",
                        getCurrentScope(), expected, actualType);
                    reportSemanticError(msg);
                }
                analyzeExpr(node->data.returnExpr);
            }
            break;
        }

        /* ── FUNCTION DECLARATION ────────────────────────────────────────── */
        case NODE_FUNC_DECL: {
            const char* fname      = node->data.funcDecl.name;
            const char* returnType = node->data.funcDecl.returnType;

            printf("  Analyzing function '%s' returns %s\n", fname, returnType);

            /* Switch scope into this function */
            setScope(fname);
            currentFuncReturnType = returnType;

            /* Add parameters as local variables so they are visible in the body */
            addParamsAsLocals(node->data.funcDecl.params, fname);

            /* Analyze the function body */
            analyzeStmt(node->data.funcDecl.body);

            /* Restore global scope */
            setScope("global");
            currentFuncReturnType = NULL;
            break;
        }

        case NODE_WHILE: {
            analyzeExpr(node->data.whileStmt.condition);
            analyzeStmt(node->data.whileStmt.body);
            break;
        }

        case NODE_FOR: {
            /* init — treated like a stand-alone decAssign or assign statement */
            inForInit = 1;
            analyzeStmt(node->data.forStmt.init);
            inForInit = 0;
            /* condition — same as while's condition */
            analyzeExpr(node->data.forStmt.condition);
            /* update — treated like a stand-alone assign statement */
            analyzeStmt(node->data.forStmt.update);
            /* body */
            analyzeStmt(node->data.forStmt.body);
            break;
        }

        case NODE_STMT_LIST:
            analyzeStmt(node->data.stmtlist.stmt);
            analyzeStmt(node->data.stmtlist.next);
            break;

        case NODE_STRUCT_DECL: {
            /* Register the struct type and all its fields */
            char* sname = node->data.structDecl.name;
            if (addStructDef(sname) == -1) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Struct '%s' already defined", sname);
                reportSemanticError(msg);
                break;
            }
            /* Walk the field list recursively — the grammar builds a left-leaning
             * NODE_STMT_LIST tree, so a flat while-loop only reaches 2 fields.
             * registerStructFields handles arbitrary depth. */
            registerStructFields(sname, node->data.structDecl.fields);
            printf("  ✓ Struct type '%s' defined (%d field(s))\n",
                   sname, getStructFieldCount(sname));
            break;
        }

        case NODE_STRUCT_VAR: {
            char* stype = node->data.structVar.structType;
            char* vname = node->data.structVar.varName;
            if (!isStructDefined(stype)) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Struct type '%s' is not defined (used for variable '%s')",
                    stype, vname);
                reportSemanticError(msg);
                break;
            }
            int off = addStructVar(vname, stype);
            if (off == -1) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Variable '%s' already declared in this scope", vname);
                reportSemanticError(msg);
            } else {
                markInitialized(vname);
                printf("  ✓ Struct variable '%s' of type '%s' declared at offset %d\n",
                       vname, stype, off);
            }
            break;
        }

        case NODE_FIELD_ASSIGN: {
            char* vname = node->data.fieldAssign.varName;
            char* fname = node->data.fieldAssign.fieldName;
            const char* vtype = getVarType(vname);
            if (!vtype) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Variable '%s' not declared", vname);
                reportSemanticError(msg);
                break;
            }
            if (getStructFieldOffset((char*)vtype, fname) == -1) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Struct '%s' has no field '%s'", vtype, fname);
                reportSemanticError(msg);
            }
            analyzeExpr(node->data.fieldAssign.value);
            break;
        }
        case NODE_IF: {
            analyzeExpr(node->data.ifStmt.condition);
            analyzeStmt(node->data.ifStmt.thenBody);
            if (node->data.ifStmt.elseBody) {
                analyzeStmt(node->data.ifStmt.elseBody);
            }
            break;
        }
        case NODE_ELSE: {
            analyzeStmt(node->data.elseBody);
            break;
        }
       case NODE_SWITCH: {
            analyzeExpr(node->data.switchStmt.expr);
            analyzeStmt(node->data.switchStmt.cases);
            break;
        }
        case NODE_CASE: {
            analyzeExpr(node->data.caseStmt.value);
            analyzeStmt(node->data.caseStmt.body);
            break;
        }

        case NODE_DEFAULT: {
            analyzeStmt(node->data.defaultBody);
            break;
        }
        
        default:
            break;
    }
}

/* ── PROGRAM ANALYSIS ────────────────────────────────────────────────────── */
int analyzeProgram(ASTNode* root) {
    printf("Starting semantic analysis...\n");
    printf("───────────────────────────────\n");

    initSymTab();
    initFuncTab();
    initStructTab();

    /* First pass: register all function signatures so forward calls work */
    registerFunctions(root);

    /* Second pass: full semantic analysis */
    analyzeStmt(root);

    /* Enforce mandatory entry point.
     * The class notes specify Master() as the required program entry point. */
    if (!isFuncDeclared("Master")) {
        fprintf(stderr,
            "\n✗ SEMANTIC ERROR: No 'Master' function declared.\n"
            "   Every program must define an entry point:\n"
            "   function Master() returns nothing { ... }\n\n");
        semanticErrors++;
    } else {
        printf("  ✓ Entry point 'Master()' is declared\n");
    }

    printf("───────────────────────────────\n");

    if (semanticErrors == 0) {
        printf("✓ Semantic analysis passed — no errors found!\n");
        return 1;
    } else {
        fprintf(stderr, "✗ Semantic analysis failed with %d error(s)\n",
                semanticErrors);
        return 0;
    }
}