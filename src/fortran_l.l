%{
/*
 * fortran.l
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
 * lex input file for fortran scanner
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "adtutils.hpp"


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


#define YYSTYPE   fortranType


#include "fortran_y.h"


int           yyFortrandebug             = 0;

int           adtFortran_nError          = 0;
int           adtFortran_nLineNumber     = 1;
const char*   adtFortran_pFileName       = "";
int           adtFortran_nBlockDepth     = 0;
void*         adtFortran_pFortranContext = 0;
char          adtFortran_sLastLine[512]  = {0};
int           adtFortran_nLastLineCount  = 0;


static int input();


void yyFortran_appendToLastLine(const char* pText)
{
  int         nLength     = strlen(pText);
  int         nMaxLength  = (sizeof(adtFortran_sLastLine) / sizeof(*adtFortran_sLastLine)) - 1;
  const char* pTextChar   = pText;

  while (*pTextChar != 0)
  {
    if (adtFortran_nLastLineCount < nMaxLength)
    {
      adtFortran_sLastLine[adtFortran_nLastLineCount] = *pTextChar;
      adtFortran_nLastLineCount++;
    }
    else
    {
      break;
    }

    pTextChar++;
  }

  adtFortran_sLastLine[adtFortran_nLastLineCount] = 0;
}


void yyFortran_resetLastLine()
{
  adtFortran_nLastLineCount                         = 0;
  adtFortran_sLastLine[adtFortran_nLastLineCount]   = 0;
}


void yyFortran_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
  yyFortran_resetLastLine();

  adtFortran_nLineNumber     = 1;
  adtFortran_nBlockDepth     = 0;
}


void yyFortran_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);

  if (adtFortran_nError != 0)
  {
    adtFortran_releaseRoot();
  }
}


int yyFortran_lineNumber(void)
{
  return (adtFortran_nLineNumber);
}


const char* yyFortran_fileName(void)
{
  return (adtFortran_pFileName);
}


void yyFortran_resetLineNumber(const char* pFileName)
{
  adtFortran_nError       = 0;
  adtFortran_nLineNumber  = 1;
  adtFortran_pFileName    = "";

  if (pFileName)
  {
    adtFortran_pFileName = pFileName;
  }
}


int yyFortran_error(void)
{
  return (adtFortran_nError);
}


void yyFortranerror(char const* sErrorMessage)
{
  printf("FORTRAN COMPILE ERROR on line %d in file %s : %s\n", adtFortran_nLineNumber, adtFortran_pFileName, sErrorMessage);
  printf("Context : %s\n", adtFortran_sLastLine);

  adtFortran_LogFlush(adtFortran_pFortranContext);

  adtFortran_nError = 1;
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext    = pContext;
    p_yylval->dValue      = 0.0;
    p_yylval->nValue      = 0;
    p_yylval->sValue      = 0;
    p_yylval->nBlockDepth = adtFortran_nBlockDepth;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      case TOKEN_TEXT:
      {
        switch (nToken)
        {
          case XNAME:
          {
            p_yylval->sValue = adtFortran_AllocString(pContext, pTokenText, 1);

            break;
          }

          case COMMENT:
          {
            adtFortran_AppendComment(pContext, pTokenText, adtFortran_pFileName, adtFortran_nLineNumber);
            break;
          }

          default:
          {
            p_yylval->sValue = adtFortran_AllocString(pContext, pTokenText, 0);
            break;
          }
        }
        break;
      }

      case TOKEN_NUMBER:
      {
        p_yylval->sValue = adtFortran_AllocString(pContext, pTokenText, 0);
        p_yylval->dValue = atof(pTokenText);
        break;
      }

      default:
      {
        break;
      }
    }

    adtFortran_LogText(pContext, pTokenText, adtFortran_nLineNumber);
    yyFortran_appendToLastLine(pTokenText);
  }

  return (nToken);
}


void commenteof()
{
  printf ("unexpected EOF inside comment at line %d\n", adtFortran_nLineNumber);
  AdtExit(1);
}


void adjustLineNumber(const char* pTokenText)
{
  const char* pChar = pTokenText;

  for (pChar = pTokenText ; *pChar != 0 ; pChar++)
  {
    if (*pChar == '\n')
    {
      yyFortran_resetLastLine();
      adtFortran_nLineNumber++;
    }
  }
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
      adtFortran_nLineNumber++;
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


%s Implicit


%%
 /* Undo continuation lines */
.*\&[ \t\f\r]*\n[ \t\f\r]*\&                        {
                                                      const char* pAmpersand = 0;

                                                      dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, LINE_CONTINUATION);
                                                      adjustLineNumber(yytext);

                                                      pAmpersand = strchr(yylval.sValue, '&');

                                                      if (pAmpersand != 0)
                                                      {
                                                        pAmpersand--;

                                                        for ( ; pAmpersand >= yylval.sValue ; pAmpersand--)
                                                        {
                                                          unput(*pAmpersand);
                                                        }
                                                      }
                                                    };

