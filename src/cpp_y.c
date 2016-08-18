/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "cpp_y.y" /* yacc.c:339  */

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


#line 111 "../../src/cpp_y.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
/* Tokens.  */
#define OR_EQ 258
#define MOD 259
#define PROD 260
#define XOR 261
#define DOT 262
#define XOR_EQ 263
#define LT_EQ 264
#define NEQ 265
#define ELLIPSIS 266
#define LBRACKET 267
#define RBRACKET 268
#define LSBRACKET 269
#define RSBRACKET 270
#define LSQBRACKET 271
#define RSQBRACKET 272
#define AND_EQ 273
#define LT 274
#define GT 275
#define DECR 276
#define INCR 277
#define PLUS 278
#define MINUS 279
#define SHR_EQ 280
#define SHL_EQ 281
#define GT_EQ 282
#define COLON 283
#define COMMA 284
#define LAND 285
#define LOR 286
#define LNOT 287
#define NOT 288
#define SEMICOLON 289
#define LITERAL 290
#define AND 291
#define EQEQ 292
#define SHR 293
#define M_EQ 294
#define P_EQ 295
#define SHL 296
#define QUESTION 297
#define MOD_EQ 298
#define DIV_EQ 299
#define DIV 300
#define PROD_EQ 301
#define EQ 302
#define OR 303
#define STRING_LITERAL 304
#define TYPENAME 305
#define DOUBLE 306
#define FLOAT 307
#define MUTABLE 308
#define PUBLIC 309
#define PRIVATE 310
#define PROTECTED 311
#define EXTERN 312
#define DEFAULT 313
#define WHILE 314
#define SWITCH 315
#define ENUM 316
#define RETURN 317
#define UNSIGNED 318
#define ASM 319
#define DO 320
#define AUTO 321
#define CONTINUE 322
#define BOOL 323
#define WCHAR_T 324
#define EXPLICIT 325
#define IF 326
#define SIZEOF 327
#define UNION 328
#define CHAR 329
#define CLASS 330
#define USING 331
#define VOLATILE 332
#define SIGNED 333
#define CONST 334
#define LONG 335
#define STATIC 336
#define INT 337
#define ELSE 338
#define SHORT 339
#define NAMESPACE 340
#define REGISTER 341
#define TYPEDEF 342
#define FRIEND 343
#define FOR 344
#define GOTO 345
#define VIRTUAL 346
#define INLINE 347
#define CASE 348
#define VOID 349
#define STRUCT 350
#define BREAK 351
#define IDENTIFIER 352
#define QUALIFIED_IDENTIFIER 353
#define DTOR 354
#define QUALIFIED_DTOR 355
#define OBJ_IDENTIFIER 356
#define QUALIFIED_OBJ_IDENTIFIER 357
#define SINGLELINE_COMMENT 358
#define MULTILINE_COMMENT 359
#define EMBEDDED_COMMANDS 360
#define ADDVARIABLES 361

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 374 "../../src/cpp_y.c" /* yacc.c:358  */

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
#define YYFINAL  120
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  366
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  590

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
     813,   820,   826,   832,   838,   844,   853,   859,   868,   872,
     876,   890,   894,   898,   902,   906,   910,   914,   918,   922,
     926,   930,   934,   938,   942,   946,   950,   954,   958,   962,
     966,   970,   974,   978,   982,   986,   990,   994,   998,  1002,
    1006,  1010,  1014,  1018,  1022,  1026,  1030,  1034,  1038,  1042,
    1046,  1050,  1054,  1058,  1062,  1066,  1070,  1074,  1078,  1082,
    1086,  1090,  1094,  1098,  1102,  1106,  1110,  1114,  1118,  1122,
    1126,  1130,  1134,  1141,  1145,  1152,  1156,  1163,  1169,  1176,
    1185,  1192,  1198,  1207,  1213,  1222,  1229,  1233,  1237,  1244,
    1248,  1255,  1259,  1268,  1272,  1279,  1283,  1287,  1291,  1295,
    1299,  1329,  1336,  1346,  1356,  1366,  1376,  1386,  1396,  1409,
    1415,  1421,  1427,  1433,  1439,  1448,  1452,  1456,  1460,  1467,
    1471,  1475,  1479,  1486,  1490,  1497,  1501,  1505,  1509,  1513,
    1517,  1524,  1528,  1532,  1536,  1540,  1544,  1548,  1555,  1559,
    1563,  1567,  1571,  1575,  1579,  1589,  1596,  1603,  1609,  1618,
    1622,  1629,  1633,  1637,  1641,  1648,  1652,  1659,  1666,  1673,
    1680,  1687,  1694,  1701,  1708,  1715,  1722,  1729,  1736,  1746,
    1750,  1757,  1761,  1765,  1769,  1773,  1777,  1781,  1785,  1789,
    1796,  1800,  1807,  1811,  1818,  1822,  1829,  1835,  1841,  1847,
    1853,  1859,  1865,  1871,  1877,  1883,  1889,  1895,  1901,  1907,
    1913,  1919,  1925,  1931,  1937,  1943,  1949,  1955,  1964,  1971,
    1975,  1982,  1986,  1993,  1997,  2001,  2005
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

