/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_______SRC_CPP_Y_H_INCLUDED
# define YY_YY_______SRC_CPP_Y_H_INCLUDED
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

#endif /* !YY_YY_______SRC_CPP_Y_H_INCLUDED  */
