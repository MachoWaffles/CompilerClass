%{
/* SYNTAX ANALYZER (PARSER)
 * Phase 2 of compilation — checks grammar and builds the AST.
 * Extended for Project 3:
 *   - type non-terminal covers int, float, char, bool, nothing
 *   - Function declarations and calls
 *   - Parameter lists and argument lists
 *   - return statement
 *   - New literal types (float, char, bool)
 *   - Operator precedence stubs for -, *, / (grammar rules TODO)
 *   - Array declaration grammar stub (TODO)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
extern char* yytext;

void yyerror(const char* s);
ASTNode* root = NULL;
%}

/* ── SEMANTIC VALUE UNION ───────────────────────────────────────────────── */
%union {
    int   num;          /* integer and char literals, bool (0/1) */
    float fval;         /* float literals */
    char* str;          /* identifiers and type strings */
    struct ASTNode* node;
}

/* ── TOKEN DECLARATIONS ─────────────────────────────────────────────────── */
%token <num> NUM          /* integer literal */
%token <fval> FLOAT_LIT   /* float literal, e.g. 3.14 */
%token <num> CHAR_LIT     /* char literal, e.g. 'a' — stored as ASCII int */
%token <num> TRUE_LIT     /* true — stored as 1 */
%token <num> FALSE_LIT    /* false — stored as 0 */
%token <str> ID           /* identifier */

/* Type keywords */
%token INT FLOAT CHAR_TYPE BOOL_TYPE NOTHING

/* Function keywords */
%token FUNCTION RETURNS RETURN_KW

/* Other keywords */
%token PRINT

%token WHILE

/* ── NON-TERMINAL TYPES ─────────────────────────────────────────────────── */
%type <node> program top_level_list top_level_item
%type <node> stmt_list stmt decl assign expr print_stmt decAssign
%type <node> func_decl param_decl_list param_decl arg_list return_stmt call_stmt
%type <node> array_decl array_assign
%type <str>  type
%type <node> while_stmt

/* ── OPERATOR PRECEDENCE ────────────────────────────────────────────────── */
%left '+' '-'    /* addition and subtraction (- grammar rule TODO) */
%left '*' '/'    /* multiplication and division (grammar rules TODO) */

%%

/* ── TOP-LEVEL PROGRAM ──────────────────────────────────────────────────── */
program:
    top_level_list  { root = $1; }
    ;

/* Top-level items: global statements or function declarations */
top_level_list:
    top_level_item                      { $$ = $1; }
    | top_level_list top_level_item     { $$ = createStmtList($1, $2); }
    ;

top_level_item:
    stmt        { $$ = $1; }
    | func_decl { $$ = $1; }
    ;

/* ── STATEMENT LIST (used inside function bodies) ────────────────────────── */
stmt_list:
    stmt                    { $$ = $1; }
    | stmt_list stmt        { $$ = createStmtList($1, $2); }
    ;

/* ── STATEMENT TYPES ────────────────────────────────────────────────────── */
stmt:
    decl
    | assign
    | decAssign
    | print_stmt
    | return_stmt
    | call_stmt
    | array_decl
    | array_assign
    | while_stmt
    ;

/* ── TYPE NON-TERMINAL ───────────────────────────────────────────────────── */
/* Returns a static string — callers that store it must strdup it themselves */
type:
    INT       { $$ = "int"; }
    | FLOAT   { $$ = "float"; }
    | CHAR_TYPE { $$ = "char"; }
    | BOOL_TYPE { $$ = "bool"; }
    | NOTHING { $$ = "nothing"; }
    ;

/* ── VARIABLE DECLARATION ────────────────────────────────────────────────── */
decl:
    type ID ';' {
        $$ = createDecl($1, $2);
        free($2);
    }
    | type ID error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid syntax after '%s %s'\n", $1, $2);
        fprintf(stderr, "   💡 Suggestions:\n");
        fprintf(stderr, "      • Declaration only:            '%s %s;'\n", $1, $2);
        fprintf(stderr, "      • Declaration with assignment: '%s %s = <expression>;'\n\n", $1, $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    | type error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected '<type> <identifier>;'\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── DECLARATION WITH ASSIGNMENT ─────────────────────────────────────────── */
decAssign:
    type ID '=' expr ';' {
        $$ = createDecAssignNode($1, $2, $4);
        free($2);
    }
    | type ID '=' expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after declaration-assignment for '%s'\n", $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    | type ID '=' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing expression after '='\n");
        free($2);
        $$ = NULL;
        yyerrok;
    }
    ;
/* ── ARRAY DECLARATION ───────────────────────────────────────────────────── */
array_decl:
    type ID '[' NUM ']' ';' {
        $$ = createArrayDecl($1, $2, $4);
        free($2);
    }
    | type ID '[' NUM ']' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array declaration for '%s'\n", $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── ARRAY ASSIGNMENT ────────────────────────────────────────────────────── */
array_assign:
    ID '[' expr ']' '=' expr ';' {
        $$ = createArrayAssign($1, $3, $6);
        free($1);
    }
    | ID '[' expr ']' '=' expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array assignment for '%s'\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── ASSIGNMENT ──────────────────────────────────────────────────────────── */
