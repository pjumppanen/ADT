/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "black_box_y.y"

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
 * {<
 *  D/D(.) INV(X+Y),
 *  D/D(X) .*X,
 *  D/D(Y) .*(1/Y);
 *  >}
 *
 * You can alos include a black box dependency specification with, for example,
 *
 * {<BLACKBOX ReadNotWritten:(1,0,0) NotReadThenWritten:(0,1,0) deps:(1,0,0,id,id);>}
 *
 * < and > symbols are used to indicate the start and end of a black box
 * definition and must be supplied for inline definitions. This allows the
 * black box definition to be embedded within existing comments and not break
 * the parsing of the definition.
 *
 * For stand alone black box definition files the braces are not required and
 * you can have something like,
 *   function MyFunction(X : real_array in, Y : real_array in) : real_array
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



#line 141 "../../src/black_box_y.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    LBRACKET = 258,
    RBRACKET = 259,
    PLUS = 260,
    MINUS = 261,
    MULTIPLY = 262,
    DIVIDE = 263,
    POWER = 264,
    PERIOD = 265,
    IDENTIFIER = 266,
    QUALIFIED_IDENTIFIER = 267,
    NUMBER_FIXED = 268,
    NUMBER_FLOAT = 269,
    COMMA = 270,
    COLON = 271,
    SEMICOLON = 272,
    DERIV_OP = 273,
    BLACKBOX = 274,
    READ_NOT_WRITTEN = 275,
    NOT_READ_THEN_WRITTEN = 276,
    NOT_READ_NOT_WRITTEN = 277,
    READ_THEN_WRITTEN = 278,
    DEPS = 279,
    ID = 280,
    REAL = 281,
    INTEGER = 282,
    COMPLEX = 283,
    CHARACTER = 284,
    BOOLEAN = 285,
    REAL_ARRAY = 286,
    INTEGER_ARRAY = 287,
    COMPLEX_ARRAY = 288,
    CHARACTER_ARRAY = 289,
    BOOLEAN_ARRAY = 290,
    IN = 291,
    OUT = 292,
    F_BEGIN = 293,
    F_END = 294,
    FUNCTION = 295,
    PROCEDURE = 296,
    RESULT = 297,
    BB_BEGIN = 298,
    BB_END = 299
  };
