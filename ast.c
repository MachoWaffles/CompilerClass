/* AST IMPLEMENTATION
 * Constructors build nodes during parsing; printAST traces the tree for
 * educational output during Phase 2 of compilation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* createNum(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->data.num = value;
    return node;
}

ASTNode* createFloatLit(float value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT_LIT;
    node->data.fval = value;
    return node;
}

/* Char and bool share the `num` field because both are integral values. */
ASTNode* createCharLit(int asciiVal) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CHAR_LIT;
    node->data.num = asciiVal;
    return node;
}

ASTNode* createBoolLit(int val) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BOOL_LIT;
    node->data.num = val;  /* 1 = true, 0 = false */
    return node;
}

ASTNode* createVar(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->data.name = strdup(name);
    return node;
}

ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op    = op;
    node->data.binop.left  = left;
    node->data.binop.right = right;
    return node;
}

ASTNode* createDecl(char* type, char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.decl.name    = strdup(name);
    node->data.decl.varType = strdup(type);
    return node;
}

ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var   = strdup(var);
    node->data.assign.value = value;
    return node;
}

ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.expr = expr;
    return node;
}

ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = stmt1;
    node->data.stmtlist.next = stmt2;
    return node;
}

ASTNode* createDecAssignNode(char* type, char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DEC_ASSIGN;
    node->data.DecAssignNode.varType = strdup(type);
    node->data.DecAssignNode.name    = strdup(name);
    node->data.DecAssignNode.value   = value;
    return node;
}

/* A single parameter in a function signature, e.g. "int x" */
ASTNode* createParamDecl(char* type, char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM_DECL;
    node->data.param.paramType = strdup(type);
    node->data.param.name      = strdup(name);
    return node;
}

/* Full function declaration node.
 * params: linked list of NODE_PARAM_DECL (or NULL for no params)
 * body:   linked stmt_list (or NULL for empty body)
 */
ASTNode* createFuncDecl(char* name, char* returnType,
                         ASTNode* params, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECL;
    node->data.funcDecl.name       = strdup(name);
    node->data.funcDecl.returnType = strdup(returnType);
    node->data.funcDecl.params     = params;
    node->data.funcDecl.body       = body;
    return node;
}

/* Function call expression node.
 * args: expression linked list (reuses NODE_STMT_LIST), or NULL */
ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_CALL;
    node->data.funcCall.name = strdup(name);
    node->data.funcCall.args = args;
    return node;
}

/* Return statement node. expr is NULL for void return. */
ASTNode* createReturn(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.returnExpr = expr;
    return node;
}

ASTNode* createArrayDecl(char* type, char* name, int size) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->data.arrayDecl.type = strdup(type);
    node->data.arrayDecl.name = strdup(name);
    node->data.arrayDecl.size = size;
    return node;
}

ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.arrayAssign.name = strdup(name);
    node->data.arrayAssign.index = index;
    node->data.arrayAssign.value = value;
    return node;
}

ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.arrayAccess.name = strdup(name);
    node->data.arrayAccess.index = index;
    return node;
}

ASTNode* createWhile(ASTNode* condition, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->data.whileStmt.condition = condition;
    node->data.whileStmt.body = body;
    return node;
}

ASTNode* createFor(ASTNode* init, ASTNode* condition,
                   ASTNode* update, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->data.forStmt.init      = init;
    node->data.forStmt.condition = condition;
    node->data.forStmt.update    = update;
    node->data.forStmt.body      = body;
    return node;
}

