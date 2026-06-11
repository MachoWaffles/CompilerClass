/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     FLOAT_LIT = 259,
     CHAR_LIT = 260,
     TRUE_LIT = 261,
     FALSE_LIT = 262,
     ID = 263,
     INT = 264,
     FLOAT = 265,
     CHAR_TYPE = 266,
     BOOL_TYPE = 267,
     NOTHING = 268,
     FUNCTION = 269,
     RETURNS = 270,
     RETURN_KW = 271,
     PRINT = 272,
     WHILE = 273,
     FOR = 274,
     INC = 275,
     LE = 276,
     GE = 277,
     EQ = 278,
     NE = 279,
     STRUCT = 280,
     IF = 281,
     THEN = 282,
     ALTERNATIVELY = 283
   };
#endif
/* Tokens.  */
#define NUM 258
#define FLOAT_LIT 259
#define CHAR_LIT 260
#define TRUE_LIT 261
#define FALSE_LIT 262
#define ID 263
#define INT 264
#define FLOAT 265
#define CHAR_TYPE 266
#define BOOL_TYPE 267
#define NOTHING 268
#define FUNCTION 269
#define RETURNS 270
#define RETURN_KW 271
#define PRINT 272
#define WHILE 273
#define FOR 274
#define INC 275
#define LE 276
#define GE 277
#define EQ 278
#define NE 279
#define STRUCT 280
#define IF 281
#define THEN 282
#define ALTERNATIVELY 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "parser.y"
{
    int   num;          /* integer and char literals, bool (0/1) */
    float fval;         /* float literals */
    char* str;          /* identifiers and type strings */
    struct ASTNode* node;
}
/* Line 1529 of yacc.c.  */
#line 112 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

