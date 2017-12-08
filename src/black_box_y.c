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
#line 1 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:339  */

/*
 * black_box_y.y
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
 * black box parser grammar for Auto-differentiation utility. This parses
 * black box definitions for functions that are not to be differentiated
 * with ADT. These definitions are provided by our own simplfied syntax
 * and then translated into a form that tapenade understands. For example,
 * this is a definition in a Pascal comment field:
 *
 * {D/D(.) INV(X+Y),
 *  D/D(X) .*X,
 *  D/D(Y) .*(1/Y);}
 *
 * You can also include a black box dependency specification with, for example,
 *
 * {BLACKBOX ReadNotWritten:(1,0,0) NotReadThenWritten:(0,1,0) deps:(1,0,0,id,id);}
 *
 *
 * For stand alone black box definition files you can have something like,
 *   MyFunction(X : real_array in, Y : real_array in) : real_array
 *   begin
 *     D/D(.) INV(X+Y),
 *     D/D(X) .*X,
 *     D/D(Y) .*(1/Y);
 *   end;
 */

#include <stdio.h>
#include "lexer.h"
#include "adtblackbox.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr    stdout

#define YYSTYPE   blackBoxType


typedef struct blackBoxDefBeginInfo
{
  const char*   pIdentifier;
  void*         pArgDefList;
  int           nArgType;

} blackBoxDefBeginInfo;



#line 130 "..\\src\\black_box_y.c" /* yacc.c:339  */

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
   by #include "black_box_y.h".  */
#ifndef YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED
# define YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED
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
    LBRACKET = 258,
    RBRACKET = 259,
    PLUS = 260,
    MINUS = 261,
    MULTIPLY = 262,
    DIVIDE = 263,
    POWER = 264,
    PERIOD = 265,
    IDENTIFIER = 266,
    NUMBER_FIXED = 267,
    NUMBER_FLOAT = 268,
    COMMA = 269,
    COLON = 270,
    SEMICOLON = 271,
    DERIV_OP = 272,
    BLACKBOX = 273,
    READ_NOT_WRITTEN = 274,
    NOT_READ_THEN_WRITTEN = 275,
    NOT_READ_NOT_WRITTEN = 276,
    READ_THEN_WRITTEN = 277,
    DEPS = 278,
    ID = 279,
    REAL = 280,
    INTEGER = 281,
    COMPLEX = 282,
    CHARACTER = 283,
    BOOLEAN = 284,
    REAL_ARRAY = 285,
    INTEGER_ARRAY = 286,
    COMPLEX_ARRAY = 287,
    CHARACTER_ARRAY = 288,
    BOOLEAN_ARRAY = 289,
    IN = 290,
    OUT = 291,
    F_BEGIN = 292,
    F_END = 293,
    FUNCTION = 294,
    PROCEDURE = 295,
    RESULT = 296
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

