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
#line 1 "cpp_y.y"

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



#line 116 "../../src/cpp_y.c"

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
#define LONGBOOL 324
#define WCHAR_T 325
#define EXPLICIT 326
#define IF 327
#define SIZEOF 328
#define UNION 329
#define CHAR 330
#define CLASS 331
#define USING 332
#define VOLATILE 333
#define SIGNED 334
#define CONST 335
#define LONG 336
#define STATIC 337
#define INT 338
#define ELSE 339
#define SHORT 340
#define NAMESPACE 341
#define REGISTER 342
#define TYPEDEF 343
#define FRIEND 344
#define FOR 345
#define GOTO 346
#define VIRTUAL 347
#define INLINE 348
#define CASE 349
#define VOID 350
#define STRUCT 351
#define BREAK 352
#define IDENTIFIER 353
#define QUALIFIED_IDENTIFIER 354
#define DTOR 355
#define QUALIFIED_DTOR 356
#define OBJ_IDENTIFIER 357
#define QUALIFIED_OBJ_IDENTIFIER 358
#define SINGLELINE_COMMENT 359
#define MULTILINE_COMMENT 360
#define EMBEDDED_COMMANDS 361
#define PREPROCESSOR 362
#define WHITESPACE 363
#define ADDVARIABLES 364

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
typedef yytype_int16 yy_state_t;

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

#define YYUNDEFTOK  2
#define YYMAXUTOK   364


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
static const yytype_int16 yyrline[] =
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
static const yytype_int16 yytoknum[] =
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

#define YYPACT_NINF (-384)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
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
static const yytype_int16 yydefact[] =
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
static const yytype_int16 yytable[] =
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
static const yytype_int8 yyr2[] =
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
#line 74 "cpp_y.y"
{
  void* pObj;

  pObj        = adtCppTranslationUnit_create(yyvsp[0].pContext);
  yyval.pContext = adtCpp_setRoot(pObj);

  adtCpp_releaseObject(pObj);
}
#line 2360 "../../src/cpp_y.c"
    break;

  case 3:
#line 83 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(adtCpp_getRoot(), yyvsp[0].pContext);
}
#line 2368 "../../src/cpp_y.c"
    break;

  case 4:
#line 91 "cpp_y.y"
{
  yyval.pContext = adtCppMacro_create(yyvsp[-4].sValue, yyvsp[-2].pContext, yyvsp[0].pContext, 0);
}
#line 2376 "../../src/cpp_y.c"
    break;

  case 5:
#line 95 "cpp_y.y"
{
  yyval.pContext = adtCppMacro_create(yyvsp[-6].sValue, yyvsp[-4].pContext, yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2384 "../../src/cpp_y.c"
    break;

  case 6:
#line 101 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleDeclarationList_create(yyvsp[0].pContext);
}
#line 2392 "../../src/cpp_y.c"
    break;

  case 7:
#line 105 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 2400 "../../src/cpp_y.c"
    break;

  case 8:
#line 112 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(0, 0, 0, 0, yyvsp[0].sValue);
}
#line 2408 "../../src/cpp_y.c"
    break;

  case 9:
#line 116 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(0, 0, 0, 0, yyvsp[0].sValue);
}
#line 2416 "../../src/cpp_y.c"
    break;

  case 10:
#line 120 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(yyvsp[-1].pContext, 0, 0, 0, 0);
}
#line 2424 "../../src/cpp_y.c"
    break;

  case 11:
#line 124 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(0, yyvsp[-1].pContext, 0, 1, 0);
}
#line 2432 "../../src/cpp_y.c"
    break;

  case 12:
#line 128 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(0, yyvsp[-1].pContext, 0, 0, 0);
}
#line 2440 "../../src/cpp_y.c"
    break;

  case 13:
#line 132 "cpp_y.y"
{
  yyval.pContext = adtCppPostfixExpression_create(0, 0, yyvsp[0].pContext, 0, 0);
}
#line 2448 "../../src/cpp_y.c"
    break;

  case 14:
#line 139 "cpp_y.y"
{
  yyval.pContext = adtCppExpressionList_create(yyvsp[0].pContext);
}
#line 2456 "../../src/cpp_y.c"
    break;

  case 15:
#line 143 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2464 "../../src/cpp_y.c"
    break;

  case 16:
#line 150 "cpp_y.y"
{
  yyval.pContext = adtCppDirectedExpression_create(yyvsp[0].pContext);
}
#line 2472 "../../src/cpp_y.c"
    break;

  case 17:
#line 154 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2480 "../../src/cpp_y.c"
    break;

  case 18:
#line 165 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[0].sValue, 0, 0, 0, 0);
}
#line 2488 "../../src/cpp_y.c"
    break;

  case 19:
#line 169 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[0].sValue, 0, 0, 1, 0);
}
#line 2496 "../../src/cpp_y.c"
    break;

  case 20:
#line 173 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-2].sValue, 0, 0, 0, 1);
}
#line 2504 "../../src/cpp_y.c"
    break;

  case 21:
#line 177 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-2].sValue, 0, 0, 1, 1);
}
#line 2512 "../../src/cpp_y.c"
    break;

  case 22:
#line 181 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-3].sValue, yyvsp[-1].pContext, 0, 0, 1);
}
#line 2520 "../../src/cpp_y.c"
    break;

  case 23:
#line 185 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-3].sValue, yyvsp[-1].pContext, 0, 1, 1);
}
#line 2528 "../../src/cpp_y.c"
    break;

  case 24:
#line 189 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-1].sValue, 0, yyvsp[0].pContext, 0, 0);
}
#line 2536 "../../src/cpp_y.c"
    break;

  case 25:
#line 193 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-1].sValue, 0, yyvsp[0].pContext, 1, 0);
}
#line 2544 "../../src/cpp_y.c"
    break;

  case 26:
#line 197 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-3].sValue, 0, yyvsp[0].pContext, 0, 1);
}
#line 2552 "../../src/cpp_y.c"
    break;

  case 27:
#line 201 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-3].sValue, 0, yyvsp[0].pContext, 1, 1);
}
#line 2560 "../../src/cpp_y.c"
    break;

  case 28:
#line 205 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-4].sValue, yyvsp[-2].pContext, yyvsp[0].pContext, 0, 1);
}
#line 2568 "../../src/cpp_y.c"
    break;

  case 29:
#line 209 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpression_create(yyvsp[-4].sValue, yyvsp[-2].pContext, yyvsp[0].pContext, 1, 1);
}
#line 2576 "../../src/cpp_y.c"
    break;

  case 30:
#line 216 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorExpressionDims_create(yyvsp[-1].pContext);
}
#line 2584 "../../src/cpp_y.c"
    break;

  case 31:
#line 220 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-3].pContext, yyvsp[-1].pContext);
}
#line 2592 "../../src/cpp_y.c"
    break;

  case 32:
#line 227 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryExpression_create(yyvsp[0].pContext, 0, 0, 0, 0);
}
#line 2600 "../../src/cpp_y.c"
    break;

  case 33:
#line 231 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryExpression_create(0, yyvsp[0].pContext, 0, 0, 1);
}
#line 2608 "../../src/cpp_y.c"
    break;

  case 34:
#line 235 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryExpression_create(0, yyvsp[0].pContext, 0, 0, 0);
}
#line 2616 "../../src/cpp_y.c"
    break;

  case 35:
#line 239 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryExpression_create(0, yyvsp[0].pContext, yyvsp[-1].pContext, 0, 0);
}
#line 2624 "../../src/cpp_y.c"
    break;

  case 36:
#line 243 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryExpression_create(0, 0, 0, yyvsp[-1].pContext, 0);
}
#line 2632 "../../src/cpp_y.c"
    break;

  case 37:
