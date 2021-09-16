//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    Adtutils.cpp
//
//  Purpose:
//    This file includes implementations of utility classes used with Flex/Bison
//    parsing in this project.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtutils.hpp"
#include "adtcpp.hpp"
#include "adtjava.hpp"
#include "adtdelphi.hpp"
#include "adtfortran.hpp"
#include "adtautomate.hpp"


const AdtStringList* Lex_SearchPaths = 0;

//  ----------------------------------------------------------------------------

FILE* lex_fopen(const char* pFileName, const char* pMode)
{
  FILE* File = fopen(pFileName, pMode);

  if ((File == 0) && (Lex_SearchPaths != 0))
  {
    AdtStringListConstIter  Iter;

    for (Iter = Lex_SearchPaths->begin() ; Iter != Lex_SearchPaths->end() ; ++Iter)
    {
      string  rPath(*Iter);

      if (rPath.length() > 0)
      {
        switch (rPath[rPath.length() - 1])
        {
          case '/':
          case '\\':
          {
            break;
          }

          default:
          {
            // Need to append slash to seperate folder from filename.
            rPath += '/';
            break;
          }
        }

        rPath += pFileName;
        File   = fopen(rPath, pMode);

        if (File != 0)
        {
          break;
        }
      }
    }
  }

  return (File);
}

//  ----------------------------------------------------------------------------

void automate_DisableAutomation(int nDisable)
{
  AdtAutoClass::includeDisableAutomation(nDisable != 0);
}

//  ----------------------------------------------------------------------------

int automate_ParseBegin(const char*& pChar,
                        const char** ppKeywords,
                        int nKeywords,
                        const char* pFileName,
                        int nLineNumber)
{
  int nWhich = -1;

  pChar = AdtParse::nextWord(pChar);

  // Look for opening comment brace
  const char* ppOpenBraces[2] = {"/*","{"};

  if (AdtParse::matchWhichWord(pChar, ppOpenBraces, 2) < 0)
  {
    ::printf("FATAL: Unknown comment brace. See file %s on line %d\n", __FILE__, __LINE__);
    AdtExit(-1);
  }

  pChar = AdtParse::nextWord(pChar);

  // look for keyword
  nWhich = AdtParse::matchWhichWord(pChar, ppKeywords, nKeywords);

  if (nWhich < 0)
  {
    ::printf("ERROR: Unknown macro %s in file %s on line %d\n", pChar, pFileName, nLineNumber);
    AdtExit(-1);
  }

  pChar = AdtParse::nextWord(pChar);

  return (nWhich);
}

//  ----------------------------------------------------------------------------

void automate_ParseEnd(const char*& pChar,
                       const char* pFileName,
                       int nLineNumber)
{
  pChar = AdtParse::nextWord(pChar);

  // look for closing comment brace
  const char* ppCloseBraces[2] = {"*/","}"};

  if (AdtParse::matchWhichWord(pChar, ppCloseBraces, 2) < 0)
  {
    ::printf("FATAL: No closing comment brace. See file %s on line %d\n", __FILE__, __LINE__);
    AdtExit(-1);
  }
}

//  ----------------------------------------------------------------------------

void automate_AD_LibName(const char* pText, const char* pFileName, int nLineNumber)
{
  // Parse comment field describing AD alias. Can be,
  //
  // Pascal case:
  //   { AD_LIBNAME Library_name }
  //
  // C++ case:
  //   /* AD_LIBNAME Library_name */
  //
  if (pText != 0)
  {
    string      sLibName;
    const char* pChar         = pText;
    const char* ppKeywords[1] = {"AD_LIBNAME"};

    automate_ParseBegin(pChar, ppKeywords, 1, pFileName, nLineNumber);

    // look for libname
    if (!AdtParse::extractWord(sLibName, ", *}", pChar, true))
    {
      ::printf("ERROR: No library name specified in macro AD_LIBNAME in file %s on line %d\n", pFileName, nLineNumber);
      AdtExit(-1);
    }

    automate_ParseEnd(pChar, pFileName, nLineNumber);

    AdtAutoClass::addLibName(sLibName, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void automate_AD_Alias(const char* pText, const char* pFileName, int nLineNumber)
{
  // Parse comment field describing AD alias. Can be,
  //
  // Pascal case:
  //   { AD_ALIAS short_name=full_name }
  //     or
  //   { AD_ALIAS short_name=full_name, parent_full_name }
  //
  // C++ case:
  //   /* AD_ALIAS short_name=full_name */
  //      or
  //   /* AD_ALIAS short_name=full_name, parent_full_name */
  //
  if (pText != 0)
  {
    string      sShortName;
    string      sFullName;
    string      sParentFullName;
    const char* pChar         = pText;
    const char* ppKeywords[1] = {"AD_ALIAS"};

    automate_ParseBegin(pChar, ppKeywords, 1, pFileName, nLineNumber);

    // look for short_name
    if (!AdtParse::extractWord(sShortName, " =", pChar, true))
    {
      ::printf("ERROR: No short name specified in macro AD_ALIAS in file %s on line %d\n", pFileName, nLineNumber);
      AdtExit(-1);
    }

    pChar = AdtParse::nextWord(pChar);

    // look for full_name
    if (!AdtParse::matchWord(pChar, "=") || !AdtParse::extractWord(sFullName, ", *}", pChar, true))
    {
      ::printf("ERROR: No full name specified in macro AD_ALIAS in file %s on line %d\n", pFileName, nLineNumber);
      AdtExit(-1);
    }

    pChar = AdtParse::nextWord(pChar);

    // look for parent_full_name
    if (AdtParse::matchWord(pChar, ","))
    {
      pChar = AdtParse::nextWord(pChar);

      if (!AdtParse::extractWord(sParentFullName, " *}", pChar, true))
      {
        ::printf("ERROR: No parent class full name specified in macro AD_ALIAS in file %s on line %d\n", pFileName, nLineNumber);
        AdtExit(-1);
      }
    }

    automate_ParseEnd(pChar, pFileName, nLineNumber);

    AdtAutoClass::addClassNameAndAlias(sFullName, sShortName, sParentFullName, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void automate_VarModeAndPhase(int nMode, const char* pText, const char* pFileName, int nLineNumber)
{
  int   nPhase        = 1;
  bool  bNoInterface  = false;

  // Parse comment fields parameter types. Can be,
  //
  // Pascal case:
  //   { AUTOINIT [phase_number] }
  //   { AUTODEC [phase_number] [NO_INTERFACE] }
  //   { MANUAL [NO_INTERFACE] }
  //
  // C++ case:
  //   /* AUTOINIT [phase_number] */
  //   /* AUTODEC [phase_number] [NO_INTERFACE] */
  //   /* MANUAL [NO_INTERFACE] */
  //
  // where items in [] are optional
  //
  if (pText != 0)
  {
    string      sArg;
    const char* pChar         = pText;
    const char* ppKeywords[3] = {"MANUAL", "AUTOINIT", "AUTODEC"};

    automate_ParseBegin(pChar, ppKeywords, 3, pFileName, nLineNumber);

    // look for phase number or NO_INTERFACE command
    while (AdtParse::extractWord(sArg, " *}", pChar, true))
    {
      if (::isdigit(sArg.c_str()[0]) != 0)
      {
        if (::sscanf(sArg.c_str(), "%d", &nPhase) != 1)
        {
          ::printf("WARNING: Bad or missing phase number in command in file %s on line %d\n", pFileName, nLineNumber);
        }
      }
      else
      {
        const char* pKeyword = sArg.c_str();

        if (AdtParse::matchWord(pKeyword, "NO_INTERFACE"))
        {
          bNoInterface = true;
        }
        else
        {
          ::printf("WARNING: Bad or missing NO_INTERFACE option in command in file %s on line %d\n", pFileName, nLineNumber);
        }
      }

      pChar = AdtParse::nextWord(pChar);
    }

    automate_ParseEnd(pChar, pFileName, nLineNumber);
  }

  AdtAutoClass::setModeAndPhase(nMode, nPhase, bNoInterface, pFileName, nLineNumber);
}

//  ----------------------------------------------------------------------------

int automate_IgnoreCheck(const char* pFileName, const char** ppFileTypes, int nNumFileTypes)
{
  int nIgnore = 0;

  if ((pFileName != 0) && (ppFileTypes != 0) && (nNumFileTypes > 0))
  {
    string      sFileName(pFileName);

    sFileName.toLower();

    for (int cn = 0 ; cn < nNumFileTypes ; cn++)
    {
      if (::strstr(sFileName.c_str(), ppFileTypes[cn]) != 0)
      {
        nIgnore = 1;
        break;
      }
    }
  }

  return (nIgnore);
}

//  ----------------------------------------------------------------------------

int automate_IgnoreInclude(const char* pFileName)
{
  // If any of the includes are standard automation includes then we ignore
  // them and don't include it. This is not a proper check but a quick and dirty.
  // Might need re-working in future.
  const char* ppAutomationFiles[] = {CONSTRUCTOR_SCALARS_PHASE,
                                     CONSTRUCTOR_ARRAYS_PHASE,
                                     IMPL_LIB_INTERFACE_METHODS,
                                     IMPL_LIB_INTERFACE_GLOBALS,
                                     DECL_LIB_INTERFACE_METHODS,
                                     DECL_LIB_INTERFACE_GLOBALS,
                                     DECL_LIB_INTERFACE_CONSTRUCTOR,
                                     IMPL_LIB_INTERFACE_CONSTRUCTOR,
                                     IMPL_LIB_REGISTRATION,
                                     LIB_EXPORTS,
                                     ARRAY_PLANS};

  int         nTypes = sizeof(ppAutomationFiles) / sizeof(*ppAutomationFiles);

  return (automate_IgnoreCheck(pFileName, ppAutomationFiles, nTypes));
}

//  ----------------------------------------------------------------------------

int automate_preserveInclude(const char* pFileName)
{
  // Some includes we wish to treat like comments so they are preserved in
  // the parse tree.
  const char* ppAutomationFiles[] = {DECL_LIB_INTERFACE_METHODS};

  int         nTypes = sizeof(ppAutomationFiles) / sizeof(*ppAutomationFiles);

  return (automate_IgnoreCheck(pFileName, ppAutomationFiles, nTypes));
}

//  ----------------------------------------------------------------------------

int automate_IgnoreDependency(const char* pFileName)
{
  const char* ppAutomationFiles[] = {CONSTRUCTOR_ARGS,
                                     CONSTRUCTOR_CALL_ARGS,
                                     CONSTRUCTOR_LOCALS,
                                     CONSTRUCTOR_SCALARS_PHASE,
                                     CONSTRUCTOR_ARRAYS_PHASE,
                                     IMPL_LIB_INTERFACE_METHODS,
                                     IMPL_LIB_INTERFACE_GLOBALS,
                                     DECL_LIB_INTERFACE_METHODS,
                                     DECL_LIB_INTERFACE_GLOBALS,
                                     DECL_LIB_INTERFACE_CONSTRUCTOR,
                                     IMPL_LIB_INTERFACE_CONSTRUCTOR,
                                     IMPL_LIB_REGISTRATION,
                                     LIB_EXPORTS,
                                     ARRAY_PLANS};

  int         nTypes = sizeof(ppAutomationFiles) / sizeof(*ppAutomationFiles);

  return (automate_IgnoreCheck(pFileName, ppAutomationFiles, nTypes));
}

//  ----------------------------------------------------------------------------

int automate_ForceInclude(const char* pFileName)
{
  // Need to force the inclusion of CONSTRUCTOR_ARGS and CONSTRUCTOR_CALL_ARGS
  // to make compilable code, otherwise the includes for the differentiated
  // class will be lost.
  const char* ppAutomationFiles[] = {CONSTRUCTOR_LOCALS,
                                     CONSTRUCTOR_ARGS,
                                     CONSTRUCTOR_CALL_ARGS};

  int         nTypes = sizeof(ppAutomationFiles) / sizeof(*ppAutomationFiles);

  return (automate_IgnoreCheck(pFileName, ppAutomationFiles, nTypes));
}

//  ----------------------------------------------------------------------------

void* scopeManager_Create(void)
{
  AdtCppScopeManager* pScopeManager = AdtCppScopeManager::globalScopeManager();

  return ((void*)pScopeManager);
}

//  ----------------------------------------------------------------------------

void scopeManager_Destroy(void* pPtrScopeManager)
{
  // do nothing
}

//  ----------------------------------------------------------------------------

void scopeManager_addUsing(void* pPtrScopeManager, const char* pUsing)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pUsing);

    pScopeManager->addUsing(NameAndComment.name());
  }
}

//  ----------------------------------------------------------------------------

void scopeManager_addUsingDeclaration(void* pPtrScopeManager, const char* pTypeName)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pTypeName);

    pScopeManager->addUsingDeclaration(NameAndComment.name());
  }
}

//  ----------------------------------------------------------------------------

void scopeManager_addType(void* pPtrScopeManager, const char* pTypeName)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pTypeName);

    pScopeManager->addType(NameAndComment.name());
  }
}

//  ----------------------------------------------------------------------------

void scopeManager_addSymbol(void* pPtrScopeManager, const char* pSymbolName)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pSymbolName);

    pScopeManager->addSymbol(NameAndComment.name());
  }
}

//  ----------------------------------------------------------------------------

int scopeManager_isType(void* pPtrScopeManager, const char* pSymbolName)
{
  int                 nIsType       = 0;
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pSymbolName);

    nIsType = pScopeManager->isType(NameAndComment.name()) ? 1 : 0;
  }

  return (nIsType);
}

//  ----------------------------------------------------------------------------

void scopeManager_pushScope(void* pPtrScopeManager, const char* pScope, int nIsFunction)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pScope);

    pScopeManager->pushScope(NameAndComment.name(), nIsFunction != 0);
  }
}

//  ----------------------------------------------------------------------------

void scopeManager_popScope(void* pPtrScopeManager)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    pScopeManager->popScope();
  }
}

//  ----------------------------------------------------------------------------

void scopeManager_inheritsFrom(void* pPtrScopeManager, const char* pParentScope)
{
  AdtCppScopeManager* pScopeManager = (AdtCppScopeManager*)pPtrScopeManager;

  if (pScopeManager != 0)
  {
    pScopeManager->inheritsFrom(pParentScope);
  }
}

//  ----------------------------------------------------------------------------

void* symTable_Create(void)
{
  AdtStringByStringMap* pMap = new AdtStringByStringMap;

  return ((void*)pMap);
}

//  ----------------------------------------------------------------------------

void symTable_Destroy(void* pSymTable)
{
  AdtStringByStringMap* pMap = (AdtStringByStringMap*)pSymTable;

  if (pMap != 0)
  {
    delete pMap;
  }
}

//  ----------------------------------------------------------------------------

void symTable_Add(void* pSymTable, const char* pSymbol, const char* pValue)
{
  AdtStringByStringMap* pMap = (AdtStringByStringMap*)pSymTable;

  if ((pMap != 0) && (pSymbol != 0))
  {
    string  sSymbol(pSymbol);

    if (pValue != 0)
    {
      string  sValue(pValue);

      (*pMap)[sSymbol] = sValue;
    }
    else
    {
      (*pMap)[sSymbol] = sSymbol;
    }
  }
}

//  ----------------------------------------------------------------------------

void symTable_Remove(void* pSymTable, const char* pSymbol)
{
  AdtStringByStringMap* pMap = (AdtStringByStringMap*)pSymTable;

  if ((pMap != 0) && (pSymbol != 0))
  {
    string  sSymbol(pSymbol);

    pMap->erase(sSymbol);
  }
}

//  ----------------------------------------------------------------------------

int symTable_Defined(void* pSymTable, const char* pSymbol, int* pnValue)
{
  int                   nFound  = 0;
  AdtStringByStringMap* pMap    = (AdtStringByStringMap*)pSymTable;

  if ((pMap != 0) && (pSymbol != 0))
  {
    string                        sSymbol(pSymbol);
    AdtStringByStringMapConstIter Iter = pMap->find(sSymbol);

    if (Iter != pMap->end())
    {
      if (pnValue != 0)
      {
        int nValue = 0;

        if (sscanf(Iter->second.c_str(), "%d", &nValue) == 0)
        {
          nValue = 0;
        }

        *pnValue = nValue;
      }

      nFound = 1;
    }
  }

  return (nFound);
}

//  ----------------------------------------------------------------------------

size_t adtParse_wordLength(const char* pText, const char* pWordDelimiters, const char** ppEndWord)
{
  return (AdtParse::wordLength(pText, pWordDelimiters, ppEndWord));
}

//  ----------------------------------------------------------------------------

int adtParse_stepOverWord(const char* pWordDelimiters, const char** rpText)
{
  int nDone = AdtParse::stepOverWord(pWordDelimiters, *rpText) ? 1 : 0;

  return (nDone);
}

//  ----------------------------------------------------------------------------

int adtParse_extractWord2(const char** ppWordDelimiters, const char** rpText)
{
  int nDone = AdtParse::stepOverWord(ppWordDelimiters, *rpText) ? 1 : 0;

  return (nDone);
}

//  ----------------------------------------------------------------------------

int adtParse_extractWord(char** pWord, const char* pWordDelimiters, const char** rpText)
{
  int     nExtracted;
  string  sWord;

  nExtracted  = 0;
  *pWord      = 0;

  if (AdtParse::extractWord(sWord, pWordDelimiters, *rpText))
  {
    *pWord = (char*)malloc(sWord.length() + 1);

    if (*pWord)
    {
      strcpy(*pWord, sWord);

      nExtracted = 1;
    }
  }

  return (nExtracted);
}

//  ----------------------------------------------------------------------------

int adtParse_extractWord2(char** pWord, const char** ppWordDelimiters, const char** rpText)
{
  int     nExtracted;
  string  sWord;

  nExtracted  = 0;
  *pWord      = 0;

  if (AdtParse::extractWord(sWord, ppWordDelimiters, *rpText))
  {
    *pWord = (char*)malloc(sWord.length() + 1);

    if (*pWord)
    {
      strcpy(*pWord, sWord);

      nExtracted = 1;
    }
  }

  return (nExtracted);
}

//  ----------------------------------------------------------------------------

