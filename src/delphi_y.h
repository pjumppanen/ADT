/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    OUTO = 319,
    OVERLOAD = 320,
    OVERRIDE = 321,
    PACKAGE = 322,
    PACKED = 323,
    PASCAL = 324,
    PCHAR = 325,
    PRIVATE = 326,
    PROCEDURE = 327,
    PROGRAM = 328,
    PROPERTY = 329,
    PROTECTED = 330,
    PUBLIC = 331,
    PUBLISHED = 332,
    READ = 333,
    REAL = 334,
    REAL48 = 335,
    RECORD = 336,
    REGISTER = 337,
    REINTRODUCE = 338,
    REPEAT = 339,
    REQUIRES = 340,
    SAFECALL = 341,
    SET = 342,
    SHL = 343,
    SHORTINT = 344,
    SHR = 345,
    SINGLE = 346,
    SIZEOF = 347,
    SMALLINT = 348,
    STDCALL = 349,
    STORED = 350,
    STRING = 351,
    THEN = 352,
    TO = 353,
    TYPE = 354,
    UNIT = 355,
    UNTIL = 356,
    USES = 357,
    VAR = 358,
    VARIANT = 359,
    VIRTUAL = 360,
    WHILE = 361,
    WIDECHAR = 362,
    WIDESTRING = 363,
    WITH = 364,
    WORD = 365,
    WRITE = 366,
    XOR = 367,
    EXIT = 368,
    POINTER = 369,
    COMMA = 370,
    SEMICOLON = 371,
    COLON = 372,
    ASSIGNMENT = 373,
    PLUS_EQUALS = 374,
    MINUS_EQUALS = 375,
    TIMES_EQUALS = 376,
    DIV_EQUALS = 377,
    EQUALS = 378,
    DOT = 379,
    RANGE = 380,
    LPARENTHESIS = 381,
    RPARENTHESIS = 382,
    LBRACKET = 383,
    RBRACKET = 384,
    AT = 385,
    HAT = 386,
    PLUS = 387,
    MINUS = 388,
    GT = 389,
    LT = 390,
    GE = 391,
    LE = 392,
    NE = 393,
    MULTIPLY = 394,
    DIVIDE = 395,
    IDENTIFIER = 396,
    BOOL_NUMBER = 397,
    INT_NUMBER = 398,
    REAL_NUMBER = 399,
    TEXT = 400,
    SINGLELINE_COMMENT = 401,
    MULTILINE_COMMENT = 402,
    EMBEDDED_COMMANDS = 403,
    ADDVARIABLES = 404
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
#define OUTO 319
#define OVERLOAD 320
#define OVERRIDE 321
#define PACKAGE 322
#define PACKED 323
#define PASCAL 324
#define PCHAR 325
#define PRIVATE 326
#define PROCEDURE 327
#define PROGRAM 328
#define PROPERTY 329
#define PROTECTED 330
#define PUBLIC 331
#define PUBLISHED 332
#define READ 333
#define REAL 334
#define REAL48 335
#define RECORD 336
#define REGISTER 337
#define REINTRODUCE 338
#define REPEAT 339
#define REQUIRES 340
#define SAFECALL 341
#define SET 342
#define SHL 343
#define SHORTINT 344
#define SHR 345
#define SINGLE 346
#define SIZEOF 347
#define SMALLINT 348
#define STDCALL 349
#define STORED 350
#define STRING 351
#define THEN 352
#define TO 353
#define TYPE 354
#define UNIT 355
#define UNTIL 356
#define USES 357
#define VAR 358
#define VARIANT 359
#define VIRTUAL 360
#define WHILE 361
#define WIDECHAR 362
#define WIDESTRING 363
#define WITH 364
#define WORD 365
#define WRITE 366
#define XOR 367
#define EXIT 368
#define POINTER 369
#define COMMA 370
#define SEMICOLON 371
#define COLON 372
#define ASSIGNMENT 373
#define PLUS_EQUALS 374
#define MINUS_EQUALS 375
#define TIMES_EQUALS 376
#define DIV_EQUALS 377
#define EQUALS 378
#define DOT 379
#define RANGE 380
#define LPARENTHESIS 381
#define RPARENTHESIS 382
#define LBRACKET 383
#define RBRACKET 384
#define AT 385
#define HAT 386
#define PLUS 387
#define MINUS 388
#define GT 389
#define LT 390
#define GE 391
#define LE 392
#define NE 393
#define MULTIPLY 394
#define DIVIDE 395
#define IDENTIFIER 396
#define BOOL_NUMBER 397
#define INT_NUMBER 398
#define REAL_NUMBER 399
#define TEXT 400
#define SINGLELINE_COMMENT 401
#define MULTILINE_COMMENT 402
#define EMBEDDED_COMMANDS 403
#define ADDVARIABLES 404

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_______SRC_DELPHI_Y_H_INCLUDED  */
