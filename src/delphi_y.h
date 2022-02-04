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

#ifndef YY_YY_______SRC_DELPHI_Y_H_INCLUDED
# define YY_YY_______SRC_DELPHI_Y_H_INCLUDED
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
    LONGBOOL = 265,
    BYTE = 266,
    CASE = 267,
    CDECL = 268,
    CHAR = 269,
    CLASS = 270,
    COMP = 271,
    CONST = 272,
    CONSTRUCTOR = 273,
    CONTAINS = 274,
    CURRENCY = 275,
    DEFAULT = 276,
    DESTRUCTOR = 277,
    DIV = 278,
    DO = 279,
    DOUBLE = 280,
    DOWNTO = 281,
    DYNAMIC = 282,
    ELSE = 283,
    B_END = 284,
    EXPORT = 285,
    EXTENDED = 286,
    EXTERNAL = 287,
    FAR = 288,
    P_FILE = 289,
    FINALIZATION = 290,
    FOR = 291,
    FORWARD = 292,
    FUNCTION = 293,
    GOTO = 294,
    IF = 295,
    IMPLEMENTATION = 296,
    IMPLEMENTS = 297,
    IN = 298,
    INDEX = 299,
    INHERITED = 300,
    INITIALIZATION = 301,
    INT64 = 302,
    INTEGER = 303,
    INTERFACE = 304,
    IS = 305,
    LABEL = 306,
    LIBRARY = 307,
    LONGINT = 308,
    LONGWORD = 309,
    MESSAGE = 310,
    MOD = 311,
    NIL = 312,
    NODEFAULT = 313,
    NOT = 314,
    OBJECT = 315,
    OF = 316,
    OLEVARIANT = 317,
    OR = 318,
    OUT = 319,
    OUTO = 320,
    OVERLOAD = 321,
    OVERRIDE = 322,
    PACKAGE = 323,
    PACKED = 324,
    PASCAL = 325,
    PCHAR = 326,
    PRIVATE = 327,
    PROCEDURE = 328,
    PROGRAM = 329,
    PROPERTY = 330,
    PROTECTED = 331,
    PUBLIC = 332,
    PUBLISHED = 333,
    READ = 334,
    REAL = 335,
    REAL48 = 336,
    RECORD = 337,
    REGISTER = 338,
    REINTRODUCE = 339,
    REPEAT = 340,
    REQUIRES = 341,
    SAFECALL = 342,
    SET = 343,
    SHL = 344,
    SHORTINT = 345,
    SHR = 346,
    SINGLE = 347,
    SIZEOF = 348,
    SMALLINT = 349,
    STDCALL = 350,
    STORED = 351,
    STRING = 352,
    THEN = 353,
    TO = 354,
    TYPE = 355,
    UNIT = 356,
    UNTIL = 357,
    USES = 358,
    VAR = 359,
    VARIANT = 360,
    VIRTUAL = 361,
    WHILE = 362,
    WIDECHAR = 363,
    WIDESTRING = 364,
    WITH = 365,
    WORD = 366,
    WRITE = 367,
    XOR = 368,
    EXIT = 369,
    POINTER = 370,
    COMMA = 371,
    SEMICOLON = 372,
    COLON = 373,
    ASSIGNMENT = 374,
    PLUS_EQUALS = 375,
    MINUS_EQUALS = 376,
    TIMES_EQUALS = 377,
    DIV_EQUALS = 378,
    EQUALS = 379,
    DOT = 380,
    RANGE = 381,
    LPARENTHESIS = 382,
    RPARENTHESIS = 383,
    LBRACKET = 384,
    RBRACKET = 385,
    AT = 386,
    HAT = 387,
    PLUS = 388,
    MINUS = 389,
    GT = 390,
    LT = 391,
    GE = 392,
    LE = 393,
    NE = 394,
    MULTIPLY = 395,
    DIVIDE = 396,
    IDENTIFIER = 397,
    BOOL_NUMBER = 398,
    INT_NUMBER = 399,
    REAL_NUMBER = 400,
    TEXT = 401,
    SINGLELINE_COMMENT = 402,
    MULTILINE_COMMENT = 403,
    EMBEDDED_COMMANDS = 404,
    ADDVARIABLES = 405
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
#define LONGBOOL 265
#define BYTE 266
#define CASE 267
#define CDECL 268
#define CHAR 269
#define CLASS 270
#define COMP 271
#define CONST 272
#define CONSTRUCTOR 273
#define CONTAINS 274
#define CURRENCY 275
#define DEFAULT 276
#define DESTRUCTOR 277
#define DIV 278
#define DO 279
#define DOUBLE 280
#define DOWNTO 281
#define DYNAMIC 282
#define ELSE 283
#define B_END 284
#define EXPORT 285
#define EXTENDED 286
#define EXTERNAL 287
#define FAR 288
#define P_FILE 289
#define FINALIZATION 290
#define FOR 291
#define FORWARD 292
#define FUNCTION 293
#define GOTO 294
#define IF 295
#define IMPLEMENTATION 296
#define IMPLEMENTS 297
#define IN 298
#define INDEX 299
#define INHERITED 300
#define INITIALIZATION 301
#define INT64 302
#define INTEGER 303
#define INTERFACE 304
#define IS 305
#define LABEL 306
#define LIBRARY 307
#define LONGINT 308
#define LONGWORD 309
#define MESSAGE 310
#define MOD 311
#define NIL 312
#define NODEFAULT 313
#define NOT 314
#define OBJECT 315
#define OF 316
#define OLEVARIANT 317
#define OR 318
#define OUT 319
#define OUTO 320
#define OVERLOAD 321
#define OVERRIDE 322
#define PACKAGE 323
#define PACKED 324
#define PASCAL 325
#define PCHAR 326
#define PRIVATE 327
#define PROCEDURE 328
#define PROGRAM 329
#define PROPERTY 330
#define PROTECTED 331
#define PUBLIC 332
#define PUBLISHED 333
#define READ 334
#define REAL 335
#define REAL48 336
#define RECORD 337
#define REGISTER 338
#define REINTRODUCE 339
#define REPEAT 340
#define REQUIRES 341
#define SAFECALL 342
#define SET 343
#define SHL 344
#define SHORTINT 345
#define SHR 346
#define SINGLE 347
#define SIZEOF 348
#define SMALLINT 349
#define STDCALL 350
#define STORED 351
#define STRING 352
#define THEN 353
#define TO 354
#define TYPE 355
#define UNIT 356
#define UNTIL 357
#define USES 358
#define VAR 359
#define VARIANT 360
#define VIRTUAL 361
#define WHILE 362
#define WIDECHAR 363
#define WIDESTRING 364
#define WITH 365
#define WORD 366
#define WRITE 367
#define XOR 368
#define EXIT 369
#define POINTER 370
#define COMMA 371
#define SEMICOLON 372
#define COLON 373
#define ASSIGNMENT 374
#define PLUS_EQUALS 375
#define MINUS_EQUALS 376
#define TIMES_EQUALS 377
#define DIV_EQUALS 378
#define EQUALS 379
#define DOT 380
#define RANGE 381
#define LPARENTHESIS 382
#define RPARENTHESIS 383
#define LBRACKET 384
#define RBRACKET 385
#define AT 386
#define HAT 387
#define PLUS 388
#define MINUS 389
#define GT 390
#define LT 391
#define GE 392
#define LE 393
#define NE 394
#define MULTIPLY 395
#define DIVIDE 396
#define IDENTIFIER 397
#define BOOL_NUMBER 398
#define INT_NUMBER 399
#define REAL_NUMBER 400
#define TEXT 401
#define SINGLELINE_COMMENT 402
#define MULTILINE_COMMENT 403
#define EMBEDDED_COMMANDS 404
#define ADDVARIABLES 405

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_______SRC_DELPHI_Y_H_INCLUDED  */
