/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_MAKE_Y_H_INCLUDED
# define YY_YY_SRC_MAKE_Y_H_INCLUDED
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MAKE_Y_H_INCLUDED  */
