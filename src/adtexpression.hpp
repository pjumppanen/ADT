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
//    adtexpression.hpp
//
//  Purpose:
//    This file includes declarations of classes used to build expression
//    parse trees.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTEXPRESSION_HPP
#define __ADTEXPRESSION_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION const char*  adtExpression_AllocString(void* pContext, const char* pTokenText);

C_FUNCTION void* adtExpressionIndexList_add(void* pList, void* pObj);
C_FUNCTION void* adtExpressionIndexList_create(void* pExpressionIndexListObj);
C_FUNCTION void* adtExpressionPostfix_create(void* pExprAdditiveObj, void* pExprIndexListObj, const char* pIdentifier, int nNumber, int nIsSubIndex, int nIsMinus);
C_FUNCTION void* adtExpressionUnary_create(void* pExprPostfixObj, int nType);
C_FUNCTION void* adtExpressionMultiplicative_create(void* pExprMultObj, void* pExprUnaryObj, int nType);
C_FUNCTION void* adtExpressionAdditive_create(void* pExprAddObj, void* pExprMultObj, int nType);
C_FUNCTION void* adtExpressionMultiplicative_create(void* pExprMultObj, void* pExprUnaryObj, int nType);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtExpressionAdditive;


//  ----------------------------------------------------------------------------
//  class AdtExpressionCompiler
//  ----------------------------------------------------------------------------
class AdtExpressionCompiler : public AdtCommon
{
private:
  string                          ErrorMsg;
  string                          ErrorContext;

public:
  AdtExpressionCompiler();
  virtual ~AdtExpressionCompiler();

  AdtExpressionAdditive*          compile(const char* pExpressionText);

  void                            findDependencies(const char* pExpressionText,
                                                   AdtStringList& rDependencyList,
                                                   string* pReconstructedText = 0,
                                                   AdtExpressionAdditive** ppRoot = 0);

  void                            reconstruct(const char* pExpressionText,
                                              string& rReconstructedText);

  void                            reconstructWithIndexing(const char* pExpressionText,
                                                          const char* pIndexBase,
                                                          int nCurrentIndex,
                                                          string& rReconstructedText);

  void                            reconstructWithPossibleSEXPArgs(const char* pExpressionText,
                                                                  string& rReconstructedText,
                                                                  const AdtIntByStringMap& rWithSEXP_map,
                                                                  bool bWithUnderscore,
                                                                  bool bR_Prefix);
};


//  ----------------------------------------------------------------------------
//  class AdtExpressionBase
//  ----------------------------------------------------------------------------
class AdtExpressionBase : public AdtParser
{
private:
  static AdtExpressionAdditive*   ExpressionRootObject;

public:
  AdtExpressionBase();
  AdtExpressionBase(const AdtExpressionBase& rCopy);
  virtual ~AdtExpressionBase();

  static void                     expressionRootObject(AdtParser* pRoot);
  static AdtExpressionAdditive*   expressionRootObject();

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtExpressionIndexList class
//  ----------------------------------------------------------------------------
class AdtExpressionIndexList : public AdtExpressionBase
{
private:
  bool                            IndicesFixed;

public:
  AdtExpressionIndexList(AdtParser* pExpressionIndexListObj);
  AdtExpressionIndexList(const AdtExpressionIndexList& rCopy);
  virtual ~AdtExpressionIndexList();

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  void                            indicesFixed(bool bFixed);

  declListType(AdtExpressionAdditive);
  declType;
};

//  ----------------------------------------------------------------------------

inline void AdtExpressionIndexList::indicesFixed(bool bFixed)
{
  IndicesFixed = bFixed;
}


//  ----------------------------------------------------------------------------
//  AdtExpressionPostfix class
//  ----------------------------------------------------------------------------
class AdtExpressionPostfix : public AdtExpressionBase
{
private:
  AdtExpressionAdditive*          ExpressionAdditive;
  AdtExpressionIndexList*         ExpressionIndexList;
  int                             Number;
  bool                            IsNumber;
  bool                            IsSubIndex;
  bool                            IsMinus;

public:
  AdtExpressionPostfix(AdtParser* pExprAdditiveObj,
                       AdtParser* pExprIndexListObj,
                       const char* pStringExp,
                       int nNumber,
                       bool bIsSubIndex,
                       bool bIsMinus);

  AdtExpressionPostfix(const AdtExpressionPostfix& rCopy);
  virtual ~AdtExpressionPostfix();

  bool                            isNumber() const;
  bool                            isString() const;

  bool                            buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                                  const AdtStringByIntMap& rUpperBoundMap,
                                                  int nCurrentIndex,
                                                  int& nSubIndexCount,
                                                  int& nSmallestIndex,
                                                  string& sLowerDimension,
                                                  string& sUpperDimension) const;

  void                            fixIndexing(const char* pIndexBase, int nCurrentIndex);