#endif
/* Tokens.  */
#define LBRACKET 258
#define RBRACKET 259
#define PLUS 260
#define MINUS 261
#define MULTIPLY 262
#define DIVIDE 263
#define POWER 264
#define PERIOD 265
#define IDENTIFIER 266
#define QUALIFIED_IDENTIFIER 267
#define NUMBER_FIXED 268
#define NUMBER_FLOAT 269
#define COMMA 270
#define COLON 271
#define SEMICOLON 272
#define DERIV_OP 273
#define BLACKBOX 274
#define READ_NOT_WRITTEN 275
#define NOT_READ_THEN_WRITTEN 276
#define NOT_READ_NOT_WRITTEN 277
#define READ_THEN_WRITTEN 278
#define DEPS 279
#define ID 280
#define REAL 281
#define INTEGER 282
#define COMPLEX 283
#define CHARACTER 284
#define BOOLEAN 285
#define REAL_ARRAY 286
#define INTEGER_ARRAY 287
#define COMPLEX_ARRAY 288
#define CHARACTER_ARRAY 289
#define BOOLEAN_ARRAY 290
#define IN 291
#define OUT 292
#define F_BEGIN 293
#define F_END 294
#define FUNCTION 295
#define PROCEDURE 296
#define RESULT 297
#define BB_BEGIN 298
#define BB_END 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    92,    96,   103,   114,   125,   136,   147,
     158,   187,   199,   211,   223,   238,   247,   251,   255,   259,
     263,   267,   271,   275,   279,   283,   290,   294,   298,   302,
     309,   313,   317,   324,   328,   335,   342,   346,   353,   357,
     361,   365,   369,   376,   380,   387,   391,   398,   402,   409,
     413,   417,   424,   428,   432,   439,   443,   450,   454,   458,
     465,   469,   473,   477,   481,   488,   492
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LBRACKET", "RBRACKET", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "POWER", "PERIOD", "IDENTIFIER",
  "QUALIFIED_IDENTIFIER", "NUMBER_FIXED", "NUMBER_FLOAT", "COMMA", "COLON",
  "SEMICOLON", "DERIV_OP", "BLACKBOX", "READ_NOT_WRITTEN",
  "NOT_READ_THEN_WRITTEN", "NOT_READ_NOT_WRITTEN", "READ_THEN_WRITTEN",
  "DEPS", "ID", "REAL", "INTEGER", "COMPLEX", "CHARACTER", "BOOLEAN",
  "REAL_ARRAY", "INTEGER_ARRAY", "COMPLEX_ARRAY", "CHARACTER_ARRAY",
  "BOOLEAN_ARRAY", "IN", "OUT", "F_BEGIN", "F_END", "FUNCTION",
  "PROCEDURE", "RESULT", "BB_BEGIN", "BB_END", "$accept", "root",
  "derivativeList", "derivative", "defBegin", "defEnd", "argType",
  "dirType", "argDef", "argDefList", "derivativeExtended",
  "blackBoxSpecList", "blackBoxSpec", "ident", "identList",
  "derivativeExtendedList", "exprAdditive", "exprMultiplicative",
  "exprPower", "exprUnary", "exprPostfix", "argList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,     7,    68,    91,    93,    38,   -13,   -75,   -13,   108,
     -75,    24,    79,    90,   116,   117,    77,   -75,    81,   131,
     132,   133,   -75,   -75,   -15,   -75,    89,   134,   136,   137,
     138,   139,   140,   -75,   -75,    -9,    -9,    -9,    -9,   -75,
       9,     9,    -4,    -4,    -4,    -4,    -4,   121,   128,   -75,
      27,    54,    55,    56,     9,    53,    53,   142,   -75,   -75,
      72,   113,    48,   -75,   -75,     2,   -75,   -75,   -75,    57,
      58,    59,    61,    64,    18,    82,   130,    -9,   135,   109,
     110,    12,   -75,   -75,     9,     9,     9,   141,     9,     9,
       9,   -75,   -75,    -4,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   112,   114,
      86,    82,   -75,    82,   -75,    82,   -75,   -75,   -75,   119,
      71,   113,   113,   149,   -75,    15,    48,    48,   -75,   -75,
     -75,   -75,   -75,   -75,   115,   118,   -75,     9,   143,   141,
     -75,   -75,   -75,   119,   151,   -75,   147,   153,     9,   119
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       9,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     1,     4,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     8,    37,     0,     0,     0,     0,    15,
       7,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,    62,    60,    61,
       0,    49,    52,    55,    57,     0,    44,    43,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     6,    38,     0,    39,    40,    41,    42,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,     0,    32,     0,    34,     0,    11,    12,    64,    65,
       0,    50,    51,     0,    47,     0,    53,    54,    56,    46,
      28,    29,    30,    31,     0,     0,    63,     0,     0,     0,
       5,    13,    14,    66,     0,    48,     0,     0,     0,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   150,     5,   -75,   -75,   -74,    51,    85,    -2,
      25,   -75,   152,    70,    37,   -75,   -41,    41,    40,    76,
      75,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    25,   110,   111,    49,    50,
     124,    16,    17,    68,    69,   125,    60,    61,    62,    63,
      64,   120
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,   112,    47,     1,     2,     1,     2,    85,    86,    66,
       9,    23,    54,    81,    55,    56,   118,    85,    86,    91,
      57,    67,    58,    59,    39,     3,     4,     3,     4,    23,
     139,    76,   140,    48,    51,    52,    53,   133,    22,   134,
      28,   135,    77,   119,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    54,    90,    78,    79,
      80,    92,    94,    95,    57,    96,    58,    59,    97,    77,
      77,    77,    93,    93,    93,   136,    93,    85,    86,    93,
      70,    71,    72,    73,    35,    10,   137,    87,    11,    12,
      13,    14,    15,    40,    33,    29,   143,    11,    12,    13,
      14,    15,    18,    19,    20,    21,    30,   149,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,    26,    27,
      88,    89,   108,   109,    85,    86,   121,   122,   126,   127,
      82,    83,    31,    32,    36,    37,    38,    74,    41,    42,
      43,    44,    45,    46,    75,    84,   113,   116,   117,   130,
     131,   115,   138,   141,   144,   146,   142,   147,    24,   123,
     148,   132,   114,   129,   145,     0,   128,     0,    34
};

