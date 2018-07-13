%{
/*
 * cpp.l
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
 * lex input file for C scanner with limited CPP extensions
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


#define YYSTYPE   cppType


#include "cpp_y.h"


typedef struct IncludeContext
{
  const char*       pLastFileName;
  int               nLastLineNumber;
  YY_BUFFER_STATE   yyLastBufferState;
  FILE*             yyIn;
} IncludeContext;


struct IncludeContext adtCpp_IncludeStack[64] = {0};
int                   adtCpp_IncludeSP        = 0;


int         yyCppdebug                = 0;

int         adtCpp_nError             = 0;
int         adtCpp_nLineNumber        = 1;
const char* adtCpp_pFileName          = "";
int         adtCpp_nBlockDepth        = 0;
void*       adtCpp_ScopeManager       = 0;
void*       adtCpp_pCppContext        = 0;
int         adtCpp_nIfDefSP           = 0;
int         adtCpp_nIfDefStack[64]    = {0};
int         adtCpp_nIfDefCodeActive   = 1;
char        adtCpp_sLastLine[512]     = {0};
int         adtCpp_nLastLineCount     = 0;
void*       adtCpp_SymbolTable        = 0;


static int input();


void yyCpp_appendToLastLine(const char* pText)
{
  int         nLength     = strlen(pText);
  int         nMaxLength  = (sizeof(adtCpp_sLastLine) / sizeof(*adtCpp_sLastLine)) - 1;
  const char* pTextChar   = pText;

  while (*pTextChar != 0)
  {
    if (adtCpp_nLastLineCount < nMaxLength)
    {
      adtCpp_sLastLine[adtCpp_nLastLineCount] = *pTextChar;
      adtCpp_nLastLineCount++;
    }
    else
    {
      break;
    }

    pTextChar++;
  }

  adtCpp_sLastLine[adtCpp_nLastLineCount] = 0;
}


void yyCpp_resetLastLine()
{
  adtCpp_nLastLineCount                   = 0;
  adtCpp_sLastLine[adtCpp_nLastLineCount] = 0;
}


void yyCpp_ifDefUpdateActive()
{
  int cn;
  int nActive = 1;

  for (cn = 1 ; cn <= adtCpp_nIfDefSP ; cn++)
  {
    nActive *= adtCpp_nIfDefStack[cn];
  }

  adtCpp_nIfDefCodeActive = nActive;
}


void yyCpp_beginInclude(const char* pFileName, int* pPreserveInclude)
{
  if (adtCpp_IncludeSP < 64)
  {
    if (!automate_IgnoreDependency(pFileName))
    {
      make_AddInclude(pFileName);
    }

    /* For C++ code includes <> enclosed quotes we ignore the include command.
       We do this because we do not want to parse system files as they'll
       contain code our parser does not understand. This allows the user to
       distiguish between code the parser should attempt to parse and the
       code it should ignore. We ignore some automation includes to avoid
       compilation problems */
    if (!automate_IgnoreInclude(pFileName))
    {
      FILE* hFile = lex_fopen(pFileName, "r");

      if (hFile > 0)
      {
        adtCpp_IncludeStack[adtCpp_IncludeSP].pLastFileName     = adtCpp_pFileName;
        adtCpp_IncludeStack[adtCpp_IncludeSP].nLastLineNumber   = adtCpp_nLineNumber;
        adtCpp_IncludeStack[adtCpp_IncludeSP].yyLastBufferState = YY_CURRENT_BUFFER;
        adtCpp_IncludeStack[adtCpp_IncludeSP].yyIn              = yyin;

        yyCpp_resetLineNumber(pFileName);

        yyin = hFile;

        yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));

        adtCpp_IncludeSP++;
      }
      else
      {
        printf("WARNING Cannot open include file %s on line %d in file %s\n", pFileName, adtCpp_nLineNumber, adtCpp_pFileName);
      }
    }

    if ((pPreserveInclude != 0) && (adtCpp_IncludeSP == 0))
    {
      *pPreserveInclude = automate_preserveInclude(pFileName);
    }

    if (adtCpp_IncludeSP > 1)
    {
      /* disable automation for includes higher than this level to avoid duplicate processing of parent class */
      automate_DisableAutomation(1);
    }
  }
  else
  {
    yyCpperror("Too deep nesting of #include directives");
    AdtExit(-1);
  }
}


