#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

static FILE* output;

/* ── TEMPORARY REGISTER POOL ($t0-$t7) ──────────────────────────────────── */
static int tempUsed[8] = {0};

static int getNextTemp() {
    for (int i = 0; i < 8; i++) {
        if (!tempUsed[i]) {
            tempUsed[i] = 1;
            return i;
        }
    }

    fprintf(stderr,
            "\n❌ Internal Error: Out of temporary registers ($t0-$t7)\n");
    exit(1);
}

static void free_temp(int r) {
    if (r >= 0 && r < 8)
        tempUsed[r] = 0;
}

static void resetTemps() {
    for (int i = 0; i < 8; i++)
        tempUsed[i] = 0;
}

/* ── UNIQUE LABEL COUNTER ───────────────────────────────────────────────── */
static int printLabelCount = 0;

/* ── FORWARD DECLARATIONS ───────────────────────────────────────────────── */
static int         genExpr(ASTNode* node);
static void        genStmt(ASTNode* node);
static const char* inferExprType(ASTNode* node);

/* ── TYPE INFERENCE ──────────────────────────────────────────────────────
 * Best-effort: walks the expression and returns the most likely type string.
 * Falls back to "int" for anything it can't determine.
 */
static const char* inferExprType(ASTNode* node) {
    if (!node) return "int";

    switch (node->type) {
        case NODE_FLOAT_LIT: return "float";
        case NODE_BOOL_LIT:  return "bool";
        case NODE_CHAR_LIT:  return "char";
        case NODE_NUM:       return "int";

        case NODE_VAR: {
            const char* t = getVarType(node->data.name);
            fprintf(stderr, "DEBUG inferExprType: var '%s' -> type '%s' (scope: %s)\n",
                    node->data.name, t ? t : "NULL", getCurrentScope());
            return t ? t : "int";
        }

        case NODE_BINOP: {
            /* If either operand is float, the result is float */
            const char* lType = inferExprType(node->data.binop.left);
            const char* rType = inferExprType(node->data.binop.right);
            if (strcmp(lType, "float") == 0 || strcmp(rType, "float") == 0)
                return "float";
            return lType;
        }

        case NODE_FUNC_CALL:
            /* We don't track return types through the symbol table yet,
             * so default to int — extend this when return types are stored. */
            return "int";

        default:
            return "int";
    }
}