static const yytype_int16 yycheck[] =
{
      41,    75,    11,    18,    19,    18,    19,     5,     6,    13,
       3,     6,     3,    54,     5,     6,     4,     5,     6,    17,
      11,    25,    13,    14,    39,    40,    41,    40,    41,    24,
      15,     4,    17,    42,    36,    37,    38,   111,     0,   113,
      16,   115,    15,    84,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     3,     9,     4,     4,
       4,     4,     4,     4,    11,     4,    13,    14,     4,    15,
      15,    15,    15,    15,    15,     4,    15,     5,     6,    15,
      43,    44,    45,    46,     3,    17,    15,    15,    20,    21,
      22,    23,    24,     4,    17,    16,   137,    20,    21,    22,
      23,    24,    11,    12,    11,    12,    16,   148,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    10,    11,
       7,     8,    36,    37,     5,     6,    85,    86,    88,    89,
      55,    56,    16,    16,     3,     3,     3,    16,     4,     3,
       3,     3,     3,     3,    16,     3,    16,    38,    38,    37,
      36,    16,     3,    38,    11,     4,    38,    10,     8,    18,
       7,   110,    77,    93,   139,    -1,    90,    -1,    16
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    18,    19,    40,    41,    46,    47,    48,    49,     3,
      17,    20,    21,    22,    23,    24,    56,    57,    11,    12,
      11,    12,     0,    48,    47,    50,    10,    11,    16,    16,
      16,    16,    16,    17,    57,     3,     3,     3,     3,    39,
       4,     4,     3,     3,     3,     3,     3,    11,    42,    53,
      54,    54,    54,    54,     3,     5,     6,    11,    13,    14,
      61,    62,    63,    64,    65,    61,    13,    25,    58,    59,
      59,    59,    59,    59,    16,    16,     4,    15,     4,     4,
       4,    61,    65,    65,     3,     5,     6,    15,     7,     8,
       9,    17,     4,    15,     4,     4,     4,     4,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      51,    52,    51,    16,    53,    16,    38,    38,     4,    61,
      66,    62,    62,    18,    55,    60,    63,    63,    64,    58,
      37,    36,    52,    51,    51,    51,     4,    15,     3,    15,
      17,    38,    38,    61,    11,    55,     4,    10,     7,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    49,    49,    49,    49,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52,    52,    52,    52,
      53,    53,    53,    54,    54,    55,    56,    56,    57,    57,
      57,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    62,    62,    62,    63,    63,    64,    64,    64,
      65,    65,    65,    65,    65,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     6,     4,     3,     2,
       2,     6,     6,     8,     8,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     4,     3,     1,     3,     7,     1,     2,     5,     5,
       5,     5,     5,     1,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     1,     2,     2,
       1,     1,     1,     4,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 86 "black_box_y.y"
{
  adtBlackBox_SetRoot(yyvsp[0].pContext);
}
#line 1556 "../../src/black_box_y.c"
    break;

  case 3:
#line 93 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxDerivativeList_create(yyvsp[0].pContext);
}
#line 1564 "../../src/black_box_y.c"
    break;

  case 4:
#line 97 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 1572 "../../src/black_box_y.c"
    break;

  case 5:
#line 104 "black_box_y.y"
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* multi-part derivative def */
  yyval.pContext = adtBlackBoxDerivative_create(0, yyvsp[-3].pContext, yyvsp[-1].pContext, 0, 0, 0, 0);
}
#line 1587 "../../src/black_box_y.c"
    break;

  case 6:
#line 115 "black_box_y.y"
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* complete derivative def */
  yyval.pContext = adtBlackBoxDerivative_create(yyvsp[-3].sValue, yyvsp[-1].pContext, 0, 0, 0, 0, 0);
}
#line 1602 "../../src/black_box_y.c"
    break;

  case 7:
#line 126 "black_box_y.y"
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* null derivative def */
  yyval.pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 1, 0);
}
#line 1617 "../../src/black_box_y.c"
    break;

  case 8:
#line 137 "black_box_y.y"
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  yyval.pContext = adtBlackBoxDerivative_create(0, 0, 0, yyvsp[-1].pContext, 0, 0, 0);
}
#line 1632 "../../src/black_box_y.c"
    break;

  case 9:
#line 148 "black_box_y.y"
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  yyval.pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, 0);
}
#line 1647 "../../src/black_box_y.c"
    break;

  case 10:
#line 159 "black_box_y.y"
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

      pInfo         = (struct blackBoxDefBeginInfo*)yyvsp[-1].pContext;
      pBlackBoxDef  = adtBlackBoxStandAloneDef_create(pInfo->pIdentifier, pInfo->pArgDefList, pInfo->nArgType, yyvsp[0].pContext);
      yyval.pContext   = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, pBlackBoxDef);
    }
  }
  else
  {
    yyBlackBoxerror("Stand-alone black box definitions not allowed in comment fields.");
    YYERROR;
  }
}
#line 1677 "../../src/black_box_y.c"
    break;

  case 11:
#line 188 "black_box_y.y"
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = yyvsp[-4].sValue;
  Info.pArgDefList  = yyvsp[-2].pContext;
  Info.nArgType     = -1;

  yyval.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1693 "../../src/black_box_y.c"
    break;

  case 12:
#line 200 "black_box_y.y"
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = yyvsp[-4].sValue;
  Info.pArgDefList  = yyvsp[-2].pContext;
  Info.nArgType     = -1;

  yyval.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1709 "../../src/black_box_y.c"
    break;

  case 13:
#line 212 "black_box_y.y"
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = yyvsp[-6].sValue;
  Info.pArgDefList  = yyvsp[-4].pContext;
  Info.nArgType     = yyvsp[-1].nValue;

  yyval.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1725 "../../src/black_box_y.c"
    break;

  case 14:
#line 224 "black_box_y.y"
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = yyvsp[-6].sValue;
  Info.pArgDefList  = yyvsp[-4].pContext;
  Info.nArgType     = yyvsp[-1].nValue;

  yyval.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
#line 1741 "../../src/black_box_y.c"
    break;

  case 15:
#line 239 "black_box_y.y"
{
  yyval.pContext = yyvsp[-1].pContext;

  yyBlackBoxReentrancyCount--;
}
#line 1751 "../../src/black_box_y.c"
    break;

  case 16:
#line 248 "black_box_y.y"
{
  yyval.nValue = 0;
}
#line 1759 "../../src/black_box_y.c"
    break;

  case 17:
#line 252 "black_box_y.y"
{
  yyval.nValue = 1;
}
#line 1767 "../../src/black_box_y.c"
    break;

  case 18:
#line 256 "black_box_y.y"
{
  yyval.nValue = 2;
}
#line 1775 "../../src/black_box_y.c"
    break;

  case 19:
#line 260 "black_box_y.y"
{
  yyval.nValue = 3;
}
#line 1783 "../../src/black_box_y.c"
    break;

  case 20:
#line 264 "black_box_y.y"
{
  yyval.nValue = 4;
}
#line 1791 "../../src/black_box_y.c"
    break;

  case 21:
#line 268 "black_box_y.y"
{
  yyval.nValue = 5;
}
#line 1799 "../../src/black_box_y.c"
    break;

  case 22:
#line 272 "black_box_y.y"
{
  yyval.nValue = 6;
}
#line 1807 "../../src/black_box_y.c"
    break;

  case 23:
#line 276 "black_box_y.y"
{
  yyval.nValue = 7;
}
#line 1815 "../../src/black_box_y.c"
    break;

  case 24:
#line 280 "black_box_y.y"
{
  yyval.nValue = 8;
}
#line 1823 "../../src/black_box_y.c"
    break;

  case 25:
#line 284 "black_box_y.y"
{
  yyval.nValue = 9;
}
#line 1831 "../../src/black_box_y.c"
    break;

  case 26:
#line 291 "black_box_y.y"
{
  yyval.nValue = 1;
}
#line 1839 "../../src/black_box_y.c"
    break;

  case 27:
#line 295 "black_box_y.y"
{
  yyval.nValue = 2;
}
#line 1847 "../../src/black_box_y.c"
    break;

  case 28:
#line 299 "black_box_y.y"
{
  yyval.nValue = 0;
}
#line 1855 "../../src/black_box_y.c"
    break;

  case 29:
#line 303 "black_box_y.y"
{
  yyval.nValue = 0;
}
#line 1863 "../../src/black_box_y.c"
    break;

  case 30:
#line 310 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxArgDef_create(yyvsp[-3].sValue, yyvsp[-1].nValue, yyvsp[0].nValue);
}
#line 1871 "../../src/black_box_y.c"
    break;

  case 31:
#line 314 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxArgDef_create(yyvsp[-3].sValue, yyvsp[0].nValue, yyvsp[-1].nValue);
}
#line 1879 "../../src/black_box_y.c"
    break;

  case 32:
#line 318 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxArgDef_create("result", yyvsp[0].nValue, 2);
}
#line 1887 "../../src/black_box_y.c"
    break;

  case 33:
#line 325 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxArgDefList_create(yyvsp[0].pContext);
}
#line 1895 "../../src/black_box_y.c"
    break;

  case 34:
#line 329 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 1903 "../../src/black_box_y.c"
    break;

  case 35:
#line 336 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxDerivative_create(yyvsp[-4].sValue, yyvsp[0].pContext, 0, 0, 1, 0, 0);
}
#line 1911 "../../src/black_box_y.c"
    break;

  case 36:
#line 343 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpecList_create(yyvsp[0].pContext);
}
#line 1919 "../../src/black_box_y.c"
    break;

  case 37:
#line 347 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 1927 "../../src/black_box_y.c"
    break;

  case 38:
#line 354 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpec_create(yyvsp[-1].pContext, 0);
}
#line 1935 "../../src/black_box_y.c"
    break;

  case 39:
#line 358 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpec_create(yyvsp[-1].pContext, 1);
}
#line 1943 "../../src/black_box_y.c"
    break;

  case 40:
#line 362 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpec_create(yyvsp[-1].pContext, 2);
}
#line 1951 "../../src/black_box_y.c"
    break;

  case 41:
#line 366 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpec_create(yyvsp[-1].pContext, 3);
}
#line 1959 "../../src/black_box_y.c"
    break;

  case 42:
#line 370 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxSpec_create(yyvsp[-1].pContext, 4);
}
#line 1967 "../../src/black_box_y.c"
    break;

  case 43:
#line 377 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxIdent_create(-1);
}
#line 1975 "../../src/black_box_y.c"
    break;

  case 44:
#line 381 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxIdent_create(yyvsp[0].nValue);
}
#line 1983 "../../src/black_box_y.c"
    break;

  case 45:
#line 388 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxIdentList_create(yyvsp[0].pContext);
}
#line 1991 "../../src/black_box_y.c"
    break;

  case 46:
#line 392 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 1999 "../../src/black_box_y.c"
    break;

  case 47:
#line 399 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxDerivativeList_create(yyvsp[0].pContext);
}
#line 2007 "../../src/black_box_y.c"
    break;

  case 48:
#line 403 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2015 "../../src/black_box_y.c"
    break;

  case 49:
#line 410 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprAdditive_create(0, yyvsp[0].pContext, 0);
}
#line 2023 "../../src/black_box_y.c"
    break;

  case 50:
#line 414 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprAdditive_create(yyvsp[-2].pContext, yyvsp[0].pContext, 1);
}
#line 2031 "../../src/black_box_y.c"
    break;

  case 51:
#line 418 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprAdditive_create(yyvsp[-2].pContext, yyvsp[0].pContext, 0);
}
#line 2039 "../../src/black_box_y.c"
    break;

  case 52:
#line 425 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprMultiplicative_create(0, yyvsp[0].pContext, 0);
}
#line 2047 "../../src/black_box_y.c"
    break;

  case 53:
#line 429 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprMultiplicative_create(yyvsp[-2].pContext, yyvsp[0].pContext, 1);
}
#line 2055 "../../src/black_box_y.c"
    break;

  case 54:
#line 433 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprMultiplicative_create(yyvsp[-2].pContext, yyvsp[0].pContext, 0);
}
#line 2063 "../../src/black_box_y.c"
    break;

  case 55:
#line 440 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPower_create(0, yyvsp[0].pContext);
}
#line 2071 "../../src/black_box_y.c"
    break;

  case 56:
#line 444 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPower_create(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2079 "../../src/black_box_y.c"
    break;

  case 57:
#line 451 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprUnary_create(yyvsp[0].pContext, 0, 0);
}
#line 2087 "../../src/black_box_y.c"
    break;

  case 58:
#line 455 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprUnary_create(yyvsp[0].pContext, 1, 1);
}
#line 2095 "../../src/black_box_y.c"
    break;

  case 59:
#line 459 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprUnary_create(yyvsp[0].pContext, 1, 0);
}
#line 2103 "../../src/black_box_y.c"
    break;

  case 60:
#line 466 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPostfix_create(0, yyvsp[0].nValue, 0, 0, 0, 0);
}
#line 2111 "../../src/black_box_y.c"
    break;

  case 61:
#line 470 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPostfix_create(1, 0, yyvsp[0].dValue, 0, 0, 0);
}
#line 2119 "../../src/black_box_y.c"
    break;

  case 62:
#line 474 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPostfix_create(2, 0, 0, yyvsp[0].sValue, 0, 0);
}
#line 2127 "../../src/black_box_y.c"
    break;

  case 63:
#line 478 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPostfix_create(3, 0, 0, yyvsp[-3].sValue, yyvsp[-1].pContext, 0);
}
#line 2135 "../../src/black_box_y.c"
    break;

  case 64:
#line 482 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxExprPostfix_create(4, 0, 0, 0, 0, yyvsp[-1].pContext);
}
#line 2143 "../../src/black_box_y.c"
    break;

  case 65:
#line 489 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxArgList_create(yyvsp[0].pContext);
}
#line 2151 "../../src/black_box_y.c"
    break;

  case 66:
#line 493 "black_box_y.y"
{
  yyval.pContext = adtBlackBoxList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2159 "../../src/black_box_y.c"
    break;


#line 2163 "../../src/black_box_y.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
