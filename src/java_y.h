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

#ifndef YY_YY_SRC_JAVA_Y_H_INCLUDED
# define YY_YY_SRC_JAVA_Y_H_INCLUDED
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_JAVA_Y_H_INCLUDED  */
