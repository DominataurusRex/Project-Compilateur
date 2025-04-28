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
#line 1 "src/tpc.y"

/* exp.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
int yylex();
void yyerror(char *);
Node* root = NULL;
extern char *yytext;
extern char* file_name;
extern int nb_error;
Node* tree;

#line 87 "obj/tpc.tab.c"

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

#include "tpc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CHARACTER = 3,                  /* CHARACTER  */
  YYSYMBOL_ADDSUB = 4,                     /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 5,                    /* DIVSTAR  */
  YYSYMBOL_NUM = 6,                        /* NUM  */
  YYSYMBOL_IDENT = 7,                      /* IDENT  */
  YYSYMBOL_TYPE = 8,                       /* TYPE  */
  YYSYMBOL_ORDER = 9,                      /* ORDER  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_VOID = 17,                      /* VOID  */
  YYSYMBOL_STATIC = 18,                    /* STATIC  */
  YYSYMBOL_19_ = 19,                       /* ';'  */
  YYSYMBOL_20_ = 20,                       /* ','  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '}'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_Prog = 28,                      /* Prog  */
  YYSYMBOL_DeclVarsExt = 29,               /* DeclVarsExt  */
  YYSYMBOL_Declarateurs = 30,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 31,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 32,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 33,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 34,                /* Parametres  */
  YYSYMBOL_ListTypVar = 35,                /* ListTypVar  */
  YYSYMBOL_Corps = 36,                     /* Corps  */
  YYSYMBOL_DeclVarsInt = 37,               /* DeclVarsInt  */
  YYSYMBOL_SuiteInstr = 38,                /* SuiteInstr  */
  YYSYMBOL_Instr = 39,                     /* Instr  */
  YYSYMBOL_Exp = 40,                       /* Exp  */
  YYSYMBOL_TB = 41,                        /* TB  */
  YYSYMBOL_FB = 42,                        /* FB  */
  YYSYMBOL_M = 43,                         /* M  */
  YYSYMBOL_E = 44,                         /* E  */
  YYSYMBOL_T = 45,                         /* T  */
  YYSYMBOL_F = 46,                         /* F  */
  YYSYMBOL_Arguments = 47,                 /* Arguments  */
  YYSYMBOL_ListExp = 48                    /* ListExp  */
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
typedef yytype_int8 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      21,    22,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    35,    35,    44,    52,    56,    64,    73,    77,    80,
      87,    99,   112,   117,   120,   132,   144,   152,   159,   166,
     169,   177,   180,   187,   198,   214,   225,   232,   239,   245,
     246,   248,   253,   255,   260,   262,   268,   270,   276,   278,
     284,   286,   292,   294,   299,   303,   304,   310,   316,   322,
     331,   332,   335,   339
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
  "\"end of file\"", "error", "\"invalid token\"", "CHARACTER", "ADDSUB",
  "DIVSTAR", "NUM", "IDENT", "TYPE", "ORDER", "EQ", "OR", "AND", "WHILE",
  "IF", "ELSE", "RETURN", "VOID", "STATIC", "';'", "','", "'('", "')'",
  "'{'", "'}'", "'='", "'!'", "$accept", "Prog", "DeclVarsExt",
  "Declarateurs", "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres",
  "ListTypVar", "Corps", "DeclVarsInt", "SuiteInstr", "Instr", "Exp", "TB",
  "FB", "M", "E", "T", "F", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-64)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -64,     2,    32,   -64,    14,    17,    54,   -64,    16,    35,
      53,    45,    61,   -64,   -64,   -64,    57,   -64,    73,    57,
      35,    28,    74,   -64,    60,    63,   -64,    62,    78,    79,
      18,   -64,   -64,    80,   -64,   -64,    56,    78,    -2,    65,
      68,     1,   -64,   -64,   -64,   -64,    83,   -64,    59,     9,
       9,     9,     9,   -64,     9,   -64,    70,   -64,     9,     9,
       7,    81,    82,    85,    91,    92,   -64,    31,   -64,   -64,
      87,    77,    76,    58,    -8,    42,   -64,     9,    48,   -64,
       9,   -64,     9,     9,     9,     9,     9,   -64,    84,     9,
     -64,    44,    44,    86,   -64,    81,    82,    85,    91,    92,
     -64,   -64,    87,   -64,    89,   -64,    44,   -64
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,     8,     0,     6,
       0,     0,     0,     7,    19,     9,     0,     3,     0,     0,
       0,    21,     0,    12,     0,    13,     5,     0,     0,     0,
       0,    15,    10,     0,    11,     6,     0,     0,     0,     0,
       0,     0,    30,    21,    16,    20,     0,    17,     0,    51,
       0,     0,     0,    47,     0,    46,    48,    28,     0,     0,
       0,    32,    34,    36,    38,    40,    42,     0,    14,    18,
      53,     0,    50,     0,     0,     0,    43,    51,     0,    44,
       0,    27,     0,     0,     0,     0,     0,    29,     0,     0,
      22,     0,     0,     0,    45,    31,    33,    35,    37,    39,
      41,    26,    52,    25,    23,    49,     0,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -64,   -64,    24,   -64,    94,   -64,    88,   -64,   -64,
     -64,    66,   -63,   -41,    21,    20,    22,    26,    27,   -53,
      29,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,     6,     7,     8,    24,    25,    15,
      21,    30,    45,    70,    61,    62,    63,    64,    65,    66,
      71,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      60,    76,     3,    80,    53,    54,    79,    55,    56,    73,
      74,    75,    53,    54,    91,    55,    56,    78,    80,    49,
      57,     9,    58,    50,    11,    38,    81,    59,   103,   104,
      58,    39,    40,   100,    41,    59,    28,    42,    38,    14,
       4,    43,    44,   107,    39,    40,    29,    41,   102,     5,
      42,    38,    36,    80,    43,    87,    16,    39,    40,    80,
      41,    48,    12,    42,    92,    22,    19,    43,    20,    80,
      94,     5,    17,    18,    23,    47,    18,    90,    69,    18,
      26,    31,    32,    33,    34,    35,    51,    37,    46,    52,
      68,    77,    83,    82,    84,    85,    89,    86,    80,    88,
      13,    95,    96,   101,   106,    97,    93,    27,   105,    67,
      98,     0,    99
};

