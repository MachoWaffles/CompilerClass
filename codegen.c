#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

FILE* output;

/* Track temporary register usage */
int tempUsed[8] = {0};

/* Allocate next available temp register */
int getNextTemp() {
    for (int i = 0; i < 8; i++) {
        if (!tempUsed[i]) {
            tempUsed[i] = 1;

            printf("[TEMP DEBUG] Using temporary register $t%d\n", i);

            return i;
        }
    }

    /* All 8 registers are in use — this means an expression is nested too deeply */
    fprintf(stderr, "\n❌ Internal Error: Out of temporary registers ($t0-$t7)\n");
    fprintf(stderr, "   All 8 temporary registers are simultaneously in use\n");
    fprintf(stderr, "   This is caused by a deeply nested or very complex expression\n");
    fprintf(stderr, "   💡 Suggestion: Break the expression into smaller steps using\n");
    fprintf(stderr, "      intermediate variables, e.g. instead of:\n");
    fprintf(stderr, "      x = a + b + c + d + e + f + g + h + i;\n");
    fprintf(stderr, "      use: int tmp = a + b + c + d;\n");
    fprintf(stderr, "           x = tmp + e + f + g + h + i;\n\n");
    exit(1);
}

/* Free a temp register */
void free_temp(char *temp) {
    if (temp == NULL) return;

    if (temp[0] == '$' && temp[1] == 't') {
        int reg = atoi(&temp[2]);

        if (reg >= 0 && reg < 8) {
            tempUsed[reg] = 0;

            printf("[TEMP DEBUG] Freed temporary register $t%d\n", reg);
        }
    }
}

/* Reset all temp registers */
void resetTemps() {
    printf("[TEMP DEBUG] Resetting all temporary registers\n");

    for (int i = 0; i < 8; i++) {
        tempUsed[i] = 0;
    }
}

int genExpr(ASTNode* node) {
    if (!node) return -1;

    switch(node->type) {

        case NODE_NUM: {
            int reg = getNextTemp();

            fprintf(output, "    li $t%d, %d\n", reg, node->data.num);

            return reg;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);

            if (offset == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' not declared\n",
                        node->data.name);
                fprintf(stderr,
                        "   💡 Suggestion: Declare the variable before using it: 'int %s;'\n\n",
                        node->data.name);
                exit(1);
            }

            int reg = getNextTemp();

            fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);

            return reg;
        }

        case NODE_BINOP: {
            /* Division by zero: catch compile-time constant division by 0.
             * The language currently only supports '+', but this guard is in place
             * so the check fires immediately if '/' is ever added to the grammar. */
            if (node->data.binop.op == '/') {
                if (node->data.binop.right &&
                    node->data.binop.right->type == NODE_NUM &&
                    node->data.binop.right->data.num == 0) {
                    fprintf(stderr, "\n❌ Code Generation Error: Division by zero detected\n");
                    fprintf(stderr, "   Dividing by the constant 0 produces undefined behavior\n");
                    fprintf(stderr, "   💡 Suggestion: Check your divisor — it must not be 0\n\n");
                    exit(1);
                }
            }

            int leftReg = genExpr(node->data.binop.left);
            int rightReg = genExpr(node->data.binop.right);

            fprintf(output,
                    "    add $t%d, $t%d, $t%d\n",
                    leftReg,
                    leftReg,
                    rightReg);

            char tempName[10];
            sprintf(tempName, "$t%d", rightReg);
            free_temp(tempName);

            return leftReg;
        }

        default:
            return -1;
    }
}

