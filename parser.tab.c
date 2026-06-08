/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 98 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FLOAT_LIT = 4,                  /* FLOAT_LIT  */
  YYSYMBOL_CHAR_LIT = 5,                   /* CHAR_LIT  */
  YYSYMBOL_TRUE_LIT = 6,                   /* TRUE_LIT  */
  YYSYMBOL_FALSE_LIT = 7,                  /* FALSE_LIT  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_CHAR_TYPE = 11,                 /* CHAR_TYPE  */
  YYSYMBOL_BOOL_TYPE = 12,                 /* BOOL_TYPE  */
  YYSYMBOL_NOTHING = 13,                   /* NOTHING  */
  YYSYMBOL_FUNCTION = 14,                  /* FUNCTION  */
  YYSYMBOL_RETURNS = 15,                   /* RETURNS  */
  YYSYMBOL_RETURN_KW = 16,                 /* RETURN_KW  */
  YYSYMBOL_PRINT = 17,                     /* PRINT  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_INC = 20,                       /* INC  */
  YYSYMBOL_LE = 21,                        /* LE  */
  YYSYMBOL_GE = 22,                        /* GE  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NE = 24,                        /* NE  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_26_ = 26,                       /* '<'  */
  YYSYMBOL_27_ = 27,                       /* '>'  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program = 43,                   /* program  */
  YYSYMBOL_top_level_list = 44,            /* top_level_list  */
  YYSYMBOL_top_level_item = 45,            /* top_level_item  */
  YYSYMBOL_stmt_list = 46,                 /* stmt_list  */
  YYSYMBOL_stmt = 47,                      /* stmt  */
  YYSYMBOL_type = 48,                      /* type  */
  YYSYMBOL_decl = 49,                      /* decl  */
  YYSYMBOL_decAssign = 50,                 /* decAssign  */
  YYSYMBOL_array_decl = 51,                /* array_decl  */
  YYSYMBOL_array_assign = 52,              /* array_assign  */
  YYSYMBOL_assign = 53,                    /* assign  */
  YYSYMBOL_return_stmt = 54,               /* return_stmt  */
  YYSYMBOL_call_stmt = 55,                 /* call_stmt  */
  YYSYMBOL_func_decl = 56,                 /* func_decl  */
  YYSYMBOL_param_decl_list = 57,           /* param_decl_list  */
  YYSYMBOL_param_decl = 58,                /* param_decl  */
  YYSYMBOL_while_stmt = 59,                /* while_stmt  */
  YYSYMBOL_for_init = 60,                  /* for_init  */
  YYSYMBOL_for_update = 61,                /* for_update  */
  YYSYMBOL_for_stmt = 62,                  /* for_stmt  */
  YYSYMBOL_expr = 63,                      /* expr  */
  YYSYMBOL_arg_list = 64,                  /* arg_list  */
  YYSYMBOL_print_stmt = 65,                /* print_stmt  */
  YYSYMBOL_struct_decl = 66,               /* struct_decl  */
  YYSYMBOL_field_decl_list = 67,           /* field_decl_list  */
  YYSYMBOL_struct_var = 68,                /* struct_var  */
  YYSYMBOL_field_assign = 69               /* field_assign  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,    30,    28,    40,    29,    41,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      26,    33,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    85,    86,    90,    91,    92,    97,    98,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   120,   121,   122,   123,   124,   129,   133,   143,
     154,   158,   165,   175,   179,   190,   194,   205,   209,   223,
     230,   241,   244,   248,   259,   262,   265,   277,   281,   286,
     293,   300,   311,   312,   313,   317,   324,   327,   348,   349,
     353,   354,   358,   361,   365,   376,   377,   378,   379,   380,
     381,   384,   385,   386,   387,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   404,   405,   410,   413,
     420,   426,   432,   438,   452,   458,   459,   465,   473
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FLOAT_LIT",
  "CHAR_LIT", "TRUE_LIT", "FALSE_LIT", "ID", "INT", "FLOAT", "CHAR_TYPE",
  "BOOL_TYPE", "NOTHING", "FUNCTION", "RETURNS", "RETURN_KW", "PRINT",
  "WHILE", "FOR", "INC", "LE", "GE", "EQ", "NE", "STRUCT", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "';'", "'='", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "','", "'.'", "$accept", "program", "top_level_list",
  "top_level_item", "stmt_list", "stmt", "type", "decl", "decAssign",
  "array_decl", "array_assign", "assign", "return_stmt", "call_stmt",
  "func_decl", "param_decl_list", "param_decl", "while_stmt", "for_init",
  "for_update", "for_stmt", "expr", "arg_list", "print_stmt",
  "struct_decl", "field_decl_list", "struct_var", "field_assign", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-95)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     321,     4,   -95,   -95,   -95,   -95,   -95,    16,   139,     8,
     -11,   -10,    41,   114,   321,   -95,   -95,    82,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,    83,    28,   151,    51,   108,    14,   -95,
     -95,   -95,   -95,   -95,   -28,   -95,   151,   167,   -95,    15,
     151,   206,    89,   -95,   -95,   -95,    29,   -95,   -95,   180,
     351,    96,   405,    45,   106,   -95,   332,   151,   126,   133,
     327,   -95,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   -95,   -95,   118,    74,   339,   127,   156,   134,
     332,   -95,   -95,   117,   162,   -95,   -95,   136,   -95,    52,
     151,   151,   159,   111,   -95,   366,   -95,   112,   -95,   -95,
     107,   107,   416,   416,   107,   107,   -27,   -27,   -95,   -95,
     -95,   -95,    75,   135,   151,   141,   151,   105,   -95,   308,
     -95,   199,   137,   151,   -95,   -95,   405,   381,   -95,    77,
     332,   -95,   -95,   -95,   -95,   237,   405,   151,   393,    76,
     -95,   -95,   -95,   -95,    78,   212,   -95,   -95,   332,   -95,
     -95,   249,   -95,   405,   168,   -95,   -95,   -95,   -95,     9,
     -95,   -95,    79,   140,   -95,   261,   -95,   151,    10,   -95,
     273,   405,   -95,   285,   -95,   -95,   297,   -95
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     2,     3,     5,     0,    10,    12,
      16,    17,    11,    14,    15,     6,    18,    19,    13,     7,
      20,    21,    40,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,    70,    42,     0,     0,    93,     0,
       0,     0,     0,     1,     4,    29,     0,    97,    39,     0,
       0,     0,    86,     0,     0,    51,    52,     0,     0,     0,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    92,     0,     0,     0,     0,     0,     0,
       0,    28,    27,     0,     0,    38,    37,     0,    45,     0,
       0,     0,     0,     0,    53,     0,    72,     0,    74,    85,
      81,    82,    83,    84,    79,    80,    75,    76,    77,    78,
      89,    91,     0,     0,     0,     0,     0,     0,    95,     0,
      32,     0,     0,     0,    46,    44,    87,     0,    55,     0,
       0,    73,    71,    90,    88,     0,    59,     0,     0,     0,
      94,    96,    31,    30,     0,     0,    98,    50,     0,    54,
      57,     0,     8,    58,     0,    34,    33,    36,    35,     0,
      56,     9,     0,     0,    49,     0,    61,     0,     0,    48,
       0,    60,    64,     0,    47,    63,     0,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -95,   -95,   -95,   164,   -94,     0,   -49,   -83,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,    39,   -95,   -95,   -95,
     -95,    -7,   115,   -95,   -95,   -95,   -95,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    13,    14,    15,   161,   162,    17,    18,    19,    20,
      21,    22,    23,    24,    25,   103,   104,    26,    89,   173,
      27,    62,    63,    28,    29,   129,    30,    31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      16,    47,    88,    80,    81,    32,    67,   128,    68,    48,
     174,   182,    33,    69,    16,    65,    83,   102,    39,    40,
      41,    42,    43,    44,    38,    50,    51,    59,    60,    58,
      91,    39,    40,    41,    42,    43,    44,    34,    35,    70,
      36,   127,    85,    86,    49,    37,   151,   175,   183,    52,
      66,    46,    84,   134,    39,    40,    41,    42,    43,    44,
     105,    92,    93,    94,    46,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   121,   143,    91,   157,   165,
     127,   180,    99,    55,   135,   100,   131,    46,    61,   186,
      56,   102,   158,   136,   137,    72,    73,    74,    75,   176,
      76,    77,    78,    79,    80,    81,    55,   144,    92,   169,
     166,   122,   177,   149,    53,    57,    64,   146,   130,   148,
      39,    40,    41,    42,    43,    44,   155,    90,    98,    39,
      40,    41,    42,    43,    44,    78,    79,    80,    81,   101,
     163,   108,    39,    40,    41,    42,    43,    44,   139,   142,
     120,   140,   100,    46,    39,    40,    41,    42,    43,    44,
     124,   171,    46,   106,   125,   132,   126,   138,    71,   133,
     181,    45,   154,   145,   147,    46,   172,   178,    54,   159,
     171,    95,     0,   107,     0,     0,   171,    46,    72,    73,
      74,    75,     0,    76,    77,    78,    79,    80,    81,    82,
     152,    72,    73,    74,    75,     0,    76,    77,    78,    79,
      80,    81,    96,   167,    87,     2,     3,     4,     5,     6,
      72,    73,    74,    75,     0,    76,    77,    78,    79,    80,
      81,   153,     0,    72,    73,    74,    75,     0,    76,    77,
      78,    79,    80,    81,   168,     1,     2,     3,     4,     5,
       6,     0,     0,     8,     9,    10,    11,     1,     2,     3,
       4,     5,     6,     0,     0,     8,     9,    10,    11,     1,
       2,     3,     4,     5,     6,     0,   160,     8,     9,    10,
      11,     1,     2,     3,     4,     5,     6,     0,   170,     8,
       9,    10,    11,     1,     2,     3,     4,     5,     6,     0,
     179,     8,     9,    10,    11,     1,     2,     3,     4,     5,
       6,     0,   184,     8,     9,    10,    11,     2,     3,     4,
       5,     6,     0,     0,   185,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,   187,     8,     9,    10,
      11,     2,     3,     4,     5,     6,    12,   150,    72,    73,
      74,    75,     0,    76,    77,    78,    79,    80,    81,     0,
      72,    73,    74,    75,   109,    76,    77,    78,    79,    80,
      81,     0,    72,    73,    74,    75,   123,    76,    77,    78,
      79,    80,    81,     0,     0,     0,    97,    72,    73,    74,
      75,     0,    76,    77,    78,    79,    80,    81,     0,     0,
       0,   141,    72,    73,    74,    75,     0,    76,    77,    78,
      79,    80,    81,   156,    72,    73,    74,    75,     0,    76,
      77,    78,    79,    80,    81,   164,    72,    73,    74,    75,
       0,    76,    77,    78,    79,    80,    81,    72,    73,     0,
       0,     0,    76,    77,    78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       0,     8,    51,    30,    31,     1,    34,    90,    36,     1,
       1,     1,     8,    41,    14,     1,     1,    66,     3,     4,
       5,     6,     7,     8,     8,    36,    36,    34,    35,     1,
       1,     3,     4,     5,     6,     7,     8,    33,    34,    46,
      36,    90,    49,    50,    36,    41,   129,    38,    38,     8,
      36,    36,    37,     1,     3,     4,     5,     6,     7,     8,
      67,    32,    33,    34,    36,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     1,     1,     1,     1,     1,
     129,   175,    37,     1,    32,    40,    93,    36,    37,   183,
       8,   140,    15,   100,   101,    21,    22,    23,    24,    20,
      26,    27,    28,    29,    30,    31,     1,    32,    32,   158,
      32,    37,    33,     8,     0,    32,     8,   124,     1,   126,
       3,     4,     5,     6,     7,     8,   133,    38,    32,     3,
       4,     5,     6,     7,     8,    28,    29,    30,    31,    33,
     147,     8,     3,     4,     5,     6,     7,     8,    37,    37,
      32,    40,    40,    36,     3,     4,     5,     6,     7,     8,
      33,   161,    36,    37,     8,     3,    32,     8,     1,    33,
     177,    32,    35,    38,    33,    36,     8,    37,    14,   140,
     180,     1,    -1,    68,    -1,    -1,   186,    36,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
       1,    21,    22,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,     1,     8,     9,    10,    11,    12,    13,
      21,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    21,    22,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,     8,     9,    10,    11,    12,
      13,    -1,    -1,    16,    17,    18,    19,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    17,    18,    19,     8,
       9,    10,    11,    12,    13,    -1,    39,    16,    17,    18,
      19,     8,     9,    10,    11,    12,    13,    -1,    39,    16,
      17,    18,    19,     8,     9,    10,    11,    12,    13,    -1,
      39,    16,    17,    18,    19,     8,     9,    10,    11,    12,
      13,    -1,    39,    16,    17,    18,    19,     9,    10,    11,
      12,    13,    -1,    -1,    39,    -1,    -1,    -1,    -1,     8,
       9,    10,    11,    12,    13,    14,    39,    16,    17,    18,
      19,     9,    10,    11,    12,    13,    25,    39,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    -1,
      21,    22,    23,    24,    37,    26,    27,    28,    29,    30,
      31,    -1,    21,    22,    23,    24,    37,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    35,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    35,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    21,    22,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    21,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    21,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      18,    19,    25,    43,    44,    45,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    59,    62,    65,    66,
      68,    69,     1,     8,    33,    34,    36,    41,     8,     3,
       4,     5,     6,     7,     8,    32,    36,    63,     1,    36,
      36,    36,     8,     0,    45,     1,     8,    32,     1,    63,
      63,    37,    63,    64,     8,     1,    36,    34,    36,    41,
      63,     1,    21,    22,    23,    24,    26,    27,    28,    29,
      30,    31,    32,     1,    37,    63,    63,     8,    48,    60,
      38,     1,    32,    33,    34,     1,    32,    35,    32,    37,
      40,    33,    48,    57,    58,    63,    37,    64,     8,    37,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      32,     1,    37,    37,    33,     8,    32,    48,    49,    67,
       1,    63,     3,    33,     1,    32,    63,    63,     8,    37,
      40,    35,    37,     1,    32,    38,    63,    33,    63,     8,
      39,    49,     1,    32,    35,    63,    32,     1,    15,    58,
      39,    46,    47,    63,    32,     1,    32,     1,    32,    48,
      39,    47,     8,    61,     1,    38,    20,    33,    37,    39,
      46,    63,     1,    38,    39,    39,    46,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    48,    48,    48,    49,    49,    49,
      50,    50,    50,    51,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    54,    55,    55,    55,    56,    56,    56,
      56,    56,    57,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    66,    67,    67,    68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       5,     5,     4,     6,     6,     7,     7,     4,     4,     3,
       2,     3,     2,     3,     5,     4,     5,    10,     9,     8,
       6,     3,     0,     1,     3,     2,     7,     6,     4,     3,
       3,     2,    11,    10,     9,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     5,     4,
       5,     4,     3,     2,     5,     1,     2,     3,     6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: top_level_list  */
