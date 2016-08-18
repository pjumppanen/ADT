D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|d|D)

%{
/*
 * java.l
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
 * lex input file for java scanner with limited java extensions
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


#define YYSTYPE   javaType


#include "java_y.h"


int         yyJavadebug               = 0;

int         adtJava_nError            = 0;
int         adtJava_nLineNumber       = 1;
const char* adtJava_pFileName         = "";
int         adtJava_nBlockDepth       = 0;
void*       adtJava_pJavaContext      = 0;
int         adtJava_nIfDefSP          = 0;
int         adtJava_nIfDefStack[64]   = {0};
int         adtJava_nIfDefCodeActive  = 1;
char        adtJava_sLastLine[512]    = {0};
int         adtJava_nLastLineCount    = 0;


static int input();


void yyJava_appendToLastLine(const char* pText)
{
  int         nLength     = strlen(pText);
  int         nMaxLength  = (sizeof(adtJava_sLastLine) / sizeof(*adtJava_sLastLine)) - 1;
  const char* pTextChar   = pText;

  while (*pTextChar != 0)
  {
    if (adtJava_nLastLineCount < nMaxLength)
    {
      adtJava_sLastLine[adtJava_nLastLineCount] = *pTextChar;
      adtJava_nLastLineCount++;
    }
    else
    {
      break;
    }

    pTextChar++;
  }

  adtJava_sLastLine[adtJava_nLastLineCount] = 0;
}


void yyJava_resetLastLine()
{
  adtJava_nLastLineCount                   = 0;
  adtJava_sLastLine[adtJava_nLastLineCount] = 0;
}


void yyJava_ifDefUpdateActive()
{
  int cn;
  int nActive = 1;

  for (cn = 1 ; cn <= adtJava_nIfDefSP ; cn++)
  {
    nActive *= adtJava_nIfDefStack[cn];
  }

  adtJava_nIfDefCodeActive = nActive;
}


void yyJava_beginIfDef(int nOn)
{
  if (adtJava_nIfDefSP < 63)
  {
    adtJava_nIfDefSP++;
    adtJava_nIfDefStack[adtJava_nIfDefSP] = (nOn != 0) ? 1 : 0;

    yyJava_ifDefUpdateActive();
  }
}


void yyJava_elseIfDef()
{
  adtJava_nIfDefStack[adtJava_nIfDefSP] = (adtJava_nIfDefStack[adtJava_nIfDefSP] != 0) ? 0 : 1;
  yyJava_ifDefUpdateActive();
}


void yyJava_endIfDef()
{
  if (adtJava_nIfDefSP > 0)
  {
    adtJava_nIfDefSP--;
    yyJava_ifDefUpdateActive();
  }
}


void yyJava_endParse(void)
{
  yy_flush_buffer(YY_CURRENT_BUFFER);
  yyJava_resetLastLine();

  adtJava_nLineNumber     = 1;
  adtJava_nBlockDepth     = 0;
  adtJava_nIfDefSP        = 0;
}


void yyJava_releaseBuffer(void)
{
  yy_delete_buffer(YY_CURRENT_BUFFER);

  if (adtJava_nError != 0)
  {
    adtJava_releaseRoot();
  }
}


int yyJava_lineNumber(void)
{
  return (adtJava_nLineNumber);
}


const char* yyJava_fileName(void)
{
  return (adtJava_pFileName);
}


void yyJava_resetLineNumber(const char* pFileName)
{
  adtJava_nError      = 0;
  adtJava_nLineNumber = 1;
  adtJava_pFileName   = "";

  if (pFileName != 0)
  {
    adtJava_pFileName = pFileName;
  }
}


int yyJava_error(void)
{
  return (adtJava_nError);
}


void yyJavaerror(char const* sErrorMessage)
{
  printf("CPP COMPILE ERROR on line %d in file %s : %s\n", adtJava_nLineNumber, adtJava_pFileName, sErrorMessage);
  printf("Context : %s\n", adtJava_sLastLine);

  adtJava_LogFlush(adtJava_pJavaContext);

  adtJava_nError = 1;
}


int dispatchToken(void* pContext, YYSTYPE* p_yylval, const char* pTokenText, int nType, int nToken)
{
  if (p_yylval != 0)
  {
    p_yylval->pContext    = pContext;
    p_yylval->dValue      = 0.0;
    p_yylval->sValue      = 0;
    p_yylval->sComment    = 0;
    p_yylval->nBlockDepth = adtJava_nBlockDepth;

    switch (nType)
    {
      case TOKEN_KEYWORD:
      case TOKEN_TEXT:
      {
        switch (nToken)
        {
          case EMBEDDED_COMMANDS:
          {
            adtJava_ParseCommandBlock(pContext, pTokenText);
            /* fall through */
          }

          case SINGLELINE_COMMENT:
          case MULTILINE_COMMENT:
          {
            adtJava_AppendComment(pContext, pTokenText);
            break;
          }

          default:
          {
            p_yylval->sValue = adtJava_AllocString(pContext, pTokenText, 1);

            if (nType == TOKEN_KEYWORD)
            {
              p_yylval->sComment = adtJava_ExtractComment(pContext);
            }
          }
        }
        break;
      }

      case TOKEN_NUMBER:
      {
        p_yylval->sValue = adtJava_AllocString(pContext, pTokenText, 0);
        p_yylval->dValue = atof(pTokenText);
        break;
      }

      default:
      {
        break;
      }
    }

    adtJava_LogText(pContext, pTokenText, adtJava_nLineNumber);
    yyJava_appendToLastLine(pTokenText);
  }

  return (nToken);
}