#define YYPACT_NINF -381

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-381)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1885,  -381,    -6,    56,  -381,   -25,   240,    11,    59,  -381,
     103,   126,  -381,   247,   160,   257,   -14,  -381,    45,  -381,
      46,  -381,   214,    26,     5,  -381,  2038,  -381,    67,  -381,
     223,   275,   290,   299,   305,   314,    39,   124,   269,  -381,
    1940,  -381,  -381,  -381,  -381,  2038,   258,   320,   302,   311,
    -381,   343,  -381,  -381,  -381,  -381,  -381,    96,   521,  -381,
     219,  -381,  -381,  1156,  -381,  -381,  -381,   338,    21,   348,
      60,   318,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,   295,   177,   369,  -381,   378,    52,   384,
      87,  -381,   394,   404,   406,  -381,  -381,   411,  1940,   407,
    -381,  -381,   428,   429,  2038,   285,   451,  -381,  -381,  -381,
    -381,  -381,  1842,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,   454,  -381,  -381,   311,  -381,    16,  -381,    67,   212,
     249,   455,   456,   239,  -381,    62,    97,  1940,  -381,   297,
    -381,  -381,   643,   457,  -381,   246,  2038,   311,  -381,   459,
      27,  -381,  1432,   -12,  1212,  -381,  -381,  -381,   433,   434,
    -381,  -381,   437,   460,   440,   443,   447,  -381,  -381,  -381,
     446,   474,  -381,  -381,   490,  -381,  -381,  -381,  -381,  1268,
     438,   285,   511,   511,  -381,  -381,   251,  -381,  1842,  1842,
    1842,  -381,  -381,  -381,  -381,  -381,  -381,   523,   279,   308,
     359,    37,   530,  -381,  -381,  1842,    49,   365,   154,   181,
      70,   502,   533,   492,   512,  1882,  -381,  -381,  -381,   252,
     130,  -381,   494,   208,  -381,   329,   527,   527,   285,  -381,
    1842,  1679,  -381,  -381,  -381,  1324,  -381,  -381,  -381,  -381,
     516,  -381,   536,   734,  -381,  -381,   522,   537,   539,  1683,
    1007,   518,   545,   461,   547,   463,  1842,   528,   182,  -381,
     253,  -381,  -381,  -381,  -381,   825,  -381,  -381,  -381,  -381,
    -381,  2038,   285,  -381,  -381,  -381,  -381,   311,   514,  -381,
    -381,   342,  -381,   568,  -381,   535,   538,   540,   -11,  2038,
     541,   542,   311,  -381,   157,  -381,  1484,  -381,   150,   152,
     165,    14,  -381,  -381,   200,  -381,  -381,  1380,  -381,  -381,
    -381,   543,  -381,  -381,  -381,  -381,  -381,  -381,  -381,   546,
     259,  -381,   120,  -381,  -381,  1842,  1712,  1842,   553,  1717,
     553,  -381,  -381,  1007,  1842,   309,  -381,  1842,  1842,  1842,
    1842,  1842,  1842,  1842,  1842,  1842,  1842,  1842,  1842,  1842,
    1842,  1842,  1842,  1842,  -381,  -381,  -381,  -381,  -381,  1842,
    -381,  -381,  1842,  -381,  -381,  -381,  -381,  1842,  -381,  -381,
    -381,  1842,  -381,   473,  -381,   232,  -381,   554,  1736,  -381,
     159,   307,  -381,  -381,  -381,   297,  1770,  -381,   916,  1007,
    1842,  1842,  -381,   270,   524,  -381,  1842,   407,  1094,   548,
     557,  -381,  1007,  1842,  -381,  -381,  -381,   285,   549,  1842,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,   311,  -381,  -381,
     550,   131,   272,  -381,  -381,   552,   457,  -381,  -381,   321,
    -381,  -381,   323,  -381,  -381,   327,  -381,  -381,   331,   334,
     336,  -381,  -381,  1536,   -12,  -381,  -381,  -381,  -381,  -381,
     180,   572,   184,    38,  1842,   572,   189,   427,  -381,  -381,
    -381,  -381,  -381,    49,    49,   365,   365,   154,   154,   154,
     154,   181,   181,    70,   502,   533,   492,   512,   417,  -381,
    -381,  -381,  -381,  -381,   575,  -381,  -381,  -381,   233,  -381,
    -381,   190,  -381,  -381,   192,   198,  -381,   581,   202,  -381,
    1804,  -381,  -381,  1007,  -381,  -381,  1842,  -381,   153,   280,
     497,  -381,   574,   285,  -381,  -381,   576,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    1588,  -381,  -381,   553,   572,  -381,   217,   553,   572,  1992,
    1842,  -381,  -381,   532,  -381,  1007,  1007,  1842,  1007,  1808,
     281,  -381,  -381,  -381,   577,  -381,  -381,  -381,  -381,  -381,
    -381,   553,  -381,   553,  1992,  -381,  -381,  -381,  -381,  -381,
    -381,   203,   531,  1007,   209,  1837,  -381,  -381,   582,  1007,
    -381,  1007,  1007,   213,  -381,  -381,  -381,  -381,  1007,  -381
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   126,   186,   185,   142,   141,     0,   178,     0,   138,
     165,   163,   145,     0,   164,     0,     0,   147,   171,   146,
     169,   140,   166,   167,     0,   139,     0,   148,   144,   143,
     191,     0,     0,     0,     0,     0,   161,   162,     0,     3,
       2,   120,   122,   127,   149,     0,     0,   158,     0,     0,
     125,     0,   129,   130,   131,   128,   124,     0,     0,   123,
     151,   217,   216,     0,   156,   157,   209,   184,   182,   179,
     180,     0,   196,   194,   315,   317,   316,   318,   195,   307,
     309,   308,   310,     0,     0,     0,   202,   177,   175,   172,
     173,   200,   187,   188,   170,   197,   198,   168,     0,   229,
     141,   144,   161,   162,     0,     0,     0,   222,   311,   313,
     312,   314,   252,   254,   256,   257,   253,   192,   255,   193,
       1,     0,   121,   150,     0,   132,     0,   133,     0,   245,
     247,   246,   248,     0,   239,   241,     0,     0,   296,     0,
     281,   284,     0,     0,   269,   259,     0,   279,   251,     0,
     270,   273,     0,     0,     0,   238,   215,   213,   190,   183,
     210,   211,   181,     0,     0,     0,     0,   231,   208,   206,
     189,   176,   203,   204,   174,   218,   219,   201,   199,     0,
       0,     0,   245,   247,   246,   248,     0,   258,     0,     0,
       0,    37,    38,    39,    40,     8,     9,     0,    18,    19,
      32,     0,    13,    16,    41,     0,    45,    48,    51,    56,
      59,    61,    63,    65,    67,    69,    71,    14,   252,     0,
       0,   159,   225,     0,   223,     0,   249,   250,     0,   134,
       0,     0,   242,   282,   286,     0,   363,   364,   365,   366,
     358,   359,     0,     0,   297,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    84,
       0,   101,    87,    88,    89,     0,    90,    91,    92,    93,
     119,     0,     0,   295,   285,   261,   260,   280,   275,   243,
     244,   262,   271,     0,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   324,     0,   323,     0,   319,     0,     0,
       0,     0,   336,   340,     0,   334,   236,     0,   221,   214,
     212,     0,   232,   233,   234,   220,   207,   205,   228,     0,
       0,   135,     0,    34,    33,     0,     0,     0,    24,     0,
      25,    12,    11,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    83,    82,    81,    80,    79,     0,
      78,    77,     0,    76,    75,    74,    73,     0,   136,   283,
     287,     0,   160,     0,   265,    69,    86,     0,     0,   240,
       0,     0,   301,   299,   227,     0,     0,    99,     0,     0,
       0,     0,   116,     0,     0,   115,     0,     0,     0,     0,
       0,   114,     0,     0,    98,   298,   102,     0,   276,     0,
     264,   263,   272,   274,   329,   327,   328,     0,   325,   326,
     332,     0,     0,   330,   288,     0,     0,   153,   320,     0,
     339,   343,     0,   337,   341,     0,   338,   342,     0,     0,
       0,   344,   348,     0,     0,   237,   235,   230,   137,    10,
       0,    20,     0,     0,     0,    21,     0,     4,    15,    17,
      44,    42,    43,    46,    47,    50,    49,    54,    52,    53,
      55,    58,    57,    60,    62,    64,    66,    68,     0,    72,
     226,   224,   266,   267,     0,   300,   304,   305,     0,   360,
     361,     0,   100,    96,     0,     0,   117,     0,     0,   112,
       0,   113,   118,     0,    94,    85,     0,   277,     0,     0,
       0,   289,     0,     0,   321,   291,     0,   354,   357,   352,
     355,   353,   356,   347,   351,   345,   349,   346,   350,   154,
       0,   335,    36,    26,    22,    30,     0,    27,    23,     0,
       0,   268,   302,     0,   362,     0,     0,     0,     0,     0,
       0,    95,   278,   290,     0,   322,   333,   293,   331,   292,
     155,    28,    31,    29,     5,     6,    70,   303,   306,   106,
     105,     0,   103,     0,     0,     0,   294,     7,     0,     0,
     108,     0,     0,     0,   107,   104,   109,   110,     0,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -381,  -381,  -381,  -381,  -381,  -209,  -381,   271,  -191,  -156,
    -381,   112,   113,    71,   109,   267,   273,   266,   274,   276,
    -210,  -208,  -109,  -381,  -184,  -231,  -213,  -381,   228,  -381,
    -227,  -381,  -381,  -381,  -381,  -381,   -76,   -31,    20,  -380,
     -32,     1,  -145,  -381,  -140,     0,  -381,   255,  -381,  -381,
    -381,  -138,  -381,  -381,  -381,   -95,   405,   355,  -142,   -47,
    -381,  -381,  -107,  -381,  -381,   356,  -381,  -381,  -108,  -381,
    -381,  -381,  -370,  -381,  -381,   197,  -290,   224,   138,  -381,
     199,   350,  -381,   268,  -381
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    38,    39,   564,   200,   201,   202,   203,   328,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   259,   367,   260,   377,   261,   262,   263,   264,
     265,   266,   267,   500,   268,   269,    40,    41,   270,    43,
      44,   271,    46,    47,    48,   272,   223,   224,    50,    51,
      52,    53,    54,    55,    56,   133,   134,   278,   135,    57,
      58,   148,   226,   149,   150,   151,    59,   295,   141,   142,
     273,   232,   383,   488,    60,   296,   297,   422,   423,   304,
     305,   143,   240,   241,   242
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      49,    45,   136,   217,   322,   279,   428,   290,   330,   122,
     186,   487,   291,   123,   293,   375,   388,   376,   501,    98,
      42,   380,   179,   227,    63,   400,   105,   104,   234,   219,
      61,   221,   155,   323,   324,   274,    83,   394,   282,    83,
      49,    45,   298,   299,   300,   124,   375,    66,   376,   336,
     333,   116,   406,   337,   338,   535,   283,   157,   147,   146,
      42,   235,    96,    49,    45,   393,   334,   403,   438,   439,
     440,    84,   123,    71,   230,   117,   227,   220,   307,   301,
     348,    86,    91,    42,    85,    67,   320,    85,   169,   302,
     303,    68,    62,    69,   339,    70,   161,    92,    49,    45,
     280,   158,    99,   159,   181,   294,   457,   349,    97,   231,
     138,   138,   370,   222,   123,   441,   442,   452,    42,    87,
     456,   217,   382,   173,   139,    88,    93,    89,    94,    90,
     140,   233,   170,   449,   171,   279,   118,    49,    45,    72,
     480,   450,   162,   453,   138,   138,   277,   484,   122,   403,
     420,   290,   292,   289,    49,    45,   291,    42,   293,   565,
     119,   375,    73,   376,   369,   511,   106,   138,   375,   174,
     376,   138,   485,   568,    42,   406,   493,   491,   478,    49,
      45,   460,   461,   462,   577,   139,   425,   553,   334,   504,
     344,   424,   342,   532,   326,   343,    78,   534,   327,    42,
     345,   346,   538,   544,   122,   545,   494,   495,   347,   403,
     402,   546,   498,   334,   443,   548,   578,   217,   334,   334,
     217,   403,   581,   372,   218,   458,   588,   403,   225,   444,
     280,   403,   403,   152,   562,    49,    45,   373,   403,   123,
     428,   429,   403,   432,   406,   421,   403,   153,   542,   294,
      95,   430,   431,   433,   434,    42,   435,   123,   479,   107,
     533,   113,   543,   359,   537,   225,   436,   437,   228,   120,
     536,   407,   382,   229,   362,   420,   122,   217,   165,   166,
     228,   228,   403,   147,   146,   321,   368,   404,   228,   417,
     551,   326,   125,   448,   505,   327,   292,   289,   290,   403,
     507,   513,   112,   291,   496,   293,   514,    49,    45,   513,
     403,   113,   219,   512,   555,   575,   550,   114,   516,   188,
     329,   381,   486,   275,   327,   276,   115,    42,   189,   190,
     191,   192,   569,   570,   126,   572,   127,    64,    65,   193,
     194,   188,   195,   561,    74,    75,   374,   563,    76,    77,
     189,   190,   191,   192,    79,    80,   196,   137,    81,    82,
     580,   193,   194,   571,   195,   574,   585,   163,   586,   587,
     508,   420,   108,   109,   156,   589,   110,   111,   196,   197,
     331,   332,   182,   183,   160,   290,   184,   185,   340,   341,
     291,   583,   293,   164,   236,   237,   294,   552,   238,   239,
     554,   197,   128,   167,   198,   199,   198,   199,   129,   130,
      34,    35,   131,   132,   168,   467,   468,   469,   470,   410,
     172,   411,   517,   518,   519,   520,   198,   199,   521,   522,
     175,   566,   523,   524,   382,   525,   526,   527,   528,   188,
     176,   243,   177,   292,   289,   540,   403,   178,   189,   190,
     191,   192,   463,   464,   180,   465,   466,   471,   472,   193,
     194,   245,   195,   187,   117,   119,   218,   116,   118,   308,
     309,   138,   281,   310,   312,   311,   196,   313,     2,     3,
       4,   314,   315,   294,   100,   246,   247,   248,     6,   249,
       7,     8,   250,     9,   251,    10,    11,    12,   252,   197,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
     316,    23,   253,    25,    26,    27,   254,   255,   101,    29,
     256,    30,    31,   257,   258,   199,   317,   225,   102,   103,
     292,   289,   144,   539,   145,   325,   319,   335,   350,   351,
     352,   371,   353,   378,   188,   385,   381,   567,   386,   390,
     389,   391,   395,   189,   190,   191,   192,   396,   397,   398,
     399,   409,   401,   414,   193,   194,   415,   195,   416,   454,
     222,   482,     2,     3,     4,   418,   419,   446,   100,   412,
     447,   196,   502,   497,     7,   503,   515,     9,   327,    10,
      11,    12,   541,   547,   556,    14,   506,   510,    17,    18,
      19,    20,    21,    22,   197,    23,   459,    25,   557,    27,
     559,   576,   101,    29,   579,    30,   584,   473,   475,     2,
       3,     4,   102,   103,   474,   100,   499,   476,   481,   198,
     199,     7,   408,   379,     9,   477,    10,    11,    12,   413,
     530,   509,    14,   531,   426,    17,    18,    19,    20,    21,
      22,   558,    23,   489,    25,   188,    27,   243,   244,   101,
      29,     0,    30,     0,   189,   190,   191,   192,     0,   102,
     103,     0,     0,     0,     0,   193,   194,   245,   195,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   196,     0,     2,     3,     4,     0,     0,     0,
     100,   246,   247,   248,     6,   249,     7,     8,   250,     9,
     251,    10,    11,    12,   252,   197,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,    23,   253,    25,
      26,    27,   254,   255,   101,    29,   256,    30,    31,   257,
     258,   199,     0,     0,   102,   103,   188,     0,   243,   387,
       0,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,   193,   194,   245,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,     2,     3,     4,     0,     0,
       0,   100,   246,   247,   248,     6,   249,     7,     8,   250,
       9,   251,    10,    11,    12,   252,   197,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,     0,    23,   253,
      25,    26,    27,   254,   255,   101,    29,   256,    30,    31,
     257,   258,   199,     0,     0,   102,   103,   188,     0,   243,
     405,     0,     0,     0,     0,     0,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   245,
     195,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,     0,     2,     3,     4,     0,
       0,     0,   100,   246,   247,   248,     6,   249,     7,     8,
     250,     9,   251,    10,    11,    12,   252,   197,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    23,
     253,    25,    26,    27,   254,   255,   101,    29,   256,    30,
      31,   257,   258,   199,     0,     0,   102,   103,   188,     0,
     243,   492,     0,     0,     0,     0,     0,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,   193,   194,
     245,   195,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   196,     0,     2,     3,     4,
       0,     0,     0,   100,   246,   247,   248,     6,   249,     7,
       8,   250,     9,   251,    10,    11,    12,   252,   197,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
      23,   253,    25,    26,    27,   254,   255,   101,    29,   256,
      30,    31,   257,   258,   199,     0,     0,   102,   103,   188,
       0,   243,     0,     0,     0,     0,     0,     0,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   245,   195,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   196,     0,     2,     3,
       4,     0,     0,     0,   100,   246,   247,   248,     6,   249,
       7,     8,   250,     9,   251,    10,    11,    12,   252,   197,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,    23,   253,    25,    26,    27,   254,   255,   101,    29,
     256,    30,    31,   257,   258,   199,   188,     0,   102,   103,
       0,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,   193,   194,   245,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,     2,     3,     4,     0,     0,
       0,   100,     0,     0,     0,     6,     0,     7,     0,     0,
       9,     0,    10,    11,    12,     0,   197,    13,    14,    15,
     154,    17,    18,    19,    20,    21,    22,     0,    23,     0,
      25,    26,    27,     0,     0,   101,    29,     0,    30,    31,
       1,   198,   199,     0,     0,   102,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     3,     4,
       0,     0,     0,     5,     0,     0,     0,     6,     0,     7,
       8,     0,     9,     0,    10,    11,    12,   306,     0,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,     0,     1,    28,    29,     0,
      30,    31,     0,   121,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     2,     3,     4,     0,     0,     0,     5,
       0,     0,     0,     6,     0,     7,     8,     0,     9,     0,
      10,    11,    12,   318,     0,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,     0,     1,    28,    29,     0,    30,    31,     0,   121,
      33,    34,    35,    36,    37,     0,     0,     0,     0,     2,
       3,     4,     0,     0,     0,     5,     0,     0,     0,     6,
       0,     7,     8,     0,     9,     0,    10,    11,    12,   384,
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,     0,     1,    28,
      29,     0,    30,    31,     0,   121,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     2,     3,     4,     0,     0,
       0,     5,     0,     0,     0,     6,     0,     7,     8,     0,
       9,     0,    10,    11,    12,   445,     0,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,     0,     1,    28,    29,     0,    30,    31,
       0,   121,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     2,     3,     4,     0,     0,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,   284,    10,    11,
      12,     0,     0,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    24,    25,    26,    27,     0,
       0,    28,    29,     0,    30,    31,     0,   121,    33,    34,
      35,    36,    37,     2,     3,     4,   285,   286,   287,   100,
       0,     0,     0,     6,     0,     7,     0,     0,     9,   427,
      10,    11,    12,     0,     0,    13,    14,    15,   288,    17,
      18,    19,    20,    21,    22,     0,    23,     0,    25,     0,
      27,     0,     0,    28,    29,     0,    30,    31,     0,   121,
      33,    34,    35,    36,    37,     2,     3,     4,   285,   286,
     287,   100,     0,     0,     0,     6,     0,     7,     0,     0,
       9,   529,    10,    11,    12,     0,     0,    13,    14,    15,
     288,    17,    18,    19,    20,    21,    22,     0,    23,     0,
      25,     0,    27,     0,     0,    28,    29,     0,    30,    31,
       0,   121,    33,    34,    35,    36,    37,     2,     3,     4,
     285,   286,   287,   100,     0,     0,     0,     6,     0,     7,
       0,     0,     9,   560,    10,    11,    12,     0,     0,    13,
      14,    15,   288,    17,    18,    19,    20,    21,    22,     0,
      23,     0,    25,     0,    27,     0,     0,    28,    29,     0,
      30,    31,     0,   121,    33,    34,    35,    36,    37,     2,
       3,     4,   285,   286,   287,   100,     0,     0,     0,     6,
       0,     7,     0,     0,     9,     0,    10,    11,    12,     0,
       0,    13,    14,    15,   288,    17,    18,    19,    20,    21,
      22,     0,    23,     0,    25,     0,    27,     0,     0,    28,
      29,     0,    30,    31,     0,   121,    33,    34,    35,    36,
      37,   188,     0,   381,     0,   188,     0,     0,     0,     0,
     189,   190,   191,   192,   189,   190,   191,   192,     0,     0,
       0,   193,   194,     0,   195,   193,   194,   392,   195,     0,
       0,     0,     0,     0,   188,   451,     0,     0,   196,   188,
     455,     0,   196,   189,   190,   191,   192,     0,   189,   190,
     191,   192,     0,     0,   193,   194,     0,   195,   188,   193,
     194,   197,   195,   483,     0,   197,     0,   189,   190,   191,
     192,   196,     0,     0,     0,     0,   196,     0,   193,   194,
       0,   195,     0,     0,     0,     0,   198,   199,     0,     0,
     198,   199,   188,   490,   197,   196,     0,     0,     0,   197,
       0,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,   193,   194,     0,   195,     0,     0,   197,   198,
     199,     0,     0,     0,   198,   199,   188,     0,     0,   196,
     188,   573,     0,     0,     0,   189,   190,   191,   192,   189,
     190,   191,   192,   198,   199,     0,   193,   194,   549,   195,
     193,   194,   197,   195,     0,     0,     0,     0,     0,   188,
     582,     0,     0,   196,   188,     0,     0,   196,   189,   190,
     191,   192,     0,   189,   190,   191,   192,   198,   199,   193,
     194,     0,   195,     0,   193,   194,   197,   195,     0,     0,
     197,     0,     0,     0,     0,   354,   196,     0,     0,     0,
     355,   196,     0,     0,     0,     0,     0,     0,     0,     0,
     356,   198,   199,     0,     0,   198,   199,   357,   358,   197,
       0,     0,     0,   359,   197,     0,     0,     0,     0,     1,
       0,   360,   361,     0,   362,   363,   364,     0,   365,   366,
       0,     0,     0,     0,   198,   199,     2,     3,     4,   198,
     199,     0,     5,     0,     0,     0,     6,     0,     7,     8,
       0,     9,     0,    10,    11,    12,     0,     0,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,     1,     0,    28,    29,     0,    30,
      31,     0,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     2,     3,     4,     0,     0,     0,     5,     0,     0,
       0,     6,     0,     7,     8,     0,     9,     0,    10,    11,
      12,     0,     0,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    24,    25,    26,    27,     0,
       0,    28,    29,     0,    30,    31,     0,   121,    33,    34,
      35,    36,    37,     2,     3,     4,     0,     0,     0,   100,
       0,     0,     0,     6,     0,     7,     0,     0,     9,     0,
      10,    11,    12,     0,     0,    13,    14,    15,     0,    17,
      18,    19,    20,    21,    22,     0,    23,     0,    25,    26,
      27,     0,     0,   101,    29,     0,    30,    31,     0,     2,
       3,     4,     0,   102,   103,   100,     0,     0,     0,     0,
       0,     7,     0,     0,     9,     0,    10,    11,    12,     0,
       0,     0,    14,     0,     0,    17,    18,    19,    20,    21,
      22,     0,    23,     0,    25,     0,    27,     0,     0,   101,
      29,     0,    30,     0,     0,     0,     0,     0,     0,   102,
     103
};

