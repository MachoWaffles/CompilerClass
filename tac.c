/* THREE-ADDRESS CODE (TAC) IMPLEMENTATION
 * Converts the AST into a flat sequence of simple instructions.
 * Extended for Project 3 to handle:
 *   - Float, char, and bool literals (stored as their string representation)
 *   - Function declarations (label + param setup + body + return)
 *   - Function calls (argument passing via P0/P1/... then TAC_CALL)
 *   - Return statements
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;

void initTAC() {
    tacList.head       = NULL;
    tacList.tail       = NULL;
    tacList.tempCount  = 0;
    tacList.paramCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

/* Generate next expression temporary: t0, t1, t2, ... */
char* newTemp() {
    char* temp = malloc(16);
    sprintf(temp, "t%d", tacList.tempCount++);
    return temp;
}

/* Generate next parameter slot name: P0, P1, P2, ... (class notes convention) */
char* newParam() {
    char* p = malloc(16);
    sprintf(p, "P%d", tacList.paramCount++);
    return p;
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op     = op;
    instr->arg1   = arg1   ? strdup(arg1)   : NULL;
    instr->arg2   = arg2   ? strdup(arg2)   : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next   = NULL;
    return instr;
}

void appendTAC(TACInstr* instr) {
    if (!tacList.head) {
        tacList.head = tacList.tail = instr;
    } else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

static void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head) {
        optimizedList.head = optimizedList.tail = instr;
    } else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

/* ── EXPRESSION TAC ──────────────────────────────────────────────────────── */
char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_NUM: {
            char* s = malloc(24);
            sprintf(s, "%d", node->data.num);
            return s;
        }
        case NODE_FLOAT_LIT: {
            char* s = malloc(32);
            sprintf(s, "%g", node->data.fval);
            return s;
        }
        case NODE_CHAR_LIT: {
            /* Represent char literals as their ASCII integer value in TAC */
            char* s = malloc(8);
            sprintf(s, "%d", node->data.num);
            return s;
        }
        case NODE_BOOL_LIT: {
            return strdup(node->data.num ? "1" : "0");
        }
        case NODE_VAR:
            return strdup(node->data.name);

        case NODE_BINOP: {
            char* left  = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp  = newTemp();

        if (node->data.binop.op == '+') {
            appendTAC(createTAC(TAC_ADD, left, right, temp));
        } else if (node->data.binop.op == '-') {
            appendTAC(createTAC(TAC_SUB, left, right, temp));
        } else if (node->data.binop.op == '*') {
            appendTAC(createTAC(TAC_MUL, left, right, temp));
        } else if (node->data.binop.op == '/') {
            appendTAC(createTAC(TAC_DIV, left, right, temp));
        }

        if (left) free(left);
        if (right) free(right);

        return temp;
    }
        case NODE_ARRAY_ACCESS: {
            char* index = generateTACExpr(node->data.arrayAccess.index);

            char* result = malloc(128);
            sprintf(result, "%s[%s]",
                node->data.arrayAccess.name,
                index ? index : "0");

        if (index) free(index);

        return result;
    }

        case NODE_FUNC_CALL: {
            /* Arguments are passed as P0, P1, P2, ...
             * Reset the param counter at each call site. */
            tacList.paramCount = 0;
            ASTNode* arg = node->data.funcCall.args;
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

                char* argVal  = generateTACExpr(argExpr);
                char* paramSl = newParam();
                appendTAC(createTAC(TAC_PARAM, argVal, NULL, paramSl));
                free(argVal);
            }

            /* The return value, if any, lands in a fresh temporary */
            char* retTemp = newTemp();
            appendTAC(createTAC(TAC_CALL,
                                 node->data.funcCall.name, NULL, retTemp));
            return retTemp;
        }

        default:
            return NULL;
    }
}

