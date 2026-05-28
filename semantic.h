#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* SEMANTIC ANALYZER
 * Phase 3 of compilation — validates the AST for correctness beyond syntax.
 * Extended for Project 3 to check:
 *   - Functions declared before being called
 *   - Argument count matches declared parameter count
 *   - Argument types are compatible with parameter types
 *   - Return type of return statement matches the enclosing function's type
 *   - Type compatibility on variable assignment (widening allowed: int → float)
 *   - Mandatory Master() entry point is declared somewhere in the program
 */

extern int semanticErrors;

void  initSemantic();
int   analyzeProgram(ASTNode* root);    /* returns 1 if clean, 0 if errors */
void  analyzeStmt(ASTNode* node);
void  analyzeExpr(ASTNode* node);

/* Returns the inferred type string of an expression node ("int", "float",
 * "char", "bool", "nothing", or "unknown" if it cannot be determined). */
const char* getExprType(ASTNode* node);

void  reportSemanticError(const char* msg);

#endif
