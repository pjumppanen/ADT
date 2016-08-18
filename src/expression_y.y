%{
/*
 * expression_y.y
 *
 *  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
 *  ORGANISATION (CSIRO), Australia.
 *  All rights reserved.
 *
 *  This file is part of ADT.  The full ADT copyright notice, including
 *  terms governing use, modification, and redistribution, is contained in
 *  the file COPYING. COPYING can be found at the root of the source code
 *  distribution tree;
 *
 * Expression parser grammar for Auto-differentiation utility. This parses
 * simple mathmatical expressions like A + (C * 3 - B) etc. for use in
 * automatic initialisation code generation of arrays and the like. We need
 * to be able to parse the array sizes specified in comment fields which
 * can be complex expressions.
 *
 */

#include <stdio.h>
#include "lexer.h"
#include "adtexpression.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr    stdout

#define YYSTYPE   expressionType

%}

/* expression keyword tokens */
%token LPARENTHESIS RPARENTHESIS PLUS MINUS MULTIPLY DIVIDE IDENTIFIER NUMBER
%token LT GT SLBRACKET SRBRACKET COMMA


%%
ExpressionAdditive
 : ExpressionMultiplicative
{
  $$.pContext = adtExpressionAdditive_create(0, $1.pContext, 0);
}
 | ExpressionAdditive PLUS ExpressionMultiplicative
{
  $$.pContext = adtExpressionAdditive_create($1.pContext, $3.pContext, 1);
}
 | ExpressionAdditive MINUS ExpressionMultiplicative
{
  $$.pContext = adtExpressionAdditive_create($1.pContext, $3.pContext, 2);
}
;

ExpressionMultiplicative
 : ExpressionUnary
{
  $$.pContext = adtExpressionMultiplicative_create(0, $1.pContext, 0);
}
 | ExpressionMultiplicative MULTIPLY ExpressionUnary
{
  $$.pContext = adtExpressionMultiplicative_create($1.pContext, $3.pContext, 1);
}
 | ExpressionMultiplicative DIVIDE ExpressionUnary
{
  $$.pContext = adtExpressionMultiplicative_create($1.pContext, $3.pContext, 2);
}
;

ExpressionUnary
 : ExpressionPostfix
{
  $$.pContext = adtExpressionUnary_create($1.pContext, 0);
}
 | PLUS ExpressionPostfix
{
  $$.pContext = adtExpressionUnary_create($2.pContext, 1);
}
 | MINUS ExpressionPostfix
{
  $$.pContext = adtExpressionUnary_create($2.pContext, 2);
}
;

ExpressionPostfix
 : NUMBER
{
  $$.pContext = adtExpressionPostfix_create(0, 0, 0, $1.nValue, 0, 0);
}
 | IDENTIFIER
{
  $$.pContext = adtExpressionPostfix_create(0, 0, $1.sValue, 0, 0, 0);
}
 | IDENTIFIER SLBRACKET ExpressionIndexList SRBRACKET
{
  $$.pContext = adtExpressionPostfix_create(0, $3.pContext, $1.sValue, 0, 0, 0);
}
 | LPARENTHESIS ExpressionAdditive RPARENTHESIS
{
  $$.pContext = adtExpressionPostfix_create($2.pContext, 0, 0, 0, 0, 0);
}
;

ExpressionIndexList
 : ExpressionIndex
{
  $$.pContext = adtExpressionIndexList_create($1.pContext);
}
 | ExpressionIndexList COMMA ExpressionIndex
{
  $$.pContext = adtExpressionIndexList_add($1.pContext, $3.pContext);
}
;

ExpressionIndex
 : ExpressionIndexMultiplicative
{
  $$.pContext = adtExpressionAdditive_create(0, $1.pContext, 0);
}
 | ExpressionIndex PLUS ExpressionIndexMultiplicative
{
  $$.pContext = adtExpressionAdditive_create($1.pContext, $3.pContext, 1);
}
 | ExpressionIndex MINUS ExpressionIndexMultiplicative
{
  $$.pContext = adtExpressionAdditive_create($1.pContext, $3.pContext, 2);
}
;

ExpressionIndexMultiplicative
 : ExpressionIndexUnary
{
  $$.pContext = adtExpressionMultiplicative_create(0, $1.pContext, 0);
}
 | ExpressionIndexMultiplicative MULTIPLY ExpressionIndexUnary
{
  $$.pContext = adtExpressionMultiplicative_create($1.pContext, $3.pContext, 1);
}
 | ExpressionIndexMultiplicative DIVIDE ExpressionIndexUnary
{
  $$.pContext = adtExpressionMultiplicative_create($1.pContext, $3.pContext, 2);
}
;

ExpressionIndexUnary
 : ExpressionIndexPostfix
{
  $$.pContext = adtExpressionUnary_create($1.pContext, 0);
}
 | PLUS ExpressionIndexPostfix
{
  $$.pContext = adtExpressionUnary_create($2.pContext, 1);
}
 | MINUS ExpressionIndexPostfix
{
  $$.pContext = adtExpressionUnary_create($2.pContext, 2);
}
;

ExpressionIndexPostfix
 : NUMBER
{
  $$.pContext = adtExpressionPostfix_create(0, 0, 0, $1.nValue, 0, 0);
}
 | IDENTIFIER
{
  $$.pContext = adtExpressionPostfix_create(0, 0, $1.sValue, 0, 0, 0);
}
 | LPARENTHESIS ExpressionIndex RPARENTHESIS
{
  $$.pContext = adtExpressionPostfix_create($2.pContext, 0, 0, 0, 0, 0);
}
 | LT NUMBER GT
{
  $$.pContext = adtExpressionPostfix_create(0, 0, 0, $2.nValue, 1, 0);
}
 | LT MINUS NUMBER GT
{
  $$.pContext = adtExpressionPostfix_create(0, 0, 0, $3.nValue, 1, 1);
}
;
