%{
/*
 * black_box_y.y
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
 * black box parser grammar for Auto-differentiation utility. This parses
 * black box definitions for functions that are not to be differentiated
 * with ADT. These definitions are provided by our own simplfied syntax
 * and then translated into a form that tapenade understands. For example,
 * this is a definition in a Pascal comment field:
 *
 * {D/D(.) INV(X+Y),
 *  D/D(X) .*X,
 *  D/D(Y) .*(1/Y);}
 *
 * You can also include a black box dependency specification with, for example,
 *
 * {BLACKBOX ReadNotWritten:(1,0,0) NotReadThenWritten:(0,1,0) deps:(1,0,0,id,id);}
 *
 *
 * For stand alone black box definition files you can have something like,
 *   MyFunction(X : real_array in, Y : real_array in) : real_array
 *   begin
 *     D/D(.) INV(X+Y),
 *     D/D(X) .*X,
 *     D/D(Y) .*(1/Y);
 *   end;
 */

#include <stdio.h>
#include "lexer.h"
#include "adtblackbox.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr    stdout

#define YYSTYPE   blackBoxType


typedef struct blackBoxDefBeginInfo
{
  const char*   pIdentifier;
  void*         pArgDefList;
  int           nArgType;

} blackBoxDefBeginInfo;


%}


/* expression keyword tokens */
%token LBRACKET RBRACKET PLUS MINUS MULTIPLY DIVIDE POWER PERIOD IDENTIFIER
%token NUMBER_FIXED NUMBER_FLOAT COMMA COLON SEMICOLON DERIV_OP BLACKBOX
%token READ_NOT_WRITTEN NOT_READ_THEN_WRITTEN NOT_READ_NOT_WRITTEN
%token READ_THEN_WRITTEN DEPS ID
%token REAL INTEGER COMPLEX CHARACTER BOOLEAN
%token REAL_ARRAY INTEGER_ARRAY COMPLEX_ARRAY CHARACTER_ARRAY BOOLEAN_ARRAY
%token IN OUT F_BEGIN F_END FUNCTION PROCEDURE RESULT


%%
root : derivativeList
{
  adtBlackBox_SetRoot($1.pContext);
}
;

derivativeList
 : derivative
{
  $$.pContext = adtBlackBoxDerivativeList_create($1.pContext);
}
 | derivativeList derivative
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $2.pContext);
}
;

derivative
 : DERIV_OP LBRACKET PERIOD RBRACKET exprAdditive COMMA derivativeExtendedList SEMICOLON
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* multi-part derivative def */
  $$.pContext = adtBlackBoxDerivative_create(0, $5.pContext, $7.pContext, 0, 0, 0, 0);
}
 | DERIV_OP LBRACKET IDENTIFIER RBRACKET exprAdditive SEMICOLON
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* complete derivative def */
  $$.pContext = adtBlackBoxDerivative_create($3.sValue, $5.pContext, 0, 0, 0, 0, 0);
}
 | DERIV_OP LBRACKET PERIOD RBRACKET
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* null derivative def */
  $$.pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 1, 0);
}
 | BLACKBOX blackBoxSpecList SEMICOLON
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  $$.pContext = adtBlackBoxDerivative_create(0, 0, 0, $2.pContext, 0, 0, 0);
}
 | BLACKBOX SEMICOLON
{
  if ((yyBlackBoxIsFile != 0) && (yyBlackBoxReentrancyCount == 0))
  {
    yyBlackBoxerror("Stand-alone black box definitions must be in a function or procedure definition.");
    YYERROR;
  }

  /* black box def */
  $$.pContext = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, 0);
}
 | defBegin defEnd
{
  if (yyBlackBoxIsFile != 0)
  {
    /* stand alone black box def */
    if (yyBlackBoxReentrancyCount > 0)
    {
      yyBlackBoxerror("Nested stand-alone black box definitions not allowed.");
      YYERROR;
    }
    else
    {
      void*                         pBlackBoxDef;
      struct blackBoxDefBeginInfo*  pInfo;

      pInfo         = (struct blackBoxDefBeginInfo*)$1.pContext;
      pBlackBoxDef  = adtBlackBoxStandAloneDef_create(pInfo->pIdentifier, pInfo->pArgDefList, pInfo->nArgType, $2.pContext);
      $$.pContext   = adtBlackBoxDerivative_create(0, 0, 0, 0, 0, 0, pBlackBoxDef);
    }
  }
  else
  {
    yyBlackBoxerror("Stand-alone black box definitions not allowed in comment fields.");
    YYERROR;
  }
}
;

