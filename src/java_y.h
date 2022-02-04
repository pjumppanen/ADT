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

#ifndef YY_YY_______SRC_JAVA_Y_H_INCLUDED
# define YY_YY_______SRC_JAVA_Y_H_INCLUDED
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
    ABSTRACT = 258,
    AND = 259,
    AND_EQUALS = 260,
    BOOL = 261,
    BOOLEAN = 262,
    BOOLEANLITERAL = 263,
    BREAK = 264,
    BYTE = 265,
    CASE = 266,
    CATCH = 267,
    CHAR = 268,
    CHARACTERLITERAL = 269,
    CLASS = 270,
    COLON = 271,
    COMMA = 272,
    CONST = 273,
    CONTINUE = 274,
    DECR = 275,
    DEFAULT = 276,
    DIV = 277,
    DIV_EQUALS = 278,
    DO = 279,
    DOUBLE = 280,
    ELSE = 281,
    EQ = 282,
    EQUALS = 283,
    EXTENDS = 284,
    FINAL = 285,
    FINALLY = 286,
    FLOAT = 287,
    FLOATINGPOINTLITERAL = 288,
    FOR = 289,
    GT = 290,
    GTE = 291,
    IDENTIFIER = 292,
    IF = 293,
    IMPLEMENTS = 294,
    IMPORT = 295,
    INCR = 296,
    INSTANCEOF = 297,
    INT = 298,
    INTEGERLITERAL = 299,
    INTERFACE = 300,
    LAND = 301,
    LBRACKET = 302,
    LCBRACKET = 303,
    LNOT = 304,
    LONG = 305,
    LOR = 306,
    LSQRBRACKET = 307,
    LT = 308,
    LTE = 309,
    MINUS = 310,
    MINUS_EQUALS = 311,
    MOD = 312,
    MOD_EQUALS = 313,
    MULTIPLY = 314,
    NATIVE = 315,
    NE = 316,
    NEW = 317,
    NOT = 318,
    NULLLITERAL = 319,
    OR = 320,
    OR_EQUALS = 321,
    PACKAGE = 322,
    PERIOD = 323,
    PLUS = 324,
    PLUS_EQUALS = 325,
    PRIVATE = 326,
    PROTECTED = 327,
    PUBLIC = 328,
    QUESTION = 329,
    RBRACKET = 330,
    RCBRACKET = 331,
    RETURN = 332,
    RSQRBRACKET = 333,
    SAL = 334,
    SAL_EQUALS = 335,
    SAR = 336,
    SAR_EQUALS = 337,
    SEMICOLON = 338,
    SHORT = 339,
    SHR = 340,
    SHR_EQUALS = 341,
    STATIC = 342,
    STRINGLITERAL = 343,
    SUPER = 344,
    SWITCH = 345,
    SYNCHRONIZED = 346,
    THIS = 347,
    THROW = 348,
    THROWS = 349,
    TIMES_EQUALS = 350,
    TRANSIENT = 351,
    TRY = 352,
    VOID = 353,
    VOLATILE = 354,
    WHILE = 355,
    XOR = 356,
    XOR_EQUALS = 357,
    SCOPE = 358,
    SINGLELINE_COMMENT = 359,
    MULTILINE_COMMENT = 360,
    EMBEDDED_COMMANDS = 361
  };
#endif
/* Tokens.  */
#define ABSTRACT 258
#define AND 259
#define AND_EQUALS 260
#define BOOL 261
#define BOOLEAN 262
#define BOOLEANLITERAL 263
#define BREAK 264
#define BYTE 265
#define CASE 266
#define CATCH 267
#define CHAR 268
#define CHARACTERLITERAL 269
#define CLASS 270
#define COLON 271
#define COMMA 272
#define CONST 273
#define CONTINUE 274
#define DECR 275
#define DEFAULT 276
#define DIV 277
#define DIV_EQUALS 278
#define DO 279
#define DOUBLE 280
#define ELSE 281
#define EQ 282
#define EQUALS 283
#define EXTENDS 284
#define FINAL 285
#define FINALLY 286
#define FLOAT 287
#define FLOATINGPOINTLITERAL 288
#define FOR 289
#define GT 290
#define GTE 291
#define IDENTIFIER 292
#define IF 293
#define IMPLEMENTS 294
#define IMPORT 295
#define INCR 296
#define INSTANCEOF 297
#define INT 298
#define INTEGERLITERAL 299
#define INTERFACE 300
#define LAND 301
#define LBRACKET 302
#define LCBRACKET 303
#define LNOT 304
#define LONG 305
#define LOR 306
#define LSQRBRACKET 307
#define LT 308
#define LTE 309
#define MINUS 310
#define MINUS_EQUALS 311
#define MOD 312
#define MOD_EQUALS 313
#define MULTIPLY 314
#define NATIVE 315
#define NE 316
#define NEW 317
#define NOT 318
#define NULLLITERAL 319
#define OR 320
#define OR_EQUALS 321
#define PACKAGE 322
#define PERIOD 323
#define PLUS 324
#define PLUS_EQUALS 325
#define PRIVATE 326
#define PROTECTED 327
#define PUBLIC 328
#define QUESTION 329
#define RBRACKET 330
#define RCBRACKET 331
#define RETURN 332
#define RSQRBRACKET 333
#define SAL 334
#define SAL_EQUALS 335
#define SAR 336
#define SAR_EQUALS 337
#define SEMICOLON 338
#define SHORT 339
#define SHR 340
#define SHR_EQUALS 341
#define STATIC 342
#define STRINGLITERAL 343
#define SUPER 344
#define SWITCH 345
#define SYNCHRONIZED 346
#define THIS 347
#define THROW 348
#define THROWS 349
#define TIMES_EQUALS 350
#define TRANSIENT 351
#define TRY 352
#define VOID 353
#define VOLATILE 354
#define WHILE 355
#define XOR 356
#define XOR_EQUALS 357
#define SCOPE 358
#define SINGLELINE_COMMENT 359
#define MULTILINE_COMMENT 360
#define EMBEDDED_COMMANDS 361

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_______SRC_JAVA_Y_H_INCLUDED  */
