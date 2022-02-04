%{
/*
 * delphi.l
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
 * lex input file for delphi scanner
 *
 * note that we include trailing comments in the IDENTIFIER token so that we can
 * extract Marks array size comments on variable declarations
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


#define YYSTYPE   delphiType


#include "delphi_y.h"


typedef struct IncludeContext
{
  const char*       pLastFileName;
  int               nLastLineNumber;
  YY_BUFFER_STATE   yyLastBufferState;
  FILE*             yyIn;
} IncludeContext;


struct IncludeContext adtDelphi_IncludeStack[64] = {0};
int                   adtDelphi_IncludeSP        = 0;


#if defined(_MSC_VER)
int         yyDelphidebug               = 0;
#endif
int         adtDelphi_nSection          = AdtDelphiSection_IMPLEMENTATION;
int         adtDelphi_nCodeType         = AdtDelphiCodeType_PROGRAM;
int         adtDelphi_nError            = 0;
int         adtDelphi_nLineNumber       = 1;
const char* adtDelphi_pFileName         = "";
int         adtDelphi_nBlockDepth       = 0;
void*       adtDelphi_pDelphiContext    = 0;
int         adtDelphi_nIfDefSP          = 0;
int         adtDelphi_nIfDefStack[64]   = {0};
int         adtDelphi_nIfDefCodeActive  = 1;
char        adtDelphi_sLastLine[512]    = {0};
int         adtDelphi_nLastLineCount    = 0;
void*       adtDelphi_SymbolTable       = 0;


static int input();


void yyDelphi_appendToLastLine(const char* pText)
{
  int         nLength     = strlen(pText);
  int         nMaxLength  = (sizeof(adtDelphi_sLastLine) / sizeof(*adtDelphi_sLastLine)) - 1;
  const char* pTextChar   = pText;

  while (*pTextChar != 0)
  {
    if (adtDelphi_nLastLineCount < nMaxLength)
    {
      adtDelphi_sLastLine[adtDelphi_nLastLineCount] = *pTextChar;
      adtDelphi_nLastLineCount++;
    }
    else
    {
      break;
    }

    pTextChar++;
  }

  adtDelphi_sLastLine[adtDelphi_nLastLineCount] = 0;
}


void yyDelphi_resetLastLine()
{
  adtDelphi_nLastLineCount                      = 0;
  adtDelphi_sLastLine[adtDelphi_nLastLineCount] = 0;
}


const char* yyDelphi_appendString(const char* pTextA, const char* pTextB)
{
  const char* pResult = 0;

  if ((pTextA != 0) && (pTextB != 0))
  {
    int   nLength       = strlen(pTextA) + strlen(pTextB) + 1;
    char* pAppendedText = (char*)malloc(nLength * sizeof(char));

    if (pAppendedText != 0)
    {
      strcpy(pAppendedText, pTextA);
      strcat(pAppendedText, pTextB);

      pResult = adtDelphi_AllocString(adtDelphi_pDelphiContext, pAppendedText, 0);

      free(pAppendedText);
    }
  }

  return (pResult);
}


void yyDelphi_ifDefUpdateActive()
{
  int cn;
  int nActive = 1;

  for (cn = 1 ; cn <= adtDelphi_nIfDefSP ; cn++)
  {
    nActive *= adtDelphi_nIfDefStack[cn];
  }

  adtDelphi_nIfDefCodeActive = nActive;
}


void yyDelphi_beginInclude(const char* pFileName, int* pPreserveInclude)
{
  if (!automate_IgnoreDependency(pFileName))
  {
    make_AddInclude(pFileName);
  }

  if (!automate_IgnoreInclude(pFileName))
  {
    FILE* hFile = lex_fopen(pFileName, "r");

    if (hFile > 0)
    {
      if (adtDelphi_IncludeSP < 64)
      {
        adtDelphi_IncludeStack[adtDelphi_IncludeSP].pLastFileName     = adtDelphi_pFileName;
        adtDelphi_IncludeStack[adtDelphi_IncludeSP].nLastLineNumber   = adtDelphi_nLineNumber;
        adtDelphi_IncludeStack[adtDelphi_IncludeSP].yyLastBufferState = YY_CURRENT_BUFFER;
        adtDelphi_IncludeStack[adtDelphi_IncludeSP].yyIn              = yyin;

        yyDelphi_resetLineNumber(pFileName);

        yyin = hFile;

        yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));

        adtDelphi_IncludeSP++;
      }
      else
      {
        yyDelphierror("Too deep nesting of $INCLUDE directives");
        AdtExit(-1);
      }
    }
    else
    {
      printf("WARNING Cannot open include file %s on line %d in file %s\n", pFileName, adtDelphi_nLineNumber, adtDelphi_pFileName);
    }

    if (pPreserveInclude != 0)
    {
      *pPreserveInclude = automate_preserveInclude(pFileName);
    }
  }
}


int yyDelphi_endInclude()
{
  int nInclude = 0;

  if (adtDelphi_IncludeSP > 0)
  {
    adtDelphi_IncludeSP--;

    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(adtDelphi_IncludeStack[adtDelphi_IncludeSP].yyLastBufferState);
    yyDelphi_resetLineNumber(adtDelphi_IncludeStack[adtDelphi_IncludeSP].pLastFileName);

    yyin                  = adtDelphi_IncludeStack[adtDelphi_IncludeSP].yyIn;
    adtDelphi_nLineNumber = adtDelphi_IncludeStack[adtDelphi_IncludeSP].nLastLineNumber;
    nInclude              = 1;
  }

  return (nInclude);
}


void yyDelphi_beginIfDef(int nOn)
{
  if (adtDelphi_nIfDefSP < 63)
  {
    adtDelphi_nIfDefSP++;
    adtDelphi_nIfDefStack[adtDelphi_nIfDefSP] = (nOn != 0) ? 1 : 0;

    yyDelphi_ifDefUpdateActive();
  }
}


void yyDelphi_elseIfDef()
{
  adtDelphi_nIfDefStack[adtDelphi_nIfDefSP] = (adtDelphi_nIfDefStack[adtDelphi_nIfDefSP] != 0) ? 0 : 1;
  yyDelphi_ifDefUpdateActive();
}


void yyDelphi_endIfDef()
{
  if (adtDelphi_nIfDefSP > 0)
  {
    adtDelphi_nIfDefSP--;
    yyDelphi_ifDefUpdateActive();
  }
}


void yyDelphi_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
  yyDelphi_resetLastLine();
  symTable_Destroy(adtDelphi_SymbolTable);

  adtDelphi_nSection        = AdtDelphiSection_IMPLEMENTATION;
  adtDelphi_nCodeType       = AdtDelphiCodeType_PROGRAM;
  adtDelphi_nLineNumber     = 1;
  adtDelphi_nBlockDepth     = 0;
  adtDelphi_nIfDefSP        = 0;
  adtDelphi_SymbolTable     = 0;
}


void yyDelphi_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);

  if (adtDelphi_nError != 0)
  {
    adtDelphi_releaseRoot();
  }
}


int yyDelphi_lineNumber(void)
{
  return (adtDelphi_nLineNumber);
}


const char* yyDelphi_fileName(void)
{
  return (adtDelphi_pFileName);
}


void yyDelphi_resetLineNumber(const char* pFileName)
{
  adtDelphi_nError      = 0;
  adtDelphi_nLineNumber = 1;
  adtDelphi_pFileName   = "";

  if (pFileName)
  {
    adtDelphi_pFileName = pFileName;
  }
}


int yyDelphi_error(void)
{
  return (adtDelphi_nError);
}


void yyDelphierror(char const* sErrorMessage)
{
  printf("DELPHI COMPILE ERROR on line %d in file %s : %s\n", adtDelphi_nLineNumber, adtDelphi_pFileName, sErrorMessage);
  printf("Context : %s\n", adtDelphi_sLastLine);

  adtDelphi_LogFlush(adtDelphi_pDelphiContext);

  adtDelphi_nError = 1;
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext    = pContext;
    p_yylval->dValue      = 0.0;
    p_yylval->nValue      = 0;
    p_yylval->sValue      = 0;
    p_yylval->nBlockDepth = adtDelphi_nBlockDepth;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      case TOKEN_TEXT:
      {
        switch (nToken)
        {
          case EMBEDDED_COMMANDS:
          {
            adtDelphi_ParseCommandBlock(pContext, pTokenText);
            /* fall through */
          }

          case SINGLELINE_COMMENT:
          case MULTILINE_COMMENT:
          {
            if (adtDelphi_nIfDefCodeActive != 0)
            {
              adtDelphi_AppendComment(pContext, pTokenText, adtDelphi_pFileName, adtDelphi_nLineNumber);
            }
            break;
          }

          default:
          {
            p_yylval->sValue = adtDelphi_AllocString(pContext, pTokenText, 1);
            break;
          }
        }
        break;
      }

      case TOKEN_NUMBER:
      {
        p_yylval->sValue = adtDelphi_AllocString(pContext, pTokenText, 0);
        p_yylval->dValue = atof(pTokenText);
        break;
      }

      default:
      {
        break;
      }
    }

    if (adtDelphi_nIfDefCodeActive != 0)
    {
      adtDelphi_LogText(pContext, pTokenText, adtDelphi_nLineNumber);
    }

    yyDelphi_appendToLastLine(pTokenText);
  }

  return (nToken);
}


