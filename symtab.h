#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Extended for Project 3 to support:
 *   - Multiple variable types (int, float, char, bool)
 *   - Scoped variables: each symbol records which function it belongs to,
 *     or "global" if it lives at the top level.
 *   - A separate function table tracking declared functions and their
 *     signatures (return type, parameter count, and parameter types).
 *
 * Scope rules:
 *   - When compiling inside a function, local variables are added with
 *     scope = that function's name.
 *   - Lookups search the current scope first, then "global".
 *   - setScope / getCurrentScope manage the active compilation context.
 */

#define MAX_VARS   200   /* max total symbols across all scopes */
#define MAX_FUNCS   50   /* max function declarations */
#define MAX_PARAMS  20   /* max parameters per function */

/* ── VARIABLE SYMBOL ─────────────────────────────────────────────────────── */
typedef struct {
    char* name;     /* identifier */
    char* type;     /* "int", "float", "char", "bool" */
    char* scope;    /* "global" or function name for locals */
    int   offset;   /* stack offset in bytes within its scope's frame */
} Symbol;

typedef struct {
    Symbol vars[MAX_VARS];
    int    count;
    int    nextGlobalOffset;   /* offset counter for global scope */
    int    nextLocalOffset;    /* offset counter for current function scope */
} SymbolTable;

/* ── FUNCTION SYMBOL ─────────────────────────────────────────────────────── */
typedef struct {
    char* name;
    char* returnType;
    char* paramNames[MAX_PARAMS];
    char* paramTypes[MAX_PARAMS];
    int   paramCount;
} FuncSymbol;

typedef struct {
    FuncSymbol funcs[MAX_FUNCS];
    int        count;
} FuncTable;

/* ── SYMBOL TABLE OPERATIONS ─────────────────────────────────────────────── */
void  initSymTab();
int   addVar(char* name, char* type);   /* uses current scope; -1 = duplicate */
int   getVarOffset(char* name);         /* current scope then global; -1 = not found */
int   isVarDeclared(char* name);
const char* getVarType(char* name);           /* returns type string or NULL */
void  printSymTab();

/* Scope control */
void  setScope(const char* scope);      /* switch active compilation scope */
const char* getCurrentScope();

/* Read-only accessors for codegen */
int   getVarCount();
char* getVarNameAt(int index);
char* getVarScopeAt(int index);
int   getVarOffsetAt(int index);
int   getStackUsage();                  /* total bytes used in current scope */
int   isVarGlobal(const char* name);   /* 1 if the variable lives in global scope */

/* ── FUNCTION TABLE OPERATIONS ───────────────────────────────────────────── */
void  initFuncTab();
int   addFunc(char* name, char* returnType);  /* -1 = duplicate */
int   addFuncParam(char* funcName, char* paramType, char* paramName);
int   isFuncDeclared(char* name);
char* getFuncReturnType(char* name);   /* NULL if not found */
int   getFuncParamCount(char* name);   /* -1 if not found */
char* getFuncParamType(char* name, int idx);
char* getFuncParamName(char* name, int idx);

/* TODO: When arrays are added, the symbol table will need an additional
 * field in Symbol to track array size, and array-specific helpers:
 *   int addArray(char* name, char* type, int size);
 *   int getArraySize(char* name);
 *   int getArrayElementOffset(char* name, int index);
 */

#endif