/* ── EXPRESSION CODE GENERATION ─────────────────────────────────────────── */
static int genExpr(ASTNode* node) {
    if (!node)
        return -1;

    switch (node->type) {

        case NODE_NUM: {
            int r = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", r, node->data.num);
            return r;
        }

        case NODE_FLOAT_LIT: {
            int r = getNextTemp();

            union {
                float f;
                int   i;
            } cvt;

            cvt.f = node->data.fval;

            fprintf(output,
                    "    # float literal %g (IEEE bits 0x%08X)\n",
                    node->data.fval,
                    (unsigned)cvt.i);

            fprintf(output, "    li $t%d, %d\n", r, cvt.i);

            return r;
        }

        case NODE_CHAR_LIT:
        case NODE_BOOL_LIT: {
            int r = getNextTemp();
            fprintf(output, "    li $t%d, %d\n", r, node->data.num);
            return r;
        }

        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);

            if (offset == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' not found\n",
                        node->data.name);
                exit(1);
            }

            int r = getNextTemp();

            if (isVarGlobal(node->data.name))
                fprintf(output, "    lw $t%d, %d($sp)\n", r, offset);
            else
                fprintf(output, "    lw $t%d, %d($fp)\n", r, offset);

            return r;
        }

        case NODE_BINOP: {

            if (node->data.binop.op == '/' &&
                node->data.binop.right &&
                node->data.binop.right->type == NODE_NUM &&
                node->data.binop.right->data.num == 0) {

                fprintf(stderr,
                        "\n❌ Code Generation Error: Division by zero\n");
                exit(1);
            }

            /* Determine if this is a float operation */
            const char* lType = inferExprType(node->data.binop.left);
            const char* rType = inferExprType(node->data.binop.right);
            int isFloat = (strcmp(lType, "float") == 0 || strcmp(rType, "float") == 0);

            int lR = genExpr(node->data.binop.left);
            int rR = genExpr(node->data.binop.right);

            if (isFloat) {
                /* Move bits into float registers, converting ints if needed */
                fprintf(output, "    mtc1 $t%d, $f0\n", lR);
                if (strcmp(lType, "int") == 0)
                    fprintf(output, "    cvt.s.w $f0, $f0\n");

                fprintf(output, "    mtc1 $t%d, $f2\n", rR);
                if (strcmp(rType, "int") == 0)
                    fprintf(output, "    cvt.s.w $f2, $f2\n");

                switch (node->data.binop.op) {
                    case '+':
                        fprintf(output, "    add.s $f0, $f0, $f2\n");
                        break;
                    case '-':
                        fprintf(output, "    sub.s $f0, $f0, $f2\n");
                        break;
                    case '*':
                        fprintf(output, "    mul.s $f0, $f0, $f2\n");
                        break;
                    case '/':
                        fprintf(output, "    div.s $f0, $f0, $f2\n");
                        break;
                    default:
                        fprintf(stderr,
                                "\n❌ Unsupported binary operator '%c'\n",
                                node->data.binop.op);
                        exit(1);
                }

                /* Move result bits back to integer register */
                fprintf(output, "    mfc1 $t%d, $f0\n", lR);
            }
            else {
                switch (node->data.binop.op) {

                    case '+':
                        fprintf(output,
                                "    add $t%d, $t%d, $t%d\n",
                                lR, lR, rR);
                        break;

                    case '-':
                        fprintf(output,
                                "    sub $t%d, $t%d, $t%d\n",
                                lR, lR, rR);
                        break;

                    case '*':
                        fprintf(output,
                                "    mul $t%d, $t%d, $t%d\n",
                                lR, lR, rR);
                        break;

                    case '/':
                        fprintf(output,
                                "    div $t%d, $t%d\n",
                                lR, rR);
                        fprintf(output,
                                "    mflo $t%d\n",
                                lR);
                        break;

                    default:
                        fprintf(stderr,
                                "\n❌ Unsupported binary operator '%c'\n",
                                node->data.binop.op);
                        exit(1);
                }
            }

            free_temp(rR);

            return lR;
        }

        case NODE_FUNC_CALL: {

            int argRegs[4];
            int argCount = 0;

            ASTNode* arg = node->data.funcCall.args;

            while (arg && argCount < 4) {

                ASTNode* argExpr = NULL;

                if (arg->type == NODE_STMT_LIST) {
                    argExpr = arg->data.stmtlist.stmt;
                    arg     = arg->data.stmtlist.next;
                }
                else {
                    argExpr = arg;
                    arg     = NULL;
                }

                if (!argExpr)
                    break;

                argRegs[argCount] = genExpr(argExpr);

                fprintf(output,
                        "    move $a%d, $t%d\n",
                        argCount,
                        argRegs[argCount]);

                argCount++;
            }

            fprintf(output,
                    "    jal _%s\n",
                    node->data.funcCall.name);

            for (int i = 0; i < argCount; i++)
                free_temp(argRegs[i]);

            int retR = getNextTemp();

            fprintf(output,
                    "    move $t%d, $v0\n",
                    retR);

            return retR;
        }

        default:
            return -1;
    }
}

/* ── COUNT LOCALS ───────────────────────────────────────────────────────── */
static int countLocals(ASTNode* node) {

    if (!node)
        return 0;

    if (node->type == NODE_DECL ||
        node->type == NODE_DEC_ASSIGN)
        return 1;

    if (node->type == NODE_STMT_LIST)
        return countLocals(node->data.stmtlist.stmt)
             + countLocals(node->data.stmtlist.next);

    return 0;
}

