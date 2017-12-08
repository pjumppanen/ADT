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

#ifndef YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED
# define YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    PLUS = 260,
    MINUS = 261,
    MULTIPLY = 262,
    DIVIDE = 263,
    POWER = 264,
    PERIOD = 265,
    IDENTIFIER = 266,
    NUMBER_FIXED = 267,
    NUMBER_FLOAT = 268,
    COMMA = 269,
    COLON = 270,
    SEMICOLON = 271,
    DERIV_OP = 272,
    BLACKBOX = 273,
    READ_NOT_WRITTEN = 274,
    NOT_READ_THEN_WRITTEN = 275,
    NOT_READ_NOT_WRITTEN = 276,
    READ_THEN_WRITTEN = 277,
    DEPS = 278,
    ID = 279,
    REAL = 280,
    INTEGER = 281,
    COMPLEX = 282,
    CHARACTER = 283,
    BOOLEAN = 284,
    REAL_ARRAY = 285,
    INTEGER_ARRAY = 286,
    COMPLEX_ARRAY = 287,
    CHARACTER_ARRAY = 288,
    BOOLEAN_ARRAY = 289,
    IN = 290,
    OUT = 291,
    F_BEGIN = 292,
    F_END = 293,
    FUNCTION = 294,
    PROCEDURE = 295,
    RESULT = 296
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

#endif /* !YY_YY_SRC_BLACK_BOX_Y_H_INCLUDED  */