int yyCpp_endInclude()
{
  int nInclude = 0;

  if (adtCpp_IncludeSP > 0)
  {
    adtCpp_IncludeSP--;

    if (adtCpp_IncludeSP <= 1)
    {
      automate_DisableAutomation(0);
    }

    /* For C++ files we only allow one level of include to allow inclusion of
       sibling header files. We disallow further inclusion because we don't want
       to parse the include code as it may contain stuff that we do not support
       (template code for example) that will cause the compilation to fail. The
        only exception is some of the automation related header files which we
        force inclusion of. */
    if (adtCpp_IncludeSP >= 0)
    {
      yy_delete_buffer(YY_CURRENT_BUFFER);
      yy_switch_to_buffer(adtCpp_IncludeStack[adtCpp_IncludeSP].yyLastBufferState);
      yyCpp_resetLineNumber(adtCpp_IncludeStack[adtCpp_IncludeSP].pLastFileName);

      yyin                  = adtCpp_IncludeStack[adtCpp_IncludeSP].yyIn;
      adtCpp_nLineNumber    = adtCpp_IncludeStack[adtCpp_IncludeSP].nLastLineNumber;
    }

    nInclude = 1;
  }

  return (nInclude);
}


void yyCpp_beginIfDef(int nOn)
{
  if (adtCpp_nIfDefSP < 63)
  {
    adtCpp_nIfDefSP++;
    adtCpp_nIfDefStack[adtCpp_nIfDefSP] = (nOn != 0) ? 1 : 0;
  }

  yyCpp_ifDefUpdateActive();
}


void yyCpp_elseIf(int nOn)
{
  adtCpp_nIfDefStack[adtCpp_nIfDefSP] = nOn;
  yyCpp_ifDefUpdateActive();
}


void yyCpp_elseIfDef()
{
  adtCpp_nIfDefStack[adtCpp_nIfDefSP] = (adtCpp_nIfDefStack[adtCpp_nIfDefSP] != 0) ? 0 : 1;
  yyCpp_ifDefUpdateActive();
}


void yyCpp_endIfDef()
{
  if (adtCpp_nIfDefSP > 0)
  {
    adtCpp_nIfDefSP--;
  }

  yyCpp_ifDefUpdateActive();
}


void yyCpp_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
  yyCpp_resetLastLine();
  symTable_Destroy(adtCpp_SymbolTable);

  adtCpp_nLineNumber     = 1;
  adtCpp_nBlockDepth     = 0;
  adtCpp_nIfDefSP        = 0;
  adtCpp_SymbolTable     = 0;

  scopeManager_Destroy(adtCpp_ScopeManager);

  adtCpp_ScopeManager    = 0;
}


void yyCpp_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);

  if (adtCpp_nError != 0)
  {
    adtCpp_releaseRoot();
  }
}


int yyCpp_lineNumber(void)
{
  return (adtCpp_nLineNumber);
}


const char* yyCpp_fileName(void)
{
  return (adtCpp_pFileName);
}


void yyCpp_resetLineNumber(const char* pFileName)
{
  adtCpp_nError       = 0;
  adtCpp_nLineNumber  = 1;
  adtCpp_pFileName    = "";

  if (pFileName != 0)
  {
    adtCpp_pFileName = pFileName;
  }
}


int yyCpp_error(void)
{
  return (adtCpp_nError);
}


