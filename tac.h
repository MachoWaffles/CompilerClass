#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and MIPS assembly.
 * Each instruction has at most 3 operands: result = arg1 op arg2.
 * Extended for Project 3 with function-related operations and stubs for
 * arithmetic operators not yet wired into the grammar.
 *
 * Naming convention for temporaries (class notes):
 *   - Expression temps: t0, t1, t2, ...
 *   - Parameter passing: P0, P1, P2, ... (before a function call)
 */

typedef enum {
    /* Existing arithmetic */
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,      /* result = arg1 op arg2 */
    TAC_ASSIGN,   /* result = arg1 */
    TAC_PRINT,    /* print(arg1) */
    TAC_DECL,     /* declare variable 'result' of type arg1 */

    TAC_LABEL,
    TAC_GOTO,
    TAC_IF_FALSE,

    /* Comparison operators — result is 1 (true) or 0 (false) */
    TAC_LT,       /* result = arg1 <  arg2  (parser op '<') */
    TAC_GT,       /* result = arg1 >  arg2  (parser op '>') */
    TAC_LE,       /* result = arg1 <= arg2  (parser op 'L') */
    TAC_GE,       /* result = arg1 >= arg2  (parser op 'G') */
    TAC_EQ,       /* result = arg1 == arg2  (parser op 'E') */
    TAC_NE,       /* result = arg1 != arg2  (parser op 'N') */

    /* Function-related operations */
    TAC_FUNC_BEGIN, /* Marks the start of a function: result = function name label */
    TAC_FUNC_END,   /* Marks the end of a function body (before jr $ra) */
    TAC_PARAM,      /* Pass argument to function: arg1 = value for P<n> slot */
    TAC_CALL,       /* Call function: result = call arg1 (result holds return value temp) */
    TAC_RETURN      /* Return from function: arg1 = return value (NULL for void) */
} TACOp;

typedef struct TACInstr {
    TACOp  op;
    char*  arg1;
    char*  arg2;
    char*  result;
    struct TACInstr* next;
} TACInstr;

typedef struct {
    TACInstr* head;
    TACInstr* tail;
    int       tempCount;
    int       paramCount;  /* resets to 0 at each function call site */
} TACList;

/* Generation */
void    initTAC();
char*   newTemp();
char*   newParam();                                             /* P0, P1, P2, ... */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void    appendTAC(TACInstr* instr);
void    generateTAC(ASTNode* node);
char*   generateTACExpr(ASTNode* node);

/* Output */
void    printTAC();
void    optimizeTAC();
void    printOptimizedTAC();
void    saveTACToFile(const char* filename);
void    saveOptimizedTACToFile(const char* filename);

#endif