/* ── STATEMENT TAC ───────────────────────────────────────────────────────── */
void generateTAC(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL,
                                 node->data.decl.varType, NULL,
                                 node->data.decl.name));
            break;

        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            free(expr);
            break;
        }

        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            free(expr);
            break;
        }

        case NODE_DEC_ASSIGN:
            appendTAC(createTAC(TAC_DECL,
                                 node->data.DecAssignNode.varType, NULL,
                                 node->data.DecAssignNode.name));
            {
                char* expr = generateTACExpr(node->data.DecAssignNode.value);
                appendTAC(createTAC(TAC_ASSIGN, expr, NULL,
                                     node->data.DecAssignNode.name));
                free(expr);
            }
            break;

            case NODE_ARRAY_DECL:
                appendTAC(createTAC(
                    TAC_DECL,
                    node->data.arrayDecl.type,
                    NULL,
                    node->data.arrayDecl.name
                    ));
                    break;
                    
                    case NODE_ARRAY_ASSIGN: {
                        char* index = generateTACExpr(node->data.arrayAssign.index);
                        char* value = generateTACExpr(node->data.arrayAssign.value);

                        char target[128];
                        sprintf(target, "%s[%s]",
                            node->data.arrayAssign.name,
                            index ? index : "0");

                    appendTAC(createTAC(
                        TAC_ASSIGN,
                        value,
                        NULL,
                        target
                    ));

                    if (index) free(index);
                    if (value) free(value);
                    
                    break;
                }

        case NODE_FUNC_DECL:
            /* Emit the function label, then its parameter declarations,
             * then the body, then an end marker. */
            appendTAC(createTAC(TAC_FUNC_BEGIN,
                                 node->data.funcDecl.returnType, NULL,
                                 node->data.funcDecl.name));

            /* Declare each parameter as a local variable in TAC */
            {
                ASTNode* p = node->data.funcDecl.params;
                while (p) {
                    ASTNode* paramNode = NULL;
                    if (p->type == NODE_PARAM_DECL) {
                        paramNode = p; p = NULL;
                    } else if (p->type == NODE_STMT_LIST) {
                        paramNode = p->data.stmtlist.stmt;
                        p = p->data.stmtlist.next;
                    } else { break; }
                    if (paramNode && paramNode->type == NODE_PARAM_DECL) {
                        appendTAC(createTAC(TAC_DECL,
                                             paramNode->data.param.paramType, NULL,
                                             paramNode->data.param.name));
                    }
                }
            }

            generateTAC(node->data.funcDecl.body);
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL,
                                 node->data.funcDecl.name));
            break;

        case NODE_RETURN: {
            char* retVal = node->data.returnExpr
                           ? generateTACExpr(node->data.returnExpr)
                           : NULL;
            appendTAC(createTAC(TAC_RETURN, retVal, NULL, NULL));
            if (retVal) free(retVal);
            break;
        }

        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;

        default:
            break;
    }
}

/* ── PRINT TAC ────────────────────────────────────────────────────────────── */
static void printTACInstr(TACInstr* curr, int lineNum, int optimized) {
    printf("%2d: ", lineNum);
    switch (curr->op) {
        case TAC_DECL:
            printf("DECL %s %s",
                   curr->arg1 ? curr->arg1 : "?", curr->result);
            printf("       // Declare '%s' (type: %s)\n",
                   curr->result, curr->arg1 ? curr->arg1 : "unknown");
            break;
        case TAC_ADD:
            printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
            printf("     // Addition\n");
            break;
        case TAC_ASSIGN:
            printf("%s = %s", curr->result, curr->arg1);
            printf("           // Assign\n");
            break;
        case TAC_PRINT:
            printf("PRINT %s", curr->arg1);
            printf("          // Output\n");
            break;
        case TAC_FUNC_BEGIN:
            printf("FUNC_BEGIN %s  returns %s",
                   curr->result, curr->arg1 ? curr->arg1 : "nothing");
            printf("  // --- function start ---\n");
            break;
        case TAC_FUNC_END:
            printf("FUNC_END %s", curr->result);
            printf("         // --- function end ---\n");
            break;
        case TAC_PARAM:
            printf("%s = %s", curr->result, curr->arg1);
            printf("           // Setup parameter slot\n");
            break;
        case TAC_CALL:
            printf("%s = CALL %s", curr->result, curr->arg1);
            printf("     // Call function, result in %s\n", curr->result);
            break;
        case TAC_RETURN:
            if (curr->arg1)
                printf("RETURN %s\n", curr->arg1);
            else
                printf("RETURN  // void return\n");
            break;
        case TAC_SUB:
            printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
            printf("     // Subtraction\n");
            break;
        case TAC_MUL:
            printf("%s = %s * %s", curr->result, curr->arg1, curr->arg2);
            printf("     // Multiplication\n");
            break;
        case TAC_DIV:
            printf("%s = %s / %s", curr->result, curr->arg1, curr->arg2);
            printf("     // Division\n");
            break;
        default:
            printf("(unknown op)\n");
            break;
    }
}

void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int n = 1;
    while (curr) { printTACInstr(curr, n++, 0); curr = curr->next; }
}

/* ── OPTIMIZATION ─────────────────────────────────────────────────────────── */
/* Applies constant folding and copy propagation to the flat TAC list.
 * Function boundary instructions (FUNC_BEGIN/END, PARAM, CALL, RETURN)
 * are passed through unchanged — optimization within function bodies is
 * a future enhancement. */