static const yytype_int8 yycheck[] =
{
      41,    54,     0,    11,     3,     4,    59,     6,     7,    50,
      51,    52,     3,     4,    22,     6,     7,    58,    11,    21,
      19,     7,    21,    25,     7,     7,    19,    26,    91,    92,
      21,    13,    14,    86,    16,    26,     8,    19,     7,    23,
       8,    23,    24,   106,    13,    14,    18,    16,    89,    17,
      19,     7,    28,    11,    23,    24,    21,    13,    14,    11,
      16,    37,     8,    19,    22,     8,    21,    23,     7,    11,
      22,    17,    19,    20,    17,    19,    20,    19,    19,    20,
       7,     7,    22,    20,    22,     7,    21,     8,     8,    21,
       7,    21,    10,    12,     9,     4,    20,     5,    11,    22,
       6,    80,    82,    19,    15,    83,    77,    19,    22,    43,
      84,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     8,    17,    31,    32,    33,     7,
      30,     7,     8,    32,    23,    36,    21,    19,    20,    21,
       7,    37,     8,    17,    34,    35,     7,    34,     8,    18,
      38,     7,    22,    20,    22,     7,    30,     8,     7,    13,
      14,    16,    19,    23,    24,    39,     8,    19,    30,    21,
      25,    21,    21,     3,     4,     6,     7,    19,    21,    26,
      40,    41,    42,    43,    44,    45,    46,    38,     7,    19,
      40,    47,    48,    40,    40,    40,    46,    21,    40,    46,
      11,    19,    12,    10,     9,     4,     5,    24,    22,    20,
      19,    22,    22,    47,    22,    41,    42,    43,    44,    45,
      46,    19,    40,    39,    39,    22,    15,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    29,    30,    30,    31,    31,    32,
      33,    33,    34,    34,    35,    35,    36,    37,    37,    37,
      38,    38,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     1,     2,     1,     2,
       5,     5,     1,     1,     4,     2,     4,     4,     5,     0,
       2,     0,     4,     5,     7,     5,     5,     3,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     2,     3,     1,     1,     1,     4,
       1,     0,     3,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: DeclVarsExt DeclFoncts  */
#line 35 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Prog);
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                    root = (yyval.node);
}
#line 1307 "obj/tpc.tab.c"
    break;

  case 3: /* DeclVarsExt: DeclVarsExt TYPE Declarateurs ';'  */
#line 44 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-3].node);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup((yyvsp[-2].ident));
                                                    addChild((yyval.node), type);
                                                    addChild(type, (yyvsp[-1].node));
}
#line 1319 "obj/tpc.tab.c"
    break;

  case 4: /* DeclVarsExt: %empty  */
#line 52 "src/tpc.y"
                                                    {(yyval.node) = makeNode(DeclVars);}
