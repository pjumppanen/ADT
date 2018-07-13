%{
/*
 * black_box_l.l
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
 * lex input file for black box definition parser. This parses black box
 * definitions for functions that are not to be differentiated with ADT.
 * These definitions are provided by our own simplfied syntax and then
 * translated into a form that tapenade understands. For example,
 * this is a definition in a Pascal comment field:
 *
 * {<
 *  D/D(.) INV(X+Y),
 *  D/D(X) .*X,
 *  D/D(Y) .*(1/Y);
 *  >}
 *
 * You can alos include a black box dependency specification with, for example,
 *
 * {<BLACKBOX ReadNotWritten:(1,0,0) NotReadThenWritten:(0,1,0) deps:(1,0,0,id,id);>}
 *
 * < and > symbols are used to indicate the start and end of a black box
 * definition and must be supplied for inline definitions. This allows the
 * black box definition to be embedded within existing comments and not break
 * the parsing of the definition.
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "adtutils.hpp"
#include "adtblackbox.hpp"


#if defined(_MSC_VER)
  #include <io.h>

  #define isatty _isatty

  #pragma warning(disable : 4996)
#else
  #include <unistd.h>
#endif


#define TOKEN_KEYWORD       0
#define TOKEN_NUMBER_FIXED  1
#define TOKEN_NUMBER_FLOAT  2
#define TOKEN_TEXT          3


#define YYSTYPE   blackBoxType


#include "black_box_y.h"


int         yyBlackBoxdebug           = 0;
int         yyBlackBoxIsFile          = 0;
int         yyBlackBoxReentrancyCount = 0;
int         adtBlackBox_nError        = 0;
const char* adtBlackBox_pErrorMsg     = 0;
int         adtBlackBox_nLineNumber   = 1;
const char* adtBlackBox_pFileName     = "";
void*       adtBlackBox_pContext      = 0;
char        sTempBuffer[1024]         = {0};


static int input();


void yyBlackBox_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
}


void yyBlackBox_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);
}


int yyBlackBox_lineNumber(void)
{
  return (adtBlackBox_nLineNumber);
}


const char* yyBlackBox_fileName(void)
{
  return (adtBlackBox_pFileName);
}


void yyBlackBox_resetLineNumber(const char* pFileName)
{
  adtBlackBox_nError        = 0;
  adtBlackBox_pErrorMsg     = 0;
  adtBlackBox_nLineNumber   = 1;
  adtBlackBox_pFileName     = "";
  yyBlackBoxIsFile          = 0;
  yyBlackBoxReentrancyCount = 0;

  if (pFileName)
  {
    adtBlackBox_pFileName = pFileName;
    yyBlackBoxIsFile      = 1;
  }
}


int yyBlackBox_error(void)
{
  return (adtBlackBox_nError);
}


const char* yyBlackBox_errorMsg(void)
{
  return (adtBlackBox_pErrorMsg);
}


void yyBlackBoxerror(char const* sErrorMessage)
{
  if (adtBlackBox_pFileName != 0)
  {
    printf("BLACK BOX COMPILE ERROR on line %d in file %s : %s\n", adtBlackBox_nLineNumber, adtBlackBox_pFileName, sErrorMessage);
  }

  adtBlackBox_nError    = 1;
  adtBlackBox_pErrorMsg = adtBlackBox_AllocString(adtBlackBox_pContext, sErrorMessage);
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext  = pContext;
    p_yylval->dValue    = 0.0;
    p_yylval->nValue    = 0;
    p_yylval->sValue    = 0;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      {
        p_yylval->sValue = adtBlackBox_AllocString(pContext, pTokenText);
        break;
      }

      case TOKEN_NUMBER_FIXED:
      {
        p_yylval->sValue = adtBlackBox_AllocString(pContext, pTokenText);
        p_yylval->nValue = atoi(pTokenText);
        break;
      }

      case TOKEN_NUMBER_FLOAT:
      {
        p_yylval->sValue = adtBlackBox_AllocString(pContext, pTokenText);
        p_yylval->dValue = atof(pTokenText);
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

%option stack
%x BLACKBOXDEF

DECIMAL_LITERAL         ([0-9]+)
FLOATING_POINT_LITERAL  ((([0-9]+\.[0-9]*)|(\.[0-9]+))([eE][+-]?[0-9]+)?(f|F|l|L)?)
NAME_ID                 [a-zA-Z_]([a-zA-Z0-9_])*
QUALIFIED_NAME_ID       ((({NAME_ID}::)+{NAME_ID})|(({NAME_ID}\.)+{NAME_ID}))


%%
<INITIAL,BLACKBOXDEF>\<                 {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                          yyBlackBox_push_state(BLACKBOXDEF);
                                        }

<INITIAL,BLACKBOXDEF>\>                {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                          yyBlackBox_pop_state();
                                        }

                                        /* tokenise comment delimiters and ignore them. This has the effect of treating the entire
                                           comment block less the comment delimiters as a command field to be parsed */
<INITIAL,BLACKBOXDEF>\{                 {dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);}
<INITIAL,BLACKBOXDEF>\}                 {dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);}
<INITIAL,BLACKBOXDEF>\/\*               {dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);}
<INITIAL,BLACKBOXDEF>\*\/               {dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);}
<INITIAL,BLACKBOXDEF>\/\/               {dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);}

                                        /* single line comment. This allows comments in standalone definition files */
