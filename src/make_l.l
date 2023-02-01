%{
/*
 * make.l
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
 * lex input file for make scanner
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "adtutils.hpp"
#include "adtmake.hpp"


#if defined(_MSC_VER)
  #include <io.h>

  #define isatty _isatty

  #pragma warning(disable : 4996)
#else
  #include <unistd.h>
#endif


#define YYSTYPE   makeType


#include "make_y.h"


int         yyMakedebug             = 0;

int         adtMake_nError          = 0;
int         adtMake_nLineNumber     = 1;
const char* adtMake_pFileName       = "";
int         adtMake_nLastLineCount  = 0;
char        adtMake_sLastLine[512]  = {0};


static int input();


void yyMake_appendToLastLine(const char* pText)
{
  int         nLength     = strlen(pText);
  int         nMaxLength  = (sizeof(adtMake_sLastLine) / sizeof(*adtMake_sLastLine)) - 1;
  const char* pTextChar   = pText;

  while (*pTextChar != 0)
  {
    if (adtMake_nLastLineCount < nMaxLength)
    {
      adtMake_sLastLine[adtMake_nLastLineCount] = *pTextChar;
      adtMake_nLastLineCount++;
    }
    else
    {
      break;
    }

    pTextChar++;
  }

  adtMake_sLastLine[adtMake_nLastLineCount] = 0;
}


void yyMake_resetLastLine()
{
  adtMake_nLastLineCount                    = 0;
  adtMake_sLastLine[adtMake_nLastLineCount] = 0;
}


int dispatchToken(YYSTYPE* p_yylval, const char* pTokenText, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext  = 0;
    p_yylval->sValue    = make_AllocString(pTokenText);
  }

  make_LogText(pTokenText, adtMake_nLineNumber);
  yyMake_appendToLastLine(pTokenText);

  return (nToken);
}


void yyMake_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);

  adtMake_nLineNumber = 0;
}


void yyMake_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);
}


int yyMake_lineNumber(void)
{
  return (adtMake_nLineNumber);
}


const char* yyMake_fileName(void)
{
  return (adtMake_pFileName);
}


void yyMake_resetLineNumber(const char* pFileName)
{
  adtMake_nError      = 0;
  adtMake_nLineNumber = 1;
  adtMake_pFileName   = "";

  if (pFileName != 0)
  {
    adtMake_pFileName = pFileName;
  }
}


int yyMake_error(void)
{
  return (adtMake_nError);
}


void yyMakeerror(char const* sErrorMessage)
{
  printf("MAKE COMPILE ERROR on line %d in file %s : %s\n", adtMake_nLineNumber, adtMake_pFileName, sErrorMessage);
  printf("Context : %s\n", adtMake_sLastLine);

  adtMake_nError = 1;
}


void commenteof()
{
  printf ("unexpected EOF inside comment at line %d\n", adtMake_nLineNumber);
  AdtExit(1);
}


char* growBuffer(char* pBuffer, int* pnSize, int nGrowSize)
{
  char* pOldBuffer  = pBuffer;
  int   nNewSize    = *pnSize + nGrowSize;

  pBuffer = (char*)malloc(nNewSize * sizeof(char));

  memset(pBuffer, 0, nNewSize * sizeof(char));
  memcpy(pBuffer, pOldBuffer, (*pnSize) * sizeof(char));
  free(pOldBuffer);

  *pnSize = nNewSize;

  return (pBuffer);
}


char* mallocScanComment(const char* pClosingBrace)
{
  int         nGrowSize     = 1024;
  int         nSize         = nGrowSize;
  char*       pBuffer       = (char*)malloc(nSize * sizeof(char));
  char        nChar         = 0;
  int         nCharCount    = 0;
  const char* pMatch        = pClosingBrace;
  const char* pToken        = yytext;
  int         bMatched      = 0;

  memset(pBuffer, 0, nSize * sizeof(char));

  while (*pToken != '\0')
  {
    if (nCharCount >= nSize - 1)
    {
      pBuffer = growBuffer(pBuffer, &nSize, nGrowSize);
    }

    pBuffer[nCharCount] = *pToken;
    nCharCount++;
    pToken++;
  }

  for (nChar = input() ; nChar != 0 ; nChar = input())
  {
    if (nCharCount >= nSize - 1)
    {
      pBuffer = growBuffer(pBuffer, &nSize, nGrowSize);
    }

    pBuffer[nCharCount] = nChar;
    nCharCount++;

    if (nChar == '\n')
    {
      yyMake_resetLastLine();
      adtMake_nLineNumber++;
    }

    if (nChar == *pMatch)
    {
      pMatch++;

      if (*pMatch == '\0')
      {
        bMatched = 1;
        break;
      }
    }
    else
    {
      pMatch = pClosingBrace;
    }
  }

  if (!bMatched)
  {
    commenteof();
  }

  return (pBuffer);
}


%}

%x FILENAMES


FILENAME_CHARS          [a-zA-Z0-9_%&(){}#@!$\+\-]
QUOTED_FILENAME_CHARS   [a-zA-Z0-9_%&(){}#@!$\+\- ]
FILENAME_LITERAL        ((([a-zA-Z]\:)?{FILENAME_CHARS}*(\.{FILENAME_CHARS}*)*([\\\/]{FILENAME_CHARS}*(\.{FILENAME_CHARS}*)*)*)|([\'\"]([a-zA-Z ]\:)?{QUOTED_FILENAME_CHARS}*(\.{QUOTED_FILENAME_CHARS}*)*([\\\/]{QUOTED_FILENAME_CHARS}*(\.{QUOTED_FILENAME_CHARS}*)*)*[\'\"]))
IDENTIFIER_LITERAL      [a-zA-Z_]([a-zA-Z0-9_])*


%%
<*>AD                                             return (dispatchToken(&yylval, yytext, M_AD));
<*>CLASS                                          return (dispatchToken(&yylval, yytext, M_CLASS));
<*>BEGIN                                          {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_BEGIN));
                                                  }
<*>BOUNDS                                         return (dispatchToken(&yylval, yytext, M_BOUNDS));
<*>CHECK                                          return (dispatchToken(&yylval, yytext, M_CHECK));
<*>END                                            return (dispatchToken(&yylval, yytext, M_END));
<*>PATHS                                          {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_PATHS));
                                                  }
<*>SOURCE                                         return (dispatchToken(&yylval, yytext, M_SOURCE));
<*>INCLUDE                                        return (dispatchToken(&yylval, yytext, M_INCLUDE));
<*>OUTPUT                                         return (dispatchToken(&yylval, yytext, M_OUTPUT));
<*>FILE                                           {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_FILE));
                                                  }
<*>SWITCHES                                       {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_SWITCHES));
                                                  }
<*>BLACKBOX                                       {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_BLACKBOX));
                                                  }
<*>FILES                                          {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_FILES));
                                                  }
<*>WORKING                                        return (dispatchToken(&yylval, yytext, M_WORKING));
<*>DIRECTORY                                      {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_DIRECTORY));
                                                  }
<*>OPTIONS                                        return (dispatchToken(&yylval, yytext, M_OPTIONS));
<*>CPP                                            return (dispatchToken(&yylval, yytext, M_CPP));
<*>PASCAL                                         return (dispatchToken(&yylval, yytext, M_PASCAL));
<*>FORTRAN                                        return (dispatchToken(&yylval, yytext, M_FORTRAN));
<*>FUNCTION                                       return (dispatchToken(&yylval, yytext, M_FUNCTION));
<*>DIFF                                           return (dispatchToken(&yylval, yytext, M_DIFF));
<*>GRAD                                           return (dispatchToken(&yylval, yytext, M_GRAD));
<*>MULTIDIFF                                      return (dispatchToken(&yylval, yytext, M_MULTIDIFF));
<*>MULTIGRAD                                      return (dispatchToken(&yylval, yytext, M_MULTIGRAD));
<*>HESSIAN                                        return (dispatchToken(&yylval, yytext, M_HESSIAN));
<*>VAR                                            return (dispatchToken(&yylval, yytext, M_VAR));
<*>OUTVAR                                         return (dispatchToken(&yylval, yytext, M_OUTVAR));
<*>REML                                           return (dispatchToken(&yylval, yytext, M_REML));
<*>PARAMETERS                                     return (dispatchToken(&yylval, yytext, M_PARAMETERS));
<*>RANDOM                                         return (dispatchToken(&yylval, yytext, M_RANDOM));
<*>MODE                                           return (dispatchToken(&yylval, yytext, M_MODE));
<*>USER                                           return (dispatchToken(&yylval, yytext, M_USER));
<*>PRE                                            return (dispatchToken(&yylval, yytext, M_PRE));
<*>POST                                           return (dispatchToken(&yylval, yytext, M_POST));
<*>PRAGMAS                                        return (dispatchToken(&yylval, yytext, M_PRAGMAS));
<*>","                                            return (dispatchToken(&yylval, yytext, M_COMMA));
<*>";"                                            {
                                                    BEGIN(0);
                                                    return (dispatchToken(&yylval, yytext, M_SEMICOLON));
                                                  }
<INITIAL>":"                                      {
                                                    BEGIN(FILENAMES);
                                                    return (dispatchToken(&yylval, yytext, M_COLON));
                                                  }
<*>"="                                            return (dispatchToken(&yylval, yytext, M_EQUALS));
<*>"("                                            return (dispatchToken(&yylval, yytext, M_LBRACKET));
<*>")"                                            return (dispatchToken(&yylval, yytext, M_RBRACKET));
<*>"{"                                            {
                                                    int   nToken   = M_MULTILINE_COMMENT;
                                                    char* pComment = mallocScanComment("}");

                                                    if (pComment != 0)
                                                    {
                                                      dispatchToken(&yylval, pComment, nToken);
                                                      free(pComment);
                                                    }
                                                  }
<*>"(*"                                           {
                                                    int   nToken   = M_SINGLELINE_COMMENT;
                                                    char* pComment = mallocScanComment("*)");

                                                    if (pComment != 0)
                                                    {
                                                      dispatchToken(&yylval, pComment, nToken);
                                                      free(pComment);
                                                    }
                                                  }
<*>([\/][\/].*[\n])                               {
                                                    int   nToken   = M_SINGLELINE_COMMENT;
                                                  }
<FILENAMES>{FILENAME_LITERAL}                     {
                                                    return (dispatchToken(&yylval, yytext, M_FILENAME));
                                                  }
<INITIAL>{IDENTIFIER_LITERAL}                     return (dispatchToken(&yylval, yytext, M_IDENT));
<*>\'[^\'\n]*[\'\n]                               return (dispatchToken(&yylval, yytext, M_TEXT));
<*>\"[^\"\n]*[\"\n]                               return (dispatchToken(&yylval, yytext, M_TEXT));
<*>\n                                             {
                                                    dispatchToken(&yylval, yytext, -1);
                                                    yyMake_resetLastLine();
                                                    adtMake_nLineNumber++;
                                                  }
<*>[ \t\f\r]                                      {
                                                    dispatchToken(&yylval, yytext, -1);
                                                  }
<*>.                                              {
                                                    printf("'%c' (0x%x): illegal character at line %d\n", yytext[0], yytext[0], adtMake_nLineNumber);
                                                  }

%%

int yywrap()
{
  return (1);
}