int adtParse_bracketedExtractWord(char** pWord,
                                  const char* pWordDelimiters,
                                  const char* pOpenBrackets,
                                  const char* pCloseBrackets,
                                  const char** rpText)
{
  int     nExtracted;
  string  sWord;

  nExtracted  = 0;
  *pWord      = 0;

  if (AdtParse::bracketedExtractWord(sWord,
                                     pWordDelimiters,
                                     pOpenBrackets,
                                     pCloseBrackets,
                                     *rpText))
  {
    *pWord = (char*)malloc(sWord.length() + 1);

    if (*pWord)
    {
      strcpy(*pWord, sWord);

      nExtracted = 1;
    }
  }

  return (nExtracted);
}

//  ----------------------------------------------------------------------------

int adtParse_bracketedExtractWord2(char** pWord,
                                   const char** ppWordDelimiters,
                                   const char** ppOpenBrackets,
                                   const char** ppCloseBrackets,
                                   const char** rpText)
{
  int     nExtracted;
  string  sWord;

  nExtracted  = 0;
  *pWord      = 0;

  if (AdtParse::bracketedExtractWord(sWord,
                                     ppWordDelimiters,
                                     ppOpenBrackets,
                                     ppCloseBrackets,
                                     *rpText))
  {
    *pWord = (char*)malloc(sWord.length() + 1);

    if (*pWord)
    {
      strcpy(*pWord, sWord);

      nExtracted = 1;
    }
  }

  return (nExtracted);
}

//  ----------------------------------------------------------------------------

int adtParse_previousMatchWord(const char** ppChar, const char* pFirstChar, const char* pWord, int nCaseSensitive)
{
  return (AdtParse::previousMatchWord(*ppChar, pFirstChar, pWord, nCaseSensitive != 0) ? 1 : 0);
}

//  ----------------------------------------------------------------------------

int adtParse_matchWord(const char** ppChar, const char* pWord, int nCaseSensitive)
{
  return (AdtParse::matchWord(*ppChar, pWord, nCaseSensitive != 0) ? 1 : 0);
}

//  ----------------------------------------------------------------------------

const char* adtParse_previousWord(const char* pChar, const char* pFirstChar, size_t* pnCount)
{
  return (AdtParse::previousWord(pChar, pFirstChar, pnCount));
}

//  ----------------------------------------------------------------------------

const char* adtParse_nextWord(const char* pChar, size_t* pnCount, int bIncludeNewline)
{
  return (AdtParse::nextWord(pChar, pnCount, bIncludeNewline != 0));
}

//  ----------------------------------------------------------------------------

const char* adtParse_nextLine(const char* pChar, size_t* pnCount)
{
  return (AdtParse::nextLine(pChar, pnCount));
}

//  ----------------------------------------------------------------------------

