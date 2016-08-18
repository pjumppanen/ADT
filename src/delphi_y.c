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
#line 1 "delphi_y.y" /* yacc.c:339  */

/*
 * delphi.y
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
 * delphi grammar in Yacc format, based on BNF given
 * in "BORLAND Delphi 6.0 Object Pascal Language Guide -- Appendix A".
 *
 */

#include <stdio.h>
#include "lexer.h"
#include "adtdelphi.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   delphiType


#line 101 "../../src/delphi_y.c" /* yacc.c:339  */

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
    ABSOLUTE = 258,
    AND = 259,
    ANSISTRING = 260,
    ARRAY = 261,
    AS = 262,
    B_BEGIN = 263,
    BOOLEAN = 264,
    BYTE = 265,
    CASE = 266,
    CDECL = 267,
    CHAR = 268,
    CLASS = 269,
    COMP = 270,
    CONST = 271,
    CONSTRUCTOR = 272,
    CONTAINS = 273,
    CURRENCY = 274,
    DEFAULT = 275,
    DESTRUCTOR = 276,
    DIV = 277,
    DO = 278,
    DOUBLE = 279,
    DOWNTO = 280,
    DYNAMIC = 281,
    ELSE = 282,
    B_END = 283,
    EXPORT = 284,
    EXTENDED = 285,
    EXTERNAL = 286,
    FAR = 287,
    P_FILE = 288,
    FINALIZATION = 289,
    FOR = 290,
    FORWARD = 291,
    FUNCTION = 292,
    GOTO = 293,
    IF = 294,
    IMPLEMENTATION = 295,
    IMPLEMENTS = 296,
    IN = 297,
    INDEX = 298,
    INHERITED = 299,
    INITIALIZATION = 300,
    INT64 = 301,
    INTEGER = 302,
    INTERFACE = 303,
    IS = 304,
    LABEL = 305,
    LIBRARY = 306,
    LONGINT = 307,
    LONGWORD = 308,
    MESSAGE = 309,
    MOD = 310,
    NIL = 311,
    NODEFAULT = 312,
    NOT = 313,
    OBJECT = 314,
    OF = 315,
    OLEVARIANT = 316,
    OR = 317,
    OUT = 318,
    OVERLOAD = 319,
    OVERRIDE = 320,
    PACKAGE = 321,
    PACKED = 322,
    PASCAL = 323,
    PCHAR = 324,
    PRIVATE = 325,
    PROCEDURE = 326,
    PROGRAM = 327,
    PROPERTY = 328,
    PROTECTED = 329,
    PUBLIC = 330,
    PUBLISHED = 331,
    READ = 332,
    REAL = 333,
    REAL48 = 334,
    RECORD = 335,
    REGISTER = 336,
    REINTRODUCE = 337,
    REPEAT = 338,
    REQUIRES = 339,
    SAFECALL = 340,
    SET = 341,
    SHL = 342,
    SHORTINT = 343,
    SHR = 344,
    SINGLE = 345,
    SIZEOF = 346,
    SMALLINT = 347,
    STDCALL = 348,
    STORED = 349,
    STRING = 350,
    THEN = 351,
    TO = 352,
    TYPE = 353,
    UNIT = 354,
    UNTIL = 355,
    USES = 356,
    VAR = 357,
    VARIANT = 358,
    VIRTUAL = 359,
    WHILE = 360,
    WIDECHAR = 361,
    WIDESTRING = 362,
    WITH = 363,
    WORD = 364,
    WRITE = 365,
    XOR = 366,
    EXIT = 367,
    POINTER = 368,
    COMMA = 369,
    SEMICOLON = 370,
    COLON = 371,
    ASSIGNMENT = 372,
    PLUS_EQUALS = 373,
    MINUS_EQUALS = 374,
    TIMES_EQUALS = 375,
    DIV_EQUALS = 376,
    EQUALS = 377,
    DOT = 378,
    RANGE = 379,
    LPARENTHESIS = 380,
    RPARENTHESIS = 381,
    LBRACKET = 382,
    RBRACKET = 383,
    AT = 384,
    HAT = 385,
    PLUS = 386,
    MINUS = 387,
    GT = 388,
    LT = 389,
    GE = 390,
    LE = 391,
    NE = 392,
    MULTIPLY = 393,
    DIVIDE = 394,
    IDENTIFIER = 395,
    BOOL_NUMBER = 396,
    INT_NUMBER = 397,
    REAL_NUMBER = 398,
    TEXT = 399,
    SINGLELINE_COMMENT = 400,
    MULTILINE_COMMENT = 401,
    EMBEDDED_COMMANDS = 402,
    ADDVARIABLES = 403
  };
#endif
/* Tokens.  */
#define ABSOLUTE 258
#define AND 259
#define ANSISTRING 260
#define ARRAY 261
#define AS 262
#define B_BEGIN 263
#define BOOLEAN 264
#define BYTE 265
#define CASE 266
#define CDECL 267
#define CHAR 268
#define CLASS 269
#define COMP 270
#define CONST 271
#define CONSTRUCTOR 272
#define CONTAINS 273
#define CURRENCY 274
#define DEFAULT 275
#define DESTRUCTOR 276
#define DIV 277
#define DO 278
#define DOUBLE 279
#define DOWNTO 280
#define DYNAMIC 281
#define ELSE 282
#define B_END 283
#define EXPORT 284
#define EXTENDED 285
#define EXTERNAL 286
#define FAR 287
#define P_FILE 288
#define FINALIZATION 289
#define FOR 290
#define FORWARD 291
#define FUNCTION 292
#define GOTO 293
#define IF 294
#define IMPLEMENTATION 295
#define IMPLEMENTS 296
#define IN 297
#define INDEX 298
#define INHERITED 299
#define INITIALIZATION 300
#define INT64 301
#define INTEGER 302
#define INTERFACE 303
#define IS 304
#define LABEL 305
#define LIBRARY 306
#define LONGINT 307
#define LONGWORD 308
#define MESSAGE 309
#define MOD 310
#define NIL 311
#define NODEFAULT 312
#define NOT 313
#define OBJECT 314
#define OF 315
#define OLEVARIANT 316
#define OR 317
#define OUT 318
#define OVERLOAD 319
#define OVERRIDE 320
#define PACKAGE 321
#define PACKED 322
#define PASCAL 323
#define PCHAR 324
#define PRIVATE 325
#define PROCEDURE 326
#define PROGRAM 327
#define PROPERTY 328
#define PROTECTED 329
#define PUBLIC 330
#define PUBLISHED 331
#define READ 332
#define REAL 333
#define REAL48 334
#define RECORD 335
#define REGISTER 336
#define REINTRODUCE 337
#define REPEAT 338
#define REQUIRES 339
#define SAFECALL 340
#define SET 341
#define SHL 342
#define SHORTINT 343
#define SHR 344
#define SINGLE 345
#define SIZEOF 346
#define SMALLINT 347
#define STDCALL 348
#define STORED 349
#define STRING 350
#define THEN 351
#define TO 352
#define TYPE 353
#define UNIT 354
#define UNTIL 355
#define USES 356
#define VAR 357
#define VARIANT 358
#define VIRTUAL 359
#define WHILE 360
#define WIDECHAR 361
#define WIDESTRING 362
#define WITH 363
#define WORD 364
#define WRITE 365
#define XOR 366
#define EXIT 367
#define POINTER 368
#define COMMA 369
#define SEMICOLON 370
#define COLON 371
#define ASSIGNMENT 372
#define PLUS_EQUALS 373
#define MINUS_EQUALS 374
#define TIMES_EQUALS 375
#define DIV_EQUALS 376
#define EQUALS 377
#define DOT 378
#define RANGE 379
#define LPARENTHESIS 380
#define RPARENTHESIS 381
#define LBRACKET 382
#define RBRACKET 383
#define AT 384
#define HAT 385
#define PLUS 386
#define MINUS 387
#define GT 388
#define LT 389
#define GE 390
#define LE 391
#define NE 392
#define MULTIPLY 393
#define DIVIDE 394
#define IDENTIFIER 395
#define BOOL_NUMBER 396
#define INT_NUMBER 397
#define REAL_NUMBER 398
#define TEXT 399
#define SINGLELINE_COMMENT 400
#define MULTILINE_COMMENT 401
#define EMBEDDED_COMMANDS 402
#define ADDVARIABLES 403

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

#line 448 "../../src/delphi_y.c" /* yacc.c:358  */

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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3967

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  149
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  132
/* YYNRULES -- Number of rules.  */
#define YYNRULES  486
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  947

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   403

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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    78,    87,    96,   105,   115,   119,   123,
     127,   131,   135,   139,   143,   149,   153,   157,   163,   169,
     173,   177,   181,   187,   193,   198,   203,   207,   212,   217,
     221,   227,   231,   235,   239,   245,   250,   255,   261,   267,
     272,   277,   281,   287,   293,   298,   303,   307,   313,   317,
     321,   327,   332,   337,   341,   347,   355,   361,   369,   373,
     377,   383,   389,   393,   399,   405,   409,   415,   421,   425,
     429,   433,   437,   441,   445,   449,   453,   459,   463,   467,
     473,   477,   483,   487,   493,   497,   501,   505,   509,   513,
     517,   523,   527,   531,   537,   541,   545,   549,   553,   557,
     561,   565,   569,   573,   577,   581,   585,   591,   595,   601,
     607,   613,   617,   623,   627,   633,   637,   641,   645,   651,
     655,   659,   663,   667,   671,   675,   679,   685,   689,   695,
     699,   705,   709,   713,   717,   721,   727,   731,   737,   743,
     747,   753,   757,   761,   765,   771,   775,   779,   783,   787,
     793,   797,   803,   809,   813,   819,   823,   829,   833,   837,
     841,   847,   852,   857,   861,   867,   871,   875,   879,   883,
     889,   895,   899,   903,   907,   911,   915,   919,   923,   927,
     931,   937,   943,   947,   951,   955,   959,   963,   967,   971,
     975,   979,   983,   987,   991,   995,   999,  1005,  1011,  1015,
    1019,  1023,  1027,  1031,  1035,  1039,  1052,  1056,  1060,  1064,
    1068,  1072,  1076,  1080,  1084,  1088,  1094,  1098,  1104,  1110,
    1114,  1120,  1124,  1128,  1132,  1136,  1140,  1144,  1148,  1152,
    1156,  1160,  1164,  1170,  1174,  1180,  1184,  1190,  1194,  1200,
    1204,  1210,  1214,  1220,  1224,  1230,  1234,  1238,  1242,  1246,
    1250,  1254,  1258,  1262,  1266,  1270,  1274,  1278,  1282,  1286,
    1290,  1294,  1298,  1302,  1308,  1312,  1318,  1322,  1327,  1331,
    1335,  1339,  1343,  1347,  1351,  1355,  1359,  1363,  1367,  1371,
    1375,  1379,  1383,  1387,  1393,  1397,  1401,  1405,  1411,  1415,
    1421,  1425,  1431,  1435,  1439,  1445,  1449,  1455,  1461,  1465,
    1471,  1475,  1481,  1485,  1491,  1497,  1501,  1505,  1509,  1515,
    1521,  1526,  1531,  1535,  1541,  1545,  1549,  1553,  1557,  1561,
    1565,  1569,  1575,  1579,  1583,  1587,  1591,  1595,  1599,  1603,
    1607,  1611,  1615,  1619,  1625,  1629,  1633,  1637,  1643,  1647,
    1653,  1657,  1663,  1667,  1671,  1675,  1681,  1685,  1689,  1693,
    1697,  1701,  1705,  1709,  1713,  1717,  1721,  1725,  1729,  1735,
    1739,  1743,  1747,  1751,  1755,  1759,  1763,  1767,  1771,  1775,
    1779,  1783,  1787,  1791,  1797,  1801,  1807,  1811,  1815,  1819,
    1823,  1827,  1831,  1835,  1839,  1843,  1847,  1851,  1857,  1861,
    1867,  1871,  1875,  1879,  1883,  1887,  1891,  1895,  1901,  1905,
    1909,  1913,  1919,  1923,  1927,  1931,  1937,  1941,  1947,  1953,
    1957,  1961,  1965,  1971,  1975,  1979,  1983,  1987,  1991,  1995,
    1999,  2003,  2007,  2011,  2015,  2019,  2023,  2027,  2031,  2037,
    2041,  2047,  2051,  2055,  2059,  2063,  2069,  2073,  2079,  2083,
    2087,  2091,  2095,  2101,  2105,  2111,  2115,  2119,  2123,  2127,
    2133,  2137,  2141,  2147,  2151,  2157,  2161,  2171,  2175,  2179,
    2183,  2187,  2191,  2195,  2199,  2204,  2209,  2213,  2217,  2221,
    2225,  2229,  2233,  2237,  2243,  2247,  2259,  2263,  2267,  2273,
    2279,  2285,  2291,  2297,  2301,  2305,  2311
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ABSOLUTE", "AND", "ANSISTRING", "ARRAY",
  "AS", "B_BEGIN", "BOOLEAN", "BYTE", "CASE", "CDECL", "CHAR", "CLASS",
  "COMP", "CONST", "CONSTRUCTOR", "CONTAINS", "CURRENCY", "DEFAULT",
  "DESTRUCTOR", "DIV", "DO", "DOUBLE", "DOWNTO", "DYNAMIC", "ELSE",
  "B_END", "EXPORT", "EXTENDED", "EXTERNAL", "FAR", "P_FILE",
  "FINALIZATION", "FOR", "FORWARD", "FUNCTION", "GOTO", "IF",
  "IMPLEMENTATION", "IMPLEMENTS", "IN", "INDEX", "INHERITED",
  "INITIALIZATION", "INT64", "INTEGER", "INTERFACE", "IS", "LABEL",
  "LIBRARY", "LONGINT", "LONGWORD", "MESSAGE", "MOD", "NIL", "NODEFAULT",
  "NOT", "OBJECT", "OF", "OLEVARIANT", "OR", "OUT", "OVERLOAD", "OVERRIDE",
  "PACKAGE", "PACKED", "PASCAL", "PCHAR", "PRIVATE", "PROCEDURE",
  "PROGRAM", "PROPERTY", "PROTECTED", "PUBLIC", "PUBLISHED", "READ",
  "REAL", "REAL48", "RECORD", "REGISTER", "REINTRODUCE", "REPEAT",
  "REQUIRES", "SAFECALL", "SET", "SHL", "SHORTINT", "SHR", "SINGLE",
  "SIZEOF", "SMALLINT", "STDCALL", "STORED", "STRING", "THEN", "TO",
  "TYPE", "UNIT", "UNTIL", "USES", "VAR", "VARIANT", "VIRTUAL", "WHILE",
  "WIDECHAR", "WIDESTRING", "WITH", "WORD", "WRITE", "XOR", "EXIT",
  "POINTER", "COMMA", "SEMICOLON", "COLON", "ASSIGNMENT", "PLUS_EQUALS",
  "MINUS_EQUALS", "TIMES_EQUALS", "DIV_EQUALS", "EQUALS", "DOT", "RANGE",
  "LPARENTHESIS", "RPARENTHESIS", "LBRACKET", "RBRACKET", "AT", "HAT",
  "PLUS", "MINUS", "GT", "LT", "GE", "LE", "NE", "MULTIPLY", "DIVIDE",
  "IDENTIFIER", "BOOL_NUMBER", "INT_NUMBER", "REAL_NUMBER", "TEXT",
  "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "EMBEDDED_COMMANDS",
  "ADDVARIABLES", "$accept", "Goal", "Macro", "Program", "Unit", "Package",
  "Library", "UsesClause", "InterfaceSection", "ExportedHeadingList",
  "ExportedHeading", "ImplementationSection", "Block", "DeclSection",
  "LabelDeclSection", "LabelDeclList", "LabelDecl", "ConstSection",
  "ConstantDeclList", "ConstantDecl", "TypeSection", "TypeDeclList",
  "TypeDeclBegin", "TypeDecl", "TypedConstant", "ArrayConstant",
  "TypedConstantList", "RecordConstant", "RecordFieldConstantList",
  "RecordFieldConstant", "Type", "RestrictedType", "ClassRefType",
  "SimpleType", "RealType", "OrdinalType", "OrdIdent", "VariantType",
  "SubrangeType", "EnumeratedType", "EnumeratedTypeElementList",
  "EnumeratedTypeElement", "StringType", "StructType", "ArrayType",
  "OrdinalTypeList", "RecType", "FieldDeclList", "FieldDecl",
  "VariantSectionList", "VariantSection", "RecVariant", "ConstExprList",
  "SetType", "FileType", "PointerType", "ProcedureType", "VarSection",
  "VarDeclList", "VarDecl", "Expression", "ExpressionRelOpList",
  "SimpleExpression", "SimpleExpressionAddOpList", "Term",
  "FactorMulOpList", "Factor", "CastExpression", "Designator",
  "DesignatorObjList", "DesignatorObj", "DesignatorRefList",
  "DesignatorRef", "SetConstructor", "SetElementList", "SetElement",
  "ExprList", "Statement", "StmtList", "ExitStatement", "SimpleStatement",
  "SizeofType", "CompoundStmt", "IfStmt", "CaseStmt", "CaseSelectorList",
  "CaseSelector", "CaseLabelList", "CaseLabel", "RepeatStmt", "WhileStmt",
  "ForStmt", "WithStmt", "ProcedureDeclSection", "ProcedureDeclList",
  "ProcedureDecl", "FunctionHeading", "ProcedureHeading",
  "FormalParameters", "FormalParamList", "FormalParam", "Parameter",
  "Directive", "DirectiveList", "ObjectType", "MethodList", "Method",
  "ConstructorHeading", "DestructorHeading", "ObjFieldList", "ObjField",
  "InitSection", "ClassType", "ClassFieldList", "ClassField",
  "ClassMethodList", "ClassMethod", "ClassPropertyList", "ClassProperty",
  "Property", "PropertyParameterList", "PropertyParameter",
  "PropertySpecifiers", "InterfaceType", "IdentList", "ConstExpr",
  "TypeId", "UnitId", "Ident", "LabelId", "Number", "String", YY_NULLPTR
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403
};
# endif