void commenteof()
{
  printf ("unexpected EOF inside comment at line %d\n", adtJava_nLineNumber);
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
      yyJava_resetLastLine();
      adtJava_nLineNumber++;
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


%x NOT_AD_CODE


%%
<NOT_AD_CODE>[^{}\n]*           dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, SINGLELINE_COMMENT);
<INITIAL,NOT_AD_CODE>(#.*[\n])  {
                                  const char* pChar = adtJava_AllocString(adtJava_pJavaContext, yytext, 0);

                                  dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, SINGLELINE_COMMENT);

                                  while (*pChar != '\0')
                                  {
                                    pChar = adtParse_nextWord(pChar, 0);

                                    if (adtParse_matchWord(&pChar, "#ifdef", 1))
                                    {
                                      pChar = adtParse_nextWord(pChar, 0);

                                      if (adtParse_matchWord(&pChar, "AD", 1))
                                      {
                                        yyJava_beginIfDef(1);
                                      }
                                      else
                                      {
                                        yyJava_beginIfDef(0);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#ifndef", 1))
                                    {
                                      pChar = adtParse_nextWord(pChar, 0);

                                      if (adtParse_matchWord(&pChar, "AD", 1))
                                      {
                                        yyJava_beginIfDef(0);
                                      }
                                      else
                                      {
                                        yyJava_beginIfDef(1);
                                      }
                                    }
                                    else if (adtParse_matchWord(&pChar, "#else", 1))
                                    {
                                      yyJava_elseIfDef();
                                    }
                                    else if (adtParse_matchWord(&pChar, "#endif", 1))
                                    {
                                      yyJava_endIfDef();
                                    }
                                    else
                                    {
                                      pChar = adtParse_nextLine(pChar, 0);
                                    }
                                  }

                                  if (adtJava_nIfDefCodeActive != 0)
                                  {
                                    BEGIN(INITIAL);
                                  }
                                  else
                                  {
                                    BEGIN(NOT_AD_CODE);
                                  }
                                }
"/*%"                           {
                                  char* pComment = mallocScanComment("*/", 0);

                                  if (pComment != 0)
                                  {
                                    dispatchToken(adtJava_pJavaContext, &yylval, pComment, TOKEN_TEXT, EMBEDDED_COMMANDS);
                                    free(pComment);
                                  }
                                }

<INITIAL,NOT_AD_CODE>"/*"       {
                                  char* pComment = mallocScanComment("*/", 0);

                                  if (pComment != 0)
                                  {
                                    dispatchToken(adtJava_pJavaContext, &yylval, pComment, TOKEN_TEXT, MULTILINE_COMMENT);
                                    free(pComment);
                                  }
                                }

([\/][\/].*[\n])                {
                                  dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, SINGLELINE_COMMENT);
                                  yyJava_resetLastLine();
                                  adtJava_nLineNumber++;
                                }