void commenteof()
{
  printf ("unexpected EOF inside comment at line %d\n", adtDelphi_nLineNumber);
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


char* mallocScanComment(const char* pClosingBrace, int nToUpper)
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

    pBuffer[nCharCount] = (nToUpper == 0) ? *pToken : toupper(*pToken);
    nCharCount++;
    pToken++;
  }

  for (nChar = input() ; nChar != 0 ; nChar = input())
  {
    if (nCharCount >= nSize - 2)
    {
      pBuffer = growBuffer(pBuffer, &nSize, nGrowSize);
    }

    pBuffer[nCharCount] = (nToUpper == 0) ? nChar : toupper(nChar);
    nCharCount++;

    if (nChar == '\n')
    {
      yyDelphi_resetLastLine();
      adtDelphi_nLineNumber++;
    }

    if (nChar == *pMatch)
    {
      pMatch++;

      if (*pMatch == '\0')
      {
        bMatched            = 1;
        pBuffer[nCharCount] = '\n';
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


%x NOT_AD_CODE


INLINE_COMMENT          [ \t]*(\{[^\}\n]*\})
ID                      [a-zA-Z_]([a-zA-Z0-9_])*{INLINE_COMMENT}?


%%
ADD_VARIABLES                                     return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ADDVARIABLES));
ABSOLUTE                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ABSOLUTE));
AND                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, AND));
ANSISTRING                                        return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ANSISTRING));
ARRAY                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ARRAY));
AS                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, AS));
BEGIN                                             {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, B_BEGIN);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
BOOLEAN                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEAN));
LONGBOOL                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LONGBOOL));
BYTE                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, BYTE));
CASE                                              {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CASE);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
CDECL                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CDECL));
CHAR                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CHAR));
CLASS                                             {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CLASS);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
COMP                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, COMP));
CONST                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CONST));
CONSTRUCTOR                                       return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CONSTRUCTOR));
CONTAINS                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CONTAINS));
CURRENCY                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, CURRENCY));
DEFAULT                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DEFAULT));
DESTRUCTOR                                        return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DESTRUCTOR));
DIV                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DIV));
DO                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DO));
DOUBLE                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DOUBLE));
DOWNTO                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DOWNTO));
DYNAMIC                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DYNAMIC));
ELSE                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ELSE));
END                                               {
                                                    adtDelphi_nBlockDepth--;
                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, B_END));
                                                  }
