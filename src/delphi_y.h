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

#endif /* !YY_YY_______SRC_DELPHI_Y_H_INCLUDED  */