void genStmt(ASTNode* node) {
    if (!node) return;

    switch(node->type) {

        case NODE_DECL: {
            int offset = addVar(node->data.decl.name,
                                node->data.decl.varType);

            if (offset == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' already declared\n",
                        node->data.decl.name);
                fprintf(stderr,
                        "   💡 Suggestion: Each variable name must be unique within the program\n\n");
                exit(1);
            }

            fprintf(output,
                    "    # Declared %s %s at offset %d\n",
                    node->data.decl.varType,
                    node->data.decl.name,
                    offset);

            break;
        }

        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);

            if (offset == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' not declared\n",
                        node->data.assign.var);
                fprintf(stderr,
                        "   💡 Suggestion: Declare the variable before assigning to it: 'int %s;'\n\n",
                        node->data.assign.var);
                exit(1);
            }

            int reg = genExpr(node->data.assign.value);

            fprintf(output,
                    "    sw $t%d, %d($sp)\n",
                    reg,
                    offset);

            char tempName[10];
            sprintf(tempName, "$t%d", reg);
            free_temp(tempName);

            resetTemps();

            break;
        }

        case NODE_PRINT: {
            int reg = genExpr(node->data.expr);

            fprintf(output, "    # Print integer\n");
            fprintf(output, "    move $a0, $t%d\n", reg);
            fprintf(output, "    li $v0, 1\n");
            fprintf(output, "    syscall\n");

            fprintf(output, "    # Print newline\n");
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");

            char tempName[10];
            sprintf(tempName, "$t%d", reg);
            free_temp(tempName);

            resetTemps();

            break;
        }

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        case NODE_DEC_ASSIGN: {
            int offset = addVar(node->data.DecAssignNode.name, node->data.DecAssignNode.varType);
            if (offset == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' already declared\n",
                        node->data.DecAssignNode.name);
                fprintf(stderr,
                        "   💡 Suggestion: Each variable name must be unique within the program\n\n");
                exit(1);
            }
            fprintf(output, "    # Declared %s %s at offset %d\n",
                    node->data.DecAssignNode.varType,
                    node->data.DecAssignNode.name,
                    offset);
            int reg = genExpr(node->data.DecAssignNode.value);
            fprintf(output, "    sw $t%d, %d($sp)\n", reg, offset);
            char tempName[10];
            sprintf(tempName, "$t%d", reg);
            free_temp(tempName);
            resetTemps();
            break;
        }

        default:
            break;
    }
}

/* --- Pre-pass: collect all variable names that are READ in expressions ---
 * "Read" means appearing as a NODE_VAR in an expression context.
 * Variables that are only declared and assigned but never read are unused. */
static char* usedVarNames[100];
static int   usedVarCount = 0;

static void collectUsedVars(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_VAR: {
            /* Record this variable as used (read), avoid duplicates */
            for (int i = 0; i < usedVarCount; i++) {
                if (strcmp(usedVarNames[i], node->data.name) == 0) return;
            }
            if (usedVarCount < 100) {
                usedVarNames[usedVarCount++] = node->data.name;
            }
            break;
        }
        case NODE_BINOP:
            collectUsedVars(node->data.binop.left);
            collectUsedVars(node->data.binop.right);
            break;
        case NODE_ASSIGN:
            collectUsedVars(node->data.assign.value);
            break;
        case NODE_PRINT:
            collectUsedVars(node->data.expr);
            break;
        case NODE_DEC_ASSIGN:
            collectUsedVars(node->data.DecAssignNode.value);
            break;
        case NODE_STMT_LIST:
            collectUsedVars(node->data.stmtlist.stmt);
            collectUsedVars(node->data.stmtlist.next);
            break;
        default:
            break;
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");

    if (!output) {
        fprintf(stderr,
                "\n❌ File Error: Cannot open output file '%s'\n",
                filename);
        fprintf(stderr,
                "   💡 Suggestion: Check that the directory exists and you have write permission\n\n");
        exit(1);
    }

    initSymTab();

    fprintf(output, ".data\n");
    fprintf(output, "\n.text\n");
    fprintf(output, ".globl main\n");
    fprintf(output, "main:\n");

    fprintf(output, "    # Allocate stack space\n");
    fprintf(output, "    addi $sp, $sp, -400\n\n");

    genStmt(root);

    /* --- Stack overflow check ---
     * The stack was allocated as 400 bytes. Each int variable uses 4 bytes,
     * so the program supports at most 100 variables. If more were declared,
     * variables will have silently overwritten each other in memory. */
    int stackUsed = getStackUsage();
    if (stackUsed > 400) {
        fprintf(stderr, "\n⚠ Warning: Stack overflow in generated code\n");
        fprintf(stderr, "   Program declared %d variables requiring %d bytes,\n",
                getVarCount(), stackUsed);
        fprintf(stderr, "   but only 400 bytes of stack were allocated\n");
        fprintf(stderr, "   Variables will have overwritten each other in memory\n");
        fprintf(stderr, "   💡 Suggestion: Reduce the number of variables (max 100 int variables)\n\n");
    }

    /* --- Unused variable warnings ---
     * Collect every variable that is actually read in an expression, then
     * compare against every declared variable. Any declared variable that
     * never appears in a read context gets a warning. */
    usedVarCount = 0;
    collectUsedVars(root);

    int declaredCount = getVarCount();
    for (int i = 0; i < declaredCount; i++) {
        char* varName = getVarNameAt(i);
        if (!varName) continue;

        int found = 0;
        for (int j = 0; j < usedVarCount; j++) {
            if (strcmp(varName, usedVarNames[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "\n⚠ Warning: Variable '%s' is declared but never used\n", varName);
            fprintf(stderr, "   💡 Suggestion: Remove the declaration or use '%s' in an expression\n\n",
                    varName);
        }
    }

    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");

    fclose(output);
}