EXPORT                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, EXPORT));
EXTENDED                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, EXTENDED));
EXTERNAL                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, EXTERNAL));
FAR                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, FAR));
FILE                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, P_FILE));
FINALIZATION                                      return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, FINALIZATION));
FOR                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, FOR));
FORWARD                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, FORWARD));
FUNCTION                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, FUNCTION));
GOTO                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, GOTO));
IF                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IF));
IMPLEMENTATION                                    {
                                                    adtDelphi_nSection = AdtDelphiSection_IMPLEMENTATION;
                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IMPLEMENTATION));
                                                  }
IMPLEMENTS                                        return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IMPLEMENTS));
IN                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IN));
INDEX                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INDEX));
INHERITED                                         return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INHERITED));
INITIALIZATION                                    {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INITIALIZATION);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
INT64                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INT64));
INTEGER                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INTEGER));
INTERFACE                                         {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, INTERFACE);

                                                    adtDelphi_nSection = AdtDelphiSection_INTERFACE;

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
IS                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IS));
LABEL                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LABEL));
LIBRARY                                           {
                                                    adtDelphi_nCodeType = AdtDelphiCodeType_LIBRARY;
                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LIBRARY));
                                                  }
LONGINT                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LONGINT));
LONGWORD                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LONGWORD));
MESSAGE                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, MESSAGE));
MOD                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, MOD));
NIL                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, NIL));
NODEFAULT                                         return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, NODEFAULT));
NOT                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, NOT));
OBJECT                                            {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OBJECT);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
OF                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OF));
OLEVARIANT                                        return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OLEVARIANT));
OR                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OR));
OUT                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OUT));
OUTO                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OUTO));
OVERLOAD                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OVERLOAD));
OVERRIDE                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, OVERRIDE));
PACKAGE                                           {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PACKAGE);

                                                    adtDelphi_nCodeType = AdtDelphiCodeType_PACKAGE;
                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