/* ── FUNCTION CODE GENERATION ───────────────────────────────────────────── */
static void genFuncDecl(ASTNode* node) {

    const char* fname = node->data.funcDecl.name;

    int frameSize = 8;

    ASTNode* p = node->data.funcDecl.params;

    while (p) {

        if (p->type == NODE_PARAM_DECL) {
            frameSize += 4;
            p = NULL;
        }
        else if (p->type == NODE_STMT_LIST) {

            if (p->data.stmtlist.stmt &&
                p->data.stmtlist.stmt->type == NODE_PARAM_DECL)
                frameSize += 4;

            p = p->data.stmtlist.next;
        }
        else {
            break;
        }
    }

    frameSize += countLocals(node->data.funcDecl.body) * 4;

    fprintf(output, "\n# Function: %s\n", fname);
    fprintf(output, "_%s:\n", fname);

    fprintf(output,
            "    addi $sp, $sp, -%d\n",
            frameSize);

    fprintf(output,
            "    sw   $ra, %d($sp)\n",
            frameSize - 4);

    fprintf(output,
            "    sw   $fp, %d($sp)\n",
            frameSize - 8);

    fprintf(output,
            "    move $fp, $sp\n\n");

    /* Parameters */

    int paramIdx = 0;

    ASTNode* params = node->data.funcDecl.params;

    while (params) {

        ASTNode* paramNode = NULL;

        if (params->type == NODE_PARAM_DECL) {
            paramNode = params;
            params = NULL;
        }
        else if (params->type == NODE_STMT_LIST) {
            paramNode = params->data.stmtlist.stmt;
            params = params->data.stmtlist.next;
        }
        else {
            break;
        }

        if (paramNode &&
            paramNode->type == NODE_PARAM_DECL &&
            paramIdx < 4) {

            int offset =
                addVar(paramNode->data.param.name,
                       paramNode->data.param.paramType);

            fprintf(output,
                    "    sw $a%d, %d($fp)   # param '%s'\n",
                    paramIdx,
                    offset,
                    paramNode->data.param.name);

            paramIdx++;
        }
    }

    genStmt(node->data.funcDecl.body);

    fprintf(output, "\n    # Epilogue\n");

    fprintf(output,
            "    lw   $ra, %d($sp)\n",
            frameSize - 4);

    fprintf(output,
            "    lw   $fp, %d($sp)\n",
            frameSize - 8);

    fprintf(output,
            "    addi $sp, $sp, %d\n",
            frameSize);

    fprintf(output,
            "    jr   $ra\n");

    fprintf(output,
            "# End _%s\n",
            fname);

    resetTemps();
}