"CALL_EXPAND"                                       return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CALL_EXPAND));
"ADD_VARIABLES"                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ADD_VARIABLES));
"INTENT"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, INTENT));
"IN"                                                return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, IN));
"OUT"                                               return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, OUT));
"INOUT"                                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, INOUT));
"("                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LBRACKET));
")"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, RBRACKET));
","                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
":"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, COLON));
"="                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ASSIGN));
"+"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
"-"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
"**"                                                return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, POWER));
"*"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, MULTIPLY));
"/"                                                 return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DIVIDE));
".EQ."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_EQ));
".NE."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_NE));
".LT."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_LT));
".LE."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_LE));
".GT."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_GT));
".GE."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_GE));
".NOT."                                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_NOT));
".AND."                                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_AND));
".OR."                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_OR));
".EQV."                                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_EQUIV));
".NEQV."                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_NEQUIV));
("==")|(".EQ.")                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, EQUAL));
("\\=")|(".NE.")                                    return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, NEQUAL));
("<")|(".LT.")                                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LT));
("<=")|(".LE.")                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LE));
(">")|(".GT.")                                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, GT));
(">=")|(".GE.")                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, GE));
".TRUE."                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_TRUE));
".FALSE."                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL_FALSE));
"INTEGER"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, INTEGER));
"UNSIGNED"                                          return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, UNSIGNED));
"REAL"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, REAL));
"DOUBLE"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DOUBLE));
"PRECISION"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PRECISION));
"DOUBLEPRECISION"                                   return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DOUBLEPRECISION));
"COMPLEX"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, COMPLEX));
"LOGICAL"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, LOGICAL));
"CHARACTER"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CHARACTER));
"UNKNOWNTYPE"                                       return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, UNKNOWNTYPE));
"DIMENSION"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DIMENSION));
"END"                                               {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, END);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"PARAMETER"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PARAMETER));
"PRIVATE"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PRIVATE));
"PROTECTED"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PROTECTED));
"PUBLIC"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PUBLIC));
"IMPLICIT"                                          {
                                                      BEGIN(Implicit);
                                                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, IMPLICIT));
                                                    };
"NONE"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, NONE));
"WHERE"                                             {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, WHERE);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"ELSEWHERE"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ELSEWHERE));
"ENDWHERE"                                          {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDWHERE);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"GOTO"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, GOTO));
"IF"                                                return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, IF));
"THEN"                                              {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, THEN);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"ELSEIF"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ELSEIF));
"ELSE"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ELSE));
"ENDIF"                                             {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDIF);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"SELECTCASE"                                        {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, SELECTCASE);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"SELECT"                                            {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, SELECT);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"ENDSELECT"                                         {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDSELECT);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"CASE"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CASE));
"DEFAULT"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DEFAULT));
"DO"                                                return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, DO));
"ENDDO"                                             {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDDO);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"WHILE"                                             {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, WHILE);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"CYCLE"                                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CYCLE));
"EXIT"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, EXIT));
"CONTINUE"                                          return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CONTINUE));
"INTRINSIC"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, INTRINSIC));
"MODULE"                                            {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, MODULE);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"ENDMODULE"                                         {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDMODULE);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"USE"                                               return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, USE));
"CALL"                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, CALL));
"PROGRAM"                                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, PROGRAM));
"RESULT"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, RESULT));
"FUNCTION"                                          {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, FUNCTION);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"RECURSIVE"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, RECURSIVE));
"ENDFUNCTION"                                       {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDFUNCTION);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"SUBROUTINE"                                        {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, SUBROUTINE);

                                                      adtFortran_nBlockDepth++;
                                                      return (nReturn);
                                                    };
"ENDSUBROUTINE"                                     {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, ENDSUBROUTINE);

                                                      adtFortran_nBlockDepth--;
                                                      return (nReturn);
                                                    };
"RETURN"                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, RETURN));
"EXTERNAL"                                          return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, EXTERNAL));
"nbdirsmax"                                         return (dispatchToken(adtFortran_pFortranContext, &yylval, "nbdirs", TOKEN_KEYWORD, XNAME)); /* Translate nbdirsmax into nbdirs to simply resulting code */
[a-zA-Z_]([a-zA-Z0-9_])*                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, XNAME));
\'[^\'\n]*[\']                                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, XSCON));

[0-9]+\.[0-9]+[eEdD][+-]?[0-9]+_[0-9]+              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
[0-9]+\.[0-9]+_[0-9]+                               return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
[0-9]+[eEdD][+-]?[0-9]+_[0-9]+                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
[0-9]+\.[eEdD][+-]?[0-9]+_[0-9]+                    return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
[0-9]+\._[0-9]+                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
\.[0-9]+[eEdD][+-]?[0-9]+_[0-9]+                    return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));
\.[0-9]+_[0-9]+                                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON_S));

[0-9]+\.[0-9]+[eEdD][+-]?[0-9]+                     return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
[0-9]+\.[0-9]+                                      return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
[0-9]+[eEdD][+-]?[0-9]+                             return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
[0-9]+\.[eEdD][+-]?[0-9]+                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
[0-9]+\./[ \),=\+\-\*/\\<>\n]                       return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
\.[0-9]+[eEdD][+-]?[0-9]+                           return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));
\.[0-9]+                                            return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XRCON));

[0-9]+_[0-9]+                                       return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XICON_S));
[0-9]+                                              return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XICON));

<Implicit>\([a-zA-Z](\-[a-zA-Z])?(,[a-zA-Z](\-[a-zA-Z])?)*\)  return (dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_NUMBER, XIMPL));
\!.*[\n]                                            {
                                                      dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, COMMENT);
                                                      adjustLineNumber(yytext);
                                                    };
[ \t\f\r]+                                          {
                                                      dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                    };
^([ \t\f]*)\n                                       {
                                                      dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                      BEGIN(0);
                                                      adjustLineNumber(yytext);
                                                    };
\n                                                  {
                                                      int nReturn = dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_KEYWORD, xEOS);

                                                      BEGIN(0);
                                                      adjustLineNumber(yytext);
                                                      return (nReturn);
                                                    };
.                                                   {
                                                      dispatchToken(adtFortran_pFortranContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                      printf("'%c' (0x%x): illegal charcter at line %d\n", yytext[0], yytext[0], adtFortran_nLineNumber);
                                                    };

%%


int yywrap()
{
  return (1);
}