PACKED                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PACKED));
PASCAL                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PASCAL));
PCHAR                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PCHAR));
POINTER                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, POINTER));
PRIVATE                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PRIVATE));
PROCEDURE                                         return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PROCEDURE));
PROGRAM                                           {
                                                    adtDelphi_nCodeType = AdtDelphiCodeType_PROGRAM;
                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PROGRAM));
                                                  }

PROPERTY                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PROPERTY));
PROTECTED                                         return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PROTECTED));
PUBLIC                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PUBLIC));
PUBLISHED                                         return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PUBLISHED));
READ                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, READ));
REAL                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REAL));
REAL48                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REAL48));
RECORD                                            {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, RECORD);

                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
REGISTER                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REGISTER));
REINTRODUCE                                       return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REINTRODUCE));
REPEAT                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REPEAT));
REQUIRES                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, REQUIRES));
SAFECALL                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SAFECALL));
SET                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SET));
SHL                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SHL));
SHORTINT                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SHORTINT));
SHR                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SHR));
SINGLE                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SINGLE));
SIZEOF                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SIZEOF));
SMALLINT                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SMALLINT));
STDCALL                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, STDCALL));
STORED                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, STORED));
STRING                                            return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, STRING));
THEN                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, THEN));
TO                                                return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, TO));
TYPE                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, TYPE));
UNIT                                              {
                                                    int nReturn = dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, UNIT);

                                                    adtDelphi_nCodeType = AdtDelphiCodeType_UNIT;
                                                    adtDelphi_nBlockDepth++;
                                                    return (nReturn);
                                                  }
UNTIL                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, UNTIL));
USES                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, USES));
VAR                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, VAR));
VARIANT                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, VARIANT));
VIRTUAL                                           return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, VIRTUAL));
WHILE                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WHILE));
WIDECHAR                                          return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WIDECHAR));
WIDESTRING                                        return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WIDESTRING));
WITH                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WITH));
WORD                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WORD));
WRITE                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, WRITE));
XOR                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, XOR));
TRUE                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, BOOL_NUMBER));
FALSE                                             return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, BOOL_NUMBER));
EXIT                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, EXIT));
","                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
";"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, SEMICOLON));
":"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, COLON));
":="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, ASSIGNMENT));
"+="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PLUS_EQUALS));
"-="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, MINUS_EQUALS));
"*="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, TIMES_EQUALS));
"/="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DIV_EQUALS));
"="                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, EQUALS));
"."                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DOT));
".."                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, RANGE));