static const yytype_int16 yycheck[] =
{
       0,     0,    49,   112,   188,   147,   296,   152,   199,    40,
     105,   381,   152,    45,   152,   225,   243,   225,   398,    14,
       0,   230,    98,   130,    49,   256,    26,    26,   136,   124,
      36,    15,    63,   189,   190,   143,    50,   250,    11,    50,
      40,    40,    54,    55,    56,    45,   256,    36,   256,   205,
      13,    12,   265,     4,     5,    17,    29,    36,    58,    58,
      40,   137,    36,    63,    63,   249,    29,    29,    54,    55,
      56,    85,   104,    14,    12,    36,   183,   124,   154,    91,
      10,    36,    36,    63,    98,    74,   181,    98,    36,   101,
     102,    80,    36,    82,    45,    84,    36,    51,    98,    98,
     147,    80,    97,    82,   104,   152,   333,    37,    82,    47,
      14,    14,   220,    97,   146,   101,   102,   326,    98,    74,
     329,   230,   231,    36,    28,    80,    80,    82,    82,    84,
      34,    34,    80,    13,    82,   277,    12,   137,   137,    36,
     371,   325,    82,   327,    14,    14,   146,   378,   179,    29,
     292,   296,   152,   152,   154,   154,   296,   137,   296,   539,
      36,   371,    36,   371,    34,    34,    99,    14,   378,    82,
     378,    14,    13,   543,   154,   388,   389,   386,   362,   179,
     179,   337,   338,   339,   564,    28,   294,    34,    29,   402,
       9,    34,    38,    13,    12,    41,    36,    13,    16,   179,
      19,    20,    13,    13,   235,    13,   390,   391,    27,    29,
      28,    13,   396,    29,    14,    13,    13,   326,    29,    29,
     329,    29,    13,    15,    12,   334,    13,    29,    16,    29,
     277,    29,    29,    14,    17,   235,   235,    29,    29,   271,
     530,    91,    29,    91,   457,   292,    29,    28,    15,   296,
      36,   101,   102,   101,   102,   235,    91,   289,   367,    36,
     451,    12,    29,    31,   455,    16,   101,   102,    29,     0,
     454,   271,   381,    34,    42,   417,   307,   386,   101,   102,
      29,    29,    29,   283,   283,    34,    34,    34,    29,   289,
     503,    12,    34,    34,   403,    16,   296,   296,   443,    29,
     409,    29,    12,   443,    34,   443,    34,   307,   307,    29,
      29,    12,   407,   421,    34,    34,   500,    12,   426,    12,
      12,    14,    15,    77,    16,    79,    12,   307,    21,    22,
      23,    24,   545,   546,    14,   548,    34,    97,    98,    32,
      33,    12,    35,   534,    97,    98,    17,   538,   101,   102,
      21,    22,    23,    24,    97,    98,    49,    14,   101,   102,
     573,    32,    33,   547,    35,   549,   579,    49,   581,   582,
     417,   513,    97,    98,    36,   588,   101,   102,    49,    72,
      21,    22,    97,    98,    36,   530,   101,   102,    23,    24,
     530,   575,   530,    98,    97,    98,   443,   506,   101,   102,
     508,    72,    91,    34,    97,    98,    97,    98,    97,    98,
      99,   100,   101,   102,    36,   344,   345,   346,   347,    77,
      36,    79,   101,   102,   101,   102,    97,    98,   101,   102,
      36,   540,   101,   102,   543,   101,   102,   101,   102,    12,
      36,    14,    36,   443,   443,    28,    29,    36,    21,    22,
      23,    24,   340,   341,    47,   342,   343,   348,   349,    32,
      33,    34,    35,    12,    36,    36,    12,    12,    12,    36,
      36,    14,    13,    36,    34,    15,    49,    34,    51,    52,
      53,    34,    36,   530,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      36,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    36,    16,   101,   102,
     530,   530,    11,   106,    13,    12,    98,     7,    36,     6,
      48,    47,    30,    16,    12,    29,    14,    15,    12,    12,
      28,    12,    34,    21,    22,    23,    24,    12,    97,    12,
      97,    47,    34,    28,    32,    33,    28,    35,    28,    16,
      97,    17,    51,    52,    53,    34,    34,    34,    57,    11,
      34,    49,    34,    59,    63,    28,    34,    66,    16,    68,
      69,    70,    17,    12,    97,    74,    47,    47,    77,    78,
      79,    80,    81,    82,    72,    84,   335,    86,    34,    88,
      34,    34,    91,    92,    83,    94,    34,   350,   352,    51,
      52,    53,   101,   102,   351,    57,   398,   353,   373,    97,
      98,    63,   277,   228,    66,   359,    68,    69,    70,   283,
     443,   417,    74,   444,   294,    77,    78,    79,    80,    81,
      82,   513,    84,   385,    86,    12,    88,    14,    15,    91,
      92,    -1,    94,    -1,    21,    22,    23,    24,    -1,   101,
     102,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,   101,   102,    12,    -1,    14,    15,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    53,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,   101,   102,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,    -1,
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
      -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    12,    -1,   101,   102,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,
      66,    -1,    68,    69,    70,    -1,    72,    73,    74,    75,
      14,    77,    78,    79,    80,    81,    82,    -1,    84,    -1,
      86,    87,    88,    -1,    -1,    91,    92,    -1,    94,    95,
      34,    97,    98,    -1,    -1,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,    63,
      64,    -1,    66,    -1,    68,    69,    70,    15,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      84,    85,    86,    87,    88,    -1,    34,    91,    92,    -1,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    -1,    63,    64,    -1,    66,    -1,
      68,    69,    70,    15,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    -1,    34,    91,    92,    -1,    94,    95,    -1,    97,
      98,    99,   100,   101,   102,    -1,    -1,    -1,    -1,    51,
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
      -1,    61,    -1,    63,    64,    -1,    66,    15,    68,    69,
      70,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    84,    85,    86,    87,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    97,    98,    99,
     100,   101,   102,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    61,    -1,    63,    -1,    -1,    66,    15,
      68,    69,    70,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    -1,    86,    -1,
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
      -1,    63,    -1,    -1,    66,    -1,    68,    69,    70,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,    91,
      92,    -1,    94,    95,    -1,    97,    98,    99,   100,   101,
     102,    12,    -1,    14,    -1,    12,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    21,    22,    23,    24,    -1,    -1,
      -1,    32,    33,    -1,    35,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    12,    13,    -1,    -1,    49,    12,
      13,    -1,    49,    21,    22,    23,    24,    -1,    21,    22,
      23,    24,    -1,    -1,    32,    33,    -1,    35,    12,    32,
      33,    72,    35,    17,    -1,    72,    -1,    21,    22,    23,
      24,    49,    -1,    -1,    -1,    -1,    49,    -1,    32,    33,
      -1,    35,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,
      97,    98,    12,    13,    72,    49,    -1,    -1,    -1,    72,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    35,    -1,    -1,    72,    97,
      98,    -1,    -1,    -1,    97,    98,    12,    -1,    -1,    49,
      12,    13,    -1,    -1,    -1,    21,    22,    23,    24,    21,
      22,    23,    24,    97,    98,    -1,    32,    33,    34,    35,
      32,    33,    72,    35,    -1,    -1,    -1,    -1,    -1,    12,
      13,    -1,    -1,    49,    12,    -1,    -1,    49,    21,    22,
      23,    24,    -1,    21,    22,    23,    24,    97,    98,    32,
      33,    -1,    35,    -1,    32,    33,    72,    35,    -1,    -1,
      72,    -1,    -1,    -1,    -1,     3,    49,    -1,    -1,    -1,
       8,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    97,    98,    -1,    -1,    97,    98,    25,    26,    72,
      -1,    -1,    -1,    31,    72,    -1,    -1,    -1,    -1,    34,
      -1,    39,    40,    -1,    42,    43,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    97,    98,    51,    52,    53,    97,
      98,    -1,    57,    -1,    -1,    -1,    61,    -1,    63,    64,
      -1,    66,    -1,    68,    69,    70,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    84,
      85,    86,    87,    88,    34,    -1,    91,    92,    -1,    94,
      95,    -1,    97,    98,    99,   100,   101,   102,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61,    -1,    63,    64,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    84,    85,    86,    87,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    97,    98,    99,
     100,   101,   102,    51,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    -1,    63,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    73,    74,    75,    -1,    77,
      78,    79,    80,    81,    82,    -1,    84,    -1,    86,    87,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    51,
      52,    53,    -1,   101,   102,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    66,    -1,    68,    69,    70,    -1,
      -1,    -1,    74,    -1,    -1,    77,    78,    79,    80,    81,
      82,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,    91,
      92,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102
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
     181,    36,    36,    49,    97,    98,    36,    74,    80,    82,
      84,    14,    36,    36,    97,    98,   101,   102,    36,    97,
      98,   101,   102,    50,    85,    98,    36,    74,    80,    82,
      84,    36,    51,    80,    82,    36,    36,    82,    14,    97,
      57,    91,   101,   102,   148,   152,    99,    36,    97,    98,
     101,   102,    12,    12,    12,    12,    12,    36,    12,    36,
       0,    97,   144,   147,   152,    34,    14,    34,    91,    97,
      98,   101,   102,   162,   163,   165,   166,    14,    14,    28,
      34,   175,   176,   188,    11,    13,   148,   152,   168,   170,
     171,   172,    14,    28,    14,   144,    36,    36,    80,    82,
      36,    36,    82,    49,    98,   101,   102,    34,    36,    36,
      80,    82,    36,    36,    82,    36,    36,    36,    36,   143,
      47,   152,    97,    98,   101,   102,   162,    12,    12,    21,
      22,    23,    24,    32,    33,    35,    49,    72,    97,    98,
     111,   112,   113,   114,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    12,   162,
     166,    15,    97,   153,   154,    16,   169,   169,    29,    34,
      12,    47,   178,    34,   175,   143,    97,    98,   101,   102,
     189,   190,   191,    14,    15,    34,    58,    59,    60,    62,
      65,    67,    71,    85,    89,    90,    93,    96,    97,   129,
     131,   133,   134,   135,   136,   137,   138,   139,   141,   142,
     145,   148,   152,   177,   175,    77,    79,   152,   164,   165,
     166,    13,    11,    29,    15,    54,    55,    56,    76,   148,
     149,   151,   152,   158,   166,   174,   182,   183,    54,    55,
      56,    91,   101,   102,   186,   187,    15,   143,    36,    36,
      36,    15,    34,    34,    34,    36,    36,    36,    15,    98,
     162,    34,   131,   116,   116,    12,    12,    16,   115,    12,
     115,    21,    22,    13,    29,     7,   116,     4,     5,    45,
      23,    24,    38,    41,     9,    19,    20,    27,    10,    37,
      36,     6,    48,    30,     3,     8,    18,    25,    26,    31,
      39,    40,    42,    43,    44,    46,    47,   130,    34,    34,
     175,    47,    15,    29,    17,   127,   128,   132,    16,   163,
     112,    14,   129,   179,    15,    29,    12,    15,   137,    28,
      12,    12,    34,   131,   133,    34,    12,    97,    12,    97,
     132,    34,    28,    29,    34,    15,   133,   152,   164,    47,
      77,    79,    11,   172,    28,    28,    28,   152,    34,    34,
     165,   166,   184,   185,    34,   175,   188,    15,   183,    91,
     101,   102,    91,   101,   102,    91,   101,   102,    54,    55,
      56,   101,   102,    14,    29,    15,    34,    34,    34,    13,
     131,    13,   112,   131,    16,    13,   112,   137,   129,   114,
     116,   116,   116,   118,   118,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   123,   124,   125,   126,   131,   129,
     132,   154,    17,    17,   132,    13,    15,   179,   180,   190,
      13,   112,    15,   133,   131,   131,    34,    59,   131,   135,
     140,   146,    34,    28,   133,   129,    47,   129,   166,   184,
      47,    34,   175,    29,    34,    34,   175,   101,   102,   101,
     102,   101,   102,   101,   102,   101,   102,   101,   102,    15,
     182,   187,    13,   115,    13,    17,   131,   115,    13,   106,
      28,    17,    15,    29,    13,    13,    13,    12,    13,    34,
     131,   133,   129,    34,   175,    34,    97,    34,   185,    34,
      15,   115,    17,   115,   110,   146,   129,    15,   179,   133,
     133,   131,   133,    13,   131,    34,    34,   146,    13,    83,
     133,    13,    13,   131,    34,   133,   133,   133,    13,   133
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
     148,   149,   149,   149,   149,   149,   150,   150,   151,   151,
     151,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   153,   154,   154,   155,   155,   156,
     157,   158,   158,   159,   159,   160,   161,   161,   161,   162,
     162,   163,   163,   164,   164,   165,   165,   165,   165,   165,
     165,   166,   167,   167,   167,   167,   167,   167,   167,   168,
     168,   168,   168,   168,   168,   169,   169,   169,   169,   170,
     170,   170,   170,   171,   171,   172,   172,   172,   172,   172,
     172,   173,   173,   173,   173,   173,   173,   173,   174,   174,
     174,   174,   174,   174,   174,   175,   176,   177,   177,   178,
     178,   179,   179,   179,   179,   180,   180,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   182,
     182,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     184,   184,   185,   185,   186,   186,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   188,   189,
     189,   190,   190,   191,   191,   191,   191
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
       2,     1,     3,     4,     5,     6,     2,     2,     1,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     2,     3,     2,     3,     2,     1,     2,
       2,     3,     2,     3,     2,     1,     1,     2,     2,     3,
       3,     1,     2,     2,     2,     2,     2,     2,     2,     3,
       2,     3,     2,     3,     3,     4,     3,     4,     3,     2,
       3,     3,     4,     3,     4,     3,     2,     2,     3,     3,
       4,     4,     2,     1,     3,     1,     3,     4,     4,     2,
       5,     3,     4,     4,     4,     5,     4,     5,     3,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     1,
       2,     2,     2,     3,     3,     2,     3,     3,     4,     1,
       1,     2,     3,     1,     3,     2,     3,     4,     5,     1,
       2,     2,     3,     4,     2,     3,     3,     4,     2,     3,
       4,     3,     4,     4,     5,     2,     1,     1,     2,     2,
       3,     1,     3,     4,     2,     1,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     3,     4,     1,     1,     2,     2,     2,     2,     2,
       1,     3,     1,     3,     1,     3,     1,     2,     2,     2,
       1,     2,     2,     2,     2,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       3,     3,     4,     1,     1,     1,     1
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
#line 73 "cpp_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtCppTranslationUnit_create((yyvsp[0]).pContext);
  (yyval).pContext = adtCpp_setRoot(pObj);

  adtCpp_releaseObject(pObj);
}
#line 2237 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 3:
#line 82 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add(adtCpp_getRoot(), (yyvsp[0]).pContext);
}
#line 2245 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 4:
#line 90 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 2253 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 5:
#line 94 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMacro_create((yyvsp[-6]).sValue, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2261 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclarationList_create((yyvsp[0]).pContext);
}
#line 2269 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 7:
#line 104 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2277 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 8:
#line 111 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2285 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 9:
#line 115 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, 0, 0, (yyvsp[0]).sValue);
}
#line 2293 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 10:
#line 119 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create((yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 2301 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 11:
#line 123 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 1, 0);
}
#line 2309 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 2317 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppPostfixExpression_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2325 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionList_create((yyvsp[0]).pContext);
}
#line 2333 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 15:
#line 142 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2341 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 16:
#line 149 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDirectedExpression_create((yyvsp[0]).pContext);
}
#line 2349 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 17:
#line 153 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2357 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 2365 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 19:
#line 168 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[0]).sValue, 0, 0, 1, 0, (yyvsp[0]).sComment);
}
#line 2373 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 20:
#line 172 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 0, 1, (yyvsp[-2]).sComment);
}
#line 2381 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 21:
#line 176 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-2]).sValue, 0, 0, 1, 1, (yyvsp[-2]).sComment);
}
#line 2389 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 22:
#line 180 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 0, 1, (yyvsp[-3]).sComment);
}
#line 2397 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 23:
#line 184 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 1, 1, (yyvsp[-3]).sComment);
}
#line 2405 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 24:
#line 188 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 0, 0, (yyvsp[-1]).sComment);
}
#line 2413 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 25:
#line 192 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-1]).sValue, 0, (yyvsp[0]).pContext, 1, 0, (yyvsp[-1]).sComment);
}
#line 2421 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 26:
#line 196 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 0, 1, (yyvsp[-3]).sComment);
}
#line 2429 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 27:
#line 200 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-3]).sValue, 0, (yyvsp[0]).pContext, 1, 1, (yyvsp[-3]).sComment);
}
#line 2437 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 28:
#line 204 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1, (yyvsp[-4]).sComment);
}
#line 2445 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 29:
#line 208 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpression_create((yyvsp[-4]).sValue, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1, 1, (yyvsp[-4]).sComment);
}
#line 2453 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 30:
#line 215 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorExpressionDims_create((yyvsp[-1]).pContext);
}
#line 2461 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 31:
#line 219 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 2469 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 32:
#line 226 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2477 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 33:
#line 230 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 1);
}
#line 2485 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 34:
#line 234 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2493 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 35:
#line 238 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 2501 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 36:
#line 242 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryExpression_create(0, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 2509 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 37:
#line 249 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(0);
}
#line 2517 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 38:
#line 253 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(1);
}
#line 2525 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 39:
#line 257 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(2);
}
#line 2533 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 40:
#line 261 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUnaryOperator_create(3);
}
#line 2541 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 41:
#line 268 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2549 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 42:
#line 272 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2557 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 43:
#line 276 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2565 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 44:
#line 280 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMultiplicativeExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2573 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 45:
#line 287 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2581 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 46:
#line 291 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2589 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 47:
#line 295 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAdditiveExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2597 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 48:
#line 302 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2605 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 49:
#line 306 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2613 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 50:
#line 310 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppShiftExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2621 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 51:
#line 317 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2629 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 52:
#line 321 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2637 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 53:
#line 325 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2645 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 54:
#line 329 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(2, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2653 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 55:
#line 333 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppRelationalExpression_create(3, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2661 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 56:
#line 340 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, 0);
}
#line 2669 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 57:
#line 344 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2677 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 58:
#line 348 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEqualityExpression_create(1, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2685 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 59:
#line 355 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2693 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2701 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 61:
#line 366 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2709 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 62:
#line 370 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2717 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 63:
#line 377 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2725 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 64:
#line 381 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInclusiveOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2733 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 65:
#line 388 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, 0);
}
#line 2741 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 66:
#line 392 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalAndExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2749 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 67:
#line 399 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, 0);
}
#line 2757 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 68:
#line 403 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLogicalOrExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2765 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 69:
#line 410 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[0]).pContext, 0, 0);
}
#line 2773 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 70:
#line 414 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConditionalExpression_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2781 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 71:
#line 421 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 2789 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 72:
#line 425 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentExpression_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 2797 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 73:
#line 432 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(0);
}
#line 2805 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 74:
#line 436 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(1);
}
#line 2813 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 75:
#line 440 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(2);
}
#line 2821 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 76:
#line 444 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(3);
}
#line 2829 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 77:
#line 448 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(4);
}
#line 2837 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 78:
#line 452 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(5);
}
#line 2845 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 79:
#line 456 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(6);
}
#line 2853 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 80:
#line 460 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(7);
}
#line 2861 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 81:
#line 464 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(8);
}
#line 2869 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 82:
#line 468 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(9);
}
#line 2877 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 83:
#line 472 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAssignmentOperator_create(10);
}
#line 2885 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 84:
#line 479 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, 0);
}
#line 2893 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 85:
#line 483 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpression_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 2901 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 86:
#line 490 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppConstantExpression_create((yyvsp[0]).pContext);
}
#line 2909 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 87:
#line 497 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 2917 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 88:
#line 501 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0);
}
#line 2925 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 89:
#line 505 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 2933 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 90:
#line 509 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 2941 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 91:
#line 513 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 2949 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 92:
#line 517 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 2957 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 93:
#line 521 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatement_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 2965 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 94:
#line 528 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).sValue, 0, (yyvsp[-2]).sComment);
}
#line 2973 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 95:
#line 532 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, (yyvsp[-3]).sComment);
}
#line 2981 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 96:
#line 536 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLabeledStatement_create(0, (yyvsp[0]).pContext, 0, 1, (yyvsp[-2]).sComment);
}
#line 2989 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 97:
#line 543 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create(0, (yyvsp[0]).sComment);
}
#line 2997 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 98:
#line 547 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppExpressionStatement_create((yyvsp[-1]).pContext, (yyvsp[0]).sComment);
}
#line 3005 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 99:
#line 554 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0, (yyvsp[-1]).sComment);
}
#line 3013 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 100:
#line 558 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext, (yyvsp[-2]).sComment);
}
#line 3021 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 101:
#line 565 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppStatementSeq_create((yyvsp[0]).pContext);
}
#line 3029 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 102:
#line 569 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3037 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 103:
#line 580 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1, (yyvsp[-4]).sComment);
}
#line 3045 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 104:
#line 584 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1, (yyvsp[-6]).sComment);
}
#line 3053 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 105:
#line 588 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSelectionStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, (yyvsp[-4]).sComment);
}
#line 3061 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 106:
#line 595 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-4]).sComment);
}
#line 3069 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 107:
#line 599 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[-5]).pContext, 1, (yyvsp[-6]).sComment);
}
#line 3077 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 108:
#line 603 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-3]).pContext, 0, 0, (yyvsp[0]).pContext, 0, (yyvsp[-5]).sComment);
}
#line 3085 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 109:
#line 607 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-6]).sComment);
}
#line 3093 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 110:
#line 611 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-6]).sComment);
}
#line 3101 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 111:
#line 615 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppIterationStatement_create((yyvsp[-5]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-7]).sComment);
}
#line 3109 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 112:
#line 622 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create((yyvsp[0]).pContext, 0);
}
#line 3117 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 113:
#line 626 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppForInitStatement_create(0, (yyvsp[0]).pContext);
}
#line 3125 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 114:
#line 633 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 0, (yyvsp[-1]).sComment);
}
#line 3133 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 115:
#line 637 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 1, (yyvsp[-1]).sComment);
}
#line 3141 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 116:
#line 641 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, 0, 2, (yyvsp[-1]).sComment);
}
#line 3149 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 117:
#line 645 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create((yyvsp[-1]).pContext, 0, 2, (yyvsp[-2]).sComment);
}
#line 3157 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 118:
#line 649 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppJumpStatement_create(0, (yyvsp[-1]).sValue, 3, (yyvsp[-2]).sComment);
}
#line 3165 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 119:
#line 656 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationStatement_create((yyvsp[0]).pContext);
}
#line 3173 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 120:
#line 663 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarationSeq_create((yyvsp[0]).pContext);
}
#line 3181 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 121:
#line 667 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3189 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 122:
#line 674 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3197 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 123:
#line 678 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3205 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 124:
#line 682 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3213 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 125:
#line 686 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3221 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 126:
#line 690 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaration_create(0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 3229 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 127:
#line 697 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3237 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 128:
#line 701 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3245 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 129:
#line 705 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3253 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 130:
#line 709 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3261 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 131:
#line 713 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBlockDeclaration_create(0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 3269 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 132:
#line 720 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 3277 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 133:
#line 724 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0);
}
#line 3285 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 134:
#line 728 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 3293 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 135:
#line 732 "cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 1, (yyvsp[-3]).sComment);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3309 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 136:
#line 744 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 0, 0);
}
#line 3317 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 137:
#line 748 "cpp_y.y" /* yacc.c:1646  */
    {
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1, (yyvsp[-4]).sComment);

  (yyval).pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3333 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 138:
