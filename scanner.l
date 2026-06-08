%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int displayTokens;
int yycolno = 1;

#define YY_USER_ACTION \
    yycolno += yyleng;
%}

%option nounput
%option noinput
%option yylineno

%x COMMENT

%%

"//".*          { if (displayTokens) printf("  (ignoring single-line comment)\n"); }

"/*"            { if (displayTokens) printf("  (start multi-line comment)\n"); BEGIN(COMMENT); }
<COMMENT>"*/"   { if (displayTokens) printf("  (end multi-line comment)\n"); BEGIN(INITIAL); }
<COMMENT>\n     { yycolno = 1; }
<COMMENT>.      { }

"int"           { if (displayTokens) printf("  TOKEN: INT keyword\n");      return INT; }
"float"         { if (displayTokens) printf("  TOKEN: FLOAT keyword\n");    return FLOAT; }
"char"          { if (displayTokens) printf("  TOKEN: CHAR keyword\n");     return CHAR_TYPE; }
"bool"          { if (displayTokens) printf("  TOKEN: BOOL keyword\n");     return BOOL_TYPE; }
"nothing"       { if (displayTokens) printf("  TOKEN: NOTHING keyword\n");  return NOTHING; }

"function"      { if (displayTokens) printf("  TOKEN: FUNCTION keyword\n"); return FUNCTION; }
"returns"       { if (displayTokens) printf("  TOKEN: RETURNS keyword\n");  return RETURNS; }
"return"        { if (displayTokens) printf("  TOKEN: RETURN keyword\n");   return RETURN_KW; }

"true"          { if (displayTokens) printf("  TOKEN: true (bool literal)\n");  yylval.num = 1; return TRUE_LIT; }
"false"         { if (displayTokens) printf("  TOKEN: false (bool literal)\n"); yylval.num = 0; return FALSE_LIT; }

"print"         { if (displayTokens) printf("  TOKEN: PRINT keyword\n"); return PRINT; }

"while"     { printf("  TOKEN: WHILE keyword\n"); return WHILE; }

[a-zA-Z_][a-zA-Z0-9_]* {
    if (displayTokens) printf("  TOKEN: ID '%s'\n", yytext);
    yylval.str = strdup(yytext);
    return ID;
}

[0-9]+\.[0-9]+ {
    if (displayTokens) printf("  TOKEN: FLOAT_LIT %s\n", yytext);
    yylval.fval = atof(yytext);
    return FLOAT_LIT;
}

"++"            {
    fprintf(stderr, "\nLexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
    fprintf(stderr, "   Consecutive '+' operators ('++') are not supported\n");
    fprintf(stderr, "   Suggestion: Use 'x = x + 1;' instead\n\n");
    exit(1);
}

[0-9]+          {
    if (displayTokens) printf("  TOKEN: NUM %s\n", yytext);
    long val = strtol(yytext, NULL, 10);
    if (val > 2147483647L || val < -2147483648L) {
        fprintf(stderr, "\nLexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
        fprintf(stderr, "   Integer literal '%s' overflows the int type\n", yytext);
        fprintf(stderr, "   Valid range: -2147483648 to 2147483647\n\n");
        exit(1);
    }
    yylval.num = (int)val;
    return NUM;
}

\'[^\'\\]\'     { if (displayTokens) printf("  TOKEN: CHAR_LIT '%c'\n", yytext[1]); yylval.num = (int)yytext[1]; return CHAR_LIT; }
\'\\n\'         { if (displayTokens) printf("  TOKEN: CHAR_LIT newline\n");          yylval.num = '\n'; return CHAR_LIT; }
\'\\t\'         { if (displayTokens) printf("  TOKEN: CHAR_LIT tab\n");              yylval.num = '\t'; return CHAR_LIT; }
\'\\\\\'        { if (displayTokens) printf("  TOKEN: CHAR_LIT backslash\n");        yylval.num = '\\'; return CHAR_LIT; }

"+"             { if (displayTokens) printf("  TOKEN: '+'\n"); return '+'; }
"="             { if (displayTokens) printf("  TOKEN: '='\n"); return '='; }
"-"             { if (displayTokens) printf("  TOKEN: '-'\n"); return '-'; }
"*"             { if (displayTokens) printf("  TOKEN: '*'\n"); return '*'; }
"/"             { if (displayTokens) printf("  TOKEN: '/'\n"); return '/'; }
"["             { if (displayTokens) printf("  TOKEN: '['\n"); return '['; }
"]"             { if (displayTokens) printf("  TOKEN: ']'\n"); return ']'; }
";"             { if (displayTokens) printf("  TOKEN: ';'\n"); return ';'; }
"("             { if (displayTokens) printf("  TOKEN: '('\n"); return '('; }
")"             { if (displayTokens) printf("  TOKEN: ')'\n"); return ')'; }
"{"             { if (displayTokens) printf("  TOKEN: '{'\n"); return '{'; }
"}"             { if (displayTokens) printf("  TOKEN: '}'\n"); return '}'; }
","             { if (displayTokens) printf("  TOKEN: ','\n"); return ','; }

[ \t]           { }
\n              { yycolno = 1; }

.               {
    fprintf(stderr, "\nLexical Error at line %d, col %d:\n", yylineno, (int)(yycolno - yyleng));
    fprintf(stderr, "   Unknown character: '%c' (ASCII %d)\n", *yytext, (int)*yytext);
    fprintf(stderr, "   Suggestion: Remove this character or check for typos\n\n");
    exit(1);
}

<<EOF>>         {
    if (YY_START == COMMENT) {
        fprintf(stderr, "\nLexical Error at line %d:\n", yylineno);
        fprintf(stderr, "   Unterminated multi-line comment - reached end of file\n");
        fprintf(stderr, "   Suggestion: Add '*/' to close the comment\n\n");
        return 0;
    }
    yyterminate();
}

%%

int yywrap() { return 1; }