<BLACKBOXDEF>\#.*\n                     {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                          adtBlackBox_nLineNumber++;
                                        }

<BLACKBOXDEF>"function"                 return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, FUNCTION));
<BLACKBOXDEF>"procedure"                return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, PROCEDURE));
<BLACKBOXDEF>"result"                   return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, RESULT));
<BLACKBOXDEF>"in"                       return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, IN));
<BLACKBOXDEF>"out"                      return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, OUT));
<BLACKBOXDEF>"begin"                    return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, F_BEGIN));
<BLACKBOXDEF>"end"                      return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, F_END));
<BLACKBOXDEF>"real"                     return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, REAL));
<BLACKBOXDEF>"integer"                  return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, INTEGER));
<BLACKBOXDEF>"complex"                  return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, COMPLEX));
<BLACKBOXDEF>"character"                return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, CHARACTER));
<BLACKBOXDEF>"boolean"                  return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEAN));
<BLACKBOXDEF>"real_array"               return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, REAL_ARRAY));
<BLACKBOXDEF>"integer_array"            return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, INTEGER_ARRAY));
<BLACKBOXDEF>"complex_array"            return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, COMPLEX_ARRAY));
<BLACKBOXDEF>"character_array"          return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, CHARACTER_ARRAY));
<BLACKBOXDEF>"boolean_array"            return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEAN_ARRAY));
<BLACKBOXDEF>"BLACKBOX"                 return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, BLACKBOX));
<BLACKBOXDEF>"ReadNotWritten"           return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, READ_NOT_WRITTEN));
<BLACKBOXDEF>"NotReadThenWritten"       return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, NOT_READ_THEN_WRITTEN));
<BLACKBOXDEF>"NotReadNotWritten"        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, NOT_READ_NOT_WRITTEN));
<BLACKBOXDEF>"ReadThenWritten"          return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, READ_THEN_WRITTEN));
<BLACKBOXDEF>"deps"                     return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, DEPS));
<BLACKBOXDEF>"D/D"                      return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, DERIV_OP));
<BLACKBOXDEF>"id"                       return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, ID));
<BLACKBOXDEF>":"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, COLON));
<BLACKBOXDEF>";"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, SEMICOLON));
<BLACKBOXDEF>","                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
<BLACKBOXDEF>"("                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, LBRACKET));
<BLACKBOXDEF>")"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, RBRACKET));
<BLACKBOXDEF>"+"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
<BLACKBOXDEF>"-"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
<BLACKBOXDEF>"*"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, MULTIPLY));
<BLACKBOXDEF>"**"                       return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, POWER));
<BLACKBOXDEF>"^"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, POWER));
<BLACKBOXDEF>"/"                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, DIVIDE));
<BLACKBOXDEF>"."                        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, PERIOD));
<BLACKBOXDEF>{NAME_ID}                  return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, IDENTIFIER));
<BLACKBOXDEF>{QUALIFIED_NAME_ID}        return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_KEYWORD, QUALIFIED_IDENTIFIER));
<BLACKBOXDEF>{DECIMAL_LITERAL}          return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_NUMBER_FIXED, NUMBER_FIXED));
<BLACKBOXDEF>{FLOATING_POINT_LITERAL}   return (dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_NUMBER_FLOAT, NUMBER_FLOAT));

<BLACKBOXDEF>[ \t\f\r]                  {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                        }

<BLACKBOXDEF>[\n]                       {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                          adtBlackBox_nLineNumber++;
                                        }

<BLACKBOXDEF>.                          {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);

                                          sprintf(sTempBuffer, "illegal character '%c' (0x%x) in black box definition", yytext[0], yytext[0]);

                                          adtBlackBox_nError    = 1;
                                          adtBlackBox_pErrorMsg = adtBlackBox_AllocString(adtBlackBox_pContext, sTempBuffer);
                                        }

<INITIAL>[\n]                           {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                          adtBlackBox_nLineNumber++;
                                        }

<INITIAL>.                              {
                                          dispatchToken(adtBlackBox_pContext, &yylval, yytext, TOKEN_TEXT, -1);
                                        }
%%


int yywrap()
{
  return (1);
}


void yyBlackBox_pushState(int nState)
{
  yyBlackBox_push_state(nState);
}


void yyBlackBox_popState(void)
{
  yyBlackBox_pop_state();
}


int yyBlackBox_topState(void)
{
  return (yyBlackBox_top_state());
}