#line 1325 "obj/tpc.tab.c"
    break;

  case 5: /* Declarateurs: Declarateurs ',' IDENT  */
#line 56 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-2].node);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup((yyvsp[0].ident));
                                                    ident->line = (yylsp[0]).first_line;
                                                    ident->column = (yylsp[0]).first_column;
                                                    addSibling((yyval.node), ident);
}
#line 1338 "obj/tpc.tab.c"
    break;

  case 6: /* Declarateurs: IDENT  */
#line 64 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->ident = strdup((yyvsp[0].ident));
                                                    (yyval.node)->line = (yylsp[0]).first_line;
                                                    (yyval.node)->column = (yylsp[0]).first_column;
}
#line 1349 "obj/tpc.tab.c"
    break;

  case 7: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 73 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-1].node);
                                                    addSibling((yyval.node), (yyvsp[0].node));
}
#line 1358 "obj/tpc.tab.c"
    break;

  case 8: /* DeclFoncts: DeclFonct  */
#line 77 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1364 "obj/tpc.tab.c"
    break;

  case 9: /* DeclFonct: EnTeteFonct Corps  */
#line 80 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(DeclFonct);
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1374 "obj/tpc.tab.c"
    break;

  case 10: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 87 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(EnTeteFonct);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup((yyvsp[-4].ident));
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup((yyvsp[-3].ident));
                                                    ident->line = (yylsp[-3]).first_line;
                                                    ident->column = (yylsp[-3]).first_column;
                                                    addChild((yyval.node), type);
                                                    addChild((yyval.node), ident);
                                                    addChild((yyval.node), (yyvsp[-1].node));
}
#line 1391 "obj/tpc.tab.c"
    break;

  case 11: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 99 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(EnTeteFonct);
                                                    Node* type = makeNode(Void);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup((yyvsp[-3].ident));
                                                    ident->line = (yylsp[-3]).first_line;
                                                    ident->column = (yylsp[-3]).first_column;
                                                    addChild((yyval.node), type);
                                                    addChild((yyval.node), ident);
                                                    addChild((yyval.node), (yyvsp[-1].node));
}
#line 1407 "obj/tpc.tab.c"
    break;

  case 12: /* Parametres: VOID  */
#line 112 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Var);
                                                    Node* vide = makeNode(Void);
                                                    addChild((yyval.node), vide);
}
#line 1417 "obj/tpc.tab.c"
    break;

  case 13: /* Parametres: ListTypVar  */
#line 117 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1423 "obj/tpc.tab.c"
    break;

  case 14: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 120 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Var);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup((yyvsp[-1].ident));
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup((yyvsp[0].ident));
                                                    ident->line = (yylsp[0]).first_line;
                                                    ident->column = (yylsp[0]).first_column;
                                                    addChild((yyval.node), type);
                                                    addChild((yyval.node), ident);
                                                    addSibling((yyval.node), (yyvsp[-3].node));
}
#line 1440 "obj/tpc.tab.c"
    break;

  case 15: /* ListTypVar: TYPE IDENT  */
#line 132 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Var);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup((yyvsp[-1].ident));
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup((yyvsp[0].ident));
                                                    ident->line = (yylsp[0]).first_line;
                                                    ident->column = (yylsp[0]).first_column;
                                                    addChild((yyval.node), type);
                                                    addChild((yyval.node), ident);
}
#line 1456 "obj/tpc.tab.c"
    break;

  case 16: /* Corps: '{' DeclVarsInt SuiteInstr '}'  */
#line 144 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-2].node);
                                                    Node* instr = makeNode(Instr);
                                                    addSibling((yyval.node), instr);
                                                    addChild(instr, (yyvsp[-1].node));
}
#line 1467 "obj/tpc.tab.c"
    break;

  case 17: /* DeclVarsInt: DeclVarsInt TYPE Declarateurs ';'  */
#line 152 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-3].node);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup((yyvsp[-2].ident));
                                                    addChild((yyval.node), type);
                                                    addChild(type, (yyvsp[-1].node));
}
#line 1479 "obj/tpc.tab.c"
    break;

  case 18: /* DeclVarsInt: DeclVarsInt STATIC TYPE Declarateurs ';'  */
#line 159 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-4].node);
                                                    Node* type = makeNode(StaticType);
                                                    type->ident = strdup((yyvsp[-2].ident));
                                                    addChild((yyval.node), type);
                                                    addChild(type, (yyvsp[-1].node));
}
#line 1491 "obj/tpc.tab.c"
    break;

  case 19: /* DeclVarsInt: %empty  */
