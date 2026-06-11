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
static int loopLabelCount  = 0;
static int inForInit       = 0;  /* suppresses duplicate-decl error in for init */

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

            if (isVarGlobal(node->data.name)) {
                fprintf(output, "    la  $t%d, _g_%s\n", r, node->data.name);
                fprintf(output, "    lw  $t%d, 0($t%d)\n", r, r);
            } else
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
                        fprintf(output, "    mfc1 $t%d, $f0\n", lR);
                        break;
                    case '-':
                        fprintf(output, "    sub.s $f0, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f0\n", lR);
                        break;
                    case '*':
                        fprintf(output, "    mul.s $f0, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f0\n", lR);
                        break;
                    case '/':
                        fprintf(output, "    div.s $f0, $f0, $f2\n");
                        fprintf(output, "    mfc1 $t%d, $f0\n", lR);
                        break;

                    /* ── Float comparison operators ──
                     * MIPS FPU sets the condition flag with c.xx.s,
                     * then we materialise 0/1 in an integer register.
                     * NO mfc1 here — $tN already holds the 0/1 result. */
                    case '<':
                        fprintf(output, "    c.lt.s $f0, $f2\n");
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;
                    case '>':
                        fprintf(output, "    c.lt.s $f2, $f0\n");
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;
                    case 'L': /* <= */
                        fprintf(output, "    c.le.s $f0, $f2\n");
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;
                    case 'G': /* >= */
                        fprintf(output, "    c.le.s $f2, $f0\n");
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;
                    case 'E': /* == */
                        fprintf(output, "    c.eq.s $f0, $f2\n");
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;
                    case 'N': /* != */
                        fprintf(output, "    c.eq.s $f0, $f2\n");
                        fprintf(output, "    li $t%d, 1\n",  lR);
                        fprintf(output, "    bc1f _fcmp_end_%d\n", printLabelCount);
                        fprintf(output, "    li $t%d, 0\n",  lR);
                        fprintf(output, "_fcmp_end_%d:\n",   printLabelCount++);
                        break;

                    default:
                        fprintf(stderr,
                                "\n❌ Unsupported binary operator '%c'\n",
                                node->data.binop.op);
                        exit(1);
                }
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

                    /* ── Comparison operators — result is 0 (false) or 1 (true) ── */
                    case '<':
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", lR, lR, rR);
                        break;
                    case '>':
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", lR, rR, lR);
                        break;
                    case 'L': /* <= */
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", lR, rR, lR);
                        fprintf(output, "    xori $t%d, $t%d, 1\n",   lR, lR);
                        break;
                    case 'G': /* >= */
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", lR, lR, rR);
                        fprintf(output, "    xori $t%d, $t%d, 1\n",   lR, lR);
                        break;
                    case 'E': /* == */
                        fprintf(output, "    xor  $t%d, $t%d, $t%d\n", lR, lR, rR);
                        fprintf(output, "    sltiu $t%d, $t%d, 1\n",   lR, lR);
                        break;
                    case 'N': /* != */
                        fprintf(output, "    xor  $t%d, $t%d, $t%d\n", lR, lR, rR);
                        fprintf(output, "    sltu $t%d, $zero, $t%d\n", lR, lR);
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

        case NODE_ARRAY_ACCESS: {
            const char* arrName = node->data.arrayAccess.name;
            int base = getVarOffset((char*)arrName);
            if (base == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Array '%s' not found\n",
                        arrName);
                exit(1);
            }

            int idxR = genExpr(node->data.arrayAccess.index);
            fprintf(output, "    sll $t%d, $t%d, 2\n", idxR, idxR);

            int addrR = getNextTemp();
            if (isVarGlobal(arrName))
                fprintf(output, "    la  $t%d, _g_%s\n", addrR, arrName);
            else
                fprintf(output, "    addi $t%d, $fp, %d\n", addrR, base);

            fprintf(output, "    add  $t%d, $t%d, $t%d\n", addrR, addrR, idxR);
            free_temp(idxR);
            fprintf(output, "    lw   $t%d, 0($t%d)\n", addrR, addrR);
            return addrR;
        }

        case NODE_FIELD_ACCESS: {
            /* address = struct_base_offset + field_index * 4 */
            const char* vname = node->data.fieldAccess.varName;
            const char* fname = node->data.fieldAccess.fieldName;
            int base = getVarOffset((char*)vname);
            if (base == -1) {
                fprintf(stderr,
                    "\n❌ Code Generation Error: Struct variable '%s' not found\n", vname);
                exit(1);
            }
            const char* vtype = getVarType((char*)vname);
            int fieldOff = getStructFieldOffset((char*)vtype, (char*)fname);
            if (fieldOff == -1) {
                fprintf(stderr,
                    "\n❌ Code Generation Error: Field '%s' not in struct '%s'\n",
                    fname, vtype);
                exit(1);
            }
            int r = getNextTemp();
            fprintf(output, "    # field access %s.%s\n", vname, fname);
            if (isVarGlobal(vname)) {
                fprintf(output, "    la  $t%d, _g_%s\n", r, vname);
                fprintf(output, "    lw  $t%d, %d($t%d)\n", r, fieldOff, r);
            } else
                fprintf(output, "    lw   $t%d, %d($fp)\n", r, base + fieldOff);
            return r;
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

    /* Arrays need size slots, not just 1 */
    if (node->type == NODE_ARRAY_DECL)
        return node->data.arrayDecl.size;

    /* Struct vars occupy one word per field */
    if (node->type == NODE_STRUCT_VAR)
        return getStructFieldCount(node->data.structVar.structType);

    if (node->type == NODE_STMT_LIST)
        return countLocals(node->data.stmtlist.stmt)
             + countLocals(node->data.stmtlist.next);

    /* A for-loop init may declare a new variable (int i = 0) */
    if (node->type == NODE_FOR)
        return countLocals(node->data.forStmt.init)
             + countLocals(node->data.forStmt.body);

    if (node->type == NODE_WHILE)
        return countLocals(node->data.whileStmt.body);

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

            if (isVarGlobal(node->data.assign.var)) {
                int addrR = getNextTemp();
                fprintf(output, "    la  $t%d, _g_%s\n", addrR, node->data.assign.var);
                fprintf(output, "    sw  $t%d, 0($t%d)\n", r, addrR);
                free_temp(addrR);
            } else
                fprintf(output, "    sw $t%d, %d($fp)\n", r, offset);

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_DEC_ASSIGN: {

            int offset;

            if (strcmp(getCurrentScope(), "global") == 0) {
                offset = getVarOffset(node->data.DecAssignNode.name);
            }
            else {
                offset = inForInit
                    ? addOrReuseVar(node->data.DecAssignNode.name,
                                    node->data.DecAssignNode.varType)
                    : addVar(node->data.DecAssignNode.name,
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

            if (strcmp(scope, "global") == 0) {
                int addrR = getNextTemp();
                fprintf(output, "    la  $t%d, _g_%s\n", addrR, node->data.DecAssignNode.name);
                fprintf(output, "    sw  $t%d, 0($t%d)\n", r, addrR);
                free_temp(addrR);
            } else
                fprintf(output,
                        "    sw $t%d, %d($fp)\n",
                        r, offset);

            free_temp(r);
            resetTemps();

            break;
        }

        case NODE_ARRAY_DECL: {
            /* Register the array in the symbol table, reserving size*4 bytes.
             * In global scope this was already done by preRegisterGlobals;
             * in a function scope we register it now during codegen. */
            if (strcmp(getCurrentScope(), "global") != 0) {
                int offset = addArray(node->data.arrayDecl.name,
                                      node->data.arrayDecl.type,
                                      node->data.arrayDecl.size);
                fprintf(output,
                        "    # array %s %s[%d] at fp+%d\n",
                        node->data.arrayDecl.type,
                        node->data.arrayDecl.name,
                        node->data.arrayDecl.size,
                        offset);
            }
            break;
        }

        case NODE_ARRAY_ASSIGN: {
            /* Evaluate RHS FIRST so any jal inside it doesn't clobber
             * the address registers we compute afterward. */
            const char* arrName = node->data.arrayAssign.name;
            int base = getVarOffset((char*)arrName);
            if (base == -1) {
                fprintf(stderr,
                        "\n❌ Code Generation Error: Array '%s' not declared\n",
                        arrName);
                exit(1);
            }

            /* 1. Evaluate the value to store */
            int valR = genExpr(node->data.arrayAssign.value);

            /* 2. Evaluate the index (no more jal possible after this) */
            int idxR = genExpr(node->data.arrayAssign.index);
            fprintf(output, "    sll $t%d, $t%d, 2\n", idxR, idxR);

            /* 3. Compute address */
            int addrR = getNextTemp();
            if (isVarGlobal(arrName))
                fprintf(output, "    la  $t%d, _g_%s\n", addrR, arrName);
            else
                fprintf(output, "    addi $t%d, $fp, %d\n", addrR, base);

            fprintf(output, "    add  $t%d, $t%d, $t%d\n", addrR, addrR, idxR);
            free_temp(idxR);

            /* 4. Store */
            fprintf(output, "    sw   $t%d, 0($t%d)\n", valR, addrR);

            free_temp(valR);
            free_temp(addrR);
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

        case NODE_WHILE: {
            int lbl = loopLabelCount++;
            fprintf(output, "\n_while_start_%d:\n", lbl);

            /* Evaluate condition; branch past body if false (== 0) */
            int condR = genExpr(node->data.whileStmt.condition);
            fprintf(output, "    beq $t%d, $zero, _while_end_%d\n", condR, lbl);
            free_temp(condR);
            resetTemps();

            genStmt(node->data.whileStmt.body);

            fprintf(output, "    j _while_start_%d\n", lbl);
            fprintf(output, "_while_end_%d:\n\n", lbl);

            break;
        }

        case NODE_FOR: {
            int lbl = loopLabelCount++;

            /* Init — a DEC_ASSIGN (int i = 0) or ASSIGN (i = 0) */
            inForInit = 1;
            genStmt(node->data.forStmt.init);
            inForInit = 0;
            resetTemps();

            fprintf(output, "\n_for_start_%d:\n", lbl);

            /* Condition — branch past body if false */
            int condR = genExpr(node->data.forStmt.condition);
            fprintf(output, "    beq $t%d, $zero, _for_end_%d\n", condR, lbl);
            free_temp(condR);
            resetTemps();

            /* Body */
            genStmt(node->data.forStmt.body);

            /* Update — always an ASSIGN (i = i + 1, or desugared i++) */
            genStmt(node->data.forStmt.update);
            resetTemps();

            fprintf(output, "    j _for_start_%d\n", lbl);
            fprintf(output, "_for_end_%d:\n\n", lbl);

            break;
        }

        case NODE_IF: {
            int lbl = loopLabelCount++;

            /* Evaluate condition; branch past then body if false (== 0) */
            int condR = genExpr(node->data.ifStmt.condition);
            fprintf(output, "    beq $t%d, $zero, _if_end_%d\n", condR, lbl);
            free_temp(condR);
            resetTemps();

            genStmt(node->data.ifStmt.thenBody);

            if (node->data.ifStmt.elseBody) {
                fprintf(output, "    j _if_else_%d\n", lbl);
                fprintf(output, "_if_end_%d:\n\n", lbl);
                genStmt(node->data.ifStmt.elseBody);
                fprintf(output, "_if_else_%d:\n\n", lbl);
            } else {
                fprintf(output, "_if_end_%d:\n\n", lbl);
            }

            break;
        }

        case NODE_ELSE: {
            genStmt(node->data.elseBody);
            break;
        }

        case NODE_SWITCH: {
            /* Implementation for switch statement code generation */
            break;
        }
        
        /* These node types are expression nodes handled by genExpr, or
         * structural nodes (PARAM_DECL, FUNC_DECL) handled elsewhere.
         * They should never arrive at genStmt; list them explicitly to
         * satisfy -Wswitch and document the intentional no-op. */
        case NODE_NUM:
        case NODE_VAR:
        case NODE_BINOP:
        case NODE_FLOAT_LIT:
        case NODE_CHAR_LIT:
        case NODE_BOOL_LIT:
        case NODE_ARRAY_ACCESS:
        case NODE_FIELD_ACCESS:   /* expression node — handled by genExpr */
        case NODE_PARAM_DECL:
        case NODE_FUNC_DECL:
            break;

        case NODE_STRUCT_DECL:
            /* Pure type definition — no code emitted; already registered by
             * preRegisterGlobals / semantic analysis. */
            break;

        case NODE_STRUCT_VAR: {
            /* Declare a struct variable in local scope (global handled by
             * preRegisterGlobals). */
            if (strcmp(getCurrentScope(), "global") != 0) {
                addStructVar(node->data.structVar.varName,
                             node->data.structVar.structType);
                fprintf(output, "    # struct %s %s (local)\n",
                        node->data.structVar.structType,
                        node->data.structVar.varName);
            }
            break;
        }

        case NODE_FIELD_ASSIGN: {
            /* Evaluate RHS, store into struct_base + field_offset */
            const char* vname = node->data.fieldAssign.varName;
            const char* fname = node->data.fieldAssign.fieldName;
            int base = getVarOffset((char*)vname);
            if (base == -1) {
                fprintf(stderr,
                    "\n❌ Code Generation Error: Struct variable '%s' not found\n",
                    vname);
                exit(1);
            }
            const char* vtype = getVarType((char*)vname);
            int fieldOff = getStructFieldOffset((char*)vtype, (char*)fname);
            if (fieldOff == -1) {
                fprintf(stderr,
                    "\n❌ Code Generation Error: Field '%s' not in struct '%s'\n",
                    fname, vtype);
                exit(1);
            }
            int valR = genExpr(node->data.fieldAssign.value);
            fprintf(output, "    # field assign %s.%s\n", vname, fname);
            if (isVarGlobal(vname)) {
                int addrR = getNextTemp();
                fprintf(output, "    la  $t%d, _g_%s\n", addrR, vname);
                fprintf(output, "    sw  $t%d, %d($t%d)\n", valR, fieldOff, addrR);
                free_temp(addrR);
            } else
                fprintf(output, "    sw   $t%d, %d($fp)\n", valR, base + fieldOff);
            free_temp(valR);
            resetTemps();
            break;
        }

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
        addVar(node->data.decl.name, node->data.decl.varType);
    }
    else if (node->type == NODE_DEC_ASSIGN) {
        addVar(node->data.DecAssignNode.name, node->data.DecAssignNode.varType);
    }
    else if (node->type == NODE_ARRAY_DECL) {
        addArray(node->data.arrayDecl.name,
                 node->data.arrayDecl.type,
                 node->data.arrayDecl.size);
    }
    else if (node->type == NODE_STRUCT_DECL) {
        /* Register the struct type definition so subsequent NODE_STRUCT_VAR
         * nodes in global scope can call addStructVar. */
        char* sname = node->data.structDecl.name;
        addStructDef(sname);
        ASTNode* flist = node->data.structDecl.fields;
        while (flist) {
            ASTNode* fnode = NULL;
            if (flist->type == NODE_DECL) {
                fnode = flist; flist = NULL;
            } else if (flist->type == NODE_STMT_LIST) {
                fnode = flist->data.stmtlist.stmt;
                flist = flist->data.stmtlist.next;
            } else { break; }
            if (fnode && fnode->type == NODE_DECL)
                addStructField(sname, fnode->data.decl.varType, fnode->data.decl.name);
        }
    }
    else if (node->type == NODE_STRUCT_VAR) {
        addStructVar(node->data.structVar.varName,
                     node->data.structVar.structType);
    }
}

/* ── EMIT GLOBAL DATA LABELS ─────────────────────────────────────────────── */
/* Walk the top-level AST and emit a .word/.space label for every global
 * variable, array, or struct variable. Scalar globals: _g_name: .word 0
 * Arrays / struct vars: _g_name: .space N  (N = size * 4 bytes)          */
static void emitGlobalData(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        emitGlobalData(node->data.stmtlist.stmt);
        emitGlobalData(node->data.stmtlist.next);
        return;
    }
    if (node->type == NODE_FUNC_DECL) return;  /* skip functions */

    if (node->type == NODE_DECL || node->type == NODE_DEC_ASSIGN) {
        const char* name = (node->type == NODE_DECL)
            ? node->data.decl.name
            : node->data.DecAssignNode.name;
        fprintf(output, "_g_%s: .word 0\n", name);
    }
    else if (node->type == NODE_ARRAY_DECL) {
        fprintf(output, "_g_%s: .space %d\n",
                node->data.arrayDecl.name,
                node->data.arrayDecl.size * 4);
    }
    else if (node->type == NODE_STRUCT_DECL) {
        /* type definition only — no storage */
    }
    else if (node->type == NODE_STRUCT_VAR) {
        int sz = getStructSize(node->data.structVar.structType);
        fprintf(output, "_g_%s: .space %d\n",
                node->data.structVar.varName, sz > 0 ? sz : 4);
    }
}

/* ── ENTRY POINT ────────────────────────────────────────────────────────── */
void generateMIPS(ASTNode* root, const char* filename) {

    output = fopen(filename, "w");

    if (!output) {
        fprintf(stderr, "\n❌ Cannot open output file '%s'\n\n", filename);
        exit(1);
    }

    initSymTab();
    initStructTab();

    /* Register globals in symtab (offsets not used for scalars anymore,
     * but arrays still need offset tracking within their label block). */
    preRegisterGlobals(root);

    /* ── .data section ──────────────────────────────────────────────────── */
    fprintf(output, ".data\n");
    fprintf(output, "_str_true:  .asciiz \"true\"\n");
    fprintf(output, "_str_false: .asciiz \"false\"\n");

    /* Emit a label + storage for every global variable/array/struct */
    emitGlobalData(root);

    fprintf(output, "\n.text\n\n");

    genAllFunctions(root);

    /* ── main: initialise globals then call Master ──────────────────────── */
    fprintf(output, "\n.globl main\n");
    fprintf(output, "main:\n");
    fprintf(output, "    addi $sp, $sp, -8\n");
    fprintf(output, "    sw   $ra, 4($sp)\n\n");

    genTopLevelStmts(root);   /* runs initialisers like  int step = 10  */

    fprintf(output, "\n    jal _Master\n\n");
    fprintf(output, "    lw   $ra, 4($sp)\n");
    fprintf(output, "    addi $sp, $sp, 8\n");
    fprintf(output, "    li   $v0, 10\n");
    fprintf(output, "    syscall\n");

    fclose(output);
}