"abstract"                      return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, ABSTRACT));
"bool"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BOOL));
"boolean"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEAN));
"break"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BREAK));
"byte"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BYTE));
"case"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CASE));
"catch"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CATCH));
"char"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CHAR));
"class"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CLASS));
"const"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CONST));
"continue"                      return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, CONTINUE));
"default"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DEFAULT));
"do"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DO));
"double"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DOUBLE));
"else"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, ELSE));
"extends"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, EXTENDS));
"finally"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FINALLY));
"final"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FINAL));
"float"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FLOAT));
"for"                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FOR));
"if"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, IF));
"implements"                    return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, IMPLEMENTS));
"import"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, IMPORT));
"interface"                     return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INTERFACE));
"instanceof"                    return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INSTANCEOF));
"int"                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INT));
"long"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LONG));
"native"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, NATIVE));
"new"                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, NEW));
"package"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PACKAGE));
"public"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PUBLIC));
"private"                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PRIVATE));
"protected"                     return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PROTECTED));
"return"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, RETURN));
"short"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SHORT));
"static"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, STATIC));
"super"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SUPER));
"switch"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SWITCH));
"synchronized"                  return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SYNCHRONIZED));
"this"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, THIS));
"throw"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, THROW));
"throws"                        return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, THROWS));
"transient"                     return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, TRANSIENT));
"try"                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, TRY));
"void"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, VOID));
"volatile"                      return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, VOLATILE));
"while"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, WHILE));
"true"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEANLITERAL));
"false"                         return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, BOOLEANLITERAL));
"null"                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, NULLLITERAL));
">>>="                          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SHR_EQUALS));
">>="                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SAR_EQUALS));
"<<="                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SAL_EQUALS));
"+="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PLUS_EQUALS));
"-="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, MINUS_EQUALS));
"*="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, TIMES_EQUALS));
"/="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DIV_EQUALS));
"%="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, MOD_EQUALS));
"&="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, AND_EQUALS));
"^="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, XOR_EQUALS));
"|="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, OR_EQUALS));
">>>"                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SHR));
">>"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SAR));
"<<"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SAL));
"++"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INCR));
"--"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DECR));
"&&"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LAND));
"||"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LOR));
"<="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LTE));
">="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, GTE));
"=="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, EQ));
"!="                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, NE));
";"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SEMICOLON));
"{"                             {
                                  int nReturn = dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LCBRACKET);

                                  adtJava_nBlockDepth++;
                                  return (nReturn);
                                }
"}"                             {
                                  adtJava_nBlockDepth--;
                                  return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, RCBRACKET));
                                }
","                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, COMMA));
":"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, COLON));
"="                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, EQUALS));
"("                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LBRACKET));
")"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, RBRACKET));
"["                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LSQRBRACKET));
"]"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, RSQRBRACKET));
"."                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PERIOD));
"&"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, AND));
"!"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LNOT));
"~"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, NOT));
"-"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, MINUS));
"+"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, PLUS));
"*"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, MULTIPLY));
"/"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, DIV));
"%"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, MOD));
"<"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, LT));
">"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, GT));
"^"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, XOR));
"|"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, OR));
"?"                             return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, QUESTION));
"::"                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, SCOPE));
{L}({L}|{D})*                   return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, IDENTIFIER));
0[xX]{H}+                       return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INTEGERLITERAL));
0{D}+                           return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INTEGERLITERAL));
{D}+                            return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, INTEGERLITERAL));
{D}+{E}{FS}?                    return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FLOATINGPOINTLITERAL));
{D}*"."{D}+({E})?{FS}?          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FLOATINGPOINTLITERAL));
{D}+"."{D}*({E})?{FS}?          return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_KEYWORD, FLOATINGPOINTLITERAL));
'(\\.|[^\\'])+'                 return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT,    CHARACTERLITERAL));
\"(\\.|[^\\"])*\"               return (dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT,    STRINGLITERAL));
<INITIAL,NOT_AD_CODE>\n         {
                                  dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, -1);
                                  yyJava_resetLastLine();
                                  adtJava_nLineNumber++;
                                }
[ \v\t\f\r]                     {
                                  dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, -1);
                                }
.                               {
                                  dispatchToken(adtJava_pJavaContext, &yylval, yytext, TOKEN_TEXT, -1);
                                  printf("'%c' (0x%x): illegal character at line %d\n", yytext[0], yytext[0], adtJava_nLineNumber);
                                }

%%


int yywrap()
{
  return (1);
}
