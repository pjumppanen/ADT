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
//    AdtFortran.hpp
//
//  Purpose:
//    This file includes declarations of classes used to collate information
//    describing the fortran file auto-differentiated output.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTFORTRAN_HPP
#define __ADTFORTRAN_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void* adtFortran_setRoot(void* pRoot);
C_FUNCTION void* adtFortran_getRoot(void);
C_FUNCTION void  adtFortran_releaseRoot(void);
C_FUNCTION void  adtFortran_releaseObject(void* pObj);
C_FUNCTION void* adtFortranList_add(void* pList, void* pObj);
C_FUNCTION void* adtFortranExecutableProgram_create(void* pObj);
C_FUNCTION void* adtFortranProgramUnit_create(void* pFunctionSubprogramObj, void* pSubroutineSubprogramObj, void* pModuleObj, void* pCallExpandObj, void* pProgramConstructObj);
C_FUNCTION void* adtFortranCallExpand_create(void* pNameObj, void* pNameListObj, void* pConditionalBodyObj, void* pTypeDeclarationStmtListObj, int nHasBrackets);
C_FUNCTION void* adtFortranProgramConstruct_create(void* pLblDefObj, void* pNameObj, void* pBodyObj, void* pEndLblDefObj);
C_FUNCTION void* adtFortranTypeDeclarationStmtList_create(void* pTypeDeclarationStmtObj);
C_FUNCTION void* adtFortranBody_create(void* pBodyConstructObj);
C_FUNCTION void* adtFortranBodyConstruct_create(void* pSpecificationPartConstructObj, void* pExecutableConstructObj);
C_FUNCTION void* adtFortranFunctionSubprogram_create(void* pFunctionStmtObj, void* pEndFunctionStmtObj, void* pBodyObj);
C_FUNCTION void* adtFortranSubroutineSubprogram_create(void* pSubroutineStmtObj, void* pEndSubroutineStmtObj, void* pBodyObj);
C_FUNCTION void* adtFortranModule_create(void* pModuleStmtObj, void* pModuleBodyObj, void* pEndModuleStmtObj);
C_FUNCTION void* adtFortranModuleBody_create(void* pModuleBodyContentObj);
C_FUNCTION void* adtFortranModuleBodyContent_create(void* pSpecificationPartConstructObj, void* pFunctionSubprogramObj, void* pSubroutineSubprogramObj);
C_FUNCTION void* adtFortranSpecificationPartConstruct_create(void* pUseStmtObj, void* pImplicitStmtObj, void* pParameterStmtObj, void* pTypeDeclarationStmtObj, void* pDimensionStmtObj, void* pIntrinsicStmtObj, void* pExternalStmtObj, void* pIntentStmtObj);
C_FUNCTION void* adtFortranExecutableConstruct_create(void* pActionStmtObj, void* pCaseConstructObj,  void* pDoConstructObj, void* pIfConstructObj, void* pWhereConstructObj);
C_FUNCTION void* adtFortranActionStmt_create(void* pArithmeticIfStmtObj, void* pAssignmentStmtObj, void* pCallStmtObj, void* pContinueStmtObj, void* pCycleStmtObj, void* pExitStmtObj, void* pIfStmtObj, void* pReturnStmtObj, void* pWhereStmtObj, void* pGotoStmtObj);
C_FUNCTION void* adtFortranRelOp_create(int nOp);
C_FUNCTION void* adtFortranTypeDeclarationStmt_create(void* pLblDefObj, void* pTypeSpecObj, void* pAttrSpecSeqObj, void* pEntityDeclListObj);
C_FUNCTION void* adtFortranAttrSpecSeq_create(void* pAttrSpecObj);
C_FUNCTION void* adtFortranTypeSpec_create(int nType, const char* pIcon);
C_FUNCTION void* adtFortranAttrSpec_create(void* pShapeSpecListObj, void* pIntentSpecObj, int nAttribute);
C_FUNCTION void* adtFortranEntityDeclList_create(void* pEntityDeclObj);
C_FUNCTION void* adtFortranEntityDecl_create(void* pNameObj, void* pExprObj, void* pCharLengthObj, void* pShapeSpecListObj, void* pInvalidEntityDeclObj);
C_FUNCTION void* adtFortranInvalidEntityDecl_create(void* pNameObj, void* pExprObj, void* pCharLengthObj, void* pShapeSpecListObj);
C_FUNCTION void* adtFortranCharLength_create(void* pExprObj, void* pIconObj);
C_FUNCTION void* adtFortranShapeSpecList_create(void* pShapeSpecObj);
C_FUNCTION void* adtFortranShapeSpec_create(void* pExprObj, void* pExpr2Obj);
C_FUNCTION void* adtFortranDimensionStmt_create(void* pLblDefObj, void* pArrayDeclaratorListObj);
C_FUNCTION void* adtFortranArrayDeclaratorList_create(void* pArrayDeclaratorObj);
C_FUNCTION void* adtFortranArrayDeclarator_create(void* pNameObj, void* pShapeSpecListObj);
C_FUNCTION void* adtFortranParameterStmt_create(void* pLblDefObj, void* pNamedConstantDefListObj);
C_FUNCTION void* adtFortranNamedConstantDefList_create(void* pNamedConstantDefObj);
C_FUNCTION void* adtFortranNamedConstantDef_create(void* pNameObj, void* pExprObj);
C_FUNCTION void* adtFortranImplicitSpecList_create(void* pImplicitSpecObj);
C_FUNCTION void* adtFortranImplicitSpec_create(void* pTypeSpecObj, void* pImplObj);
C_FUNCTION void* adtFortranSectionSubscriptList_create(void* pSectionSubscriptObj);
C_FUNCTION void* adtFortranSectionSubscript_create(void* pExprObj, void* pSubscriptTripletObj);
C_FUNCTION void* adtFortranSubscriptTriplet_create(int nCase, void* pExprObj, void* pExpr2Obj, void* pExpr3Obj);
C_FUNCTION void* adtFortranPrimary_create(void* pNameObj, void* pSconObj, void* pIconObj, void* pRconObj, void* pExprObj, void* pExpr2Obj, void* pSectionSubscriptListObj, int nIsTrue, int nIsBracket);
C_FUNCTION void* adtFortranMultOperand_create(void* pPrimaryObj, void* pMultOperandObj);
C_FUNCTION void* adtFortranAddOperand_create(void* pMultOperandObj, void* pAddOperandObj, int nMultiply);
C_FUNCTION void* adtFortranLevel2Expr_create(void* pAddOperandObj, void* pLevel2ExprObj, int nSign, int nHasOp);
C_FUNCTION void* adtFortranLevel4Expr_create(void* pLevel2ExprObj, void* pRelOpObj, void* pLevel2Expr2Obj);
C_FUNCTION void* adtFortranAndOperand_create(void* pLevel4ExprObj, int nNot);
C_FUNCTION void* adtFortranOrOperand_create(void* pAndOperandObj, void* pOrOperandObj);
C_FUNCTION void* adtFortranEquivOperand_create(void* pOrOperandObj, void* pEquivOperandObj);
C_FUNCTION void* adtFortranExpr_create(void* pEquivOperandObj, void* pExprObj, int nIsEquivalent);
C_FUNCTION void* adtFortranSFExprList_create(void* pSFExprListObj, void* pExprObj, void* pExpr2Obj);
C_FUNCTION void* adtFortranAssignmentStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj, void* pSFExprListObj, void* pSectionSubscriptListObj);
C_FUNCTION void* adtFortranWhereStmt_create(void* pLblDefObj, void* pExprObj, void* pAssignmentStmtObj);
C_FUNCTION void* adtFortranWhereConstruct_create(void* pWhereConstructStmtObj, void* pWhereRangeObj);
C_FUNCTION void* adtFortranWhereRange_create(void* pWhereBodyConstructBlockObj, void* pElsewhereConstructObj, void* pMaskedElsewhereConstructObj, void* pEndWhereStmtObj);
C_FUNCTION void* adtFortranMaskedElsewhereConstruct_create(void* pMaskedElsewhereStmtObj, void* pWhereRangeObj);
C_FUNCTION void* adtFortranElsewhereConstruct_create(void* pElsewhereStmtObj, void* pElsewherePartObj);
C_FUNCTION void* adtFortranElsewherePart_create(void* pEndWhereStmtObj, void* pWhereBodyConstructBlockObj);
C_FUNCTION void* adtFortranWhereBodyConstructBlock_create(void* pWhereBodyConstructObj);
C_FUNCTION void* adtFortranWhereConstructStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj);
C_FUNCTION void* adtFortranWhereBodyConstruct_create(void* pAssignmentStmtObj, void* pWhereStmtObj, void* pWhereConstructObj);
C_FUNCTION void* adtFortranMaskedElsewhereStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj);
C_FUNCTION void* adtFortranElsewhereStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranEndWhereStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranIfConstruct_create(void* pIfThenStmtObj, void* pThenPartObj);
C_FUNCTION void* adtFortranThenPart_create(void* pEndIfStmtObj, void* pConditionalBodyObj, void* pElseIfConstructObj, void* pElseConstructObj);
C_FUNCTION void* adtFortranElseIfConstruct_create(void* pElseIfStmtObj, void* pThenPartObj);
C_FUNCTION void* adtFortranElseConstruct_create(void* pElseStmtObj, void* pElsePartObj);
C_FUNCTION void* adtFortranElsePart_create(void* pEndIfStmtObj, void* pConditionalBodyObj);
C_FUNCTION void* adtFortranConditionalBody_create(void* pExecutableConstructObj);
C_FUNCTION void* adtFortranIfThenStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj);
C_FUNCTION void* adtFortranElseIfStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj);
C_FUNCTION void* adtFortranElseStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranEndIfStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranIfStmt_create(void* pLblDefObj, void* pExprObj, void* pActionStmtObj);
C_FUNCTION void* adtFortranCaseConstruct_create(void* pSelectCaseStmtObj, void* pSelectCaseBodyObj, void* pEndSelectStmtObj);
C_FUNCTION void* adtFortranSelectCaseBody_create(void* pCaseStmtObj, void* pSelectCaseBodyObj, void* pCaseBodyConstructObj);
C_FUNCTION void* adtFortranCaseBodyConstruct_create(void* pCaseStmtObj, void* pExecutableConstructObj);
C_FUNCTION void* adtFortranSelectCaseStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj);
C_FUNCTION void* adtFortranCaseStmt_create(void* pLblDefObj, void* pCaseSelectorObj, void* pNameObj);
C_FUNCTION void* adtFortranEndSelectStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranCaseSelector_create(void* pCaseValueRangeListObj);
C_FUNCTION void* adtFortranCaseValueRangeList_create(void* pCaseValueRangeObj);
C_FUNCTION void* adtFortranCaseValueRange_create(void* pExprObj, void* pExpr2Obj, int nHasColon);
C_FUNCTION void* adtFortranDoConstruct_create(void* pLblDefObj, void* pLblRefObj, void* pLoopControlObj, void* pNameObj, void* pConditionalBodyObj, void* pEndDoStmtObj, int nHasComma);
C_FUNCTION void* adtFortranLoopControl_create(void* pNameObj, void* pExprObj, void* pExpr2Obj, void* pExpr3Obj);
C_FUNCTION void* adtFortranEndDoStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranCycleStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranExitStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranGotoStmt_create(void* pLblDefObj, void* pLblRefObj);
C_FUNCTION void* adtFortranArithmeticIfStmt_create(void* pLblDefObj, void* pExprObj, void* pLblRefObj, void* pLblRef2Obj, void* pLblRef3Obj);
C_FUNCTION void* adtFortranContinueStmt_create(void* pLblDefObj);
C_FUNCTION void* adtFortranModuleStmt_create(void* pLblDefObj, void* pModuleNameObj);
C_FUNCTION void* adtFortranEndModuleStmt_create(void* pLblDefObj, void* pModuleNameObj);
C_FUNCTION void* adtFortranUseStmt_create(void* pLblDefObj, void* pNameObj);
C_FUNCTION void* adtFortranIntentStmt_create(void* pLblDefObj, void* pIntentSpecObj, void* pNameListObj, int nHasColonColon);
C_FUNCTION void* adtFortranIntentSpec_create(int nIntentSpec);
C_FUNCTION void* adtFortranIntrinsicStmt_create(void* pLblDefObj, void* pNameListObj);
C_FUNCTION void* adtFortranExternalStmt_create(void* pLblDefObj, void* pNameListObj, int nHasColon);
C_FUNCTION void* adtFortranCallStmt_create(void* pLblDefObj, void* pNameObj, void* pSectionSubscriptListObj);
C_FUNCTION void* adtFortranFunctionStmt_create(void* pLblDefObj, void* pTypeSpecObj, void* pFunctionNameObj, void* pParameterListObj, int nEmptyParameterList, int nRecursive, void* pResultNameObj);
C_FUNCTION void* adtFortranLblRef_create(const char* pIcon);
C_FUNCTION void* adtFortranName_create(const char* pIdent);
C_FUNCTION void* adtFortranNameList_create(void* pNameObj);
C_FUNCTION void* adtFortranEndFunctionStmt_create(void* pLblDefObj, void* pFunctionNameObj);
C_FUNCTION void* adtFortranSubroutineStmt_create(void* pLblDefObj, void* pSubroutineNameObj, void* pParameterListObj, int nEmptyParameterList, int nRecursive);
C_FUNCTION void* adtFortranEndSubroutineStmt_create(void* pLblDefObj, void* pSubroutineNameObj);
C_FUNCTION void* adtFortranReturnStmt_create(void* pLblDefObj, void* pExprObj);
C_FUNCTION void* adtFortranLblDef_create(void* pIconObj, const char* pComment);
C_FUNCTION void* adtFortranImplicitStmt_create(void* pLblDefObj, void* pImplicitSpecListObj);
C_FUNCTION void* adtFortranIcon_create(const char* pIcon);
C_FUNCTION void* adtFortranRcon_create(const char* pRcon);
C_FUNCTION void* adtFortranScon_create(const char* pScon);
C_FUNCTION void* adtFortranImpl_create(const char* pImpl);