void adtDelphi_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtDelphi*  DelphiContext = (AdtDelphi*)pContext;

    DelphiContext->appendComment(pTokenText, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

const char* adtDelphi_AllocString(void* pContext, const char* pTokenText, int nTranslate)
{
  const char* pString     = 0;
  bool        bTranslate  = (nTranslate != 0);

  if (pContext != 0)
  {
    AdtDelphi*  DelphiContext = (AdtDelphi*)pContext;

    pString = DelphiContext->allocString(pTokenText, 0, bTranslate);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void adtDelphi_ParseCommandBlock(void* pContext, const char* pCommandBlock)
{
  if ((pContext != 0) && (pCommandBlock != 0))
  {
    AdtDelphi*  DelphiContext = (AdtDelphi*)pContext;

    DelphiContext->parseCommandBlock(pCommandBlock, true);
  }
}

//  ----------------------------------------------------------------------------

void  adtDelphi_LogText(void* pContext, const char* pTokenText, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtDelphi*  DelphiContext = (AdtDelphi*)pContext;

    DelphiContext->logText(pTokenText, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void  adtDelphi_LogFlush(void* pContext)
{
  if (pContext != 0)
  {
    AdtDelphi*  DelphiContext = (AdtDelphi*)pContext;

    DelphiContext->logFlush();
  }
}

//  ----------------------------------------------------------------------------

void adtFortran_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtFortran* FortranContext = (AdtFortran*)pContext;

    FortranContext->appendComment(pTokenText, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

const char* adtFortran_AllocString(void* pContext, const char* pTokenText, int nTranslate)
{
  const char* pString     = 0;
  bool        bTranslate  = (nTranslate != 0);

  if (pContext != 0)
  {
    AdtFortran* FortranContext = (AdtFortran*)pContext;

    pString = FortranContext->allocString(pTokenText, 0, bTranslate);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void  adtFortran_LogText(void* pContext, const char* pTokenText, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtFortran* FortranContext = (AdtFortran*)pContext;

    FortranContext->logText(pTokenText, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void  adtFortran_LogFlush(void* pContext)
{
  if (pContext != 0)
  {
    AdtFortran* FortranContext = (AdtFortran*)pContext;

    FortranContext->logFlush();
  }
}

//  ----------------------------------------------------------------------------

void adtCpp_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtCpp* CppContext = (AdtCpp*)pContext;

    CppContext->appendComment(pTokenText, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

const char* adtCpp_AllocString(void* pContext, const char* pTokenText, int nTranslate)
{
  const char* pString     = 0;
  bool        bTranslate  = (nTranslate != 0);

  if (pContext != 0)
  {
    AdtCpp*  CppContext = (AdtCpp*)pContext;

    pString = CppContext->allocString(pTokenText, 0, bTranslate);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void adtCpp_ParseCommandBlock(void* pContext, const char* pCommandBlock)
{
  if ((pContext != 0) && (pCommandBlock != 0))
  {
    AdtCpp*  CppContext = (AdtCpp*)pContext;

    CppContext->parseCommandBlock(pCommandBlock, true);
  }
}

//  ----------------------------------------------------------------------------

void  adtCpp_LogText(void* pContext, const char* pTokenText, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtCpp*  CppContext = (AdtCpp*)pContext;

    CppContext->logText(pTokenText, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void  adtCpp_LogFlush(void* pContext)
{
  if (pContext != 0)
  {
    AdtCpp*  CppContext = (AdtCpp*)pContext;

    CppContext->logFlush();
  }
}

//  ----------------------------------------------------------------------------

void adtJava_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtJava* JavaContext = (AdtJava*)pContext;

    JavaContext->appendComment(pTokenText, pFileName, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

const char* adtJava_AllocString(void* pContext, const char* pTokenText, int nTranslate)
{
  const char* pString     = 0;
  bool        bTranslate  = (nTranslate != 0);

  if (pContext != 0)
  {
    AdtJava*  JavaContext = (AdtJava*)pContext;

    pString = JavaContext->allocString(pTokenText, 0, bTranslate);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void adtJava_ParseCommandBlock(void* pContext, const char* pCommandBlock)
{
  if ((pContext != 0) && (pCommandBlock != 0))
  {
    AdtJava*  JavaContext = (AdtJava*)pContext;

    JavaContext->parseCommandBlock(pCommandBlock, true);
  }
}

//  ----------------------------------------------------------------------------

void  adtJava_LogText(void* pContext, const char* pTokenText, int nLineNumber)
{
  if (pContext != 0)
  {
    AdtJava*  JavaContext = (AdtJava*)pContext;

    JavaContext->logText(pTokenText, nLineNumber);
  }
}

//  ----------------------------------------------------------------------------

void  adtJava_LogFlush(void* pContext)
{
  if (pContext != 0)
  {
    AdtJava*  JavaContext = (AdtJava*)pContext;

    JavaContext->logFlush();
  }
}


//  ----------------------------------------------------------------------------
//  AdtTapenadeVersion method implementions
//  ----------------------------------------------------------------------------
double AdtTapenadeVersion::TapenadeVersion = 0.0;

//  ----------------------------------------------------------------------------

AdtTapenadeVersion::AdtTapenadeVersion(bool bInit)
{
  if (bInit)
  {
    AdtTapenadeVersion::TapenadeVersion = 0.0;

    FILE* pPipe = popen("tapenade -d", "r");

    if (pPipe != 0)
    {
      char pBuffer[128] = {0};

      while(!feof(pPipe))
      {
        if (::fgets(pBuffer, 128, pPipe) != 0)
        {
          char   sName[16] = {0};
          double dVersion  = 0.0;

          if (::sscanf(pBuffer, "%9s%lf", sName, &dVersion) == 2)
          {
            for (int cn = 0 ; cn < 9 ; cn++)
            {
              sName[cn] = tolower(sName[cn]);
            }

            if (::strcmp(sName, "tapenade") == 0)
            {
              AdtTapenadeVersion::TapenadeVersion = dVersion;
              break;
            }
          }
        }
      }

      int nExitCode = pclose(pPipe);
    }
  }
}


//  ----------------------------------------------------------------------------
//  AdtCppScope method implementations
//  ----------------------------------------------------------------------------
AdtCppScope::AdtCppScope(AdtCppScope* pParent, const char* pName)
 : Name(pName),
   InheritsFromMap(),
   TypeMap(),
   SymbolMap(),
   ScopeMap()
{
  Parent = pParent;
}

//  ----------------------------------------------------------------------------

AdtCppScope::AdtCppScope(const AdtCppScope& rCopy)
 : Name(),
   InheritsFromMap(),
   TypeMap(),
   SymbolMap(),
   ScopeMap()
{
  FAIL();
}

//  ----------------------------------------------------------------------------

AdtCppScope::~AdtCppScope()
{

}

//  ----------------------------------------------------------------------------

void AdtCppScope::reset()
{
  AdtCppScopePtrByStringMapIter Iter;

  InheritsFromMap.clear();
  TypeMap.clear();
  SymbolMap.clear();

  for (Iter = ScopeMap.begin() ; Iter != ScopeMap.end() ; ++Iter)
  {
    AdtCppScope*  pScope = (*Iter).second;

    if (pScope != 0)
    {
      delete pScope;
    }
  }

  ScopeMap.clear();
}

//  ----------------------------------------------------------------------------

AdtCppScope* AdtCppScope::findScope(const char* pScopeName)
{
  AdtCppScope* pScope = 0;

  if (pScopeName != 0)
  {
    AdtCppScopePtrByStringMapIter Iter = ScopeMap.find(pScopeName);

    if (Iter != ScopeMap.end())
    {
      pScope = (*Iter).second;
    }
  }

  return (pScope);
}

//  ----------------------------------------------------------------------------

AdtCppScope* AdtCppScope::addScope(const char* pScopeName)
{
  AdtCppScope* pScope = 0;

  if (pScopeName != 0)
  {
    if (findScope(pScopeName) == 0)
    {
      pScope = new AdtCppScope(this, pScopeName);

      if (pScope != 0)
      {
        ScopeMap[pScopeName] = pScope;
      }
    }
  }

  return (pScope);
}

//  ----------------------------------------------------------------------------

void AdtCppScope::addType(const char* pTypeName)
{
  if (pTypeName != 0)
  {
    TypeMap[pTypeName] = 1;
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScope::addSymbol(const char* pSymbolName)
{
  if (pSymbolName != 0)
  {
    SymbolMap[pSymbolName] = 1;
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScope::inheritsFrom(const char* pParentScope)
{
  if (pParentScope != 0)
  {
    InheritsFromMap[pParentScope] = 1;
  }
}

//  ----------------------------------------------------------------------------

bool AdtCppScope::isTypeOrSymbol(string* pKeySymbolName, const char* pSymbolName, bool bCheckType, bool bRecurse) const
{
  bool bDefined = false;

  if (bRecurse)
  {
    const AdtCppScope*  pScope = this;

    while (!bDefined && (pScope != 0))
    {
      const AdtIntByStringMap&    rMap = bCheckType ? pScope->TypeMap : pScope->SymbolMap;
      AdtIntByStringMapConstIter  Iter = rMap.find(pSymbolName);

      if (Iter != rMap.end())
      {
        if (pKeySymbolName != 0)
        {
          *pKeySymbolName = (*Iter).first;
        }

        bDefined = true;
      }

      pScope = pScope->Parent;
    }
  }
  else
  {
    const AdtIntByStringMap&    rMap = bCheckType ? TypeMap : SymbolMap;
    AdtIntByStringMapConstIter  Iter = rMap.find(pSymbolName);

    if (Iter != rMap.end())
    {
      if (pKeySymbolName != 0)
      {
        *pKeySymbolName = (*Iter).first;
      }

      bDefined = true;
    }
  }

  if (!bDefined && (this->Parent != 0))
  {
    AdtIntByStringMapConstIter Iter;

    for (Iter = InheritsFromMap.begin() ; !bDefined && (Iter != InheritsFromMap.end()) ; ++Iter)
    {
      const string&       rScopeName  = (*Iter).first;
      const AdtCppScope*  pScope      = this->Parent->findScope(rScopeName);

      if (pScope != 0)
      {
        bDefined = pScope->isTypeOrSymbol(pKeySymbolName, pSymbolName, bCheckType, bRecurse);
      }
    }
  }

  return (bDefined);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::mapSymbolCase(string& rMappedSymbolName, const char* pSymbolName) const
{
  const char* pEndScope = strrchr(pSymbolName, ':');

  rMappedSymbolName = pSymbolName;

  if (isTypeOrSymbol(&rMappedSymbolName, pSymbolName, false))
  {
    if (pEndScope != 0)
    {
      // If the symbol name was found and there was a scoping prefix it will
      // have been clobbered by the call to isTypeOrSymbol() and we need to
      // restore it.
      string  sScope(pSymbolName, (size_t)(pEndScope + 1 - pSymbolName));

      rMappedSymbolName = sScope + rMappedSymbolName;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScope::qualifiedName(string& rName, bool bWithGlobal, bool bAsScope) const
{
  AdtCppScope* pParent = Parent;

  if (bAsScope && (Parent != 0))
  {
    rName = name() + "::";
  }
  else
  {
    rName = name();
  }

  while (pParent != 0)
  {
    // Don't include the global scope
    if (pParent->Parent != 0)
    {
      rName = pParent->name() + "::" + rName;
    }

    pParent = pParent->Parent;
  }

  if (bWithGlobal)
  {
    rName   = "::" + rName;
  }
}


//  ----------------------------------------------------------------------------
//  AdtCppScopeManager method implementations
//  ----------------------------------------------------------------------------
AdtCppScopeManager  AdtCppScopeManager::GlobalScopeManager;
bool                AdtCppScopeManager::MapNames = false;

//  ----------------------------------------------------------------------------

AdtCppScope* AdtCppScopeManager::findScope(AdtCppScope* pCurrentScope,
                                           const char*& pScopeName,
                                           bool bCreate) const
{
  string        sScopeName;
  AdtCppScope*  pScope = pCurrentScope;

  ASSERT(pScopeName != 0);

  while ((pScopeName != 0) && nestedNameSpecifier(sScopeName, pScopeName))
  {
    AdtCppScope*  pLastScope = pScope;

    if (sScopeName.length() == 0)
    {
      pScope = &GlobalScope;
    }
    else
    {
      pScope = pLastScope->findScope(sScopeName);
    }

    if ((pScope == 0) && bCreate)
    {
      pScope = pLastScope->addScope(sScopeName);
    }
  }

  return (pScope);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::setScope(const char* pScopeName)
{
  if (pScopeName != 0)
  {
    CurrentScope = findScope(CurrentScope, pScopeName, true);
  }
  else
  {
    CurrentScope = &GlobalScope;
  }
}

//  ----------------------------------------------------------------------------

AdtCppScopeManager::AdtCppScopeManager()
 : UsingMap(),
   ScopeStack(),
   GlobalScope(0, 0)
{
  CurrentScope = &GlobalScope;
}

//  ----------------------------------------------------------------------------

AdtCppScopeManager::AdtCppScopeManager(const AdtCppScopeManager& rCopy)
 : UsingMap(rCopy.UsingMap),
   ScopeStack(rCopy.ScopeStack),
   GlobalScope(rCopy.GlobalScope)
{
  CurrentScope = &GlobalScope;

  FAIL();
}

//  ----------------------------------------------------------------------------

AdtCppScopeManager::~AdtCppScopeManager()
{

}

//  ----------------------------------------------------------------------------

AdtCppScopeManager* AdtCppScopeManager::globalScopeManager()
{
  return (&GlobalScopeManager);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::resetGlobalScopeManager()
{
  GlobalScopeManager.reset();
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::addUserDefinedType(const char* pTypeName)
{
  GlobalScopeManager.GlobalScope.addType(pTypeName);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::mapNames(bool bEnable)
{
  MapNames = bEnable;
}

//  ----------------------------------------------------------------------------

bool AdtCppScopeManager::mapNames()
{
  return (MapNames);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::reset()
{
  UsingMap.clear();
  ScopeStack.clear();
  GlobalScope.reset();

  CurrentScope = &GlobalScope;
}

//  ----------------------------------------------------------------------------

bool AdtCppScopeManager::nestedNameSpecifier(string& sScopeName, const char*& pTypeName)
{
  bool bIsNested = false;

  // This method needs to scan from the beginning of pTypeName for :: and place
  // its prefix in sScopeName and its suffix pointed to by pTypeName
  pTypeName = AdtParse::nextWord(pTypeName);

  AdtParse::extractWord(sScopeName, ":", pTypeName, true);

  if (AdtParse::matchWord(pTypeName, "::"))
  {
    bIsNested = true;
  }

  return (bIsNested);
}

//  ----------------------------------------------------------------------------

bool AdtCppScopeManager::splitScope(const char* pScope, string& rScope, string& rSymbol)
{
  bool        bHasScopePrefix = false;
  const char* pEndScope       = pScope;

  do
  {
    // scan from the beginning of pScope for ::
    pEndScope = AdtParse::nextWord(pEndScope);

    AdtParse::wordLength(pEndScope, ":", &pEndScope, true);

    if (AdtParse::matchWord(pEndScope, "::"))
    {
      bHasScopePrefix = true;
    }
    else
    {
      break;
    }

  } while (true);

  if (bHasScopePrefix)
  {
    rScope.assign(pScope, pEndScope - pScope);

    rSymbol = pEndScope;
  }
  else
  {
    rScope.clear();

    rSymbol = pScope;
  }

  return (bHasScopePrefix);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::inheritsFrom(const char* pParentScope)
{
  if (CurrentScope != 0)
  {
    CurrentScope->inheritsFrom(pParentScope);
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::addUsing(const char* pUsing)
{
  if (pUsing != 0)
  {
    if (UsingMap.find(pUsing) == UsingMap.end())
    {
      UsingMap[pUsing] = 1;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::addUsingDeclaration(const char* pTypeName)
{
  string  sSymbolName;

  if ((CurrentScope != 0) && isType(pTypeName, &sSymbolName))
  {
    CurrentScope->addType(sSymbolName);
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::addType(const char* pTypeName)
{
  if (pTypeName != 0)
  {
    AdtCppScope*  pScope = findScope(CurrentScope, pTypeName, true);

    if (pScope != 0)
    {
      pScope->addType(pTypeName);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::addSymbol(const char* pSymbolName)
{
  if (!AdtCppScopeManager::mapNames() && (pSymbolName != 0))
  {
    AdtCppScope*  pScope = findScope(CurrentScope, pSymbolName, true);

    if (pScope != 0)
    {
      pScope->addSymbol(pSymbolName);
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtCppScopeManager::isTypeOrSymbol(string* pKeySymbolName, const char* pSymbolName, bool bCheckType, string* pDestBaseName) const
{
  bool bMatched = false;

  if (pSymbolName != 0)
  {
    // Search local scope for symbol
    const char*   pFindSymbolName = pSymbolName;
    AdtCppScope*  pScope          = findScope(CurrentScope, pFindSymbolName, false);

    if (pScope != 0)
    {
      if (pScope->isTypeOrSymbol(pKeySymbolName, pFindSymbolName, bCheckType, true))
      {
        if (pDestBaseName != 0)
        {
          *pDestBaseName = pFindSymbolName;
        }

        bMatched = true;
      }
    }

    if (!bMatched)
    {
      // Search 'using' scopes for symbol
      AdtIntByStringMapConstIter  Iter;

      for (Iter = UsingMap.begin() ; Iter != UsingMap.end() ; ++Iter)
      {
        const char* pUsingScopeName   = (*Iter).first;
        const char* pUsingSymbolName  = 0;
        string      sQualifiedSymbolName(pUsingScopeName);

        sQualifiedSymbolName += "::";
        sQualifiedSymbolName += pSymbolName;

        // check for relative scope
        pUsingSymbolName  = sQualifiedSymbolName.c_str();
        pScope            = findScope(CurrentScope, pUsingSymbolName, false);

        // check for absolute scope
        if (pScope == 0)
        {
          pUsingSymbolName  = sQualifiedSymbolName.c_str();
          pScope            = findScope(&GlobalScope, pUsingSymbolName, false);
        }

        if ((pScope != 0) && pScope->isTypeOrSymbol(pKeySymbolName, pUsingSymbolName, bCheckType, true))
        {
          if (pDestBaseName != 0)
          {
            *pDestBaseName = pFindSymbolName;
          }

          bMatched = true;
          break;
        }
      }
    }

    if (!bMatched)
    {
      // Search global scope for symbol
      pFindSymbolName = pSymbolName;

      if (GlobalScope.isTypeOrSymbol(pKeySymbolName, pFindSymbolName, bCheckType, true))
      {
        if (pDestBaseName != 0)
        {
          *pDestBaseName = pFindSymbolName;
        }

        bMatched = true;
      }
    }
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::pushScope(const char* pScope, bool bIsFunction)
{
  string sCurrentScopeName;

  CurrentScope->qualifiedName(sCurrentScopeName, true, true);

  ScopeStack.push_front(sCurrentScopeName);

  if (bIsFunction)
  {
    string  rScope;
    string  rSymbol;

    // pushScope() is called for all function definitions including global ones
    // so we check if the name has a scope prefix and if so, only then set a
    // new scope.
    if (splitScope(pScope, rScope, rSymbol))
    {
      setScope(rScope);
    }
  }
  else
  {
    // For other pushScope cases we need to suffix with ::
    string  sNextScope(pScope);

    sNextScope += "::";

    setScope(sNextScope);
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::popScope()
{
  string sScope(*ScopeStack.begin());

  setScope(sScope);
  ScopeStack.pop_front();
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::currentScopeName(string& rName)
{
  if (CurrentScope != 0)
  {
    CurrentScope->qualifiedName(rName);
  }
  else
  {
    rName = "";
  }
}

//  ----------------------------------------------------------------------------

void AdtCppScopeManager::qualifyName(string& rName)
{
  string  rQualifier;

  currentScopeName(rQualifier);

  if (!rQualifier.empty())
  {
    rName = rQualifier + "::" + rName;
  }
}


//  ----------------------------------------------------------------------------
//  AdtCppSplitNameAndComment method implementations
//  ----------------------------------------------------------------------------
AdtCppSplitNameAndComment::AdtCppSplitNameAndComment(const char* pNameAndPossibleComment)
 : Name(),
   Comment()
{
  split(pNameAndPossibleComment);
}

//  ----------------------------------------------------------------------------

AdtCppSplitNameAndComment::AdtCppSplitNameAndComment(const AdtCppSplitNameAndComment& rCopy)
 : Name(rCopy.Name),
   Comment(rCopy.Comment)
{

}

//  ----------------------------------------------------------------------------

AdtCppSplitNameAndComment::~AdtCppSplitNameAndComment()
{

}

//  ----------------------------------------------------------------------------

void AdtCppSplitNameAndComment::split(const char* pNameAndPossibleComment)
{
  if (pNameAndPossibleComment != 0)
  {
    const char* pChar         = pNameAndPossibleComment;
    const char* pNameEnd      = 0;
    const char* pCommentStart = 0;
    char        nQuote        = 0;
    bool        bIsString;
    bool        bInString     = false;

    Comment = "";

    if (pChar[0] == 'L')
    {
      bIsString = ((pChar[1] == '"') || (pChar[1] == '\''));

      if (bIsString)
      {
        nQuote = pChar[1];
      }
    }
    else
    {
      bIsString = ((pChar[0] == '"') || (pChar[0] == '\''));

      if (bIsString)
      {
        nQuote = pChar[0];
      }
    }

    while (*pChar != 0)
    {
      switch (*pChar)
      {
        case '\\':
        {
          if (bIsString)
          {
            // Ignore next character as it is escaped
            pChar++;
          }
          break;
        }

        case '\'':
        case '"':
        {
          if (bIsString && (*pChar == nQuote))
          {
            bInString = !bInString;
          }
          break;
        }

        case ' ':
        case '\t':
        {
          if (!bInString && (pNameEnd == 0))
          {
            pNameEnd = pChar;
          }
          break;
        }

        case '/':
        {
          if (!bInString)
          {
            if (pNameEnd == 0)
            {
              pNameEnd = pChar;
            }

            pCommentStart = pChar;

            switch (pChar[1])
            {
              case '/':
              {
                // End of line style comment, shouldn't be possible.
                FAIL();

                // fall thru
              }

              case '*':
              {
                // Multiline style comment.
                while (*pChar != 0)
                {
                  if (isalnum(*pChar) != 0)
                  {
                    int         nCount        = 0;
                    const char* pSymbolStart  = pChar;

                    while ((*pChar != 0) && (isalnum(*pChar) != 0))
                    {
                      nCount++;
                      pChar++;
                    }

                    string  sSymbol(pSymbolStart, nCount);

                    if (AdtCppScopeManager::mapNames())
                    {
                      string  sMappedSymbol;

                      AdtCppScopeManager::globalScopeManager()->mapSymbolCase(sMappedSymbol, sSymbol);

                      Comment += sMappedSymbol;
                    }
                    else
                    {
                      Comment += sSymbol;
                    }
                  }

                  Comment += pChar[0];

                  pChar++;
                }

                pChar--;
                break;
              }

              default:
              {
                // should never happen
                FAIL();
              }
            }
          }
          break;
        }

        default:
        {
          break;
        }
      }

      pChar++;
    }

    if (pNameEnd == 0)
    {
      pNameEnd = pChar;
    }

    Name.assign(pNameAndPossibleComment, pNameEnd - pNameAndPossibleComment);
  }
}


//  ----------------------------------------------------------------------------
//  AdtStringCache method implementations
//  ----------------------------------------------------------------------------
AdtStringCache::AdtStringCache()
 : StringMap()
{

}

//  ----------------------------------------------------------------------------

AdtStringCache::~AdtStringCache()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtStringCache::flush()
{
  StringMap.clear();
}

//  ----------------------------------------------------------------------------

const char* AdtStringCache::add(const char* pString, const string** ppCachedString)
{
  const char* pCopy = 0;

  if (ppCachedString != 0)
  {
    *ppCachedString = 0;
  }

  if (pString != 0)
  {
    size_t nLength = ::strlen(pString);

    if (nLength > 0)
    {
      string                        sFindKey(pString);
      AdtIntByStringMapCSConstIter  Iter = StringMap.find(sFindKey);

      if (Iter == StringMap.end())
      {
        StringMap[sFindKey] = 0;
        Iter                = StringMap.find(sFindKey);
      }

      pCopy = (*Iter).first;

      if (ppCachedString != 0)
      {
        *ppCachedString = &(*Iter).first;
      }
    }
  }

  return (pCopy);
}


//  ----------------------------------------------------------------------------
//  AdtFileCopy method implementations
//  ----------------------------------------------------------------------------
AdtFileCopy::AdtFileCopy(const char* pSrcFile, const char* pDestFile, bool bAppend)
{
  if ((pSrcFile != 0) && (pDestFile != 0))
  {
    FILE* SrcFile   = ::fopen(pSrcFile, "rb");
    FILE* DestFile  = ::fopen(pDestFile, bAppend ? "ab+" : "wb");

    if ((SrcFile != 0) && (DestFile != 0))
    {
      f_ptr   nLength;
      char    Buffer[4096] = {0};
      int     BufferLength = sizeof(Buffer) / sizeof(*Buffer);

      ::fseeko(SrcFile, 0, SEEK_END);

      nLength = ::ftello(SrcFile);

      ::fseeko(SrcFile, 0, SEEK_SET);

      while (nLength > BufferLength)
      {
        size_t  nRead;

        nRead = ::fread(Buffer, BufferLength, 1, SrcFile);
        ::fwrite(Buffer, BufferLength, 1, DestFile);

        nLength -= BufferLength;
      }

      if (nLength > 0)
      {
        size_t  nRead;

        nRead = ::fread(Buffer, (int)nLength, 1, SrcFile);
        ::fwrite(Buffer, (int)nLength, 1, DestFile);
      }
    }

    if (SrcFile != 0)
    {
      ::fclose(SrcFile);
    }

    if (DestFile != 0)
    {
      ::fclose(DestFile);
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFileCopy::~AdtFileCopy()
{
  // Do nothing
}


//  ----------------------------------------------------------------------------
//  AdtFile method implementations
//  ----------------------------------------------------------------------------
void AdtFile::writeChar(char nChar) const
{
  if (Handle != 0)
  {
    ::fprintf(Handle, "%c", nChar);
  }
  else if (OutputBuffer != 0)
  {
    (*OutputBuffer) += nChar;
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::writeString(const char* pString, size_t nStringLength) const
{
  if (Handle != 0)
  {
    if (nStringLength == (size_t)-1)
    {
      ::fprintf(Handle, "%s", pString);
    }
    else
    {
      ::fwrite(pString, sizeof(char), nStringLength, Handle);
    }
  }
  else if (OutputBuffer != 0)
  {
    if (nStringLength == (size_t)-1)
    {
      (*OutputBuffer) += pString;
    }
    else
    {
      (*OutputBuffer) += string(pString, 0, nStringLength);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::addDelayedNewlines() const
{
  while (DelayedNewlineCount > 0)
  {
    DelayedNewlineCount--;
    newline();
  }
}

//  ----------------------------------------------------------------------------

AdtFile::AdtFile(bool bIsFortranFile)
 : FileName()
{
  Handle              = 0;
  OutputBuffer        = 0;
  TabSize             = 2;
  Indent              = 0;
  LastNewlinePos      = 0;
  DelayedNewlineCount = 0;
  IsFortranFile       = bIsFortranFile;
  IsEnabled           = false;
  IsComment           = false;
  LineCharCount       = 0;
}

//  ----------------------------------------------------------------------------

AdtFile::~AdtFile()
{
  close();
}

//  ----------------------------------------------------------------------------

bool AdtFile::open(const char* sFileName, const char* sMode)
{
  close();

  if ((sFileName != 0) && (sMode != 0))
  {
    Handle = ::fopen(sFileName, sMode);

    OutputBuffer        = 0;
    Indent              = 0;
    LastNewlinePos      = 0;
    DelayedNewlineCount = 0;
    LineCharCount       = 0;
    IsEnabled           = true;
    IsComment           = false;
  }

  return (Handle != 0);
}

//  ----------------------------------------------------------------------------

bool AdtFile::open(string& rBuffer)
{
  close();

  OutputBuffer        = &rBuffer;
  Indent              = 0;
  LastNewlinePos      = 0;
  DelayedNewlineCount = 0;
  LineCharCount       = 0;
  IsEnabled           = true;
  IsComment           = false;

  return (OutputBuffer != 0);
}

//  ----------------------------------------------------------------------------

void AdtFile::close()
{
  if (Handle != 0)
  {
    ::fclose(Handle);
  }

  OutputBuffer        = 0;
  Handle              = 0;
  LastNewlinePos      = 0;
  DelayedNewlineCount = 0;
  LineCharCount       = 0;
  IsEnabled           = false;
  IsComment           = false;
}

//  ----------------------------------------------------------------------------

void AdtFile::newline() const
{
  if (IsEnabled)
  {
    addDelayedNewlines();

    if (isOpen())
    {
      int nWidth = Indent * TabSize;

      writeString("\n");

      if (Handle != 0)
      {
        LastNewlinePos = ::ftello(Handle);

        ::fprintf(Handle, "%*s",nWidth, "");
      }
      else
      {
        LastNewlinePos = OutputBuffer->length();

        if (nWidth > 0)
        {
          (*OutputBuffer) += string(nWidth, ' ');
        }
      }

      LineCharCount = nWidth;
      IsComment     = false;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::homeline() const
{
  if (IsEnabled)
  {
    addDelayedNewlines();

    if (isOpen() && (LastNewlinePos >= 0))
    {
      int nWidth = Indent * TabSize;

      if (Handle != 0)
      {
        ::fseeko(Handle, LastNewlinePos, SEEK_SET);
        ::fprintf(Handle, "%*s",nWidth, "");
      }
      else
      {
        OutputBuffer->left((int)LastNewlinePos);

        if (nWidth > 0)
        {
          (*OutputBuffer) += string(nWidth, ' ');
        }
      }

      LineCharCount = nWidth;
      IsComment     = false;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::delayedNewlines(int nCount) const
{
  if ((Handle != 0) && IsEnabled)
  {
    DelayedNewlineCount = nCount;
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::write(const char* pString) const
{
  if ((pString != 0) && isOpen() && IsEnabled)
  {
    if (IsFortranFile && !IsComment)
    {
      size_t      nWriteableChars = 72 - LineCharCount - 1;
      size_t      nComment        = 0;
      const char* pComment        = ::strchr(pString, '!');

      if (!IsComment && (pComment != 0))
      {
        nComment  = (pComment - pString) / sizeof(char);
        IsComment = (nComment <= nWriteableChars);
      }

      if (IsComment)
      {
        writeString(pString);
      }
      else
      {
        size_t  nStringLength = ::strlen(pString) - nComment;

        while (nStringLength > nWriteableChars)
        {
          writeString(pString, nWriteableChars);

          pString += nWriteableChars;

          writeChar('&');

          newline();

          writeChar('&');

          LineCharCount++;

          nWriteableChars = 72 - LineCharCount - 1;
          nStringLength   = ::strlen(pString) - nComment;
        }

        nStringLength = ::strlen(pString);

        writeString(pString, nStringLength);

        LineCharCount += nStringLength;
      }
    }
    else
    {
      writeString(pString);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::write(char nChar) const
{
  if (isOpen() && IsEnabled)
  {
    if (IsFortranFile && !IsComment)
    {
      IsComment = (nChar == '!');
    }

    if (IsFortranFile && !IsComment)
    {
      size_t nWriteableChars = 72 - LineCharCount - 1;

      if (nWriteableChars <= 1)
      {
        writeChar('&');

        newline();

        writeChar('&');

        LineCharCount = 1;
      }
    }

    writeChar(nChar);
    LineCharCount++;
  }
}

//  ----------------------------------------------------------------------------

void AdtFile::readLines(AdtStringList& rStringList)
{
  string sString;

  if (isOpen() && IsEnabled)
  {
    bool  bMore = true;

    while (bMore)
    {
      char  sBuffer[1024] = {0};

      bMore = (::fscanf(Handle, "%1024[^\n]", sBuffer) != EOF);

      sString += sBuffer;

      if (bMore)
      {
        char  sDelimeter[2] = {0};

        bMore = (::fscanf(Handle, "%1c", sDelimeter) != EOF);

        if (sDelimeter[0] == '\n')
        {
          rStringList.push_back(sString);
          sString.clear();
        }
      }
    }
  }
}


//  ----------------------------------------------------------------------------
//  AdtParse namespace functions
//  ----------------------------------------------------------------------------
size_t AdtParse::wordLength(const char* pText,
                            const char* pWordDelimiters,
                            const char** ppEndWord,
                            bool bMustBeDelimited)
{
  int         nLength   = 0;
  const char* pWord     = pText;
  bool        bContinue = true;

  while ((*pWord != '\0') && bContinue)
  {
    if (strchr(pWordDelimiters, *pWord) != 0)
    {
      bContinue = false;
    }
    else
    {
      bContinue = true;
      pWord++;
      nLength++;
    }
  }

  if (bMustBeDelimited && bContinue)
  {
    pWord   = pText;
    nLength = 0;
  }

  if (ppEndWord != 0)
  {
    *ppEndWord = pWord;
  }

  return (nLength);
}

//  ----------------------------------------------------------------------------

size_t AdtParse::wordLength(const char* pText,
                            const char** ppWordDelimiters,
                            const char** ppEndWord,
                            bool bMustBeDelimited)
{
  size_t      nLength   = 0;
  int         cn        = 0;
  const char* pEndWord  = pText;

  while (*ppWordDelimiters[cn] != '\0')
  {
    const char* pWord = strstr(pText, ppWordDelimiters[cn]);

    if (pWord != 0)
    {
      size_t nThisLength = pWord - pText;

      if ((nLength == 0) || (nLength > nThisLength))
      {
        nLength   = nThisLength;
        pEndWord  = pWord;
      }
    }

    cn++;
  }

  if (!bMustBeDelimited && (nLength == 0))
  {
    nLength   = strlen(pText);
    pEndWord  = pText + nLength;
  }

  if (ppEndWord != 0)
  {
    *ppEndWord = pEndWord;
  }

  return (nLength);
}

//  ----------------------------------------------------------------------------

size_t AdtParse::bracketedWordLength(const char* pText,
                                     const char* pWordDelimiters,
                                     const char* pOpenBrackets,
                                     const char* pCloseBrackets,
                                     const char** ppEndWord,
                                     bool bMustBeDelimited)
{
  size_t      nLength   = 0;
  size_t      nDepth    = 0;
  const char* pWord     = pText;
  bool        bContinue = true;

  while ((*pWord != '\0') && bContinue)
  {
    if ((pOpenBrackets != 0) && (strchr(pOpenBrackets, *pWord) != 0))
    {
      nDepth++;
    }
    else if ((pCloseBrackets != 0) && (strchr(pCloseBrackets, *pWord) != 0))
    {
      nDepth--;
    }

    if ((strchr(pWordDelimiters, *pWord) != 0) && (nDepth <= 0))
    {
      if ((nDepth == 0) && (pCloseBrackets != 0) && (strchr(pCloseBrackets, *pWord) != 0))
      {
        pWord++;
        nLength++;
      }

      bContinue = false;
    }
    else
    {
      bContinue = true;
      pWord++;
      nLength++;
    }
  }

  if (bMustBeDelimited && bContinue)
  {
    pWord   = pText;
    nLength = 0;
  }

  if (ppEndWord != 0)
  {
    *ppEndWord = pWord;
  }

  return (nLength);
}

//  ----------------------------------------------------------------------------

size_t AdtParse::bracketedWordLength(const char* pText,
                                     const char** ppWordDelimiters,
                                     const char** ppOpenBrackets,
                                     const char** ppCloseBrackets,
                                     const char** ppEndWord,
                                     bool bMustBeDelimited)
{
  size_t      nLength   = 0;
  size_t      nDepth    = 0;
  const char* pWord     = pText;
  bool        bContinue = true;

  while ((*pWord != '\0') && bContinue)
  {
    bool  bNext = true;
    int   cn    = 0;

    if ((ppOpenBrackets != 0) && (ppCloseBrackets != 0))
    {
      while ((*ppOpenBrackets[cn] != '\0') && (*ppCloseBrackets[cn] != '\0'))
      {
        if (strstr(pWord, ppOpenBrackets[cn]) == pWord)
        {
          size_t nBracketLength = strlen(ppOpenBrackets[cn]);

          pWord   += nBracketLength;
          nLength += nBracketLength;
          bNext    = false;

          nDepth++;
          break;
        }
        else if (strstr(pWord, ppCloseBrackets[cn]) == pWord)
        {
          size_t nBracketLength = strlen(ppOpenBrackets[cn]);

          pWord   += nBracketLength;
          nLength += nBracketLength;
          bNext    = false;

          nDepth--;
          break;
        }

        cn++;
      }
    }

    cn = 0;

    if ((ppWordDelimiters != 0) && (nDepth <= 0))
    {
      while (*ppWordDelimiters[cn] != '\0')
      {
        if (strstr(pWord, ppWordDelimiters[cn]) == pWord)
        {
          bNext = false;

          if ((nDepth == 0) && (ppCloseBrackets != 0))
          {
            cn = 0;

            while ((*ppCloseBrackets[cn] != '\0') && (*ppCloseBrackets[cn] != '\0'))
            {
              if (strstr(pWord, ppCloseBrackets[cn]) == pWord)
              {
                size_t nBracketLength = strlen(ppOpenBrackets[cn]);

                pWord   += nBracketLength;
                nLength += nBracketLength;
                break;
              }

              cn++;
            }
          }

          bContinue = false;
          break;
        }

        cn++;
      }
    }

    if (bNext)
    {
      pWord++;
      nLength++;
    }
  }

  if (bMustBeDelimited && bContinue)
  {
    pWord   = pText;
    nLength = 0;
  }

  if (ppEndWord != 0)
  {
    *ppEndWord = pWord;
  }

  return (nLength);
}

//  ----------------------------------------------------------------------------

bool AdtParse::stepOverWord(const char* pWordDelimiters,
                            const char*& rpText,
                            bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = wordLength(rpText, pWordDelimiters, &pEndWord, bMustBeDelimited);
  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::stepOverWord(const char** ppWordDelimiters,
                            const char*& rpText,
                            bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = wordLength(rpText, ppWordDelimiters, &pEndWord, bMustBeDelimited);
  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::extractWord(string& sWord,
                           const char* pWordDelimiters,
                           const char*& rpText,
                           bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = wordLength(rpText, pWordDelimiters, &pEndWord, bMustBeDelimited);

  if (nLength > 0)
  {
    sWord = string(rpText, 0, nLength);
  }
  else
  {
    sWord = "";
  }

  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::extractWord(string& sWord,
                           const char** ppWordDelimiters,
                           const char*& rpText,
                           bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = wordLength(rpText, ppWordDelimiters, &pEndWord, bMustBeDelimited);

  if (nLength > 0)
  {
    sWord = string(rpText, 0, nLength);
  }
  else
  {
    sWord = "";
  }

  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::matchExtractWord(string& sWord,
                                const char* pDelimitingWord,
                                const char*& rpText)
{
  bool        bMatched  = false;
  const char* pWordEnd  = strstr(rpText, pDelimitingWord);

  if (pWordEnd != 0)
  {
    sWord     = string(rpText, 0, pWordEnd - rpText);
    rpText    = pWordEnd;
    bMatched  = true;
  }
  else
  {
    sWord     = "";
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

bool AdtParse::bracketedExtractWord(string& sWord,
                                    const char* pWordDelimiters,
                                    const char* pOpenBrackets,
                                    const char* pCloseBrackets,
                                    const char*& rpText,
                                    bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = bracketedWordLength(rpText,
                                pWordDelimiters,
                                pOpenBrackets,
                                pCloseBrackets,
                                &pEndWord,
                                bMustBeDelimited);

  if (nLength > 0)
  {
    sWord = string(rpText, 0, nLength);
  }
  else
  {
    sWord = "";
  }

  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::bracketedExtractWord(string& sWord,
                                    const char** ppWordDelimiters,
                                    const char** ppOpenBrackets,
                                    const char** ppCloseBrackets,
                                    const char*& rpText,
                                    bool bMustBeDelimited)
{
  size_t      nLength;
  const char* pEndWord = rpText;

  nLength = bracketedWordLength(rpText,
                                ppWordDelimiters,
                                ppOpenBrackets,
                                ppCloseBrackets,
                                &pEndWord,
                                bMustBeDelimited);

  if (nLength > 0)
  {
    sWord = string(rpText, 0, nLength);
  }
  else
  {
    sWord = "";
  }

  rpText  = pEndWord;

  return (nLength > 0);
}

//  ----------------------------------------------------------------------------

bool AdtParse::previousMatchWord(const char*& rpChar,
                                 const char* pFirstChar,
                                 const char* pWord,
                                 bool bCaseSensitive)
{
  const char* pParseText  = rpChar;
  const char* pMatchWord  = pWord;
  const char* pFirstWord  = pWord;
  bool        bMatched    = false;

  while (*pMatchWord != '\0')
  {
    pMatchWord++;
  }

  pMatchWord--;

  while ((pMatchWord >= pFirstWord) && (pParseText != pFirstChar))
  {
    bMatched = bCaseSensitive ? *pMatchWord             == *pParseText
                              : ::tolower(*pMatchWord)  == ::tolower(*pParseText);

    pMatchWord--;
    pParseText--;

    if (!bMatched)
    {
      break;
    }
  }

  if (bMatched)
  {
    rpChar = pParseText;
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

bool AdtParse::matchWord(const char*& rpChar,
                         const char* pWord,
                         bool bCaseSensitive)
{
  const char* pParseText  = rpChar;
  const char* pMatchWord  = pWord;
  bool        bMatched    = false;

  while ((*pMatchWord != '\0') && (*pParseText != '\0'))
  {
    bMatched = bCaseSensitive ? *pMatchWord             == *pParseText
                              : ::tolower(*pMatchWord)  == ::tolower(*pParseText);

    pMatchWord++;
    pParseText++;

    if (!bMatched)
    {
      break;
    }
  }

  if (bMatched)
  {
    rpChar = pParseText;
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

int AdtParse::matchWhichWord(const char*& pChar,
                             const char** ppWords,
                             int nWords,
                             bool bCaseSensitive)
{
  int nWhich = -1;

  if ((ppWords != 0) && (nWords > 0))
  {
    for (int cn = 0 ; cn < nWords ; cn++)
    {
      if (AdtParse::matchWord(pChar, ppWords[cn], bCaseSensitive))
      {
        nWhich = cn;
        break;
      }
    }
  }

  return (nWhich);
}

//  ----------------------------------------------------------------------------

const char* AdtParse::previousWord(const char* pChar,
                                   const char* pFirstChar,
                                   size_t* pnCount)
{
  const char* pWord     = pChar;
  bool        bContinue = true;
  size_t      nCount    = 0;

  while ((pWord != pFirstChar) && bContinue)
  {
    switch (*pWord)
    {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
      case 0:
      {
        bContinue = true;
        pWord--;
        nCount++;
        break;
      }

      default:
      {
        bContinue = false;
        break;
      }
    }
  }

  if (pnCount != 0)
  {
    *pnCount = nCount;
  }

  return (pWord);
}

//  ----------------------------------------------------------------------------

const char* AdtParse::nextWord(const char* pChar, size_t* pnCount, bool bIncludeNewline)
{
  const char* pWord     = pChar;
  bool        bContinue = true;
  size_t      nCount    = 0;

  while ((*pWord != '\0') && bContinue)
  {
    switch (*pWord)
    {
      case '\n':
      case '\r':
      {
        if (!bIncludeNewline)
        {
          bContinue = false;
          break;
        }
        // fall thru
      }

      case ' ':
      case '\t':
      {
        bContinue = true;
        pWord++;
        nCount++;
        break;
      }

      default:
      {
        bContinue = false;
        break;
      }
    }
  }

  if (pnCount != 0)
  {
    *pnCount = nCount;
  }

  return (pWord);
}

//  ----------------------------------------------------------------------------

const char* AdtParse::nextLine(const char* pChar, size_t* pnCount)
{
  const char* pWord     = pChar;
  bool        bContinue = true;
  size_t      nCount    = 0;

  while ((*pWord != '\0') && bContinue)
  {
    switch (*pWord)
    {
      case '\n':
      case '\r':
      {
        bContinue = false;
        break;
      }

      default:
      {
        bContinue = true;
        pWord++;
        nCount++;
        break;
      }
    }
  }

  switch (*pWord)
  {
    case '\n':
    {
      if (pWord[1] == '\r')
      {
        pWord++;
        nCount++;
      }
      break;
    }

    case '\r':
    {
      if (pWord[1] == '\n')
      {
        pWord++;
        nCount++;
      }
      break;
    }

    default:
    {
      break;
    }
  }

  if (pnCount != 0)
  {
    *pnCount = nCount;
  }

  return (pWord);
}


//  ----------------------------------------------------------------------------
//  AdtGenericAbstractCommand method implementations
//  ----------------------------------------------------------------------------
AdtGenericAbstractCommand::AdtGenericAbstractCommand()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtGenericAbstractCommand::AdtGenericAbstractCommand(const AdtGenericAbstractCommand& rCopy)
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtGenericAbstractCommand::~AdtGenericAbstractCommand()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

bool AdtGenericAbstractCommand::isType(const char* pType) const
{
  bool bIsType = (::strcmp("AdtGenericAbstractCommand", pType) == 0);

  return (bIsType);
}

//  ----------------------------------------------------------------------------

const char* AdtGenericAbstractCommand::type() const
{
  return ("AdtGenericAbstractCommand");
}


//  ----------------------------------------------------------------------------
//  AdtGenericDefineCommand class
//  ----------------------------------------------------------------------------
//  This class implements the macro define command.
//  ----------------------------------------------------------------------------
AdtGenericDefineCommand::AdtGenericDefineCommand(const char* pCompressedMacro,
                                                 const char* pExpandedMacro,
                                                 const char* pVariableDefinitions,
                                                 const char* pCommandBlockName)
 : AdtGenericAbstractCommand(),
   CompressedMacro(),
   ExpandedMacro(),
   VariableDefinitions(),
   CommandBlockName()
{
  if (pCompressedMacro != 0)
  {
    CompressedMacro = pCompressedMacro;
  }

  if (pExpandedMacro != 0)
  {
    ExpandedMacro = pExpandedMacro;
  }

  if (pVariableDefinitions != 0)
  {
    VariableDefinitions = pVariableDefinitions;
  }

  if (pCommandBlockName != 0)
  {
    CommandBlockName = pCommandBlockName;
  }
}

//  ----------------------------------------------------------------------------

AdtGenericDefineCommand::AdtGenericDefineCommand(const AdtGenericDefineCommand& rCopy)
 : AdtGenericAbstractCommand(rCopy),
   CompressedMacro(rCopy.CompressedMacro),
   ExpandedMacro(rCopy.ExpandedMacro),
   VariableDefinitions(rCopy.VariableDefinitions),
   CommandBlockName(rCopy.CommandBlockName)
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtGenericDefineCommand::~AdtGenericDefineCommand()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

bool AdtGenericDefineCommand::execute(AdtDelphi& rParent,
                                      FILE*& yyDelphiin,
                                      int& yyDelphidebug,
                                      parse_fn yyDelphiparse)
{
  bool  bExecuted    = false;
  char* pTmpFileName = tempnam(0, "adttmp");
  FILE* pTempFile    = ::fopen(pTmpFileName, "w+");

  if (pTempFile != 0)
  {
    //Write the macro definition to a temporary file
    if (VariableDefinitions.length() > 0)
    {
      ::fprintf(pTempFile, "%s %s; add_variables %s;", (const char*)CompressedMacro, (const char*)ExpandedMacro, (const char*)VariableDefinitions);
    }
    else
    {
      ::fprintf(pTempFile, "%s %s;", (const char*)CompressedMacro, (const char*)ExpandedMacro);
    }

    string sContext(CommandBlockName);

    sContext += " => Macro ";
    sContext += CompressedMacro;

    //Use the Delphi parser to parse the macro
    ::fseeko(pTempFile, 0, SEEK_SET);

    yyDelphidebug = 0;
    yyDelphiin    = pTempFile;

    yyDelphirestart(yyDelphiin);
    yyDelphi_resetLineNumber(sContext);
    yyDelphiparse();
    yyDelphi_endParse();
    yyDelphi_resetLineNumber(0);
    yyDelphi_releaseBuffer();

    yyDelphidebug = 0;
    yyDelphiin    = 0;

    ::fclose(pTempFile);
    ::unlink(pTmpFileName);
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericDefineCommand::execute(AdtCpp& rParent,
                                      FILE*& yyCppin,
                                      int& yyCppdebug,
                                      parse_fn yyCppparse)
{
  bool  bExecuted    = false;
  char* pTmpFileName = tempnam(0, "adttmp");
  FILE* pTempFile    = ::fopen(pTmpFileName, "w+");

  if (pTempFile != 0)
  {
    //Write the macro definition to a temporary file
    if (VariableDefinitions.length() > 0)
    {
      ::fprintf(pTempFile, "%s %s add_variables %s", (const char*)CompressedMacro, (const char*)ExpandedMacro, (const char*)VariableDefinitions);
    }
    else
    {
      ::fprintf(pTempFile, "%s %s", (const char*)CompressedMacro, (const char*)ExpandedMacro);
    }

    string sContext(CommandBlockName);

    sContext += " => Macro ";
    sContext += CompressedMacro;

    //Use the Cpp parser to parse the macro
    ::fseeko(pTempFile, 0, SEEK_SET);

    // Need to disable name mapping for macro expansion compilation
    bool bMapNames = AdtCppScopeManager::mapNames();

    AdtCppScopeManager::mapNames(false);

    yyCppdebug  = 0;
    yyCppin     = pTempFile;

    yyCpprestart(yyCppin);
    yyCpp_resetLineNumber(sContext);
    yyCppparse();
    yyCpp_endParse();
    yyCpp_resetLineNumber(0);
    yyCpp_releaseBuffer();

    yyCppdebug  = 0;
    yyCppin     = 0;

    ::fclose(pTempFile);
    ::unlink(pTmpFileName);

    AdtCppScopeManager::mapNames(bMapNames);
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericDefineCommand::execute(AdtJava& rParent,
                                      FILE*& yyJavain,
                                      int& yyJavadebug,
                                      parse_fn yyJavaparse)
{
  bool  bExecuted    = false;
  char* pTmpFileName = tempnam(0, "adttmp");
  FILE* pTempFile    = ::fopen(pTmpFileName, "w+");

  if (pTempFile != 0)
  {
    //Write the macro definition to a temporary file
    if (VariableDefinitions.length() > 0)
    {
      ::fprintf(pTempFile, "%s %s; add_variables %s;", (const char*)CompressedMacro, (const char*)ExpandedMacro, (const char*)VariableDefinitions);
    }
    else
    {
      ::fprintf(pTempFile, "%s %s;", (const char*)CompressedMacro, (const char*)ExpandedMacro);
    }

    string sContext(CommandBlockName);

    sContext += " => Macro ";
    sContext += CompressedMacro;

    //Use the Java parser to parse the macro
    ::fseeko(pTempFile, 0, SEEK_SET);

    yyJavadebug  = 0;
    yyJavain     = pTempFile;

    yyJavarestart(yyJavain);
    yyCpp_resetLineNumber(sContext);
    yyJavaparse();
    yyJava_endParse();
    yyJava_resetLineNumber(0);
    yyJava_releaseBuffer();

    yyJavadebug  = 0;
    yyJavain     = 0;

    ::fclose(pTempFile);
    ::unlink(pTmpFileName);
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

implTypeWithoutCopy(AdtGenericDefineCommand, AdtGenericAbstractCommand);


//  ----------------------------------------------------------------------------
//  AdtGenericTypeMapCommand class
//  ----------------------------------------------------------------------------
//  This class implements the type map command.
//  ----------------------------------------------------------------------------
AdtGenericTypeMapCommand::AdtGenericTypeMapCommand(const char* pGenericType,
                                                   const char* pFortranType,
                                                   const char* pFortranSize)
 : AdtGenericAbstractCommand(),
   GenericType(),
   FortranType(),
   FortranSize()
{
  if (pGenericType != 0)
  {
    GenericType = pGenericType;
  }

  if (pFortranType != 0)
  {
    FortranType = pFortranType;
  }

  if (pFortranSize != 0)
  {
    FortranSize = pFortranSize;
  }
}

//  ----------------------------------------------------------------------------

AdtGenericTypeMapCommand::AdtGenericTypeMapCommand(const AdtGenericTypeMapCommand& rCopy)
 : AdtGenericAbstractCommand(rCopy),
   GenericType(rCopy.GenericType),
   FortranType(rCopy.FortranType),
   FortranSize(rCopy.FortranSize)
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtGenericTypeMapCommand::~AdtGenericTypeMapCommand()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

bool AdtGenericTypeMapCommand::execute(AdtDelphi& rParent,
                                       FILE*& yyDelphiin,
                                       int& yyDelphidebug,
                                       parse_fn yyDelphiparse)
{
  AdtDelphiBase::addFortranTypeMap(GenericType,
                                   FortranType,
                                   FortranSize);

  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtGenericTypeMapCommand::execute(AdtCpp& rParent,
                                       FILE*& yyCppin,
                                       int& yyCppdebug,
                                       parse_fn yyCppparse)
{
  AdtCppBase::addFortranTypeMap(GenericType,
                                FortranType,
                                FortranSize);

  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtGenericTypeMapCommand::execute(AdtJava& rParent,
                                       FILE*& yyJavain,
                                       int& yyJavadebug,
                                       parse_fn yyJavaparse)
{
  AdtJavaBase::addFortranTypeMap(GenericType,
                                 FortranType,
                                 FortranSize);

  return (true);
}

//  ----------------------------------------------------------------------------

implTypeWithoutCopy(AdtGenericTypeMapCommand, AdtGenericAbstractCommand);


//  ----------------------------------------------------------------------------
//  AdtGenericCommandBlock method implementations
//  ----------------------------------------------------------------------------
void AdtGenericCommandBlock::flush(AdtGenericAbstractCommandPtrList& rList)
{
  while (rList.size() > 0)
  {
    AdtGenericAbstractCommand* pCommand;

    pCommand = rList.back();
    rList.pop_back();

    if (pCommand != 0)
    {
      delete pCommand;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtGenericCommandBlock::add(AdtGenericAbstractCommandPtrList& rList, AdtGenericAbstractCommand* pCommand)
{
  if (pCommand != 0)
  {
    rList.push_back(pCommand);
  }
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtGenericAbstractCommandPtrList& rList,
                                     AdtDelphi& rParent,
                                     FILE*& yyDelphiin,
                                     int& yyDelphidebug,
                                     parse_fn yyDelphiparse)
{
  bool bExecuted = false;

  AdtGenericAbstractCommandPtrListIter Iter;
  AdtGenericAbstractCommand*           pCommand = 0;

  //Do define commands
  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    pCommand = *Iter;

    if (pCommand != 0)
    {
      bExecuted = (pCommand->execute(rParent, yyDelphiin, yyDelphidebug, yyDelphiparse) ? true : bExecuted);
    }
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtGenericAbstractCommandPtrList& rList,
                                     AdtCpp& rParent,
                                     FILE*& yyCppin,
                                     int& yyCppdebug,
                                     parse_fn yyCppparse)
{
  bool bExecuted = false;

  AdtGenericAbstractCommandPtrListIter Iter;
  AdtGenericAbstractCommand*           pCommand = 0;

  //Do define commands
  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    pCommand = *Iter;

    if (pCommand != 0)
    {
      bExecuted = (pCommand->execute(rParent, yyCppin, yyCppdebug, yyCppparse) ? true : bExecuted);
    }
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtGenericAbstractCommandPtrList& rList,
                                     AdtJava& rParent,
                                     FILE*& yyJavain,
                                     int& yyJavadebug,
                                     parse_fn yyJavaparse)
{
  bool bExecuted = false;

  AdtGenericAbstractCommandPtrListIter Iter;
  AdtGenericAbstractCommand*           pCommand = 0;

  //Do define commands
  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    pCommand = *Iter;

    if (pCommand != 0)
    {
      bExecuted = (pCommand->execute(rParent, yyJavain, yyJavadebug, yyJavaparse) ? true : bExecuted);
    }
  }

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

const char* AdtGenericCommandBlock::parseDefine(const char* pChar, int nMode, const char* pCommandBlockName)
{
  //Trying to match a definition like this:
  //
  //  #define XCOPY(a,b,c)  for i__:=1 to c do
  //                        begin
  //                          a[i__]:=b[i__];
  //                        end;
  //                        add_variables
  //                        i__ : integer;
  string      sCompressedMacro;
  string      sExpandedMacro;
  string      sVariableDefinitions;
  const char* pParseText        = AdtParse::nextWord(pChar);
  const char* pStatementOrigin  = 0;
  size_t      nStatementLength  = 0;
  bool        bHasAddVariables  = false;
  bool        bAddDefine        = false;

  AdtParse::extractWord(sCompressedMacro, " \t\n\r", pParseText);

  pParseText        = AdtParse::nextWord(pParseText);
  pStatementOrigin  = pParseText;
  nStatementLength  = AdtParse::wordLength(pParseText, " \t\n\r", &pParseText);

  while ((*pParseText != '\0') && (*pParseText != '#'))
  {
    size_t nLength;

    nLength     = 0;
    pParseText  = AdtParse::nextWord(pParseText, &nLength);

    if (AdtParse::matchWord(pParseText, "add_variables"))
    {
      pParseText       = AdtParse::nextWord(pParseText);
      bHasAddVariables = true;
      break;
    }
    else
    {
      nStatementLength += AdtParse::wordLength(pParseText, " \t\n\r#", &pParseText);
      nStatementLength += nLength;
    }
  }

  if (nStatementLength > 0)
  {
    sExpandedMacro = string(pStatementOrigin, 0, nStatementLength);
  }

  if (bHasAddVariables)
  {
    const char* pDeclOrigin = pParseText;
    size_t      nDeclLength = 0;

    while ((*pParseText != '\0') && (*pParseText != '#'))
    {
      size_t nLength;

      nLength       = 0;
      pParseText    = AdtParse::nextWord(pParseText, &nLength);
      nDeclLength  += AdtParse::wordLength(pParseText, " \t\n\r#", &pParseText);
      nDeclLength  += nLength;
    }

    if (nDeclLength > 0)
    {
      sVariableDefinitions = string(pDeclOrigin, 0, nDeclLength);
    }
  }

  switch (nMode)
  {
    // Don't care mode
    default:
    case 0:
    {
      bAddDefine  = true;
      break;
    }

    // Forward mode
    case 1:
    {
      bAddDefine  = IsForwardMode;
      break;
    }

    // Backward mode
    case 2:
    {
      bAddDefine  = !IsForwardMode;
      break;
    }
  }

  if (bAddDefine)
  {
    add(DefineCommandList, new AdtGenericDefineCommand(sCompressedMacro,
                                                       sExpandedMacro,
                                                       sVariableDefinitions,
                                                       pCommandBlockName));
  }

  return (pParseText);
}

//  ----------------------------------------------------------------------------

const char* AdtGenericCommandBlock::parseInclude(const char* pChar)
{
  //Trying to match a definition like this:
  //
  //  #include instructions.txt
  string      sFilename;
  const char* pParseText  = AdtParse::nextWord(pChar);
  FILE*       pFile       = 0;

  AdtParse::extractWord(sFilename, " \t\n\r", pParseText);

  pFile = ::fopen(sFilename, "rt");

  if (pFile != 0)
  {
    f_ptr nFileSize = 0;

    ::fseeko(pFile, 0, SEEK_END);
    nFileSize = ::ftello(pFile);
    ::fseeko(pFile, 0, SEEK_SET);

    if (nFileSize > 0)
    {
      char*   pBuffer = (char*)::malloc((((size_t)nFileSize) + 1) * sizeof(char));

      if (pBuffer != 0)
      {
        size_t  nRead;

        ::memset(pBuffer, 0, (((size_t)nFileSize) + 1) * sizeof(char));
        nRead = ::fread(pBuffer, sizeof(char), (size_t)nFileSize, pFile);

        parseAppend(pBuffer, sFilename);
        ::free(pBuffer);
      }
    }
  }
  else
  {
    ::printf("WARNING: Unable to open command include %s\n", (const char*)sFilename);
  }

  pParseText = AdtParse::nextWord(pParseText);

  return (pParseText);
}

//  ----------------------------------------------------------------------------

const char* AdtGenericCommandBlock::parseTypeMap(const char* pChar)
{
  //Trying to match a definition like this:
  //
  //  #type_map   ARRAY_1D : DOUBLE PRECISION, (:)
  string      sGenericType;
  string      sFortranType;
  string      sFortranSize;
  const char* pParseText  = AdtParse::nextWord(pChar);

  AdtParse::extractWord(sGenericType, " \t\n\r", pParseText);

  pParseText = AdtParse::nextWord(pParseText);

  if (AdtParse::matchWord(pParseText, ":"))
  {
    pParseText = AdtParse::nextWord(pParseText);

    AdtParse::extractWord(sFortranType, ",\n\r", pParseText);

    pParseText = AdtParse::nextWord(pParseText);

    if (AdtParse::matchWord(pParseText, ","))
    {
      int   nSize;
      bool  bError = true;

      pParseText = AdtParse::nextWord(pParseText);

      AdtParse::extractWord(sFortranSize, " \t\n\r", pParseText);

      if (::sscanf(sFortranSize, "%d", &nSize) == 1)
      {
        char  sBuffer[32] = {0};

        ::sprintf(sBuffer, "%d", nSize);

        if (::strlen(sBuffer) == ::strlen(sFortranSize))
        {
          bError = false;
        }
      }

      if (bError)
      {
        ::printf("ERROR: Invalid #type_map format in command section\n");
      }

      pParseText = AdtParse::nextWord(pParseText);
    }
  }
  else
  {
    ::printf("ERROR: Invalid #type_map format in command section\n");
  }

  AdtCppScopeManager::addUserDefinedType(sGenericType);

  add(TypeMapCommandList, new AdtGenericTypeMapCommand(sGenericType,
                                                       sFortranType,
                                                       sFortranSize));

  return (pParseText);
}

//  ----------------------------------------------------------------------------

const char* AdtGenericCommandBlock::parseDefType(const char* pChar)
{
  //Trying to match a definition like this:
  //
  //  #def_type  AdtArray
  string      sGenericType;
  const char* pParseText  = AdtParse::nextWord(pChar);

  AdtParse::extractWord(sGenericType, " \t\n\r", pParseText);

  pParseText = AdtParse::nextWord(pParseText);

  AdtCppScopeManager::addUserDefinedType(sGenericType);

  return (pParseText);
}

//  ----------------------------------------------------------------------------

AdtGenericCommandBlock::AdtGenericCommandBlock()
 : DefineCommandList(),
   TypeMapCommandList()
{
  IsForwardMode = true;
}

//  ----------------------------------------------------------------------------

AdtGenericCommandBlock::AdtGenericCommandBlock(const AdtGenericCommandBlock& rCopy)
 : DefineCommandList(),
   TypeMapCommandList()
{
  IsForwardMode = rCopy.IsForwardMode;
}

//  ----------------------------------------------------------------------------

AdtGenericCommandBlock::~AdtGenericCommandBlock()
{
  reset();
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::reset()
{
  bool bReset = false;

  flush(DefineCommandList);
  flush(TypeMapCommandList);

  return (bReset);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::parseAppend(const char* pCommandBlock, const char* pCommandBlockName)
{
  //Trying to parse a block like this:
  //
  //  #comment| These are mappings to convert the ARRAY_?? delphi class types into
  //  #comment| nearest equivalent intrinsic types in fortran.
  //  #def_type AdtArray
  //  #type_map   ARRAY_1D : DOUBLE PRECISION, (:)
  //  #type_map   ARRAY_2D : DOUBLE PRECISION, (:,:)
  //  #type_map   ARRAY_3D : DOUBLE PRECISION, (:,:,:)
  //  #type_map   ARRAY_4D : DOUBLE PRECISION, (:,:,:,:)
  //  #type_map   ARRAY_1L : INTEGER, (:)
  //  #type_map   ARRAY_2L : INTEGER, (:,:)
  //  #type_map   ARRAY_3L : INTEGER, (:,:,:)
  //  #type_map   ARRAY_4L : INTEGER, (:,:,:,:)
  //  #type_map   ARRAY_1B : LOGICAL, (:)
  //  #type_map   ARRAY_2B : LOGICAL, (:,:)
  //  #type_map   ARRAY_3B : LOGICAL, (:,:,:)
  //  #type_map   ARRAY_4B : LOGICAL, (:,:,:,:)
  //  #include instructions.txt
  //  #defineb GETSIZE(_stack)  PLONGINT(_stack)^
  //  #defineb LOG(_a)          ln(_a)
  //  #definef ln(a)            (LOG(a))
  //  #definef sqr(a)           (a*a)
  //  #definef logit(a)         (LOG((a)/(1-(a))))
  //  #definef inc(a)           a:=a+1
  //  #definef inc(a,d)         a:=a+(d)
  //  #definef dec(a)           a:=a-1
  //  #definef dec(a,d)         a:=a-(d)
  //  #definef XCOPY(a,b,c)     for i__:=1 to c do
  //                            begin
  //                              a[i__]:=b[i__];
  //                            end;
  //                            add_variables
  //                            i__ : integer;
  //
  // defineb is backward step define and definef is forward step define.
  // Depending on whether compiling in forward or backward mode these defines
  // are either included or discarded.
  //
  // We need this functionality because the macro substitution is used in the
  // conversion from Delphi to Fortran (forward step) as well as the conversion
  // from Fortran to Delphi (backward step) and need to avoid circular macro
  // substitutions. For example, this pair would be circular if we didn't have
  // a concept of forward and backward step.
  //
  //  #defineb LOG(_a)          ln(_a)
  //  #definef ln(a)            (LOG(a))
  bool bParsed = false;

  if (pCommandBlock != 0)
  {
    int         nCount  = 0;
    const char* pChar   = pCommandBlock;

    while (*pChar != '\0')
    {
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, "#comment"))
      {
        pChar = AdtParse::nextLine(pChar);
      }
      else if (AdtParse::matchWord(pChar, "#definef"))
      {
        pChar = parseDefine(pChar, 1, pCommandBlockName);
      }
      else if (AdtParse::matchWord(pChar, "#defineb"))
      {
        pChar = parseDefine(pChar, 2, pCommandBlockName);
      }
      else if (AdtParse::matchWord(pChar, "#define"))
      {
        pChar = parseDefine(pChar, 0, pCommandBlockName);
      }
      else if (AdtParse::matchWord(pChar, "#include"))
      {
        pChar = parseInclude(pChar);
      }
      else if (AdtParse::matchWord(pChar, "#type_map"))
      {
        pChar = parseTypeMap(pChar);
      }
      else if (AdtParse::matchWord(pChar, "#def_type"))
      {
        pChar = parseDefType(pChar);
      }
      else
      {
        pChar = AdtParse::nextLine(pChar);
      }
    }
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtDelphi& rParent,
                                     FILE*& yyDelphiin,
                                     int& yyDelphidebug,
                                     parse_fn yyDelphiparse)
{
  bool bExecuted = false;

  //Do define commands
  bExecuted = execute(DefineCommandList, rParent, yyDelphiin, yyDelphidebug, yyDelphiparse) ? true : bExecuted;

  //Do type map commands
  bExecuted = execute(TypeMapCommandList, rParent, yyDelphiin, yyDelphidebug, yyDelphiparse) ? true : bExecuted;

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtCpp& rParent,
                                     FILE*& yyCppin,
                                     int& yyCppdebug,
                                     parse_fn yyCppparse)
{
  bool bExecuted = false;

  //Do define commands
  bExecuted = execute(DefineCommandList, rParent, yyCppin, yyCppdebug, yyCppparse) ? true : bExecuted;

  //Do type map commands
  bExecuted = execute(TypeMapCommandList, rParent, yyCppin, yyCppdebug, yyCppparse) ? true : bExecuted;

  return (bExecuted);
}

//  ----------------------------------------------------------------------------

bool AdtGenericCommandBlock::execute(AdtJava& rParent,
                                     FILE*& yyJavain,
                                     int& yyJavadebug,
                                     parse_fn yyJavaparse)
{
  bool bExecuted = false;

  //Do define commands
  bExecuted = execute(DefineCommandList, rParent, yyJavain, yyJavadebug, yyJavaparse) ? true : bExecuted;

  //Do type map commands
  bExecuted = execute(TypeMapCommandList, rParent, yyJavain, yyJavadebug, yyJavaparse) ? true : bExecuted;

  return (bExecuted);
}


//  ----------------------------------------------------------------------------
//  AdtCommentCollection method implementations
//  ----------------------------------------------------------------------------
AdtCommentCollection::AdtCommentCollection(const char* pFileName)
 : FileName(pFileName),
   CommentMap()
{

}

//  ----------------------------------------------------------------------------

AdtCommentCollection::~AdtCommentCollection()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtCommentCollection::addComment(const char* pComment, int nLineNumber)
{
  AdtStringByIntMapIter Iter = CommentMap.find(nLineNumber);

  if (Iter == CommentMap.end())
  {
    CommentMap[nLineNumber] = string(pComment);
  }
  else
  {
    CommentMap[nLineNumber] = Iter->second + string(pComment);
  }
}

//  ----------------------------------------------------------------------------

bool AdtCommentCollection::extractComment(string& rComment, int nUpToLineNumber)
{
  bool bExtracted = false;

  rComment.clear();

  AdtStringByIntMapIter EraseBegin;
  AdtStringByIntMapIter EraseEnd = CommentMap.end();
  bool                  bErase   = false;

  for (AdtStringByIntMapIter Iter = CommentMap.begin() ; Iter != CommentMap.end() ; ++Iter)
  {
    if (Iter->first <= nUpToLineNumber)
    {
      if (!bErase)
      {
        EraseBegin = Iter;
        bErase     = true;
      }

      rComment  += Iter->second;
      bExtracted = true;
    }
    else
    {
      EraseEnd = Iter;
      break;
    }
  }

  if (bErase)
  {
    CommentMap.erase(EraseBegin, EraseEnd);
  }

  return (bExtracted);
}


//  ----------------------------------------------------------------------------
//  AdtCommon method implementations
//  ----------------------------------------------------------------------------
AdtStringCache        AdtCommon::StringCache;
AdtStringByStringMap  AdtCommon::TranslationMap;

//  ----------------------------------------------------------------------------

bool AdtCommon::beginParseString(FILE*& rFile, string& sFileName, const char* pString)
{
  bool bDone;

  sFileName = tempnam(0, "adttmp");
  rFile     = fopen(sFileName, "w+");

  if (rFile != 0)
  {
    ::fprintf(rFile, "%s", pString);
    ::fseeko(rFile, 0, SEEK_SET);

    bDone = true;
  }

  ASSERT(bDone);

  return (bDone);
}

//  ----------------------------------------------------------------------------

bool AdtCommon::endParseString(FILE*& rFile, string& sFileName)
{
  bool bDone = false;

  if (rFile != 0)
  {
    ::fclose(rFile);
    ::unlink(sFileName);

    rFile = 0;
    bDone = true;
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

void AdtCommon::flush()
{
  for (AdtCommentCollectionPtrByStringMapIter Iter = CommentCollectionMap.begin() ;Iter != CommentCollectionMap.end() ; ++Iter)
  {
    AdtCommentCollection* pCommentCollection = Iter->second;

    if (pCommentCollection != 0)
    {
      delete pCommentCollection;
    }
  }

  CommentCollectionMap.clear();
}

//  ----------------------------------------------------------------------------

AdtCommon::AdtCommon()
 : CommentCollectionMap()
{
  Log = 0;
}

//  ----------------------------------------------------------------------------

AdtCommon::~AdtCommon()
{
  flush();
}

//  ----------------------------------------------------------------------------

bool AdtCommon::openLog(const char* pFileAndPath, const char* pMode)
{
    Log = ::fopen(pFileAndPath, pMode);

    return (Log != 0);
}

//  ----------------------------------------------------------------------------

bool AdtCommon::closeLog()
{
  bool bClosed = false;

  if (Log != 0)
  {
    ::fclose(Log);

    Log     = 0;
    bClosed = true;
  }

  return (bClosed);
}

//  ----------------------------------------------------------------------------

void AdtCommon::appendComment(const char* pCommentText, const char* pFileName, int nLineNumber)
{
  if ((pCommentText != 0) && (pFileName != 0))
  {
    AdtCommentCollection*                   pCommentCollection = 0;
    AdtCommentCollectionPtrByStringMapIter  Iter               = CommentCollectionMap.find(pFileName);

    if (Iter == CommentCollectionMap.end())
    {
      pCommentCollection              = new AdtCommentCollection(pFileName);
      CommentCollectionMap[pFileName] = pCommentCollection;
    }
    else
    {
      pCommentCollection = Iter->second;
    }

    if (pCommentCollection != 0)
    {
      pCommentCollection->addComment(pCommentText, nLineNumber);
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtCommon::extractComment(const string** ppComment, const char* pFileName, int nUpToLineNumber)
{
  bool bExtracted = false;

  if (ppComment != 0)
  {
    string rComment;

    if (pFileName != 0)
    {
      AdtCommentCollectionPtrByStringMapIter  Iter = CommentCollectionMap.find(pFileName);

      if (Iter != CommentCollectionMap.end())
      {
        AdtCommentCollection* pCommentCollection = Iter->second;

        if (pCommentCollection != 0)
        {
          bExtracted = pCommentCollection->extractComment(rComment, nUpToLineNumber);
        }
      }
      else
      {
        rComment.clear();
      }
    }
    else
    {
      rComment.clear();
    }

    if (rComment.length() > 0)
    {
      allocString(rComment.c_str(), ppComment, false);
    }
  }

  return (bExtracted);
}

//  ----------------------------------------------------------------------------

void AdtCommon::addTranslation(const char* pOriginalText, const char* pTranslatedText)
{
  if ((pOriginalText    != 0            ) &&
      (pTranslatedText  != 0            ) &&
      (pTranslatedText  != pOriginalText))
  {
    TranslationMap[pOriginalText] = pTranslatedText;
  }
}

//  ----------------------------------------------------------------------------

void AdtCommon::addTranslation(const AdtStringList& rOriginalTextList, const AdtStringList& rTranslatedTextList)
{
  if (rOriginalTextList.size() == rTranslatedTextList.size())
  {
    AdtStringListConstIter  OriginalIter;
    AdtStringListConstIter  TranslatedIter;

    for (OriginalIter = rOriginalTextList.begin(), TranslatedIter = rTranslatedTextList.begin() ;
         OriginalIter != rOriginalTextList.end() ;
         ++OriginalIter, ++TranslatedIter)
    {
      addTranslation(*OriginalIter, *TranslatedIter);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCommon::removeTranslation(const char* pOriginalText)
{
  if (pOriginalText != 0)
  {
    TranslationMap.erase(pOriginalText);
  }
}

//  ----------------------------------------------------------------------------

void AdtCommon::removeTranslation(const AdtStringList& rOriginalTextList)
{
  AdtStringListConstIter  Iter;

  for (Iter = rOriginalTextList.begin() ; Iter != rOriginalTextList.end() ; ++Iter)
  {
    removeTranslation(*Iter);
  }
}

//  ----------------------------------------------------------------------------

const char* AdtCommon::allocString(const char* pTokenText, const string** ppCachedString, bool bTranslate)
{
  const char* pTranslatedText = pTokenText;

  if (bTranslate)
  {
    AdtStringByStringMapConstIter Iter = TranslationMap.find(pTokenText);

    if (Iter != TranslationMap.end())
    {
      pTranslatedText = (*Iter).second;
    }
  }

  return (StringCache.add(pTranslatedText, ppCachedString));
}

//  ----------------------------------------------------------------------------

void AdtCommon::logText(const char* pTokenText, int nLineNumber)
{
  if ((Log != 0) && (pTokenText != 0))
  {
    ::fputs(pTokenText, Log);
  }
}

//  ----------------------------------------------------------------------------

void AdtCommon::logFlush()
{
  if (Log != 0)
  {
    ::fflush(Log);
  }
}


//  ----------------------------------------------------------------------------
//  AdtCompilerBase method implementations
//  ----------------------------------------------------------------------------
void AdtCompilerBase::stripComments(string& sStrippedCommandBlock,
                                    const char* pCommandBlock,
                                    const char** ppLeadingBraces,
                                    const char** ppTrailingBraces,
                                    int nBraceTypes) const
{
  if ((pCommandBlock    != 0) &&
      (ppLeadingBraces  != 0) &&
      (ppTrailingBraces != 0) &&
      (nBraceTypes       > 0))
  {
    int         cn;
    const char* pStart  = pCommandBlock;
    size_t      nLength = ::strlen(pCommandBlock);

    for (cn = 0 ; cn < nBraceTypes ; cn++)
    {
      const char* pLeadingBrace   = ppLeadingBraces[cn];
      const char* pTrailingBrace  = ppTrailingBraces[cn];
      const char* pChar           = pCommandBlock;

      // find block header
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, pLeadingBrace))
      {
        nLength = nLength - (pChar - pStart);
        pStart  = pChar;
        pChar  += nLength - 1;

        //Search from the end for a match
        pChar = AdtParse::previousWord(pChar, pStart);
        AdtParse::previousMatchWord(pChar, pStart, pTrailingBrace);

        nLength = pChar - pStart + 1;
        break;
      }
    }

    sStrippedCommandBlock = string(pStart, nLength);
  }
}

//  ----------------------------------------------------------------------------

void AdtCompilerBase::parseCommandBlock(const char* pCommandBlock)
{
  CommandBlock.parseAppend(pCommandBlock, 0);
}

//  ----------------------------------------------------------------------------

AdtCompilerBase::AdtCompilerBase()
 : CommandBlock()
{

}

//  ----------------------------------------------------------------------------

AdtCompilerBase::~AdtCompilerBase()
{

}


//  ----------------------------------------------------------------------------
//  AdtCompiler method implementations
//  ----------------------------------------------------------------------------
AdtCompilerBase* AdtCompiler::createCompilerForFile(const string& rSourceFile) const
{
  AdtCompilerBase* pCompiler = 0;

  switch (adtSourceFileTypeFromFile(rSourceFile))
  {
    case DelphiSourceFileType:
    {
      pCompiler = new AdtDelphi();
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      pCompiler = new AdtCpp();
      break;
    }

    case JavaSourceFileType:
    {
      pCompiler = new AdtJava();
      break;
    }

    case FortranSourceFileType:
    {
      pCompiler = new AdtFortran();
      break;
    }

    case UnknownSourceFileType:
    default:
    {
      break;
    }
  }

  return (pCompiler);
}

//  ----------------------------------------------------------------------------

AdtCompiler::AdtCompiler(const AdtCompiler& rCopy)
{
  ParserContext = 0;

  FAIL();
}

//  ----------------------------------------------------------------------------

AdtCompiler::AdtCompiler(const string& rSourceFile)
{
  ParserContext = createCompilerForFile(rSourceFile);
}

//  ----------------------------------------------------------------------------

AdtCompiler::~AdtCompiler()
{
  if (ParserContext != 0)
  {
    delete ParserContext;
  }
}


//  ----------------------------------------------------------------------------
//  AdtFortran method implementations
//  ----------------------------------------------------------------------------
const char* AdtFortran::PushPopFunctions[] =
{
  "PUSHREAL4",
  "POPREAL4",
  "LOOKREAL4",
  "PUSHREAL4ARRAY",
  "POPREAL4ARRAY",
  "PUSHREAL8",
  "POPREAL8",
  "LOOKREAL8",
  "PUSHREAL8ARRAY",
  "POPREAL8ARRAY",
  "PUSHREAL16",
  "POPREAL16",
  "LOOKREAL16",
  "PUSHREAL16ARRAY",
  "POPREAL16ARRAY",
  "PUSHINTEGER1",
  "POPINTEGER1",
  "LOOKINTEGER1",
  "PUSHINTEGER1ARRAY",
  "POPINTEGER1ARRAY",
  "PUSHINTEGER2",
  "POPINTEGER2",
  "LOOKINTEGER2",
  "PUSHINTEGER2ARRAY",
  "POPINTEGER2ARRAY",
  "PUSHINTEGER4",
  "POPINTEGER4",
  "LOOKINTEGER4",
  "PUSHINTEGER4ARRAY",
  "POPINTEGER4ARRAY",
  "PUSHINTEGER8",
  "POPINTEGER8",
  "LOOKINTEGER8",
  "PUSHINTEGER8ARRAY",
  "POPINTEGER8ARRAY",
  "PUSHCONTROL1B",
  "POPCONTROL1B",
  "LOOKCONTROL1B",
  "PUSHCONTROL1BARRAY",
  "POPCONTROL1BARRAY",
  "PUSHCONTROL2B",
  "POPCONTROL2B",
  "LOOKCONTROL2B",
  "PUSHCONTROL2BARRAY",
  "POPCONTROL2BARRAY",
  "PUSHCONTROL3B",
  "POPCONTROL3B",
  "LOOKCONTROL3B",
  "PUSHCONTROL3BARRAY",
  "POPCONTROL3BARRAY",
  "PUSHCONTROL4B",
  "POPCONTROL4B",
  "LOOKCONTROL4B",
  "PUSHCONTROL4BARRAY",
  "POPCONTROL4BARRAY",
};

//  ----------------------------------------------------------------------------

const char* AdtFortran::CallExpandMacrosWithStackSubstitution =
"CALL_EXPAND PUSHINTEGER1ARRAY(a,size_a)\n"
"    bstacki = bstacki + size_a\n"
"    bstack(bstacki - size_a + 1:bstacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1ARRAY(a,size_a)\n"
"    bstacki = bstacki - size_a\n"
"    a = bstack(bstacki:bstacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER1(x)\n"
"    bstacki = bstacki + 1\n"
"    bstack(bstacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER1(x)\n"
"    x = bstack(bstacki)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1(x)\n"
"    x = bstack(bstacki)\n"
"    bstacki = bstacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4ARRAY(a,size_a)\n"
"    i4stacki = i4stacki + size_a\n"
"    i4stack(i4stacki - size_a + 1:i4stacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER i4stacki\n"
"    INTEGER i4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4ARRAY(a,size_a)\n"
"    i4stacki = i4stacki - size_a\n"
"    a = i4stack(i4stacki:i4stacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER i4stacki\n"
"    INTEGER i4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4(x)\n"
"    i4stacki = i4stacki + 1\n"
"    i4stack(i4stacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER i4stacki\n"
"    INTEGER i4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER4(x)\n"
"    x = i4stack(i4stacki)\n"
"ADD_VARIABLES\n"
"    INTEGER i4stacki\n"
"    INTEGER i4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4(x)\n"
"    x = i4stack(i4stacki)\n"
"    i4stacki = i4stacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER i4stacki\n"
"    INTEGER i4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8ARRAY(a,size_a)\n"
"    i8stacki = i8stacki + size_a\n"
"    i8stack(i8stacki - size_a + 1:i8stacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER i8stacki\n"
"    INTEGER i8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8ARRAY(a,size_a)\n"
"    i8stacki = i8stacki - size_a\n"
"    a = i8stack(i8stacki:i8stacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER i8stacki\n"
"    INTEGER i8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8(x)\n"
"    i8stacki = i8stacki + 1\n"
"    i8stack(i8stacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER i8stacki\n"
"    INTEGER i8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER8(x)\n"
"    x = i8stack(i8stacki)\n"
"ADD_VARIABLES\n"
"    INTEGER i8stacki\n"
"    INTEGER i8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8(x)\n"
"    x = i8stack(i8stacki)\n"
"    i8stacki = i8stacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER i8stacki\n"
"    INTEGER i8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL4ARRAY(a,size_a)\n"
"    r4stacki = r4stacki + size_a\n"
"    r4stack(r4stacki - size_a + 1:r4stacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER r4stacki\n"
"    REAL(4) r4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4ARRAY(a,size_a)\n"
"    r4stacki = r4stacki - size_a\n"
"    a = r4stack(r4stacki:r4stacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER r4stacki\n"
"    REAL(4) r4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL4(x)\n"
"    r4stacki = r4stacki + 1\n"
"    r4stack(r4stacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER r4stacki\n"
"    REAL(4) r4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL4(x)\n"
"    x = r4stack(r4stacki)\n"
"ADD_VARIABLES\n"
"    INTEGER r4stacki\n"
"    REAL(4) r4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4(x)\n"
"    x = r4stack(r4stacki)\n"
"    r4stacki = r4stacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER r4stacki\n"
"    REAL(4) r4stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8ARRAY(a,size_a)\n"
"    r8stacki = r8stacki + size_a\n"
"    r8stack(r8stacki - size_a + 1:r8stacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER r8stacki\n"
"    REAL(8) r8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8ARRAY(a,size_a)\n"
"    r8stacki = r8stacki - size_a\n"
"    a = r8stack(r8stacki:r8stacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER r8stacki\n"
"    REAL(8) r8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8(x)\n"
"    r8stacki = r8stacki + 1\n"
"    r8stack(r8stacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER r8stacki\n"
"    REAL(8) r8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL8(x)\n"
"    x = r8stack(r8stacki)\n"
"ADD_VARIABLES\n"
"    INTEGER r8stacki\n"
"    REAL(8) r8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8(x)\n"
"    x = r8stack(r8stacki)\n"
"    r8stacki = r8stacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER r8stacki\n"
"    REAL(8) r8stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16ARRAY(a,size_a)\n"
"    r16stacki = r16stacki + size_a\n"
"    r16stack(r16stacki - size_a + 1:r16stacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER r16stacki\n"
"    REAL(16) r16stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16ARRAY(a,size_a)\n"
"    r16stacki = r16stacki - size_a\n"
"    a = r16stack(r16stacki:r16stacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER r16stacki\n"
"    REAL(16) r16stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16(x)\n"
"    r16stacki = r16stacki + 1\n"
"    r16stack(r16stacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER r16stacki\n"
"    REAL(16) r16stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL16(x)\n"
"    x = r16stack(r16stacki)\n"
"ADD_VARIABLES\n"
"    INTEGER r16stacki\n"
"    REAL(16) r16stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16(x)\n"
"    x = r16stack(r16stacki)\n"
"    r16stacki = r16stacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER r16stacki\n"
"    REAL(16) r16stack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1BARRAY(a,size_a)\n"
"    bstacki = bstacki + size_a\n"
"    bstack(bstacki - size_a + 1:bstacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1BARRAY(a,size_a)\n"
"    bstacki = bstacki - size_a\n"
"    a = bstack(bstacki:bstacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1B(x)\n"
"    bstacki = bstacki + 1\n"
"    bstack(bstacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL1B(x)\n"
"    x = bstack(bstacki)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1B(x)\n"
"    x = bstack(bstacki)\n"
"    bstacki = bstacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2BARRAY(a,size_a)\n"
"    bstacki = bstacki + size_a\n"
"    bstack(bstacki - size_a + 1:bstacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2BARRAY(a,size_a)\n"
"    bstacki = bstacki - size_a\n"
"    a = bstack(bstacki:bstacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2B(x)\n"
"    bstacki = bstacki + 1\n"
"    bstack(bstacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL2B(x)\n"
"    x = bstack(bstacki)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2B(x)\n"
"    x = bstack(bstacki)\n"
"    bstacki = bstacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3BARRAY(a,size_a)\n"
"    bstacki = bstacki + size_a\n"
"    bstack(bstacki - size_a + 1:bstacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3BARRAY(a,size_a)\n"
"    bstacki = bstacki - size_a\n"
"    a = bstack(bstacki:bstacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3B(x)\n"
"    bstacki = bstacki + 1\n"
"    bstack(bstacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL3B(x)\n"
"    x = bstack(bstacki)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3B(x)\n"
"    x = bstack(bstacki)\n"
"    bstacki = bstacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4BARRAY(a,size_a)\n"
"    bstacki = bstacki + size_a\n"
"    bstack(bstacki - size_a + 1:bstacki) = a\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4BARRAY(a,size_a)\n"
"    bstacki = bstacki - size_a\n"
"    a = bstack(bstacki:bstacki + size_a - 1)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4B(x)\n"
"    bstacki = bstacki + 1\n"
"    bstack(bstacki) = x\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL4B(x)\n"
"    x = bstack(bstacki)\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4B(x)\n"
"    x = bstack(bstacki)\n"
"    bstacki = bstacki - 1\n"
"ADD_VARIABLES\n"
"    INTEGER bstacki\n"
"    INTEGER(1) bstack(dim_stack)\n"
"END\n";

//  ----------------------------------------------------------------------------

const char* AdtFortran::CallExpandMacrosWithoutStackSubstitution =
"CALL_EXPAND PUSHREAL4_D(V,VD)\n"
"  CALL PUSHREAL4(V)\n"
"  CALL PUSHREAL4(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4_D(V,VD)\n"
"  CALL POPREAL4(VD)\n"
"  CALL POPREAL4(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL4_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL4ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHREAL4ARRAY(V,SIZE)\n"
"  CALL PUSHREAL4ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4ARRAY_D(V,VD,SIZE)\n"
"  CALL POPREAL4ARRAY(VD,SIZE)\n"
"  CALL POPREAL4ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8_D(V,VD)\n"
"  CALL PUSHREAL8(V)\n"
"  CALL PUSHREAL8(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8_D(V,VD)\n"
"  CALL POPREAL8(VD)\n"
"  CALL POPREAL8(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL8_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHREAL8ARRAY(V,SIZE)\n"
"  CALL PUSHREAL8ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8ARRAY_D(V,VD,SIZE)\n"
"  CALL POPREAL8ARRAY(VD,SIZE)\n"
"  CALL POPREAL8ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16_D(V,VD)\n"
"  CALL PUSHREAL16(V)\n"
"  CALL PUSHREAL16(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16_D(V,VD)\n"
"  CALL POPREAL16(VD)\n"
"  CALL POPREAL16(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL16_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHREAL16ARRAY(V,SIZE)\n"
"  CALL PUSHREAL16ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16ARRAY_D(V,VD,SIZE)\n"
"  CALL POPREAL16ARRAY(VD,SIZE)\n"
"  CALL POPREAL16ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER1_D(V,VD)\n"
"  CALL PUSHINTEGER1(V)\n"
"  CALL PUSHINTEGER1(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1_D(V,VD)\n"
"  CALL POPINTEGER1(VD)\n"
"  CALL POPINTEGER1(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER1_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER1ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHINTEGER1ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER1ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1ARRAY_D(V,VD,SIZE)\n"
"  CALL POPINTEGER1ARRAY(VD,SIZE)\n"
"  CALL POPINTEGER1ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER2_D(V,VD)\n"
"  CALL PUSHINTEGER2(V)\n"
"  CALL PUSHINTEGER2(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER2_D(V,VD)\n"
"  CALL POPINTEGER2(VD)\n"
"  CALL POPINTEGER2(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER2_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER2ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHINTEGER2ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER2ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER2ARRAY_D(V,VD,SIZE)\n"
"  CALL POPINTEGER2ARRAY(VD,SIZE)\n"
"  CALL POPINTEGER2ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4_D(V,VD)\n"
"  CALL PUSHINTEGER4(V)\n"
"  CALL PUSHINTEGER4(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4_D(V,VD)\n"
"  CALL POPINTEGER4(VD)\n"
"  CALL POPINTEGER4(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER4_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHINTEGER4ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER4ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4ARRAY_D(V,VD,SIZE)\n"
"  CALL POPINTEGER4ARRAY(VD,SIZE)\n"
"  CALL POPINTEGER4ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8_D(V,VD)\n"
"  CALL PUSHINTEGER8(V)\n"
"  CALL PUSHINTEGER8(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8_D(V,VD)\n"
"  CALL POPINTEGER8(VD)\n"
"  CALL POPINTEGER8(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER8_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8ARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHINTEGER8ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER8ARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8ARRAY_D(V,VD,SIZE)\n"
"  CALL POPINTEGER8ARRAY(VD,SIZE)\n"
"  CALL POPINTEGER8ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1B_D(V,VD)\n"
"  CALL PUSHCONTROL1B(V)\n"
"  CALL PUSHCONTROL1B(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1B_D(V,VD)\n"
"  CALL POPCONTROL1B(VD)\n"
"  CALL POPCONTROL1B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL1B_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1BARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHCONTROL1BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL1BARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1BARRAY_D(V,VD,SIZE)\n"
"  CALL POPCONTROL1BARRAY(VD,SIZE)\n"
"  CALL POPCONTROL1BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2B_D(V,VD)\n"
"  CALL PUSHCONTROL2B(V)\n"
"  CALL PUSHCONTROL2B(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2B_D(V,VD)\n"
"  CALL POPCONTROL2B(VD)\n"
"  CALL POPCONTROL2B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL2B_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2BARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHCONTROL2BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL2BARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2BARRAY_D(V,VD,SIZE)\n"
"  CALL POPCONTROL2BARRAY(VD,SIZE)\n"
"  CALL POPCONTROL2BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3B_D(V,VD)\n"
"  CALL PUSHCONTROL3B(V)\n"
"  CALL PUSHCONTROL3B(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3B_D(V,VD)\n"
"  CALL POPCONTROL3B(VD)\n"
"  CALL POPCONTROL3B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL3B_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3BARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHCONTROL3BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL3BARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3BARRAY_D(V,VD,SIZE)\n"
"  CALL POPCONTROL3BARRAY(VD,SIZE)\n"
"  CALL POPCONTROL3BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4B_D(V,VD)\n"
"  CALL PUSHCONTROL4B(V)\n"
"  CALL PUSHCONTROL4B(VD)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4B_D(V,VD)\n"
"  CALL POPCONTROL4B(VD)\n"
"  CALL POPCONTROL4B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL4B_D(V,VD)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4BARRAY_D(V,VD,SIZE)\n"
"  CALL PUSHCONTROL4BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL4BARRAY(VD,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4BARRAY_D(V,VD,SIZE)\n"
"  CALL POPCONTROL4BARRAY(VD,SIZE)\n"
"  CALL POPCONTROL4BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL4_DV(V,VD,NBDIRS)\n"
"  CALL PUSHREAL4(V)\n"
"  CALL PUSHREAL4ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4_DV(V,VD,NBDIRS)\n"
"  CALL POPREAL4ARRAY(VD,NBDIRS)\n"
"  CALL POPREAL4(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL4_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL4ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHREAL4ARRAY(V,SIZE)\n"
"  CALL PUSHREAL4ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL4ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPREAL4ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPREAL4ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8_DV(V,VD,NBDIRS)\n"
"  CALL PUSHREAL8(V)\n"
"  CALL PUSHREAL8ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8_DV(V,VD,NBDIRS)\n"
"  CALL POPREAL8ARRAY(VD,NBDIRS)\n"
"  CALL POPREAL8(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL8_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL8ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHREAL8ARRAY(V,SIZE)\n"
"  CALL PUSHREAL8ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL8ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPREAL8ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPREAL8ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16_DV(V,VD,NBDIRS)\n"
"  CALL PUSHREAL16(V)\n"
"  CALL PUSHREAL16ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16_DV(V,VD,NBDIRS)\n"
"  CALL POPREAL16ARRAY(VD,NBDIRS)\n"
"  CALL POPREAL16(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKREAL16_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHREAL16ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHREAL16ARRAY(V,SIZE)\n"
"  CALL PUSHREAL16ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPREAL16ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPREAL16ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPREAL16ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER1_DV(V,VD,NBDIRS)\n"
"  CALL PUSHINTEGER1(V)\n"
"  CALL PUSHINTEGER1ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1_DV(V,VD,NBDIRS)\n"
"  CALL POPINTEGER1ARRAY(VD,NBDIRS)\n"
"  CALL POPINTEGER1(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER1_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER1ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHINTEGER1ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER1ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER1ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPINTEGER1ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPINTEGER1ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER2_DV(V,VD,NBDIRS)\n"
"  CALL PUSHINTEGER2(V)\n"
"  CALL PUSHINTEGER2ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER2_DV(V,VD,NBDIRS)\n"
"  CALL POPINTEGER2ARRAY(VD,NBDIRS)\n"
"  CALL POPINTEGER2(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER2_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER2ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHINTEGER2ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER2ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER2ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPINTEGER2ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPINTEGER2ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4_DV(V,VD,NBDIRS)\n"
"  CALL PUSHINTEGER4(V)\n"
"  CALL PUSHINTEGER4ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4_DV(V,VD,NBDIRS)\n"
"  CALL POPINTEGER4ARRAY(VD,NBDIRS)\n"
"  CALL POPINTEGER4(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER4_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER4ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHINTEGER4ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER4ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER4ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPINTEGER4ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPINTEGER4ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8_DV(V,VD,NBDIRS)\n"
"  CALL PUSHINTEGER8(V)\n"
"  CALL PUSHINTEGER8ARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8_DV(V,VD,NBDIRS)\n"
"  CALL POPINTEGER8ARRAY(VD,NBDIRS)\n"
"  CALL POPINTEGER8(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKINTEGER8_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHINTEGER8ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHINTEGER8ARRAY(V,SIZE)\n"
"  CALL PUSHINTEGER8ARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPINTEGER8ARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPINTEGER8ARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPINTEGER8ARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1B_DV(V,VD,NBDIRS)\n"
"  CALL PUSHCONTROL1B(V)\n"
"  CALL PUSHCONTROL1BARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1B_DV(V,VD,NBDIRS)\n"
"  CALL POPCONTROL1BARRAY(VD,NBDIRS)\n"
"  CALL POPCONTROL1B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL1B_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL1BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHCONTROL1BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL1BARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL1BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPCONTROL1BARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPCONTROL1BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2B_DV(V,VD,NBDIRS)\n"
"  CALL PUSHCONTROL2B(V)\n"
"  CALL PUSHCONTROL2BARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2B_DV(V,VD,NBDIRS)\n"
"  CALL POPCONTROL2BARRAY(VD,NBDIRS)\n"
"  CALL POPCONTROL2B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL2B_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL2BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHCONTROL2BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL2BARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL2BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPCONTROL2BARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPCONTROL2BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3B_DV(V,VD,NBDIRS)\n"
"  CALL PUSHCONTROL3B(V)\n"
"  CALL PUSHCONTROL3BARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3B_DV(V,VD,NBDIRS)\n"
"  CALL POPCONTROL3BARRAY(VD,NBDIRS)\n"
"  CALL POPCONTROL3B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL3B_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL3BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHCONTROL3BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL3BARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL3BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPCONTROL3BARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPCONTROL3BARRAY(V,SIZE)\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4B_DV(V,VD,NBDIRS)\n"
"  CALL PUSHCONTROL4B(V)\n"
"  CALL PUSHCONTROL4BARRAY(VD,NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4B_DV(V,VD,NBDIRS)\n"
"  CALL POPCONTROL4BARRAY(VD,NBDIRS)\n"
"  CALL POPCONTROL4B(V)\n"
"END\n"
"\n"
"CALL_EXPAND LOOKCONTROL4B_DV(V,VD,NBDIRS)\n"
"  CONTINUE\n"
"END\n"
"\n"
"CALL_EXPAND PUSHCONTROL4BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL PUSHCONTROL4BARRAY(V,SIZE)\n"
"  CALL PUSHCONTROL4BARRAY(VD,SIZE*NBDIRS)\n"
"END\n"
"\n"
"CALL_EXPAND POPCONTROL4BARRAY_DV(V,VD,SIZE,NBDIRS)\n"
"  CALL POPCONTROL4BARRAY(VD,SIZE*NBDIRS)\n"
"  CALL POPCONTROL4BARRAY(V,SIZE)\n"
"END\n";

//  ----------------------------------------------------------------------------

bool AdtFortran::parse(void*& pFortranContext,
                       const char* pFilename,
                       FILE*& yyFortranin,
                       int& yyFortrandebug,
                       parse_fn yyFortranparse)
{
  bool bSucceeded = false;

  if ((yyFortranparse != 0) &&
      (pFilename      != 0))
  {
    void* pLastContext;

    pLastContext    = pFortranContext;
    pFortranContext = (void*)this;
    yyFortranin     = 0;
//    yyFortrandebug  = 1;
    yyFortrandebug  = 0;

    if (yyFortrandebug != 0)
    {
      openLog("fortran.out", "wt");
    }

    yyFortranin = ::fopen(pFilename, "rt");

    if (yyFortranin != 0)
    {
      yyFortranrestart(yyFortranin);
      yyFortran_resetLineNumber(allocString(pFilename));
      yyFortranparse();
      yyFortran_endParse();

      bSucceeded = (yyFortran_error() == 0);

      yyFortran_releaseBuffer();

      ::fclose(yyFortranin);

      yyFortranin = 0;
    }

    yyFortrandebug = 0;
    closeLog();

    pFortranContext = pLastContext;
  }

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

bool AdtFortran::parseString(void*& pFortranContext,
                             AdtFortranExecutableProgram*& pRoot,
                             const char* pString,
                             FILE*& yyFortranin,
                             int& yyFortrandebug,
                             parse_fn yyFortranparse)
{
  bool bSucceeded = false;

  if ((yyFortranparse != 0) &&
      (pString        != 0))
  {
    string  rFileName;

    if (beginParseString(yyFortranin, rFileName, pString))
    {
      AdtFortranExecutableProgram*  pOldRoot;
      void*                         pLastContext;

      pLastContext      = pFortranContext;
      pFortranContext   = (void*)this;
      pOldRoot          = AdtFortranBase::fortranRootObject();

      if (pOldRoot != 0)
      {
        pOldRoot->lock();
        AdtFortranBase::fortranRootObject(0);
      }

      //yyFortrandebug = 1;
      yyFortrandebug = 0;

      if (yyFortrandebug != 0)
      {
        openLog("fortran.out", "wt");
      }

      yyFortranrestart(yyFortranin);
      yyFortran_resetLineNumber(0);
      yyFortranparse();
      yyFortran_endParse();

      bSucceeded = (yyFortran_error() == 0);

      yyFortran_releaseBuffer();

      yyFortrandebug = 0;
      closeLog();

      pRoot = AdtFortranBase::fortranRootObject();

      if (pRoot != 0)
      {
        pRoot->lock();
      }

      AdtFortranBase::fortranRootObject(pOldRoot);
      UtlReleaseReference(pOldRoot);
      endParseString(yyFortranin, rFileName);

      pFortranContext = pLastContext;
    }
  }

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

AdtFortran::AdtFortran()
 : AdtCompilerBase()
{

}

//  ----------------------------------------------------------------------------

AdtFortran::~AdtFortran()
{

}

//  ----------------------------------------------------------------------------

void AdtFortran::parseCommandBlock(const char* pCommandBlock, bool bEmbedded)
{
  AdtCompilerBase::parseCommandBlock(pCommandBlock);
}

//  ----------------------------------------------------------------------------

bool AdtFortran::parse(const char* pFilename,
                       const char* pCommandBlock,
                       const char* pCommandBlockName,
                       const AdtStringList* pSearchPaths,
                       bool bForwardMode)
{
  bool bResult;

  Lex_SearchPaths = pSearchPaths;

  bResult = parse(adtFortran_pFortranContext,
                  pFilename,
                  yyFortranin,
                  yyFortrandebug,
                  yyFortranparse);

  if (bResult)
  {
    AdtFortranBase::rootBindComments(this);
  }

  Lex_SearchPaths = 0;

  return (bResult);
}

//  ----------------------------------------------------------------------------

bool AdtFortran::parseString(AdtParser*& pRoot,
                             const char* pString)
{
  AdtFortranExecutableProgram*  pNativeRoot;
  bool                          bParsed;

  pRoot   = 0;
  bParsed = false;

  if (parseString(adtFortran_pFortranContext,
                  pNativeRoot,
                  pString,
                  yyFortranin,
                  yyFortrandebug,
                  yyFortranparse))
  {
    pRoot   = pNativeRoot;
    bParsed = true;
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

bool AdtFortran::parseCallExpandMacros(AdtFortranExecutableProgram*& pRoot)
{
  const char* pCode       = 0;
  AdtParser*  pParseRoot  = 0;
  bool        bParsed     = false;

  if (AdtFortranBase::WithStackSubstitution)
  {
    pCode = CallExpandMacrosWithStackSubstitution;
  }
  else
  {
    pCode = CallExpandMacrosWithoutStackSubstitution;
  }

  if (parseString(pParseRoot, pCode) &&
      pParseRoot->isType("AdtFortranExecutableProgram"))
  {
    pRoot   = (AdtFortranExecutableProgram*)pParseRoot;
    bParsed = true;
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

void AdtFortran::releaseRoot()
{
  adtFortran_releaseRoot();
}

//  ----------------------------------------------------------------------------

AdtParser* AdtFortran::parseRoot() const
{
  return (AdtFortranBase::fortranRootObject());
}

//  ----------------------------------------------------------------------------

AdtSourceRoot* AdtFortran::sourceRoot() const
{
  return (AdtFortranBase::fortranRootObject());
}

//  ----------------------------------------------------------------------------

void AdtFortran::setPushPopSubstitution(const char* pFullSuffix, const char* pBaseSuffix)
{
  int nCount = sizeof(PushPopFunctions) / sizeof(*PushPopFunctions);

  for (int cn = 0 ; cn < nCount ; cn++)
  {
    string sTranslation(PushPopFunctions[cn]);
    string sKey(PushPopFunctions[cn]);

    sKey          += pFullSuffix;
    sTranslation  += pBaseSuffix;

    AdtCommon::addTranslation(sKey, sTranslation);
  }
}

//  ----------------------------------------------------------------------------

void AdtFortran::clearPushPopSubstitution(const char* pFullSuffix)
{
  int nCount = sizeof(PushPopFunctions) / sizeof(*PushPopFunctions);

  for (int cn = 0 ; cn < nCount ; cn++)
  {
    string sKey(PushPopFunctions[cn]);

    sKey += pFullSuffix;

    AdtCommon::removeTranslation(sKey);
  }
}


//  ----------------------------------------------------------------------------
//  AdtDelphi method implementations
//  ----------------------------------------------------------------------------
bool AdtDelphi::parse(void*& pDelphiContext,
                      const char* pFilename,
                      FILE*& yyDelphiin,
                      int& yyDelphidebug,
                      parse_fn yyDelphiparse,
                      const char* pCommandBlock,
                      const char* pCommandBlockName,
                      bool bForwardMode)
{
  bool  bSucceeded    = false;
  void* pLastContext  = pDelphiContext;

  CommandBlock.isForwardMode(bForwardMode);
  CommandBlock.reset();

  if (pCommandBlock != 0)
  {
    CommandBlock.parseAppend(pCommandBlock, pCommandBlockName);
  }

  if ((yyDelphiparse != 0) &&
      (pFilename     != 0))
  {
    pDelphiContext  = (void*)this;
    yyDelphiin      = 0;
//    yyDelphidebug   = 1;
    yyDelphidebug   = 0;

    if (yyDelphidebug != 0)
    {
      openLog("delphi.out", "wt");
    }

    yyDelphiin = ::fopen(pFilename, "rt");

    if (yyDelphiin != 0)
    {
      yyDelphirestart(yyDelphiin);
      yyDelphi_resetLineNumber(allocString(pFilename));
      yyDelphiparse();
      yyDelphi_endParse();

      bSucceeded = (yyDelphi_error() == 0);

      yyDelphi_releaseBuffer();

      ::fclose(yyDelphiin);

      yyDelphiin = 0;
    }

    yyDelphidebug = 0;
    closeLog();
  }

  CommandBlock.execute(*this, yyDelphiin, yyDelphidebug, yyDelphiparse);

  pDelphiContext = pLastContext;

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

bool AdtDelphi::parseString(void*& pDelphiContext,
                            AdtDelphiGoal*& pRoot,
                            const char* pString,
                            FILE*& yyDelphiin,
                            int& yyDelphidebug,
                            parse_fn yyDelphiparse)
{
  bool bSucceeded = false;

  if ((yyDelphiparse != 0) &&
      (pString       != 0))
  {
    string  rFileName;

    if (beginParseString(yyDelphiin, rFileName, pString))
    {
      AdtDelphiGoal*  pOldRoot;
      void*           pLastContext;

      pLastContext    = pDelphiContext;
      pDelphiContext  = (void*)this;
      pOldRoot        = AdtDelphiBase::delphiRootObject();

      if (pOldRoot != 0)
      {
        pOldRoot->lock();
      }

//      yyDelphidebug   = 1;
      yyDelphidebug   = 0;

      if (yyDelphidebug != 0)
      {
        openLog("delphi.out", "wt");
      }

      yyDelphirestart(yyDelphiin);
      yyDelphi_resetLineNumber(0);
      yyDelphiparse();
      yyDelphi_endParse();

      bSucceeded = (yyDelphi_error() == 0);

      yyDelphi_releaseBuffer();

      yyDelphidebug = 0;
      closeLog();

      pRoot = AdtDelphiBase::delphiRootObject();

      if (pRoot != 0)
      {
        pRoot->lock();
      }

      AdtDelphiBase::delphiRootObject(pOldRoot);
      UtlReleaseReference(pOldRoot);
      endParseString(yyDelphiin, rFileName);

      pDelphiContext = pLastContext;
    }
  }

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

AdtDelphi::AdtDelphi()
 : AdtCompilerBase()
{

}

//  ----------------------------------------------------------------------------

AdtDelphi::~AdtDelphi()
{

}

//  ----------------------------------------------------------------------------

void AdtDelphi::parseCommandBlock(const char* pCommandBlock, bool bEmbedded)
{
  if (bEmbedded)
  {
    string      sStrippedCommandBlock;
    const char* pLeadingBraces[2]   = {"{%", "(*%"};
    const char* pTrailingBraces[2]  = {"}", "*)"};

    // Remove leading and trailing comment
    AdtCompilerBase::stripComments(sStrippedCommandBlock,
                                   pCommandBlock,
                                   pLeadingBraces,
                                   pTrailingBraces,
                                   2);

    AdtCompilerBase::parseCommandBlock(sStrippedCommandBlock);
  }
  else
  {
    AdtCompilerBase::parseCommandBlock(pCommandBlock);
  }
}

//  ----------------------------------------------------------------------------

bool AdtDelphi::parse(const char* pFilename,
                      const char* pCommandBlock,
                      const char* pCommandBlockName,
                      const AdtStringList* pSearchPaths,
                      bool bForwardMode)
{
  bool bResult;

  Lex_SearchPaths = pSearchPaths;

  bResult = parse(adtDelphi_pDelphiContext,
                  pFilename,
                  yyDelphiin,
                  yyDelphidebug,
                  yyDelphiparse,
                  pCommandBlock,
                  pCommandBlockName,
                  bForwardMode);

  if (bResult)
  {
    AdtDelphiBase::rootBindComments(this);
  }

  Lex_SearchPaths = 0;

  return (bResult);
}

//  ----------------------------------------------------------------------------

bool AdtDelphi::parseString(AdtParser*& pRoot,
                            const char* pString)
{
  AdtDelphiGoal*  pNativeRoot;
  bool            bParsed;

  pRoot   = 0;
  bParsed = false;

  if (parseString(adtDelphi_pDelphiContext,
                  pNativeRoot,
                  pString,
                  yyDelphiin,
                  yyDelphidebug,
                  yyDelphiparse))
  {
    pRoot   = pNativeRoot;
    bParsed = true;
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

void AdtDelphi::releaseRoot()
{
  adtDelphi_releaseRoot();
}

//  ----------------------------------------------------------------------------

AdtParser* AdtDelphi::parseRoot() const
{
  return (AdtDelphiBase::delphiRootObject());
}

//  ----------------------------------------------------------------------------

AdtSourceRoot* AdtDelphi::sourceRoot() const
{
  return (AdtDelphiBase::delphiRootObject());
}


//  ----------------------------------------------------------------------------
//  AdtCpp method implementations
//  ----------------------------------------------------------------------------
bool AdtCpp::parse(void*& pCppContext,
                   const char* pFilename,
                   FILE*& yyCppin,
                   int& yyCppdebug,
                   parse_fn yyCppparse,
                   const char* pCommandBlock,
                   const char* pCommandBlockName,
                   bool bForwardMode)
{
  bool bSucceeded = false;

  CommandBlock.isForwardMode(bForwardMode);
  CommandBlock.reset();

  if (pCommandBlock != 0)
  {
    CommandBlock.parseAppend(pCommandBlock, pCommandBlockName);
  }

  if ((yyCppparse != 0) &&
      (pFilename  != 0))
  {
    pCppContext   = (void*)this;
    yyCppin       = 0;
//    yyCppdebug    = 1;
    yyCppdebug    = 0;

    if (yyCppdebug != 0)
    {
      openLog("cpp.out", "wt");
    }

    yyCppin = ::fopen(pFilename, "rt");

    if (yyCppin != 0)
    {
      yyCpprestart(yyCppin);
      yyCpp_resetLineNumber(allocString(pFilename));
      yyCppparse();
      yyCpp_endParse();

      bSucceeded = (yyCpp_error() == 0);

      yyCpp_releaseBuffer();

      ::fclose(yyCppin);

      yyCppin = 0;
    }

    yyCppdebug = 0;
    closeLog();
  }

  CommandBlock.execute(*this, yyCppin, yyCppdebug, yyCppparse);

  pCppContext = 0;

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

bool AdtCpp::parseString(void*& pCppContext,
                         AdtCppTranslationUnit*& pRoot,
                         const char* pString,
                         FILE*& yyCppin,
                         int& yyCppdebug,
                         parse_fn yyCppparse)
{
  bool bSucceeded = false;

  if ((yyCppparse != 0) &&
      (pString    != 0))
  {
    string  rFileName;

    if (beginParseString(yyCppin, rFileName, pString))
    {
      AdtCppTranslationUnit*  pOldRoot;
      void*                   pLastContext;

      pLastContext    = pCppContext;
      pCppContext     = (void*)this;
      pOldRoot        = AdtCppBase::cppRootObject();

      if (pOldRoot != 0)
      {
        pOldRoot->lock();
      }

//      yyCppdebug   = 1;
      yyCppdebug   = 0;

      if (yyCppdebug != 0)
      {
        openLog("cpp.out", "wt");
      }

      yyCpprestart(yyCppin);
      yyCpp_resetLineNumber(0);
      yyCppparse();
      yyCpp_endParse();

      bSucceeded = (yyCpp_error() == 0);

      yyCpp_releaseBuffer();

      yyCppdebug = 0;
      closeLog();

      pRoot = AdtCppBase::cppRootObject();

      if (pRoot != 0)
      {
        pRoot->lock();
      }

      AdtCppBase::cppRootObject(pOldRoot);
      UtlReleaseReference(pOldRoot);
      endParseString(yyCppin, rFileName);

      pCppContext = pLastContext;
    }
  }

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

AdtCpp::AdtCpp()
 : AdtCompilerBase()
{

}

//  ----------------------------------------------------------------------------

AdtCpp::~AdtCpp()
{

}

//  ----------------------------------------------------------------------------

void AdtCpp::parseCommandBlock(const char* pCommandBlock, bool bEmbedded)
{
  if (bEmbedded)
  {
    string      sStrippedCommandBlock;
    const char* pLeadingBraces[1]   = {"/*%"};
    const char* pTrailingBraces[1]  = {"*/"};

    // Remove leading and trailing comment
    AdtCompilerBase::stripComments(sStrippedCommandBlock,
                                   pCommandBlock,
                                   pLeadingBraces,
                                   pTrailingBraces,
                                   1);

    AdtCompilerBase::parseCommandBlock(sStrippedCommandBlock);
  }
  else
  {
    AdtCompilerBase::parseCommandBlock(pCommandBlock);
  }
}

//  ----------------------------------------------------------------------------

bool AdtCpp::parse(const char* pFilename,
                   const char* pCommandBlock,
                   const char* pCommandBlockName,
                   const AdtStringList* pSearchPaths,
                   bool bForwardMode)
{
  bool bResult;

  Lex_SearchPaths = pSearchPaths;

  bResult = parse(adtCpp_pCppContext,
                  pFilename,
                  yyCppin,
                  yyCppdebug,
                  yyCppparse,
                  pCommandBlock,
                  pCommandBlockName,
                  bForwardMode);

  if (bResult)
  {
    AdtCppBase::rootBindComments(this);
  }

  Lex_SearchPaths = 0;

  return (bResult);
}

//  ----------------------------------------------------------------------------

bool AdtCpp::parseString(AdtParser*& pRoot,
                         const char* pString)
{
  AdtCppTranslationUnit*  pNativeRoot;
  bool                    bParsed;

  pRoot   = 0;
  bParsed = false;

  if (parseString(adtCpp_pCppContext,
                  pNativeRoot,
                  pString,
                  yyCppin,
                  yyCppdebug,
                  yyCppparse))
  {
    pRoot   = pNativeRoot;
    bParsed = true;
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

void AdtCpp::releaseRoot()
{
  adtCpp_releaseRoot();
}

//  ----------------------------------------------------------------------------

AdtParser* AdtCpp::parseRoot() const
{
  return (AdtCppBase::cppRootObject());
}

//  ----------------------------------------------------------------------------

AdtSourceRoot* AdtCpp::sourceRoot() const
{
  return (AdtCppBase::cppRootObject());
}


//  ----------------------------------------------------------------------------
//  AdtJava method implementations
//  ----------------------------------------------------------------------------
bool AdtJava::parse(void*& pJavaContext,
                    const char* pFilename,
                    FILE*& yyJavain,
                    int& yyJavadebug,
                    parse_fn yyJavaparse,
                    const char* pCommandBlock,
                    const char* pCommandBlockName,
                    bool bForwardMode)
{
  bool bSucceeded = false;

  CommandBlock.isForwardMode(bForwardMode);
  CommandBlock.reset();

  if (pCommandBlock != 0)
  {
    CommandBlock.parseAppend(pCommandBlock, pCommandBlockName);
  }

  if ((yyJavaparse != 0) &&
      (pFilename   != 0))
  {
    pJavaContext   = (void*)this;
    yyJavain       = 0;
//    yyJavadebug    = 1;
    yyJavadebug    = 0;

    if (yyJavadebug != 0)
    {
      openLog("Java.out", "wt");
    }

    yyJavain = ::fopen(pFilename, "rt");

    if (yyJavain != 0)
    {
      yyJavarestart(yyJavain);
      yyJava_resetLineNumber(allocString(pFilename));
      yyJavaparse();
      yyJava_endParse();
      yyJava_releaseBuffer();

      bSucceeded = (yyJava_error() == 0);

      ::fclose(yyJavain);

      yyJavain = 0;
    }

    yyJavadebug = 0;
    closeLog();
  }

  CommandBlock.execute(*this, yyJavain, yyJavadebug, yyJavaparse);

  pJavaContext = 0;

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

bool AdtJava::parseString(void*& pJavaContext,
                          AdtJavaGoal*& pRoot,
                          const char* pString,
                          FILE*& yyJavain,
                          int& yyJavadebug,
                          parse_fn yyJavaparse)
{
  bool bSucceeded = false;

  if ((yyJavaparse != 0) &&
      (pString     != 0))
  {
    string  rFileName;

    if (beginParseString(yyJavain, rFileName, pString))
    {
      AdtJavaGoal*  pOldRoot;
      void*         pLastContext;

      pLastContext    = pJavaContext;
      pJavaContext    = (void*)this;
      pOldRoot        = AdtJavaBase::javaRootObject();

      if (pOldRoot != 0)
      {
        pOldRoot->lock();
      }

//      yyJavadebug   = 1;
      yyJavadebug   = 0;

      if (yyJavadebug != 0)
      {
        openLog("cpp.out", "wt");
      }

      yyJavarestart(yyJavain);
      yyJava_resetLineNumber(0);
      yyJavaparse();
      yyJava_endParse();

      bSucceeded = (yyJava_error() == 0);

      yyJava_releaseBuffer();

      yyJavadebug = 0;
      closeLog();

      pRoot = AdtJavaBase::javaRootObject();

      if (pRoot != 0)
      {
        pRoot->lock();
      }

      AdtJavaBase::javaRootObject(pOldRoot);
      UtlReleaseReference(pOldRoot);
      endParseString(yyJavain, rFileName);

      pJavaContext = pLastContext;
    }
  }

  return (bSucceeded);
}

//  ----------------------------------------------------------------------------

AdtJava::AdtJava()
 : AdtCompilerBase()
{

}

//  ----------------------------------------------------------------------------

AdtJava::~AdtJava()
{

}

//  ----------------------------------------------------------------------------

void AdtJava::parseCommandBlock(const char* pCommandBlock, bool bEmbedded)
{
  if (bEmbedded)
  {
    string      sStrippedCommandBlock;
    const char* pLeadingBraces[1]   = {"/*%"};
    const char* pTrailingBraces[1]  = {"*/"};

    // Remove leading and trailing comment
    AdtCompilerBase::stripComments(sStrippedCommandBlock,
                                   pCommandBlock,
                                   pLeadingBraces,
                                   pTrailingBraces,
                                   1);

    AdtCompilerBase::parseCommandBlock(sStrippedCommandBlock);
  }
  else
  {
    AdtCompilerBase::parseCommandBlock(pCommandBlock);
  }
}

//  ----------------------------------------------------------------------------

bool AdtJava::parse(const char* pFilename,
                    const char* pCommandBlock,
                    const char* pCommandBlockName,
                    const AdtStringList* pSearchPaths,
                    bool bForwardMode)
{
  bool bResult;

  Lex_SearchPaths = pSearchPaths;

  bResult = parse(adtJava_pJavaContext,
                  pFilename,
                  yyJavain,
                  yyJavadebug,
                  yyJavaparse,
                  pCommandBlock,
                  pCommandBlockName,
                  bForwardMode);

  if (bResult)
  {
    AdtJavaBase::rootBindComments(this);
  }

  Lex_SearchPaths = 0;

  return (bResult);
}

//  ----------------------------------------------------------------------------

bool AdtJava::parseString(AdtParser*& pRoot,
                          const char* pString)
{
  AdtJavaGoal*  pNativeRoot;
  bool          bParsed;

  pRoot   = 0;
  bParsed = false;

  if (parseString(adtJava_pJavaContext,
                  pNativeRoot,
                  pString,
                  yyJavain,
                  yyJavadebug,
                  yyJavaparse))
  {
    pRoot   = pNativeRoot;
    bParsed = true;
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

void AdtJava::releaseRoot()
{
  adtJava_releaseRoot();
}

//  ----------------------------------------------------------------------------

AdtParser* AdtJava::parseRoot() const
{
  return (AdtJavaBase::javaRootObject());
}

//  ----------------------------------------------------------------------------

AdtSourceRoot* AdtJava::sourceRoot() const
{
  return (AdtJavaBase::javaRootObject());
}
