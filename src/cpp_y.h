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

#endif /* !YY_YY_______SRC_CPP_Y_H_INCLUDED  */
