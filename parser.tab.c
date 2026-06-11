/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "parser.y"
{
    int   num;          /* integer and char literals, bool (0/1) */
    float fval;         /* float literals */
    char* str;          /* identifiers and type strings */
    struct ASTNode* node;
}
/* Line 193 of yacc.c.  */
#line 186 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 199 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   571

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  205

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,    33,    31,    43,    32,    44,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      29,    36,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    55,    57,    61,
      65,    68,    74,    80,    85,    92,    99,   107,   115,   120,
     125,   129,   132,   136,   139,   143,   149,   154,   160,   171,
     181,   190,   197,   201,   202,   204,   208,   211,   219,   226,
     231,   235,   239,   242,   254,   265,   275,   285,   294,   299,
     303,   304,   306,   308,   310,   312,   314,   316,   321,   325,
     330,   334,   338,   342,   346,   350,   354,   358,   362,   366,
     370,   374,   378,   380,   384,   390,   395,   401,   406,   410,
     413,   419,   421,   424,   428
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    47,    -1,    48,    -1,    47,    48,    -1,
      50,    -1,    59,    -1,    71,    -1,    50,    -1,    49,    50,
      -1,    52,    -1,    56,    -1,    53,    -1,    70,    -1,    57,
      -1,    58,    -1,    54,    -1,    55,    -1,    62,    -1,    65,
      -1,    66,    -1,    73,    -1,    74,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    51,     8,    35,
      -1,    51,     8,     1,    -1,    51,     1,    -1,    51,     8,
      36,    68,    35,    -1,    51,     8,    36,    68,     1,    -1,
      51,     8,    36,     1,    -1,    51,     8,    37,     3,    38,
      35,    -1,    51,     8,    37,     3,    38,     1,    -1,     8,
      37,    68,    38,    36,    68,    35,    -1,     8,    37,    68,
      38,    36,    68,     1,    -1,     8,    36,    68,    35,    -1,
       8,    36,    68,     1,    -1,     8,    36,     1,    -1,     8,
       1,    -1,    16,    68,    35,    -1,    16,    35,    -1,    16,
      68,     1,    -1,     8,    39,    69,    40,    35,    -1,     8,
      39,    40,    35,    -1,     8,    39,    69,    40,     1,    -1,
      14,     8,    39,    60,    40,    15,    51,    41,    49,    42,
      -1,    14,     8,    39,    60,    40,    15,    51,    41,    42,
      -1,    14,     8,    39,    60,    40,    15,    51,     1,    -1,
      14,     8,    39,    60,    40,     1,    -1,    14,     8,     1,
      -1,    -1,    61,    -1,    60,    43,    61,    -1,    51,     8,
      -1,    18,    39,    68,    40,    41,    49,    42,    -1,    18,
      39,    68,    40,    41,    42,    -1,    51,     8,    36,    68,
      -1,     8,    36,    68,    -1,     8,    36,    68,    -1,     8,
      20,    -1,    19,    39,    63,    35,    68,    35,    64,    40,
      41,    49,    42,    -1,    19,    39,    63,    35,    68,    35,
      64,    40,    41,    42,    -1,    19,    39,    63,    35,    68,
      35,    64,    40,     1,    -1,    26,    39,    68,    40,    27,
      41,    49,    42,    67,    -1,    26,    39,    68,    40,    27,
      41,    42,    67,    -1,    28,    41,    49,    42,    -1,    28,
      41,    42,    -1,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     8,    39,    69,    40,
      -1,     8,    39,    40,    -1,     8,    37,    68,    38,    -1,
       8,    44,     8,    -1,    68,    31,    68,    -1,    68,    32,
      68,    -1,    68,    33,    68,    -1,    68,    34,    68,    -1,
      68,    29,    68,    -1,    68,    30,    68,    -1,    68,    21,
      68,    -1,    68,    22,    68,    -1,    68,    23,    68,    -1,
      68,    24,    68,    -1,    39,    68,    40,    -1,    68,    -1,
      69,    43,    68,    -1,    17,    39,    68,    40,    35,    -1,
      17,    39,    40,    35,    -1,    17,    39,    68,    40,     1,
      -1,    17,    39,    68,     1,    -1,    17,    39,     1,    -1,
      17,     1,    -1,    25,     8,    41,    72,    42,    -1,    52,
      -1,    72,    52,    -1,     8,     8,    35,    -1,     8,    44,
       8,    36,    68,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,    91,    92,    96,    97,    98,   103,   104,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   127,   128,   129,   130,   131,   136,   140,
     150,   161,   165,   172,   182,   186,   197,   201,   212,   216,
     230,   237,   248,   251,   255,   266,   269,   272,   284,   288,
     293,   300,   307,   318,   319,   320,   324,   331,   334,   355,
     356,   360,   361,   365,   368,   372,   383,   386,   392,   395,
     398,   404,   405,   406,   407,   408,   409,   412,   413,   414,
     415,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   432,   433,   438,   441,   448,   454,   460,   466,
     480,   486,   487,   493,   501
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "FLOAT_LIT", "CHAR_LIT",
  "TRUE_LIT", "FALSE_LIT", "ID", "INT", "FLOAT", "CHAR_TYPE", "BOOL_TYPE",
  "NOTHING", "FUNCTION", "RETURNS", "RETURN_KW", "PRINT", "WHILE", "FOR",
  "INC", "LE", "GE", "EQ", "NE", "STRUCT", "IF", "THEN", "ALTERNATIVELY",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "';'", "'='", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "','", "'.'", "$accept", "program",
  "top_level_list", "top_level_item", "stmt_list", "stmt", "type", "decl",
  "decAssign", "array_decl", "array_assign", "assign", "return_stmt",
  "call_stmt", "func_decl", "param_decl_list", "param_decl", "while_stmt",
  "for_init", "for_update", "for_stmt", "if_stmt", "else_part", "expr",
  "arg_list", "print_stmt", "struct_decl", "field_decl_list", "struct_var",
  "field_assign", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      62,    43,    45,    42,    47,    59,    61,    91,    93,    40,
      41,   123,   125,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    51,    51,    52,    52,
      52,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    57,    58,    58,    58,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    66,    66,    67,    67,
      67,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      71,    72,    72,    73,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     5,     5,     4,     6,     6,     7,     7,     4,     4,
       3,     2,     3,     2,     3,     5,     4,     5,    10,     9,
       8,     6,     3,     0,     1,     3,     2,     7,     6,     4,
       3,     3,     2,    11,    10,     9,     9,     8,     4,     3,
       0,     1,     1,     1,     1,     1,     1,     4,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     5,     4,     5,     4,     3,     2,
       5,     1,     2,     3,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     5,     0,    10,
      12,    16,    17,    11,    14,    15,     6,    18,    19,    20,
      13,     7,    21,    22,    41,     0,     0,     0,     0,     0,
       0,    71,    72,    73,    74,    75,    76,    43,     0,     0,
      99,     0,     0,     0,     0,     0,     1,     4,    30,     0,
     103,    40,     0,     0,     0,    92,     0,     0,    52,    53,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    98,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    28,     0,     0,    39,
      38,     0,    46,     0,     0,     0,     0,     0,    54,     0,
      78,     0,    80,    91,    87,    88,    89,    90,    85,    86,
      81,    82,    83,    84,    95,    97,     0,     0,     0,     0,
       0,     0,   101,     0,     0,    33,     0,     0,     0,    47,
      45,    93,     0,    56,     0,     0,    79,    77,    96,    94,
       0,    60,     0,     0,     0,   100,   102,     0,    32,    31,
       0,     0,   104,    51,     0,    55,    58,     0,     8,    59,
       0,     0,    35,    34,    37,    36,     0,    57,     9,     0,
       0,    70,     0,    50,     0,    62,     0,     0,     0,    67,
      70,    49,     0,    61,    65,     0,     0,    66,    48,    64,
       0,    69,     0,    63,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,   167,   168,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   107,   108,    27,    92,   180,
      28,    29,   189,    65,    66,    30,    31,   133,    32,    33
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -92
static const yytype_int16 yypact[] =
{
     472,    13,   -92,   -92,   -92,   -92,   -92,     1,   145,    12,
     -28,    -2,    48,    21,    91,   472,   -92,   -92,    95,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,    57,    80,    28,   129,    98,
      15,   -92,   -92,   -92,   -92,   -92,   -27,   -92,    28,   164,
     -92,    19,    28,   318,    74,    28,   -92,   -92,   -92,     3,
     -92,   -92,   182,   471,    81,   537,   -35,   108,   -92,   356,
      28,   135,   153,   410,   -92,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,   -92,   -92,   127,    78,   425,
     128,   158,   136,   356,   439,   -92,   -92,   121,   169,   -92,
     -92,   141,   -92,    18,    28,    28,   170,    77,   -92,   489,
     -92,   133,   -92,   -92,   176,   176,   125,   125,   176,   176,
      32,    32,   -92,   -92,   -92,   -92,    27,   140,    28,   154,
      28,   162,   -92,   279,   191,   -92,   200,   151,    28,   -92,
     -92,   537,   507,   -92,    63,   356,   -92,   -92,   -92,   -92,
     228,   537,    28,   522,    54,   -92,   -92,   150,   -92,   -92,
      60,   227,   -92,   -92,   356,   -92,   -92,   255,   -92,   537,
     211,   267,   -92,   -92,   -92,   -92,     2,   -92,   -92,    94,
     180,   197,   294,   -92,   306,   -92,    28,     5,   185,   -92,
     197,   -92,   333,   537,   -92,   345,   372,   -92,   -92,   -92,
     384,   -92,   411,   -92,   -92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   -92,   212,   -91,     0,   -51,   -86,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,    97,   -92,   -92,   -92,
     -92,   -92,    53,    -7,   181,   -92,   -92,   -92,   -92,   -92
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      17,    49,    91,   183,    95,   103,   194,   132,   104,    40,
      70,    52,    71,    50,    34,    17,    68,    72,   106,   139,
      86,    35,    41,    42,    43,    44,    45,    46,   148,    62,
      63,    41,    42,    43,    44,    45,    46,    53,    96,    97,
      98,    73,   131,   184,    88,    89,   195,   156,    94,    36,
      37,    51,    38,   140,    69,    95,    54,    39,    48,    87,
      55,   172,   149,   109,   163,    83,    84,    48,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   164,   125,
     182,    61,   131,    41,    42,    43,    44,    45,    46,    96,
     136,    56,    60,   192,   106,   173,    58,   141,   142,    75,
      76,    77,    78,    59,   200,   202,    67,    79,    80,    81,
      82,    83,    84,   176,   185,    93,   102,   144,   126,    48,
     145,   151,   135,   153,    41,    42,    43,    44,    45,    46,
     186,   161,    41,    42,    43,    44,    45,    46,    41,    42,
      43,    44,    45,    46,   105,   169,    75,    76,    41,    42,
      43,    44,    45,    46,    79,    80,    81,    82,    83,    84,
      48,   112,   124,    58,   128,    74,   129,   178,    48,    64,
     154,   130,   137,   147,    48,   110,   104,   138,   143,   193,
      47,   150,   178,    99,    48,    75,    76,    77,    78,   160,
     152,   171,   178,    79,    80,    81,    82,    83,    84,    85,
     178,   158,   178,    75,    76,    77,    78,    81,    82,    83,
      84,    79,    80,    81,    82,    83,    84,   100,   157,   179,
     187,    75,    76,    77,    78,   188,   196,    57,   174,    79,
      80,    81,    82,    83,    84,   159,     1,     2,     3,     4,
       5,     6,   165,   197,     8,     9,    10,    11,    75,    76,
      77,    78,   111,     0,    13,     0,    79,    80,    81,    82,
      83,    84,   175,     1,     2,     3,     4,     5,     6,     0,
     166,     8,     9,    10,    11,     1,     2,     3,     4,     5,
       6,    13,     0,     8,     9,    10,    11,     0,     2,     3,
       4,     5,     6,    13,     0,     0,     0,   177,     0,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     0,   181,
       8,     9,    10,    11,     1,     2,     3,     4,     5,     6,
      13,   155,     8,     9,    10,    11,    90,     2,     3,     4,
       5,     6,    13,     0,     0,     0,   190,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     0,   191,     8,
       9,    10,    11,     1,     2,     3,     4,     5,     6,    13,
       0,     8,     9,    10,    11,     2,     3,     4,     5,     6,
       0,    13,     0,     0,     0,   198,     0,     0,     0,     0,
       1,     2,     3,     4,     5,     6,     0,   199,     8,     9,
      10,    11,     1,     2,     3,     4,     5,     6,    13,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,   201,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     0,   203,     8,     9,    10,
      11,    75,    76,    77,    78,     0,     0,    13,     0,    79,
      80,    81,    82,    83,    84,     0,    75,    76,    77,    78,
     113,     0,     0,   204,    79,    80,    81,    82,    83,    84,
      75,    76,    77,    78,     0,   127,     0,     0,    79,    80,
      81,    82,    83,    84,     0,     0,     0,     0,     0,   134,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    75,    76,    77,    78,     0,    12,    13,     0,
      79,    80,    81,    82,    83,    84,     0,     0,     0,   101,
      75,    76,    77,    78,     0,     0,     0,     0,    79,    80,
      81,    82,    83,    84,     0,     0,     0,   146,    75,    76,
      77,    78,     0,     0,     0,     0,    79,    80,    81,    82,
      83,    84,   162,    75,    76,    77,    78,     0,     0,     0,
       0,    79,    80,    81,    82,    83,    84,   170,    75,    76,
      77,    78,     0,     0,     0,     0,    79,    80,    81,    82,
      83,    84
};

