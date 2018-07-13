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
#define YYSTYPE           cppType
#define YYTYPE_INT16      short

const char* adtCpp_pLastFunctionName        = 0;
int         adtCpp_pLastFunctionIsObj       = 0;
int         adtCpp_pLastFunctionIsQualified = 0;
int         adtCpp_pLastFunctionIsVirtual   = 0;
int*        adtCpp_yyState                  = 0;



#line 112 "..\\src\\cpp_y.c" /* yacc.c:339  */

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
# define YYDEBUG 0
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
    LONGBOOL = 324,
    WCHAR_T = 325,
    EXPLICIT = 326,
    IF = 327,
    SIZEOF = 328,
    UNION = 329,
    CHAR = 330,
    CLASS = 331,
    USING = 332,
    VOLATILE = 333,
    SIGNED = 334,
    CONST = 335,
    LONG = 336,
    STATIC = 337,
    INT = 338,
    ELSE = 339,
    SHORT = 340,
    NAMESPACE = 341,
    REGISTER = 342,
    TYPEDEF = 343,
    FRIEND = 344,
    FOR = 345,
    GOTO = 346,
    VIRTUAL = 347,
    INLINE = 348,
    CASE = 349,
    VOID = 350,
    STRUCT = 351,
    BREAK = 352,
    IDENTIFIER = 353,
    QUALIFIED_IDENTIFIER = 354,
    DTOR = 355,
    QUALIFIED_DTOR = 356,
    OBJ_IDENTIFIER = 357,
    QUALIFIED_OBJ_IDENTIFIER = 358,
    SINGLELINE_COMMENT = 359,
    MULTILINE_COMMENT = 360,
    EMBEDDED_COMMANDS = 361,
    PREPROCESSOR = 362,
    WHITESPACE = 363,
    ADDVARIABLES = 364
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

#line 273 "..\\src\\cpp_y.c" /* yacc.c:358  */

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
#define YYFINAL  124
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  370
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  594

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   364

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
     105,   106,   107,   108,   109
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    82,    90,    94,   100,   104,   111,   115,
     119,   123,   127,   131,   138,   142,   149,   153,   164,   168,
     172,   176,   180,   184,   188,   192,   196,   200,   204,   208,
     215,   219,   226,   230,   234,   238,   242,   249,   253,   257,
     261,   268,   272,   276,   280,   287,   291,   295,   302,   306,
     310,   317,   321,   325,   329,   333,   340,   344,   348,   355,
     359,   366,   370,   377,   381,   388,   392,   399,   403,   410,
     414,   421,   425,   432,   436,   440,   444,   448,   452,   456,
     460,   464,   468,   472,   479,   483,   490,   497,   501,   505,
     509,   513,   517,   521,   528,   532,   536,   543,   547,   554,
     558,   565,   569,   580,   584,   588,   595,   599,   603,   607,
     611,   615,   622,   626,   633,   637,   641,   645,   649,   656,
     663,   667,   674,   678,   682,   686,   690,   697,   701,   705,
     709,   713,   720,   724,   728,   732,   744,   748,   763,   767,
     771,   775,   779,   783,   787,   791,   795,   799,   803,   810,
     814,   821,   827,   833,   839,   845,   854,   860,   866,   870,
     877,   881,   885,   899,   903,   907,   911,   915,   919,   923,
     927,   931,   935,   939,   943,   947,   951,   955,   959,   963,
     967,   971,   975,   979,   983,   987,   991,   995,   999,  1003,
    1007,  1011,  1015,  1019,  1023,  1027,  1031,  1035,  1039,  1043,
    1047,  1051,  1055,  1059,  1063,  1067,  1071,  1075,  1079,  1083,
    1087,  1091,  1095,  1099,  1103,  1107,  1111,  1115,  1119,  1123,
    1127,  1131,  1135,  1139,  1143,  1147,  1151,  1158,  1162,  1169,
    1173,  1180,  1186,  1193,  1201,  1208,  1214,  1223,  1229,  1238,
    1245,  1249,  1253,  1260,  1264,  1271,  1275,  1284,  1288,  1295,
    1299,  1303,  1307,  1311,  1315,  1345,  1352,  1361,  1370,  1379,
    1388,  1397,  1406,  1418,  1424,  1430,  1436,  1442,  1448,  1457,
    1461,  1465,  1469,  1476,  1480,  1484,  1488,  1495,  1499,  1506,
    1510,  1514,  1518,  1522,  1526,  1533,  1537,  1541,  1545,  1549,
    1553,  1557,  1564,  1568,  1572,  1576,  1580,  1584,  1588,  1598,
    1605,  1612,  1618,  1627,  1631,  1638,  1642,  1646,  1650,  1657,
    1661,  1668,  1675,  1682,  1689,  1696,  1703,  1710,  1717,  1724,
    1731,  1738,  1745,  1755,  1759,  1766,  1770,  1774,  1778,  1782,
    1786,  1790,  1794,  1798,  1805,  1809,  1816,  1820,  1827,  1831,
    1838,  1844,  1850,  1856,  1862,  1868,  1874,  1880,  1886,  1892,
    1898,  1904,  1910,  1916,  1922,  1928,  1934,  1940,  1946,  1952,
    1958,  1964,  1973,  1980,  1984,  1991,  1995,  2002,  2006,  2010,
    2014
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
  "AUTO", "CONTINUE", "BOOL", "LONGBOOL", "WCHAR_T", "EXPLICIT", "IF",
  "SIZEOF", "UNION", "CHAR", "CLASS", "USING", "VOLATILE", "SIGNED",
  "CONST", "LONG", "STATIC", "INT", "ELSE", "SHORT", "NAMESPACE",
  "REGISTER", "TYPEDEF", "FRIEND", "FOR", "GOTO", "VIRTUAL", "INLINE",
  "CASE", "VOID", "STRUCT", "BREAK", "IDENTIFIER", "QUALIFIED_IDENTIFIER",
  "DTOR", "QUALIFIED_DTOR", "OBJ_IDENTIFIER", "QUALIFIED_OBJ_IDENTIFIER",
  "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "EMBEDDED_COMMANDS",
  "PREPROCESSOR", "WHITESPACE", "ADDVARIABLES", "$accept",
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364
};
# endif