#endif /* !YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 223 "..\\src\\black_box_y.c" /* yacc.c:358  */

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    84,    88,    95,   106,   117,   128,   139,
     150,   179,   191,   206,   215,   219,   223,   227,   231,   235,
     239,   243,   247,   251,   258,   262,   266,   270,   277,   281,
     285,   292,   296,   303,   310,   314,   321,   325,   329,   333,
     337,   344,   348,   355,   359,   366,   370,   377,   381,   385,
     392,   396,   400,   407,   411,   418,   422,   426,   433,   437,
     441,   445,   449,   456,   460
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LBRACKET", "RBRACKET", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "POWER", "PERIOD", "IDENTIFIER", "NUMBER_FIXED",
  "NUMBER_FLOAT", "COMMA", "COLON", "SEMICOLON", "DERIV_OP", "BLACKBOX",
  "READ_NOT_WRITTEN", "NOT_READ_THEN_WRITTEN", "NOT_READ_NOT_WRITTEN",
  "READ_THEN_WRITTEN", "DEPS", "ID", "REAL", "INTEGER", "COMPLEX",
  "CHARACTER", "BOOLEAN", "REAL_ARRAY", "INTEGER_ARRAY", "COMPLEX_ARRAY",
  "CHARACTER_ARRAY", "BOOLEAN_ARRAY", "IN", "OUT", "F_BEGIN", "F_END",
  "FUNCTION", "PROCEDURE", "RESULT", "$accept", "root", "derivativeList",
  "derivative", "defBegin", "defEnd", "argType", "dirType", "argDef",
  "argDefList", "derivativeExtended", "blackBoxSpecList", "blackBoxSpec",
  "ident", "identList", "derivativeExtendedList", "exprAdditive",
  "exprMultiplicative", "exprPower", "exprUnary", "exprPostfix", "argList", YY_NULLPTR
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
     295,   296
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -12,     6,    -6,    19,    22,    57,   -12,   -69,   -12,    68,
     -69,    23,    61,    73,   105,   108,    71,   -69,    50,    79,
     -69,   -69,   -14,   -69,   120,   121,   123,   124,   125,   126,
     127,   -69,   -69,    -9,    -9,   -69,    49,    49,    -4,    -4,
      -4,    -4,    -4,   116,   117,   -69,     8,    17,    49,    53,
      53,   130,   -69,   -69,    69,   103,   128,   -69,   -69,    13,
     -69,   -69,   -69,    54,    55,    59,    63,    66,    15,    75,
     119,    -9,    35,    80,   -69,   -69,    49,    49,    49,   118,
      49,    49,    49,   -69,   -69,    -4,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     100,   104,    77,    75,   -69,    75,   -69,   -69,   -69,   109,
      67,   103,   103,   135,   -69,    20,   128,   128,   -69,   -69,
     -69,   -69,   -69,   -69,   106,   -69,    49,   129,   118,   -69,
     -69,   109,   137,   -69,   132,   138,    49,   109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       9,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       1,     4,     0,    10,     0,     0,     0,     0,     0,     0,
       0,     8,    35,     0,     0,    13,     7,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,    60,    58,    59,     0,    47,    50,    53,    55,     0,
      42,    41,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     6,    36,     0,    37,    38,    39,    40,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     0,     0,    30,     0,    32,    11,    62,    63,
       0,    48,    49,     0,    45,     0,    51,    52,    54,    44,
      26,    27,    28,    29,     0,    61,     0,     0,     0,     5,
      12,    64,     0,    46,     0,     0,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   136,     1,   -69,   -69,   -68,    44,    76,   114,
      21,   -69,   134,    70,    56,   -69,   -37,    39,    38,    74,
      72,   -69
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    23,   102,   103,    45,    46,
     114,    16,    17,    62,    63,   115,    54,    55,    56,    57,
      58,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,   104,    43,     1,     2,     1,     2,    21,    60,     9,
      10,    73,    70,    11,    12,    13,    14,    15,    77,    78,
      61,    72,    71,    21,    35,     3,     4,     3,     4,    83,
      18,    71,    44,    19,   128,   123,   129,   124,    26,   109,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,    48,    33,    49,    50,    48,    20,    84,    86,
      51,    52,    53,    87,    51,    52,    53,    88,    85,    85,
      89,   125,   107,    85,    77,    78,    27,    85,    24,    25,
      85,   126,    34,    79,   108,    77,    78,    31,    28,   131,
      11,    12,    13,    14,    15,    64,    65,    66,    67,   137,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      80,    81,   100,   101,    77,    78,   111,   112,   116,   117,
      29,    74,    75,    30,    36,    37,    38,    39,    40,    41,
      42,    68,    69,    76,   105,   113,   120,    82,   127,   121,
     132,   134,   135,   130,    22,   136,   122,   106,    47,   133,
      32,     0,     0,     0,     0,   119,   118
};