#define YYPACT_NINF -823

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-823)))

#define YYTABLE_NINF -483

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     454,   -71,   -71,   -71,   -71,   -71,  -823,   131,  -823,  -823,
    -823,  -823,  -823,    90,    26,    56,   101,   -39,   144,   227,
    -823,  -823,    50,   145,   276,   274,    90,  -823,  1889,   208,
     211,   208,   -71,   268,   -71,  -823,  -823,   210,  -823,  3090,
    -823,   192,   250,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   -71,  -823,  -823,  -823,  -823,  -823,  2393,  -823,  -823,
    -823,  -823,  -823,   240,  -823,  -823,  -823,  -823,  1889,  1593,
     -11,  2393,  2393,  -823,  -823,  -823,  -823,   243,   267,  -823,
     494,  -823,   283,  -823,    75,  -823,  -823,  -823,   266,  -823,
    -823,   197,   321,  -823,  -823,    90,   -71,   272,   -71,    90,
     198,   208,   359,  -823,  -823,  1889,  -823,   303,    50,  1889,
     -71,  3620,   291,  1889,   -11,   336,   354,  1168,  1181,   368,
    3196,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     386,   390,   192,  -823,   411,   408,   -71,   432,   352,  -823,
    3827,   412,  -823,   413,   -62,  -823,  -823,  -823,  -823,  1889,
    1889,  1889,  1889,  1889,  1889,  1889,  1889,  1889,  1889,  1889,
    1913,  2049,  2073,  2209,  2393,  2393,  2393,  2393,  2393,  2393,
    2393,   -11,  1889,  1484,  1729,  1889,  -823,   220,  -823,   427,
     381,  -823,   403,   439,   453,   274,   208,   118,   512,   457,
     458,   471,  -823,   495,    22,  3302,  3827,   569,   577,   480,
    2233,  1889,  1889,  1889,  1889,  2369,  1889,  1889,  1889,  1889,
    -823,  -823,   496,  3726,  -823,   303,   287,   -71,  1119,  -823,
     490,   -71,   385,  1753,   220,  -823,  -823,  -823,  -823,  -823,
    -823,   488,  -823,  1889,  1889,  -823,   491,   507,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  2393,  2393,  -823,
    2393,  2393,  -823,  2393,  2393,  -823,  2393,  2393,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   516,   505,
    1168,  1181,  1000,   220,   200,    95,  -823,  -823,   593,   235,
    -823,   208,   250,    90,  3620,  -823,  3620,   514,   287,   -71,
    1889,  3620,  1889,  1889,   517,  3620,  3620,  -823,   -71,  -823,
    -823,  -823,  -823,  -823,   -71,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
     519,   523,  -823,  -823,  -823,   531,  -823,  -823,   -14,  1407,
     590,   -71,   931,   528,   221,   -71,    15,   594,   544,  -823,
     -71,   521,   457,   558,   565,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,   621,   622,  -823,  -823,  -823,   559,  -823,   564,  -823,
     -71,  -823,    72,   -71,   -71,  -823,   385,  -823,   575,   579,
     580,   584,   220,   201,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  3827,  -823,   552,
     -71,   220,   220,  -823,   578,   -71,   583,    90,   432,  -823,
    3408,  2876,  -823,   133,  -823,   110,  -823,   585,   587,    37,
     675,  -823,  -823,  -823,  -823,  -823,   -71,   219,  -823,  1260,
    1049,  -823,   521,    28,   -71,    28,    28,    28,   -71,   592,
     607,  -823,   609,   614,  -823,   617,  -823,   899,  -823,   618,
    -823,  -823,   282,   521,   119,  -823,   530,   530,   530,   530,
     -71,  1166,   620,  -823,   303,   581,  -823,   624,  -823,  -823,
    -823,  -823,  -823,   317,  -823,    44,  -823,   338,  1049,   287,
     264,  -823,   586,  -823,   613,  -823,  -823,   678,   683,   287,
     603,  -823,  1260,   340,   353,  -823,  3081,  3081,  3081,  3081,
     220,   220,   625,   -71,   -40,   220,  -823,   407,  -823,   631,
      24,  -823,  -823,  3620,  3620,  -823,  -823,   287,  3620,   287,
    1889,  1889,  1889,  3620,   634,   417,   647,  -823,  -823,  -823,
     703,  -823,  -823,   166,  -823,   643,  -823,  -823,  -823,  1020,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,   277,
    3818,  3818,  3818,  3818,   789,  -823,  -823,   654,   725,  1260,
    -823,   649,  2537,   -71,    41,   658,   306,  -823,   663,   923,
     659,   655,  -823,  -823,   285,   -71,  -823,   645,  -823,    25,
     105,  -823,  1260,  -823,   660,   -71,  -823,   287,   603,  -823,
    -823,  -823,  -823,  -823,    60,   -71,  -823,   -71,  -823,  -823,
    -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,   668,  -823,   674,   679,   682,   687,
     690,   694,   697,   220,  -823,    79,  -823,   762,  -823,    24,
    -823,   700,   701,  3514,  2982,  -823,  -823,  -823,    42,   797,
     798,  -823,   219,  -823,   313,   -68,  -823,   713,  -823,  1049,
     771,   603,   287,   521,   287,  -823,   -71,   -71,   -71,   -71,
     -71,  -823,  1389,   719,   720,   721,   724,  -823,  -823,  2630,
     728,   952,  -823,   772,   772,   772,   772,  -823,  -823,   603,
    -823,  -823,  -823,   -23,   -71,   -71,   -71,  -823,    80,  -823,
    -823,   419,  2646,  2647,   975,  -823,   -71,   376,  -823,   598,
    -823,   723,   163,   786,   743,   756,  -823,  -823,  -823,   846,
    -823,  -823,  -823,  -823,  -823,  -823,   534,  -823,   534,   723,
     723,  -823,  3081,  -823,  3081,  -823,  3081,  -823,  3081,  -823,
     753,  -823,  3818,  3818,  -823,  -823,   849,  1889,  1889,  3620,
    3620,   764,   219,  -823,   -71,  -823,   219,  -823,  1260,  -823,
    -823,  -823,   758,  -823,  -823,  -823,  -823,   714,   190,  -823,
     430,  -823,   768,  2657,   770,  3818,  3818,  3818,  3818,  -823,
     775,  1178,  -823,  -823,  2730,   778,  -823,  -823,  -823,    43,
    -823,  1362,  -823,  -823,  -823,  -823,  2777,   780,  -823,   760,
    -823,   759,   792,  -823,  -823,   287,   603,   521,  -823,   793,
     794,   795,   796,  -823,  -823,   800,  -823,   803,   804,   806,
    -823,   807,   813,  -823,   864,   890,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,   603,  -823,   -71,   814,   521,  1638,  -823,
     816,  1207,  1244,  -823,  -823,  -823,  -823,  2754,  -823,   874,
    -823,  -823,   815,   817,  -823,   820,  1283,   438,  -823,   511,
     827,   473,  -823,   893,   894,   834,  -823,  -823,  -823,  -823,
    -823,  -823,  -823,  -823,  3818,  3818,  3620,  3620,  -823,  -823,
     -71,  -823,   835,  -823,  2904,   845,  1323,  -823,  -823,  -823,
    -823,  -823,  2529,   287,   -71,  1346,  -823,  -823,   790,   847,
    -823,   852,  -823,   287,   836,   287,   287,   603,  -823,  -823,
     714,   603,  -823,   856,  1363,  -823,  -823,  -823,   859,   860,
    -823,  -823,  -823,  -823,   627,  -823,  -823,    -5,   861,   863,
     934,  -823,  -823,  1373,  -823,   287,   -71,  -823,   854,  -823,
      78,  -823,  -823,   287,  -823,  -823,  -823,  -823,   177,  -823,
      81,   880,  -823,   886,  -823,  -823,  -823
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      25,     0,     0,     0,     0,     0,   481,     0,     6,     2,
       5,     3,     4,    40,     0,     0,     0,     0,     0,     0,
     475,     1,     0,     0,     0,    45,    39,    42,     0,    25,
       0,    25,     0,    28,     0,    24,   482,     0,    17,     0,
      37,     0,    52,    41,   101,    97,   102,    90,    89,    87,
      88,     0,    99,    96,    98,   104,   210,     0,   105,    85,
      84,    94,    86,     0,    95,   103,   100,   106,     0,     0,
       0,     0,     0,   483,   484,   485,   486,     0,     0,   244,
     170,   180,   181,   196,   197,   205,   215,   206,   218,   220,
     213,     0,   226,   208,   209,    40,     0,     0,     0,    40,
       0,    25,    36,   474,    43,     0,   289,     0,     0,     0,
     276,     0,     0,     0,     0,   266,   481,     0,   268,     0,
       0,   245,   246,   247,   248,   249,   250,   251,   252,   253,
       0,   479,    44,    47,     0,     0,     0,   162,   232,   212,
       0,     0,   238,   242,     0,   240,   207,   194,   195,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,   223,   234,     0,
       0,    19,     0,     0,     0,    45,    25,     0,     0,   481,
       0,     0,   277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     265,   288,     0,   254,    46,     0,     0,    51,     0,    54,
       0,     0,   311,     0,   229,   108,   107,   285,   284,   286,
     287,     0,   211,     0,     0,   237,     0,     0,   178,   176,
     177,   179,   171,   172,   174,   173,   175,     0,     0,   192,
       0,     0,   193,     0,     0,   190,     0,     0,   191,   202,
     200,   201,   203,   204,   198,   199,   219,   243,     0,     7,
     215,   206,     9,   225,     0,     0,   233,    23,     0,     0,
      16,    25,    52,    40,     0,   412,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   267,   283,   282,
     278,   279,   280,   281,   274,   273,   269,   270,   271,   272,
     264,   255,   256,   257,   258,   259,   260,   261,   262,   263,
       0,     0,   477,   476,   478,     0,    53,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   117,
       0,     0,   479,     0,     0,    76,    70,    83,    82,    93,
      75,    91,    92,    73,    71,   123,   126,   124,   125,    72,
      74,   160,   158,    77,    78,    79,     0,    68,     0,    55,
     161,   164,     0,     0,     0,    38,   310,   313,     0,     0,
       0,     0,   231,     0,   214,   241,   239,   217,   216,   184,
     188,   185,   189,   182,   186,   183,   187,     0,     8,    10,
       0,   222,   224,   235,     0,     0,     0,    40,   162,    35,
       0,     0,    18,     0,   296,     0,   299,   301,     0,     0,
     290,   302,   303,   275,   304,   309,     0,     0,    48,     0,
       0,   413,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   438,     0,     0,   431,     0,   430,     0,   437,     0,
     444,   445,     0,     0,     0,   466,     0,     0,     0,     0,
       0,     0,     0,   376,     0,     0,   389,     0,   407,   119,
     122,   120,   121,   337,   135,     0,   137,     0,     0,     0,
       0,   112,   114,   155,     0,    56,    57,     0,     0,     0,
       0,   163,     0,   401,   405,   312,    40,    40,    40,    40,
     228,   230,     0,     0,    11,   221,    20,     0,    21,     0,
      27,   411,   409,     0,     0,   292,   295,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    58,
       0,   128,   130,     0,    80,     0,   441,   434,   448,   465,
     440,   433,   447,   439,   432,   446,   442,   435,   449,     0,
     393,   391,   395,   397,     0,   415,   436,     0,     0,     0,
     153,     0,     0,     0,     0,     0,     0,   467,     0,     0,
       0,     0,   377,   388,     0,     0,   335,     0,   131,     0,
       0,   140,     0,   152,     0,     0,   110,     0,     0,   159,
     157,   109,   479,    69,     0,     0,   399,     0,   403,   359,
     361,   363,   364,   365,   366,   367,   369,   368,   370,   360,
     371,   372,   373,   362,     0,   375,     0,     0,     0,     0,
       0,     0,     0,   227,   214,    13,    12,     0,    15,    26,
      30,     0,     0,     0,     0,   298,   297,   300,     0,     0,
       0,   291,     0,    63,     0,     0,    66,     0,    49,     0,
       0,     0,     0,     0,     0,   462,     0,     0,     0,     0,
       0,   452,     0,     0,     0,     0,     0,   417,   429,     0,
       0,     0,   414,     0,     0,     0,     0,   443,   408,     0,
     333,   325,   329,     0,     0,     0,     0,   339,     0,   341,
     345,   354,     0,     0,     0,   468,     0,     0,   378,     0,
     406,   336,   479,     0,     0,     0,   132,   136,   133,     0,
     139,   138,   118,   111,   113,   156,     0,   169,     0,   400,
     404,   321,    40,   315,    40,   317,    40,   319,    40,    14,
       0,    29,    34,    33,   410,   293,     0,     0,     0,     0,
       0,     0,     0,    61,     0,    64,     0,   129,     0,    81,
     461,   463,     0,   457,   458,   460,   459,   465,     0,   454,
       0,   421,     0,     0,     0,   392,   390,   394,   396,   419,
       0,     0,   416,   154,     0,     0,   343,   344,   342,     0,
     338,     0,   331,   323,   327,   470,     0,     0,   469,     0,
     381,     0,     0,   379,   334,     0,     0,     0,   134,     0,
       0,     0,     0,   398,   402,     0,   374,     0,     0,     0,
      22,     0,     0,   294,     0,     0,   308,   306,    50,    62,
      65,    67,   127,     0,   451,     0,     0,     0,     0,   423,
       0,     0,     0,   418,   332,   324,   328,     0,   340,     0,
     353,   351,   347,   349,   471,     0,     0,     0,   383,     0,
       0,     0,   151,     0,     0,     0,   166,   165,   168,   167,
     320,   314,   316,   318,    32,    31,     0,     0,   464,   453,
       0,   455,     0,   425,     0,     0,     0,   422,   420,   330,
     322,   326,     0,     0,     0,     0,   472,   380,     0,     0,
     385,     0,   143,     0,     0,     0,     0,     0,   307,   305,
     465,     0,   427,     0,     0,   424,   352,   350,   346,   348,
     356,   358,   473,   382,     0,   387,   150,     0,     0,     0,
       0,   450,   456,     0,   426,     0,     0,   384,     0,   149,
       0,   144,   141,     0,   428,   355,   357,   386,     0,   145,
       0,     0,   146,     0,   147,   142,   148
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -823,  -823,  -823,  -823,  -823,  -823,  -823,    19,  -823,  -823,
     371,  -823,   -88,   731,  -823,  -823,   992,   838,  -823,   888,
     739,  -823,  -823,   812,  -501,  -823,  -823,  -823,  -823,   288,
    -409,  -823,  -823,  -544,   -69,  -401,  -109,  -115,  -823,  -823,
    -823,   446,  -823,  -823,   699,  -823,   702,   117,  -571,   107,
    -574,  -822,  -823,   708,   726,  -823,  -823,   646,  -346,  -351,
     783,  -823,   747,  -823,   693,  -823,    33,   -29,   -26,  -823,
     884,  -121,  -154,  -823,  -823,   823,    76,     1,   -95,   851,
     853,  -175,    12,   855,   857,  -823,   652,  -823,   555,   867,
     868,   869,   871,  -823,  -823,   698,  -158,  -138,  -221,  -823,
     307,  -178,    -7,  -374,  -823,  -539,  -225,  -196,  -184,  -675,
    -318,  -823,  -823,   423,  -545,  -276,  -433,  -305,  -101,   290,
    -823,   262,  -715,  -823,     7,   325,    -4,   -77,     0,    46,
    -823,  -823
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,   102,   629,
     630,   187,    23,    24,    25,    26,    27,    42,   132,   133,
     137,   217,   218,   219,   526,   527,   644,   528,   645,   646,
     343,   344,   345,   346,    77,   348,    78,   350,   351,   352,
     480,   481,   353,   354,   355,   533,   356,   475,   476,   580,
     581,   850,   851,   357,   358,   359,   360,   222,   370,   371,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   177,   178,    90,   144,   145,    91,   212,   120,   121,
     122,   231,   123,   124,   125,   413,   414,   415,   416,   126,
     127,   128,   129,   375,   376,   377,   439,   440,   565,   688,
     689,   690,   615,   616,   363,   465,   441,   442,   443,   467,
     444,   287,   364,   445,   446,   447,   448,   449,   450,   451,
     758,   759,   661,   365,   452,   366,   367,   368,    92,   130,
      93,    94
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    15,    16,    17,    18,    20,   710,   179,   707,   668,
     117,   183,    19,   118,   556,   468,   195,   224,   681,   491,
     531,   294,   792,   276,   643,   229,   380,   462,   556,   532,
     190,   228,    20,    51,   103,   699,    40,   134,   381,   100,
     119,   135,   824,   474,   146,   373,   429,   744,    95,   374,
      99,   138,   234,   706,   504,   577,   461,   684,   745,   684,
     361,   331,   521,   716,   378,   331,   235,   737,    37,     6,
     276,   227,   578,   918,   919,   626,    31,   583,   272,   164,
     362,   229,   117,   594,   379,   118,    32,   228,   198,   577,
     139,   117,   577,   774,   118,   335,    20,   165,    20,   335,
       6,   434,   564,   180,   685,   182,   685,   191,   466,   349,
     138,   941,   194,   430,   230,   537,   577,   541,   544,   547,
     185,   929,   292,   618,   620,   622,   284,   227,   134,     6,
     166,    21,   135,   708,   522,     6,   220,   210,   320,   738,
      22,   741,   557,   686,   270,   686,   285,   271,   783,   347,
     678,    28,   401,   491,   192,     6,   568,   625,   791,   579,
     514,   515,   167,   286,   168,     6,   117,   687,     6,   118,
     230,    29,   889,   711,   119,   717,   663,   664,   665,   666,
     380,     6,   718,     6,   117,   921,    34,   118,   492,   410,
      36,   411,   381,   938,   729,   779,   943,   259,   260,   261,
     262,   263,   264,   265,   939,   283,   780,   944,   536,   172,
     540,   543,   546,   169,   170,   321,    30,   220,   378,     6,
     709,    20,   502,   403,   517,   313,   518,   328,   372,    96,
     835,   536,   540,   543,   546,   562,   556,   842,   379,    97,
     573,   819,   563,   117,   564,   821,   118,   276,   747,   670,
     274,   275,   576,   405,   330,   117,   700,   117,   118,    33,
     118,   500,   117,   406,   484,   118,   117,   117,    38,   118,
     118,   361,   596,   598,   491,   322,   323,   324,   669,  -481,
     649,   505,   229,   668,    39,   119,  -480,   119,   228,   418,
      41,   362,   420,   880,   650,    98,   424,   425,   138,   383,
     407,   336,   373,   942,   138,   825,   374,   337,   888,     5,
     891,   172,    34,   698,   172,   172,   101,     6,   826,   509,
     349,   349,   331,   173,   184,   104,   402,   501,   227,    20,
     556,   454,   131,    20,   361,   473,    20,   483,   908,   822,
     482,    34,    35,   477,   525,   160,   276,   175,   136,   466,
     176,   276,   631,   556,   362,   535,   335,   764,   811,   812,
     347,   322,   323,   324,   770,   140,   710,   707,   149,   349,
      20,   230,   632,   493,   494,   928,   561,   372,   585,   468,
     623,   117,   117,   349,   118,   118,   763,   570,   787,   171,
     586,    34,   150,   373,   161,   181,    34,   374,   559,   186,
      20,   361,   373,   662,   790,    20,   374,   372,   614,   617,
     619,   621,   507,   331,   162,   163,   196,   786,   633,   634,
      34,   362,   331,   347,   361,     6,   524,   742,   534,   322,
     323,   324,   693,    20,   539,    20,    20,    20,    20,   743,
     575,   556,   564,   189,   362,   549,   174,   335,   175,   560,
     349,   176,    34,   349,   582,   373,   335,   677,   830,   374,
      20,   199,   775,   595,   571,   564,   887,   566,   677,   276,
    -482,   631,   466,   349,   573,   331,   597,   223,   564,   175,
     794,   845,   176,   210,   117,   117,   593,   118,   118,   117,
     347,   632,   118,   347,   117,    34,   278,   118,   803,   804,
     704,   151,   213,    20,    20,     1,   776,   777,   778,   335,
     372,   372,  -481,   347,   119,   119,     6,    34,   279,   636,
       2,    34,   627,   875,   641,   647,     3,   215,   373,   468,
     216,   700,   374,    34,   221,   781,   152,   233,   232,   890,
     349,   325,   525,   153,    34,   373,   827,   373,   331,   374,
     277,   374,   874,     4,    20,     5,   463,     6,   682,   322,
     323,   324,   280,   683,    20,   331,   573,   331,   281,   903,
     677,   691,   288,   703,    20,   701,   752,   705,     6,    20,
    -480,   289,   335,   349,   715,   482,   477,   893,   290,   894,
     361,   291,   295,   677,     6,   719,   700,   720,   373,   335,
     296,   335,   374,   434,   117,   117,   297,   118,   118,   572,
     362,   310,   369,   417,   384,   373,   154,   387,   331,   374,
     398,   404,   466,   347,   466,    20,   793,   155,   156,   157,
     158,   159,   372,   388,   805,   331,   807,   412,   808,   349,
     809,   397,   426,   423,   373,   427,   428,   749,   374,   751,
     453,     6,   335,   464,   478,   927,   754,   755,   756,   757,
      20,   342,    20,   573,   331,   349,   573,   760,     6,   335,
     677,   479,   349,   485,     6,   773,   322,   323,   324,   347,
     486,   487,   488,   489,    20,    20,    20,   490,   784,   466,
     496,   691,   691,   691,   497,   498,   789,    20,   335,   499,
     503,   506,   523,   573,   520,   347,   508,   550,   587,   519,
     117,   117,   347,   118,   118,   806,   800,   806,   802,   806,
     855,   806,   551,   538,   552,   542,   545,   548,   349,   553,
     677,   677,   554,   558,   652,   569,   588,   589,   417,   574,
     816,   817,   590,   592,   647,   677,   538,   542,   545,   548,
     872,   624,   529,   672,   628,   653,   642,   654,   806,   806,
     806,   806,   648,   432,   147,   148,   651,     6,   347,   671,
     836,   655,   679,   349,   692,   677,   373,   843,   694,    20,
     374,   697,   696,   721,   677,   702,   691,   848,   712,   722,
     730,   656,   853,   854,   723,   673,   331,   724,   434,   674,
     675,   676,   725,   677,   584,   726,   373,   373,   657,   727,
     374,   374,   728,   347,   591,   732,   733,   667,   913,   868,
     739,   740,   677,   871,   658,    20,   331,   331,    20,   746,
     335,   748,   760,   881,   765,   766,   767,   117,   117,   768,
     118,   118,   417,   771,   637,   434,   795,    20,   564,    20,
     529,   141,   143,   249,   252,   255,   258,   806,   806,   433,
     335,   335,   434,   435,   436,   437,   796,   898,   899,   373,
     900,   373,   797,   374,   798,   374,   810,   813,   909,   818,
     915,   823,   937,   828,   911,   831,   847,   866,   188,   331,
     832,   331,   193,   920,   837,   846,   197,   922,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   849,   856,   857,
     858,   859,   714,   867,    20,   860,   373,    20,   861,   862,
     374,   863,   864,   335,   477,   335,   936,   555,   865,     6,
     870,   876,   236,   237,   882,   885,   331,   883,    20,   884,
     389,   390,   892,   391,   392,   477,   393,   394,   373,   395,
     396,   695,   374,   895,   896,   267,   269,   897,   901,   455,
     904,   917,   914,   538,   542,   545,   548,   529,   331,   456,
     335,   923,   434,   457,   458,   459,   931,   750,   932,   753,
     772,   925,   926,   299,   300,   301,   302,   303,   305,   306,
     307,   308,   309,   673,   933,   945,   434,   674,   675,   676,
     731,   456,   335,   788,   434,   457,   458,   459,    39,    44,
      45,   105,   946,    46,   409,    47,   385,   143,    43,    48,
     214,   408,   673,   282,    49,   434,   674,   675,   676,   326,
      50,   713,   820,   469,   930,   107,   470,   940,   108,   109,
     652,   799,   471,   801,   110,   673,    52,    53,   434,   674,
     675,   676,    54,    55,   510,   266,   460,   386,    44,    45,
     472,   653,    46,   654,   311,   516,   312,   529,   314,    58,
     315,   529,   635,   419,   495,   421,   422,   655,    59,    60,
     316,   317,   318,   111,   319,   762,   838,   869,    61,     0,
      62,   112,    64,     0,     0,    52,    53,   656,     0,     0,
       0,    54,    55,     0,     0,   113,    65,     0,   114,    66,
       0,     0,   115,    67,   657,   399,     0,     0,    58,     0,
     852,     0,     0,     0,   327,   328,     0,     0,    44,    45,
     658,     0,    46,   329,    47,     0,   659,    61,    48,     0,
     116,    64,     0,    49,     0,     0,     0,   660,   400,    50,
       0,     0,   330,     0,     0,    65,   331,     0,    66,     0,
       0,     0,    67,     0,     0,    52,    53,   332,     0,     0,
       0,    54,    55,     0,   340,     0,     0,     0,   333,     0,
     225,     0,     0,   373,     0,     0,   334,   374,    58,     0,
     335,   322,   323,   324,   567,     0,     0,    59,    60,   336,
       0,     0,     0,   331,     0,   337,   833,    61,   910,    62,
       0,    64,     0,     0,   338,     0,     0,     0,   916,     0,
     852,   852,   226,     0,     0,    65,   339,     0,    66,     0,
       0,     0,    67,     0,     0,   877,   456,   335,     0,   434,
     457,   458,   459,     0,   340,     0,     0,     0,   673,   341,
     935,   434,   674,   675,   676,     0,     0,     0,   852,   342,
       0,   322,   323,   324,     0,   327,   328,     0,     0,    44,
      45,     0,   878,    46,   530,    47,     0,   673,     0,    48,
     434,   674,   675,   676,    49,   200,   201,   202,   203,   204,
      50,     0,     0,   330,     0,     0,     0,   331,   205,   206,
     207,   208,   209,   638,   639,   640,    52,    53,     0,     0,
       0,   886,    54,    55,   673,     0,     0,   434,   674,   675,
     676,   225,     0,     0,     0,     0,     0,   334,     0,    58,
       0,   335,     0,     0,     0,     0,     0,     0,    59,    60,
     336,     0,     0,     0,     0,     0,   337,     0,    61,     0,
      62,   905,    64,   673,     0,   338,   434,   674,   675,   676,
       0,     0,     0,   226,     0,     0,    65,   339,   839,    66,
       0,    44,    45,    67,   912,    46,     0,    47,     0,     0,
       0,    48,     0,     0,     0,   340,    49,     0,     0,     0,
     341,   924,    50,   673,     0,   840,   434,   674,   675,   676,
     342,   934,   322,   323,   324,     0,   373,     0,    52,    53,
     374,     0,     0,     0,    54,    55,   673,   761,     0,   434,
     674,   675,   676,     0,   373,     0,   331,     0,   374,     0,
       0,    58,     0,   673,     0,   431,   434,   674,   675,   676,
      59,    60,     0,   673,   331,     0,   434,   674,   675,   676,
      61,     0,    62,     0,    64,     0,     0,   841,     0,   433,
     335,     0,   434,   435,   436,   437,     0,   432,    65,     0,
       0,    66,     0,     0,     0,    67,     0,   433,   335,     0,
     434,   435,   436,   437,     0,     0,     0,   340,     0,     0,
       0,     0,    39,    44,    45,   105,     0,    46,     0,    47,
       0,     0,   592,    48,   322,   323,   324,     0,    49,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,   107,
     814,   815,   108,   109,     0,     0,     0,     0,   110,     6,
      52,    53,   438,     0,     0,     0,    54,    55,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     6,     0,     0,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,     0,   111,     0,     0,
       0,     0,    61,     0,    62,   268,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
      65,     0,   114,    66,     0,     0,   115,    67,     0,     0,
       0,     0,    44,    45,     0,     0,    46,     0,    47,    68,
       0,    69,    48,    70,     0,    71,    72,    49,     0,     0,
       0,     0,     0,    50,   116,    73,    74,    75,    76,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,    52,
      53,     0,     0,     0,     0,    54,    55,     0,     0,    56,
       0,    57,     0,     0,     0,   373,     0,     0,     0,   374,
       0,     0,    58,     0,     0,     0,   873,     0,     0,     0,
       0,    59,    60,     0,     0,   331,     0,     0,     0,     0,
       0,    61,     0,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,    66,     0,     0,     0,    67,     0,   433,   335,
       0,   434,   435,   436,   437,     0,     0,     0,    68,     0,
      69,   142,    70,     0,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,     0,     0,    48,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,    50,
       0,     0,    44,    45,     0,     0,    46,     0,    47,     0,
       0,     0,    48,    51,     0,    52,    53,    49,     6,     0,
       0,    54,    55,    50,     0,    56,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    58,    52,
      53,     0,     0,     0,     0,    54,    55,    59,    60,    56,
       0,    57,     0,     0,     0,     0,     0,    61,     0,    62,
      63,    64,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,    65,     0,     0,    66,     0,
       0,    61,    67,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    68,   273,    69,     0,    70,    65,
      71,    72,    66,     0,     0,     0,    67,     0,     0,     6,
      73,    74,    75,    76,     0,     0,     0,     0,    68,   382,
      69,     0,    70,     0,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,     0,     0,    48,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,    50,
       0,     0,    44,    45,     0,     0,    46,     0,    47,     0,
       0,     0,    48,    51,     0,    52,    53,    49,     0,     0,
       0,    54,    55,    50,     0,    56,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    58,    52,
      53,     0,     0,     0,     0,    54,    55,    59,    60,    56,
       0,    57,     0,     0,     0,     0,     0,    61,     0,    62,
      63,    64,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,    65,     0,     0,    66,     0,
       0,    61,    67,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    65,
      71,    72,    66,     0,     0,     0,    67,     0,     0,     6,
      73,    74,    75,    76,     0,     0,     0,     0,    68,     0,
      69,     0,    70,     0,   247,   248,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,     0,     0,    48,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,    50,
       0,     0,    44,    45,     0,     0,    46,     0,    47,     0,
       0,     0,    48,    51,     0,    52,    53,    49,     0,     0,
       0,    54,    55,    50,     0,    56,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    58,    52,
      53,     0,     0,     0,     0,    54,    55,    59,    60,    56,
       0,    57,     0,     0,     0,     0,     0,    61,     0,    62,
      63,    64,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,    65,     0,     0,    66,     0,
       0,    61,    67,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    65,
     250,   251,    66,     0,     0,     0,    67,     0,     0,     6,
      73,    74,    75,    76,     0,     0,     0,     0,    68,     0,
      69,     0,    70,     0,   253,   254,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,     0,     0,    48,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,    50,
       0,     0,    44,    45,     0,     0,    46,     0,    47,     0,
       0,     0,    48,    51,     0,    52,    53,    49,     0,     0,
       0,    54,    55,    50,     0,    56,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   298,    58,    52,
      53,     0,     0,     0,     0,    54,    55,    59,    60,    56,
       0,    57,     0,     0,     0,     0,     0,    61,     0,    62,
      63,    64,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,    65,     0,     0,    66,     0,
       0,    61,    67,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    65,
     256,   257,    66,     0,     0,     0,    67,     0,     0,     6,
      73,    74,    75,    76,     0,     0,     0,     0,    68,     0,
      69,     0,    70,     0,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,     0,     0,    48,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,    50,
       0,     0,    44,    45,     0,     0,    46,     0,    47,     0,
       0,     0,    48,   304,     0,    52,    53,    49,     0,     0,
       0,    54,    55,    50,     0,    56,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    58,    52,
      53,     0,     0,     0,     0,    54,    55,    59,    60,    56,
       0,    57,     0,     0,     0,     0,     0,    61,     0,    62,
      63,    64,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,    65,     0,     0,    66,     0,
       0,    61,    67,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    65,
      71,    72,    66,     0,     0,     0,    67,     0,     0,     6,
      73,    74,    75,    76,     0,     0,     0,     0,    68,     0,
      69,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    73,    74,    75,    76,    44,    45,
       0,     0,    46,     0,    47,     0,    44,    45,    48,     0,
      46,     0,    47,    49,     0,     0,    48,     0,     0,    50,
       0,    49,   906,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,    52,    53,     0,     0,     0,
       0,    54,    55,    52,    53,     0,     0,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,     0,     0,    59,    60,    61,     0,    62,
       0,    64,     0,     0,   907,    61,     0,    62,     0,    64,
       0,     0,   680,     0,     0,    65,     0,     0,    66,     0,
       0,     0,    67,    65,     0,     0,    66,   373,     0,     0,
      67,   374,     0,     0,   340,    44,    45,     0,   769,    46,
       0,    47,   340,     0,   373,    48,     0,   331,   374,   592,
      49,   322,   323,   324,   373,   785,    50,   592,   374,   322,
     323,   324,     0,     0,   331,   829,     0,     0,     0,     0,
       0,     0,    52,    53,   331,     0,     0,     0,    54,    55,
     456,   335,     0,   434,   457,   458,   459,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,   456,   335,     0,
     434,   457,   458,   459,    59,    60,     0,   456,   335,     0,
     434,   457,   458,   459,    61,     0,    62,     0,    64,    44,
      45,   782,     0,    46,     0,    47,     0,     0,     0,    48,
       0,     0,    65,     0,    49,    66,     0,     0,     0,    67,
      50,     0,     0,    44,    45,     0,     0,    46,     0,    47,
       0,   340,     0,    48,     0,     0,    52,    53,    49,     0,
       0,     0,    54,    55,    50,     0,   592,     0,   322,   323,
     324,     0,     0,     0,   373,     0,     0,     0,   374,    58,
      52,    53,     0,     0,     0,   844,    54,    55,    59,    60,
       0,     0,     0,     0,   331,     0,     0,     0,    61,     0,
      62,     0,    64,    58,     0,   834,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,    65,     0,     0,    66,
       0,     0,    61,    67,    62,     0,    64,   456,   335,   879,
     434,   457,   458,   459,     0,   340,     0,     0,     0,     0,
      65,     0,     0,    66,     0,     0,     0,    67,     0,     0,
     592,     0,   322,   323,   324,     0,     0,     0,     0,   340,
       0,     0,     0,     0,    39,    44,    45,   105,     0,    46,
       0,    47,     0,     0,   592,    48,   322,   323,   324,     0,
      49,     0,     0,     0,   512,     0,    50,     0,     0,     0,
     513,   107,     0,     0,   108,   109,     0,     0,     0,     0,
     110,   373,    52,    53,     0,   374,     0,     0,    54,    55,
       0,     0,   902,     0,     0,     0,     0,     0,     0,     0,
       0,   331,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,   111,
       0,     0,     0,     0,    61,     0,    62,   112,    64,     0,
       0,     0,     0,     0,   456,   335,     0,   434,   457,   458,
     459,   113,    65,     0,   114,    66,     0,     0,   115,    67,
      39,    44,    45,   105,     0,    46,     0,    47,     0,     0,
       0,    48,     0,     0,     0,     0,    49,     0,     0,     0,
     735,     0,    50,     0,     0,     0,   116,   107,     0,     0,
     108,   109,     0,     0,     0,     0,   110,     0,    52,    53,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,   111,     0,     0,     0,     0,
      61,     0,    62,   112,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,    65,     0,
     114,    66,     0,   599,   115,    67,     0,   736,    39,    44,
      45,   105,     0,    46,     0,    47,     0,   600,     0,    48,
     601,     0,   602,   603,    49,     0,     0,   604,   106,     0,
      50,     0,   116,     0,     0,   107,     0,     0,   108,   109,
       0,    22,     0,     0,   110,   605,    52,    53,     0,     0,
       0,     0,    54,    55,     0,   606,   607,     0,     0,   608,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
       0,     0,   609,   610,     0,     0,   611,     0,    59,    60,
       0,     0,     0,   111,   612,     0,     0,     0,    61,     0,
      62,   112,    64,     0,     0,   613,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,    65,     0,   114,    66,
       0,     0,   115,    67,    39,    44,    45,   105,     0,    46,
       0,    47,     0,     0,     0,    48,     0,     0,     0,     0,
      49,     0,     0,     0,   211,     0,    50,     0,     0,     0,
     116,   107,     0,     0,   108,   109,     0,     0,     0,     0,
     110,     0,    52,    53,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,   111,
       0,     0,     0,     0,    61,     0,    62,   112,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,    65,     0,   114,    66,     0,     0,   115,    67,
      39,    44,    45,   105,     0,    46,     0,    47,     0,     0,
       0,    48,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,    50,     0,     0,     0,   116,   107,     0,     0,
     108,   109,     0,     0,     0,     0,   110,     0,    52,    53,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,   111,     0,     0,     0,     0,
      61,     0,    62,   112,    64,     0,     0,     0,     0,     0,
       0,     0,   293,     0,     0,     0,     0,   113,    65,     0,
     114,    66,     0,     0,   115,    67,    39,    44,    45,   105,
       0,    46,     0,    47,     0,     0,     0,    48,     0,     0,
       0,     0,    49,     0,     0,     0,   511,     0,    50,     0,
       0,     0,   116,   107,     0,     0,   108,   109,     0,     0,
       0,     0,   110,     0,    52,    53,     0,     0,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,     0,     0,
       0,   111,     0,     0,     0,     0,    61,     0,    62,   112,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,    65,     0,   114,    66,     0,     0,
     115,    67,    39,    44,    45,   105,     0,    46,     0,    47,
       0,     0,     0,    48,     0,     0,     0,     0,    49,     0,
       0,     0,   734,     0,    50,     0,     0,     0,   116,   107,
       0,     0,   108,   109,     0,     0,     0,     0,   110,     0,
      52,    53,     0,     0,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,     0,   111,     0,     0,
       0,     0,    61,     0,    62,   112,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
      65,     0,   114,    66,     0,     0,   115,    67,    39,    44,
      45,   105,     0,    46,     0,    47,     0,     0,     0,    48,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
      50,     0,     0,     0,   116,   107,     0,     0,   108,   109,
       0,     0,     0,     0,   110,     0,    52,    53,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
       0,     0,     0,   111,     0,     0,     0,     0,    61,     0,
      62,   112,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,    65,     0,   114,    66,
       0,     0,   115,    67,    39,    44,    45,   105,     0,    46,
       0,    47,     0,     0,     0,    48,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,    50,     0,     0,     0,
     116,   107,     0,     0,   108,   109,     0,     0,     0,     0,
     110,     0,    52,    53,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,   111,
       0,     0,     0,     0,    61,     0,    62,   112,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     599,   113,    65,     0,   114,    66,    44,    45,   115,    67,
      46,     0,    47,     0,   600,     0,    48,   601,     0,   602,
     603,    49,     0,     0,   604,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,    51,   605,    52,    53,     0,     0,     0,     0,    54,
      55,     0,   606,   607,     0,     0,   608,     0,   225,     0,
       0,     0,     0,     0,     0,     0,    58,     0,     0,   609,
     610,     0,     0,   611,     0,    59,    60,     0,     0,     0,
       0,   612,     0,     0,     0,    61,     0,    62,     0,    64,
       0,     0,   613,     0,     0,     0,     0,     0,     0,     0,
     226,     0,     0,    65,     0,     0,    66,     0,     0,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6
};