defBegin
 : PROCEDURE IDENTIFIER LBRACKET argDefList RBRACKET F_BEGIN
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = $2.sValue;
  Info.pArgDefList  = $4.pContext;
  Info.nArgType     = -1;

  $$.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
 | FUNCTION IDENTIFIER LBRACKET argDefList RBRACKET COLON argType F_BEGIN
{
  static struct blackBoxDefBeginInfo  Info = {0};

  Info.pIdentifier  = $2.sValue;
  Info.pArgDefList  = $4.pContext;
  Info.nArgType     = $7.nValue;

  $$.pContext = (void*)&Info;

  yyBlackBoxReentrancyCount++;
}
;

defEnd
 : derivativeList F_END
{
  $$.pContext = $1.pContext;

  yyBlackBoxReentrancyCount--;
}
;

argType
 : REAL
{
  $$.nValue = 0;
}
 | INTEGER
{
  $$.nValue = 1;
}
 | COMPLEX
{
  $$.nValue = 2;
}
 | CHARACTER
{
  $$.nValue = 3;
}
 | BOOLEAN
{
  $$.nValue = 4;
}
 | REAL_ARRAY
{
  $$.nValue = 5;
}
 | INTEGER_ARRAY
{
  $$.nValue = 6;
}
 | COMPLEX_ARRAY
{
  $$.nValue = 7;
}
 | CHARACTER_ARRAY
{
  $$.nValue = 8;
}
 | BOOLEAN_ARRAY
{
  $$.nValue = 9;
}
;

dirType
 : IN
{
  $$.nValue = 1;
}
 | OUT
{
  $$.nValue = 2;
}
 | IN OUT
{
  $$.nValue = 0;
}
 | OUT IN
{
  $$.nValue = 0;
}
;

argDef
: IDENTIFIER COLON argType dirType
{
  $$.pContext = adtBlackBoxArgDef_create($1.sValue, $3.nValue, $4.nValue);
}
| IDENTIFIER COLON dirType argType
{
  $$.pContext = adtBlackBoxArgDef_create($1.sValue, $4.nValue, $3.nValue);
}
| RESULT COLON argType
{
  $$.pContext = adtBlackBoxArgDef_create("result", $3.nValue, 2);
}
;

argDefList
 : argDef
{
  $$.pContext = adtBlackBoxArgDefList_create($1.pContext);
}
 | argDefList COMMA argDef
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $3.pContext);
}
;

derivativeExtended
 : DERIV_OP LBRACKET IDENTIFIER RBRACKET PERIOD MULTIPLY exprAdditive
{
  $$.pContext = adtBlackBoxDerivative_create($3.sValue, $7.pContext, 0, 0, 1, 0, 0);
}
;

blackBoxSpecList
 : blackBoxSpec
{
  $$.pContext = adtBlackBoxSpecList_create($1.pContext);
}
 | blackBoxSpecList blackBoxSpec
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $2.pContext);
}
;