static const yytype_int16 yycheck[] =
{
      37,    69,    11,    17,    18,    17,    18,     6,    12,     3,
      16,    48,     4,    19,    20,    21,    22,    23,     5,     6,
      24,     4,    14,    22,    38,    39,    40,    39,    40,    16,
      11,    14,    41,    11,    14,   103,    16,   105,    15,    76,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,     3,     3,     5,     6,     3,     0,     4,     4,
      11,    12,    13,     4,    11,    12,    13,     4,    14,    14,
       4,     4,    37,    14,     5,     6,    15,    14,    10,    11,
      14,    14,     3,    14,     4,     5,     6,    16,    15,   126,
      19,    20,    21,    22,    23,    39,    40,    41,    42,   136,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       7,     8,    35,    36,     5,     6,    77,    78,    80,    81,
      15,    49,    50,    15,     4,     4,     3,     3,     3,     3,
       3,    15,    15,     3,    15,    17,    36,     9,     3,    35,
      11,     4,    10,    37,     8,     7,   102,    71,    34,   128,
      16,    -1,    -1,    -1,    -1,    85,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    18,    39,    40,    43,    44,    45,    46,     3,
      16,    19,    20,    21,    22,    23,    53,    54,    11,    11,
       0,    45,    44,    47,    10,    11,    15,    15,    15,    15,
      15,    16,    54,     3,     3,    38,     4,     4,     3,     3,
       3,     3,     3,    11,    41,    50,    51,    51,     3,     5,
       6,    11,    12,    13,    58,    59,    60,    61,    62,    58,
      12,    24,    55,    56,    56,    56,    56,    56,    15,    15,
       4,    14,     4,    58,    62,    62,     3,     5,     6,    14,
       7,     8,     9,    16,     4,    14,     4,     4,     4,     4,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    48,    49,    48,    15,    50,    37,     4,    58,
      63,    59,    59,    17,    52,    57,    60,    60,    61,    55,
      36,    35,    49,    48,    48,     4,    14,     3,    14,    16,
      37,    58,    11,    52,     4,    10,     7,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    46,    46,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    49,    49,    49,    49,    50,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    54,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      59,    59,    59,    60,    60,    61,    61,    61,    62,    62,
      62,    62,    62,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     6,     4,     3,     2,
       2,     6,     8,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       3,     1,     3,     7,     1,     2,     5,     5,     5,     5,
       5,     1,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     1,     2,     2,     1,     1,
       1,     4,     3,     1,     3
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
#line 78 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  adtBlackBox_SetRoot((yyvsp[0]).pContext);
}
#line 1399 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 3:
#line 85 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxDerivativeList_create((yyvsp[0]).pContext);
}
#line 1407 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 4:
#line 89 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 1415 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 5:
#line 96 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* multi-part derivative def */
  (yyval).pContext = adtBlackBoxDerivative_create(0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 1430 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 6:
#line 107 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* complete derivative def */
  (yyval).pContext = adtBlackBoxDerivative_create((yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0);
}
#line 1445 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* null derivative def */
  (yyval).pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 1, 0);
}
#line 1460 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 8:
#line 129 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  (yyval).pContext = adtBlackBoxDerivative_create(0, 0, 0, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 1475 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 9:
#line 140 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  (yyval).pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, 0);
}
#line 1490 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 10:
#line 151 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  if (yyBlackBoxIsFile != 0)
  {
    /* stand alone black box def */
    if (yyBlackBoxReentrancyCount > 0)
    {
      yyBlackBoxerror("Nested stand-alone black box definitions not allowed.");
      YYERROR;
    }
    else
    {
      void*                         pBlackBoxDef;
      struct blackBoxDefBeginInfo*  pInfo;

      pInfo         = (struct blackBoxDefBeginInfo*)(yyvsp[-1]).pContext;
      pBlackBoxDef  = adtBlackBoxStandAloneDef_create(pInfo->pIdentifier, pInfo->pArgDefList, pInfo->nArgType, (yyvsp[0]).pContext);
      (yyval).pContext   = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, pBlackBoxDef);
    }
  }
  else
  {
    yyBlackBoxerror("Stand-alone black box definitions not allowed in comment fields.");
    YYERROR;
  }
}
#line 1520 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 11:
#line 180 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = (yyvsp[-4]).sValue;
  Info.pArgDefList  = (yyvsp[-2]).pContext;
  Info.nArgType     = -1;

  (yyval).pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1536 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 12:
#line 192 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = (yyvsp[-6]).sValue;
  Info.pArgDefList  = (yyvsp[-4]).pContext;
  Info.nArgType     = (yyvsp[-1]).nValue;

  (yyval).pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1552 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 13:
#line 207 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = (yyvsp[-1]).pContext;

  yyBlackBoxReentrancyCount--;
}
#line 1562 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 14:
#line 216 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 0;
}
#line 1570 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 15:
#line 220 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 1;
}
#line 1578 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 16:
#line 224 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 2;
}
#line 1586 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 17:
#line 228 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 3;
}
#line 1594 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 4;
}
#line 1602 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 19:
#line 236 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 5;
}
#line 1610 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 20:
#line 240 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 6;
}
#line 1618 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 21:
#line 244 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 7;
}
#line 1626 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 22:
#line 248 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 8;
}
#line 1634 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 23:
#line 252 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 9;
}
#line 1642 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 24:
#line 259 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 1;
}
#line 1650 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 25:
#line 263 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 2;
}
#line 1658 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 26:
#line 267 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 0;
}
#line 1666 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 27:
#line 271 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).nValue = 0;
}
#line 1674 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 28:
#line 278 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxArgDef_create((yyvsp[-3]).sValue, (yyvsp[-1]).nValue, (yyvsp[0]).nValue);
}
#line 1682 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 29:
#line 282 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxArgDef_create((yyvsp[-3]).sValue, (yyvsp[0]).nValue, (yyvsp[-1]).nValue);
}
#line 1690 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 30:
#line 286 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxArgDef_create("result", (yyvsp[0]).nValue, 2);
}
#line 1698 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 31:
#line 293 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxArgDefList_create((yyvsp[0]).pContext);
}
#line 1706 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 32:
#line 297 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 1714 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 33:
#line 304 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxDerivative_create((yyvsp[-4]).sValue, (yyvsp[0]).pContext, 0, 0, 1, 0, 0);
}
#line 1722 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 34:
#line 311 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpecList_create((yyvsp[0]).pContext);
}
#line 1730 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 35:
#line 315 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 1738 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 36:
#line 322 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpec_create((yyvsp[-1]).pContext, 0);
}
#line 1746 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 37:
#line 326 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpec_create((yyvsp[-1]).pContext, 1);
}
#line 1754 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 38:
#line 330 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpec_create((yyvsp[-1]).pContext, 2);
}
#line 1762 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 39:
#line 334 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpec_create((yyvsp[-1]).pContext, 3);
}
#line 1770 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 40:
#line 338 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxSpec_create((yyvsp[-1]).pContext, 4);
}
#line 1778 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 41:
#line 345 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxIdent_create(-1);
}
#line 1786 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 42:
#line 349 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxIdent_create((yyvsp[0]).nValue);
}
#line 1794 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 43:
#line 356 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxIdentList_create((yyvsp[0]).pContext);
}
#line 1802 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 44:
#line 360 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 1810 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 45:
#line 367 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxDerivativeList_create((yyvsp[0]).pContext);
}
#line 1818 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 46:
#line 371 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 1826 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 47:
#line 378 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprAdditive_create(0, (yyvsp[0]).pContext, 0);
}
#line 1834 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 48:
#line 382 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprAdditive_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1);
}
#line 1842 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 49:
#line 386 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprAdditive_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 1850 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 50:
#line 393 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprMultiplicative_create(0, (yyvsp[0]).pContext, 0);
}
#line 1858 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 51:
#line 397 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprMultiplicative_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1);
}
#line 1866 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 52:
#line 401 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprMultiplicative_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 1874 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 53:
#line 408 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPower_create(0, (yyvsp[0]).pContext);
}
#line 1882 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 54:
#line 412 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPower_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 1890 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 55:
#line 419 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprUnary_create((yyvsp[0]).pContext, 0, 0);
}
#line 1898 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 56:
#line 423 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprUnary_create((yyvsp[0]).pContext, 1, 1);
}
#line 1906 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 57:
#line 427 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprUnary_create((yyvsp[0]).pContext, 1, 0);
}
#line 1914 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 58:
#line 434 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPostfix_create(0, (yyvsp[0]).nValue, 0, 0, 0, 0);
}
#line 1922 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 59:
#line 438 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPostfix_create(1, 0, (yyvsp[0]).dValue, 0, 0, 0);
}
#line 1930 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 60:
#line 442 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPostfix_create(2, 0, 0, (yyvsp[0]).sValue, 0, 0);
}
#line 1938 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 61:
#line 446 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPostfix_create(3, 0, 0, (yyvsp[-3]).sValue, (yyvsp[-1]).pContext, 0);
}
#line 1946 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 62:
#line 450 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxExprPostfix_create(4, 0, 0, 0, 0, (yyvsp[-1]).pContext);
}
#line 1954 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 63:
#line 457 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxArgList_create((yyvsp[0]).pContext);
}
#line 1962 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;

  case 64:
#line 461 "C:\\cygwin\\usr\\src\\adt\\src\\black_box_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtBlackBoxList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 1970 "..\\src\\black_box_y.c" /* yacc.c:1646  */
    break;


#line 1974 "..\\src\\black_box_y.c" /* yacc.c:1646  */
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