#line 250 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryOperator_create(0);
}
#line 2640 "../../src/cpp_y.c"
    break;

  case 38:
#line 254 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryOperator_create(1);
}
#line 2648 "../../src/cpp_y.c"
    break;

  case 39:
#line 258 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryOperator_create(2);
}
#line 2656 "../../src/cpp_y.c"
    break;

  case 40:
#line 262 "cpp_y.y"
{
  yyval.pContext = adtCppUnaryOperator_create(3);
}
#line 2664 "../../src/cpp_y.c"
    break;

  case 41:
#line 269 "cpp_y.y"
{
  yyval.pContext = adtCppMultiplicativeExpression_create(0, yyvsp[0].pContext, 0);
}
#line 2672 "../../src/cpp_y.c"
    break;

  case 42:
#line 273 "cpp_y.y"
{
  yyval.pContext = adtCppMultiplicativeExpression_create(0, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2680 "../../src/cpp_y.c"
    break;

  case 43:
#line 277 "cpp_y.y"
{
  yyval.pContext = adtCppMultiplicativeExpression_create(1, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2688 "../../src/cpp_y.c"
    break;

  case 44:
#line 281 "cpp_y.y"
{
  yyval.pContext = adtCppMultiplicativeExpression_create(2, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2696 "../../src/cpp_y.c"
    break;

  case 45:
#line 288 "cpp_y.y"
{
  yyval.pContext = adtCppAdditiveExpression_create(0, yyvsp[0].pContext, 0);
}
#line 2704 "../../src/cpp_y.c"
    break;

  case 46:
#line 292 "cpp_y.y"
{
  yyval.pContext = adtCppAdditiveExpression_create(0, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2712 "../../src/cpp_y.c"
    break;

  case 47:
#line 296 "cpp_y.y"
{
  yyval.pContext = adtCppAdditiveExpression_create(1, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2720 "../../src/cpp_y.c"
    break;

  case 48:
#line 303 "cpp_y.y"
{
  yyval.pContext = adtCppShiftExpression_create(0, yyvsp[0].pContext, 0);
}
#line 2728 "../../src/cpp_y.c"
    break;

  case 49:
#line 307 "cpp_y.y"
{
  yyval.pContext = adtCppShiftExpression_create(0, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2736 "../../src/cpp_y.c"
    break;

  case 50:
#line 311 "cpp_y.y"
{
  yyval.pContext = adtCppShiftExpression_create(1, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2744 "../../src/cpp_y.c"
    break;

  case 51:
#line 318 "cpp_y.y"
{
  yyval.pContext = adtCppRelationalExpression_create(0, yyvsp[0].pContext, 0);
}
#line 2752 "../../src/cpp_y.c"
    break;

  case 52:
#line 322 "cpp_y.y"
{
  yyval.pContext = adtCppRelationalExpression_create(0, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2760 "../../src/cpp_y.c"
    break;

  case 53:
#line 326 "cpp_y.y"
{
  yyval.pContext = adtCppRelationalExpression_create(1, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2768 "../../src/cpp_y.c"
    break;

  case 54:
#line 330 "cpp_y.y"
{
  yyval.pContext = adtCppRelationalExpression_create(2, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2776 "../../src/cpp_y.c"
    break;

  case 55:
#line 334 "cpp_y.y"
{
  yyval.pContext = adtCppRelationalExpression_create(3, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2784 "../../src/cpp_y.c"
    break;

  case 56:
#line 341 "cpp_y.y"
{
  yyval.pContext = adtCppEqualityExpression_create(0, yyvsp[0].pContext, 0);
}
#line 2792 "../../src/cpp_y.c"
    break;

  case 57:
#line 345 "cpp_y.y"
{
  yyval.pContext = adtCppEqualityExpression_create(0, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2800 "../../src/cpp_y.c"
    break;

  case 58:
#line 349 "cpp_y.y"
{
  yyval.pContext = adtCppEqualityExpression_create(1, yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2808 "../../src/cpp_y.c"
    break;

  case 59:
#line 356 "cpp_y.y"
{
  yyval.pContext = adtCppAndExpression_create(yyvsp[0].pContext, 0);
}
#line 2816 "../../src/cpp_y.c"
    break;

  case 60:
#line 360 "cpp_y.y"
{
  yyval.pContext = adtCppAndExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2824 "../../src/cpp_y.c"
    break;

  case 61:
#line 367 "cpp_y.y"
{
  yyval.pContext = adtCppExclusiveOrExpression_create(yyvsp[0].pContext, 0);
}
#line 2832 "../../src/cpp_y.c"
    break;

  case 62:
#line 371 "cpp_y.y"
{
  yyval.pContext = adtCppExclusiveOrExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2840 "../../src/cpp_y.c"
    break;

  case 63:
#line 378 "cpp_y.y"
{
  yyval.pContext = adtCppInclusiveOrExpression_create(yyvsp[0].pContext, 0);
}
#line 2848 "../../src/cpp_y.c"
    break;

  case 64:
#line 382 "cpp_y.y"
{
  yyval.pContext = adtCppInclusiveOrExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2856 "../../src/cpp_y.c"
    break;

  case 65:
#line 389 "cpp_y.y"
{
  yyval.pContext = adtCppLogicalAndExpression_create(yyvsp[0].pContext, 0);
}
#line 2864 "../../src/cpp_y.c"
    break;

  case 66:
#line 393 "cpp_y.y"
{
  yyval.pContext = adtCppLogicalAndExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2872 "../../src/cpp_y.c"
    break;

  case 67:
#line 400 "cpp_y.y"
{
  yyval.pContext = adtCppLogicalOrExpression_create(yyvsp[0].pContext, 0);
}
#line 2880 "../../src/cpp_y.c"
    break;

  case 68:
#line 404 "cpp_y.y"
{
  yyval.pContext = adtCppLogicalOrExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 2888 "../../src/cpp_y.c"
    break;

  case 69:
#line 411 "cpp_y.y"
{
  yyval.pContext = adtCppConditionalExpression_create(yyvsp[0].pContext, 0, 0);
}
#line 2896 "../../src/cpp_y.c"
    break;

  case 70:
#line 415 "cpp_y.y"
{
  yyval.pContext = adtCppConditionalExpression_create(yyvsp[-4].pContext, yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 2904 "../../src/cpp_y.c"
    break;

  case 71:
#line 422 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentExpression_create(yyvsp[0].pContext, 0, 0, 0);
}
#line 2912 "../../src/cpp_y.c"
    break;

  case 72:
#line 426 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentExpression_create(0, yyvsp[-2].pContext, yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 2920 "../../src/cpp_y.c"
    break;

  case 73:
#line 433 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(0);
}
#line 2928 "../../src/cpp_y.c"
    break;

  case 74:
#line 437 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(1);
}
#line 2936 "../../src/cpp_y.c"
    break;

  case 75:
#line 441 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(2);
}
#line 2944 "../../src/cpp_y.c"
    break;

  case 76:
#line 445 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(3);
}
#line 2952 "../../src/cpp_y.c"
    break;

  case 77:
#line 449 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(4);
}
#line 2960 "../../src/cpp_y.c"
    break;

  case 78:
#line 453 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(5);
}
#line 2968 "../../src/cpp_y.c"
    break;

  case 79:
#line 457 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(6);
}
#line 2976 "../../src/cpp_y.c"
    break;

  case 80:
#line 461 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(7);
}
#line 2984 "../../src/cpp_y.c"
    break;

  case 81:
#line 465 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(8);
}
#line 2992 "../../src/cpp_y.c"
    break;

  case 82:
#line 469 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(9);
}
#line 3000 "../../src/cpp_y.c"
    break;

  case 83:
#line 473 "cpp_y.y"
{
  yyval.pContext = adtCppAssignmentOperator_create(10);
}
#line 3008 "../../src/cpp_y.c"
    break;

  case 84:
#line 480 "cpp_y.y"
{
  yyval.pContext = adtCppExpression_create(yyvsp[0].pContext, 0);
}
#line 3016 "../../src/cpp_y.c"
    break;

  case 85:
#line 484 "cpp_y.y"
{
  yyval.pContext = adtCppExpression_create(yyvsp[0].pContext, yyvsp[-2].pContext);
}
#line 3024 "../../src/cpp_y.c"
    break;

  case 86:
#line 491 "cpp_y.y"
{
  yyval.pContext = adtCppConstantExpression_create(yyvsp[0].pContext);
}
#line 3032 "../../src/cpp_y.c"
    break;

  case 87:
#line 498 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(yyvsp[0].pContext, 0, 0, 0, 0, 0, 0);
}
#line 3040 "../../src/cpp_y.c"
    break;

  case 88:
#line 502 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, yyvsp[0].pContext, 0, 0, 0, 0, 0);
}
#line 3048 "../../src/cpp_y.c"
    break;

  case 89:
#line 506 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, 0, yyvsp[0].pContext, 0, 0, 0, 0);
}
#line 3056 "../../src/cpp_y.c"
    break;

  case 90:
#line 510 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, 0, 0, yyvsp[0].pContext, 0, 0, 0);
}
#line 3064 "../../src/cpp_y.c"
    break;

  case 91:
#line 514 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, 0, 0, 0, yyvsp[0].pContext, 0, 0);
}
#line 3072 "../../src/cpp_y.c"
    break;

  case 92:
#line 518 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, 0, 0, 0, 0, yyvsp[0].pContext, 0);
}
#line 3080 "../../src/cpp_y.c"
    break;

  case 93:
#line 522 "cpp_y.y"
{
  yyval.pContext = adtCppStatement_create(0, 0, 0, 0, 0, 0, yyvsp[0].pContext);
}
#line 3088 "../../src/cpp_y.c"
    break;

  case 94:
#line 529 "cpp_y.y"
{
  yyval.pContext = adtCppLabeledStatement_create(0, yyvsp[0].pContext, yyvsp[-2].sValue, 0);
}
#line 3096 "../../src/cpp_y.c"
    break;

  case 95:
#line 533 "cpp_y.y"
{
  yyval.pContext = adtCppLabeledStatement_create(yyvsp[-2].pContext, yyvsp[0].pContext, 0, 0);
}
#line 3104 "../../src/cpp_y.c"
    break;

  case 96:
#line 537 "cpp_y.y"
{
  yyval.pContext = adtCppLabeledStatement_create(0, yyvsp[0].pContext, 0, 1);
}
#line 3112 "../../src/cpp_y.c"
    break;

  case 97:
#line 544 "cpp_y.y"
{
  yyval.pContext = adtCppExpressionStatement_create(0);
}
#line 3120 "../../src/cpp_y.c"
    break;

  case 98:
#line 548 "cpp_y.y"
{
  yyval.pContext = adtCppExpressionStatement_create(yyvsp[-1].pContext);
}
#line 3128 "../../src/cpp_y.c"
    break;

  case 99:
#line 555 "cpp_y.y"
{
  yyval.pContext = adtCppCompoundStatement_create(0);
}
#line 3136 "../../src/cpp_y.c"
    break;

  case 100:
#line 559 "cpp_y.y"
{
  yyval.pContext = adtCppCompoundStatement_create(yyvsp[-1].pContext);
}
#line 3144 "../../src/cpp_y.c"
    break;

  case 101:
#line 566 "cpp_y.y"
{
  yyval.pContext = adtCppStatementSeq_create(yyvsp[0].pContext);
}
#line 3152 "../../src/cpp_y.c"
    break;

  case 102:
#line 570 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 3160 "../../src/cpp_y.c"
    break;

  case 103:
#line 581 "cpp_y.y"
{
  yyval.pContext = adtCppSelectionStatement_create(yyvsp[-2].pContext, yyvsp[0].pContext, 0, 1);
}
#line 3168 "../../src/cpp_y.c"
    break;

  case 104:
#line 585 "cpp_y.y"
{
  yyval.pContext = adtCppSelectionStatement_create(yyvsp[-4].pContext, yyvsp[-2].pContext, yyvsp[0].pContext, 1);
}
#line 3176 "../../src/cpp_y.c"
    break;

  case 105:
#line 589 "cpp_y.y"
{
  yyval.pContext = adtCppSelectionStatement_create(yyvsp[-2].pContext, yyvsp[0].pContext, 0, 0);
}
#line 3184 "../../src/cpp_y.c"
    break;

  case 106:
#line 596 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(0, yyvsp[-2].pContext, 0, yyvsp[0].pContext, 0);
}
#line 3192 "../../src/cpp_y.c"
    break;

  case 107:
#line 600 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(0, yyvsp[-2].pContext, 0, yyvsp[-5].pContext, 1);
}
#line 3200 "../../src/cpp_y.c"
    break;

  case 108:
#line 604 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(yyvsp[-3].pContext, 0, 0, yyvsp[0].pContext, 0);
}
#line 3208 "../../src/cpp_y.c"
    break;

  case 109:
#line 608 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(yyvsp[-4].pContext, 0, yyvsp[-2].pContext, yyvsp[0].pContext, 0);
}
#line 3216 "../../src/cpp_y.c"
    break;

  case 110:
#line 612 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(yyvsp[-4].pContext, yyvsp[-3].pContext, 0, yyvsp[0].pContext, 0);
}
#line 3224 "../../src/cpp_y.c"
    break;

  case 111:
#line 616 "cpp_y.y"
{
  yyval.pContext = adtCppIterationStatement_create(yyvsp[-5].pContext, yyvsp[-4].pContext, yyvsp[-2].pContext, yyvsp[0].pContext, 0);
}
#line 3232 "../../src/cpp_y.c"
    break;

  case 112:
#line 623 "cpp_y.y"
{
  yyval.pContext = adtCppForInitStatement_create(yyvsp[0].pContext, 0);
}
#line 3240 "../../src/cpp_y.c"
    break;

  case 113:
#line 627 "cpp_y.y"
{
  yyval.pContext = adtCppForInitStatement_create(0, yyvsp[0].pContext);
}
#line 3248 "../../src/cpp_y.c"
    break;

  case 114:
#line 634 "cpp_y.y"
{
  yyval.pContext = adtCppJumpStatement_create(0, 0, 0);
}
#line 3256 "../../src/cpp_y.c"
    break;

  case 115:
#line 638 "cpp_y.y"
{
  yyval.pContext = adtCppJumpStatement_create(0, 0, 1);
}
#line 3264 "../../src/cpp_y.c"
    break;

  case 116:
#line 642 "cpp_y.y"
{
  yyval.pContext = adtCppJumpStatement_create(0, 0, 2);
}
#line 3272 "../../src/cpp_y.c"
    break;

  case 117:
#line 646 "cpp_y.y"
{
  yyval.pContext = adtCppJumpStatement_create(yyvsp[-1].pContext, 0, 2);
}
#line 3280 "../../src/cpp_y.c"
    break;

  case 118:
#line 650 "cpp_y.y"
{
  yyval.pContext = adtCppJumpStatement_create(0, yyvsp[-1].sValue, 3);
}
#line 3288 "../../src/cpp_y.c"
    break;

  case 119:
#line 657 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarationStatement_create(yyvsp[0].pContext);
}
#line 3296 "../../src/cpp_y.c"
    break;

  case 120:
#line 664 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarationSeq_create(yyvsp[0].pContext);
}
#line 3304 "../../src/cpp_y.c"
    break;

  case 121:
#line 668 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 3312 "../../src/cpp_y.c"
    break;

  case 122:
#line 675 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaration_create(yyvsp[0].pContext, 0, 0, 0);
}
#line 3320 "../../src/cpp_y.c"
    break;

  case 123:
#line 679 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaration_create(0, yyvsp[0].pContext, 0, 0);
}
#line 3328 "../../src/cpp_y.c"
    break;

  case 124:
#line 683 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaration_create(0, 0, yyvsp[0].pContext, 0);
}
#line 3336 "../../src/cpp_y.c"
    break;

  case 125:
#line 687 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaration_create(0, 0, 0, yyvsp[0].pContext);
}
#line 3344 "../../src/cpp_y.c"
    break;

  case 126:
#line 691 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaration_create(0, 0, 0, 0);
}
#line 3352 "../../src/cpp_y.c"
    break;

  case 127:
#line 698 "cpp_y.y"
{
  yyval.pContext = adtCppBlockDeclaration_create(yyvsp[0].pContext, 0, 0, 0, 0);
}
#line 3360 "../../src/cpp_y.c"
    break;

  case 128:
#line 702 "cpp_y.y"
{
  yyval.pContext = adtCppBlockDeclaration_create(0, yyvsp[0].pContext, 0, 0, 0);
}
#line 3368 "../../src/cpp_y.c"
    break;

  case 129:
#line 706 "cpp_y.y"
{
  yyval.pContext = adtCppBlockDeclaration_create(0, 0, yyvsp[0].pContext, 0, 0);
}
#line 3376 "../../src/cpp_y.c"
    break;

  case 130:
#line 710 "cpp_y.y"
{
  yyval.pContext = adtCppBlockDeclaration_create(0, 0, 0, yyvsp[0].pContext, 0);
}
#line 3384 "../../src/cpp_y.c"
    break;

  case 131:
#line 714 "cpp_y.y"
{
  yyval.pContext = adtCppBlockDeclaration_create(0, 0, 0, 0, yyvsp[0].pContext);
}
#line 3392 "../../src/cpp_y.c"
    break;

  case 132:
#line 721 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleDeclaration_create(yyvsp[-1].pContext, 0, 0, 0, 0, 0);
}
#line 3400 "../../src/cpp_y.c"
    break;

  case 133:
#line 725 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleDeclaration_create(0, yyvsp[-1].pContext, 0, 0, 0, 0);
}
#line 3408 "../../src/cpp_y.c"
    break;

  case 134:
#line 729 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleDeclaration_create(0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0);
}
#line 3416 "../../src/cpp_y.c"
    break;

  case 135:
#line 733 "cpp_y.y"
{
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 1);

  yyval.pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3432 "../../src/cpp_y.c"
    break;

  case 136:
#line 745 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleDeclaration_create(0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, yyvsp[-3].pContext, 0);
}
#line 3440 "../../src/cpp_y.c"
    break;

  case 137:
#line 749 "cpp_y.y"
{
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, yyvsp[-3].pContext, 1);

  yyval.pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
#line 3456 "../../src/cpp_y.c"
    break;

  case 138:
#line 764 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(0);
}
#line 3464 "../../src/cpp_y.c"
    break;

  case 139:
#line 768 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(1);
}
#line 3472 "../../src/cpp_y.c"
    break;

  case 140:
#line 772 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(2);
}
#line 3480 "../../src/cpp_y.c"
    break;

  case 141:
#line 776 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(3);
}
#line 3488 "../../src/cpp_y.c"
    break;

  case 142:
#line 780 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(4);
}
#line 3496 "../../src/cpp_y.c"
    break;

  case 143:
#line 784 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(5);
}
#line 3504 "../../src/cpp_y.c"
    break;

  case 144:
#line 788 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(6);
}
#line 3512 "../../src/cpp_y.c"
    break;

  case 145:
#line 792 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(7);
}
#line 3520 "../../src/cpp_y.c"
    break;

  case 146:
#line 796 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(8);
}
#line 3528 "../../src/cpp_y.c"
    break;

  case 147:
#line 800 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(9);
}
#line 3536 "../../src/cpp_y.c"
    break;

  case 148:
#line 804 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifier_create(10);
}
#line 3544 "../../src/cpp_y.c"
    break;

  case 149:
#line 811 "cpp_y.y"
{
  yyval.pContext = adtCppDeclModifierList_create(yyvsp[0].pContext);
}
#line 3552 "../../src/cpp_y.c"
    break;

  case 150:
#line 815 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 3560 "../../src/cpp_y.c"
    break;

  case 151:
#line 822 "cpp_y.y"
{
  scopeManager_popScope(adtCpp_ScopeManager);

  yyval.pContext = adtCppClassSpecifier_create(yyvsp[0].pContext, 0, 0, 0);
}
#line 3570 "../../src/cpp_y.c"
    break;

  case 152:
#line 828 "cpp_y.y"
{
  scopeManager_popScope(adtCpp_ScopeManager);

  yyval.pContext = adtCppClassSpecifier_create(yyvsp[-2].pContext, 0, 0, 1);
}
#line 3580 "../../src/cpp_y.c"
    break;

  case 153:
#line 834 "cpp_y.y"
{
  scopeManager_popScope(adtCpp_ScopeManager);

  yyval.pContext = adtCppClassSpecifier_create(yyvsp[-3].pContext, 0, yyvsp[-1].pContext, 1);
}
#line 3590 "../../src/cpp_y.c"
    break;

  case 154:
#line 840 "cpp_y.y"
{
  scopeManager_popScope(adtCpp_ScopeManager);

  yyval.pContext = adtCppClassSpecifier_create(yyvsp[-4].pContext, yyvsp[-2].pContext, 0, 1);
}
#line 3600 "../../src/cpp_y.c"
    break;

  case 155:
#line 846 "cpp_y.y"
{
  scopeManager_popScope(adtCpp_ScopeManager);

  yyval.pContext = adtCppClassSpecifier_create(yyvsp[-5].pContext, yyvsp[-3].pContext, yyvsp[-1].pContext, 1);
}
#line 3610 "../../src/cpp_y.c"
    break;

  case 156:
#line 855 "cpp_y.y"
{
  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppEnumSpecifierName_create(yyvsp[0].sValue, 0);
}
#line 3620 "../../src/cpp_y.c"
    break;

  case 157:
#line 861 "cpp_y.y"
{
  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppEnumSpecifierName_create(yyvsp[0].sValue, 1);
}
#line 3630 "../../src/cpp_y.c"
    break;

  case 158:
#line 867 "cpp_y.y"
{
  yyval.pContext = adtCppEnumSpecifierName_create(yyvsp[0].sValue, 0);
}
#line 3638 "../../src/cpp_y.c"
    break;

  case 159:
#line 871 "cpp_y.y"
{
  yyval.pContext = adtCppEnumSpecifierName_create(yyvsp[0].sValue, 1);
}
#line 3646 "../../src/cpp_y.c"
    break;

  case 160:
#line 878 "cpp_y.y"
{
  yyval.pContext = adtCppEnumSpecifier_create(0, yyvsp[0].pContext, 0);
}
#line 3654 "../../src/cpp_y.c"
    break;

  case 161:
#line 882 "cpp_y.y"
{
  yyval.pContext = adtCppEnumSpecifier_create(0, yyvsp[-2].pContext, 1);
}
#line 3662 "../../src/cpp_y.c"
    break;

  case 162:
#line 886 "cpp_y.y"
{
  yyval.pContext = adtCppEnumSpecifier_create(yyvsp[-1].pContext, yyvsp[-3].pContext, 1);
}
#line 3670 "../../src/cpp_y.c"
    break;

  case 163:
#line 900 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(yyvsp[0].sValue, 0, 0);
}
#line 3678 "../../src/cpp_y.c"
    break;

  case 164:
#line 904 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(yyvsp[0].sValue, 1, 0);
}
#line 3686 "../../src/cpp_y.c"
    break;

  case 165:
#line 908 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 2, 0);
}
#line 3694 "../../src/cpp_y.c"
    break;

  case 166:
#line 912 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 3, 0);
}
#line 3702 "../../src/cpp_y.c"
    break;

  case 167:
#line 916 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 4, 0);
}
#line 3710 "../../src/cpp_y.c"
    break;

  case 168:
#line 920 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 5, 0);
}
#line 3718 "../../src/cpp_y.c"
    break;

  case 169:
#line 924 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 6, 0);
}
#line 3726 "../../src/cpp_y.c"
    break;

  case 170:
#line 928 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 7, 0);
}
#line 3734 "../../src/cpp_y.c"
    break;

  case 171:
#line 932 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 8, 0);
}
#line 3742 "../../src/cpp_y.c"
    break;

  case 172:
#line 936 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 9, 0);
}
#line 3750 "../../src/cpp_y.c"
    break;

  case 173:
#line 940 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 10, 0);
}
#line 3758 "../../src/cpp_y.c"
    break;

  case 174:
#line 944 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 11, 0);
}
#line 3766 "../../src/cpp_y.c"
    break;

  case 175:
#line 948 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 12, 0);
}
#line 3774 "../../src/cpp_y.c"
    break;

  case 176:
#line 952 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 13, 0);
}
#line 3782 "../../src/cpp_y.c"
    break;

  case 177:
#line 956 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 14, 0);
}
#line 3790 "../../src/cpp_y.c"
    break;

  case 178:
#line 960 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 15, 0);
}
#line 3798 "../../src/cpp_y.c"
    break;

  case 179:
#line 964 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 16, 0);
}
#line 3806 "../../src/cpp_y.c"
    break;

  case 180:
#line 968 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 17, 0);
}
#line 3814 "../../src/cpp_y.c"
    break;

  case 181:
#line 972 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 18, 0);
}
#line 3822 "../../src/cpp_y.c"
    break;

  case 182:
#line 976 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 19, 0);
}
#line 3830 "../../src/cpp_y.c"
    break;

  case 183:
#line 980 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 20, 0);
}
#line 3838 "../../src/cpp_y.c"
    break;

  case 184:
#line 984 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 21, 0);
}
#line 3846 "../../src/cpp_y.c"
    break;

  case 185:
#line 988 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 22, 0);
}
#line 3854 "../../src/cpp_y.c"
    break;

  case 186:
#line 992 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 23, 0);
}
#line 3862 "../../src/cpp_y.c"
    break;

  case 187:
#line 996 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 24, 0);
}
#line 3870 "../../src/cpp_y.c"
    break;

  case 188:
#line 1000 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 25, 0);
}
#line 3878 "../../src/cpp_y.c"
    break;

  case 189:
#line 1004 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 26, 0);
}
#line 3886 "../../src/cpp_y.c"
    break;

  case 190:
#line 1008 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 27, 0);
}
#line 3894 "../../src/cpp_y.c"
    break;

  case 191:
#line 1012 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 28, 0);
}
#line 3902 "../../src/cpp_y.c"
    break;

  case 192:
#line 1016 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 29, 0);
}
#line 3910 "../../src/cpp_y.c"
    break;

  case 193:
#line 1020 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 30, 0);
}
#line 3918 "../../src/cpp_y.c"
    break;

  case 194:
#line 1024 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 31, 0);
}
#line 3926 "../../src/cpp_y.c"
    break;

  case 195:
#line 1028 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(yyvsp[-1].sValue, 0, 1);
}
#line 3934 "../../src/cpp_y.c"
    break;

  case 196:
#line 1032 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(yyvsp[-1].sValue, 1, 1);
}
#line 3942 "../../src/cpp_y.c"
    break;

  case 197:
#line 1036 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 2, 1);
}
#line 3950 "../../src/cpp_y.c"
    break;

  case 198:
#line 1040 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 3, 1);
}
#line 3958 "../../src/cpp_y.c"
    break;

  case 199:
#line 1044 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 4, 1);
}
#line 3966 "../../src/cpp_y.c"
    break;

  case 200:
#line 1048 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 5, 1);
}
#line 3974 "../../src/cpp_y.c"
    break;

  case 201:
#line 1052 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 6, 1);
}
#line 3982 "../../src/cpp_y.c"
    break;

  case 202:
#line 1056 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 7, 1);
}
#line 3990 "../../src/cpp_y.c"
    break;

  case 203:
#line 1060 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 8, 1);
}
#line 3998 "../../src/cpp_y.c"
    break;

  case 204:
#line 1064 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 9, 1);
}
#line 4006 "../../src/cpp_y.c"
    break;

  case 205:
#line 1068 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 10, 1);
}
#line 4014 "../../src/cpp_y.c"
    break;

  case 206:
#line 1072 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 11, 1);
}
#line 4022 "../../src/cpp_y.c"
    break;

  case 207:
#line 1076 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 12, 1);
}
#line 4030 "../../src/cpp_y.c"
    break;

  case 208:
#line 1080 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 13, 1);
}
#line 4038 "../../src/cpp_y.c"
    break;

  case 209:
#line 1084 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 14, 1);
}
#line 4046 "../../src/cpp_y.c"
    break;

  case 210:
#line 1088 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 15, 1);
}
#line 4054 "../../src/cpp_y.c"
    break;

  case 211:
#line 1092 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 16, 1);
}
#line 4062 "../../src/cpp_y.c"
    break;

  case 212:
#line 1096 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 17, 1);
}
#line 4070 "../../src/cpp_y.c"
    break;

  case 213:
#line 1100 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 18, 1);
}
#line 4078 "../../src/cpp_y.c"
    break;

  case 214:
#line 1104 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 19, 1);
}
#line 4086 "../../src/cpp_y.c"
    break;

  case 215:
#line 1108 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 20, 1);
}
#line 4094 "../../src/cpp_y.c"
    break;

  case 216:
#line 1112 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 21, 1);
}
#line 4102 "../../src/cpp_y.c"
    break;

  case 217:
#line 1116 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 22, 1);
}
#line 4110 "../../src/cpp_y.c"
    break;

  case 218:
#line 1120 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 23, 1);
}
#line 4118 "../../src/cpp_y.c"
    break;

  case 219:
#line 1124 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 24, 1);
}
#line 4126 "../../src/cpp_y.c"
    break;

  case 220:
#line 1128 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 25, 1);
}
#line 4134 "../../src/cpp_y.c"
    break;

  case 221:
#line 1132 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 26, 1);
}
#line 4142 "../../src/cpp_y.c"
    break;

  case 222:
#line 1136 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 27, 1);
}
#line 4150 "../../src/cpp_y.c"
    break;

  case 223:
#line 1140 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 28, 1);
}
#line 4158 "../../src/cpp_y.c"
    break;

  case 224:
#line 1144 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 29, 1);
}
#line 4166 "../../src/cpp_y.c"
    break;

  case 225:
#line 1148 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 30, 1);
}
#line 4174 "../../src/cpp_y.c"
    break;

  case 226:
#line 1152 "cpp_y.y"
{
  yyval.pContext = adtCppSimpleTypeSpecifier_create(0, 31, 1);
}
#line 4182 "../../src/cpp_y.c"
    break;

  case 227:
#line 1159 "cpp_y.y"
{
  yyval.pContext = adtCppEnumeratorList_create(yyvsp[0].pContext);
}
#line 4190 "../../src/cpp_y.c"
    break;

  case 228:
#line 1163 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4198 "../../src/cpp_y.c"
    break;

  case 229:
#line 1170 "cpp_y.y"
{
  yyval.pContext = adtCppEnumeratorDefinition_create(0, yyvsp[0].sValue);
}
#line 4206 "../../src/cpp_y.c"
    break;

  case 230:
#line 1174 "cpp_y.y"
{
  yyval.pContext = adtCppEnumeratorDefinition_create(yyvsp[0].pContext, yyvsp[-2].sValue);
}
#line 4214 "../../src/cpp_y.c"
    break;

  case 231:
#line 1181 "cpp_y.y"
{
  yyval.pContext = adtCppNamespaceDefinition_create(yyvsp[-1].pContext, yyvsp[-3].sValue);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4224 "../../src/cpp_y.c"
    break;

  case 232:
#line 1187 "cpp_y.y"
{
  yyval.pContext = adtCppNamespaceDefinition_create(yyvsp[-1].pContext, 0);
}
#line 4232 "../../src/cpp_y.c"
    break;

  case 233:
#line 1194 "cpp_y.y"
{
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);

  yyval.sValue = yyvsp[0].sValue;
}
#line 4242 "../../src/cpp_y.c"
    break;

  case 234:
#line 1202 "cpp_y.y"
{
  yyval.pContext = adtCppNamespaceAliasDefinition_create(yyvsp[-3].sValue, yyvsp[-1].sValue);
}
#line 4250 "../../src/cpp_y.c"
    break;

  case 235:
#line 1209 "cpp_y.y"
{
  yyval.pContext = adtCppUsingDeclaration_create(yyvsp[-1].sValue, 0);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, yyvsp[-1].sValue);
}
#line 4260 "../../src/cpp_y.c"
    break;

  case 236:
#line 1215 "cpp_y.y"
{
  yyval.pContext = adtCppUsingDeclaration_create(yyvsp[-1].sValue, 1);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, yyvsp[-1].sValue);
}
#line 4270 "../../src/cpp_y.c"
    break;

  case 237:
#line 1224 "cpp_y.y"
{
  yyval.pContext = adtCppUsingDirective_create(yyvsp[-1].sValue, 0);

  scopeManager_addUsing(adtCpp_ScopeManager, yyvsp[-1].sValue);
}
#line 4280 "../../src/cpp_y.c"
    break;

  case 238:
#line 1230 "cpp_y.y"
{
  yyval.pContext = adtCppUsingDirective_create(yyvsp[-1].sValue, 1);

  scopeManager_addUsing(adtCpp_ScopeManager, yyvsp[-1].sValue);
}
#line 4290 "../../src/cpp_y.c"
    break;

  case 239:
#line 1239 "cpp_y.y"
{
  yyval.pContext = adtCppAsmDefinition_create(yyvsp[-2].sValue);
}
#line 4298 "../../src/cpp_y.c"
    break;

  case 240:
#line 1246 "cpp_y.y"
{
  yyval.pContext = adtCppLinkageSpecification_create(0, 0, yyvsp[-2].sValue);
}
#line 4306 "../../src/cpp_y.c"
    break;

  case 241:
#line 1250 "cpp_y.y"
{
  yyval.pContext = adtCppLinkageSpecification_create(yyvsp[-1].pContext, 0, yyvsp[-3].sValue);
}
#line 4314 "../../src/cpp_y.c"
    break;

  case 242:
#line 1254 "cpp_y.y"
{
  yyval.pContext = adtCppLinkageSpecification_create(0, yyvsp[0].pContext, yyvsp[-1].sValue);
}
#line 4322 "../../src/cpp_y.c"
    break;

  case 243:
#line 1261 "cpp_y.y"
{
  yyval.pContext = adtCppInitDeclaratorList_create(yyvsp[0].pContext);
}
#line 4330 "../../src/cpp_y.c"
    break;

  case 244:
#line 1265 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4338 "../../src/cpp_y.c"
    break;

  case 245:
#line 1272 "cpp_y.y"
{
  yyval.pContext = adtCppInitDeclarator_create(yyvsp[0].pContext, 0);
}
#line 4346 "../../src/cpp_y.c"
    break;

  case 246:
#line 1276 "cpp_y.y"
{
  yyval.pContext = adtCppInitDeclarator_create(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 4354 "../../src/cpp_y.c"
    break;

  case 247:
#line 1285 "cpp_y.y"
{
  yyval.pContext = yyvsp[0].pContext;
}
#line 4362 "../../src/cpp_y.c"
    break;

  case 248:
#line 1289 "cpp_y.y"
{
  yyval.pContext = yyvsp[0].pContext;
}
#line 4370 "../../src/cpp_y.c"
    break;

  case 249:
#line 1296 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, yyvsp[0].sValue, 0, 0, 0, 0, 0, 1);
}
#line 4378 "../../src/cpp_y.c"
    break;

  case 250:
#line 1300 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, yyvsp[0].sValue, 0, 0, 1, 0, 0, 0);
}
#line 4386 "../../src/cpp_y.c"
    break;

  case 251:
#line 1304 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, yyvsp[0].sValue, 0, 1, 0, 0, 0, 1);
}
#line 4394 "../../src/cpp_y.c"
    break;

  case 252:
#line 1308 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, yyvsp[0].sValue, 0, 1, 1, 0, 0, 0);
}
#line 4402 "../../src/cpp_y.c"
    break;

  case 253:
#line 1312 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, yyvsp[0].pContext, yyvsp[-1].sValue, 0, 0, 0, 0, 0, 1);
}
#line 4410 "../../src/cpp_y.c"
    break;

  case 254:
#line 1316 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, yyvsp[0].pContext, yyvsp[-1].sValue, 0, 1, 0, 0, 0, 1);
}
#line 4418 "../../src/cpp_y.c"
    break;

  case 255:
#line 1346 "cpp_y.y"
{
 yyval.pContext = yyvsp[0].pContext;
}
#line 4426 "../../src/cpp_y.c"
    break;

  case 256:
#line 1353 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4439 "../../src/cpp_y.c"
    break;

  case 257:
#line 1362 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4452 "../../src/cpp_y.c"
    break;

  case 258:
#line 1371 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4465 "../../src/cpp_y.c"
    break;

  case 259:
#line 1380 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4478 "../../src/cpp_y.c"
    break;

  case 260:
#line 1389 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4491 "../../src/cpp_y.c"
    break;

  case 261:
#line 1398 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4504 "../../src/cpp_y.c"
    break;

  case 262:
#line 1407 "cpp_y.y"
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, yyvsp[-1].sValue, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 1;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4517 "../../src/cpp_y.c"
    break;

  case 263:
#line 1419 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4527 "../../src/cpp_y.c"
    break;

  case 264:
#line 1425 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4537 "../../src/cpp_y.c"
    break;

  case 265:
#line 1431 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4547 "../../src/cpp_y.c"
    break;

  case 266:
#line 1437 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(yyvsp[-1].pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4557 "../../src/cpp_y.c"
    break;

  case 267:
#line 1443 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(yyvsp[-2].pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4567 "../../src/cpp_y.c"
    break;

  case 268:
#line 1449 "cpp_y.y"
{
  yyval.pContext = adtCppDeclarator_create(yyvsp[-2].pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4577 "../../src/cpp_y.c"
    break;

  case 269:
#line 1458 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorDims_create(0, 0);
}
#line 4585 "../../src/cpp_y.c"
    break;

  case 270:
#line 1462 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorDims_create(yyvsp[-1].pContext, 0);
}
#line 4593 "../../src/cpp_y.c"
    break;

  case 271:
#line 1466 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorDims_create(0, yyvsp[-2].pContext);
}
#line 4601 "../../src/cpp_y.c"
    break;

  case 272:
#line 1470 "cpp_y.y"
{
  yyval.pContext = adtCppDeclaratorDims_create(yyvsp[-1].pContext, yyvsp[-3].pContext);
}
#line 4609 "../../src/cpp_y.c"
    break;

  case 273:
#line 1477 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclarationClause_create(0, 1, 0);
}
#line 4617 "../../src/cpp_y.c"
    break;

  case 274:
#line 1481 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclarationClause_create(yyvsp[0].pContext, 0, 0);
}
#line 4625 "../../src/cpp_y.c"
    break;

  case 275:
#line 1485 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclarationClause_create(yyvsp[-1].pContext, 1, 0);
}
#line 4633 "../../src/cpp_y.c"
    break;

  case 276:
#line 1489 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclarationClause_create(yyvsp[-2].pContext, 1, 1);
}
#line 4641 "../../src/cpp_y.c"
    break;

  case 277:
#line 1496 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclarationList_create(yyvsp[0].pContext);
}
#line 4649 "../../src/cpp_y.c"
    break;

  case 278:
#line 1500 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4657 "../../src/cpp_y.c"
    break;

  case 279:
#line 1507 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(0, yyvsp[-1].pContext, yyvsp[0].pContext, 0);
}
#line 4665 "../../src/cpp_y.c"
    break;

  case 280:
#line 1511 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(yyvsp[-2].pContext, yyvsp[-1].pContext, yyvsp[0].pContext, 0);
}
#line 4673 "../../src/cpp_y.c"
    break;

  case 281:
#line 1515 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(0, yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4681 "../../src/cpp_y.c"
    break;

  case 282:
#line 1519 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(yyvsp[-4].pContext, yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4689 "../../src/cpp_y.c"
    break;

  case 283:
#line 1523 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(0, yyvsp[0].pContext, 0, 0);
}
#line 4697 "../../src/cpp_y.c"
    break;

  case 284:
#line 1527 "cpp_y.y"
{
  yyval.pContext = adtCppParameterDeclaration_create(yyvsp[-1].pContext, yyvsp[0].pContext, 0, 0);
}
#line 4705 "../../src/cpp_y.c"
    break;

  case 285:
#line 1534 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4713 "../../src/cpp_y.c"
    break;

  case 286:
#line 1538 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4721 "../../src/cpp_y.c"
    break;

  case 287:
#line 1542 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4729 "../../src/cpp_y.c"
    break;

  case 288:
#line 1546 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-1].pContext, 0, yyvsp[0].pContext, 0);
}
#line 4737 "../../src/cpp_y.c"
    break;

  case 289:
#line 1550 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, yyvsp[0].pContext, 0);
}
#line 4745 "../../src/cpp_y.c"
    break;

  case 290:
#line 1554 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, yyvsp[0].pContext, 0);
}
#line 4753 "../../src/cpp_y.c"
    break;

  case 291:
#line 1558 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, yyvsp[0].pContext, 0);
}
#line 4761 "../../src/cpp_y.c"
    break;

  case 292:
#line 1565 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4769 "../../src/cpp_y.c"
    break;

  case 293:
#line 1569 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4777 "../../src/cpp_y.c"
    break;

  case 294:
#line 1573 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 1);
}
#line 4785 "../../src/cpp_y.c"
    break;

  case 295:
#line 1577 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-2].pContext, 0, yyvsp[-1].pContext, 1);
}
#line 4793 "../../src/cpp_y.c"
    break;

  case 296:
#line 1581 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, 0, yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[-1].pContext, 1);
}
#line 4801 "../../src/cpp_y.c"
    break;

  case 297:
#line 1585 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(0, yyvsp[-3].pContext, yyvsp[-2].pContext, 0, yyvsp[-1].pContext, 1);
}
#line 4809 "../../src/cpp_y.c"
    break;

  case 298:
#line 1589 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionDefinition_create(yyvsp[-4].pContext, yyvsp[-3].pContext, yyvsp[-2].pContext, 0, yyvsp[-1].pContext, 1);
}
#line 4817 "../../src/cpp_y.c"
    break;

  case 299:
#line 1599 "cpp_y.y"
{
  yyval.pContext = adtCppFunctionBody_create(yyvsp[0].pContext);
}
#line 4825 "../../src/cpp_y.c"
    break;

  case 300:
#line 1606 "cpp_y.y"
{
  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
#line 4833 "../../src/cpp_y.c"
    break;

  case 301:
#line 1613 "cpp_y.y"
{
  yyval.pContext = adtCppCompoundStatement_create(0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4843 "../../src/cpp_y.c"
    break;

  case 302:
#line 1619 "cpp_y.y"
{
  yyval.pContext = adtCppCompoundStatement_create(yyvsp[-1].pContext);

  scopeManager_popScope(adtCpp_ScopeManager);
}
#line 4853 "../../src/cpp_y.c"
    break;

  case 303:
#line 1628 "cpp_y.y"
{
  yyval.pContext = adtCppInitializer_create(yyvsp[0].pContext, 0);
}
#line 4861 "../../src/cpp_y.c"
    break;

  case 304:
#line 1632 "cpp_y.y"
{
  yyval.pContext = adtCppInitializer_create(0, yyvsp[-1].pContext);
}
#line 4869 "../../src/cpp_y.c"
    break;

  case 305:
#line 1639 "cpp_y.y"
{
  yyval.pContext = adtCppInitializerClause_create(yyvsp[0].pContext, 0, 0);
}
#line 4877 "../../src/cpp_y.c"
    break;

  case 306:
#line 1643 "cpp_y.y"
{
  yyval.pContext = adtCppInitializerClause_create(0, yyvsp[-1].pContext, 0);
}
#line 4885 "../../src/cpp_y.c"
    break;

  case 307:
#line 1647 "cpp_y.y"
{
  yyval.pContext = adtCppInitializerClause_create(0, yyvsp[-2].pContext, 1);
}
#line 4893 "../../src/cpp_y.c"
    break;

  case 308:
#line 1651 "cpp_y.y"
{
  yyval.pContext = adtCppInitializerClause_create(0, 0, 0);
}
#line 4901 "../../src/cpp_y.c"
    break;

  case 309:
#line 1658 "cpp_y.y"
{
  yyval.pContext = adtCppInitializerList_create(yyvsp[0].pContext);
}
#line 4909 "../../src/cpp_y.c"
    break;

  case 310:
#line 1662 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 4917 "../../src/cpp_y.c"
    break;

  case 311:
#line 1669 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(0, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4928 "../../src/cpp_y.c"
    break;

  case 312:
#line 1676 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(0, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4939 "../../src/cpp_y.c"
    break;

  case 313:
#line 1683 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(0, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4950 "../../src/cpp_y.c"
    break;

  case 314:
#line 1690 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(0, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4961 "../../src/cpp_y.c"
    break;

  case 315:
#line 1697 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(1, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4972 "../../src/cpp_y.c"
    break;

  case 316:
#line 1704 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(1, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4983 "../../src/cpp_y.c"
    break;

  case 317:
#line 1711 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(1, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 4994 "../../src/cpp_y.c"
    break;

  case 318:
#line 1718 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(1, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 5005 "../../src/cpp_y.c"
    break;

  case 319:
#line 1725 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(2, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 5016 "../../src/cpp_y.c"
    break;

  case 320:
#line 1732 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(2, yyvsp[0].sValue, 0);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 5027 "../../src/cpp_y.c"
    break;

  case 321:
#line 1739 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(2, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 5038 "../../src/cpp_y.c"
    break;

  case 322:
#line 1746 "cpp_y.y"
{
  yyval.pContext = adtCppClassKey_create(2, yyvsp[0].sValue, 1);

  scopeManager_addType(adtCpp_ScopeManager, yyvsp[0].sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, yyvsp[0].sValue, 0);
}
#line 5049 "../../src/cpp_y.c"
    break;

  case 323:
#line 1756 "cpp_y.y"
{
  yyval.pContext = adtCppMemberSpecification_create(yyvsp[0].pContext);
}
#line 5057 "../../src/cpp_y.c"
    break;

  case 324:
#line 1760 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-1].pContext, yyvsp[0].pContext);
}
#line 5065 "../../src/cpp_y.c"
    break;

  case 325:
#line 1767 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 0, 1);
}
#line 5073 "../../src/cpp_y.c"
    break;

  case 326:
#line 1771 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, yyvsp[-3].pContext, yyvsp[-2].pContext, yyvsp[-1].pContext, 0, 0, 0, 1);
}
#line 5081 "../../src/cpp_y.c"
    break;

  case 327:
#line 1775 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, yyvsp[0].pContext, 0, 0, 0);
}
#line 5089 "../../src/cpp_y.c"
    break;

  case 328:
#line 1779 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, yyvsp[0].pContext, 0, 0);
}
#line 5097 "../../src/cpp_y.c"
    break;

  case 329:
#line 1783 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(yyvsp[-1].pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
#line 5105 "../../src/cpp_y.c"
    break;

  case 330:
#line 1787 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, yyvsp[-1].pContext, 0, 0, 0, 0, 0, 0, 1);
}
#line 5113 "../../src/cpp_y.c"
    break;

  case 331:
#line 1791 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
#line 5121 "../../src/cpp_y.c"
    break;

  case 332:
#line 1795 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 2, 0);
}
#line 5129 "../../src/cpp_y.c"
    break;

  case 333:
#line 1799 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 3, 0);
}
#line 5137 "../../src/cpp_y.c"
    break;

  case 334:
#line 1806 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclarationList_create(yyvsp[0].pContext);
}
#line 5145 "../../src/cpp_y.c"
    break;

  case 335:
#line 1810 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 5153 "../../src/cpp_y.c"
    break;

  case 336:
#line 1817 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclarator_create(yyvsp[0].pContext, 0);
}
#line 5161 "../../src/cpp_y.c"
    break;

  case 337:
#line 1821 "cpp_y.y"
{
  yyval.pContext = adtCppMemberDeclarator_create(yyvsp[-2].pContext, yyvsp[0].sValue);
}
#line 5169 "../../src/cpp_y.c"
    break;

  case 338:
#line 1828 "cpp_y.y"
{
  yyval.pContext = adtCppBaseSpecifierList_create(yyvsp[0].pContext);
}
#line 5177 "../../src/cpp_y.c"
    break;

  case 339:
#line 1832 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 5185 "../../src/cpp_y.c"
    break;

  case 340:
#line 1839 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(0, 0, 0, yyvsp[0].sValue);
}
#line 5195 "../../src/cpp_y.c"
    break;

  case 341:
#line 1845 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 0, 0, yyvsp[0].sValue);
}
#line 5205 "../../src/cpp_y.c"
    break;

  case 342:
#line 1851 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 0, 0, yyvsp[0].sValue);
}
#line 5215 "../../src/cpp_y.c"
    break;

  case 343:
#line 1857 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 0, 0, yyvsp[0].sValue);
}
#line 5225 "../../src/cpp_y.c"
    break;

  case 344:
#line 1863 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(0, 0, 1, yyvsp[0].sValue);
}
#line 5235 "../../src/cpp_y.c"
    break;

  case 345:
#line 1869 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 0, 1, yyvsp[0].sValue);
}
#line 5245 "../../src/cpp_y.c"
    break;

  case 346:
#line 1875 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 0, 1, yyvsp[0].sValue);
}
#line 5255 "../../src/cpp_y.c"
    break;

  case 347:
#line 1881 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 0, 1, yyvsp[0].sValue);
}
#line 5265 "../../src/cpp_y.c"
    break;

  case 348:
#line 1887 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(0, 1, 0, yyvsp[0].sValue);
}
#line 5275 "../../src/cpp_y.c"
    break;

  case 349:
#line 1893 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 1, 0, yyvsp[0].sValue);
}
#line 5285 "../../src/cpp_y.c"
    break;

  case 350:
#line 1899 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 1, 0, yyvsp[0].sValue);
}
#line 5295 "../../src/cpp_y.c"
    break;

  case 351:
#line 1905 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 1, 0, yyvsp[0].sValue);
}
#line 5305 "../../src/cpp_y.c"
    break;

  case 352:
#line 1911 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(0, 1, 1, yyvsp[0].sValue);
}
#line 5315 "../../src/cpp_y.c"
    break;

  case 353:
#line 1917 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 1, 1, yyvsp[0].sValue);
}
#line 5325 "../../src/cpp_y.c"
    break;

  case 354:
#line 1923 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 1, 1, yyvsp[0].sValue);
}
#line 5335 "../../src/cpp_y.c"
    break;

  case 355:
#line 1929 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 1, 1, yyvsp[0].sValue);
}
#line 5345 "../../src/cpp_y.c"
    break;

  case 356:
#line 1935 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 1, 0, yyvsp[0].sValue);
}
#line 5355 "../../src/cpp_y.c"
    break;

  case 357:
#line 1941 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 1, 0, yyvsp[0].sValue);
}
#line 5365 "../../src/cpp_y.c"
    break;

  case 358:
#line 1947 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 1, 0, yyvsp[0].sValue);
}
#line 5375 "../../src/cpp_y.c"
    break;

  case 359:
#line 1953 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(1, 1, 1, yyvsp[0].sValue);
}
#line 5385 "../../src/cpp_y.c"
    break;

  case 360:
#line 1959 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(2, 1, 1, yyvsp[0].sValue);
}
#line 5395 "../../src/cpp_y.c"
    break;

  case 361:
#line 1965 "cpp_y.y"
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, yyvsp[0].sValue);

  yyval.pContext = adtCppBaseSpecifier_create(3, 1, 1, yyvsp[0].sValue);
}
#line 5405 "../../src/cpp_y.c"
    break;

  case 362:
#line 1974 "cpp_y.y"
{
  yyval.pContext = adtCppCtorInitializer_create(yyvsp[0].pContext);
}
#line 5413 "../../src/cpp_y.c"
    break;

  case 363:
#line 1981 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializerList_create(yyvsp[0].pContext);
}
#line 5421 "../../src/cpp_y.c"
    break;

  case 364:
#line 1985 "cpp_y.y"
{
  yyval.pContext = adtCppList_add(yyvsp[-2].pContext, yyvsp[0].pContext);
}
#line 5429 "../../src/cpp_y.c"
    break;

  case 365:
#line 1992 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializer_create(yyvsp[-2].pContext, 0);
}
#line 5437 "../../src/cpp_y.c"
    break;

  case 366:
#line 1996 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializer_create(yyvsp[-3].pContext, yyvsp[-1].pContext);
}
#line 5445 "../../src/cpp_y.c"
    break;

  case 367:
#line 2003 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializerId_create(0, yyvsp[0].sValue);
}
#line 5453 "../../src/cpp_y.c"
    break;

  case 368:
#line 2007 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializerId_create(1, yyvsp[0].sValue);
}
#line 5461 "../../src/cpp_y.c"
    break;

  case 369:
#line 2011 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializerId_create(0, yyvsp[0].sValue);
}
#line 5469 "../../src/cpp_y.c"
    break;

  case 370:
#line 2015 "cpp_y.y"
{
  yyval.pContext = adtCppMemInitializerId_create(1, yyvsp[0].sValue);
}
#line 5477 "../../src/cpp_y.c"
    break;


#line 5481 "../../src/cpp_y.c"

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
#line 2021 "cpp_y.y"