#line 763 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(0, (yyvsp[0]).sComment);
}
#line 3341 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 139:
#line 767 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(1, (yyvsp[0]).sComment);
}
#line 3349 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 140:
#line 771 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(2, (yyvsp[0]).sComment);
}
#line 3357 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 141:
#line 775 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(3, (yyvsp[0]).sComment);
}
#line 3365 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 142:
#line 779 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(4, (yyvsp[0]).sComment);
}
#line 3373 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 143:
#line 783 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(5, (yyvsp[0]).sComment);
}
#line 3381 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 144:
#line 787 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(6, (yyvsp[0]).sComment);
}
#line 3389 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 145:
#line 791 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(7, (yyvsp[0]).sComment);
}
#line 3397 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 146:
#line 795 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(8, (yyvsp[0]).sComment);
}
#line 3405 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 147:
#line 799 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(9, (yyvsp[0]).sComment);
}
#line 3413 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 148:
#line 803 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifier_create(10, (yyvsp[0]).sComment);
}
#line 3421 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 149:
#line 810 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclModifierList_create((yyvsp[0]).pContext);
}
#line 3429 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 150:
#line 814 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3437 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 151:
#line 821 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 3447 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 152:
#line 827 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-2]).pContext, 0, 0, 1);
}
#line 3457 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 153:
#line 833 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 3467 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 154:
#line 839 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 1);
}
#line 3477 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 155:
#line 845 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_popScope(adtCpp_ScopeManager);

  (yyval).pContext = adtCppClassSpecifier_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 3487 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 156:
#line 854 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);
}
#line 3497 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 157:
#line 860 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppEnumSpecifierName_create((yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);
}
#line 3507 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 158:
#line 869 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[0]).pContext, 0);
}
#line 3515 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 159:
#line 873 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create(0, (yyvsp[-2]).pContext, 1);
}
#line 3523 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 160:
#line 877 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumSpecifier_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext, 1);
}
#line 3531 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 161:
#line 891 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 0, 0, (yyvsp[0]).sComment);
}
#line 3539 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 162:
#line 895 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[0]).sValue, 1, 0, (yyvsp[0]).sComment);
}
#line 3547 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 163:
#line 899 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 0, (yyvsp[0]).sComment);
}
#line 3555 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 164:
#line 903 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 0, (yyvsp[0]).sComment);
}
#line 3563 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 165:
#line 907 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 0, (yyvsp[0]).sComment);
}
#line 3571 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 166:
#line 911 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 0, (yyvsp[0]).sComment);
}
#line 3579 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 167:
#line 915 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 0, (yyvsp[0]).sComment);
}
#line 3587 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 168:
#line 919 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 0, (yyvsp[-1]).sComment);
}
#line 3595 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 169:
#line 923 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 0, (yyvsp[0]).sComment);
}
#line 3603 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 170:
#line 927 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 0, (yyvsp[-1]).sComment);
}
#line 3611 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 171:
#line 931 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 0, (yyvsp[0]).sComment);
}
#line 3619 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 172:
#line 935 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 0, (yyvsp[-1]).sComment);
}
#line 3627 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 173:
#line 939 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 0, (yyvsp[-1]).sComment);
}
#line 3635 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 174:
#line 943 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 0, (yyvsp[-2]).sComment);
}
#line 3643 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 175:
#line 947 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 0, (yyvsp[-1]).sComment);
}
#line 3651 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 176:
#line 951 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 0, (yyvsp[-2]).sComment);
}
#line 3659 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 177:
#line 955 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 0, (yyvsp[-1]).sComment);
}
#line 3667 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 178:
#line 959 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 0, (yyvsp[0]).sComment);
}
#line 3675 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 179:
#line 963 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 0, (yyvsp[-1]).sComment);
}
#line 3683 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 180:
#line 967 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 0, (yyvsp[-1]).sComment);
}
#line 3691 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 181:
#line 971 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 0, (yyvsp[-2]).sComment);
}
#line 3699 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 182:
#line 975 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 0, (yyvsp[-1]).sComment);
}
#line 3707 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 183:
#line 979 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 0, (yyvsp[-2]).sComment);
}
#line 3715 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 184:
#line 983 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 0, (yyvsp[-1]).sComment);
}
#line 3723 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 185:
#line 987 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 0, (yyvsp[0]).sComment);
}
#line 3731 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 186:
#line 991 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 0, (yyvsp[0]).sComment);
}
#line 3739 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 187:
#line 995 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 0, (yyvsp[-1]).sComment);
}
#line 3747 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 188:
#line 999 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 0, (yyvsp[-1]).sComment);
}
#line 3755 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1003 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 0, (yyvsp[-2]).sComment);
}
#line 3763 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1007 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 0, (yyvsp[-2]).sComment);
}
#line 3771 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1011 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 0, (yyvsp[0]).sComment);
}
#line 3779 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1015 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 0, 1, (yyvsp[-1]).sComment);
}
#line 3787 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1019 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create((yyvsp[-1]).sValue, 1, 1, (yyvsp[-1]).sComment);
}
#line 3795 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1023 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 2, 1, (yyvsp[-1]).sComment);
}
#line 3803 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1027 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 3, 1, (yyvsp[-1]).sComment);
}
#line 3811 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1031 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 4, 1, (yyvsp[-1]).sComment);
}
#line 3819 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1035 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 5, 1, (yyvsp[-1]).sComment);
}
#line 3827 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1039 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 6, 1, (yyvsp[-1]).sComment);
}
#line 3835 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1043 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 7, 1, (yyvsp[-2]).sComment);
}
#line 3843 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1047 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 8, 1, (yyvsp[-1]).sComment);
}
#line 3851 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1051 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 9, 1, (yyvsp[-2]).sComment);
}
#line 3859 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1055 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 10, 1, (yyvsp[-1]).sComment);
}
#line 3867 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1059 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 11, 1, (yyvsp[-2]).sComment);
}
#line 3875 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1063 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 12, 1, (yyvsp[-2]).sComment);
}
#line 3883 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1067 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 13, 1, (yyvsp[-3]).sComment);
}
#line 3891 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1071 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 14, 1, (yyvsp[-2]).sComment);
}
#line 3899 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1075 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 15, 1, (yyvsp[-3]).sComment);
}
#line 3907 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1079 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 16, 1, (yyvsp[-2]).sComment);
}
#line 3915 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1083 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 17, 1, (yyvsp[-1]).sComment);
}
#line 3923 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1087 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 18, 1, (yyvsp[-2]).sComment);
}
#line 3931 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1091 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 19, 1, (yyvsp[-2]).sComment);
}
#line 3939 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1095 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 20, 1, (yyvsp[-3]).sComment);
}
#line 3947 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1099 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 21, 1, (yyvsp[-2]).sComment);
}
#line 3955 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1103 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 22, 1, (yyvsp[-3]).sComment);
}
#line 3963 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1107 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 23, 1, (yyvsp[-2]).sComment);
}
#line 3971 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1111 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 24, 1, (yyvsp[-1]).sComment);
}
#line 3979 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1115 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 25, 1, (yyvsp[-1]).sComment);
}
#line 3987 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1119 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 26, 1, (yyvsp[-2]).sComment);
}
#line 3995 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1123 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 27, 1, (yyvsp[-2]).sComment);
}
#line 4003 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1127 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 28, 1, (yyvsp[-3]).sComment);
}
#line 4011 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1131 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 29, 1, (yyvsp[-3]).sComment);
}
#line 4019 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1135 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppSimpleTypeSpecifier_create(0, 30, 1, (yyvsp[-1]).sComment);
}
#line 4027 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1142 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorList_create((yyvsp[0]).pContext);
}
#line 4035 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1146 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4043 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1153 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create(0, (yyvsp[0]).sValue, (yyvsp[0]).sComment);
}
#line 4051 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1157 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppEnumeratorDefinition_create((yyvsp[0]).pContext, (yyvsp[-2]).sValue, (yyvsp[-2]).sComment);
}
#line 4059 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1164 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, (yyvsp[-3]).sValue, (yyvsp[-3]).sComment);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4069 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1170 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceDefinition_create((yyvsp[-1]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 4077 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1177 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);

  (yyval).sValue   = (yyvsp[0]).sValue;
  (yyval).sComment = (yyvsp[-1]).sComment;
}
#line 4088 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1186 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppNamespaceAliasDefinition_create((yyvsp[-3]).sValue, (yyvsp[-1]).sValue, (yyvsp[-4]).sComment);
}
#line 4096 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1193 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 0, (yyvsp[-2]).sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4106 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1199 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDeclaration_create((yyvsp[-1]).sValue, 1, (yyvsp[-3]).sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4116 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1208 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 0, (yyvsp[-3]).sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4126 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1214 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppUsingDirective_create((yyvsp[-1]).sValue, 1, (yyvsp[-3]).sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, (yyvsp[-1]).sValue);
}
#line 4136 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1223 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppAsmDefinition_create((yyvsp[-2]).sValue, (yyvsp[-4]).sComment);
}
#line 4144 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1230 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, 0, (yyvsp[-2]).sValue, (yyvsp[-3]).sComment);
}
#line 4152 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1234 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create((yyvsp[-1]).pContext, 0, (yyvsp[-3]).sValue, (yyvsp[-4]).sComment);
}
#line 4160 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1238 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppLinkageSpecification_create(0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, (yyvsp[-2]).sComment);
}
#line 4168 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1245 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclaratorList_create((yyvsp[0]).pContext);
}
#line 4176 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1249 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4184 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1256 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 4192 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1260 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitDeclarator_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4200 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1269 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4208 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1273 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4216 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1280 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 0, 0, 0, (yyvsp[0]).sComment, 1);
}
#line 4224 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1284 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 0, 1, 0, 0, (yyvsp[0]).sComment, 0);
}
#line 4232 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1288 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 0, 0, 0, (yyvsp[0]).sComment, 1);
}
#line 4240 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1292 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, (yyvsp[0]).sValue, 0, 1, 1, 0, 0, (yyvsp[0]).sComment, 0);
}
#line 4248 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1296 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 0, 0, 0, 0, (yyvsp[-1]).sComment, 1);
}
#line 4256 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1300 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, (yyvsp[0]).pContext, (yyvsp[-1]).sValue, 0, 1, 0, 0, 0, (yyvsp[-1]).sComment, 1);
}
#line 4264 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1330 "cpp_y.y" /* yacc.c:1646  */
    {
 (yyval).pContext = (yyvsp[0]).pContext;
}
#line 4272 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1337 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4286 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1347 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4300 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1357 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4314 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1367 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4328 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1377 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4342 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1387 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4356 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1397 "cpp_y.y" /* yacc.c:1646  */
    {
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, (yyvsp[-1]).sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 1;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4370 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1410 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4380 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1416 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4390 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1422 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4400 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1428 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-1]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4410 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1434 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4420 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1440 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclarator_create((yyvsp[-2]).pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4430 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1449 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, 0);
}
#line 4438 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1453 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, 0);
}
#line 4446 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1457 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create(0, (yyvsp[-2]).pContext);
}
#line 4454 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1461 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppDeclaratorDims_create((yyvsp[-1]).pContext, (yyvsp[-3]).pContext);
}
#line 4462 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1468 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create(0, 1, 0);
}
#line 4470 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1472 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4478 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1476 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-1]).pContext, 1, 0);
}
#line 4486 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1480 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationClause_create((yyvsp[-2]).pContext, 1, 1);
}
#line 4494 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1487 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclarationList_create((yyvsp[0]).pContext);
}
#line 4502 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1491 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4510 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1498 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4518 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1502 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4526 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1506 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4534 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1510 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4542 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1514 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create(0, (yyvsp[0]).pContext, 0, 0);
}
#line 4550 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1518 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppParameterDeclaration_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 4558 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1525 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4566 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1529 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4574 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1533 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4582 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1537 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4590 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1541 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0);
}
#line 4598 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1545 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4606 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1549 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 4614 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1556 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4622 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1560 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4630 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1564 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4638 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1568 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4646 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1572 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 1);
}
#line 4654 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1576 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4662 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1580 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionDefinition_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4670 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1590 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppFunctionBody_create((yyvsp[0]).pContext);
}
#line 4678 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1597 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4686 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1604 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create(0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4696 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1610 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCompoundStatement_create((yyvsp[-1]).pContext, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4706 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1619 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create((yyvsp[0]).pContext, 0);
}
#line 4714 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1623 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializer_create(0, (yyvsp[-1]).pContext);
}
#line 4722 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1630 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create((yyvsp[0]).pContext, 0, 0);
}
#line 4730 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1634 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-1]).pContext, 0);
}
#line 4738 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1638 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, (yyvsp[-2]).pContext, 1);
}
#line 4746 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1642 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerClause_create(0, 0, 0);
}
#line 4754 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1649 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppInitializerList_create((yyvsp[0]).pContext);
}
#line 4762 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1653 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4770 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1660 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4781 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1667 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4792 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1674 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4803 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1681 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(0, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4814 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1688 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4825 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1695 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4836 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1702 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4847 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1709 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(1, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4858 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1716 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4869 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1723 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 0, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4880 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1730 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4891 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1737 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppClassKey_create(2, (yyvsp[0]).sValue, 1, (yyvsp[-1]).sComment);

  scopeManager_addType(adtCpp_ScopeManager, (yyvsp[0]).sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, (yyvsp[0]).sValue, 0);
}
#line 4902 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1747 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberSpecification_create((yyvsp[0]).pContext);
}
#line 4910 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1751 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4918 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1758 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4926 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1762 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 1);
}
#line 4934 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1766 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 4942 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1770 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 4950 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1774 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
#line 4958 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1778 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 4966 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1782 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 4974 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1786 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 2, 0);
}
#line 4982 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1790 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 3, 0);
}
#line 4990 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1797 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarationList_create((yyvsp[0]).pContext);
}
#line 4998 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1801 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5006 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1808 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[0]).pContext, 0);
}
#line 5014 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1812 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemberDeclarator_create((yyvsp[-2]).pContext, (yyvsp[0]).sValue);
}
#line 5022 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1819 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppBaseSpecifierList_create((yyvsp[0]).pContext);
}
#line 5030 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1823 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5038 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1830 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 0, (yyvsp[0]).sValue);
}
#line 5048 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1836 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 0, (yyvsp[0]).sValue);
}
#line 5058 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1842 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 0, (yyvsp[0]).sValue);
}
#line 5068 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1848 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 0, (yyvsp[0]).sValue);
}
#line 5078 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1854 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 0, 1, (yyvsp[0]).sValue);
}
#line 5088 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1860 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 0, 1, (yyvsp[0]).sValue);
}
#line 5098 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1866 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 0, 1, (yyvsp[0]).sValue);
}
#line 5108 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1872 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 0, 1, (yyvsp[0]).sValue);
}
#line 5118 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1878 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 0, (yyvsp[0]).sValue);
}
#line 5128 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1884 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5138 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1890 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5148 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1896 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5158 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1902 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(0, 1, 1, (yyvsp[0]).sValue);
}
#line 5168 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1908 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5178 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1914 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5188 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1920 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5198 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1926 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 0, (yyvsp[0]).sValue);
}
#line 5208 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1932 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 0, (yyvsp[0]).sValue);
}
#line 5218 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1938 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 0, (yyvsp[0]).sValue);
}
#line 5228 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1944 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(1, 1, 1, (yyvsp[0]).sValue);
}
#line 5238 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1950 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(2, 1, 1, (yyvsp[0]).sValue);
}
#line 5248 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1956 "cpp_y.y" /* yacc.c:1646  */
    {
  scopeManager_inheritsFrom(adtCpp_ScopeManager, (yyvsp[0]).sValue);

  (yyval).pContext = adtCppBaseSpecifier_create(3, 1, 1, (yyvsp[0]).sValue);
}
#line 5258 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1965 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppCtorInitializer_create((yyvsp[0]).pContext);
}
#line 5266 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1972 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerList_create((yyvsp[0]).pContext);
}
#line 5274 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1976 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5282 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1983 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-2]).pContext, 0);
}
#line 5290 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1987 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializer_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5298 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1994 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5306 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1998 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5314 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2002 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(0, (yyvsp[0]).sValue);
}
#line 5322 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2006 "cpp_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtCppMemInitializerId_create(1, (yyvsp[0]).sValue);
}
#line 5330 "../../src/cpp_y.c" /* yacc.c:1646  */
    break;


#line 5334 "../../src/cpp_y.c" /* yacc.c:1646  */
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
