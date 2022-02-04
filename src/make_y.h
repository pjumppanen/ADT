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

#ifndef YY_YY_______SRC_MAKE_Y_H_INCLUDED
# define YY_YY_______SRC_MAKE_Y_H_INCLUDED
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
    M_AD = 258,
    M_BEGIN = 259,
    M_BOUNDS = 260,
    M_CHECK = 261,
    M_END = 262,
    M_SOURCE = 263,
    M_OUTPUT = 264,
    M_FILE = 265,
    M_FILES = 266,
    M_WORKING = 267,
    M_DIRECTORY = 268,
    M_FUNCTION = 269,
    M_VAR = 270,
    M_OUTVAR = 271,
    M_MODE = 272,
    M_USER = 273,
    M_PRAGMAS = 274,
    M_PATHS = 275,
    M_CLASS = 276,
    M_OPTIONS = 277,
    M_PASCAL = 278,
    M_CPP = 279,
    M_FORTRAN = 280,
    M_INCLUDE = 281,
    M_SWITCHES = 282,
    M_BLACKBOX = 283,
    M_PRE = 284,
    M_POST = 285,
    M_COMMA = 286,
    M_SEMICOLON = 287,
    M_COLON = 288,
    M_EQUALS = 289,
    M_LBRACKET = 290,
    M_RBRACKET = 291,
    M_TEXT = 292,
    M_FILENAME = 293,
    M_IDENT = 294,
    M_SINGLELINE_COMMENT = 295,
    M_MULTILINE_COMMENT = 296
  };
#endif
/* Tokens.  */
#define M_AD 258
#define M_BEGIN 259
#define M_BOUNDS 260
#define M_CHECK 261
#define M_END 262
#define M_SOURCE 263
#define M_OUTPUT 264
#define M_FILE 265
#define M_FILES 266
#define M_WORKING 267
#define M_DIRECTORY 268
#define M_FUNCTION 269
#define M_VAR 270
#define M_OUTVAR 271
#define M_MODE 272
#define M_USER 273
#define M_PRAGMAS 274
#define M_PATHS 275
#define M_CLASS 276
#define M_OPTIONS 277
#define M_PASCAL 278
#define M_CPP 279
#define M_FORTRAN 280
#define M_INCLUDE 281
#define M_SWITCHES 282
#define M_BLACKBOX 283
#define M_PRE 284
#define M_POST 285
#define M_COMMA 286
#define M_SEMICOLON 287
#define M_COLON 288
#define M_EQUALS 289
#define M_LBRACKET 290
#define M_RBRACKET 291
#define M_TEXT 292
#define M_FILENAME 293
#define M_IDENT 294
#define M_SINGLELINE_COMMENT 295
#define M_MULTILINE_COMMENT 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_______SRC_MAKE_Y_H_INCLUDED  */