/* ── STATEMENT CODE GENERATION ──────────────────────────────────────────── */
static void genStmt(ASTNode* node) {

    if (!node)
        return;

    switch (node->type) {

        case NODE_DECL: {

            if (strcmp(getCurrentScope(), "global") != 0) {

                int offset =
                    addVar(node->data.decl.name,
                           node->data.decl.varType);

                if (offset == -1) {

                    fprintf(stderr,
                            "\n❌ Code Generation Error: Variable '%s' already declared\n",
                            node->data.decl.name);

                    exit(1);
                }

                fprintf(output,
                        "    # Declare %s %s at offset %d\n",
                        node->data.decl.varType,
                        node->data.decl.name,
                        offset);
            }

            break;
        }

        case NODE_ASSIGN: {

            int offset = getVarOffset(node->data.assign.var);

            if (offset == -1) {

                fprintf(stderr,
                        "\n❌ Code Generation Error: Variable '%s' not declared\n",
                        node->data.assign.var);

                exit(1);
            }

            int r = genExpr(node->data.assign.value);

            if (isVarGlobal(node->data.assign.var))
                fprintf(output,
                        "    sw $t%d, %d($sp)\n",
                        r, offset);
            else
                fprintf(output,
                        "    sw $t%d, %d($fp)\n",
                        r, offset);

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_DEC_ASSIGN: {

            int offset;

            if (strcmp(getCurrentScope(), "global") == 0) {
                offset =
                    getVarOffset(node->data.DecAssignNode.name);
            }
            else {

                offset =
                    addVar(node->data.DecAssignNode.name,
                           node->data.DecAssignNode.varType);

                if (offset == -1) {

                    fprintf(stderr,
                            "\n❌ Code Generation Error: Variable '%s' already declared\n",
                            node->data.DecAssignNode.name);

                    exit(1);
                }
            }

            fprintf(output,
                    "    # %s %s\n",
                    node->data.DecAssignNode.varType,
                    node->data.DecAssignNode.name);

            int r =
                genExpr(node->data.DecAssignNode.value);

            const char* scope = getCurrentScope();

            if (strcmp(scope, "global") == 0)
                fprintf(output,
                        "    sw $t%d, %d($sp)\n",
                        r, offset);
            else
                fprintf(output,
                        "    sw $t%d, %d($fp)\n",
                        r, offset);

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_PRINT: {

            ASTNode* expr = node->data.expr;

            /* Infer the type of the expression being printed */
            const char* varType = inferExprType(expr);

            int r = genExpr(expr);

            if (strcmp(varType, "float") == 0) {
                /* Move raw IEEE bits from integer reg into float reg, then print */
                fprintf(output, "    mtc1 $t%d, $f12\n", r);
                fprintf(output, "    li   $v0, 2\n");     /* print_float */
                fprintf(output, "    syscall\n");
            }
            else if (strcmp(varType, "char") == 0) {
                /* print_char — syscall 11, argument in $a0 */
                fprintf(output, "    move $a0, $t%d\n", r);
                fprintf(output, "    li   $v0, 11\n");    /* print_char */
                fprintf(output, "    syscall\n");
            }
            else if (strcmp(varType, "bool") == 0) {
                /* Branch to print "true" or "false" string */
                int lbl = printLabelCount++;
                fprintf(output, "    bne  $t%d, $zero, _print_true_%d\n", r, lbl);
                fprintf(output, "    la   $a0, _str_false\n");
                fprintf(output, "    j    _print_bool_done_%d\n", lbl);
                fprintf(output, "_print_true_%d:\n", lbl);
                fprintf(output, "    la   $a0, _str_true\n");
                fprintf(output, "_print_bool_done_%d:\n", lbl);
                fprintf(output, "    li   $v0, 4\n");     /* print_string */
                fprintf(output, "    syscall\n");
            }
            else {
                /* Default: int */
                fprintf(output, "    move $a0, $t%d\n", r);
                fprintf(output, "    li   $v0, 1\n");     /* print_int */
                fprintf(output, "    syscall\n");
            }

            /* Print newline after every value */
            fprintf(output, "    li   $v0, 11\n");
            fprintf(output, "    li   $a0, 10\n");
            fprintf(output, "    syscall\n");

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_FUNC_CALL: {

            int r = genExpr(node);

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_RETURN: {

            if (node->data.returnExpr) {

                int r = genExpr(node->data.returnExpr);

                fprintf(output,
                        "    move $v0, $t%d\n",
                        r);

                free_temp(r);
            }

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

/* ── RECURSIVE FUNCTION EMITTER ─────────────────────────────────────────── */
static void genAllFunctions(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        genAllFunctions(node->data.stmtlist.stmt);
        genAllFunctions(node->data.stmtlist.next);
        return;
    }
    if (node->type == NODE_FUNC_DECL) {
        setScope(node->data.funcDecl.name);
        genFuncDecl(node);
        setScope("global");
    }
}

/* ── RECURSIVE TOP-LEVEL STATEMENT EMITTER ──────────────────────────────── */
static void genTopLevelStmts(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        genTopLevelStmts(node->data.stmtlist.stmt);
        genTopLevelStmts(node->data.stmtlist.next);
        return;
    }
    if (node->type != NODE_FUNC_DECL)
        genStmt(node);
}

/* ── PRE-REGISTER GLOBALS ───────────────────────────────────────────────── */
static void preRegisterGlobals(ASTNode* node) {

    if (!node)
        return;

    if (node->type == NODE_STMT_LIST) {

        preRegisterGlobals(node->data.stmtlist.stmt);
        preRegisterGlobals(node->data.stmtlist.next);

        return;
    }

    if (node->type == NODE_DECL) {

        addVar(node->data.decl.name,
               node->data.decl.varType);
    }
    else if (node->type == NODE_DEC_ASSIGN) {

        addVar(node->data.DecAssignNode.name,
               node->data.DecAssignNode.varType);
    }
}

/* ── ENTRY POINT ────────────────────────────────────────────────────────── */
void generateMIPS(ASTNode* root, const char* filename) {

    output = fopen(filename, "w");

    if (!output) {

        fprintf(stderr,
                "\n❌ Cannot open output file '%s'\n\n",
                filename);

        exit(1);
    }

    initSymTab();

    /* Register globals BEFORE function generation */
    preRegisterGlobals(root);

    /* .data section — bool string literals */
    fprintf(output, ".data\n");
    fprintf(output, "_str_true:  .asciiz \"true\"\n");
    fprintf(output, "_str_false: .asciiz \"false\"\n\n");

    fprintf(output, ".text\n\n");

    genAllFunctions(root);

    fprintf(output, "\n.globl main\n");
    fprintf(output, "main:\n");

    fprintf(output,
            "    addi $sp, $sp, -400\n\n");

    genTopLevelStmts(root);

    fprintf(output, "\n    jal _Master\n");

    fprintf(output,
            "\n    addi $sp, $sp, 400\n");

    fprintf(output,
            "    li   $v0, 10\n");

    fprintf(output,
            "    syscall\n");

    fclose(output);
}