  void                            convertFromSEXP(const AdtIntByStringMap& rWithSEXP_map,
                                                  bool bWithUnderscore,
                                                  bool bR_Prefix);

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtExpressionPostfix::isNumber() const
{
  return ((ExpressionAdditive == 0) && IsNumber);
}

//  ----------------------------------------------------------------------------

inline bool AdtExpressionPostfix::isString() const
{
  return ((ExpressionAdditive == 0) && !IsNumber);
}

//  ----------------------------------------------------------------------------

enum AdtExpressionUnaryOp
{
  AdtExpressionUnaryOp_NONE  = 0,
  AdtExpressionUnaryOp_PLUS  = 1,
  AdtExpressionUnaryOp_MINUS = 2
};


//  ----------------------------------------------------------------------------
//  AdtExpressionUnary class
//  ----------------------------------------------------------------------------
class AdtExpressionUnary : public AdtExpressionBase
{
private:
  AdtExpressionPostfix*           ExpressionPostfix;
  AdtExpressionUnaryOp            Op;

public:
  AdtExpressionUnary(AdtParser* pExprPostfixObj,
                     AdtExpressionUnaryOp nType);

  AdtExpressionUnary(const AdtExpressionUnary& rCopy);
  virtual ~AdtExpressionUnary();

  bool                            buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                                  const AdtStringByIntMap& rUpperBoundMap,
                                                  int nCurrentIndex,
                                                  int& nSubIndexCount,
                                                  int& nSmallestIndex,
                                                  string& sLowerDimension,
                                                  string& sUpperDimension) const;

  void                            fixIndexing(const char* pIndexBase, int nCurrentIndex);

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtExpressionMultiplicativeOp
{
  AdtExpressionMultiplicativeOp_NONE  = 0,
  AdtExpressionMultiplicativeOp_MUL   = 1,
  AdtExpressionMultiplicativeOp_DIV   = 2
};


//  ----------------------------------------------------------------------------
//  AdtExpressionAdditive class
//  ----------------------------------------------------------------------------
class AdtExpressionMultiplicative : public AdtExpressionBase
{
private:
  AdtExpressionMultiplicative*    ExpressionMultiplicative;
  AdtExpressionUnary*             ExpressionUnary;
  AdtExpressionMultiplicativeOp   Op;

public:
  AdtExpressionMultiplicative(AdtParser* pExprMultObj,
                              AdtParser* pExprUnaryObj,
                              AdtExpressionMultiplicativeOp nType);

  AdtExpressionMultiplicative(const AdtExpressionMultiplicative& rCopy);
  virtual ~AdtExpressionMultiplicative();

  bool                            buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                                  const AdtStringByIntMap& rUpperBoundMap,
                                                  int nCurrentIndex,
                                                  int& nSubIndexCount,
                                                  int& nSmallestIndex,
                                                  string& sLowerDimension,
                                                  string& sUpperDimension) const;

  void                            fixIndexing(const char* pIndexBase, int nCurrentIndex);

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtExpressionAdditiveOp
{
  AdtExpressionAdditiveOp_NONE = 0,
  AdtExpressionAdditiveOp_ADD  = 1,
  AdtExpressionAdditiveOp_SUB  = 2
};


//  ----------------------------------------------------------------------------
//  AdtExpressionAdditive class
//  ----------------------------------------------------------------------------
class AdtExpressionAdditive : public AdtExpressionBase
{
private:
  AdtExpressionAdditive*          ExpressionAdditive;
  AdtExpressionMultiplicative*    ExpressionMultiplicative;
  AdtExpressionAdditiveOp         Op;

public:
  AdtExpressionAdditive(AdtParser* pExprAddObj,
                        AdtParser* pExprMultObj,
                        AdtExpressionAdditiveOp nType);

  AdtExpressionAdditive(const AdtExpressionAdditive& rCopy);
  virtual ~AdtExpressionAdditive();

  bool                            buildDimensions(const AdtStringByIntMap& rLowerBoundMap,
                                                  const AdtStringByIntMap& rUpperBoundMap,
                                                  int nCurrentIndex,
                                                  int& nSubIndexCount,
                                                  int& nSmallestIndex,
                                                  string& sLowerDimension,
                                                  string& sUpperDimension) const;

  void                            fixIndexing(const char* pIndexBase, int nCurrentIndex);

  virtual void                    buildExpression(string& rResult,
                                                  bool bStripRaggedIndexing);

  void                            enumerateDependencies(AdtStringList& rDependencyList) const;

  bool                            buildArrayDimension(const char* pArrayName,
                                                      const AdtStringByIntMap& rLowerBoundMap,
                                                      const AdtStringByIntMap& rUpperBoundMap,
                                                      int nCurrentIndex,
                                                      int& nSmallestIndex,
                                                      string& sDimension) const;

  declType;
};


#endif //__cplusplus
#endif //__ADTEXPRESSION_HPP