#line 166 "src/tpc.y"
                                                    {(yyval.node) = makeNode(DeclVars);}
#line 1497 "obj/tpc.tab.c"
    break;

  case 20: /* SuiteInstr: SuiteInstr Instr  */
#line 169 "src/tpc.y"
                                                    {
                                                    if ((yyvsp[-1].node) != NULL) {
                                                        (yyval.node) = (yyvsp[-1].node);
                                                        addSibling((yyval.node), (yyvsp[0].node));
                                                    } else {
                                                        (yyval.node) = (yyvsp[0].node);
                                                    }
}
#line 1510 "obj/tpc.tab.c"
    break;

  case 21: /* SuiteInstr: %empty  */
#line 177 "src/tpc.y"
                                                    {(yyval.node) = NULL;}
#line 1516 "obj/tpc.tab.c"
    break;

  case 22: /* Instr: IDENT '=' Exp ';'  */
#line 180 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Affect);
                                                    (yyval.node)->ident = strdup((yyvsp[-3].ident));
                                                    (yyval.node)->line = (yylsp[-3]).first_line;
                                                    (yyval.node)->column = (yylsp[-3]).first_column;
                                                    addChild((yyval.node), (yyvsp[-1].node));
}
#line 1528 "obj/tpc.tab.c"
    break;

  case 23: /* Instr: IF '(' Exp ')' Instr  */
#line 187 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(If);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, (yyvsp[-2].node));
                                                    addChild((yyval.node), cond);
                                                    if ((yyvsp[0].node) != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, (yyvsp[0].node));
                                                        addChild((yyval.node), doo);
                                                    }
}
#line 1544 "obj/tpc.tab.c"
    break;

  case 24: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 198 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(If);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, (yyvsp[-4].node));
                                                    addChild((yyval.node), cond);
                                                    if ((yyvsp[-2].node) != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, (yyvsp[-2].node));
                                                        addChild((yyval.node), doo);
                                                    }
                                                    if ((yyvsp[0].node) != NULL) {
                                                        Node* elsee = makeNode(Else);
                                                        addChild(elsee, (yyvsp[0].node));
                                                        addChild((yyval.node), elsee);
                                                    }
}
#line 1565 "obj/tpc.tab.c"
    break;

  case 25: /* Instr: WHILE '(' Exp ')' Instr  */
#line 214 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(While);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, (yyvsp[-2].node));
                                                    addChild((yyval.node), cond);
                                                    if ((yyvsp[0].node) != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, (yyvsp[0].node));
                                                        addChild((yyval.node), doo);
                                                    }
}
#line 1581 "obj/tpc.tab.c"
    break;

  case 26: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 225 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Funct);
                                                    (yyval.node)->ident = strdup((yyvsp[-4].ident));
                                                    (yyval.node)->line = (yylsp[-4]).first_line;
                                                    (yyval.node)->column = (yylsp[-4]).first_column;
                                                    addChild((yyval.node), (yyvsp[-2].node));
}
#line 1593 "obj/tpc.tab.c"
    break;

  case 27: /* Instr: RETURN Exp ';'  */
#line 232 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Return);
                                                    (yyval.node)->ident = strdup("return");
                                                    (yyval.node)->line =(yylsp[-2]).first_line;
                                                    (yyval.node)->column = (yylsp[-2]).first_column;
                                                    addChild((yyval.node), (yyvsp[-1].node));
}
#line 1605 "obj/tpc.tab.c"
    break;

  case 28: /* Instr: RETURN ';'  */
#line 239 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Return);
                                                    (yyval.node)->ident = strdup("return");
                                                    (yyval.node)->line =(yylsp[-1]).first_line;
                                                    (yyval.node)->column = (yylsp[-1]).first_column;
}
#line 1616 "obj/tpc.tab.c"
    break;

  case 29: /* Instr: '{' SuiteInstr '}'  */
#line 245 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[-1].node);}
#line 1622 "obj/tpc.tab.c"
    break;

  case 30: /* Instr: ';'  */
#line 246 "src/tpc.y"
                                                    {(yyval.node) = NULL;}
#line 1628 "obj/tpc.tab.c"
    break;

  case 31: /* Exp: Exp OR TB  */
#line 248 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Or);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1638 "obj/tpc.tab.c"
    break;

  case 32: /* Exp: TB  */
#line 253 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1644 "obj/tpc.tab.c"
    break;

  case 33: /* TB: TB AND FB  */
#line 255 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(And);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1654 "obj/tpc.tab.c"
    break;

  case 34: /* TB: FB  */
#line 260 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1660 "obj/tpc.tab.c"
    break;

  case 35: /* FB: FB EQ M  */
