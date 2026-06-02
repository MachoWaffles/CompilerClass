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
            
        case NODE_BINOP: {
            const char* lt = getExprType(node->data.binop.left);
            const char* rt = getExprType(node->data.binop.right);
            /* If either operand is float, the result is float (standard promotion) */
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

/* ── FIRST PASS: Register all function declarations ──────────────────────── */
/* We do a quick scan before the main analysis so that forward calls to
 * functions declared later in the file are handled correctly. */
static void registerFunctions(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        registerFunctions(node->data.stmtlist.stmt);
        registerFunctions(node->data.stmtlist.next);
        return;
    }
    if (node->type == NODE_FUNC_DECL) {
        addFunc(node->data.funcDecl.name, node->data.funcDecl.returnType);
        /* Register parameters so their types are available for call-site checks */
        ASTNode* p = node->data.funcDecl.params;
        while (p) {
            if (p->type == NODE_PARAM_DECL) {
                addFuncParam(node->data.funcDecl.name,
                             p->data.param.paramType,
                             p->data.param.name);
                p = NULL; /* single param — no next */
            } else if (p->type == NODE_STMT_LIST) {
                ASTNode* curr = p->data.stmtlist.stmt;
                if (curr && curr->type == NODE_PARAM_DECL) {
                    addFuncParam(node->data.funcDecl.name,
                                 curr->data.param.paramType,
                                 curr->data.param.name);
                }
                p = p->data.stmtlist.next;
            } else {
                break;
            }
        }
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

            /* Count and type-check arguments */
            int expectedCount = getFuncParamCount((char*)fname);
            int actualCount   = 0;
            ASTNode* arg      = node->data.funcCall.args;
            int argIdx        = 0;

            /* Walk the argument list (stored as nested STMT_LIST or single expr) */
            while (arg) {
                ASTNode* argExpr = NULL;
                if (arg->type == NODE_STMT_LIST) {
                    argExpr = arg->data.stmtlist.stmt;
                    arg     = arg->data.stmtlist.next;
                } else {
                    argExpr = arg;
                    arg     = NULL;
                }
                if (!argExpr) break;
                actualCount++;

                /* Type-check this argument against the declared parameter type */
                const char* argType   = getExprType(argExpr);
                const char* paramType = getFuncParamType((char*)fname, argIdx);
                if (paramType && argType &&
                    !typesCompatible(paramType, argType)) {
                    char msg[512];
                    snprintf(msg, sizeof(msg),
                        "Argument %d to '%s': expected %s, got %s",
                        argIdx + 1, fname, paramType, argType);
                    reportSemanticError(msg);
                }
                analyzeExpr(argExpr);
                argIdx++;
            }

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
            int offset = addVar(node->data.DecAssignNode.name,
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
            ASTNode* p = node->data.funcDecl.params;
            while (p) {
                ASTNode* paramNode = NULL;
                if (p->type == NODE_PARAM_DECL) {
                    paramNode = p;
                    p = NULL;
                } else if (p->type == NODE_STMT_LIST) {
                    paramNode = p->data.stmtlist.stmt;
                    p = p->data.stmtlist.next;
                } else {
                    break;
                }
                if (paramNode && paramNode->type == NODE_PARAM_DECL) {
                    int off = addVar(paramNode->data.param.name,
                                     paramNode->data.param.paramType);
                    if (off != -1) {
                        markInitialized(paramNode->data.param.name);
                        printf("  ✓ Parameter '%s' (type: %s) added to scope '%s'\n",
                               paramNode->data.param.name,
                               paramNode->data.param.paramType, fname);
                    }
                }
            }

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

        case NODE_STMT_LIST:
            analyzeStmt(node->data.stmtlist.stmt);
            analyzeStmt(node->data.stmtlist.next);
            break;

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