assign:
    ID '=' expr ';' {
        $$ = createAssign($1, $3);
        free($1);
    }
    | ID '=' expr error {
        if (yychar == '=') {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Chained assignment is not supported: '%s = ... = ...'\n", $1);
            fprintf(stderr, "   💡 Suggestion: Use two separate statements\n\n");
        } else {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Missing semicolon after assignment to '%s'\n", $1);
            fprintf(stderr, "   💡 Suggestion: Add ';' after the expression\n\n");
        }
        free($1);
        $$ = NULL;
        yyerrok;
    }
    | ID '=' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment to '%s'\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    | ID error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement for '%s'\n", $1);
        free($1);
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── RETURN STATEMENT ────────────────────────────────────────────────────── */
return_stmt:
    RETURN_KW expr ';' {
        $$ = createReturn($2);
    }
    | RETURN_KW ';' {
        /* void return — no expression */
        $$ = createReturn(NULL);
    }
    | RETURN_KW expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after return statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the return expression\n\n");
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── CALL STATEMENT ────────────────────────────────────────────────────── */
call_stmt:
    ID '(' arg_list ')' ';' {
        $$ = createFuncCall($1, $3);
    }
    | ID '(' ')' ';' {
        $$ = createFuncCall($1, NULL);
    }
    | ID '(' arg_list ')' error {
        fprintf(stderr, "   Missing semicolon after function call to '%s'\n", $1);
        yyerrok;
        $$ = createFuncCall($1, $3);
    }
;

/* ── FUNCTION DECLARATION ─────────────────────────────────────────────────
 *   Syntax:  function Name(type param, ...) returns type { body }
 *   Entry point:  function Master() returns nothing { ... }
 */
func_decl:
    FUNCTION ID '(' param_decl_list ')' RETURNS type '{' stmt_list '}' {
        $$ = createFuncDecl($2, $7, $4, $9);
        free($2);
    }
    | FUNCTION ID '(' param_decl_list ')' RETURNS type '{' '}' {
        /* Function with empty body */
        $$ = createFuncDecl($2, $7, $4, NULL);
        free($2);
    }
    | FUNCTION ID '(' param_decl_list ')' RETURNS type error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '{' to open function body for '%s'\n", $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    | FUNCTION ID '(' param_decl_list ')' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'returns <type>' after parameter list for '%s'\n", $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    | FUNCTION ID error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '(' after function name '%s'\n", $2);
        free($2);
        $$ = NULL;
        yyerrok;
    }
    ;

/* ── PARAMETER DECLARATION LIST ──────────────────────────────────────────── */
param_decl_list:
    /* empty */                         { $$ = NULL; }
    | param_decl                        { $$ = $1; }
    | param_decl_list ',' param_decl    { $$ = createStmtList($1, $3); }
    ;

param_decl:
    type ID {
        $$ = createParamDecl($1, $2);
        free($2);
    }
    ;

while_stmt:
    WHILE '('expr')' '{' stmt_list '}' {
        $$ = createWhile($3, $6);
    }
    | WHILE '('expr')' '{' '}' {
        $$ = createWhile($3, NULL);
    }   
    ;

/* ── EXPRESSIONS ─────────────────────────────────────────────────────────── */
expr:
    NUM                     { $$ = createNum($1); }
    | FLOAT_LIT             { $$ = createFloatLit($1); }
    | CHAR_LIT              { $$ = createCharLit($1); }
    | TRUE_LIT              { $$ = createBoolLit(1); }
    | FALSE_LIT             { $$ = createBoolLit(0); }
    | ID                    { $$ = createVar($1); free($1); }

    /* Function call in expression position: e.g., int x = add(a, b); */
    | ID '(' arg_list ')'  { $$ = createFuncCall($1, $3); free($1); }
    | ID '(' ')'           { $$ = createFuncCall($1, NULL); free($1); }
    | ID '[' expr ']'        { $$ = createArrayAccess($1, $3); free($1); }

    | expr '+' expr         { $$ = createBinOp('+', $1, $3); }

    | expr '-' expr      { $$ = createBinOp('-', $1, $3); }
    

    | expr '*' expr      { $$ = createBinOp('*', $1, $3); }
    

    | expr '/' expr      { $$ = createBinOp('/', $1, $3); }
    
    | '(' expr ')' {$$ = $2; }

    ;

/* ── ARGUMENT LIST (for function calls) ───────────────────────────────────── */
arg_list:
    expr                    { $$ = $1; }
    | arg_list ',' expr     { $$ = createStmtList($1, $3); }
    ;

/* ── PRINT STATEMENT ─────────────────────────────────────────────────────── */
print_stmt:
    PRINT '(' expr ')' ';' {
        $$ = createPrint($3);
    }
    | PRINT '(' ')' ';' {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   print() requires an expression argument\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<variable or expression>);'\n\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT '(' expr ')' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT '(' expr error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT '(' error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        $$ = NULL;
        yyerrok;
    }
    | PRINT error {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis after 'print'\n");
        $$ = NULL;
        yyerrok;
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
    fprintf(stderr, "   %s", s);
    if (yytext && yytext[0] != '\0') {
        fprintf(stderr, " (near token: '%s')\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "   💡 Common fixes:\n");
    fprintf(stderr, "      • Check for missing semicolons\n");
    fprintf(stderr, "      • Verify braces and parentheses are balanced\n");
    fprintf(stderr, "      • Ensure variables are declared before use\n");
    fprintf(stderr, "      • Function syntax: function Name(type param) returns type { ... }\n\n");
    fprintf(stderr, "      • Array syntax: int nums[5]; nums[0] = 10;\n\n");
}