#line 262 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Equal);
                                                    (yyval.node)->ident = strdup((yyvsp[-1].ident));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1671 "obj/tpc.tab.c"
    break;

  case 36: /* FB: M  */
#line 268 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1677 "obj/tpc.tab.c"
    break;

  case 37: /* M: M ORDER E  */
#line 270 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Order);
                                                    (yyval.node)->ident = strdup((yyvsp[-1].ident));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1688 "obj/tpc.tab.c"
    break;

  case 38: /* M: E  */
#line 276 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1694 "obj/tpc.tab.c"
    break;

  case 39: /* E: E ADDSUB T  */
#line 278 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(BiOperator);
                                                    (yyval.node)->byte = (yyvsp[-1].byte);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1705 "obj/tpc.tab.c"
    break;

  case 40: /* E: T  */
#line 284 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1711 "obj/tpc.tab.c"
    break;

  case 41: /* T: T DIVSTAR F  */
#line 286 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(BiOperator);
                                                    (yyval.node)->byte = (yyvsp[-1].byte);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1722 "obj/tpc.tab.c"
    break;

  case 42: /* T: F  */
#line 292 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1728 "obj/tpc.tab.c"
    break;

  case 43: /* F: ADDSUB F  */
#line 294 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(UnOperator);
                                                    (yyval.node)->byte = (yyvsp[-1].byte);
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1738 "obj/tpc.tab.c"
    break;

  case 44: /* F: '!' F  */
#line 299 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Negate);
                                                    addChild((yyval.node), (yyvsp[0].node));
}
#line 1747 "obj/tpc.tab.c"
    break;

  case 45: /* F: '(' Exp ')'  */
#line 303 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[-1].node);}
#line 1753 "obj/tpc.tab.c"
    break;

  case 46: /* F: NUM  */
#line 304 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Num);
                                                    (yyval.node)->num = (yyvsp[0].num);
                                                    (yyval.node)->line = (yylsp[0]).first_line;
                                                    (yyval.node)->column = (yylsp[0]).first_column;
}
#line 1764 "obj/tpc.tab.c"
    break;

  case 47: /* F: CHARACTER  */
#line 310 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Char);
                                                    (yyval.node)->byte = (yyvsp[0].byte);
                                                    (yyval.node)->line = (yylsp[0]).first_line;
                                                    (yyval.node)->column = (yylsp[0]).first_column;
}
#line 1775 "obj/tpc.tab.c"
    break;

  case 48: /* F: IDENT  */
#line 316 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->ident = strdup((yyvsp[0].ident));
                                                    (yyval.node)->line = (yylsp[0]).first_line;
                                                    (yyval.node)->column = (yylsp[0]).first_column;
}
#line 1786 "obj/tpc.tab.c"
    break;

  case 49: /* F: IDENT '(' Arguments ')'  */
#line 322 "src/tpc.y"
                                                    {
                                                    (yyval.node) = makeNode(Funct);
                                                    (yyval.node)->ident = strdup((yyvsp[-3].ident));
                                                    (yyval.node)->line = (yylsp[-3]).first_line;
                                                    (yyval.node)->column = (yylsp[-3]).first_column;
                                                    addChild((yyval.node), (yyvsp[-1].node));
}
#line 1798 "obj/tpc.tab.c"
    break;

  case 50: /* Arguments: ListExp  */
#line 331 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1804 "obj/tpc.tab.c"
    break;

  case 51: /* Arguments: %empty  */
#line 332 "src/tpc.y"
                                                    {(yyval.node) = makeNode(Void);}
#line 1810 "obj/tpc.tab.c"
    break;

  case 52: /* ListExp: ListExp ',' Exp  */
#line 335 "src/tpc.y"
                                                    {
                                                    (yyval.node) = (yyvsp[-2].node);
                                                    addSibling((yyval.node), (yyvsp[0].node));
}
#line 1819 "obj/tpc.tab.c"
    break;

  case 53: /* ListExp: Exp  */
#line 339 "src/tpc.y"
                                                    {(yyval.node) = (yyvsp[0].node);}
#line 1825 "obj/tpc.tab.c"
    break;


#line 1829 "obj/tpc.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 341 "src/tpc.y"


void yyerror(char* msg) {
    nb_error++;
    fprintf(
        stderr,
        "\033[1m%s:%d:%d: \033[31;1merror:\033[0m %s \033[1m‘%s’\033[0m\n",
        file_name,
        yylloc.first_line,
        yylloc.first_column,
        msg,
        yytext
    );
}
