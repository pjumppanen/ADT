/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:339  */

/*
/*
 * cpp.y
 *
 *  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
 *  ORGANISATION (CSIRO), Australia.
 *  All rights reserved.
 *
 *  This file is part of ADT.  The full ADT copyright notice, including
 *  terms governing use, modification, and redistribution, is contained in
 *  the file COPYING. COPYING can be found at the root of the source code
 *  distribution tree;
 *
 * Simplified C++ Grammar Summary
 *
 * Based on the Annex A of ISO/IEC 14882:1998 (The C++ Standard).
 *
 *Source: http://linuxsoftware.co.nz/cppgrammar.html
 */

#include <stdio.h>
#include "lexer.h"
#include "adtcpp.hpp"
#include "adtutils.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   cppType

const char* adtCpp_pLastFunctionName        = 0;
const char* adtCpp_pLastFunctionComment     = 0;
int         adtCpp_pLastFunctionIsObj       = 0;
int         adtCpp_pLastFunctionIsQualified = 0;
int         adtCpp_pLastFunctionIsVirtual   = 0;


#line 111 "..\\src\\cpp_y.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "cpp_y.h".  */
#ifndef YY_YY_SRC_CPP_Y_H_INCLUDED
# define YY_YY_SRC_CPP_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OR_EQ = 258,
    MOD = 259,
    PROD = 260,
    XOR = 261,
    DOT = 262,
    XOR_EQ = 263,
    LT_EQ = 264,
    NEQ = 265,
    ELLIPSIS = 266,
    LBRACKET = 267,
    RBRACKET = 268,
    LSBRACKET = 269,
    RSBRACKET = 270,
    LSQBRACKET = 271,
    RSQBRACKET = 272,
    AND_EQ = 273,
    LT = 274,
    GT = 275,
    DECR = 276,
    INCR = 277,
    PLUS = 278,
    MINUS = 279,
    SHR_EQ = 280,
    SHL_EQ = 281,
    GT_EQ = 282,
    COLON = 283,
    COMMA = 284,
    LAND = 285,
    LOR = 286,
    LNOT = 287,
    NOT = 288,
    SEMICOLON = 289,
    LITERAL = 290,
    AND = 291,
    EQEQ = 292,
    SHR = 293,
    M_EQ = 294,
    P_EQ = 295,
    SHL = 296,
    QUESTION = 297,
    MOD_EQ = 298,
    DIV_EQ = 299,
    DIV = 300,
    PROD_EQ = 301,
    EQ = 302,
    OR = 303,
    STRING_LITERAL = 304,
    TYPENAME = 305,
    DOUBLE = 306,
    FLOAT = 307,
    MUTABLE = 308,
    PUBLIC = 309,
    PRIVATE = 310,
    PROTECTED = 311,
    EXTERN = 312,
    DEFAULT = 313,
    WHILE = 314,
    SWITCH = 315,
    ENUM = 316,
    RETURN = 317,
    UNSIGNED = 318,
    ASM = 319,
    DO = 320,
    AUTO = 321,
    CONTINUE = 322,
    BOOL = 323,
    WCHAR_T = 324,
    EXPLICIT = 325,
    IF = 326,
    SIZEOF = 327,
    UNION = 328,
    CHAR = 329,
    CLASS = 330,
    USING = 331,
    VOLATILE = 332,
    SIGNED = 333,
    CONST = 334,
    LONG = 335,
    STATIC = 336,
    INT = 337,
    ELSE = 338,
    SHORT = 339,
    NAMESPACE = 340,
    REGISTER = 341,
    TYPEDEF = 342,
    FRIEND = 343,
    FOR = 344,
    GOTO = 345,
    VIRTUAL = 346,
    INLINE = 347,
    CASE = 348,
    VOID = 349,
    STRUCT = 350,
    BREAK = 351,
    IDENTIFIER = 352,
    QUALIFIED_IDENTIFIER = 353,
    DTOR = 354,
    QUALIFIED_DTOR = 355,
    OBJ_IDENTIFIER = 356,
    QUALIFIED_OBJ_IDENTIFIER = 357,
    SINGLELINE_COMMENT = 358,
    MULTILINE_COMMENT = 359,
    EMBEDDED_COMMANDS = 360,
    ADDVARIABLES = 361
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_CPP_Y_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 269 "..\\src\\cpp_y.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  122
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  368
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  592

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    72,    72,    81,    89,    93,    99,   103,   110,   114,
     118,   122,   126,   130,   137,   141,   148,   152,   163,   167,
     171,   175,   179,   183,   187,   191,   195,   199,   203,   207,
     214,   218,   225,   229,   233,   237,   241,   248,   252,   256,
     260,   267,   271,   275,   279,   286,   290,   294,   301,   305,
     309,   316,   320,   324,   328,   332,   339,   343,   347,   354,
     358,   365,   369,   376,   380,   387,   391,   398,   402,   409,
     413,   420,   424,   431,   435,   439,   443,   447,   451,   455,
     459,   463,   467,   471,   478,   482,   489,   496,   500,   504,
     508,   512,   516,   520,   527,   531,   535,   542,   546,   553,
     557,   564,   568,   579,   583,   587,   594,   598,   602,   606,
     610,   614,   621,   625,   632,   636,   640,   644,   648,   655,
     662,   666,   673,   677,   681,   685,   689,   696,   700,   704,
     708,   712,   719,   723,   727,   731,   743,   747,   762,   766,
     770,   774,   778,   782,   786,   790,   794,   798,   802,   809,
     813,   820,   826,   832,   838,   844,   853,   859,   865,   869,
     876,   880,   884,   898,   902,   906,   910,   914,   918,   922,
     926,   930,   934,   938,   942,   946,   950,   954,   958,   962,
     966,   970,   974,   978,   982,   986,   990,   994,   998,  1002,
    1006,  1010,  1014,  1018,  1022,  1026,  1030,  1034,  1038,  1042,
    1046,  1050,  1054,  1058,  1062,  1066,  1070,  1074,  1078,  1082,
    1086,  1090,  1094,  1098,  1102,  1106,  1110,  1114,  1118,  1122,
    1126,  1130,  1134,  1138,  1142,  1149,  1153,  1160,  1164,  1171,
    1177,  1184,  1193,  1200,  1206,  1215,  1221,  1230,  1237,  1241,
    1245,  1252,  1256,  1263,  1267,  1276,  1280,  1287,  1291,  1295,
    1299,  1303,  1307,  1337,  1344,  1354,  1364,  1374,  1384,  1394,
    1404,  1417,  1423,  1429,  1435,  1441,  1447,  1456,  1460,  1464,
    1468,  1475,  1479,  1483,  1487,  1494,  1498,  1505,  1509,  1513,
    1517,  1521,  1525,  1532,  1536,  1540,  1544,  1548,  1552,  1556,
    1563,  1567,  1571,  1575,  1579,  1583,  1587,  1597,  1604,  1611,
    1617,  1626,  1630,  1637,  1641,  1645,  1649,  1656,  1660,  1667,
    1674,  1681,  1688,  1695,  1702,  1709,  1716,  1723,  1730,  1737,
    1744,  1754,  1758,  1765,  1769,  1773,  1777,  1781,  1785,  1789,
    1793,  1797,  1804,  1808,  1815,  1819,  1826,  1830,  1837,  1843,
    1849,  1855,  1861,  1867,  1873,  1879,  1885,  1891,  1897,  1903,
    1909,  1915,  1921,  1927,  1933,  1939,  1945,  1951,  1957,  1963,
    1972,  1979,  1983,  1990,  1994,  2001,  2005,  2009,  2013
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OR_EQ", "MOD", "PROD", "XOR", "DOT",
  "XOR_EQ", "LT_EQ", "NEQ", "ELLIPSIS", "LBRACKET", "RBRACKET",
  "LSBRACKET", "RSBRACKET", "LSQBRACKET", "RSQBRACKET", "AND_EQ", "LT",
  "GT", "DECR", "INCR", "PLUS", "MINUS", "SHR_EQ", "SHL_EQ", "GT_EQ",
  "COLON", "COMMA", "LAND", "LOR", "LNOT", "NOT", "SEMICOLON", "LITERAL",
  "AND", "EQEQ", "SHR", "M_EQ", "P_EQ", "SHL", "QUESTION", "MOD_EQ",
  "DIV_EQ", "DIV", "PROD_EQ", "EQ", "OR", "STRING_LITERAL", "TYPENAME",
  "DOUBLE", "FLOAT", "MUTABLE", "PUBLIC", "PRIVATE", "PROTECTED", "EXTERN",
  "DEFAULT", "WHILE", "SWITCH", "ENUM", "RETURN", "UNSIGNED", "ASM", "DO",
  "AUTO", "CONTINUE", "BOOL", "WCHAR_T", "EXPLICIT", "IF", "SIZEOF",
  "UNION", "CHAR", "CLASS", "USING", "VOLATILE", "SIGNED", "CONST", "LONG",
  "STATIC", "INT", "ELSE", "SHORT", "NAMESPACE", "REGISTER", "TYPEDEF",
  "FRIEND", "FOR", "GOTO", "VIRTUAL", "INLINE", "CASE", "VOID", "STRUCT",
  "BREAK", "IDENTIFIER", "QUALIFIED_IDENTIFIER", "DTOR", "QUALIFIED_DTOR",
  "OBJ_IDENTIFIER", "QUALIFIED_OBJ_IDENTIFIER", "SINGLELINE_COMMENT",
  "MULTILINE_COMMENT", "EMBEDDED_COMMANDS", "ADDVARIABLES", "$accept",
  "translation_unit", "macro", "simple_declaration_list",
  "postfix_expression", "expression_list", "directed_expression",
  "declarator_expression", "declarator_expression_dims",
  "unary_expression", "unary_operator", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "statement", "labeled_statement",
  "expression_statement", "compound_statement", "statement_seq",
  "selection_statement", "iteration_statement", "for_init_statement",
  "jump_statement", "declaration_statement", "declaration_seq",
  "declaration", "block_declaration", "simple_declaration",
  "decl_modifier", "decl_modifier_list", "class_specifier",
  "enum_specifier_name", "enum_specifier", "simple_type_specifier",
  "enumerator_list", "enumerator_definition", "namespace_definition",
  "namespace_identifier", "namespace_alias_definition",
  "using_declaration", "using_directive", "asm_definition",
  "linkage_specification", "init_declarator_list", "init_declarator",
  "declarator", "var_declarator", "fn_declarator", "fn_declarator_begin",
  "fn_declarator_end", "declarator_dims", "parameter_declaration_clause",
  "parameter_declaration_list", "parameter_declaration",
  "function_definition", "class_function_definition", "function_body",
  "function_body_start", "function_body_end", "initializer",
  "initializer_clause", "initializer_list", "class_key",
  "member_specification", "member_declaration", "member_declarator_list",
  "member_declarator", "base_specifier_list", "base_specifier",
  "ctor_initializer", "mem_initializer_list", "mem_initializer",
  "mem_initializer_id", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361
};
# endif