static const yytype_int16 yycheck[] =
{
       0,     8,    53,     1,     1,    40,     1,    93,    43,     8,
      37,    39,    39,     1,     1,    15,     1,    44,    69,     1,
       1,     8,     3,     4,     5,     6,     7,     8,     1,    36,
      37,     3,     4,     5,     6,     7,     8,    39,    35,    36,
      37,    48,    93,    41,    51,    52,    41,   133,    55,    36,
      37,    39,    39,    35,    39,     1,     8,    44,    39,    40,
      39,     1,    35,    70,     1,    33,    34,    39,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    15,     1,
     171,     1,   133,     3,     4,     5,     6,     7,     8,    35,
      97,     0,    35,   184,   145,    35,     1,   104,   105,    21,
      22,    23,    24,     8,   195,   196,     8,    29,    30,    31,
      32,    33,    34,   164,    20,    41,    35,    40,    40,    39,
      43,   128,     1,   130,     3,     4,     5,     6,     7,     8,
      36,   138,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,    36,   152,    21,    22,     3,     4,
       5,     6,     7,     8,    29,    30,    31,    32,    33,    34,
      39,     8,    35,     1,    36,     1,     8,   167,    39,    40,
       8,    35,     3,    40,    39,    40,    43,    36,     8,   186,
      35,    41,   182,     1,    39,    21,    22,    23,    24,    38,
      36,    41,   192,    29,    30,    31,    32,    33,    34,    35,
     200,     1,   202,    21,    22,    23,    24,    31,    32,    33,
      34,    29,    30,    31,    32,    33,    34,    35,    27,     8,
      40,    21,    22,    23,    24,    28,    41,    15,     1,    29,
      30,    31,    32,    33,    34,    35,     8,     9,    10,    11,
      12,    13,   145,   190,    16,    17,    18,    19,    21,    22,
      23,    24,    71,    -1,    26,    -1,    29,    30,    31,    32,
      33,    34,    35,     8,     9,    10,    11,    12,    13,    -1,
      42,    16,    17,    18,    19,     8,     9,    10,    11,    12,
      13,    26,    -1,    16,    17,    18,    19,    -1,     9,    10,
      11,    12,    13,    26,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    -1,    42,
      16,    17,    18,    19,     8,     9,    10,    11,    12,    13,
      26,    42,    16,    17,    18,    19,     8,     9,    10,    11,
      12,    13,    26,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,     8,     9,    10,    11,    12,    13,    -1,    42,    16,
      17,    18,    19,     8,     9,    10,    11,    12,    13,    26,
      -1,    16,    17,    18,    19,     9,    10,    11,    12,    13,
      -1,    26,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
       8,     9,    10,    11,    12,    13,    -1,    42,    16,    17,
      18,    19,     8,     9,    10,    11,    12,    13,    26,    -1,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,     8,
       9,    10,    11,    12,    13,    -1,    42,    16,    17,    18,
      19,    21,    22,    23,    24,    -1,    -1,    26,    -1,    29,
      30,    31,    32,    33,    34,    -1,    21,    22,    23,    24,
      40,    -1,    -1,    42,    29,    30,    31,    32,    33,    34,
      21,    22,    23,    24,    -1,    40,    -1,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    17,
      18,    19,    21,    22,    23,    24,    -1,    25,    26,    -1,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    38,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    38,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      18,    19,    25,    26,    46,    47,    48,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    62,    65,    66,
      70,    71,    73,    74,     1,     8,    36,    37,    39,    44,
       8,     3,     4,     5,     6,     7,     8,    35,    39,    68,
       1,    39,    39,    39,     8,    39,     0,    48,     1,     8,
      35,     1,    68,    68,    40,    68,    69,     8,     1,    39,
      37,    39,    44,    68,     1,    21,    22,    23,    24,    29,
      30,    31,    32,    33,    34,    35,     1,    40,    68,    68,
       8,    51,    63,    41,    68,     1,    35,    36,    37,     1,
      35,    38,    35,    40,    43,    36,    51,    60,    61,    68,
      40,    69,     8,    40,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    35,     1,    40,    40,    36,     8,
      35,    51,    52,    72,    40,     1,    68,     3,    36,     1,
      35,    68,    68,     8,    40,    43,    38,    40,     1,    35,
      41,    68,    36,    68,     8,    42,    52,    27,     1,    35,
      38,    68,    35,     1,    15,    61,    42,    49,    50,    68,
      35,    41,     1,    35,     1,    35,    51,    42,    50,     8,
      64,    42,    49,     1,    41,    20,    36,    40,    28,    67,
      42,    42,    49,    68,     1,    41,    41,    67,    42,    42,
      49,    42,    49,    42,    42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 86 "parser.y"
    { root = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:
#line 91 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 4:
#line 92 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 5:
#line 96 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 6:
#line 97 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 7:
#line 98 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 8:
#line 103 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 9:
#line 104 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 23:
#line 127 "parser.y"
    { (yyval.str) = "int"; ;}
    break;

  case 24:
#line 128 "parser.y"
    { (yyval.str) = "float"; ;}
    break;

  case 25:
#line 129 "parser.y"
    { (yyval.str) = "char"; ;}
    break;

  case 26:
#line 130 "parser.y"
    { (yyval.str) = "bool"; ;}
    break;

  case 27:
#line 131 "parser.y"
    { (yyval.str) = "nothing"; ;}
    break;

  case 28:
#line 136 "parser.y"
    {
        (yyval.node) = createDecl((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
        free((yyvsp[(2) - (3)].str));
    ;}
    break;

  case 29:
#line 140 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid syntax after '%s %s'\n", (yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
        fprintf(stderr, "   💡 Suggestions:\n");
        fprintf(stderr, "      • Declaration only:            '%s %s;'\n", (yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
        fprintf(stderr, "      • Declaration with assignment: '%s %s = <expression>;'\n\n", (yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
        free((yyvsp[(2) - (3)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 30:
#line 150 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected '<type> <identifier>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 31:
#line 161 "parser.y"
    {
        (yyval.node) = createDecAssignNode((yyvsp[(1) - (5)].str), (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node));
        free((yyvsp[(2) - (5)].str));
    ;}
    break;

  case 32:
#line 165 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after declaration-assignment for '%s'\n", (yyvsp[(2) - (5)].str));
        free((yyvsp[(2) - (5)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 33:
#line 172 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing expression after '='\n");
        free((yyvsp[(2) - (4)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 34:
#line 182 "parser.y"
    {
        (yyval.node) = createArrayDecl((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num));
        free((yyvsp[(2) - (6)].str));
    ;}
    break;

  case 35:
#line 186 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array declaration for '%s'\n", (yyvsp[(2) - (6)].str));
        free((yyvsp[(2) - (6)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 36:
#line 197 "parser.y"
    {
        (yyval.node) = createArrayAssign((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
        free((yyvsp[(1) - (7)].str));
    ;}
    break;

  case 37:
#line 201 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array assignment for '%s'\n", (yyvsp[(1) - (7)].str));
        free((yyvsp[(1) - (7)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 38:
#line 212 "parser.y"
    {
        (yyval.node) = createAssign((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node));
        free((yyvsp[(1) - (4)].str));
    ;}
    break;

  case 39:
#line 216 "parser.y"
    {
        if (yychar == '=') {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Chained assignment is not supported: '%s = ... = ...'\n", (yyvsp[(1) - (4)].str));
            fprintf(stderr, "   💡 Suggestion: Use two separate statements\n\n");
        } else {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Missing semicolon after assignment to '%s'\n", (yyvsp[(1) - (4)].str));
            fprintf(stderr, "   💡 Suggestion: Add ';' after the expression\n\n");
        }
        free((yyvsp[(1) - (4)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 40:
#line 230 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment to '%s'\n", (yyvsp[(1) - (3)].str));
        free((yyvsp[(1) - (3)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 41:
#line 237 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement for '%s'\n", (yyvsp[(1) - (2)].str));
        free((yyvsp[(1) - (2)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 42:
#line 248 "parser.y"
    {
        (yyval.node) = createReturn((yyvsp[(2) - (3)].node));
    ;}
    break;

  case 43:
#line 251 "parser.y"
    {
        /* void return — no expression */
        (yyval.node) = createReturn(NULL);
    ;}
    break;

  case 44:
#line 255 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after return statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the return expression\n\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 45:
#line 266 "parser.y"
    {
        (yyval.node) = createFuncCall((yyvsp[(1) - (5)].str), (yyvsp[(3) - (5)].node));
    ;}
    break;

  case 46:
#line 269 "parser.y"
    {
        (yyval.node) = createFuncCall((yyvsp[(1) - (4)].str), NULL);
    ;}
    break;

  case 47:
#line 272 "parser.y"
    {
        fprintf(stderr, "   Missing semicolon after function call to '%s'\n", (yyvsp[(1) - (5)].str));
        yyerrok;
        (yyval.node) = createFuncCall((yyvsp[(1) - (5)].str), (yyvsp[(3) - (5)].node));
    ;}
    break;

  case 48:
#line 284 "parser.y"
    {
        (yyval.node) = createFuncDecl((yyvsp[(2) - (10)].str), (yyvsp[(7) - (10)].str), (yyvsp[(4) - (10)].node), (yyvsp[(9) - (10)].node));
        free((yyvsp[(2) - (10)].str));
    ;}
    break;

  case 49:
#line 288 "parser.y"
    {
        /* Function with empty body */
        (yyval.node) = createFuncDecl((yyvsp[(2) - (9)].str), (yyvsp[(7) - (9)].str), (yyvsp[(4) - (9)].node), NULL);
        free((yyvsp[(2) - (9)].str));
    ;}
    break;

  case 50:
#line 293 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '{' to open function body for '%s'\n", (yyvsp[(2) - (8)].str));
        free((yyvsp[(2) - (8)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 51:
#line 300 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'returns <type>' after parameter list for '%s'\n", (yyvsp[(2) - (6)].str));
        free((yyvsp[(2) - (6)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 52:
#line 307 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '(' after function name '%s'\n", (yyvsp[(2) - (3)].str));
        free((yyvsp[(2) - (3)].str));
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 53:
#line 318 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 54:
#line 319 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 55:
#line 320 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 56:
#line 324 "parser.y"
    {
        (yyval.node) = createParamDecl((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str));
        free((yyvsp[(2) - (2)].str));
    ;}
    break;

  case 57:
#line 331 "parser.y"
    {
        (yyval.node) = createWhile((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
    ;}
    break;

  case 58:
#line 334 "parser.y"
    {
        (yyval.node) = createWhile((yyvsp[(3) - (6)].node), NULL);
    ;}
    break;

  case 59:
#line 355 "parser.y"
    { (yyval.node) = createDecAssignNode((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].node)); free((yyvsp[(2) - (4)].str)); ;}
    break;

  case 60:
#line 356 "parser.y"
    { (yyval.node) = createAssign((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].node));            free((yyvsp[(1) - (3)].str)); ;}
    break;

  case 61:
#line 360 "parser.y"
    { (yyval.node) = createAssign((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].node)); free((yyvsp[(1) - (3)].str)); ;}
    break;

  case 62:
#line 361 "parser.y"
    { (yyval.node) = createAssign((yyvsp[(1) - (2)].str), createBinOp('+', createVar((yyvsp[(1) - (2)].str)), createNum(1))); free((yyvsp[(1) - (2)].str)); ;}
    break;

  case 63:
#line 365 "parser.y"
    {
        (yyval.node) = createFor((yyvsp[(3) - (11)].node), (yyvsp[(5) - (11)].node), (yyvsp[(7) - (11)].node), (yyvsp[(10) - (11)].node));
    ;}
    break;

  case 64:
#line 368 "parser.y"
    {
        /* Empty body — body is NULL */
        (yyval.node) = createFor((yyvsp[(3) - (10)].node), (yyvsp[(5) - (10)].node), (yyvsp[(7) - (10)].node), NULL);
    ;}
    break;

  case 65:
#line 372 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '{' to open for-loop body\n");
        fprintf(stderr, "   💡 Suggestion: for (init; condition; update) { ... }\n\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 66:
#line 383 "parser.y"
    {
        (yyval.node) = createIf((yyvsp[(3) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node));
    ;}
    break;

  case 67:
#line 386 "parser.y"
    {
        (yyval.node) = createIf((yyvsp[(3) - (8)].node), NULL, (yyvsp[(8) - (8)].node));
    ;}
    break;

  case 68:
#line 392 "parser.y"
    {
        (yyval.node) = createElse((yyvsp[(3) - (4)].node));
    ;}
    break;

  case 69:
#line 395 "parser.y"
    {
        (yyval.node) = createElse(NULL);
    ;}
    break;

  case 70:
#line 398 "parser.y"
    {
        (yyval.node) = NULL;
    ;}
    break;

  case 71:
#line 404 "parser.y"
    { (yyval.node) = createNum((yyvsp[(1) - (1)].num)); ;}
    break;

  case 72:
#line 405 "parser.y"
    { (yyval.node) = createFloatLit((yyvsp[(1) - (1)].fval)); ;}
    break;

  case 73:
#line 406 "parser.y"
    { (yyval.node) = createCharLit((yyvsp[(1) - (1)].num)); ;}
    break;

  case 74:
#line 407 "parser.y"
    { (yyval.node) = createBoolLit(1); ;}
    break;

  case 75:
#line 408 "parser.y"
    { (yyval.node) = createBoolLit(0); ;}
    break;

  case 76:
#line 409 "parser.y"
    { (yyval.node) = createVar((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 77:
#line 412 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 78:
#line 413 "parser.y"
    { (yyval.node) = createFuncCall((yyvsp[(1) - (3)].str), NULL); free((yyvsp[(1) - (3)].str)); ;}
    break;

  case 79:
#line 414 "parser.y"
    { (yyval.node) = createArrayAccess((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node)); free((yyvsp[(1) - (4)].str)); ;}
    break;

  case 80:
#line 415 "parser.y"
    { (yyval.node) = createFieldAccess((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str)); free((yyvsp[(1) - (3)].str)); free((yyvsp[(3) - (3)].str)); ;}
    break;

  case 81:
#line 417 "parser.y"
    { (yyval.node) = createBinOp('+', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 82:
#line 418 "parser.y"
    { (yyval.node) = createBinOp('-', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 83:
#line 419 "parser.y"
    { (yyval.node) = createBinOp('*', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 84:
#line 420 "parser.y"
    { (yyval.node) = createBinOp('/', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 85:
#line 421 "parser.y"
    { (yyval.node) = createBinOp('<', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 86:
#line 422 "parser.y"
    { (yyval.node) = createBinOp('>', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 87:
#line 423 "parser.y"
    { (yyval.node) = createBinOp('L', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 88:
#line 424 "parser.y"
    { (yyval.node) = createBinOp('G', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 89:
#line 425 "parser.y"
    { (yyval.node) = createBinOp('E', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 90:
#line 426 "parser.y"
    { (yyval.node) = createBinOp('N', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 91:
#line 427 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 92:
#line 432 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 93:
#line 433 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 94:
#line 438 "parser.y"
    {
        (yyval.node) = createPrint((yyvsp[(3) - (5)].node));
    ;}
    break;

  case 95:
#line 441 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   print() requires an expression argument\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<variable or expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 96:
#line 448 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 97:
#line 454 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 98:
#line 460 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 99:
#line 466 "parser.y"
    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis after 'print'\n");
        (yyval.node) = NULL;
        yyerrok;
    ;}
    break;

  case 100:
#line 480 "parser.y"
    {
        (yyval.node) = createStructDecl((yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].node));
    ;}
    break;

  case 101:
#line 486 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 102:
#line 487 "parser.y"
    { (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 103:
#line 493 "parser.y"
    {
        (yyval.node) = createStructVar((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].str));
    ;}
    break;

  case 104:
#line 501 "parser.y"
    {
        (yyval.node) = createFieldAssign((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].node));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2291 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 506 "parser.y"


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