static const yytype_int16 yycheck[] =
{
       0,     1,     2,     3,     4,     5,   580,    95,   579,   554,
      39,    99,     5,    39,   447,   333,   111,   138,   562,   370,
     429,   196,   697,   177,   525,   140,   222,   332,   461,   430,
     107,   140,    32,    44,    34,   574,    24,    41,   222,    32,
      39,    41,   757,    28,    70,    17,    60,   115,    29,    21,
      31,    51,   114,    28,   400,    11,   332,    16,   126,    16,
     218,    37,    25,     3,   222,    37,   128,    25,    22,   140,
     224,   140,    28,   895,   896,   115,   115,   478,   173,     4,
     218,   196,   111,   492,   222,   111,   125,   196,   114,    11,
      57,   120,    11,   116,   120,    71,    96,    22,    98,    71,
     140,    73,   125,    96,    63,    98,    63,   107,   333,   218,
     110,   933,   111,   127,   140,   433,    11,   435,   436,   437,
     101,   126,   100,   497,   498,   499,     8,   196,   132,   140,
      55,     0,   132,    28,    97,   140,   136,   115,   215,    97,
      50,   642,   447,   102,   173,   102,    28,   173,   692,   218,
     559,   125,   273,   504,   108,   140,   461,   503,   697,   115,
      27,    28,    87,    45,    89,   140,   195,   126,   140,   195,
     196,   115,   847,   582,   173,   115,   550,   551,   552,   553,
     376,   140,   122,   140,   213,   900,   114,   213,   116,   284,
     140,   286,   376,   115,   115,   115,   115,   164,   165,   166,
     167,   168,   169,   170,   126,   186,   126,   126,   433,   114,
     435,   436,   437,   138,   139,   215,   115,   217,   376,   140,
     115,   221,   397,   128,   114,   213,   116,     6,   221,    18,
     774,   456,   457,   458,   459,   116,   669,   781,   376,    28,
     465,   742,   123,   272,   125,   746,   272,   401,   649,   554,
     174,   175,   473,    18,    33,   284,   574,   286,   284,   115,
     286,   382,   291,    28,   341,   291,   295,   296,   123,   295,
     296,   429,   493,   494,   625,   142,   143,   144,   554,   116,
     114,   402,   397,   828,     8,   284,   123,   286,   397,   289,
      16,   429,   291,   837,   128,    84,   295,   296,   298,   223,
     281,    80,    17,   126,   304,   115,    21,    86,   847,   101,
     849,   114,   114,    28,   114,   114,    48,   140,   128,   407,
     429,   430,    37,   126,   126,   115,   126,   126,   397,   329,
     763,   331,   140,   333,   492,   335,   336,   341,   882,   748,
     340,   114,   115,   336,   125,    62,   500,   127,    98,   574,
     130,   505,   510,   786,   492,   432,    71,   662,   732,   733,
     429,   142,   143,   144,   669,   125,   940,   938,   125,   478,
     370,   397,   510,   373,   374,   914,   453,   370,   114,   697,
     501,   410,   411,   492,   410,   411,   662,   464,   693,   123,
     126,   114,   125,    17,   111,   123,   114,    21,   116,    40,
     400,   559,    17,   126,    28,   405,    21,   400,   496,   497,
     498,   499,   405,    37,   131,   132,   125,   693,   513,   514,
     114,   559,    37,   492,   582,   140,   426,   114,   432,   142,
     143,   144,   126,   433,   434,   435,   436,   437,   438,   126,
     123,   874,   125,   140,   582,   438,   125,    71,   127,   453,
     559,   130,   114,   562,   116,    17,    71,   558,   763,    21,
     460,   125,   683,   123,   464,   125,    28,   460,   569,   623,
     116,   629,   697,   582,   699,    37,   123,   125,   125,   127,
     701,   786,   130,   115,   513,   514,   490,   513,   514,   518,
     559,   629,   518,   562,   523,   114,   115,   523,   719,   720,
     577,     7,   116,   503,   504,    51,   684,   685,   686,    71,
     503,   504,   122,   582,   513,   514,   140,   114,   115,   518,
      66,   114,   115,   828,   523,   525,    72,   116,    17,   847,
     122,   849,    21,   114,   102,   116,    42,   124,   126,    28,
     649,   216,   125,    49,   114,    17,   116,    17,    37,    21,
     123,    21,   828,    99,   554,   101,    28,   140,   562,   142,
     143,   144,   123,   563,   564,    37,   791,    37,   115,   874,
     671,   564,    60,   577,   574,   575,   653,   577,   140,   579,
     123,   123,    71,   692,   588,   585,   579,   114,   117,   116,
     748,    96,    23,   694,   140,   595,   914,   597,    17,    71,
      23,    71,    21,    73,   633,   634,   126,   633,   634,    28,
     748,   115,   122,   288,   126,    17,   122,   126,    37,    21,
     115,    28,   847,   692,   849,   625,    28,   133,   134,   135,
     136,   137,   625,   126,   722,    37,   724,   123,   726,   748,
     728,   125,   123,   126,    17,   122,   115,   651,    21,   653,
      60,   140,    71,   125,    60,    28,   656,   657,   658,   659,
     660,   140,   662,   888,    37,   774,   891,   660,   140,    71,
     771,   127,   781,   115,   140,   679,   142,   143,   144,   748,
     115,    60,    60,   124,   684,   685,   686,   123,   692,   914,
     115,   684,   685,   686,   115,   115,   696,   697,    71,   115,
     148,   123,    27,   928,   117,   774,   123,   115,   122,   124,
     739,   740,   781,   739,   740,   722,   716,   724,   718,   726,
     797,   728,   115,   433,   115,   435,   436,   437,   837,   115,
     831,   832,   115,   115,    20,   115,   123,    59,   413,   115,
     739,   740,    59,   140,   744,   846,   456,   457,   458,   459,
     827,   126,   427,    28,   123,    41,   122,    43,   765,   766,
     767,   768,   115,    60,    71,    72,   123,   140,   837,   115,
     774,    57,   123,   882,   116,   876,    17,   781,   115,   779,
      21,   126,   123,   115,   885,   140,   779,    28,   128,   115,
      28,    77,   796,   797,   115,    70,    37,   115,    73,    74,
      75,    76,   115,   904,   479,   115,    17,    17,    94,   115,
      21,    21,   115,   882,   489,   115,   115,    28,    28,   823,
      23,    23,   923,   827,   110,   825,    37,    37,   828,   116,
      71,    60,   825,   837,   115,   115,   115,   866,   867,   115,
     866,   867,   517,   115,   519,    73,    60,   847,   125,   849,
     525,    68,    69,   160,   161,   162,   163,   864,   865,    70,
      71,    71,    73,    74,    75,    76,   123,   866,   867,    17,
     870,    17,   116,    21,    28,    21,   123,    28,   882,   115,
      28,   123,    28,   115,   884,   115,   126,    23,   105,    37,
     115,    37,   109,   897,   116,   115,   113,   901,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   115,   115,   115,
     115,   115,   587,    23,   914,   115,    17,   917,   115,   115,
      21,   115,   115,    71,   917,    71,   926,    28,   115,   140,
     116,   115,   149,   150,    60,   115,    37,   122,   938,   122,
     247,   248,   115,   250,   251,   938,   253,   254,    17,   256,
     257,    28,    21,    60,    60,   172,   173,   123,   123,    28,
     115,   125,   115,   673,   674,   675,   676,   642,    37,    70,
      71,   115,    73,    74,    75,    76,   115,   652,   115,   654,
      28,   122,   122,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,    70,    60,   115,    73,    74,    75,    76,
     629,    70,    71,    28,    73,    74,    75,    76,     8,     9,
      10,    11,   126,    13,   283,    15,   233,   234,    26,    19,
     132,   282,    70,   185,    24,    73,    74,    75,    76,   217,
      30,   585,   744,   334,   917,    35,   334,   930,    38,    39,
      20,   716,   334,   718,    44,    70,    46,    47,    73,    74,
      75,    76,    52,    53,   408,   171,   125,   234,     9,    10,
     334,    41,    13,    43,   213,   413,   213,   742,   213,    69,
     213,   746,   517,   290,   376,   292,   293,    57,    78,    79,
     213,   213,   213,    83,   213,   662,   779,   825,    88,    -1,
      90,    91,    92,    -1,    -1,    46,    47,    77,    -1,    -1,
      -1,    52,    53,    -1,    -1,   105,   106,    -1,   108,   109,
      -1,    -1,   112,   113,    94,   115,    -1,    -1,    69,    -1,
     795,    -1,    -1,    -1,     5,     6,    -1,    -1,     9,    10,
     110,    -1,    13,    14,    15,    -1,   116,    88,    19,    -1,
     140,    92,    -1,    24,    -1,    -1,    -1,   127,   148,    30,
      -1,    -1,    33,    -1,    -1,   106,    37,    -1,   109,    -1,
      -1,    -1,   113,    -1,    -1,    46,    47,    48,    -1,    -1,
      -1,    52,    53,    -1,   125,    -1,    -1,    -1,    59,    -1,
      61,    -1,    -1,    17,    -1,    -1,    67,    21,    69,    -1,
      71,   142,   143,   144,    28,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    37,    -1,    86,    28,    88,   883,    90,
      -1,    92,    -1,    -1,    95,    -1,    -1,    -1,   893,    -1,
     895,   896,   103,    -1,    -1,   106,   107,    -1,   109,    -1,
      -1,    -1,   113,    -1,    -1,    28,    70,    71,    -1,    73,
      74,    75,    76,    -1,   125,    -1,    -1,    -1,    70,   130,
     925,    73,    74,    75,    76,    -1,    -1,    -1,   933,   140,
      -1,   142,   143,   144,    -1,     5,     6,    -1,    -1,     9,
      10,    -1,    28,    13,    14,    15,    -1,    70,    -1,    19,
      73,    74,    75,    76,    24,   117,   118,   119,   120,   121,
      30,    -1,    -1,    33,    -1,    -1,    -1,    37,   117,   118,
     119,   120,   121,   520,   521,   522,    46,    47,    -1,    -1,
      -1,    28,    52,    53,    70,    -1,    -1,    73,    74,    75,
      76,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    -1,
      90,    28,    92,    70,    -1,    95,    73,    74,    75,    76,
      -1,    -1,    -1,   103,    -1,    -1,   106,   107,     6,   109,
      -1,     9,    10,   113,    28,    13,    -1,    15,    -1,    -1,
      -1,    19,    -1,    -1,    -1,   125,    24,    -1,    -1,    -1,
     130,    28,    30,    70,    -1,    33,    73,    74,    75,    76,
     140,    28,   142,   143,   144,    -1,    17,    -1,    46,    47,
      21,    -1,    -1,    -1,    52,    53,    70,    28,    -1,    73,
      74,    75,    76,    -1,    17,    -1,    37,    -1,    21,    -1,
      -1,    69,    -1,    70,    -1,    28,    73,    74,    75,    76,
      78,    79,    -1,    70,    37,    -1,    73,    74,    75,    76,
      88,    -1,    90,    -1,    92,    -1,    -1,    95,    -1,    70,
      71,    -1,    73,    74,    75,    76,    -1,    60,   106,    -1,
      -1,   109,    -1,    -1,    -1,   113,    -1,    70,    71,    -1,
      73,    74,    75,    76,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    -1,    13,    -1,    15,
      -1,    -1,   140,    19,   142,   143,   144,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    35,
     737,   738,    38,    39,    -1,    -1,    -1,    -1,    44,   140,
      46,    47,   125,    -1,    -1,    -1,    52,    53,    -1,    -1,
      56,    -1,    58,    -1,    -1,    -1,    -1,   140,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,   108,   109,    -1,    -1,   112,   113,    -1,    -1,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,   125,
      -1,   127,    19,   129,    -1,   131,   132,    24,    -1,    -1,
      -1,    -1,    -1,    30,   140,   141,   142,   143,   144,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    56,
      -1,    58,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,
      -1,    -1,    69,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,    -1,   109,    -1,    -1,    -1,   113,    -1,    70,    71,
      -1,    73,    74,    75,    76,    -1,    -1,    -1,   125,    -1,
     127,   128,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    44,    -1,    46,    47,    24,   140,    -1,
      -1,    52,    53,    30,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    69,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    78,    79,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    88,   113,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,   126,   127,    -1,   129,   106,
     131,   132,   109,    -1,    -1,    -1,   113,    -1,    -1,   140,
     141,   142,   143,   144,    -1,    -1,    -1,    -1,   125,   126,
     127,    -1,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    44,    -1,    46,    47,    24,    -1,    -1,
      -1,    52,    53,    30,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    69,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    78,    79,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    88,   113,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   127,    -1,   129,   106,
     131,   132,   109,    -1,    -1,    -1,   113,    -1,    -1,   140,
     141,   142,   143,   144,    -1,    -1,    -1,    -1,   125,    -1,
     127,    -1,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    44,    -1,    46,    47,    24,    -1,    -1,
      -1,    52,    53,    30,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    69,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    78,    79,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    88,   113,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   127,    -1,   129,   106,
     131,   132,   109,    -1,    -1,    -1,   113,    -1,    -1,   140,
     141,   142,   143,   144,    -1,    -1,    -1,    -1,   125,    -1,
     127,    -1,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    44,    -1,    46,    47,    24,    -1,    -1,
      -1,    52,    53,    30,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    69,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    78,    79,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    88,   113,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   127,    -1,   129,   106,
     131,   132,   109,    -1,    -1,    -1,   113,    -1,    -1,   140,
     141,   142,   143,   144,    -1,    -1,    -1,    -1,   125,    -1,
     127,    -1,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    44,    -1,    46,    47,    24,    -1,    -1,
      -1,    52,    53,    30,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    69,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    78,    79,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    88,   113,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   127,    -1,   129,   106,
     131,   132,   109,    -1,    -1,    -1,   113,    -1,    -1,   140,
     141,   142,   143,   144,    -1,    -1,    -1,    -1,   125,    -1,
     127,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,   141,   142,   143,   144,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,     9,    10,    19,    -1,
      13,    -1,    15,    24,    -1,    -1,    19,    -1,    -1,    30,
      -1,    24,    33,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    88,    -1,    90,
      -1,    92,    -1,    -1,    95,    88,    -1,    90,    -1,    92,
      -1,    -1,    95,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    -1,   113,   106,    -1,    -1,   109,    17,    -1,    -1,
     113,    21,    -1,    -1,   125,     9,    10,    -1,    28,    13,
      -1,    15,   125,    -1,    17,    19,    -1,    37,    21,   140,
      24,   142,   143,   144,    17,    28,    30,   140,    21,   142,
     143,   144,    -1,    -1,    37,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    47,    37,    -1,    -1,    -1,    52,    53,
      70,    71,    -1,    73,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    70,    71,    -1,
      73,    74,    75,    76,    78,    79,    -1,    70,    71,    -1,
      73,    74,    75,    76,    88,    -1,    90,    -1,    92,     9,
      10,    95,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,
      -1,    -1,   106,    -1,    24,   109,    -1,    -1,    -1,   113,
      30,    -1,    -1,     9,    10,    -1,    -1,    13,    -1,    15,
      -1,   125,    -1,    19,    -1,    -1,    46,    47,    24,    -1,
      -1,    -1,    52,    53,    30,    -1,   140,    -1,   142,   143,
     144,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    69,
      46,    47,    -1,    -1,    -1,    28,    52,    53,    78,    79,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    88,    -1,
      90,    -1,    92,    69,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,   106,    -1,    -1,   109,
      -1,    -1,    88,   113,    90,    -1,    92,    70,    71,    95,
      73,    74,    75,    76,    -1,   125,    -1,    -1,    -1,    -1,
     106,    -1,    -1,   109,    -1,    -1,    -1,   113,    -1,    -1,
     140,    -1,   142,   143,   144,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    -1,    -1,     8,     9,    10,    11,    -1,    13,
      -1,    15,    -1,    -1,   140,    19,   142,   143,   144,    -1,
      24,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,
      34,    35,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,
      44,    17,    46,    47,    -1,    21,    -1,    -1,    52,    53,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    70,    71,    -1,    73,    74,    75,
      76,   105,   106,    -1,   108,   109,    -1,    -1,   112,   113,
       8,     9,    10,    11,    -1,    13,    -1,    15,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      28,    -1,    30,    -1,    -1,    -1,   140,    35,    -1,    -1,
      38,    39,    -1,    -1,    -1,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,    -1,
     108,   109,    -1,    12,   112,   113,    -1,   115,     8,     9,
      10,    11,    -1,    13,    -1,    15,    -1,    26,    -1,    19,
      29,    -1,    31,    32,    24,    -1,    -1,    36,    28,    -1,
      30,    -1,   140,    -1,    -1,    35,    -1,    -1,    38,    39,
      -1,    50,    -1,    -1,    44,    54,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    -1,    64,    65,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    81,    82,    -1,    -1,    85,    -1,    78,    79,
      -1,    -1,    -1,    83,    93,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    -1,    -1,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,   106,    -1,   108,   109,
      -1,    -1,   112,   113,     8,     9,    10,    11,    -1,    13,
      -1,    15,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,
     140,    35,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,    -1,   108,   109,    -1,    -1,   112,   113,
       8,     9,    10,    11,    -1,    13,    -1,    15,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,   140,    35,    -1,    -1,
      38,    39,    -1,    -1,    -1,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,    -1,   105,   106,    -1,
     108,   109,    -1,    -1,   112,   113,     8,     9,    10,    11,
      -1,    13,    -1,    15,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    -1,   140,    35,    -1,    -1,    38,    39,    -1,    -1,
      -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,    -1,   108,   109,    -1,    -1,
     112,   113,     8,     9,    10,    11,    -1,    13,    -1,    15,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    28,    -1,    30,    -1,    -1,    -1,   140,    35,
      -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,   108,   109,    -1,    -1,   112,   113,     8,     9,
      10,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,   140,    35,    -1,    -1,    38,    39,
      -1,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,   106,    -1,   108,   109,
      -1,    -1,   112,   113,     8,     9,    10,    11,    -1,    13,
      -1,    15,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
     140,    35,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,   105,   106,    -1,   108,   109,     9,    10,   112,   113,
      13,    -1,    15,    -1,    26,    -1,    19,    29,    -1,    31,
      32,    24,    -1,    -1,    36,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,    -1,    -1,
      -1,    44,    54,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    -1,    64,    65,    -1,    -1,    68,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    81,
      82,    -1,    -1,    85,    -1,    78,    79,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    88,    -1,    90,    -1,    92,
      -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,    -1,    -1,   106,    -1,    -1,   109,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    51,    66,    72,    99,   101,   140,   150,   151,   152,
     153,   154,   155,   156,   277,   277,   277,   277,   277,   273,
     277,     0,    50,   161,   162,   163,   164,   165,   125,   115,
     115,   115,   125,   115,   114,   115,   140,   278,   123,     8,
     231,    16,   166,   165,     9,    10,    13,    15,    19,    24,
      30,    44,    46,    47,    52,    53,    56,    58,    69,    78,
      79,    88,    90,    91,    92,   106,   109,   113,   125,   127,
     129,   131,   132,   141,   142,   143,   144,   183,   185,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     222,   225,   277,   279,   280,   156,    18,    28,    84,   156,
     273,    48,   157,   277,   115,    11,    28,    35,    38,    39,
      44,    83,    91,   105,   108,   112,   140,   216,   217,   226,
     227,   228,   229,   231,   232,   233,   238,   239,   240,   241,
     278,   140,   167,   168,   275,   277,    98,   169,   277,   215,
     125,   209,   128,   209,   223,   224,   217,   213,   213,   125,
     125,     7,    42,    49,   122,   133,   134,   135,   136,   137,
      62,   111,   131,   132,     4,    22,    55,    87,    89,   138,
     139,   123,   114,   126,   125,   127,   130,   220,   221,   161,
     273,   123,   273,   161,   126,   156,    40,   160,   209,   140,
     276,   277,   278,   209,   226,   227,   125,   209,   217,   125,
     117,   118,   119,   120,   121,   117,   118,   119,   120,   121,
     115,    28,   226,   116,   168,   116,   122,   170,   171,   172,
     277,   102,   206,   125,   220,    61,   103,   183,   185,   186,
     217,   230,   126,   124,   114,   128,   209,   209,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   131,   132,   213,
     131,   132,   213,   131,   132,   213,   131,   132,   213,   215,
     215,   215,   215,   215,   215,   215,   219,   209,    91,   209,
     216,   217,   227,   126,   225,   225,   221,   123,   115,   115,
     123,   115,   166,   156,     8,    28,    45,   260,    60,   123,
     117,    96,   100,   100,   230,    23,    23,   126,    44,   209,
     209,   209,   209,   209,    44,   209,   209,   209,   209,   209,
     115,   228,   229,   231,   232,   233,   238,   239,   240,   241,
     276,   277,   142,   143,   144,   274,   172,     5,     6,    14,
      33,    37,    48,    59,    67,    71,    80,    86,    95,   107,
     125,   130,   140,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   191,   192,   193,   195,   202,   203,   204,
     205,   245,   246,   253,   261,   272,   274,   275,   276,   122,
     207,   208,   273,    17,    21,   242,   243,   244,   245,   246,
     256,   257,   126,   225,   126,   209,   224,   126,   126,   213,
     213,   213,   213,   213,   213,   213,   213,   125,   115,   115,
     148,   220,   126,   128,    28,    18,    28,   156,   169,   162,
     227,   227,   123,   234,   235,   236,   237,   274,   277,   209,
     226,   209,   209,   126,   226,   226,   123,   122,   115,    60,
     127,    28,    60,    70,    73,    74,    75,    76,   125,   245,
     246,   255,   256,   257,   259,   262,   263,   264,   265,   266,
     267,   268,   273,    60,   277,    28,    70,    74,    75,    76,
     125,   264,   266,    28,   125,   254,   255,   258,   259,   193,
     195,   202,   203,   277,    28,   196,   197,   273,    60,   127,
     189,   190,   277,   275,   276,   115,   115,    60,    60,   124,
     123,   208,   116,   277,   277,   244,   115,   115,   115,   115,
     220,   126,   230,   148,   207,   220,   123,   273,   123,   161,
     206,    28,    28,    34,    27,    28,   235,   114,   116,   124,
     117,    25,    97,    27,   277,   125,   173,   174,   176,   274,
      14,   179,   184,   194,   275,   276,   255,   259,   268,   277,
     255,   259,   268,   255,   259,   268,   255,   259,   268,   273,
     115,   115,   115,   115,   115,    28,   265,   266,   115,   116,
     275,   276,   116,   123,   125,   247,   273,    28,   266,   115,
     276,   277,    28,   255,   115,   123,   247,    11,    28,   115,
     198,   199,   116,   184,   274,   114,   126,   122,   123,    59,
      59,   274,   140,   275,   179,   123,   247,   123,   247,    12,
      26,    29,    31,    32,    36,    54,    64,    65,    68,    81,
      82,    85,    93,   104,   161,   251,   252,   161,   252,   161,
     252,   161,   252,   220,   126,   207,   115,   115,   123,   158,
     159,   245,   246,   227,   227,   237,   226,   274,   209,   209,
     209,   226,   122,   173,   175,   177,   178,   277,   115,   114,
     128,   123,    20,    41,    43,    57,    77,    94,   110,   116,
     127,   271,   126,   252,   252,   252,   252,    28,   263,   264,
     266,   115,    28,    70,    74,    75,    76,   267,   179,   123,
      95,   182,   275,   277,    16,    63,   102,   126,   248,   249,
     250,   273,   116,   126,   115,    28,   123,   126,    28,   254,
     259,   277,   140,   275,   276,   277,    28,   197,    28,   115,
     199,   179,   128,   190,   274,   275,     3,   115,   122,   277,
     277,   115,   115,   115,   115,   115,   115,   115,   115,   115,
      28,   159,   115,   115,    28,    28,   115,    25,    97,    23,
      23,   173,   114,   126,   115,   126,   116,   184,    60,   275,
     274,   275,   276,   274,   277,   277,   277,   277,   269,   270,
     273,    28,   262,   264,   266,   115,   115,   115,   115,    28,
     266,   115,    28,   275,   116,   247,   250,   250,   250,   115,
     126,   116,    95,   182,   275,    28,   264,   266,    28,   277,
      28,   254,   258,    28,   247,    60,   123,   116,    28,   274,
     277,   274,   277,   247,   247,   161,   251,   161,   161,   161,
     123,   252,   252,    28,   209,   209,   226,   226,   115,   173,
     178,   173,   179,   123,   271,   115,   128,   116,   115,    28,
     266,   115,   115,    28,    95,   182,   275,   116,   249,     6,
      33,    95,   182,   275,    28,   266,   115,   126,    28,   115,
     200,   201,   274,   275,   275,   276,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,    23,    23,   275,   270,
     116,   275,   276,    28,   264,   266,   115,    28,    28,    95,
     182,   275,    60,   122,   122,   115,    28,    28,   254,   258,
      28,   254,   115,   114,   116,    60,    60,   123,   226,   226,
     277,   123,    28,   266,   115,    28,    33,    95,   182,   275,
     274,   277,    28,    28,   115,    28,   274,   125,   200,   200,
     275,   271,   275,   115,    28,   122,   122,    28,   254,   126,
     196,   115,   115,    60,    28,   274,   277,    28,   115,   126,
     198,   200,   126,   115,   126,   115,   126
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   149,   150,   150,   150,   150,   150,   151,   151,   151,
     151,   151,   151,   151,   151,   152,   152,   152,   153,   154,
     154,   154,   154,   155,   156,   156,   157,   157,   157,   158,
     158,   159,   159,   159,   159,   160,   160,   161,   162,   163,
     163,   164,   164,   165,   166,   166,   167,   167,   168,   168,
     168,   169,   169,   170,   170,   171,   172,   172,   173,   173,
     173,   174,   175,   175,   176,   177,   177,   178,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   180,   180,   180,
     181,   181,   182,   182,   183,   183,   183,   183,   183,   183,
     183,   184,   184,   184,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   186,   186,   187,
     188,   189,   189,   190,   190,   191,   191,   191,   191,   192,
     192,   192,   192,   192,   192,   192,   192,   193,   193,   194,
     194,   195,   195,   195,   195,   195,   196,   196,   197,   198,
     198,   199,   199,   199,   199,   200,   200,   200,   200,   200,
     201,   201,   202,   203,   203,   204,   204,   205,   205,   205,
     205,   206,   206,   207,   207,   208,   208,   208,   208,   208,
     209,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   211,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   213,   214,   214,
     214,   214,   214,   214,   214,   214,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   216,   216,   217,   218,
     218,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   220,   220,   221,   221,   222,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   227,   227,   228,   228,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   230,   230,   230,   230,   231,   231,
     232,   232,   233,   233,   233,   234,   234,   235,   236,   236,
     237,   237,   238,   238,   239,   240,   240,   240,   240,   241,
     242,   242,   243,   243,   244,   244,   244,   244,   244,   244,
     244,   244,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   246,   246,   246,   246,   247,   247,
     248,   248,   249,   249,   249,   249,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   252,   252,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   254,   254,
     255,   255,   255,   255,   255,   255,   255,   255,   256,   256,
     256,   256,   257,   257,   257,   257,   258,   258,   259,   260,
     260,   260,   260,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   262,
     262,   263,   263,   263,   263,   263,   264,   264,   265,   265,
     265,   265,   265,   266,   266,   267,   267,   267,   267,   267,
     268,   268,   268,   269,   269,   270,   270,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   272,   272,   272,   272,
     272,   272,   272,   272,   273,   273,   274,   274,   274,   275,
     276,   277,   278,   279,   279,   279,   280
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     5,     6,     5,
       6,     7,     8,     8,     9,     9,     6,     3,     7,     5,
       8,     8,    11,     6,     3,     0,     6,     5,     0,     2,
       1,     4,     4,     2,     2,     3,     0,     2,     5,     1,
       0,     2,     1,     3,     2,     0,     2,     1,     4,     6,
       8,     2,     0,     2,     1,     2,     3,     3,     1,     1,
       1,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     1,     3,     1,     1,     1,     1,     4,     2,
       2,     2,     2,     1,     1,     1,     1,     6,     3,     3,
       1,     3,     4,     4,     5,     2,     3,     1,     3,     2,
       1,     7,     9,     5,     7,     5,     6,     6,     7,     4,
       3,     1,     3,     3,     5,     2,     4,     3,     1,     3,
       1,     2,     0,     2,     1,     6,     6,     6,     6,     4,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     3,     3,     3,     2,     2,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     2,     1,     1,
       1,     3,     2,     1,     4,     1,     4,     4,     1,     3,
       1,     5,     4,     2,     4,     3,     1,     6,     5,     3,
       5,     4,     2,     2,     1,     3,     1,     3,     2,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     4,     1,     2,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     3,     2,
       4,     6,     5,     7,     8,     2,     1,     3,     3,     1,
       3,     1,     4,     4,     4,    10,     8,    10,     8,     4,
       1,     0,     2,     1,     6,     4,     6,     4,     6,     4,
       6,     4,     7,     5,     6,     4,     7,     5,     6,     4,
       7,     5,     6,     4,     5,     3,     4,     2,     3,     2,
       3,     1,     2,     2,     2,     1,     5,     3,     5,     3,
       5,     3,     5,     3,     1,     7,     5,     7,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     3,     4,     5,
       7,     5,     8,     6,     9,     7,    10,     8,     2,     1,
       4,     2,     4,     2,     4,     2,     4,     2,     5,     3,
       4,     2,     5,     3,     4,     2,     3,     1,     3,     3,
       5,     3,     1,     2,     4,     3,     5,     4,     6,     5,
       7,     5,     7,     6,     8,     7,     9,     8,    10,     3,
       1,     1,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     3,     1,     1,     2,     2,     2,     2,
       8,     5,     3,     3,     1,     3,     5,     2,     2,     2,
       2,     2,     1,     2,     4,     0,     2,     3,     4,     5,
       5,     6,     7,     8,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
#line 70 "delphi_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtDelphiGoal_create((yyvsp[0]).pContext);
  (yyval).pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
#line 2846 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "delphi_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtDelphiGoal_create((yyvsp[0]).pContext);
  (yyval).pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
#line 2859 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 4:
#line 88 "delphi_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtDelphiGoal_create((yyvsp[0]).pContext);
  (yyval).pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
#line 2872 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 5:
#line 97 "delphi_y.y" /* yacc.c:1646  */
    {
  void* pObj;

  pObj        = adtDelphiGoal_create((yyvsp[0]).pContext);
  (yyval).pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
#line 2885 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 6:
#line 106 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add(adtDelphi_getRoot(), (yyvsp[0]).pContext);
}
#line 2893 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 7:
#line 116 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 2901 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 2909 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 9:
#line 124 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0);
}
#line 2917 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 10:
#line 128 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 0);
}
#line 2925 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 11:
#line 132 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-6]).pContext, (yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 2933 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 12:
#line 136 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 2941 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 13:
#line 140 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[0]).pContext);
}
#line 2949 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 14:
#line 144 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMacro_create((yyvsp[-8]).pContext, (yyvsp[-6]).pContext, 0, (yyvsp[-4]).pContext, (yyvsp[-1]).pContext);
}
#line 2957 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 15:
#line 150 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProgram_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-8]).sComment);
}
#line 2965 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 16:
#line 154 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProgram_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-5]).sComment);
}
#line 2973 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 17:
#line 158 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProgram_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-2]).sComment);
}
#line 2981 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiUnit_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-6]).sComment);
}
#line 2989 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 19:
#line 170 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPackage_create((yyvsp[-3]).pContext, 0, 0, (yyvsp[-4]).sComment);
}
#line 2997 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPackage_create((yyvsp[-6]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[-7]).sComment);
}
#line 3005 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 21:
#line 178 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPackage_create((yyvsp[-6]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[-7]).sComment);
}
#line 3013 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 22:
#line 182 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPackage_create((yyvsp[-9]).pContext, (yyvsp[-6]).pContext, (yyvsp[-3]).pContext, (yyvsp[-10]).sComment);
}
#line 3021 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 23:
#line 188 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiLibrary_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[-5]).sComment);
}
#line 3029 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 24:
#line 194 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiUsesClause_create((yyvsp[-1]).pContext, (yyvsp[-2]).sComment);
}
#line 3037 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 25:
#line 198 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3045 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 26:
#line 204 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceSection_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-5]).sComment);
}
#line 3053 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 27:
#line 208 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceSection_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-4]).sComment);
}
#line 3061 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 28:
#line 212 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3069 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 29:
#line 218 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3077 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 30:
#line 222 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExportedHeadingList_create((yyvsp[0]).pContext);
}
#line 3085 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 31:
#line 228 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExportedHeading_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, (yyvsp[-3]).sComment);
}
#line 3093 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 32:
#line 232 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExportedHeading_create(0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, (yyvsp[-3]).sComment);
}
#line 3101 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 33:
#line 236 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExportedHeading_create((yyvsp[-1]).pContext, 0, 0, (yyvsp[-1]).sComment);
}
#line 3109 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 34:
#line 240 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExportedHeading_create(0, (yyvsp[-1]).pContext, 0, (yyvsp[-1]).sComment);
}
#line 3117 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 35:
#line 246 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiImplementationSection_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-2]).sComment);
}
#line 3125 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 36:
#line 250 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3133 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 37:
#line 256 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiBlock_create((yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-1]).sComment);
}
#line 3141 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 38:
#line 262 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDeclSection_create((yyvsp[-4]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-4]).sComment);
}
#line 3149 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 39:
#line 268 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiLabelDeclSection_create((yyvsp[0]).pContext);
}
#line 3157 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 40:
#line 272 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3165 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 41:
#line 278 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3173 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 42:
#line 282 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiLabelDeclList_create((yyvsp[0]).pContext);
}
#line 3181 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 43:
#line 288 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiLabelDecl_create((yyvsp[-1]).pContext, (yyvsp[-2]).sComment);
}
#line 3189 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 44:
#line 294 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstSection_create((yyvsp[0]).pContext, (yyvsp[-1]).sComment);
}
#line 3197 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 45:
#line 298 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3205 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 46:
#line 304 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3213 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 47:
#line 308 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstantDeclList_create((yyvsp[0]).pContext);
}
#line 3221 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 48:
#line 314 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstantDecl_create((yyvsp[-3]).pContext, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 3229 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 49:
#line 318 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstantDecl_create((yyvsp[-3]).pContext, (yyvsp[-5]).pContext, 0, 0, (yyvsp[-1]).pContext);
}
#line 3237 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 50:
#line 322 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstantDecl_create((yyvsp[-3]).pContext, (yyvsp[-5]).pContext, (yyvsp[-7]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 3245 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypeSection_create((yyvsp[0]).pContext, (yyvsp[-1]).sComment);
}
#line 3253 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 52:
#line 332 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 3261 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 53:
#line 338 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3269 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 54:
#line 342 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypeDeclList_create((yyvsp[0]).pContext);
}
#line 3277 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 55:
#line 348 "delphi_y.y" /* yacc.c:1646  */
    {
  adtDelphi_setTypeScope((yyvsp[-1]).pContext);

  (yyval).pContext = (yyvsp[-1]).pContext;
}
#line 3287 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 56:
#line 356 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypeDecl_create((yyvsp[-2]).pContext, (yyvsp[-1]).pContext, 0);

  adtDelphi_clearTypeScope();
}
#line 3297 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 57:
#line 362 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypeDecl_create((yyvsp[-2]).pContext, 0, (yyvsp[-1]).pContext);

  adtDelphi_clearTypeScope();
}
#line 3307 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 58:
#line 370 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypedConstant_create((yyvsp[0]).pContext, 0, 0);
}
#line 3315 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 59:
#line 374 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypedConstant_create(0, (yyvsp[0]).pContext, 0);
}
#line 3323 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 60:
#line 378 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypedConstant_create(0, 0, (yyvsp[0]).pContext);
}
#line 3331 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 61:
#line 384 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiArrayConstant_create((yyvsp[-1]).pContext);
}
#line 3339 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 62:
#line 390 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3347 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 63:
#line 394 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypedConstantList_create((yyvsp[0]).pContext);
}
#line 3355 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 64:
#line 400 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecordConstant_create((yyvsp[-1]).pContext);
}
#line 3363 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 65:
#line 406 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3371 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 66:
#line 410 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecordFieldConstantList_create((yyvsp[0]).pContext);
}
#line 3379 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 67:
#line 416 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecordFieldConstant_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3387 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 68:
#line 422 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
#line 3395 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 69:
#line 426 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, 0);
}
#line 3403 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 70:
#line 430 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 3411 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 71:
#line 434 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0);
}
#line 3419 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 72:
#line 438 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 3427 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 73:
#line 442 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3435 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 74:
#line 446 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3443 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 75:
#line 450 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3451 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 76:
#line 454 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 3459 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 77:
#line 460 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRestrictedType_create((yyvsp[0]).pContext, 0, 0);
}
#line 3467 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 78:
#line 464 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRestrictedType_create(0, (yyvsp[0]).pContext, 0);
}
#line 3475 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 79:
#line 468 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRestrictedType_create(0, 0, (yyvsp[0]).pContext);
}
#line 3483 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 80:
#line 474 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassRefType_create((yyvsp[0]).pContext, 0);
}
#line 3491 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 81:
#line 478 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassRefType_create((yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 3499 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 82:
#line 484 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleType_create((yyvsp[0]).pContext, 0);
}
#line 3507 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 83:
#line 488 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleType_create(0, (yyvsp[0]).pContext);
}
#line 3515 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 84:
#line 494 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(0);
}
#line 3523 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 85:
#line 498 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(1);
}
#line 3531 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 86:
#line 502 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(2);
}
#line 3539 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 87:
#line 506 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(3);
}
#line 3547 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 88:
#line 510 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(4);
}
#line 3555 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 89:
#line 514 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(5);
}
#line 3563 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 90:
#line 518 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRealType_create(6);
}
#line 3571 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 91:
#line 524 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdinalType_create((yyvsp[0]).pContext, 0, 0);
}
#line 3579 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 92:
#line 528 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdinalType_create(0, (yyvsp[0]).pContext, 0);
}
#line 3587 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 93:
#line 532 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdinalType_create(0, 0, (yyvsp[0]).pContext);
}
#line 3595 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 94:
#line 538 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(0);
}
#line 3603 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 95:
#line 542 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(1);
}
#line 3611 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 96:
#line 546 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(2);
}
#line 3619 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 97:
#line 550 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(3);
}
#line 3627 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 98:
#line 554 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(4);
}
#line 3635 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 99:
#line 558 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(5);
}
#line 3643 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 100:
#line 562 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(6);
}
#line 3651 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 101:
#line 566 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(7);
}
#line 3659 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 102:
#line 570 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(8);
}
#line 3667 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 103:
#line 574 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(9);
}
#line 3675 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 104:
#line 578 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(10);
}
#line 3683 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 105:
#line 582 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(11);
}
#line 3691 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 106:
#line 586 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdIdent_create(12);
}
#line 3699 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 107:
#line 592 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantType_create(0);
}
#line 3707 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 108:
#line 596 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantType_create(1);
}
#line 3715 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 109:
#line 602 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSubrangeType_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3723 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 110:
#line 608 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiEnumeratedType_create((yyvsp[-1]).pContext);
}
#line 3731 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 111:
#line 614 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3739 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 112:
#line 618 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiEnumeratedTypeElementList_create((yyvsp[0]).pContext);
}
#line 3747 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 113:
#line 624 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiEnumeratedTypeElement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3755 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 114:
#line 628 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiEnumeratedTypeElement_create((yyvsp[0]).pContext, 0);
}
#line 3763 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 115:
#line 634 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStringType_create(0, 0);
}
#line 3771 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 116:
#line 638 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStringType_create(1, 0);
}
#line 3779 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 117:
#line 642 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStringType_create(2, 0);
}
#line 3787 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 118:
#line 646 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStringType_create(0, (yyvsp[-1]).pContext);
}
#line 3795 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 119:
#line 652 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(1, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 3803 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 120:
#line 656 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(1, 0, (yyvsp[-1]).pContext, 0, 0);
}
#line 3811 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 121:
#line 660 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(1, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 3819 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 122:
#line 664 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(1, 0, 0, 0, (yyvsp[-1]).pContext);
}
#line 3827 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 123:
#line 668 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 3835 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 124:
#line 672 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 3843 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 125:
#line 676 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(0, 0, 0, (yyvsp[0]).pContext, 0);
}
#line 3851 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 126:
#line 680 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStructType_create(0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 3859 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 127:
#line 686 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiArrayType_create((yyvsp[-3]).pContext, (yyvsp[0]).pContext);
}
#line 3867 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 128:
#line 690 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiArrayType_create(0, (yyvsp[0]).pContext);
}
#line 3875 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 129:
#line 696 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3883 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 130:
#line 700 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiOrdinalTypeList_create((yyvsp[0]).pContext);
}
#line 3891 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 131:
#line 706 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecType_create((yyvsp[-1]).pContext, 0);
}
#line 3899 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 132:
#line 710 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecType_create((yyvsp[-2]).pContext, 0);
}
#line 3907 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 133:
#line 714 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecType_create((yyvsp[-2]).pContext, (yyvsp[-1]).pContext);
}
#line 3915 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 134:
#line 718 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecType_create((yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 3923 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 135:
#line 722 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecType_create(0, 0);
}
#line 3931 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 136:
#line 728 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3939 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 137:
#line 732 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFieldDeclList_create((yyvsp[0]).pContext);
}
#line 3947 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 138:
#line 738 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFieldDecl_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 3955 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 139:
#line 744 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 3963 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 140:
#line 748 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantSectionList_create((yyvsp[0]).pContext);
}
#line 3971 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 141:
#line 754 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantSection_create((yyvsp[-5]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 3979 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 142:
#line 758 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantSection_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 3987 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 143:
#line 762 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantSection_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 3995 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 144:
#line 766 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVariantSection_create(0, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 4003 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 145:
#line 772 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecVariant_create((yyvsp[-4]).pContext, (yyvsp[-1]).pContext, 0);
}
#line 4011 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 146:
#line 776 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecVariant_create((yyvsp[-5]).pContext, (yyvsp[-2]).pContext, 0);
}
#line 4019 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 147:
#line 780 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecVariant_create((yyvsp[-5]).pContext, (yyvsp[-2]).pContext, (yyvsp[-1]).pContext);
}
#line 4027 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 148:
#line 784 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecVariant_create((yyvsp[-6]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 4035 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 149:
#line 788 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRecVariant_create((yyvsp[-3]).pContext, 0, 0);
}
#line 4043 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 150:
#line 794 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4051 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 151:
#line 798 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstExprList_create((yyvsp[0]).pContext);
}
#line 4059 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 152:
#line 804 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetType_create((yyvsp[0]).pContext);
}
#line 4067 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 153:
#line 810 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFileType_create(0, (yyvsp[0]).pContext);
}
#line 4075 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 154:
#line 814 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFileType_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4083 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 155:
#line 820 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPointerType_create(0, (yyvsp[0]).pContext);
}
#line 4091 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 156:
#line 824 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPointerType_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4099 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 157:
#line 830 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureType_create((yyvsp[-2]).pContext, 0, 1);
}
#line 4107 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 158:
#line 834 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureType_create((yyvsp[0]).pContext, 0, 0);
}
#line 4115 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 159:
#line 838 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureType_create(0, (yyvsp[-2]).pContext, 1);
}
#line 4123 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 160:
#line 842 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureType_create(0, (yyvsp[0]).pContext, 0);
}
#line 4131 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 161:
#line 848 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarSection_create((yyvsp[0]).pContext, (yyvsp[-1]).sComment);
}
#line 4139 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 162:
#line 852 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 4147 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 163:
#line 858 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4155 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 164:
#line 862 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDeclList_create((yyvsp[0]).pContext);
}
#line 4163 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 165:
#line 868 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDecl_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 1);
}
#line 4171 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 166:
#line 872 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDecl_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 1);
}
#line 4179 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 167:
#line 876 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDecl_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0);
}
#line 4187 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 168:
#line 880 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDecl_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 0);
}
#line 4195 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 169:
#line 884 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiVarDecl_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 4203 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 170:
#line 890 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExpression_create((yyvsp[0]).pContext);
}
#line 4211 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 171:
#line 896 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(1, (yyvsp[0]).pContext));
}
#line 4219 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 172:
#line 900 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(2, (yyvsp[0]).pContext));
}
#line 4227 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 173:
#line 904 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(3, (yyvsp[0]).pContext));
}
#line 4235 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 174:
#line 908 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(4, (yyvsp[0]).pContext));
}
#line 4243 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 175:
#line 912 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(5, (yyvsp[0]).pContext));
}
#line 4251 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 176:
#line 916 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(6, (yyvsp[0]).pContext));
}
#line 4259 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 177:
#line 920 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(7, (yyvsp[0]).pContext));
}
#line 4267 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 178:
#line 924 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(8, (yyvsp[0]).pContext));
}
#line 4275 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 179:
#line 928 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiExpressionRelOp_create(9, (yyvsp[0]).pContext));
}
#line 4283 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 180:
#line 932 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExpressionRelOpList_create(adtDelphiExpressionRelOp_create(0, (yyvsp[0]).pContext));
}
#line 4291 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 181:
#line 938 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleExpression_create((yyvsp[0]).pContext);
}
#line 4299 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 182:
#line 944 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(1, 1, (yyvsp[0]).pContext));
}
#line 4307 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 183:
#line 948 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(2, 1, (yyvsp[0]).pContext));
}
#line 4315 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 184:
#line 952 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(3, 1, (yyvsp[0]).pContext));
}
#line 4323 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 185:
#line 956 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(4, 1, (yyvsp[0]).pContext));
}
#line 4331 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 186:
#line 960 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(1, 2, (yyvsp[0]).pContext));
}
#line 4339 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 187:
#line 964 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(2, 2, (yyvsp[0]).pContext));
}
#line 4347 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 188:
#line 968 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(3, 2, (yyvsp[0]).pContext));
}
#line 4355 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 189:
#line 972 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-3]).pContext, adtDelphiSimpleExpressionAddOp_create(4, 2, (yyvsp[0]).pContext));
}
#line 4363 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 190:
#line 976 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiSimpleExpressionAddOp_create(1, 0, (yyvsp[0]).pContext));
}
#line 4371 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 191:
#line 980 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiSimpleExpressionAddOp_create(2, 0, (yyvsp[0]).pContext));
}
#line 4379 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 192:
#line 984 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiSimpleExpressionAddOp_create(3, 0, (yyvsp[0]).pContext));
}
#line 4387 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 193:
#line 988 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiSimpleExpressionAddOp_create(4, 0, (yyvsp[0]).pContext));
}
#line 4395 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 194:
#line 992 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 1, (yyvsp[0]).pContext));
}
#line 4403 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 195:
#line 996 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 2, (yyvsp[0]).pContext));
}
#line 4411 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1000 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 0, (yyvsp[0]).pContext));
}
#line 4419 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1006 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTerm_create((yyvsp[0]).pContext);
}
#line 4427 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1012 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(1, (yyvsp[0]).pContext));
}
#line 4435 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1016 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(2, (yyvsp[0]).pContext));
}
#line 4443 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1020 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(3, (yyvsp[0]).pContext));
}
#line 4451 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1024 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(4, (yyvsp[0]).pContext));
}
#line 4459 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1028 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(5, (yyvsp[0]).pContext));
}
#line 4467 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1032 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(6, (yyvsp[0]).pContext));
}
#line 4475 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1036 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, adtDelphiFactorMulOp_create(7, (yyvsp[0]).pContext));
}
#line 4483 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1040 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactorMulOpList_create(adtDelphiFactorMulOp_create(0, (yyvsp[0]).pContext));
}
#line 4491 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1053 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#line 4499 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1057 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create((yyvsp[0]).pContext, 1, 0, 0, 0, 0, 0, 0, 0, 0);
}
#line 4507 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1061 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0);
}
#line 4515 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1065 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 4523 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1069 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
}
#line 4531 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1073 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, (yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 4539 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1077 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 4547 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1081 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 4555 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1085 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 4563 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1089 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 4571 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1095 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCastExpression_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 4579 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1099 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCastExpression_create(0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 4587 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1105 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignator_create((yyvsp[0]).pContext);
}
#line 4595 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1111 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4603 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1115 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObjList_create((yyvsp[0]).pContext);
}
#line 4611 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1121 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0);
}
#line 4619 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1125 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-3]).pContext, 0, (yyvsp[0]).pContext, 1, 0);
}
#line 4627 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1129 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 4635 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1133 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 4643 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1137 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-2]).pContext, 0, 0, 1, 0);
}
#line 4651 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1141 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 4659 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1145 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 1);
}
#line 4667 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1149 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-3]).pContext, 0, (yyvsp[0]).pContext, 1, 1);
}
#line 4675 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1153 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext, 0, 1);
}
#line 4683 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1157 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, 0, 1);
}
#line 4691 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1161 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[-2]).pContext, 0, 0, 1, 1);
}
#line 4699 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1165 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorObj_create((yyvsp[0]).pContext, 0, 0, 0, 1);
}
#line 4707 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1171 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 4715 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1175 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorRefList_create((yyvsp[0]).pContext);
}
#line 4723 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1181 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorRef_create((yyvsp[-1]).pContext);
}
#line 4731 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1185 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDesignatorRef_create(0);
}
#line 4739 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1191 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetConstructor_create((yyvsp[-1]).pContext);
}
#line 4747 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1195 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetConstructor_create(0);
}
#line 4755 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1201 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4763 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1205 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetElementList_create((yyvsp[0]).pContext);
}
#line 4771 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1211 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetElement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4779 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1215 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSetElement_create((yyvsp[0]).pContext, 0);
}
#line 4787 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1221 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 4795 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1225 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExprList_create((yyvsp[0]).pContext);
}
#line 4803 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1231 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4811 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1235 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4819 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1239 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4827 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1243 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4835 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1247 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4843 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1251 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, (yyvsp[0]).sComment);
}
#line 4851 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1255 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, (yyvsp[0]).sComment);
}
#line 4859 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1259 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, (yyvsp[0]).sComment);
}
#line 4867 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1263 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, (yyvsp[0]).sComment);
}
#line 4875 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1267 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[-1]).sComment);
}
#line 4883 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1271 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4891 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1275 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4899 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1279 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4907 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1283 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4915 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1287 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4923 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1291 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0, (yyvsp[-2]).sComment);
}
#line 4931 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1295 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, (yyvsp[-2]).sComment);
}
#line 4939 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1299 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, (yyvsp[-2]).sComment);
}
#line 4947 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1303 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, 0, 0, (yyvsp[0]).pContext, (yyvsp[-2]).sComment);
}
#line 4955 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1309 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[-1]).pContext);
}
#line 4963 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1313 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiStmtList_create((yyvsp[-1]).pContext);
}
#line 4971 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1319 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExitStatement_create(0);
}
#line 4979 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1323 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiExitStatement_create(1);
}
#line 4987 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1328 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
#line 4995 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1332 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 5003 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1336 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 2);
}
#line 5011 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1340 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 3);
}
#line 5019 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1344 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 4);
}
#line 5027 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1348 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0);
}
#line 5035 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1352 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 5043 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1356 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, 0, (yyvsp[-1]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 5051 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1360 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 5059 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1364 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 5067 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1368 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).pContext, 0, 1);
}
#line 5075 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1372 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).pContext, 0, 2);
}
#line 5083 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1376 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).pContext, 0, 3);
}
#line 5091 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1380 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).pContext, 0, 4);
}
#line 5099 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1384 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, (yyvsp[0]).pContext, 0, 0, 0, 0, (yyvsp[-2]).pContext, 0, 0);
}
#line 5107 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1388 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, 0, (yyvsp[-2]).pContext, 1, 0);
}
#line 5115 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1394 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSizeofType_create((yyvsp[0]).pContext, 0, 0, 0);
}
#line 5123 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1398 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSizeofType_create(0, (yyvsp[0]).pContext, 0, 0);
}
#line 5131 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1402 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSizeofType_create(0, 0, (yyvsp[0]).pContext, 0);
}
#line 5139 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1406 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiSizeofType_create(0, 0, 0, (yyvsp[0]).pContext);
}
#line 5147 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1412 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCompoundStmt_create((yyvsp[-1]).pContext);
}
#line 5155 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1416 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCompoundStmt_create(0);
}
#line 5163 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1422 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiIfStmt_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 5171 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1426 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiIfStmt_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5179 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1432 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseStmt_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0);
}
#line 5187 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1436 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseStmt_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5195 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1440 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseStmt_create((yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext);
}
#line 5203 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1446 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 5211 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1450 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseSelectorList_create((yyvsp[0]).pContext);
}
#line 5219 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1456 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseSelector_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5227 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1462 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5235 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1466 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseLabelList_create((yyvsp[0]).pContext);
}
#line 5243 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1472 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseLabel_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5251 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1476 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiCaseLabel_create((yyvsp[0]).pContext, 0);
}
#line 5259 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1482 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRepeatStmt_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 5267 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1486 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiRepeatStmt_create(0, (yyvsp[0]).pContext, (yyvsp[-2]).pContext);
}
#line 5275 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1492 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiWhileStmt_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5283 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1498 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiForStmt_create((yyvsp[-8]).pContext, (yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 5291 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1502 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiForStmt_create(0, (yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0);
}
#line 5299 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1506 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiForStmt_create((yyvsp[-8]).pContext, (yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1);
}
#line 5307 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1510 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiForStmt_create(0, (yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 1);
}
#line 5315 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1516 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiWithStmt_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5323 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1522 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDeclSection_create((yyvsp[0]).pContext);
}
#line 5331 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1526 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = 0;
}
#line 5339 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1532 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 5347 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1536 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDeclList_create((yyvsp[0]).pContext);
}
#line 5355 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1542 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create((yyvsp[-5]).pContext, 0, 0, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5363 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1546 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create((yyvsp[-3]).pContext, 0, 0, 0, 0, (yyvsp[-1]).pContext);
}
#line 5371 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1550 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, 0, (yyvsp[-5]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5379 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1554 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, 0, (yyvsp[-3]).pContext, 0, 0, (yyvsp[-1]).pContext);
}
#line 5387 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1558 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, 0, 0, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5395 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1562 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, 0, 0, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 5403 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1566 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, (yyvsp[-5]).pContext, 0, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5411 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1570 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureDecl_create(0, (yyvsp[-3]).pContext, 0, 0, 0, (yyvsp[-1]).pContext);
}
#line 5419 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1576 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-6]).sComment);
}
#line 5427 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1580 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-4]).sComment);
}
#line 5435 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1584 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-5]).sComment);
}
#line 5443 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1588 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 5451 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1592 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, (yyvsp[-6]).sComment);
}
#line 5459 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1596 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, (yyvsp[-4]).sComment);
}
#line 5467 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1600 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 0, (yyvsp[0]).pContext, (yyvsp[-5]).sComment);
}
#line 5475 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1604 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-2]).pContext, 0, 0, (yyvsp[0]).pContext, (yyvsp[-3]).sComment);
}
#line 5483 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1608 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, 0, (yyvsp[-6]).sComment);
}
#line 5491 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1612 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, 0, 0, (yyvsp[-4]).sComment);
}
#line 5499 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1616 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 0, 0, (yyvsp[-5]).sComment);
}
#line 5507 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1620 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFunctionHeading_create(0, (yyvsp[-2]).pContext, 0, 0, 0, (yyvsp[-3]).sComment);
}
#line 5515 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1626 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureHeading_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-4]).sComment);
}
#line 5523 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1630 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureHeading_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-2]).sComment);
}
#line 5531 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1634 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureHeading_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 5539 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1638 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProcedureHeading_create(0, (yyvsp[0]).pContext, 0, (yyvsp[-1]).sComment);
}
#line 5547 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1644 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParameters_create((yyvsp[-1]).pContext);
}
#line 5555 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1648 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParameters_create(0);
}
#line 5563 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1654 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5571 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1658 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParamList_create((yyvsp[0]).pContext);
}
#line 5579 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1664 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParam_create(1, (yyvsp[0]).pContext);
}
#line 5587 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1668 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParam_create(2, (yyvsp[0]).pContext);
}
#line 5595 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1672 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParam_create(3, (yyvsp[0]).pContext);
}
#line 5603 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1676 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiFormalParam_create(0, (yyvsp[0]).pContext);
}
#line 5611 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1682 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 1, 0, 0);
}
#line 5619 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1686 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0);
}
#line 5627 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1690 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, 0, (yyvsp[0]).pContext, 0, 0, 1, 0, 0);
}
#line 5635 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1694 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, 0, 0, 0, 0);
}
#line 5643 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1698 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, 0, 0, 0, 0, 1, 1, 0);
}
#line 5651 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1702 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 1, 0);
}
#line 5659 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1706 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, 0, 0, 0, 0, 1, 0, 1);
}
#line 5667 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1710 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-2]).pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 5675 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1714 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[0]).pContext, 0, 0, 0, 0, 0, 0, 0);
}
#line 5683 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1718 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-6]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, 1, 0, 0);
}
#line 5691 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1722 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, 0, 0, 0);
}
#line 5699 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1726 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-6]).pContext, 0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 1, 0, 0);
}
#line 5707 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1730 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiParameter_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 5715 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1736 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(1);
}
#line 5723 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1740 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(2);
}
#line 5731 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1744 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(3);
}
#line 5739 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1748 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(4);
}
#line 5747 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1752 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(5);
}
#line 5755 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1756 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(6);
}
#line 5763 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 365:
#line 1760 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(7);
}
#line 5771 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 366:
#line 1764 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(8);
}
#line 5779 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 367:
#line 1768 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(9);
}
#line 5787 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 368:
#line 1772 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(10);
}
#line 5795 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 369:
#line 1776 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(11);
}
#line 5803 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 370:
#line 1780 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(12);
}
#line 5811 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 371:
#line 1784 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(13);
}
#line 5819 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 372:
#line 1788 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(14);
}
#line 5827 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 373:
#line 1792 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirective_create(15);
}
#line 5835 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 374:
#line 1798 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 5843 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 375:
#line 1802 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDirectiveList_create((yyvsp[0]).pContext);
}
#line 5851 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 376:
#line 1808 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, 0, 0, 0);
}
#line 5859 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 377:
#line 1812 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, 0, 0, (yyvsp[-1]).pContext);
}
#line 5867 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 378:
#line 1816 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, 0, (yyvsp[-2]).pContext, 0);
}
#line 5875 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 379:
#line 1820 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5883 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 380:
#line 1824 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 0);
}
#line 5891 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 381:
#line 1828 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, (yyvsp[-2]).pContext, 0, 0);
}
#line 5899 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 382:
#line 1832 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 5907 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 383:
#line 1836 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 5915 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 384:
#line 1840 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create((yyvsp[-6]).pContext, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0);
}
#line 5923 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 385:
#line 1844 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, (yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0);
}
#line 5931 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 386:
#line 1848 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5939 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 387:
#line 1852 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjectType_create(0, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 5947 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 388:
#line 1858 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 5955 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 389:
#line 1862 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethodList_create((yyvsp[0]).pContext);
}
#line 5963 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 390:
#line 1868 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create((yyvsp[-3]).pContext, 0, 0, 0, (yyvsp[-1]).pContext);
}
#line 5971 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 391:
#line 1872 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create((yyvsp[-1]).pContext, 0, 0, 0, 0);
}
#line 5979 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 392:
#line 1876 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, (yyvsp[-3]).pContext, 0, 0, (yyvsp[-1]).pContext);
}
#line 5987 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 393:
#line 1880 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, (yyvsp[-1]).pContext, 0, 0, 0);
}
#line 5995 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 394:
#line 1884 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, 0, (yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext);
}
#line 6003 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 395:
#line 1888 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, 0, (yyvsp[-1]).pContext, 0, 0);
}
#line 6011 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 396:
#line 1892 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, 0, 0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext);
}
#line 6019 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 397:
#line 1896 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiMethod_create(0, 0, 0, (yyvsp[-1]).pContext, 0);
}
#line 6027 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 398:
#line 1902 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstructorHeading_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-4]).sComment);
}
#line 6035 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 399:
#line 1906 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstructorHeading_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-2]).sComment);
}
#line 6043 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 400:
#line 1910 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstructorHeading_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 6051 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 401:
#line 1914 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstructorHeading_create(0, (yyvsp[0]).pContext, 0, (yyvsp[-1]).sComment);
}
#line 6059 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 402:
#line 1920 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDestructorHeading_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-4]).sComment);
}
#line 6067 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 403:
#line 1924 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDestructorHeading_create(0, (yyvsp[-1]).pContext, (yyvsp[0]).pContext, (yyvsp[-2]).sComment);
}
#line 6075 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 404:
#line 1928 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDestructorHeading_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext, 0, (yyvsp[-3]).sComment);
}
#line 6083 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 405:
#line 1932 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiDestructorHeading_create(0, (yyvsp[0]).pContext, 0, (yyvsp[-1]).sComment);
}
#line 6091 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 406:
#line 1938 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6099 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 407:
#line 1942 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjFieldList_create((yyvsp[0]).pContext);
}
#line 6107 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 408:
#line 1948 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiObjField_create((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6115 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 409:
#line 1954 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInitSection_create((yyvsp[-1]).pContext, 0, 1, (yyvsp[-2]).sComment);
}
#line 6123 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 410:
#line 1958 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInitSection_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 1, (yyvsp[-4]).sComment);
}
#line 6131 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 411:
#line 1962 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInitSection_create((yyvsp[-1]).pContext, 0, 0, (yyvsp[-2]).sComment);
}
#line 6139 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 412:
#line 1966 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInitSection_create(0, 0, 0, (yyvsp[0]).sComment);
}
#line 6147 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 413:
#line 1972 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, 0, 0, 0);
}
#line 6155 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 414:
#line 1976 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, 0, 0, (yyvsp[-2]).pContext);
}
#line 6163 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 415:
#line 1980 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, 0, (yyvsp[-1]).pContext, 0);
}
#line 6171 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 416:
#line 1984 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 6179 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 417:
#line 1988 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, (yyvsp[-2]).pContext, 0, 0);
}
#line 6187 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 418:
#line 1992 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, (yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext);
}
#line 6195 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 419:
#line 1996 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0);
}
#line 6203 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2000 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create(0, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 6211 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2004 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-2]).pContext, 0, 0, 0);
}
#line 6219 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2008 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-4]).pContext, 0, 0, (yyvsp[-2]).pContext);
}
#line 6227 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2012 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-3]).pContext, 0, (yyvsp[-1]).pContext, 0);
}
#line 6235 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2016 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-5]).pContext, 0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 6243 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2020 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, 0, 0);
}
#line 6251 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2024 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-6]).pContext, (yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext);
}
#line 6259 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2028 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0);
}
#line 6267 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2032 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassType_create((yyvsp[-7]).pContext, (yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext);
}
#line 6275 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2038 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6283 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2042 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassFieldList_create((yyvsp[0]).pContext);
}
#line 6291 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2048 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassField_create(0, (yyvsp[0]).pContext);
}
#line 6299 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2052 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassField_create(1, (yyvsp[0]).pContext);
}
#line 6307 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2056 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassField_create(1, (yyvsp[0]).pContext);
}
#line 6315 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2060 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassField_create(2, (yyvsp[0]).pContext);
}
#line 6323 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2064 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassField_create(3, (yyvsp[0]).pContext);
}
#line 6331 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2070 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-1]).pContext, (yyvsp[0]).pContext);
}
#line 6339 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2074 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethodList_create((yyvsp[0]).pContext);
}
#line 6347 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2080 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethod_create(0, (yyvsp[0]).pContext);
}
#line 6355 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2084 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethod_create(1, (yyvsp[0]).pContext);
}
#line 6363 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2088 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethod_create(2, (yyvsp[0]).pContext);
}
#line 6371 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2092 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethod_create(3, (yyvsp[0]).pContext);
}
#line 6379 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2096 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassMethod_create(4, (yyvsp[0]).pContext);
}
#line 6387 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2102 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6395 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2106 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassPropertyList_create((yyvsp[0]).pContext);
}
#line 6403 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2112 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassProperty_create(0, (yyvsp[0]).pContext);
}
#line 6411 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2116 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassProperty_create(1, (yyvsp[0]).pContext);
}
#line 6419 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2120 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassProperty_create(2, (yyvsp[0]).pContext);
}
#line 6427 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2124 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassProperty_create(3, (yyvsp[0]).pContext);
}
#line 6435 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2128 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiClassProperty_create(4, (yyvsp[0]).pContext);
}
#line 6443 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2134 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProperty_create((yyvsp[-6]).pContext, (yyvsp[-1]).pContext, (yyvsp[-4]).pContext, (yyvsp[0]).pContext);
}
#line 6451 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2138 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProperty_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext);
}
#line 6459 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2142 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiProperty_create(0, (yyvsp[-1]).pContext, 0, (yyvsp[0]).pContext);
}
#line 6467 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2148 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6475 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2152 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertyParameterList_create((yyvsp[0]).pContext);
}
#line 6483 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2158 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertyParameter_create((yyvsp[-2]).pContext, 0, (yyvsp[0]).pContext);
}
#line 6491 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2162 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertyParameter_create((yyvsp[-4]).pContext, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6499 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2172 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(1, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 6507 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2176 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(2, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 6515 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2180 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(3, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 6523 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2184 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(4, (yyvsp[0]).pContext, 0, 0, 0);
}
#line 6531 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2188 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(5, 0, (yyvsp[0]).pContext, 0, 0);
}
#line 6539 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2192 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(6, 0, 0, 0, 0);
}
#line 6547 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2196 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(7, 0, 0, 0, (yyvsp[0]).pContext);
}
#line 6555 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2200 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(7, 0, 0, (yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6563 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2204 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiPropertySpecifiers_create(0, 0, 0, 0, 0);
}
#line 6571 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2210 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create(0, 0, 0, (yyvsp[-1]).sComment);
}
#line 6579 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2214 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create(0, (yyvsp[-1]).pContext, 0, (yyvsp[-2]).sComment);
}
#line 6587 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2218 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create(0, 0, (yyvsp[-2]).pContext, (yyvsp[-3]).sComment);
}
#line 6595 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2222 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create(0, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-4]).sComment);
}
#line 6603 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2226 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create((yyvsp[-2]).pContext, 0, 0, (yyvsp[-4]).sComment);
}
#line 6611 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2230 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create((yyvsp[-3]).pContext, (yyvsp[-1]).pContext, 0, (yyvsp[-5]).sComment);
}
#line 6619 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2234 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create((yyvsp[-4]).pContext, 0, (yyvsp[-2]).pContext, (yyvsp[-6]).sComment);
}
#line 6627 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2238 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiInterfaceType_create((yyvsp[-5]).pContext, (yyvsp[-3]).pContext, (yyvsp[-2]).pContext, (yyvsp[-7]).sComment);
}
#line 6635 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2244 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiList_add((yyvsp[-2]).pContext, (yyvsp[0]).pContext);
}
#line 6643 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2248 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiIdentList_create((yyvsp[0]).pContext);
}
#line 6651 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2260 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstExpr_create((yyvsp[0]).sValue, 1);
}
#line 6659 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2264 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstExpr_create((yyvsp[0]).sValue, 1);
}
#line 6667 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2268 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiConstExpr_create((yyvsp[0]).sValue, 0);
}
#line 6675 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2274 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiTypeId_create((yyvsp[0]).sValue);
}
#line 6683 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2280 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiUnitId_create((yyvsp[0]).sValue);
}
#line 6691 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2286 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiIdent_create((yyvsp[0]).sValue);
}
#line 6699 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2292 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiLabelId_create((yyvsp[0]).sValue);
}
#line 6707 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2298 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiNumber_create((yyvsp[0]).sValue, 0);
}
#line 6715 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2302 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiNumber_create((yyvsp[0]).sValue, 1);
}
#line 6723 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2306 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiNumber_create((yyvsp[0]).sValue, 2);
}
#line 6731 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2312 "delphi_y.y" /* yacc.c:1646  */
    {
  (yyval).pContext = adtDelphiString_create((yyvsp[0]).sValue);
}
#line 6739 "../../src/delphi_y.c" /* yacc.c:1646  */
    break;


#line 6743 "../../src/delphi_y.c" /* yacc.c:1646  */
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
