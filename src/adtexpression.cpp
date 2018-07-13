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
//    adtexpression.cpp
//
//  Purpose:
//    This file includes implementations of classes used to build expression
//    parse trees.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtexpression.hpp"


//  ----------------------------------------------------------------------------

const char* adtExpression_AllocString(void* pContext, const char* pTokenText)
{
  const char* pString = 0;

  if (pContext != 0)
  {
    AdtExpressionCompiler* Context = (AdtExpressionCompiler*)pContext;

    pString = Context->allocString(pTokenText);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void* adtExpressionIndexList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtExpressionIndexList_create(void* pExpressionIndexListObj)
{
  return (Hnd(new AdtExpressionIndexList(ObjAndRelease(pExpressionIndexListObj)), 0, 0));
}

//  ----------------------------------------------------------------------------

void* adtExpressionPostfix_create(void* pExprAdditiveObj, void* pExprIndexListObj, const char* pIdentifier, int nNumber, int nIsSubIndex, int nIsMinus)
{
  return (Hnd(new AdtExpressionPostfix(ObjAndRelease(pExprAdditiveObj), ObjAndRelease(pExprIndexListObj), pIdentifier, nNumber, nIsSubIndex != 0, nIsMinus != 0), 0, 0));
}

//  ----------------------------------------------------------------------------

void* adtExpressionUnary_create(void* pExprPostfixObj, int nType)
{
  return (Hnd(new AdtExpressionUnary(ObjAndRelease(pExprPostfixObj), (AdtExpressionUnaryOp)nType), 0, 0));
}

//  ----------------------------------------------------------------------------

void* adtExpressionMultiplicative_create(void* pExprMultObj, void* pExprUnaryObj, int nType)
{
  return (Hnd(new AdtExpressionMultiplicative(ObjAndRelease(pExprMultObj), ObjAndRelease(pExprUnaryObj), (AdtExpressionMultiplicativeOp)nType), 0, 0));
}

//  ----------------------------------------------------------------------------

void* adtExpressionAdditive_create(void* pExprAddObj, void* pExprMultObj, int nType)
{
  AdtExpressionAdditive* pObj = new AdtExpressionAdditive(ObjAndRelease(pExprAddObj), ObjAndRelease(pExprMultObj), (AdtExpressionAdditiveOp)nType);

  // Set the root object here. As the grammar doesn't have an explicit root the
  // root becomes the last AdtExpressionAdditive created, which should be correct.
  AdtExpressionBase::expressionRootObject(pObj);

  return (Hnd(pObj, 0, 0));
}


//  ----------------------------------------------------------------------------
//  AdtExpressionCompiler method implementations
//  ----------------------------------------------------------------------------
AdtExpressionCompiler::AdtExpressionCompiler()
 : AdtCommon(),
   ErrorMsg(),
   ErrorContext()
{

}

//  ----------------------------------------------------------------------------

AdtExpressionCompiler::~AdtExpressionCompiler()
{

}

//  ----------------------------------------------------------------------------

AdtExpressionAdditive* AdtExpressionCompiler::compile(const char* pExpressionText)
{
  AdtExpressionAdditive* pExpression = 0;

  if (pExpressionText != 0)
  {
    string rFileName;

    ErrorMsg      = "";
    ErrorContext  = "";

    if (beginParseString(yyExpressionin, rFileName, pExpressionText))
    {
      adtExpression_pContext  = (void*)this;
//      yyExpressiondebug       = 1;
      yyExpressiondebug       = 0;

      yyExpression_resetError();
      yyExpressionrestart(yyExpressionin);
      yyExpressionparse();
      yyExpression_endParse();

      adtExpression_pContext  = 0;
      yyExpressiondebug       = 0;

      if (yyExpression_error() == 0)
      {
        pExpression = AdtExpressionBase::expressionRootObject();

        if (pExpression != 0)
        {
          pExpression->lock();
        }
      }
      else
      {
        ErrorMsg      = yyExpression_errorMsg();
        ErrorContext  = pExpressionText;
      }

      AdtExpressionBase::expressionRootObject(0);
      yyExpression_releaseBuffer();
      endParseString(yyExpressionin, rFileName);
    }
  }

  return (pExpression);
}

//  ----------------------------------------------------------------------------

void AdtExpressionCompiler::findDependencies(const char* pExpressionText,
                                             AdtStringList& rDependencyList,
                                             string* pReconstructedText,
                                             AdtExpressionAdditive** ppRoot)
{
  AdtExpressionAdditive*  pRoot = compile(pExpressionText);

  if (pRoot != 0)
  {
    pRoot->enumerateDependencies(rDependencyList);

    if (pReconstructedText != 0)
    {
      pRoot->buildExpression(*pReconstructedText, false);
    }

    if (ppRoot != 0)
    {
      *ppRoot = pRoot;
      pRoot->lock();
    }

    UtlReleaseReference(pRoot);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionCompiler::reconstruct(const char* pExpressionText,
                                        string& rReconstructedText)
{
  AdtExpressionAdditive*  pRoot = compile(pExpressionText);

  if (pRoot != 0)
  {
    rReconstructedText = "";

    pRoot->buildExpression(rReconstructedText, false);

    UtlReleaseReference(pRoot);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionCompiler::reconstructWithIndexing(const char* pExpressionText,
                                                    const char* pIndexBase,
                                                    int nCurrentIndex,
                                                    string& rReconstructedText)
{
  AdtExpressionAdditive*  pRoot = compile(pExpressionText);

  if (pRoot != 0)
  {
    rReconstructedText = "";

    pRoot->fixIndexing(pIndexBase, nCurrentIndex);
    pRoot->buildExpression(rReconstructedText, false);

    UtlReleaseReference(pRoot);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionCompiler::reconstructWithPossibleSEXPArgs(const char* pExpressionText,
                                                            string& rReconstructedText,
                                                            const AdtIntByStringMap& rWithSEXP_map,
                                                            bool bWithUnderscore,
                                                            bool bR_Prefix)
{
  AdtExpressionAdditive*  pRoot = compile(pExpressionText);

  if (pRoot != 0)
  {
    AdtParserPtrList      List;
    AdtParserPtrListIter  Iter;

    rReconstructedText = "";

    pRoot->findObjects(List, "AdtExpressionPostfix");

    for (Iter = List.begin() ; Iter != List.end() ; ++Iter)
    {
      AdtExpressionPostfix* pObj = (AdtExpressionPostfix*)(AdtParser*)(*Iter);

      if (pObj != 0)
      {
        pObj->convertFromSEXP(rWithSEXP_map, bWithUnderscore, bR_Prefix);
      }
    }

    pRoot->buildExpression(rReconstructedText, false);

    UtlReleaseReference(pRoot);
  }
}


//  ----------------------------------------------------------------------------
//  AdtExpressionBase method implementations
//  ----------------------------------------------------------------------------
AdtExpressionAdditive*  AdtExpressionBase::ExpressionRootObject = 0;

//  ----------------------------------------------------------------------------

AdtExpressionBase::AdtExpressionBase()
 : AdtParser()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtExpressionBase::AdtExpressionBase(const AdtExpressionBase& rCopy)
 : AdtParser(rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtExpressionBase::~AdtExpressionBase()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtExpressionBase::expressionRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(ExpressionRootObject);

  ExpressionRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtExpressionAdditive"))
    {
      ExpressionRootObject = (AdtExpressionAdditive*)pRoot;
      ExpressionRootObject->lock();
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtExpressionAdditive* AdtExpressionBase::expressionRootObject()
{
  return (ExpressionRootObject);
}

//  ----------------------------------------------------------------------------

void AdtExpressionBase::buildExpression(string& rResult,
                                        bool bStripRaggedIndexing)
{
  // Do nothing
}


//  ----------------------------------------------------------------------------
//  AdtExpressionIndexList class
//  ----------------------------------------------------------------------------
AdtExpressionIndexList::AdtExpressionIndexList(AdtParser* pExpressionIndexListObj)
 : AdtExpressionBase()
{
  IndicesFixed = false;

  add(pExpressionIndexListObj);
}

//  ----------------------------------------------------------------------------

AdtExpressionIndexList::AdtExpressionIndexList(const AdtExpressionIndexList& rCopy)
 : AdtExpressionBase(rCopy)
{
  IndicesFixed = false;
}

//  ----------------------------------------------------------------------------

AdtExpressionIndexList::~AdtExpressionIndexList()
{

}

//  ----------------------------------------------------------------------------

void AdtExpressionIndexList::buildExpression(string& rResult,
                                             bool bStripRaggedIndexing)
{
  AdtParserPtrListConstIter Iter;
  bool                      bFirst = true;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtExpressionBase*  pObj = (AdtExpressionBase*)(AdtParser*)(*Iter);

    if (!bFirst)
    {
      rResult += IndicesFixed ? "][" : ",";
    }

    pObj->buildExpression(rResult, bStripRaggedIndexing);

    bFirst = false;
  }
}

//  ----------------------------------------------------------------------------

implType(AdtExpressionIndexList, AdtExpressionBase);


//  ----------------------------------------------------------------------------
//  AdtExpressionPostfix method implementations
//  ----------------------------------------------------------------------------
AdtExpressionPostfix::AdtExpressionPostfix(AdtParser* pExprAdditiveObj,
                                           AdtParser* pExprIndexListObj,
                                           const char* pStringExp,
                                           int nNumber,
                                           bool bIsSubIndex,
                                           bool bIsMinus)
 : AdtExpressionBase()
{
  initObject(ExpressionAdditive,  pExprAdditiveObj,   AdtExpressionAdditive,  true);
  initObject(ExpressionIndexList, pExprIndexListObj,  AdtExpressionIndexList, true);

  Number      = 0;
  IsNumber    = false;
  IsSubIndex  = bIsSubIndex;
  IsMinus     = bIsMinus;

  if (ExpressionAdditive == 0)
  {
    if (pStringExp != 0)
    {
      name(pStringExp);
    }
    else
    {
      Number    = nNumber;
      IsNumber  = true;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtExpressionPostfix::AdtExpressionPostfix(const AdtExpressionPostfix& rCopy)
 : AdtExpressionBase(rCopy)
{
  copyObject(ExpressionAdditive,  rCopy, AdtExpressionAdditive);
  copyObject(ExpressionIndexList, rCopy, AdtExpressionIndexList);

  Number      = rCopy.Number;
  IsNumber    = rCopy.IsNumber;
  IsSubIndex  = rCopy.IsSubIndex;
  IsMinus     = rCopy.IsMinus;
}

//  ----------------------------------------------------------------------------

AdtExpressionPostfix::~AdtExpressionPostfix()
{
  UtlReleaseReference(ExpressionAdditive);
}

//  ----------------------------------------------------------------------------

bool AdtExpressionPostfix::buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                           const AdtStringByIntMap& rUpperBoundMap,
                                           int nCurrentIndex,
                                           int& nSubIndexCount,
                                           int& nSmallestIndex,
                                           string& sLowerDimension,
                                           string& sUpperDimension) const
{
  bool bBuilt = false;

  if (ExpressionIndexList != 0)
  {
    AdtParserPtrListConstIter Iter;
    const AdtParserPtrList&   rExpList = ExpressionIndexList->objList();
    bool                      bFirst   = true;

    bBuilt = true;

    ASSERT(nSubIndexCount == 0);

    sLowerDimension.clear();
    sUpperDimension.clear();

    for (Iter = rExpList.begin() ; Iter != rExpList.end() ; ++Iter)
    {
      AdtExpressionAdditive* pExpressionIndex = (AdtExpressionAdditive*)(AdtParser*)(*Iter);

      if (!bFirst)
      {
        sUpperDimension += ",";
      }

      if (pExpressionIndex != 0)
      {
        string  sLocalLowerDimension;
        string  sLocalUpperDimension;

        nSubIndexCount = 0;

        bBuilt = pExpressionIndex->buildDimensions(rLowerBoundMap,
                                                   rUpperBoundMap,
                                                   nCurrentIndex,
                                                   nSubIndexCount,
                                                   nSmallestIndex,
                                                   sLocalLowerDimension,
                                                   sLocalUpperDimension) & bBuilt;

        if (bBuilt)
        {
          if (sLocalLowerDimension.length() > 0)
          {
            sUpperDimension += sLocalLowerDimension + ":";
          }

          sUpperDimension += sLocalUpperDimension;
        }
      }

      bFirst = false;
    }
  }
  else if (IsSubIndex)
  {
    nSubIndexCount++;

    if (nSubIndexCount > 1)
    {
      // Error condition. Can't have multiple substitution indexs in a given
      // expression.
    }
    else
    {
      int                         nIndex  = IsMinus ? nCurrentIndex - Number : Number - 1;
      AdtStringByIntMapConstIter  Iter;

      Iter = rLowerBoundMap.find(nIndex);

      if (Iter != rLowerBoundMap.end())
      {
        sLowerDimension += (*Iter).second;
      }
      else if (sLowerDimension.length() > 0)
      {
        sLowerDimension += "1";
      }

      Iter = rUpperBoundMap.find(nIndex);

      if (Iter != rUpperBoundMap.end())
      {
        sUpperDimension += (*Iter).second;
        bBuilt           = true;
      }

      if (nSmallestIndex > nIndex)
      {
        nSmallestIndex = nIndex;
      }
    }
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

void AdtExpressionPostfix::fixIndexing(const char* pIndexBase, int nCurrentIndex)
{
  if (ExpressionIndexList != 0)
  {
    AdtParserPtrListConstIter Iter;
    const AdtParserPtrList&   rExpList = ExpressionIndexList->objList();

    ExpressionIndexList->indicesFixed(true);

    for (Iter = rExpList.begin() ; Iter != rExpList.end() ; ++Iter)
    {
      AdtExpressionAdditive* pExpressionIndex = (AdtExpressionAdditive*)(AdtParser*)(*Iter);

      if (pExpressionIndex != 0)
      {
        pExpressionIndex->fixIndexing(pIndexBase, nCurrentIndex);
      }
    }
  }
  else if (IsSubIndex)
  {
    char    sBuffer[32] = {0};
    int     nIndex      = IsMinus ? nCurrentIndex - Number : Number - 1;
    string  sName(pIndexBase);

    ::sprintf(sBuffer, "%d", nIndex);

    sName += sBuffer;

    name(sName);

    IsNumber = false;
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionPostfix::convertFromSEXP(const AdtIntByStringMap& rWithSEXP_map,
                                           bool bWithUnderscore,
                                           bool bR_Prefix)
{
  if (isString())
  {
    AdtIntByStringMapConstIter  Iter      = rWithSEXP_map.find(name());
    int                         nType     = -1;
    bool                        bConvert  = false;

    // The key value in the rWithSEXP_map map indicates whether the named
    // argument is a global constant or not. If 0 then it is a argument list
    // local and if 1 it is a global. When 1 we do not want to assume it is
    // an SEXP so don't wnat to convert it.
    if (Iter != rWithSEXP_map.end())
    {
      nType = Iter->second;
    }

    if (bWithUnderscore)
    {
      bConvert = (nType != 1);
    }
    else
    {
      bConvert = (nType == 0);
    }

    if (bConvert)
    {
      string sCast;

      if (bR_Prefix)
      {
        if (bWithUnderscore)
        {
          sCast = "R_INTEGER(arg_";
        }
        else
        {
          sCast = "R_INTEGER(";
        }
      }
      else
      {
        if (bWithUnderscore)
        {
          sCast = "INTEGER(arg_";
        }
        else
        {
          sCast = "INTEGER(";
        }
      }

      name(sCast + name() + ")[0]");
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionPostfix::buildExpression(string& rResult,
                                           bool bStripRaggedIndexing)
{
  if (ExpressionAdditive != 0)
  {
    rResult += "(";

    ExpressionAdditive->buildExpression(rResult, bStripRaggedIndexing);

    rResult += ")";
  }
  else
  {
    if (IsNumber)
    {
      char        sBuffer[32] = {0};
      const char* pFormat     = 0;

      if (IsSubIndex)
      {
        pFormat = IsMinus ? "<-%d>" : "<%d>";
      }
      else
      {
        pFormat = "%d";
      }

      ::sprintf(sBuffer, pFormat, Number);

      rResult += sBuffer;
    }
    else
    {
      rResult += name();

      if ((ExpressionIndexList != 0) && !bStripRaggedIndexing)
      {
        rResult += "[";

        ExpressionIndexList->buildExpression(rResult, bStripRaggedIndexing);

        rResult += "]";
      }
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtExpressionPostfix, AdtExpressionBase);


//  ----------------------------------------------------------------------------
//  AdtExpressionUnary method implementations
//  ----------------------------------------------------------------------------
AdtExpressionUnary::AdtExpressionUnary(AdtParser* pExprPostfixObj,
                                       AdtExpressionUnaryOp nType)
 : AdtExpressionBase()
{
  initObject(ExpressionPostfix, pExprPostfixObj, AdtExpressionPostfix, true);

  Op = nType;
}

//  ----------------------------------------------------------------------------

AdtExpressionUnary::AdtExpressionUnary(const AdtExpressionUnary& rCopy)
 : AdtExpressionBase(rCopy)
{
  copyObject(ExpressionPostfix, rCopy, AdtExpressionPostfix);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtExpressionUnary::~AdtExpressionUnary()
{
  UtlReleaseReference(ExpressionPostfix);
}

//  ----------------------------------------------------------------------------

bool AdtExpressionUnary::buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                         const AdtStringByIntMap& rUpperBoundMap,
                                         int nCurrentIndex,
                                         int& nSubIndexCount,
                                         int& nSmallestIndex,
                                         string& sLowerDimension,
                                         string& sUpperDimension) const
{
  bool bBuilt = true;

  switch(Op)
  {
    default:
    case AdtExpressionUnaryOp_NONE:
    {
      break;
    }

    case AdtExpressionUnaryOp_PLUS:
    {
      sLowerDimension += " +";
      sUpperDimension += " +";
      break;
    }

    case AdtExpressionUnaryOp_MINUS:
    {
      sLowerDimension += " -";
      sUpperDimension += " -";
      break;
    }
  }

  if (ExpressionPostfix != 0)
  {
    bBuilt = ExpressionPostfix->buildDimensions(rLowerBoundMap,
                                                rUpperBoundMap,
                                                nCurrentIndex,
                                                nSubIndexCount,
                                                nSmallestIndex,
                                                sLowerDimension,
                                                sUpperDimension);
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

void AdtExpressionUnary::fixIndexing(const char* pIndexBase, int nCurrentIndex)
{
  if (ExpressionPostfix != 0)
  {
    ExpressionPostfix->fixIndexing(pIndexBase, nCurrentIndex);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionUnary::buildExpression(string& rResult,
                                         bool bStripRaggedIndexing)
{
  switch(Op)
  {
    default:
    case AdtExpressionUnaryOp_NONE:
    {
      break;
    }

    case AdtExpressionUnaryOp_PLUS:
    {
      rResult += " +";
      break;
    }

    case AdtExpressionUnaryOp_MINUS:
    {
      rResult += " -";
      break;
    }
  }

  if (ExpressionPostfix != 0)
  {
    ExpressionPostfix->buildExpression(rResult, bStripRaggedIndexing);
  }
}

//  ----------------------------------------------------------------------------

implType(AdtExpressionUnary, AdtExpressionBase);


//  ----------------------------------------------------------------------------
//  AdtExpressionAdditive class
//  ----------------------------------------------------------------------------
AdtExpressionMultiplicative::AdtExpressionMultiplicative(AdtParser* pExprMultObj,
                                                         AdtParser* pExprUnaryObj,
                                                         AdtExpressionMultiplicativeOp nType)
 : AdtExpressionBase()
{
  initObject(ExpressionMultiplicative,  pExprMultObj,  AdtExpressionMultiplicative, true);
  initObject(ExpressionUnary,           pExprUnaryObj, AdtExpressionUnary,          true);

  Op = nType;
}

//  ----------------------------------------------------------------------------

AdtExpressionMultiplicative::AdtExpressionMultiplicative(const AdtExpressionMultiplicative& rCopy)
 : AdtExpressionBase(rCopy)
{
  copyObject(ExpressionMultiplicative,  rCopy, AdtExpressionMultiplicative);
  copyObject(ExpressionUnary,           rCopy, AdtExpressionUnary);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtExpressionMultiplicative::~AdtExpressionMultiplicative()
{
  UtlReleaseReference(ExpressionMultiplicative);
  UtlReleaseReference(ExpressionUnary);
}

//  ----------------------------------------------------------------------------

bool AdtExpressionMultiplicative::buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                                  const AdtStringByIntMap& rUpperBoundMap,
                                                  int nCurrentIndex,
                                                  int& nSubIndexCount,
                                                  int& nSmallestIndex,
                                                  string& sLowerDimension,
                                                  string& sUpperDimension) const
{
  bool bBuilt = true;

  if (ExpressionMultiplicative != 0)
  {
    bBuilt = ExpressionMultiplicative->buildDimensions(rLowerBoundMap,
                                                       rUpperBoundMap,
                                                       nCurrentIndex,
                                                       nSubIndexCount,
                                                       nSmallestIndex,
                                                       sLowerDimension,
                                                       sUpperDimension) & bBuilt;
  }

  switch(Op)
  {
    default:
    case AdtExpressionMultiplicativeOp_NONE:
    {
      break;
    }

    case AdtExpressionMultiplicativeOp_MUL:
    case AdtExpressionMultiplicativeOp_DIV:
    {
      if (sLowerDimension.length() == 0)
      {
        sLowerDimension += "1";
      }
      break;
    }
  }

  switch(Op)
  {
    default:
    case AdtExpressionMultiplicativeOp_NONE:
    {
      break;
    }

    case AdtExpressionMultiplicativeOp_MUL:
    {
      sLowerDimension += " * ";
      sUpperDimension += " * ";
      break;
    }

    case AdtExpressionMultiplicativeOp_DIV:
    {
      sLowerDimension += " / ";
      sUpperDimension += " / ";
      break;
    }
  }

  if (ExpressionUnary != 0)
  {
    bBuilt = ExpressionUnary->buildDimensions(rLowerBoundMap,
                                              rUpperBoundMap,
                                              nCurrentIndex,
                                              nSubIndexCount,
                                              nSmallestIndex,
                                              sLowerDimension,
                                              sUpperDimension) & bBuilt;
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

void AdtExpressionMultiplicative::fixIndexing(const char* pIndexBase, int nCurrentIndex)
{
  if (ExpressionMultiplicative != 0)
  {
    ExpressionMultiplicative->fixIndexing(pIndexBase, nCurrentIndex);
  }

  if (ExpressionUnary != 0)
  {
    ExpressionUnary->fixIndexing(pIndexBase, nCurrentIndex);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionMultiplicative::buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing)
{
  if (ExpressionMultiplicative != 0)
  {
    ExpressionMultiplicative->buildExpression(rResult, bStripRaggedIndexing);
  }

  switch(Op)
  {
    default:
    case AdtExpressionMultiplicativeOp_NONE:
    {
      break;
    }

    case AdtExpressionMultiplicativeOp_MUL:
    {
      rResult += " * ";
      break;
    }

    case AdtExpressionMultiplicativeOp_DIV:
    {
      rResult += " / ";
      break;
    }
  }

  if (ExpressionUnary != 0)
  {
    ExpressionUnary->buildExpression(rResult, bStripRaggedIndexing);
  }
}

//  ----------------------------------------------------------------------------

implType(AdtExpressionMultiplicative, AdtExpressionBase);


//  ----------------------------------------------------------------------------
//  AdtExpressionBase method implementations
//  ----------------------------------------------------------------------------
implType(AdtExpressionBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtExpressionAdditive method implementations
//  ----------------------------------------------------------------------------
AdtExpressionAdditive::AdtExpressionAdditive(AdtParser* pExprAddObj,
                                             AdtParser* pExprMultObj,
                                             AdtExpressionAdditiveOp nType)
 : AdtExpressionBase()
{
  initObject(ExpressionAdditive,       pExprAddObj,  AdtExpressionAdditive,       true);
  initObject(ExpressionMultiplicative, pExprMultObj, AdtExpressionMultiplicative, true);

  Op = nType;
}

//  ----------------------------------------------------------------------------

AdtExpressionAdditive::AdtExpressionAdditive(const AdtExpressionAdditive& rCopy)
 : AdtExpressionBase(rCopy)
{
  copyObject(ExpressionAdditive,       rCopy, AdtExpressionAdditive);
  copyObject(ExpressionMultiplicative, rCopy, AdtExpressionMultiplicative);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtExpressionAdditive::~AdtExpressionAdditive()
{
  UtlReleaseReference(ExpressionAdditive);
  UtlReleaseReference(ExpressionMultiplicative);
}

//  ----------------------------------------------------------------------------

void AdtExpressionAdditive::enumerateDependencies(AdtStringList& rDependencyList) const
{
  AdtParserPtrList      ObjList;
  AdtParserPtrListIter  Iter;

  findObjects(ObjList, "AdtExpressionPostfix");

  for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
  {
    const AdtParser* pObj = *Iter;

    if (pObj != 0)
    {
      AdtExpressionPostfix* pPostfixObj = (AdtExpressionPostfix*)pObj;

      if (pPostfixObj->isString())
      {
        rDependencyList.push_back(pPostfixObj->name());
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtExpressionAdditive::buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                            const AdtStringByIntMap& rUpperBoundMap,
                                            int nCurrentIndex,
                                            int& nSubIndexCount,
                                            int& nSmallestIndex,
                                            string& sLowerDimension,
                                            string& sUpperDimension) const
{
  bool bBuilt = true;

  if (ExpressionAdditive != 0)
  {
    bBuilt = ExpressionAdditive->buildDimensions(rLowerBoundMap,
                                                 rUpperBoundMap,
                                                 nCurrentIndex,
                                                 nSubIndexCount,
                                                 nSmallestIndex,
                                                 sLowerDimension,
                                                 sUpperDimension) & bBuilt;
  }

  switch(Op)
  {
    default:
    case AdtExpressionAdditiveOp_NONE:
    {
      break;
    }

    case AdtExpressionAdditiveOp_ADD:
    case AdtExpressionAdditiveOp_SUB:
    {
      if (sLowerDimension.length() == 0)
      {
        sLowerDimension += "1";
      }
      break;
    }
  }

  switch(Op)
  {
    default:
    case AdtExpressionAdditiveOp_NONE:
    {
      break;
    }

    case AdtExpressionAdditiveOp_ADD:
    {
      sLowerDimension += " + ";
      sUpperDimension += " + ";
      break;
    }

    case AdtExpressionAdditiveOp_SUB:
    {
      sLowerDimension += " - ";
      sUpperDimension += " - ";
      break;
    }
  }

  if (ExpressionMultiplicative != 0)
  {
    bBuilt = ExpressionMultiplicative->buildDimensions(rLowerBoundMap,
                                                       rUpperBoundMap,
                                                       nCurrentIndex,
                                                       nSubIndexCount,
                                                       nSmallestIndex,
                                                       sLowerDimension,
                                                       sUpperDimension) & bBuilt;
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

void AdtExpressionAdditive::fixIndexing(const char* pIndexBase, int nCurrentIndex)
{
  if (ExpressionAdditive != 0)
  {
    ExpressionAdditive->fixIndexing(pIndexBase, nCurrentIndex);
  }

  if (ExpressionMultiplicative != 0)
  {
    ExpressionMultiplicative->fixIndexing(pIndexBase, nCurrentIndex);
  }
}

//  ----------------------------------------------------------------------------

void AdtExpressionAdditive::buildExpression(string& rResult,
                                            bool bStripRaggedIndexing)
{
  if (ExpressionAdditive != 0)
  {
    ExpressionAdditive->buildExpression(rResult, bStripRaggedIndexing);
  }

  switch(Op)
  {
    default:
    case AdtExpressionAdditiveOp_NONE:
    {
      break;
    }

    case AdtExpressionAdditiveOp_ADD:
    {
      rResult += " + ";
      break;
    }

    case AdtExpressionAdditiveOp_SUB:
    {
      rResult += " - ";
      break;
    }
  }

  if (ExpressionMultiplicative != 0)
  {
    ExpressionMultiplicative->buildExpression(rResult, bStripRaggedIndexing);
  }
}

//  ----------------------------------------------------------------------------

bool AdtExpressionAdditive::buildArrayDimension(const char* pArrayName,
                                                const AdtStringByIntMap& rLowerBoundMap,
                                                const AdtStringByIntMap& rUpperBoundMap,
                                                int nCurrentIndex,
                                                int& nSmallestIndex,
                                                string& sDimension) const
{
  bool bBuilt = false;

  if (pArrayName != 0)
  {
    AdtExpressionPostfix* pObj = (AdtExpressionPostfix*)findObject("AdtExpressionPostfix", pArrayName);

    if (pObj != 0)
    {
      int     nSubIndexCount = 0;
      string  sLowerDimension;
      string  sUpperDimension;

      sDimension.clear();

      bBuilt = pObj->buildDimensions(rLowerBoundMap,
                                     rUpperBoundMap,
                                     nCurrentIndex,
                                     nSubIndexCount,
                                     nSmallestIndex,
                                     sLowerDimension,
                                     sUpperDimension);

      if (bBuilt)
      {
        if (sLowerDimension.length() > 0)
        {
          sDimension += sLowerDimension + ":";
        }

        sDimension += sUpperDimension;
      }
    }
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

implType(AdtExpressionAdditive, AdtExpressionBase);
