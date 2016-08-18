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

#ifndef YY_YY_______SRC_FORTRAN_Y_H_INCLUDED
# define YY_YY_______SRC_FORTRAN_Y_H_INCLUDED
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
    COMMA = 260,
    COLON = 261,
    ASSIGN = 262,
    PLUS = 263,
    MINUS = 264,
    POWER = 265,
    MULTIPLY = 266,
    DIVIDE = 267,
    BOGUS = 268,
    LOGICAL_EQ = 269,
    LOGICAL_NE = 270,
    LOGICAL_LT = 271,
    LOGICAL_LE = 272,
    LOGICAL_GT = 273,
    LOGICAL_GE = 274,
    LOGICAL_NOT = 275,
    LOGICAL_AND = 276,
    LOGICAL_OR = 277,
    LOGICAL_EQUIV = 278,
    LOGICAL_NEQUIV = 279,
    EQUAL = 280,
    NEQUAL = 281,
    LT = 282,
    LE = 283,
    GT = 284,
    GE = 285,
    LOGICAL_TRUE = 286,
    LOGICAL_FALSE = 287,
    INTEGER = 288,
    UNSIGNED = 289,
    REAL = 290,
    DOUBLEPRECISION = 291,
    DOUBLE = 292,
    PRECISION = 293,
    COMPLEX = 294,
    LOGICAL = 295,
    CHARACTER = 296,
    DIMENSION = 297,
    END = 298,
    PARAMETER = 299,
    PRIVATE = 300,
    PROTECTED = 301,
    PUBLIC = 302,
    IMPLICIT = 303,
    NONE = 304,
    WHERE = 305,
    ELSEWHERE = 306,
    ENDWHERE = 307,
    GOTO = 308,
    IF = 309,
    THEN = 310,
    ELSEIF = 311,
    ELSE = 312,
    ENDIF = 313,
    SELECTCASE = 314,
    SELECT = 315,
    CASE = 316,
    ENDSELECT = 317,
    DEFAULT = 318,
    DO = 319,
    WHILE = 320,
    ENDDO = 321,
    CYCLE = 322,
    EXIT = 323,
    CONTINUE = 324,
    INTRINSIC = 325,
    MODULE = 326,
    ENDMODULE = 327,
    USE = 328,
    CALL = 329,
    RESULT = 330,
    FUNCTION = 331,
    RECURSIVE = 332,
    ENDFUNCTION = 333,
    SUBROUTINE = 334,
    ENDSUBROUTINE = 335,
    RETURN = 336,
    EXTERNAL = 337,
    PROGRAM = 338,
    XNAME = 339,
    XSCON = 340,
    XRCON = 341,
    XICON = 342,
    XRCON_S = 343,
    XICON_S = 344,
    XIMPL = 345,
    xEOS = 346,
    INTENT = 347,
    IN = 348,
    OUT = 349,
    INOUT = 350,
    COMMENT = 351,
    LINE_CONTINUATION = 352,
    CALL_EXPAND = 353,
    ADD_VARIABLES = 354,
    UNKNOWNTYPE = 355
  };
#endif
/* Tokens.  */
#define LBRACKET 258
#define RBRACKET 259
#define COMMA 260
#define COLON 261
#define ASSIGN 262
#define PLUS 263
#define MINUS 264
#define POWER 265
#define MULTIPLY 266
#define DIVIDE 267
#define BOGUS 268
#define LOGICAL_EQ 269
#define LOGICAL_NE 270
#define LOGICAL_LT 271
#define LOGICAL_LE 272
#define LOGICAL_GT 273
#define LOGICAL_GE 274
#define LOGICAL_NOT 275
#define LOGICAL_AND 276
#define LOGICAL_OR 277
#define LOGICAL_EQUIV 278
#define LOGICAL_NEQUIV 279
#define EQUAL 280
#define NEQUAL 281
#define LT 282
#define LE 283
#define GT 284
#define GE 285
#define LOGICAL_TRUE 286
#define LOGICAL_FALSE 287
#define INTEGER 288
#define UNSIGNED 289
#define REAL 290
#define DOUBLEPRECISION 291
#define DOUBLE 292
#define PRECISION 293
#define COMPLEX 294
#define LOGICAL 295
#define CHARACTER 296
#define DIMENSION 297
#define END 298
#define PARAMETER 299
#define PRIVATE 300
#define PROTECTED 301
#define PUBLIC 302
#define IMPLICIT 303
#define NONE 304
#define WHERE 305
#define ELSEWHERE 306
#define ENDWHERE 307
#define GOTO 308
#define IF 309
#define THEN 310
#define ELSEIF 311
#define ELSE 312
#define ENDIF 313
#define SELECTCASE 314
#define SELECT 315
#define CASE 316
#define ENDSELECT 317
#define DEFAULT 318
#define DO 319
#define WHILE 320
#define ENDDO 321
#define CYCLE 322
#define EXIT 323
#define CONTINUE 324
#define INTRINSIC 325
#define MODULE 326
#define ENDMODULE 327
#define USE 328
#define CALL 329
#define RESULT 330
#define FUNCTION 331
#define RECURSIVE 332
#define ENDFUNCTION 333
#define SUBROUTINE 334
#define ENDSUBROUTINE 335
#define RETURN 336
#define EXTERNAL 337
#define PROGRAM 338
#define XNAME 339
#define XSCON 340
#define XRCON 341
#define XICON 342
#define XRCON_S 343
#define XICON_S 344
#define XIMPL 345
#define xEOS 346
#define INTENT 347
#define IN 348
#define OUT 349
#define INOUT 350
#define COMMENT 351
#define LINE_CONTINUATION 352
#define CALL_EXPAND 353
#define ADD_VARIABLES 354
#define UNKNOWNTYPE 355

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_______SRC_FORTRAN_Y_H_INCLUDED  */