void yyCpperror(char const* sErrorMessage)
{
  printf("CPP COMPILE ERROR on line %d in file %s : %s\n", adtCpp_nLineNumber, adtCpp_pFileName, sErrorMessage);
  printf("Context : %s\n", adtCpp_sLastLine);

  adtCpp_LogFlush(adtCpp_pCppContext);

  adtCpp_nError = 1;
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext    = pContext;
    p_yylval->dValue      = 0.0;
    p_yylval->nValue      = 0;
    p_yylval->sValue      = 0;
    p_yylval->nBlockDepth = adtCpp_nBlockDepth;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      case TOKEN_TEXT:
      {
        switch (nToken)
        {
          case EMBEDDED_COMMANDS:
          {
            adtCpp_ParseCommandBlock(pContext, pTokenText);
            /* fall through */
          }

          case PREPROCESSOR:
          case SINGLELINE_COMMENT:
          case MULTILINE_COMMENT:
          {
            if (adtCpp_nIfDefCodeActive != 0)
            {
              adtCpp_AppendComment(pContext, pTokenText, adtCpp_pFileName, adtCpp_nLineNumber);
            }
            break;
          }

          default:
          {
            p_yylval->sValue = adtCpp_AllocString(pContext, pTokenText, 1);
            break;
          }
        }
        break;
      }

      case TOKEN_NUMBER:
      {
        p_yylval->sValue = adtCpp_AllocString(pContext, pTokenText, 0);
        p_yylval->dValue = atof(pTokenText);
        break;
      }

      default:
      {
        break;
      }
    }

    adtCpp_LogText(pContext, pTokenText, adtCpp_nLineNumber);
    yyCpp_appendToLastLine(pTokenText);
  }

  return (nToken);
}