void optimizeTAC() {
    TACInstr* curr = tacList.head;

    optimizedList.head       = NULL;
    optimizedList.tail       = NULL;

    typedef struct { char* var; char* value; } VarValue;
    VarValue values[200];
    int      valueCount = 0;

    while (curr) {
        TACInstr* newInstr = NULL;

        switch (curr->op) {
            case TAC_DECL:
                newInstr = createTAC(TAC_DECL, curr->arg1, NULL, curr->result);
                break;

            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV: {
                char* left = curr->arg1;
                char* right = curr->arg2;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (left && values[i].var &&
                        strcmp(values[i].var, left) == 0) {
                        left = values[i].value;
                        break;
                    }
                }

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (right && values[i].var &&
                        strcmp(values[i].var, right) == 0) {
                        right = values[i].value;
                        break;
                    }
                }

                int leftConst =
                    left &&
                    (isdigit(left[0]) ||
                    (left[0] == '-' && isdigit(left[1])));

                int rightConst =
                    right &&
                    (isdigit(right[0]) ||
                    (right[0] == '-' && isdigit(right[1])));

                if (leftConst && rightConst) {
                    int a = atoi(left);
                    int b = atoi(right);
                    int result = 0;

                    if (curr->op == TAC_ADD) {
                        result = a + b;
                    } else if (curr->op == TAC_SUB) {
                        result = a - b;
                    } else if (curr->op == TAC_MUL) {
                        result = a * b;
                    } else if (curr->op == TAC_DIV) {
                        if (b == 0) {
                            newInstr = createTAC(curr->op, left, right, curr->result);
                            break;
                        }
                        result = a / b;
                    }

                    char buffer[32];
                    sprintf(buffer, "%d", result);

                    if (curr->result) {
                        values[valueCount].var = strdup(curr->result);
                        values[valueCount].value = strdup(buffer);
                        valueCount++;
                    }

                    newInstr = createTAC(TAC_ASSIGN, buffer, NULL, curr->result);

                } else {
                    newInstr = createTAC(curr->op, left, right, curr->result);
                }

                break;
            }

            case TAC_ASSIGN: {
                char* value = curr->arg1;
                if (value) {
                    for (int i = valueCount - 1; i >= 0; i--) {
                        if (values[i].var && strcmp(values[i].var, value) == 0) {
                            value = values[i].value;
                            break;
                        }
                    }
                }

                if (curr->result && value) {
                    values[valueCount].var   = strdup(curr->result);
                    values[valueCount].value = strdup(value);
                    valueCount++;
                }
                newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
                break;
            }

            case TAC_PRINT: {
                char* value = curr->arg1;
                for (int i = valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }
                newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
                break;
            }

            /* Function instructions pass through unmodified */
            case TAC_FUNC_BEGIN:
            case TAC_FUNC_END:
            case TAC_PARAM:
            case TAC_CALL:
            case TAC_RETURN:
                newInstr = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
                break;

            default:
                break;
        }

        if (newInstr) appendOptimizedTAC(newInstr);
        curr = curr->next;
    }
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int n = 1;
    while (curr) { printTACInstr(curr, n++, 1); curr = curr->next; }
}

/* ── SAVE TO FILE ─────────────────────────────────────────────────────────── */
static void writeTACInstr(FILE* f, TACInstr* curr, int n) {
    fprintf(f, "%2d: ", n);
    switch (curr->op) {
        case TAC_DECL:
            fprintf(f, "DECL %s %s\n",
                    curr->arg1 ? curr->arg1 : "?", curr->result);
            break;
        case TAC_ADD:
            fprintf(f, "%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_SUB:
            fprintf(f, "%s = %s - %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_MUL:
            fprintf(f, "%s = %s * %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_DIV:
            fprintf(f, "%s = %s / %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_ASSIGN:
            fprintf(f, "%s = %s\n", curr->result, curr->arg1);
            break;
        case TAC_PRINT:
            fprintf(f, "PRINT %s\n", curr->arg1);
            break;
        case TAC_FUNC_BEGIN:
            fprintf(f, "FUNC_BEGIN %s\n", curr->result);
            break;
        case TAC_FUNC_END:
            fprintf(f, "FUNC_END %s\n", curr->result);
            break;
        case TAC_PARAM:
            fprintf(f, "%s = %s\n", curr->result, curr->arg1);
            break;
        case TAC_CALL:
            fprintf(f, "%s = CALL %s\n", curr->result, curr->arg1);
            break;
        case TAC_RETURN:
            if (curr->arg1) fprintf(f, "RETURN %s\n", curr->arg1);
            else            fprintf(f, "RETURN\n");
            break;
        default:
            fprintf(f, "(unknown)\n");
            break;
    }
}

void saveTACToFile(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { fprintf(stderr, "Cannot open '%s'\n", filename); return; }
    fprintf(f, "# Three-Address Code (TAC) - Unoptimized\n\n");
    TACInstr* curr = tacList.head;
    int n = 1;
    while (curr) { writeTACInstr(f, curr, n++); curr = curr->next; }
    fclose(f);
}

void saveOptimizedTACToFile(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { fprintf(stderr, "Cannot open '%s'\n", filename); return; }
    fprintf(f, "# Three-Address Code (TAC) - Optimized\n\n");
    TACInstr* curr = optimizedList.head;
    int n = 1;
    while (curr) { writeTACInstr(f, curr, n++); curr = curr->next; }
    fclose(f);
}