<NOT_AD_CODE>[^{}\n]*                             dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, -1);
<INITIAL,NOT_AD_CODE>"{$"                         {
                                                    char* pComment = mallocScanComment("}", 0);

                                                    if (pComment != 0)
                                                    {
                                                      const char* pChar = pComment;

                                                      if (adtDelphi_SymbolTable == 0)
                                                      {
                                                        adtDelphi_SymbolTable = symTable_Create();

                                                        symTable_Add(adtDelphi_SymbolTable, "AD", 0);
                                                      }

                                                      while (*pChar != '\0')
                                                      {
                                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                                        if (adtParse_matchWord(&pChar, "{$DEFINE", 0))
                                                        {
                                                          char* pSymbolName = 0;

                                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                                          if (adtParse_extractWord(&pSymbolName, " }", &pChar))
                                                          {
                                                            symTable_Add(adtDelphi_SymbolTable, pSymbolName, 0);
                                                            free(pSymbolName);
                                                          }
                                                          else
                                                          {
                                                            yyDelphierror("Missing symbol name in $DEFINE directive");
                                                            AdtExit(-1);
                                                          }
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$UNDEF", 0))
                                                        {
                                                          char* pSymbolName = 0;

                                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                                          if (adtParse_extractWord(&pSymbolName, " }", &pChar))
                                                          {
                                                            symTable_Remove(adtDelphi_SymbolTable, pSymbolName);
                                                            free(pSymbolName);
                                                          }
                                                          else
                                                          {
                                                            yyDelphierror("Missing symbol name in $UNDEF directive");
                                                            AdtExit(-1);
                                                          }
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$IFDEF", 0))
                                                        {
                                                          char* pSymbolName = 0;

                                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                                          if (adtParse_extractWord(&pSymbolName, " }", &pChar))
                                                          {
                                                            int nValue;

                                                            if (symTable_Defined(adtDelphi_SymbolTable, pSymbolName, &nValue))
                                                            {
                                                              yyDelphi_beginIfDef(1);
                                                            }
                                                            else
                                                            {
                                                              yyDelphi_beginIfDef(0);
                                                            }

                                                            free(pSymbolName);
                                                          }
                                                          else
                                                          {
                                                            yyDelphi_beginIfDef(0);
                                                          }
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$IFNDEF", 0))
                                                        {
                                                          char* pSymbolName = 0;

                                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                                          if (adtParse_extractWord(&pSymbolName, " }", &pChar))
                                                          {
                                                            int nValue;

                                                            if (symTable_Defined(adtDelphi_SymbolTable, pSymbolName, &nValue))
                                                            {
                                                              yyDelphi_beginIfDef(0);
                                                            }
                                                            else
                                                            {
                                                              yyDelphi_beginIfDef(1);
                                                            }

                                                            free(pSymbolName);
                                                          }
                                                          else
                                                          {
                                                            yyDelphi_beginIfDef(1);
                                                          }
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$ELSE", 0))
                                                        {
                                                          yyDelphi_elseIfDef();
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$ENDIF", 0))
                                                        {
                                                          yyDelphi_endIfDef();
                                                        }
                                                        else if (adtParse_matchWord(&pChar, "{$INCLUDE", 0) ||
                                                                 adtParse_matchWord(&pChar, "{$I", 0))
                                                        {
                                                          char* pIncludePath = 0;

                                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                                          if (adtParse_extractWord(&pIncludePath, "}", &pChar))
                                                          {
                                                            yyDelphi_beginInclude(adtDelphi_AllocString(adtDelphi_pDelphiContext, pIncludePath, 0), 0);
                                                            free(pIncludePath);
                                                          }
                                                          else
                                                          {
                                                            yyDelphierror("Missing include file path in $INCLUDE directive");
                                                            AdtExit(-1);
                                                          }
                                                        }
                                                        else
                                                        {
                                                          pChar = adtParse_nextLine(pChar, 0);
                                                        }
                                                      }

                                                      if (adtDelphi_nIfDefCodeActive != 0)
                                                      {
                                                        BEGIN(INITIAL);

                                                        dispatchToken(adtDelphi_pDelphiContext, &yylval, pComment, TOKEN_TEXT, MULTILINE_COMMENT);
                                                      }
                                                      else
                                                      {
                                                        BEGIN(NOT_AD_CODE);
                                                      }

                                                      free(pComment);
                                                    }
                                                  }

"{%"                                              {
                                                    char* pComment = mallocScanComment("}", 0);

                                                    if (pComment != 0)
                                                    {
                                                      dispatchToken(adtDelphi_pDelphiContext, &yylval, pComment, TOKEN_TEXT, EMBEDDED_COMMANDS);

                                                      free(pComment);
                                                    }
                                                  }

"(*%"                                             {
                                                    char* pComment = mallocScanComment("*)", 0);

                                                    if (pComment != 0)
                                                    {
                                                      dispatchToken(adtDelphi_pDelphiContext, &yylval, pComment, TOKEN_TEXT, EMBEDDED_COMMANDS);

                                                      free(pComment);
                                                    }
                                                  }

 /* pre-processing comment embedded commands for AD code automation
    these go before the comment lexical definition so that it will
    be matched first and processed */
<INITIAL,NOT_AD_CODE>\{[ \t]*AD_ALIAS[ \t]+[^}]*\}                          automate_AD_Alias(yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AD_LIBNAME[ \t]+[^}]*\}                        automate_AD_LibName(yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTOINIT[ \t]+[0-9]*[ \t]*\}                   automate_VarModeAndPhase(2, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTOINIT[ \t]*\}                               automate_VarModeAndPhase(2, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTODEC[ \t]+[0-9]*[ \t]*\}                    automate_VarModeAndPhase(1, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTODEC[ \t]+[0-9]*[ \t]*NO_INTERFACE[ \t]*\}  automate_VarModeAndPhase(1, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTODEC[ \t]*\}                                automate_VarModeAndPhase(1, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*AUTODEC[ \t]*NO_INTERFACE[ \t]*\}              automate_VarModeAndPhase(1, yytext, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*MANUAL[ \t]*\}                                 automate_VarModeAndPhase(0, 0, adtDelphi_pFileName, adtDelphi_nLineNumber);
<INITIAL,NOT_AD_CODE>\{[ \t]*MANUAL[ \t]*NO_INTERFACE[ \t]*\}               automate_VarModeAndPhase(0, 0, adtDelphi_pFileName, adtDelphi_nLineNumber);

<INITIAL,NOT_AD_CODE>"{"                          {
                                                    char* pComment = mallocScanComment("}", 0);

                                                    if (pComment != 0)
                                                    {
                                                      if (adtDelphi_nIfDefCodeActive != 0)
                                                      {
                                                        dispatchToken(adtDelphi_pDelphiContext, &yylval, pComment, TOKEN_TEXT, MULTILINE_COMMENT);
                                                      }

                                                      free(pComment);
                                                    }
                                                  }

<INITIAL,NOT_AD_CODE>"(*"                         {
                                                    char* pComment = mallocScanComment("*)", 0);

                                                    if (pComment != 0)
                                                    {
                                                      if (adtDelphi_nIfDefCodeActive != 0)
                                                      {
                                                        dispatchToken(adtDelphi_pDelphiContext, &yylval, pComment, TOKEN_TEXT, MULTILINE_COMMENT);
                                                      }

                                                      free(pComment);
                                                    }
                                                  }

"("                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LPARENTHESIS));
")"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, RPARENTHESIS));
"["                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LBRACKET));
"]"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, RBRACKET));
"@"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, AT));
"^"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, HAT));
"+"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
"-"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
">"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, GT));
"<"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LT));
">="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, GE));
"<="                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, LE));
"<>"                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, NE));
"*"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, MULTIPLY));
([\/][\/].*[\n])                                  {
                                                    dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, SINGLELINE_COMMENT);

                                                    yyDelphi_resetLastLine();
                                                    adtDelphi_nLineNumber++;
                                                  }