void commenteof()
{
  printf ("unexpected EOF inside comment at line %d\n", adtCpp_nLineNumber);
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
    if (nCharCount >= nSize - 1)
    {
      pBuffer = growBuffer(pBuffer, &nSize, nGrowSize);
    }

    pBuffer[nCharCount] = (nToUpper == 0) ? nChar : toupper(nChar);
    nCharCount++;

    if (nChar == '\n')
    {
      yyCpp_resetLastLine();
      adtCpp_nLineNumber++;
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


int yyCpp_check_type(int nQualified)
{
  /*
    This function needs to check if the symbol is defined in the type table,
    in the given scope when specified or the current scope if not, and if so
    should return either OBJ_IDENTIFIER or QUALIFIED_OBJ_IDENTIFIER depending
    on the state of nQualified. If not defined it should return IDENTIFIER or
    QUALIFIED_IDENTIFIER depending on the state of nQualified.
  */
  int nLexeme;

  if (adtCpp_ScopeManager == 0)
  {
    adtCpp_ScopeManager = scopeManager_Create();
  }

  if (scopeManager_isType(adtCpp_ScopeManager, yytext) != 0)
  {
    nLexeme = (nQualified != 0) ? QUALIFIED_OBJ_IDENTIFIER : OBJ_IDENTIFIER;
  }
  else
  {
    nLexeme = (nQualified != 0) ? QUALIFIED_IDENTIFIER : IDENTIFIER;

    scopeManager_addSymbol(adtCpp_ScopeManager, yytext);
  }

  return(nLexeme);
}


int yyCpp_check_dtor()
{
  /*
    This function needs to check if the dtor class is defined in the type table,
    in the given scope when specified or the current scope if not, and if so
    should return 1 or 0 otherwise
  */
  char*     pBuffer;
  char*     pChar;
  int       nIsDtor = 0;
  int       cn;

  if (adtCpp_ScopeManager == 0)
  {
    adtCpp_ScopeManager = scopeManager_Create();
  }

  pBuffer = (char*)malloc((yyleng + 1) * sizeof(char));

  if (pBuffer != 0)
  {
    pChar = pBuffer;

    for (cn = 0 ; cn < yyleng ; cn++)
    {
      if (yytext[cn] != '~')
      {
        *pChar = yytext[cn];

        pChar++;
      }
    }

    *pChar = 0;

    if (scopeManager_isType(adtCpp_ScopeManager, pBuffer) != 0)
    {
      nIsDtor = 1;
    }

    free(pBuffer);
  }

  return(nIsDtor);
}


%}


%x NOT_AD_CODE


LCOMMENT                ([\/][\/].*[\n])
INLINE_COMMENT          [ \t]*([\/]\*([^\n\*]|(\*[^\n\/]))*\*[\/])
PREP                    #[^\\\n]*(\\[ \t]*\n[^\\\n]*)*[ \t]*\n
IDB                     [a-zA-Z_]([a-zA-Z_]|[0-9])*
ID                      ([a-zA-Z_]([a-zA-Z_]|[0-9])*){INLINE_COMMENT}?
PSBL_DTOR               ~[a-zA-Z_]([a-zA-Z_]|[0-9])*
QUALIFIED_ID            ((::({IDB}::)?{IDB})|(({IDB}::)+{IDB})){INLINE_COMMENT}?
QUALIFIED_PSBL_DTOR     ((::({IDB}::)?{PSBL_DTOR})|(({IDB}::)+{PSBL_DTOR})){INLINE_COMMENT}?
HEXADECIMAL_LITERAL     (0[xX][a-fA-F0-9]+(u|U|l|L)?){INLINE_COMMENT}?
OCTAL_LITERAL           (0[0-7]+(u|U|l|L)?){INLINE_COMMENT}?
DECIMAL_LITERAL         ([0-9][0-9]*(u|U|l|L)?){INLINE_COMMENT}?
CHARACTER_LITERAL       (L?\'(\\.|\\[0-9]{1,3}|0?\\x[a-fA-F0-9]+|[^\\\'\n])+\'){INLINE_COMMENT}?
FLOATING_POINT_LITERAL  ((([0-9]+\.[0-9]*)|(\.[0-9]+))([eE][+-]?[0-9]+)?(f|F|l|L)?){INLINE_COMMENT}?
STRING_LITERAL          (L?\"(\\.|\\[0-9]{1,3}|0?\\x[a-fA-F0-9]+|[^\\\"\n])+\"){INLINE_COMMENT}?


%%
<NOT_AD_CODE>[^#\n]*            dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, -1);

<INITIAL,NOT_AD_CODE>"/*%"      {
                                  char* pComment = mallocScanComment("*/", 0);

                                  if (pComment != 0)
                                  {
                                    dispatchToken(adtCpp_pCppContext, &yylval, pComment, TOKEN_TEXT, EMBEDDED_COMMANDS);

                                    free(pComment);
                                  }
                                }

 /* pre-processing comment embedded commands for AD code automation
    these go before the comment lexical definition so that it will
    be matched first and processed */

<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AD_ALIAS[ \t]+([^\n\*])*\*[\/]                     automate_AD_Alias(yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AD_LIBNAME[ \t]+([^\n\*])*\*[\/]                   automate_AD_LibName(yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTOINIT[ \t]*\*[\/]                               automate_VarModeAndPhase(2, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTOINIT[ \t]+[0-9]*[ \t]*\*[\/]                   automate_VarModeAndPhase(2, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTODEC[ \t]*\*[\/]                                automate_VarModeAndPhase(1, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTODEC[ \t]*NO_INTERFACE[ \t]*\*[\/]              automate_VarModeAndPhase(1, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTODEC[ \t]+[0-9]*[ \t]*\*[\/]                    automate_VarModeAndPhase(1, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*AUTODEC[ \t]+[0-9]*[ \t]*NO_INTERFACE[ \t]*\*[\/]  automate_VarModeAndPhase(1, yytext, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*MANUAL[ \t]*\*[\/]                                 automate_VarModeAndPhase(0, 0, adtCpp_pFileName, adtCpp_nLineNumber);
<INITIAL,NOT_AD_CODE>[\/]\*[ \t]*MANUAL[ \t]*NO_INTERFACE[ \t]*\*[\/]               automate_VarModeAndPhase(0, 0, adtCpp_pFileName, adtCpp_nLineNumber);

<INITIAL,NOT_AD_CODE>"/*"       {
                                  char* pComment = mallocScanComment("*/", 0);

                                  if (pComment != 0)
                                  {
                                    dispatchToken(adtCpp_pCppContext, &yylval, pComment, TOKEN_TEXT, MULTILINE_COMMENT);

                                    free(pComment);
                                  }
                                }

<INITIAL,NOT_AD_CODE>{LCOMMENT} {
                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, SINGLELINE_COMMENT);

                                  yyCpp_resetLastLine();
                                  adtCpp_nLineNumber++;
                                }

<INITIAL,NOT_AD_CODE>{PREP}     {
                                  int         nPreserveInclude  = 0;
                                  int         cn                = 0;
                                  const char* pChar             = adtCpp_AllocString(adtCpp_pCppContext, yytext, 0);

                                  for (cn = 0 ; pChar[cn] != '\0' ; cn++)
                                  {
                                    if (pChar[cn] == '\n')
                                    {
                                      yyCpp_resetLastLine();
                                      adtCpp_nLineNumber++;
                                    }
                                  }

                                  if (adtCpp_SymbolTable == 0)
                                  {
                                    adtCpp_SymbolTable = symTable_Create();

                                    symTable_Add(adtCpp_SymbolTable, "AD", 0);
                                  }

                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, -1);

                                  while (*pChar != '\0')
                                  {
                                    pChar = adtParse_nextWord(pChar, 0, 1);

                                    if (adtParse_matchWord(&pChar, "#include", 0))
                                    {
                                      char* pIncludePath = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_matchWord(&pChar, "\"", 0))
                                      {
                                        if (adtParse_extractWord(&pIncludePath, "\n\"", &pChar))
                                        {
                                          if (adtCpp_nIfDefCodeActive != 0)
                                          {
                                            yyCpp_beginInclude(adtCpp_AllocString(adtCpp_pCppContext, pIncludePath, 0), &nPreserveInclude);

                                            if (nPreserveInclude != 0)
                                            {
                                              dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, PREPROCESSOR);
                                            }
                                          }

                                          free(pIncludePath);
                                        }
                                        else
                                        {
                                          yyCpperror("Missing include file path in #include directive");
                                          AdtExit(-1);
                                        }
                                      }
                                      /* For <> enclosed quotes we ignore the include command.
                                         We do this because we do not want to parse system files
                                         as they'll contain code our parser does not understand.
                                         This allows the user to distiguish between code the parser
                                         should attempt to parse and the code it should ignore. */
                                      else if (adtParse_matchWord(&pChar, "<", 0))
                                      {
                                        if (adtParse_extractWord(&pIncludePath, "\n>", &pChar))
                                        {
                                          free(pIncludePath);
                                        }
                                        else
                                        {
                                          yyCpperror("Missing include file path in #include directive");
                                          AdtExit(-1);
                                        }
                                      }
                                      else
                                      {
                                        yyCpperror("Missing include file path quotes in #include directive");
                                        AdtExit(-1);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#define", 0))
                                    {
                                      char* pSymbolName = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_extractWord(&pSymbolName, " (\n", &pChar))
                                      {
                                        char* pValueName = 0;

                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                        if (adtParse_extractWord(&pValueName, " )\n", &pChar))
                                        {
                                          symTable_Add(adtCpp_SymbolTable, pSymbolName, pValueName);

                                          free(pValueName);
                                        }
                                        else
                                        {
                                          symTable_Add(adtCpp_SymbolTable, pSymbolName, 0);
                                        }

                                        free(pSymbolName);
                                      }
                                      else
                                      {
                                        yyCpperror("Missing symbol name in #define directive");
                                        AdtExit(-1);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#undef", 0))
                                    {
                                      char* pSymbolName = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_extractWord(&pSymbolName, " \n", &pChar))
                                      {
                                        symTable_Remove(adtCpp_SymbolTable, pSymbolName);
                                        free(pSymbolName);
                                      }
                                      else
                                      {
                                        yyCpperror("Missing symbol name in #undef directive");
                                        AdtExit(-1);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#ifdef", 0))
                                    {
                                      char* pSymbolName = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_extractWord(&pSymbolName, " \n", &pChar))
                                      {
                                        int nValue;

                                        if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                        {
                                          yyCpp_beginIfDef(1);
                                        }
                                        else
                                        {
                                          yyCpp_beginIfDef(0);
                                        }

                                        free(pSymbolName);
                                      }
                                      else
                                      {
                                        yyCpp_beginIfDef(0);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#ifndef", 0))
                                    {
                                      char* pSymbolName = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_extractWord(&pSymbolName, " \n", &pChar))
                                      {
                                        int nValue;

                                        if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                        {
                                          yyCpp_beginIfDef(0);
                                        }
                                        else
                                        {
                                          yyCpp_beginIfDef(1);
                                        }

                                        free(pSymbolName);
                                      }
                                      else
                                      {
                                        yyCpp_beginIfDef(1);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#if", 0))
                                    {
                                      int nNegate = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_matchWord(&pChar, "!", 0))
                                      {
                                        nNegate = 1;
                                        pChar   = adtParse_nextWord(pChar, 0, 1);
                                      }

                                      if (adtParse_matchWord(&pChar, "defined(", 0))
                                      {
                                        char* pSymbolName = 0;

                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                        if (adtParse_extractWord(&pSymbolName, " )\n", &pChar))
                                        {
                                          int nValue;

                                          if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                          {
                                            yyCpp_beginIfDef((nNegate != 0) ? 0 : 1);
                                          }
                                          else
                                          {
                                            yyCpp_beginIfDef((nNegate != 0) ? 1 : 0);
                                          }

                                          free(pSymbolName);
                                        }
                                      }
                                      else
                                      {
                                        char* pSymbolName = 0;

                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                        if (adtParse_extractWord(&pSymbolName, " \n", &pChar))
                                        {
                                          int nType = 0;

                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                          if (adtParse_matchWord(&pChar, "==", 0))
                                          {
                                            nType = 1;
                                          }
                                          else if (adtParse_matchWord(&pChar, "!=", 0))
                                          {
                                            nType = 2;
                                          }
                                          else if (adtParse_matchWord(&pChar, ">=", 0))
                                          {
                                            nType = 3;
                                          }
                                          else if (adtParse_matchWord(&pChar, ">", 0))
                                          {
                                            nType = 4;
                                          }
                                          else if (adtParse_matchWord(&pChar, "<=", 0))
                                          {
                                            nType = 5;
                                          }
                                          else if (adtParse_matchWord(&pChar, "<", 0))
                                          {
                                            nType = 6;
                                          }

                                          int nValue      = 0;
                                          int nCheckValue = 0;
                                          int nActive     = 0;

                                          if (nType > 0)
                                          {
                                            char* pCheckValue = 0;

                                            pChar = adtParse_nextWord(pChar, 0, 1);

                                            if (adtParse_extractWord(&pCheckValue, " \n", &pChar))
                                            {
                                              sscanf(pCheckValue, "%d", &nCheckValue);
                                              free(pCheckValue);
                                            }
                                          }

                                          if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                          {
                                            switch (nType)
                                            {
                                              default:
                                              case 0:
                                              {
                                                nActive = 1;
                                                break;
                                              }

                                              case 1:
                                              {
                                                /* Equals */
                                                nActive = (nValue == nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 2:
                                              {
                                                /* Not equals */
                                                nActive = (nValue != nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 3:
                                              {
                                                /* Greater than or equal */
                                                nActive = (nValue >= nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 4:
                                              {
                                                /* Greater than */
                                                nActive = (nValue > nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 5:
                                              {
                                                /* Less than or equal */
                                                nActive = (nValue <= nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 6:
                                              {
                                                /* Less than */
                                                nActive = (nValue < nCheckValue) ? 1 : 0;
                                                break;
                                              }
                                            }
                                          }

                                          yyCpp_beginIfDef(nActive);

                                          free(pSymbolName);
                                        }
                                        else
                                        {
                                          yyCpp_beginIfDef(0);
                                        }
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#elif", 0))
                                    {
                                      int nNegate = 0;

                                      pChar = adtParse_nextWord(pChar, 0, 1);

                                      if (adtParse_matchWord(&pChar, "!", 0))
                                      {
                                        nNegate = 1;
                                        pChar   = adtParse_nextWord(pChar, 0, 1);
                                      }

                                      if (adtParse_matchWord(&pChar, "defined(", 0))
                                      {
                                        char* pSymbolName = 0;

                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                        if (adtParse_extractWord(&pSymbolName, " )\n", &pChar))
                                        {
                                          int nValue;

                                          if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                          {
                                            yyCpp_elseIf((nNegate != 0) ? 0 : 1);
                                          }
                                          else
                                          {
                                            yyCpp_elseIf((nNegate != 0) ? 1 : 0);
                                          }

                                          free(pSymbolName);
                                        }
                                      }
                                      else
                                      {
                                        char* pSymbolName = 0;

                                        pChar = adtParse_nextWord(pChar, 0, 1);

                                        if (adtParse_extractWord(&pSymbolName, " \n", &pChar))
                                        {
                                          int nType = 0;

                                          pChar = adtParse_nextWord(pChar, 0, 1);

                                          if (adtParse_matchWord(&pChar, "==", 0))
                                          {
                                            nType = 1;
                                          }
                                          else if (adtParse_matchWord(&pChar, "!=", 0))
                                          {
                                            nType = 2;
                                          }
                                          else if (adtParse_matchWord(&pChar, ">=", 0))
                                          {
                                            nType = 3;
                                          }
                                          else if (adtParse_matchWord(&pChar, ">", 0))
                                          {
                                            nType = 4;
                                          }
                                          else if (adtParse_matchWord(&pChar, "<=", 0))
                                          {
                                            nType = 5;
                                          }
                                          else if (adtParse_matchWord(&pChar, "<", 0))
                                          {
                                            nType = 6;
                                          }

                                          int nValue      = 0;
                                          int nCheckValue = 0;
                                          int nActive     = 0;

                                          if (nType > 0)
                                          {
                                            char* pCheckValue = 0;

                                            pChar = adtParse_nextWord(pChar, 0, 1);

                                            if (adtParse_extractWord(&pCheckValue, " \n", &pChar))
                                            {
                                              sscanf(pCheckValue, "%d", &nCheckValue);
                                              free(pCheckValue);
                                            }
                                          }

                                          if (symTable_Defined(adtCpp_SymbolTable, pSymbolName, &nValue))
                                          {
                                            switch (nType)
                                            {
                                              default:
                                              case 0:
                                              {
                                                nActive = 1;
                                                break;
                                              }

                                              case 1:
                                              {
                                                /* Equals */
                                                nActive = (nValue == nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 2:
                                              {
                                                /* Not equals */
                                                nActive = (nValue != nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 3:
                                              {
                                                /* Greater than or equal */
                                                nActive = (nValue >= nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 4:
                                              {
                                                /* Greater than */
                                                nActive = (nValue > nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 5:
                                              {
                                                /* Less than or equal */
                                                nActive = (nValue <= nCheckValue) ? 1 : 0;
                                                break;
                                              }

                                              case 6:
                                              {
                                                /* Less than */
                                                nActive = (nValue < nCheckValue) ? 1 : 0;
                                                break;
                                              }
                                            }
                                          }

                                          yyCpp_elseIf(nActive);

                                          free(pSymbolName);
                                        }
                                        else
                                        {
                                          yyCpp_elseIf(0);
                                        }
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#else", 0))
                                    {
                                      yyCpp_elseIfDef();
                                    }
                                    else if (adtParse_matchWord(&pChar, "#endif", 0))
                                    {
                                      yyCpp_endIfDef();
                                    }
                                    else
                                    {
                                      pChar = adtParse_nextLine(pChar, 0);
                                    }
                                  }

                                  if (adtCpp_nIfDefCodeActive != 0)
                                  {
                                    BEGIN(INITIAL);
                                  }
                                  else
                                  {
                                    BEGIN(NOT_AD_CODE);
                                  }
                                }

"add_variables"                 return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, ADDVARIABLES));
"asm"                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, ASM));
"auto"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, AUTO));
"bool"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, BOOL));
"longbool"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LONGBOOL));
"break"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, BREAK));
"case"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, CASE));
"char"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, CHAR));
"class"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, CLASS));
"const"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, CONST));
"continue"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, CONTINUE));
"default"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DEFAULT));
"do"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DO));
"double"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DOUBLE));
"else"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, ELSE));
"enum"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, ENUM));
"explicit"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, EXPLICIT));
"extern"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, EXTERN));
"float"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, FLOAT));
"friend"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, FRIEND));
"for"                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, FOR));
"goto"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, GOTO));
"if"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, IF));
"inline"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, INLINE));
"int"                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, INT));
"long"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LONG));
"mutable"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, MUTABLE));
"namespace"                     return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, NAMESPACE));
"public"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PUBLIC));
"private"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PRIVATE));
"protected"                     return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PROTECTED));
"register"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, REGISTER));
"return"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, RETURN));
"short"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SHORT));
"signed"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SIGNED));
"sizeof"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SIZEOF));
"static"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, STATIC));
"struct"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, STRUCT));
"switch"                        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SWITCH));
"typedef"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, TYPEDEF));
"typename"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, TYPENAME));
"union"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, UNION));
"unsigned"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, UNSIGNED));
"using"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, USING));
"virtual"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, VIRTUAL));
"void"                          return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, VOID));
"volatile"                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, VOLATILE));
"wchar_t"                       return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, WCHAR_T));
"while"                         return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, WHILE));
{QUALIFIED_ID}                  return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, yyCpp_check_type(1)));
{ID}                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, yyCpp_check_type(0)));