#line 80 "parser.y"
                    { root = (yyvsp[0].node); }
#line 1325 "parser.tab.c"
    break;

  case 3: /* top_level_list: top_level_item  */
#line 85 "parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1331 "parser.tab.c"
    break;

  case 4: /* top_level_list: top_level_list top_level_item  */
#line 86 "parser.y"
                                        { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1337 "parser.tab.c"
    break;

  case 5: /* top_level_item: stmt  */
#line 90 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1343 "parser.tab.c"
    break;

  case 6: /* top_level_item: func_decl  */
#line 91 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1349 "parser.tab.c"
    break;

  case 7: /* top_level_item: struct_decl  */
#line 92 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1355 "parser.tab.c"
    break;

  case 8: /* stmt_list: stmt  */
#line 97 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1361 "parser.tab.c"
    break;

  case 9: /* stmt_list: stmt_list stmt  */
#line 98 "parser.y"
                            { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1367 "parser.tab.c"
    break;

  case 22: /* type: INT  */
#line 120 "parser.y"
              { (yyval.str) = "int"; }
#line 1373 "parser.tab.c"
    break;

  case 23: /* type: FLOAT  */
#line 121 "parser.y"
              { (yyval.str) = "float"; }
#line 1379 "parser.tab.c"
    break;

  case 24: /* type: CHAR_TYPE  */
#line 122 "parser.y"
                { (yyval.str) = "char"; }
#line 1385 "parser.tab.c"
    break;

  case 25: /* type: BOOL_TYPE  */
#line 123 "parser.y"
                { (yyval.str) = "bool"; }
#line 1391 "parser.tab.c"
    break;

  case 26: /* type: NOTHING  */
#line 124 "parser.y"
              { (yyval.str) = "nothing"; }
#line 1397 "parser.tab.c"
    break;

  case 27: /* decl: type ID ';'  */
#line 129 "parser.y"
                {
        (yyval.node) = createDecl((yyvsp[-2].str), (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1406 "parser.tab.c"
    break;

  case 28: /* decl: type ID error  */
#line 133 "parser.y"
                    {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid syntax after '%s %s'\n", (yyvsp[-2].str), (yyvsp[-1].str));
        fprintf(stderr, "   💡 Suggestions:\n");
        fprintf(stderr, "      • Declaration only:            '%s %s;'\n", (yyvsp[-2].str), (yyvsp[-1].str));
        fprintf(stderr, "      • Declaration with assignment: '%s %s = <expression>;'\n\n", (yyvsp[-2].str), (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1421 "parser.tab.c"
    break;

  case 29: /* decl: type error  */
#line 143 "parser.y"
                 {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected '<type> <identifier>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1433 "parser.tab.c"
    break;

  case 30: /* decAssign: type ID '=' expr ';'  */
#line 154 "parser.y"
                         {
        (yyval.node) = createDecAssignNode((yyvsp[-4].str), (yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1442 "parser.tab.c"
    break;

  case 31: /* decAssign: type ID '=' expr error  */
#line 158 "parser.y"
                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after declaration-assignment for '%s'\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1454 "parser.tab.c"
    break;

  case 32: /* decAssign: type ID '=' error  */
#line 165 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing expression after '='\n");
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1466 "parser.tab.c"
    break;

  case 33: /* array_decl: type ID '[' NUM ']' ';'  */
#line 175 "parser.y"
                            {
        (yyval.node) = createArrayDecl((yyvsp[-5].str), (yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1475 "parser.tab.c"
    break;

  case 34: /* array_decl: type ID '[' NUM ']' error  */
#line 179 "parser.y"
                                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array declaration for '%s'\n", (yyvsp[-4].str));
        free((yyvsp[-4].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1487 "parser.tab.c"
    break;

  case 35: /* array_assign: ID '[' expr ']' '=' expr ';'  */
#line 190 "parser.y"
                                 {
        (yyval.node) = createArrayAssign((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-6].str));
    }
#line 1496 "parser.tab.c"
    break;

  case 36: /* array_assign: ID '[' expr ']' '=' expr error  */
#line 194 "parser.y"
                                     {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after array assignment for '%s'\n", (yyvsp[-6].str));
        free((yyvsp[-6].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1508 "parser.tab.c"
    break;

  case 37: /* assign: ID '=' expr ';'  */
#line 205 "parser.y"
                    {
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1517 "parser.tab.c"
    break;

  case 38: /* assign: ID '=' expr error  */
#line 209 "parser.y"
                        {
        if (yychar == '=') {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Chained assignment is not supported: '%s = ... = ...'\n", (yyvsp[-3].str));
            fprintf(stderr, "   💡 Suggestion: Use two separate statements\n\n");
        } else {
            fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
            fprintf(stderr, "   Missing semicolon after assignment to '%s'\n", (yyvsp[-3].str));
            fprintf(stderr, "   💡 Suggestion: Add ';' after the expression\n\n");
        }
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1536 "parser.tab.c"
    break;

  case 39: /* assign: ID '=' error  */
#line 223 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment to '%s'\n", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1548 "parser.tab.c"
    break;

  case 40: /* assign: ID error  */
#line 230 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement for '%s'\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1560 "parser.tab.c"
    break;

  case 41: /* return_stmt: RETURN_KW expr ';'  */
#line 241 "parser.y"
                       {
        (yyval.node) = createReturn((yyvsp[-1].node));
    }
#line 1568 "parser.tab.c"
    break;

  case 42: /* return_stmt: RETURN_KW ';'  */
#line 244 "parser.y"
                    {
        /* void return — no expression */
        (yyval.node) = createReturn(NULL);
    }
#line 1577 "parser.tab.c"
    break;

  case 43: /* return_stmt: RETURN_KW expr error  */
#line 248 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after return statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the return expression\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1589 "parser.tab.c"
    break;

  case 44: /* call_stmt: ID '(' arg_list ')' ';'  */
#line 259 "parser.y"
                            {
        (yyval.node) = createFuncCall((yyvsp[-4].str), (yyvsp[-2].node));
    }
#line 1597 "parser.tab.c"
    break;

  case 45: /* call_stmt: ID '(' ')' ';'  */
#line 262 "parser.y"
                     {
        (yyval.node) = createFuncCall((yyvsp[-3].str), NULL);
    }
#line 1605 "parser.tab.c"
    break;

  case 46: /* call_stmt: ID '(' arg_list ')' error  */
#line 265 "parser.y"
                                {
        fprintf(stderr, "   Missing semicolon after function call to '%s'\n", (yyvsp[-4].str));
        yyerrok;
        (yyval.node) = createFuncCall((yyvsp[-4].str), (yyvsp[-2].node));
    }
#line 1615 "parser.tab.c"
    break;

  case 47: /* func_decl: FUNCTION ID '(' param_decl_list ')' RETURNS type '{' stmt_list '}'  */
#line 277 "parser.y"
                                                                       {
        (yyval.node) = createFuncDecl((yyvsp[-8].str), (yyvsp[-3].str), (yyvsp[-6].node), (yyvsp[-1].node));
        free((yyvsp[-8].str));
    }
#line 1624 "parser.tab.c"
    break;

  case 48: /* func_decl: FUNCTION ID '(' param_decl_list ')' RETURNS type '{' '}'  */
#line 281 "parser.y"
                                                               {
        /* Function with empty body */
        (yyval.node) = createFuncDecl((yyvsp[-7].str), (yyvsp[-2].str), (yyvsp[-5].node), NULL);
        free((yyvsp[-7].str));
    }
#line 1634 "parser.tab.c"
    break;

  case 49: /* func_decl: FUNCTION ID '(' param_decl_list ')' RETURNS type error  */
#line 286 "parser.y"
                                                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '{' to open function body for '%s'\n", (yyvsp[-6].str));
        free((yyvsp[-6].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1646 "parser.tab.c"
    break;

  case 50: /* func_decl: FUNCTION ID '(' param_decl_list ')' error  */
#line 293 "parser.y"
                                                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'returns <type>' after parameter list for '%s'\n", (yyvsp[-4].str));
        free((yyvsp[-4].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1658 "parser.tab.c"
    break;

  case 51: /* func_decl: FUNCTION ID error  */
#line 300 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '(' after function name '%s'\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1670 "parser.tab.c"
    break;

  case 52: /* param_decl_list: %empty  */
#line 311 "parser.y"
                                        { (yyval.node) = NULL; }
#line 1676 "parser.tab.c"
    break;

  case 53: /* param_decl_list: param_decl  */
#line 312 "parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 1682 "parser.tab.c"
    break;

  case 54: /* param_decl_list: param_decl_list ',' param_decl  */
#line 313 "parser.y"
                                        { (yyval.node) = createStmtList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1688 "parser.tab.c"
    break;

  case 55: /* param_decl: type ID  */
#line 317 "parser.y"
            {
        (yyval.node) = createParamDecl((yyvsp[-1].str), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1697 "parser.tab.c"
    break;

  case 56: /* while_stmt: WHILE '(' expr ')' '{' stmt_list '}'  */
#line 324 "parser.y"
                                       {
        (yyval.node) = createWhile((yyvsp[-4].node), (yyvsp[-1].node));
    }
#line 1705 "parser.tab.c"
    break;

  case 57: /* while_stmt: WHILE '(' expr ')' '{' '}'  */
#line 327 "parser.y"
                               {
        (yyval.node) = createWhile((yyvsp[-3].node), NULL);
    }
#line 1713 "parser.tab.c"
    break;

  case 58: /* for_init: type ID '=' expr  */
#line 348 "parser.y"
                       { (yyval.node) = createDecAssignNode((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 1719 "parser.tab.c"
    break;

  case 59: /* for_init: ID '=' expr  */
#line 349 "parser.y"
                       { (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));            free((yyvsp[-2].str)); }
#line 1725 "parser.tab.c"
    break;

  case 60: /* for_update: ID '=' expr  */
#line 353 "parser.y"
                  { (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 1731 "parser.tab.c"
    break;

  case 61: /* for_update: ID INC  */
#line 354 "parser.y"
                  { (yyval.node) = createAssign((yyvsp[-1].str), createBinOp('+', createVar((yyvsp[-1].str)), createNum(1))); free((yyvsp[-1].str)); }
#line 1737 "parser.tab.c"
    break;

  case 62: /* for_stmt: FOR '(' for_init ';' expr ';' for_update ')' '{' stmt_list '}'  */
#line 358 "parser.y"
                                                                   {
        (yyval.node) = createFor((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
    }
#line 1745 "parser.tab.c"
    break;

  case 63: /* for_stmt: FOR '(' for_init ';' expr ';' for_update ')' '{' '}'  */
#line 361 "parser.y"
                                                           {
        /* Empty body — body is NULL */
        (yyval.node) = createFor((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-3].node), NULL);
    }
#line 1754 "parser.tab.c"
    break;

  case 64: /* for_stmt: FOR '(' for_init ';' expr ';' for_update ')' error  */
#line 365 "parser.y"
                                                         {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected '{' to open for-loop body\n");
        fprintf(stderr, "   💡 Suggestion: for (init; condition; update) { ... }\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1766 "parser.tab.c"
    break;

  case 65: /* expr: NUM  */
#line 376 "parser.y"
                            { (yyval.node) = createNum((yyvsp[0].num)); }
#line 1772 "parser.tab.c"
    break;

  case 66: /* expr: FLOAT_LIT  */
#line 377 "parser.y"
                            { (yyval.node) = createFloatLit((yyvsp[0].fval)); }
#line 1778 "parser.tab.c"
    break;

  case 67: /* expr: CHAR_LIT  */
#line 378 "parser.y"
                            { (yyval.node) = createCharLit((yyvsp[0].num)); }
#line 1784 "parser.tab.c"
    break;

  case 68: /* expr: TRUE_LIT  */
#line 379 "parser.y"
                            { (yyval.node) = createBoolLit(1); }
#line 1790 "parser.tab.c"
    break;

  case 69: /* expr: FALSE_LIT  */
#line 380 "parser.y"
                            { (yyval.node) = createBoolLit(0); }
#line 1796 "parser.tab.c"
    break;

  case 70: /* expr: ID  */
#line 381 "parser.y"
                            { (yyval.node) = createVar((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1802 "parser.tab.c"
    break;

  case 71: /* expr: ID '(' arg_list ')'  */
#line 384 "parser.y"
                           { (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1808 "parser.tab.c"
    break;

  case 72: /* expr: ID '(' ')'  */
#line 385 "parser.y"
                           { (yyval.node) = createFuncCall((yyvsp[-2].str), NULL); free((yyvsp[-2].str)); }
#line 1814 "parser.tab.c"
    break;

  case 73: /* expr: ID '[' expr ']'  */
#line 386 "parser.y"
                             { (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node)); free((yyvsp[-3].str)); }
#line 1820 "parser.tab.c"
    break;

  case 74: /* expr: ID '.' ID  */
#line 387 "parser.y"
                             { (yyval.node) = createFieldAccess((yyvsp[-2].str), (yyvsp[0].str)); free((yyvsp[-2].str)); free((yyvsp[0].str)); }
#line 1826 "parser.tab.c"
    break;

  case 75: /* expr: expr '+' expr  */
#line 389 "parser.y"
                            { (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1832 "parser.tab.c"
    break;

  case 76: /* expr: expr '-' expr  */
#line 390 "parser.y"
                            { (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1838 "parser.tab.c"
    break;

  case 77: /* expr: expr '*' expr  */
#line 391 "parser.y"
                            { (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1844 "parser.tab.c"
    break;

  case 78: /* expr: expr '/' expr  */
#line 392 "parser.y"
                            { (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1850 "parser.tab.c"
    break;

  case 79: /* expr: expr '<' expr  */
#line 393 "parser.y"
                            { (yyval.node) = createBinOp('<', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1856 "parser.tab.c"
    break;

  case 80: /* expr: expr '>' expr  */
#line 394 "parser.y"
                            { (yyval.node) = createBinOp('>', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1862 "parser.tab.c"
    break;

  case 81: /* expr: expr LE expr  */
#line 395 "parser.y"
                            { (yyval.node) = createBinOp('L', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1868 "parser.tab.c"
    break;

  case 82: /* expr: expr GE expr  */
#line 396 "parser.y"
                            { (yyval.node) = createBinOp('G', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1874 "parser.tab.c"
    break;

  case 83: /* expr: expr EQ expr  */
#line 397 "parser.y"
                            { (yyval.node) = createBinOp('E', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1880 "parser.tab.c"
    break;

  case 84: /* expr: expr NE expr  */
#line 398 "parser.y"
                            { (yyval.node) = createBinOp('N', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1886 "parser.tab.c"
    break;

  case 85: /* expr: '(' expr ')'  */
#line 399 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1892 "parser.tab.c"
    break;

  case 86: /* arg_list: expr  */
#line 404 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1898 "parser.tab.c"
    break;

  case 87: /* arg_list: arg_list ',' expr  */
#line 405 "parser.y"
                            { (yyval.node) = createStmtList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1904 "parser.tab.c"
    break;

  case 88: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 410 "parser.y"
                           {
        (yyval.node) = createPrint((yyvsp[-2].node));
    }
#line 1912 "parser.tab.c"
    break;

  case 89: /* print_stmt: PRINT '(' ')' ';'  */
#line 413 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   print() requires an expression argument\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<variable or expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1924 "parser.tab.c"
    break;

  case 90: /* print_stmt: PRINT '(' expr ')' error  */
#line 420 "parser.y"
                               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1935 "parser.tab.c"
    break;

  case 91: /* print_stmt: PRINT '(' expr error  */
#line 426 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1946 "parser.tab.c"
    break;

  case 92: /* print_stmt: PRINT '(' error  */
#line 432 "parser.y"
                      {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1957 "parser.tab.c"
    break;

  case 93: /* print_stmt: PRINT error  */
#line 438 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis after 'print'\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1968 "parser.tab.c"
    break;

  case 94: /* struct_decl: STRUCT ID '{' field_decl_list '}'  */
#line 452 "parser.y"
                                      {
        (yyval.node) = createStructDecl((yyvsp[-3].str), (yyvsp[-1].node));
    }
#line 1976 "parser.tab.c"
    break;

  case 95: /* field_decl_list: decl  */
#line 458 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1982 "parser.tab.c"
    break;

  case 96: /* field_decl_list: field_decl_list decl  */
#line 459 "parser.y"
                                { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1988 "parser.tab.c"
    break;

  case 97: /* struct_var: ID ID ';'  */
#line 465 "parser.y"
              {
        (yyval.node) = createStructVar((yyvsp[-2].str), (yyvsp[-1].str));
    }
#line 1996 "parser.tab.c"
    break;

  case 98: /* field_assign: ID '.' ID '=' expr ';'  */
#line 473 "parser.y"
                           {
        (yyval.node) = createFieldAssign((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node));
    }
#line 2004 "parser.tab.c"
    break;


#line 2008 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 478 "parser.y"


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