#define YYPACT_NINF -384

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-384)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1910,  -384,    30,   102,  -384,   126,   236,     7,   168,  -384,
     175,   188,   190,  -384,   246,   197,   261,   -13,  -384,   132,
    -384,   110,  -384,   231,     4,     3,  -384,  2070,  -384,    90,
    -384,   233,   270,   247,   264,   271,   278,    63,    99,   326,
    -384,  1970,  -384,  -384,  -384,  -384,  2070,   210,   319,   323,
     229,  -384,   357,  -384,  -384,  -384,  -384,  -384,   164,   339,
    -384,    55,  -384,  -384,  1090,  -384,  -384,  -384,  -384,  -384,
     370,    44,   377,     8,   329,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,   328,   207,   389,
    -384,   399,   118,   404,    14,  -384,   408,   417,   424,  -384,
    -384,   436,  1970,   378,  -384,  -384,   438,   444,  2070,   281,
     458,  -384,  -384,  -384,  -384,  -384,  1902,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,   474,  -384,  -384,   229,  -384,
      19,  -384,    90,   291,   324,   478,   480,    71,  -384,    21,
      24,  1970,  -384,   313,  -384,  -384,   571,   492,  -384,   -49,
    2070,   229,  -384,   496,    50,  -384,  1375,    -7,  1147,  -384,
    -384,  -384,   481,   482,  -384,  -384,   483,   495,   486,   487,
     488,  -384,  -384,  -384,   489,   490,  -384,  -384,   491,  -384,
    -384,  -384,  -384,  1204,   416,   281,   500,   500,  -384,  -384,
     232,  -384,  1902,  1902,  1902,  -384,  -384,  -384,  -384,  -384,
    -384,   511,   342,   365,   321,    43,   517,  -384,  -384,  1902,
      89,   364,   363,   223,    26,   493,   527,   515,   549,  2153,
    -384,  -384,  -384,   255,    84,  -384,   533,   150,  -384,  1671,
     568,   568,   281,  -384,  1902,  1686,  -384,  -384,  -384,  1261,
    -384,  -384,  -384,  -384,   558,  -384,   577,   663,  -384,  -384,
     562,   579,   584,    98,   939,   563,   586,   501,   588,   503,
    1902,   573,   200,  -384,   257,  -384,  -384,  -384,  -384,   755,
    -384,  -384,  -384,  -384,  -384,  2070,   281,  -384,  -384,  -384,
    -384,   229,   555,  -384,  -384,    59,  -384,   386,  -384,   580,
     581,   582,   -15,  2070,   578,   583,   229,  -384,   172,  -384,
    1432,  -384,   202,   214,   222,   133,  -384,  -384,    48,  -384,
    -384,  1318,  -384,  -384,  -384,   585,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,   587,   317,  -384,   115,  -384,  -384,  1902,
    1730,  1902,   595,  1759,   595,  -384,  -384,   939,  1902,   331,
    -384,  1902,  1902,  1902,  1902,  1902,  1902,  1902,  1902,  1902,
    1902,  1902,  1902,  1902,  1902,  1902,  1902,  1902,  -384,  -384,
    -384,  -384,  -384,  1902,  -384,  -384,  1902,  -384,  -384,  -384,
    -384,  1902,  -384,  -384,  -384,  1902,  -384,   516,  -384,   187,
    -384,   596,  1778,  -384,   181,  1638,  -384,  -384,  -384,   313,
    1812,  -384,   847,   939,  1902,  1902,  -384,   332,   556,  -384,
    1902,   378,  1027,   591,   590,  -384,   939,  1902,  -384,  -384,
    -384,   281,   569,  1902,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,   229,  -384,  -384,   608,    92,   341,  -384,  -384,   592,
     492,  -384,  -384,   343,  -384,  -384,   348,  -384,  -384,   356,
    -384,  -384,   374,   392,   394,  -384,  -384,  1489,    -7,  -384,
    -384,  -384,  -384,  -384,   192,   611,   212,   253,  1902,   611,
     217,   479,  -384,  -384,  -384,  -384,  -384,    89,    89,   364,
     364,   363,   363,   363,   363,   223,   223,    26,   493,   527,
     515,   549,   434,  -384,  -384,  -384,  -384,  -384,   654,  -384,
    -384,  -384,   208,  -384,  -384,   234,  -384,  -384,   235,   239,
    -384,   660,   242,  -384,  1831,  -384,  -384,   939,  -384,  -384,
    1902,  -384,   135,   360,   593,  -384,   642,   281,  -384,  -384,
     645,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  1546,  -384,  -384,   595,   611,  -384,
     268,   595,   611,  2023,  1902,  -384,  -384,  1642,  -384,   939,
     939,  1902,   939,  1860,   369,  -384,  -384,  -384,   646,  -384,
    -384,  -384,  -384,  -384,  -384,   595,  -384,   595,  2023,  -384,
    -384,  -384,  -384,  -384,  -384,   244,   597,   939,   249,  1866,
    -384,  -384,   648,   939,  -384,   939,   939,   252,  -384,  -384,
    -384,  -384,   939,  -384
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   126,   188,   187,   142,   141,     0,   180,     0,   138,
     167,   194,   165,   145,     0,   166,     0,     0,   147,   173,
     146,   171,   140,   168,   169,     0,   139,     0,   148,   144,
     143,   193,     0,     0,     0,     0,     0,   163,   164,     0,
       3,     2,   120,   122,   127,   149,     0,     0,   160,     0,
       0,   125,     0,   129,   130,   131,   128,   124,     0,     0,
     123,   151,   220,   219,     0,   156,   157,   158,   159,   212,
     186,   184,   181,   182,     0,   199,   226,   197,   319,   321,
     320,   322,   198,   311,   313,   312,   314,     0,     0,     0,
     205,   179,   177,   174,   175,   203,   189,   190,   172,   200,
     201,   170,     0,   233,   141,   144,   163,   164,     0,     0,
       0,   225,   315,   317,   316,   318,   256,   258,   260,   261,
     257,   195,   259,   196,     1,     0,   121,   150,     0,   132,
       0,   133,     0,   249,   251,   250,   252,     0,   243,   245,
       0,     0,   300,     0,   285,   288,     0,     0,   273,   263,
       0,   283,   255,     0,   274,   277,     0,     0,     0,   242,
     218,   216,   192,   185,   213,   214,   183,     0,     0,     0,
       0,   235,   211,   209,   191,   178,   206,   207,   176,   221,
     222,   204,   202,     0,     0,     0,   249,   251,   250,   252,
       0,   262,     0,     0,     0,    37,    38,    39,    40,     8,
       9,     0,    18,    19,    32,     0,    13,    16,    41,     0,
      45,    48,    51,    56,    59,    61,    63,    65,    67,    69,
      71,    14,   256,     0,     0,   161,   229,     0,   227,     0,
     253,   254,     0,   134,     0,     0,   246,   286,   290,     0,
     367,   368,   369,   370,   362,   363,     0,     0,   301,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    84,     0,   101,    87,    88,    89,     0,
      90,    91,    92,    93,   119,     0,     0,   299,   289,   265,
     264,   284,   279,   247,   248,   266,   275,     0,   152,     0,
       0,     0,     0,     0,     0,     0,     0,   328,     0,   327,
       0,   323,     0,     0,     0,     0,   340,   344,     0,   338,
     240,     0,   224,   217,   215,     0,   236,   237,   238,   223,
     210,   208,   232,     0,     0,   135,     0,    34,    33,     0,
       0,     0,    24,     0,    25,    12,    11,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,    82,
      81,    80,    79,     0,    78,    77,     0,    76,    75,    74,
      73,     0,   136,   287,   291,     0,   162,     0,   269,    69,
      86,     0,     0,   244,     0,     0,   305,   303,   231,     0,
       0,    99,     0,     0,     0,     0,   116,     0,     0,   115,
       0,     0,     0,     0,     0,   114,     0,     0,    98,   302,
     102,     0,   280,     0,   268,   267,   276,   278,   333,   331,
     332,     0,   329,   330,   336,     0,     0,   334,   292,     0,
       0,   153,   324,     0,   343,   347,     0,   341,   345,     0,
     342,   346,     0,     0,     0,   348,   352,     0,     0,   241,
     239,   234,   137,    10,     0,    20,     0,     0,     0,    21,
       0,     4,    15,    17,    44,    42,    43,    46,    47,    50,
      49,    54,    52,    53,    55,    58,    57,    60,    62,    64,
      66,    68,     0,    72,   230,   228,   270,   271,     0,   304,
     308,   309,     0,   364,   365,     0,   100,    96,     0,     0,
     117,     0,     0,   112,     0,   113,   118,     0,    94,    85,
       0,   281,     0,     0,     0,   293,     0,     0,   325,   295,
       0,   358,   361,   356,   359,   357,   360,   351,   355,   349,
     353,   350,   354,   154,     0,   339,    36,    26,    22,    30,
       0,    27,    23,     0,     0,   272,   306,     0,   366,     0,
       0,     0,     0,     0,     0,    95,   282,   294,     0,   326,
     337,   297,   335,   296,   155,    28,    31,    29,     5,     6,
      70,   307,   310,   106,   105,     0,   103,     0,     0,     0,
     298,     7,     0,     0,   108,     0,     0,     0,   107,   104,
     109,   110,     0,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -384,  -384,  -384,  -384,  -384,  -218,  -384,   344,  -201,  -139,
    -384,   154,   158,   134,   155,   334,   335,   333,   336,   337,
    -209,  -208,  -111,  -384,  -186,  -246,  -230,  -384,   290,  -384,
    -221,  -384,  -384,  -384,  -384,  -384,   -84,   -19,    12,  -383,
     -37,     1,  -152,  -384,  -149,     0,  -384,   322,  -384,  -384,
    -384,  -148,  -384,  -384,  -384,   -96,   462,   420,  -141,   -47,
    -384,  -384,  -109,  -384,  -384,   415,  -384,  -384,  -117,  -384,
    -384,  -384,  -370,  -384,  -384,   256,  -289,   283,   189,  -384,
     259,   407,  -384,   320,  -384
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,   568,   204,   205,   206,   207,   332,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   263,   371,   264,   381,   265,   266,   267,   268,
     269,   270,   271,   504,   272,   273,    41,    42,   274,    44,
      45,   275,    47,    48,    49,   276,   227,   228,    51,    52,
      53,    54,    55,    56,    57,   137,   138,   282,   139,    58,
      59,   152,   230,   153,   154,   155,    60,   299,   145,   146,
     277,   236,   387,   492,    61,   300,   301,   426,   427,   308,
     309,   147,   244,   245,   246
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      50,    46,   334,   140,   294,   221,   326,   295,   297,   127,
     283,   432,    43,   190,   404,   491,   384,   102,   183,   505,
     379,   380,   126,   238,   398,   231,   392,   109,   108,   279,
     278,   280,   223,   234,   225,    87,   352,    87,   142,   410,
     100,    50,    46,    69,   165,   159,   128,   302,   303,   304,
     177,   379,   380,    43,   327,   328,   337,   239,   237,   151,
     150,   286,   447,   353,    50,    46,    62,   397,   235,   156,
     340,   127,   338,    88,   311,   120,    43,   448,   231,   287,
     161,   224,    70,   157,    89,   305,    89,   101,    71,   324,
      72,   166,    73,   341,   342,   306,   307,   178,   142,   121,
     232,   103,    50,    46,   284,   233,   142,   374,   185,   298,
     192,   122,   456,   127,    43,   460,   461,   226,   373,   193,
     194,   195,   196,   221,   386,   162,   515,   163,   453,   484,
     197,   198,   396,   199,   343,   123,   488,   414,    63,   415,
     283,    50,    46,   454,   407,   457,    95,   200,   294,   142,
     281,   295,   297,    43,   173,   424,   296,   293,    50,    46,
     569,    96,   410,   497,   126,   376,   379,   380,    90,   557,
      43,   201,   495,   379,   380,    64,   508,   572,   142,   377,
     482,   429,    74,    50,    46,   581,   142,   442,   443,   444,
     110,    97,   143,    98,   489,    43,   202,   203,   144,   174,
     143,   175,   464,   465,   466,   536,   428,    91,   498,   499,
     338,    75,   330,    92,   502,    93,   331,    94,   363,   221,
     126,   407,   221,   546,    76,   538,    77,   462,   406,   366,
     542,   410,   348,    82,   284,   445,   446,   547,   127,    50,
      46,   338,   349,   350,   129,   432,   338,   548,   549,   425,
     351,    43,   550,   298,   537,   552,   127,   582,   541,   116,
     483,   232,   585,   338,   407,   592,   325,    99,   407,   111,
     539,   407,   540,   407,   386,   411,   117,   555,   407,   221,
     424,   407,   407,   118,   232,   566,   407,   151,   150,   372,
     119,   408,   126,   421,   433,   294,   509,   407,   295,   297,
     296,   293,   511,   222,   434,   435,   436,   229,   516,   169,
     170,    50,    46,   520,   439,   223,   437,   438,   554,   573,
     574,   132,   576,    43,   440,   441,   124,   133,   134,    35,
      36,   135,   136,   130,    65,    66,   117,   565,    67,    68,
     229,   567,   335,   336,    78,    79,   232,   584,    80,    81,
     148,   452,   149,   589,   330,   590,   591,   131,   331,    83,
      84,   407,   593,    85,    86,   575,   500,   578,   112,   113,
     517,   141,   114,   115,   512,   518,   424,   333,   167,   186,
     187,   331,   294,   188,   189,   295,   297,   344,   345,   517,
       2,     3,     4,   587,   559,   558,   104,   416,   407,   556,
     298,   346,     7,   579,   347,     9,   160,    10,    11,    12,
      13,   240,   241,   164,    15,   242,   243,    18,    19,    20,
      21,    22,    23,   171,    24,   184,    26,   168,    28,   202,
     203,   105,    30,   570,    31,   172,   386,     2,     3,     4,
     176,   106,   107,   104,   179,   521,   522,   296,   293,     7,
     523,   524,     9,   180,    10,    11,    12,    13,   525,   526,
     181,    15,   544,   407,    18,    19,    20,    21,    22,    23,
     191,    24,   182,    26,   121,    28,   527,   528,   105,    30,
     123,    31,   471,   472,   473,   474,   222,   298,   106,   107,
     120,   192,   122,   247,   529,   530,   531,   532,   467,   468,
     193,   194,   195,   196,   469,   470,   142,   475,   476,   285,
     315,   197,   198,   249,   199,   323,   229,   312,   313,   314,
     316,   317,   318,   329,   339,   319,   320,   321,   200,   354,
       2,     3,     4,   355,   296,   293,   104,   250,   251,   252,
       6,   253,     7,     8,   254,     9,   255,    10,    11,    12,
      13,   256,   201,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,   356,    24,   257,    26,    27,    28,   258,
     259,   105,    30,   260,    31,    32,   261,   262,   203,   357,
     375,   106,   107,   192,   382,   247,   248,   389,   543,   390,
     393,   394,   193,   194,   195,   196,   395,   399,   400,   401,
     402,   403,   413,   197,   198,   249,   199,   405,   418,   419,
     420,   458,   422,   486,   226,   501,   510,   423,   507,   450,
     200,   451,     2,     3,     4,   506,   519,   331,   104,   250,
     251,   252,     6,   253,     7,     8,   254,     9,   255,    10,
      11,    12,    13,   256,   201,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,   514,    24,   257,    26,    27,
      28,   258,   259,   105,    30,   260,    31,    32,   261,   262,
     203,   545,   551,   106,   107,   192,   561,   247,   391,   563,
     580,   583,   588,   463,   193,   194,   195,   196,   477,   479,
     478,   560,   503,   480,   383,   197,   198,   249,   199,   485,
     481,   412,   417,   534,   513,   430,   562,   535,     0,   493,
       0,     0,   200,     0,     2,     3,     4,     0,     0,     0,
     104,   250,   251,   252,     6,   253,     7,     8,   254,     9,
     255,    10,    11,    12,    13,   256,   201,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,    24,   257,
      26,    27,    28,   258,   259,   105,    30,   260,    31,    32,
     261,   262,   203,     0,     0,   106,   107,   192,     0,   247,
     409,     0,     0,     0,     0,     0,   193,   194,   195,   196,
       0,     0,     0,     0,     0,     0,     0,   197,   198,   249,
     199,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     2,     3,     4,     0,
       0,     0,   104,   250,   251,   252,     6,   253,     7,     8,
     254,     9,   255,    10,    11,    12,    13,   256,   201,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
      24,   257,    26,    27,    28,   258,   259,   105,    30,   260,
      31,    32,   261,   262,   203,     0,     0,   106,   107,   192,
       0,   247,   496,     0,     0,     0,     0,     0,   193,   194,
     195,   196,     0,     0,     0,     0,     0,     0,     0,   197,
     198,   249,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     2,     3,
       4,     0,     0,     0,   104,   250,   251,   252,     6,   253,
       7,     8,   254,     9,   255,    10,    11,    12,    13,   256,
     201,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,    24,   257,    26,    27,    28,   258,   259,   105,
      30,   260,    31,    32,   261,   262,   203,     0,     0,   106,
     107,   192,     0,   247,     0,     0,     0,     0,     0,     0,
     193,   194,   195,   196,     0,     0,     0,     0,     0,     0,
       0,   197,   198,   249,   199,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       2,     3,     4,     0,     0,     0,   104,   250,   251,   252,
       6,   253,     7,     8,   254,     9,   255,    10,    11,    12,
      13,   256,   201,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,    24,   257,    26,    27,    28,   258,
     259,   105,    30,   260,    31,    32,   261,   262,   203,   192,
       0,   106,   107,     0,     0,     0,     0,     0,   193,   194,
     195,   196,     0,     0,     0,     0,     0,     0,     0,   197,
     198,   249,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     2,     3,
       4,     0,     0,     0,   104,     0,     0,     0,     6,     0,
       7,     0,     0,     9,     0,    10,    11,    12,    13,     0,
     201,    14,    15,    16,   158,    18,    19,    20,    21,    22,
      23,     0,    24,     0,    26,    27,    28,     0,     0,   105,
      30,     0,    31,    32,     1,   202,   203,     0,     0,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     0,     0,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,     0,    10,    11,
      12,    13,   310,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
       0,     1,    29,    30,     0,    31,    32,     0,   125,    34,
      35,    36,    37,    38,     0,     0,     0,     0,     2,     3,
       4,     0,     0,     0,     5,     0,     0,     0,     6,     0,
       7,     8,     0,     9,     0,    10,    11,    12,    13,   322,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,     0,     1,    29,
      30,     0,    31,    32,     0,   125,    34,    35,    36,    37,
      38,     0,     0,     0,     0,     2,     3,     4,     0,     0,
       0,     5,     0,     0,     0,     6,     0,     7,     8,     0,
       9,     0,    10,    11,    12,    13,   388,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,    24,
      25,    26,    27,    28,     0,     1,    29,    30,     0,    31,
      32,     0,   125,    34,    35,    36,    37,    38,     0,     0,
       0,     0,     2,     3,     4,     0,     0,     0,     5,     0,
       0,     0,     6,     0,     7,     8,     0,     9,     0,    10,
      11,    12,    13,   449,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    24,    25,    26,    27,
      28,     0,     1,    29,    30,     0,    31,    32,     0,   125,
      34,    35,    36,    37,    38,     0,     0,     0,     0,     2,
       3,     4,     0,     0,     0,     5,     0,     0,     0,     6,
       0,     7,     8,     0,     9,     0,    10,    11,    12,    13,
     288,     0,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,    24,    25,    26,    27,    28,     0,     0,
      29,    30,     0,    31,    32,     0,   125,    34,    35,    36,
      37,    38,     0,     0,     0,     0,     2,     3,     4,   289,
     290,   291,   104,     0,     0,     0,     6,     0,     7,     0,
       0,     9,     0,    10,    11,    12,    13,   431,     0,    14,
      15,    16,   292,    18,    19,    20,    21,    22,    23,     0,
      24,     0,    26,     0,    28,     0,     0,    29,    30,     0,
      31,    32,     0,   125,    34,    35,    36,    37,    38,     0,
       0,     0,     0,     2,     3,     4,   289,   290,   291,   104,
       0,     0,     0,     6,     0,     7,     0,     0,     9,     0,
      10,    11,    12,    13,   533,     0,    14,    15,    16,   292,
      18,    19,    20,    21,    22,    23,     0,    24,     0,    26,
       0,    28,     0,     0,    29,    30,     0,    31,    32,     0,
     125,    34,    35,    36,    37,    38,     0,     0,     0,     0,
       2,     3,     4,   289,   290,   291,   104,     0,     0,     0,
       6,     0,     7,     0,     0,     9,     0,    10,    11,    12,
      13,   564,     0,    14,    15,    16,   292,    18,    19,    20,
      21,    22,    23,     0,    24,     0,    26,     0,    28,     0,
       0,    29,    30,     0,    31,    32,     0,   125,    34,    35,
      36,    37,    38,     0,     0,     0,     0,     2,     3,     4,
     289,   290,   291,   104,     0,     0,     0,     6,     0,     7,
       0,     0,     9,     0,    10,    11,    12,    13,     0,     0,
      14,    15,    16,   292,    18,    19,    20,    21,    22,    23,
       0,    24,     0,    26,     0,    28,     0,     0,    29,    30,
       0,    31,    32,     0,   125,    34,    35,    36,    37,    38,
     192,     0,   385,   490,   192,     0,   385,   571,     0,   193,
     194,   195,   196,   193,   194,   195,   196,     0,     0,     0,
     197,   198,     0,   199,   197,   198,     0,   199,     0,     0,
       0,     0,     0,   192,     0,     0,     0,   200,   378,     0,
       0,   200,   193,   194,   195,   196,     0,     0,   192,     0,
     385,     0,     0,   197,   198,     0,   199,   193,   194,   195,
     196,   201,     0,     0,     0,   201,     0,     0,   197,   198,
     200,   199,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   200,   202,   203,     0,     0,
     202,   203,   192,   455,   201,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,     0,     0,     0,     0,   201,
       0,     0,   197,   198,     0,   199,     0,     0,     0,   202,
     203,   192,   459,     0,     0,     0,     0,     0,     0,   200,
     193,   194,   195,   196,   202,   203,     0,     0,     0,     0,
     192,   197,   198,     0,   199,   487,     0,     0,     0,   193,
     194,   195,   196,   201,     0,     0,     0,     0,   200,     0,
     197,   198,     0,   199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   192,   494,     0,   200,   202,   203,
       0,     0,   201,   193,   194,   195,   196,     0,     0,     0,
       0,     0,     0,   192,   197,   198,     0,   199,     0,     0,
       0,   201,   193,   194,   195,   196,     0,   202,   203,     0,
       0,   200,     0,   197,   198,   553,   199,     0,     0,     0,
       0,     0,   192,   577,     0,     0,   202,   203,   192,   586,
     200,   193,   194,   195,   196,   201,     0,   193,   194,   195,
     196,     0,   197,   198,     0,   199,     0,     0,   197,   198,
       0,   199,     0,     0,   201,     0,     0,     0,     0,   200,
     202,   203,     0,     0,   192,   200,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,     0,     0,   202,
     203,     0,     0,   201,   197,   198,     0,   199,     0,   201,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,   200,     0,     0,     0,     0,     0,     0,   202,   203,
       0,     2,     3,     4,   202,   203,     0,     5,     0,     0,
       0,     6,     0,     7,     8,   201,     9,     0,    10,    11,
      12,    13,     0,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
     202,   203,    29,    30,     1,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     0,     0,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,     0,    10,    11,
      12,    13,     0,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
       0,     0,    29,    30,     0,    31,    32,     0,   125,    34,
      35,    36,    37,    38,     2,     3,     4,     0,     0,     0,
     104,     0,     0,     0,     6,     0,     7,     0,     0,     9,
       0,    10,    11,    12,    13,     0,     0,    14,    15,    16,
       0,    18,    19,    20,    21,    22,    23,     0,    24,     0,
      26,    27,    28,     0,     0,   105,    30,     0,    31,    32,
       0,     2,     3,     4,     0,   106,   107,   104,     0,     0,
       0,     0,     0,     7,     0,     0,     9,     0,    10,    11,
      12,    13,     0,     0,     0,    15,     0,     0,    18,    19,
      20,    21,    22,    23,     0,    24,   358,    26,     0,    28,
       0,   359,   105,    30,     0,    31,     0,     0,     0,     0,
       0,   360,   106,   107,     0,     0,     0,     0,   361,   362,
       0,     0,     0,     0,   363,     0,     0,     0,     0,     0,
       0,     0,   364,   365,     0,   366,   367,   368,     0,   369,
     370
};