{QUALIFIED_PSBL_DTOR}           {
                                  if (yyCpp_check_dtor())
                                  {
                                    return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, QUALIFIED_DTOR));
                                  }
                                  else
                                  {
                                    REJECT;
                                  }
                                }

{PSBL_DTOR}                     {
                                  if (yyCpp_check_dtor())
                                  {
                                    return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DTOR));
                                  }
                                  else
                                  {
                                    REJECT;
                                  }
                                }

{FLOATING_POINT_LITERAL}        return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_NUMBER, LITERAL));
{HEXADECIMAL_LITERAL}           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_NUMBER, LITERAL));
{OCTAL_LITERAL}                 return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_NUMBER, LITERAL));
{DECIMAL_LITERAL}               return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_NUMBER, LITERAL));
{CHARACTER_LITERAL}             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, LITERAL));
{STRING_LITERAL}                return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, STRING_LITERAL));
"..."                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, ELLIPSIS));
">>="                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SHR_EQ));
"<<="                           return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SHL_EQ));
"+="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, P_EQ));
"-="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, M_EQ));
"*="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PROD_EQ));
"/="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DIV_EQ));
"%="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, MOD_EQ));
"&="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, AND_EQ));
"^="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, XOR_EQ));
"|="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, OR_EQ));
">>"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SHR));
"<<"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SHL));
"++"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, INCR));
"--"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DECR));
"&&"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LAND));
"||"                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LOR));
"<="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LT_EQ));
">="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, GT_EQ));
"=="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, EQEQ));
"!="                            return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, NEQ));
";"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, SEMICOLON));
("{"|"<%")                      {
                                  int nReturn = dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LSBRACKET);

                                  adtCpp_nBlockDepth++;
                                  return (nReturn);
                                }
