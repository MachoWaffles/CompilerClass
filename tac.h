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
    TAC_ADD,      /* result = arg1 + arg2 */
    TAC_ASSIGN,   /* result = arg1 */
    TAC_PRINT,    /* print(arg1) */
    TAC_DECL,     /* declare variable 'result' of type arg1 */

    /* TODO: TAC_SUB — result = arg1 - arg2
     *   Requires: grammar rule 'expr - expr', MIPS 'sub' instruction.
     *   When added, handle in generateTACExpr, optimizeTAC, printTAC,
     *   genExpr (codegen.c). */

    /* TODO: TAC_MUL — result = arg1 * arg2
     *   Requires: grammar rule 'expr * expr', MIPS 'mul' instruction. */

    /* TODO: TAC_DIV — result = arg1 / arg2
     *   Requires: grammar rule 'expr / expr', MIPS 'div'+'mflo',
     *   and a semantic division-by-zero check (already stubbed in semantic.c). */

    /* TODO: TAC_ARRAY_DECL — declare array: result[arg1] of type arg2
     *   Requires: array grammar rule, updated symbol table with size field,
     *   and a base address (label) in the MIPS .data section. */

    /* TODO: TAC_ARRAY_STORE — result[arg1] = arg2 (array write)
     *   Requires: array access grammar rule, base address + offset arithmetic. */

    /* TODO: TAC_ARRAY_LOAD — result = arg1[arg2] (array read) */

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
