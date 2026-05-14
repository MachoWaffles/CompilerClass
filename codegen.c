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

    fprintf(stderr, "Error: Out of temporary registers\n");
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
                        "Error: Variable %s not declared\n",
                        node->data.name);
                exit(1);
            }

            int reg = getNextTemp();

            fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);

            return reg;
        }

        case NODE_BINOP: {
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
                        "Error: Variable %s already declared\n",
                        node->data.decl.name);
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
                        "Error: Variable %s not declared\n",
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

        default:
            break;
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");

    if (!output) {
        fprintf(stderr,
                "Cannot open output file %s\n",
                filename);
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

    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");

    fclose(output);
}