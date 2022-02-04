%{
/*
 * expression_l.l
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
 * lex input file for expression parser
 *
 * The expression parser is used to parse simple mathematical expressions
 * that make up array size declarations in the comment fields of variables.
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "adtutils.hpp"
#include "adtexpression.hpp"


#if defined(_MSC_VER)
  #include <io.h>

  #define isatty _isatty

  #pragma warning(disable : 4996)
#else
  #include <unistd.h>
#endif


#define TOKEN_KEYWORD 0
#define TOKEN_NUMBER  1
#define TOKEN_TEXT    2


#define YYSTYPE   expressionType


#include "expression_y.h"


#if defined(_MSC_VER)
int         yyExpressiondebug       = 0;
#endif
int         adtExpression_nError    = 0;
const char* adtExpression_pErrorMsg = 0;
void*       adtExpression_pContext  = 0;
char        sScratchBuffer[1024]    = {0};


static int input();


void yyExpression_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
}


void yyExpression_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);
}

void yyExpression_resetError(void)
{
  adtExpression_nError    = 0;
  adtExpression_pErrorMsg = 0;
}

int yyExpression_error(void)
{
  return (adtExpression_nError);
}

const char* yyExpression_errorMsg(void)
{
  return (adtExpression_pErrorMsg);
}

void yyExpressionerror(char const* sErrorMessage)
{
  adtExpression_nError    = 1;
  adtExpression_pErrorMsg = adtExpression_AllocString(adtExpression_pContext, sErrorMessage);
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext  = pContext;
    p_yylval->nValue    = 0;
    p_yylval->sValue    = 0;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      {
        p_yylval->sValue = adtExpression_AllocString(pContext, pTokenText);
        break;
      }

      case TOKEN_NUMBER:
      {
        p_yylval->sValue = adtExpression_AllocString(pContext, pTokenText);
        p_yylval->nValue = atoi(pTokenText);
        break;
      }

      case TOKEN_TEXT:
      default:
      {
        break;
      }
    }
  }

  return (nToken);
}


%}


%%

"<"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, LT));
">"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, GT));
"["                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, SLBRACKET));
"]"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, SRBRACKET));
","                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
"("                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, LPARENTHESIS));
")"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, RPARENTHESIS));
"+"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
"-"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
"*"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, MULTIPLY));
"/"                         return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, DIVIDE));
[a-zA-Z_]([a-zA-Z0-9_])*    return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_KEYWORD, IDENTIFIER));
([0-9]+)                    return (dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_NUMBER, NUMBER));
[ \t\f\n\r]                 {
                              dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                            }

.                           {
                              dispatchToken(adtExpression_pContext, &yylval, yytext, TOKEN_TEXT, -1);

                              sprintf(sScratchBuffer, "illegal character '%c' (0x%x) in expression", yytext[0], yytext[0]);

                              adtExpression_nError    = 1;
                              adtExpression_pErrorMsg = adtExpression_AllocString(adtExpression_pContext, sScratchBuffer);
                            }
%%

int yywrap()
{
  return (1);
}