("}"|"%>")                      {
                                  adtCpp_nBlockDepth--;
                                  return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, RSBRACKET));
                                }
","                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
":"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, COLON));
"="                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, EQ));
"("                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LBRACKET));
")"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, RBRACKET));
("["|"<:")                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LSQBRACKET));
("]"|":>")                      return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, RSQBRACKET));
"."                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DOT));
"&"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, AND));
"!"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LNOT));
"~"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, NOT));
"-"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
"+"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
"*"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, PROD));
"/"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, DIV));
"%"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, MOD));
"<"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, LT));
">"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, GT));
"^"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, XOR));
"|"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, OR));
"?"                             return (dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_KEYWORD, QUESTION));
<INITIAL,NOT_AD_CODE>\n         {
                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, -1);
                                  yyCpp_resetLastLine();
                                  adtCpp_nLineNumber++;
                                }
[ \v\f\r]                       {
                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, -1);
                                }
[ \t]                           {
                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, WHITESPACE);
                                }
.                               {
                                  dispatchToken(adtCpp_pCppContext, &yylval, yytext, TOKEN_TEXT, -1);
                                  printf("'%c' (0x%x): illegal character at line %d\n", yytext[0], yytext[0], adtCpp_nLineNumber);
                                }
<<EOF>>                         {
                                  if (yyCpp_endInclude() == 0)
                                  {
                                    return YY_NULL;
                                  }
                                }

%%


int yywrap()
{
  return (1);
}