#ifdef __cplusplus


#include "adtparser.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtFortranDeclarations;
class AdtFortranExecutableProgram;
class AdtFortranProgramUnit;
class AdtFortranCallExpand;
class AdtFortranProgramConstruct;
class AdtFortranTypeDeclarationStmtList;
class AdtFortranFunctionSubprogram;
class AdtFortranFunctionStmt;
class AdtFortranEndFunctionStmt;
class AdtFortranSubroutineSubprogram;
class AdtFortranSubroutineStmt;
class AdtFortranEndSubroutineStmt;
class AdtFortranBody;
class AdtFortranBodyConstruct;
class AdtFortranExecutableConstruct;
class AdtFortranCaseConstruct;
class AdtFortranDoConstruct;
class AdtFortranIfConstruct;
class AdtFortranWhereConstruct;
class AdtFortranEndDoStmt;
class AdtFortranArithmeticIfStmt;
class AdtFortranAssignmentStmt;
class AdtFortranCallStmt;
class AdtFortranContinueStmt;
class AdtFortranCycleStmt;
class AdtFortranExitStmt;
class AdtFortranGotoStmt;
class AdtFortranIfStmt;
class AdtFortranReturnStmt;
class AdtFortranWhereStmt;
class AdtFortranActionStmt;
class AdtFortranSectionSubscriptList;
class AdtFortranSectionSubscript;
class AdtFortranSubscriptTriplet;
class AdtFortranWhereConstructStmt;
class AdtFortranWhereRange;
class AdtFortranWhereBodyConstructBlock;
class AdtFortranElsewhereConstruct;
class AdtFortranMaskedElsewhereConstruct;
class AdtFortranEndWhereStmt;
class AdtFortranMaskedElsewhereStmt;
class AdtFortranElsewhereStmt;
class AdtFortranElsewherePart;
class AdtFortranIfThenStmt;
class AdtFortranThenPart;
class AdtFortranEndIfStmt;
class AdtFortranConditionalBody;
class AdtFortranElseIfConstruct;
class AdtFortranElseConstruct;
class AdtFortranElseIfStmt;
class AdtFortranElseStmt;
class AdtFortranElsePart;
class AdtFortranModule;
class AdtFortranModuleStmt;
class AdtFortranModuleBody;
class AdtFortranModuleBodyContent;
class AdtFortranEndModuleStmt;
class AdtFortranSpecificationPartConstruct;
class AdtFortranUseStmt;
class AdtFortranImplicitStmt;
class AdtFortranParameterStmt;
class AdtFortranTypeDeclarationStmt;
class AdtFortranDimensionStmt;
class AdtFortranIntentStmt;
class AdtFortranIntentSpec;
class AdtFortranIntrinsicStmt;
class AdtFortranExternalStmt;
class AdtFortranImplicitSpecList;
class AdtFortranImplicitSpec;
class AdtFortranImpl;
class AdtFortranNamedConstantDefList;
class AdtFortranNamedConstantDef;
class AdtFortranExpr;
class AdtFortranLblDef;
class AdtFortranTypeSpec;
class AdtFortranName;
class AdtFortranIcon;
class AdtFortranRcon;
class AdtFortranScon;
class AdtFortranNameList;
class AdtFortranAttrSpecSeq;
class AdtFortranEntityDeclList;
class AdtFortranEntityDecl;
class AdtFortranCharLength;
class AdtFortranShapeSpecList;
class AdtFortranInvalidEntityDecl;
class AdtFortranArrayDeclaratorList;
class AdtFortranEquivOperand;
class AdtFortranSelectCaseStmt;
class AdtFortranSelectCaseBody;
class AdtFortranEndSelectStmt;
class AdtFortranCaseStmt;
class AdtFortranCaseBodyConstruct;
class AdtFortranCaseSelector;
class AdtFortranCaseValueRangeList;
class AdtFortranCaseValueRange;
class AdtFortranLoopControl;
class AdtFortranLblRef;


//  ----------------------------------------------------------------------------
//  AdtFortranDestCodeType enum
//  ----------------------------------------------------------------------------
//  This enumeration is a means of making the translation into different dest
//  languages more abstract without having to encompass it in a class of its own
//  ----------------------------------------------------------------------------
enum AdtFortranDestCodeType
{
  AdtFortranDestCodeCPP,
  AdtFortranDestCodeDelphi,
  AdtFortranDestCodeFortran
};

//  ----------------------------------------------------------------------------

enum AdtFortranOp
{
  ForOp_LOGICAL_EQ = 0,
  ForOp_LOGICAL_NE = 1,
  ForOp_LOGICAL_LT = 2,
  ForOp_LOGICAL_LE = 3,
  ForOp_LOGICAL_GT = 4,
  ForOp_LOGICAL_GE = 5,
  ForOp_EQUAL      = 6,
  ForOp_NEQUAL     = 7,
  ForOp_LT         = 8,
  ForOp_LE         = 9,
  ForOp_GT         = 10,
  ForOp_GE         = 11,
};

//  ----------------------------------------------------------------------------

enum AdtFortranType
{
  ForType_INTEGER           = 0,
  ForType_REAL              = 1,
  ForType_DOUBLE_PRECISION  = 2,
  ForType_COMPLEX           = 3,
  ForType_DOUBLE_COMPLEX    = 4,
  ForType_LOGICAL           = 5,
  ForType_CHARACTER         = 6,
  ForType_UNSIGNED          = 7,
  ForType_BOUNDSCHECK       = 8,
  ForType_UNKNOWNTYPE       = 9,
};

//  ----------------------------------------------------------------------------

enum AdtFortranAttr
{
  ForAttr_PARAMETER = 0,
  ForAttr_PUBLIC    = 1,
  ForAttr_PROTECTED = 2,
  ForAttr_PRIVATE   = 3,
  ForAttr_INTRINSIC = 4,
  ForAttr_EXTERNAL  = 5,
  ForAttr_DIMENSION = 6,
  ForAttr_INTENT    = 7,
};

//  ----------------------------------------------------------------------------

enum AdtFortranIntent
{
  ForIntent_IN      = 0,
  ForIntent_OUT     = 1,
  ForIntent_INOUT   = 2,
  ForIntent_IN_OUT  = 3,
};


//  ----------------------------------------------------------------------------
//  class AdtFortranVariableInfo
//  ----------------------------------------------------------------------------
//  The purpose of this class is to collate information about variable
//  declarations visible within any portion of code. Specifically, the variable
//  names, their dimension and type.
//  ----------------------------------------------------------------------------
class AdtFortranVariableInfo
{
private:
  AdtStringByStringMap    VariableInfoMap;

private:
  void                    extractTypeDefInfo(const AdtFortranTypeDeclarationStmt* pTypeDecl);
  void                    extractTypeDeclarations(const AdtParserPtrByStringMap& rTypeDeclMap);
  void                    initialise(AdtParser* pCodeObj);
  void                    initialise(const AdtFortranDeclarations* pDeclarations);

public:
  AdtFortranVariableInfo(AdtParser* pCodeObj = 0);
  AdtFortranVariableInfo(const AdtFortranDeclarations* pDeclarations);
  AdtFortranVariableInfo(const AdtFortranVariableInfo& rCopy);
  virtual ~AdtFortranVariableInfo();

  bool                    hasVariable(const char* pVarName) const;
  bool                    variableType(const char* pVarName, string& rRetType) const;
  bool                    lowerDimension(const char* pVarName, int nDimension, string& rRetDim) const;
  bool                    upperDimension(const char* pVarName, int nDimension, string& rRetDim) const;
  int                     numberOfDimensions(const char* pVarName) const;
  void                    dump() const;
};


//  ----------------------------------------------------------------------------
//  class AdtFortranSliceLoopVar
//  ----------------------------------------------------------------------------
//  This class is used to collate info pertaining to expanded slice loop
//  variables that are created during the slice fixup process.
//  ----------------------------------------------------------------------------
class AdtFortranSliceLoopVar
{
protected:
  string          Name;
  string          LowerDim;
  string          UpperDim;

public:
  AdtFortranSliceLoopVar();
  AdtFortranSliceLoopVar(const AdtFortranSliceLoopVar& rCopy);
  virtual ~AdtFortranSliceLoopVar();

  bool            initialise(const char* pName,
                             const char* pLowerDim,
                             const char* pUpperDim);

  const string&   name() const;
  const string&   lowerDim() const;
  const string&   upperDim() const;
};

//  ----------------------------------------------------------------------------

inline const string& AdtFortranSliceLoopVar::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline const string& AdtFortranSliceLoopVar::lowerDim() const
{
  return (LowerDim);
}

//  ----------------------------------------------------------------------------

inline const string& AdtFortranSliceLoopVar::upperDim() const
{
  return (UpperDim);
}


//  ----------------------------------------------------------------------------
//  class AdtFortranSliceLoopVars
//  ----------------------------------------------------------------------------
//  This class is is a container for AdtFortranSliceLoopVar instances, one per
//  slice indice in the slice fixup process.
//  ----------------------------------------------------------------------------
class AdtFortranSliceLoopVars
{
protected:
  AdtFortranSliceLoopVar*         SliceLoopVars;
  int                             NumberOfIndices;

public:
  AdtFortranSliceLoopVars(int nNumberOfIndices);
  AdtFortranSliceLoopVars(const AdtFortranSliceLoopVars& rCopy);
  virtual ~AdtFortranSliceLoopVars();

  bool                            initialise(int nIndex,
                                             const char* pName,
                                             const char* pLowerDim,
                                             const char* pUpperDim);

  AdtFortranSectionSubscriptList* createSectionSubscriptList(const AdtFortranVariableInfo& rVarInfo,
                                                             const char* pParentName = 0,
                                                             AdtFortranSectionSubscriptList* pParentSubscriptList = 0) const;

  const AdtFortranSliceLoopVar&   sliceLoopVar(int nIndex) const;
  int                             numberOfIndices() const;
};

//  ----------------------------------------------------------------------------

inline const AdtFortranSliceLoopVar& AdtFortranSliceLoopVars::sliceLoopVar(int nIndex) const
{
  return (SliceLoopVars[nIndex]);
}

//  ----------------------------------------------------------------------------

inline int AdtFortranSliceLoopVars::numberOfIndices() const
{
  return (NumberOfIndices);
}


//  ----------------------------------------------------------------------------
//  class AdtFortranDeclarations
//  ----------------------------------------------------------------------------
//  The purpose of this class is to collate and organise type declarations that
//  are defined within a code block and function argument lists.
//  ----------------------------------------------------------------------------
class AdtFortranDeclarations : public UtlReferenceCount
{
private:
  AdtIntByStringMap                     VariablesMap;
  AdtParserPtrByStringMap               TypeDeclarationMap;
  AdtParserPtrByStringMap               ParameterTypeDeclarationMap;
  AdtParserPtrByStringMap               FunctionTypeDeclarationMap;
  AdtParserPtrList                      ParameterList;
  AdtParserPtrList                      ParameterStmtList;
  AdtParserPtrList                      DimensionStmtList;

protected:
  void                                  flush(AdtParserPtrByStringMap& rMap);

  void                                  extractModuleTypeDeclarations(AdtParser* pBodyObj,
                                                                      AdtParserPtrByStringMap& rMap);

  void                                  addVariableNames(AdtIntByStringMap& rVariablesMap,
                                                         const AdtParserPtrByStringMap& rObjsMap) const;

  bool                                  extractDeclarations(AdtParser* pParentObj,
                                                            AdtParser* pBodyObj,
                                                            AdtParser* pParameterListObj,
                                                            AdtParserPtrByStringMap* pFunctionMap = 0);

public:
  AdtFortranDeclarations(AdtParser* pParentObj,
                         AdtParser* pBodyObj,
                         AdtParser* pParameterListObj,
                         AdtParserPtrByStringMap* pFunctionMap = 0);

  AdtFortranDeclarations(const AdtFortranDeclarations& rCopy);
  virtual ~AdtFortranDeclarations();

  void                                  dump(AdtFile* pFile) const;

  bool                                  isLocal(const char* pVarName) const;
  bool                                  remove(const char* pVarName);

  void                                  removeOutputVarPrefix(AdtParser* pParentObj, const char* pClassName);