static const yytype_int16 yycheck[] =
{
       0,     0,   203,    50,   156,   116,   192,   156,   156,    46,
     151,   300,     0,   109,   260,   385,   234,    14,   102,   402,
     229,   229,    41,   140,   254,   134,   247,    27,    27,    78,
     147,    80,   128,    12,    15,    50,    10,    50,    14,   269,
      36,    41,    41,    36,    36,    64,    46,    54,    55,    56,
      36,   260,   260,    41,   193,   194,    13,   141,    34,    59,
      59,    11,    14,    37,    64,    64,    36,   253,    47,    14,
     209,   108,    29,    86,   158,    12,    64,    29,   187,    29,
      36,   128,    75,    28,    99,    92,    99,    83,    81,   185,
      83,    83,    85,     4,     5,   102,   103,    83,    14,    36,
      29,    98,   102,   102,   151,    34,    14,   224,   108,   156,
      12,    12,   330,   150,   102,   333,   337,    98,    34,    21,
      22,    23,    24,   234,   235,    81,    34,    83,    13,   375,
      32,    33,    34,    35,    45,    36,   382,    78,    36,    80,
     281,   141,   141,   329,    29,   331,    36,    49,   300,    14,
     150,   300,   300,   141,    36,   296,   156,   156,   158,   158,
     543,    51,   392,   393,   183,    15,   375,   375,    36,    34,
     158,    73,   390,   382,   382,    49,   406,   547,    14,    29,
     366,   298,    14,   183,   183,   568,    14,    54,    55,    56,
     100,    81,    28,    83,    13,   183,    98,    99,    34,    81,
      28,    83,   341,   342,   343,    13,    34,    75,   394,   395,
      29,    36,    12,    81,   400,    83,    16,    85,    31,   330,
     239,    29,   333,    15,    36,    13,    36,   338,    28,    42,
      13,   461,     9,    36,   281,   102,   103,    29,   275,   239,
     239,    29,    19,    20,    34,   534,    29,    13,    13,   296,
      27,   239,    13,   300,   455,    13,   293,    13,   459,    12,
     371,    29,    13,    29,    29,    13,    34,    36,    29,    36,
      17,    29,   458,    29,   385,   275,    12,   507,    29,   390,
     421,    29,    29,    12,    29,    17,    29,   287,   287,    34,
      12,    34,   311,   293,    92,   447,   407,    29,   447,   447,
     300,   300,   413,    12,   102,   103,    92,    16,   425,   102,
     103,   311,   311,   430,    92,   411,   102,   103,   504,   549,
     550,    92,   552,   311,   102,   103,     0,    98,    99,   100,
     101,   102,   103,    14,    98,    99,    12,   538,   102,   103,
      16,   542,    21,    22,    98,    99,    29,   577,   102,   103,
      11,    34,    13,   583,    12,   585,   586,    34,    16,    98,
      99,    29,   592,   102,   103,   551,    34,   553,    98,    99,
      29,    14,   102,   103,   421,    34,   517,    12,    49,    98,
      99,    16,   534,   102,   103,   534,   534,    23,    24,    29,
      51,    52,    53,   579,    34,   512,    57,    11,    29,   510,
     447,    38,    63,    34,    41,    66,    36,    68,    69,    70,
      71,    98,    99,    36,    75,   102,   103,    78,    79,    80,
      81,    82,    83,    34,    85,    47,    87,    99,    89,    98,
      99,    92,    93,   544,    95,    36,   547,    51,    52,    53,
      36,   102,   103,    57,    36,   102,   103,   447,   447,    63,
     102,   103,    66,    36,    68,    69,    70,    71,   102,   103,
      36,    75,    28,    29,    78,    79,    80,    81,    82,    83,
      12,    85,    36,    87,    36,    89,   102,   103,    92,    93,
      36,    95,   348,   349,   350,   351,    12,   534,   102,   103,
      12,    12,    12,    14,   102,   103,   102,   103,   344,   345,
      21,    22,    23,    24,   346,   347,    14,   352,   353,    13,
      15,    32,    33,    34,    35,    99,    16,    36,    36,    36,
      34,    34,    34,    12,     7,    36,    36,    36,    49,    36,
      51,    52,    53,     6,   534,   534,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    48,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    30,
      47,   102,   103,    12,    16,    14,    15,    29,   109,    12,
      28,    12,    21,    22,    23,    24,    12,    34,    12,    98,
      12,    98,    47,    32,    33,    34,    35,    34,    28,    28,
      28,    16,    34,    17,    98,    59,    47,    34,    28,    34,
      49,    34,    51,    52,    53,    34,    34,    16,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    47,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    17,    12,   102,   103,    12,    34,    14,    15,    34,
      34,    84,    34,   339,    21,    22,    23,    24,   354,   356,
     355,    98,   402,   357,   232,    32,    33,    34,    35,   377,
     363,   281,   287,   447,   421,   298,   517,   448,    -1,   389,
      -1,    -1,    49,    -1,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,   102,   103,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,   102,   103,    12,
      -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,   102,
     103,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    12,
      -1,   102,   103,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,
      63,    -1,    -1,    66,    -1,    68,    69,    70,    71,    -1,
      73,    74,    75,    76,    14,    78,    79,    80,    81,    82,
      83,    -1,    85,    -1,    87,    88,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    34,    98,    99,    -1,    -1,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    -1,    66,    -1,    68,    69,
      70,    71,    15,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      -1,    34,    92,    93,    -1,    95,    96,    -1,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,
      63,    64,    -1,    66,    -1,    68,    69,    70,    71,    15,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    85,    86,    87,    88,    89,    -1,    34,    92,
      93,    -1,    95,    96,    -1,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    -1,    63,    64,    -1,
      66,    -1,    68,    69,    70,    71,    15,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    85,
      86,    87,    88,    89,    -1,    34,    92,    93,    -1,    95,
      96,    -1,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    61,    -1,    63,    64,    -1,    66,    -1,    68,
      69,    70,    71,    15,    -1,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    85,    86,    87,    88,
      89,    -1,    34,    92,    93,    -1,    95,    96,    -1,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,
      -1,    63,    64,    -1,    66,    -1,    68,    69,    70,    71,
      15,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    85,    86,    87,    88,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,
      -1,    66,    -1,    68,    69,    70,    71,    15,    -1,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      85,    -1,    87,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    61,    -1,    63,    -1,    -1,    66,    -1,
      68,    69,    70,    71,    15,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    85,    -1,    87,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    -1,    63,    -1,    -1,    66,    -1,    68,    69,    70,
      71,    15,    -1,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    85,    -1,    87,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    61,    -1,    63,
      -1,    -1,    66,    -1,    68,    69,    70,    71,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    85,    -1,    87,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,    -1,    98,    99,   100,   101,   102,   103,
      12,    -1,    14,    15,    12,    -1,    14,    15,    -1,    21,
      22,    23,    24,    21,    22,    23,    24,    -1,    -1,    -1,
      32,    33,    -1,    35,    32,    33,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    49,    17,    -1,
      -1,    49,    21,    22,    23,    24,    -1,    -1,    12,    -1,
      14,    -1,    -1,    32,    33,    -1,    35,    21,    22,    23,
      24,    73,    -1,    -1,    -1,    73,    -1,    -1,    32,    33,
      49,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    98,    99,    -1,    -1,
      98,    99,    12,    13,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,    98,
      99,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      21,    22,    23,    24,    98,    99,    -1,    -1,    -1,    -1,
      12,    32,    33,    -1,    35,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    73,    -1,    -1,    -1,    -1,    49,    -1,
      32,    33,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    -1,    49,    98,    99,
      -1,    -1,    73,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    32,    33,    -1,    35,    -1,    -1,
      -1,    73,    21,    22,    23,    24,    -1,    98,    99,    -1,
      -1,    49,    -1,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    12,    13,    -1,    -1,    98,    99,    12,    13,
      49,    21,    22,    23,    24,    73,    -1,    21,    22,    23,
      24,    -1,    32,    33,    -1,    35,    -1,    -1,    32,    33,
      -1,    35,    -1,    -1,    73,    -1,    -1,    -1,    -1,    49,
      98,    99,    -1,    -1,    12,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    -1,    -1,    98,
      99,    -1,    -1,    73,    32,    33,    -1,    35,    -1,    73,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
      -1,    51,    52,    53,    98,    99,    -1,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    73,    66,    -1,    68,    69,
      70,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      98,    99,    92,    93,    34,    95,    96,    -1,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    -1,    66,    -1,    68,    69,
      70,    71,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    85,    86,    87,    88,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    99,
     100,   101,   102,   103,    51,    52,    53,    -1,    -1,    -1,
      57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,    66,
      -1,    68,    69,    70,    71,    -1,    -1,    74,    75,    76,
      -1,    78,    79,    80,    81,    82,    83,    -1,    85,    -1,
      87,    88,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    51,    52,    53,    -1,   102,   103,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    66,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    75,    -1,    -1,    78,    79,
      80,    81,    82,    83,    -1,    85,     3,    87,    -1,    89,
      -1,     8,    92,    93,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    18,   102,   103,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    42,    43,    44,    -1,    46,
      47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    51,    52,    53,    57,    61,    63,    64,    66,
      68,    69,    70,    71,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    85,    86,    87,    88,    89,    92,
      93,    95,    96,    98,    99,   100,   101,   102,   103,   111,
     112,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   158,   159,   160,   161,   162,   163,   164,   169,   170,
     176,   184,    36,    36,    49,    98,    99,   102,   103,    36,
      75,    81,    83,    85,    14,    36,    36,    36,    98,    99,
     102,   103,    36,    98,    99,   102,   103,    50,    86,    99,
      36,    75,    81,    83,    85,    36,    51,    81,    83,    36,
      36,    83,    14,    98,    57,    92,   102,   103,   151,   155,
     100,    36,    98,    99,   102,   103,    12,    12,    12,    12,
      12,    36,    12,    36,     0,    98,   147,   150,   155,    34,
      14,    34,    92,    98,    99,   102,   103,   165,   166,   168,
     169,    14,    14,    28,    34,   178,   179,   191,    11,    13,
     151,   155,   171,   173,   174,   175,    14,    28,    14,   147,
      36,    36,    81,    83,    36,    36,    83,    49,    99,   102,
     103,    34,    36,    36,    81,    83,    36,    36,    83,    36,
      36,    36,    36,   146,    47,   155,    98,    99,   102,   103,
     165,    12,    12,    21,    22,    23,    24,    32,    33,    35,
      49,    73,    98,    99,   114,   115,   116,   117,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,    12,   165,   169,    15,    98,   156,   157,    16,
     172,   172,    29,    34,    12,    47,   181,    34,   178,   146,
      98,    99,   102,   103,   192,   193,   194,    14,    15,    34,
      58,    59,    60,    62,    65,    67,    72,    86,    90,    91,
      94,    97,    98,   132,   134,   136,   137,   138,   139,   140,
     141,   142,   144,   145,   148,   151,   155,   180,   178,    78,
      80,   155,   167,   168,   169,    13,    11,    29,    15,    54,
      55,    56,    77,   151,   152,   154,   155,   161,   169,   177,
     185,   186,    54,    55,    56,    92,   102,   103,   189,   190,
      15,   146,    36,    36,    36,    15,    34,    34,    34,    36,
      36,    36,    15,    99,   165,    34,   134,   119,   119,    12,
      12,    16,   118,    12,   118,    21,    22,    13,    29,     7,
     119,     4,     5,    45,    23,    24,    38,    41,     9,    19,
      20,    27,    10,    37,    36,     6,    48,    30,     3,     8,
      18,    25,    26,    31,    39,    40,    42,    43,    44,    46,
      47,   133,    34,    34,   178,    47,    15,    29,    17,   130,
     131,   135,    16,   166,   115,    14,   132,   182,    15,    29,
      12,    15,   140,    28,    12,    12,    34,   134,   136,    34,
      12,    98,    12,    98,   135,    34,    28,    29,    34,    15,
     136,   155,   167,    47,    78,    80,    11,   175,    28,    28,
      28,   155,    34,    34,   168,   169,   187,   188,    34,   178,
     191,    15,   186,    92,   102,   103,    92,   102,   103,    92,
     102,   103,    54,    55,    56,   102,   103,    14,    29,    15,
      34,    34,    34,    13,   134,    13,   115,   134,    16,    13,
     115,   140,   132,   117,   119,   119,   119,   121,   121,   122,
     122,   123,   123,   123,   123,   124,   124,   125,   126,   127,
     128,   129,   134,   132,   135,   157,    17,    17,   135,    13,
      15,   182,   183,   193,    13,   115,    15,   136,   134,   134,
      34,    59,   134,   138,   143,   149,    34,    28,   136,   132,
      47,   132,   169,   187,    47,    34,   178,    29,    34,    34,
     178,   102,   103,   102,   103,   102,   103,   102,   103,   102,
     103,   102,   103,    15,   185,   190,    13,   118,    13,    17,
     134,   118,    13,   109,    28,    17,    15,    29,    13,    13,
      13,    12,    13,    34,   134,   136,   132,    34,   178,    34,
      98,    34,   188,    34,    15,   118,    17,   118,   113,   149,
     132,    15,   182,   136,   136,   134,   136,    13,   134,    34,
      34,   149,    13,    84,   136,    13,    13,   134,    34,   136,
     136,   136,    13,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   111,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   121,   121,   122,   122,   122,   123,   123,
     123,   124,   124,   124,   124,   124,   125,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   135,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   143,   143,   144,   144,   144,   144,   144,   145,
     146,   146,   147,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   151,
     151,   152,   152,   152,   152,   152,   153,   153,   153,   153,
     154,   154,   154,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   156,   156,   157,
     157,   158,   158,   159,   160,   161,   161,   162,   162,   163,
     164,   164,   164,   165,   165,   166,   166,   167,   167,   168,
     168,   168,   168,   168,   168,   169,   170,   170,   170,   170,
     170,   170,   170,   171,   171,   171,   171,   171,   171,   172,
     172,   172,   172,   173,   173,   173,   173,   174,   174,   175,
     175,   175,   175,   175,   175,   176,   176,   176,   176,   176,
     176,   176,   177,   177,   177,   177,   177,   177,   177,   178,
     179,   180,   180,   181,   181,   182,   182,   182,   182,   183,
     183,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   185,   185,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   187,   187,   188,   188,   189,   189,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   191,   192,   192,   193,   193,   194,   194,   194,
     194
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
       2,     3,     3,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     3,     2,     3,     3,     4,     3,
       4,     3,     2,     3,     3,     4,     3,     4,     3,     2,
       2,     3,     3,     4,     4,     2,     2,     1,     3,     1,
       3,     4,     4,     2,     5,     3,     4,     4,     4,     5,
       4,     5,     3,     1,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     1,     2,     2,     2,     3,     3,     2,
       3,     3,     4,     1,     1,     2,     3,     1,     3,     2,
       3,     4,     5,     1,     2,     2,     3,     4,     2,     3,
       3,     4,     2,     3,     4,     3,     4,     4,     5,     2,
       1,     1,     2,     2,     3,     1,     3,     4,     2,     1,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     3,     4,     1,     1,     2,
       2,     2,     2,     2,     1,     3,     1,     3,     1,     3,
       1,     2,     2,     2,     1,     2,     2,     2,     2,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     3,     3,     4,     1,     1,     1,
       1
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
#line 74 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtCppTranslationUnit_create((yyvsp[0]).pContext);
  (yyval).pContext = adtCpp_setRoot(pObj);

  adtCpp_releaseObject(pObj);
}
#line 2155 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 3:
#line 83 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add(adtCpp_getRoot(), (yyvsp[0]).pContext);
}
#line 2163 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 4:
#line 91 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 2171 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 5:
#line 95 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-6]).sValue, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2179 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 6:
#line 101 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclarationList_create((yyvsp[0]).pContext);
}
#line 2187 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 7:
#line 105 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2195 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 8:
#line 112 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2203 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2211 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create((yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 2219 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 1, 0);
}
#line 2227 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 12:
#line 128 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 2235 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 13:
#line 132 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2243 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 14:
#line 139 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionList_create((yyvsp[0]).pContext);
}
#line 2251 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 15:
#line 143 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2259 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 16:
#line 150 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDirectedExpression_create((yyvsp[0]).pContext);
}
#line 2267 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 17:
#line 154 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2275 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 18:
#line 165 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 0, 0);
}
#line 2283 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 1, 0);
}
#line 2291 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 20:
#line 173 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 0, 1);
}
#line 2299 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 21:
#line 177 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 1, 1);
}
#line 2307 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 22:
#line 181 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 2315 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 23:
#line 185 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 1, 1);
}
#line 2323 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 24:
#line 189 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2331 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 25:
#line 193 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 1, 0);
}
#line 2339 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 26:
#line 197 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 0, 1);
}
#line 2347 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 27:
#line 201 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 1, 1);
}
#line 2355 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 28:
#line 205 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1);
}
#line 2363 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1, 1);
}
#line 2371 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 30:
#line 216 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpressionDims_create((yyvsp[-1]).pContext);
}
#line 2379 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 31:
#line 220 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 2387 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 32:
#line 227 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2395 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 33:
#line 231 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 1);
}
#line 2403 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 34:
#line 235 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2411 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 35:
#line 239 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 2419 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 36:
#line 243 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 2427 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 37:
#line 250 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(0);
}
#line 2435 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 38:
#line 254 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(1);
}
#line 2443 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 39:
#line 258 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(2);
}
#line 2451 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 40:
#line 262 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(3);
}
#line 2459 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 41:
#line 269 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2467 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 42:
#line 273 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2475 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 43:
#line 277 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2483 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 44:
#line 281 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2491 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 45:
#line 288 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2499 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 46:
#line 292 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2507 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 47:
#line 296 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2515 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 48:
#line 303 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2523 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 49:
#line 307 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2531 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 50:
#line 311 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2539 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 51:
#line 318 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2547 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 52:
#line 322 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2555 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 53:
#line 326 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2563 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 54:
#line 330 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2571 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 55:
#line 334 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(3, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2579 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 56:
#line 341 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2587 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 57:
#line 345 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2595 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 58:
#line 349 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2603 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 59:
#line 356 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2611 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 60:
#line 360 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2619 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 61:
#line 367 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2627 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 62:
#line 371 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2635 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 63:
#line 378 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2643 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 64:
#line 382 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2651 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 65:
#line 389 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2659 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 66:
#line 393 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2667 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 67:
#line 400 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2675 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 68:
#line 404 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2683 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 69:
#line 411 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[0]).pContext, 0, 0);
}
#line 2691 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 70:
#line 415 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2699 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 71:
#line 422 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 2707 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 72:
#line 426 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2715 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 73:
#line 433 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(0);
}
#line 2723 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 74:
#line 437 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(1);
}
#line 2731 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 75:
#line 441 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(2);
}
#line 2739 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 76:
#line 445 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(3);
}
#line 2747 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 77:
#line 449 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(4);
}
#line 2755 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 78:
#line 453 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(5);
}
#line 2763 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 79:
#line 457 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(6);
}
#line 2771 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 80:
#line 461 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(7);
}
#line 2779 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 81:
#line 465 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(8);
}
#line 2787 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 82:
#line 469 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(9);
}
#line 2795 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 83:
#line 473 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(10);
}
#line 2803 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 84:
#line 480 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, 0);
}
#line 2811 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 85:
#line 484 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2819 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 86:
#line 491 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConstantExpression_create((yyvsp[0]).pContext);
}
#line 2827 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 87:
#line 498 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 2835 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 88:
#line 502 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0);
}
#line 2843 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 89:
#line 506 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2851 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 90:
#line 510 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2859 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 91:
#line 514 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2867 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 92:
#line 518 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 2875 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 93:
#line 522 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 2883 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 94:
#line 529 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).sValue, 0);
}
#line 2891 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 95:
#line 533 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 2899 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 96:
#line 537 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, 0, 1);
}
#line 2907 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 97:
#line 544 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create(0);
}
#line 2915 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 98:
#line 548 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create((yyvsp[-1]).pContext);
}
#line 2923 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 99:
#line 555 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0);
}
#line 2931 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 100:
#line 559 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext);
}
#line 2939 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 101:
#line 566 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatementSeq_create((yyvsp[0]).pContext);
}
#line 2947 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 102:
#line 570 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2955 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 103:
#line 581 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1);
}
#line 2963 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 104:
#line 585 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1);
}
#line 2971 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 105:
#line 589 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 2979 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 106:
#line 596 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 2987 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 107:
#line 600 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[-5]).pContext, 1);
}
#line 2995 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 108:
#line 604 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-3]).pContext, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3003 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 109:
#line 608 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 3011 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 110:
#line 612 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 3019 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 111:
#line 616 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-5]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 3027 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 112:
#line 623 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create((yyvsp[0]).pContext, 0);
}
#line 3035 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 113:
#line 627 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create(0, (yyvsp[0]).pContext);
}
#line 3043 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 114:
#line 634 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 0);
}
#line 3051 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 115:
#line 638 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 1);
}
#line 3059 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 116:
#line 642 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 2);
}
#line 3067 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 117:
#line 646 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create((yyvsp[-1]).pContext, 0, 2);
}
#line 3075 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 118:
#line 650 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, (yyvsp[-1]).sValue, 3);
}
#line 3083 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 119:
#line 657 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationStatement_create((yyvsp[0]).pContext);
}
#line 3091 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 120:
#line 664 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationSeq_create((yyvsp[0]).pContext);
}
#line 3099 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 121:
#line 668 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3107 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 122:
#line 675 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 3115 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 123:
#line 679 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, (yyvsp[0]).pContext, 0, 0);
}
#line 3123 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 124:
#line 683 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, (yyvsp[0]).pContext, 0);
}
#line 3131 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 125:
#line 687 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, (yyvsp[0]).pContext);
}
#line 3139 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 126:
#line 691 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, 0);
}
#line 3147 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 127:
#line 698 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3155 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 128:
#line 702 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3163 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 129:
#line 706 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3171 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 130:
#line 710 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3179 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 131:
#line 714 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 3187 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 132:
#line 721 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0);
}
#line 3195 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 133:
#line 725 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 3203 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 134:
#line 729 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 3211 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 135:
#line 733 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 1);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3227 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 136:
#line 745 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 0);
}
#line 3235 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 137:
#line 749 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3251 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 138:
#line 764 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(0);
}
#line 3259 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 139:
#line 768 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(1);
}
#line 3267 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 140:
#line 772 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(2);
}
#line 3275 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 141:
#line 776 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(3);
}
#line 3283 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 142:
#line 780 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(4);
}
#line 3291 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 143:
#line 784 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(5);
}
#line 3299 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 144:
#line 788 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(6);
}
#line 3307 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 145:
#line 792 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(7);
}
#line 3315 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 146:
#line 796 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(8);
}
#line 3323 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 147:
#line 800 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(9);
}
#line 3331 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 148:
#line 804 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(10);
}
#line 3339 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 149:
#line 811 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifierList_create((yyvsp[0]).pContext);
}
#line 3347 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 150:
#line 815 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3355 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 151:
#line 822 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 3365 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 152:
#line 828 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-2]).pContext, 0, 0, 1);
}
#line 3375 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 153:
#line 834 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 3385 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 154:
#line 840 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 1);
}
#line 3395 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 155:
#line 846 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 3405 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 156:
#line 855 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 0);
}
#line 3415 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 157:
#line 861 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 1);
}
#line 3425 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 158:
#line 867 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 0);
}
#line 3433 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 159:
#line 871 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 1);
}
#line 3441 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 160:
#line 878 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[0]).pContext, 0);
}
#line 3449 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 161:
#line 882 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[-2]).pContext, 1);
}
#line 3457 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 162:
#line 886 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1);
}
#line 3465 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 163:
#line 900 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 0, 0);
}
#line 3473 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 164:
#line 904 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 1, 0);
}
#line 3481 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 165:
#line 908 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 0);
}
#line 3489 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 166:
#line 912 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 0);
}
#line 3497 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 167:
#line 916 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 0);
}
#line 3505 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 168:
#line 920 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 0);
}
#line 3513 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 169:
#line 924 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 0);
}
#line 3521 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 170:
#line 928 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 0);
}
#line 3529 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 171:
#line 932 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 0);
}
#line 3537 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 172:
#line 936 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 0);
}
#line 3545 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 173:
#line 940 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 0);
}
#line 3553 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 174:
#line 944 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 0);
}
#line 3561 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 175:
#line 948 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 0);
}
#line 3569 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 176:
#line 952 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 0);
}
#line 3577 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 177:
#line 956 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 0);
}
#line 3585 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 178:
#line 960 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 0);
}
#line 3593 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 179:
#line 964 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 0);
}
#line 3601 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 180:
#line 968 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 0);
}
#line 3609 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 181:
#line 972 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 0);
}
#line 3617 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 182:
#line 976 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 0);
}
#line 3625 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 183:
#line 980 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 0);
}
#line 3633 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 184:
#line 984 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 0);
}
#line 3641 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 185:
#line 988 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 0);
}
#line 3649 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 186:
#line 992 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 0);
}
#line 3657 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 187:
#line 996 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 0);
}
#line 3665 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1000 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 0);
}
#line 3673 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1004 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 0);
}
#line 3681 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1008 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 0);
}
#line 3689 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1012 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 0);
}
#line 3697 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1016 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 0);
}
#line 3705 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1020 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 0);
}
#line 3713 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1024 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 31, 0);
}
#line 3721 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1028 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 0, 1);
}
#line 3729 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1032 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 1, 1);
}
#line 3737 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1036 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 1);
}
#line 3745 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1040 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 1);
}
#line 3753 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1044 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 1);
}
#line 3761 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1048 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 1);
}
#line 3769 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1052 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 1);
}
#line 3777 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1056 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 1);
}
#line 3785 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1060 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 1);
}
#line 3793 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1064 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 1);
}
#line 3801 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1068 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 1);
}
#line 3809 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1072 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 1);
}
#line 3817 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1076 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 1);
}
#line 3825 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1080 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 1);
}
#line 3833 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1084 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 1);
}
#line 3841 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1088 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 1);
}
#line 3849 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1092 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 1);
}
#line 3857 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1096 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 1);
}
#line 3865 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1100 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 1);
}
#line 3873 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1104 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 1);
}
#line 3881 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1108 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 1);
}
#line 3889 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1112 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 1);
}
#line 3897 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1116 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 1);
}
#line 3905 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1120 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 1);
}
#line 3913 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1124 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 1);
}
#line 3921 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1128 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 1);
}
#line 3929 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1132 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 1);
}
#line 3937 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1136 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 1);
}
#line 3945 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1140 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 1);
}
#line 3953 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1144 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 1);
}
#line 3961 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1148 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 1);
}
#line 3969 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1152 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 31, 1);
}
#line 3977 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1159 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorList_create((yyvsp[0]).pContext);
}
#line 3985 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1163 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3993 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1170 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create(0, (yyvsp[0]).sValue);
}
#line 4001 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1174 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create((yyvsp[0]).pContext, (yyvsp[-2]).sValue);
}
#line 4009 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1181 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, (yyvsp[-3]).sValue);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4019 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1187 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, 0);
}
#line 4027 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1194 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);

  (yyval).sValue = (yyvsp[0]).sValue;
}
#line 4037 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1202 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceAliasDefinition_create((yyvsp[-3]).sValue, (yyvsp[-1]).sValue);
}
#line 4045 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1209 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 0);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4055 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1215 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 1);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4065 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1224 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 0);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4075 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1230 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 1);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4085 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1239 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAsmDefinition_create((yyvsp[-2]).sValue);
}
#line 4093 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1246 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, 0, (yyvsp[-2]).sValue);
}
#line 4101 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1250 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create((yyvsp[-1]).pContext, 0, (yyvsp[-3]).sValue);
}
#line 4109 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1254 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue);
}
#line 4117 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1261 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclaratorList_create((yyvsp[0]).pContext);
}
#line 4125 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1265 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4133 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1272 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 4141 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1276 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4149 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1285 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4157 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1289 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4165 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1296 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 0, 0, 0, 1);
}
#line 4173 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1300 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 1, 0, 0, 0);
}
#line 4181 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1304 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 0, 0, 0, 1);
}
#line 4189 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1308 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 1, 0, 0, 0);
}
#line 4197 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1312 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 0, 0, 0, 0, 1);
}
#line 4205 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1316 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 1, 0, 0, 0, 1);
}
#line 4213 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1346 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
 (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4221 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1353 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4234 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1362 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4247 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1371 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4260 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1380 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4273 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1389 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4286 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1398 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4299 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1407 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 1;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4312 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1419 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4322 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1425 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4332 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1431 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4342 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1437 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-1]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4352 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1443 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4362 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1449 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4372 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1458 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, 0);
}
#line 4380 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1462 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, 0);
}
#line 4388 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1466 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, (yyvsp[-2]).pContext);
}
#line 4396 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1470 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext);
}
#line 4404 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1477 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create(0, 1, 0);
}
#line 4412 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1481 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4420 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1485 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-1]).pContext, 1, 0);
}
#line 4428 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1489 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-2]).pContext, 1, 1);
}
#line 4436 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1496 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationList_create((yyvsp[0]).pContext);
}
#line 4444 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1500 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4452 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1507 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4460 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1511 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4468 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1515 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4476 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1519 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4484 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1523 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[0]).pContext, 0, 0);
}
#line 4492 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1527 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 4500 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1534 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4508 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1538 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4516 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1542 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4524 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1546 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4532 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1550 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4540 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1554 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4548 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1558 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4556 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1565 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4564 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1569 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4572 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1573 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4580 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1577 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4588 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1581 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 4596 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1585 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4604 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1589 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4612 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1599 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionBody_create((yyvsp[0]).pContext);
}
#line 4620 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1606 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4628 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1613 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4638 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1619 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4648 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1628 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create((yyvsp[0]).pContext, 0);
}
#line 4656 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1632 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create(0, (yyvsp[-1]).pContext);
}
#line 4664 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1639 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4672 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1643 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-1]).pContext, 0);
}
#line 4680 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1647 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-2]).pContext, 1);
}
#line 4688 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1651 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, 0, 0);
}
#line 4696 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1658 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerList_create((yyvsp[0]).pContext);
}
#line 4704 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1662 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4712 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1669 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4723 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1676 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4734 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1683 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4745 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1690 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4756 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1697 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4767 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1704 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4778 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1711 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4789 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1718 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4800 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1725 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4811 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1732 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4822 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1739 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4833 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1746 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4844 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1756 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberSpecification_create((yyvsp[0]).pContext);
}
#line 4852 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1760 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4860 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1767 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4868 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1771 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4876 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1775 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 4884 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1779 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 4892 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1783 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
#line 4900 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1787 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 4908 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1791 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 4916 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1795 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 2, 0);
}
#line 4924 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1799 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 3, 0);
}
#line 4932 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1806 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarationList_create((yyvsp[0]).pContext);
}
#line 4940 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1810 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4948 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1817 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 4956 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1821 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[-2]).pContext, (yyvsp[0]).sValue);
}
#line 4964 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1828 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBaseSpecifierList_create((yyvsp[0]).pContext);
}
#line 4972 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1832 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4980 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1839 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 0, (yyvsp[0]).sValue);
}
#line 4990 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1845 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 0, (yyvsp[0]).sValue);
}
#line 5000 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1851 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 0, (yyvsp[0]).sValue);
}
#line 5010 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1857 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 0, (yyvsp[0]).sValue);
}
#line 5020 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1863 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 1, (yyvsp[0]).sValue);
}
#line 5030 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1869 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 1, (yyvsp[0]).sValue);
}
#line 5040 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1875 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 1, (yyvsp[0]).sValue);
}
#line 5050 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1881 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 1, (yyvsp[0]).sValue);
}
#line 5060 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1887 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 0, (yyvsp[0]).sValue);
}
#line 5070 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1893 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5080 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1899 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5090 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1905 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5100 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1911 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 1, (yyvsp[0]).sValue);
}
#line 5110 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1917 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5120 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1923 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5130 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1929 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5140 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1935 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5150 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1941 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5160 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1947 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5170 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1953 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5180 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1959 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5190 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1965 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5200 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1974 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCtorInitializer_create((yyvsp[0]).pContext);
}
#line 5208 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1981 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerList_create((yyvsp[0]).pContext);
}
#line 5216 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1985 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5224 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 365:
#line 1992 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-2]).pContext, 0);
}
#line 5232 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 366:
#line 1996 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5240 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2003 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5248 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2007 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5256 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2011 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5264 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2015 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5272 "..\\src\\cpp_y.c" /* yacc.c:1646  */
    break;


#line 5276 "..\\src\\cpp_y.c" /* yacc.c:1646  */
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
#line 2021 "C:\\cygwin\\usr\\src\\adt\\src\\cpp_y.y" /* yacc.c:1906  */