#define YYPACT_NINF -383

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-383)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1887,  -383,    94,   101,  -383,   -13,   260,    49,    34,  -383,
     162,   165,  -383,   298,   191,   317,    92,  -383,    52,  -383,
     134,  -383,   218,     2,    11,  -383,  2040,  -383,   -38,  -383,
     224,   319,   256,   281,   283,   289,    56,    75,   304,  -383,
    1942,  -383,  -383,  -383,  -383,  2040,   273,   301,   291,   278,
    -383,   335,  -383,  -383,  -383,  -383,  -383,   152,   523,  -383,
      25,  -383,  -383,  1158,  -383,  -383,  -383,  -383,  -383,   305,
      13,   331,    21,   284,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,   272,   242,   367,  -383,   372,
      37,   375,    62,  -383,   394,   406,   408,  -383,  -383,   413,
    1942,   428,  -383,  -383,   424,   476,  2040,   325,   392,  -383,
    -383,  -383,  -383,  -383,  1844,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,   467,  -383,  -383,   278,  -383,    17,  -383,
     -38,   250,   340,   516,   517,   240,  -383,    19,    90,  1942,
    -383,   327,  -383,  -383,   645,   524,  -383,   245,  2040,   278,
    -383,   526,    22,  -383,  1434,   108,  1214,  -383,  -383,  -383,
     501,   504,  -383,  -383,   505,   527,   509,   510,   511,  -383,
    -383,  -383,   514,   515,  -383,  -383,   518,  -383,  -383,  -383,
    -383,  1270,   449,   325,   536,   536,  -383,  -383,   254,  -383,
    1844,  1844,  1844,  -383,  -383,  -383,  -383,  -383,  -383,   541,
     343,   370,   411,    86,   552,  -383,  -383,  1844,    51,   416,
     246,   204,    57,   525,   554,   520,   532,   363,  -383,  -383,
    -383,   279,   113,  -383,   530,   160,  -383,  1681,   547,   547,
     325,  -383,  1844,  1685,  -383,  -383,  -383,  1326,  -383,  -383,
    -383,  -383,   535,  -383,   553,   736,  -383,  -383,   542,   559,
     560,    48,  1009,   539,   566,   482,   572,   485,  1844,   551,
     176,  -383,   285,  -383,  -383,  -383,  -383,   827,  -383,  -383,
    -383,  -383,  -383,  2040,   325,  -383,  -383,  -383,  -383,   278,
     540,  -383,  -383,   255,  -383,   570,  -383,   562,   567,   568,
     -20,  2040,   564,   565,   278,  -383,   169,  -383,  1486,  -383,
     180,   188,   201,   -12,  -383,  -383,   186,  -383,  -383,  1382,
    -383,  -383,  -383,   574,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,   576,   294,  -383,    96,  -383,  -383,  1844,  1714,  1844,
     578,  1719,   578,  -383,  -383,  1009,  1844,   350,  -383,  1844,
    1844,  1844,  1844,  1844,  1844,  1844,  1844,  1844,  1844,  1844,
    1844,  1844,  1844,  1844,  1844,  1844,  -383,  -383,  -383,  -383,
    -383,  1844,  -383,  -383,  1844,  -383,  -383,  -383,  -383,  1844,
    -383,  -383,  -383,  1844,  -383,   491,  -383,   234,  -383,   595,
    1738,  -383,   189,   315,  -383,  -383,  -383,   327,  1772,  -383,
     918,  1009,  1844,  1844,  -383,   297,   557,  -383,  1844,   428,
    1096,   579,   590,  -383,  1009,  1844,  -383,  -383,  -383,   325,
     573,  1844,  -383,  -383,  -383,  -383,  -383,  -383,  -383,   278,
    -383,  -383,   581,   153,   306,  -383,  -383,   585,   524,  -383,
    -383,   353,  -383,  -383,   355,  -383,  -383,   357,  -383,  -383,
     364,   366,   368,  -383,  -383,  1538,   108,  -383,  -383,  -383,
    -383,  -383,   192,   610,   206,   205,  1844,   610,   213,   429,
    -383,  -383,  -383,  -383,  -383,    51,    51,   416,   416,   246,
     246,   246,   246,   204,   204,    57,   525,   554,   520,   532,
     443,  -383,  -383,  -383,  -383,  -383,   612,  -383,  -383,  -383,
     238,  -383,  -383,   215,  -383,  -383,   217,   223,  -383,   618,
     226,  -383,  1806,  -383,  -383,  1009,  -383,  -383,  1844,  -383,
     177,   339,   537,  -383,   601,   325,  -383,  -383,   603,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  1590,  -383,  -383,   578,   610,  -383,   216,   578,
     610,  1994,  1844,  -383,  -383,   534,  -383,  1009,  1009,  1844,
    1009,  1810,   356,  -383,  -383,  -383,   607,  -383,  -383,  -383,
    -383,  -383,  -383,   578,  -383,   578,  1994,  -383,  -383,  -383,
    -383,  -383,  -383,   227,   563,  1009,   228,  1839,  -383,  -383,
     608,  1009,  -383,  1009,  1009,   235,  -383,  -383,  -383,  -383,
    1009,  -383
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   126,   188,   187,   142,   141,     0,   180,     0,   138,
     167,   165,   145,     0,   166,     0,     0,   147,   173,   146,
     171,   140,   168,   169,     0,   139,     0,   148,   144,   143,
     193,     0,     0,     0,     0,     0,   163,   164,     0,     3,
       2,   120,   122,   127,   149,     0,     0,   160,     0,     0,
     125,     0,   129,   130,   131,   128,   124,     0,     0,   123,
     151,   219,   218,     0,   156,   157,   158,   159,   211,   186,
     184,   181,   182,     0,   198,   196,   317,   319,   318,   320,
     197,   309,   311,   310,   312,     0,     0,     0,   204,   179,
     177,   174,   175,   202,   189,   190,   172,   199,   200,   170,
       0,   231,   141,   144,   163,   164,     0,     0,     0,   224,
     313,   315,   314,   316,   254,   256,   258,   259,   255,   194,
     257,   195,     1,     0,   121,   150,     0,   132,     0,   133,
       0,   247,   249,   248,   250,     0,   241,   243,     0,     0,
     298,     0,   283,   286,     0,     0,   271,   261,     0,   281,
     253,     0,   272,   275,     0,     0,     0,   240,   217,   215,
     192,   185,   212,   213,   183,     0,     0,     0,     0,   233,
     210,   208,   191,   178,   205,   206,   176,   220,   221,   203,
     201,     0,     0,     0,   247,   249,   248,   250,     0,   260,
       0,     0,     0,    37,    38,    39,    40,     8,     9,     0,
      18,    19,    32,     0,    13,    16,    41,     0,    45,    48,
      51,    56,    59,    61,    63,    65,    67,    69,    71,    14,
     254,     0,     0,   161,   227,     0,   225,     0,   251,   252,
       0,   134,     0,     0,   244,   284,   288,     0,   365,   366,
     367,   368,   360,   361,     0,     0,   299,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    84,     0,   101,    87,    88,    89,     0,    90,    91,
      92,    93,   119,     0,     0,   297,   287,   263,   262,   282,
     277,   245,   246,   264,   273,     0,   152,     0,     0,     0,
       0,     0,     0,     0,     0,   326,     0,   325,     0,   321,
       0,     0,     0,     0,   338,   342,     0,   336,   238,     0,
     223,   216,   214,     0,   234,   235,   236,   222,   209,   207,
     230,     0,     0,   135,     0,    34,    33,     0,     0,     0,
      24,     0,    25,    12,    11,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,    82,    81,    80,
      79,     0,    78,    77,     0,    76,    75,    74,    73,     0,
     136,   285,   289,     0,   162,     0,   267,    69,    86,     0,
       0,   242,     0,     0,   303,   301,   229,     0,     0,    99,
       0,     0,     0,     0,   116,     0,     0,   115,     0,     0,
       0,     0,     0,   114,     0,     0,    98,   300,   102,     0,
     278,     0,   266,   265,   274,   276,   331,   329,   330,     0,
     327,   328,   334,     0,     0,   332,   290,     0,     0,   153,
     322,     0,   341,   345,     0,   339,   343,     0,   340,   344,
       0,     0,     0,   346,   350,     0,     0,   239,   237,   232,
     137,    10,     0,    20,     0,     0,     0,    21,     0,     4,
      15,    17,    44,    42,    43,    46,    47,    50,    49,    54,
      52,    53,    55,    58,    57,    60,    62,    64,    66,    68,
       0,    72,   228,   226,   268,   269,     0,   302,   306,   307,
       0,   362,   363,     0,   100,    96,     0,     0,   117,     0,
       0,   112,     0,   113,   118,     0,    94,    85,     0,   279,
       0,     0,     0,   291,     0,     0,   323,   293,     0,   356,
     359,   354,   357,   355,   358,   349,   353,   347,   351,   348,
     352,   154,     0,   337,    36,    26,    22,    30,     0,    27,
      23,     0,     0,   270,   304,     0,   364,     0,     0,     0,
       0,     0,     0,    95,   280,   292,     0,   324,   335,   295,
     333,   294,   155,    28,    31,    29,     5,     6,    70,   305,
     308,   106,   105,     0,   103,     0,     0,     0,   296,     7,
       0,     0,   108,     0,     0,     0,   107,   104,   109,   110,
       0,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -383,  -383,  -383,  -383,  -383,  -215,  -383,   308,  -194,  -145,
    -383,   131,   132,    89,   133,   303,   290,   299,   310,   302,
    -208,  -204,  -111,  -383,  -186,  -245,  -230,  -383,   270,  -383,
    -225,  -383,  -383,  -383,  -383,  -383,   -65,   -29,    12,  -382,
     -30,     1,  -149,  -383,  -148,     0,  -383,   300,  -383,  -383,
    -383,  -140,  -383,  -383,  -383,   -97,   444,   397,  -141,   -47,
    -383,  -383,  -108,  -383,  -383,   388,  -383,  -383,  -117,  -383,
    -383,  -383,  -374,  -383,  -383,   236,  -282,   263,   168,  -383,
     239,   390,  -383,   312,  -383
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    38,    39,   566,   202,   203,   204,   205,   330,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   261,   369,   262,   379,   263,   264,   265,   266,
     267,   268,   269,   502,   270,   271,    40,    41,   272,    43,
      44,   273,    46,    47,    48,   274,   225,   226,    50,    51,
      52,    53,    54,    55,    56,   135,   136,   280,   137,    57,
      58,   150,   228,   151,   152,   153,    59,   297,   143,   144,
     275,   234,   385,   490,    60,   298,   299,   424,   425,   306,
     307,   145,   242,   243,   244
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      49,    45,   138,   219,   324,   292,   293,   332,   281,   489,
     188,   124,    42,   402,   295,   125,   430,   382,   503,   377,
     390,   236,   396,   378,   229,   100,   107,   106,   276,   221,
      85,   232,   223,   284,   157,   181,    63,   408,    98,   154,
      49,    45,   440,   441,   442,   126,   325,   326,    73,   159,
     377,   285,    42,   155,   378,   339,   340,   163,   149,   148,
     190,   108,   338,    49,    45,   395,   233,   350,   118,   191,
     192,   193,   194,   171,   237,    42,   125,   229,    87,   222,
     195,   196,   394,   197,    99,    68,   322,   120,    88,   443,
     444,   309,   119,   160,   351,   161,   341,   198,   175,   335,
      49,    45,   282,   164,   140,   372,   183,   296,   101,   451,
     459,   121,    42,   454,   224,   336,   458,   172,   125,   173,
     199,   219,   384,    69,   235,   405,    89,   140,   482,    70,
      61,    71,    90,    72,    91,   486,    92,    62,   281,    49,
      45,   452,    85,   455,   176,   200,   201,   371,   279,   292,
     293,    42,   124,   422,   294,   291,    49,    45,   295,   567,
     408,   495,   300,   301,   302,   377,   140,   140,    42,   378,
      93,   570,   377,   493,   506,   374,   378,    86,   480,   427,
     141,    49,    45,   140,   579,    94,   142,   513,   328,   375,
      87,   140,   329,    42,   462,   463,   464,   141,    74,   303,
     445,    75,   487,   426,   404,   534,   496,   497,   124,   304,
     305,   555,   500,   346,    95,   446,    96,   219,   336,   536,
     219,   405,   537,   347,   348,   460,   540,    80,   546,   408,
     547,   349,   282,   564,   405,   336,   548,    49,    45,   550,
     580,   583,   336,   125,   336,   405,   405,   423,   590,    42,
     430,   296,   405,   544,    97,   405,   405,   405,   481,   535,
     109,   125,   220,   539,   405,   361,   227,   545,   114,   230,
     538,   431,   384,   409,   231,   553,   364,   219,   422,   434,
     124,   432,   433,   230,   344,   149,   148,   345,   323,   435,
     436,   419,   437,   115,   507,   116,   292,   293,   294,   291,
     509,   117,   438,   439,   122,   295,   514,   127,   230,    49,
      45,   518,   221,   370,   405,   128,   552,   571,   572,   406,
     574,    42,   277,   230,   278,   129,   405,   190,   450,   383,
     488,   498,   412,   165,   413,   515,   191,   192,   193,   194,
     516,   158,   563,   167,   168,   582,   565,   195,   196,   139,
     197,   587,   115,   588,   589,   328,   227,    64,    65,   329,
     591,    66,    67,   573,   198,   576,   356,   162,   515,   130,
     166,   357,   510,   557,   422,   131,   132,    34,    35,   133,
     134,   358,   331,   292,   293,   405,   329,   199,   359,   360,
     577,   585,   295,   556,   361,    76,    77,   554,   296,    78,
      79,   169,   362,   363,   189,   364,   365,   366,   170,   367,
     368,   174,   200,   201,    81,    82,   110,   111,    83,    84,
     112,   113,   184,   185,   238,   239,   186,   187,   240,   241,
     177,   568,   333,   334,   384,   469,   470,   471,   472,   342,
     343,   190,   178,   245,   179,   294,   291,   200,   201,   180,
     191,   192,   193,   194,   519,   520,   521,   522,   523,   524,
     119,   195,   196,   247,   197,   525,   526,   527,   528,   529,
     530,   542,   405,   465,   466,   182,   467,   468,   198,   220,
       2,     3,     4,   473,   474,   296,   102,   248,   249,   250,
       6,   251,     7,     8,   252,     9,   253,    10,    11,    12,
     254,   199,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,   121,    23,   255,    25,    26,    27,   256,   257,
     103,    29,   258,    30,    31,   259,   260,   201,   118,   120,
     104,   105,   294,   291,   146,   541,   147,   310,   140,   283,
     311,   312,   313,   314,   315,   316,   190,   321,   383,   569,
     317,   318,   227,   327,   319,   191,   192,   193,   194,   337,
     353,   352,   355,   380,   387,   388,   195,   196,   354,   197,
     391,   392,   393,   397,     2,     3,     4,   373,   398,   399,
     102,   414,   401,   198,   400,   403,     7,   411,   224,     9,
     416,    10,    11,    12,   456,   417,   418,    14,   420,   421,
      17,    18,    19,    20,    21,    22,   199,    23,   448,    25,
     449,    27,   484,   504,   103,    29,   499,    30,   505,   517,
     508,     2,     3,     4,   104,   105,   329,   102,   512,   543,
     549,   200,   201,     7,   558,   559,     9,   561,    10,    11,
      12,   578,   586,   476,    14,   461,   581,    17,    18,    19,
      20,    21,    22,   477,    23,   475,    25,   190,    27,   245,
     246,   103,    29,   479,    30,   478,   191,   192,   193,   194,
     501,   104,   105,   415,   381,   483,   410,   195,   196,   247,
     197,   532,   511,   560,     0,   533,   428,     0,     0,     0,
       0,     0,     0,     0,   198,     0,     2,     3,     4,   491,
       0,     0,   102,   248,   249,   250,     6,   251,     7,     8,
     252,     9,   253,    10,    11,    12,   254,   199,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    23,
     255,    25,    26,    27,   256,   257,   103,    29,   258,    30,
      31,   259,   260,   201,     0,     0,   104,   105,   190,     0,
     245,   389,     0,     0,     0,     0,     0,   191,   192,   193,
     194,     0,     0,     0,     0,     0,     0,     0,   195,   196,
     247,   197,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   198,     0,     2,     3,     4,
       0,     0,     0,   102,   248,   249,   250,     6,   251,     7,
       8,   252,     9,   253,    10,    11,    12,   254,   199,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
      23,   255,    25,    26,    27,   256,   257,   103,    29,   258,
      30,    31,   259,   260,   201,     0,     0,   104,   105,   190,
       0,   245,   407,     0,     0,     0,     0,     0,   191,   192,
     193,   194,     0,     0,     0,     0,     0,     0,     0,   195,
     196,   247,   197,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   198,     0,     2,     3,
       4,     0,     0,     0,   102,   248,   249,   250,     6,   251,
       7,     8,   252,     9,   253,    10,    11,    12,   254,   199,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,    23,   255,    25,    26,    27,   256,   257,   103,    29,
     258,    30,    31,   259,   260,   201,     0,     0,   104,   105,
     190,     0,   245,   494,     0,     0,     0,     0,     0,   191,
     192,   193,   194,     0,     0,     0,     0,     0,     0,     0,
     195,   196,   247,   197,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   198,     0,     2,
       3,     4,     0,     0,     0,   102,   248,   249,   250,     6,
     251,     7,     8,   252,     9,   253,    10,    11,    12,   254,
     199,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     0,    23,   255,    25,    26,    27,   256,   257,   103,
      29,   258,    30,    31,   259,   260,   201,     0,     0,   104,
     105,   190,     0,   245,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,     0,     0,     0,     0,     0,     0,
       0,   195,   196,   247,   197,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   198,     0,
       2,     3,     4,     0,     0,     0,   102,   248,   249,   250,
       6,   251,     7,     8,   252,     9,   253,    10,    11,    12,
     254,   199,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,     0,    23,   255,    25,    26,    27,   256,   257,
     103,    29,   258,    30,    31,   259,   260,   201,   190,     0,
     104,   105,     0,     0,     0,     0,     0,   191,   192,   193,
     194,     0,     0,     0,     0,     0,     0,     0,   195,   196,
     247,   197,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   198,     0,     2,     3,     4,
       0,     0,     0,   102,     0,     0,     0,     6,     0,     7,
       0,     0,     9,     0,    10,    11,    12,     0,   199,    13,
      14,    15,   156,    17,    18,    19,    20,    21,    22,     0,
      23,     0,    25,    26,    27,     0,     0,   103,    29,     0,
      30,    31,     1,   200,   201,     0,     0,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     0,     0,     0,     5,     0,     0,     0,     6,
       0,     7,     8,     0,     9,     0,    10,    11,    12,   308,
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,     0,     1,    28,
      29,     0,    30,    31,     0,   123,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     2,     3,     4,     0,     0,
       0,     5,     0,     0,     0,     6,     0,     7,     8,     0,
       9,     0,    10,    11,    12,   320,     0,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,     0,     1,    28,    29,     0,    30,    31,
       0,   123,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     2,     3,     4,     0,     0,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,     0,    10,    11,
      12,   386,     0,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    24,    25,    26,    27,     0,
       1,    28,    29,     0,    30,    31,     0,   123,    33,    34,
      35,    36,    37,     0,     0,     0,     0,     2,     3,     4,
       0,     0,     0,     5,     0,     0,     0,     6,     0,     7,
       8,     0,     9,     0,    10,    11,    12,   447,     0,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,     0,     1,    28,    29,     0,
      30,    31,     0,   123,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     2,     3,     4,     0,     0,     0,     5,
       0,     0,     0,     6,     0,     7,     8,     0,     9,   286,
      10,    11,    12,     0,     0,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,     0,     0,    28,    29,     0,    30,    31,     0,   123,
      33,    34,    35,    36,    37,     2,     3,     4,   287,   288,
     289,   102,     0,     0,     0,     6,     0,     7,     0,     0,
       9,   429,    10,    11,    12,     0,     0,    13,    14,    15,
     290,    17,    18,    19,    20,    21,    22,     0,    23,     0,
      25,     0,    27,     0,     0,    28,    29,     0,    30,    31,
       0,   123,    33,    34,    35,    36,    37,     2,     3,     4,
     287,   288,   289,   102,     0,     0,     0,     6,     0,     7,
       0,     0,     9,   531,    10,    11,    12,     0,     0,    13,
      14,    15,   290,    17,    18,    19,    20,    21,    22,     0,
      23,     0,    25,     0,    27,     0,     0,    28,    29,     0,
      30,    31,     0,   123,    33,    34,    35,    36,    37,     2,
       3,     4,   287,   288,   289,   102,     0,     0,     0,     6,
       0,     7,     0,     0,     9,   562,    10,    11,    12,     0,
       0,    13,    14,    15,   290,    17,    18,    19,    20,    21,
      22,     0,    23,     0,    25,     0,    27,     0,     0,    28,
      29,     0,    30,    31,     0,   123,    33,    34,    35,    36,
      37,     2,     3,     4,   287,   288,   289,   102,     0,     0,
       0,     6,     0,     7,     0,     0,     9,     0,    10,    11,
      12,     0,     0,    13,    14,    15,   290,    17,    18,    19,
      20,    21,    22,     0,    23,     0,    25,     0,    27,     0,
       0,    28,    29,     0,    30,    31,     0,   123,    33,    34,
      35,    36,    37,   190,     0,     0,     0,   190,   376,   383,
       0,     0,   191,   192,   193,   194,   191,   192,   193,   194,
       0,     0,     0,   195,   196,     0,   197,   195,   196,     0,
     197,     0,     0,     0,     0,     0,   190,   453,     0,     0,
     198,   190,   457,     0,   198,   191,   192,   193,   194,     0,
     191,   192,   193,   194,     0,     0,   195,   196,     0,   197,
     190,   195,   196,   199,   197,   485,     0,   199,     0,   191,
     192,   193,   194,   198,     0,     0,     0,     0,   198,     0,
     195,   196,     0,   197,     0,     0,     0,     0,   200,   201,
       0,     0,   200,   201,   190,   492,   199,   198,     0,     0,
       0,   199,     0,   191,   192,   193,   194,     0,     0,     0,
       0,     0,     0,     0,   195,   196,     0,   197,     0,     0,
     199,   200,   201,     0,     0,     0,   200,   201,   190,     0,
       0,   198,   190,   575,     0,     0,     0,   191,   192,   193,
     194,   191,   192,   193,   194,   200,   201,     0,   195,   196,
     551,   197,   195,   196,   199,   197,     0,     0,     0,     0,
       0,   190,   584,     0,     0,   198,   190,     0,     0,   198,
     191,   192,   193,   194,     0,   191,   192,   193,   194,   200,
     201,   195,   196,     0,   197,     0,   195,   196,   199,   197,
       0,     0,   199,     0,     0,     0,     0,     0,   198,     0,
       0,     0,     0,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   200,   201,     0,     0,   200,   201,     0,
       0,   199,     0,     0,     0,     0,   199,     0,     0,     0,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,   201,     2,     3,
       4,   200,   201,     0,     5,     0,     0,     0,     6,     0,
       7,     8,     0,     9,     0,    10,    11,    12,     0,     0,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,     1,     0,    28,    29,
       0,    30,    31,     0,    32,    33,    34,    35,    36,    37,
       0,     0,     0,     2,     3,     4,     0,     0,     0,     5,
       0,     0,     0,     6,     0,     7,     8,     0,     9,     0,
      10,    11,    12,     0,     0,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,     0,     0,    28,    29,     0,    30,    31,     0,   123,
      33,    34,    35,    36,    37,     2,     3,     4,     0,     0,
       0,   102,     0,     0,     0,     6,     0,     7,     0,     0,
       9,     0,    10,    11,    12,     0,     0,    13,    14,    15,
       0,    17,    18,    19,    20,    21,    22,     0,    23,     0,
      25,    26,    27,     0,     0,   103,    29,     0,    30,    31,
       0,     2,     3,     4,     0,   104,   105,   102,     0,     0,
       0,     0,     0,     7,     0,     0,     9,     0,    10,    11,
      12,     0,     0,     0,    14,     0,     0,    17,    18,    19,
      20,    21,    22,     0,    23,     0,    25,     0,    27,     0,
       0,   103,    29,     0,    30,     0,     0,     0,     0,     0,
       0,   104,   105
};