  void                                  checkIsVariable(AdtParser* pRootObj, AdtFile* pFile = 0) const;

  const AdtParserPtrByStringMap&        typeDeclarationMap() const;
  const AdtParserPtrByStringMap&        parameterTypeDeclarationMap() const;
  const AdtParserPtrByStringMap&        functionTypeDeclarationMap() const;
  const AdtParserPtrList&               parameterList() const;
  const AdtParserPtrList&               parameterStmtList() const;
  const AdtParserPtrList&               dimensionStmtList() const;

  AdtFile&                              writeGenericSeperator(AdtFile& pOutFile, AdtFortranDestCodeType nType) const;
  AdtFile&                              writeGenericParameterList(AdtFile& pOutFile, AdtFortranDestCodeType nType) const;
  AdtFile&                              writeGenericInitialisations(AdtFile& pOutFile, AdtFortranDestCodeType nType) const;
  AdtFile&                              writeGenericReturnType(AdtFile& pOutFile, const char* pFunctionName, AdtFortranDestCodeType nType) const;

  AdtFile&                              writeCPP_ParameterList(AdtFile& pOutFile) const;
  AdtFile&                              writeCPP_Declarations(AdtFile& pOutFile) const;
  AdtFile&                              writeCPP_Initialisations(AdtFile& pOutFile) const;
  AdtFile&                              writeCPP_Allocations(AdtFile& pOutFile) const;
  AdtFile&                              writeCPP_Deallocations(AdtFile& pOutFile) const;
  AdtFile&                              writeCPP_ReturnType(AdtFile& pOutFile, const char* pFunctionName) const;

  AdtFile&                              writeDelphiParameterList(AdtFile& pOutFile) const;
  AdtFile&                              writeDelphiDeclarations(AdtFile& pOutFile) const;
  AdtFile&                              writeDelphiInitialisations(AdtFile& pOutFile) const;

  AdtFile&                              writeDelphiAllocations(AdtFile& pOutFile,
                                                               AdtStringList* pVarList,
                                                               AdtStringList* pDestroyList) const;

