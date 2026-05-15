%{
/* LEXICAL ANALYZER (SCANNER)
 * This is the first phase of compilation - breaking input into tokens
 * Flex generates a scanner from these rules that reads character by character
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"  /* Token definitions from Bison */
/* Global flag to enable token display */
extern int displayTokens;
int yycolno = 1;
%}
/* Flex options to suppress warnings for unused functions */
%option nounput
%option noinput
%option yylineno
%{
#define YY_USER_ACTION \
    yycolno += yyleng;
%}
/* Exclusive start condition for multi-line comments */
%x COMMENT
%%
"//".*          {
    /* Single-line comment - ignore everything from // to end of line */
    if (displayTokens) printf("  (ignoring single-line comment)\n");
}
"/*"            {
    /* Start of multi-line comment - switch to COMMENT state */
    if (displayTokens) printf("  (start multi-line comment)\n");
    BEGIN(COMMENT);
}
<COMMENT>"*/"   {
    /* End of multi-line comment - return to normal scanning */
    if (displayTokens) printf("  (end multi-line comment)\n");
    BEGIN(INITIAL);
}
<COMMENT>\n     {
    /* Newline inside comment - reset column and continue in COMMENT state */
    yycolno = 1;
}
<COMMENT>.      {
    /* Any other character inside comment - ignore */
}
"int"           {
    if (displayTokens) printf("  TOKEN: INT keyword\n");
    return INT;
}
"print"         {
    if (displayTokens) printf("  TOKEN: PRINT keyword\n");
    return PRINT;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (displayTokens) printf("  TOKEN: ID '%s'\n", yytext);
    yylval.str = strdup(yytext);
    return ID;
}
"++"            {
    /* Consecutive + operators - common mistake from C/C++ programmers */
    fprintf(stderr, "\n❌ Lexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
    fprintf(stderr, "   Consecutive '+' operators ('++') are not supported\n");
    fprintf(stderr, "   This language does not have an increment operator\n");
    fprintf(stderr, "   💡 Suggestion: Use 'x = x + 1;' instead of 'x++' or '++x'\n\n");
    exit(1);
}
[0-9]+          {
    if (displayTokens) printf("  TOKEN: NUM %s\n", yytext);
    /* Check for integer overflow before storing the value */
    long val = strtol(yytext, NULL, 10);
    if (val > 2147483647L || val < -2147483648L) {
        fprintf(stderr, "\n❌ Lexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
        fprintf(stderr, "   Integer literal '%s' overflows the int type\n", yytext);
        fprintf(stderr, "   Valid range: -2147483648 to 2147483647\n");
        fprintf(stderr, "   💡 Suggestion: Use a value within the valid int range\n\n");
        exit(1);
    }
    yylval.num = (int)val;
    return NUM;
}
"+"             {
    if (displayTokens) printf("  TOKEN: '+'\n");
    return '+';
}
"="             {
    if (displayTokens) printf("  TOKEN: '='\n");
    return '=';
}
";"             {
    if (displayTokens) printf("  TOKEN: ';'\n");
    return ';';
}
"("             {
    if (displayTokens) printf("  TOKEN: '('\n");
    return '(';
}
")"             {
    if (displayTokens) printf("  TOKEN: ')'\n");
    return ')';
}
[ \t]           { }
\n              { yycolno = 1; }
.               {
    fprintf(stderr, "\n❌ Lexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
    fprintf(stderr, "   Unknown character: '%c' (ASCII %d)\n", *yytext, (int)*yytext);
    fprintf(stderr, "   💡 Suggestion: Remove this character or check for typos\n\n");
    exit(1);
}
<<EOF>>         {
    if (YY_START == COMMENT) {
        fprintf(stderr, "\n❌ Lexical Error at line %d:\n", yylineno);
        fprintf(stderr, "   Unterminated multi-line comment - reached end of file\n");
        fprintf(stderr, "   💡 Suggestion: Add '*/' to close the comment\n\n");
        return 0;
    }
    yyterminate();
}
%%
/* Required by Flex - signals end of input */
int yywrap() {
    return 1;  /* 1 means no more input files */
}