/* ── PRINT AST ────────────────────────────────────────────────────────────── */
void printAST(ASTNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUM:
            printf("NUM: %d\n", node->data.num);
            break;
        case NODE_FLOAT_LIT:
            printf("FLOAT_LIT: %g\n", node->data.fval);
            break;
        case NODE_CHAR_LIT:
            printf("CHAR_LIT: '%c' (ASCII %d)\n", (char)node->data.num, node->data.num);
            break;
        case NODE_BOOL_LIT:
            printf("BOOL_LIT: %s\n", node->data.num ? "true" : "false");
            break;
        case NODE_VAR:
            printf("VAR: %s\n", node->data.name);
            break;
        case NODE_BINOP: {
            const char* opName;
            switch (node->data.binop.op) {
                case 'L': opName = "<="; break;
                case 'G': opName = ">="; break;
                case 'E': opName = "=="; break;
                case 'N': opName = "!="; break;
                default: {
                    static char buf[2] = {0, 0};
                    buf[0] = node->data.binop.op;
                    opName = buf;
                }
            }
            printf("BINOP: %s\n", opName);
            printAST(node->data.binop.left,  level + 1);
            printAST(node->data.binop.right, level + 1);
            break;
        }
        case NODE_DECL:
            printf("DECL: %s %s\n", node->data.decl.varType, node->data.decl.name);
            break;
        case NODE_ASSIGN:
            printf("ASSIGN: %s =\n", node->data.assign.var);
            printAST(node->data.assign.value, level + 1);
            break;
        case NODE_PRINT:
            printf("PRINT\n");
            printAST(node->data.expr, level + 1);
            break;
        case NODE_STMT_LIST:
            printAST(node->data.stmtlist.stmt, level);
            printAST(node->data.stmtlist.next, level);
            break;
        case NODE_DEC_ASSIGN:
            printf("DEC_ASSIGN: %s %s =\n",
                   node->data.DecAssignNode.varType,
                   node->data.DecAssignNode.name);
            printAST(node->data.DecAssignNode.value, level + 1);
            break;
        case NODE_PARAM_DECL:
            printf("PARAM: %s %s\n",
                   node->data.param.paramType,
                   node->data.param.name);
            break;
        case NODE_FUNC_DECL:
            printf("FUNC_DECL: %s returns %s\n",
                   node->data.funcDecl.name,
                   node->data.funcDecl.returnType);
            if (node->data.funcDecl.params) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("PARAMS:\n");
                printAST(node->data.funcDecl.params, level + 2);
            }
            if (node->data.funcDecl.body) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("BODY:\n");
                printAST(node->data.funcDecl.body, level + 2);
            }
            break;
        case NODE_FUNC_CALL:
            printf("FUNC_CALL: %s\n", node->data.funcCall.name);
            if (node->data.funcCall.args) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("ARGS:\n");
                printAST(node->data.funcCall.args, level + 2);
            }
            break;
        case NODE_RETURN:
            printf("RETURN\n");
            if (node->data.returnExpr) {
                printAST(node->data.returnExpr, level + 1);
            }
            break;
        case NODE_ARRAY_DECL:
            printf("ARRAY_DECL: %s %s[%d]\n",
                node->data.arrayDecl.type,
                node->data.arrayDecl.name,
                node->data.arrayDecl.size);
            break;

        case NODE_ARRAY_ASSIGN:
            printf("ARRAY_ASSIGN: %s[index] =\n",
                node->data.arrayAssign.name);

            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("INDEX:\n");
            printAST(node->data.arrayAssign.index, level + 2);

            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("VALUE:\n");
            printAST(node->data.arrayAssign.value, level + 2);
            break;

        case NODE_ARRAY_ACCESS:
            printf("ARRAY_ACCESS: %s[index]\n",
                node->data.arrayAccess.name);
            printAST(node->data.arrayAccess.index, level + 1);
            break;

        case NODE_WHILE:
            printf("WHILE\n");
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("CONDITION:\n");
            printAST(node->data.whileStmt.condition, level + 2);    

            for (int i = 0; i < level + 1; i++) printf("  ");   
            printf("BODY:\n");
            printAST(node->data.whileStmt.body, level + 2);
            break;

        case NODE_FOR:
            printf("FOR\n");
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("INIT:\n");
            printAST(node->data.forStmt.init, level + 2);

            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("CONDITION:\n");
            printAST(node->data.forStmt.condition, level + 2);

            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("UPDATE:\n");
            printAST(node->data.forStmt.update, level + 2);

            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("BODY:\n");
            printAST(node->data.forStmt.body, level + 2);
            break;

        case NODE_STRUCT_DECL:
            printf("STRUCT_DECL: %s\n", node->data.structDecl.name);
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("FIELDS:\n");
            printAST(node->data.structDecl.fields, level + 2);
            break;

        case NODE_STRUCT_VAR:
            printf("STRUCT_VAR: %s %s\n",
                node->data.structVar.structType,
                node->data.structVar.varName);
            break;

        case NODE_FIELD_ACCESS:
            printf("FIELD_ACCESS: %s.%s\n",
                node->data.fieldAccess.varName,
                node->data.fieldAccess.fieldName);
            break;

        case NODE_FIELD_ASSIGN:
            printf("FIELD_ASSIGN: %s.%s =\n",
                node->data.fieldAssign.varName,
                node->data.fieldAssign.fieldName);
            printAST(node->data.fieldAssign.value, level + 1);
            break;
    }
}

/* ── STRUCT CONSTRUCTORS ─────────────────────────────────────────────────── */

ASTNode* createStructDecl(char* name, ASTNode* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_DECL;
    node->data.structDecl.name   = strdup(name);
    node->data.structDecl.fields = fields;
    return node;
}

ASTNode* createStructVar(char* structType, char* varName) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_VAR;
    node->data.structVar.structType = strdup(structType);
    node->data.structVar.varName    = strdup(varName);
    return node;
}

ASTNode* createFieldAccess(char* varName, char* fieldName) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FIELD_ACCESS;
    node->data.fieldAccess.varName   = strdup(varName);
    node->data.fieldAccess.fieldName = strdup(fieldName);
    return node;
}

ASTNode* createFieldAssign(char* varName, char* fieldName, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FIELD_ASSIGN;
    node->data.fieldAssign.varName   = strdup(varName);
    node->data.fieldAssign.fieldName = strdup(fieldName);
    node->data.fieldAssign.value     = value;
    return node;
}