  AdtFile&                              writeDelphiDeallocations(AdtFile& pOutFile) const;
  AdtFile&                              writeDelphiReturnType(AdtFile& pOutFile, const char* pFunctionName) const;
};

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtFortranDeclarations::typeDeclarationMap() const
{
  return (TypeDeclarationMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtFortranDeclarations::parameterTypeDeclarationMap() const
{
  return (ParameterTypeDeclarationMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtFortranDeclarations::functionTypeDeclarationMap() const
{
  return (FunctionTypeDeclarationMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrList& AdtFortranDeclarations::parameterList() const
{
  return (ParameterList);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrList& AdtFortranDeclarations::parameterStmtList() const
{
  return (ParameterStmtList);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrList& AdtFortranDeclarations::dimensionStmtList() const
{
  return (DimensionStmtList);
}


//  ----------------------------------------------------------------------------
//  These class definitions map 1:1 to the grammar rules for the parser
//  ----------------------------------------------------------------------------
class AdtFortranBase : public AdtParser
{
protected:
  static AdtFortranExecutableProgram*   FortranRootObject;
  static const char*                    RemovePrefixString;
  static const char*                    AddPrefixString;

protected:
  AdtFile&                              forAllWriteGeneric(AdtFile& pOutFile, AdtFortranDestCodeType nDestCodeType, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                              forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                              forAllWriteDelphi(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                              forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false) const;

public:
  AdtFortranBase();
  AdtFortranBase(const AdtFortranBase& rCopy);
  virtual ~AdtFortranBase();

  // This parameter is used to control push and pop processing. With PushPopDisable true
  // push and pop ops are dropped. With it false they are translated into array ops
  static bool                           PushPopDisable;
  static bool                           WithStackSubstitution;

  static void                           setChangePrefix(const char* pRemovePrefixString, const char* pAddPrefixString);
  static AdtFile&                       writeWithChangedPrefix(AdtFile& pOutFile, const char* pString, bool bSupressNew);

  static void                           initialise();
  static void                           fortranRootObject(AdtParser* pRoot);
  static AdtFortranExecutableProgram*   fortranRootObject();

  static void                           splitNumericConstant(string& rNumber, string& rSize, const char* pNumericConstant);

  static AdtFortranExpr*                createSimpleExpression(const char* pIdent);
  static AdtFortranTypeDeclarationStmt* createSimpleTypeDeclarationStmt(const char* pVarName,
                                                                        AdtFortranType nType,
                                                                        AdtFortranExpr* pExprObj = 0);

  static void                           createDefaultSubscripts(AdtParserPtrList& rResultSubscriptList,
                                                                const AdtFortranVariableInfo& rVariableInfo,
                                                                const char* pName);

  static void                           makeImplicitSubscriptExplicit(AdtFortranSectionSubscript* pSubscript,
                                                                      const AdtFortranVariableInfo& rVariableInfo,
                                                                      const char* pName,
                                                                      int nIndex);

  static AdtFortranExecutableConstruct* createDoConstruct(const char* pLoopVarName,
                                                          const char* pLabel,
                                                          AdtParser* pExecutableConstruct,
                                                          AdtFortranExpr* pStartExpr,
                                                          AdtFortranExpr* pEndExpr,
                                                          AdtFortranExpr* pStepExpr = 0);

  bool                                  nameToNameAndClass(string& rName, string& rClassName) const;

  AdtFile&                              writeGeneric(AdtFile& pOutFile, AdtFortranDestCodeType nDestCodeType, int nMode = 0) const;
  virtual AdtFile&                      writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                      writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
{
  return (forAllWriteGeneric(pOutFile, AdtFortranDestCodeCPP, nMode, pDelimiter, bNewline, bExcludeLast, pSuffix));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::forAllWriteDelphi(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
{
  return (forAllWriteGeneric(pOutFile, AdtFortranDestCodeDelphi, nMode, pDelimiter, bNewline, bExcludeLast, pSuffix));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast) const
{
  return (forAllWriteGeneric(pOutFile, AdtFortranDestCodeFortran, nMode, pDelimiter, bNewline, bExcludeLast, 0));
}

//  ----------------------------------------------------------------------------

inline AdtFortranBase::AdtFortranBase(const AdtFortranBase& rCopy)
 : AdtParser(rCopy)
{

}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtFortranBase::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}


//  ----------------------------------------------------------------------------
//  AdtFortranExecutableProgram class
//  ----------------------------------------------------------------------------
//  This is the root object that is a list of program units.
//  ----------------------------------------------------------------------------
class AdtFortranExecutableProgram : public AdtFortranBase, public AdtSourceRoot
{
private:
  enum PushPopCallType {PushArrayCall = 0,
                        PopArrayCall  = 1,
                        PushCall      = 2,
                        LookCall      = 3,
                        PopCall       = 4};

  enum PushPopVarType {CharacterVarType  = 0,
                       BooleanVarType    = 1,
                       Integer4VarType   = 2,
                       Integer8VarType   = 3,
                       Real4VarType      = 4,
                       Real8VarType      = 5,
                       Real16VarType     = 6};

  struct PushPopCall
  {
    const char*     CallName;
    PushPopCallType CallType;
    PushPopVarType  VarType;
    int             ArgsExpected;
    const char*     BaseStackName;
    const char*     VarTypeName;
  };

  static const PushPopCall      PushPopCalls[55];

protected:
  void                          createStackVarNames(string& rStackName,
                                                    string& rIndexName,
                                                    const string& rBaseStackName,
                                                    int nIteration,
                                                    int nFnNumber);

  void                          createLocalVar(const char* pVarName,
                                               AdtFortranType nVarType,
                                               AdtParser* pObjToAddTo,
                                               AdtStringByStringMap& rNewLocalsMap,
                                               const AdtFortranVariableInfo& rVariableInfo);

  void                          baseStackName(string& rBaseStackName,
                                              const char* pArrayName);

  bool                          translatePushPopArrayCall(AdtFortranCallStmt* pCallObj,
                                                          const PushPopCall& rPushPopCallInfo,
                                                          AdtFortranModuleBody* pModuleBody,
                                                          int nIteration,
                                                          int nFnNumber,
                                                          AdtStringByStringMap& rNewLocalsMap,
                                                          const AdtFortranVariableInfo& rVariableInfo);

  bool                          removePushPopCall(AdtFortranCallStmt* pCallObj,
                                                  const PushPopCall& rPushPopCallInfo,
                                                  AdtFortranModuleBody* pModuleBody,
                                                  int nIteration,
                                                  int nFnNumber,
                                                  AdtStringList& rNewAttributeList,
                                                  AdtStringByStringMap& rNewAttributeMap,
                                                  AdtStringByStringMap& rNewLocalsMap,
                                                  const AdtFortranVariableInfo& rVariableInfo);

  void                          enumerateLinkages(const char* pFunctionName,
                                                  const AdtParserPtrByStringMap& rFunctionMap,
                                                  AdtStringByStringMap& rFunctionLinkagesMap) const;

  void                          enumerateSubroutineOrFunctionNames(AdtStringByStringMap& rRegardAsClassObjMap,
                                                                   bool bSubroutines,
                                                                   const char* pClassPrefix) const;

  static AdtFortranBase*        expressionBuildInner(const char* pCodeString,
                                                     AdtParser* pStmtObj,
                                                     AdtParser*& pObjectToReplace,
                                                     AdtParser*& pObjectContainer,
                                                     AdtParser*& pReplacementContainer);

  void                          addBoundsChecking(AdtParser* pFuncOrSubObj,
                                                  const AdtFortranVariableInfo& rVariableInfo);

public:
  AdtFortranExecutableProgram(AdtParser* pProgramUnitObj);
  AdtFortranExecutableProgram(const AdtFortranExecutableProgram& rCopy);
  virtual ~AdtFortranExecutableProgram();

  void                          initialise();

  static AdtFortranBase*        expressionBuild(const char* pCodeString,
                                                bool bIncludeConditionalContext);

  static AdtFortranBase*        expressionBuildAndReplace(const char* pCodeString,
                                                          AdtParser* pStmtObj,
                                                          AdtParserPtrList* pAddedList = 0);

  static AdtFortranBase*        expressionBuildAndInsert(const char* pCodeString,
                                                         AdtParser* pStmtObj,
                                                         bool bInsertAfter,
                                                         AdtParserPtrList* pAddedList = 0);

  void                          addStackFixups(const AdtStringByStringMap& rNewMethodMap);
  void                          addSliceFixups(const AdtStringByStringMap& rNewMethodMap,
                                               AdtStringList& rNewMethodList,
                                               const AdtStringList& rBoundsCheckList,
                                               const AdtStringList& rGlobalBoundsCheckList,
                                               const char* pClassPrefix,
                                               AdtFile* pFile = 0);

  void                          boundsCheck(const AdtStringList& rBoundsCheckList);

  void                          enumerateFunctionNames(AdtStringByStringMap& rRegardAsClassFunctionsMap,
                                                       const char* pClassPrefix);

  void                          enumerateSubroutineNames(AdtStringByStringMap& rRegardAsClassSubroutinesMap,
                                                         const char* pClassPrefix);

  bool                          mergeWith(AdtFortranExecutableProgram* pSource,
                                          AdtFortranExecutableProgram* pCallExpandRoot,
                                          AdtStringList* pNewFunctionsList,
                                          int nIteration,
                                          AdtStringList& rNewMethodList,
                                          AdtStringByStringMap& rNewMethodMap,
                                          AdtStringList& rNewAttributeList,
                                          AdtStringByStringMap& rNewAttributeMap,
                                          const char* pParentClassName,
                                          const char* pModuleSuffix,
                                          AdtStringList* pNewLocalsList = 0,
                                          AdtStringByStringMap* pNewLocalsMap = 0);

  void                          writeCPP_ClassHeader(AdtFile& pOutFile,
                                                     const char* pParentIncludeName,
                                                     const AdtStringList& rMethodList,
                                                     const AdtStringList& rAttributeList,
                                                     const char* pClassName,
                                                     const char* pParentClassName,
                                                     AdtStringList& rCPP_ConstructorList,
                                                     string& sPreText,
                                                     string& sPostText) const;

  void                          writeCPP_ClassImplementation(AdtFile& pOutFile,
                                                             const char* pIncludeName,
                                                             const AdtStringList& rMethodList,
                                                             const AdtStringList& rAttributeList,
                                                             const char* pClassName,
                                                             const char* pParentClassName,
                                                             AdtStringList& rCPP_ConstructorList,
                                                             AdtStringList* pVarSuffixList,
                                                             string& sPreText,
                                                             string& sPostText) const;

  void                          writeDelphiClass(AdtFile& pOutFile,
                                                 const AdtStringList& rMethodList,
                                                 const AdtStringList& rAttributeList,
                                                 const char* pClassName,
                                                 const char* pParentClassName,
                                                 AdtStringList& rDelphiConstructorList,
                                                 const char* pUsesList,
                                                 AdtStringList* pVarSuffixList) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  virtual void                  enumerateMethodNames(AdtStringList& rMethodList) const;

  virtual bool                  hasClass(const char* pClassName,
                                         string& rParentClassName) const;

  virtual bool                  buildBlackBoxFile(const char* pBlackBoxFileName,
                                                  AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                  AdtStringByStringMap& rRegardAsClassSubroutineMap);

  virtual bool                  flattenClass(const char* pClassName,
                                             const AdtParserPtrList& rRootList,
                                             string& rUsesList);

  virtual bool                  optimise(const AdtStringList& rNewMethodList,
                                         const AdtStringByStringMap& rNewMethodMap);

  virtual bool                  expandMacros();

  virtual bool                  extractClassConstructors(AdtStringList& rConstructorList,
                                                         const char* pClassName,
                                                         const char* pParentClassName,
                                                         AdtSourceFileType nAsFileType) const;

  virtual AdtFile&              writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                           const AdtFortranExecutableProgram* pSavedRoot,
                                                           const char* pClassName,
                                                           const char* pParentClassName,
                                                           bool bExpandMacros) const;

  virtual AdtFile&              writeNative(AdtFile& rOutFile) const;

  virtual AdtSourceFileType     sourceFileType() const;

  declListType(AdtFortranProgramUnit);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranProgramUnit class
//  ----------------------------------------------------------------------------
class AdtFortranProgramUnit : public AdtFortranBase
{
private:
  AdtFortranFunctionSubprogram*   FunctionSubprogram;
  AdtFortranSubroutineSubprogram* SubroutineSubprogram;
  AdtFortranModule*               Module;
  AdtFortranCallExpand*           CallExpand;
  AdtFortranProgramConstruct*     ProgramConstruct;

public:
  AdtFortranProgramUnit(AdtParser* pFunctionSubprogramObj,
                        AdtParser* pSubroutineSubprogramObj,
                        AdtParser* pModuleObj,
                        AdtParser* pCallExpandObj,
                        AdtParser* pProgramConstructObj);

  AdtFortranProgramUnit(const AdtFortranProgramUnit& rCopy);
  virtual ~AdtFortranProgramUnit();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCallExpand class
//  ----------------------------------------------------------------------------
class AdtFortranCallExpand : public AdtFortranBase
{
private:
  AdtFortranName*                     Name;
  AdtFortranNameList*                 NameList;
  AdtFortranConditionalBody*          ConditionalBody;
  AdtFortranTypeDeclarationStmtList*  TypeDeclarationStmtList;
  bool                                HasBrackets;

protected:
  AdtFortranExpr*               createExpression(AdtFortranName* pNameObj) const;

public:
  AdtFortranCallExpand(AdtParser* pNameObj,
                       AdtParser* pNameListObj,
                       AdtParser* pConditionalBodyObj,
                       AdtParser* pTypeDeclarationStmtListObj,
                       bool bHasBrackets);

  AdtFortranCallExpand(const AdtFortranCallExpand& rCopy);
  virtual ~AdtFortranCallExpand();

  bool                          expand(AdtFortranCallStmt* pCallStmt,
                                       AdtFortranModuleBody* pModuleBody,
                                       int nIteration,
                                       int nFnNumber,
                                       AdtStringList& rNewAttributeList) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranProgramConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranProgramConstruct : public AdtFortranBase
{
private:
  AdtFortranLblDef*                   LblDef;
  AdtFortranName*                     Name;
  AdtFortranBody*                     Body;
  AdtFortranLblDef*                   EndLblDef;

public:
  AdtFortranProgramConstruct(AdtParser* pLblDefObj,
                             AdtParser* pNameObj,
                             AdtParser* pBodyObj,
                             AdtParser* pEndLblDefObj);

  AdtFortranProgramConstruct(const AdtFortranProgramConstruct& rCopy);
  virtual ~AdtFortranProgramConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranTypeDeclarationStmtList class
//  ----------------------------------------------------------------------------
class AdtFortranTypeDeclarationStmtList : public AdtFortranBase
{
public:
  AdtFortranTypeDeclarationStmtList(AdtParser* pTypeDeclarationStmtObj);
  AdtFortranTypeDeclarationStmtList(const AdtFortranTypeDeclarationStmtList& rCopy);
  virtual ~AdtFortranTypeDeclarationStmtList();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranTypeDeclarationStmt);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranBody class
//  ----------------------------------------------------------------------------
class AdtFortranBody : public AdtFortranBase
{
public:
  AdtFortranBody(AdtParser* pBodyConstructObj);
  AdtFortranBody(const AdtFortranBody& rCopy);
  virtual ~AdtFortranBody();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  void                            addTypeDeclarationStmt(AdtFortranTypeDeclarationStmt* pObj);

  declListType(AdtFortranBodyConstruct);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranBodyConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranBodyConstruct : public AdtFortranBase
{
private:
  AdtFortranSpecificationPartConstruct* SpecificationPartConstruct;
  AdtFortranExecutableConstruct*        ExecutableConstruct;

public:
  AdtFortranBodyConstruct(AdtParser* pSpecificationPartConstructObj,
                          AdtParser* pExecutableConstructObj);

  AdtFortranBodyConstruct(const AdtFortranBodyConstruct& rCopy);
  virtual ~AdtFortranBodyConstruct();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranFunctionSubprogram class
//  ----------------------------------------------------------------------------
class AdtFortranFunctionSubprogram : public AdtFortranBase
{
private:
  AdtFortranFunctionStmt*       FunctionStmt;
  AdtFortranEndFunctionStmt*    EndFunctionStmt;
  AdtFortranBody*               Body;

public:
  AdtFortranFunctionSubprogram(AdtParser* pFunctionStmtObj,
                               AdtParser* pEndFunctionStmtObj,
                               AdtParser* pBodyObj);

  AdtFortranFunctionSubprogram(const AdtFortranFunctionSubprogram& rCopy);
  virtual ~AdtFortranFunctionSubprogram();

  void                          replaceFunctionVarWithResult();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSubroutineSubprogram class
//  ----------------------------------------------------------------------------
class AdtFortranSubroutineSubprogram : public AdtFortranBase
{
private:
  AdtFortranSubroutineStmt*       SubroutineStmt;
  AdtFortranEndSubroutineStmt*    EndSubroutineStmt;
  AdtFortranBody*                 Body;

public:
  AdtFortranSubroutineSubprogram(AdtParser* pSubroutineStmtObj,
                                 AdtParser* pEndSubroutineStmtObj,
                                 AdtParser* pBodyObj);

  AdtFortranSubroutineSubprogram(const AdtFortranSubroutineSubprogram& rCopy);
  virtual ~AdtFortranSubroutineSubprogram();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranModule class
//  ----------------------------------------------------------------------------
class AdtFortranModule : public AdtFortranBase
{
private:
  AdtFortranModuleStmt*     ModuleStmt;
  AdtFortranModuleBody*     ModuleBody;
  AdtFortranEndModuleStmt*  EndModuleStmt;

public:
  AdtFortranModule(AdtParser* pModuleStmtObj,
                   AdtParser* pModuleBodyObj,
                   AdtParser* pEndModuleStmtObj);

  AdtFortranModule(const AdtFortranModule& rCopy);
  virtual ~AdtFortranModule();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranModuleBody class
//  ----------------------------------------------------------------------------
class AdtFortranModuleBody : public AdtFortranBase
{
public:
  AdtFortranModuleBody();
  AdtFortranModuleBody(AdtParser* pModuleBodyContentObj);
  AdtFortranModuleBody(const AdtFortranModuleBody& rCopy);
  virtual ~AdtFortranModuleBody();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranModuleBodyContent);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranModuleBodyContent class
//  ----------------------------------------------------------------------------
class AdtFortranModuleBodyContent : public AdtFortranBase
{
private:
  AdtFortranSpecificationPartConstruct* SpecificationPartConstruct;
  AdtFortranFunctionSubprogram*         FunctionSubprogram;
  AdtFortranSubroutineSubprogram*       SubroutineSubprogram;

public:
  AdtFortranModuleBodyContent(AdtParser* pSpecificationPartConstructObj,
                              AdtParser* pFunctionSubprogramObj,
                              AdtParser* pSubroutineSubprogramObj);

  AdtFortranModuleBodyContent(const AdtFortranModuleBodyContent& rCopy);
  virtual ~AdtFortranModuleBodyContent();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSpecificationPartConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranSpecificationPartConstruct : public AdtFortranBase
{
private:
  AdtFortranUseStmt*              UseStmt;
  AdtFortranImplicitStmt*         ImplicitStmt;
  AdtFortranParameterStmt*        ParameterStmt;
  AdtFortranTypeDeclarationStmt*  TypeDeclarationStmt;
  AdtFortranDimensionStmt*        DimensionStmt;
  AdtFortranIntrinsicStmt*        IntrinsicStmt;
  AdtFortranExternalStmt*         ExternalStmt;
  AdtFortranIntentStmt*           IntentStmt;

public:
  AdtFortranSpecificationPartConstruct(AdtParser* pUseStmtObj,
                                       AdtParser* pImplicitStmtObj,
                                       AdtParser* pParameterStmtObj,
                                       AdtParser* pTypeDeclarationStmtObj,
                                       AdtParser* pDimensionStmtObj,
                                       AdtParser* pIntrinsicStmtObj,
                                       AdtParser* pExternalStmtObj,
                                       AdtParser* pIntentStmtObj);

  AdtFortranSpecificationPartConstruct(const AdtFortranSpecificationPartConstruct& rCopy);
  virtual ~AdtFortranSpecificationPartConstruct();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranExecutableConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranExecutableConstruct : public AdtFortranBase
{
private:
  AdtFortranActionStmt*           ActionStmt;
  AdtFortranCaseConstruct*        CaseConstruct;
  AdtFortranDoConstruct*          DoConstruct;
  AdtFortranIfConstruct*          IfConstruct;
  AdtFortranWhereConstruct*       WhereConstruct;

public:
  AdtFortranExecutableConstruct(AdtParser* pActionStmtObj,
                                AdtParser* pCaseConstructObj,
                                AdtParser* pDoConstructObj,
                                AdtParser* pIfConstructObj,
                                AdtParser* pWhereConstructObj);

  AdtFortranExecutableConstruct(const AdtFortranExecutableConstruct& rCopy);
  virtual ~AdtFortranExecutableConstruct();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranActionStmt class
//  ----------------------------------------------------------------------------
class AdtFortranActionStmt : public AdtFortranBase
{
private:
  AdtFortranArithmeticIfStmt*     ArithmeticIfStmt;
  AdtFortranAssignmentStmt*       AssignmentStmt;
  AdtFortranCallStmt*             CallStmt;
  AdtFortranContinueStmt*         ContinueStmt;
  AdtFortranCycleStmt*            CycleStmt;
  AdtFortranExitStmt*             ExitStmt;
  AdtFortranIfStmt*               IfStmt;
  AdtFortranReturnStmt*           ReturnStmt;
  AdtFortranWhereStmt*            WhereStmt;
  AdtFortranGotoStmt*             GotoStmt;

public:
  AdtFortranActionStmt(AdtParser* pArithmeticIfStmtObj,
                       AdtParser* pAssignmentStmtObj,
                       AdtParser* pCallStmtObj,
                       AdtParser* pContinueStmtObj,
                       AdtParser* pCycleStmtObj,
                       AdtParser* pExitStmtObj,
                       AdtParser* pIfStmtObj,
                       AdtParser* pReturnStmtObj,
                       AdtParser* pWhereStmtObj,
                       AdtParser* pGotoStmtObj);

  AdtFortranActionStmt(const AdtFortranActionStmt& rCopy);
  virtual ~AdtFortranActionStmt();

  void                            makeCallStmt(AdtFortranCallStmt* pCallStmt);

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranRelOp class
//  ----------------------------------------------------------------------------
class AdtFortranRelOp : public AdtFortranBase
{
private:
  AdtFortranOp                  Op;

public:
  AdtFortranRelOp(AdtFortranOp nOp);
  AdtFortranRelOp(const AdtFortranRelOp& rCopy);
  virtual ~AdtFortranRelOp();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranTypeDeclarationStmt class
//  ----------------------------------------------------------------------------
class AdtFortranTypeDeclarationStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranTypeSpec*             TypeSpec;
  AdtFortranAttrSpecSeq*          AttrSpecSeq;
  AdtFortranEntityDeclList*       EntityDeclList;
  size_t                          Dimensions;
  bool                            IsConst;

public:
  AdtFortranTypeDeclarationStmt(AdtParser* pLblDefObj,
                                AdtParser* pTypeSpecObj,
                                AdtParser* pAttrSpecSeqObj,
                                AdtParser* pEntityDeclListObj);

  AdtFortranTypeDeclarationStmt(const AdtFortranTypeDeclarationStmt& rCopy);
  virtual ~AdtFortranTypeDeclarationStmt();

  void                            isConst(bool bIsConst);
  bool                            isConst() const;

  void                            removeExternals(const AdtParserPtrByStringMap& rExternalsMap);

  bool                            removeSharedNames(AdtParser* pDestModuleBody,
                                                    AdtStringList* pNewAttributeList,
                                                    AdtStringByStringMap* pNewAttributeMap);

  void                            splitAndEnumerate(AdtParser* pParentObj,
                                                    AdtParserPtrByStringMap& rMap) const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline void AdtFortranTypeDeclarationStmt::isConst(bool bIsConst)
{
  IsConst = bIsConst;
}

//  ----------------------------------------------------------------------------

inline bool AdtFortranTypeDeclarationStmt::isConst() const
{
  return (IsConst);
}


//  ----------------------------------------------------------------------------
//  AdtFortranAttrSpecSeq class
//  ----------------------------------------------------------------------------
class AdtFortranAttrSpecSeq : public AdtFortranBase
{
public:
  AdtFortranAttrSpecSeq(AdtParser* pAttrSpecObj);
  AdtFortranAttrSpecSeq(const AdtFortranAttrSpecSeq& rCopy);
  virtual ~AdtFortranAttrSpecSeq();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranAttrSpec);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranTypeSpec class
//  ----------------------------------------------------------------------------
class AdtFortranTypeSpec : public AdtFortranBase
{
private:
  AdtFortranType                Type;
  int                           ByteLength;

protected:
  void                          initialise();

public:
  AdtFortranTypeSpec(AdtFortranType nType, const char* pIcon);
  AdtFortranTypeSpec(const AdtFortranTypeSpec& rCopy);
  virtual ~AdtFortranTypeSpec();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  bool                          isUnknown() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtFortranTypeSpec::isUnknown() const
{
  return (Type == ForType_UNKNOWNTYPE);
}


//  ----------------------------------------------------------------------------
//  AdtFortranAttrSpec class
//  ----------------------------------------------------------------------------
class AdtFortranAttrSpec : public AdtFortranBase
{
private:
  AdtFortranShapeSpecList*      ShapeSpecList;
  AdtFortranIntentSpec*         IntentSpec;
  AdtFortranAttr                Attribute;

public:
  AdtFortranAttrSpec(AdtParser* pShapeSpecListObj,
                     AdtParser* pIntentSpecObj,
                     AdtFortranAttr nAttribute);

  AdtFortranAttrSpec(const AdtFortranAttrSpec& rCopy);
  virtual ~AdtFortranAttrSpec();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEntityDeclList class
//  ----------------------------------------------------------------------------
class AdtFortranEntityDeclList : public AdtFortranBase
{
public:
  AdtFortranEntityDeclList(AdtParser* pEntityDeclObj);
  AdtFortranEntityDeclList(const AdtFortranEntityDeclList& rCopy);
  virtual ~AdtFortranEntityDeclList();

  void                           removeExternals(const AdtParserPtrByStringMap& rExternalsMap);

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranEntityDecl);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEntityDecl class
//  ----------------------------------------------------------------------------
class AdtFortranEntityDecl : public AdtFortranBase
{
private:
  AdtFortranName*               Name;
  AdtFortranExpr*               Expr;
  AdtFortranCharLength*         CharLength;
  AdtFortranShapeSpecList*      ShapeSpecList;
  AdtFortranInvalidEntityDecl*  InvalidEntityDecl;

public:
  AdtFortranEntityDecl(AdtParser* pNameObj,
                       AdtParser* pExprObj,
                       AdtParser* pCharLengthObj,
                       AdtParser* pShapeSpecListObj,
                       AdtParser* pInvalidEntityDeclObj);

  AdtFortranEntityDecl(const AdtFortranEntityDecl& rCopy);
  virtual ~AdtFortranEntityDecl();

  size_t                         numberOfDimensions() const;

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranInvalidEntityDecl class
//  ----------------------------------------------------------------------------
class AdtFortranInvalidEntityDecl : public AdtFortranBase
{
private:
  AdtFortranName*               Name;
  AdtFortranExpr*               Expr;
  AdtFortranCharLength*         CharLength;
  AdtFortranShapeSpecList*      ShapeSpecList;

public:
  AdtFortranInvalidEntityDecl(AdtParser* pNameObj,
                              AdtParser* pExprObj,
                              AdtParser* pCharLengthObj,
                              AdtParser* pShapeSpecListObj);

  AdtFortranInvalidEntityDecl(const AdtFortranInvalidEntityDecl& rCopy);
  virtual ~AdtFortranInvalidEntityDecl();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCharLength class
//  ----------------------------------------------------------------------------
class AdtFortranCharLength : public AdtFortranBase
{
private:
  AdtFortranExpr*               Expr;
  AdtFortranIcon*               Icon;

public:
  AdtFortranCharLength(AdtParser* pExprObj,
                       AdtParser* pIconObj);

  AdtFortranCharLength(const AdtFortranCharLength& rCopy);
  virtual ~AdtFortranCharLength();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranShapeSpecList class
//  ----------------------------------------------------------------------------
class AdtFortranShapeSpecList : public AdtFortranBase
{
public:
  AdtFortranShapeSpecList(AdtParser* pShapeSpecObj);
  AdtFortranShapeSpecList(const AdtFortranShapeSpecList& rCopy);
  virtual ~AdtFortranShapeSpecList();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranShapeSpec);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranShapeSpec class
//  ----------------------------------------------------------------------------
class AdtFortranShapeSpec : public AdtFortranBase
{
private:
  AdtFortranExpr*               Expr;
  AdtFortranExpr*               Expr2;

public:
  AdtFortranShapeSpec(AdtParser* pExprObj,
                      AdtParser* pExpr2Obj);

  AdtFortranShapeSpec(const AdtFortranShapeSpec& rCopy);
  virtual ~AdtFortranShapeSpec();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranDimensionStmt class
//  ----------------------------------------------------------------------------
class AdtFortranDimensionStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranArrayDeclaratorList*  ArrayDeclaratorList;

public:
  AdtFortranDimensionStmt(AdtParser* pLblDefObj,
                          AdtParser* pArrayDeclaratorListObj);

  AdtFortranDimensionStmt(const AdtFortranDimensionStmt& rCopy);
  virtual ~AdtFortranDimensionStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranArrayDeclaratorList class
//  ----------------------------------------------------------------------------
class AdtFortranArrayDeclaratorList : public AdtFortranBase
{
public:
  AdtFortranArrayDeclaratorList(AdtParser* pArrayDeclaratorObj);
  AdtFortranArrayDeclaratorList(const AdtFortranArrayDeclaratorList& rCopy);
  virtual ~AdtFortranArrayDeclaratorList();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranArrayDeclarator);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranArrayDeclarator class
//  ----------------------------------------------------------------------------
class AdtFortranArrayDeclarator : public AdtFortranBase
{
private:
  AdtFortranName*               Name;
  AdtFortranShapeSpecList*      ShapeSpecList;

public:
  AdtFortranArrayDeclarator(AdtParser* pNameObj,
                            AdtParser* pShapeSpecListObj);

  AdtFortranArrayDeclarator(const AdtFortranArrayDeclarator& rCopy);
  virtual ~AdtFortranArrayDeclarator();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranParameterStmt class
//  ----------------------------------------------------------------------------
class AdtFortranParameterStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranNamedConstantDefList* NamedConstantDefList;

public:
  AdtFortranParameterStmt(AdtParser* pLblDefObj,
                          AdtParser* pNamedConstantDefListObj);

  AdtFortranParameterStmt(const AdtFortranParameterStmt& rCopy);
  virtual ~AdtFortranParameterStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranNamedConstantDefList class
//  ----------------------------------------------------------------------------
class AdtFortranNamedConstantDefList : public AdtFortranBase
{
public:
  AdtFortranNamedConstantDefList(AdtParser* pNamedConstantDefObj);
  AdtFortranNamedConstantDefList(const AdtFortranNamedConstantDefList& rCopy);
  virtual ~AdtFortranNamedConstantDefList();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranNamedConstantDef);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranNamedConstantDef class
//  ----------------------------------------------------------------------------
class AdtFortranNamedConstantDef : public AdtFortranBase
{
private:
  AdtFortranName* Name;
  AdtFortranExpr* Expr;

public:
  AdtFortranNamedConstantDef(AdtParser* pNameObj,
                             AdtParser* pExprObj);

  AdtFortranNamedConstantDef(const AdtFortranNamedConstantDef& rCopy);
  virtual ~AdtFortranNamedConstantDef();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitSpecList class
//  ----------------------------------------------------------------------------
class AdtFortranImplicitSpecList : public AdtFortranBase
{
public:
  AdtFortranImplicitSpecList(AdtParser* pImplicitSpecObj);
  AdtFortranImplicitSpecList(const AdtFortranImplicitSpecList& rCopy);
  virtual ~AdtFortranImplicitSpecList();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranImplicitSpec);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitSpec class
//  ----------------------------------------------------------------------------
class AdtFortranImplicitSpec : public AdtFortranBase
{
private:
  AdtFortranTypeSpec*           TypeSpec;
  AdtFortranImpl*               Impl;

public:
  AdtFortranImplicitSpec(AdtParser* pTypeSpecObj,
                         AdtParser* pImplObj);

  AdtFortranImplicitSpec(const AdtFortranImplicitSpec& rCopy);
  virtual ~AdtFortranImplicitSpec();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSectionSubscriptList class
//  ----------------------------------------------------------------------------
class AdtFortranSectionSubscriptList : public AdtFortranBase
{
public:
  AdtFortranSectionSubscriptList(AdtParser* pArrayDeclaratorObj);
  AdtFortranSectionSubscriptList(const AdtFortranSectionSubscriptList& rCopy);
  virtual ~AdtFortranSectionSubscriptList();

  bool                            hasSlice(int& nTriplets) const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranSectionSubscript);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSectionSubscript class
//  ----------------------------------------------------------------------------
class AdtFortranSectionSubscript : public AdtFortranBase
{
private:
  AdtFortranExpr*                 Expr;
  AdtFortranSubscriptTriplet*     SubscriptTriplet;
  AdtFortranSectionSubscriptList* SubscriptList;
  bool                            DoDelphiSliceExpand;

public:
  AdtFortranSectionSubscript(AdtParser* pExprObj,
                             AdtParser* pSubscriptTripletObj);
  AdtFortranSectionSubscript(AdtParser* pSubscriptListObj);
  AdtFortranSectionSubscript(const AdtFortranSectionSubscript& rCopy);
  virtual ~AdtFortranSectionSubscript();

  bool                            isSimple() const;
  bool                            hasSlice() const;
  void                            doDelphiSliceExpand(bool bExpand);

  AdtFortranSectionSubscript*     firstSubscript(int& nIndex) const;
  AdtFortranSectionSubscript*     nextSubscript(int& nIndex) const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSubscriptTriplet class
//  ----------------------------------------------------------------------------
class AdtFortranSubscriptTriplet : public AdtFortranBase
{
private:
  int                             Case;
  AdtFortranExpr*                 Expr;
  AdtFortranExpr*                 Expr2;
  AdtFortranExpr*                 Expr3;
  bool                            DoDelphiSliceExpand;

public:
  AdtFortranSubscriptTriplet(int nCase,
                             AdtParser* pExprObj,
                             AdtParser* pExpr2Obj,
                             AdtParser* pExpr3Obj);

  AdtFortranSubscriptTriplet(const AdtFortranSubscriptTriplet& rCopy);
  virtual ~AdtFortranSubscriptTriplet();

  void                            doDelphiSliceExpand(bool bExpand);
  bool                            isImplicit() const;

  bool                            lowerIndex(string& sLowerIndex) const;
  bool                            upperIndex(string& sUpperIndex) const;
  bool                            stride(string& sStride) const;

  void                            substituteExpr(AdtFortranExpr* pExpr);
  void                            substituteExpr2(AdtFortranExpr* pExpr2);

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline void AdtFortranSectionSubscript::doDelphiSliceExpand(bool bExpand)
{
  DoDelphiSliceExpand = bExpand;

  if (SubscriptTriplet != 0)
  {
    SubscriptTriplet->doDelphiSliceExpand(bExpand);
  }
}

//  ----------------------------------------------------------------------------

inline void AdtFortranSubscriptTriplet::doDelphiSliceExpand(bool bExpand)
{
  DoDelphiSliceExpand = bExpand;
}

//  ----------------------------------------------------------------------------

inline bool AdtFortranSubscriptTriplet::isImplicit() const
{
  return (((Case == 0) || (Case == 1) || (Case == 2)) && ((Expr == 0) || (Expr2 == 0)));
}


//  ----------------------------------------------------------------------------
//  AdtFortranPrimary class
//  ----------------------------------------------------------------------------
class AdtFortranPrimary : public AdtFortranBase
{
private:
  AdtFortranName*                 Name;
  AdtFortranScon*                 Scon;
  AdtFortranIcon*                 Icon;
  AdtFortranRcon*                 Rcon;
  AdtFortranExpr*                 Expr;
  AdtFortranExpr*                 Expr2;
  AdtFortranSectionSubscriptList* SectionSubscriptList;
  bool                            IsTrue;
  bool                            IsBracket;
  bool                            IsVariable;

public:
  AdtFortranPrimary(AdtParser* pNameObj,
                    AdtParser* pSconObj,
                    AdtParser* pIconObj,
                    AdtParser* pRconObj,
                    AdtParser* pExprObj,
                    AdtParser* pExpr2Obj,
                    AdtParser* pSectionSubscriptListObj,
                    bool bIsTrue,
                    bool bIsBracket);

  AdtFortranPrimary(const AdtFortranPrimary& rCopy);
  virtual ~AdtFortranPrimary();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          hasSlice() const;
  bool                          isValidLHS() const;
  bool                          isVariable() const;
  void                          checkIsVariable(const AdtIntByStringMap& rMap);

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtFortranPrimary::isValidLHS() const
{
  bool bIsValidLHS = ((Name  != 0) &&
                      (Scon  == 0) &&
                      (Icon  == 0) &&
                      (Rcon  == 0) &&
                      (Expr  == 0) &&
                      (Expr2 == 0));

  return (bIsValidLHS);
}

//  ----------------------------------------------------------------------------

inline bool AdtFortranPrimary::isVariable() const
{
  return (IsVariable);
}


//  ----------------------------------------------------------------------------
//  AdtFortranMultOperand class
//  ----------------------------------------------------------------------------
class AdtFortranMultOperand : public AdtFortranBase
{
private:
  AdtFortranPrimary*      Primary;
  AdtFortranMultOperand*  MultOperand;

public:
  AdtFortranMultOperand(AdtParser* pPrimaryObj,
                        AdtParser* pMultOperandObj);

  AdtFortranMultOperand(const AdtFortranMultOperand& rCopy);
  virtual ~AdtFortranMultOperand();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;


  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranAddOperand class
//  ----------------------------------------------------------------------------
class AdtFortranAddOperand : public AdtFortranBase
{
private:
  AdtFortranMultOperand*  MultOperand;
  AdtFortranAddOperand*   AddOperand;
  bool                    Multiply;

public:
  AdtFortranAddOperand(AdtParser* pMultOperandObj,
                       AdtParser* pAddOperandObj,
                       bool bMultiply);

  AdtFortranAddOperand(const AdtFortranAddOperand& rCopy);
  virtual ~AdtFortranAddOperand();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranLevel2Expr class
//  ----------------------------------------------------------------------------
class AdtFortranLevel2Expr : public AdtFortranBase
{
private:
  AdtFortranAddOperand*   AddOperand;
  AdtFortranLevel2Expr*   Level2Expr;
  bool                    Sign;
  bool                    HasOp;

public:
  AdtFortranLevel2Expr(AdtParser* pAddOperandObj,
                       AdtParser* pLevel2ExprObj,
                       bool bSign,
                       bool bHasOp);

  AdtFortranLevel2Expr(const AdtFortranLevel2Expr& rCopy);
  virtual ~AdtFortranLevel2Expr();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  bool                          hasSignOperator(bool& bPlus) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtFortranLevel2Expr::hasSignOperator(bool& bPlus) const
{
  bool bHasSignOperator = false;

  if ((AddOperand != 0) && (Level2Expr == 0) && HasOp)
  {
    bPlus            = Sign;
    bHasSignOperator = HasOp;
  }

  return (bHasSignOperator);
}


//  ----------------------------------------------------------------------------
//  AdtFortranLevel4Expr class
//  ----------------------------------------------------------------------------
class AdtFortranLevel4Expr : public AdtFortranBase
{
private:
  AdtFortranLevel2Expr*   Level2Expr;
  AdtFortranRelOp*        RelOp;
  AdtFortranLevel2Expr*   Level2Expr2;

public:
  AdtFortranLevel4Expr(AdtParser* pLevel2ExprObj,
                       AdtParser* pRelOpObj,
                       AdtParser* pLevel2Expr2Obj);

  AdtFortranLevel4Expr(const AdtFortranLevel4Expr& rCopy);
  virtual ~AdtFortranLevel4Expr();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranAndOperand class
//  ----------------------------------------------------------------------------
class AdtFortranAndOperand : public AdtFortranBase
{
private:
  AdtFortranLevel4Expr*   Level4Expr;
  bool                    Not;

public:
  AdtFortranAndOperand(AdtParser* pLevel4ExprObj,
                       bool bNot);

  AdtFortranAndOperand(const AdtFortranAndOperand& rCopy);
  virtual ~AdtFortranAndOperand();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranOrOperand class
//  ----------------------------------------------------------------------------
class AdtFortranOrOperand : public AdtFortranBase
{
private:
  AdtFortranAndOperand*   AndOperand;
  AdtFortranOrOperand*    OrOperand;

public:
  AdtFortranOrOperand(AdtParser* pAndOperandObj,
                      AdtParser* pOrOperandObj);

  AdtFortranOrOperand(const AdtFortranOrOperand& rCopy);
  virtual ~AdtFortranOrOperand();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEquivOperand class
//  ----------------------------------------------------------------------------
class AdtFortranEquivOperand : public AdtFortranBase
{
private:
  AdtFortranOrOperand*    OrOperand;
  AdtFortranEquivOperand* EquivOperand;

public:
  AdtFortranEquivOperand(AdtParser* pOrOperandObj,
                         AdtParser* pEquivOperandObj);

  AdtFortranEquivOperand(const AdtFortranEquivOperand& rCopy);
  virtual ~AdtFortranEquivOperand();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranExpr class
//  ----------------------------------------------------------------------------
class AdtFortranExpr : public AdtFortranBase
{
private:
  AdtFortranEquivOperand*       EquivOperand;
  AdtFortranExpr*               Expr;
  bool                          IsEquivalent;

public:
  AdtFortranExpr(AdtParser* pEquivOperandObj,
                 AdtParser* pExprObj,
                 bool bIsEquivalent);

  AdtFortranExpr(const AdtFortranExpr& rCopy);
  virtual ~AdtFortranExpr();

  void                          implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                     const AdtFortranSliceLoopVars& rSliceLoopVars);

  bool                          isSimple() const;
  bool                          hasSlice() const;
  virtual bool                  allowableMatch(const AdtParser* pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSFExprList class
//  ----------------------------------------------------------------------------
class AdtFortranSFExprList : public AdtFortranBase
{
private:
  AdtFortranSFExprList*           SFExprList;
  AdtFortranExpr*                 Expr;
  AdtFortranExpr*                 Expr2;

public:
  AdtFortranSFExprList(AdtParser* pSFExprListObj,
                       AdtParser* pExprObj,
                       AdtParser* pExpr2Obj);

  AdtFortranSFExprList(const AdtFortranSFExprList& rCopy);
  virtual ~AdtFortranSFExprList();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranAssignmentStmt class
//  ----------------------------------------------------------------------------
class AdtFortranAssignmentStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranName*                 Name;
  AdtFortranExpr*                 Expr;
  AdtFortranSFExprList*           SFExprList;
  AdtFortranSectionSubscriptList* SectionSubscriptList;

public:
  AdtFortranAssignmentStmt(AdtParser* pLblDefObj,
                           AdtParser* pNameObj,
                           AdtParser* pExprObj,
                           AdtParser* pSFExprListObj,
                           AdtParser* pSectionSubscriptListObj);

  AdtFortranAssignmentStmt(const AdtFortranAssignmentStmt& rCopy);
  virtual ~AdtFortranAssignmentStmt();

  bool                            hasSlice(int& nTriplets) const;

  bool                            implementSliceFixups(AdtStringByStringMap& rAddedVarMap,
                                                       const AdtFortranVariableInfo& rVariableInfo,
                                                       AdtFortranDeclarations* pDeclarations = 0,
                                                       AdtFile* pFile = 0);

  bool                            replace(AdtFortranPrimary* pPrimaryObj);

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereStmt class
//  ----------------------------------------------------------------------------
class AdtFortranWhereStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranExpr*                 Expr;
  AdtFortranAssignmentStmt*       AssignmentStmt;

public:
  AdtFortranWhereStmt(AdtParser* pLblDefObj,
                      AdtParser* pExprObj,
                      AdtParser* pAssignmentStmtObj);

  AdtFortranWhereStmt(const AdtFortranWhereStmt& rCopy);
  virtual ~AdtFortranWhereStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranWhereConstruct : public AdtFortranBase
{
private:
  AdtFortranWhereConstructStmt*   WhereConstructStmt;
  AdtFortranWhereRange*           WhereRange;

public:
  AdtFortranWhereConstruct(AdtParser* pWhereConstructStmtObj,
                           AdtParser* pWhereRangeObj);

  AdtFortranWhereConstruct(const AdtFortranWhereConstruct& rCopy);
  virtual ~AdtFortranWhereConstruct();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereRange class
//  ----------------------------------------------------------------------------
class AdtFortranWhereRange : public AdtFortranBase
{
private:
  AdtFortranWhereBodyConstructBlock*  WhereBodyConstructBlock;
  AdtFortranElsewhereConstruct*       ElsewhereConstruct;
  AdtFortranMaskedElsewhereConstruct* MaskedElsewhereConstruct;
  AdtFortranEndWhereStmt*             EndWhereStmt;

public:
  AdtFortranWhereRange(AdtParser* pWhereBodyConstructBlockObj,
                       AdtParser* pElsewhereConstructObj,
                       AdtParser* pMaskedElsewhereConstructObj,
                       AdtParser* pEndWhereStmtObj);

  AdtFortranWhereRange(const AdtFortranWhereRange& rCopy);
  virtual ~AdtFortranWhereRange();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranMaskedElsewhereConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranMaskedElsewhereConstruct : public AdtFortranBase
{
private:
  AdtFortranMaskedElsewhereStmt*  MaskedElsewhereStmt;
  AdtFortranWhereRange*           WhereRange;

public:
  AdtFortranMaskedElsewhereConstruct(AdtParser* pMaskedElsewhereStmtObj,
                                     AdtParser* pWhereRangeObj);

  AdtFortranMaskedElsewhereConstruct(const AdtFortranMaskedElsewhereConstruct& rCopy);
  virtual ~AdtFortranMaskedElsewhereConstruct();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElsewhereConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranElsewhereConstruct : public AdtFortranBase
{
private:
  AdtFortranElsewhereStmt*      ElsewhereStmt;
  AdtFortranElsewherePart*      ElsewherePart;

public:
  AdtFortranElsewhereConstruct(AdtParser* pElsewhereStmtObj,
                               AdtParser* pElsewherePartObj);

  AdtFortranElsewhereConstruct(const AdtFortranElsewhereConstruct& rCopy);
  virtual ~AdtFortranElsewhereConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElsewherePart class
//  ----------------------------------------------------------------------------
class AdtFortranElsewherePart : public AdtFortranBase
{
private:
  AdtFortranEndWhereStmt*             EndWhereStmt;
  AdtFortranWhereBodyConstructBlock*  WhereBodyConstructBlock;

public:
  AdtFortranElsewherePart(AdtParser* pEndWhereStmtObj,
                          AdtParser* pWhereBodyConstructBlockObj);

  AdtFortranElsewherePart(const AdtFortranElsewherePart& rCopy);
  virtual ~AdtFortranElsewherePart();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereBodyConstructBlock class
//  ----------------------------------------------------------------------------
class AdtFortranWhereBodyConstructBlock : public AdtFortranBase
{
public:
  AdtFortranWhereBodyConstructBlock(AdtParser* pWhereBodyConstructObj);
  AdtFortranWhereBodyConstructBlock(const AdtFortranWhereBodyConstructBlock& rCopy);
  virtual ~AdtFortranWhereBodyConstructBlock();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranWhereBodyConstruct);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereConstructStmt class
//  ----------------------------------------------------------------------------
class AdtFortranWhereConstructStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;
  AdtFortranExpr*               Expr;

public:
  AdtFortranWhereConstructStmt(AdtParser* pLblDefObj,
                               AdtParser* pNameObj,
                               AdtParser* pExprObj);

  AdtFortranWhereConstructStmt(const AdtFortranWhereConstructStmt& rCopy);
  virtual ~AdtFortranWhereConstructStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranWhereBodyConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranWhereBodyConstruct : public AdtFortranBase
{
private:
  AdtFortranAssignmentStmt*     AssignmentStmt;
  AdtFortranWhereStmt*          WhereStmt;
  AdtFortranWhereConstruct*     WhereConstruct;

public:
  AdtFortranWhereBodyConstruct(AdtParser* pAssignmentStmtObj,
                               AdtParser* pWhereStmtObj,
                               AdtParser* pWhereConstructObj);

  AdtFortranWhereBodyConstruct(const AdtFortranWhereBodyConstruct& rCopy);
  virtual ~AdtFortranWhereBodyConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranMaskedElsewhereStmt class
//  ----------------------------------------------------------------------------
class AdtFortranMaskedElsewhereStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranExpr*               Expr;
  AdtFortranName*               Name;

public:
  AdtFortranMaskedElsewhereStmt(AdtParser* pLblDefObj,
                                AdtParser* pExprObj,
                                AdtParser* pNameObj);

  AdtFortranMaskedElsewhereStmt(const AdtFortranMaskedElsewhereStmt& rCopy);
  virtual ~AdtFortranMaskedElsewhereStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElsewhereStmt class
//  ----------------------------------------------------------------------------
class AdtFortranElsewhereStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranElsewhereStmt(AdtParser* pLblDefObj,
                          AdtParser* pNameObj);

  AdtFortranElsewhereStmt(const AdtFortranElsewhereStmt& rCopy);
  virtual ~AdtFortranElsewhereStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEndWhereStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndWhereStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranEndWhereStmt(AdtParser* pLblDefObj,
                         AdtParser* pNameObj);

  AdtFortranEndWhereStmt(const AdtFortranEndWhereStmt& rCopy);
  virtual ~AdtFortranEndWhereStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranIfConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranIfConstruct : public AdtFortranBase
{
private:
  AdtFortranIfThenStmt*         IfThenStmt;
  AdtFortranThenPart*           ThenPart;

public:
  AdtFortranIfConstruct(AdtParser* pIfThenStmtObj,
                        AdtParser* pThenPartObj);

  AdtFortranIfConstruct(const AdtFortranIfConstruct& rCopy);
  virtual ~AdtFortranIfConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranThenPart class
//  ----------------------------------------------------------------------------
class AdtFortranThenPart : public AdtFortranBase
{
private:
  AdtFortranEndIfStmt*          EndIfStmt;
  AdtFortranConditionalBody*    ConditionalBody;
  AdtFortranElseIfConstruct*    ElseIfConstruct;
  AdtFortranElseConstruct*      ElseConstruct;

public:
  AdtFortranThenPart(AdtParser* pEndIfStmtObj,
                     AdtParser* pConditionalBodyObj,
                     AdtParser* pElseIfConstructObj,
                     AdtParser* pElseConstructObj);

  AdtFortranThenPart(const AdtFortranThenPart& rCopy);
  virtual ~AdtFortranThenPart();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElseIfConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranElseIfConstruct : public AdtFortranBase
{
private:
  AdtFortranElseIfStmt*         ElseIfStmt;
  AdtFortranThenPart*           ThenPart;

public:
  AdtFortranElseIfConstruct(AdtParser* pElseIfStmtObj,
                            AdtParser* pThenPartObj);

  AdtFortranElseIfConstruct(const AdtFortranElseIfConstruct& rCopy);
  virtual ~AdtFortranElseIfConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElseConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranElseConstruct : public AdtFortranBase
{
private:
  AdtFortranElseStmt*           ElseStmt;
  AdtFortranElsePart*           ElsePart;

public:
  AdtFortranElseConstruct(AdtParser* pElseStmtObj,
                          AdtParser* pElsePartObj);

  AdtFortranElseConstruct(const AdtFortranElseConstruct& rCopy);
  virtual ~AdtFortranElseConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElsePart class
//  ----------------------------------------------------------------------------
class AdtFortranElsePart : public AdtFortranBase
{
private:
  AdtFortranEndIfStmt*          EndIfStmt;
  AdtFortranConditionalBody*    ConditionalBody;

public:
  AdtFortranElsePart(AdtParser* pEndIfStmtObj,
                     AdtParser* pConditionalBodyObj);

  AdtFortranElsePart(const AdtFortranElsePart& rCopy);
  virtual ~AdtFortranElsePart();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranConditionalBody class
//  ----------------------------------------------------------------------------
class AdtFortranConditionalBody : public AdtFortranBase
{
public:
  AdtFortranConditionalBody(AdtParser* pExecutableConstructObj);
  AdtFortranConditionalBody(const AdtFortranConditionalBody& rCopy);
  virtual ~AdtFortranConditionalBody();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranExecutableConstruct);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranIfThenStmt class
//  ----------------------------------------------------------------------------
class AdtFortranIfThenStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranExpr*               Expr;
  AdtFortranName*               Name;

public:
  AdtFortranIfThenStmt(AdtParser* pLblDefObj,
                       AdtParser* pExprObj,
                       AdtParser* pNameObj);

  AdtFortranIfThenStmt(const AdtFortranIfThenStmt& rCopy);
  virtual ~AdtFortranIfThenStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElseIfStmt class
//  ----------------------------------------------------------------------------
class AdtFortranElseIfStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranExpr*               Expr;
  AdtFortranName*               Name;

public:
  AdtFortranElseIfStmt(AdtParser* pLblDefObj,
                       AdtParser* pExprObj,
                       AdtParser* pNameObj);

  AdtFortranElseIfStmt(const AdtFortranElseIfStmt& rCopy);
  virtual ~AdtFortranElseIfStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranElseStmt class
//  ----------------------------------------------------------------------------
class AdtFortranElseStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranElseStmt(AdtParser* pLblDefObj,
                     AdtParser* pNameObj);

  AdtFortranElseStmt(const AdtFortranElseStmt& rCopy);
  virtual ~AdtFortranElseStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEndIfStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndIfStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranEndIfStmt(AdtParser* pLblDefObj,
                      AdtParser* pNameObj);

  AdtFortranEndIfStmt(const AdtFortranEndIfStmt& rCopy);
  virtual ~AdtFortranEndIfStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranIfStmt class
//  ----------------------------------------------------------------------------
class AdtFortranIfStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranExpr*               Expr;
  AdtFortranActionStmt*         ActionStmt;

public:
  AdtFortranIfStmt(AdtParser* pLblDefObj,
                   AdtParser* pExprObj,
                   AdtParser* pActionStmtObj);

  AdtFortranIfStmt(const AdtFortranIfStmt& rCopy);
  virtual ~AdtFortranIfStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  void                          equivalentIfThenCode(string& rCodeString) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranCaseConstruct : public AdtFortranBase
{
private:
  AdtFortranSelectCaseStmt*     SelectCaseStmt;
  AdtFortranSelectCaseBody*     SelectCaseBody;
  AdtFortranEndSelectStmt*      EndSelectStmt;

public:
  AdtFortranCaseConstruct(AdtParser* pSelectCaseStmtObj,
                          AdtParser* pSelectCaseBodyObj,
                          AdtParser* pEndSelectStmtObj);

  AdtFortranCaseConstruct(const AdtFortranCaseConstruct& rCopy);
  virtual ~AdtFortranCaseConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSelectCaseBody class
//  ----------------------------------------------------------------------------
class AdtFortranSelectCaseBody : public AdtFortranBase
{
private:
  AdtFortranCaseStmt*           CaseStmt;
  AdtFortranSelectCaseBody*     SelectCaseBody;
  AdtFortranCaseBodyConstruct*  CaseBodyConstruct;

public:
  AdtFortranSelectCaseBody(AdtParser* pCaseStmtObj,
                           AdtParser* pSelectCaseBodyObj,
                           AdtParser* pCaseBodyConstructObj);

  AdtFortranSelectCaseBody(const AdtFortranSelectCaseBody& rCopy);
  virtual ~AdtFortranSelectCaseBody();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseBodyConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranCaseBodyConstruct : public AdtFortranBase
{
private:
  AdtFortranCaseStmt*             CaseStmt;
  AdtFortranExecutableConstruct*  ExecutableConstruct;

public:
  AdtFortranCaseBodyConstruct(AdtParser* pCaseStmtObj,
                              AdtParser* pExecutableConstructObj);

  AdtFortranCaseBodyConstruct(const AdtFortranCaseBodyConstruct& rCopy);
  virtual ~AdtFortranCaseBodyConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSelectCaseStmt class
//  ----------------------------------------------------------------------------
class AdtFortranSelectCaseStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;
  AdtFortranExpr*               Expr;

public:
  AdtFortranSelectCaseStmt(AdtParser* pLblDefObj,
                           AdtParser* pNameObj,
                           AdtParser* pExprObj);

  AdtFortranSelectCaseStmt(const AdtFortranSelectCaseStmt& rCopy);
  virtual ~AdtFortranSelectCaseStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseStmt class
//  ----------------------------------------------------------------------------
class AdtFortranCaseStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranCaseSelector*       CaseSelector;
  AdtFortranName*               Name;

public:
  AdtFortranCaseStmt(AdtParser* pLblDefObj,
                     AdtParser* pCaseSelectorObj,
                     AdtParser* pNameObj);

  AdtFortranCaseStmt(const AdtFortranCaseStmt& rCopy);
  virtual ~AdtFortranCaseStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEndSelectStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndSelectStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranEndSelectStmt(AdtParser* pLblDefObj,
                          AdtParser* pNameObj);

  AdtFortranEndSelectStmt(const AdtFortranEndSelectStmt& rCopy);
  virtual ~AdtFortranEndSelectStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseSelector class
//  ----------------------------------------------------------------------------
class AdtFortranCaseSelector : public AdtFortranBase
{
private:
  AdtFortranCaseValueRangeList* CaseValueRangeList;

public:
  AdtFortranCaseSelector(AdtParser* pCaseValueRangeListObj);
  AdtFortranCaseSelector(const AdtFortranCaseSelector& rCopy);
  virtual ~AdtFortranCaseSelector();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseValueRangeList class
//  ----------------------------------------------------------------------------
class AdtFortranCaseValueRangeList : public AdtFortranBase
{
public:
  AdtFortranCaseValueRangeList(AdtParser* pCaseValueRangeObj);
  AdtFortranCaseValueRangeList(const AdtFortranCaseValueRangeList& rCopy);
  virtual ~AdtFortranCaseValueRangeList();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranCaseValueRange);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCaseValueRange class
//  ----------------------------------------------------------------------------
class AdtFortranCaseValueRange : public AdtFortranBase
{
private:
  AdtFortranExpr*               Expr;
  AdtFortranExpr*               Expr2;
  bool                          HasColon;

public:
  AdtFortranCaseValueRange(AdtParser* pExprObj,
                           AdtParser* pExpr2Obj,
                           bool bHasColon);

  AdtFortranCaseValueRange(const AdtFortranCaseValueRange& rCopy);
  virtual ~AdtFortranCaseValueRange();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranDoConstruct class
//  ----------------------------------------------------------------------------
class AdtFortranDoConstruct : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranLblRef*             LblRef;
  AdtFortranLoopControl*        LoopControl;
  AdtFortranName*               Name;
  AdtFortranConditionalBody*    ConditionalBody;
  AdtFortranEndDoStmt*          EndDoStmt;
  bool                          HasComma;

public:
  AdtFortranDoConstruct(AdtParser* pLblDefObj,
                        AdtParser* pLblRefObj,
                        AdtParser* pLoopControlObj,
                        AdtParser* pNameObj,
                        AdtParser* pConditionalBodyObj,
                        AdtParser* pEndDoStmtObj,
                        bool bHasComma);

  AdtFortranDoConstruct(const AdtFortranDoConstruct& rCopy);
  virtual ~AdtFortranDoConstruct();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranLoopControl class
//  ----------------------------------------------------------------------------
class AdtFortranLoopControl : public AdtFortranBase
{
private:
  AdtFortranName*               Name;
  AdtFortranExpr*               Expr;
  AdtFortranExpr*               Expr2;
  AdtFortranExpr*               Expr3;
  AdtFortranLevel2Expr*         Expr3Sign;
  AdtFortranIcon*               Expr3Value;

public:
  AdtFortranLoopControl(AdtParser* pNameObj,
                        AdtParser* pExprObj,
                        AdtParser* pExpr2Obj,
                        AdtParser* pExpr3Obj);

  AdtFortranLoopControl(const AdtFortranLoopControl& rCopy);
  virtual ~AdtFortranLoopControl();

  AdtFile&                      writeDelphiLoopStep(AdtFile& pOutFile, int nMode = 0) const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  bool                          unityloopIncrement(bool& bPlus) const;
  bool                          isWhileConstruct() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtFortranLoopControl::isWhileConstruct() const
{
  return (Name == 0);
}


//  ----------------------------------------------------------------------------
//  AdtFortranEndDoStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndDoStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranEndDoStmt(AdtParser* pLblDefObj,
                      AdtParser* pNameObj);

  AdtFortranEndDoStmt(const AdtFortranEndDoStmt& rCopy);
  virtual ~AdtFortranEndDoStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCycleStmt class
//  ----------------------------------------------------------------------------
class AdtFortranCycleStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranCycleStmt(AdtParser* pLblDefObj,
                      AdtParser* pNameObj);

  AdtFortranCycleStmt(const AdtFortranCycleStmt& rCopy);
  virtual ~AdtFortranCycleStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranExitStmt class
//  ----------------------------------------------------------------------------
class AdtFortranExitStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranExitStmt(AdtParser* pLblDefObj,
                     AdtParser* pNameObj);

  AdtFortranExitStmt(const AdtFortranExitStmt& rCopy);
  virtual ~AdtFortranExitStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranGotoStmt class
//  ----------------------------------------------------------------------------
class AdtFortranGotoStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranLblRef*             LblRef;

public:
  AdtFortranGotoStmt(AdtParser* pLblDefObj,
                     AdtParser* pLblRefObj);

  AdtFortranGotoStmt(const AdtFortranGotoStmt& rCopy);
  virtual ~AdtFortranGotoStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranArithmeticIfStmt class
//  ----------------------------------------------------------------------------
class AdtFortranArithmeticIfStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranExpr*               Expr;
  AdtFortranLblRef*             LblRef;
  AdtFortranLblRef*             LblRef2;
  AdtFortranLblRef*             LblRef3;

public:
  AdtFortranArithmeticIfStmt(AdtParser* pLblDefObj,
                             AdtParser* pExprObj,
                             AdtParser* pLblRefObj,
                             AdtParser* pLblRef2Obj,
                             AdtParser* pLblRef3Obj);

  AdtFortranArithmeticIfStmt(const AdtFortranArithmeticIfStmt& rCopy);
  virtual ~AdtFortranArithmeticIfStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranContinueStmt class
//  ----------------------------------------------------------------------------
class AdtFortranContinueStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;

public:
  AdtFortranContinueStmt(AdtParser* pLblDefObj);
  AdtFortranContinueStmt(const AdtFortranContinueStmt& rCopy);
  virtual ~AdtFortranContinueStmt();

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranModuleStmt class
//  ----------------------------------------------------------------------------
class AdtFortranModuleStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef* LblDef;
  AdtFortranName*   ModuleName;

public:
  AdtFortranModuleStmt(AdtParser* pLblDefObj,
                       AdtParser* pModuleNameObj);

  AdtFortranModuleStmt(const AdtFortranModuleStmt& rCopy);
  virtual ~AdtFortranModuleStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEndModuleStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndModuleStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef* LblDef;
  AdtFortranName*   ModuleName;

public:
  AdtFortranEndModuleStmt(AdtParser* pLblDefObj,
                          AdtParser* pModuleNameObj);

  AdtFortranEndModuleStmt(const AdtFortranEndModuleStmt& rCopy);
  virtual ~AdtFortranEndModuleStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranUseStmt class
//  ----------------------------------------------------------------------------
class AdtFortranUseStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranName*               Name;

public:
  AdtFortranUseStmt(AdtParser* pLblDefObj,
                    AdtParser* pNameObj);

  AdtFortranUseStmt(const AdtFortranUseStmt& rCopy);
  virtual ~AdtFortranUseStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranIntentSpec class
//  ----------------------------------------------------------------------------
class AdtFortranIntentSpec : public AdtFortranBase
{
private:
  AdtFortranIntent               Intent;

public:
  AdtFortranIntentSpec(int nIntent);
  AdtFortranIntentSpec(const AdtFortranIntentSpec& rCopy);
  virtual ~AdtFortranIntentSpec();

  AdtFortranIntent               intent() const;

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFortranIntent AdtFortranIntentSpec::intent() const
{
  return (Intent);
}


//  ----------------------------------------------------------------------------
//  AdtFortranIntentStmt class
//  ----------------------------------------------------------------------------
class AdtFortranIntentStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranIntentSpec*           IntentSpec;
  AdtFortranNameList*             NameList;
  bool                            HasColonColon;

public:
  AdtFortranIntentStmt(AdtParser* pLblDefObj,
                       AdtParser* pIntentSpecObj,
                       AdtParser* pNameListObj,
                       bool bHasColonColon);

  AdtFortranIntentStmt(const AdtFortranIntentStmt& rCopy);
  virtual ~AdtFortranIntentStmt();

  AdtFortranIntent                intent() const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFortranIntent AdtFortranIntentStmt::intent() const
{
  return (IntentSpec != 0 ? IntentSpec->intent() : ForIntent_INOUT);
}


//  ----------------------------------------------------------------------------
//  AdtFortranIntrinsicStmt class
//  ----------------------------------------------------------------------------
class AdtFortranIntrinsicStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranNameList*             NameList;

public:
  AdtFortranIntrinsicStmt(AdtParser* pLblDefObj,
                          AdtParser* pNameListObj);

  AdtFortranIntrinsicStmt(const AdtFortranIntrinsicStmt& rCopy);
  virtual ~AdtFortranIntrinsicStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranExternalStmt class
//  ----------------------------------------------------------------------------
class AdtFortranExternalStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranNameList*             NameList;
  bool                            HasColon;

public:
  AdtFortranExternalStmt(AdtParser* pLblDefObj,
                         AdtParser* pNameListObj,
                         bool bHasColon);

  AdtFortranExternalStmt(const AdtFortranExternalStmt& rCopy);
  virtual ~AdtFortranExternalStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranCallStmt class
//  ----------------------------------------------------------------------------
class AdtFortranCallStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranName*                 Name;
  AdtFortranSectionSubscriptList* SectionSubscriptList;

public:
  AdtFortranCallStmt(AdtParser* pLblDefObj,
                     AdtParser* pNameObj,
                     AdtParser* pSectionSubscriptListObj);

  AdtFortranCallStmt(const AdtFortranCallStmt& rCopy);
  virtual ~AdtFortranCallStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranFunctionStmt class
//  ----------------------------------------------------------------------------
class AdtFortranFunctionStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranTypeSpec*           TypeSpec;
  AdtFortranName*               FunctionName;
  AdtFortranNameList*           ParameterList;
  bool                          EmptyParameterList;
  bool                          Recursive;
  bool                          IsVirtual;
  AdtFortranName*               ResultName;
  AdtFortranDeclarations*       Declarations;

public:
  AdtFortranFunctionStmt(AdtParser* pLblDefObj,
                         AdtParser* pTypeSpecObj,
                         AdtParser* pFunctionNameObj,
                         AdtParser* pParameterListObj,
                         bool bEmptyParameterList,
                         bool bRecursive,
                         AdtParser* pResultNameObj);

  AdtFortranFunctionStmt(const AdtFortranFunctionStmt& rCopy);
  virtual ~AdtFortranFunctionStmt();

  AdtFortranDeclarations*         declarations();

  void                            isVirtual(bool bIsVirtual);

  void                            initialise(AdtParserPtrByStringMap* pFunctionMap = 0);

  AdtFile&                        writeCPP_Initialisations(AdtFile& pOutFile) const;
  AdtFile&                        writeCPP_Allocations(AdtFile& pOutFile) const;
  AdtFile&                        writeCPP_Deallocations(AdtFile& pOutFile) const;
  AdtFile&                        writeDelphiInitialisations(AdtFile& pOutFile) const;

  AdtFile&                        writeDelphiAllocations(AdtFile& pOutFile,
                                                         AdtStringList* pVarList,
                                                         AdtStringList* pDestroyList) const;

  AdtFile&                        writeDelphiDeallocations(AdtFile& pOutFile) const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFortranDeclarations* AdtFortranFunctionStmt::declarations()
{
  return (Declarations);
}

//  ----------------------------------------------------------------------------

inline void AdtFortranFunctionStmt::isVirtual(bool bIsVirtual)
{
  IsVirtual = bIsVirtual;
}


//  ----------------------------------------------------------------------------
//  AdtFortranLblRef class
//  ----------------------------------------------------------------------------
class AdtFortranLblRef : public AdtFortranBase
{
public:
  AdtFortranLblRef(const char* pIcon);
  AdtFortranLblRef(const AdtFortranLblRef& rCopy);
  virtual ~AdtFortranLblRef();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranName class
//  ----------------------------------------------------------------------------
class AdtFortranName : public AdtFortranBase
{
private:
  static const char*             PrefixString;
  static const char*             FindString;
  static const char*             ReplaceString;

protected:
  AdtFile&                       writeChanged(AdtFile& pOutFile, int nMode) const;

public:
  AdtFortranName(const char* pIdent);
  AdtFortranName(const AdtFortranName& rCopy);
  virtual ~AdtFortranName();

  static void                    setClearPrefix(const char* pPrefixString);
  static void                    setSubstitute(const char* pFind, const char* pReplace);

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranNameList class
//  ----------------------------------------------------------------------------
class AdtFortranNameList : public AdtFortranBase
{
public:
  AdtFortranNameList(AdtParser* pNameObj);
  AdtFortranNameList(const AdtFortranNameList& rCopy);
  virtual ~AdtFortranNameList();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtFortranName);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranEndFunctionStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndFunctionStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranName*                 FunctionName;

public:
  AdtFortranEndFunctionStmt(AdtParser* pLblDefObj,
                            AdtParser* pFunctionNameObj);

  AdtFortranEndFunctionStmt(const AdtFortranEndFunctionStmt& rCopy);
  virtual ~AdtFortranEndFunctionStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranSubroutineStmt class
//  ----------------------------------------------------------------------------
class AdtFortranSubroutineStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranName*                 SubroutineName;
  AdtFortranNameList*             ParameterList;
  bool                            EmptyParameterList;
  bool                            Recursive;
  bool                            IsVirtual;
  AdtFortranDeclarations*         Declarations;

public:
  AdtFortranSubroutineStmt(AdtParser* pLblDefObj,
                           AdtParser* pSubroutineNameObj,
                           AdtParser* pParameterListObj,
                           bool bEmptyParameterList,
                           bool bRecursive);

  AdtFortranSubroutineStmt(const AdtFortranSubroutineStmt& rCopy);
  virtual ~AdtFortranSubroutineStmt();

  AdtFortranDeclarations*         declarations();

  void                            isVirtual(bool bIsVirtual);

  void                            initialise(AdtParserPtrByStringMap* pFunctionMap = 0);

  AdtFile&                        writeCPP_Initialisations(AdtFile& pOutFile) const;
  AdtFile&                        writeCPP_Allocations(AdtFile& pOutFile) const;
  AdtFile&                        writeCPP_Deallocations(AdtFile& pOutFile) const;
  AdtFile&                        writeDelphiInitialisations(AdtFile& pOutFile) const;

  AdtFile&                        writeDelphiAllocations(AdtFile& pOutFile,
                                                         AdtStringList* pVarList,
                                                         AdtStringList* pDestroyList) const;

  AdtFile&                        writeDelphiDeallocations(AdtFile& pOutFile) const;

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFortranDeclarations* AdtFortranSubroutineStmt::declarations()
{
  return (Declarations);
}

//  ----------------------------------------------------------------------------

inline void AdtFortranSubroutineStmt::isVirtual(bool bIsVirtual)
{
  IsVirtual = bIsVirtual;
}


//  ----------------------------------------------------------------------------
//  AdtFortranEndSubroutineStmt class
//  ----------------------------------------------------------------------------
class AdtFortranEndSubroutineStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranName*                 SubroutineName;

public:
  AdtFortranEndSubroutineStmt(AdtParser* pLblDefObj,
                              AdtParser* pSubroutineNameObj);

  AdtFortranEndSubroutineStmt(const AdtFortranEndSubroutineStmt& rCopy);
  virtual ~AdtFortranEndSubroutineStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranReturnStmt class
//  ----------------------------------------------------------------------------
class AdtFortranReturnStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*               LblDef;
  AdtFortranExpr*                 Expr;

public:
  AdtFortranReturnStmt(AdtParser* pLblDefObj,
                       AdtParser* pExprObj);

  AdtFortranReturnStmt(const AdtFortranReturnStmt& rCopy);
  virtual ~AdtFortranReturnStmt();

  virtual AdtFile&                writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranLblDef class
//  ----------------------------------------------------------------------------
class AdtFortranLblDef : public AdtFortranBase
{
private:
  AdtFortranIcon*               Icon;

public:
  AdtFortranLblDef(AdtParser* pIconObj,
                   const char* pComment);

  AdtFortranLblDef(const AdtFortranLblDef& rCopy);
  virtual ~AdtFortranLblDef();

  bool                          isEmpty() const;

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtFortranLblDef::isEmpty() const
{
  return (Icon == 0);
}


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitStmt class
//  ----------------------------------------------------------------------------
class AdtFortranImplicitStmt : public AdtFortranBase
{
private:
  AdtFortranLblDef*             LblDef;
  AdtFortranImplicitSpecList*   ImplicitSpecList;

public:
  AdtFortranImplicitStmt(AdtParser* pLblDefObj,
                         AdtParser* pImplicitSpecListObj);

  AdtFortranImplicitStmt(const AdtFortranImplicitStmt& rCopy);
  virtual ~AdtFortranImplicitStmt();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranIcon class
//  ----------------------------------------------------------------------------
class AdtFortranIcon : public AdtFortranBase
{
protected:
  string                         Size;

public:
  AdtFortranIcon(const char* pIcon);
  AdtFortranIcon(const AdtFortranIcon& rCopy);
  virtual ~AdtFortranIcon();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranRcon class
//  ----------------------------------------------------------------------------
class AdtFortranRcon : public AdtFortranBase
{
protected:
  string                         Size;

public:
  AdtFortranRcon(const char* pRcon);
  AdtFortranRcon(const AdtFortranRcon& rCopy);
  virtual ~AdtFortranRcon();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranScon class
//  ----------------------------------------------------------------------------
class AdtFortranScon : public AdtFortranBase
{
public:
  AdtFortranScon(const char* pScon);
  AdtFortranScon(const AdtFortranScon& rCopy);
  virtual ~AdtFortranScon();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtFortranImpl class
//  ----------------------------------------------------------------------------
class AdtFortranImpl : public AdtFortranBase
{
public:
  AdtFortranImpl(const char* pImpl);
  AdtFortranImpl(const AdtFortranImpl& rCopy);
  virtual ~AdtFortranImpl();

  virtual AdtFile&               writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&               writeFortran(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


#endif //__cplusplus
#endif //__AdtFortran_HPP