static const yytype_int16 yycheck[] =
{
       0,     0,    49,   114,   190,   154,   154,   201,   149,   383,
     107,    40,     0,   258,   154,    45,   298,   232,   400,   227,
     245,   138,   252,   227,   132,    14,    26,    26,   145,   126,
      50,    12,    15,    11,    63,   100,    49,   267,    36,    14,
      40,    40,    54,    55,    56,    45,   191,   192,    14,    36,
     258,    29,    40,    28,   258,     4,     5,    36,    58,    58,
      12,    99,   207,    63,    63,   251,    47,    10,    12,    21,
      22,    23,    24,    36,   139,    63,   106,   185,    98,   126,
      32,    33,    34,    35,    82,    36,   183,    12,    36,   101,
     102,   156,    36,    80,    37,    82,    45,    49,    36,    13,
     100,   100,   149,    82,    14,   222,   106,   154,    97,    13,
     335,    36,   100,   328,    97,    29,   331,    80,   148,    82,
      72,   232,   233,    74,    34,    29,    74,    14,   373,    80,
      36,    82,    80,    84,    82,   380,    84,    36,   279,   139,
     139,   327,    50,   329,    82,    97,    98,    34,   148,   298,
     298,   139,   181,   294,   154,   154,   156,   156,   298,   541,
     390,   391,    54,    55,    56,   373,    14,    14,   156,   373,
      36,   545,   380,   388,   404,    15,   380,    85,   364,   296,
      28,   181,   181,    14,   566,    51,    34,    34,    12,    29,
      98,    14,    16,   181,   339,   340,   341,    28,    36,    91,
      14,    36,    13,    34,    28,    13,   392,   393,   237,   101,
     102,    34,   398,     9,    80,    29,    82,   328,    29,    13,
     331,    29,    17,    19,    20,   336,    13,    36,    13,   459,
      13,    27,   279,    17,    29,    29,    13,   237,   237,    13,
      13,    13,    29,   273,    29,    29,    29,   294,    13,   237,
     532,   298,    29,    15,    36,    29,    29,    29,   369,   453,
      36,   291,    12,   457,    29,    31,    16,    29,    12,    29,
     456,    91,   383,   273,    34,   505,    42,   388,   419,    91,
     309,   101,   102,    29,    38,   285,   285,    41,    34,   101,
     102,   291,    91,    12,   405,    12,   445,   445,   298,   298,
     411,    12,   101,   102,     0,   445,   423,    34,    29,   309,
     309,   428,   409,    34,    29,    14,   502,   547,   548,    34,
     550,   309,    77,    29,    79,    34,    29,    12,    34,    14,
      15,    34,    77,    49,    79,    29,    21,    22,    23,    24,
      34,    36,   536,   101,   102,   575,   540,    32,    33,    14,
      35,   581,    12,   583,   584,    12,    16,    97,    98,    16,
     590,   101,   102,   549,    49,   551,     3,    36,    29,    91,
      98,     8,   419,    34,   515,    97,    98,    99,   100,   101,
     102,    18,    12,   532,   532,    29,    16,    72,    25,    26,
      34,   577,   532,   510,    31,    97,    98,   508,   445,   101,
     102,    34,    39,    40,    12,    42,    43,    44,    36,    46,
      47,    36,    97,    98,    97,    98,    97,    98,   101,   102,
     101,   102,    97,    98,    97,    98,   101,   102,   101,   102,
      36,   542,    21,    22,   545,   346,   347,   348,   349,    23,
      24,    12,    36,    14,    36,   445,   445,    97,    98,    36,
      21,    22,    23,    24,   101,   102,   101,   102,   101,   102,
      36,    32,    33,    34,    35,   101,   102,   101,   102,   101,
     102,    28,    29,   342,   343,    47,   344,   345,    49,    12,
      51,    52,    53,   350,   351,   532,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    36,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    12,    12,
     101,   102,   532,   532,    11,   106,    13,    36,    14,    13,
      36,    36,    15,    34,    34,    34,    12,    98,    14,    15,
      36,    36,    16,    12,    36,    21,    22,    23,    24,     7,
       6,    36,    30,    16,    29,    12,    32,    33,    48,    35,
      28,    12,    12,    34,    51,    52,    53,    47,    12,    97,
      57,    11,    97,    49,    12,    34,    63,    47,    97,    66,
      28,    68,    69,    70,    16,    28,    28,    74,    34,    34,
      77,    78,    79,    80,    81,    82,    72,    84,    34,    86,
      34,    88,    17,    34,    91,    92,    59,    94,    28,    34,
      47,    51,    52,    53,   101,   102,    16,    57,    47,    17,
      12,    97,    98,    63,    97,    34,    66,    34,    68,    69,
      70,    34,    34,   353,    74,   337,    83,    77,    78,    79,
      80,    81,    82,   354,    84,   352,    86,    12,    88,    14,
      15,    91,    92,   361,    94,   355,    21,    22,    23,    24,
     400,   101,   102,   285,   230,   375,   279,    32,    33,    34,
      35,   445,   419,   515,    -1,   446,   296,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,   387,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,   101,   102,    12,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,   101,   102,    12,
      -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,   101,   102,
      12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,   101,
     102,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    12,    -1,
     101,   102,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,    63,
      -1,    -1,    66,    -1,    68,    69,    70,    -1,    72,    73,
      74,    75,    14,    77,    78,    79,    80,    81,    82,    -1,
      84,    -1,    86,    87,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    34,    97,    98,    -1,    -1,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,
      -1,    63,    64,    -1,    66,    -1,    68,    69,    70,    15,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    84,    85,    86,    87,    88,    -1,    34,    91,
      92,    -1,    94,    95,    -1,    97,    98,    99,   100,   101,
     102,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    -1,    63,    64,    -1,
      66,    -1,    68,    69,    70,    15,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    84,    85,
      86,    87,    88,    -1,    34,    91,    92,    -1,    94,    95,
      -1,    97,    98,    99,   100,   101,   102,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    -1,    66,    -1,    68,    69,
      70,    15,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    84,    85,    86,    87,    88,    -1,
      34,    91,    92,    -1,    94,    95,    -1,    97,    98,    99,
     100,   101,   102,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,    63,
      64,    -1,    66,    -1,    68,    69,    70,    15,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    -1,    34,    91,    92,    -1,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    -1,    63,    64,    -1,    66,    15,
      68,    69,    70,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,
      98,    99,   100,   101,   102,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,
      66,    15,    68,    69,    70,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    84,    -1,
      86,    -1,    88,    -1,    -1,    91,    92,    -1,    94,    95,
      -1,    97,    98,    99,   100,   101,   102,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    61,    -1,    63,
      -1,    -1,    66,    15,    68,    69,    70,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    -1,    86,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    61,
      -1,    63,    -1,    -1,    66,    15,    68,    69,    70,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,    91,
      92,    -1,    94,    95,    -1,    97,    98,    99,   100,   101,
     102,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    61,    -1,    63,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    97,    98,    99,
     100,   101,   102,    12,    -1,    -1,    -1,    12,    17,    14,
      -1,    -1,    21,    22,    23,    24,    21,    22,    23,    24,
      -1,    -1,    -1,    32,    33,    -1,    35,    32,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    -1,
      49,    12,    13,    -1,    49,    21,    22,    23,    24,    -1,
      21,    22,    23,    24,    -1,    -1,    32,    33,    -1,    35,
      12,    32,    33,    72,    35,    17,    -1,    72,    -1,    21,
      22,    23,    24,    49,    -1,    -1,    -1,    -1,    49,    -1,
      32,    33,    -1,    35,    -1,    -1,    -1,    -1,    97,    98,
      -1,    -1,    97,    98,    12,    13,    72,    49,    -1,    -1,
      -1,    72,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    -1,    35,    -1,    -1,
      72,    97,    98,    -1,    -1,    -1,    97,    98,    12,    -1,
      -1,    49,    12,    13,    -1,    -1,    -1,    21,    22,    23,
      24,    21,    22,    23,    24,    97,    98,    -1,    32,    33,
      34,    35,    32,    33,    72,    35,    -1,    -1,    -1,    -1,
      -1,    12,    13,    -1,    -1,    49,    12,    -1,    -1,    49,
      21,    22,    23,    24,    -1,    21,    22,    23,    24,    97,
      98,    32,    33,    -1,    35,    -1,    32,    33,    72,    35,
      -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    98,    -1,    -1,    97,    98,    -1,
      -1,    72,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    51,    52,
      53,    97,    98,    -1,    57,    -1,    -1,    -1,    61,    -1,
      63,    64,    -1,    66,    -1,    68,    69,    70,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    84,    85,    86,    87,    88,    34,    -1,    91,    92,
      -1,    94,    95,    -1,    97,    98,    99,   100,   101,   102,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    -1,    63,    64,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,
      98,    99,   100,   101,   102,    51,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,
      66,    -1,    68,    69,    70,    -1,    -1,    73,    74,    75,
      -1,    77,    78,    79,    80,    81,    82,    -1,    84,    -1,
      86,    87,    88,    -1,    -1,    91,    92,    -1,    94,    95,
      -1,    51,    52,    53,    -1,   101,   102,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    74,    -1,    -1,    77,    78,    79,
      80,    81,    82,    -1,    84,    -1,    86,    -1,    88,    -1,
      -1,    91,    92,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    51,    52,    53,    57,    61,    63,    64,    66,
      68,    69,    70,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    84,    85,    86,    87,    88,    91,    92,
      94,    95,    97,    98,    99,   100,   101,   102,   108,   109,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     155,   156,   157,   158,   159,   160,   161,   166,   167,   173,
     181,    36,    36,    49,    97,    98,   101,   102,    36,    74,
      80,    82,    84,    14,    36,    36,    97,    98,   101,   102,
      36,    97,    98,   101,   102,    50,    85,    98,    36,    74,
      80,    82,    84,    36,    51,    80,    82,    36,    36,    82,
      14,    97,    57,    91,   101,   102,   148,   152,    99,    36,
      97,    98,   101,   102,    12,    12,    12,    12,    12,    36,
      12,    36,     0,    97,   144,   147,   152,    34,    14,    34,
      91,    97,    98,   101,   102,   162,   163,   165,   166,    14,
      14,    28,    34,   175,   176,   188,    11,    13,   148,   152,
     168,   170,   171,   172,    14,    28,    14,   144,    36,    36,
      80,    82,    36,    36,    82,    49,    98,   101,   102,    34,
      36,    36,    80,    82,    36,    36,    82,    36,    36,    36,
      36,   143,    47,   152,    97,    98,   101,   102,   162,    12,
      12,    21,    22,    23,    24,    32,    33,    35,    49,    72,
      97,    98,   111,   112,   113,   114,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
      12,   162,   166,    15,    97,   153,   154,    16,   169,   169,
      29,    34,    12,    47,   178,    34,   175,   143,    97,    98,
     101,   102,   189,   190,   191,    14,    15,    34,    58,    59,
      60,    62,    65,    67,    71,    85,    89,    90,    93,    96,
      97,   129,   131,   133,   134,   135,   136,   137,   138,   139,
     141,   142,   145,   148,   152,   177,   175,    77,    79,   152,
     164,   165,   166,    13,    11,    29,    15,    54,    55,    56,
      76,   148,   149,   151,   152,   158,   166,   174,   182,   183,
      54,    55,    56,    91,   101,   102,   186,   187,    15,   143,
      36,    36,    36,    15,    34,    34,    34,    36,    36,    36,
      15,    98,   162,    34,   131,   116,   116,    12,    12,    16,
     115,    12,   115,    21,    22,    13,    29,     7,   116,     4,
       5,    45,    23,    24,    38,    41,     9,    19,    20,    27,
      10,    37,    36,     6,    48,    30,     3,     8,    18,    25,
      26,    31,    39,    40,    42,    43,    44,    46,    47,   130,
      34,    34,   175,    47,    15,    29,    17,   127,   128,   132,
      16,   163,   112,    14,   129,   179,    15,    29,    12,    15,
     137,    28,    12,    12,    34,   131,   133,    34,    12,    97,
      12,    97,   132,    34,    28,    29,    34,    15,   133,   152,
     164,    47,    77,    79,    11,   172,    28,    28,    28,   152,
      34,    34,   165,   166,   184,   185,    34,   175,   188,    15,
     183,    91,   101,   102,    91,   101,   102,    91,   101,   102,
      54,    55,    56,   101,   102,    14,    29,    15,    34,    34,
      34,    13,   131,    13,   112,   131,    16,    13,   112,   137,
     129,   114,   116,   116,   116,   118,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   122,   123,   124,   125,   126,
     131,   129,   132,   154,    17,    17,   132,    13,    15,   179,
     180,   190,    13,   112,    15,   133,   131,   131,    34,    59,
     131,   135,   140,   146,    34,    28,   133,   129,    47,   129,
     166,   184,    47,    34,   175,    29,    34,    34,   175,   101,
     102,   101,   102,   101,   102,   101,   102,   101,   102,   101,
     102,    15,   182,   187,    13,   115,    13,    17,   131,   115,
      13,   106,    28,    17,    15,    29,    13,    13,    13,    12,
      13,    34,   131,   133,   129,    34,   175,    34,    97,    34,
     185,    34,    15,   115,    17,   115,   110,   146,   129,    15,
     179,   133,   133,   131,   133,    13,   131,    34,    34,   146,
      13,    83,   133,    13,    13,   131,    34,   133,   133,   133,
      13,   133
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   109,   109,   110,   110,   111,   111,
     111,   111,   111,   111,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   119,   119,   119,   120,   120,
     120,   121,   121,   121,   121,   121,   122,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   140,   140,   141,   141,   141,   141,   141,   142,
     143,   143,   144,   144,   144,   144,   144,   145,   145,   145,
     145,   145,   146,   146,   146,   146,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   150,   150,   150,   150,
     151,   151,   151,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   153,   153,   154,   154,   155,
     155,   156,   157,   158,   158,   159,   159,   160,   161,   161,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   165,
     165,   165,   165,   166,   167,   167,   167,   167,   167,   167,
     167,   168,   168,   168,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   170,   170,   171,   171,   172,   172,   172,
     172,   172,   172,   173,   173,   173,   173,   173,   173,   173,
     174,   174,   174,   174,   174,   174,   174,   175,   176,   177,
     177,   178,   178,   179,   179,   179,   179,   180,   180,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   182,   182,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   184,   184,   185,   185,   186,   186,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     188,   189,   189,   190,   190,   191,   191,   191,   191
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     7,     1,     2,     1,     1,
       3,     2,     2,     1,     1,     3,     1,     3,     1,     1,
       3,     3,     4,     4,     2,     2,     4,     4,     5,     5,
       3,     4,     1,     2,     2,     2,     4,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     3,     1,     2,     2,
       3,     1,     2,     5,     7,     5,     5,     7,     6,     7,
       7,     8,     1,     1,     2,     2,     2,     3,     3,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     4,     4,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     3,     4,     5,     6,     2,     2,     2,     2,
       1,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     2,     3,     2,     3,     2,
       1,     2,     2,     3,     2,     3,     2,     1,     1,     2,
       2,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     3,     2,     3,     2,     3,     3,     4,     3,     4,
       3,     2,     3,     3,     4,     3,     4,     3,     2,     2,
       3,     3,     4,     4,     2,     1,     3,     1,     3,     4,
       4,     2,     5,     3,     4,     4,     4,     5,     4,     5,
       3,     1,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     1,     2,     2,     2,     3,     3,     2,     3,     3,
       4,     1,     1,     2,     3,     1,     3,     2,     3,     4,
       5,     1,     2,     2,     3,     4,     2,     3,     3,     4,
       2,     3,     4,     3,     4,     4,     5,     2,     1,     1,
       2,     2,     3,     1,     3,     4,     2,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     2,     3,     4,     1,     1,     2,     2,     2,
       2,     2,     1,     3,     1,     3,     1,     3,     1,     2,
       2,     2,     1,     2,     2,     2,     2,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     3,     4,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 73 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtCppTranslationUnit_create((yyvsp[0]).pContext);
  (yyval).pContext = adtCpp_setRoot(pObj);

  adtCpp_releaseObject(pObj);
}
#line 2135 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 3:
#line 82 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add(adtCpp_getRoot(), (yyvsp[0]).pContext);
}
#line 2143 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 4:
#line 90 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 2151 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 5:
#line 94 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-6]).sValue, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2159 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclarationList_create((yyvsp[0]).pContext);
}
#line 2167 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 7:
#line 104 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2175 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 8:
#line 111 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2183 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 9:
#line 115 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2191 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 10:
#line 119 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create((yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 2199 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 11:
#line 123 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 1, 0);
}
#line 2207 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 2215 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2223 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionList_create((yyvsp[0]).pContext);
}
#line 2231 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 15:
#line 142 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2239 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 16:
#line 149 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDirectedExpression_create((yyvsp[0]).pContext);
}
#line 2247 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 17:
#line 153 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2255 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 2263 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 19:
#line 168 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 1, 0, (yyvsp[0]).sComment);
}
#line 2271 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 20:
#line 172 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 0, 1, (yyvsp[-2]).sComment);
}
#line 2279 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 21:
#line 176 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 1, 1, (yyvsp[-2]).sComment);
}
#line 2287 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 22:
#line 180 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 0, 1, (yyvsp[-3]).sComment);
}
#line 2295 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 23:
#line 184 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 1, 1, (yyvsp[-3]).sComment);
}
#line 2303 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 24:
#line 188 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 0, 0, (yyvsp[-1]).sComment);
}
#line 2311 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 25:
#line 192 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 1, 0, (yyvsp[-1]).sComment);
}
#line 2319 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 26:
#line 196 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 0, 1, (yyvsp[-3]).sComment);
}
#line 2327 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 27:
#line 200 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 1, 1, (yyvsp[-3]).sComment);
}
#line 2335 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 28:
#line 204 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1, (yyvsp[-4]).sComment);
}
#line 2343 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 29:
#line 208 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1, 1, (yyvsp[-4]).sComment);
}
#line 2351 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 30:
#line 215 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpressionDims_create((yyvsp[-1]).pContext);
}
#line 2359 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 31:
#line 219 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 2367 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 32:
#line 226 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2375 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 33:
#line 230 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 1);
}
#line 2383 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 34:
#line 234 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2391 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 35:
#line 238 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 2399 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 36:
#line 242 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 2407 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 37:
#line 249 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(0);
}
#line 2415 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 38:
#line 253 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(1);
}
#line 2423 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 39:
#line 257 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(2);
}
#line 2431 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 40:
#line 261 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(3);
}
#line 2439 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 41:
#line 268 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2447 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 42:
#line 272 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2455 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 43:
#line 276 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2463 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 44:
#line 280 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2471 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 45:
#line 287 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2479 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 46:
#line 291 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2487 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 47:
#line 295 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2495 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 48:
#line 302 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2503 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 49:
#line 306 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2511 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 50:
#line 310 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2519 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 51:
#line 317 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2527 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 52:
#line 321 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2535 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 53:
#line 325 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2543 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 54:
#line 329 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2551 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 55:
#line 333 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(3, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2559 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 56:
#line 340 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2567 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 57:
#line 344 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2575 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 58:
#line 348 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2583 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 59:
#line 355 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2591 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2599 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 61:
#line 366 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2607 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 62:
#line 370 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2615 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 63:
#line 377 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2623 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 64:
#line 381 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2631 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 65:
#line 388 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2639 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 66:
#line 392 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2647 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 67:
#line 399 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2655 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 68:
#line 403 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2663 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 69:
#line 410 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[0]).pContext, 0, 0);
}
#line 2671 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 70:
#line 414 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2679 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 71:
#line 421 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 2687 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 72:
#line 425 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2695 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 73:
#line 432 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(0);
}
#line 2703 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 74:
#line 436 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(1);
}
#line 2711 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 75:
#line 440 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(2);
}
#line 2719 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 76:
#line 444 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(3);
}
#line 2727 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 77:
#line 448 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(4);
}
#line 2735 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 78:
#line 452 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(5);
}
#line 2743 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 79:
#line 456 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(6);
}
#line 2751 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 80:
#line 460 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(7);
}
#line 2759 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 81:
#line 464 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(8);
}
#line 2767 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 82:
#line 468 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(9);
}
#line 2775 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 83:
#line 472 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(10);
}
#line 2783 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 84:
#line 479 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, 0);
}
#line 2791 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 85:
#line 483 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2799 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 86:
#line 490 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConstantExpression_create((yyvsp[0]).pContext);
}
#line 2807 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 87:
#line 497 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 2815 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 88:
#line 501 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0);
}
#line 2823 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 89:
#line 505 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2831 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 90:
#line 509 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2839 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 91:
#line 513 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2847 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 92:
#line 517 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 2855 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 93:
#line 521 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 2863 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 94:
#line 528 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).sValue, 0, (yyvsp[-2]).sComment);
}
#line 2871 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 95:
#line 532 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, (yyvsp[-3]).sComment);
}
#line 2879 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 96:
#line 536 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, 0, 1, (yyvsp[-2]).sComment);
}
#line 2887 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 97:
#line 543 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create(0, (yyvsp[0]).sComment);
}
#line 2895 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 98:
#line 547 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create((yyvsp[-1]).pContext, (yyvsp[0]).sComment);
}
#line 2903 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 99:
#line 554 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0, (yyvsp[-1]).sComment);
}
#line 2911 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 100:
#line 558 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext, (yyvsp[-2]).sComment);
}
#line 2919 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 101:
#line 565 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatementSeq_create((yyvsp[0]).pContext);
}
#line 2927 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 102:
#line 569 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2935 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 103:
#line 580 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1, (yyvsp[-4]).sComment);
}
#line 2943 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 104:
#line 584 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1, (yyvsp[-6]).sComment);
}
#line 2951 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 105:
#line 588 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, (yyvsp[-4]).sComment);
}
#line 2959 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 106:
#line 595 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-4]).sComment);
}
#line 2967 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 107:
#line 599 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[-5]).pContext, 1, (yyvsp[-6]).sComment);
}
#line 2975 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 108:
#line 603 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-3]).pContext, 0, 0, (yyvsp[0]).pContext, 0, (yyvsp[-5]).sComment);
}
#line 2983 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 109:
#line 607 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-6]).sComment);
}
#line 2991 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 110:
#line 611 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-6]).sComment);
}
#line 2999 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 111:
#line 615 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-5]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-7]).sComment);
}
#line 3007 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 112:
#line 622 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create((yyvsp[0]).pContext, 0);
}
#line 3015 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 113:
#line 626 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create(0, (yyvsp[0]).pContext);
}
#line 3023 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 114:
#line 633 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 0, (yyvsp[-1]).sComment);
}
#line 3031 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 115:
#line 637 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 1, (yyvsp[-1]).sComment);
}
#line 3039 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 116:
#line 641 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 2, (yyvsp[-1]).sComment);
}
#line 3047 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 117:
#line 645 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create((yyvsp[-1]).pContext, 0, 2, (yyvsp[-2]).sComment);
}
#line 3055 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 118:
#line 649 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, (yyvsp[-1]).sValue, 3, (yyvsp[-2]).sComment);
}
#line 3063 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 119:
#line 656 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationStatement_create((yyvsp[0]).pContext);
}
#line 3071 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 120:
#line 663 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationSeq_create((yyvsp[0]).pContext);
}
#line 3079 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 121:
#line 667 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3087 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 122:
#line 674 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3095 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 123:
#line 678 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3103 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 124:
#line 682 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3111 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 125:
#line 686 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3119 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 126:
#line 690 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 3127 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 127:
#line 697 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3135 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 128:
#line 701 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3143 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 129:
#line 705 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3151 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 130:
#line 709 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3159 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 131:
#line 713 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 3167 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 132:
#line 720 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 3175 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 133:
#line 724 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0);
}
#line 3183 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 134:
#line 728 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 3191 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 135:
#line 732 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 1, (yyvsp[-3]).sComment);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3207 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 136:
#line 744 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 0, 0);
}
#line 3215 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 137:
#line 748 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1, (yyvsp[-4]).sComment);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3231 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 138:
#line 763 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(0, (yyvsp[0]).sComment);
}
#line 3239 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 139:
#line 767 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(1, (yyvsp[0]).sComment);
}
#line 3247 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 140:
#line 771 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(2, (yyvsp[0]).sComment);
}
#line 3255 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 141:
#line 775 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(3, (yyvsp[0]).sComment);
}
#line 3263 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 142:
#line 779 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(4, (yyvsp[0]).sComment);
}
#line 3271 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 143:
#line 783 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(5, (yyvsp[0]).sComment);
}
#line 3279 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 144:
#line 787 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(6, (yyvsp[0]).sComment);
}
#line 3287 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 145:
#line 791 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(7, (yyvsp[0]).sComment);
}
#line 3295 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 146:
#line 795 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(8, (yyvsp[0]).sComment);
}
#line 3303 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 147:
#line 799 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(9, (yyvsp[0]).sComment);
}
#line 3311 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 148:
#line 803 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(10, (yyvsp[0]).sComment);
}
#line 3319 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 149:
#line 810 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifierList_create((yyvsp[0]).pContext);
}
#line 3327 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 150:
#line 814 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3335 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 151:
#line 821 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 3345 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 152:
#line 827 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-2]).pContext, 0, 0, 1);
}
#line 3355 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 153:
#line 833 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 3365 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 154:
#line 839 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 1);
}
#line 3375 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 155:
#line 845 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 3385 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 156:
#line 854 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);
}
#line 3395 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 157:
#line 860 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);
}
#line 3405 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 158:
#line 866 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);
}
#line 3413 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 159:
#line 870 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);
}
#line 3421 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 160:
#line 877 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[0]).pContext, 0);
}
#line 3429 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 161:
#line 881 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[-2]).pContext, 1);
}
#line 3437 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 162:
#line 885 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1);
}
#line 3445 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 163:
#line 899 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 0, 0, (yyvsp[0]).sComment);
}
#line 3453 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 164:
#line 903 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 1, 0, (yyvsp[0]).sComment);
}
#line 3461 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 165:
#line 907 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 0, (yyvsp[0]).sComment);
}
#line 3469 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 166:
#line 911 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 0, (yyvsp[0]).sComment);
}
#line 3477 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 167:
#line 915 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 0, (yyvsp[0]).sComment);
}
#line 3485 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 168:
#line 919 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 0, (yyvsp[0]).sComment);
}
#line 3493 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 169:
#line 923 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 0, (yyvsp[0]).sComment);
}
#line 3501 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 170:
#line 927 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 0, (yyvsp[-1]).sComment);
}
#line 3509 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 171:
#line 931 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 0, (yyvsp[0]).sComment);
}
#line 3517 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 172:
#line 935 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 0, (yyvsp[-1]).sComment);
}
#line 3525 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 173:
#line 939 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 0, (yyvsp[0]).sComment);
}
#line 3533 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 174:
#line 943 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 0, (yyvsp[-1]).sComment);
}
#line 3541 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 175:
#line 947 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 0, (yyvsp[-1]).sComment);
}
#line 3549 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 176:
#line 951 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 0, (yyvsp[-2]).sComment);
}
#line 3557 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 177:
#line 955 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 0, (yyvsp[-1]).sComment);
}
#line 3565 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 178:
#line 959 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 0, (yyvsp[-2]).sComment);
}
#line 3573 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 179:
#line 963 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 0, (yyvsp[-1]).sComment);
}
#line 3581 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 180:
#line 967 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 0, (yyvsp[0]).sComment);
}
#line 3589 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 181:
#line 971 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 0, (yyvsp[-1]).sComment);
}
#line 3597 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 182:
#line 975 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 0, (yyvsp[-1]).sComment);
}
#line 3605 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 183:
#line 979 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 0, (yyvsp[-2]).sComment);
}
#line 3613 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 184:
#line 983 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 0, (yyvsp[-1]).sComment);
}
#line 3621 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 185:
#line 987 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 0, (yyvsp[-2]).sComment);
}
#line 3629 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 186:
#line 991 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 0, (yyvsp[-1]).sComment);
}
#line 3637 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 187:
#line 995 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 0, (yyvsp[0]).sComment);
}
#line 3645 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 188:
#line 999 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 0, (yyvsp[0]).sComment);
}
#line 3653 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1003 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 0, (yyvsp[-1]).sComment);
}
#line 3661 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1007 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 0, (yyvsp[-1]).sComment);
}
#line 3669 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1011 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 0, (yyvsp[-2]).sComment);
}
#line 3677 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1015 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 0, (yyvsp[-2]).sComment);
}
#line 3685 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1019 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 0, (yyvsp[0]).sComment);
}
#line 3693 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1023 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 0, 1, (yyvsp[-1]).sComment);
}
#line 3701 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1027 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 1, 1, (yyvsp[-1]).sComment);
}
#line 3709 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1031 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 1, (yyvsp[-1]).sComment);
}
#line 3717 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1035 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 1, (yyvsp[-1]).sComment);
}
#line 3725 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1039 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 1, (yyvsp[-1]).sComment);
}
#line 3733 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1043 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 1, (yyvsp[-1]).sComment);
}
#line 3741 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1047 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 1, (yyvsp[-1]).sComment);
}
#line 3749 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1051 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 1, (yyvsp[-2]).sComment);
}
#line 3757 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1055 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 1, (yyvsp[-1]).sComment);
}
#line 3765 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1059 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 1, (yyvsp[-2]).sComment);
}
#line 3773 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1063 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 1, (yyvsp[-1]).sComment);
}
#line 3781 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1067 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 1, (yyvsp[-2]).sComment);
}
#line 3789 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1071 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 1, (yyvsp[-2]).sComment);
}
#line 3797 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1075 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 1, (yyvsp[-3]).sComment);
}
#line 3805 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1079 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 1, (yyvsp[-2]).sComment);
}
#line 3813 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1083 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 1, (yyvsp[-3]).sComment);
}
#line 3821 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1087 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 1, (yyvsp[-2]).sComment);
}
#line 3829 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1091 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 1, (yyvsp[-1]).sComment);
}
#line 3837 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1095 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 1, (yyvsp[-2]).sComment);
}
#line 3845 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1099 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 1, (yyvsp[-2]).sComment);
}
#line 3853 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1103 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 1, (yyvsp[-3]).sComment);
}
#line 3861 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1107 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 1, (yyvsp[-2]).sComment);
}
#line 3869 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1111 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 1, (yyvsp[-3]).sComment);
}
#line 3877 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1115 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 1, (yyvsp[-2]).sComment);
}
#line 3885 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1119 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 1, (yyvsp[-1]).sComment);
}
#line 3893 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1123 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 1, (yyvsp[-1]).sComment);
}
#line 3901 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1127 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 1, (yyvsp[-2]).sComment);
}
#line 3909 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1131 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 1, (yyvsp[-2]).sComment);
}
#line 3917 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1135 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 1, (yyvsp[-3]).sComment);
}
#line 3925 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1139 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 1, (yyvsp[-3]).sComment);
}
#line 3933 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1143 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 1, (yyvsp[-1]).sComment);
}
#line 3941 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1150 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorList_create((yyvsp[0]).pContext);
}
#line 3949 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1154 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3957 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1161 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create(0, (yyvsp[0]).sValue, (yyvsp[0]).sComment);
}
#line 3965 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1165 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create((yyvsp[0]).pContext, (yyvsp[-2]).sValue, (yyvsp[-2]).sComment);
}
#line 3973 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1172 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, (yyvsp[-3]).sValue, (yyvsp[-3]).sComment);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 3983 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1178 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 3991 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1185 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);

  (yyval).sValue   = (yyvsp[0]).sValue;
  (yyval).sComment = (yyvsp[-1]).sComment;
}
#line 4002 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1194 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceAliasDefinition_create((yyvsp[-3]).sValue, (yyvsp[-1]).sValue, (yyvsp[-4]).sComment);
}
#line 4010 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1201 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 0, (yyvsp[-2]).sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4020 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1207 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 1, (yyvsp[-3]).sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4030 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1216 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 0, (yyvsp[-3]).sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4040 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1222 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 1, (yyvsp[-3]).sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4050 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1231 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAsmDefinition_create((yyvsp[-2]).sValue, (yyvsp[-4]).sComment);
}
#line 4058 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1238 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, 0, (yyvsp[-2]).sValue, (yyvsp[-3]).sComment);
}
#line 4066 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1242 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create((yyvsp[-1]).pContext, 0, (yyvsp[-3]).sValue, (yyvsp[-4]).sComment);
}
#line 4074 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1246 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, (yyvsp[-2]).sComment);
}
#line 4082 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1253 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclaratorList_create((yyvsp[0]).pContext);
}
#line 4090 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1257 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4098 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1264 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 4106 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1268 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4114 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1277 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4122 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1281 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4130 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1288 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 0, 0, 0, (yyvsp[0]).sComment, 1);
}
#line 4138 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1292 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 1, 0, 0, (yyvsp[0]).sComment, 0);
}
#line 4146 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1296 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 0, 0, 0, (yyvsp[0]).sComment, 1);
}
#line 4154 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1300 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 1, 0, 0, (yyvsp[0]).sComment, 0);
}
#line 4162 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1304 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 0, 0, 0, 0, (yyvsp[-1]).sComment, 1);
}
#line 4170 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1308 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 1, 0, 0, 0, (yyvsp[-1]).sComment, 1);
}
#line 4178 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1338 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
 (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4186 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1345 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4200 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1355 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4214 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1365 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4228 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1375 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4242 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1385 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4256 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1395 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4270 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1405 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 1;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4284 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1418 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4294 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1424 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4304 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1430 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4314 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1436 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-1]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4324 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1442 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4334 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1448 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4344 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1457 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, 0);
}
#line 4352 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1461 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, 0);
}
#line 4360 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1465 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, (yyvsp[-2]).pContext);
}
#line 4368 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1469 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext);
}
#line 4376 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1476 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create(0, 1, 0);
}
#line 4384 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1480 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4392 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1484 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-1]).pContext, 1, 0);
}
#line 4400 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1488 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-2]).pContext, 1, 1);
}
#line 4408 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1495 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationList_create((yyvsp[0]).pContext);
}
#line 4416 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1499 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4424 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1506 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4432 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1510 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4440 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1514 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4448 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1518 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4456 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1522 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[0]).pContext, 0, 0);
}
#line 4464 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1526 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 4472 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1533 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4480 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1537 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4488 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1541 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4496 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1545 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4504 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1549 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4512 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1553 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4520 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1557 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4528 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1564 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4536 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1568 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4544 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1572 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4552 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1576 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4560 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1580 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 4568 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1584 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4576 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1588 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4584 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1598 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionBody_create((yyvsp[0]).pContext);
}
#line 4592 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1605 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4600 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1612 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4610 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1618 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4620 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1627 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create((yyvsp[0]).pContext, 0);
}
#line 4628 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1631 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create(0, (yyvsp[-1]).pContext);
}
#line 4636 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1638 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4644 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1642 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-1]).pContext, 0);
}
#line 4652 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1646 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-2]).pContext, 1);
}
#line 4660 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1650 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, 0, 0);
}
#line 4668 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1657 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerList_create((yyvsp[0]).pContext);
}
#line 4676 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1661 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4684 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1668 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4695 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1675 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4706 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1682 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4717 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1689 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4728 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1696 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4739 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1703 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4750 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1710 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4761 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1717 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4772 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1724 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4783 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1731 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4794 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1738 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4805 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1745 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4816 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1755 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberSpecification_create((yyvsp[0]).pContext);
}
#line 4824 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1759 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4832 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1766 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4840 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1770 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4848 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1774 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 4856 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1778 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 4864 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1782 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
#line 4872 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1786 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 4880 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1790 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 4888 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1794 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 2, 0);
}
#line 4896 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1798 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 3, 0);
}
#line 4904 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1805 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarationList_create((yyvsp[0]).pContext);
}
#line 4912 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1809 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4920 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1816 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 4928 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1820 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[-2]).pContext, (yyvsp[0]).sValue);
}
#line 4936 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1827 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBaseSpecifierList_create((yyvsp[0]).pContext);
}
#line 4944 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1831 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4952 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1838 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 0, (yyvsp[0]).sValue);
}
#line 4962 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1844 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 0, (yyvsp[0]).sValue);
}
#line 4972 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1850 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 0, (yyvsp[0]).sValue);
}
#line 4982 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1856 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 0, (yyvsp[0]).sValue);
}
#line 4992 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1862 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 1, (yyvsp[0]).sValue);
}
#line 5002 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1868 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 1, (yyvsp[0]).sValue);
}
#line 5012 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1874 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 1, (yyvsp[0]).sValue);
}
#line 5022 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1880 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 1, (yyvsp[0]).sValue);
}
#line 5032 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1886 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 0, (yyvsp[0]).sValue);
}
#line 5042 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1892 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5052 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1898 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5062 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1904 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5072 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1910 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 1, (yyvsp[0]).sValue);
}
#line 5082 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1916 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5092 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1922 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5102 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1928 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5112 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1934 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5122 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1940 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5132 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1946 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5142 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1952 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5152 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1958 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5162 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1964 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5172 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1973 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCtorInitializer_create((yyvsp[0]).pContext);
}
#line 5180 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1980 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerList_create((yyvsp[0]).pContext);
}
#line 5188 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1984 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5196 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1991 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-2]).pContext, 0);
}
#line 5204 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1995 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5212 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2002 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5220 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2006 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5228 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2010 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5236 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2014 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5244 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;


#line 5248 "..\\src\\cpp_y.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
  return yyresult;
}
