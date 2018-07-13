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
    PLUS = 260,
    MINUS = 261,
    MULTIPLY = 262,
    DIVIDE = 263,
    POWER = 264,
    PERIOD = 265,
    IDENTIFIER = 266,
    QUALIFIED_IDENTIFIER = 267,
    NUMBER_FIXED = 268,
    NUMBER_FLOAT = 269,
    COMMA = 270,
    COLON = 271,
    SEMICOLON = 272,
    DERIV_OP = 273,
    BLACKBOX = 274,
    READ_NOT_WRITTEN = 275,
    NOT_READ_THEN_WRITTEN = 276,
    NOT_READ_NOT_WRITTEN = 277,
    READ_THEN_WRITTEN = 278,
    DEPS = 279,
    ID = 280,
    REAL = 281,
    INTEGER = 282,
    COMPLEX = 283,
    CHARACTER = 284,
    BOOLEAN = 285,
    REAL_ARRAY = 286,
    INTEGER_ARRAY = 287,
    COMPLEX_ARRAY = 288,
    CHARACTER_ARRAY = 289,
    BOOLEAN_ARRAY = 290,
    IN = 291,
    OUT = 292,
    F_BEGIN = 293,
    F_END = 294,
    FUNCTION = 295,
    PROCEDURE = 296,
    RESULT = 297,
    BB_BEGIN = 298,
    BB_END = 299
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