"/"                                               return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, DIVIDE));
{ID}                                              return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_KEYWORD, IDENTIFIER));
([0-9]+)                                          {
                                                    char  sBuffer[256]  = {0};
                                                    int   nLen          = strlen(yytext);

                                                    strcpy(sBuffer, yytext);

                                                    if (sBuffer[nLen - 1] == '.')
                                                    {
                                                      char nNext = input();

                                                      if (nNext == '.')
                                                      {
                                                        sBuffer[nLen - 1] = 0;

                                                        unput(nNext);
                                                      }

                                                      unput(nNext);
                                                    }

                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, sBuffer, TOKEN_NUMBER, INT_NUMBER));
                                                  }

([0-9]*(\.[0-9]*)?)([eE][+-]?[0-9]+)?             {
                                                    char  sBuffer[256]  = {0};
                                                    int   nLen          = strlen(yytext);

                                                    strcpy(sBuffer, yytext);

                                                    if (sBuffer[nLen - 1] == '.')
                                                    {
                                                      char nNext = input();

                                                      if (nNext == '.')
                                                      {
                                                        sBuffer[nLen - 1] = 0;

                                                        unput(nNext);
                                                      }

                                                      unput(nNext);
                                                    }

                                                    return (dispatchToken(adtDelphi_pDelphiContext, &yylval, sBuffer, TOKEN_NUMBER, REAL_NUMBER));
                                                  }

\'[^\'\n]*[\'\n]                                  return (dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, TEXT));
<INITIAL,NOT_AD_CODE>\n                           {
                                                    dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                    yyDelphi_resetLastLine();
                                                    adtDelphi_nLineNumber++;
                                                  }
[ \t\f\r]                                         {
                                                    dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                  }

.                                                 {
                                                    dispatchToken(adtDelphi_pDelphiContext, &yylval, yytext, TOKEN_TEXT, -1);
                                                    printf("'%c' (0x%x): illegal character at line %d\n", yytext[0], yytext[0], adtDelphi_nLineNumber);
                                                  }

<<EOF>>                                           {
                                                    if (yyDelphi_endInclude() == 0)
                                                    {
                                                      return YY_NULL;
                                                    }
                                                  }
%%

int yywrap()
{
  return (1);
}
