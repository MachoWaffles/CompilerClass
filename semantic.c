/* SEMANTIC ANALYZER IMPLEMENTATION
 * Checks the AST for semantic errors before code generation
 * This ensures the program makes sense semantically, even if syntactically correct
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symtab.h"

/* yylineno is available from the lexer, but note: since semantic analysis
 * runs after parsing is fully complete, yylineno reflects the last line of
 * the source file, not the actual location of the error. For accurate per-node
 * line numbers, AST nodes would need to store their own line info at parse time. */
extern int yylineno;

/* Track number of semantic errors found */
int semanticErrors = 0;

/* Track which variables have been initialized (assigned a value).
 * A variable is "declared" when its NODE_DECL or NODE_DEC_ASSIGN is processed.
 * It is "initialized" only after a NODE_ASSIGN or NODE_DEC_ASSIGN sets a value.
 * Used to warn when a declared-but-never-assigned variable is read. */
static char* initializedVars[100];
static int   initializedCount = 0;

/* Mark a variable as initialized (has been assigned a value) */
static void markInitialized(const char* name) {
    for (int i = 0; i < initializedCount; i++) {
        if (strcmp(initializedVars[i], name) == 0) return;  /* Already marked */
    }
    if (initializedCount < 100) {
        initializedVars[initializedCount++] = strdup(name);
    }
}

/* Check whether a variable has been initialized */
static int isInitialized(const char* name) {
    for (int i = 0; i < initializedCount; i++) {
        if (strcmp(initializedVars[i], name) == 0) return 1;
    }
    return 0;
}

/* Initialize semantic analyzer */
void initSemantic() {
    semanticErrors  = 0;
    initializedCount = 0;
    printf("SEMANTIC ANALYZER: Initialized\n\n");
}

/* Report a semantic error — goes to stderr so it is not mixed with normal output */
void reportSemanticError(const char* msg) {
    fprintf(stderr, "✗ SEMANTIC ERROR (near line %d): %s\n", yylineno, msg);
    semanticErrors++;
}

/* Report a semantic warning — non-fatal, printed to stdout to stay visible
 * alongside the normal phase output, but clearly labelled as a warning */
void reportSemanticWarning(const char* msg) {
    printf("⚠ SEMANTIC WARNING (near line %d): %s\n", yylineno, msg);
}

/* Analyze an expression for semantic correctness */
void analyzeExpr(ASTNode* node) {
    if (!node) return;

    switch(node->type) {
        case NODE_NUM:
            /* Numbers are always valid */
            break;

        case NODE_VAR: {
            /* Check if variable has been declared */
            if (!isVarDeclared(node->data.name)) {
                char errorMsg[256];
                sprintf(errorMsg, "Variable '%s' used before declaration", node->data.name);
                reportSemanticError(errorMsg);
            } else {
                printf("  ✓ Variable '%s' is declared\n", node->data.name);
                /* Check if variable has ever been assigned a value */
                if (!isInitialized(node->data.name)) {
                    char warnMsg[256];
                    sprintf(warnMsg,
                            "Variable '%s' may be used before being assigned a value",
                            node->data.name);
                    reportSemanticWarning(warnMsg);
                }
            }
            break;
        }

        case NODE_BINOP:
            /* Division by zero: catch compile-time constant division by 0.
             * This language currently only supports '+', but this check is in
             * place for when division is added so the error fires immediately. */
            if (node->data.binop.op == '/') {
                if (node->data.binop.right &&
                    node->data.binop.right->type == NODE_NUM &&
                    node->data.binop.right->data.num == 0) {
                    reportSemanticError("Division by zero: dividing by the constant 0 is undefined");
                }
            }
            /* Recursively analyze both operands */
            analyzeExpr(node->data.binop.left);
            analyzeExpr(node->data.binop.right);
            break;

        default:
            break;
    }
}

/* Analyze a statement for semantic correctness */
void analyzeStmt(ASTNode* node) {
    if (!node) return;

    switch(node->type) {
        case NODE_DECL: {
            /* Check if variable is already declared */
            if (isVarDeclared(node->data.decl.name)) {
                char errorMsg[256];
                sprintf(errorMsg, "Variable '%s' already declared", node->data.decl.name);
                reportSemanticError(errorMsg);
            } else {
                /* Add variable to symbol table with its type */
                int offset = addVar(node->data.decl.name, node->data.decl.varType);
                if (offset != -1) {
                    printf("  ✓ Variable '%s' (type: %s) declared successfully\n",
                           node->data.decl.name, node->data.decl.varType);
                }
                /* Note: variable is declared but NOT yet initialized.
                 * It will be marked initialized when a NODE_ASSIGN is seen for it. */
            }
            break;
        }

        case NODE_ASSIGN: {
            /* Check if variable being assigned to has been declared */
            if (!isVarDeclared(node->data.assign.var)) {
                char errorMsg[256];
                sprintf(errorMsg, "Cannot assign to undeclared variable '%s'", node->data.assign.var);
                reportSemanticError(errorMsg);
            } else {
                printf("  ✓ Assignment to declared variable '%s'\n", node->data.assign.var);
                /* Mark the variable as initialized now that it has been assigned */
                markInitialized(node->data.assign.var);
            }
            /* Check the expression being assigned */
            analyzeExpr(node->data.assign.value);
            break;
        }

        case NODE_PRINT:
            /* Check the expression being printed */
            printf("  Checking print statement expression:\n");
            analyzeExpr(node->data.expr);
            break;

        case NODE_STMT_LIST:
            /* Recursively analyze all statements */
            analyzeStmt(node->data.stmtlist.stmt);
            analyzeStmt(node->data.stmtlist.next);
            break;

        case NODE_DEC_ASSIGN: {
            if (isVarDeclared(node->data.DecAssignNode.name)) {
                char errorMsg[256];
                sprintf(errorMsg, "Variable '%s' already declared", node->data.DecAssignNode.name);
                reportSemanticError(errorMsg);
            } else {
                int offset = addVar(node->data.DecAssignNode.name, node->data.DecAssignNode.varType);
                if (offset != -1) {
                    printf("  ✓ Variable '%s' (type: %s) declared and assigned\n",
                           node->data.DecAssignNode.name, node->data.DecAssignNode.varType);
                    /* Declaration-with-assignment counts as initialized immediately */
                    markInitialized(node->data.DecAssignNode.name);
                }
            }
            analyzeExpr(node->data.DecAssignNode.value);
            break;
        }

        default:
            break;
    }
}

/* Analyze the entire program */
int analyzeProgram(ASTNode* root) {
    printf("Starting semantic analysis...\n");
    printf("───────────────────────────────\n");

    /* Initialize symbol table for semantic checking */
    initSymTab();

    /* Analyze all statements */
    analyzeStmt(root);

    printf("───────────────────────────────\n");

    /* Report results */
    if (semanticErrors == 0) {
        printf("✓ Semantic analysis passed - no errors found!\n");
        return 1;  /* Success */
    } else {
        fprintf(stderr, "✗ Semantic analysis failed with %d error(s)\n", semanticErrors);
        return 0;  /* Failure */
    }
}