blackBoxSpec
 : READ_NOT_WRITTEN COLON LBRACKET identList RBRACKET
{
  $$.pContext = adtBlackBoxSpec_create($4.pContext, 0);
}
 | NOT_READ_THEN_WRITTEN COLON LBRACKET identList RBRACKET
{
  $$.pContext = adtBlackBoxSpec_create($4.pContext, 1);
}
 | NOT_READ_NOT_WRITTEN COLON LBRACKET identList RBRACKET
{
  $$.pContext = adtBlackBoxSpec_create($4.pContext, 2);
}
 | READ_THEN_WRITTEN COLON LBRACKET identList RBRACKET
{
  $$.pContext = adtBlackBoxSpec_create($4.pContext, 3);
}
 | DEPS COLON LBRACKET identList RBRACKET
{
  $$.pContext = adtBlackBoxSpec_create($4.pContext, 4);
}
;

ident
 : ID
{
  $$.pContext = adtBlackBoxIdent_create(-1);
}
 | NUMBER_FIXED
{
  $$.pContext = adtBlackBoxIdent_create($1.nValue);
}
;

identList
 : ident
{
  $$.pContext = adtBlackBoxIdentList_create($1.pContext);
}
 | identList COMMA ident
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $3.pContext);
}
;

derivativeExtendedList
 : derivativeExtended
{
  $$.pContext = adtBlackBoxDerivativeList_create($1.pContext);
}
 | derivativeExtendedList COMMA derivativeExtended
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $3.pContext);
}
;

exprAdditive
 : exprMultiplicative
{
  $$.pContext = adtBlackBoxExprAdditive_create(0, $1.pContext, 0);
}
 | exprAdditive PLUS exprMultiplicative
{
  $$.pContext = adtBlackBoxExprAdditive_create($1.pContext, $3.pContext, 1);
}
 | exprAdditive MINUS exprMultiplicative
{
  $$.pContext = adtBlackBoxExprAdditive_create($1.pContext, $3.pContext, 0);
}
;

exprMultiplicative
 : exprPower
{
  $$.pContext = adtBlackBoxExprMultiplicative_create(0, $1.pContext, 0);
}
 | exprMultiplicative MULTIPLY exprPower
{
  $$.pContext = adtBlackBoxExprMultiplicative_create($1.pContext, $3.pContext, 1);
}
 | exprMultiplicative DIVIDE exprPower
{
  $$.pContext = adtBlackBoxExprMultiplicative_create($1.pContext, $3.pContext, 0);
}
;

exprPower
 : exprUnary
{
  $$.pContext = adtBlackBoxExprPower_create(0, $1.pContext);
}
 | exprPower POWER exprUnary
{
  $$.pContext = adtBlackBoxExprPower_create($1.pContext, $3.pContext);
}
;

exprUnary
 : exprPostfix
{
  $$.pContext = adtBlackBoxExprUnary_create($1.pContext, 0, 0);
}
 | PLUS exprPostfix
{
  $$.pContext = adtBlackBoxExprUnary_create($2.pContext, 1, 1);
}
 | MINUS exprPostfix
{
  $$.pContext = adtBlackBoxExprUnary_create($2.pContext, 1, 0);
}
;

exprPostfix
 : NUMBER_FIXED
{
  $$.pContext = adtBlackBoxExprPostfix_create(0, $1.nValue, 0, 0, 0, 0);
}
 | NUMBER_FLOAT
{
  $$.pContext = adtBlackBoxExprPostfix_create(1, 0, $1.dValue, 0, 0, 0);
}
 | IDENTIFIER
{
  $$.pContext = adtBlackBoxExprPostfix_create(2, 0, 0, $1.sValue, 0, 0);
}
 | IDENTIFIER LBRACKET argList RBRACKET
{
  $$.pContext = adtBlackBoxExprPostfix_create(3, 0, 0, $1.sValue, $3.pContext, 0);
}
 | LBRACKET exprAdditive RBRACKET
{
  $$.pContext = adtBlackBoxExprPostfix_create(4, 0, 0, 0, 0, $2.pContext);
}
;

argList
 : exprAdditive
{
  $$.pContext = adtBlackBoxArgList_create($1.pContext);
}
 | argList COMMA exprAdditive
{
  $$.pContext = adtBlackBoxList_add($1.pContext, $3.pContext);
}
;
