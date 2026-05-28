#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * Intermediate representation of program structure built during parsing.
 * Extended for Project 3 to include:
 *   - Float, char, and bool literal nodes
 *   - Function declaration node (name, return type, params, body)
 *   - Function call node (name, argument list)
 *   - Parameter declaration node (type + name, used in param lists)
 *   - Return statement node
 */

typedef enum {
    /* Existing nodes */
    NODE_NUM,         /* Integer literal, e.g. 42 */
    NODE_VAR,         /* Variable reference, e.g. x */
    NODE_BINOP,       /* Binary operation, e.g. x + y */
    NODE_DECL,        /* Variable declaration, e.g. int x; */
    NODE_ASSIGN,      /* Assignment, e.g. x = 10; */
    NODE_PRINT,       /* print(expr); */
    NODE_STMT_LIST,   /* Linked list of statements */
    NODE_DEC_ASSIGN,  /* Declaration + assignment, e.g. int x = 5; */

    /* New nodes for Project 3 */
    NODE_FLOAT_LIT,   /* Float literal, e.g. 3.14 */
    NODE_CHAR_LIT,    /* Char literal, e.g. 'a' — stored as ASCII int */
    NODE_BOOL_LIT,    /* Bool literal: true (1) or false (0) */
    NODE_PARAM_DECL,  /* One parameter declaration in a function signature */
    NODE_FUNC_DECL,   /* Function declaration */
    NODE_FUNC_CALL,   /* Function call in expression position */
    NODE_RETURN       /* return expr; or return; */

    /* TODO: NODE_ARRAY_DECL  — e.g. int arr[10]; */
    /* TODO: NODE_ARRAY_ACCESS — e.g. arr[i] */
} NodeType;

typedef struct ASTNode {
    NodeType type;

    union {
        /* NODE_NUM: integer value */
        int num;

        /* NODE_FLOAT_LIT: float value */
        float fval;

        /* NODE_CHAR_LIT: ASCII value of the character */
        /* NODE_BOOL_LIT: 0 (false) or 1 (true) */
        /* Both reuse num since they are integral values */

        /* NODE_VAR: variable name */
        char* name;

        /* NODE_DECL */
        struct {
            char* name;
            char* varType;
        } decl;

        /* NODE_BINOP */
        struct {
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        /* NODE_ASSIGN */
        struct {
            char* var;
            struct ASTNode* value;
        } assign;

        /* NODE_PRINT — expression to print */
        struct ASTNode* expr;

        /* NODE_STMT_LIST — also used for param/arg lists */
        struct {
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmtlist;

        /* NODE_DEC_ASSIGN */
        struct {
            char* varType;
            char* name;
            struct ASTNode* value;
        } DecAssignNode;

        /* NODE_PARAM_DECL — one parameter in a function signature */
        struct {
            char* paramType;
            char* name;
        } param;

        /* NODE_FUNC_DECL */
        struct {
            char* name;          /* function name */
            char* returnType;    /* declared return type string */
            struct ASTNode* params; /* linked NODE_PARAM_DECL list (or NULL) */
            struct ASTNode* body;   /* stmt_list (or NULL for empty body) */
        } funcDecl;

        /* NODE_FUNC_CALL */
        struct {
            char* name;          /* function being called */
            struct ASTNode* args; /* linked expression list (or NULL) */
        } funcCall;

        /* NODE_RETURN */
        struct ASTNode* returnExpr; /* NULL for void return */

        /* TODO: NODE_ARRAY_DECL — would need: type, name, size */
        /* TODO: NODE_ARRAY_ACCESS — would need: name, index expr */
    } data;
} ASTNode;

/* ── CONSTRUCTORS ────────────────────────────────────────────────────────── */
ASTNode* createNum(int value);
ASTNode* createFloatLit(float value);
ASTNode* createCharLit(int asciiVal);
ASTNode* createBoolLit(int val);          /* val = 1 (true) or 0 (false) */
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createDecl(char* type, char* name);
ASTNode* createAssign(char* var, ASTNode* value);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);
ASTNode* createDecAssignNode(char* type, char* name, ASTNode* value);
ASTNode* createParamDecl(char* type, char* name);
ASTNode* createFuncDecl(char* name, char* returnType, ASTNode* params, ASTNode* body);
ASTNode* createFuncCall(char* name, ASTNode* args);
ASTNode* createReturn(ASTNode* expr);     /* expr may be NULL for void return */

/* ── DISPLAY ─────────────────────────────────────────────────────────────── */
void printAST(ASTNode* node, int level);

#endif
