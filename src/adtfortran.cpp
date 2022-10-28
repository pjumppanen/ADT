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
//    AdtFortran.cpp
//
//  Purpose:
//    This file includes implementation of classes used to collate information
//    describing the fortran file auto-differentiated output.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtfortran.hpp"
#include "adtdelphi.hpp"
#include "adtcpp.hpp"
#include "adtutils.hpp"
#include "adtautomate.hpp"


#define DELPHI_MODE_FUNCTION_DECLARATION  10
#define CPP_MODE_FUNCTION_DECLARATION     11


//  ----------------------------------------------------------------------------
//  Globals
//  ----------------------------------------------------------------------------
AdtFortranExecutableProgram*  AdtFortranBase::FortranRootObject           = 0;
const char*                   AdtFortranBase::RemovePrefixString          = 0;
const char*                   AdtFortranBase::AddPrefixString             = 0;
bool                          AdtFortranBase::PushPopDisable              = false;
bool                          AdtFortranBase::WithStackSubstitution       = false;
//  ----------------------------------------------------------------------------
const char*                   AdtFortranName::PrefixString                = 0;
const char*                   AdtFortranName::FindString                  = 0;
const char*                   AdtFortranName::ReplaceString               = 0;


//  ----------------------------------------------------------------------------
//  "C" callable function implementations
//  ----------------------------------------------------------------------------
void* adtFortran_setRoot(void* pRoot)
{
  AdtFortranBase::fortranRootObject(Obj(pRoot));

  return (pRoot);
}

//  ----------------------------------------------------------------------------

void* adtFortran_getRoot(void)
{
  return (Hnd(AdtFortranBase::fortranRootObject()));
}

//  ----------------------------------------------------------------------------

void adtFortran_releaseRoot(void)
{
  AdtFortranBase::fortranRootObject(0);
}

//  ----------------------------------------------------------------------------

void adtFortran_releaseObject(void* pObj)
{
  UtlReleaseReference(Obj(pObj));
}

//  ----------------------------------------------------------------------------

void* adtFortranList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtFortranExecutableProgram_create(void* pObj)
{
  return (Hnd(new AdtFortranExecutableProgram(ObjAndRelease(pObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranProgramUnit_create(void* pFunctionSubprogramObj, void* pSubroutineSubprogramObj, void* pModuleObj, void* pCallExpandObj, void* pProgramConstructObj)
{
  return (Hnd(new AdtFortranProgramUnit(ObjAndRelease(pFunctionSubprogramObj), ObjAndRelease(pSubroutineSubprogramObj), ObjAndRelease(pModuleObj), ObjAndRelease(pCallExpandObj), ObjAndRelease(pProgramConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCallExpand_create(void* pNameObj, void* pNameListObj, void* pConditionalBodyObj, void* pTypeDeclarationStmtListObj, int nHasBrackets)
{
  return (Hnd(new AdtFortranCallExpand(ObjAndRelease(pNameObj), ObjAndRelease(pNameListObj), ObjAndRelease(pConditionalBodyObj), ObjAndRelease(pTypeDeclarationStmtListObj), nHasBrackets != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranProgramConstruct_create(void* pLblDefObj, void* pNameObj, void* pBodyObj, void* pEndLblDefObj)
{
  return (Hnd(new AdtFortranProgramConstruct(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj), ObjAndRelease(pBodyObj), ObjAndRelease(pEndLblDefObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranTypeDeclarationStmtList_create(void* pTypeDeclarationStmtObj)
{
  return (Hnd(new AdtFortranTypeDeclarationStmtList(ObjAndRelease(pTypeDeclarationStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranBody_create(void* pBodyConstructObj)
{
  return (Hnd(new AdtFortranBody(ObjAndRelease(pBodyConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranBodyConstruct_create(void* pSpecificationPartConstructObj, void* pExecutableConstructObj)
{
  return (Hnd(new AdtFortranBodyConstruct(ObjAndRelease(pSpecificationPartConstructObj), ObjAndRelease(pExecutableConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranFunctionSubprogram_create(void* pFunctionStmtObj, void* pEndFunctionStmtObj, void* pBodyObj)
{
  return (Hnd(new AdtFortranFunctionSubprogram(ObjAndRelease(pFunctionStmtObj), ObjAndRelease(pEndFunctionStmtObj), ObjAndRelease(pBodyObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSubroutineSubprogram_create(void* pSubroutineStmtObj, void* pEndSubroutineStmtObj, void* pBodyObj)
{
  return (Hnd(new AdtFortranSubroutineSubprogram(ObjAndRelease(pSubroutineStmtObj), ObjAndRelease(pEndSubroutineStmtObj), ObjAndRelease(pBodyObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranModule_create(void* pModuleStmtObj, void* pModuleBodyObj, void* pEndModuleStmtObj)
{
  return (Hnd(new AdtFortranModule(ObjAndRelease(pModuleStmtObj), ObjAndRelease(pModuleBodyObj), ObjAndRelease(pEndModuleStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranModuleBody_create(void* pModuleBodyContentObj)
{
  return (Hnd(new AdtFortranModuleBody(ObjAndRelease(pModuleBodyContentObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranModuleBodyContent_create(void* pSpecificationPartConstructObj, void* pFunctionSubprogramObj, void* pSubroutineSubprogramObj)
{
  return (Hnd(new AdtFortranModuleBodyContent(ObjAndRelease(pSpecificationPartConstructObj), ObjAndRelease(pFunctionSubprogramObj), ObjAndRelease(pSubroutineSubprogramObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSpecificationPartConstruct_create(void* pUseStmtObj, void* pImplicitStmtObj, void* pParameterStmtObj, void* pTypeDeclarationStmtObj, void* pDimensionStmtObj, void* pIntrinsicStmtObj, void* pExternalStmtObj, void* pIntentStmtObj)
{
  return (Hnd(new AdtFortranSpecificationPartConstruct(ObjAndRelease(pUseStmtObj), ObjAndRelease(pImplicitStmtObj), ObjAndRelease(pParameterStmtObj), ObjAndRelease(pTypeDeclarationStmtObj), ObjAndRelease(pDimensionStmtObj), ObjAndRelease(pIntrinsicStmtObj), ObjAndRelease(pExternalStmtObj), ObjAndRelease(pIntentStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranExecutableConstruct_create(void* pActionStmtObj, void* pCaseConstructObj, void* pDoConstructObj, void* pIfConstructObj, void* pWhereConstructObj)
{
  return (Hnd(new AdtFortranExecutableConstruct(ObjAndRelease(pActionStmtObj), ObjAndRelease(pCaseConstructObj), ObjAndRelease(pDoConstructObj), ObjAndRelease(pIfConstructObj), ObjAndRelease(pWhereConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranActionStmt_create(void* pArithmeticIfStmtObj, void* pAssignmentStmtObj, void* pCallStmtObj, void* pContinueStmtObj, void* pCycleStmtObj, void* pExitStmtObj, void* pIfStmtObj, void* pReturnStmtObj, void* pWhereStmtObj, void* pGotoStmtObj)
{
  return (Hnd(new AdtFortranActionStmt(ObjAndRelease(pArithmeticIfStmtObj), ObjAndRelease(pAssignmentStmtObj), ObjAndRelease(pCallStmtObj), ObjAndRelease(pContinueStmtObj), ObjAndRelease(pCycleStmtObj), ObjAndRelease(pExitStmtObj), ObjAndRelease(pIfStmtObj), ObjAndRelease(pReturnStmtObj), ObjAndRelease(pWhereStmtObj), ObjAndRelease(pGotoStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranRelOp_create(int nOp)
{
  return (Hnd(new AdtFortranRelOp((AdtFortranOp)nOp), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranTypeDeclarationStmt_create(void* pLblDefObj, void* pTypeSpecObj, void* pAttrSpecSeqObj, void* pEntityDeclListObj)
{
  return (Hnd(new AdtFortranTypeDeclarationStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pTypeSpecObj), ObjAndRelease(pAttrSpecSeqObj), ObjAndRelease(pEntityDeclListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranAttrSpecSeq_create(void* pAttrSpecObj)
{
  return (Hnd(new AdtFortranAttrSpecSeq(ObjAndRelease(pAttrSpecObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranTypeSpec_create(int nType, const char* pIcon)
{
  return (Hnd(new AdtFortranTypeSpec((AdtFortranType)nType, pIcon), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranAttrSpec_create(void* pShapeSpecListObj, void* pIntentSpecObj, int nAttribute)
{
  return (Hnd(new AdtFortranAttrSpec(ObjAndRelease(pShapeSpecListObj), ObjAndRelease(pIntentSpecObj), (AdtFortranAttr)nAttribute), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEntityDeclList_create(void* pEntityDeclObj)
{
  return (Hnd(new AdtFortranEntityDeclList(ObjAndRelease(pEntityDeclObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEntityDecl_create(void* pNameObj, void* pExprObj, void* pCharLengthObj, void* pShapeSpecListObj, void* pInvalidEntityDeclObj)
{
  return (Hnd(new AdtFortranEntityDecl(ObjAndRelease(pNameObj), ObjAndRelease(pExprObj), ObjAndRelease(pCharLengthObj), ObjAndRelease(pShapeSpecListObj), ObjAndRelease(pInvalidEntityDeclObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranInvalidEntityDecl_create(void* pNameObj, void* pExprObj, void* pCharLengthObj, void* pShapeSpecListObj)
{
  return (Hnd(new AdtFortranInvalidEntityDecl(ObjAndRelease(pNameObj), ObjAndRelease(pExprObj), ObjAndRelease(pCharLengthObj), ObjAndRelease(pShapeSpecListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCharLength_create(void* pExprObj, void* pIconObj)
{
  return (Hnd(new AdtFortranCharLength(ObjAndRelease(pExprObj), ObjAndRelease(pIconObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranShapeSpecList_create(void* pShapeSpecObj)
{
  return (Hnd(new AdtFortranShapeSpecList(ObjAndRelease(pShapeSpecObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranShapeSpec_create(void* pExprObj, void* pExpr2Obj)
{
  return (Hnd(new AdtFortranShapeSpec(ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranDimensionStmt_create(void* pLblDefObj, void* pArrayDeclaratorListObj)
{
  return (Hnd(new AdtFortranDimensionStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pArrayDeclaratorListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranArrayDeclaratorList_create(void* pArrayDeclaratorObj)
{
  return (Hnd(new AdtFortranArrayDeclaratorList(ObjAndRelease(pArrayDeclaratorObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranArrayDeclarator_create(void* pNameObj, void* pShapeSpecListObj)
{
  return (Hnd(new AdtFortranArrayDeclarator(ObjAndRelease(pNameObj), ObjAndRelease(pShapeSpecListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranParameterStmt_create(void* pLblDefObj, void* pNamedConstantDefListObj)
{
  return (Hnd(new AdtFortranParameterStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNamedConstantDefListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranNamedConstantDefList_create(void* pNamedConstantDefObj)
{
  return (Hnd(new AdtFortranNamedConstantDefList(ObjAndRelease(pNamedConstantDefObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranNamedConstantDef_create(void* pNameObj, void* pExprObj)
{
  return (Hnd(new AdtFortranNamedConstantDef(ObjAndRelease(pNameObj), ObjAndRelease(pExprObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranImplicitSpecList_create(void* pImplicitSpecObj)
{
  return (Hnd(new AdtFortranImplicitSpecList(ObjAndRelease(pImplicitSpecObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranImplicitSpec_create(void* pTypeSpecObj, void* pImplObj)
{
  return (Hnd(new AdtFortranImplicitSpec(ObjAndRelease(pTypeSpecObj), ObjAndRelease(pImplObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSectionSubscriptList_create(void* pSectionSubscriptObj)
{
  return (Hnd(new AdtFortranSectionSubscriptList(ObjAndRelease(pSectionSubscriptObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSectionSubscript_create(void* pExprObj, void* pSubscriptTripletObj)
{
  return (Hnd(new AdtFortranSectionSubscript(ObjAndRelease(pExprObj), ObjAndRelease(pSubscriptTripletObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSubscriptTriplet_create(int nCase, void* pExprObj, void* pExpr2Obj, void* pExpr3Obj)
{
  return (Hnd(new AdtFortranSubscriptTriplet(nCase, ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj), ObjAndRelease(pExpr3Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranPrimary_create(void* pNameObj, void* pSconObj, void* pIconObj, void* pRconObj, void* pExprObj, void* pExpr2Obj, void* pSectionSubscriptListObj, int nIsTrue, int nIsBracket)
{
  return (Hnd(new AdtFortranPrimary(ObjAndRelease(pNameObj), ObjAndRelease(pSconObj), ObjAndRelease(pIconObj), ObjAndRelease(pRconObj), ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj), ObjAndRelease(pSectionSubscriptListObj), nIsTrue != 0, nIsBracket != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranMultOperand_create(void* pPrimaryObj, void* pMultOperandObj)
{
  return (Hnd(new AdtFortranMultOperand(ObjAndRelease(pPrimaryObj), ObjAndRelease(pMultOperandObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranAddOperand_create(void* pMultOperandObj, void* pAddOperandObj, int nMultiply)
{
  return (Hnd(new AdtFortranAddOperand(ObjAndRelease(pMultOperandObj), ObjAndRelease(pAddOperandObj), nMultiply != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranLevel2Expr_create(void* pAddOperandObj, void* pLevel2ExprObj, int nSign, int nHasOp)
{
  return (Hnd(new AdtFortranLevel2Expr(ObjAndRelease(pAddOperandObj), ObjAndRelease(pLevel2ExprObj), nSign != 0, nHasOp != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranLevel4Expr_create(void* pLevel2ExprObj, void* pRelOpObj, void* pLevel2Expr2Obj)
{
  return (Hnd(new AdtFortranLevel4Expr(ObjAndRelease(pLevel2ExprObj), ObjAndRelease(pRelOpObj), ObjAndRelease(pLevel2Expr2Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranAndOperand_create(void* pLevel4ExprObj, int nNot)
{
  return (Hnd(new AdtFortranAndOperand(ObjAndRelease(pLevel4ExprObj), nNot != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranOrOperand_create(void* pAndOperandObj, void* pOrOperandObj)
{
  return (Hnd(new AdtFortranOrOperand(ObjAndRelease(pAndOperandObj), ObjAndRelease(pOrOperandObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEquivOperand_create(void* pOrOperandObj, void* pEquivOperandObj)
{
  return (Hnd(new AdtFortranEquivOperand(ObjAndRelease(pOrOperandObj), ObjAndRelease(pEquivOperandObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranExpr_create(void* pEquivOperandObj, void* pExprObj, int nIsEquivalent)
{
  return (Hnd(new AdtFortranExpr(ObjAndRelease(pEquivOperandObj), ObjAndRelease(pExprObj), nIsEquivalent != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSFExprList_create(void* pSFExprListObj, void* pExprObj, void* pExpr2Obj)
{
  return (Hnd(new AdtFortranSFExprList(ObjAndRelease(pSFExprListObj), ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranAssignmentStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj, void* pSFExprListObj, void* pSectionSubscriptListObj)
{
  return (Hnd(new AdtFortranAssignmentStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj), ObjAndRelease(pExprObj), ObjAndRelease(pSFExprListObj), ObjAndRelease(pSectionSubscriptListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereStmt_create(void* pLblDefObj, void* pExprObj, void* pAssignmentStmtObj)
{
  return (Hnd(new AdtFortranWhereStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pAssignmentStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereConstruct_create(void* pWhereConstructStmtObj, void* pWhereRangeObj)
{
  return (Hnd(new AdtFortranWhereConstruct(ObjAndRelease(pWhereConstructStmtObj), ObjAndRelease(pWhereRangeObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereRange_create(void* pWhereBodyConstructBlockObj, void* pElsewhereConstructObj, void* pMaskedElsewhereConstructObj, void* pEndWhereStmtObj)
{
  return (Hnd(new AdtFortranWhereRange(ObjAndRelease(pWhereBodyConstructBlockObj), ObjAndRelease(pElsewhereConstructObj), ObjAndRelease(pMaskedElsewhereConstructObj), ObjAndRelease(pEndWhereStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranMaskedElsewhereConstruct_create(void* pMaskedElsewhereStmtObj, void* pWhereRangeObj)
{
  return (Hnd(new AdtFortranMaskedElsewhereConstruct(ObjAndRelease(pMaskedElsewhereStmtObj), ObjAndRelease(pWhereRangeObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElsewhereConstruct_create(void* pElsewhereStmtObj, void* pElsewherePartObj)
{
  return (Hnd(new AdtFortranElsewhereConstruct(ObjAndRelease(pElsewhereStmtObj), ObjAndRelease(pElsewherePartObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElsewherePart_create(void* pEndWhereStmtObj, void* pWhereBodyConstructBlockObj)
{
  return (Hnd(new AdtFortranElsewherePart(ObjAndRelease(pEndWhereStmtObj), ObjAndRelease(pWhereBodyConstructBlockObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereBodyConstructBlock_create(void* pWhereBodyConstructObj)
{
  return (Hnd(new AdtFortranWhereBodyConstructBlock(ObjAndRelease(pWhereBodyConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereConstructStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj)
{
  return (Hnd(new AdtFortranWhereConstructStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj), ObjAndRelease(pExprObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranWhereBodyConstruct_create(void* pAssignmentStmtObj, void* pWhereStmtObj, void* pWhereConstructObj)
{
  return (Hnd(new AdtFortranWhereBodyConstruct(ObjAndRelease(pAssignmentStmtObj), ObjAndRelease(pWhereStmtObj), ObjAndRelease(pWhereConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranMaskedElsewhereStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj)
{
  return (Hnd(new AdtFortranMaskedElsewhereStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElsewhereStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranElsewhereStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndWhereStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranEndWhereStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIfConstruct_create(void* pIfThenStmtObj, void* pThenPartObj)
{
  return (Hnd(new AdtFortranIfConstruct(ObjAndRelease(pIfThenStmtObj), ObjAndRelease(pThenPartObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranThenPart_create(void* pEndIfStmtObj, void* pConditionalBodyObj, void* pElseIfConstructObj, void* pElseConstructObj)
{
  return (Hnd(new AdtFortranThenPart(ObjAndRelease(pEndIfStmtObj), ObjAndRelease(pConditionalBodyObj), ObjAndRelease(pElseIfConstructObj), ObjAndRelease(pElseConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElseIfConstruct_create(void* pElseIfStmtObj, void* pThenPartObj)
{
  return (Hnd(new AdtFortranElseIfConstruct(ObjAndRelease(pElseIfStmtObj), ObjAndRelease(pThenPartObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElseConstruct_create(void* pElseStmtObj, void* pElsePartObj)
{
  return (Hnd(new AdtFortranElseConstruct(ObjAndRelease(pElseStmtObj), ObjAndRelease(pElsePartObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElsePart_create(void* pEndIfStmtObj, void* pConditionalBodyObj)
{
  return (Hnd(new AdtFortranElsePart(ObjAndRelease(pEndIfStmtObj), ObjAndRelease(pConditionalBodyObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranConditionalBody_create(void* pExecutableConstructObj)
{
  return (Hnd(new AdtFortranConditionalBody(ObjAndRelease(pExecutableConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIfThenStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj)
{
  return (Hnd(new AdtFortranIfThenStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElseIfStmt_create(void* pLblDefObj, void* pExprObj, void* pNameObj)
{
  return (Hnd(new AdtFortranElseIfStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranElseStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranElseStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndIfStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranEndIfStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIfStmt_create(void* pLblDefObj, void* pExprObj, void* pActionStmtObj)
{
  return (Hnd(new AdtFortranIfStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pActionStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseConstruct_create(void* pSelectCaseStmtObj, void* pSelectCaseBodyObj, void* pEndSelectStmtObj)
{
  return (Hnd(new AdtFortranCaseConstruct(ObjAndRelease(pSelectCaseStmtObj), ObjAndRelease(pSelectCaseBodyObj), ObjAndRelease(pEndSelectStmtObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSelectCaseBody_create(void* pCaseStmtObj, void* pSelectCaseBodyObj, void* pCaseBodyConstructObj)
{
  return (Hnd(new AdtFortranSelectCaseBody(ObjAndRelease(pCaseStmtObj), ObjAndRelease(pSelectCaseBodyObj), ObjAndRelease(pCaseBodyConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseBodyConstruct_create(void* pCaseStmtObj, void* pExecutableConstructObj)
{
  return (Hnd(new AdtFortranCaseBodyConstruct(ObjAndRelease(pCaseStmtObj), ObjAndRelease(pExecutableConstructObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSelectCaseStmt_create(void* pLblDefObj, void* pNameObj, void* pExprObj)
{
  return (Hnd(new AdtFortranSelectCaseStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj), ObjAndRelease(pExprObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseStmt_create(void* pLblDefObj, void* pCaseSelectorObj, void* pNameObj)
{
  return (Hnd(new AdtFortranCaseStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pCaseSelectorObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndSelectStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranEndSelectStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseSelector_create(void* pCaseValueRangeListObj)
{
  return (Hnd(new AdtFortranCaseSelector(ObjAndRelease(pCaseValueRangeListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseValueRangeList_create(void* pCaseValueRangeObj)
{
  return (Hnd(new AdtFortranCaseValueRangeList(ObjAndRelease(pCaseValueRangeObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCaseValueRange_create(void* pExprObj, void* pExpr2Obj, int nHasColon)
{
  return (Hnd(new AdtFortranCaseValueRange(ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj), nHasColon != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranDoConstruct_create(void* pLblDefObj, void* pLblRefObj, void* pLoopControlObj, void* pNameObj, void* pConditionalBodyObj, void* pEndDoStmtObj, int nHasComma)
{
  return (Hnd(new AdtFortranDoConstruct(ObjAndRelease(pLblDefObj), ObjAndRelease(pLblRefObj), ObjAndRelease(pLoopControlObj), ObjAndRelease(pNameObj), ObjAndRelease(pConditionalBodyObj), ObjAndRelease(pEndDoStmtObj), nHasComma != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranLoopControl_create(void* pNameObj, void* pExprObj, void* pExpr2Obj, void* pExpr3Obj)
{
  return (Hnd(new AdtFortranLoopControl(ObjAndRelease(pNameObj), ObjAndRelease(pExprObj), ObjAndRelease(pExpr2Obj), ObjAndRelease(pExpr3Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndDoStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranEndDoStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCycleStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranCycleStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranExitStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranExitStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranGotoStmt_create(void* pLblDefObj, void* pLblRefObj)
{
  return (Hnd(new AdtFortranGotoStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pLblRefObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranArithmeticIfStmt_create(void* pLblDefObj, void* pExprObj, void* pLblRefObj, void* pLblRef2Obj, void* pLblRef3Obj)
{
  return (Hnd(new AdtFortranArithmeticIfStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj), ObjAndRelease(pLblRefObj), ObjAndRelease(pLblRef2Obj), ObjAndRelease(pLblRef3Obj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranContinueStmt_create(void* pLblDefObj)
{
  return (Hnd(new AdtFortranContinueStmt(ObjAndRelease(pLblDefObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranModuleStmt_create(void* pLblDefObj, void* pModuleNameObj)
{
  return (Hnd(new AdtFortranModuleStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pModuleNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndModuleStmt_create(void* pLblDefObj, void* pModuleNameObj)
{
  return (Hnd(new AdtFortranEndModuleStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pModuleNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranUseStmt_create(void* pLblDefObj, void* pNameObj)
{
  return (Hnd(new AdtFortranUseStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIntentStmt_create(void* pLblDefObj, void* pIntentSpecObj, void* pNameListObj, int nHasColonColon)
{
  return (Hnd(new AdtFortranIntentStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pIntentSpecObj), ObjAndRelease(pNameListObj), nHasColonColon != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIntentSpec_create(int nIntentSpec)
{
  return (Hnd(new AdtFortranIntentSpec(nIntentSpec), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIntrinsicStmt_create(void* pLblDefObj, void* pNameListObj)
{
  return (Hnd(new AdtFortranIntrinsicStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranExternalStmt_create(void* pLblDefObj, void* pNameListObj, int nHasColon)
{
  return (Hnd(new AdtFortranExternalStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameListObj), nHasColon != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranCallStmt_create(void* pLblDefObj, void* pNameObj, void* pSectionSubscriptListObj)
{
  return (Hnd(new AdtFortranCallStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pNameObj), ObjAndRelease(pSectionSubscriptListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranFunctionStmt_create(void* pLblDefObj, void* pTypeSpecObj, void* pFunctionNameObj, void* pParameterListObj, int nEmptyParameterList, int nRecursive, void* pResultNameObj)
{
  return (Hnd(new AdtFortranFunctionStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pTypeSpecObj), ObjAndRelease(pFunctionNameObj), ObjAndRelease(pParameterListObj), nEmptyParameterList != 0, nRecursive != 0, ObjAndRelease(pResultNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranLblRef_create(const char* pIcon)
{
  return (Hnd(new AdtFortranLblRef(pIcon), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranName_create(const char* pIdent)
{
  return (Hnd(new AdtFortranName(pIdent), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranNameList_create(void* pNameObj)
{
  return (Hnd(new AdtFortranNameList(ObjAndRelease(pNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndFunctionStmt_create(void* pLblDefObj, void* pFunctionNameObj)
{
  return (Hnd(new AdtFortranEndFunctionStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pFunctionNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranSubroutineStmt_create(void* pLblDefObj, void* pSubroutineNameObj, void* pParameterListObj, int nEmptyParameterList, int nRecursive)
{
  return (Hnd(new AdtFortranSubroutineStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pSubroutineNameObj), ObjAndRelease(pParameterListObj), nEmptyParameterList != 0, nRecursive != 0), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranEndSubroutineStmt_create(void* pLblDefObj, void* pSubroutineNameObj)
{
  return (Hnd(new AdtFortranEndSubroutineStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pSubroutineNameObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranReturnStmt_create(void* pLblDefObj, void* pExprObj)
{
  return (Hnd(new AdtFortranReturnStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pExprObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranLblDef_create(void* pIconObj)
{
  return (Hnd(new AdtFortranLblDef(ObjAndRelease(pIconObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranImplicitStmt_create(void* pLblDefObj, void* pImplicitSpecListObj)
{
  return (Hnd(new AdtFortranImplicitStmt(ObjAndRelease(pLblDefObj), ObjAndRelease(pImplicitSpecListObj)), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranIcon_create(const char* pIcon)
{
  return (Hnd(new AdtFortranIcon(pIcon), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranRcon_create(const char* pRcon)
{
  return (Hnd(new AdtFortranRcon(pRcon), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranScon_create(const char* pScon)
{
  return (Hnd(new AdtFortranScon(pScon), yyFortran_lineNumber(), yyFortran_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtFortranImpl_create(const char* pImpl)
{
  return (Hnd(new AdtFortranImpl(pImpl), yyFortran_lineNumber(), yyFortran_fileName()));
}


//  ----------------------------------------------------------------------------
//  AdtFortranSliceLoopVar method implementations
//  ----------------------------------------------------------------------------
AdtFortranSliceLoopVar::AdtFortranSliceLoopVar()
 : Name(),
   LowerDim(),
   UpperDim()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtFortranSliceLoopVar::AdtFortranSliceLoopVar(const AdtFortranSliceLoopVar& rCopy)
 : Name(rCopy.Name),
   LowerDim(rCopy.LowerDim),
   UpperDim(rCopy.UpperDim)
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

AdtFortranSliceLoopVar::~AdtFortranSliceLoopVar()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

bool AdtFortranSliceLoopVar::initialise(const char* pName,
                                        const char* pLowerDim,
                                        const char* pUpperDim)
{
  bool bInitialised = false;

  if ((pName      != 0) &&
      (pLowerDim  != 0) &&
      (pUpperDim  != 0))
  {
    Name          = pName;
    LowerDim      = pLowerDim;
    UpperDim      = pUpperDim;
    bInitialised  = true;
  }

  return (bInitialised);
}


//  ----------------------------------------------------------------------------
//  AdtFortranSliceLoopVars method implementations
//  ----------------------------------------------------------------------------
AdtFortranSliceLoopVars::AdtFortranSliceLoopVars(int nNumberOfIndices)
{
  NumberOfIndices = 0;
  SliceLoopVars   = 0;

  if (nNumberOfIndices > 0)
  {
    NumberOfIndices = nNumberOfIndices;
    SliceLoopVars   = new AdtFortranSliceLoopVar[NumberOfIndices];
  }
}

//  ----------------------------------------------------------------------------

AdtFortranSliceLoopVars::AdtFortranSliceLoopVars(const AdtFortranSliceLoopVars& rCopy)
{
  NumberOfIndices = 0;
  SliceLoopVars   = 0;

  if ((rCopy.NumberOfIndices > 0) && (rCopy.SliceLoopVars != 0))
  {
    NumberOfIndices = rCopy.NumberOfIndices;
    SliceLoopVars   = new AdtFortranSliceLoopVar[NumberOfIndices];

    for (int cn = 0 ; cn < NumberOfIndices ; cn++)
    {
      const AdtFortranSliceLoopVar& rSliceLoopVar = rCopy.sliceLoopVar(cn);

      initialise(cn,
                 rSliceLoopVar.name(),
                 rSliceLoopVar.lowerDim(),
                 rSliceLoopVar.upperDim());
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranSliceLoopVars::~AdtFortranSliceLoopVars()
{
  if (SliceLoopVars != 0)
  {
    delete [] SliceLoopVars;
  }
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscriptList* AdtFortranSliceLoopVars::createSectionSubscriptList(const AdtFortranVariableInfo& rVarInfo,
                                                                                    const char* pParentName,
                                                                                    AdtFortranSectionSubscriptList* pParentSubscriptList) const
{
  AdtFortranSectionSubscriptList* pSubscriptList = new AdtFortranSectionSubscriptList(0);

  if (pSubscriptList != 0)
  {
    if ((pParentSubscriptList != 0) && (pParentName != 0) && rVarInfo.hasVariable(pParentName))
    {
      AdtParserPtrListConstIter Iter;
      const AdtParserPtrList&   rList = pParentSubscriptList->objList();
      int                       cn    = 0;
      int                       cm    = 0;

      for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
      {
        AdtParser*                    pParentObj        = *Iter;
        AdtFortranSectionSubscript*   pParentSubscript  = (AdtFortranSectionSubscript*)(pParentObj);
        AdtFortranSectionSubscript*   pSubscript        = 0;

        if (pParentSubscript != 0)
        {
          AdtFortranSubscriptTriplet* pSubscriptTriplet = (AdtFortranSubscriptTriplet*)pParentSubscript->findDescendant("SubscriptTriplet");

          // Does this subcript contain a slice?
          if (pSubscriptTriplet != 0)
          {
            // It does so we need to dereference it
            string                        sLowerDim;
            string                        sExpression;
            const AdtFortranSliceLoopVar& rSliceLoopVar = sliceLoopVar(cn);
            AdtFortranExpr*               pExpr         = 0;

            rVarInfo.lowerDimension(pParentName, cm, sLowerDim);
            pSubscriptTriplet->lowerIndex(sLowerDim);

            sExpression = rSliceLoopVar.name() + " - (" + rSliceLoopVar.lowerDim() + ") + " + sLowerDim;
            pExpr       = AdtFortranBase::createSimpleExpression(sExpression);
            pSubscript  = new AdtFortranSectionSubscript(pExpr, 0);

            UtlReleaseReference(pExpr);
            cn++;
          }
          else
          {
            // It doesn't so create a literal copy of it and put it in our subscript list.
            pSubscript = (AdtFortranSectionSubscript*)pParentSubscript->copy();
          }

          pSubscriptList->add(pSubscript);

          UtlReleaseReference(pSubscript);
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranSliceLoopVars::createSectionSubscriptList "
                   "failure on line %d in file %s\nContext line %d, file %s\n",
                   pParentSubscriptList->lineNumber(),
                   pParentSubscriptList->fileName(),
                   __LINE__,
                   __FILE__);
          FAIL();
          AdtExit(-1);
        }

        cm++;
      }
    }
    else
    {
      for (int cn = 0 ; cn < NumberOfIndices ; cn++)
      {
        const AdtFortranSliceLoopVar& rSliceLoopVar = sliceLoopVar(cn);
        AdtFortranExpr*               pExpr         = AdtFortranBase::createSimpleExpression(rSliceLoopVar.name());
        AdtFortranSectionSubscript*   pSubscript    = new AdtFortranSectionSubscript(pExpr, 0);

        pSubscriptList->add(pSubscript);

        UtlReleaseReference(pSubscript);
        UtlReleaseReference(pExpr);
      }
    }
  }

  return (pSubscriptList);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSliceLoopVars::initialise(int nIndex,
                                         const char* pName,
                                         const char* pLowerDim,
                                         const char* pUpperDim)
{
  bool bInitialised = false;

  if ((SliceLoopVars != 0) &&
      (nIndex        >= 0) &&
      (nIndex        < NumberOfIndices))
  {
    bInitialised = SliceLoopVars[nIndex].initialise(pName, pLowerDim, pUpperDim);
  }

  return (bInitialised);
}


//  ----------------------------------------------------------------------------
//  AdtFortranVariableInfo method implementations
//  ----------------------------------------------------------------------------
void AdtFortranVariableInfo::extractTypeDefInfo(const AdtFortranTypeDeclarationStmt* pTypeDecl, bool bIsArguments)
{
  if (pTypeDecl != 0)
  {
    const AdtFortranTypeSpec*       pTypeSpec       = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");
    const AdtFortranAttrSpecSeq*    pAttrSpecSeq    = (const AdtFortranAttrSpecSeq*)pTypeDecl->findDescendant("AttrSpecSeq");
    const AdtFortranEntityDeclList* pEntityDeclList = (const AdtFortranEntityDeclList*)pTypeDecl->findDescendant("EntityDeclList");

    if ((pTypeSpec != 0) && (pEntityDeclList != 0))
    {
      const AdtFortranShapeSpecList*  pGlobalShapeSpecList = 0;
      string                          sIntent;

      if (pAttrSpecSeq != 0)
      {
        // Extract the dimension from the attribute list if any.
        const AdtParserPtrList&   AttrList = pAttrSpecSeq->objList();
        AdtParserPtrListConstIter AttrIter;

        for (AttrIter = AttrList.begin() ; AttrIter != AttrList.end() ; ++AttrIter)
        {
          const AdtFortranAttrSpec* pAttrSpec = (const AdtFortranAttrSpec*)(const AdtParser*)*AttrIter;

          if (pAttrSpec != 0)
          {
            if (bIsArguments)
            {
              const AdtFortranIntentSpec* pIntentSpec = (const AdtFortranIntentSpec*)pAttrSpec->findDescendant("IntentSpec");

              if (pIntentSpec != 0)
              {
                pIntentSpec->intent(sIntent);
              }
            }

            pGlobalShapeSpecList = (const AdtFortranShapeSpecList*)pAttrSpec->findDescendant("ShapeSpecList");

            if ((pGlobalShapeSpecList != 0) && (pGlobalShapeSpecList->listSize() > 0))
            {
              break;
            }
          }
        }
      }

      const AdtParserPtrList&   EntityList = pEntityDeclList->objList();
      AdtParserPtrListConstIter EntityIter;

      for (EntityIter = EntityList.begin() ; EntityIter != EntityList.end() ; ++EntityIter)
      {
        const AdtFortranEntityDecl* pEntityDecl = (const AdtFortranEntityDecl*)(const AdtParser*)*EntityIter;

        if (pEntityDecl != 0)
        {
          const AdtFortranName* pName = (const AdtFortranName*)pEntityDecl->findDescendant("Name");

          if (pName != 0)
          {
            AdtFile                         sStringFile;
            string                          sTypeName;
            const string&                   rVarName        = pName->name();
            const AdtFortranShapeSpecList*  pShapeSpecList  = (const AdtFortranShapeSpecList*)pEntityDecl->findDescendant("ShapeSpecList");

            sStringFile.open(sTypeName);
            pTypeSpec->writeFortran(sStringFile);
            sStringFile.close();

            VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName, sTypeName));

            if (bIsArguments)
            {
              ArgumentList.push_back(rVarName);

              if (sIntent.length() > 0)
              {
                VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "*", sIntent));
              }
            }

            if (pShapeSpecList == 0)
            {
              // If the variable has no explicit dimension use the dimensions in the attribute
              // list, if any
              pShapeSpecList = pGlobalShapeSpecList;
            }

            if (pShapeSpecList != 0)
            {
              const AdtParserPtrList&   ShapeList = pShapeSpecList->objList();
              AdtParserPtrListConstIter ShapeIter;
              int                       nDim        = 0;
              char                      sBuffer[16] = {0};

              for (ShapeIter = ShapeList.begin() ; ShapeIter != ShapeList.end() ; ++ShapeIter)
              {
                const AdtFortranShapeSpec*  pShapeSpec = (const AdtFortranShapeSpec*)(const AdtParser*)*ShapeIter;

                if (pShapeSpec != 0)
                {
                  const AdtFortranExpr* pExpr = (const AdtFortranExpr*)pShapeSpec->findDescendant("Expr");

                  if (pExpr != 0)
                  {
                    char                  sDim[16]  = {0};
                    const AdtFortranExpr* pExpr2    = (const AdtFortranExpr*)pShapeSpec->findDescendant("Expr2");
                    string                sExpr;

                    sStringFile.open(sExpr);
                    pExpr->writeFortran(sStringFile);
                    sStringFile.close();

                    ::sprintf(sDim, "%d", nDim);

                    if (pExpr2 != 0)
                    {
                      string                sExpr2;

                      sStringFile.open(sExpr2);
                      pExpr2->writeFortran(sStringFile);
                      sStringFile.close();

                      VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "|" + sDim, sExpr));
                      VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "||" + sDim, sExpr2));
                    }
                    else
                    {
                      VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "|" + sDim, "1"));
                      VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "||" + sDim, sExpr));
                    }
                  }
                }

                nDim++;
              }

              sprintf(sBuffer, "%zd", pShapeSpecList->objList().size());

              VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "#", sBuffer));
            }
            else
            {
              VariableInfoMap.insert(AdtStringByStringMap::value_type(rVarName + "#", "0"));
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::extractTypeDeclarations(const AdtParserPtrByStringMap& rTypeDeclMap, bool bIsArguments)
{
  AdtParserPtrByStringMapConstIter  TypeDeclIter;

  for (TypeDeclIter = rTypeDeclMap.begin() ; TypeDeclIter != rTypeDeclMap.end() ; ++TypeDeclIter)
  {
    const AdtParser*  pObj = (*TypeDeclIter).second;

    if (pObj->isType("AdtFortranTypeDeclarationStmt"))
    {
      const AdtFortranTypeDeclarationStmt* pTypeDecl = (const AdtFortranTypeDeclarationStmt*)pObj;

      extractTypeDefInfo(pTypeDecl, bIsArguments);
    }
    else
    {
      ::printf("FATAL ERROR: AdtFortranVariableInfo::extractTypeDeclarations "
               "failure on line %d in file %s\nContext line %d, file %s\n",
               pObj->lineNumber(),
               pObj->fileName(),
               __LINE__,
               __FILE__);
      FAIL();
      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::extractModuleTypeDeclarations(const AdtParser* pModuleObj)
{
  if (pModuleObj != 0)
  {
    AdtParserPtrList          TypeDeclStmtList;
    AdtParserPtrListConstIter DeclIter;

    pModuleObj->findObjects(TypeDeclStmtList, "AdtFortranTypeDeclarationStmt");

    //Step through all type declaration statments
    for (DeclIter = TypeDeclStmtList.begin() ; DeclIter != TypeDeclStmtList.end() ; ++DeclIter)
    {
      const AdtFortranTypeDeclarationStmt*  pTypeDecl = (const AdtFortranTypeDeclarationStmt*)(const AdtParser*)*DeclIter;

      extractTypeDefInfo(pTypeDecl, false);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::initialise(AdtParser* pCodeObj, const AdtParser* pModuleObj)
{
  VariableInfoMap.clear();

  //Use the root object to enumerate the module variable definitions
  AdtFortranExecutableProgram*  pRoot = AdtFortranBase::fortranRootObject();

  if (pCodeObj != 0)
  {
    pRoot = (AdtFortranExecutableProgram*)pCodeObj->findAscendantWithClass("AdtFortranExecutableProgram");

    //Search for the Function or Subroutine statement to get the declarations object
    AdtFortranFunctionSubprogram*   pFunctionSubprogram       = 0;
    AdtFortranDeclarations*         pDeclarations             = 0;

    if (pCodeObj->isType("AdtFortranFunctionSubprogram"))
    {
      pFunctionSubprogram = (AdtFortranFunctionSubprogram*)pCodeObj;
    }
    else
    {
      pFunctionSubprogram = (AdtFortranFunctionSubprogram*)pCodeObj->findAscendantWithClass("AdtFortranFunctionSubprogram");
    }

    if (pFunctionSubprogram != 0)
    {
      AdtFortranFunctionStmt* pFunctionStmt = (AdtFortranFunctionStmt*)pFunctionSubprogram->findDescendant("FunctionStmt");

      if (pFunctionStmt != 0)
      {
        pDeclarations = pFunctionStmt->declarations();
      }
    }
    else
    {
      AdtFortranSubroutineSubprogram* pSubroutineSubprogram = 0;

      if (pCodeObj->isType("AdtFortranSubroutineSubprogram"))
      {
        pSubroutineSubprogram = (AdtFortranSubroutineSubprogram*)pCodeObj;
      }
      else
      {
        pSubroutineSubprogram = (AdtFortranSubroutineSubprogram*)pCodeObj->findAscendantWithClass("AdtFortranSubroutineSubprogram");
      }

      if (pSubroutineSubprogram != 0)
      {
        AdtFortranSubroutineStmt* pSubroutineStmt = (AdtFortranSubroutineStmt*)pSubroutineSubprogram->findDescendant("SubroutineStmt");

        if (pSubroutineStmt != 0)
        {
          pDeclarations = pSubroutineStmt->declarations();
        }
      }
    }

    //Use the declarations object to enumerate the local variable definitions
    initialise(pDeclarations, false);
  }

  extractModuleTypeDeclarations(pModuleObj);
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::initialise(AdtParser* pCodeObj, const char* pModuleSuffix)
{
  const AdtParser*              pModuleObj  = 0; 
  AdtFortranExecutableProgram*  pRoot       = AdtFortranBase::fortranRootObject();

  if (pRoot != 0)
  {
    string  sModuleName("COMMON");

    if (pModuleSuffix != 0)
    {
      sModuleName += pModuleSuffix;
    }

    pModuleObj = pRoot->findObject("AdtFortranModule", sModuleName);
  }

  initialise(pCodeObj, pModuleObj);
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::initialise(const AdtFortranDeclarations* pDeclarations, bool bReset)
{
  if (bReset)
  {
    VariableInfoMap.clear();
    ArgumentList.clear();
  }

  if (pDeclarations != 0)
  {
    extractTypeDeclarations(pDeclarations->typeDeclarationMap(), false);
    extractTypeDeclarations(pDeclarations->parameterTypeDeclarationMap(), true);
  }
}

//  ----------------------------------------------------------------------------

AdtFortranVariableInfo::AdtFortranVariableInfo(AdtParser* pCodeObj, const char* pModuleSuffix)
 : VariableInfoMap(),
   ArgumentList()
{
  initialise(pCodeObj, pModuleSuffix);
}

//  ----------------------------------------------------------------------------

AdtFortranVariableInfo::AdtFortranVariableInfo(AdtParser* pCodeObj, const AdtParser* pModuleObj)
 : VariableInfoMap(),
   ArgumentList()
{
  initialise(pCodeObj, pModuleObj);
}

//  ----------------------------------------------------------------------------

AdtFortranVariableInfo::AdtFortranVariableInfo(const AdtFortranDeclarations* pDeclarations)
 : VariableInfoMap(),
   ArgumentList()
{
  initialise(pDeclarations, true);
}

//  ----------------------------------------------------------------------------

AdtFortranVariableInfo::AdtFortranVariableInfo(const AdtFortranVariableInfo& rCopy)
 : VariableInfoMap(rCopy.VariableInfoMap),
   ArgumentList(rCopy.ArgumentList)
{

}

//  ----------------------------------------------------------------------------

AdtFortranVariableInfo::~AdtFortranVariableInfo()
{

}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::hasVariable(const char* pVarName) const
{
  bool  bHasVariable = false;

  if (pVarName != 0)
  {
    bHasVariable = (VariableInfoMap.find(pVarName) != VariableInfoMap.end());
  }

  return (bHasVariable);
}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::variableType(const char* pVarName, string& rRetType) const
{
  bool  bDone = false;

  if (pVarName != 0)
  {
    AdtStringByStringMapConstIter Iter = VariableInfoMap.find(pVarName);

    if (Iter != VariableInfoMap.end())
    {
      rRetType  = (*Iter).second;
      bDone     = true;
    }
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::lowerDimension(const char* pVarName, int nDimension, string& rRetDim) const
{
  bool  bDone = false;

  if (pVarName != 0)
  {
    char    sBuffer[16] = {0};
    string  sKeyName(pVarName);

    ::sprintf(sBuffer, "|%d", nDimension);

    sKeyName += sBuffer;

    AdtStringByStringMapConstIter Iter = VariableInfoMap.find(sKeyName);

    if (Iter != VariableInfoMap.end())
    {
      rRetDim = (*Iter).second;
      bDone   = true;
    }
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::upperDimension(const char* pVarName, int nDimension, string& rRetDim) const
{
  bool  bDone = false;

  if (pVarName != 0)
  {
    char    sBuffer[16] = {0};
    string  sKeyName(pVarName);

    ::sprintf(sBuffer, "||%d", nDimension);

    sKeyName += sBuffer;

    AdtStringByStringMapConstIter Iter = VariableInfoMap.find(sKeyName);

    if (Iter != VariableInfoMap.end())
    {
      rRetDim = (*Iter).second;
      bDone   = true;
    }
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::intent(const char* pVarName, string& rRetIntent) const
{
  bool  bDone = false;

  rRetIntent.clear();

  if (pVarName != 0)
  {
    string  sKeyName(pVarName);

    sKeyName += "*";

    AdtStringByStringMapConstIter Iter = VariableInfoMap.find(sKeyName);

    if (Iter != VariableInfoMap.end())
    {
      rRetIntent = (*Iter).second;
      bDone      = true;
    }
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

int AdtFortranVariableInfo::numberOfDimensions(const char* pVarName) const
{
  int nNumDims = 0;

  if (pVarName != 0)
  {
    string  sKeyName(pVarName);

    sKeyName += "#";

    AdtStringByStringMapConstIter Iter = VariableInfoMap.find(sKeyName);

    if (Iter != VariableInfoMap.end())
    {
      const string& rNumDims = (*Iter).second;

      nNumDims = ::atoi(rNumDims);
    }
  }

  return (nNumDims);
}

//  ----------------------------------------------------------------------------

bool AdtFortranVariableInfo::buildVariableDeclaration(const char* pVarName, bool bWithIntent, string& rDeclaration) const
{
  string sType;
  bool   bFound = false;

  if (variableType(pVarName, sType))
  {
    string  sIntent;
    int     nDim = numberOfDimensions(pVarName);

    bFound = true;

    rDeclaration += sType;

    if (bWithIntent && intent(pVarName, sIntent))
    {
      rDeclaration += ", INTENT(";
      rDeclaration += sIntent;
      rDeclaration += ")";
    }

    rDeclaration += " :: ";
    rDeclaration += pVarName;
    
    if (nDim > 0)
    {
      rDeclaration += "(";

      for (int cn = 0 ; cn < nDim ; cn++)
      {
        string sLowerDim;
        string sUpperDim;

        if (cn > 0)
        {
          rDeclaration += ",";
        }

        lowerDimension(pVarName, cn, sLowerDim);
        upperDimension(pVarName, cn, sUpperDim);

        rDeclaration += sLowerDim + ":" + sUpperDim;
      }

      rDeclaration += ")";
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

void AdtFortranVariableInfo::dump() const
{
  ::printf("\n Variable Info Dump\n");

  AdtStringByStringMapConstIter Iter;

  for (Iter = VariableInfoMap.begin() ; Iter != VariableInfoMap.end() ; ++Iter)
  {
    ::printf("%s => %s\n", (*Iter).first.c_str(), (*Iter).second.c_str());
  }
}


//  ----------------------------------------------------------------------------
//  AdtFortranDeclarations method implementations
//  ----------------------------------------------------------------------------
void AdtFortranDeclarations::flush(AdtParserPtrByStringMap& rMap)
{
  AdtParserPtrByStringMapIter Iter;

  for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
  {
    AdtParser* pObj = (*Iter).second;

    UtlReleaseReference(pObj);
  }

  rMap.clear();
}

//  ----------------------------------------------------------------------------

void AdtFortranDeclarations::extractModuleTypeDeclarations(AdtParser* pBodyObj,
                                                           AdtParserPtrByStringMap& rMap)
{
  ASSERT(pBodyObj != 0);

  AdtFortranBase* pRootObj = (AdtFortranBase*)pBodyObj->findAscendantWithClass("AdtFortranExecutableProgram");

  if (pRootObj != 0)
  {
    AdtParserPtrListConstIter UseIter;
    AdtParserPtrList          rUseStmtList;

    //enumerate the use statements
    pBodyObj->findObjects(rUseStmtList,  "AdtFortranUseStmt");

    for (UseIter = rUseStmtList.begin() ; UseIter != rUseStmtList.end() ; ++UseIter)
    {
      AdtFortranUseStmt*  pUseStmtObj = (AdtFortranUseStmt*)((AdtParser*)*UseIter);

      if (pUseStmtObj != 0)
      {
        AdtFortranModule* pModule = (AdtFortranModule*)pRootObj->findObject("AdtFortranModule", pUseStmtObj->name());

        if (pModule != 0)
        {
          AdtParserPtrListConstIter Iter;
          AdtParserPtrList          rTypeDeclarationStmtList;
          AdtParserPtrList          rParameterStmtList;
          AdtParserPtrList          rDimensionStmtList;

          //enumerate the type declaration statements
          pModule->findObjects(rTypeDeclarationStmtList,  "AdtFortranTypeDeclarationStmt");

          for (Iter = rTypeDeclarationStmtList.begin() ; Iter != rTypeDeclarationStmtList.end() ; ++Iter)
          {
            AdtFortranTypeDeclarationStmt* pTypeDeclObj = (AdtFortranTypeDeclarationStmt*)((AdtParser*)*Iter);

            if (pTypeDeclObj != 0)
            {
              pTypeDeclObj->enumerateDescendantMap(rMap, "EntityDeclList");
            }
          }

          //enumerate the parameter statements (constant definitions)
          pModule->findObjects(rParameterStmtList,  "AdtFortranParameterStmt");

          for (Iter = rParameterStmtList.begin() ; Iter != rParameterStmtList.end() ; ++Iter)
          {
            AdtFortranParameterStmt* pParameterStmtObj = (AdtFortranParameterStmt*)((AdtParser*)*Iter);

            if (pParameterStmtObj != 0)
            {
              pParameterStmtObj->enumerateDescendantMap(rMap, "NamedConstantDefList");
            }
          }

          //enumerate the dimension statements
          pModule->findObjects(rDimensionStmtList,  "AdtFortranDimensionStmt");

          for (Iter = rDimensionStmtList.begin() ; Iter != rDimensionStmtList.end() ; ++Iter)
          {
            AdtFortranDimensionStmt* pDimensionStmtObj = (AdtFortranDimensionStmt*)((AdtParser*)*Iter);

            if (pDimensionStmtObj != 0)
            {
              pDimensionStmtObj->enumerateDescendantMap(rMap, "ArrayDeclaratorList");
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranDeclarations::addVariableNames(AdtIntByStringMap& rVariablesMap,
                                              const AdtParserPtrByStringMap& rObjsMap) const
{
  AdtParserPtrByStringMapConstIter  Iter;

  for (Iter = rObjsMap.begin() ; Iter != rObjsMap.end() ; ++Iter)
  {
    rVariablesMap[(*Iter).first] = 0;
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranDeclarations::extractDeclarations(AdtParser* pParentObj,
                                                 AdtParser* pBodyObj,
                                                 AdtParser* pParameterListObj,
                                                 AdtParserPtrByStringMap* pFunctionMap)
{
  bool bExtracted = false;

  if ((pBodyObj != 0) && pBodyObj->isType("AdtFortranBody"))
  {
    AdtParserPtrListConstIter Iter;
    AdtParserPtrList          TypeDeclarationStmtList;
    AdtParserPtrByStringMap   ModuleTypeDeclarationMap;

    flush(TypeDeclarationMap);
    flush(ParameterTypeDeclarationMap);
    flush(FunctionTypeDeclarationMap);

    ParameterList.clear();
    ParameterStmtList.clear();
    DimensionStmtList.clear();

    //enumerate the module type declaration statements
    extractModuleTypeDeclarations(pBodyObj, ModuleTypeDeclarationMap);

    //enumerate the type declaration statements
    pBodyObj->findObjects(TypeDeclarationStmtList,  "AdtFortranTypeDeclarationStmt");

    //enumerate the parameter statements (constant definitions)
    pBodyObj->findObjects(ParameterStmtList,  "AdtFortranParameterStmt");

    for (Iter = ParameterStmtList.begin() ; Iter != ParameterStmtList.end() ; ++Iter)
    {
      AdtFortranParameterStmt* pParameterStmtObj = (AdtFortranParameterStmt*)((AdtParser*)*Iter);

      if (pParameterStmtObj != 0)
      {
        pParameterStmtObj->enumerateDescendantMap(ModuleTypeDeclarationMap, "NamedConstantDefList");
      }
    }

    //enumerate the dimension statements
    pBodyObj->findObjects(DimensionStmtList,  "AdtFortranDimensionStmt");

    for (Iter = DimensionStmtList.begin() ; Iter != DimensionStmtList.end() ; ++Iter)
    {
      AdtFortranDimensionStmt* pDimensionStmtObj = (AdtFortranDimensionStmt*)((AdtParser*)*Iter);

      if (pDimensionStmtObj != 0)
      {
        pDimensionStmtObj->enumerateDescendantMap(ModuleTypeDeclarationMap, "ArrayDeclaratorList");
      }
    }

    //Split the type declarations up to one declaration per variable
    for (Iter = TypeDeclarationStmtList.begin() ; Iter != TypeDeclarationStmtList.end() ; ++Iter)
    {
      AdtFortranTypeDeclarationStmt* pTypeDeclObj = (AdtFortranTypeDeclarationStmt*)((AdtParser*)*Iter);

      if (pTypeDeclObj != 0)
      {
        pTypeDeclObj->splitAndEnumerate(pParentObj, TypeDeclarationMap);
      }
    }

    if ((pParameterListObj != 0) && pParameterListObj->isType("AdtFortranNameList"))
    {
      AdtParserPtrListConstIter  Iter;

      //Enumerate the parameter list
      pParameterListObj->enumerate(ParameterList);

      //Remove the parameter type declarations from the TypeDeclarationMap and
      //put them into the ParameterTypeDeclarationMap
      for (Iter = ParameterList.begin() ; Iter != ParameterList.end() ; ++Iter)
      {
        AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

        if (pObj != 0)
        {
          AdtParserPtrByStringMapIter  MapIter = TypeDeclarationMap.find(pObj->name());

          if (MapIter != TypeDeclarationMap.end())
          {
            AdtParser* pParameterTypeDeclObj = (*MapIter).second;

            ParameterTypeDeclarationMap.insert(AdtParserPtrByStringMap::value_type(pObj->name(), pParameterTypeDeclObj));
            TypeDeclarationMap.erase(MapIter);
          }
        }
      }
    }

    AdtParserPtrList          IntentStmtList;
    AdtParserPtrByStringMap   ConstVarMap;
    AdtParserPtrByStringMap   OutVarMap;
    AdtParserPtrByStringMap   NonConstVarMap;

    // enumerate the intent statements and set the appropriate flag in
    // AdtFortranTypeDeclarationStmt in ParameterTypeDeclarationMap to indicate
    // whether the parameter is constant or not. Only map IN to const and
    // ignore the other cases.
    pBodyObj->findObjects(IntentStmtList,  "AdtFortranIntentStmt");

    for (Iter = IntentStmtList.begin() ; Iter != IntentStmtList.end() ; ++Iter)
    {
      AdtFortranIntentStmt* pIntentStmtObj = (AdtFortranIntentStmt*)((AdtParser*)*Iter);

      if (pIntentStmtObj != 0)
      {
        switch (pIntentStmtObj->intent())
        {
          case ForIntent_IN:
          {
            pIntentStmtObj->enumerateDescendantMap(ConstVarMap, "NameList");
            break;
          }

          case ForIntent_OUT:
          {
            pIntentStmtObj->enumerateDescendantMap(OutVarMap, "NameList");
            break;
          }

          case ForIntent_INOUT:
          case ForIntent_IN_OUT:
          default:
          {
            pIntentStmtObj->enumerateDescendantMap(NonConstVarMap, "NameList");
            break;
          }
        }
      }
    }

    for (Iter = ParameterList.begin() ; Iter != ParameterList.end() ; ++Iter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pObj != 0)
      {
        AdtParserPtrByStringMapConstIter  Iter                  = ParameterTypeDeclarationMap.find(pObj->name());
        AdtFortranTypeDeclarationStmt*    pParameterTypeDeclObj = 0;

        if (Iter != ParameterTypeDeclarationMap.end())
        {
          pParameterTypeDeclObj = (AdtFortranTypeDeclarationStmt*)((AdtParser*)((*Iter).second));
        }

        if ((pParameterTypeDeclObj != 0) && !pParameterTypeDeclObj->hasIntent())
        {
          if ((ConstVarMap.find(pObj->name()) != ConstVarMap.end()) && (pParameterTypeDeclObj != 0))
          {
            pParameterTypeDeclObj->isConst(true, false);
          }
          else if ((OutVarMap.find(pObj->name()) != OutVarMap.end()) && (pParameterTypeDeclObj != 0))
          {
            pParameterTypeDeclObj->isConst(false, true);
          }
          else if ((NonConstVarMap.find(pObj->name()) != NonConstVarMap.end()) && (pParameterTypeDeclObj != 0))
          {
            pParameterTypeDeclObj->isConst(false, false);
          }
          else if (pParameterTypeDeclObj != 0)
          {
            // Make anything unspecified non-const
            pParameterTypeDeclObj->isConst(false, false);
          }
        }
      }
    }

    //Enumerate all functions and remove any variable declarations in
    //TypeDeclarationMap that correspond to functions. The assumption here is that
    //the variable declaration is a declaration of a function reference external
    //to this function. If a local variable uses the same name as an external
    //function then this approach fails to correctly identify it as a variable.
    //The other assumption here is that the entire file source is compiled.
    AdtParserPtrByStringMap     FunctionMap;
    AdtParserPtrByStringMapIter DeclIter;
    AdtParserPtrListIter        FunctionIter;
    AdtParserPtrByStringMapIter RemoveIter;
    AdtFortranBase*             pRootObj = (AdtFortranBase*)pBodyObj->findAscendantWithClass("AdtFortranExecutableProgram");

    if ((pFunctionMap == 0) && (pRootObj != 0))
    {
      AdtParserPtrList  FunctionList;

      pRootObj->findObjects(FunctionList, "AdtFortranFunctionStmt");
      pRootObj->listToMap(FunctionMap, FunctionList);

      pFunctionMap = &FunctionMap;
    }

    ASSERT(pFunctionMap != 0);

    for (DeclIter = TypeDeclarationMap.begin() ; DeclIter != TypeDeclarationMap.end() ; ++DeclIter)
    {
      const string& rKey = (*DeclIter).first;
      AdtParser*    pObj = (*DeclIter).second;

      if ((pFunctionMap->find(rKey) != pFunctionMap->end()) && (pObj != 0))
      {
        FunctionTypeDeclarationMap.insert(AdtParserPtrByStringMap::value_type(rKey, pObj));
      }
    }

    //This looks odd but I need to do it this way because there is something
    //not quite right in the implementation of map that corrupts it if you
    //attempt removing objects whilst iterating at the same time.
    for (RemoveIter = FunctionTypeDeclarationMap.begin() ; RemoveIter != FunctionTypeDeclarationMap.end() ; ++RemoveIter)
    {
      const string&               rKey    = (*RemoveIter).first;
      AdtParserPtrByStringMapIter ObjIter = TypeDeclarationMap.find(rKey);

      TypeDeclarationMap.erase(rKey);
    }

    // Build variables map
    VariablesMap.clear();

    addVariableNames(VariablesMap, TypeDeclarationMap);
    addVariableNames(VariablesMap, ParameterTypeDeclarationMap);
    addVariableNames(VariablesMap, ModuleTypeDeclarationMap);

    //Flag Primary objects as being variables when they actually are
    checkIsVariable(pBodyObj);

    bExtracted = true;
  }

  return (bExtracted);
}

//  ----------------------------------------------------------------------------

AdtFortranDeclarations::AdtFortranDeclarations(AdtParser* pParentObj,
                                               AdtParser* pBodyObj,
                                               AdtParser* pParameterListObj,
                                               AdtParserPtrByStringMap* pFunctionMap)
 : UtlReferenceCount(),
   VariablesMap(),
   TypeDeclarationMap(),
   ParameterTypeDeclarationMap(),
   FunctionTypeDeclarationMap(),
   ParameterList(),
   ParameterStmtList(),
   DimensionStmtList()
{
  extractDeclarations(pParentObj, pBodyObj, pParameterListObj, pFunctionMap);
}

//  ----------------------------------------------------------------------------

AdtFortranDeclarations::AdtFortranDeclarations(const AdtFortranDeclarations& rCopy)
 : UtlReferenceCount(rCopy),
   VariablesMap(),
   TypeDeclarationMap(),
   ParameterTypeDeclarationMap(),
   FunctionTypeDeclarationMap(),
   ParameterList(),
   ParameterStmtList(),
   DimensionStmtList()
{

}

//  ----------------------------------------------------------------------------

AdtFortranDeclarations::~AdtFortranDeclarations()
{
  flush(TypeDeclarationMap);
  flush(ParameterTypeDeclarationMap);
  flush(FunctionTypeDeclarationMap);

  VariablesMap.clear();
  ParameterList.clear();
  ParameterStmtList.clear();
  DimensionStmtList.clear();
}

//  ----------------------------------------------------------------------------

void AdtFortranDeclarations::dump(AdtFile* pFile) const
{
  // Dump the keys of VariablesMap for debugging purposes
  if (pFile != 0)
  {
    pFile->incrementIndent();
    pFile->homeline();

    AdtIntByStringMapConstIter  Iter;

    for (Iter = VariablesMap.begin() ; Iter != VariablesMap.end() ; ++Iter)
    {
      pFile->write((*Iter).first);
      pFile->newline();
    }

    pFile->decrementIndent();
    pFile->homeline();
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranDeclarations::hasVarDeclarations() const
{
  bool bHasVarDeclarations = ((DimensionStmtList.size() > 0) || (TypeDeclarationMap.size() > 0));

  return (bHasVarDeclarations);
}

//  ----------------------------------------------------------------------------

bool AdtFortranDeclarations::isLocal(const char* pVarName) const
{
  bool bIsLocal = false;

  if (pVarName != 0)
  {
    AdtParserPtrByStringMapConstIter  Iter = TypeDeclarationMap.find(pVarName);

    bIsLocal = (Iter != TypeDeclarationMap.end());
  }

  return (bIsLocal);
}

//  ----------------------------------------------------------------------------

bool AdtFortranDeclarations::remove(const char* pVarName)
{
  bool bRemoved = false;

  if (pVarName != 0)
  {
    AdtParserPtrByStringMapConstIter  Iter = TypeDeclarationMap.find(pVarName);

    if (Iter != TypeDeclarationMap.end())
    {
      UtlReleaseReference((*Iter).second);
      TypeDeclarationMap.erase(pVarName);
      bRemoved = true;
    }
  }

  return (bRemoved);
}

//  ----------------------------------------------------------------------------

void AdtFortranDeclarations::removeOutputVarPrefix(AdtParser* pParentObj, const char* pClassName)
{
  if ((pClassName != 0) &&
      (pParentObj != 0))
  {
    // Look for arguments that have class prefixes.
    AdtParserPtrListIter  Iter;
    string                sClassPrefix(pClassName);

    sClassPrefix += "__";

    for (Iter = ParameterList.begin() ; Iter != ParameterList.end() ; ++Iter)
    {
      AdtParser*  pParamObj = *Iter;

      if (pParamObj != 0)
      {
        string  sPrefixedName(pParamObj->name());
        int     nStart  = 0;
        int     nLength = 0;

        if (AdtParser::hasSubString(sPrefixedName,
                                    sClassPrefix,
                                    nStart,
                                    nLength,
                                    false))
        {
          AdtParserPtrListIter  NameIter;
          AdtParserPtrList      NameList;
          const char*           pName = sPrefixedName;
          string                sUnPrefixedName(pName + nLength);

          // Find all AdtFortranNames with sPrefixedName as the name and replace
          // the name with sUnPrefixedName
          pParentObj->findObjects(NameList,
                                  "AdtFortranName",
                                  sPrefixedName,
                                  false,
                                  0,
                                  false);

          for (NameIter = NameList.begin() ; NameIter != NameList.end() ; ++NameIter)
          {
            AdtParser*  pNameObj = *NameIter;

            if (pNameObj != 0)
            {
              pNameObj->name(sUnPrefixedName);
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranDeclarations::checkIsVariable(AdtParser* pRootObj, AdtFile* pFile) const
{
  if (pRootObj != 0)
  {
    AdtParserPtrListConstIter Iter;
    AdtParserPtrList          PrimaryList;

    //enumerate the Primary constructs (fundamental component of expressions)
    pRootObj->findObjects(PrimaryList, "AdtFortranPrimary");

    if (pFile != 0)
    {
      ((AdtFortranBase*)pRootObj)->writeFortran(*pFile);
      pFile->newline();
      pFile->newline();
    }

    //Flag Primary objects as being variables rather than something else like
    //function calls. We do this so that the streaming code will know when to
    //A(x,y,z) is an array and when it is something else. If an array it needs
    //to be written as A[x][y][z] in Delphi code.
    for (Iter = PrimaryList.begin() ; Iter != PrimaryList.end() ; ++Iter)
    {
      AdtFortranPrimary* pPrimaryObj = (AdtFortranPrimary*)((AdtParser*)*Iter);

      if (pPrimaryObj != 0)
      {
        pPrimaryObj->checkIsVariable(VariablesMap);

        if (pFile != 0)
        {
          char sBuffer[64] = {0};

          ::sprintf(sBuffer, " line number=%d", pPrimaryObj->lineNumber());
          pFile->write(pPrimaryObj->isVariable() ? "Is Var=TRUE" : "Is Var=FALSE");
          pFile->write(sBuffer);
          pFile->newline();
          pFile->write("Fortran Code");
          pFile->newline();
          pPrimaryObj->writeFortran(*pFile);
          pFile->newline();
          pFile->write("Delphi Code");
          pFile->newline();
          pPrimaryObj->writeDelphi(*pFile, 0);
          pFile->newline();
          pFile->newline();
        }
      }
    }

    if (pFile != 0)
    {
      ((AdtFortranBase*)pRootObj)->writeDelphi(*pFile, 0);
      pFile->newline();
      pFile->newline();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeGenericSeperator(AdtFile& pOutFile, AdtFortranDestCodeType nType) const
{
  switch(nType)
  {
    case AdtFortranDestCodeCPP:
    {
      pOutFile.write(", ");
      break;
    }

    case AdtFortranDestCodeDelphi:
    case AdtFortranDestCodeFortran:
    {
      pOutFile.write("; ");
      break;
    }

    default:
    {
      ::printf("FATAL ERROR: AdtFortranDeclarations::writeGenericSeperator "
               "failure on line %d in file %s\n",
               __LINE__,
               __FILE__);

      FAIL();
      AdtExit(-1);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeGenericParameterList(AdtFile& pOutFile, AdtFortranDestCodeType nType) const
{
  AdtParserPtrListConstIter  Iter;
  size_t                     nCount  = 0;
  size_t                     nSize   = ParameterList.size();

  for (Iter = ParameterList.begin() ; Iter != ParameterList.end() ; ++Iter)
  {
    AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

    if (pObj != 0)
    {
      AdtParserPtrByStringMapConstIter  Iter = ParameterTypeDeclarationMap.find(pObj->name());

      if (Iter != ParameterTypeDeclarationMap.end())
      {
        AdtFortranBase* pParameterTypeDeclObj = (AdtFortranBase*)((AdtParser*)((*Iter).second));

        pParameterTypeDeclObj->writeGeneric(pOutFile, nType, 3);
      }

      nCount++;

      if (nCount < nSize)
      {
        writeGenericSeperator(pOutFile, nType);
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeGenericInitialisations(AdtFile& pOutFile, AdtFortranDestCodeType nType) const
{
  if (TypeDeclarationMap.size() > 0)
  {
    //Write variable initialisations
    AdtParserPtrByStringMapConstIter  MapIter;

    for (MapIter = TypeDeclarationMap.begin() ; MapIter != TypeDeclarationMap.end() ; ++MapIter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)((*MapIter).second));

      if (pObj != 0)
      {
        pObj->writeGeneric(pOutFile, nType, 2);
      }
    }

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeGenericReturnType(AdtFile& pOutFile, const char* pFunctionName, AdtFortranDestCodeType nType) const
{
  AdtParserPtrByStringMapConstIter Iter = FunctionTypeDeclarationMap.find(pFunctionName);

  if (Iter != FunctionTypeDeclarationMap.end())
  {
    AdtFortranBase* pObj = (AdtFortranBase*)(AdtParser*)((*Iter).second);

    if (pObj != 0)
    {
      pObj->writeGeneric(pOutFile, nType, 4);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_ParameterList(AdtFile& pOutFile) const
{
  return (writeGenericParameterList(pOutFile, AdtFortranDestCodeCPP));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_Declarations(AdtFile& pOutFile) const
{
  if (ParameterStmtList.size() > 0)
  {
    pOutFile.newline();

    //Write constants
    AdtParserPtrListConstIter  Iter;

    for (Iter = ParameterStmtList.begin() ; Iter != ParameterStmtList.end() ; ++Iter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pObj != 0)
      {
        pObj->writeCPP(pOutFile, 1);
      }
    }

    pOutFile.newline();
  }

  if ((DimensionStmtList.size() > 0) || (TypeDeclarationMap.size() > 0))
  {
    pOutFile.newline();

    //Write variable declarations
    AdtParserPtrListConstIter  Iter;

    for (Iter = DimensionStmtList.begin() ; Iter != DimensionStmtList.end() ; ++Iter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pObj != 0)
      {
        pObj->writeCPP(pOutFile, 1);
      }
    }

    AdtParserPtrByStringMapConstIter  MapIter;

    for (MapIter = TypeDeclarationMap.begin() ; MapIter != TypeDeclarationMap.end() ; ++MapIter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)((*MapIter).second));

      if (pObj != 0)
      {
        pObj->writeCPP(pOutFile, 1);
        pOutFile.write(";");
        pOutFile.newline();
      }
    }

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_Initialisations(AdtFile& pOutFile) const
{
  return (writeGenericInitialisations(pOutFile, AdtFortranDestCodeCPP));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_Allocations(AdtFile& pOutFile) const
{
  AdtParserPtrByStringMapConstIter  Iter;
  AdtFortranVariableInfo            VariableInfo(this);
  AdtStringByStringMap              PlanMap;
  int                               nPlan = 1;

  for (Iter = TypeDeclarationMap.begin() ; Iter != TypeDeclarationMap.end() ; ++Iter)
  {
    const string& rName         = (*Iter).first;
    AdtParser*    pTypeDeclStmt = (*Iter).second;
    int           nDimensions   = VariableInfo.numberOfDimensions(rName);

    if (nDimensions > 0)
    {
      string              sPlanName;
      string              sArrayPlanArgs;
      AdtFortranTypeSpec* pTypeSpec = (AdtFortranTypeSpec*)pTypeDeclStmt->findDescendant("TypeSpec");

      // We have an array that needs initialising with a statement like this:
      //  AdtArrayPlan  Plan_n_h_1(1, n_h);
      //
      //  Plan_n_h_1.create(MemAllocator, wt_A);
      // Need to reverse dimensions.
      for (int cn = nDimensions - 1 ; cn >= 0 ; cn--)
      {
        string  sLowerDim;
        string  sUpperDim;

        VariableInfo.lowerDimension(rName, cn, sLowerDim);
        VariableInfo.upperDimension(rName, cn, sUpperDim);

        if (cn != 0)
        {
          sArrayPlanArgs += ",";
        }

        sArrayPlanArgs += sLowerDim + "," + sUpperDim + " - " + sLowerDim + " + 1";
      }

      AdtStringByStringMapConstIter PlanIter  = PlanMap.find(sArrayPlanArgs);
      bool                          bDeclare  = false;

      if (PlanIter == PlanMap.end())
      {
        char sBuffer[32] = {0};

        ::sprintf(sBuffer, "Plan_l%d", nPlan);

        sPlanName               = sBuffer;
        PlanMap[sArrayPlanArgs] = sPlanName;
        bDeclare                = true;

        nPlan++;
      }
      else
      {
        sPlanName = (*PlanIter).second;
      }

      if (bDeclare)
      {
        pOutFile.newline();
        pOutFile.write("AdtArrayPlan ");
        pOutFile.write(sPlanName);
        pOutFile.write("(");
        pOutFile.write(sArrayPlanArgs);
        pOutFile.write(");");
      }

      pOutFile.newline();
      pOutFile.write(sPlanName);
      pOutFile.write(".create(MemAllocator, ");
      pOutFile.write(rName);
      pOutFile.write(");");

      pOutFile.newline();
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_Deallocations(AdtFile& pOutFile) const
{
  AdtParserPtrByStringMapConstIter  Iter;
  AdtFortranVariableInfo            VariableInfo(this);

  for (Iter = TypeDeclarationMap.begin() ; Iter != TypeDeclarationMap.end() ; ++Iter)
  {
    const string& rName       = (*Iter).first;
    int           nDimensions = VariableInfo.numberOfDimensions(rName);

    if (nDimensions > 0)
    {
      // We have an array that needs freeing with a statement like this:
      //  destroy(neg_ain__i);
      pOutFile.write("destroy(");
      pOutFile.write(rName);
      pOutFile.write(");");
      pOutFile.newline();
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeCPP_ReturnType(AdtFile& pOutFile, const char* pFunctionName) const
{
  return (writeGenericReturnType(pOutFile, pFunctionName, AdtFortranDestCodeCPP));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiParameterList(AdtFile& pOutFile) const
{
  return (writeGenericParameterList(pOutFile, AdtFortranDestCodeDelphi));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiDeclarations(AdtFile& pOutFile) const
{
  if (ParameterStmtList.size() > 0)
  {
    pOutFile.newline();
    pOutFile.write("const");
    pOutFile.incrementIndent();
    pOutFile.newline();

    //Write constants
    AdtParserPtrListConstIter  Iter;

    for (Iter = ParameterStmtList.begin() ; Iter != ParameterStmtList.end() ; ++Iter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pObj != 0)
      {
        pObj->writeDelphi(pOutFile, 1);
      }
    }

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if ((DimensionStmtList.size() > 0) || (TypeDeclarationMap.size() > 0))
  {
    pOutFile.newline();
    pOutFile.write("var");
    pOutFile.incrementIndent();
    pOutFile.newline();

    //Write variable declarations
    AdtParserPtrListConstIter  Iter;

    for (Iter = DimensionStmtList.begin() ; Iter != DimensionStmtList.end() ; ++Iter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pObj != 0)
      {
        pObj->writeDelphi(pOutFile, 1);
      }
    }

    AdtParserPtrByStringMapConstIter  MapIter;

    for (MapIter = TypeDeclarationMap.begin() ; MapIter != TypeDeclarationMap.end() ; ++MapIter)
    {
      AdtFortranBase* pObj = (AdtFortranBase*)((AdtParser*)((*MapIter).second));

      if (pObj != 0)
      {
        pObj->writeDelphi(pOutFile, 1);
        pOutFile.write(";");
        pOutFile.newline();
      }
    }

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiInitialisations(AdtFile& pOutFile) const
{
  return (writeGenericInitialisations(pOutFile, AdtFortranDestCodeDelphi));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiAllocations(AdtFile& pOutFile,
                                                        AdtStringList* pVarList,
                                                        AdtStringList* pDestroyList) const
{
  AdtParserPtrByStringMapConstIter  Iter;
  AdtFortranVariableInfo            VariableInfo(this);
  AdtStringByStringMap              PlanMap;
  int                               nPlan = 1;

  for (Iter = TypeDeclarationMap.begin() ; Iter != TypeDeclarationMap.end() ; ++Iter)
  {
    const string& rName         = (*Iter).first;
    AdtParser*    pTypeDeclStmt = (*Iter).second;
    int           nDimensions   = VariableInfo.numberOfDimensions(rName);

    if (nDimensions > 0)
    {
      string              sPlanName;
      string              sArrayPlanArgs;
      AdtFortranTypeSpec* pTypeSpec = (AdtFortranTypeSpec*)pTypeDeclStmt->findDescendant("TypeSpec");

      // We have an array that needs initialising with a statement like this:
      //  AdtArrayPlan  Plan_n_h_1(1, n_h);
      //
      //  Plan_n_h_1.create(MemAllocator, wt_A);
      // Need to reverse dimensions.
      for (int cn = nDimensions - 1 ; cn >= 0 ; cn--)
      {
        string  sLowerDim;
        string  sUpperDim;

        VariableInfo.lowerDimension(rName, cn, sLowerDim);
        VariableInfo.upperDimension(rName, cn, sUpperDim);

        if (cn != 0)
        {
          sArrayPlanArgs += ",";
        }

        sArrayPlanArgs += sLowerDim + "," + sUpperDim + " - " + sLowerDim + " + 1";
      }

      AdtStringByStringMapConstIter PlanIter  = PlanMap.find(sArrayPlanArgs);
      bool                          bDeclare  = false;

      if (PlanIter == PlanMap.end())
      {
        char sBuffer[32] = {0};

        ::sprintf(sBuffer, "Plan_l%d", nPlan);

        sPlanName               = sBuffer;
        PlanMap[sArrayPlanArgs] = sPlanName;
        bDeclare                = true;

        if (pVarList != 0)
        {
          string  sVarDecl = sPlanName + " : AdtArrayPlan;";

          pVarList->push_back(sVarDecl);
        }

        if (pDestroyList != 0)
        {
          string  sVarDestroy = sPlanName + ".destroy();";

          pDestroyList->push_back(sVarDestroy);
        }

        nPlan++;
      }
      else
      {
        sPlanName = (*PlanIter).second;
      }

      if (bDeclare)
      {
        pOutFile.newline();
        pOutFile.write(sPlanName);
        pOutFile.write(" := AdtArrayPlan.create(");
        pOutFile.write(sArrayPlanArgs);
        pOutFile.write(");");
      }

      pOutFile.newline();
      pOutFile.write(sPlanName);
      pOutFile.write(".create(_MemAllocator, ");
      pOutFile.write(rName);
      pOutFile.write(");");

      pOutFile.newline();
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiDeallocations(AdtFile& pOutFile) const
{
  AdtParserPtrByStringMapConstIter  Iter;
  AdtFortranVariableInfo            VariableInfo(this);

  for (Iter = TypeDeclarationMap.begin() ; Iter != TypeDeclarationMap.end() ; ++Iter)
  {
    const string& rName       = (*Iter).first;
    int           nDimensions = VariableInfo.numberOfDimensions(rName);

    if (nDimensions > 0)
    {
      // We have an array that needs freeing with a statement like this:
      //  destroy(neg_ain__i);
      pOutFile.write("destroy(");
      pOutFile.write(rName);
      pOutFile.write(");");
      pOutFile.newline();
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDeclarations::writeDelphiReturnType(AdtFile& pOutFile, const char* pFunctionName) const
{
  return (writeGenericReturnType(pOutFile, pFunctionName, AdtFortranDestCodeDelphi));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiBase method implementations
//  ----------------------------------------------------------------------------
AdtFile& AdtFortranBase::forAllWriteGeneric(AdtFile& pOutFile, AdtFortranDestCodeType nDestCodeType, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix, bool bReverse) const
{
  if (pOutFile.isOpen())
  {
    if (bReverse)
    {
      AdtParserPtrListConstRIter    Iter;
      size_t                        nSize = objList().size();
      size_t                        cn    = 0;

      for (Iter = objList().rbegin() ; Iter != objList().rend() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        cn++;

        if ((pObj != 0) && pObj->isType("AdtFortranBase"))
        {
          AdtFortranBase* pFortranObj = (AdtFortranBase*)pObj;

          pFortranObj->writeGeneric(pOutFile, nDestCodeType, nMode);

          if (pSuffix != 0)
          {
            write(pOutFile, pSuffix);
          }

          if (bExcludeLast && (cn == nSize))
          {
            //Do nothing
          }
          else
          {
            write(pOutFile, pDelimiter);

            if (bNewline)
            {
              pOutFile.newline();
            }
          }
        }
      }
    }
    else
    {
      AdtParserPtrListConstIter     Iter;
      size_t                        nSize = objList().size();
      size_t                        cn    = 0;

      for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        cn++;

        if ((pObj != 0) && pObj->isType("AdtFortranBase"))
        {
          AdtFortranBase* pFortranObj = (AdtFortranBase*)pObj;

          pFortranObj->writeGeneric(pOutFile, nDestCodeType, nMode);

          if (pSuffix != 0)
          {
            write(pOutFile, pSuffix);
          }

          if (bExcludeLast && (cn == nSize))
          {
            //Do nothing
          }
          else
          {
            write(pOutFile, pDelimiter);

            if (bNewline)
            {
              pOutFile.newline();
            }
          }
        }
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFortranBase::AdtFortranBase()
 : AdtParser()
{

}

//  ----------------------------------------------------------------------------

AdtFortranBase::~AdtFortranBase()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::rootBindComments(AdtCommon* pCompilerBase)
{
  if (FortranRootObject != 0)
  {
    FortranRootObject->bindComments(pCompilerBase);
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::setChangePrefix(const char* pRemovePrefixString, const char* pAddPrefixString)
{
  RemovePrefixString  = pRemovePrefixString;
  AddPrefixString     = pAddPrefixString;
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBase::writeWithChangedPrefix(AdtFile& pOutFile, const char* pString, bool bAddNew, bool bUnconditional)
{
  int         nStart  = 0;
  int         nLength = 0;
  string      sName(pString);
  const char* pName    = sName;
  bool        bRemoved = false;

  if (RemovePrefixString != 0)
  {
    if (AdtParser::hasSubString(sName,
                                RemovePrefixString,
                                nStart,
                                nLength,
                                false) && (nStart == 0))
    {
      // If it matches the prefix we should remove it
      pName   += nLength;
      bRemoved = true;
    }
  }

  if ((AddPrefixString != 0) && ((bAddNew && bRemoved) || (bUnconditional || bRemoved)))
  {
    if (!(AdtParser::hasSubString(pName,
                                  AddPrefixString,
                                  nStart,
                                  nLength,
                                  false) && (nStart == 0)))
    {                                  
      write(pOutFile, AddPrefixString);
    }
  }

  write(pOutFile, pName);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::initialise()
{
  //Do whatever is required. Possibly not needed anymore
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::splitNumericConstant(string& rNumber, string& rSize, const char* pNumericConstant)
{
  const char* pChar = pNumericConstant;

  if (AdtParse::extractWord(rNumber, "_", pChar, true))
  {
    // has _ size delimeter
    pChar++;

    rSize = pChar;

    if (rNumber[rNumber.length() - 1] == '.')
    {
      // Fixup real numbers like 5. to be 5.0
      rNumber += "0";
    }
  }
  else
  {
    string  sMantissa;

    pChar = pNumericConstant;

    if (AdtParse::extractWord(sMantissa, "dD", pChar, true))
    {
      // has d or D in it
      pChar++;

      if (*pChar == '0')
      {
        // numerical constant without exponent
        rNumber = sMantissa + pChar;
      }
      else
      {
        // numerical constant with exponent
        rNumber = sMantissa + "E" + pChar;
        rSize   = "8";
      }
    }
    else
    {
      rNumber = pNumericConstant;
      rSize   = "";
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranExpr* AdtFortranBase::createSimpleExpression(const char* pIdent)
{
  AdtFortranExpr* pExpr = 0;

  if (pIdent != 0)
  {
    AdtFortranBase* pRoot;
    string          sAssignment("Dummy=");

    sAssignment += pIdent;
    pRoot        = AdtFortranExecutableProgram::expressionBuild(sAssignment, false);

    if (pRoot != 0)
    {
      // Find the Assignment statement object
      AdtFortranAssignmentStmt* pStatement = (AdtFortranAssignmentStmt*)pRoot->findObject("AdtFortranAssignmentStmt");

      if (pStatement != 0)
      {
        pExpr = (AdtFortranExpr*)pStatement->findDescendant("Expr");

        if (pExpr != 0)
        {
          pExpr->lock();
        }
      }

      UtlReleaseReference(pRoot);
    }
  }

  return (pExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmt* AdtFortranBase::createSimpleTypeDeclarationStmt(const char* pVarName,
                                                                               AdtFortranType nType,
                                                                               AdtFortranExpr* pExprObj)
{
  AdtFortranIcon*                 pIconObj            = new AdtFortranIcon("");
  AdtFortranLblDef*               pLblDefObj          = new AdtFortranLblDef(pIconObj);
  AdtFortranTypeSpec*             pTypeSpecObj        = new AdtFortranTypeSpec(nType, 0);
  AdtFortranName*                 pNameObj            = new AdtFortranName(pVarName);

  AdtFortranEntityDecl*           pEntityDeclObj      = new AdtFortranEntityDecl(pNameObj,
                                                                                 pExprObj,
                                                                                 0,
                                                                                 0,
                                                                                 0);

  AdtFortranEntityDeclList*       pEntityDeclListObj  = new AdtFortranEntityDeclList(pEntityDeclObj);

  AdtFortranTypeDeclarationStmt*  pTypeDeclStmt       = new AdtFortranTypeDeclarationStmt(pLblDefObj,
                                                                                          pTypeSpecObj,
                                                                                          0,
                                                                                          pEntityDeclListObj);

  UtlReleaseReference(pIconObj);
  UtlReleaseReference(pLblDefObj);
  UtlReleaseReference(pTypeSpecObj);
  UtlReleaseReference(pNameObj);
  UtlReleaseReference(pEntityDeclObj);
  UtlReleaseReference(pEntityDeclListObj);

  return (pTypeDeclStmt);
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::createDefaultSubscripts(AdtParserPtrList& rResultSubscriptList,
                                             const AdtFortranVariableInfo& rVariableInfo,
                                             const char* pName)
{
  int nDims = rVariableInfo.numberOfDimensions(pName);

  for (int cn = 0 ; cn < nDims ; cn++)
  {
    string sLowerDim;
    string sUpperDim;

    if (rVariableInfo.lowerDimension(pName, cn, sLowerDim) &&
        rVariableInfo.upperDimension(pName, cn, sUpperDim))
    {
      AdtFortranExpr*             pExprObj             = createSimpleExpression(sLowerDim);
      AdtFortranExpr*             pExpr2Obj            = createSimpleExpression(sUpperDim);
      AdtFortranSubscriptTriplet* pSubscriptTripletObj = new AdtFortranSubscriptTriplet(3,
                                                                                        pExprObj,
                                                                                        pExpr2Obj,
                                                                                        0);

      AdtFortranSectionSubscript* pSectionSubscriptObj = new AdtFortranSectionSubscript(0, pSubscriptTripletObj);

      rResultSubscriptList.push_back(pSectionSubscriptObj);

      UtlReleaseReference(pSectionSubscriptObj);
      UtlReleaseReference(pSubscriptTripletObj);
      UtlReleaseReference(pExpr2Obj);
      UtlReleaseReference(pExprObj);
    }
    else
    {
      ::printf("FATAL ERROR: Cannot determine index range for subscript %d in variable %s"
               "\nContext line %d, file %s\n",
               cn,
               pName,
               __LINE__,
               __FILE__);

      FAIL();
      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::makeImplicitSubscriptExplicit(AdtFortranSectionSubscript* pSubscript,
                                                   const AdtFortranVariableInfo& rVariableInfo,
                                                   const char* pName,
                                                   int nIndex)
{
  AdtFortranSubscriptTriplet* pSubscriptTriplet = (AdtFortranSubscriptTriplet*)pSubscript->findDescendant("SubscriptTriplet");

  if ((pSubscriptTriplet != 0) && pSubscriptTriplet->isImplicit())
  {
    AdtFortranExpr* Expr  = (AdtFortranExpr*)pSubscript->findDescendant("Expr");
    AdtFortranExpr* Expr2 = (AdtFortranExpr*)pSubscript->findDescendant("Expr2");
    int             nDims = rVariableInfo.numberOfDimensions(pName);

    if ((nIndex >= 0) && (nIndex < nDims))
    {
      if (Expr == 0)
      {
        string sLowerDim;

        if (rVariableInfo.lowerDimension(pName, nIndex, sLowerDim))
        {
          AdtFortranExpr* pExprObj = createSimpleExpression(sLowerDim);

          pSubscriptTriplet->substituteExpr(pExprObj);
          UtlReleaseReference(pExprObj);
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranBase::makeImplicitSubscriptExplicit "
                   "failure on line %d in file %s\nContext line %d, file %s\n",
                   pSubscript->lineNumber(),
                   pSubscript->fileName(),
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }

      if (Expr2 == 0)
      {
        string sUpperDim;

        if (rVariableInfo.upperDimension(pName, nIndex, sUpperDim))
        {
          AdtFortranExpr* pExpr2Obj = createSimpleExpression(sUpperDim);

          pSubscriptTriplet->substituteExpr2(pExpr2Obj);
          UtlReleaseReference(pExpr2Obj);
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranBase::makeImplicitSubscriptExplicit "
                   "failure on line %d in file %s\nContext line %d, file %s\n",
                   pSubscript->lineNumber(),
                   pSubscript->fileName(),
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableConstruct* AdtFortranBase::createDoConstruct(const char* pLoopVarName,
                                                                 const char* pLabel,
                                                                 AdtParser* pExecutableConstruct,
                                                                 AdtFortranExpr* pStartExpr,
                                                                 AdtFortranExpr* pEndExpr,
                                                                 AdtFortranExpr* pStepExpr)
{
  AdtFortranExecutableConstruct*  pNewExecutableConstruct = 0;

  if ((pLoopVarName         != 0) &&
      (pExecutableConstruct != 0) &&
      (pStartExpr           != 0) &&
      (pEndExpr             != 0))
  {
    AdtFortranIcon*             pIcon             = new AdtFortranIcon(pLabel);
    AdtFortranLblDef*           pLblDef           = new AdtFortranLblDef(pIcon);
    AdtFortranIcon*             pNullIcon         = new AdtFortranIcon("");
    AdtFortranLblDef*           pNullLblDef       = new AdtFortranLblDef(pNullIcon);
    AdtFortranEndDoStmt*        pEndDoStmt        = new AdtFortranEndDoStmt(pNullLblDef, 0);
    AdtFortranName*             pLoopIdxName      = new AdtFortranName(pLoopVarName);
    AdtFortranConditionalBody*  pConditionalBody  = new AdtFortranConditionalBody(pExecutableConstruct);
    AdtFortranLoopControl*      pLoopControl      = new AdtFortranLoopControl(pLoopIdxName,
                                                                              pStartExpr,
                                                                              pEndExpr,
                                                                              pStepExpr);

    AdtFortranDoConstruct*      pDoConstruct      = new AdtFortranDoConstruct(pLblDef,
                                                                              0,
                                                                              pLoopControl,
                                                                              0,
                                                                              pConditionalBody,
                                                                              pEndDoStmt,
                                                                              false);

    pNewExecutableConstruct = new AdtFortranExecutableConstruct(0,
                                                                0,
                                                                pDoConstruct,
                                                                0,
                                                                0);

    UtlReleaseReference(pDoConstruct);
    UtlReleaseReference(pConditionalBody);
    UtlReleaseReference(pLoopControl);
    UtlReleaseReference(pLoopIdxName);
    UtlReleaseReference(pEndDoStmt);
    UtlReleaseReference(pNullLblDef);
    UtlReleaseReference(pNullIcon);
    UtlReleaseReference(pLblDef);
    UtlReleaseReference(pIcon);
  }

  return (pNewExecutableConstruct);
}

//  ----------------------------------------------------------------------------

bool AdtFortranBase::nameToNameAndClass(string& rName, string& rClassName) const
{
  bool        bConverted  = false;
  const char* pText       = name();
  char*       pSeperator  = (char*)::strstr(pText, "__");

  if (pSeperator != 0)
  {
    rName       = pSeperator + 2;
    *pSeperator = 0;
    rClassName  = pText;
    *pSeperator = '_';
    bConverted  = true;
  }

  return (bConverted);
}

//  ----------------------------------------------------------------------------

void AdtFortranBase::fortranRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(FortranRootObject);

  FortranRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtFortranExecutableProgram"))
    {
      FortranRootObject = (AdtFortranExecutableProgram*)pRoot;
      FortranRootObject->lock();
    }
    else
    {
      ::printf("FATAL ERROR: AdtFortranBase::fortranRootObject "
               "failure on line %d in file %s\nContext line %d, file %s\n",
               pRoot->lineNumber(),
               pRoot->fileName(),
               __LINE__,
               __FILE__);

      FAIL();
      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableProgram* AdtFortranBase::fortranRootObject()
{
  return (FortranRootObject);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBase::writeGeneric(AdtFile& pOutFile, AdtFortranDestCodeType nDestCodeType, int nMode) const
{
  switch (nDestCodeType)
  {
    case AdtFortranDestCodeCPP:
    {
      this->writeCPP(pOutFile, nMode);
      break;
    }

    case AdtFortranDestCodeDelphi:
    {
      this->writeDelphi(pOutFile, nMode);
      break;
    }

    case AdtFortranDestCodeFortran:
    default:
    {
      this->writeFortran(pOutFile, nMode);
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtFortranExecutableProgram method implementations
//  ----------------------------------------------------------------------------
void AdtFortranExecutableProgram::addBoundsChecking(AdtParser* pFuncOrSubObj,
                                                    const AdtFortranVariableInfo& rVariableInfo,
                                                    bool bThrowException)
{
  if (pFuncOrSubObj)
  {
    AdtStringByStringMap            AddedVarMap;
    AdtParserPtrList                ObjList;
    AdtParserPtrListIter            Iter;
    AdtFortranSectionSubscriptList* pSectionSubscriptList = 0;
    AdtStringByStringMap            AddedCheckMap;

    // Find all assignment statments and primary objects
    pFuncOrSubObj->findObjects(ObjList, "AdtFortranAssignmentStmt");
    pFuncOrSubObj->findObjects(ObjList, "AdtFortranPrimary");

    for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        int nDims = rVariableInfo.numberOfDimensions(pObj->name());

        if ((nDims > 0) && (strstr(pObj->name().c_str(), "stack") == 0))
        {
          pSectionSubscriptList = (AdtFortranSectionSubscriptList*)pObj->findDescendant("SectionSubscriptList");

          if ((pSectionSubscriptList != 0) && (pSectionSubscriptList->objList().size() > 0))
          {
            char sBuffer[2048] = {0};

            sprintf(sBuffer, "CHECK_%s_%zd", pObj->name().c_str(), pSectionSubscriptList->objList().size());

            // Check if we need to add a bounds check context variable definition
            string  sContextVar(sBuffer);

            if (AddedVarMap.find(sContextVar) == AddedVarMap.end())
            {
              // Add bounds checking context variable definition
              AdtFortranBody* pBody = (AdtFortranBody*)pObj->findAscendantWithClass("AdtFortranBody");

              AddedVarMap[sContextVar] = sContextVar;

              if (pBody != 0)
              {
                AdtFortranExpr*                 pNull         = createSimpleExpression("nil");
                AdtFortranTypeDeclarationStmt*  pTypeDeclStmt = createSimpleTypeDeclarationStmt(sContextVar, ForType_BOUNDSCHECK, pNull);

                pBody->addTypeDeclarationStmt(pTypeDeclStmt);
                UtlReleaseReference(pTypeDeclStmt);
                UtlReleaseReference(pNull);
              }
            }

            // Construct a call to do the bounds check and insert it in the code.
            sprintf(sBuffer,
                    "CALL check%zd(%s, %s, '%s', __FILE__, __LINE__, %s",
                    pSectionSubscriptList->objList().size(),
                    sContextVar.c_str(),
                    pObj->name().c_str(),
                    pObj->name().c_str(),
                    bThrowException ? ".TRUE." : ".FALSE.");

            // Note that in a delphi context __FILE__ and __LINE__ need to
            // be somehow mapped to {$I %FILE%} and {$I %LINE%}. Given that
            // we first write to a temp delphi file and then re-compile, the
            // easy way to handle this is to map it using the delphi lexer
            // and reserve __FILE__ and __LINE__ as tokens that map to those
            // comment fields.

            string                    sCallCode(sBuffer);
            AdtParserPtrListConstIter IndexIter;

            for (IndexIter = pSectionSubscriptList->objList().begin() ; IndexIter != pSectionSubscriptList->objList().end() ; ++IndexIter)
            {
              AdtFile     TextFile;
              string      sIndex;

              TextFile.open(sIndex);
              ((AdtFortranBase*)(AdtParser*)(*IndexIter))->writeFortran(TextFile);
              TextFile.close();

              sCallCode += ", " + sIndex + ", '" + sIndex + "'";
            }

            sCallCode += ")\n";

            AdtParser* pRoot = pObj->findAscendantWithClass("AdtFortranExecutableConstruct");

            ::sprintf(sBuffer, "%zx", (size_t)pRoot);

            string  sKey(sCallCode + sBuffer);

            // Only add check code if the same check has not already occured
            // for the same line of code. If it has then the extra check is
            // superfluous. We cannot do it globally because the values
            // making up the indexing may change between execution lines,
            // hence we build the statement root pointer into the key.
            if (AddedCheckMap.find(sKey) == AddedCheckMap.end())
            {
              AdtFortranBase* pContainer = expressionBuildAndInsert(sCallCode,
                                                                    pObj,
                                                                    false);

              if (0)
              {
                string  sTest;
                AdtFile FortranOut;

                if (FortranOut.open(sTest))
                {
                  pContainer->writeFortran(FortranOut);
                  FortranOut.close();
                }
              }

              AddedCheckMap[sKey] = "";
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableProgram::AdtFortranExecutableProgram(AdtParser* pProgramUnitObj)
 : AdtFortranBase(),
   AdtSourceRoot()
{
  add(pProgramUnitObj);
  depth(0, true);
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableProgram::AdtFortranExecutableProgram(const AdtFortranExecutableProgram& rCopy)
 : AdtFortranBase(rCopy),
   AdtSourceRoot(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranExecutableProgram::~AdtFortranExecutableProgram()
{

}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::initialise()
{
  AdtParserPtrListIter    Iter;
  AdtParserPtrList        FunctionList;
  AdtParserPtrList        SubroutineList;
  AdtParserPtrByStringMap FunctionMap;

  findObjects(FunctionList, "AdtFortranFunctionStmt");
  listToMap(FunctionMap, FunctionList);

  for (Iter = FunctionList.begin() ; Iter != FunctionList.end() ; ++Iter)
  {
    AdtFortranFunctionStmt* pFuncStmt = (AdtFortranFunctionStmt*)(AdtParser*)(*Iter);

    if (pFuncStmt != 0)
    {
      pFuncStmt->initialise(&FunctionMap);
    }
  }

  findObjects(SubroutineList, "AdtFortranSubroutineStmt");

  for (Iter = SubroutineList.begin() ; Iter != SubroutineList.end() ; ++Iter)
  {
    AdtFortranSubroutineStmt* pSubStmt = (AdtFortranSubroutineStmt*)(AdtParser*)(*Iter);

    if (pSubStmt != 0)
    {
      pSubStmt->initialise(&FunctionMap);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::addStackFixups(const AdtStringByStringMap& rNewMethodMap)
{
  AdtParserPtrList      StackObjList;
  AdtParserPtrList      CodeList;
  AdtParserPtrListIter  Iter;

  //Find all functions and subroutines
  findObjects(CodeList, "AdtFortranFunctionSubprogram");
  findObjects(CodeList, "AdtFortranSubroutineSubprogram");

  //Find all stack variables used in functions and subroutines
  for (Iter = CodeList.begin() ; Iter != CodeList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if ((pObj != 0) && (rNewMethodMap.find(pObj->name()) != rNewMethodMap.end()))
    {
      pObj->findObjects(StackObjList,
                        "AdtFortranName",
                        "stack_",
                        false,
                        0,
                        true);
    }
  }

  //For all stack var instances, find the ones corresponding to array writing
  //operations and insert stack checking code for them. Array reading should not
  //require a check as the stack only grows on writing and not reading.
  for (Iter = StackObjList.begin() ; Iter != StackObjList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if (pObj != 0)
    {
      const AdtParser*  pSubscriptObj        = 0;
      AdtParser*        pListObj             = 0;
      AdtParser*        pRootConditionalBody = 0;
      AdtParser*        pRootBody            = 0;
      AdtParser*        pSubscriptListObj    = 0;
      AdtParser*        pExprObj             = pObj->findAscendantWithClassLineage("AdtFortranPrimary,AdtFortranMultOperand,AdtFortranAddOperand,"
                                                                                   "AdtFortranLevel2Expr,AdtFortranLevel4Expr,AdtFortranAndOperand,"
                                                                                   "AdtFortranOrOperand,AdtFortranEquivOperand,AdtFortranExpr");

      if (pExprObj == 0)
      {
        // Assignment statement so do check size.
        pExprObj          = pObj->findAscendantWithClassLineage("AdtFortranAssignmentStmt");
        pSubscriptListObj = (pExprObj != 0) ? pExprObj->findDescendant("SectionSubscriptList") : 0;
      }

      if (pSubscriptListObj != 0)
      {
        pSubscriptObj = *(pSubscriptListObj->objList().begin());

        if ((pSubscriptObj != 0) && !pSubscriptObj->isType("AdtFortranSectionSubscript"))
        {
          pSubscriptObj = 0;
        }
      }

      if (pExprObj != 0)
      {
        pRootConditionalBody = pExprObj->findAscendantWithClass("AdtFortranConditionalBody", &pListObj);

        if (pRootConditionalBody == 0)
        {
          pRootBody = pExprObj->findAscendantWithClass("AdtFortranBody", &pListObj);
        }
      }

      if ((pListObj != 0) && (pSubscriptObj != 0))
      {
        // If pSubscriptObj contains a slice (ie. a colon) then we need a two
        // value CHECKSIZE call (ie. CHECKSIZE2), one for the start index and
        // one for the end index.
        const AdtFortranSectionSubscript* pOrigSubscriptObj = (const AdtFortranSectionSubscript*)pSubscriptObj;
        AdtFortranSectionSubscriptList*   pSubscriptList    = new AdtFortranSectionSubscriptList(0);

        if (pSubscriptList != 0)
        {
          AdtFortranName*                 pName             = new AdtFortranName("CHECKSIZE");
          AdtFortranSectionSubscript*     pCopySubscriptObj = 0;
          AdtFortranCallStmt*             pCallStmt         = 0;
          AdtFortranActionStmt*           pActionStmt       = 0;
          AdtFortranExecutableConstruct*  pExecConstruct    = 0;
          AdtFortranBodyConstruct*        pBodyConstruct    = 0;
          int                             nSubscript        = 0;
          AdtFortranExpr*                 pArrayExpr        = createSimpleExpression(pObj->name());
          AdtFortranSectionSubscript*     pSectionSubscript = new AdtFortranSectionSubscript(pArrayExpr, 0);
          bool                            bAddCheckSize     = true;

          // Add array variable name
          pSubscriptList->add(pSectionSubscript);

          UtlReleaseReference(pArrayExpr);
          UtlReleaseReference(pSectionSubscript);

          // Add the indices referenced
          for (pCopySubscriptObj = pOrigSubscriptObj->firstSubscript(nSubscript) ; pCopySubscriptObj != 0 ; pCopySubscriptObj = pOrigSubscriptObj->nextSubscript(nSubscript))
          {
            pSubscriptList->add(pCopySubscriptObj);
            UtlReleaseReference(pCopySubscriptObj);
          }

          switch (nSubscript)
          {
            case 0:
            {
              // No subscripts means implied array size so no check size is required
              bAddCheckSize = false;
            }

            case 1:
            {
              // Do nothing
              break;
            }

            case 2:
            {
              // Two index CHECKSIZE operation so use CHECKSIZE2
              pName->name("CHECKSIZE2");
              break;
            }

            default:
            {
              // Should never happen
              ::printf("FATAL ERROR: AdtFortranExecutableProgram::addStackFixups "
                       "failure on line %d in file %s\nContext line %d, file %s\n",
                       pSubscriptObj->lineNumber(),
                       pSubscriptObj->fileName(),
                       __LINE__,
                       __FILE__);

              FAIL();
              AdtExit(-1);
            }
          }

          // Create the call statement
          pCallStmt = new AdtFortranCallStmt(0,
                                             pName,
                                             pSubscriptList);

          pActionStmt = new AdtFortranActionStmt(0,
                                                 0,
                                                 pCallStmt,
                                                 0,
                                                 0,
                                                 0,
                                                 0,
                                                 0,
                                                 0,
                                                 0);

          pExecConstruct = new AdtFortranExecutableConstruct(pActionStmt,
                                                             0,
                                                             0,
                                                             0,
                                                             0);

          if (bAddCheckSize)
          {
            if (pRootBody != 0)
            {
              pBodyConstruct = new AdtFortranBodyConstruct(0, pExecConstruct);

              pRootBody->insertBefore(pListObj, pBodyConstruct);
            }
            else if (pRootConditionalBody != 0)
            {
              pRootConditionalBody->insertBefore(pListObj, pExecConstruct);
            }
            else
            {
              ::printf("FATAL ERROR: AdtFortranExecutableProgram::addStackFixups "
                       "failure on line %d in file %s\nContext line %d, file %s\n",
                       pObj->lineNumber(),
                       pObj->fileName(),
                       __LINE__,
                       __FILE__);

              FAIL();
              AdtExit(-1);
            }
          }

          UtlReleaseReference(pBodyConstruct);
          UtlReleaseReference(pExecConstruct);
          UtlReleaseReference(pActionStmt);
          UtlReleaseReference(pCallStmt);
          UtlReleaseReference(pSubscriptList);
          UtlReleaseReference(pName);
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::addSliceFixups(const AdtStringByStringMap& rNewMethodMap,
                                                 AdtStringList& rNewMethodList,
                                                 const AdtStringList& rBoundsCheckList,
                                                 const AdtStringList& rGlobalBoundsCheckList,
                                                 const char* pClassPrefix,
                                                 AdtFile* pFile,
                                                 bool bThrowException)
{
  // Make a map of bounds checked functions indexed by function.
  AdtStringByStringMap  BoundsCheckMap;

  AdtParser::nameListToNameMap(BoundsCheckMap, rBoundsCheckList, pClassPrefix);
  AdtParser::nameListToNameMap(BoundsCheckMap, rGlobalBoundsCheckList, pClassPrefix);

  // What needs to happen is this. Assume the slice expression is syntactically valid.
  // Determine the number of indices and the index ranges for the slice from the
  // left hand array. Construct a nested loop to loop over all indices of the arrays
  // involved and add the correct inner expression to do the required assignment.
  // This method is fool proof, requires no additional code to library or
  // language support for slicing and requires no temporary storage. Should make for
  // and efficient implementation.
  AdtParserPtrList      FuncAndSubList;
  AdtParserPtrListIter  FuncAndSubIter;

  // Find all functions and subroutines. We need to find them first as the slice
  // fixup process needs to create new local loop variables but we only want to
  // create them once, so we need to keep track of the created vars on a
  // function/subroutine basis (each has its own local variable space on the stack)
  findObjects(FuncAndSubList, "AdtFortranFunctionSubprogram");
  findObjects(FuncAndSubList, "AdtFortranSubroutineSubprogram");

  for (FuncAndSubIter = FuncAndSubList.begin() ; FuncAndSubIter != FuncAndSubList.end() ; ++FuncAndSubIter)
  {
    AdtParser*  pFuncOrSubObj = *FuncAndSubIter;

    if ((pFuncOrSubObj != 0) && ((rNewMethodMap.find(pFuncOrSubObj->name()) != rNewMethodMap.end()) ||
                                 (BoundsCheckMap.find(pFuncOrSubObj->name()) != BoundsCheckMap.end())))
    {
      AdtStringByStringMap    AddedVarMap;
      AdtParserPtrList        ObjList;
      AdtParserPtrListIter    Iter;
      AdtFortranVariableInfo  VariableInfo(pFuncOrSubObj);
      AdtFortranDeclarations* pDeclarations = 0;
      bool                    bRemovedSlice = false;
      // If the method isn't a new method then it means we are overriding a parent
      // class method for the purposes of bounds checking, in which case, we need
      // to make it virtual so it overrides the behaviour of the parent class.
      // We assume that the author of the parent class will make the parent
      // method virtual in the first place.
      bool                    bMakeVirtual  = (rNewMethodMap.find(pFuncOrSubObj->name()) == rNewMethodMap.end());

      // Need to find declarations object
      AdtFortranFunctionStmt* pFunctionStmt = (AdtFortranFunctionStmt*)pFuncOrSubObj->findObject("AdtFortranFunctionStmt");

      if (pFunctionStmt != 0)
      {
        pDeclarations = pFunctionStmt->declarations();
      }
      else
      {
        AdtFortranSubroutineStmt* pSubroutineStmt = (AdtFortranSubroutineStmt*)pFuncOrSubObj->findObject("AdtFortranSubroutineStmt");

        if (pSubroutineStmt != 0)
        {
          pDeclarations = pSubroutineStmt->declarations();
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      // Find all If statments
      pFuncOrSubObj->findObjects(ObjList, "AdtFortranIfStmt");

      // Replace any containing IfStmt constructs with an equivalent IfThenStmt
      // before doing slice fixups and bounds checking. This is required
      // because an IfStmt can only have a single line expression as the
      // action part whereas we need a conditional body to be able to insert
      // the multiple statements to expand the slice or implement bounds
      // checking. Hence we need to change it to an IfThenStmt first.
      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        if (pObj != 0)
        {
          string            sCodeString;
          AdtFortranIfStmt* pIfStmt = (AdtFortranIfStmt*)pObj;

          pIfStmt->equivalentIfThenCode(sCodeString);
          AdtFortranExecutableProgram::expressionBuildAndReplace(sCodeString, pIfStmt, 0);
        }
      }

      ObjList.clear();

      // Find all assignment statments
      pFuncOrSubObj->findObjects(ObjList, "AdtFortranAssignmentStmt");

      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        if (pObj != 0)
        {
          bool                      bChanged;
          AdtFortranAssignmentStmt* pAssignmentStmt = (AdtFortranAssignmentStmt*)pObj;
          AdtParser*                pParent         = pAssignmentStmt->parent();

          // Only do slice fixups on new functions and subroutines
          if (0)
          {
            // Debug code to see the statement form
            string  sBuffer;
            AdtFile File;

            File.open(sBuffer);
            pAssignmentStmt->writeFortran(File);
            File.close();

            // Do slice fixups on assignment statements
            bChanged = pAssignmentStmt->implementSliceFixups(AddedVarMap, VariableInfo, pDeclarations, pFile);
          }
          else
          {
            // Do slice fixups on assignment statements
            bChanged = pAssignmentStmt->implementSliceFixups(AddedVarMap, VariableInfo, pDeclarations, pFile);
          }

          if (bChanged)
          {
            bRemovedSlice = true;
          }
        }
      }

      if ((bRemovedSlice) && (pFile != 0))
      {
        pFile->write(pFuncOrSubObj->name());
        pFile->newline();
        pDeclarations->dump(pFile);
        pFile->newline();
        pFile->newline();
      }

      if (BoundsCheckMap.find(pFuncOrSubObj->name()) != BoundsCheckMap.end())
      {
        addBoundsChecking(pFuncOrSubObj, VariableInfo, bThrowException);

        if (bMakeVirtual)
        {
          // The bounds checked function is being over-ridden from a parent one
          // so we must force it to be virtual and add it to the new method
          // list so that it appears in the output.
          rNewMethodList.push_back(pFuncOrSubObj->name());

          AdtFortranFunctionStmt* pFunctionStmt = (AdtFortranFunctionStmt*)pFuncOrSubObj->findDescendant("FunctionStmt");

          if (pFunctionStmt != 0)
          {
            pFunctionStmt->isVirtual(true);
          }
          else
          {
            AdtFortranSubroutineStmt* pSubroutineStmt = (AdtFortranSubroutineStmt*)pFuncOrSubObj->findDescendant("SubroutineStmt");

            if (pSubroutineStmt != 0)
            {
              pSubroutineStmt->isVirtual(true);
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::enumerateSubroutineOrFunctionNames(AdtStringByStringMap& rRegardAsClassObjMap,
                                                                     bool bSubroutines,
                                                                     const char* pClassPrefix) const
{
  if (pClassPrefix != 0)
  {
    AdtParserPtrList      CodeList;
    AdtParserPtrListIter  Iter;

    if (bSubroutines)
    {
      //Find all subroutines
      findObjects(CodeList, "AdtFortranSubroutineSubprogram");
    }
    else
    {
      //Find all functions
      findObjects(CodeList, "AdtFortranFunctionSubprogram");
    }

    //Enumerate all the function names with the designated prefix and add the
    //names less the prefix to the map
    for (Iter = CodeList.begin() ; Iter != CodeList.end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        int     nStart  = 0;
        int     nLength = 0;
        string  sName(pObj->name());

        if (AdtParser::hasSubString(sName,
                                    pClassPrefix,
                                    nStart,
                                    nLength,
                                    false) && (nStart == 0))
        {
          const char* pName               = sName;
          const char* pNameWithoutPrefix  = pName + nLength;

          rRegardAsClassObjMap[pNameWithoutPrefix] = pNameWithoutPrefix;
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::enumerateFunctionNames(AdtStringByStringMap& rRegardAsClassFunctionsMap,
                                                         const char* pClassPrefix)
{
  enumerateSubroutineOrFunctionNames(rRegardAsClassFunctionsMap,
                                     false,
                                     pClassPrefix);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::enumerateSubroutineNames(AdtStringByStringMap& rRegardAsClassSubroutinesMap,
                                                           const char* pClassPrefix)
{
  enumerateSubroutineOrFunctionNames(rRegardAsClassSubroutinesMap,
                                     true,
                                     pClassPrefix);
}

//  ----------------------------------------------------------------------------

const AdtFortranExecutableProgram::PushPopCall  AdtFortranExecutableProgram::PushPopCalls[] = {{"PUSHINTEGER1ARRAY",  PushArrayCall, BooleanVarType  , 2, "bstack",   "INTEGER(1)"},
                                                                                               {"POPINTEGER1ARRAY",   PopArrayCall , BooleanVarType  , 2, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHINTEGER1",       PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKINTEGER1",       LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPINTEGER1",        PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHINTEGER2ARRAY",  PushArrayCall, Integer4VarType , 2, "i2stack",  "INTEGER(2)"},
                                                                                               {"POPINTEGER2ARRAY",   PopArrayCall , Integer4VarType , 2, "i2stack",  "INTEGER(2)"},
                                                                                               {"PUSHINTEGER2",       PushCall     , Integer4VarType , 1, "i2stack",  "INTEGER(2)"},
                                                                                               {"LOOKINTEGER2",       LookCall     , Integer4VarType , 1, "i2stack",  "INTEGER(2)"},
                                                                                               {"POPINTEGER4",        PopCall      , Integer4VarType , 1, "i4stack",  "INTEGER(4)"},
                                                                                               {"PUSHINTEGER4ARRAY",  PushArrayCall, Integer4VarType , 2, "i4stack",  "INTEGER(4)"},
                                                                                               {"POPINTEGER4ARRAY",   PopArrayCall , Integer4VarType , 2, "i4stack",  "INTEGER(4)"},
                                                                                               {"PUSHINTEGER4",       PushCall     , Integer4VarType , 1, "i4stack",  "INTEGER(4)"},
                                                                                               {"LOOKINTEGER4",       LookCall     , Integer4VarType , 1, "i4stack",  "INTEGER(4)"},
                                                                                               {"POPINTEGER4",        PopCall      , Integer4VarType , 1, "i4stack",  "INTEGER(4)"},
                                                                                               {"PUSHINTEGER8ARRAY",  PushArrayCall, Integer8VarType , 2, "i8stack",  "INTEGER(8)"},
                                                                                               {"POPINTEGER8ARRAY",   PopArrayCall , Integer8VarType , 2, "i8stack",  "INTEGER(8)"},
                                                                                               {"PUSHINTEGER8",       PushCall     , Integer8VarType , 1, "i8stack",  "INTEGER(8)"},
                                                                                               {"LOOKINTEGER8",       LookCall     , Integer8VarType , 1, "i8stack",  "INTEGER(8)"},
                                                                                               {"POPINTEGER8",        PopCall      , Integer8VarType , 1, "i8stack",  "INTEGER(8)"},
                                                                                               {"PUSHREAL4ARRAY",     PushArrayCall, Real4VarType    , 2, "r4stack",  "REAL(4)"},
                                                                                               {"POPREAL4ARRAY",      PopArrayCall , Real4VarType    , 2, "r4stack",  "REAL(4)"},
                                                                                               {"PUSHREAL4",          PushCall     , Real4VarType    , 1, "r4stack",  "REAL(4)"},
                                                                                               {"LOOKREAL4",          LookCall     , Real4VarType    , 1, "r4stack",  "REAL(4)"},
                                                                                               {"POPREAL4",           PopCall      , Real4VarType    , 1, "r4stack",  "REAL(4)"},
                                                                                               {"PUSHREAL8ARRAY",     PushArrayCall, Real8VarType    , 2, "r8stack",  "REAL(8)"},
                                                                                               {"POPREAL8ARRAY",      PopArrayCall , Real8VarType    , 2, "r8stack",  "REAL(8)"},
                                                                                               {"PUSHREAL8",          PushCall     , Real8VarType    , 1, "r8stack",  "REAL(8)"},
                                                                                               {"LOOKREAL8",          LookCall     , Real8VarType    , 1, "r8stack",  "REAL(8)"},
                                                                                               {"POPREAL8",           PopCall      , Real8VarType    , 1, "r8stack",  "REAL(8)"},
                                                                                               {"PUSHREAL16ARRAY",    PushArrayCall, Real16VarType   , 2, "r16stack",  "REAL(16)"},
                                                                                               {"POPREAL16ARRAY",     PopArrayCall , Real16VarType   , 2, "r16stack",  "REAL(16)"},
                                                                                               {"PUSHREAL16",         PushCall     , Real16VarType   , 1, "r16stack",  "REAL(16)"},
                                                                                               {"LOOKREAL16",         LookCall     , Real16VarType   , 1, "r16stack",  "REAL(16)"},
                                                                                               {"POPREAL16",          PopCall      , Real16VarType   , 1, "r16stack",  "REAL(16)"},
                                                                                               {"PUSHCONTROL1B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL1B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL1B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL2B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL2B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL2B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL3B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL3B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL3B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL4B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL4B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL4B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL5B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL5B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL5B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL6B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL6B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL6B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL7B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL7B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL7B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL8B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL8B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL8B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"PUSHCONTROL9B",      PushCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"LOOKCONTROL9B",      LookCall     , BooleanVarType  , 1, "bstack",   "INTEGER(1)"},
                                                                                               {"POPCONTROL9B",       PopCall      , BooleanVarType  , 1, "bstack",   "INTEGER(1)"}};

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::createStackVarNames(string& rStackName,
                                                      string& rIndexName,
                                                      const string& rBaseStackName,
                                                      int nIteration,
                                                      int nFnNumber)
{
  char sBuffer[32] = {0};

  ::sprintf(sBuffer, "_%d_%d", nFnNumber, nIteration);

  rStackName = rBaseStackName;

  rStackName += sBuffer;

  rIndexName = rStackName;

  rIndexName += "i";
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::createLocalVar(const char* pVarName,
                                                 AdtFortranType nVarType,
                                                 AdtParser* pObjToAddTo,
                                                 AdtStringByStringMap& rNewLocalsMap,
                                                 const AdtFortranVariableInfo& rVariableInfo)
{
  if ((pVarName != 0) && (pObjToAddTo != 0))
  {
    // Is var already defined
    AdtStringByStringMapIter  Iter = rNewLocalsMap.find(pVarName);

    if (!(rVariableInfo.hasVariable(pVarName) || (Iter != rNewLocalsMap.end())))
    {
      AdtFortranBody* pBody = (AdtFortranBody*)pObjToAddTo->findAscendantWithClass("AdtFortranBody");

      rNewLocalsMap.insert(AdtStringByStringMap::value_type(pVarName, pVarName));

      // Add new local variable definition
      if (pBody != 0)
      {
        AdtFortranTypeDeclarationStmt*  pTypeDeclStmt = createSimpleTypeDeclarationStmt(pVarName, nVarType);

        pBody->addTypeDeclarationStmt(pTypeDeclStmt);
        UtlReleaseReference(pTypeDeclStmt);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtParser* AdtFortranExecutableProgram::findFunctionOrSubroutine(const char* pFunctionName, bool& bIsFunction) const
{
  AdtParser*  pFuncOrSubSubprogram = findObject("AdtFortranFunctionSubprogram",
                                                pFunctionName,
                                                false);

  bIsFunction = true;

  if (pFuncOrSubSubprogram == 0)
  {
    pFuncOrSubSubprogram = findObject("AdtFortranSubroutineSubprogram",
                                      pFunctionName,
                                      false);

    bIsFunction = false;                                                                        
  }

  return (pFuncOrSubSubprogram);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::makeWrapper(AdtFortranExecutableProgram* pWorkingRoot,
                                              const char* pWrapperFunctionName,
                                              AdtFortranWrapperType nWrapperType,
                                              const char* pADFunctionName,
                                              const char* pFunctionName,
                                              const char* pClassName,
                                              const char* pVarSuffix,
                                              const char* pSubSuffix,
                                              const char* pModuleSuffix,
                                              const AdtStringList& Vars)
{
  bool  bMade = false;

  if ((pWorkingRoot         != 0) &&
      (pWrapperFunctionName != 0) && 
      (pADFunctionName      != 0) && 
      (pFunctionName        != 0) && 
      (pClassName           != 0) && 
      (pVarSuffix           != 0) && 
      (pSubSuffix           != 0) &&
      (pModuleSuffix        != 0))
  {
    // Note that in finding the module definition for COMMON variables we need
    // to use an elaborate approach because of how Tapenade behaviour has changed
    // over different versions. Originally Tapenade would always create a copy 
    // of COMMON, for instance COMMON_d when doing forward mode, and include it 
    // in the source code output for the AD'ed function. In current versions it
    // does not but I suspect might do if it needs to add a variable to COMMON
    // (not clear that it every does but have coded for the situation). The 
    // extra findObject calls are there to obtain the module definition in these
    // other scenarios as it will be needed to create the wrapper code. 
    string            sModuleName("COMMON");
    AdtFortranModule* pModule = (AdtFortranModule*)findObject("AdtFortranModule",
                                                              sModuleName,
                                                              false);

    if (pModule == 0)
    {
      string  sDiffModuleName("COMMON");

      sDiffModuleName += pModuleSuffix;

      pModule = (AdtFortranModule*)findObject("AdtFortranModule",
                                              sDiffModuleName,
                                              false);
    }

    if (pModule == 0)
    {
      pModule = (AdtFortranModule*)pWorkingRoot->findObject("AdtFortranModule",
                                                            sModuleName,
                                                            false);
    }
   
    if (pModule != 0)
    {
      bool        bIsFunction;
      bool        bSupported              = true;
      AdtParser*  pFuncOrSubSubprogram    = pWorkingRoot->findFunctionOrSubroutine(pFunctionName, bIsFunction);
      AdtParser*  pADFuncOrSubSubprogram  = findFunctionOrSubroutine(pADFunctionName, bIsFunction);

      if ((pFuncOrSubSubprogram   != 0) && 
          (pADFuncOrSubSubprogram != 0))
      {
        AdtFortranVariableInfo  VariableInfo(pFuncOrSubSubprogram, "");
        AdtFortranVariableInfo  ADVariableInfo(pADFuncOrSubSubprogram, pModule);
        const AdtStringList&    rArgList    = VariableInfo.argumentList();
        const AdtStringList&    rADArgList  = ADVariableInfo.argumentList();
        AdtStringListConstIter  Iter;

        // Found sub-routine or function. Now need to build code string for a new wrapper function or subroutine
        // with appropriately named arguments and add appropriate variable definitions to the module for 
        // arrays/variables that we need to add to COMMON. Then use the builder methods to create an object 
        // representation of that new code and splice the needed additions into the parse tree. That is add
        // one new function/subroutine and however many variables needed to COMMON.

        // Begin FUNCTION / SUBROUTINE
        AdtFile       FortranOutFunction(true);
        AdtFile       FortranOutModule(true);
        AdtFortran    FortranContext;
        AdtParser*    pRoot       = 0;
        AdtParser*    pCodeObject = 0;
        bool          bFirst      = true;
        const char*   sType       = bIsFunction ? "FUNCTION" : "SUBROUTINE";
        string        sCodeFunction;
        string        sCodeBody;
        string        sCodeModule;
        string        sDeclarations;
        string        sLastArg;

        sDeclarations = "INTEGER(4) :: cn\n";

        if (bIsFunction)
        {
          sDeclarations += "REAL(8) :: ";
          sDeclarations += pFunctionName;
          sDeclarations += "\n";
        }

        FortranOutModule.open(sCodeModule);

        FortranOutModule.write("MODULE COMMON");
        FortranOutModule.incrementIndent();
        FortranOutModule.newline();

        FortranOutFunction.open(sCodeFunction);

        FortranOutFunction.write(sType);
        FortranOutFunction.write(" ");
        FortranOutFunction.write(pWrapperFunctionName);
        FortranOutFunction.write("(");

        // Do argument list
        for (Iter = rADArgList.begin() ; Iter != rADArgList.end() ; ++Iter)
        {
          string       sDeclaration;
          const string rArg       = *Iter;
          bool         bNew       = !VariableInfo.hasVariable(rArg);
          bool         bWriteArg  = true;

          if (bNew)
          {
            // Add alternate variables.
            // For DIFF replace direction vector with direction scalar, add direction vector 
            // and initialise it in the code according to directon scalar.
            // For GRAD remove chaining vector and add vector to common and initialised to zero in code.
            if (rArg.eq(pFunctionName))
            {
              // The original function value from diff of a function which we can discard
              ADVariableInfo.buildVariableDeclaration(rArg, false, sDeclaration);

              bWriteArg = false;
            }
            else if (rArg.eq(pADFunctionName))
            {
              // The gradient return value from grad of a function which we must keep and return
            }
            else
            {
              // Other added variables
              string sIntent;
              string sLowerDim;
              string sUpperDim;
              ADVariableInfo.buildVariableDeclaration(rArg, false, sDeclaration);
              ADVariableInfo.intent(rArg, sIntent);
              ADVariableInfo.lowerDimension(rArg, 0, sLowerDim);
              ADVariableInfo.upperDimension(rArg, 0, sUpperDim);

              if ((ADVariableInfo.numberOfDimensions(rArg) == 2) && (sUpperDim.eq("nbdirsmax")))
              {
                // Argument added from MULTIDIFF or MULTIGRAD operation
                bool   bIsOut = sIntent.eq("OUT");

                FortranOutModule.write(sDeclaration);
                FortranOutModule.newline();

                switch (nWrapperType)
                {
                  case ForWrapper_DIFF:
                  {
                    break;
                  }

                  case ForWrapper_MULTIDIFF:
                  {
                    string  sNewArg;
                    string  sNewDeclaration("INTEGER(4), INTENT(IN):: ");

                    sNewArg = sLastArg + "_dir";

                    FortranOutFunction.write(", ");
                    FortranOutFunction.write(sNewArg);

                    sNewDeclaration += sNewArg;

                    sDeclarations += sNewDeclaration;
                    sDeclarations += "\n";

                    if (sUpperDim.length() > 0)
                    {
                      sCodeBody += "\nDO cn = " + sLowerDim + "," + sUpperDim + "\n";
                      sCodeBody += rArg + "(cn) = 0\n";
                      sCodeBody += "ENDDO\n\n";
                      sCodeBody += "IF (" + sNewArg + " >= " + sLowerDim + " .AND. " + sNewArg + " <= " + sUpperDim + ") THEN\n";
                      sCodeBody += rArg + "(" + sNewArg + ") = 1\n";
                      sCodeBody += "END IF\n\n";
                    }
                    else
                    {
                      sCodeBody += rArg + " = 0\n";
                      sCodeBody += "IF (" + sNewArg + " > 0) THEN\n";
                      sCodeBody += rArg + " = 1\n";
                      sCodeBody += "END IF\n\n";
                    }
                    break;
                  }

                  case ForWrapper_GRAD:
                  {
                    break;
                  }

                  case ForWrapper_MULTIGRAD:
                  {
                    break;
                  }

                  default:
                  {
                    FAIL();
                    break;
                  }
                }

                bWriteArg = false;
              }
              else if (ADVariableInfo.numberOfDimensions(rArg) > 1)
              {
                ::printf("WARNING: Differentiation with respect to variables of dimension greater than 1 not supported in wrapper function %s.\n", pWrapperFunctionName);

                bSupported = false;
              }
              else
              {
                bool   bIsOut = sIntent.eq("OUT");

                FortranOutModule.write(sDeclaration);
                FortranOutModule.newline();

                switch (nWrapperType)
                {
                  case ForWrapper_DIFF:
                  {
                    string  sNewArg;
                    string  sNewDeclaration("INTEGER(4), INTENT(IN):: ");

                    sNewArg = sLastArg + "_dir";

                    FortranOutFunction.write(", ");
                    FortranOutFunction.write(sNewArg);

                    sNewDeclaration += sNewArg;

                    sDeclarations += sNewDeclaration;
                    sDeclarations += "\n";

                    if (sUpperDim.length() > 0)
                    {
                      sCodeBody += "\nDO cn = " + sLowerDim + "," + sUpperDim + "\n";
                      sCodeBody += rArg + "(cn) = 0\n";
                      sCodeBody += "ENDDO\n\n";
                      sCodeBody += "IF (" + sNewArg + " >= " + sLowerDim + " .AND. " + sNewArg + " <= " + sUpperDim + ") THEN\n";
                      sCodeBody += rArg + "(" + sNewArg + ") = 1\n";
                      sCodeBody += "END IF\n\n";
                    }
                    else
                    {
                      sCodeBody += rArg + " = 0\n";
                      sCodeBody += "IF (" + sNewArg + " > 0) THEN\n";
                      sCodeBody += rArg + " = 1\n";
                      sCodeBody += "END IF\n\n";
                    }
                    break;
                  }

                  case ForWrapper_MULTIDIFF:
                  {
                    break;
                  }

                  case ForWrapper_GRAD:
                  {
                    break;
                  }

                  case ForWrapper_MULTIGRAD:
                  {
                    break;
                  }

                  default:
                  {
                    FAIL();
                    break;
                  }
                }

                bWriteArg = false;
              }
            }
          }

          if (bWriteArg)
          {
            if (!bFirst)
            {
              FortranOutFunction.write(", ");
            }

            ADVariableInfo.buildVariableDeclaration(rArg, true, sDeclaration);

            sDeclarations += sDeclaration;
            sDeclarations += "\n";

            FortranOutFunction.write(rArg);

            sLastArg = rArg;

            bFirst = false;
          }
        }

        FortranOutFunction.write(")");
        FortranOutFunction.incrementIndent();
        FortranOutFunction.newline();

        // Do arg declarations
        FortranOutFunction.writeLines(sDeclarations);

        // Do Use commands
        FortranOutFunction.write("USE DIFFSIZES");
        FortranOutFunction.newline();
        FortranOutFunction.write("USE COMMON");
        FortranOutFunction.newline();

        // Add function call
        if (bIsFunction)
        {
          sCodeBody += pWrapperFunctionName;
          sCodeBody += " = ";
          sCodeBody += pADFunctionName;
          sCodeBody += "(";

          bFirst = true;

          for (Iter = rADArgList.begin() ; Iter != rADArgList.end() ; ++Iter)
          {
            const string rArg = *Iter;

            if (!bFirst)
            {
              sCodeBody += ", ";
            }

            bFirst     = false;
            sCodeBody += rArg;
          }

          sCodeBody += ")\n";
        }
        else
        {
          sCodeBody += "CALL ";
          sCodeBody += pADFunctionName;
          sCodeBody += "(";

          bFirst = true;

          for (Iter = rADArgList.begin() ; Iter != rADArgList.end() ; ++Iter)
          {
            const string rArg = *Iter;

            if (!bFirst)
            {
              sCodeBody += ", ";
            }

            bFirst     = false;
            sCodeBody += rArg;
          }

          sCodeBody += ")\n";
        }

        // Do Code Body
        FortranOutFunction.writeLines(sCodeBody);

        // End FUNCTION / SUBROUTINE
        FortranOutFunction.decrementIndent();
        FortranOutFunction.newline();
        FortranOutFunction.write("END ");
        FortranOutFunction.write(sType);
        FortranOutFunction.write(" ");
        FortranOutFunction.write(pWrapperFunctionName);
        FortranOutFunction.newline();
        FortranOutFunction.close();

        if (bSupported)
        {
          // Add function
          bool bParsed = FortranContext.parseString(pRoot, sCodeFunction);

          pCodeObject = (AdtFortranBase*)pRoot;

          if (bParsed && (pCodeObject != 0))
          {
            pWorkingRoot->insertAfter(pFuncOrSubSubprogram->parent(), pCodeObject);
          }
          else
          {
            ::printf("%s\n", sCodeFunction.c_str());
          }

          UtlReleaseReference(pCodeObject);

          // End module declaration for adding new variables to COMMON module
          FortranOutModule.decrementIndent();
          FortranOutModule.newline();
          FortranOutModule.write("END MODULE");
          FortranOutModule.newline();
          FortranOutModule.close();

          // Add extra variable declarations to module
          bParsed = FortranContext.parseString(pRoot, sCodeModule);

          pCodeObject = (AdtFortranBase*)pRoot;

          if (bParsed && (pCodeObject != 0))
          {

          }
          else
          {
            ::printf("%s\n", sCodeModule.c_str());
          }

          UtlReleaseReference(pCodeObject);
        }
      }
    }
  }

  return (bMade);
}                                              

//  ----------------------------------------------------------------------------

AdtFortranBase* AdtFortranExecutableProgram::expressionBuild(const char* pCodeString,
                                                             bool bIncludeConditionalContext)
{
  AdtFortranBase* pCodeObject = 0;

  if (pCodeString != 0)
  {
    AdtFortran  FortranContext;
    AdtParser*  pRoot = 0;
    string      rCodeString("PROGRAM Fragment \n");
    bool        bParsed = false;

    if (bIncludeConditionalContext)
    {
      // AdtFortranConditionalBody container case
      rCodeString += "IF (.FALSE.) THEN \n";
      rCodeString += pCodeString;
      rCodeString += "\n END IF \n";
    }
    else
    {
      // AdtFortranBody container case
      rCodeString += pCodeString;
    }

    rCodeString += "\n END \n";

    bParsed = FortranContext.parseString(pRoot,
                                         rCodeString);

    pCodeObject = (AdtFortranBase*)pRoot;

    ASSERT(bParsed && (pCodeObject != 0));

    if (0)
    {
      string  sTest;
      AdtFile FortranOut;

      if (FortranOut.open(sTest))
      {
        pCodeObject->writeFortran(FortranOut);
        FortranOut.close();
      }
    }
  }

  return (pCodeObject);
}

//  ----------------------------------------------------------------------------

AdtFortranBase* AdtFortranExecutableProgram::expressionBuildInner(const char* pCodeString,
                                                                  AdtParser* pStmtObj,
                                                                  AdtParser*& pObjectToReplace,
                                                                  AdtParser*& pObjectContainer,
                                                                  AdtParser*& pReplacementContainer)
{
  AdtFortranBase* pRoot = 0;

  if (pStmtObj != 0)
  {
    pObjectToReplace      = pStmtObj->findAscendantWithClass("AdtFortranExecutableConstruct");
    pObjectContainer      = pObjectToReplace->parent();
    pReplacementContainer = 0;

    if (pObjectContainer->isType("AdtFortranBodyConstruct"))
    {
      pRoot                 = expressionBuild(pCodeString, false);
      pObjectToReplace      = pObjectToReplace->findAscendantWithClass("AdtFortranBodyConstruct");
      pObjectContainer      = pObjectContainer->parent();
      pReplacementContainer = pRoot->findObject("AdtFortranBody");
    }
    else if (pObjectContainer->isType("AdtFortranConditionalBody"))
    {
      AdtParser* pThenPart;

      pRoot     = expressionBuild(pCodeString, true);
      pThenPart = pRoot->findObject("AdtFortranThenPart");

      // We must first search for a AdtFortranThenPart object because AdtFortranConditionalBody is
      // used in the body of a DO construct as well as IF statements. This ensures we get the
      // IF statement one.
      pReplacementContainer = (pThenPart != 0) ? pThenPart->findObject("AdtFortranConditionalBody") : 0;
    }
    else
    {
      ::printf("FATAL ERROR: AdtFortranExecutableProgram::expressionBuildInner "
               "failure on line %d in file %s\nContext line %d, file %s\n",
               pStmtObj->lineNumber(),
               pStmtObj->fileName(),
               __LINE__,
               __FILE__);

      FAIL();
      AdtExit(-1);
    }

    if (0)
    {
      string  sTest;
      AdtFile FortranOut;

      if (FortranOut.open(sTest))
      {
        ((AdtFortranBase*)pReplacementContainer)->writeFortran(FortranOut);
        FortranOut.close();
      }
    }
  }

  return (pRoot);
}

//  ----------------------------------------------------------------------------

AdtFortranBase* AdtFortranExecutableProgram::expressionBuildAndReplace(const char* pCodeString,
                                                                       AdtParser* pStmtObj,
                                                                       AdtParserPtrList* pAddedList)
{
  AdtFortranBase* pContainer = 0;

  if (pStmtObj != 0)
  {
    AdtParser*      pObjectToReplace      = 0;
    AdtParser*      pObjectContainer      = 0;
    AdtParser*      pReplacementContainer = 0;
    AdtFortranBase* pRoot                 = expressionBuildInner(pCodeString,
                                                                 pStmtObj,
                                                                 pObjectToReplace,
                                                                 pObjectContainer,
                                                                 pReplacementContainer);

    if (pRoot != 0)
    {
      if ((pObjectToReplace       != 0) &&
          (pObjectContainer       != 0) &&
          (pReplacementContainer  != 0))
      {
        if (pAddedList != 0)
        {
          pReplacementContainer->enumerate(*pAddedList);
        }

        pObjectContainer->replace(pObjectToReplace, pReplacementContainer);
      }

      pContainer = (AdtFortranBase*)pObjectContainer;

      UtlReleaseReference(pRoot);
    }
  }

  return (pContainer);
}

//  ----------------------------------------------------------------------------

AdtFortranBase* AdtFortranExecutableProgram::expressionBuildAndInsert(const char* pCodeString,
                                                                      AdtParser* pStmtObj,
                                                                      bool bInsertAfter,
                                                                      AdtParserPtrList* pAddedList)
{
  AdtFortranBase* pContainer = 0;

  if (pStmtObj != 0)
  {
    AdtParser*      pObjectToInsertAt     = 0;
    AdtParser*      pObjectContainer      = 0;
    AdtParser*      pReplacementContainer = 0;
    AdtFortranBase* pRoot                 = expressionBuildInner(pCodeString,
                                                                 pStmtObj,
                                                                 pObjectToInsertAt,
                                                                 pObjectContainer,
                                                                 pReplacementContainer);

    if (pRoot != 0)
    {
      if ((pObjectToInsertAt      != 0) &&
          (pObjectContainer       != 0) &&
          (pReplacementContainer  != 0))
      {
        if (pAddedList != 0)
        {
          pReplacementContainer->enumerate(*pAddedList);
        }

        if (bInsertAfter)
        {
          pObjectContainer->insertAfter(pObjectToInsertAt, pReplacementContainer->objList());
        }
        else
        {
          pObjectContainer->insertBefore(pObjectToInsertAt, pReplacementContainer->objList());
        }
      }

      pContainer = (AdtFortranBase*)pObjectContainer;

      UtlReleaseReference(pRoot);
    }
  }

  return (pContainer);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::baseStackName(string& rBaseStackName,
                                                const char* pArrayName)
{
  ASSERT(pArrayName != 0);

  const char* pKeyword    = "stack";
  const char* pStackName  = ::strstr(pArrayName, pKeyword);

  if (pStackName != 0)
  {
    // Need to extract the base stack name which follows a pattern
    // {*}stack_{num}_{num}
    const size_t  nKeywordLen = ::strlen(pKeyword);
    const char*   pEnd        = pStackName + nKeywordLen;
    bool          bContinue   = (pEnd[0] != 0);
    int           nUnderscore = 0;

    while (bContinue)
    {
      switch(*pEnd)
      {
        case '_':
        {
          pEnd++;
          bContinue = (nUnderscore < 2) && (pEnd[0] != 0);
          nUnderscore++;
          break;
        }

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        {
          pEnd++;
          bContinue = (pEnd[0] != 0);
          break;
        }

        default:
        {
          bContinue = false;
          break;
        }
      }
    }

    rBaseStackName = string(pArrayName, pEnd - pArrayName);
  }
  else
  {
    rBaseStackName = "";
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::translatePushPopArrayCall(AdtFortranCallStmt* pCallObj,
                                                            const PushPopCall& rPushPopCallInfo,
                                                            AdtFortranModuleBody* pModuleBody,
                                                            int nIteration,
                                                            int nFnNumber,
                                                            AdtStringByStringMap& rNewLocalsMap,
                                                            const AdtFortranVariableInfo& rVariableInfo)
{
  bool  bRemoved = false;

  if ((pCallObj != 0) && (rPushPopCallInfo.ArgsExpected == 2))
  {
    AdtFortranSectionSubscriptList* pSectionSubscriptList = (AdtFortranSectionSubscriptList*)pCallObj->findDescendant("SectionSubscriptList");

    if (pSectionSubscriptList != 0)
    {
      size_t nArgs = pSectionSubscriptList->listSize();

      if (rPushPopCallInfo.ArgsExpected == nArgs)
      {
        int nTriplets = 0;

        if (!pSectionSubscriptList->hasSlice(nTriplets))
        {
          const AdtParserPtrList&           rObjList        = pSectionSubscriptList->objList();
          AdtParserPtrListConstIter         Iter            = rObjList.begin();
          const AdtFortranSectionSubscript* pArg1_Subscript = (const AdtFortranSectionSubscript*)(const AdtParser*)*Iter;

          Iter++;

          const AdtFortranSectionSubscript* pArg2_Subscript = (const AdtFortranSectionSubscript*)(const AdtParser*)*Iter;

          if ((pArg1_Subscript != 0) && (pArg2_Subscript != 0))
          {
            string                        sArg1;
            string                        sArg2;
            AdtFile                       FortranOut;

            FortranOut.open(sArg1);
            pArg1_Subscript->writeFortran(FortranOut);
            FortranOut.close();

            FortranOut.open(sArg2);
            pArg2_Subscript->writeFortran(FortranOut);
            FortranOut.close();

            if ((::strstr(sArg1, "stack")    != 0) &&
                pArg1_Subscript->isSimple()        &&
                (sArg2.icompare("dim_stack") == 0))
            {
              string            rCodeString;
              string            sBaseStackName;
              AdtFortranLblDef* pLblDef = (AdtFortranLblDef*)pCallObj->findDescendant("LblDef");

              if (pLblDef != 0)
              {
                FortranOut.open(rCodeString);
                pLblDef->writeFortran(FortranOut);
                FortranOut.close();

                rCodeString += " ";
              }

              baseStackName(sBaseStackName,
                            sArg1);

              switch(rPushPopCallInfo.CallType)
              {
                case PushArrayCall:
                {
                  // need to translate,
                  //
                  //  CALL PUSHARRAY(stack, dim_stack)
                  //
                  // into,
                  //
                  //  CALL PUSHARRAY(stack, stacki)
                  //  CALL PUSHINTEGER4(stacki)
                  //
                  rCodeString += "CALL " + string(rPushPopCallInfo.CallName) + "(" + sArg1 + "," + sBaseStackName + "i)\n";
                  rCodeString += "CALL PUSHINTEGER4(" + sBaseStackName + "i)\n";
                  break;
                }

                case PopArrayCall:
                {
                  // need to translate,
                  //
                  //  CALL POPARRAY(stack, dim_stack)
                  //
                  // is translated to,
                  //
                  //  CALL POPINTEGER4(saved_stacki)
                  //  CALL POPARRAY(stack, saved_stacki)
                  //
                  // where saved_stacki is a local scope variable.
                  string  sLocalIndexName("saved_" + sBaseStackName + "i");

                  createLocalVar(sLocalIndexName,
                                 ForType_INTEGER,
                                 pCallObj,
                                 rNewLocalsMap,
                                 rVariableInfo);

                  rCodeString += "CALL POPINTEGER4(" + sLocalIndexName + ")\n";
                  rCodeString += "CALL " + string(rPushPopCallInfo.CallName) + "(" + sArg1 + "," + sLocalIndexName + ")\n";
                  break;
                }

                case PushCall:
                case LookCall:
                case PopCall:
                default:
                {
                  ::printf("FATAL ERROR: AdtFortranExecutableProgram::translatePushPopArrayCall "
                           "failure on line %d in file %s\nContext line %d, file %s\n",
                           pCallObj->lineNumber(),
                           pCallObj->fileName(),
                           __LINE__,
                           __FILE__);

                  FAIL();
                  AdtExit(-1);
                  break;
                }
              }

              expressionBuildAndReplace(rCodeString, pCallObj);
            }
          }
        }
      }
    }
  }

  return (bRemoved);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::removePushPopCall(AdtFortranCallStmt* pCallObj,
                                                    const PushPopCall& rPushPopCallInfo,
                                                    AdtFortranModuleBody* pModuleBody,
                                                    int nIteration,
                                                    int nFnNumber,
                                                    AdtStringList& rNewAttributeList,
                                                    AdtStringByStringMap& rNewAttributeMap,
                                                    AdtStringByStringMap& rNewLocalsMap,
                                                    const AdtFortranVariableInfo& rVariableInfo)
{
  bool  bRemoved = false;

  if (pCallObj != 0)
  {
    string                          sCallExpression;
    AdtFile                         StringFile;
    AdtFortranSectionSubscriptList* pSectionSubscriptList = (AdtFortranSectionSubscriptList*)pCallObj->findDescendant("SectionSubscriptList");

    StringFile.open(sCallExpression);
    pCallObj->writeFortran(StringFile);
    StringFile.close();

    if (pSectionSubscriptList != 0)
    {
      size_t nArgs = pSectionSubscriptList->listSize();

      if (rPushPopCallInfo.ArgsExpected == nArgs)
      {
        int nTriplets = 0;

        if (!pSectionSubscriptList->hasSlice(nTriplets))
        {
          // Remove PUSH / POP calls by replacing them with array equivalents
          const AdtParserPtrList&           rObjList        = pSectionSubscriptList->objList();
          AdtParserPtrListConstIter         Iter            = rObjList.begin();
          const AdtFortranSectionSubscript* pArg1_Subscript = (const AdtFortranSectionSubscript*)(const AdtParser*)*Iter;

          Iter++;

          const AdtFortranSectionSubscript* pArg2_Subscript = nArgs > 1 ? (const AdtFortranSectionSubscript*)(const AdtParser*)*Iter : 0;

          if (pArg1_Subscript != 0)
          {
            string                        rCodeString;
            string                        sLabel;
            string                        sIndexName;
            string                        sStackName;
            string                        sArg1;
            string                        sArg2;
            AdtFile                       FortranOut;
            AdtStringByStringMapIter      Iter;
            AdtFortran                    FortranContext;
            AdtFortranLblDef*             pLblDef = (AdtFortranLblDef*)pCallObj->findDescendant("LblDef");

            if (pLblDef != 0)
            {
              FortranOut.open(sLabel);
              pLblDef->writeFortran(FortranOut);
              FortranOut.close();

              rCodeString += sLabel;
              rCodeString += " ";
            }

            FortranOut.open(sArg1);
            pArg1_Subscript->writeFortran(FortranOut);
            FortranOut.close();

            if (pArg2_Subscript != 0)
            {
              FortranOut.open(sArg2);
              pArg2_Subscript->writeFortran(FortranOut);
              FortranOut.close();
            }

            createStackVarNames(sStackName,
                                sIndexName,
                                rPushPopCallInfo.BaseStackName,
                                nIteration,
                                nFnNumber);

            Iter = rNewAttributeMap.find(sStackName);

            if (Iter == rNewAttributeMap.end())
            {
              rNewAttributeList.push_back(sStackName);
              rNewAttributeList.push_back(sIndexName);
              rNewAttributeMap.insert(AdtStringByStringMap::value_type(sStackName, sStackName));
              rNewAttributeMap.insert(AdtStringByStringMap::value_type(sIndexName, sIndexName));

              if (pModuleBody != 0)
              {
                AdtParser*            pRoot = 0;
                AdtFortranModuleBody* pReplacementBody;
                string                rDeclString("MODULE Fragment\n");

                rDeclString += "INTEGER " + sIndexName + "\n";
                rDeclString += string(rPushPopCallInfo.VarTypeName) + " " + sStackName + "(dim_stack)\nENDMODULE\n";

                FortranContext.parseString(pRoot,
                                           rDeclString);

                pReplacementBody = (AdtFortranModuleBody*)pRoot->findObject("AdtFortranModuleBody");
                pModuleBody->addListCopy(pReplacementBody);

                UtlReleaseReference(pRoot);
              }
            }

            bool bIsArrayOp = false;
            bool bIsPush    = false;

            switch(rPushPopCallInfo.CallType)
            {
              case PushArrayCall:
              {
                bIsPush = true;
                // fall thru
              }
              case PopArrayCall:
              {
                bIsArrayOp = true;

                if (AdtFortranBase::PushPopDisable)
                {
                  // No need to process as we kill Array pushes and pops in this case.
                  break;
                }

                // FIX ME. Need to fix this code as it assumes only whole arrays
                // will be pushed. It is possible that Array slices can be pushed
                // and in this current code it will fail.
                bool bIsStackVar = (::strstr(sArg1, "stack") != 0);

                // Change. If the var is a stack it has no size comment. It is a
                // vector and the size can be determined
                if ((rVariableInfo.hasVariable(sArg1) || bIsStackVar) &&
                    pArg1_Subscript->isSimple()                       &&
                    (pArg2_Subscript != 0))
                {
                  int         cn;
                  int         nRepeat = 0;
                  int         nDims   = bIsStackVar ? 1 : rVariableInfo.numberOfDimensions(sArg1);
                  const char* pChar   = AdtParse::nextWord(sArg2);
                  string      sIndexedArg(sArg1);
                  string      sCount;

                  sIndexedArg += "(";

                  for (cn = 0 ; cn < nDims ; cn++)
                  {
                    string sLowerDim;
                    string sUpperDim;
                    bool   bAddCode = false;

                    if (bIsStackVar)
                    {
                      // We initialise to [1:sArg2] because in the case of stack
                      // the base index is always 1 and the size will be in the
                      // push/pop array call because we put it there through
                      // pre-processing
                      sLowerDim = "1";
                      sUpperDim = sArg2;
                    }

                    pChar = AdtParse::nextWord(pChar);

                    if ((nRepeat == 0) && AdtParse::matchWord(pChar, "*"))
                    {
                      string  sPower;

                      AdtParse::extractWord(sPower, "*", pChar, false);
                      nRepeat = ::atoi(sPower) - 1;
                    }

                    if ((nRepeat > 0) || AdtParse::extractWord(sCount, "*", pChar))
                    {
                      char  sLoopVarName[16]  = {0};

                      if (nRepeat == 0)
                      {
                        AdtParse::matchWord(pChar, "*");
                      }
                      else
                      {
                        nRepeat--;
                      }

                      rVariableInfo.lowerDimension(sArg1, cn, sLowerDim);
                      rVariableInfo.upperDimension(sArg1, cn, sUpperDim);

                      // Create a loop variable
                      ::sprintf(sLoopVarName, "ix_%d___", cn);

                      createLocalVar(sLoopVarName,
                                     ForType_INTEGER,
                                     pCallObj,
                                     rNewLocalsMap,
                                     rVariableInfo);

                      string sLoopVar(sLoopVarName);

                      sIndexedArg += sLoopVarName;

                      if (cn < nDims - 1)
                      {
                        sIndexedArg += ",";
                      }

                      if (bIsPush)
                      {
                        rCodeString += "DO " + sLoopVar + "=" + sLowerDim + ",(" + sLowerDim + "+" + sCount + "-1)\n";
                      }
                      else
                      {
                        // Need to reverse the order of looping so we don't end up swapping the order
                        // of the numbers in the saved and restored arrays.
                        rCodeString += "DO " + sLoopVar + "=(" + sLowerDim + "+" + sCount + "-1)," + sLowerDim + ",-1\n";
                      }
                    }
                    else
                    {
                      ::printf("FATAL ERROR: AdtFortranExecutableProgram::removePushPopCall "
                               "failure on line %d in file %s converting expression:\n %s\n"
                               "Cannot determine loop indices.\nContext line %d, file %s\n",
                                pCallObj->lineNumber(),
                                pCallObj->fileName(),
                                sCallExpression.c_str(),
                                __LINE__,
                                __FILE__);

                      FAIL();
                      AdtExit(-1);
                    }
                  }

                  sIndexedArg += ")";


                  if (rPushPopCallInfo.CallType == PushArrayCall)
                  {
                    // Increment Stack
                    rCodeString += sIndexName + "=" + sIndexName + "+1\n";

                    // Push operation
                    rCodeString += sStackName + "(" + sIndexName + ")=" + sIndexedArg + "\n";
                  }
                  else
                  {
                    // Pop operation
                    rCodeString += sIndexedArg + "=" + sStackName + "(" + sIndexName + ")\n";

                    // Decrement Stack
                    rCodeString += sIndexName + "=" + sIndexName + "-1\n";
                  }

                  for (cn = 0 ; cn < nDims ; cn++)
                  {
                    rCodeString += "END DO\n";
                  }
                }
                else
                {
                  ::printf("FATAL ERROR: AdtFortranExecutableProgram::removePushPopCall "
                           "failure on line %d in file %s converting expression:\n %s\n"
                           "%s has no size information.\nContext line %d, file %s\n",
                           pCallObj->lineNumber(),
                           pCallObj->fileName(),
                           sCallExpression.c_str(),
                           sArg1.c_str(),
                           __LINE__,
                           __FILE__);

                  FAIL();
                  AdtExit(-1);
                }
                break;
              }

              case PushCall:
              {
                // Increment Stack
                rCodeString += sIndexName + "=" + sIndexName + "+1\n";

                // Push operation
                rCodeString += sStackName + "(" + sIndexName + ")=" + sArg1 + "\n";
                break;
              }

              case LookCall:
              {
                // Look operation
                rCodeString += sArg1 + "=" + sStackName + "(" + sIndexName + ")\n";
                break;
              }

              case PopCall:
              {
                // Pop operation
                rCodeString += sArg1 + "=" + sStackName + "(" + sIndexName + ")\n";

                // Decrement Stack
                rCodeString += sIndexName + "=" + sIndexName + "-1\n";
                break;
              }

              default:
              {
                ::printf("FATAL ERROR: AdtFortranExecutableProgram::removePushPopCall "
                         "failure on line %d in file %s converting expression:\n %s\n "
                         "Context line %d, file %s\n",
                         pCallObj->lineNumber(),
                         pCallObj->fileName(),
                         sCallExpression.c_str(),
                         __LINE__,
                         __FILE__);

                FAIL();
                AdtExit(-1);
                break;
              }
            }

            if (AdtFortranBase::PushPopDisable && bIsArrayOp)
            {
              if (sLabel.length() != 0)
              {
                // The line we are removing has a label so we need to replace
                // the line with a NOP label
                rCodeString = sLabel + " CONTINUE\n";

                expressionBuildAndReplace(rCodeString, pCallObj);
              }
              else
              {
                AdtParser*  pObjectToRemove   = pCallObj->findAscendantWithClass("AdtFortranExecutableConstruct");
                AdtParser*  pObjectContainer  = pObjectToRemove->parent();

                if (pObjectContainer->isType("AdtFortranBodyConstruct"))
                {
                  pObjectToRemove   = pObjectContainer;
                  pObjectContainer  = pObjectToRemove->parent();
                }

                pObjectContainer->remove(pObjectToRemove);
              }
            }
            else
            {
              expressionBuildAndReplace(rCodeString, pCallObj);
            }

            bRemoved = true;
          }
        }
        else
        {
          ::printf("MERGE ERROR : slice expression not allowed in %s call on "
                   "line %d in file %s converting expression:\n %s\n",
                   rPushPopCallInfo.CallName,
                   lineNumber(),
                   fileName(),
                   sCallExpression.c_str());
          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        ::printf("MERGE ERROR : wrong number of arguments in %s call on "
                 "line %d in file %s converting expression:\n %s\n",
                 rPushPopCallInfo.CallName,
                 lineNumber(),
                 fileName(),
                 sCallExpression.c_str());
        FAIL();
        AdtExit(-1);
      }
    }
  }

  return (bRemoved);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::enumerateLinkages(const char* pFunctionName,
                                                    const AdtParserPtrByStringMap& rFunctionMap,
                                                    AdtStringByStringMap& rFunctionLinkagesMap) const
{
  if (pFunctionName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = rFunctionMap.find(pFunctionName);

    if (Iter != rFunctionMap.end())
    {
      AdtParser* pNewFunctionObj = (*Iter).second;

      if (pNewFunctionObj != 0)
      {
        AdtParserPtrList  rNameList;

        rFunctionLinkagesMap.insert(AdtStringByStringMap::value_type(pFunctionName, pFunctionName));

        pNewFunctionObj->findObjects(rNameList, "AdtFortranName");

        for (AdtParserPtrListConstIter ListIter = rNameList.begin() ; ListIter != rNameList.end() ; ++ListIter)
        {
          AdtParser*  pNameObj = *ListIter;

          if ((pNameObj != 0) && (pNameObj->name() != pFunctionName))
          {
            // Note that we only consider Primary expressions and Call statements
            // when looking at linkages. This is because Tapenade has a habbit
            // of putting in superfluous EXTERNALS when not needed.
            if ((pNameObj->findAscendantWithClassLineage("AdtFortranPrimary")   != 0) ||
                (pNameObj->findAscendantWithClassLineage("AdtFortranCallStmt")  != 0))
            {
              AdtStringByStringMapConstIter LinkedIter = rFunctionLinkagesMap.find(pNameObj->name());

              if (LinkedIter == rFunctionLinkagesMap.end())
              {
                enumerateLinkages(pNameObj->name(),
                                  rFunctionMap,
                                  rFunctionLinkagesMap);
              }
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::mergeWith(AdtFortranExecutableProgram* pSource,
                                            AdtFortranExecutableProgram* pCallExpandRoot,
                                            AdtStringList* pNewFunctionsList,
                                            int nIteration,
                                            AdtStringList& rNewMethodList,
                                            AdtStringByStringMap& rNewMethodMap,
                                            AdtStringList& rNewAttributeList,
                                            AdtStringByStringMap& rNewAttributeMap,
                                            const char* pParentClassName,
                                            const char* pModuleSuffix,
                                            AdtStringList* pNewLocalsList,
                                            AdtStringByStringMap* pNewLocalsMap)
{
  bool bMerged = false;

  if (pSource != 0)
  {
    //Search through and add any new variable definitions that tapenade has added
    //to the module definition in the working fortran source code.
    AdtFortranModuleBody* pModuleBody     = 0;
    AdtParser*            pDestModuleBody = 0;
    string                ClassPrefix(pParentClassName);

    ClassPrefix += "__";

    if (pNewLocalsList == 0)
    {
      pNewLocalsList  = &rNewAttributeList;
      pNewLocalsMap   = &rNewAttributeMap;
    }

    string      SourceName("COMMON");
    bool        bFailed       = true;

    if (pModuleSuffix != 0)
    {
      SourceName += pModuleSuffix;
    }

    AdtParser*  pDestModule   = findObject("AdtFortranModule", "COMMON");
    AdtParser*  pSourceModule = pSource->findObject("AdtFortranModule", SourceName);

    if (pDestModule != 0)
    {
      bFailed = false;

      pDestModuleBody = pDestModule->findDescendant("ModuleBody");
      pModuleBody     = (AdtFortranModuleBody*)pDestModuleBody;

      if (pSourceModule != 0)
      {
        AdtParser*  pSourceModuleBody;

        pSourceModuleBody = pSourceModule->findDescendant("ModuleBody");

        if ((pDestModuleBody != 0) && (pSourceModuleBody != 0))
        {
          AdtParserPtrList      TypeDeclList;
          AdtParserPtrListIter  Iter;

          //Find all the type definitions that tapenade created and step through them
          pSourceModuleBody->findObjects(TypeDeclList, "AdtFortranTypeDeclarationStmt");

          for (Iter = TypeDeclList.begin() ; Iter != TypeDeclList.end() ; ++Iter)
          {
            AdtParser*  pTypeDeclObj = *(Iter);

            if ((pTypeDeclObj != 0) &&
                (pTypeDeclObj->findAscendantWithClassLineage("AdtFortranSpecificationPartConstruct,AdtFortranModuleBodyContent") != 0))
            {
              //Make a temporary copy of the type definition and remove any variable
              //names already defined in our module from it. If there are any left
              //then add the copied definition to our module.
              AdtFortranTypeDeclarationStmt*  pTypeDeclCopy = (AdtFortranTypeDeclarationStmt*)pTypeDeclObj->copy();

              if (pTypeDeclCopy->removeSharedNames(pDestModuleBody, &rNewAttributeList, &rNewAttributeMap))
              {
                AdtParser* pSpecificationPart = new AdtFortranSpecificationPartConstruct(0, 0, 0, pTypeDeclCopy, 0, 0, 0, 0);
                AdtParser* pBodyContent       = new AdtFortranModuleBodyContent(pSpecificationPart, 0, 0);

                pDestModuleBody->add(pBodyContent);

                UtlReleaseReference(pBodyContent);
                UtlReleaseReference(pSpecificationPart);
              }

              UtlReleaseReference(pTypeDeclCopy);
            }
          }
        }
      }
    }

    if (bFailed)
    {
      ::printf("MERGE ERROR : Missing destination MODULE "
               "line %d in file %s\n", lineNumber(),
                                       fileName());
      FAIL();
      AdtExit(-1);
    }

    //Now do the function / Subroutine merging.
    AdtParserPtrList  DestFunctionList;
    AdtParserPtrList  SrcFunctionList;

    findObjects(DestFunctionList,
                "AdtFortranFunctionSubprogram",
                0,
                false,
                "AdtFortranProgramUnit");

    findObjects(DestFunctionList,
                "AdtFortranSubroutineSubprogram",
                0,
                false,
                "AdtFortranProgramUnit");

    pSource->findObjects(SrcFunctionList,
                         "AdtFortranFunctionSubprogram",
                         0,
                         false,
                         "AdtFortranProgramUnit");

    pSource->findObjects(SrcFunctionList,
                         "AdtFortranSubroutineSubprogram",
                         0,
                         false,
                         "AdtFortranProgramUnit");

    AdtStringByStringMap  rSrcFunctionLinkagesMap;
    bool                  bAddingNewFunctions = false;

    if ((pNewFunctionsList != 0) && (pNewFunctionsList->size() > 0))
    {
      // Note that we must only add functions to the module that are actually
      // required (ie. those that link to the AD generated functions). The
      // latest versions of Tapenade have a habbit of providing extra
      // differentiated functions that are never actually linked to by the
      // differential we ask for. If we were to add this superfluous code
      // then the code base will grow very large very quickly, to the point
      // that tapenade will crash because the source file is too big for it
      // to process.
      AdtStringListConstIter  rNewFuncIter;
      AdtParserPtrByStringMap rSrcFunctionMap;

      pSource->listToMap(rSrcFunctionMap, SrcFunctionList);

      for (rNewFuncIter = pNewFunctionsList->begin() ; rNewFuncIter != pNewFunctionsList->end() ; ++rNewFuncIter)
      {
        const string& rNewFunctionName = *rNewFuncIter;

        enumerateLinkages(rNewFunctionName,
                          rSrcFunctionMap,
                          rSrcFunctionLinkagesMap);
      }

      bAddingNewFunctions = true;
    }

    int                       nFnNumber = 1;
    AdtParserPtrListConstIter Iter;
    AdtParserPtrByStringMap   DestFunctionMap;
    AdtParserPtrList          CallExpandList;

    listToMap(DestFunctionMap, DestFunctionList);

    AdtParserPtrByStringMap   CompleteFunctionMap;

    listToMap(CompleteFunctionMap, SrcFunctionList);
    listToMap(CompleteFunctionMap, DestFunctionList);

    if (pCallExpandRoot != 0)
    {
      pCallExpandRoot->findObjects(CallExpandList, "AdtFortranCallExpand");
    }

    for (Iter = SrcFunctionList.begin() ; Iter != SrcFunctionList.end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      // Only add functions that are linked to when new functions are being added.
      // if bAddingNewFunctions is false we should add unconditionally.
      if ((pObj != 0) &&
          (!bAddingNewFunctions || (rSrcFunctionLinkagesMap.find(pObj->name()) != rSrcFunctionLinkagesMap.end())))
      {
        AdtParserPtrByStringMapIter DestIter = DestFunctionMap.find(pObj->name());

        if ((DestIter == DestFunctionMap.end()) && (pObj->parent() != 0))
        {
          //Add the new tapenade generated function
          AdtParser*  pParentObjCopy  = pObj->parent()->copy();
          AdtParser*  pObjCopy        = pParentObjCopy->findObject(pObj->type());

          if (rNewMethodMap.find(pObjCopy->name()) == rNewMethodMap.end())
          {
            add(pParentObjCopy);

            rNewMethodMap[pObjCopy->name()] = pObjCopy->name();
            rNewMethodList.push_back(pObjCopy->name());

            //Change the USE statement to point to COMMON and remove other USE statements
            AdtParserPtrList      UseList;
            AdtParserPtrListIter  UseIter;
            bool                  bFirstUse = true;

            pObjCopy->findObjects(UseList, "AdtFortranUseStmt");

            for (UseIter = UseList.begin() ; UseIter != UseList.end() ; ++UseIter)
            {
              AdtParser*  pUseStmt = *UseIter;

              if (pUseStmt != 0)
              {
                if (bFirstUse)
                {
                  AdtParser*  pName = pUseStmt->findDescendant("Name");

                  if (pName != 0)
                  {
                    pName->name("COMMON");

                    bFirstUse = false;
                  }
                }
                else
                {
                  AdtParser*  pParentBodyConstruct = pUseStmt->findAscendantWithClassLineage("AdtFortranSpecificationPartConstruct,AdtFortranBodyConstruct");

                  if ((pParentBodyConstruct != 0) && (pParentBodyConstruct->parent() != 0))
                  {
                    pParentBodyConstruct->lock();
                    pParentBodyConstruct->parent()->remove(pParentBodyConstruct);
                    UtlReleaseReference(pParentBodyConstruct);
                  }
                }
              }
            }

            const char*               pNext           = 0;
            const char*               pSuffix         = pObjCopy->name().findMatch(ClassPrefix, pNext, true, false);
            AdtFortranFunctionStmt*   pOrigFuncObj    = (AdtFortranFunctionStmt*)pObj->findDescendant("FunctionStmt");
            AdtFortranSubroutineStmt* pOrigSubObj     = (AdtFortranSubroutineStmt*)pObj->findDescendant("SubroutineStmt");
            AdtFortranFunctionStmt*   pFunctionObj    = (AdtFortranFunctionStmt*)pObjCopy->findDescendant("FunctionStmt");
            AdtFortranSubroutineStmt* pSubroutineObj  = (AdtFortranSubroutineStmt*)pObjCopy->findDescendant("SubroutineStmt");

            if (pFunctionObj != 0)
            {
              pFunctionObj->initialise(&CompleteFunctionMap);
            }

            if (pSubroutineObj != 0)
            {
              pSubroutineObj->initialise(&CompleteFunctionMap);
            }

            AdtFortranDeclarations*   pDeclarations   = (pOrigFuncObj != 0) ? pOrigFuncObj->declarations() : ((pOrigSubObj != 0) ? pOrigSubObj->declarations() : 0);
            AdtFortranBody*           pBody           = (AdtFortranBody*)pObjCopy->findDescendant("Body");
            bool                      bInitCodeAdded  = false;
            string                    sInitLocalsCode;

            //Look for new output variables and remove the class prefix from them
            pDeclarations->removeOutputVarPrefix(pObjCopy, pParentClassName);

            //Eliminate unused local variables and initialise unitialised variables.
            if ((pSuffix          != 0) &&
                (pDestModuleBody  != 0) &&
                (pDeclarations    != 0) &&
                (pBody            != 0))
            {
              AdtParserPtrList      EntityDeclList;
              AdtParserPtrListIter  EntityDeclIter;

              pObjCopy->findObjects(EntityDeclList, "AdtFortranEntityDecl");

              for (EntityDeclIter = EntityDeclList.begin() ; EntityDeclIter != EntityDeclList.end() ; ++EntityDeclIter)
              {
                AdtFortranEntityDecl* pEntityDecl = (AdtFortranEntityDecl*)(AdtParser*)(*EntityDeclIter);

                if (pDeclarations->isLocal(pEntityDecl->name()) &&
                    (pEntityDecl                          != 0) &&
                    (pEntityDecl->parent()                != 0))
                {
                  AdtParserPtrList      NameObjList;
                  AdtParserPtrListIter  NameObjIter;
                  AdtParser*            pFirstUseObj    = 0;
                  AdtParser*            pEntityDeclObj  = 0;
                  bool                  bLocalVarIsUsed = false;

                  pBody->findObjects(NameObjList, "AdtFortranName", pEntityDecl->name(), false);

                  for (NameObjIter = NameObjList.begin() ; NameObjIter != NameObjList.end() ; ++NameObjIter)
                  {
                    AdtParser*  pNameObj = *NameObjIter;
                    AdtParser*  pFindObj;

                    pFindObj = pNameObj->findAscendantWithClass("AdtFortranEntityDecl");

                    if (pFindObj != 0)
                    {
                      pEntityDeclObj = pFindObj;
                    }
                    else
                    {
                      pFirstUseObj    = pNameObj;
                      bLocalVarIsUsed = true;
                      break;
                    }
                  }

                  if (bLocalVarIsUsed)
                  {
                    bool  bIsArray  = (pEntityDecl->numberOfDimensions() > 0);

                    // Local var is present in body. Check to see if it needs initialisation.
                    // If it is an array we don't need initialisation as we assume array
                    // construction will do that.
                    if ((pFirstUseObj->parent() != 0) && !bIsArray)
                    {
                      if ((pFirstUseObj->parent()->isType("AdtFortranAssignmentStmt")     == 0) &&
                          (pFirstUseObj->findAscendantWithClass("AdtFortranLoopControl")  == 0))
                      {
                        // Not LHS so requires initialisation.
                        sInitLocalsCode += pEntityDecl->name() + "=0\n";

                        bInitCodeAdded = true;
                      }
                    }
                  }
                  else
                  {
                    AdtParser*  pEntityDeclListObj = pEntityDeclObj->parent();

                    // Local var is not present in body. remove the declaration
                    if (pEntityDeclListObj->listSize() > 1)
                    {
                      // More than one declaration of this type so just remove the named variable
                      pEntityDeclListObj->remove(pEntityDeclObj);
                    }
                    else
                    {
                      // Only one variable so remove the entire statement
                      AdtParser*  pBodyConstructObj = pEntityDeclObj->findAscendantWithClass("AdtFortranBodyConstruct");

                      pBody->remove(pBodyConstructObj);
                    }

                    pDeclarations->remove(pEntityDecl->name());
                  }
                }
              }
            }

            if ((bInitCodeAdded) && (pBody != 0))
            {
              AdtFortranBase* pCodeObj = expressionBuild(sInitLocalsCode, false);

              if (pCodeObj != 0)
              {
                // Find the code body
                AdtParser*  pBodyObj                = pCodeObj->findObject("AdtFortranBody");
                AdtParser*  pExecutableConstructObj = pBody->findObject("AdtFortranExecutableConstruct");

                if ((pBodyObj                           != 0) &&
                    (pExecutableConstructObj            != 0) &&
                    (pExecutableConstructObj->parent()  != 0))
                {
                  AdtParserPtrListConstIter Iter;
                  const AdtParserPtrList&   rList = pBodyObj->objList();

                  // Loop through all the body constructs making copies and
                  // adding the copies to the code body in the appropriate place
                  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
                  {
                    const AdtParser*  pBodyConstructObj = *Iter;

                    if (pBodyConstructObj != 0)
                    {
                      AdtParser*  pCopyBodyConstructObj = pBodyConstructObj->copy();

                      pBody->insertBefore(pExecutableConstructObj->parent(), pCopyBodyConstructObj);

                      UtlReleaseReference(pCopyBodyConstructObj);
                    }
                  }
                }

                UtlReleaseReference(pCodeObj);
              }
            }

            // modify PUSH/POP ARRAY stack pushes to include the saving
            // of size in the operation. That is,
            //
            //  CALL PUSHARRAY(stack, dim_stack)
            //
            // is translated to,
            //
            //  CALL PUSHARRAY(stack, stacki)
            //  CALL PUSHINTEGER4(stacki)
            //
            // and
            //
            //  CALL POPARRAY(stack, dim_stack)
            //
            // is translated to,
            //
            //  CALL POPINTEGER4(stack_sz)
            //  CALL POPARRAY(stack, stack_sz)
            //
            // where stack_sz is a local scope variable.
            AdtParserPtrListIter          CallExpandIter;
            AdtParserPtrList              CallList;
            AdtParserPtrByStringMultiMap  CallMap;
            AdtFortranVariableInfo        VariableInfo(pObjCopy);

            pObjCopy->findObjects(CallList, "AdtFortranCallStmt");
            listToMap(CallMap, CallList);

            if (WithStackSubstitution)
            {
              //Need to translate these calls
              // PUSHINTEGER1ARRAY
              // POPINTEGER1ARRAY
              // PUSHINTEGER4ARRAY
              // POPINTEGER4ARRAY
              // PUSHINTEGER8ARRAY
              // POPINTEGER8ARRAY
              // PUSHREAL4ARRAY
              // POPREAL4ARRAY
              // PUSHREAL8ARRAY
              // POPREAL8ARRAY
              // PUSHREAL16ARRAY
              // POPREAL16ARRAY

              AdtStringByStringMap    rNewLocalsMap;
              int                     cn;

              for (cn = 0 ; cn < sizeof(PushPopCalls) / sizeof(PushPopCalls[0]) ; cn++)
              {
                switch(PushPopCalls[cn].CallType)
                {
                  case PushArrayCall:
                  case PopArrayCall:
                  {
                    AdtParserPtrByStringMultiMapIter CallIter;

                    for (CallIter = CallMap.lower_bound(PushPopCalls[cn].CallName) ; CallIter != CallMap.upper_bound(PushPopCalls[cn].CallName) ; ++CallIter)
                    {
                      //push/pop array call translation.
                      AdtFortranCallStmt*     pCallObj = (AdtFortranCallStmt*)(AdtParser*)(*CallIter).second;

                      translatePushPopArrayCall(pCallObj,
                                                PushPopCalls[cn],
                                                pModuleBody,
                                                nIteration,
                                                nFnNumber,
                                                rNewLocalsMap,
                                                VariableInfo);
                    }
                    break;
                  }

                  default:
                  {
                    break;
                  }
                }
              }

              //Translate PUSH/POP stack calls to equivalent arrays to allow for
              //further differentiation
              CallList.clear();
              CallMap.clear();

              pObjCopy->findObjects(CallList, "AdtFortranCallStmt");
              listToMap(CallMap, CallList);

              //Need to translate these calls
              // PUSHCHARACTERARRAY
              // POPCHARACTERARRAY
              // PUSHCHARACTER
              // LOOKCHARACTER
              // POPCHARACTER
              // PUSHBOOLEANARRAY
              // POPBOOLEANARRAY
              // PUSHBOOLEAN
              // LOOKBOOLEAN
              // POPBOOLEAN
              // PUSHINTEGER4ARRAY
              // POPINTEGER4ARRAY
              // PUSHINTEGER4
              // LOOKINTEGER4
              // POPINTEGER4
              // PUSHINTEGER8ARRAY
              // POPINTEGER8ARRAY
              // PUSHINTEGER8
              // LOOKINTEGER8
              // POPINTEGER8
              // PUSHREAL4ARRAY
              // POPREAL4ARRAY
              // PUSHREAL4
              // LOOKREAL4
              // POPREAL4
              // PUSHREAL8ARRAY
              // POPREAL8ARRAY
              // PUSHREAL8
              // LOOKREAL8
              // POPREAL8
              // PUSHREAL16ARRAY
              // POPREAL16ARRAY
              // PUSHREAL16
              // LOOKREAL16
              // POPREAL16

              //Do push/pop/look call elimination
              for (cn = 0 ; cn < sizeof(PushPopCalls) / sizeof(PushPopCalls[0]) ; cn++)
              {
                AdtParserPtrByStringMultiMapIter CallIter;

                for (CallIter = CallMap.lower_bound(PushPopCalls[cn].CallName) ; CallIter != CallMap.upper_bound(PushPopCalls[cn].CallName) ; ++CallIter)
                {
                  //push/pop/look call match found. Carry out call elimination.
                  AdtFortranCallStmt*     pCallObj = (AdtFortranCallStmt*)(AdtParser*)(*CallIter).second;

                  removePushPopCall(pCallObj,
                                    PushPopCalls[cn],
                                    pModuleBody,
                                    nIteration,
                                    nFnNumber,
                                    rNewAttributeList,
                                    rNewAttributeMap,
                                    rNewLocalsMap,
                                    VariableInfo);
                }

                //Remove the calls from the map as they have been translated and we
                //don't want them being processed by call expansions
                CallMap.erase(PushPopCalls[cn].CallName);
              }
            }

            // Carry out all call expansions
            for (CallExpandIter = CallExpandList.begin() ; CallExpandIter != CallExpandList.end() ; ++CallExpandIter)
            {
              AdtFortranCallExpand* pCallExpandObj = (AdtFortranCallExpand*)(AdtParser*)*CallExpandIter;

              if (pCallExpandObj != 0)
              {
                AdtParserPtrByStringMultiMapIter CallIter;

                for (CallIter = CallMap.lower_bound(pCallExpandObj->name()) ; CallIter != CallMap.upper_bound(pCallExpandObj->name()) ; ++CallIter)
                {
                  //Call expansion match found. Carry out call expansion.
                  AdtFortranCallStmt* pCallObj = (AdtFortranCallStmt*)(AdtParser*)(*CallIter).second;

                  pCallExpandObj->expand(pCallObj,
                                         pModuleBody,
                                         nIteration,
                                         nFnNumber,
                                         rNewAttributeList);
                }
              }
            }
          }
          else
          {
            ::printf("WARNING: Method %s is already defined in module. This definition ignored.\n", pObjCopy->name().c_str());
          }

          UtlReleaseReference(pParentObjCopy);
        }

        nFnNumber++;
      }
    }
  }

  return (bMerged);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::writeCPP_MethodDeclarations(AdtFile& pOutFile,
                                                              bool bPublic,
                                                              const AdtParserPtrByStringMap& rFunctionObjectMap,
                                                              const AdtParserPtrByStringMap& rSubroutineObjectMap,
                                                              const AdtStringByStringMap& rPublicMethodsMap,
                                                              const AdtStringList& rMethodList,
                                                              const char* pParentClassName) const
{
  AdtStringListConstIter  Iter;
  string                  sClassPrefix(pParentClassName);

  sClassPrefix += "__";

  AdtFortranName::setClearPrefix(sClassPrefix);
  AdtFortranBase::setChangePrefix(sClassPrefix, 0);

  for (Iter = rMethodList.begin() ; Iter != rMethodList.end() ; ++Iter)
  {
    const string& rMethodName = *Iter;
    bool          bWrite      = false;

    if (bPublic)
    {
      bWrite = (rPublicMethodsMap.find(rMethodName) != rPublicMethodsMap.end());
    }
    else
    {
      bWrite = (rPublicMethodsMap.find(rMethodName) == rPublicMethodsMap.end());
    }

    if (bWrite)
    {
      const AdtFortranBase*             pSubprogramObj  = 0;
      AdtParserPtrByStringMapConstIter  ObjIter         = rFunctionObjectMap.find(rMethodName);

      if (ObjIter != rFunctionObjectMap.end())
      {
        pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
      }

      if (pSubprogramObj == 0)
      {
        ObjIter = rSubroutineObjectMap.find(rMethodName);

        if (ObjIter != rSubroutineObjectMap.end())
        {
          pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
        }
      }

      if (pSubprogramObj != 0)
      {
        pSubprogramObj->writeCPP(pOutFile, CPP_MODE_FUNCTION_DECLARATION);
      }
    }
  }

  AdtFortranName::setClearPrefix(0);
  AdtFortranBase::setChangePrefix(0, 0);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::writeCPP_ClassHeader(AdtFile& pOutFile,
                                                       const char* pParentIncludeName,
                                                       const AdtStringByStringMap& rPublicMethodsMap,
                                                       const AdtStringList& rMethodList,
                                                       const AdtStringList& rAttributeList,
                                                       const char* pClassName,
                                                       const char* pParentClassName,
                                                       const char* pPathPrefix,
                                                       AdtStringList& rCPP_ConstructorList,
                                                       string& sPreText,
                                                       string& sPostText) const
{
  const AdtParser* pModuleObj = findObject("AdtFortranModule", "COMMON");

  if (pModuleObj != 0)
  {
    string                  sDefineName;
    AdtStringListConstIter  Iter;

    sDefineName  = "__";
    sDefineName += pClassName;
    sDefineName += "_HPP";

    sPreText = "//  ----------------------------------------------------------------------------\n"
               "//  ADT generated header defining class ";

    sPreText += pClassName;
    sPreText += "\n//  ----------------------------------------------------------------------------\n\n\n"
                "#ifndef ";
    sPreText += sDefineName;
    sPreText += "\n#define ";
    sPreText += sDefineName;

    if ((pParentIncludeName != 0) && (pParentIncludeName[0] != 0))
    {
      sPreText += "\n\n\n#include \"";
      sPreText += pParentIncludeName;
      sPreText += "\"\n\n\n";
    }

    pOutFile.write("class ");
    pOutFile.write(pClassName);
    pOutFile.write(" : public ");
    pOutFile.write(pParentClassName);
    pOutFile.newline();
    pOutFile.write("{");
    pOutFile.newline();

    // To speed up the process of building the class we pre-cache required
    // objects into maps rather than doing repeated scans of the parse tree.
    // This makes the process considerably faster.

    // Cache AdtFortranName objects
    AdtParserPtrList            rNameObjectList;
    AdtParserPtrByStringMap     rNameObjectMap;
    AdtParserPtrByStringMapIter ObjIter;

    pModuleObj->findObjects(rNameObjectList,
                            "AdtFortranName",
                            0,
                            false,
                            "AdtFortranEntityDecl");

    listToMap(rNameObjectMap, rNameObjectList);

    // Cache AdtFortranFunctionSubprogram objects
    AdtParserPtrList            rFunctionObjectList;
    AdtParserPtrByStringMap     rFunctionObjectMap;

    findObjects(rFunctionObjectList,
                "AdtFortranFunctionSubprogram");

    listToMap(rFunctionObjectMap, rFunctionObjectList);

    // Cache AdtFortranSubroutineSubprogram objects
    AdtParserPtrList            rSubroutineObjectList;
    AdtParserPtrByStringMap     rSubroutineObjectMap;

    findObjects(rSubroutineObjectList,
                "AdtFortranSubroutineSubprogram");

    listToMap(rSubroutineObjectMap, rSubroutineObjectList);

    if (rAttributeList.size() > 0)
    {
      pOutFile.write("protected:");
      pOutFile.incrementIndent();
      pOutFile.newline();
    }

    //Write class variable attributes
    for (Iter = rAttributeList.begin() ; Iter != rAttributeList.end() ; ++Iter)
    {
      const string& rAttributeName = *Iter;

      ObjIter = rNameObjectMap.find(rAttributeName);

      if (ObjIter != rNameObjectMap.end())
      {
        const AdtParser*  pNameObj = (*ObjIter).second;

        if (pNameObj != 0)
        {
          const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
          const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

          if ((pEntityDecl != 0) && (pTypeDecl != 0))
          {
            const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

            if (pTypeSpec != 0)
            {
              if (pEntityDecl->numberOfDimensions() > 0)
              {
                const char* pType = 0;

                AdtCppBase::mapTypesToCpp(pTypeSpec->name(), pEntityDecl->numberOfDimensions(), pType);
                pOutFile.write(pType);
              }
              else
              {
                pTypeSpec->writeCPP(pOutFile, 0);
              }

              pOutFile.write(" ");

              pEntityDecl->writeCPP(pOutFile, 1);
            }

            pOutFile.write(";");
            pOutFile.newline();
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassHeader "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassHeader "
                   "failure on line %d in file %s\n",
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassHeader "
                 "failure on line %d in file %s\n",
                 __LINE__,
                 __FILE__);

        FAIL();
        AdtExit(-1);
      }
    }

    pOutFile.newline();
    pOutFile.newline();

    writeCPP_MethodDeclarations(pOutFile,
                                false,
                                rFunctionObjectMap,
                                rSubroutineObjectMap,
                                rPublicMethodsMap,
                                rMethodList,
                                pParentClassName);

    pOutFile.newline();
    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.write("public:");
    pOutFile.incrementIndent();
    pOutFile.newline();

    // Write class interface methods include here. Note that we must write it
    // before the class constructor because this include gets interpreted as a
    // comment line (to preserve it in code) that will bind to the next parsed
    // object. If we place it at the end of the class definition it will be
    // lost because there is no object to bind it to.
    AdtAutoClass::writeInterfaceMethodsDeclInclude(pOutFile,
                                                   CppSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    //Write class constructors
    for (Iter = rCPP_ConstructorList.begin() ; Iter != rCPP_ConstructorList.end() ; ++Iter)
    {
      const string& rConstructorDeclaration = *Iter;
      const string& rConstructorCall        = *(++Iter);

      pOutFile.write(pClassName);
      pOutFile.write(rConstructorDeclaration);
      pOutFile.write(";");
      pOutFile.newline();
    }

    //Write class destructor
    pOutFile.write("virtual ~");
    pOutFile.write(pClassName);
    pOutFile.write("();");
    pOutFile.newline();
    pOutFile.newline();

    //Write class method attributes
    writeCPP_MethodDeclarations(pOutFile,
                                true,
                                rFunctionObjectMap,
                                rSubroutineObjectMap,
                                rPublicMethodsMap,
                                rMethodList,
                                pParentClassName);

    pOutFile.decrementIndent();
    pOutFile.newline();

    pOutFile.write("};");

    sPostText = "\n\n";

    string  sIncludes;
    AdtFile sTextFile;

    sTextFile.open(sIncludes);

    AdtAutoClass::writeInterfaceGlobalsDeclInclude(sTextFile,
                                                   CppSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeConstructorDeclInclude(sTextFile,
                                              CppSourceFileType,
                                              pClassName,
                                              pPathPrefix);

    sTextFile.close();

    sPostText += sIncludes;
    sPostText += "\n\n#endif //";
    sPostText += sDefineName;
    sPostText += "\n\n";
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::writeCPP_ClassImplementation(AdtFile& pOutFile,
                                                               const char* pIncludeName,
                                                               const AdtStringList& rMethodList,
                                                               const AdtStringList& rAttributeList,
                                                               const char* pClassName,
                                                               const char* pParentClassName,
                                                               const char* pPathPrefix,
                                                               AdtStringList& rCPP_ConstructorList,
                                                               AdtStringList* pVarSuffixList,
                                                               string& sPreText,
                                                               string& sPostText) const
{
  const AdtParser* pModuleObj = findObject("AdtFortranModule", "COMMON");

  if (pModuleObj != 0)
  {
    AdtStringListConstIter  Iter;

    sPreText = "//  ----------------------------------------------------------------------------\n"
               "//  ADT generated file implementing class ";

    sPreText += pClassName;
    sPreText += "\n//  ----------------------------------------------------------------------------";

    if (pIncludeName != 0)
    {
      pOutFile.newline();
      pOutFile.newline();
      pOutFile.newline();
      pOutFile.write("#include \"");
      pOutFile.write(pIncludeName);
      pOutFile.write("\"");
    }

    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();

    // To speed up the process of building the class we pre-cache required
    // objects into maps rather than doing repeated scans of the parse tree.
    // This makes the process considerably faster.

    // Cache AdtFortranName objects
    AdtParserPtrList            rNameObjectList;
    AdtParserPtrByStringMap     rNameObjectMap;
    AdtParserPtrByStringMapIter ObjIter;

    pModuleObj->findObjects(rNameObjectList,
                            "AdtFortranName",
                            0,
                            false,
                            "AdtFortranEntityDecl");

    listToMap(rNameObjectMap, rNameObjectList);

    // Cache AdtFortranFunctionSubprogram objects
    AdtParserPtrList            rFunctionObjectList;
    AdtParserPtrByStringMap     rFunctionObjectMap;

    findObjects(rFunctionObjectList,
                "AdtFortranFunctionSubprogram");

    listToMap(rFunctionObjectMap, rFunctionObjectList);

    // Cache AdtFortranSubroutineSubprogram objects
    AdtParserPtrList            rSubroutineObjectList;
    AdtParserPtrByStringMap     rSubroutineObjectMap;

    findObjects(rSubroutineObjectList,
                "AdtFortranSubroutineSubprogram");

    listToMap(rSubroutineObjectMap, rSubroutineObjectList);

    //Write class method attributes
    string  sClassPrefix(pParentClassName);
    string  sNewClassPrefix(pClassName);

    sClassPrefix += "__";
    sNewClassPrefix += "::";

    AdtFortranName::setClearPrefix(0);
    AdtFortranBase::setChangePrefix(0, 0);

    //Write class constructor implementations
    for (Iter = rCPP_ConstructorList.begin() ; Iter != rCPP_ConstructorList.end() ; ++Iter)
    {
      const string&           rConstructorDeclaration = *Iter;
      const string&           rConstructorCall        = *(++Iter);
      AdtStringListConstIter  Iter2;
      AdtStringByStringMap    PlanMap;
      int                     nPlan = 1;

      pOutFile.write(sNewClassPrefix);
      pOutFile.write(pClassName);
      pOutFile.write(rConstructorDeclaration);
      pOutFile.newline();
      pOutFile.write(" : ");
      pOutFile.write(rConstructorCall);
      pOutFile.newline();
      pOutFile.write("{");
      pOutFile.incrementIndent();
      pOutFile.newline();

      // Go through all the new arrays one by one. If the name has stack in it
      // assume it is a stack variable and initialise with alloc_stacks. If the
      // name has part of the name common with a parent class variable and it
      // is an array then use create with the parent class variable
      // as the argument. If the variable is single value data initialise to
      // zero. Remaining arrays must be allocated using alloc_arrays and the
      // sizes specified by the associated size comments. The exception is
      // variable size arrays. MB is probably revising what needs doing for
      // this case as I write this.
      for (Iter2 = rAttributeList.begin() ; Iter2 != rAttributeList.end() ; ++Iter2)
      {
        const string& rAttributeName = *Iter2;

        ObjIter = rNameObjectMap.find(rAttributeName);

        if (ObjIter != rNameObjectMap.end())
        {
          const AdtParser*  pNameObj = (*ObjIter).second;

          if (pNameObj != 0)
          {
            const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
            const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

            if ((pEntityDecl != 0) && (pTypeDecl != 0))
            {
              const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

              if (pTypeSpec != 0)
              {
                size_t nDims = pEntityDecl->numberOfDimensions();

                if (nDims > 0)
                {
                  const char* pType  = 0;
                  string      sCapsName(rAttributeName);

                  sCapsName.toUpper();

                  AdtCppBase::mapTypesToCpp(pTypeSpec->name(), pEntityDecl->numberOfDimensions(), pType);

                  if ((::strstr(sCapsName, "STACK") != 0) && (nDims == 1))
                  {
                    //It is a stack
                    pOutFile.write("createStack(");
                    pOutFile.write(rAttributeName);
                    pOutFile.write(");");
                  }
                  else
                  {
                    // It is an array
                    string  sParentName(rAttributeName);
                    bool    bHasParentArray = false;

                    if (pVarSuffixList != 0)
                    {
                      AdtStringListConstIter  DiffIter;
                      bool                    bMatched;
                      size_t                  nMaxLength;
                      size_t                  nCutLength;

                      // Need to search for the maximum length suffix match from
                      // the list of suffixes. When found we then repeat the
                      // process until we fail to get a match. At this point we
                      // will have arrived at the parent variable.
                      do
                      {
                        bMatched    = false;
                        nMaxLength  = 0;
                        nCutLength  = 0;

                        for (DiffIter = pVarSuffixList->begin() ; DiffIter != pVarSuffixList->end() ; ++DiffIter)
                        {
                          const string  sVarSuffix = *DiffIter;

                          if (sVarSuffix.length() > nMaxLength)
                          {
                            const char*   pNext      = 0;
                            const char*   pMatch     = sParentName.findMatch(sVarSuffix, pNext, false, false);

                            if (pMatch != 0)
                            {
                              bool bOk = true;

                              for ( ; ((*pNext != 0) && bOk) ; ++pNext)
                              {
                                switch (*pNext)
                                {
                                  case '0':
                                  case '1':
                                  case '2':
                                  case '3':
                                  case '4':
                                  case '5':
                                  case '6':
                                  case '7':
                                  case '8':
                                  case '9':
                                  {
                                    break;
                                  }

                                  default:
                                  {
                                    bOk = false;
                                    break;
                                  }
                                }
                              }

                              if (bOk)
                              {
                                bMatched        = true;
                                bHasParentArray = true;
                                nMaxLength      = sVarSuffix.length();
                                nCutLength      = sParentName.length() - ::strlen(pMatch);
                              }
                            }
                          }
                        }

                        if (bMatched)
                        {
                          sParentName.left(nCutLength);
                        }

                      } while (bMatched);

                      if (bHasParentArray)
                      {
                        ObjIter = rNameObjectMap.find(sParentName);

                        if (ObjIter != rNameObjectMap.end())
                        {
                          const AdtParser*  pNameObj = (*ObjIter).second;

                          if (pNameObj != 0)
                          {
                            const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
                            const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

                            if ((pEntityDecl != 0) && (pTypeDecl != 0))
                            {
                              const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

                              if (pTypeSpec != 0)
                              {
                                size_t nDims = pEntityDecl->numberOfDimensions();

                                if (nDims > 0)
                                {
                                  const char* pParentType = 0;
                                  string      sCapsName(rAttributeName);

                                  sCapsName.toUpper();

                                  AdtCppBase::mapTypesToCpp(pTypeSpec->name(), pEntityDecl->numberOfDimensions(), pParentType);

                                  if(strcmp(pType, pParentType) != 0)
                                  {
                                    bHasParentArray = false;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }

                    if (bHasParentArray)
                    {
                      // It is an array with parent so allocate with create()
                      pOutFile.write("create(");
                      pOutFile.write(rAttributeName);
                      pOutFile.write(",");
                      pOutFile.write(sParentName);
                      pOutFile.write(");");
                    }
                    else
                    {
                      // It is an array without parent so allocate with AdtArrayPlan
                      //  AdtArrayPlan  Plan_n_h_1(1, n_h);
                      //
                      //  Plan_n_h_1.create(MemAllocator, wt_A);
                      AdtFile     File;
                      string      sSizes;
                      string      sBaseIndices;
                      string      sArrayPlanArgs;
                      string      sPlanName;

                      // Get the indices of the array into strings
                      File.open(sSizes);

                      pEntityDecl->writeDelphi(File, 4);

                      File.close();

                      File.open(sBaseIndices);

                      pEntityDecl->writeDelphi(File, 5);

                      File.close();

                      // We need to splice the strings together to make the
                      // AdtArrayPlan constructor arguments.
                      string      sSize;
                      string      sBaseIndex;
                      const char* pSizes        = sSizes;
                      const char* pBaseIndices  = sBaseIndices;
                      bool        bFirst        = true;

                      pSizes        = AdtParse::nextWord(pSizes);
                      pBaseIndices  = AdtParse::nextWord(pBaseIndices);

                      while (AdtParse::extractWord(sSize,       ",", pSizes) &&
                             AdtParse::extractWord(sBaseIndex,  ",", pBaseIndices))
                      {
                        AdtParse::matchWord(pSizes, ",");
                        AdtParse::matchWord(pBaseIndices, ",");
                        pSizes        = AdtParse::nextWord(pSizes);
                        pBaseIndices  = AdtParse::nextWord(pBaseIndices);

                        if (!bFirst)
                        {
                          sArrayPlanArgs = "," + sArrayPlanArgs;
                        }

                        sArrayPlanArgs = sBaseIndex + "," + sSize + sArrayPlanArgs;

                        bFirst = false;
                      }

                      AdtStringByStringMapConstIter PlanIter  = PlanMap.find(sArrayPlanArgs);
                      bool                          bDeclare  = false;

                      if (PlanIter == PlanMap.end())
                      {
                        char sBuffer[32] = {0};

                        ::sprintf(sBuffer, "Plan_%d", nPlan);

                        sPlanName               = sBuffer;
                        PlanMap[sArrayPlanArgs] = sPlanName;
                        bDeclare                = true;

                        nPlan++;
                      }
                      else
                      {
                        sPlanName = (*PlanIter).second;
                      }

                      // Write the array plan construction and the array
                      // create call.
                      if (bDeclare)
                      {
                        pOutFile.newline();
                        pOutFile.write("AdtArrayPlan ");
                        pOutFile.write(sPlanName);
                        pOutFile.write("(");
                        pOutFile.write(sArrayPlanArgs);
                        pOutFile.write(");");
                      }

                      pOutFile.newline();
                      pOutFile.write(sPlanName);
                      pOutFile.write(".create(MemAllocator, ");
                      pOutFile.write(rAttributeName);
                      pOutFile.write(");");
                    }
                  }
                }
                else
                {
                  // Is a scalar so initialise to zero.
                  pOutFile.write(rAttributeName);
                  pOutFile.write(" = 0;");
                }
              }

              pOutFile.newline();
            }
            else
            {
              ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                       "failure on line %d in file %s\n",
                       __LINE__,
                       __FILE__);

              FAIL();
              AdtExit(-1);
            }
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                   "failure on line %d in file %s\n",
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }

      pOutFile.decrementIndent();
      pOutFile.newline();
      pOutFile.write("}");
      pOutFile.newline();
    }

    pOutFile.newline();

    //Write class destructor
    pOutFile.write(sNewClassPrefix);
    pOutFile.write("~");
    pOutFile.write(pClassName);
    pOutFile.write("()");
    pOutFile.newline();
    pOutFile.write("{");
    pOutFile.incrementIndent();
    pOutFile.newline();

    // Go through all the arrays and stacks and explicitely free them.
    for (Iter = rAttributeList.begin() ; Iter != rAttributeList.end() ; ++Iter)
    {
      const string& rAttributeName = *Iter;

      ObjIter = rNameObjectMap.find(rAttributeName);

      if (ObjIter != rNameObjectMap.end())
      {
        const AdtParser*  pNameObj = (*ObjIter).second;

        if (pNameObj != 0)
        {
          const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
          const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

          if ((pEntityDecl != 0) && (pTypeDecl != 0))
          {
            const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

            if (pTypeSpec != 0)
            {
              size_t nDims = pEntityDecl->numberOfDimensions();

              if (nDims > 0)
              {
                pOutFile.write("destroy(");
                pOutFile.write(rAttributeName);
                pOutFile.write(");");
                pOutFile.newline();
              }
            }

            pOutFile.newline();
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                   "failure on line %d in file %s\n",
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeCPP_ClassImplementation "
                 "failure on line %d in file %s\n",
                 __LINE__,
                 __FILE__);

        FAIL();
        AdtExit(-1);
      }
    }

    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.write("}");
    pOutFile.newline();
    pOutFile.newline();

    //Write class method implemetations
    for (Iter = rMethodList.begin() ; Iter != rMethodList.end() ; ++Iter)
    {
      const string&         rMethodName    = *Iter;
      const AdtFortranBase* pSubprogramObj = 0;

      ObjIter = rSubroutineObjectMap.find(rMethodName);

      if (ObjIter != rSubroutineObjectMap.end())
      {
        pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
      }

      if (pSubprogramObj == 0)
      {
        AdtFortranFunctionSubprogram* pFunctionSubprogram = 0;

        ObjIter = rFunctionObjectMap.find(rMethodName);

        if (ObjIter != rFunctionObjectMap.end())
        {
          pFunctionSubprogram = (AdtFortranFunctionSubprogram*)(AdtParser*)(*ObjIter).second;
        }

        pSubprogramObj = (const AdtFortranBase*)pFunctionSubprogram;
      }

      if (pSubprogramObj != 0)
      {
        AdtFortranName::setClearPrefix(sClassPrefix);
        AdtFortranBase::setChangePrefix(sClassPrefix, sNewClassPrefix);

        pSubprogramObj->writeCPP(pOutFile, 0);

        AdtFortranName::setClearPrefix(0);
        AdtFortranBase::setChangePrefix(0, 0);
      }
    }

    sPostText = "\n\n";

    string  sInclude;
    AdtFile sTextFile;

    sTextFile.open(sInclude);

    AdtAutoClass::writeInterfaceMethodsImplInclude(sTextFile,
                                                   CppSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeInterfaceGlobalsImplInclude(sTextFile,
                                                   CppSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeConstructorImplInclude(sTextFile,
                                              CppSourceFileType,
                                              pClassName,
                                              pPathPrefix);

    sTextFile.close();

    sPostText += sInclude;
    sPostText += "\n\n";
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::writeDelphi_MethodDeclarations(AdtFile& pOutFile,
                                                                 bool bPublic,
                                                                 const AdtParserPtrByStringMap& rFunctionObjectMap,
                                                                 const AdtParserPtrByStringMap& rSubroutineObjectMap,
                                                                 const AdtStringByStringMap& rPublicMethodsMap,
                                                                 const AdtStringList& rMethodList,
                                                                 const char* pParentClassName) const
{
  AdtStringListConstIter  Iter;
  string                  sClassPrefix(pParentClassName);

  sClassPrefix += "__";

  AdtFortranName::setClearPrefix(sClassPrefix);
  AdtFortranBase::setChangePrefix(sClassPrefix, 0);

  for (Iter = rMethodList.begin() ; Iter != rMethodList.end() ; ++Iter)
  {
    const string& rMethodName = *Iter;
    bool          bWrite      = false;

    if (bPublic)
    {
      bWrite = (rPublicMethodsMap.find(rMethodName) != rPublicMethodsMap.end());
    }
    else
    {
      bWrite = (rPublicMethodsMap.find(rMethodName) == rPublicMethodsMap.end());
    }

    if (bWrite)
    {
      const AdtFortranBase*             pSubprogramObj  = 0;
      AdtParserPtrByStringMapConstIter  ObjIter         = rFunctionObjectMap.find(rMethodName);

      if (ObjIter != rFunctionObjectMap.end())
      {
        pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
      }

      if (pSubprogramObj == 0)
      {
        ObjIter = rSubroutineObjectMap.find(rMethodName);

        if (ObjIter != rSubroutineObjectMap.end())
        {
          pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
        }
      }

      if (pSubprogramObj != 0)
      {
        pSubprogramObj->writeDelphi(pOutFile, DELPHI_MODE_FUNCTION_DECLARATION);
      }
    }
  }

  AdtFortranName::setClearPrefix(0);
  AdtFortranBase::setChangePrefix(0, 0);
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::writeDelphiClass(AdtFile& pOutFile,
                                                   const AdtStringByStringMap& rPublicMethodsMap,
                                                   const AdtStringList& rMethodList,
                                                   const AdtStringList& rAttributeList,
                                                   const char* pClassName,
                                                   const char* pParentClassName,
                                                   const char* pPathPrefix,
                                                   AdtStringList& rDelphiConstructorList,
                                                   const char* pUsesList,
                                                   AdtStringList* pVarSuffixList) const
{
  const AdtParser* pModuleObj = findObject("AdtFortranModule", "COMMON");

  if (pModuleObj != 0)
  {
    string                  sUnitName;
    string                  sParentUnitName;
    AdtStringListConstIter  Iter;

    sUnitName  = pClassName;
    sUnitName += "_Unit";

    sParentUnitName  = pParentClassName;
    sParentUnitName += "_Unit";

    pOutFile.write("{$mode objfpc}{$modeswitch autoderef}{$modeswitch duplicatelocals}{$H+}");
    pOutFile.newline();
    pOutFile.write("unit ");
    pOutFile.write(sUnitName);
    pOutFile.write(";");

    pOutFile.newline();
    pOutFile.newline();

    pOutFile.write("interface");

    pOutFile.incrementIndent();
    pOutFile.newline();

    pOutFile.write("uses ");
    pOutFile.write(sParentUnitName);

    if ((pUsesList != 0) && (::strlen(pUsesList) > 0))
    {
      pOutFile.write(",");
      pOutFile.write(pUsesList);
    }

    pOutFile.write(";");

    pOutFile.newline();
    pOutFile.newline();

    pOutFile.write("type");

    pOutFile.incrementIndent();
    pOutFile.newline();

    pOutFile.write(pClassName);
    pOutFile.write(" = class(");
    pOutFile.write(pParentClassName);
    pOutFile.write(")");
    pOutFile.newline();
    pOutFile.newline();

    // To speed up the process of building the class we pre-cache required
    // objects into maps rather than doing repeated scans of the parse tree.
    // This makes the process considerably faster.

    // Cache AdtFortranName objects
    AdtParserPtrList            rNameObjectList;
    AdtParserPtrByStringMap     rNameObjectMap;
    AdtParserPtrByStringMapIter ObjIter;

    pModuleObj->findObjects(rNameObjectList,
                            "AdtFortranName",
                            0,
                            false,
                            "AdtFortranEntityDecl");

    listToMap(rNameObjectMap, rNameObjectList);

    // Cache AdtFortranFunctionSubprogram objects
    AdtParserPtrList            rFunctionObjectList;
    AdtParserPtrByStringMap     rFunctionObjectMap;

    findObjects(rFunctionObjectList,
                "AdtFortranFunctionSubprogram");

    listToMap(rFunctionObjectMap, rFunctionObjectList);

    // Cache AdtFortranSubroutineSubprogram objects
    AdtParserPtrList            rSubroutineObjectList;
    AdtParserPtrByStringMap     rSubroutineObjectMap;

    findObjects(rSubroutineObjectList,
                "AdtFortranSubroutineSubprogram");

    listToMap(rSubroutineObjectMap, rSubroutineObjectList);

    if (rAttributeList.size() > 0)
    {
      pOutFile.write("protected");
      pOutFile.incrementIndent();
      pOutFile.newline();
      pOutFile.newline();
    }

    //Write class variable attributes
    for (Iter = rAttributeList.begin() ; Iter != rAttributeList.end() ; ++Iter)
    {
      const string& rAttributeName = *Iter;

      ObjIter = rNameObjectMap.find(rAttributeName);

      if (ObjIter != rNameObjectMap.end())
      {
        const AdtParser*  pNameObj = (*ObjIter).second;

        if (pNameObj != 0)
        {
          const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
          const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

          if ((pEntityDecl != 0) && (pTypeDecl != 0))
          {
            const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

            if (pTypeSpec != 0)
            {
              pEntityDecl->writeDelphi(pOutFile, 1);

              pOutFile.write(" : ");

              if (pEntityDecl->numberOfDimensions() > 0)
              {
                const char* pType = 0;

                AdtDelphiBase::mapTypesToDelphi(pTypeSpec->name(), pEntityDecl->numberOfDimensions(), pType);
                pOutFile.write(pType);
              }
              else
              {
                pTypeSpec->writeDelphi(pOutFile, 0);
              }
            }

            pOutFile.write(";");
            pOutFile.newline();
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                   "failure on line %d in file %s\n",
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                 "failure on line %d in file %s\n",
                 __LINE__,
                 __FILE__);

        FAIL();
        AdtExit(-1);
      }
    }

    pOutFile.newline();
    pOutFile.newline();

    writeDelphi_MethodDeclarations(pOutFile,
                                   false,
                                   rFunctionObjectMap,
                                   rSubroutineObjectMap,
                                   rPublicMethodsMap,
                                   rMethodList,
                                   pParentClassName);

    pOutFile.newline();
    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.write("public");
    pOutFile.incrementIndent();
    pOutFile.newline();

    // Write class interface methods include here. Note that we must write it
    // before the class constructor because this include gets interpreted as a
    // comment line (to preserve it in code) that will bind to the next parsed
    // object. If we place it at the end of the class definition it will be
    // lost because there is no object to bind it to.
    AdtAutoClass::writeInterfaceMethodsDeclInclude(pOutFile,
                                                   DelphiSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    //Write class constructors
    for (Iter = rDelphiConstructorList.begin() ; Iter != rDelphiConstructorList.end() ; ++Iter)
    {
      const string& rConstructorDeclaration = *Iter;
      const string& rConstructorCall        = *(++Iter);

      pOutFile.write("constructor ");
      pOutFile.write(rConstructorDeclaration);
      pOutFile.write("overload;");
      pOutFile.newline();
    }

    //Write class destructor
    pOutFile.write("destructor destroy(); override;");
    pOutFile.newline();
    pOutFile.newline();

    //Write class method attributes
    writeDelphi_MethodDeclarations(pOutFile,
                                   true,
                                   rFunctionObjectMap,
                                   rSubroutineObjectMap,
                                   rPublicMethodsMap,
                                   rMethodList,
                                   pParentClassName);

    string  sClassPrefix(pParentClassName);
    string  sNewClassPrefix(pClassName);

    sClassPrefix += "__";
    sNewClassPrefix += ".";

    pOutFile.decrementIndent();
    pOutFile.newline();

    pOutFile.write("end;");

    AdtAutoClass::writeInterfaceGlobalsDeclInclude(pOutFile,
                                                   DelphiSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeConstructorDeclInclude(pOutFile,
                                              DelphiSourceFileType,
                                              pClassName,
                                              pPathPrefix);

    pOutFile.decrementIndent();
    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.newline();

    pOutFile.write("implementation");

    pOutFile.incrementIndent();
    pOutFile.newline();
    pOutFile.newline();

    //Write class constructor implementations
    for (Iter = rDelphiConstructorList.begin() ; Iter != rDelphiConstructorList.end() ; ++Iter)
    {
      AdtStringList rVarList;
      AdtStringList rDestroyList;
      const string& rConstructorDeclaration = *Iter;
      const string& rConstructorCall        = *(++Iter);
      int           nPass;

      pOutFile.write("constructor ");
      pOutFile.write(sNewClassPrefix);
      pOutFile.write(rConstructorDeclaration);
      pOutFile.newline();

      for (nPass = 0 ; nPass < 2 ; nPass++)
      {
        AdtStringListConstIter  Iter2;
        AdtStringByStringMap    PlanMap;
        int                     nPlan = 1;

        switch(nPass)
        {
          case 0:
          {
            rVarList.clear();
            rDestroyList.clear();
            pOutFile.disable();
            break;
          }

          default:
          case 1:
          {
            pOutFile.enable();

            if (rVarList.size() > 0)
            {
              pOutFile.write("Var");
              pOutFile.incrementIndent();
              pOutFile.newline();

              for (AdtStringListConstIter DeclIter = rVarList.begin() ; DeclIter != rVarList.end() ; ++DeclIter)
              {
                pOutFile.write(*DeclIter);
                pOutFile.newline();
              }

              pOutFile.decrementIndent();
              pOutFile.newline();
            }
            break;
          }
        }

        pOutFile.write("begin");
        pOutFile.incrementIndent();
        pOutFile.newline();
        pOutFile.write("inherited ");
        pOutFile.write(rConstructorCall);
        pOutFile.newline();

        // Go through all the new arrays one by one. If the name has stack in it
        // assume it is a stack variable and initialise with alloc_stacks. If the
        // name has part of the name common with a parent class variable and it
        // is an array then use alloc_same_shape with the parent class variable
        // as the argument. If the variable is single value data initialise to
        // zero. Remaining arrays must be allocated using alloc_arrays and the
        // sizes specified by the associated size comments. The exception is
        // variable size arrays. MB is probably revising what needs doing for
        // this case as I write this.
        for (Iter2 = rAttributeList.begin() ; Iter2 != rAttributeList.end() ; ++Iter2)
        {
          const string& rAttributeName = *Iter2;

          ObjIter = rNameObjectMap.find(rAttributeName);

          if (ObjIter != rNameObjectMap.end())
          {
            const AdtParser*  pNameObj = (*ObjIter).second;

            if (pNameObj != 0)
            {
              const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
              const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

              if ((pEntityDecl != 0) && (pTypeDecl != 0))
              {
                const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

                if (pTypeSpec != 0)
                {
                  size_t nDims = pEntityDecl->numberOfDimensions();

                  if (nDims > 0)
                  {
                    const char* pType = 0;
                    string      sCapsName(rAttributeName);

                    sCapsName.toUpper();

                    AdtDelphiBase::mapTypesToDelphi(pTypeSpec->name(), pEntityDecl->numberOfDimensions(), pType);

                    if ((::strstr(sCapsName, "STACK") != 0) && (nDims == 1))
                    {
                      //It is a stack
                      pOutFile.write("createStack(");
                      pOutFile.write(rAttributeName);
                      pOutFile.write(")");
                    }
                    else
                    {
                      // It is an array
                      string  sParentName(rAttributeName);
                      bool    bHasParentArray = false;

                      if (pVarSuffixList != 0)
                      {
                        AdtStringListConstIter  DiffIter;
                        bool                    bMatched;
                        size_t                  nMaxLength;
                        size_t                  nCutLength;

                        // Need to search for the maximum length suffix match from
                        // the list of suffixes. When found we then repeat the
                        // process until we fail to get a match. At this point we
                        // will have arrived at the parent variable.
                        do
                        {
                          bMatched    = false;
                          nMaxLength  = 0;
                          nCutLength  = 0;

                          for (DiffIter = pVarSuffixList->begin() ; DiffIter != pVarSuffixList->end() ; ++DiffIter)
                          {
                            const string  sVarSuffix = *DiffIter;

                            if (sVarSuffix.length() > nMaxLength)
                            {
                              const char*   pNext      = 0;
                              const char*   pMatch     = sParentName.findMatch(sVarSuffix, pNext, false, false);

                              if (pMatch != 0)
                              {
                                bool bOk = true;

                                for ( ; ((*pNext != 0) && bOk) ; ++pNext)
                                {
                                  switch (*pNext)
                                  {
                                    case '0':
                                    case '1':
                                    case '2':
                                    case '3':
                                    case '4':
                                    case '5':
                                    case '6':
                                    case '7':
                                    case '8':
                                    case '9':
                                    {
                                      break;
                                    }

                                    default:
                                    {
                                      bOk = false;
                                      break;
                                    }
                                  }
                                }

                                if (bOk)
                                {
                                  bMatched        = true;
                                  bHasParentArray = true;
                                  nMaxLength      = sVarSuffix.length();
                                  nCutLength      = sParentName.length() - ::strlen(pMatch);
                                }
                              }
                            }
                          }

                          if (bMatched)
                          {
                            sParentName.left(nCutLength);
                          }

                        } while (bMatched);
                      }

                      if (bHasParentArray)
                      {
                        // It is an array with parent so allocate with create()
                        pOutFile.write("create(");
                        pOutFile.write(rAttributeName);
                        pOutFile.write(",");
                        pOutFile.write(sParentName);
                        pOutFile.write(")");
                      }
                      else
                      {
                        // It is an array without parent so allocate with AdtArrayPlan
                        //  AdtArrayPlan  Plan_n_h_1(1, n_h);
                        //
                        //  Plan_n_h_1.create(MemAllocator, wt_A);
                        AdtFile     File;
                        string      sSizes;
                        string      sBaseIndices;
                        string      sArrayPlanArgs;
                        string      sPlanName;

                        // Get the indices of the array into strings
                        File.open(sSizes);

                        pEntityDecl->writeDelphi(File, 4);

                        File.close();

                        File.open(sBaseIndices);

                        pEntityDecl->writeDelphi(File, 5);

                        File.close();

                        // We need to splice the strings together to make the
                        // AdtArrayPlan constructor arguments.
                        string      sSize;
                        string      sBaseIndex;
                        const char* pSizes        = sSizes;
                        const char* pBaseIndices  = sBaseIndices;
                        bool        bFirst        = true;

                        pSizes        = AdtParse::nextWord(pSizes);
                        pBaseIndices  = AdtParse::nextWord(pBaseIndices);

                        while (AdtParse::extractWord(sSize,       ",", pSizes) &&
                               AdtParse::extractWord(sBaseIndex,  ",", pBaseIndices))
                        {
                          AdtParse::matchWord(pSizes, ",");
                          AdtParse::matchWord(pBaseIndices, ",");
                          pSizes        = AdtParse::nextWord(pSizes);
                          pBaseIndices  = AdtParse::nextWord(pBaseIndices);

                          if (!bFirst)
                          {
                            sArrayPlanArgs = "," + sArrayPlanArgs;
                          }

                          sArrayPlanArgs = sBaseIndex + "," + sSize + sArrayPlanArgs;

                          bFirst = false;
                        }

                        AdtStringByStringMapConstIter PlanIter  = PlanMap.find(sArrayPlanArgs);
                        bool                          bDeclare  = false;

                        if (PlanIter == PlanMap.end())
                        {
                          char    sBuffer[32] = {0};

                          ::sprintf(sBuffer, "Plan_c%d", nPlan);

                          sPlanName               = sBuffer;
                          PlanMap[sArrayPlanArgs] = sPlanName;
                          bDeclare                = true;

                          if (nPass == 0)
                          {
                            string  sPlanDecl     = sPlanName + " : AdtArrayPlan;";
                            string  sPlanDestroy  = sPlanName + ".destroy;";

                            rVarList.push_back(sPlanDecl);
                            rDestroyList.push_back(sPlanDestroy);
                          }

                          nPlan++;
                        }
                        else
                        {
                          sPlanName = (*PlanIter).second;
                        }

                        // Write the array plan construction and the array
                        // create call.
                        if (bDeclare)
                        {
                          pOutFile.newline();
                          pOutFile.write(sPlanName);
                          pOutFile.write(" := AdtArrayPlan.create(");
                          pOutFile.write(sArrayPlanArgs);
                          pOutFile.write(");");
                        }

                        pOutFile.newline();
                        pOutFile.write(sPlanName);
                        pOutFile.write(".create(_MemAllocator, ");
                        pOutFile.write(rAttributeName);
                        pOutFile.write(");");
                      }
                    }
                  }
                  else
                  {
                    // Is a scalar so initialise to zero.
                    pOutFile.write(rAttributeName);
                    pOutFile.write(" := 0");
                  }
                }

                pOutFile.write(";");
                pOutFile.newline();
              }
              else
              {
                ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                         "failure on line %d in file %s\n",
                         __LINE__,
                         __FILE__);

                FAIL();
                AdtExit(-1);
              }
            }
            else
            {
              ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                       "failure on line %d in file %s\n",
                       __LINE__,
                       __FILE__);

              FAIL();
              AdtExit(-1);
            }
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }

        if (nPass == 1)
        {
          for (AdtStringListConstIter DestroyIter = rDestroyList.begin() ; DestroyIter != rDestroyList.end() ; ++DestroyIter)
          {
            pOutFile.write(*DestroyIter);
            pOutFile.newline();
          }
        }

        pOutFile.decrementIndent();
        pOutFile.newline();
        pOutFile.write("end;");
        pOutFile.newline();
      }
    }

    pOutFile.newline();

    //Write class destructor implemetation
    pOutFile.write("destructor ");
    pOutFile.write(sNewClassPrefix);
    pOutFile.write("destroy();");
    pOutFile.newline();
    pOutFile.newline();
    pOutFile.write("begin");
    pOutFile.incrementIndent();
    pOutFile.newline();

    for (Iter = rAttributeList.begin() ; Iter != rAttributeList.end() ; ++Iter)
    {
      const string& rAttributeName = *Iter;

      ObjIter = rNameObjectMap.find(rAttributeName);

      if (ObjIter != rNameObjectMap.end())
      {
        const AdtParser*  pNameObj = (*ObjIter).second;

        if (pNameObj != 0)
        {
          const AdtFortranEntityDecl*           pEntityDecl = (const AdtFortranEntityDecl*)pNameObj->findAscendantWithClass("AdtFortranEntityDecl");
          const AdtFortranTypeDeclarationStmt*  pTypeDecl   = (const AdtFortranTypeDeclarationStmt*)pNameObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");

          if ((pEntityDecl != 0) && (pTypeDecl != 0))
          {
            const AdtFortranTypeSpec* pTypeSpec = (const AdtFortranTypeSpec*)pTypeDecl->findDescendant("TypeSpec");

            if (pTypeSpec != 0)
            {
              size_t nDims = pEntityDecl->numberOfDimensions();

              if (nDims > 0)
              {
                pOutFile.write("destroy(");
                pOutFile.write(rAttributeName);
                pOutFile.write(");");
                pOutFile.newline();
              }
            }
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                     "failure on line %d in file %s\n",
                     __LINE__,
                     __FILE__);

            FAIL();
            AdtExit(-1);
          }
        }
        else
        {
          ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                   "failure on line %d in file %s\n",
                   __LINE__,
                   __FILE__);

          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        ::printf("FATAL ERROR: AdtFortranExecutableProgram::writeDelphiClass "
                 "failure on line %d in file %s\n",
                 __LINE__,
                 __FILE__);

        FAIL();
        AdtExit(-1);
      }
    }

    pOutFile.newline();
    pOutFile.write("inherited;");
    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.write("end;");
    pOutFile.newline();
    pOutFile.newline();

    //Write class method implemetations
    for (Iter = rMethodList.begin() ; Iter != rMethodList.end() ; ++Iter)
    {
      const string&         rMethodName    = *Iter;
      const AdtFortranBase* pSubprogramObj = 0;

      ObjIter = rSubroutineObjectMap.find(rMethodName);

      if (ObjIter != rSubroutineObjectMap.end())
      {
        pSubprogramObj = (const AdtFortranBase*)(const AdtParser*)(*ObjIter).second;
      }

      if (pSubprogramObj == 0)
      {
        AdtFortranFunctionSubprogram* pFunctionSubprogram = 0;

        ObjIter = rFunctionObjectMap.find(rMethodName);

        if (ObjIter != rFunctionObjectMap.end())
        {
          pFunctionSubprogram = (AdtFortranFunctionSubprogram*)(AdtParser*)(*ObjIter).second;
        }

        pSubprogramObj = (const AdtFortranBase*)pFunctionSubprogram;

        if (pFunctionSubprogram != 0)
        {
          pFunctionSubprogram->replaceFunctionVarWithResult();
        }
      }

      if (pSubprogramObj != 0)
      {
        AdtFortranName::setClearPrefix(sClassPrefix);
        AdtFortranBase::setChangePrefix(sClassPrefix, sNewClassPrefix);

        pSubprogramObj->writeDelphi(pOutFile, 0);

        AdtFortranName::setClearPrefix(0);
        AdtFortranBase::setChangePrefix(0, 0);
      }
    }

    AdtAutoClass::writeInterfaceMethodsImplInclude(pOutFile,
                                                   DelphiSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeInterfaceGlobalsImplInclude(pOutFile,
                                                   DelphiSourceFileType,
                                                   pClassName,
                                                   pPathPrefix);

    AdtAutoClass::writeConstructorImplInclude(pOutFile,
                                              DelphiSourceFileType,
                                              pClassName,
                                              pPathPrefix);

    pOutFile.decrementIndent();
    pOutFile.newline();
    pOutFile.newline();

    pOutFile.write("end.");
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableProgram::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableProgram::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableProgram::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

void AdtFortranExecutableProgram::enumerateMethodNames(AdtStringList& rMethodList) const
{

}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::hasClass(const char* pClassName,
                                           string& rParentClassName) const
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::buildBlackBoxFile(const char* pBlackBoxFileName,
                                                    AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                    AdtStringByStringMap& rRegardAsClassSubroutineMap,
                                                    double dVersionNumber)
{
  bool bBuilt = false;

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::flattenClass(const char* pClassName,
                                               const AdtParserPtrList& rRootList,
                                               string& rUsesList,
                                               AdtStringByStringMap& rPublicMethodsMap)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::optimise(const AdtStringList& rNewMethodList,
                                           const AdtStringByStringMap& rNewMethodMap)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::expandMacros()
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExecutableProgram::extractClassConstructors(AdtStringList& rConstructorList,
                                                           const char* pClassName,
                                                           const char* pParentClassName,
                                                           const char* pPathPrefix,
                                                           AdtSourceFileType nAsFileType) const
{
  return (false);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableProgram::writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                                 const AdtFortranExecutableProgram* pSavedRoot,
                                                                 const char* pClassName,
                                                                 const char* pParentClassName,
                                                                 bool bExpandMacros) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableProgram::writeNative(AdtFile& rOutFile) const
{
  return (writeFortran(rOutFile, 0));
}

//  ----------------------------------------------------------------------------

AdtSourceFileType AdtFortranExecutableProgram::sourceFileType() const
{
  return (FortranSourceFileType);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranExecutableProgram, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranProgramUnit method implementations
//  ----------------------------------------------------------------------------
AdtFortranProgramUnit::AdtFortranProgramUnit(AdtParser* pFunctionSubprogramObj,
                                             AdtParser* pSubroutineSubprogramObj,
                                             AdtParser* pModuleObj,
                                             AdtParser* pCallExpandObj,
                                             AdtParser* pProgramConstructObj)
 : AdtFortranBase()
{
  initObject(FunctionSubprogram,    pFunctionSubprogramObj,   AdtFortranFunctionSubprogram,   true);
  initObject(SubroutineSubprogram,  pSubroutineSubprogramObj, AdtFortranSubroutineSubprogram, true);
  initObject(Module,                pModuleObj,               AdtFortranModule,               true);
  initObject(CallExpand,            pCallExpandObj,           AdtFortranCallExpand,           true);
  initObject(ProgramConstruct,      pProgramConstructObj,     AdtFortranProgramConstruct,     true);
}

//  ----------------------------------------------------------------------------

AdtFortranProgramUnit::AdtFortranProgramUnit(const AdtFortranProgramUnit& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(FunctionSubprogram,    rCopy, AdtFortranFunctionSubprogram);
  copyObject(SubroutineSubprogram,  rCopy, AdtFortranSubroutineSubprogram);
  copyObject(Module,                rCopy, AdtFortranModule);
  copyObject(CallExpand,            rCopy, AdtFortranCallExpand);
  copyObject(ProgramConstruct,      rCopy, AdtFortranProgramConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranProgramUnit::~AdtFortranProgramUnit()
{
  UtlReleaseReference(FunctionSubprogram);
  UtlReleaseReference(SubroutineSubprogram);
  UtlReleaseReference(Module);
  UtlReleaseReference(CallExpand);
  UtlReleaseReference(ProgramConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramUnit::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeCPP(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)
  {
    SubroutineSubprogram->writeCPP(pOutFile, nMode);
  }

  if (Module != 0)
  {
    Module->writeCPP(pOutFile, nMode);
  }

  if (ProgramConstruct != 0)
  {
    ProgramConstruct->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramUnit::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeDelphi(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)
  {
    SubroutineSubprogram->writeDelphi(pOutFile, nMode);
  }

  if (Module != 0)
  {
    Module->writeDelphi(pOutFile, nMode);
  }

  if (ProgramConstruct != 0)
  {
    ProgramConstruct->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramUnit::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeFortran(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)

  {
    SubroutineSubprogram->writeFortran(pOutFile, nMode);
  }

  if (Module != 0)
  {
    Module->writeFortran(pOutFile, nMode);
  }

  if (ProgramConstruct != 0)
  {
    ProgramConstruct->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}


//  ----------------------------------------------------------------------------

implType(AdtFortranProgramUnit, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCallExpand method implementations
//  ----------------------------------------------------------------------------
AdtFortranExpr* AdtFortranCallExpand::createExpression(AdtFortranName* pNameObj) const
{
  AdtFortranExpr* pExpr = 0;

  if (pNameObj != 0)
  {
    AdtFortranPrimary*      pPrimary      = new AdtFortranPrimary(pNameObj, 0, 0, 0, 0, 0, 0, false, false);
    AdtFortranMultOperand*  pMultOperand  = new AdtFortranMultOperand(pPrimary, 0);
    AdtFortranAddOperand*   pAddOperand   = new AdtFortranAddOperand(pMultOperand, 0, false);
    AdtFortranLevel2Expr*   pLevel2Expr   = new AdtFortranLevel2Expr(pAddOperand, 0, false, false);
    AdtFortranLevel4Expr*   pLevel4Expr   = new AdtFortranLevel4Expr(pLevel2Expr, 0, 0);
    AdtFortranAndOperand*   pAndOperand   = new AdtFortranAndOperand(pLevel4Expr, false);
    AdtFortranOrOperand*    pOrOperand    = new AdtFortranOrOperand(pAndOperand, 0);
    AdtFortranEquivOperand* pEquivOperand = new AdtFortranEquivOperand(pOrOperand, 0);

    pExpr = new AdtFortranExpr(pEquivOperand, 0, false);

    UtlReleaseReference(pEquivOperand);
    UtlReleaseReference(pOrOperand);
    UtlReleaseReference(pAndOperand);
    UtlReleaseReference(pLevel4Expr);
    UtlReleaseReference(pLevel2Expr);
    UtlReleaseReference(pAddOperand);
    UtlReleaseReference(pMultOperand);
    UtlReleaseReference(pPrimary);
  }

  return (pExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranCallExpand::AdtFortranCallExpand(AdtParser* pNameObj,
                                           AdtParser* pNameListObj,
                                           AdtParser* pConditionalBodyObj,
                                           AdtParser* pTypeDeclarationStmtListObj,
                                           bool bHasBrackets)
 : AdtFortranBase()
{
  initObject(Name,                    pNameObj,                     AdtFortranName,                     true);
  initObject(NameList,                pNameListObj,                 AdtFortranNameList,                 true);
  initObject(ConditionalBody,         pConditionalBodyObj,          AdtFortranConditionalBody,          true);
  initObject(TypeDeclarationStmtList, pTypeDeclarationStmtListObj,  AdtFortranTypeDeclarationStmtList,  true);

  if (Name != 0)
  {
    name(Name->name());
  }

  HasBrackets = bHasBrackets;
}

//  ----------------------------------------------------------------------------

AdtFortranCallExpand::AdtFortranCallExpand(const AdtFortranCallExpand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,                    rCopy, AdtFortranName);
  copyObject(NameList,                rCopy, AdtFortranNameList);
  copyObject(ConditionalBody,         rCopy, AdtFortranConditionalBody);
  copyObject(TypeDeclarationStmtList, rCopy, AdtFortranTypeDeclarationStmtList);

  HasBrackets = rCopy.HasBrackets;
}

//  ----------------------------------------------------------------------------

AdtFortranCallExpand::~AdtFortranCallExpand()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(NameList);
  UtlReleaseReference(ConditionalBody);
  UtlReleaseReference(TypeDeclarationStmtList);
}

//  ----------------------------------------------------------------------------

bool AdtFortranCallExpand::expand(AdtFortranCallStmt* pCallStmt,
                                  AdtFortranModuleBody* pModuleBody,
                                  int nIteration,
                                  int nFnNumber,
                                  AdtStringList& rNewAttributeList) const
{
  bool  bDone = false;

  if ((pCallStmt != 0) && (ConditionalBody != 0))
  {
    AdtFortranConditionalBody*  pBodyCopy           = 0;
    AdtParser*                  pBodyConstructObj   = pCallStmt->findAscendantWithClassLineage("AdtFortranActionStmt,AdtFortranExecutableConstruct,AdtFortranBodyConstruct");
    AdtParser*                  pArgListObj         = pCallStmt->findDescendant("SectionSubscriptList");

    if (pBodyConstructObj == 0)
    {
      pBodyConstructObj = pCallStmt->findAscendantWithClassLineage("AdtFortranActionStmt,AdtFortranExecutableConstruct");
    }

    if ((pArgListObj != 0) && (pArgListObj->listSize() > 0))
    {
      //We have call parameters
      if ((NameList != 0) && (NameList->listSize() == pArgListObj->listSize()))
      {
        //Argument list size matches
        pBodyCopy = (AdtFortranConditionalBody*)ConditionalBody->copy();

        if (pBodyCopy != 0)
        {
          AdtParserPtrListConstIter ParamIter;
          AdtParserPtrListConstIter ExprIter = pArgListObj->objList().begin();

          //Step through each parameter and argment so we can substitute the
          //argument expression in place of the parameter
          for (ParamIter = NameList->objList().begin() ; ParamIter != NameList->objList().end() ; ++ParamIter)
          {
            AdtParser*  pParam  = *ParamIter;
            AdtParser*  pExpr   = *ExprIter;

            if ((pParam != 0) && (pExpr != 0))
            {
              AdtParser*  pArgBottom        = pParam->copy();
              AdtParser*  pArg              = createExpression((AdtFortranName*)pArgBottom);

              UtlReleaseReference(pArgBottom);

              if ((pArgBottom !=0) && (pArg != 0))
              {
                AdtParserPtrList      SubstitutionList;
                AdtParserPtrListIter  SubstitutionIter;

                //Substitute all instances of the parameter with the argument expression
                pBodyCopy->findObjects(SubstitutionList, "AdtFortranName", pParam->name());

                SubstitutionList.sort();
                SubstitutionList.reverse();

                for (SubstitutionIter = SubstitutionList.begin() ; SubstitutionIter != SubstitutionList.end() ; ++SubstitutionIter)
                {
                  AdtParser*  pName   = *SubstitutionIter;

                  if (pName != 0)
                  {
                    AdtParser*  pSubstitutionTop  = 0;
                    AdtParser*  pArgTop           = 0;

                    pName->findOutermostMatch(pArgBottom, pSubstitutionTop, pArgTop, 0);

                    if (pSubstitutionTop != 0)
                    {
                      AdtParser*  pSubstitutionTopNew = 0;
                      AdtParser*  pParamTop           = pExpr->findDescendantMatch(pSubstitutionTop, pSubstitutionTopNew);

                      if ((pParamTop != 0) && (pSubstitutionTopNew != 0))
                      {
                        //Substitute a copy of pParamTop with pSubstitutionTop.
                        AdtParser*  pParamTopCopy = pParamTop->copy();

                        if (pParamTopCopy != 0)
                        {
                          pSubstitutionTopNew->replaceInParent(pParamTopCopy);
                          UtlReleaseReference(pParamTopCopy);
                        }
                      }
                      else
                      {
                        ::printf("FATAL ERROR: AdtFortranCallExpand::expand "
                                 "failure on line %d in file %s\n",
                                 __LINE__,
                                 __FILE__);

                        FAIL();
                        AdtExit(-1);
                      }
                    }
                    else
                    {
                      ::printf("FATAL ERROR: AdtFortranCallExpand::expand "
                               "failure on line %d in file %s\n",
                               __LINE__,
                               __FILE__);

                      FAIL();
                      AdtExit(-1);
                    }
                  }
                }
              }

              UtlReleaseReference(pArg);
            }

            ++ExprIter;
          }
        }
      }
      else
      {
        //Argument list does not match so no substitution is possible
        ::printf("WARNING: Incompatible macro replacement, %s\n", name().c_str());
      }
    }
    else
    {
      //We have no call parameters
      if ((NameList == 0) || ((NameList != 0) && (NameList->listSize() == 0)))
      {
        //Empty argument list
        pBodyCopy = (AdtFortranConditionalBody*)ConditionalBody->copy();
      }
      else
      {
        //Argument list not empty so no substitution is possible
        ::printf("WARNING: Incompatible macro replacement, %s\n", name().c_str());
      }
    }

    if ((pBodyConstructObj != 0) && (pBodyConstructObj->parent() != 0) && (pBodyCopy != 0) && (pModuleBody != 0))
    {
      //Need to put a copy of the label object in the call statement into the
      //first line of the expansion (pBodyCopy).
      AdtFortranLblDef* pLblDef = (AdtFortranLblDef*)pCallStmt->findDescendant("LblDef");

      if (pLblDef != 0)
      {
        AdtFortranLblDef* pLblDefCopy = (AdtFortranLblDef*)pLblDef->copy();

        if (pLblDefCopy != 0)
        {
          AdtParserPtrListConstIter Iter = pBodyCopy->objList().begin();

          if (Iter != pBodyCopy->objList().end())
          {
            AdtParser*  pExecConstructObj = *Iter;

            if (pExecConstructObj != 0)
            {
              AdtParser*  pLblDefObj = pExecConstructObj->findObject("AdtFortranLblDef");

              if (pLblDefObj != 0)
              {
                pLblDefObj->replaceInParent(pLblDefCopy);
              }
            }
          }
        }

        UtlReleaseReference(pLblDefCopy);
      }

      AdtParserPtrByStringMap VarMap;
      AdtParserPtrList        VarList;

      pModuleBody->findObjects(VarList,
                               "AdtFortranName",
                               0,
                               false,
                               "AdtFortranEntityDecl");

      listToMap(VarMap, VarList);

      //Typical expansion definition looks like
      //
      //CALL_EXPAND PUSHINTEGER4(x)
      //    istacki = istacki + 1
      //    istack(istacki) = x
      //ADD_VARIABLES
      //    INTEGER istacki
      //    INTEGER istack(:)
      //END

      if (TypeDeclarationStmtList != 0)
      {
        AdtFortranTypeDeclarationStmtList*  pDeclListCopy = (AdtFortranTypeDeclarationStmtList*)TypeDeclarationStmtList->copy();

        if (pDeclListCopy != 0)
        {
          AdtParserPtrList          VarList;
          AdtParserPtrListConstIter VarIter;

          //Need to enumerate the variable names, alter the name by the
          //interation number, and add those definitions to the module.
          pDeclListCopy->findObjects(VarList, "AdtFortranName", 0, false, "AdtFortranEntityDecl");

          for (VarIter = VarList.begin() ; VarIter != VarList.end() ; ++VarIter)
          {
            AdtParser*  pName = *VarIter;

            if (pName != 0)
            {
              char sBuffer[32] = {0};

              string sOriginalName(pName->name());
              string sNewName(sOriginalName);

              ::sprintf(sBuffer, "_%d_%d", nFnNumber, nIteration);

              sNewName += sBuffer;

              //Change the variable declaration name
              pName->name(sNewName);

              if (pBodyCopy != 0)
              {
                AdtParserPtrList      ChangeVarList;
                AdtParserPtrListIter  ChangeVarIter;

                //Change the name of all instances of the variable in the code
                //to the new name
                pBodyCopy->findObjects(ChangeVarList, "AdtFortranName", sOriginalName, false);

                for (ChangeVarIter = ChangeVarList.begin() ; ChangeVarIter != ChangeVarList.end() ; ++ChangeVarIter)
                {
                  AdtParser*  pName = *ChangeVarIter;

                  if (pName != 0)
                  {
                    pName->name(sNewName);
                  }
                }
              }

              //Check if the variable is already defined and if it is delete it
              //from the definition to be added.
              if (VarMap.find(sNewName) != VarMap.end())
              {
                AdtParser*  pEntityDecl = pName->findAscendantWithClassLineage("AdtFortranEntityDecl");

                if ((pEntityDecl != 0) && (pEntityDecl->parent() != 0))
                {
                  pEntityDecl->parent()->remove(pEntityDecl);
                }
              }
              else
              {
                rNewAttributeList.push_back(sNewName);
              }
            }
          }

          //Add the variable declarations to the Module definition
          AdtParserPtrListConstIter DeclIter;

          for (DeclIter = pDeclListCopy->objList().begin() ; DeclIter != pDeclListCopy->objList().end() ; ++DeclIter)
          {
            AdtParser*  pTypeDeclStmt = *DeclIter;

            if (pTypeDeclStmt != 0)
            {
              AdtFortranSpecificationPartConstruct* pSpecificationPart = new AdtFortranSpecificationPartConstruct(0, 0, 0, pTypeDeclStmt, 0, 0, 0, 0);
              AdtFortranModuleBodyContent*          pBodyContent       = new AdtFortranModuleBodyContent(pSpecificationPart, 0, 0);

              pModuleBody->add(pBodyContent);
              UtlReleaseReference(pBodyContent);
              UtlReleaseReference(pSpecificationPart);
            }
          }
        }

        UtlReleaseReference(pDeclListCopy);
      }

      //Do the call expansion
      if (pBodyConstructObj->isType("AdtFortranExecutableConstruct"))
      {
        //AdtFortranExecutableConstruct case (ie. DO loops and IF statements)
        pBodyConstructObj->parent()->replace(pBodyConstructObj, pBodyCopy);
        bDone = true;
      }
      else if (pBodyConstructObj->isType("AdtFortranBodyConstruct"))
      {
        //AdtFortranBodyConstruct case (ie. outer scope body code not in control structures)
        AdtFortranBody* pMacroBody = new AdtFortranBody(0);

        if (pMacroBody != 0)
        {
          AdtParserPtrListConstIter ExecIter;

          for (ExecIter = pBodyCopy->objList().begin() ; ExecIter != pBodyCopy->objList().end() ; ++ExecIter)
          {
            AdtFortranBodyConstruct*  pConstruct = new AdtFortranBodyConstruct(0, *ExecIter);

            if (pConstruct != 0)
            {
              pMacroBody->add(pConstruct);
              bDone = true;
            }

            UtlReleaseReference(pConstruct);
          }

          pBodyConstructObj->parent()->replace(pBodyConstructObj, pMacroBody);
        }

        UtlReleaseReference(pMacroBody);
      }
    }

    UtlReleaseReference(pBodyCopy);
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallExpand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallExpand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallExpand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCallExpand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranProgramConstruct class
//  ----------------------------------------------------------------------------
AdtFortranProgramConstruct::AdtFortranProgramConstruct(AdtParser* pLblDefObj,
                                                       AdtParser* pNameObj,
                                                       AdtParser* pBodyObj,
                                                       AdtParser* pEndLblDefObj)
 : AdtFortranBase()
{
  initObject(LblDef,      pLblDefObj,     AdtFortranLblDef, true);
  initObject(Name,        pNameObj,       AdtFortranName,   true);
  initObject(Body,        pBodyObj,       AdtFortranBody,   true);
  initObject(EndLblDef,   pEndLblDefObj,  AdtFortranLblDef, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranProgramConstruct::AdtFortranProgramConstruct(const AdtFortranProgramConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,      rCopy,  AdtFortranLblDef);
  copyObject(Name,        rCopy,  AdtFortranName);
  copyObject(Body,        rCopy,  AdtFortranBody);
  copyObject(EndLblDef,   rCopy,  AdtFortranLblDef);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranProgramConstruct::~AdtFortranProgramConstruct()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
  UtlReleaseReference(Body);
  UtlReleaseReference(EndLblDef);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranProgramConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " PROGRAM ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (Body != 0)
  {
    Body->writeFortran(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.newline();

  if (EndLblDef != 0)
  {
    EndLblDef->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranProgramConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranTypeDeclarationStmtList class
//  ----------------------------------------------------------------------------
AdtFortranTypeDeclarationStmtList::AdtFortranTypeDeclarationStmtList(AdtParser* pTypeDeclarationStmtObj)
 : AdtFortranBase()
{
  add(pTypeDeclarationStmtObj);
}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmtList::AdtFortranTypeDeclarationStmtList(const AdtFortranTypeDeclarationStmtList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmtList::~AdtFortranTypeDeclarationStmtList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmtList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmtList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmtList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranTypeDeclarationStmtList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranBody method implementations
//  ----------------------------------------------------------------------------
AdtFortranBody::AdtFortranBody(AdtParser* pBodyConstructObj)
 : AdtFortranBase()
{
  add(pBodyConstructObj);
}

//  ----------------------------------------------------------------------------

AdtFortranBody::AdtFortranBody(const AdtFortranBody& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranBody::~AdtFortranBody()
{

}

//  ----------------------------------------------------------------------------

void AdtFortranBody::addTypeDeclarationStmt(AdtFortranTypeDeclarationStmt* pObj)
{
  // Need to find the last type declaration in the list and insert the new one
  // there.
  AdtParserPtrList  ObjList;
  AdtParser*        pInsertAfter = 0;

  enumerate(ObjList);

  AdtParserPtrListConstIter Iter;

  for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if ((pObj != 0) && (pObj->findDescendant("SpecificationPartConstruct") != 0))
    {
      pInsertAfter = pObj;
    }
  }

  if (pInsertAfter == 0)
  {

  }
  else
  {
    AdtFortranSpecificationPartConstruct* pSpecPartConstruct = new AdtFortranSpecificationPartConstruct(0, 0, 0, pObj, 0, 0, 0, 0);
    AdtFortranBodyConstruct*              pBodyConstruct     = new AdtFortranBodyConstruct(pSpecPartConstruct, 0);

    insertAfter(pInsertAfter, pBodyConstruct);

    UtlReleaseReference(pBodyConstruct);
    UtlReleaseReference(pSpecPartConstruct);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBody::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBody::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBody::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranBody, AdtFortranBase);



//  ----------------------------------------------------------------------------
//  AdtFortranBodyConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranBodyConstruct::AdtFortranBodyConstruct(AdtParser* pSpecificationPartConstructObj,
                                                 AdtParser* pExecutableConstructObj)
 : AdtFortranBase()
{
  initObject(SpecificationPartConstruct,  pSpecificationPartConstructObj, AdtFortranSpecificationPartConstruct, true);
  initObject(ExecutableConstruct,         pExecutableConstructObj,        AdtFortranExecutableConstruct,        true);
}

//  ----------------------------------------------------------------------------

AdtFortranBodyConstruct::AdtFortranBodyConstruct(const AdtFortranBodyConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(SpecificationPartConstruct,  rCopy, AdtFortranSpecificationPartConstruct);
  copyObject(ExecutableConstruct,         rCopy, AdtFortranExecutableConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranBodyConstruct::~AdtFortranBodyConstruct()
{
  UtlReleaseReference(SpecificationPartConstruct);
  UtlReleaseReference(ExecutableConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBodyConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeCPP(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    ExecutableConstruct->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBodyConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeDelphi(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    ExecutableConstruct->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranBodyConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeFortran(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    ExecutableConstruct->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranBodyConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranFunctionSubprogram method implementations
//  ----------------------------------------------------------------------------
AdtFortranFunctionSubprogram::AdtFortranFunctionSubprogram(AdtParser* pFunctionStmtObj,
                                                           AdtParser* pEndFunctionStmtObj,
                                                           AdtParser* pBodyObj)
 : AdtFortranBase()
{
  initObject(FunctionStmt,    pFunctionStmtObj,     AdtFortranFunctionStmt,     true);
  initObject(EndFunctionStmt, pEndFunctionStmtObj,  AdtFortranEndFunctionStmt,  true);
  initObject(Body,            pBodyObj,             AdtFortranBody,             true);

  if (FunctionStmt != 0)
  {
    name(FunctionStmt->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranFunctionSubprogram::AdtFortranFunctionSubprogram(const AdtFortranFunctionSubprogram& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(FunctionStmt,    rCopy,  AdtFortranFunctionStmt);
  copyObject(EndFunctionStmt, rCopy,  AdtFortranEndFunctionStmt);
  copyObject(Body,            rCopy,  AdtFortranBody);
}

//  ----------------------------------------------------------------------------

AdtFortranFunctionSubprogram::~AdtFortranFunctionSubprogram()
{
  UtlReleaseReference(FunctionStmt);
  UtlReleaseReference(EndFunctionStmt);
  UtlReleaseReference(Body);
}

//  ----------------------------------------------------------------------------

void AdtFortranFunctionSubprogram::replaceFunctionVarWithResult()
{
  if (Body != 0)
  {
    AdtParserPtrListIter  Iter;
    AdtParserPtrList      rResultVarList;

    Body->findObjects(rResultVarList,
                      "AdtFortranName",
                      name(),
                      false);

    for (Iter = rResultVarList.begin() ; Iter != rResultVarList.end() ; ++Iter)
    {
      AdtFortranName* pFortranNameObj = (AdtFortranName*)(AdtParser*)*Iter;

      if (pFortranNameObj != 0)
      {
        pFortranNameObj->name("result");
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionSubprogram::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (FunctionStmt != 0)
  {
    FunctionStmt->writeCPP(pOutFile, nMode);
  }

  if (nMode == CPP_MODE_FUNCTION_DECLARATION)
  {
    //do nothing
  }
  else
  {
    if (Body != 0)
    {
      if (FunctionStmt != 0)
      {
        FunctionStmt->writeCPP_Initialisations(pOutFile);
        FunctionStmt->writeCPP_Allocations(pOutFile);
      }

      string      sReturnVar("ret_");
      int         nStart  = 0;
      int         nLength = 0;
      const char* pName   = name().c_str();

      if (AdtParser::hasSubString(pName,
                                  RemovePrefixString,
                                  nStart,
                                  nLength,
                                  false) && (nStart == 0))
      {
        pName = pName + nLength;
      }

      sReturnVar += pName;

      AdtFortranName::setSubstitute(name(), sReturnVar);

      Body->writeCPP(pOutFile, nMode);

      AdtFortranName::setSubstitute(0, 0);

      if (FunctionStmt != 0)
      {
        FunctionStmt->writeCPP_Deallocations(pOutFile);
      }

      pOutFile.decrementIndent();
      pOutFile.newline();

      write(pOutFile, "}");
      pOutFile.newline();
    }

    if (EndFunctionStmt != 0)
    {
      EndFunctionStmt->writeCPP(pOutFile, nMode);
    }

    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionSubprogram::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (FunctionStmt != 0)
  {
    FunctionStmt->writeDelphi(pOutFile, nMode);
  }

  if (nMode == DELPHI_MODE_FUNCTION_DECLARATION)
  {
    //do nothing
  }
  else
  {
    if (Body != 0)
    {
      AdtStringList VarList;
      AdtStringList DestroyList;

      if (FunctionStmt != 0)
      {
        pOutFile.disable();
        FunctionStmt->writeDelphiAllocations(pOutFile, &VarList, &DestroyList);
        pOutFile.enable();

        if (VarList.size() > 0)
        {
          if (!FunctionStmt->hasVarDeclarations())
          {
            write(pOutFile, "Var");
          }

          pOutFile.incrementIndent();
          pOutFile.newline();

          for (AdtStringListIter VarIter = VarList.begin() ; VarIter != VarList.end() ; ++VarIter)
          {
            write(pOutFile, *VarIter);
            pOutFile.newline();
          }

          pOutFile.decrementIndent();
          pOutFile.newline();
        }
      }

      write(pOutFile, "begin");

      pOutFile.incrementIndent();
      pOutFile.newline();

      if (FunctionStmt != 0)
      {
        FunctionStmt->writeDelphiInitialisations(pOutFile);
        FunctionStmt->writeDelphiAllocations(pOutFile, 0, 0);
      }

      Body->writeDelphi(pOutFile, nMode);

      if (FunctionStmt != 0)
      {
        FunctionStmt->writeDelphiDeallocations(pOutFile);
      }

      if (DestroyList.size() > 0)
      {
        for (AdtStringListIter DestroyIter = DestroyList.begin() ; DestroyIter != DestroyList.end() ; ++DestroyIter)
        {
          pOutFile.newline();
          write(pOutFile, *DestroyIter);
        }
      }

      pOutFile.decrementIndent();
      pOutFile.newline();

      write(pOutFile, "end;");
      pOutFile.newline();
    }

    if (EndFunctionStmt != 0)
    {
      EndFunctionStmt->writeDelphi(pOutFile, nMode);
    }

    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionSubprogram::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (FunctionStmt != 0)
  {
    FunctionStmt->writeFortran(pOutFile, nMode);
  }

  if (Body != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    Body->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndFunctionStmt != 0)
  {
    EndFunctionStmt->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranFunctionSubprogram, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSubroutineSubprogram method implementations
//  ----------------------------------------------------------------------------
AdtFortranSubroutineSubprogram::AdtFortranSubroutineSubprogram(AdtParser* pSubroutineStmtObj,
                                                               AdtParser* pEndSubroutineStmtObj,
                                                               AdtParser* pBodyObj)
 : AdtFortranBase()
{
  initObject(SubroutineStmt,    pSubroutineStmtObj,     AdtFortranSubroutineStmt,     true);
  initObject(EndSubroutineStmt, pEndSubroutineStmtObj,  AdtFortranEndSubroutineStmt,  true);
  initObject(Body,              pBodyObj,               AdtFortranBody,               true);

  if (SubroutineStmt != 0)
  {
    name(SubroutineStmt->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranSubroutineSubprogram::AdtFortranSubroutineSubprogram(const AdtFortranSubroutineSubprogram& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(SubroutineStmt,    rCopy,  AdtFortranSubroutineStmt);
  copyObject(EndSubroutineStmt, rCopy,  AdtFortranEndSubroutineStmt);
  copyObject(Body,              rCopy,  AdtFortranBody);
}

//  ----------------------------------------------------------------------------

AdtFortranSubroutineSubprogram::~AdtFortranSubroutineSubprogram()
{
  UtlReleaseReference(SubroutineStmt);
  UtlReleaseReference(EndSubroutineStmt);
  UtlReleaseReference(Body);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineSubprogram::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (SubroutineStmt != 0)
  {
    SubroutineStmt->writeCPP(pOutFile, nMode);
  }

  if (nMode == CPP_MODE_FUNCTION_DECLARATION)
  {
    //do nothing
  }
  else
  {
    if (Body != 0)
    {
      if (SubroutineStmt != 0)
      {
        SubroutineStmt->writeCPP_Initialisations(pOutFile);
        SubroutineStmt->writeCPP_Allocations(pOutFile);
      }

      Body->writeCPP(pOutFile, nMode);

      if (SubroutineStmt != 0)
      {
        SubroutineStmt->writeCPP_Deallocations(pOutFile);
      }

      pOutFile.decrementIndent();
      pOutFile.newline();

      write(pOutFile, "}");
      pOutFile.newline();
    }

    if (EndSubroutineStmt != 0)
    {
      EndSubroutineStmt->writeCPP(pOutFile, nMode);
    }

    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineSubprogram::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (SubroutineStmt != 0)
  {
    SubroutineStmt->writeDelphi(pOutFile, nMode);
  }

  if (nMode == DELPHI_MODE_FUNCTION_DECLARATION)
  {
    //do nothing
  }
  else
  {
    if (Body != 0)
    {
      AdtStringList VarList;
      AdtStringList DestroyList;

      if (SubroutineStmt != 0)
      {
        pOutFile.disable();
        SubroutineStmt->writeDelphiAllocations(pOutFile, &VarList, &DestroyList);
        pOutFile.enable();

        if (VarList.size() > 0)
        {
          if (!SubroutineStmt->hasVarDeclarations())
          {
            write(pOutFile, "Var");
          }

          pOutFile.incrementIndent();
          pOutFile.newline();

          for (AdtStringListIter VarIter = VarList.begin() ; VarIter != VarList.end() ; ++VarIter)
          {
            write(pOutFile, *VarIter);
            pOutFile.newline();
          }

          pOutFile.decrementIndent();
          pOutFile.newline();
        }
      }

      write(pOutFile, "begin");

      pOutFile.incrementIndent();
      pOutFile.newline();

      if (SubroutineStmt != 0)
      {
        SubroutineStmt->writeDelphiInitialisations(pOutFile);
        SubroutineStmt->writeDelphiAllocations(pOutFile, 0, 0);
      }

      Body->writeDelphi(pOutFile, nMode);

      if (SubroutineStmt != 0)
      {
        SubroutineStmt->writeDelphiDeallocations(pOutFile);
      }

      if (DestroyList.size() > 0)
      {
        for (AdtStringListIter DestroyIter = DestroyList.begin() ; DestroyIter != DestroyList.end() ; ++DestroyIter)
        {
          pOutFile.newline();
          write(pOutFile, *DestroyIter);
        }
      }

      pOutFile.decrementIndent();
      pOutFile.newline();

      write(pOutFile, "end;");
      pOutFile.newline();
    }

    if (EndSubroutineStmt != 0)
    {
      EndSubroutineStmt->writeDelphi(pOutFile, nMode);
    }

    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineSubprogram::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (SubroutineStmt != 0)
  {
    SubroutineStmt->writeFortran(pOutFile, nMode);
  }

  if (Body != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    Body->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndSubroutineStmt != 0)
  {
    EndSubroutineStmt->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSubroutineSubprogram, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranModule method implementations
//  ----------------------------------------------------------------------------
AdtFortranModule::AdtFortranModule(AdtParser* pModuleStmtObj,
                                   AdtParser* pModuleBodyObj,
                                   AdtParser* pEndModuleStmtObj)
 : AdtFortranBase()
{
  bool bCreated = false;

  // If pModuleBodyObj is null then create an empty one as we need this to be
  // initialised for the mergeWith() method to work correctly.
  if (pModuleBodyObj == 0)
  {
    pModuleBodyObj  = new AdtFortranModuleBody();
    bCreated        = true;
  }

  initObject(ModuleStmt,    pModuleStmtObj,     AdtFortranModuleStmt,     true);
  initObject(ModuleBody,    pModuleBodyObj,     AdtFortranModuleBody,     true);
  initObject(EndModuleStmt, pEndModuleStmtObj,  AdtFortranEndModuleStmt,  true);

  if (ModuleStmt != 0)
  {
    name(ModuleStmt->name());
  }

  if (bCreated)
  {
    UtlReleaseReference(pModuleBodyObj);
  }
}

//  ----------------------------------------------------------------------------

AdtFortranModule::AdtFortranModule(const AdtFortranModule& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ModuleStmt,    rCopy, AdtFortranModuleStmt);
  copyObject(ModuleBody,    rCopy, AdtFortranModuleBody);
  copyObject(EndModuleStmt, rCopy, AdtFortranEndModuleStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranModule::~AdtFortranModule()
{
  UtlReleaseReference(ModuleStmt);
  UtlReleaseReference(ModuleBody);
  UtlReleaseReference(EndModuleStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModule::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModule::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModule::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ModuleStmt != 0)
  {
    ModuleStmt->writeFortran(pOutFile, nMode);
  }

  if (ModuleBody != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    ModuleBody->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndModuleStmt != 0)
  {
    EndModuleStmt->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranModule, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranModuleBody method implementations
//  ----------------------------------------------------------------------------
AdtFortranModuleBody::AdtFortranModuleBody()
 : AdtFortranBase()
{

}

//  ----------------------------------------------------------------------------

AdtFortranModuleBody::AdtFortranModuleBody(AdtParser* pModuleBodyContentObj)
 : AdtFortranBase()
{
  add(pModuleBodyContentObj);
}

//  ----------------------------------------------------------------------------

AdtFortranModuleBody::AdtFortranModuleBody(const AdtFortranModuleBody& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranModuleBody::~AdtFortranModuleBody()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBody::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBody::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBody::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", false));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranModuleBody, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranModuleBodyContent method implementations
//  ----------------------------------------------------------------------------
AdtFortranModuleBodyContent::AdtFortranModuleBodyContent(AdtParser* pSpecificationPartConstructObj,
                                                         AdtParser* pFunctionSubprogramObj,
                                                         AdtParser* pSubroutineSubprogramObj)
 : AdtFortranBase()
{
  initObject(SpecificationPartConstruct,  pSpecificationPartConstructObj, AdtFortranSpecificationPartConstruct, true);
  initObject(FunctionSubprogram,          pFunctionSubprogramObj,         AdtFortranFunctionSubprogram,         true);
  initObject(SubroutineSubprogram,        pSubroutineSubprogramObj,       AdtFortranSubroutineSubprogram,       true);
}

//  ----------------------------------------------------------------------------

AdtFortranModuleBodyContent::AdtFortranModuleBodyContent(const AdtFortranModuleBodyContent& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(SpecificationPartConstruct,  rCopy,  AdtFortranSpecificationPartConstruct);
  copyObject(FunctionSubprogram,          rCopy,  AdtFortranFunctionSubprogram);
  copyObject(SubroutineSubprogram,        rCopy,  AdtFortranSubroutineSubprogram);
}

//  ----------------------------------------------------------------------------

AdtFortranModuleBodyContent::~AdtFortranModuleBodyContent()
{
  UtlReleaseReference(SpecificationPartConstruct);
  UtlReleaseReference(FunctionSubprogram);
  UtlReleaseReference(SubroutineSubprogram);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBodyContent::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeCPP(pOutFile, nMode);
  }

  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeCPP(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)
  {
    SubroutineSubprogram->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBodyContent::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeDelphi(pOutFile, nMode);
  }

  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeDelphi(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)
  {
    SubroutineSubprogram->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleBodyContent::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (SpecificationPartConstruct != 0)
  {
    SpecificationPartConstruct->writeFortran(pOutFile, nMode);
  }

  if (FunctionSubprogram != 0)
  {
    FunctionSubprogram->writeFortran(pOutFile, nMode);
  }

  if (SubroutineSubprogram != 0)
  {
    SubroutineSubprogram->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranModuleBodyContent, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSpecificationPartConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranSpecificationPartConstruct::AdtFortranSpecificationPartConstruct(AdtParser* pUseStmtObj,
                                                                           AdtParser* pImplicitStmtObj,
                                                                           AdtParser* pParameterStmtObj,
                                                                           AdtParser* pTypeDeclarationStmtObj,
                                                                           AdtParser* pDimensionStmtObj,
                                                                           AdtParser* pIntrinsicStmtObj,
                                                                           AdtParser* pExternalStmtObj,
                                                                           AdtParser* pIntentStmtObj)
 : AdtFortranBase()
{
  initObject(UseStmt,             pUseStmtObj,              AdtFortranUseStmt,              true);
  initObject(ImplicitStmt,        pImplicitStmtObj,         AdtFortranImplicitStmt,         true);
  initObject(ParameterStmt,       pParameterStmtObj,        AdtFortranParameterStmt,        true);
  initObject(TypeDeclarationStmt, pTypeDeclarationStmtObj,  AdtFortranTypeDeclarationStmt,  true);
  initObject(DimensionStmt,       pDimensionStmtObj,        AdtFortranDimensionStmt,        true);
  initObject(IntrinsicStmt,       pIntrinsicStmtObj,        AdtFortranIntrinsicStmt,        true);
  initObject(ExternalStmt,        pExternalStmtObj,         AdtFortranExternalStmt,         true);
  initObject(IntentStmt,          pIntentStmtObj,           AdtFortranIntentStmt,           true);
}

//  ----------------------------------------------------------------------------

AdtFortranSpecificationPartConstruct::AdtFortranSpecificationPartConstruct(const AdtFortranSpecificationPartConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(UseStmt,             rCopy,  AdtFortranUseStmt);
  copyObject(ImplicitStmt,        rCopy,  AdtFortranImplicitStmt);
  copyObject(ParameterStmt,       rCopy,  AdtFortranParameterStmt);
  copyObject(TypeDeclarationStmt, rCopy,  AdtFortranTypeDeclarationStmt);
  copyObject(DimensionStmt,       rCopy,  AdtFortranDimensionStmt);
  copyObject(IntrinsicStmt,       rCopy,  AdtFortranIntrinsicStmt);
  copyObject(ExternalStmt,        rCopy,  AdtFortranExternalStmt);
  copyObject(IntentStmt,          rCopy,  AdtFortranIntentStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranSpecificationPartConstruct::~AdtFortranSpecificationPartConstruct()
{
  UtlReleaseReference(UseStmt);
  UtlReleaseReference(ImplicitStmt);
  UtlReleaseReference(ParameterStmt);
  UtlReleaseReference(TypeDeclarationStmt);
  UtlReleaseReference(DimensionStmt);
  UtlReleaseReference(IntrinsicStmt);
  UtlReleaseReference(ExternalStmt);
  UtlReleaseReference(IntentStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSpecificationPartConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (UseStmt != 0)
  {
    UseStmt->writeCPP(pOutFile, nMode);
  }

//  if (IntentStmt != 0)
//  {
//    IntentStmt->writeCPP(pOutFile, nMode);
//  }

  if (ImplicitStmt != 0)
  {
    ImplicitStmt->writeCPP(pOutFile, nMode);
  }

  if (ParameterStmt != 0)
  {
    ParameterStmt->writeCPP(pOutFile, nMode);
  }

  if (TypeDeclarationStmt != 0)
  {
    TypeDeclarationStmt->writeCPP(pOutFile, nMode);
  }

  if (DimensionStmt != 0)
  {
    DimensionStmt->writeCPP(pOutFile, nMode);
  }

  if (IntrinsicStmt != 0)
  {
    IntrinsicStmt->writeCPP(pOutFile, nMode);
  }

  if (ExternalStmt != 0)
  {
    ExternalStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSpecificationPartConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (UseStmt != 0)
  {
    UseStmt->writeDelphi(pOutFile, nMode);
  }

//  if (IntentStmt != 0)
//  {
//    IntentStmt->writeDelphi(pOutFile, nMode);
//  }

  if (ImplicitStmt != 0)
  {
    ImplicitStmt->writeDelphi(pOutFile, nMode);
  }

  if (ParameterStmt != 0)
  {
    ParameterStmt->writeDelphi(pOutFile, nMode);
  }

  if (TypeDeclarationStmt != 0)
  {
    TypeDeclarationStmt->writeDelphi(pOutFile, nMode);
  }

  if (DimensionStmt != 0)
  {
    DimensionStmt->writeDelphi(pOutFile, nMode);
  }

  if (IntrinsicStmt != 0)
  {
    IntrinsicStmt->writeDelphi(pOutFile, nMode);
  }

  if (ExternalStmt != 0)
  {
    ExternalStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSpecificationPartConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (UseStmt != 0)
  {
    UseStmt->writeFortran(pOutFile, nMode);
  }

  if (IntentStmt != 0)
  {
    IntentStmt->writeFortran(pOutFile, nMode);
  }

  if (ImplicitStmt != 0)
  {
    ImplicitStmt->writeFortran(pOutFile, nMode);
  }

  if (ParameterStmt != 0)
  {
    ParameterStmt->writeFortran(pOutFile, nMode);
  }

  if (TypeDeclarationStmt != 0)
  {
    TypeDeclarationStmt->writeFortran(pOutFile, nMode);
  }

  if (DimensionStmt != 0)
  {
    DimensionStmt->writeFortran(pOutFile, nMode);
  }

  if (IntrinsicStmt != 0)
  {
    IntrinsicStmt->writeFortran(pOutFile, nMode);
  }

  if (ExternalStmt != 0)
  {
    ExternalStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSpecificationPartConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranExecutableConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranExecutableConstruct::AdtFortranExecutableConstruct(AdtParser* pActionStmtObj,
                                                             AdtParser* pCaseConstructObj,
                                                             AdtParser* pDoConstructObj,
                                                             AdtParser* pIfConstructObj,
                                                             AdtParser* pWhereConstructObj)
 : AdtFortranBase()
{
  initObject(ActionStmt,      pActionStmtObj,     AdtFortranActionStmt,     true);
  initObject(CaseConstruct,   pCaseConstructObj,  AdtFortranCaseConstruct,  true);
  initObject(DoConstruct,     pDoConstructObj,    AdtFortranDoConstruct,    true);
  initObject(IfConstruct,     pIfConstructObj,    AdtFortranIfConstruct,    true);
  initObject(WhereConstruct,  pWhereConstructObj, AdtFortranWhereConstruct, true);
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableConstruct::AdtFortranExecutableConstruct(const AdtFortranExecutableConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ActionStmt,      rCopy,  AdtFortranActionStmt);
  copyObject(CaseConstruct,   rCopy,  AdtFortranCaseConstruct);
  copyObject(DoConstruct,     rCopy,  AdtFortranDoConstruct);
  copyObject(IfConstruct,     rCopy,  AdtFortranIfConstruct);
  copyObject(WhereConstruct,  rCopy,  AdtFortranWhereConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranExecutableConstruct::~AdtFortranExecutableConstruct()
{
  UtlReleaseReference(ActionStmt);
  UtlReleaseReference(CaseConstruct);
  UtlReleaseReference(DoConstruct);
  UtlReleaseReference(IfConstruct);
  UtlReleaseReference(WhereConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ActionStmt != 0)
  {
    ActionStmt->writeCPP(pOutFile, nMode);
  }

  if (CaseConstruct != 0)
  {
    CaseConstruct->writeCPP(pOutFile, nMode);
  }

  if (DoConstruct != 0)
  {
    DoConstruct->writeCPP(pOutFile, nMode);
  }

  if (IfConstruct != 0)
  {
    IfConstruct->writeCPP(pOutFile, nMode);
  }

  if (WhereConstruct != 0)
  {
    WhereConstruct->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ActionStmt != 0)
  {
    ActionStmt->writeDelphi(pOutFile, nMode);
  }

  if (CaseConstruct != 0)
  {
    CaseConstruct->writeDelphi(pOutFile, nMode);
  }

  if (DoConstruct != 0)
  {
    DoConstruct->writeDelphi(pOutFile, nMode);
  }

  if (IfConstruct != 0)
  {
    IfConstruct->writeDelphi(pOutFile, nMode);
  }

  if (WhereConstruct != 0)
  {
    WhereConstruct->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExecutableConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ActionStmt != 0)
  {
    ActionStmt->writeFortran(pOutFile, nMode);
  }

  if (CaseConstruct != 0)
  {
    CaseConstruct->writeFortran(pOutFile, nMode);
  }

  if (DoConstruct != 0)
  {
    DoConstruct->writeFortran(pOutFile, nMode);
  }

  if (IfConstruct != 0)
  {
    IfConstruct->writeFortran(pOutFile, nMode);
  }

  if (WhereConstruct != 0)
  {
    WhereConstruct->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranExecutableConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranActionStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranActionStmt::AdtFortranActionStmt(AdtParser* pArithmeticIfStmtObj,
                                           AdtParser* pAssignmentStmtObj,
                                           AdtParser* pCallStmtObj,
                                           AdtParser* pContinueStmtObj,
                                           AdtParser* pCycleStmtObj,
                                           AdtParser* pExitStmtObj,
                                           AdtParser* pIfStmtObj,
                                           AdtParser* pReturnStmtObj,
                                           AdtParser* pWhereStmtObj,
                                           AdtParser* pGotoStmtObj)
 : AdtFortranBase()
{
  initObject(ArithmeticIfStmt,  pArithmeticIfStmtObj, AdtFortranArithmeticIfStmt, true);
  initObject(AssignmentStmt,    pAssignmentStmtObj,   AdtFortranAssignmentStmt,   true);
  initObject(CallStmt,          pCallStmtObj,         AdtFortranCallStmt,         true);
  initObject(ContinueStmt,      pContinueStmtObj,     AdtFortranContinueStmt,     true);
  initObject(CycleStmt,         pCycleStmtObj,        AdtFortranCycleStmt,        true);
  initObject(ExitStmt,          pExitStmtObj,         AdtFortranExitStmt,         true);
  initObject(IfStmt,            pIfStmtObj,           AdtFortranIfStmt,           true);
  initObject(ReturnStmt,        pReturnStmtObj,       AdtFortranReturnStmt,       true);
  initObject(WhereStmt,         pWhereStmtObj,        AdtFortranWhereStmt,        true);
  initObject(GotoStmt,          pGotoStmtObj,         AdtFortranGotoStmt,         true);
}

//  ----------------------------------------------------------------------------

AdtFortranActionStmt::AdtFortranActionStmt(const AdtFortranActionStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ArithmeticIfStmt,  rCopy,  AdtFortranArithmeticIfStmt);
  copyObject(AssignmentStmt,    rCopy,  AdtFortranAssignmentStmt);
  copyObject(CallStmt,          rCopy,  AdtFortranCallStmt);
  copyObject(ContinueStmt,      rCopy,  AdtFortranContinueStmt);
  copyObject(CycleStmt,         rCopy,  AdtFortranCycleStmt);
  copyObject(ExitStmt,          rCopy,  AdtFortranExitStmt);
  copyObject(IfStmt,            rCopy,  AdtFortranIfStmt);
  copyObject(ReturnStmt,        rCopy,  AdtFortranReturnStmt);
  copyObject(WhereStmt,         rCopy,  AdtFortranWhereStmt);
  copyObject(GotoStmt,          rCopy,  AdtFortranGotoStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranActionStmt::~AdtFortranActionStmt()
{
  UtlReleaseReference(ArithmeticIfStmt);
  UtlReleaseReference(AssignmentStmt);
  UtlReleaseReference(CallStmt);
  UtlReleaseReference(ContinueStmt);
  UtlReleaseReference(CycleStmt);
  UtlReleaseReference(ExitStmt);
  UtlReleaseReference(IfStmt);
  UtlReleaseReference(ReturnStmt);
  UtlReleaseReference(WhereStmt);
  UtlReleaseReference(GotoStmt);
}

//  ----------------------------------------------------------------------------

void AdtFortranActionStmt::makeCallStmt(AdtFortranCallStmt* pCallStmt)
{
  UtlReleaseReference(ArithmeticIfStmt);
  UtlReleaseReference(AssignmentStmt);
  UtlReleaseReference(CallStmt);
  UtlReleaseReference(ContinueStmt);
  UtlReleaseReference(CycleStmt);
  UtlReleaseReference(ExitStmt);
  UtlReleaseReference(IfStmt);
  UtlReleaseReference(ReturnStmt);
  UtlReleaseReference(WhereStmt);
  UtlReleaseReference(GotoStmt);

  ArithmeticIfStmt  = 0;
  AssignmentStmt    = 0;
  CallStmt          = 0;
  ContinueStmt      = 0;
  CycleStmt         = 0;
  ExitStmt          = 0;
  IfStmt            = 0;
  ReturnStmt        = 0;
  WhereStmt         = 0;
  GotoStmt          = 0;

  initObject(CallStmt, pCallStmt, AdtFortranCallStmt, true);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranActionStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ArithmeticIfStmt != 0)
  {
    ArithmeticIfStmt->writeCPP(pOutFile, nMode);
  }

  if (AssignmentStmt != 0)
  {
    AssignmentStmt->writeCPP(pOutFile, nMode);
  }

  if (CallStmt != 0)
  {
    CallStmt->writeCPP(pOutFile, nMode);
  }

  if (ContinueStmt != 0)
  {
    ContinueStmt->writeCPP(pOutFile, nMode);
  }

  if (CycleStmt != 0)
  {
    CycleStmt->writeCPP(pOutFile, nMode);
  }

  if (ExitStmt != 0)
  {
    ExitStmt->writeCPP(pOutFile, nMode);
  }

  if (IfStmt != 0)
  {
    IfStmt->writeCPP(pOutFile, nMode);
  }

  if (ReturnStmt != 0)
  {
    ReturnStmt->writeCPP(pOutFile, nMode);
  }

  if (WhereStmt != 0)
  {
    WhereStmt->writeCPP(pOutFile, nMode);
  }

  if (GotoStmt != 0)
  {
    GotoStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranActionStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ArithmeticIfStmt != 0)
  {
    ArithmeticIfStmt->writeDelphi(pOutFile, nMode);
  }

  if (AssignmentStmt != 0)
  {
    AssignmentStmt->writeDelphi(pOutFile, nMode);
  }

  if (CallStmt != 0)
  {
    CallStmt->writeDelphi(pOutFile, nMode);
  }

  if (ContinueStmt != 0)
  {
    ContinueStmt->writeDelphi(pOutFile, nMode);
  }

  if (CycleStmt != 0)
  {
    CycleStmt->writeDelphi(pOutFile, nMode);
  }

  if (ExitStmt != 0)
  {
    ExitStmt->writeDelphi(pOutFile, nMode);
  }

  if (IfStmt != 0)
  {
    IfStmt->writeDelphi(pOutFile, nMode);
  }

  if (ReturnStmt != 0)
  {
    ReturnStmt->writeDelphi(pOutFile, nMode);
  }

  if (WhereStmt != 0)
  {
    WhereStmt->writeDelphi(pOutFile, nMode);
  }

  if (GotoStmt != 0)
  {
    GotoStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranActionStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ArithmeticIfStmt != 0)
  {
    ArithmeticIfStmt->writeFortran(pOutFile, nMode);
  }

  if (AssignmentStmt != 0)
  {
    AssignmentStmt->writeFortran(pOutFile, nMode);
  }

  if (CallStmt != 0)
  {
    CallStmt->writeFortran(pOutFile, nMode);
  }

  if (ContinueStmt != 0)
  {
    ContinueStmt->writeFortran(pOutFile, nMode);
  }

  if (CycleStmt != 0)
  {
    CycleStmt->writeFortran(pOutFile, nMode);
  }

  if (ExitStmt != 0)
  {
    ExitStmt->writeFortran(pOutFile, nMode);
  }

  if (IfStmt != 0)
  {
    IfStmt->writeFortran(pOutFile, nMode);
  }

  if (ReturnStmt != 0)
  {
    ReturnStmt->writeFortran(pOutFile, nMode);
  }

  if (WhereStmt != 0)
  {
    WhereStmt->writeFortran(pOutFile, nMode);
  }

  if (GotoStmt != 0)
  {
    GotoStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranActionStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranRelOp method implementations
//  ----------------------------------------------------------------------------
AdtFortranRelOp::AdtFortranRelOp(AdtFortranOp nOp)
 : AdtFortranBase()
{
  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtFortranRelOp::AdtFortranRelOp(const AdtFortranRelOp& rCopy)
 : AdtFortranBase(rCopy)
{
  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtFortranRelOp::~AdtFortranRelOp()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRelOp::writeCPP(AdtFile& pOutFile, int nMode) const
{
  switch (Op)
  {
    case ForOp_LOGICAL_EQ:
    {
      write(pOutFile, "==");
      break;
    }

    case ForOp_LOGICAL_NE:
    {
      write(pOutFile, "!=");
      break;
    }

    case ForOp_LOGICAL_LT:
    {
      write(pOutFile, "<");
      break;
    }

    case ForOp_LOGICAL_LE:
    {
      write(pOutFile, "<=");
      break;
    }

    case ForOp_LOGICAL_GT:
    {
      write(pOutFile, ">");
      break;
    }

    case ForOp_LOGICAL_GE:
    {
      write(pOutFile, ">=");
      break;
    }

    case ForOp_EQUAL:
    {
      write(pOutFile, "==");
      break;
    }

    case ForOp_NEQUAL:
    {
      write(pOutFile, "!=");
      break;
    }

    case ForOp_LT:
    {
      write(pOutFile, "<");
      break;
    }

    case ForOp_LE:
    {
      write(pOutFile, "<=");
      break;
    }

    case ForOp_GT:
    {
      write(pOutFile, ">");
      break;
    }

    case ForOp_GE:
    {
      write(pOutFile, ">=");
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRelOp::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  switch (Op)
  {
    case ForOp_LOGICAL_EQ:
    {
      write(pOutFile, "=");
      break;
    }

    case ForOp_LOGICAL_NE:
    {
      write(pOutFile, "<>");
      break;
    }

    case ForOp_LOGICAL_LT:
    {
      write(pOutFile, "<");
      break;
    }

    case ForOp_LOGICAL_LE:
    {
      write(pOutFile, "<=");
      break;
    }

    case ForOp_LOGICAL_GT:
    {
      write(pOutFile, ">");
      break;
    }

    case ForOp_LOGICAL_GE:
    {
      write(pOutFile, ">=");
      break;
    }

    case ForOp_EQUAL:
    {
      write(pOutFile, "=");
      break;
    }

    case ForOp_NEQUAL:
    {
      write(pOutFile, "<>");
      break;
    }

    case ForOp_LT:
    {
      write(pOutFile, "<");
      break;
    }

    case ForOp_LE:
    {
      write(pOutFile, "<=");
      break;
    }

    case ForOp_GT:
    {
      write(pOutFile, ">");
      break;
    }

    case ForOp_GE:
    {
      write(pOutFile, ">=");
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRelOp::writeFortran(AdtFile& pOutFile, int nMode) const
{
  switch (Op)
  {
    case ForOp_LOGICAL_EQ:
    {
      write(pOutFile, ".EQ.");
      break;
    }

    case ForOp_LOGICAL_NE:
    {
      write(pOutFile, ".NE.");
      break;
    }

    case ForOp_LOGICAL_LT:
    {
      write(pOutFile, ".LT.");
      break;
    }

    case ForOp_LOGICAL_LE:
    {
      write(pOutFile, ".LE.");
      break;
    }

    case ForOp_LOGICAL_GT:
    {
      write(pOutFile, ".GT.");
      break;
    }

    case ForOp_LOGICAL_GE:
    {
      write(pOutFile, ".GE.");
      break;
    }

    case ForOp_EQUAL:
    {
      write(pOutFile, "==");
      break;
    }

    case ForOp_NEQUAL:
    {
      write(pOutFile, "\\=");
      break;
    }

    case ForOp_LT:
    {
      write(pOutFile, "<");
      break;
    }

    case ForOp_LE:
    {
      write(pOutFile, "<=");
      break;
    }

    case ForOp_GT:
    {
      write(pOutFile, ">");
      break;
    }

    case ForOp_GE:
    {
      write(pOutFile, ">=");
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranRelOp, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranTypeDeclarationStmt method implementations
//  ----------------------------------------------------------------------------
void AdtFortranTypeDeclarationStmt::initIntent()
{
  if (AttrSpecSeq != 0)
  {
    const AdtParser* pObj = AttrSpecSeq->findObject("AdtFortranIntentSpec");

    if (pObj != 0)
    {
      const AdtFortranIntentSpec* pIntentSpec = (const AdtFortranIntentSpec*)pObj;

      switch(pIntentSpec->intent())
      {
        case ForIntent_IN:
        {
          IsConst   = true;
          IsOutOnly = false;
          break;
        }

        case ForIntent_OUT:
        {
          IsConst   = false;
          IsOutOnly = true;
          break;
        }

        case ForIntent_INOUT:
        case ForIntent_IN_OUT:
        default:
        {
          IsConst   = false;
          IsOutOnly = false;
          break;
        }
      }

      HasIntent = true;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmt::AdtFortranTypeDeclarationStmt(AdtParser* pLblDefObj,
                                                             AdtParser* pTypeSpecObj,
                                                             AdtParser* pAttrSpecSeqObj,
                                                             AdtParser* pEntityDeclListObj)
 : AdtFortranBase()
{
  initObject(LblDef,          pLblDefObj,         AdtFortranLblDef,         true);
  initObject(TypeSpec,        pTypeSpecObj,       AdtFortranTypeSpec,       true);
  initObject(AttrSpecSeq,     pAttrSpecSeqObj,    AdtFortranAttrSpecSeq,    true);
  initObject(EntityDeclList,  pEntityDeclListObj, AdtFortranEntityDeclList, true);

  Dimensions  = 0;
  IsConst     = false;
  IsOutOnly   = false;
  HasIntent   = false;

  initIntent();

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmt::AdtFortranTypeDeclarationStmt(const AdtFortranTypeDeclarationStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,          rCopy,  AdtFortranLblDef);
  copyObject(TypeSpec,        rCopy,  AdtFortranTypeSpec);
  copyObject(AttrSpecSeq,     rCopy,  AdtFortranAttrSpecSeq);
  copyObject(EntityDeclList,  rCopy,  AdtFortranEntityDeclList);

  Dimensions  = rCopy.Dimensions;
  IsConst     = rCopy.IsConst;
  IsOutOnly   = rCopy.IsOutOnly;
  HasIntent   = rCopy.HasIntent;

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranTypeDeclarationStmt::~AdtFortranTypeDeclarationStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(TypeSpec);
  UtlReleaseReference(AttrSpecSeq);
  UtlReleaseReference(EntityDeclList);
}

//  ----------------------------------------------------------------------------

void AdtFortranTypeDeclarationStmt::removeExternals(const AdtParserPtrByStringMap& rExternalsMap)
{
  if (EntityDeclList != 0)
  {
    EntityDeclList->removeExternals(rExternalsMap);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranTypeDeclarationStmt::removeSharedNames(AdtParser* pDestModuleBody,
                                                      AdtStringList* pNewAttributeList,
                                                      AdtStringByStringMap* pNewAttributeMap)
{
  bool bNonEmptyList = false;

  if ((pDestModuleBody != 0) && (EntityDeclList != 0))
  {
    AdtParserPtrList          NameList;
    AdtParserPtrListIter      Iter;

    EntityDeclList->findObjects(NameList, "AdtFortranName", 0, false, "AdtFortranEntityDecl");

    for (Iter = NameList.begin() ; Iter != NameList.end() ; ++Iter)
    {
      AdtParser* pName = (*Iter);

      if (pName != 0)
      {
        AdtParser* pTypeDeclName = pDestModuleBody->findObject("AdtFortranName", pName->name(), false, "AdtFortranEntityDecl");

        if ((pTypeDeclName              != 0) &&
            (pName->parent()            != 0) &&
            (pName->parent()->parent()  != 0) &&
             pTypeDeclName->findAscendantWithClassLineage("AdtFortranEntityDecl,"
                                                          "AdtFortranEntityDeclList,"
                                                          "AdtFortranTypeDeclarationStmt,"
                                                          "AdtFortranSpecificationPartConstruct,"
                                                          "AdtFortranModuleBodyContent") != 0)
        {
          pName->parent()->parent()->remove(pName->parent());
        }
        else if ((pNewAttributeList                     != 0) &&
                 (pNewAttributeMap                      != 0) &&
                 (pNewAttributeMap->find(pName->name()) == pNewAttributeMap->end()))
        {
          (*pNewAttributeMap)[pName->name()] = pName->name();
          pNewAttributeList->push_back(pName->name());
        }
      }
    }

    bNonEmptyList = (EntityDeclList->listSize() > 0);
  }

  return (bNonEmptyList);
}

//  ----------------------------------------------------------------------------

void AdtFortranTypeDeclarationStmt::splitAndEnumerate(AdtParser* pParentObj, AdtParserPtrByStringMap& rMap) const
{
  // The purpose of this method is to split multi-variable type declarations
  // (ie. ones with a comma seperated list of variables) into one to one type /
  // variable name declarations. Doing so makes conversion from Fortran to other
  // languages much easier.
  if (EntityDeclList != 0)
  {
    const AdtFortranShapeSpecList*  pGlobalShapeSpecList  = 0;
    AdtFortranAttrSpecSeq*          pNewAttrSpecSeq       = new AdtFortranAttrSpecSeq(0);

    if ((AttrSpecSeq != 0) && (pNewAttrSpecSeq != 0))
    {
      // Extract the dimension from the attribute list if any.
      const AdtParserPtrList&   AttrList = AttrSpecSeq->objList();
      AdtParserPtrListConstIter AttrIter;

      for (AttrIter = AttrList.begin() ; AttrIter != AttrList.end() ; ++AttrIter)
      {
        const AdtFortranAttrSpec* pAttrSpec = (const AdtFortranAttrSpec*)(const AdtParser*)*AttrIter;

        if (pAttrSpec != 0)
        {
          pGlobalShapeSpecList = (const AdtFortranShapeSpecList*)pAttrSpec->findDescendant("ShapeSpecList");

          if (pGlobalShapeSpecList != 0)
          {
            break;
          }
          else
          {
            // Only add attributes not describing dimension
            pNewAttrSpecSeq->add(ObjAndRelease(Hnd(pAttrSpec->copy())));
          }
        }
      }
    }

    if (pNewAttrSpecSeq == 0)
    {
      pNewAttrSpecSeq = AttrSpecSeq;

      if (pNewAttrSpecSeq != 0)
      {
        pNewAttrSpecSeq->lock();
      }
    }

    AdtParserPtrListConstIter  Iter;

    for (Iter = EntityDeclList->objList().begin() ; Iter != EntityDeclList->objList().end() ; ++Iter)
    {
      AdtFortranEntityDecl* pEntityDeclObj = (AdtFortranEntityDecl*)((AdtParser*)*Iter);

      if (pEntityDeclObj != 0)
      {
        const AdtParser* pNameObj              = pEntityDeclObj->findDescendant("Name");
        const AdtParser* pExprObj              = pEntityDeclObj->findDescendant("Expr");
        const AdtParser* pCharLengthObj        = pEntityDeclObj->findDescendant("CharLength");
        const AdtParser* pShapeSpecListObj     = pEntityDeclObj->findDescendant("ShapeSpecList");
        const AdtParser* pInvalidEntityDeclObj = pEntityDeclObj->findDescendant("InvalidEntityDecl");

        if (pShapeSpecListObj == 0)
        {
          pShapeSpecListObj = pGlobalShapeSpecList;
        }

        AdtFortranEntityDecl* pNewEntityDecl = new AdtFortranEntityDecl(ObjAndRelease(Hnd(pNameObj != 0 ? pNameObj->copy() : 0)),
                                                                        ObjAndRelease(Hnd(pExprObj != 0 ? pExprObj->copy() : 0)),
                                                                        ObjAndRelease(Hnd(pCharLengthObj != 0 ? pCharLengthObj->copy() : 0)),
                                                                        ObjAndRelease(Hnd(pShapeSpecListObj != 0 ? pShapeSpecListObj->copy() : 0)),
                                                                        ObjAndRelease(Hnd(pInvalidEntityDeclObj != 0 ? pInvalidEntityDeclObj->copy() : 0)));

        size_t                    nDimensions         = pNewEntityDecl->numberOfDimensions();
        AdtFortranEntityDeclList* pNewEntityDeclList  = new AdtFortranEntityDeclList(pNewEntityDecl);

        UtlReleaseReference(pNewEntityDecl);

        if (pNewEntityDeclList != 0)
        {
          AdtFortranTypeDeclarationStmt* pNewTypeDeclStmt = new AdtFortranTypeDeclarationStmt(ObjAndRelease(Hnd(LblDef != 0 ? LblDef->copy() : 0)),
                                                                                              ObjAndRelease(Hnd(TypeSpec != 0 ? TypeSpec->copy() : 0)),
                                                                                              ObjAndRelease(Hnd(pNewAttrSpecSeq != 0 ? pNewAttrSpecSeq->copy() : 0)),
                                                                                              ObjAndRelease(Hnd(pNewEntityDeclList != 0 ? pNewEntityDeclList->copy() : 0)));

          if (pNewTypeDeclStmt != 0)
          {
            pNewTypeDeclStmt->Dimensions = nDimensions;

            if (pParentObj != 0)
            {
              pNewTypeDeclStmt->parent(pParentObj);
            }

            rMap.insert(AdtParserPtrByStringMap::value_type(pEntityDeclObj->name(), pNewTypeDeclStmt));
          }

          UtlReleaseReference(pNewEntityDeclList);
        }
      }
    }

    UtlReleaseReference(pNewAttrSpecSeq);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if ((EntityDeclList != 0) && (EntityDeclList->listSize() == 0) || ((TypeSpec != 0) && TypeSpec->isUnknown()))
  {
    //Do nothing
  }
  else
  {
    switch (nMode)
    {
      case 1:
      {
        //locals declaration
        if ((EntityDeclList != 0) && (TypeSpec != 0))
        {
          AdtParserPtrListConstIter  Iter;

          for (Iter = EntityDeclList->objList().begin() ; Iter != EntityDeclList->objList().end() ; ++Iter)
          {
            AdtFortranEntityDecl* pEntityDeclObj = (AdtFortranEntityDecl*)((AdtParser*)*Iter);

            if (pEntityDeclObj != 0)
            {
              if (Dimensions > 0)
              {
                const char* pType = 0;

                AdtCppBase::mapTypesToCpp(TypeSpec->name(), Dimensions, pType);
                pOutFile.write(pType);
              }
              else
              {
                TypeSpec->writeCPP(pOutFile, nMode);
              }

              pOutFile.write(" ");

              pEntityDeclObj->writeCPP(pOutFile, nMode);
            }
          }
        }
        break;
      }

      case 3:
      {
        //param list declaration
        if ((EntityDeclList != 0) && (TypeSpec != 0))
        {
          AdtParserPtrListConstIter   Iter;
          bool                        bWriteComma = false;

          for (Iter = EntityDeclList->objList().begin() ; Iter != EntityDeclList->objList().end() ; ++Iter)
          {
            AdtFortranEntityDecl* pEntityDeclObj = (AdtFortranEntityDecl*)((AdtParser*)*Iter);

            if (pEntityDeclObj != 0)
            {
              if (bWriteComma)
              {
                pOutFile.write(", ");
              }

              if (Dimensions > 0)
              {
                const char* pType = 0;

                if (IsConst)
                {
                  pOutFile.write("const ");
                }

                AdtCppBase::mapTypesToCpp(TypeSpec->name(), Dimensions, pType);
                pOutFile.write(pType);
              }
              else
              {
                TypeSpec->writeCPP(pOutFile, nMode);

                if (!IsConst)
                {
                  pOutFile.write("&");
                }
              }

              pOutFile.write(" ");

              pEntityDeclObj->writeCPP(pOutFile, nMode);

              bWriteComma = true;
            }
          }
        }
        break;
      }

      case 4:
      {
        //Var declaration
        if (TypeSpec != 0)
        {
          if (Dimensions > 0)
          {
            const char* pType = 0;

            AdtCppBase::mapTypesToCpp(TypeSpec->name(), Dimensions, pType);
            pOutFile.write(pType);
          }
          else
          {
            TypeSpec->writeCPP(pOutFile, nMode);
          }

          pOutFile.write(" ");
        }
        break;
      }

      case 2:
      {
        //variable initialisation
        if (EntityDeclList != 0)
        {
          EntityDeclList->writeCPP(pOutFile, nMode);
        }
        break;
      }

      case 0:
      default:
      {
        break;
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if ((EntityDeclList != 0) && (EntityDeclList->listSize() == 0) || ((TypeSpec != 0) && TypeSpec->isUnknown()))
  {
    //Do nothing
  }
  else
  {
    switch (nMode)
    {
      case 3:
      {
        if (IsConst)
        {
          pOutFile.write("const ");
        }
        else if (IsOutOnly)
        {
          pOutFile.write("outo ");
        }
        else
        {
          pOutFile.write("var ");
        }
        //Fall through
      }

      case 1:
      {
        if (TypeSpec != 0)
        {
          if (EntityDeclList != 0)
          {
            EntityDeclList->writeDelphi(pOutFile, nMode);
          }
        }
        //Fall through
      }
      case 4:
      {
        //Var declaration
        if (TypeSpec != 0)
        {
          pOutFile.write(" : ");

          if (Dimensions > 0)
          {
            const char* pType = 0;

            AdtDelphiBase::mapTypesToDelphi(TypeSpec->name(), Dimensions, pType);
            pOutFile.write(pType);
          }
          else
          {
            TypeSpec->writeDelphi(pOutFile, nMode);
          }
        }
        break;
      }

      case 2:
      {
        //variable initialisation
        if (EntityDeclList != 0)
        {
          EntityDeclList->writeDelphi(pOutFile, nMode);
        }
        break;
      }

      case 0:
      default:
      {
        break;
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeDeclarationStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if ((EntityDeclList != 0) && (EntityDeclList->listSize() == 0) || ((TypeSpec != 0) && TypeSpec->isUnknown()))
  {
    //Do nothing
  }
  else
  {
    if (LblDef != 0)
    {
      LblDef->writeFortran(pOutFile, nMode);
    }

    if (TypeSpec != 0)
    {
      TypeSpec->writeFortran(pOutFile, nMode);
    }

    if (AttrSpecSeq != 0)
    {
      write(pOutFile, ", ");
      AttrSpecSeq->writeFortran(pOutFile, nMode);
    }

    write(pOutFile, ":: ");

    if (EntityDeclList != 0)
    {
      EntityDeclList->writeFortran(pOutFile, nMode);
    }

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranTypeDeclarationStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranAttrSpecSeq method implementations
//  ----------------------------------------------------------------------------
AdtFortranAttrSpecSeq::AdtFortranAttrSpecSeq(AdtParser* pAttrSpecObj)
 : AdtFortranBase()
{
  add(pAttrSpecObj);
}

//  ----------------------------------------------------------------------------

AdtFortranAttrSpecSeq::AdtFortranAttrSpecSeq(const AdtFortranAttrSpecSeq& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranAttrSpecSeq::~AdtFortranAttrSpecSeq()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpecSeq::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpecSeq::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpecSeq::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranAttrSpecSeq, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranTypeSpec method implementations
//  ----------------------------------------------------------------------------
void AdtFortranTypeSpec::initialise()
{
  const char* pTypeName = "";

  switch (Type)
  {
    case ForType_INTEGER:
    {
      pTypeName = "INTEGER(4)";
      break;
    }

    case ForType_REAL:
    {
      pTypeName = "REAL(8)";
      break;
    }

    case ForType_DOUBLE_PRECISION:
    {
      pTypeName = "REAL(8)";
      break;
    }

    case ForType_LOGICAL:
    {
      pTypeName = "BOOLEAN";
      break;
    }

    case ForType_UNSIGNED:
    {
      pTypeName = "UNSIGNED";
      break;
    }

    case ForType_BOUNDSCHECK:
    {
      pTypeName = "CHECK_CONTEXT";
      break;
    }

    default:
    {
      break;
    }
  }

  name(pTypeName);
}

//  ----------------------------------------------------------------------------

AdtFortranTypeSpec::AdtFortranTypeSpec(AdtFortranType nType, const char* pIcon)
 : AdtFortranBase()
{
  Type        = nType;
  ByteLength  = (pIcon != 0) ? ::atoi(pIcon) : 0;

  initialise();
}

//  ----------------------------------------------------------------------------

AdtFortranTypeSpec::AdtFortranTypeSpec(const AdtFortranTypeSpec& rCopy)
 : AdtFortranBase(rCopy)
{
  Type        = rCopy.Type;
  ByteLength  = rCopy.ByteLength;
}

//  ----------------------------------------------------------------------------

AdtFortranTypeSpec::~AdtFortranTypeSpec()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeSpec::writeCPP(AdtFile& pOutFile, int nMode) const
{
  switch (Type)
  {
    case ForType_INTEGER:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "int ";
          break;
        }

        case 1:
        {
          pTypeName = "char ";
          break;
        }

        case 2:
        {
          pTypeName = "short ";
          break;
        }

        case 4:
        {
          pTypeName = "int ";
          break;
        }

        case 8:
        {
          pTypeName = "long long ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_REAL:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "double ";
          break;
        }

        case 4:
        {
          pTypeName = "float ";
          break;
        }

        case 8:
        {
          pTypeName = "double ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_DOUBLE_PRECISION:
    {
      write(pOutFile, "double ");
      break;
    }

    case ForType_COMPLEX:
    {
      break;
    }

    case ForType_DOUBLE_COMPLEX:
    {
      break;
    }

    case ForType_LOGICAL:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "bool ";
          break;
        }

        case 4:
        {
          pTypeName = "longbool ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_CHARACTER:
    {
      write(pOutFile, "char ");
      break;
    }

    case ForType_UNSIGNED:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "unsigned ";
          break;
        }

        case 1:
        {
          pTypeName = "unsigned char ";
          break;
        }

        case 2:
        {
          pTypeName = "unsigned short ";
          break;
        }

        case 4:
        {
          pTypeName = "unsigned int ";
          break;
        }

        case 8:
        {
          pTypeName = "unsigned long long ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_BOUNDSCHECK:
    {
      write(pOutFile, "CHECK_CONTEXT ");
      break;
    }

    case ForType_UNKNOWNTYPE:
    {
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeSpec::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  switch (Type)
  {
    case ForType_INTEGER:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "integer ";
          break;
        }

        case 1:
        {
          pTypeName = "byte ";
          break;
        }

        case 2:
        {
          pTypeName = "word ";
          break;
        }

        case 4:
        {
          pTypeName = "longint ";
          break;
        }

        case 8:
        {
          pTypeName = "int64 ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_REAL:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "double ";
          break;
        }

        case 4:
        {
          pTypeName = "single ";
          break;
        }

        case 8:
        {
          pTypeName = "double ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_DOUBLE_PRECISION:
    {
      write(pOutFile, "double ");
      break;
    }

    case ForType_COMPLEX:
    {
      break;
    }

    case ForType_DOUBLE_COMPLEX:
    {
      break;
    }

    case ForType_LOGICAL:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "boolean ";
          break;
        }

        case 4:
        {
          pTypeName = "longbool ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_CHARACTER:
    {
      write(pOutFile, "char ");
      break;
    }

    case ForType_BOUNDSCHECK:
    {
      write(pOutFile, "CHECK_CONTEXT ");
      break;
    }

    case ForType_UNKNOWNTYPE:
    {
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranTypeSpec::writeFortran(AdtFile& pOutFile, int nMode) const
{
  switch (Type)
  {
    case ForType_INTEGER:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "INTEGER(4) ";
          break;
        }

        case 1:
        {
          pTypeName = "INTEGER(1) ";
          break;
        }

        case 2:
        {
          pTypeName = "INTEGER(2) ";
          break;
        }

        case 4:
        {
          pTypeName = "INTEGER(4) ";
          break;
        }

        case 8:
        {
          pTypeName = "INTEGER(8) ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_REAL:
    {
      write(pOutFile, "REAL(8) ");
      break;
    }

    case ForType_DOUBLE_PRECISION:
    {
      write(pOutFile, "REAL(8) ");
      break;
    }

    case ForType_COMPLEX:
    {
      write(pOutFile, "COMPLEX ");
      break;
    }

    case ForType_DOUBLE_COMPLEX:
    {
      write(pOutFile, "DOUBLE COMPLEX ");
      break;
    }

    case ForType_LOGICAL:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "LOGICAL ";
          break;
        }

        case 4:
        {
          pTypeName = "LOGICAL(4) ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_CHARACTER:
    {
      write(pOutFile, "CHARACTER ");
      break;
    }

    case ForType_UNSIGNED:
    {
      const char* pTypeName = 0;

      switch (ByteLength)
      {
        case 0:
        default:
        {
          pTypeName = "UNSIGNED(4) ";
          break;
        }

        case 1:
        {
          pTypeName = "UNSIGNED(1) ";
          break;
        }

        case 2:
        {
          pTypeName = "UNSIGNED(2) ";
          break;
        }

        case 4:
        {
          pTypeName = "UNSIGNED(4) ";
          break;
        }

        case 8:
        {
          pTypeName = "UNSIGNED(8) ";
          break;
        }
      }

      write(pOutFile, pTypeName);
      break;
    }

    case ForType_BOUNDSCHECK:
    {
      write(pOutFile, "CHECK_CONTEXT ");
      break;
    }

    case ForType_UNKNOWNTYPE:
    {
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranTypeSpec, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranAttrSpec method implementations
//  ----------------------------------------------------------------------------
AdtFortranAttrSpec::AdtFortranAttrSpec(AdtParser* pShapeSpecListObj,
                                       AdtParser* pIntentSpecObj,
                                       AdtFortranAttr nAttribute)
 : AdtFortranBase()
{
  initObject(ShapeSpecList, pShapeSpecListObj,  AdtFortranShapeSpecList,  true);
  initObject(IntentSpec,    pIntentSpecObj,     AdtFortranIntentSpec,     true);

  Attribute = nAttribute;
}

//  ----------------------------------------------------------------------------

AdtFortranAttrSpec::AdtFortranAttrSpec(const AdtFortranAttrSpec& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ShapeSpecList, rCopy,  AdtFortranShapeSpecList);
  copyObject(IntentSpec,    rCopy,  AdtFortranIntentSpec);

  Attribute = rCopy.Attribute;
}

//  ----------------------------------------------------------------------------

AdtFortranAttrSpec::~AdtFortranAttrSpec()
{
  UtlReleaseReference(ShapeSpecList);
  UtlReleaseReference(IntentSpec);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpec::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpec::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAttrSpec::writeFortran(AdtFile& pOutFile, int nMode) const
{
  switch (Attribute)
  {
    case ForAttr_PARAMETER:
    {
      write(pOutFile, "PARAMETER ");
      break;
    }

    case ForAttr_PUBLIC:
    {
      write(pOutFile, "PUBLIC ");
      break;
    }

    case ForAttr_PROTECTED:
    {
      write(pOutFile, "PROTECTED ");
      break;
    }

    case ForAttr_PRIVATE:
    {
      write(pOutFile, "PRIVATE ");
      break;
    }

    case ForAttr_INTRINSIC:
    {
      write(pOutFile, "INTRINSIC ");
      break;
    }

    case ForAttr_EXTERNAL:
    {
      write(pOutFile, "EXTERNAL ");
      break;
    }

    case ForAttr_DIMENSION:
    {
      write(pOutFile, "DIMENSION (");

      if (ShapeSpecList != 0)
      {
        ShapeSpecList->writeFortran(pOutFile, nMode);
      }

      write(pOutFile, ")");
      break;
    }

    case ForAttr_INTENT:
    {
      write(pOutFile, "INTENT ");

      if (IntentSpec != 0)
      {
        IntentSpec->writeFortran(pOutFile, nMode);
      }
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranAttrSpec, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEntityDeclList method implementations
//  ----------------------------------------------------------------------------
AdtFortranEntityDeclList::AdtFortranEntityDeclList(AdtParser* pEntityDeclObj)
 : AdtFortranBase()
{
  add(pEntityDeclObj);
}

//  ----------------------------------------------------------------------------

AdtFortranEntityDeclList::AdtFortranEntityDeclList(const AdtFortranEntityDeclList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranEntityDeclList::~AdtFortranEntityDeclList()
{

}

//  ----------------------------------------------------------------------------

void AdtFortranEntityDeclList::removeExternals(const AdtParserPtrByStringMap& rExternalsMap)
{
  removeMatching(rExternalsMap);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDeclList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  switch (nMode)
  {
    case 5:
    case 4:
    case 3:
    case 1:
    {
      forAllWriteCPP(pOutFile, nMode, ",", false, true);
      break;
    }

    case 2:
    {
      forAllWriteCPP(pOutFile, nMode, "", false, false);
      break;
    }

    case 0:
    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  switch (nMode)
  {
    case 5:
    case 4:
    case 3:
    case 1:
    {
      forAllWriteDelphi(pOutFile, nMode, ",", false, true);
      break;
    }

    case 2:
    {
      forAllWriteDelphi(pOutFile, nMode, "", false, false);
      break;
    }

    case 0:
    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDeclList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEntityDeclList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEntityDecl method implementations
//  ----------------------------------------------------------------------------
AdtFortranEntityDecl::AdtFortranEntityDecl(AdtParser* pNameObj,
                                           AdtParser* pExprObj,
                                           AdtParser* pCharLengthObj,
                                           AdtParser* pShapeSpecListObj,
                                           AdtParser* pInvalidEntityDeclObj)
 : AdtFortranBase()
{
  initObject(Name,              pNameObj,               AdtFortranName,               true);
  initObject(Expr,              pExprObj,               AdtFortranExpr,               true);
  initObject(CharLength,        pCharLengthObj,         AdtFortranCharLength,         true);
  initObject(ShapeSpecList,     pShapeSpecListObj,      AdtFortranShapeSpecList,      true);
  initObject(InvalidEntityDecl, pInvalidEntityDeclObj,  AdtFortranInvalidEntityDecl,  true);

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranEntityDecl::AdtFortranEntityDecl(const AdtFortranEntityDecl& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,              rCopy,  AdtFortranName);
  copyObject(Expr,              rCopy,  AdtFortranExpr);
  copyObject(CharLength,        rCopy,  AdtFortranCharLength);
  copyObject(ShapeSpecList,     rCopy,  AdtFortranShapeSpecList);
  copyObject(InvalidEntityDecl, rCopy,  AdtFortranInvalidEntityDecl);
}

//  ----------------------------------------------------------------------------

AdtFortranEntityDecl::~AdtFortranEntityDecl()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
  UtlReleaseReference(CharLength);
  UtlReleaseReference(ShapeSpecList);
  UtlReleaseReference(InvalidEntityDecl);
}

//  ----------------------------------------------------------------------------

size_t AdtFortranEntityDecl::numberOfDimensions() const
{
  return (ShapeSpecList != 0 ? ShapeSpecList->listSize() : 0);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDecl::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if ((nMode == 4) || (nMode == 5))
  {
    if (ShapeSpecList != 0)
    {
      //Write array sizes / initial indices.
      ShapeSpecList->writeCPP(pOutFile, nMode);
    }
  }
  else
  {
    if ((Name != 0) && ((nMode == 1) || (nMode == 3)))
    {
      Name->writeCPP(pOutFile, nMode);
    }

    if (ShapeSpecList != 0)
    {
      //Write array sizes as inline comments.
      write(pOutFile, "/* ");
      ShapeSpecList->writeCPP(pOutFile, nMode);
      write(pOutFile, " */");
    }

    if (CharLength != 0)
    {
      //Don't write. Won't be supporting strings any time soon.
    }

    if ((Name != 0) && (Expr != 0) && (nMode == 2))
    {
      Name->writeCPP(pOutFile, nMode);
      write(pOutFile, " = ");
      Expr->writeCPP(pOutFile, nMode);
      write(pOutFile, ";");
      pOutFile.newline();
    }

    if (InvalidEntityDecl != 0)
    {
      //Not supported
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if ((nMode == 4) || (nMode == 5))
  {
    if (ShapeSpecList != 0)
    {
      //Write array sizes / initial indices.
      ShapeSpecList->writeDelphi(pOutFile, nMode);
    }
  }
  else
  {
    if ((Name != 0) && ((nMode == 1) || (nMode == 3)))
    {
      Name->writeDelphi(pOutFile, nMode);
    }

    if (ShapeSpecList != 0)
    {
      //Write array sizes as inline comments.
      write(pOutFile, "{");
      ShapeSpecList->writeDelphi(pOutFile, nMode);
      write(pOutFile, "}");
    }

    if (CharLength != 0)
    {
      //Don't write. Won't be supporting strings any time soon.
    }

    if ((Name != 0) && (Expr != 0) && (nMode == 2))
    {
      Name->writeDelphi(pOutFile, nMode);
      write(pOutFile, " := ");
      Expr->writeDelphi(pOutFile, nMode);
      write(pOutFile, ";");
      pOutFile.newline();
    }

    if (InvalidEntityDecl != 0)
    {
      //Not supported
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEntityDecl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  if (ShapeSpecList != 0)
  {
    write(pOutFile, "(");
    ShapeSpecList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (CharLength != 0)
  {
    write(pOutFile, "*");
    CharLength->writeFortran(pOutFile, nMode);
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");
    Expr->writeFortran(pOutFile, nMode);
  }

  if (InvalidEntityDecl != 0)
  {
    InvalidEntityDecl->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEntityDecl, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranInvalidEntityDecl method implementations
//  ----------------------------------------------------------------------------
AdtFortranInvalidEntityDecl::AdtFortranInvalidEntityDecl(AdtParser* pNameObj,
                                                         AdtParser* pExprObj,
                                                         AdtParser* pCharLengthObj,
                                                         AdtParser* pShapeSpecListObj)
 : AdtFortranBase()
{
  initObject(Name,              pNameObj,               AdtFortranName,               true);
  initObject(Expr,              pExprObj,               AdtFortranExpr,               true);
  initObject(CharLength,        pCharLengthObj,         AdtFortranCharLength,         true);
  initObject(ShapeSpecList,     pShapeSpecListObj,      AdtFortranShapeSpecList,      true);

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranInvalidEntityDecl::AdtFortranInvalidEntityDecl(const AdtFortranInvalidEntityDecl& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,              rCopy,  AdtFortranName);
  copyObject(Expr,              rCopy,  AdtFortranExpr);
  copyObject(CharLength,        rCopy,  AdtFortranCharLength);
  copyObject(ShapeSpecList,     rCopy,  AdtFortranShapeSpecList);
}

//  ----------------------------------------------------------------------------

AdtFortranInvalidEntityDecl::~AdtFortranInvalidEntityDecl()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
  UtlReleaseReference(CharLength);
  UtlReleaseReference(ShapeSpecList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranInvalidEntityDecl::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranInvalidEntityDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranInvalidEntityDecl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  if (CharLength != 0)
  {
    write(pOutFile, "*");
    CharLength->writeFortran(pOutFile, nMode);
  }

  if (ShapeSpecList != 0)
  {
    write(pOutFile, "(");
    ShapeSpecList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");
    Expr->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranInvalidEntityDecl, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCharLength method implementations
//  ----------------------------------------------------------------------------
AdtFortranCharLength::AdtFortranCharLength(AdtParser* pExprObj,
                                           AdtParser* pIconObj)
 : AdtFortranBase()
{
  initObject(Expr,  pExprObj, AdtFortranExpr, true);
  initObject(Icon,  pIconObj, AdtFortranIcon, true);
}

//  ----------------------------------------------------------------------------

AdtFortranCharLength::AdtFortranCharLength(const AdtFortranCharLength& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Expr,  rCopy,  AdtFortranExpr);
  copyObject(Icon,  rCopy,  AdtFortranIcon);
}

//  ----------------------------------------------------------------------------

AdtFortranCharLength::~AdtFortranCharLength()
{
  UtlReleaseReference(Expr);
  UtlReleaseReference(Icon);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCharLength::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCharLength::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCharLength::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Icon != 0)
  {
    Icon->writeFortran(pOutFile, nMode);
  }
  else
  {
    write(pOutFile, "(");

    if (Expr != 0)
    {
      Expr->writeFortran(pOutFile, nMode);
    }
    else
    {
      write(pOutFile, "*");
    }

    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCharLength, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranShapeSpecList method implementations
//  ----------------------------------------------------------------------------
AdtFortranShapeSpecList::AdtFortranShapeSpecList(AdtParser* pShapeSpecObj)
 : AdtFortranBase()
{
  add(pShapeSpecObj);
}

//  ----------------------------------------------------------------------------

AdtFortranShapeSpecList::AdtFortranShapeSpecList(const AdtFortranShapeSpecList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranShapeSpecList::~AdtFortranShapeSpecList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpecList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true, 0, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpecList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpecList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranShapeSpecList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranShapeSpec method implementations
//  ----------------------------------------------------------------------------
AdtFortranShapeSpec::AdtFortranShapeSpec(AdtParser* pExprObj,
                                         AdtParser* pExpr2Obj)
 : AdtFortranBase()
{
  initObject(Expr,  pExprObj,   AdtFortranExpr, true);
  initObject(Expr2, pExpr2Obj,  AdtFortranExpr, true);
}

//  ----------------------------------------------------------------------------

AdtFortranShapeSpec::AdtFortranShapeSpec(const AdtFortranShapeSpec& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Expr,  rCopy,  AdtFortranExpr);
  copyObject(Expr2, rCopy,  AdtFortranExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranShapeSpec::~AdtFortranShapeSpec()
{
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpec::writeCPP(AdtFile& pOutFile, int nMode) const
{
  switch (nMode)
  {
    case 4:
    {
      if (Expr != 0)
      {
        if (Expr2 != 0)
        {
          Expr2->writeCPP(pOutFile);
          write(pOutFile, "+1-");
          Expr->writeCPP(pOutFile);
        }
        else
        {
          Expr->writeCPP(pOutFile);
        }
      }
      break;
    }

    case 5:
    {
      if (Expr != 0)
      {
        if (Expr2 != 0)
        {
          Expr->writeCPP(pOutFile);
        }
        else
        {
          write(pOutFile, "1");
        }
      }
      break;
    }

    default:
    {
      if (Expr != 0)
      {
        Expr->writeCPP(pOutFile);

        if (Expr2 != 0)
        {
          write(pOutFile, ":");
          Expr2->writeCPP(pOutFile);
        }
      }
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpec::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  switch (nMode)
  {
    case 4:
    {
      if (Expr != 0)
      {
        if (Expr2 != 0)
        {
          Expr2->writeDelphi(pOutFile);
          write(pOutFile, "+1-");
          Expr->writeDelphi(pOutFile);
        }
        else
        {
          Expr->writeDelphi(pOutFile);
        }
      }
      break;
    }

    case 5:
    {
      if (Expr != 0)
      {
        if (Expr2 != 0)
        {
          Expr->writeDelphi(pOutFile);
        }
        else
        {
          write(pOutFile, "1");
        }
      }
      break;
    }

    default:
    {
      if (Expr != 0)
      {
        Expr->writeDelphi(pOutFile);

        if (Expr2 != 0)
        {
          write(pOutFile, ":");
          Expr2->writeDelphi(pOutFile);
        }
      }
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranShapeSpec::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);

    if (Expr2 != 0)
    {
      write(pOutFile, ":");
      Expr2->writeFortran(pOutFile, nMode);
    }
  }
  else
  {
    write(pOutFile, ":");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranShapeSpec, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranDimensionStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranDimensionStmt::AdtFortranDimensionStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pArrayDeclaratorListObj)
 : AdtFortranBase()
{
  initObject(LblDef,              pLblDefObj,               AdtFortranLblDef,               true);
  initObject(ArrayDeclaratorList, pArrayDeclaratorListObj,  AdtFortranArrayDeclaratorList,  true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranDimensionStmt::AdtFortranDimensionStmt(const AdtFortranDimensionStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,              rCopy,  AdtFortranLblDef);
  copyObject(ArrayDeclaratorList, rCopy,  AdtFortranArrayDeclaratorList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranDimensionStmt::~AdtFortranDimensionStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(ArrayDeclaratorList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDimensionStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (nMode == 1)
  {
    pOutFile.newline();
    ::printf("ERROR: DIMENSION statement not supported on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDimensionStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (nMode == 1)
  {
    pOutFile.newline();
    ::printf("ERROR: DIMENSION statement not supported on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDimensionStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "DIMENSION ");

  if (ArrayDeclaratorList != 0)
  {
    ArrayDeclaratorList->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranDimensionStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranArrayDeclaratorList method implementations
//  ----------------------------------------------------------------------------
AdtFortranArrayDeclaratorList::AdtFortranArrayDeclaratorList(AdtParser* pArrayDeclaratorObj)
 : AdtFortranBase()
{
  add(pArrayDeclaratorObj);
}

//  ----------------------------------------------------------------------------

AdtFortranArrayDeclaratorList::AdtFortranArrayDeclaratorList(const AdtFortranArrayDeclaratorList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranArrayDeclaratorList::~AdtFortranArrayDeclaratorList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclaratorList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclaratorList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclaratorList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranArrayDeclaratorList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranArrayDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtFortranArrayDeclarator::AdtFortranArrayDeclarator(AdtParser* pNameObj,
                                                     AdtParser* pShapeSpecListObj)
 : AdtFortranBase()
{
  initObject(Name,          pNameObj,           AdtFortranName,           true);
  initObject(ShapeSpecList, pShapeSpecListObj,  AdtFortranShapeSpecList,  true);

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranArrayDeclarator::AdtFortranArrayDeclarator(const AdtFortranArrayDeclarator& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,          rCopy,  AdtFortranName);
  copyObject(ShapeSpecList, rCopy,  AdtFortranShapeSpecList);
}

//  ----------------------------------------------------------------------------

AdtFortranArrayDeclarator::~AdtFortranArrayDeclarator()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(ShapeSpecList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclarator::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclarator::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArrayDeclarator::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  if (ShapeSpecList != 0)
  {
    write(pOutFile, "(");

    ShapeSpecList->writeFortran(pOutFile, nMode);

    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranArrayDeclarator, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranParameterStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranParameterStmt::AdtFortranParameterStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pNamedConstantDefListObj)
 : AdtFortranBase()
{
  initObject(LblDef,                pLblDefObj,               AdtFortranLblDef,               true);
  initObject(NamedConstantDefList,  pNamedConstantDefListObj, AdtFortranNamedConstantDefList, true);
}

//  ----------------------------------------------------------------------------

AdtFortranParameterStmt::AdtFortranParameterStmt(const AdtFortranParameterStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,                rCopy,  AdtFortranLblDef);
  copyObject(NamedConstantDefList,  rCopy,  AdtFortranNamedConstantDefList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranParameterStmt::~AdtFortranParameterStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(NamedConstantDefList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranParameterStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (nMode == 1)
  {
    if (NamedConstantDefList != 0)
    {
      NamedConstantDefList->writeCPP(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranParameterStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (nMode == 1)
  {
    if (NamedConstantDefList != 0)
    {
      NamedConstantDefList->writeDelphi(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranParameterStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (NamedConstantDefList != 0)
  {
    write(pOutFile, "PARAMETER (");

    NamedConstantDefList->writeFortran(pOutFile, nMode);

    write(pOutFile, ")");
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranParameterStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranNamedConstantDefList method implementations
//  ----------------------------------------------------------------------------
AdtFortranNamedConstantDefList::AdtFortranNamedConstantDefList(AdtParser* pNamedConstantDefObj)
 : AdtFortranBase()
{
  add(pNamedConstantDefObj);
}

//  ----------------------------------------------------------------------------

AdtFortranNamedConstantDefList::AdtFortranNamedConstantDefList(const AdtFortranNamedConstantDefList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranNamedConstantDefList::~AdtFortranNamedConstantDefList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDefList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ";", true, false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDefList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true, false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDefList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranNamedConstantDefList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranNamedConstantDef method implementations
//  ----------------------------------------------------------------------------
AdtFortranNamedConstantDef::AdtFortranNamedConstantDef(AdtParser* pNameObj,
                                                       AdtParser* pExprObj)
 : AdtFortranBase()
{
  initObject(Name,  pNameObj, AdtFortranName, true);
  initObject(Expr,  pExprObj, AdtFortranExpr, true);

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranNamedConstantDef::AdtFortranNamedConstantDef(const AdtFortranNamedConstantDef& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,  rCopy,  AdtFortranName);
  copyObject(Expr,  rCopy,  AdtFortranExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranNamedConstantDef::~AdtFortranNamedConstantDef()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDef::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: untyped CONSTANTs not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDef::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");

    Expr->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNamedConstantDef::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");

    Expr->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranNamedConstantDef, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitSpecList method implementations
//  ----------------------------------------------------------------------------
AdtFortranImplicitSpecList::AdtFortranImplicitSpecList(AdtParser* pImplicitSpecObj)
 : AdtFortranBase()
{
  add(pImplicitSpecObj);
}

//  ----------------------------------------------------------------------------

AdtFortranImplicitSpecList::AdtFortranImplicitSpecList(const AdtFortranImplicitSpecList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranImplicitSpecList::~AdtFortranImplicitSpecList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpecList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpecList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpecList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranImplicitSpecList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitSpec method implementations
//  ----------------------------------------------------------------------------
AdtFortranImplicitSpec::AdtFortranImplicitSpec(AdtParser* pTypeSpecObj,
                                               AdtParser* pImplObj)
 : AdtFortranBase()
{
  initObject(TypeSpec,  pTypeSpecObj, AdtFortranTypeSpec, true);
  initObject(Impl,      pImplObj,     AdtFortranImpl,     true);
}

//  ----------------------------------------------------------------------------

AdtFortranImplicitSpec::AdtFortranImplicitSpec(const AdtFortranImplicitSpec& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(TypeSpec,  rCopy, AdtFortranTypeSpec);
  copyObject(Impl,      rCopy, AdtFortranImpl);
}

//  ----------------------------------------------------------------------------

AdtFortranImplicitSpec::~AdtFortranImplicitSpec()
{
  UtlReleaseReference(TypeSpec);
  UtlReleaseReference(Impl);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpec::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpec::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitSpec::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (TypeSpec != 0)
  {
    TypeSpec->writeFortran(pOutFile, nMode);
  }

  if (Impl != 0)
  {
    Impl->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranImplicitSpec, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSectionSubscriptList method implementations
//  ----------------------------------------------------------------------------
AdtFortranSectionSubscriptList::AdtFortranSectionSubscriptList(AdtParser* pSectionSubscriptObj)
 : AdtFortranBase()
{
  add(pSectionSubscriptObj);
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscriptList::AdtFortranSectionSubscriptList(const AdtFortranSectionSubscriptList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscriptList::~AdtFortranSectionSubscriptList()
{

}

//  ----------------------------------------------------------------------------

bool AdtFortranSectionSubscriptList::hasSlice(int& nTriplets) const
{
  bool                      bHasSlice = false;
  AdtParserPtrListConstIter Iter;

  nTriplets = 0;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    const AdtFortranSectionSubscript* pObj = (const AdtFortranSectionSubscript*)(const AdtParser*)*Iter;

    if ((pObj != 0) && pObj->hasSlice())
    {
      nTriplets++;
      bHasSlice = true;
    }
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscriptList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscriptList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscriptList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSectionSubscriptList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSectionSubscript method implementations
//  ----------------------------------------------------------------------------
AdtFortranSectionSubscript::AdtFortranSectionSubscript(AdtParser* pExprObj,
                                                       AdtParser* pSubscriptTripletObj)
 : AdtFortranBase()
{
  initObject(Expr,              pExprObj,             AdtFortranExpr,             true);
  initObject(SubscriptTriplet,  pSubscriptTripletObj, AdtFortranSubscriptTriplet, true);

  SubscriptList       = 0;
  DoDelphiSliceExpand = false;
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscript::AdtFortranSectionSubscript(AdtParser* pSubscriptListObj)
{
  //This special constructor is not part of the FORTRAN language support but a
  //special way to support conversion of call lists to a specific form required
  //in Delphi. More specifically, to support Mark Bravingtons desire method of
  //specifying the index parameters in slice operations with constructs like
  //
  //  ArrayInit(A,[b,c],value)
  //
  //and,
  //
  //  ArrayCopy(A1, [a, b], A2, [c, c, d, e])
  initObject(SubscriptList,  pSubscriptListObj, AdtFortranSectionSubscriptList, true);

  Expr                = 0;
  SubscriptTriplet    = 0;
  DoDelphiSliceExpand = false;
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscript::AdtFortranSectionSubscript(const AdtFortranSectionSubscript& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Expr,              rCopy,  AdtFortranExpr);
  copyObject(SubscriptTriplet,  rCopy,  AdtFortranSubscriptTriplet);
  copyObject(SubscriptList,     rCopy,  AdtFortranSectionSubscriptList);

  DoDelphiSliceExpand = rCopy.DoDelphiSliceExpand;
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscript::~AdtFortranSectionSubscript()
{
  UtlReleaseReference(Expr);
  UtlReleaseReference(SubscriptTriplet);
  UtlReleaseReference(SubscriptList);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSectionSubscript::isSimple() const
{
  bool bIsSimple = ((Expr != 0) && Expr->isSimple() && (SubscriptTriplet == 0) && (SubscriptList == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSectionSubscript::hasSlice() const
{
  bool bHasSlice = (SubscriptTriplet != 0);

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscript* AdtFortranSectionSubscript::firstSubscript(int& nIndex) const
{
  AdtFortranSectionSubscript* pNewSectionSubscript = 0;

  nIndex = 0;

  if (Expr != 0)
  {
    AdtParser*  pExprObjCopy;

    pExprObjCopy          = Expr->copy();
    pNewSectionSubscript  = new AdtFortranSectionSubscript(pExprObjCopy, 0);

    UtlReleaseReference(pExprObjCopy);
  }
  else if (SubscriptTriplet != 0)
  {
    AdtParser*  pExprObj  = SubscriptTriplet->findDescendant("Expr");

    if (pExprObj != 0)
    {
      AdtParser*  pExprObjCopy;

      pExprObjCopy          = pExprObj->copy();
      pNewSectionSubscript  = new AdtFortranSectionSubscript(pExprObjCopy, 0);

      UtlReleaseReference(pExprObjCopy);
    }
  }

  return (pNewSectionSubscript);
}

//  ----------------------------------------------------------------------------

AdtFortranSectionSubscript* AdtFortranSectionSubscript::nextSubscript(int& nIndex) const
{
  AdtFortranSectionSubscript* pNewSectionSubscript = 0;

  nIndex++;

  if ((Expr == 0) && (SubscriptTriplet != 0) && (nIndex == 1))
  {
    AdtParser*  pExprObj  = SubscriptTriplet->findDescendant("Expr2");

    if (pExprObj != 0)
    {
      AdtParser*  pExprObjCopy;

      pExprObjCopy          = pExprObj->copy();
      pNewSectionSubscript  = new AdtFortranSectionSubscript(pExprObjCopy, 0);

      UtlReleaseReference(pExprObjCopy);
    }
  }

  return (pNewSectionSubscript);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscript::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (SubscriptList != 0)
  {
    write(pOutFile, "[");
    SubscriptList->writeDelphi(pOutFile, nMode);
    write(pOutFile, "]");
  }

  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);

    if (DoDelphiSliceExpand)
    {
      write(pOutFile, ",");
      Expr->writeCPP(pOutFile, nMode);
    }
  }

  if (SubscriptTriplet != 0)
  {
    SubscriptTriplet->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscript::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (SubscriptList != 0)
  {
    write(pOutFile, "[");
    SubscriptList->writeDelphi(pOutFile, nMode);
    write(pOutFile, "]");
  }

  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);

    if (DoDelphiSliceExpand)
    {
      write(pOutFile, ",");
      Expr->writeDelphi(pOutFile, nMode);
    }
  }

  if (SubscriptTriplet != 0)
  {
    SubscriptTriplet->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSectionSubscript::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ASSERT(SubscriptList == 0);

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);

    if (DoDelphiSliceExpand)
    {
      write(pOutFile, ",");
      Expr->writeDelphi(pOutFile);
    }
  }

  if (SubscriptTriplet != 0)
  {
    SubscriptTriplet->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSectionSubscript, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSubscriptTriplet class
//  ----------------------------------------------------------------------------
AdtFortranSubscriptTriplet::AdtFortranSubscriptTriplet(int nCase,
                                                       AdtParser* pExprObj,
                                                       AdtParser* pExpr2Obj,
                                                       AdtParser* pExpr3Obj)
 : AdtFortranBase()
{
  Case = nCase;

  initObject(Expr,  pExprObj,   AdtFortranExpr, true);
  initObject(Expr2, pExpr2Obj,  AdtFortranExpr, true);
  initObject(Expr3, pExpr3Obj,  AdtFortranExpr, true);

  DoDelphiSliceExpand = false;
}

//  ----------------------------------------------------------------------------

AdtFortranSubscriptTriplet::AdtFortranSubscriptTriplet(const AdtFortranSubscriptTriplet& rCopy)
 : AdtFortranBase(rCopy)
{
  Case = rCopy.Case;

  copyObject(Expr,  rCopy,  AdtFortranExpr);
  copyObject(Expr2, rCopy,  AdtFortranExpr);
  copyObject(Expr3, rCopy,  AdtFortranExpr);

  DoDelphiSliceExpand = rCopy.DoDelphiSliceExpand;
}

//  ----------------------------------------------------------------------------

AdtFortranSubscriptTriplet::~AdtFortranSubscriptTriplet()
{
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
  UtlReleaseReference(Expr3);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSubscriptTriplet::lowerIndex(string& sLowerIndex) const
{
  bool            bSet  = false;
  AdtFortranExpr* pExpr = 0;

  switch (Case)
  {
    case 2:
    case 3:
    case 4:
    case 5:
    {
      pExpr = Expr;
      break;
    }

    case 0:
    case 1:
    case 6:
    case 7:
    default:
    {
      break;
    }
  }

  if (pExpr != 0)
  {
    AdtFile StringFile;

    sLowerIndex = "";

    if (StringFile.open(sLowerIndex))
    {
      pExpr->writeFortran(StringFile);
      bSet = true;
    }
  }

  return (bSet);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSubscriptTriplet::upperIndex(string& sUpperIndex) const
{
  bool            bSet  = false;
  AdtFortranExpr* pExpr = 0;

  switch (Case)
  {
    case 1:
    {
      break;
    }

    case 3:
    {
      // xExpr COLON xExpr
      pExpr = Expr2;
      break;
    }

    case 4:
    {
      // xExpr COLON xExpr COLON xExpr
      pExpr = Expr2;
      break;
    }

    case 6:
    {
      // COLON xExpr COLON xExpr
      pExpr = Expr;
      break;
    }

    case 0:
    case 2:
    case 5:
    case 7:
    default:
    {
      break;
    }
  }

  if (pExpr != 0)
  {
    AdtFile StringFile;

    sUpperIndex = "";

    if (StringFile.open(sUpperIndex))
    {
      pExpr->writeFortran(StringFile);
      bSet = true;
    }
  }

  return (bSet);
}

//  ----------------------------------------------------------------------------

bool AdtFortranSubscriptTriplet::stride(string& sStride) const
{
  bool            bSet  = false;
  AdtFortranExpr* pExpr = 0;


  switch (Case)
  {
    case 4:
    {
      // xExpr COLON xExpr COLON xExpr
      pExpr = Expr3;
      break;
    }

    case 5:
    {
      // xExpr COLON COLON xExpr
      pExpr = Expr2;
      break;
    }

    case 6:
    {
      // COLON xExpr COLON xExpr
      pExpr = Expr2;
      break;
    }

    case 7:
    {
      // COLON COLON xExpr
      pExpr = Expr;
      break;
    }

    case 0:
    case 1:
    case 2:
    case 3:
    default:
    {
      break;
    }
  }

  if (pExpr != 0)
  {
    AdtFile StringFile;

    sStride = "";

    if (StringFile.open(sStride))
    {
      pExpr->writeFortran(StringFile);
      bSet = true;
    }
  }

  return (bSet);
}

//  ----------------------------------------------------------------------------

void AdtFortranSubscriptTriplet::substituteExpr(AdtFortranExpr* pExprObj)
{
  if (pExprObj != 0)
  {
    UtlReleaseReference(Expr);

    Expr = 0;

    initObject(Expr,  pExprObj, AdtFortranExpr, true);
    pExprObj->depth(depth() + 1, true);

    switch (Case)
    {
      case 0:
      {
        // COLON
        Case = 2;
        break;
      }

      case 1:
      {
        // COLON xExpr
        Case = 3;
        break;
      }

      default:
      {
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtFortranSubscriptTriplet::substituteExpr2(AdtFortranExpr* pExpr2Obj)
{
  if (pExpr2Obj != 0)
  {
    UtlReleaseReference(Expr2);

    Expr2 = 0;

    initObject(Expr2,  pExpr2Obj, AdtFortranExpr, true);
    pExpr2Obj->depth(depth() + 1, true);

    switch (Case)
    {
      case 0:
      {
        // COLON
        Case = 1;
        break;
      }

      case 2:
      {
        // xExpr COLON
        Case = 3;
        break;
      }

      default:
      {
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubscriptTriplet::writeCPP(AdtFile& pOutFile, int nMode) const
{
  switch (Case)
  {
    case 0:
    {
      // COLON
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      break;
    }

    case 1:
    {
      // COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 2:
    {
      // xExpr COLON
      if (Expr != 0)
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      }
      break;
    }

    case 3:
    {
      // xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 4:
    {
      // xExpr COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0) && (Expr3 != 0))
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr3->writeFortran(pOutFile);
      }
      break;
    }

    case 5:
    {
      // xExpr COLON COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
      }
      break;
    }

    case 6:
    {
      // COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
      }
      break;
    }

    case 7:
    {
      // COLON COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile);
      }
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}


//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubscriptTriplet::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  switch (Case)
  {
    case 0:
    {
      // COLON
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      break;
    }

    case 1:
    {
      // COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile);
      }
      break;
    }

    case 2:
    {
      // xExpr COLON
      if (Expr != 0)
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      }
      break;
    }

    case 3:
    {
      // xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
      }
      break;
    }

    case 4:
    {
      // xExpr COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0) && (Expr3 != 0))
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr3->writeFortran(pOutFile);
      }
      break;
    }

    case 5:
    {
      // xExpr COLON COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
      }
      break;
    }

    case 6:
    {
      // COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile);
      }
      break;
    }

    case 7:
    {
      // COLON COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile);
      }
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubscriptTriplet::writeFortran(AdtFile& pOutFile, int nMode) const
{
  switch (Case)
  {
    case 0:
    {
      // COLON
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      break;
    }

    case 1:
    {
      // COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 2:
    {
      // xExpr COLON
      if (Expr != 0)
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
      }
      break;
    }

    case 3:
    {
      // xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 4:
    {
      // xExpr COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0) && (Expr3 != 0))
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr3->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 5:
    {
      // xExpr COLON COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 6:
    {
      // COLON xExpr COLON xExpr
      if ((Expr != 0) && (Expr2 != 0))
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile, nMode);
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr2->writeFortran(pOutFile, nMode);
      }
      break;
    }

    case 7:
    {
      // COLON COLON xExpr
      if (Expr != 0)
      {
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        write(pOutFile, DoDelphiSliceExpand ? "," : ":");
        Expr->writeFortran(pOutFile, nMode);
      }
      break;
    }

    default:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSubscriptTriplet, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranPrimary method implementations
//  ----------------------------------------------------------------------------
AdtFortranPrimary::AdtFortranPrimary(AdtParser* pNameObj,
                                     AdtParser* pSconObj,
                                     AdtParser* pIconObj,
                                     AdtParser* pRconObj,
                                     AdtParser* pExprObj,
                                     AdtParser* pExpr2Obj,
                                     AdtParser* pSectionSubscriptListObj,
                                     bool bIsTrue,
                                     bool bIsBracket)
 : AdtFortranBase()
{
  initObject(Name,                  pNameObj,                 AdtFortranName,                 true);
  initObject(Scon,                  pSconObj,                 AdtFortranScon,                 true);
  initObject(Icon,                  pIconObj,                 AdtFortranIcon,                 true);
  initObject(Rcon,                  pRconObj,                 AdtFortranRcon,                 true);
  initObject(Expr,                  pExprObj,                 AdtFortranExpr,                 true);
  initObject(Expr2,                 pExpr2Obj,                AdtFortranExpr,                 true);
  initObject(SectionSubscriptList,  pSectionSubscriptListObj, AdtFortranSectionSubscriptList, true);

  IsTrue      = bIsTrue;
  IsBracket   = bIsBracket;
  IsVariable  = false;

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranPrimary::AdtFortranPrimary(const AdtFortranPrimary& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,                  rCopy,  AdtFortranName);
  copyObject(Scon,                  rCopy,  AdtFortranScon);
  copyObject(Icon,                  rCopy,  AdtFortranIcon);
  copyObject(Rcon,                  rCopy,  AdtFortranRcon);
  copyObject(Expr,                  rCopy,  AdtFortranExpr);
  copyObject(Expr2,                 rCopy,  AdtFortranExpr);
  copyObject(SectionSubscriptList,  rCopy,  AdtFortranSectionSubscriptList);

  IsTrue      = rCopy.IsTrue;
  IsBracket   = rCopy.IsBracket;
  IsVariable  = rCopy.IsVariable;

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranPrimary::~AdtFortranPrimary()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Scon);
  UtlReleaseReference(Icon);
  UtlReleaseReference(Rcon);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
  UtlReleaseReference(SectionSubscriptList);
}

//  ----------------------------------------------------------------------------

void AdtFortranPrimary::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                             const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  // Is this an array variable?
  if ((Name != 0) && rVarInfo.numberOfDimensions(Name->name()) > 0)
  {
    // Dereference any array indexing
    AdtFortranSectionSubscriptList* pSectionSubscriptList = rSliceLoopVars.createSectionSubscriptList(rVarInfo,
                                                                                                      Name->name(),
                                                                                                      SectionSubscriptList);

    if (SectionSubscriptList != 0)
    {
      SectionSubscriptList->replaceInParent(pSectionSubscriptList);
    }
    else
    {
      initObject(SectionSubscriptList, pSectionSubscriptList, AdtFortranSectionSubscriptList, true);
    }

    UtlReleaseReference(pSectionSubscriptList);
  }

  if (Expr != 0)
  {
    Expr->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (Expr2 != 0)
  {
    Expr2->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranPrimary::hasSlice() const
{
  bool bHasSlice = false;

  if (SectionSubscriptList != 0)
  {
    int nTriplets = 0;

    bHasSlice = SectionSubscriptList->hasSlice(nTriplets);
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

void AdtFortranPrimary::checkIsVariable(const AdtIntByStringMap& rMap)
{
  if ((Name != 0) && !IsVariable)
  {
    AdtIntByStringMapConstIter  Iter = rMap.find(Name->name());

    IsVariable  = (Iter != rMap.end());
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranPrimary::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if ((Name                 == 0) &&
      (Scon                 == 0) &&
      (Icon                 == 0) &&
      (Rcon                 == 0) &&
      (Expr                 == 0) &&
      (Expr2                == 0) &&
      (SectionSubscriptList == 0))
  {
    if (IsTrue)
    {
      write(pOutFile, "true");
    }
    else
    {
      write(pOutFile, "false");
    }
  }
  else
  {
    if (Scon != 0)
    {
      Scon->writeCPP(pOutFile, nMode);
    }

    if (Icon != 0)
    {
      Icon->writeCPP(pOutFile, nMode);
    }

    if (Rcon != 0)
    {
      Rcon->writeCPP(pOutFile, nMode);
    }

    if (Name != 0)
    {
      Name->writeCPP(pOutFile, nMode);
    }

    if (IsBracket && !IsVariable)
    {
      write(pOutFile, "(");
    }

    if (Expr != 0)
    {
      Expr->writeCPP(pOutFile, nMode);

      if (Expr2 != 0)
      {
        write(pOutFile, ",");

        Expr2->writeCPP(pOutFile, nMode);
      }
    }

    if (SectionSubscriptList != 0)
    {
      if (IsVariable)
      {
        AdtParserPtrListConstRIter  Iter;

        for (Iter = SectionSubscriptList->objList().rbegin() ; Iter != SectionSubscriptList->objList().rend() ; ++Iter)
        {
          AdtFortranBase* pFortranObj = (AdtFortranBase*)((AdtParser*)*Iter);

          if (pFortranObj != 0)
          {
            pOutFile.write("[");
            pFortranObj->writeCPP(pOutFile, nMode);
            pOutFile.write("]");
          }
        }
      }
      else
      {
        SectionSubscriptList->writeCPP(pOutFile, nMode);
      }
    }

    if (IsBracket && !IsVariable)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranPrimary::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if ((Name                 == 0) &&
      (Scon                 == 0) &&
      (Icon                 == 0) &&
      (Rcon                 == 0) &&
      (Expr                 == 0) &&
      (Expr2                == 0) &&
      (SectionSubscriptList == 0))
  {
    if (IsTrue)
    {
      write(pOutFile, "true");
    }
    else
    {
      write(pOutFile, "false");
    }
  }
  else
  {
    if (Scon != 0)
    {
      Scon->writeDelphi(pOutFile, nMode);
    }

    if (Icon != 0)
    {
      Icon->writeDelphi(pOutFile, nMode);
    }

    if (Rcon != 0)
    {
      Rcon->writeDelphi(pOutFile, nMode);
    }

    if (Name != 0)
    {
      Name->writeDelphi(pOutFile, nMode);
    }

    if (IsBracket && !IsVariable)
    {
      write(pOutFile, "(");
    }

    if (Expr != 0)
    {
      Expr->writeDelphi(pOutFile, nMode);

      if (Expr2 != 0)
      {
        write(pOutFile, ",");

        Expr2->writeDelphi(pOutFile, nMode);
      }
    }

    if (SectionSubscriptList != 0)
    {
      if (IsVariable)
      {
        AdtParserPtrListConstIter  Iter;

        for (Iter = SectionSubscriptList->objList().begin() ; Iter != SectionSubscriptList->objList().end() ; ++Iter)
        {
          AdtFortranBase* pFortranObj = (AdtFortranBase*)((AdtParser*)*Iter);

          if (pFortranObj != 0)
          {
            pOutFile.write("[");
            pFortranObj->writeDelphi(pOutFile, nMode);
            pOutFile.write("]");
          }
        }
      }
      else
      {
        SectionSubscriptList->writeDelphi(pOutFile, nMode);
      }
    }

    if (IsBracket && !IsVariable)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranPrimary::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if ((Name                 == 0) &&
      (Scon                 == 0) &&
      (Icon                 == 0) &&
      (Rcon                 == 0) &&
      (Expr                 == 0) &&
      (Expr2                == 0) &&
      (SectionSubscriptList == 0))
  {
    if (IsTrue)
    {
      write(pOutFile, ".TRUE.");
    }
    else
    {
      write(pOutFile, ".FALSE.");
    }
  }
  else
  {
    if (Scon != 0)
    {
      Scon->writeFortran(pOutFile, nMode);
    }

    if (Icon != 0)
    {
      Icon->writeFortran(pOutFile, nMode);
    }

    if (Rcon != 0)
    {
      Rcon->writeFortran(pOutFile, nMode);
    }

    if (Name != 0)
    {
      AdtFortranBase::writeWithChangedPrefix(pOutFile, Name->name(), false);
    }

    if (IsBracket)
    {
      write(pOutFile, "(");
    }

    if (Expr != 0)
    {
      Expr->writeFortran(pOutFile, nMode);

      if (Expr2 != 0)
      {
        write(pOutFile, ",");

        Expr2->writeFortran(pOutFile, nMode);
      }
    }

    if (SectionSubscriptList != 0)
    {
      SectionSubscriptList->writeFortran(pOutFile, nMode);
    }

    if (IsBracket)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranPrimary, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranMultOperand method implementations
//  ----------------------------------------------------------------------------
AdtFortranMultOperand::AdtFortranMultOperand(AdtParser* pPrimaryObj,
                                             AdtParser* pMultOperandObj)
 : AdtFortranBase()
{
  initObject(Primary,     pPrimaryObj,      AdtFortranPrimary,      true);
  initObject(MultOperand, pMultOperandObj,  AdtFortranMultOperand,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranMultOperand::AdtFortranMultOperand(const AdtFortranMultOperand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Primary,     rCopy, AdtFortranPrimary);
  copyObject(MultOperand, rCopy, AdtFortranMultOperand);
}

//  ----------------------------------------------------------------------------

AdtFortranMultOperand::~AdtFortranMultOperand()
{
  UtlReleaseReference(Primary);
  UtlReleaseReference(MultOperand);
}

//  ----------------------------------------------------------------------------

void AdtFortranMultOperand::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                 const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (Primary != 0)
  {
    Primary->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (MultOperand != 0)
  {
    MultOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranMultOperand::isSimple() const
{
  bool bIsSimple = ((Primary != 0) && (MultOperand == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranMultOperand::hasSlice() const
{
  bool bHasSlice = false;

  if (Primary != 0)
  {
    bHasSlice = Primary->hasSlice();
  }

  if (MultOperand != 0)
  {
    bHasSlice = bHasSlice || MultOperand->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranMultOperand::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranMultOperand"))
  {
    const AdtFortranMultOperand* pMultOperand = (const AdtFortranMultOperand*)pObj;

    bAllowableMatch = isSimple() && pMultOperand->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMultOperand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (MultOperand != 0)
  {
    write(pOutFile, "pow(");

    if (Primary != 0)
    {
      Primary->writeCPP(pOutFile, nMode);
    }

    write(pOutFile, ",");

    MultOperand->writeCPP(pOutFile, nMode);

    write(pOutFile, ")");
  }
  else if (Primary != 0)
  {
    Primary->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMultOperand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (MultOperand != 0)
  {
    write(pOutFile, "pwr(");

    if (Primary != 0)
    {
      Primary->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, ",");

    MultOperand->writeDelphi(pOutFile, nMode);

    write(pOutFile, ")");
  }
  else if (Primary != 0)
  {
    Primary->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMultOperand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Primary != 0)
  {
    Primary->writeFortran(pOutFile, nMode);
  }

  if (MultOperand != 0)
  {
    write(pOutFile, "**");
    MultOperand->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranMultOperand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranAddOperand method implementations
//  ----------------------------------------------------------------------------
AdtFortranAddOperand::AdtFortranAddOperand(AdtParser* pMultOperandObj,
                                           AdtParser* pAddOperandObj,
                                           bool bMultiply)
 : AdtFortranBase()
{
  initObject(MultOperand, pMultOperandObj,  AdtFortranMultOperand,  true);
  initObject(AddOperand,  pAddOperandObj,  AdtFortranAddOperand,    true);

  Multiply  = bMultiply;
}

//  ----------------------------------------------------------------------------

AdtFortranAddOperand::AdtFortranAddOperand(const AdtFortranAddOperand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(MultOperand, rCopy, AdtFortranMultOperand);
  copyObject(AddOperand,  rCopy, AdtFortranAddOperand);

  Multiply  = rCopy.Multiply;
}

//  ----------------------------------------------------------------------------

AdtFortranAddOperand::~AdtFortranAddOperand()
{
  UtlReleaseReference(MultOperand);
  UtlReleaseReference(AddOperand);
}

//  ----------------------------------------------------------------------------

void AdtFortranAddOperand::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (MultOperand != 0)
  {
    MultOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (AddOperand != 0)
  {
    AddOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranAddOperand::isSimple() const
{
  bool bIsSimple = false;

  if ((MultOperand != 0) && (AddOperand == 0))
  {
    bIsSimple = MultOperand->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAddOperand::hasSlice() const
{
  bool bHasSlice = false;

  if (MultOperand != 0)
  {
    bHasSlice = MultOperand->hasSlice();
  }

  if (AddOperand != 0)
  {
    bHasSlice = bHasSlice || AddOperand->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAddOperand::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranAddOperand"))
  {
    const AdtFortranAddOperand* pAddOperand = (const AdtFortranAddOperand*)pObj;

    bAllowableMatch = isSimple() && pAddOperand->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAddOperand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (MultOperand != 0)
  {
    if (AddOperand != 0)
    {
      AddOperand->writeCPP(pOutFile, nMode);

      write(pOutFile, Multiply ? " * " : " / ");
    }

    MultOperand->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAddOperand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (MultOperand != 0)
  {
    if (AddOperand != 0)
    {
      AddOperand->writeDelphi(pOutFile, nMode);

      write(pOutFile, Multiply ? " * " : " / ");
    }

    MultOperand->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAddOperand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (MultOperand != 0)
  {
    if (AddOperand != 0)
    {
      AddOperand->writeFortran(pOutFile, nMode);

      write(pOutFile, Multiply ? " * " : " / ");
    }

    MultOperand->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranAddOperand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranLevel2Expr method implementations
//  ----------------------------------------------------------------------------
AdtFortranLevel2Expr::AdtFortranLevel2Expr(AdtParser* pAddOperandObj,
                                           AdtParser* pLevel2ExprObj,
                                           bool bSign,
                                           bool bHasOp)
 : AdtFortranBase()
{
  initObject(AddOperand,  pAddOperandObj, AdtFortranAddOperand, true);
  initObject(Level2Expr,  pLevel2ExprObj, AdtFortranLevel2Expr, true);

  Sign  = bSign;
  HasOp = bHasOp;
}

//  ----------------------------------------------------------------------------

AdtFortranLevel2Expr::AdtFortranLevel2Expr(const AdtFortranLevel2Expr& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(AddOperand,  rCopy, AdtFortranAddOperand);
  copyObject(Level2Expr,  rCopy, AdtFortranLevel2Expr);

  Sign  = rCopy.Sign;
  HasOp = rCopy.HasOp;
}

//  ----------------------------------------------------------------------------

AdtFortranLevel2Expr::~AdtFortranLevel2Expr()
{
  UtlReleaseReference(AddOperand);
  UtlReleaseReference(Level2Expr);
}

//  ----------------------------------------------------------------------------

void AdtFortranLevel2Expr::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (AddOperand != 0)
  {
    AddOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (Level2Expr != 0)
  {
    Level2Expr->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel2Expr::isSimple() const
{
  bool bIsSimple = false;

  if ((AddOperand != 0) && (Level2Expr == 0))
  {
    bIsSimple = AddOperand->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel2Expr::hasSlice() const
{
  bool bHasSlice = false;

  if (AddOperand != 0)
  {
    bHasSlice = AddOperand->hasSlice();
  }

  if (Level2Expr != 0)
  {
    bHasSlice = bHasSlice || Level2Expr->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel2Expr::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranLevel2Expr"))
  {
    const AdtFortranLevel2Expr* pLevel2Expr = (const AdtFortranLevel2Expr*)pObj;

    bAllowableMatch = isSimple() && pLevel2Expr->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel2Expr::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (AddOperand != 0)
  {
    if (Level2Expr != 0)
    {
      Level2Expr->writeCPP(pOutFile, nMode);
      write(pOutFile, Sign ? " + " : " - ");
      AddOperand->writeCPP(pOutFile, nMode);
    }
    else
    {
      if (HasOp)
      {
        write(pOutFile, Sign ? "+" : "-");
      }

      AddOperand->writeCPP(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel2Expr::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (AddOperand != 0)
  {
    if (Level2Expr != 0)
    {
      Level2Expr->writeDelphi(pOutFile, nMode);
      write(pOutFile, Sign ? " + " : " - ");
      AddOperand->writeDelphi(pOutFile, nMode);
    }
    else
    {
      if (HasOp)
      {
        write(pOutFile, Sign ? "+" : "-");
      }

      AddOperand->writeDelphi(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel2Expr::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (AddOperand != 0)
  {
    if (Level2Expr != 0)
    {
      Level2Expr->writeFortran(pOutFile, nMode);
      write(pOutFile, Sign ? " + " : " - ");
      AddOperand->writeFortran(pOutFile, nMode);
    }
    else
    {
      if (HasOp)
      {
        write(pOutFile, Sign ? "+" : "-");
      }

      AddOperand->writeFortran(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranLevel2Expr, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranLevel4Expr method implementations
//  ----------------------------------------------------------------------------
AdtFortranLevel4Expr::AdtFortranLevel4Expr(AdtParser* pLevel2ExprObj,
                                           AdtParser* pRelOpObj,
                                           AdtParser* pLevel2Expr2Obj)
 : AdtFortranBase()
{
  initObject(Level2Expr,  pLevel2ExprObj,   AdtFortranLevel2Expr, true);
  initObject(RelOp,       pRelOpObj,        AdtFortranRelOp,      true);
  initObject(Level2Expr2, pLevel2Expr2Obj,  AdtFortranLevel2Expr, true);
}

//  ----------------------------------------------------------------------------

AdtFortranLevel4Expr::AdtFortranLevel4Expr(const AdtFortranLevel4Expr& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Level2Expr,  rCopy,  AdtFortranLevel2Expr);
  copyObject(RelOp,       rCopy,  AdtFortranRelOp);
  copyObject(Level2Expr2, rCopy,  AdtFortranLevel2Expr);
}

//  ----------------------------------------------------------------------------

AdtFortranLevel4Expr::~AdtFortranLevel4Expr()
{
  UtlReleaseReference(Level2Expr);
  UtlReleaseReference(RelOp);
  UtlReleaseReference(Level2Expr2);
}

//  ----------------------------------------------------------------------------

void AdtFortranLevel4Expr::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (Level2Expr != 0)
  {
    Level2Expr->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (Level2Expr2 != 0)
  {
    Level2Expr2->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel4Expr::isSimple() const
{
  bool bIsSimple = false;

  if ((Level2Expr != 0) && (Level2Expr2 == 0))
  {
    bIsSimple = Level2Expr->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel4Expr::hasSlice() const
{
  bool bHasSlice = false;

  if (Level2Expr != 0)
  {
    bHasSlice = Level2Expr->hasSlice();
  }

  if (Level2Expr2 != 0)
  {
    bHasSlice = bHasSlice || Level2Expr2->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranLevel4Expr::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranLevel4Expr"))
  {
    const AdtFortranLevel4Expr* pLevel4Expr = (const AdtFortranLevel4Expr*)pObj;

    bAllowableMatch = isSimple() && pLevel4Expr->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel4Expr::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (Level2Expr != 0)
  {
    bool bHasOp = ((Level2Expr2 != 0) && (RelOp != 0));

    if (bHasOp)
    {
      write(pOutFile, "(");
    }

    Level2Expr->writeCPP(pOutFile, nMode);

    if (bHasOp)
    {
      write(pOutFile, " ");
      RelOp->writeCPP(pOutFile, nMode);
      write(pOutFile, " ");
      Level2Expr2->writeCPP(pOutFile, nMode);
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel4Expr::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Level2Expr != 0)
  {
    bool bHasOp = ((Level2Expr2 != 0) && (RelOp != 0));

    if (bHasOp)
    {
      write(pOutFile, "(");
    }

    Level2Expr->writeDelphi(pOutFile, nMode);

    if (bHasOp)
    {
      write(pOutFile, " ");
      RelOp->writeDelphi(pOutFile, nMode);
      write(pOutFile, " ");
      Level2Expr2->writeDelphi(pOutFile, nMode);
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLevel4Expr::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Level2Expr != 0)
  {
    Level2Expr->writeFortran(pOutFile, nMode);

    if ((Level2Expr2 != 0) && (RelOp != 0))
    {
      RelOp->writeFortran(pOutFile, nMode);
      Level2Expr2->writeFortran(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranLevel4Expr, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranAndOperand method implementations
//  ----------------------------------------------------------------------------
AdtFortranAndOperand::AdtFortranAndOperand(AdtParser* pLevel4ExprObj,
                                           bool bNot)
 : AdtFortranBase()
{
  initObject(Level4Expr,  pLevel4ExprObj, AdtFortranLevel4Expr, true);

  Not   = bNot;
}

//  ----------------------------------------------------------------------------

AdtFortranAndOperand::AdtFortranAndOperand(const AdtFortranAndOperand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Level4Expr,  rCopy, AdtFortranLevel4Expr);

  Not   = rCopy.Not;
}

//  ----------------------------------------------------------------------------

AdtFortranAndOperand::~AdtFortranAndOperand()
{
  UtlReleaseReference(Level4Expr);
}

//  ----------------------------------------------------------------------------

void AdtFortranAndOperand::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (Level4Expr != 0)
  {
    Level4Expr->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranAndOperand::isSimple() const
{
  bool bIsSimple = false;

  if ((Level4Expr != 0) && !Not)
  {
    bIsSimple = Level4Expr->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAndOperand::hasSlice() const
{
  bool bHasSlice = false;

  if (Level4Expr != 0)
  {
    bHasSlice = Level4Expr->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAndOperand::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranAndOperand"))
  {
    const AdtFortranAndOperand* pAndOperand = (const AdtFortranAndOperand*)pObj;

    bAllowableMatch = isSimple() && pAndOperand->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAndOperand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (Level4Expr != 0)
  {
    if (Not)
    {
      write(pOutFile, "!(");
    }

    Level4Expr->writeCPP(pOutFile, nMode);

    if (Not)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAndOperand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Level4Expr != 0)
  {
    if (Not)
    {
      write(pOutFile, " not (");
    }

    Level4Expr->writeDelphi(pOutFile, nMode);

    if (Not)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAndOperand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Level4Expr != 0)
  {
    if (Not)
    {
      write(pOutFile, ".NOT.(");
    }

    Level4Expr->writeFortran(pOutFile, nMode);

    if (Not)
    {
      write(pOutFile, ")");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranAndOperand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranOrOperand method implementations
//  ----------------------------------------------------------------------------
AdtFortranOrOperand::AdtFortranOrOperand(AdtParser* pAndOperandObj,
                                         AdtParser* pOrOperandObj)
 : AdtFortranBase()
{
  initObject(AndOperand,  pAndOperandObj, AdtFortranAndOperand, true);
  initObject(OrOperand,   pOrOperandObj,  AdtFortranOrOperand,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranOrOperand::AdtFortranOrOperand(const AdtFortranOrOperand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(AndOperand,  rCopy,  AdtFortranAndOperand);
  copyObject(OrOperand,   rCopy,  AdtFortranOrOperand);
}

//  ----------------------------------------------------------------------------

AdtFortranOrOperand::~AdtFortranOrOperand()
{
  UtlReleaseReference(AndOperand);
  UtlReleaseReference(OrOperand);
}

//  ----------------------------------------------------------------------------

void AdtFortranOrOperand::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                               const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (AndOperand != 0)
  {
    AndOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (OrOperand != 0)
  {
    OrOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranOrOperand::isSimple() const
{
  bool bIsSimple = false;

  if ((AndOperand != 0) && (OrOperand == 0))
  {
    bIsSimple = AndOperand->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranOrOperand::hasSlice() const
{
  bool bHasSlice = false;

  if (AndOperand != 0)
  {
    bHasSlice = AndOperand->hasSlice();
  }

  if (OrOperand != 0)
  {
    bHasSlice = bHasSlice || OrOperand->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranOrOperand::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranOrOperand"))
  {
    const AdtFortranOrOperand* pOrOperand = (const AdtFortranOrOperand*)pObj;

    bAllowableMatch = isSimple() && pOrOperand->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranOrOperand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (AndOperand != 0)
  {
    if (OrOperand != 0)
    {
      OrOperand->writeCPP(pOutFile, nMode);

      write(pOutFile, " && ");
    }

    AndOperand->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranOrOperand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (AndOperand != 0)
  {
    if (OrOperand != 0)
    {
      OrOperand->writeDelphi(pOutFile, nMode);

      write(pOutFile, " and ");
    }

    AndOperand->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranOrOperand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (AndOperand != 0)
  {
    if (OrOperand != 0)
    {
      OrOperand->writeFortran(pOutFile, nMode);

      write(pOutFile, ".AND.");
    }

    AndOperand->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranOrOperand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEquivOperand method implementations
//  ----------------------------------------------------------------------------
AdtFortranEquivOperand::AdtFortranEquivOperand(AdtParser* pOrOperandObj,
                                               AdtParser* pEquivOperandObj)
 : AdtFortranBase()
{
  initObject(OrOperand,     pOrOperandObj,    AdtFortranOrOperand,    true);
  initObject(EquivOperand,  pEquivOperandObj, AdtFortranEquivOperand, true);
}

//  ----------------------------------------------------------------------------

AdtFortranEquivOperand::AdtFortranEquivOperand(const AdtFortranEquivOperand& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(OrOperand,     rCopy,  AdtFortranOrOperand);
  copyObject(EquivOperand,  rCopy,  AdtFortranEquivOperand);
}

//  ----------------------------------------------------------------------------

AdtFortranEquivOperand::~AdtFortranEquivOperand()
{
  UtlReleaseReference(OrOperand);
  UtlReleaseReference(EquivOperand);
}

//  ----------------------------------------------------------------------------

void AdtFortranEquivOperand::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                                  const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (OrOperand != 0)
  {
    OrOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (EquivOperand != 0)
  {
    EquivOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranEquivOperand::isSimple() const
{
  bool bIsSimple = false;

  if ((OrOperand != 0) && (EquivOperand == 0))
  {
    bIsSimple = OrOperand->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranEquivOperand::hasSlice() const
{
  bool bHasSlice = false;

  if (OrOperand != 0)
  {
    bHasSlice = OrOperand->hasSlice();
  }

  if (EquivOperand != 0)
  {
    bHasSlice = bHasSlice || EquivOperand->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranEquivOperand::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranEquivOperand"))
  {
    const AdtFortranEquivOperand* pEquivOperand = (const AdtFortranEquivOperand*)pObj;

    bAllowableMatch = isSimple() && pEquivOperand->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEquivOperand::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (OrOperand != 0)
  {
    if (EquivOperand != 0)
    {
      EquivOperand->writeCPP(pOutFile, nMode);

      write(pOutFile, " || ");
    }

    OrOperand->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEquivOperand::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (OrOperand != 0)
  {
    if (EquivOperand != 0)
    {
      EquivOperand->writeDelphi(pOutFile, nMode);

      write(pOutFile, " or ");
    }

    OrOperand->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEquivOperand::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (OrOperand != 0)
  {
    if (EquivOperand != 0)
    {
      EquivOperand->writeFortran(pOutFile, nMode);

      write(pOutFile, ".OR.");
    }

    OrOperand->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEquivOperand, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranExpr method implementations
//  ----------------------------------------------------------------------------
AdtFortranExpr::AdtFortranExpr(AdtParser* pEquivOperandObj,
                               AdtParser* pExprObj,
                               bool bIsEquivalent)
 : AdtFortranBase()
{
  initObject(EquivOperand,  pEquivOperandObj, AdtFortranEquivOperand, true);
  initObject(Expr,          pExprObj,         AdtFortranExpr,         true);

  IsEquivalent = bIsEquivalent;
}

//  ----------------------------------------------------------------------------

AdtFortranExpr::AdtFortranExpr(const AdtFortranExpr& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(EquivOperand,  rCopy,  AdtFortranEquivOperand);
  copyObject(Expr,          rCopy,  AdtFortranExpr);

  IsEquivalent = rCopy.IsEquivalent;
}

//  ----------------------------------------------------------------------------

AdtFortranExpr::~AdtFortranExpr()
{
  UtlReleaseReference(EquivOperand);
  UtlReleaseReference(Expr);
}

//  ----------------------------------------------------------------------------

void AdtFortranExpr::implementSliceFixups(const AdtFortranVariableInfo& rVarInfo,
                                          const AdtFortranSliceLoopVars& rSliceLoopVars)
{
  if (EquivOperand != 0)
  {
    EquivOperand->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }

  if (Expr != 0)
  {
    Expr->implementSliceFixups(rVarInfo, rSliceLoopVars);
  }
}

//  ----------------------------------------------------------------------------

bool AdtFortranExpr::isSimple() const
{
  bool bIsSimple = false;

  if ((EquivOperand != 0) && (Expr == 0))
  {
    bIsSimple = EquivOperand->isSimple();
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExpr::hasSlice() const
{
  bool bHasSlice = false;

  if (EquivOperand != 0)
  {
    bHasSlice = EquivOperand->hasSlice();
  }

  if (Expr != 0)
  {
    bHasSlice = bHasSlice || Expr->hasSlice();
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranExpr::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowableMatch = AdtFortranBase::allowableMatch(pObj);

  if (bAllowableMatch && pObj->isType("AdtFortranExpr"))
  {
    const AdtFortranExpr* pExpr = (const AdtFortranExpr*)pObj;

    bAllowableMatch = isSimple() && pExpr->isSimple();
  }

  return (bAllowableMatch);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExpr::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (EquivOperand != 0)
  {
    if (Expr != 0)
    {
      write(pOutFile, "(");

      Expr->writeCPP(pOutFile, nMode);

      write(pOutFile, IsEquivalent ? ") == (" : ") != (");
      write(pOutFile, ")");
    }

    EquivOperand->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExpr::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (EquivOperand != 0)
  {
    if (Expr != 0)
    {
      write(pOutFile, "(");

      Expr->writeDelphi(pOutFile, nMode);

      write(pOutFile, IsEquivalent ? ") = (" : ") <> (");
      write(pOutFile, ")");
    }

    EquivOperand->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExpr::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (EquivOperand != 0)
  {
    if (Expr != 0)
    {
      Expr->writeFortran(pOutFile, nMode);

      write(pOutFile, IsEquivalent ? ".EQV." : ".NEQV.");
    }

    EquivOperand->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranExpr, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSFExprList method implementations
//  ----------------------------------------------------------------------------
AdtFortranSFExprList::AdtFortranSFExprList(AdtParser* pSFExprListObj,
                                           AdtParser* pExprObj,
                                           AdtParser* pExpr2Obj)
 : AdtFortranBase()
{
  initObject(SFExprList,  pSFExprListObj, AdtFortranSFExprList, true);
  initObject(Expr,        pExprObj,       AdtFortranExpr,       true);
  initObject(Expr2,       pExpr2Obj,      AdtFortranExpr,       true);
}

//  ----------------------------------------------------------------------------

AdtFortranSFExprList::AdtFortranSFExprList(const AdtFortranSFExprList& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(SFExprList,  rCopy,  AdtFortranSFExprList);
  copyObject(Expr,        rCopy,  AdtFortranExpr);
  copyObject(Expr2,       rCopy,  AdtFortranExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranSFExprList::~AdtFortranSFExprList()
{
  UtlReleaseReference(SFExprList);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSFExprList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSFExprList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSFExprList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (SFExprList != 0)
  {
    SFExprList->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ":");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ":");

  if (Expr2 != 0)
  {
    Expr2->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSFExprList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranAssignmentStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranAssignmentStmt::AdtFortranAssignmentStmt(AdtParser* pLblDefObj,
                                                   AdtParser* pNameObj,
                                                   AdtParser* pExprObj,
                                                   AdtParser* pSFExprListObj,
                                                   AdtParser* pSectionSubscriptListObj)
 : AdtFortranBase()
{

  initObject(LblDef,                pLblDefObj,               AdtFortranLblDef,               true);
  initObject(Name,                  pNameObj,                 AdtFortranName,                 true);
  initObject(Expr,                  pExprObj,                 AdtFortranExpr,                 true);
  initObject(SFExprList,            pSFExprListObj,           AdtFortranSFExprList,           true);
  initObject(SectionSubscriptList,  pSectionSubscriptListObj, AdtFortranSectionSubscriptList, true);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranAssignmentStmt::AdtFortranAssignmentStmt(const AdtFortranAssignmentStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,                rCopy,  AdtFortranLblDef);
  copyObject(Name,                  rCopy,  AdtFortranName);
  copyObject(Expr,                  rCopy,  AdtFortranExpr);
  copyObject(SFExprList,            rCopy,  AdtFortranSFExprList);
  copyObject(SectionSubscriptList,  rCopy,  AdtFortranSectionSubscriptList);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranAssignmentStmt::~AdtFortranAssignmentStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
  UtlReleaseReference(SFExprList);
  UtlReleaseReference(SectionSubscriptList);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAssignmentStmt::hasSlice(int& nTriplets) const
{
  bool bHasSlice = false;

  nTriplets = 0;

  // ignore variable declarations (ie. SFExprList is only used in array
  // declarations as far as I'm aware).
  if ((Name       != 0) &&
      (Expr       != 0) &&
      (SFExprList == 0))
  {
    bHasSlice = Expr->hasSlice();

    if (SectionSubscriptList != 0)
    {
      bool bRH_HasSlice = SectionSubscriptList->hasSlice(nTriplets);

      // Need to be careful how we write this so that the optimiser doesn't
      // exclude the call to hasSlice()
      if (!bHasSlice)
      {
        bHasSlice = bRH_HasSlice;
      }
    }
  }

  return (bHasSlice);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAssignmentStmt::implementSliceFixups(AdtStringByStringMap& rAddedVarMap,
                                                    const AdtFortranVariableInfo& rVariableInfo,
                                                    AdtFortranDeclarations* pDeclarations,
                                                    AdtFile* pFile)
{
  // What needs to happen is this. Assume the slice expression is syntactically valid.
  // Determine the number of indexes and the index ranges for the slice from the
  // left hand array. Construct a nested loop to loop over all indices of the arrays
  // involved and add the correct inner expression to do the required assignment.
  // This method is fool proof, requires no additional code to library or
  // language support for slicing and requires no temporary storage. Should make for
  // and efficient implementation.
  AdtFortranIfStmt*               pIfStmt               = (AdtFortranIfStmt*)this->findAscendantWithClassLineage("AdtFortranActionStmt,AdtFortranIfStmt");
  AdtFortranExecutableConstruct*  pExecutableConstruct  = (AdtFortranExecutableConstruct*)this->findAscendantWithClassLineage("AdtFortranActionStmt,AdtFortranExecutableConstruct");
  int                             nNumberOfDimensions   = rVariableInfo.numberOfDimensions(Name->name());
  int                             nTriplets             = 0;
  bool                            bNonIndexedArray      = ((nNumberOfDimensions > 0) && (SectionSubscriptList == 0));
  bool                            bChanged              = false;

  if (pIfStmt != 0)
  {
    // This should never happen as the IfStmt should have been converted to an
    // IfThenStmt by this stage. If not, we are in error.
    FAIL();
  }
  else if (pExecutableConstruct != 0)
  {
    // Do we have slices or is the destination an array without indexing, ie A instead of A(3)
    if (hasSlice(nTriplets) || bNonIndexedArray)
    {
      AdtFile                         StringFile;
      string                          OriginalConstruct;
      string                          NewConstruct;
      string                          sLabel;
      AdtFortranExecutableConstruct*  pDoConstruct              = 0;
      AdtFortranExecutableConstruct*  pInnerExecutableConstruct = (AdtFortranExecutableConstruct*)pExecutableConstruct->copy();
      AdtFortranAssignmentStmt*       pFixupAssignmentStmt      = (AdtFortranAssignmentStmt*)pInnerExecutableConstruct->findDescendant("ActionStmt,AssignmentStmt");
      AdtFortranIcon*                 pIcon                     = (AdtFortranIcon*)pFixupAssignmentStmt->findDescendant("LblDef,Icon");

      pFixupAssignmentStmt->lock();

      if (pIcon != 0)
      {
        sLabel = pIcon->name();
        pIcon->name("");
      }

      // Get a record of the construct we are about to change (for error reporting)
      StringFile.open(OriginalConstruct);

      pExecutableConstruct->writeFortran(StringFile);

      StringFile.close();

      // How many indices do we need (ie. the number of nested DO loops) to dereference the arrays.
      int nNumberOfIndices = (nTriplets > 0) ? nTriplets : nNumberOfDimensions;

      AdtFortranSliceLoopVars SliceLoopVars(nNumberOfIndices);

      // Create nested loop constructs to replace the slice assignment expression. We do this
      // by looping over all indices of Dest in the case of no triplets or over the ranges
      // specified by the triplets when we have them.
      //
      // Do we support arbitrary stride? Does fortran allow a different stride on source
      // and dest arguments? Maybe we should ignore stride for now. I don't see it cropping
      // up in any case, only if someone happens to use it in the pre-tapenade processed source.
      if ((SectionSubscriptList != 0) && (pInnerExecutableConstruct != 0))
      {
        AdtParserPtrListConstIter Iter;
        const AdtParserPtrList&   rList     = SectionSubscriptList->objList();
        int                       cn        = 0;
        int                       cm        = 0;
        int                       cm_Label  = 0;

        // If we have a label then we need to know the cm correponding to the
        // last indice need expansion as this is the one that need the label
        // associated with it
        if (sLabel.length() > 0)
        {
          for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
          {
            AdtParser*                    pSubscriptObj = *Iter;
            AdtFortranSectionSubscript*   pSubscript    = (AdtFortranSectionSubscript*)(pSubscriptObj);

            if (pSubscript != 0)
            {
              AdtFortranSubscriptTriplet* pSubscriptTriplet = (AdtFortranSubscriptTriplet*)pSubscript->findDescendant("SubscriptTriplet");

              // Does this subcript contain a slice?
              if (pSubscriptTriplet != 0)
              {
                string  LowerDim;
                string  UpperDim;

                if (rVariableInfo.lowerDimension(Name->name(), cm, LowerDim) &&
                    rVariableInfo.upperDimension(Name->name(), cm, UpperDim))
                {
                  cm_Label = cm;
                }
              }
            }

            cm++;
          }
        }

        cm = 0;

        for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
        {
          AdtParser*                    pSubscriptObj = *Iter;
          AdtFortranSectionSubscript*   pSubscript    = (AdtFortranSectionSubscript*)(pSubscriptObj);

          if (pSubscript != 0)
          {
            AdtFortranSubscriptTriplet* pSubscriptTriplet = (AdtFortranSubscriptTriplet*)pSubscript->findDescendant("SubscriptTriplet");

            // Does this subcript contain a slice?
            if (pSubscriptTriplet != 0)
            {
              string  LowerDim;
              string  UpperDim;

              if (rVariableInfo.lowerDimension(Name->name(), cm, LowerDim) &&
                  rVariableInfo.upperDimension(Name->name(), cm, UpperDim))
              {
                if (UpperDim.icompare("dim_stack") == 0)
                {
                  UpperDim  = "GETSIZE(";
                  UpperDim += Name->name();
                  UpperDim += ")";
                }

                pSubscriptTriplet->lowerIndex(LowerDim);
                pSubscriptTriplet->upperIndex(UpperDim);

                char            sLoopVarName[16]  = {0};
                AdtFortranExpr* pLowerDimExpr     = createSimpleExpression(LowerDim);
                AdtFortranExpr* pUpperDimExpr     = createSimpleExpression(UpperDim);

                ::sprintf(sLoopVarName, "ix_%d___", cn);

                SliceLoopVars.initialise(cn, sLoopVarName, LowerDim, UpperDim);

                // Is loop counter already defined
                AdtStringByStringMapIter  Iter = rAddedVarMap.find(sLoopVarName);

                if (!(rVariableInfo.hasVariable(sLoopVarName) || (Iter != rAddedVarMap.end())))
                {
                  rAddedVarMap.insert(AdtStringByStringMap::value_type(sLoopVarName, sLoopVarName));

                  // Add new local variable definition for loop counter.
                  AdtFortranBody* pBody = (AdtFortranBody*)findAscendantWithClass("AdtFortranBody");

                  if (pBody != 0)
                  {
                    AdtFortranTypeDeclarationStmt*  pTypeDeclStmt = createSimpleTypeDeclarationStmt(sLoopVarName, ForType_INTEGER);

                    pBody->addTypeDeclarationStmt(pTypeDeclStmt);
                    UtlReleaseReference(pTypeDeclStmt);
                  }
                }

                pDoConstruct = createDoConstruct(sLoopVarName,
                                                 (cm == cm_Label) ? sLabel : "",
                                                 pInnerExecutableConstruct,
                                                 pLowerDimExpr,
                                                 pUpperDimExpr,
                                                 0);

                // Set pInnerExecutableConstruct to pDoConstruct to create nested loops
                UtlReleaseReference(pInnerExecutableConstruct);
                pInnerExecutableConstruct = pDoConstruct;

                UtlReleaseReference(pLowerDimExpr);
                UtlReleaseReference(pUpperDimExpr);
              }
              else
              {
                ::printf("FATAL ERROR: AdtFortranAssignmentStmt::implementSliceFixups "
                         "failure on line %d in file %s\nCode being processed is\n"
                         "%s\n on line %d in file %s\n",
                         __LINE__,
                         __FILE__,
                         OriginalConstruct.c_str(),
                         lineNumber(),
                         fileName());

                rVariableInfo.dump();

                FAIL();
                AdtExit(-1);
              }

              cn++;
            }

            cm++;
          }
          else
          {
            ::printf("FATAL ERROR: AdtFortranAssignmentStmt::implementSliceFixups "
                     "failure on line %d in file %s\nCode being processed is\n"
                     "%s\n on line %d in file %s\n",
                     __LINE__,
                     __FILE__,
                     OriginalConstruct.c_str(),
                     lineNumber(),
                     fileName());

            FAIL();
            AdtExit(-1);
          }
        }

        // Set the parent of this new nested loop replacement to the original parent
        // for the un-expanded inner code.
        pExecutableConstruct->replaceInParent(pInnerExecutableConstruct);

        // Dereference any array indexing
        AdtFortranSectionSubscriptList* pNewSectionSubscriptList = SliceLoopVars.createSectionSubscriptList(rVariableInfo,
                                                                                                            pFixupAssignmentStmt->Name->name(),
                                                                                                            pFixupAssignmentStmt->SectionSubscriptList);

        pFixupAssignmentStmt->SectionSubscriptList->replaceInParent(pNewSectionSubscriptList);
        UtlReleaseReference(pNewSectionSubscriptList);

        if (pDeclarations != 0)
        {
          pDeclarations->checkIsVariable(pInnerExecutableConstruct, pFile);
        }

        if (cn != nNumberOfIndices)
        {
          // Get a record of the construct change we made
          StringFile.open(NewConstruct);

          pInnerExecutableConstruct->writeFortran(StringFile);

          StringFile.close();

          ::printf("SLICE FIXUP ERROR : problem fixing slice in expression on "
                   "line %d in file %s\n\nFrom\n\n%s\n\nto\n\n%s\n\n", lineNumber(),
                                                                       fileName(),
                                                                       OriginalConstruct.c_str(),
                                                                       NewConstruct.c_str());

          FAIL();
          AdtExit(-1);
        }
      }
      else
      {
        int cn        = 0;
        int cn_Label  = 0;

        // If we have a label then we need to know the cm correponding to the
        // last indice need expansion as this is the one that need the label
        // associated with it
        if (sLabel.length() > 0)
        {
          for (cn = 0 ; cn < nNumberOfIndices ; cn++)
          {
            string  LowerDim;
            string  UpperDim;

            if (rVariableInfo.lowerDimension(Name->name(), cn, LowerDim) &&
                rVariableInfo.upperDimension(Name->name(), cn, UpperDim))
            {
              cn_Label = cn;
            }
          }
        }

        for (cn = 0 ; cn < nNumberOfIndices ; cn++)
        {
          string  LowerDim;
          string  UpperDim;

          if (rVariableInfo.lowerDimension(Name->name(), cn, LowerDim) &&
              rVariableInfo.upperDimension(Name->name(), cn, UpperDim))
          {
            if (UpperDim.icompare("dim_stack") == 0)
            {
              UpperDim  = "GETSIZE(";
              UpperDim += Name->name();
              UpperDim += ")";
            }

            char            sLoopVarName[16]  = {0};
            AdtFortranExpr* pLowerDimExpr     = createSimpleExpression(LowerDim);
            AdtFortranExpr* pUpperDimExpr     = createSimpleExpression(UpperDim);

            ::sprintf(sLoopVarName, "ix_%d___", cn);

            SliceLoopVars.initialise(cn, sLoopVarName, LowerDim, UpperDim);

            // Is loop counter already defined
            AdtStringByStringMapIter  Iter = rAddedVarMap.find(sLoopVarName);

            if (!(rVariableInfo.hasVariable(sLoopVarName) || (Iter != rAddedVarMap.end())))
            {
              rAddedVarMap.insert(AdtStringByStringMap::value_type(sLoopVarName, sLoopVarName));

              // Add new local variable definition for loop counter.
              AdtFortranBody* pBody = (AdtFortranBody*)findAscendantWithClass("AdtFortranBody");

              if (pBody != 0)
              {
                AdtFortranTypeDeclarationStmt*  pTypeDeclStmt = createSimpleTypeDeclarationStmt(sLoopVarName, ForType_INTEGER);

                pBody->addTypeDeclarationStmt(pTypeDeclStmt);
                UtlReleaseReference(pTypeDeclStmt);
              }
            }

            pDoConstruct = createDoConstruct(sLoopVarName,
                                             (cn == cn_Label) ? sLabel : "",
                                             pInnerExecutableConstruct,
                                             pLowerDimExpr,
                                             pUpperDimExpr,
                                             0);

            // Set pInnerExecutableConstruct to pDoConstruct to create nested loops
            UtlReleaseReference(pInnerExecutableConstruct);
            pInnerExecutableConstruct = pDoConstruct;

            UtlReleaseReference(pLowerDimExpr);
            UtlReleaseReference(pUpperDimExpr);
          }
        }

        // Set the parent of this new nested loop replacement to the original parent
        // for the un-expanded inner code.
        pExecutableConstruct->replaceInParent(pInnerExecutableConstruct);

        // Add array indexing to the LHS of the assignment expression
        pFixupAssignmentStmt->SectionSubscriptList = SliceLoopVars.createSectionSubscriptList(rVariableInfo, 0, 0);
        pFixupAssignmentStmt->SectionSubscriptList->parent(pFixupAssignmentStmt);
      }

      // fixup the indexing on the inner loop expression
      pFixupAssignmentStmt->Expr->implementSliceFixups(rVariableInfo, SliceLoopVars);

      if (pDeclarations != 0)
      {
        pDeclarations->checkIsVariable(pInnerExecutableConstruct, pFile);
      }

      UtlReleaseReference(pFixupAssignmentStmt);
      UtlReleaseReference(pInnerExecutableConstruct);

      bChanged = true;
    }
  }

  return (bChanged);
}

//  ----------------------------------------------------------------------------

bool AdtFortranAssignmentStmt::replace(AdtFortranPrimary* pPrimaryObj)
{
  bool  bReplaced = false;

  if ((Expr                 != 0) &&
      (SFExprList           == 0) &&
      (SectionSubscriptList == 0) &&
      (pPrimaryObj          != 0) &&
       pPrimaryObj->isValidLHS())
  {
    AdtParser*  pName                 = pPrimaryObj->findDescendant("Name");
    AdtParser*  pSectionSubscriptList = pPrimaryObj->findDescendant("SectionSubscriptList");

    if (pName != 0)
    {
      Name->name(pName->name());
    }

    if (pSectionSubscriptList != 0)
    {
      AdtFortranSectionSubscriptList* pSectionSubscriptListCopy = (AdtFortranSectionSubscriptList*)pSectionSubscriptList->copy();

      UtlReleaseReference(SectionSubscriptList);
      SectionSubscriptList = pSectionSubscriptListCopy;
    }

    bReplaced = true;
  }

  return (bReplaced);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAssignmentStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
  }

  if (SFExprList != 0)
  {
    write(pOutFile, "(");
    SFExprList->writeCPP(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (SectionSubscriptList != 0)
  {
    AdtParserPtrListConstRIter  Iter;

    for (Iter = SectionSubscriptList->objList().rbegin() ; Iter != SectionSubscriptList->objList().rend() ; ++Iter)
    {
      AdtFortranBase* pFortranObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pFortranObj != 0)
      {
        pOutFile.write("[");
        pFortranObj->writeCPP(pOutFile, nMode);
        pOutFile.write("]");
      }
    }
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");
    Expr->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAssignmentStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
  }

  if (SFExprList != 0)
  {
    write(pOutFile, "(");
    SFExprList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (SectionSubscriptList != 0)
  {
    AdtParserPtrListConstIter  Iter;

    for (Iter = SectionSubscriptList->objList().begin() ; Iter != SectionSubscriptList->objList().end() ; ++Iter)
    {
      AdtFortranBase* pFortranObj = (AdtFortranBase*)((AdtParser*)*Iter);

      if (pFortranObj != 0)
      {
        pOutFile.write("[");
        pFortranObj->writeDelphi(pOutFile, nMode);
        pOutFile.write("]");
      }
    }
  }

  if (Expr != 0)
  {
    write(pOutFile, " := ");
    Expr->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranAssignmentStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, Name->name(), false);
  }

  if (SFExprList != 0)
  {
    write(pOutFile, "(");
    SFExprList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (SectionSubscriptList != 0)
  {
    write(pOutFile, "(");
    SectionSubscriptList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (Expr != 0)
  {
    write(pOutFile, " = ");
    Expr->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranAssignmentStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereStmt::AdtFortranWhereStmt(AdtParser* pLblDefObj,
                                         AdtParser* pExprObj,
                                         AdtParser* pAssignmentStmtObj)
 : AdtFortranBase()
{
  initObject(LblDef,          pLblDefObj,         AdtFortranLblDef,         true);
  initObject(Expr,            pExprObj,           AdtFortranExpr,           true);
  initObject(AssignmentStmt,  pAssignmentStmtObj, AdtFortranAssignmentStmt, true);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereStmt::AdtFortranWhereStmt(const AdtFortranWhereStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,          rCopy,  AdtFortranLblDef);
  copyObject(Expr,            rCopy,  AdtFortranExpr);
  copyObject(AssignmentStmt,  rCopy,  AdtFortranAssignmentStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereStmt::~AdtFortranWhereStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(AssignmentStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "WHERE ");

  if (Expr != 0)
  {
    write(pOutFile, "(");
    Expr->writeFortran(pOutFile, nMode);
    write(pOutFile, ") ");
  }

  if (AssignmentStmt != 0)
  {
    AssignmentStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereConstruct::AdtFortranWhereConstruct(AdtParser* pWhereConstructStmtObj,
                                                   AdtParser* pWhereRangeObj)
 : AdtFortranBase()
{
  initObject(WhereConstructStmt,  pWhereConstructStmtObj, AdtFortranWhereConstructStmt, true);
  initObject(WhereRange,          pWhereRangeObj,         AdtFortranWhereRange,         true);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereConstruct::AdtFortranWhereConstruct(const AdtFortranWhereConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(WhereConstructStmt,  rCopy,  AdtFortranWhereConstructStmt);
  copyObject(WhereRange,          rCopy,  AdtFortranWhereRange);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereConstruct::~AdtFortranWhereConstruct()
{
  UtlReleaseReference(WhereConstructStmt);
  UtlReleaseReference(WhereRange);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (WhereConstructStmt != 0)
  {
    WhereConstructStmt->writeFortran(pOutFile, nMode);
  }

  if (WhereRange != 0)
  {
    WhereRange->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereRange method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereRange::AdtFortranWhereRange(AdtParser* pWhereBodyConstructBlockObj,
                                           AdtParser* pElsewhereConstructObj,
                                           AdtParser* pMaskedElsewhereConstructObj,
                                           AdtParser* pEndWhereStmtObj)
 : AdtFortranBase()
{
  initObject(WhereBodyConstructBlock,   pWhereBodyConstructBlockObj,  AdtFortranWhereBodyConstructBlock,  true);
  initObject(ElsewhereConstruct,        pElsewhereConstructObj,       AdtFortranElsewhereConstruct,       true);
  initObject(MaskedElsewhereConstruct,  pMaskedElsewhereConstructObj, AdtFortranMaskedElsewhereConstruct, true);
  initObject(EndWhereStmt,              pEndWhereStmtObj,             AdtFortranEndWhereStmt,             true);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereRange::AdtFortranWhereRange(const AdtFortranWhereRange& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(WhereBodyConstructBlock,   rCopy,  AdtFortranWhereBodyConstructBlock);
  copyObject(ElsewhereConstruct,        rCopy,  AdtFortranElsewhereConstruct);
  copyObject(MaskedElsewhereConstruct,  rCopy,  AdtFortranMaskedElsewhereConstruct);
  copyObject(EndWhereStmt,              rCopy,  AdtFortranEndWhereStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereRange::~AdtFortranWhereRange()
{
  UtlReleaseReference(WhereBodyConstructBlock);
  UtlReleaseReference(ElsewhereConstruct);
  UtlReleaseReference(MaskedElsewhereConstruct);
  UtlReleaseReference(EndWhereStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereRange::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereRange::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereRange::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (WhereBodyConstructBlock != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    WhereBodyConstructBlock->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (MaskedElsewhereConstruct != 0)
  {
    MaskedElsewhereConstruct->writeFortran(pOutFile, nMode);
  }

  if (ElsewhereConstruct != 0)
  {
    ElsewhereConstruct->writeFortran(pOutFile, nMode);
  }

  if (EndWhereStmt != 0)
  {
    EndWhereStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereRange, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranMaskedElsewhereConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranMaskedElsewhereConstruct::AdtFortranMaskedElsewhereConstruct(AdtParser* pMaskedElsewhereStmtObj,
                                                                       AdtParser* pWhereRangeObj)
 : AdtFortranBase()
{
  initObject(MaskedElsewhereStmt, pMaskedElsewhereStmtObj,  AdtFortranMaskedElsewhereStmt,  true);
  initObject(WhereRange,          pWhereRangeObj,           AdtFortranWhereRange,           true);
}

//  ----------------------------------------------------------------------------

AdtFortranMaskedElsewhereConstruct::AdtFortranMaskedElsewhereConstruct(const AdtFortranMaskedElsewhereConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(MaskedElsewhereStmt, rCopy,  AdtFortranMaskedElsewhereStmt);
  copyObject(WhereRange,          rCopy,  AdtFortranWhereRange);
}

//  ----------------------------------------------------------------------------

AdtFortranMaskedElsewhereConstruct::~AdtFortranMaskedElsewhereConstruct()
{
  UtlReleaseReference(MaskedElsewhereStmt);
  UtlReleaseReference(WhereRange);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (MaskedElsewhereStmt != 0)
  {
    MaskedElsewhereStmt->writeFortran(pOutFile, nMode);
  }

  if (WhereRange != 0)
  {
    WhereRange->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranMaskedElsewhereConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElsewhereConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranElsewhereConstruct::AdtFortranElsewhereConstruct(AdtParser* pElsewhereStmtObj,
                                                           AdtParser* pElsewherePartObj)
 : AdtFortranBase()
{
  initObject(ElsewhereStmt, pElsewhereStmtObj,  AdtFortranElsewhereStmt,  true);
  initObject(ElsewherePart, pElsewherePartObj,  AdtFortranElsewherePart,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranElsewhereConstruct::AdtFortranElsewhereConstruct(const AdtFortranElsewhereConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ElsewhereStmt, rCopy,  AdtFortranElsewhereStmt);
  copyObject(ElsewherePart, rCopy,  AdtFortranElsewherePart);
}

//  ----------------------------------------------------------------------------

AdtFortranElsewhereConstruct::~AdtFortranElsewhereConstruct()
{
  UtlReleaseReference(ElsewhereStmt);
  UtlReleaseReference(ElsewherePart);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ElsewhereStmt != 0)
  {
    ElsewhereStmt->writeFortran(pOutFile, nMode);
  }

  if (ElsewherePart != 0)
  {
    ElsewherePart->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElsewhereConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElsewherePart method implementations
//  ----------------------------------------------------------------------------
AdtFortranElsewherePart::AdtFortranElsewherePart(AdtParser* pEndWhereStmtObj,
                                                 AdtParser* pWhereBodyConstructBlockObj)
 : AdtFortranBase()
{
  initObject(EndWhereStmt,            pEndWhereStmtObj,             AdtFortranEndWhereStmt,             true);
  initObject(WhereBodyConstructBlock, pWhereBodyConstructBlockObj,  AdtFortranWhereBodyConstructBlock,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranElsewherePart::AdtFortranElsewherePart(const AdtFortranElsewherePart& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(EndWhereStmt,            rCopy,  AdtFortranEndWhereStmt);
  copyObject(WhereBodyConstructBlock, rCopy,  AdtFortranWhereBodyConstructBlock);
}

//  ----------------------------------------------------------------------------

AdtFortranElsewherePart::~AdtFortranElsewherePart()
{
  UtlReleaseReference(EndWhereStmt);
  UtlReleaseReference(WhereBodyConstructBlock);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewherePart::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewherePart::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewherePart::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (WhereBodyConstructBlock != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    WhereBodyConstructBlock->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndWhereStmt != 0)
  {
    EndWhereStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElsewherePart, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereBodyConstructBlock method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereBodyConstructBlock::AdtFortranWhereBodyConstructBlock(AdtParser* pWhereBodyConstructObj)
 : AdtFortranBase()
{
  add(pWhereBodyConstructObj);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranWhereBodyConstructBlock::AdtFortranWhereBodyConstructBlock(const AdtFortranWhereBodyConstructBlock& rCopy)
 : AdtFortranBase(rCopy)
{
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranWhereBodyConstructBlock::~AdtFortranWhereBodyConstructBlock()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstructBlock::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstructBlock::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstructBlock::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  pOutFile.incrementIndent();
  pOutFile.newline();

  forAllWriteFortran(pOutFile, nMode, "", false, false);

  pOutFile.decrementIndent();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereBodyConstructBlock, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereConstructStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereConstructStmt::AdtFortranWhereConstructStmt(AdtParser* pLblDefObj,
                                                           AdtParser* pNameObj,
                                                           AdtParser* pExprObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);
  initObject(Expr,    pExprObj,   AdtFortranExpr,   true);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereConstructStmt::AdtFortranWhereConstructStmt(const AdtFortranWhereConstructStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);
  copyObject(Expr,    rCopy,  AdtFortranExpr);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereConstructStmt::~AdtFortranWhereConstructStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstructStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstructStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereConstructStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (Expr != 0)
  {
    write(pOutFile, "WHERE (");
    Expr->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereConstructStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranWhereBodyConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranWhereBodyConstruct::AdtFortranWhereBodyConstruct(AdtParser* pAssignmentStmtObj,
                                                           AdtParser* pWhereStmtObj,
                                                           AdtParser* pWhereConstructObj)
 : AdtFortranBase()
{
  initObject(AssignmentStmt,  pAssignmentStmtObj, AdtFortranAssignmentStmt, true);
  initObject(WhereStmt,       pWhereStmtObj,      AdtFortranWhereStmt,      true);
  initObject(WhereConstruct,  pWhereConstructObj, AdtFortranWhereConstruct, true);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereBodyConstruct::AdtFortranWhereBodyConstruct(const AdtFortranWhereBodyConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(AssignmentStmt,  rCopy,  AdtFortranAssignmentStmt);
  copyObject(WhereStmt,       rCopy,  AdtFortranWhereStmt);
  copyObject(WhereConstruct,  rCopy,  AdtFortranWhereConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranWhereBodyConstruct::~AdtFortranWhereBodyConstruct()
{
  UtlReleaseReference(AssignmentStmt);
  UtlReleaseReference(WhereStmt);
  UtlReleaseReference(WhereConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranWhereBodyConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (AssignmentStmt != 0)
  {
    AssignmentStmt->writeFortran(pOutFile, nMode);
  }

  if (WhereStmt != 0)
  {
    WhereStmt->writeFortran(pOutFile, nMode);
  }

  if (WhereConstruct != 0)
  {
    WhereConstruct->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranWhereBodyConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranMaskedElsewhereStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranMaskedElsewhereStmt::AdtFortranMaskedElsewhereStmt(AdtParser* pLblDefObj,
                                                             AdtParser* pExprObj,
                                                             AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Expr,    pExprObj,   AdtFortranExpr,   true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranMaskedElsewhereStmt::AdtFortranMaskedElsewhereStmt(const AdtFortranMaskedElsewhereStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Expr,    rCopy,  AdtFortranExpr);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranMaskedElsewhereStmt::~AdtFortranMaskedElsewhereStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranMaskedElsewhereStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " ELSEWHERE (");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranMaskedElsewhereStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElsewhereStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranElsewhereStmt::AdtFortranElsewhereStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElsewhereStmt::AdtFortranElsewhereStmt(const AdtFortranElsewhereStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElsewhereStmt::~AdtFortranElsewhereStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsewhereStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " ELSEWHERE ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElsewhereStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndWhereStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndWhereStmt::AdtFortranEndWhereStmt(AdtParser* pLblDefObj,
                                               AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranEndWhereStmt::AdtFortranEndWhereStmt(const AdtFortranEndWhereStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranEndWhereStmt::~AdtFortranEndWhereStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndWhereStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndWhereStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: WHERE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndWhereStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " ENDWHERE ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndWhereStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIfConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranIfConstruct::AdtFortranIfConstruct(AdtParser* pIfThenStmtObj,
                                             AdtParser* pThenPartObj)
 : AdtFortranBase()
{
  initObject(IfThenStmt,  pIfThenStmtObj, AdtFortranIfThenStmt, true);
  initObject(ThenPart,    pThenPartObj,   AdtFortranThenPart,   true);
}

//  ----------------------------------------------------------------------------

AdtFortranIfConstruct::AdtFortranIfConstruct(const AdtFortranIfConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(IfThenStmt,  rCopy,  AdtFortranIfThenStmt);
  copyObject(ThenPart,    rCopy,  AdtFortranThenPart);
}

//  ----------------------------------------------------------------------------

AdtFortranIfConstruct::~AdtFortranIfConstruct()
{
  UtlReleaseReference(IfThenStmt);
  UtlReleaseReference(ThenPart);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (IfThenStmt != 0)
  {
    IfThenStmt->writeCPP(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (IfThenStmt != 0)
  {
    IfThenStmt->writeDelphi(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (IfThenStmt != 0)
  {
    IfThenStmt->writeFortran(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIfConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranThenPart method implementations
//  ----------------------------------------------------------------------------
AdtFortranThenPart::AdtFortranThenPart(AdtParser* pEndIfStmtObj,
                                       AdtParser* pConditionalBodyObj,
                                       AdtParser* pElseIfConstructObj,
                                       AdtParser* pElseConstructObj)
 : AdtFortranBase()
{
  initObject(EndIfStmt,       pEndIfStmtObj,        AdtFortranEndIfStmt,        true);
  initObject(ConditionalBody, pConditionalBodyObj,  AdtFortranConditionalBody,  true);
  initObject(ElseIfConstruct, pElseIfConstructObj,  AdtFortranElseIfConstruct,  true);
  initObject(ElseConstruct,   pElseConstructObj,    AdtFortranElseConstruct,    true);
}

//  ----------------------------------------------------------------------------

AdtFortranThenPart::AdtFortranThenPart(const AdtFortranThenPart& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(EndIfStmt,       rCopy,  AdtFortranEndIfStmt);
  copyObject(ConditionalBody, rCopy,  AdtFortranConditionalBody);
  copyObject(ElseIfConstruct, rCopy,  AdtFortranElseIfConstruct);
  copyObject(ElseConstruct,   rCopy,  AdtFortranElseConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranThenPart::~AdtFortranThenPart()
{
  UtlReleaseReference(EndIfStmt);
  UtlReleaseReference(ConditionalBody);
  UtlReleaseReference(ElseIfConstruct);
  UtlReleaseReference(ElseConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranThenPart::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeCPP(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");

    pOutFile.newline();
  }

  if (ElseIfConstruct != 0)
  {
    ElseIfConstruct->writeCPP(pOutFile, nMode);
  }

  if (ElseConstruct != 0)
  {
    ElseConstruct->writeCPP(pOutFile, nMode);
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranThenPart::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end");

    if ((ElseIfConstruct == 0) && (ElseConstruct == 0))
    {
      pOutFile.write(";");
    }

    pOutFile.newline();
  }

  if (ElseIfConstruct != 0)
  {
    ElseIfConstruct->writeDelphi(pOutFile, nMode);
  }

  if (ElseConstruct != 0)
  {
    ElseConstruct->writeDelphi(pOutFile, nMode);
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranThenPart::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (ElseIfConstruct != 0)
  {
    ElseIfConstruct->writeFortran(pOutFile, nMode);
  }

  if (ElseConstruct != 0)
  {
    ElseConstruct->writeFortran(pOutFile, nMode);
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranThenPart, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElseIfConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranElseIfConstruct::AdtFortranElseIfConstruct(AdtParser* pElseIfStmtObj,
                                                     AdtParser* pThenPartObj)
 : AdtFortranBase()
{
  initObject(ElseIfStmt,  pElseIfStmtObj, AdtFortranElseIfStmt, true);
  initObject(ThenPart,    pThenPartObj,   AdtFortranThenPart,   true);
}

//  ----------------------------------------------------------------------------

AdtFortranElseIfConstruct::AdtFortranElseIfConstruct(const AdtFortranElseIfConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ElseIfStmt,  rCopy,  AdtFortranElseIfStmt);
  copyObject(ThenPart,    rCopy,  AdtFortranThenPart);
}

//  ----------------------------------------------------------------------------

AdtFortranElseIfConstruct::~AdtFortranElseIfConstruct()
{
  UtlReleaseReference(ElseIfStmt);
  UtlReleaseReference(ThenPart);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ElseIfStmt != 0)
  {
    ElseIfStmt->writeCPP(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ElseIfStmt != 0)
  {
    ElseIfStmt->writeDelphi(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ElseIfStmt != 0)
  {
    ElseIfStmt->writeFortran(pOutFile, nMode);
  }

  if (ThenPart != 0)
  {
    ThenPart->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElseIfConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElseConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranElseConstruct::AdtFortranElseConstruct(AdtParser* pElseStmtObj,
                                                 AdtParser* pElsePartObj)
 : AdtFortranBase()
{
  initObject(ElseStmt,  pElseStmtObj,   AdtFortranElseStmt, true);
  initObject(ElsePart,  pElsePartObj,   AdtFortranElsePart, true);
}

//  ----------------------------------------------------------------------------

AdtFortranElseConstruct::AdtFortranElseConstruct(const AdtFortranElseConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(ElseStmt,  rCopy,  AdtFortranElseStmt);
  copyObject(ElsePart,  rCopy,  AdtFortranElsePart);
}

//  ----------------------------------------------------------------------------

AdtFortranElseConstruct::~AdtFortranElseConstruct()
{
  UtlReleaseReference(ElseStmt);
  UtlReleaseReference(ElsePart);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ElseStmt != 0)
  {
    ElseStmt->writeCPP(pOutFile, nMode);
  }

  if (ElsePart != 0)
  {
    ElsePart->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ElseStmt != 0)
  {
    ElseStmt->writeDelphi(pOutFile, nMode);
  }

  if (ElsePart != 0)
  {
    ElsePart->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ElseStmt != 0)
  {
    ElseStmt->writeFortran(pOutFile, nMode);
  }

  if (ElsePart != 0)
  {
    ElsePart->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElseConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElsePart method implementations
//  ----------------------------------------------------------------------------
AdtFortranElsePart::AdtFortranElsePart(AdtParser* pEndIfStmtObj,
                                       AdtParser* pConditionalBodyObj)
 : AdtFortranBase()
{
  initObject(EndIfStmt,       pEndIfStmtObj,        AdtFortranEndIfStmt,        true);
  initObject(ConditionalBody, pConditionalBodyObj,  AdtFortranConditionalBody,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranElsePart::AdtFortranElsePart(const AdtFortranElsePart& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(EndIfStmt,       rCopy,  AdtFortranEndIfStmt);
  copyObject(ConditionalBody, rCopy,  AdtFortranConditionalBody);
}

//  ----------------------------------------------------------------------------

AdtFortranElsePart::~AdtFortranElsePart()
{
  UtlReleaseReference(EndIfStmt);
  UtlReleaseReference(ConditionalBody);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsePart::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeCPP(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");
    pOutFile.newline();
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsePart::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end;");
    pOutFile.newline();
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElsePart::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (ConditionalBody != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    ConditionalBody->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndIfStmt != 0)
  {
    EndIfStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElsePart, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranConditionalBody method implementations
//  ----------------------------------------------------------------------------
AdtFortranConditionalBody::AdtFortranConditionalBody(AdtParser* pExecutableConstructObj)
 : AdtFortranBase()
{
  add(pExecutableConstructObj);
}

//  ----------------------------------------------------------------------------

AdtFortranConditionalBody::AdtFortranConditionalBody(const AdtFortranConditionalBody& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranConditionalBody::~AdtFortranConditionalBody()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranConditionalBody::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, "", false, false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranConditionalBody::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "", false, false));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranConditionalBody::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", false, false));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranConditionalBody, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIfThenStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranIfThenStmt::AdtFortranIfThenStmt(AdtParser* pLblDefObj,
                                           AdtParser* pExprObj,
                                           AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Expr,    pExprObj,   AdtFortranExpr,   true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIfThenStmt::AdtFortranIfThenStmt(const AdtFortranIfThenStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Expr,    rCopy,  AdtFortranExpr);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIfThenStmt::~AdtFortranIfThenStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfThenStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "if (");

  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfThenStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "if (");

  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ") then");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfThenStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "IF (");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ") THEN");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIfThenStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElseIfStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranElseIfStmt::AdtFortranElseIfStmt(AdtParser* pLblDefObj,
                                           AdtParser* pExprObj,
                                           AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Expr,    pExprObj,   AdtFortranExpr,   true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElseIfStmt::AdtFortranElseIfStmt(const AdtFortranElseIfStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Expr,    rCopy,  AdtFortranExpr);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElseIfStmt::~AdtFortranElseIfStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "else if (");

  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "else if (");

  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ") then ");

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseIfStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ELSEIF (");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ") THEN ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElseIfStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranElseStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranElseStmt::AdtFortranElseStmt(AdtParser* pLblDefObj,
                                       AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElseStmt::AdtFortranElseStmt(const AdtFortranElseStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranElseStmt::~AdtFortranElseStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "else ");

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "else ");

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranElseStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ELSE ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranElseStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndIfStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndIfStmt::AdtFortranEndIfStmt(AdtParser* pLblDefObj,
                                         AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranEndIfStmt::AdtFortranEndIfStmt(const AdtFortranEndIfStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranEndIfStmt::~AdtFortranEndIfStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndIfStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndIfStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndIfStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDIF ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndIfStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIfStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranIfStmt::AdtFortranIfStmt(AdtParser* pLblDefObj,
                                   AdtParser* pExprObj,
                                   AdtParser* pActionStmtObj)
 : AdtFortranBase()
{
  initObject(LblDef,      pLblDefObj,     AdtFortranLblDef,     true);
  initObject(Expr,        pExprObj,       AdtFortranExpr,       true);
  initObject(ActionStmt,  pActionStmtObj, AdtFortranActionStmt, true);
}

//  ----------------------------------------------------------------------------

AdtFortranIfStmt::AdtFortranIfStmt(const AdtFortranIfStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,      rCopy,  AdtFortranLblDef);
  copyObject(Expr,        rCopy,  AdtFortranExpr);
  copyObject(ActionStmt,  rCopy,  AdtFortranActionStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranIfStmt::~AdtFortranIfStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(ActionStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "if (");

  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  pOutFile.newline();

  write(pOutFile, "{");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ActionStmt != 0)
  {
    ActionStmt->writeCPP(pOutFile, nMode);
  }

  pOutFile.decrementIndent();

  pOutFile.newline();

  write(pOutFile, "}");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "if (");

  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ") then");

  pOutFile.newline();

  write(pOutFile, "begin");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ActionStmt != 0)
  {
    ActionStmt->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();

  pOutFile.newline();

  write(pOutFile, "end;");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIfStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "IF (");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  if (ActionStmt != 0)
  {
    ActionStmt->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

void AdtFortranIfStmt::equivalentIfThenCode(string& rCodeString) const
{
  AdtFile File;

  File.open(rCodeString);

  if (LblDef != 0)
  {
    LblDef->writeFortran(File, 0);
  }

  write(File, "IF (");

  if (Expr != 0)
  {
    Expr->writeFortran(File, 0);
  }

  write(File, ") THEN ");
  File.incrementIndent();
  File.newline();

  if (ActionStmt != 0)
  {
    ActionStmt->writeFortran(File, 0);
  }

  File.decrementIndent();
  File.newline();
  write(File, " END IF");
  File.newline();

  File.close();
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIfStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseConstruct::AdtFortranCaseConstruct(AdtParser* pSelectCaseStmtObj,
                                                 AdtParser* pSelectCaseBodyObj,
                                                 AdtParser* pEndSelectStmtObj)
 : AdtFortranBase()
{
  initObject(SelectCaseStmt,  pSelectCaseStmtObj, AdtFortranSelectCaseStmt, true);
  initObject(SelectCaseBody,  pSelectCaseBodyObj, AdtFortranSelectCaseBody, true);
  initObject(EndSelectStmt,   pEndSelectStmtObj,  AdtFortranEndSelectStmt,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseConstruct::AdtFortranCaseConstruct(const AdtFortranCaseConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(SelectCaseStmt,  rCopy,  AdtFortranSelectCaseStmt);
  copyObject(SelectCaseBody,  rCopy,  AdtFortranSelectCaseBody);
  copyObject(EndSelectStmt,   rCopy,  AdtFortranEndSelectStmt);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseConstruct::~AdtFortranCaseConstruct()
{
  UtlReleaseReference(SelectCaseStmt);
  UtlReleaseReference(SelectCaseBody);
  UtlReleaseReference(EndSelectStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (SelectCaseStmt != 0)
  {
    SelectCaseStmt->writeDelphi(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    SelectCaseBody->writeCPP(pOutFile, nMode);

    pOutFile.newline();
    write(pOutFile, "break;");
    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");
    pOutFile.newline();
  }

  if (EndSelectStmt != 0)
  {
    EndSelectStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (SelectCaseStmt != 0)
  {
    SelectCaseStmt->writeDelphi(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    SelectCaseBody->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end;");
    pOutFile.newline();
  }

  if (EndSelectStmt != 0)
  {
    EndSelectStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (SelectCaseStmt != 0)
  {
    SelectCaseStmt->writeFortran(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    SelectCaseBody->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  if (EndSelectStmt != 0)
  {
    EndSelectStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSelectCaseBody method implementations
//  ----------------------------------------------------------------------------
AdtFortranSelectCaseBody::AdtFortranSelectCaseBody(AdtParser* pCaseStmtObj,
                                                   AdtParser* pSelectCaseBodyObj,
                                                   AdtParser* pCaseBodyConstructObj)
 : AdtFortranBase()
{
  initObject(CaseStmt,          pCaseStmtObj,           AdtFortranCaseStmt,           true);
  initObject(SelectCaseBody,    pSelectCaseBodyObj,     AdtFortranSelectCaseBody,     true);
  initObject(CaseBodyConstruct, pCaseBodyConstructObj,  AdtFortranCaseBodyConstruct,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranSelectCaseBody::AdtFortranSelectCaseBody(const AdtFortranSelectCaseBody& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(CaseStmt,          rCopy,  AdtFortranCaseStmt);
  copyObject(SelectCaseBody,    rCopy,  AdtFortranSelectCaseBody);
  copyObject(CaseBodyConstruct, rCopy,  AdtFortranCaseBodyConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranSelectCaseBody::~AdtFortranSelectCaseBody()
{
  UtlReleaseReference(CaseStmt);
  UtlReleaseReference(SelectCaseBody);
  UtlReleaseReference(CaseBodyConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseBody::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeCPP(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    SelectCaseBody->writeCPP(pOutFile, nMode);
  }

  if (CaseBodyConstruct != 0)
  {
    CaseBodyConstruct->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseBody::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeDelphi(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    SelectCaseBody->writeDelphi(pOutFile, nMode);
  }

  if (CaseBodyConstruct != 0)
  {
    CaseBodyConstruct->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseBody::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeFortran(pOutFile, nMode);
  }

  if (SelectCaseBody != 0)
  {
    SelectCaseBody->writeFortran(pOutFile, nMode);
  }

  if (CaseBodyConstruct != 0)
  {
    CaseBodyConstruct->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSelectCaseBody, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseBodyConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseBodyConstruct::AdtFortranCaseBodyConstruct(AdtParser* pCaseStmtObj,
                                                         AdtParser* pExecutableConstructObj)
 : AdtFortranBase()
{
  initObject(CaseStmt,            pCaseStmtObj,             AdtFortranCaseStmt,             true);
  initObject(ExecutableConstruct, pExecutableConstructObj,  AdtFortranExecutableConstruct,  true);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseBodyConstruct::AdtFortranCaseBodyConstruct(const AdtFortranCaseBodyConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(CaseStmt,            rCopy,  AdtFortranCaseStmt);
  copyObject(ExecutableConstruct, rCopy,  AdtFortranExecutableConstruct);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseBodyConstruct::~AdtFortranCaseBodyConstruct()
{
  UtlReleaseReference(CaseStmt);
  UtlReleaseReference(ExecutableConstruct);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseBodyConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeCPP(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ExecutableConstruct->writeCPP(pOutFile, nMode);

    pOutFile.newline();

    write(pOutFile, "break;");
    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseBodyConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeDelphi(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ExecutableConstruct->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end;");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseBodyConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (CaseStmt != 0)
  {
    CaseStmt->writeFortran(pOutFile, nMode);
  }

  if (ExecutableConstruct != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.newline();

    ExecutableConstruct->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseBodyConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSelectCaseStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranSelectCaseStmt::AdtFortranSelectCaseStmt(AdtParser* pLblDefObj,
                                                   AdtParser* pNameObj,
                                                   AdtParser* pExprObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);
  initObject(Expr,    pExprObj,   AdtFortranExpr,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranSelectCaseStmt::AdtFortranSelectCaseStmt(const AdtFortranSelectCaseStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);
  copyObject(Expr,    rCopy,  AdtFortranExpr);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranSelectCaseStmt::~AdtFortranSelectCaseStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "select(");

  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  pOutFile.newline();

  write(pOutFile, "{");

  pOutFile.incrementIndent();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "case (");

  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ") of ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSelectCaseStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "SELECTCASE (");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ") ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSelectCaseStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseStmt::AdtFortranCaseStmt(AdtParser* pLblDefObj,
                                       AdtParser* pCaseSelectorObj,
                                       AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,        pLblDefObj,       AdtFortranLblDef,       true);
  initObject(CaseSelector,  pCaseSelectorObj, AdtFortranCaseSelector, true);
  initObject(Name,          pNameObj,         AdtFortranName,         true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCaseStmt::AdtFortranCaseStmt(const AdtFortranCaseStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,        rCopy,  AdtFortranLblDef);
  copyObject(CaseSelector,  rCopy,  AdtFortranCaseSelector);
  copyObject(Name,          rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCaseStmt::~AdtFortranCaseStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(CaseSelector);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "case ");

  if (CaseSelector != 0)
  {
    CaseSelector->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ": ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (CaseSelector != 0)
  {
    CaseSelector->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ": ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "CASE ");

  if (CaseSelector != 0)
  {
    CaseSelector->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndSelectStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndSelectStmt::AdtFortranEndSelectStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,        pLblDefObj,       AdtFortranLblDef,       true);
  initObject(Name,          pNameObj,         AdtFortranName,         true);
}

//  ----------------------------------------------------------------------------

AdtFortranEndSelectStmt::AdtFortranEndSelectStmt(const AdtFortranEndSelectStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,        rCopy,  AdtFortranLblDef);
  copyObject(Name,          rCopy,  AdtFortranName);
}

//  ----------------------------------------------------------------------------

AdtFortranEndSelectStmt::~AdtFortranEndSelectStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSelectStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.newline();

  write(pOutFile, "}");

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSelectStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "end;");

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSelectStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDSELECT ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndSelectStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseSelector method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseSelector::AdtFortranCaseSelector(AdtParser* pCaseValueRangeListObj)
 : AdtFortranBase()
{
  initObject(CaseValueRangeList,  pCaseValueRangeListObj, AdtFortranCaseValueRangeList, true);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseSelector::AdtFortranCaseSelector(const AdtFortranCaseSelector& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(CaseValueRangeList,  rCopy,  AdtFortranCaseValueRangeList);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseSelector::~AdtFortranCaseSelector()
{
  UtlReleaseReference(CaseValueRangeList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseSelector::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (CaseValueRangeList != 0)
  {
    CaseValueRangeList->writeCPP(pOutFile, nMode);
  }
  else
  {
    write(pOutFile, "default");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseSelector::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (CaseValueRangeList != 0)
  {
    CaseValueRangeList->writeDelphi(pOutFile, nMode);
  }
  else
  {
    write(pOutFile, "default");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseSelector::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (CaseValueRangeList != 0)
  {
    write(pOutFile, "(");
    CaseValueRangeList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }
  else
  {
    write(pOutFile, "DEFAULT");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseSelector, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseValueRangeList method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseValueRangeList::AdtFortranCaseValueRangeList(AdtParser* pCaseValueRangeObj)
 : AdtFortranBase()
{
  add(pCaseValueRangeObj);
}

//  ----------------------------------------------------------------------------

AdtFortranCaseValueRangeList::AdtFortranCaseValueRangeList(const AdtFortranCaseValueRangeList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranCaseValueRangeList::~AdtFortranCaseValueRangeList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRangeList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRangeList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRangeList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseValueRangeList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCaseValueRange method implementations
//  ----------------------------------------------------------------------------
AdtFortranCaseValueRange::AdtFortranCaseValueRange(AdtParser* pExprObj,
                                                   AdtParser* pExpr2Obj,
                                                   bool bHasColon)
 : AdtFortranBase()
{
  initObject(Expr,  pExprObj,   AdtFortranExpr, true);
  initObject(Expr2, pExpr2Obj,  AdtFortranExpr, true);

  HasColon = bHasColon;
}

//  ----------------------------------------------------------------------------

AdtFortranCaseValueRange::AdtFortranCaseValueRange(const AdtFortranCaseValueRange& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Expr,  rCopy,  AdtFortranExpr);
  copyObject(Expr2, rCopy,  AdtFortranExpr);

  HasColon = rCopy.HasColon;
}

//  ----------------------------------------------------------------------------

AdtFortranCaseValueRange::~AdtFortranCaseValueRange()
{
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRange::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (Expr != 0)
  {
    Expr->writeCPP(pOutFile, nMode);
  }

  if (HasColon)
  {
    write(pOutFile, "..");
  }

  if (Expr2 != 0)
  {
    Expr2->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRange::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Expr != 0)
  {
    Expr->writeDelphi(pOutFile, nMode);
  }

  if (HasColon)
  {
    write(pOutFile, "..");
  }

  if (Expr2 != 0)
  {
    Expr2->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCaseValueRange::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  if (HasColon)
  {
    write(pOutFile, ":");
  }

  if (Expr2 != 0)
  {
    Expr2->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCaseValueRange, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranDoConstruct method implementations
//  ----------------------------------------------------------------------------
AdtFortranDoConstruct::AdtFortranDoConstruct(AdtParser* pLblDefObj,
                                             AdtParser* pLblRefObj,
                                             AdtParser* pLoopControlObj,
                                             AdtParser* pNameObj,
                                             AdtParser* pConditionalBodyObj,
                                             AdtParser* pEndDoStmtObj,
                                             bool bHasComma)
 : AdtFortranBase()
{
  initObject(LblDef,          pLblDefObj,           AdtFortranLblDef,           true);
  initObject(LblRef,          pLblRefObj,           AdtFortranLblRef,           true);
  initObject(LoopControl,     pLoopControlObj,      AdtFortranLoopControl,      true);
  initObject(Name,            pNameObj,             AdtFortranName,             true);
  initObject(ConditionalBody, pConditionalBodyObj,  AdtFortranConditionalBody,  true);
  initObject(EndDoStmt,       pEndDoStmtObj,        AdtFortranEndDoStmt,        true);

  HasComma = bHasComma;

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranDoConstruct::AdtFortranDoConstruct(const AdtFortranDoConstruct& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,          rCopy,  AdtFortranLblDef);
  copyObject(LblRef,          rCopy,  AdtFortranLblRef);
  copyObject(LoopControl,     rCopy,  AdtFortranLoopControl);
  copyObject(Name,            rCopy,  AdtFortranName);
  copyObject(ConditionalBody, rCopy,  AdtFortranConditionalBody);
  copyObject(EndDoStmt,       rCopy,  AdtFortranEndDoStmt);

  HasComma        = rCopy.HasComma;
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranDoConstruct::~AdtFortranDoConstruct()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(LblRef);
  UtlReleaseReference(LoopControl);
  UtlReleaseReference(Name);
  UtlReleaseReference(ConditionalBody);
  UtlReleaseReference(EndDoStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDoConstruct::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LoopControl != 0)
  {
    if (LblDef != 0)
    {
      LblDef->writeCPP(pOutFile, nMode);
    }

//    write(pOutFile, LoopControl->isWhileConstruct() ? " " : "for ");

    if (LblRef != 0)
    {
      pOutFile.newline();
      ::printf("ERROR: DO labels not supported on "
               "line %d in file %s\n", lineNumber(),
                                       fileName());
      AdtExit(-1);
      pOutFile.newline();
    }

    if (HasComma)
    {
      //Ignore
    }

    LoopControl->writeCPP(pOutFile, nMode);

    pOutFile.newline();
    write(pOutFile, "{");
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ConditionalBody != 0)
  {
    ConditionalBody->writeCPP(pOutFile, nMode);
  }

//  if (LoopControl != 0)
//  {
//    LoopControl->writeDelphiLoopStep(pOutFile, nMode);
//  }

  if (EndDoStmt != 0)
  {
    EndDoStmt->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDoConstruct::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LoopControl != 0)
  {
    if (LblDef != 0)
    {
      LblDef->writeDelphi(pOutFile, nMode);
    }

//    write(pOutFile, LoopControl->isWhileConstruct() ? " " : "for ");

    if (LblRef != 0)
    {
      pOutFile.newline();
      ::printf("ERROR: DO labels not supported "
               "line %d in file %s\n", lineNumber(),
                                       fileName());
      AdtExit(-1);
      pOutFile.newline();
    }

    if (HasComma)
    {
      //Ignore
    }

    LoopControl->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
    write(pOutFile, "begin");
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ConditionalBody != 0)
  {
    ConditionalBody->writeDelphi(pOutFile, nMode);
  }

//  if (LoopControl != 0)
//  {
//    LoopControl->writeDelphiLoopStep(pOutFile, nMode);
//  }

  if (EndDoStmt != 0)
  {
    EndDoStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranDoConstruct::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  write(pOutFile, "DO ");

  if (LblRef != 0)
  {
    LblRef->writeFortran(pOutFile, nMode);
  }

  if (HasComma)
  {
    write(pOutFile, ",");
  }

  if (LoopControl != 0)
  {
    LoopControl->writeFortran(pOutFile, nMode);
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ConditionalBody != 0)
  {
    ConditionalBody->writeFortran(pOutFile, nMode);
  }

  if (EndDoStmt != 0)
  {
    EndDoStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranDoConstruct, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranLoopControl method implementations
//  ----------------------------------------------------------------------------
AdtFortranLoopControl::AdtFortranLoopControl(AdtParser* pNameObj,
                                             AdtParser* pExprObj,
                                             AdtParser* pExpr2Obj,
                                             AdtParser* pExpr3Obj)
 : AdtFortranBase()
{
  initObject(Name,  pNameObj,   AdtFortranName, true);
  initObject(Expr,  pExprObj,   AdtFortranExpr, true);
  initObject(Expr2, pExpr2Obj,  AdtFortranExpr, true);
  initObject(Expr3, pExpr3Obj,  AdtFortranExpr, true);

  Expr3Sign   = 0;
  Expr3Value  = 0;

  if (Expr3 != 0)
  {
    Expr3Sign   = (AdtFortranLevel2Expr*)Expr3->findDescendant("EquivOperand,OrOperand,AndOperand,Level4Expr,Level2Expr");
    Expr3Value  = (AdtFortranIcon*)Expr3Sign->findDescendant("AddOperand,MultOperand,Primary,Icon");
  }
}

//  ----------------------------------------------------------------------------

AdtFortranLoopControl::AdtFortranLoopControl(const AdtFortranLoopControl& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Name,  rCopy,  AdtFortranName);
  copyObject(Expr,  rCopy,  AdtFortranExpr);
  copyObject(Expr2, rCopy,  AdtFortranExpr);
  copyObject(Expr3, rCopy,  AdtFortranExpr);

  Expr3Sign   = 0;
  Expr3Value  = 0;

  if (Expr3 != 0)
  {
    Expr3Sign   = (AdtFortranLevel2Expr*)Expr3->findDescendant("EquivOperand,OrOperand,AndOperand,Level4Expr,Level2Expr");
    Expr3Value  = (AdtFortranIcon*)Expr3Sign->findDescendant("AddOperand,MultOperand,Primary,Icon");
  }
}

//  ----------------------------------------------------------------------------

AdtFortranLoopControl::~AdtFortranLoopControl()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Expr);
  UtlReleaseReference(Expr2);
  UtlReleaseReference(Expr3);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLoopControl::writeDelphiLoopStep(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    bool bPlus      = true;
    bool bUnityLoop = unityloopIncrement(bPlus);

    Name->writeDelphi(pOutFile, nMode);

    write(pOutFile, " := ");

    Name->writeDelphi(pOutFile, nMode);

    if (bUnityLoop)
    {
      write(pOutFile, (bPlus ? " + " : " - "));
      write(pOutFile, "1; ");
    }
    else if (Expr3 != 0)
    {
      write(pOutFile, " + (");

      Expr3->writeDelphi(pOutFile, nMode);

      write(pOutFile, "); ");
    }

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLoopControl::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    bool    bPlus      = true;
    bool    bUnityLoop = unityloopIncrement(bPlus);
    AdtFile StringFile;
    string  sIncrement;

    StringFile.open(sIncrement);

    if (bUnityLoop)
    {
      write(StringFile, (bPlus ? "++" : "--"));
      Name->writeCPP(StringFile, nMode);
    }
    else if (Expr3 != 0)
    {
      Name->writeCPP(StringFile, nMode);
      write(StringFile, " += ");
      Expr3->writeCPP(StringFile, nMode);
    }

    StringFile.close();

    write(pOutFile, "for (");

    Name->writeCPP(pOutFile, nMode);

    write(pOutFile, " = ");

    if (Expr != 0)
    {
      Expr->writeCPP(pOutFile, nMode);
    }

    write(pOutFile, " ; ");

    Name->writeCPP(pOutFile, nMode);

    write(pOutFile, bPlus ? " <= " : " >= ");

    if (Expr2 != 0)
    {
      Expr2->writeCPP(pOutFile, nMode);
    }

    write(pOutFile, " ; ");

    write(pOutFile, sIncrement);
    write(pOutFile, ") ");
  }
  else
  {
    write(pOutFile, "while (");

    if (Expr != 0)
    {
      Expr->writeCPP(pOutFile, nMode);
    }

    write(pOutFile, ") ");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLoopControl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    bool    bPlus      = true;
    bool    bUnityLoop = unityloopIncrement(bPlus);
    AdtFile StringFile;
    string  sIncrement;

    StringFile.open(sIncrement);

    if (bUnityLoop)
    {
      write(StringFile, (bPlus ? "1" : "-1"));
    }
    else if (Expr3 != 0)
    {
      Expr3->writeDelphi(StringFile, nMode);
    }

    StringFile.close();

    Name->writeDelphi(pOutFile, nMode);

    write(pOutFile, " := ");

    if (Expr != 0)
    {
      Expr->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, " - (");
    write(pOutFile, sIncrement);
    write(pOutFile, ");");

    pOutFile.newline();

    write(pOutFile, "while add_to(");

    Name->writeDelphi(pOutFile, nMode);

    write(pOutFile, ",");
    write(pOutFile, sIncrement);
    write(pOutFile, bPlus ? ") <= " : ") >= ");

    if (Expr2 != 0)
    {
      Expr2->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, " do ");
  }
  else
  {
    write(pOutFile, "while (");

    if (Expr != 0)
    {
      Expr->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, ") do ");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLoopControl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
    write(pOutFile, " = ");
  }
  else
  {
    write(pOutFile, "WHILE (");
  }

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  if (Expr2 != 0)
  {
    write(pOutFile, ",");
    Expr2->writeFortran(pOutFile, nMode);
  }

  if (Expr3 != 0)
  {
    write(pOutFile, ",");
    Expr3->writeFortran(pOutFile, nMode);
  }

  if (Name == 0)
  {
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtFortranLoopControl::unityloopIncrement(bool& bPlus) const
{
  bool bIsUnityIncrement = false;

  if (Expr3Sign != 0)
  {
    if ((Expr3Value != 0) && (Expr3Value->name() == "1"))
    {
      bIsUnityIncrement = true;
      bPlus             = true;

      Expr3Sign->hasSignOperator(bPlus);
    }
  }
  else
  {
    bIsUnityIncrement = true;
    bPlus             = true;
  }

  return (bIsUnityIncrement);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranLoopControl, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndDoStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndDoStmt::AdtFortranEndDoStmt(AdtParser* pLblDefObj,
                                         AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  if (Name != 0)
  {
    name(Name->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranEndDoStmt::AdtFortranEndDoStmt(const AdtFortranEndDoStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);
}

//  ----------------------------------------------------------------------------

AdtFortranEndDoStmt::~AdtFortranEndDoStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndDoStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.decrementIndent();
  pOutFile.homeline();

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "}");

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndDoStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.decrementIndent();
  pOutFile.homeline();

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "end;");

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndDoStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  pOutFile.decrementIndent();
  pOutFile.homeline();

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDDO ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndDoStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCycleStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranCycleStmt::AdtFortranCycleStmt(AdtParser* pLblDefObj,
                                         AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCycleStmt::AdtFortranCycleStmt(const AdtFortranCycleStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCycleStmt::~AdtFortranCycleStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCycleStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();
  write(pOutFile, "continue;");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCycleStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();
  write(pOutFile, "continue()");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCycleStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "CYCLE ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCycleStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranExitStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranExitStmt::AdtFortranExitStmt(AdtParser* pLblDefObj,
                                       AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,    pNameObj,   AdtFortranName,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranExitStmt::AdtFortranExitStmt(const AdtFortranExitStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Name,    rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranExitStmt::~AdtFortranExitStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExitStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();
  write(pOutFile, "break;");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExitStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();
  write(pOutFile, "break()");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExitStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "EXIT ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranExitStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranGotoStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranGotoStmt::AdtFortranGotoStmt(AdtParser* pLblDefObj,
                                       AdtParser* pLblRefObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj, AdtFortranLblDef, true);
  initObject(LblRef,  pLblRefObj, AdtFortranLblRef, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranGotoStmt::AdtFortranGotoStmt(const AdtFortranGotoStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(LblRef,  rCopy,  AdtFortranLblRef);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranGotoStmt::~AdtFortranGotoStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(LblRef);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranGotoStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, "goto ");

  if (LblRef != 0)
  {
    LblRef->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranGotoStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "goto ");

  if (LblRef != 0)
  {
    LblRef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranGotoStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "GOTO ");

  if (LblRef != 0)
  {
    LblRef->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranGotoStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranArithmeticIfStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranArithmeticIfStmt::AdtFortranArithmeticIfStmt(AdtParser* pLblDefObj,
                                                       AdtParser* pExprObj,
                                                       AdtParser* pLblRefObj,
                                                       AdtParser* pLblRef2Obj,
                                                       AdtParser* pLblRef3Obj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj,   AdtFortranLblDef, true);
  initObject(Expr,    pExprObj,     AdtFortranExpr,   true);
  initObject(LblRef,  pLblRefObj,   AdtFortranLblRef, true);
  initObject(LblRef2, pLblRef2Obj,  AdtFortranLblRef, true);
  initObject(LblRef3, pLblRef3Obj,  AdtFortranLblRef, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranArithmeticIfStmt::AdtFortranArithmeticIfStmt(const AdtFortranArithmeticIfStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);
  copyObject(Expr,    rCopy,  AdtFortranExpr);
  copyObject(LblRef,  rCopy,  AdtFortranLblRef);
  copyObject(LblRef2, rCopy,  AdtFortranLblRef);
  copyObject(LblRef3, rCopy,  AdtFortranLblRef);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranArithmeticIfStmt::~AdtFortranArithmeticIfStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
  UtlReleaseReference(LblRef);
  UtlReleaseReference(LblRef2);
  UtlReleaseReference(LblRef3);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArithmeticIfStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if ((Expr    != 0) &&
      (LblRef  != 0) &&
      (LblRef2 != 0) &&
      (LblRef3 != 0))
  {
    string rComment;

    pOutFile.newline();

    translateComment(rComment, AdtParserCodeCPP, true);
    writeExpanded(pOutFile, rComment);

    if (LblDef != 0)
    {
      LblDef->writeCPP(pOutFile, nMode);
    }

    write(pOutFile, "if ((");

    Expr->writeCPP(pOutFile, nMode);

    write(pOutFile, ") < 0)");

    pOutFile.newline();

    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef->writeCPP(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");

    pOutFile.newline();

    write(pOutFile, "else if ((");

    Expr->writeCPP(pOutFile, nMode);

    write(pOutFile, ") == 0)");

    pOutFile.newline();

    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef2->writeCPP(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");

    pOutFile.newline();

    write(pOutFile, "else");

    pOutFile.newline();

    write(pOutFile, "{");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef3->writeCPP(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "}");

    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArithmeticIfStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if ((Expr    != 0) &&
      (LblRef  != 0) &&
      (LblRef2 != 0) &&
      (LblRef3 != 0))
  {
    string rComment;

    pOutFile.newline();

    translateComment(rComment, AdtParserCodeDelphi, true);
    writeExpanded(pOutFile, rComment);

    if (LblDef != 0)
    {
      LblDef->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, "if ((");

    Expr->writeDelphi(pOutFile, nMode);

    write(pOutFile, ") < 0) then");

    pOutFile.newline();

    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef->writeDelphi(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end");

    pOutFile.newline();

    write(pOutFile, "else if ((");

    Expr->writeDelphi(pOutFile, nMode);

    write(pOutFile, ") = 0) then");

    pOutFile.newline();

    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef2->writeDelphi(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end");

    pOutFile.newline();

    write(pOutFile, "else");

    pOutFile.newline();

    write(pOutFile, "begin");

    pOutFile.incrementIndent();
    pOutFile.newline();

    write(pOutFile, "goto ");

    LblRef3->writeDelphi(pOutFile, nMode);

    write(pOutFile, ";");

    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "end;");

    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranArithmeticIfStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if ((Expr    != 0) &&
      (LblRef  != 0) &&
      (LblRef2 != 0) &&
      (LblRef3 != 0))
  {
    writeExpanded(pOutFile, comment());

    if (LblDef != 0)
    {
      LblDef->writeFortran(pOutFile, nMode);
    }

    write(pOutFile, "IF (");

    Expr->writeFortran(pOutFile, nMode);

    write(pOutFile, ") ");

    LblRef->writeFortran(pOutFile, nMode);

    write(pOutFile, ",");
    LblRef2->writeFortran(pOutFile, nMode);

    write(pOutFile, ",");
    LblRef3->writeFortran(pOutFile, nMode);

    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranArithmeticIfStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranContinueStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranContinueStmt::AdtFortranContinueStmt(AdtParser* pLblDefObj)
 : AdtFortranBase()
{
  initObject(LblDef,  pLblDefObj,   AdtFortranLblDef, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranContinueStmt::AdtFortranContinueStmt(const AdtFortranContinueStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,  rCopy,  AdtFortranLblDef);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranContinueStmt::~AdtFortranContinueStmt()
{
  UtlReleaseReference(LblDef);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranContinueStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranContinueStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranContinueStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "CONTINUE ");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranContinueStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranModuleStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranModuleStmt::AdtFortranModuleStmt(AdtParser* pLblDefObj,
                                           AdtParser* pModuleNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,      pLblDefObj,     AdtFortranLblDef, true);
  initObject(ModuleName,  pModuleNameObj, AdtFortranName,   true);

  if (ModuleName != 0)
  {
    name(ModuleName->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranModuleStmt::AdtFortranModuleStmt(const AdtFortranModuleStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,      rCopy,  AdtFortranLblDef);
  copyObject(ModuleName,  rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranModuleStmt::~AdtFortranModuleStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(ModuleName);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: MODULE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: MODULE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranModuleStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "MODULE ");

  if (ModuleName != 0)
  {
    ModuleName->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranModuleStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndModuleStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndModuleStmt::AdtFortranEndModuleStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pModuleNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,      pLblDefObj,     AdtFortranLblDef, true);
  initObject(ModuleName,  pModuleNameObj, AdtFortranName,   true);

  if (ModuleName != 0)
  {
    name(ModuleName->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranEndModuleStmt::AdtFortranEndModuleStmt(const AdtFortranEndModuleStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,      rCopy,  AdtFortranLblDef);
  copyObject(ModuleName,  rCopy,  AdtFortranName);
}

//  ----------------------------------------------------------------------------

AdtFortranEndModuleStmt::~AdtFortranEndModuleStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(ModuleName);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndModuleStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: ENDMODULE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndModuleStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.newline();
  ::printf("ERROR: ENDMODULE not supported on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndModuleStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDMODULE ");

  if (ModuleName != 0)
  {
    ModuleName->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndModuleStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranUseStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranUseStmt::AdtFortranUseStmt(AdtParser* pLblDefObj,
                                     AdtParser* pNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,    pLblDefObj, AdtFortranLblDef, true);
  initObject(Name,      pNameObj,   AdtFortranName,   true);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranUseStmt::AdtFortranUseStmt(const AdtFortranUseStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,    rCopy,  AdtFortranLblDef);
  copyObject(Name,      rCopy,  AdtFortranName);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranUseStmt::~AdtFortranUseStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranUseStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranUseStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranUseStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "USE ");

  if (Name != 0)
  {
    Name->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranUseStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIntentStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranIntentStmt::AdtFortranIntentStmt(AdtParser* pLblDefObj,
                                           AdtParser* pIntentSpecObj,
                                           AdtParser* pNameListObj,
                                           bool bHasColonColon)
 : AdtFortranBase()
{
  initObject(LblDef,      pLblDefObj,     AdtFortranLblDef,     true);
  initObject(IntentSpec,  pIntentSpecObj, AdtFortranIntentSpec, true);
  initObject(NameList,    pNameListObj,   AdtFortranNameList,   true);

  HasColonColon   = bHasColonColon;
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIntentStmt::AdtFortranIntentStmt(const AdtFortranIntentStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,      rCopy,  AdtFortranLblDef);
  copyObject(IntentSpec,  rCopy,  AdtFortranIntentSpec);
  copyObject(NameList,    rCopy,  AdtFortranNameList);

  HasColonColon   = rCopy.HasColonColon;
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIntentStmt::~AdtFortranIntentStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(IntentSpec);
  UtlReleaseReference(NameList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "INTENT ");

  if (IntentSpec != 0)
  {
    IntentSpec->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " ");

  if (HasColonColon)
  {
    write(pOutFile, ":: ");
  }

  if (NameList != 0)
  {
    NameList->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIntentStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIntentSpec method implementations
//  ----------------------------------------------------------------------------
AdtFortranIntentSpec::AdtFortranIntentSpec(int nIntent)
 : AdtFortranBase()
{
  Intent = (AdtFortranIntent)nIntent;
}

//  ----------------------------------------------------------------------------

AdtFortranIntentSpec::AdtFortranIntentSpec(const AdtFortranIntentSpec& rCopy)
 : AdtFortranBase(rCopy)
{
  Intent = rCopy.Intent;
}

//  ----------------------------------------------------------------------------

AdtFortranIntentSpec::~AdtFortranIntentSpec()
{

}

//  ----------------------------------------------------------------------------

void AdtFortranIntentSpec::intent(string& rIntent) const
{
  rIntent.clear();

  switch (Intent)
  {
    case ForIntent_IN:
    {
      rIntent = "IN";
      break;
    }

    case ForIntent_OUT:
    {
      rIntent = "OUT";
      break;
    }
    
    case ForIntent_INOUT:
    default:
    {
      rIntent = "INOUT";
      break;
    }
    
    case ForIntent_IN_OUT:
    {
      rIntent = "IN OUT";
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentSpec::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentSpec::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntentSpec::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pIntent = 0;

  switch (Intent)
  {
    case ForIntent_IN:
    {
      pIntent = "(IN)";
      break;
    }

    case ForIntent_OUT:
    {
      pIntent = "(OUT)";
      break;
    }

    default:
    case ForIntent_INOUT:
    {
      pIntent = "(INOUT)";
      break;
    }

    case ForIntent_IN_OUT:
    {
      pIntent = "(IN OUT)";
      break;
    }
  }

  write(pOutFile, pIntent);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIntentSpec, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIntrinsicStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranIntrinsicStmt::AdtFortranIntrinsicStmt(AdtParser* pLblDefObj,
                                                 AdtParser* pNameListObj)
 : AdtFortranBase()
{
  initObject(LblDef,    pLblDefObj,   AdtFortranLblDef,   true);
  initObject(NameList,  pNameListObj, AdtFortranNameList, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIntrinsicStmt::AdtFortranIntrinsicStmt(const AdtFortranIntrinsicStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,    rCopy,  AdtFortranLblDef);
  copyObject(NameList,  rCopy,  AdtFortranNameList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranIntrinsicStmt::~AdtFortranIntrinsicStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(NameList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntrinsicStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntrinsicStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIntrinsicStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "INTRINSIC ");

  if (NameList != 0)
  {
    NameList->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIntrinsicStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranExternalStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranExternalStmt::AdtFortranExternalStmt(AdtParser* pLblDefObj,
                                               AdtParser* pNameListObj,
                                               bool bHasColon)
 : AdtFortranBase()
{
  initObject(LblDef,    pLblDefObj,   AdtFortranLblDef,   true);
  initObject(NameList,  pNameListObj, AdtFortranNameList, true);

  HasColon        = bHasColon;
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranExternalStmt::AdtFortranExternalStmt(const AdtFortranExternalStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,    rCopy,  AdtFortranLblDef);
  copyObject(NameList,  rCopy,  AdtFortranNameList);

  HasColon        = rCopy.HasColon;
  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranExternalStmt::~AdtFortranExternalStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(NameList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExternalStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExternalStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranExternalStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "EXTERNAL ");

  if (HasColon)
  {
    write(pOutFile, ":: ");
  }

  if (NameList != 0)
  {
    NameList->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranExternalStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranCallStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranCallStmt::AdtFortranCallStmt(AdtParser* pLblDefObj,
                                       AdtParser* pNameObj,
                                       AdtParser* pSectionSubscriptListObj)
 : AdtFortranBase()
{
  initObject(LblDef,                pLblDefObj,               AdtFortranLblDef,               true);
  initObject(Name,                  pNameObj,                 AdtFortranName,                 true);
  initObject(SectionSubscriptList,  pSectionSubscriptListObj, AdtFortranSectionSubscriptList, true);

  if (Name != 0)
  {
    name(Name->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCallStmt::AdtFortranCallStmt(const AdtFortranCallStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,                rCopy,  AdtFortranLblDef);
  copyObject(Name,                  rCopy,  AdtFortranName);
  copyObject(SectionSubscriptList,  rCopy,  AdtFortranSectionSubscriptList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranCallStmt::~AdtFortranCallStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Name);
  UtlReleaseReference(SectionSubscriptList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeCPP(pOutFile, nMode);
  }

  if (SectionSubscriptList != 0)
  {
    write(pOutFile, "(");
    SectionSubscriptList->writeCPP(pOutFile, nMode);
    write(pOutFile, ")");
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (Name != 0)
  {
    Name->writeDelphi(pOutFile, nMode);
  }

  if (SectionSubscriptList != 0)
  {
    write(pOutFile, "(");
    SectionSubscriptList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  write(pOutFile, ";");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranCallStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Name != 0)
  {
    if (LblDef != 0)
    {
      LblDef->writeFortran(pOutFile, nMode);
    }

    write(pOutFile, "CALL ");

    AdtFortranBase::writeWithChangedPrefix(pOutFile, Name->name(), false);

    if (SectionSubscriptList != 0)
    {
      write(pOutFile, "(");
      SectionSubscriptList->writeFortran(pOutFile, nMode);
      write(pOutFile, ")");
    }

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranCallStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranFunctionStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranFunctionStmt::AdtFortranFunctionStmt(AdtParser* pLblDefObj,
                                               AdtParser* pTypeSpecObj,
                                               AdtParser* pFunctionNameObj,
                                               AdtParser* pParameterListObj,
                                               bool bEmptyParameterList,
                                               bool bRecursive,
                                               AdtParser* pResultNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,        pLblDefObj,         AdtFortranLblDef,   true);
  initObject(TypeSpec,      pTypeSpecObj,       AdtFortranTypeSpec, true);
  initObject(FunctionName,  pFunctionNameObj,   AdtFortranName,     true);
  initObject(ParameterList, pParameterListObj,  AdtFortranNameList, true);
  initObject(ResultName,    pResultNameObj,     AdtFortranName,     true);

  Declarations        = 0;
  EmptyParameterList  = bEmptyParameterList;
  Recursive           = bRecursive;
  IsVirtual           = false;

  if (FunctionName != 0)
  {
    name(FunctionName->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranFunctionStmt::AdtFortranFunctionStmt(const AdtFortranFunctionStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,        rCopy, AdtFortranLblDef);
  copyObject(TypeSpec,      rCopy, AdtFortranTypeSpec);
  copyObject(FunctionName,  rCopy, AdtFortranName);
  copyObject(ParameterList, rCopy, AdtFortranNameList);
  copyObject(ResultName,    rCopy, AdtFortranName);

  Declarations        = 0;
  EmptyParameterList  = rCopy.EmptyParameterList;
  Recursive           = rCopy.Recursive;
  IsVirtual           = rCopy.IsVirtual;
  CanBindComments     = true;
}

//  ----------------------------------------------------------------------------

AdtFortranFunctionStmt::~AdtFortranFunctionStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(TypeSpec);
  UtlReleaseReference(FunctionName);
  UtlReleaseReference(ParameterList);
  UtlReleaseReference(ResultName);
  UtlReleaseReference(Declarations);
}

//  ----------------------------------------------------------------------------

void AdtFortranFunctionStmt::initialise(AdtParserPtrByStringMap* pFunctionMap)
{
  UtlReleaseReference(Declarations);

  if (Parent != 0)
  {
    AdtParser* pBodyObj = Parent->findDescendant("Body");

    if ((pBodyObj     != 0) &&
        (FunctionName != 0))
    {

      // Make a copy of pFunctionMap, remove any elements that match the
      // elements in the arg list, add any externals, then remove all those
      // from matching type declaration statements. This ensures that when
      // translating into C++ or Delphi the externals are treated as functions
      // and not variables.
      AdtParserPtrListConstIter Iter;
      AdtParserPtrByStringMap   rExternalsMap(*pFunctionMap);

      if (ParameterList != 0)
      {
        for (Iter = ParameterList->objList().begin() ; Iter != ParameterList->objList().end() ; ++Iter)
        {
          AdtParser* pObj = *Iter;

          if (pObj != 0)
          {
            rExternalsMap.erase(pObj->name());
          }
        }
      }

      pBodyObj->enumerateDescendantMap(rExternalsMap, "AdtFortranBodyConstruct,SpecificationPartConstruct,ExternalStmt,NameList");

      if (rExternalsMap.size() > 0)
      {
        AdtParserPtrList  rTypeDeclarationStmtList;

        pBodyObj->enumerateDescendantList(rTypeDeclarationStmtList, "AdtFortranBodyConstruct,SpecificationPartConstruct,TypeDeclarationStmt");

        for (Iter = rTypeDeclarationStmtList.begin() ; Iter != rTypeDeclarationStmtList.end() ; ++Iter)
        {
          AdtParser* pObj = *Iter;

          if ((pObj != 0) && pObj->isType("AdtFortranTypeDeclarationStmt"))
          {
            AdtFortranTypeDeclarationStmt* pTypeDeclarationStmt = (AdtFortranTypeDeclarationStmt*)pObj;

            pTypeDeclarationStmt->removeExternals(rExternalsMap);
          }
        }

        rTypeDeclarationStmtList.clear();
      }

      rExternalsMap.clear();

      if (ResultName != 0)
      {
        // If ResultName != 0 then we need to find the type declaration for
        // ResultName and remove it from the function body, use the type to make a
        // TypeSpec instance for the function and then replace all name instances
        // of ResultName with FunctionName. That changes the function declaration
        // from new style to old style, which is easier to convert to Delphi or C++.
        AdtParserPtrList      rNameList;

        pBodyObj->findObjects(rNameList,
                              "AdtFortranName",
                              ResultName->name(),
                              false);

        for (Iter = rNameList.begin() ; Iter != rNameList.end() ; ++Iter)
        {
          AdtParser* pObj = *Iter;

          if (pObj != 0)
          {
            if ((pObj->parent()            != 0) &&
                (pObj->parent()->parent()  != 0) &&
                (pObj->findAscendantWithClassLineage("AdtFortranEntityDecl,"
                                                     "AdtFortranEntityDeclList,"
                                                     "AdtFortranTypeDeclarationStmt,"
                                                     "AdtFortranSpecificationPartConstruct") != 0))
            {
              AdtParser*  pTypeDeclStmt = pObj->findAscendantWithClass("AdtFortranTypeDeclarationStmt");
              AdtParser*  pTypeSpecObj  = pTypeDeclStmt->findDescendant("TypeSpec");

              UtlReleaseReference(TypeSpec);

              // Add return type spec
              initObject(TypeSpec, pTypeSpecObj->copy(), AdtFortranTypeSpec, true);

              // Remove type declaration
              pObj->parent()->parent()->remove(pObj->parent());
            }

            // Change symbol name
            pObj->name(FunctionName->name());
          }
        }

        // Remove result name
        UtlReleaseReference(ResultName);
        ResultName = 0;
      }
    }

    Declarations = new AdtFortranDeclarations(this, pBodyObj, ParameterList, pFunctionMap);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeCPP_Initialisations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    if (TypeSpec != 0)
    {
      TypeSpec->writeCPP(pOutFile, 0);
    }
    else if (Declarations != 0)
    {
      //Need to search for the typedef corresponding to the function name.
      Declarations->writeCPP_ReturnType(pOutFile, FunctionName->name());
    }

    write(pOutFile, "ret_");
    FunctionName->writeCPP(pOutFile, 0);
    write(pOutFile, ";");
    pOutFile.newline();

    Declarations->writeCPP_Initialisations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeCPP_Allocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeCPP_Allocations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeCPP_Deallocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeCPP_Deallocations(pOutFile);

    pOutFile.newline();
    write(pOutFile, "return (ret_");
    FunctionName->writeCPP(pOutFile, 0);
    write(pOutFile, ");");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeDelphiInitialisations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiInitialisations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeDelphiAllocations(AdtFile& pOutFile,
                                                        AdtStringList* pVarList,
                                                        AdtStringList* pDestroyList) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiAllocations(pOutFile, pVarList, pDestroyList);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeDelphiDeallocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiDeallocations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if (ResultName != 0)
  {
    // Should never happen as we replace RESULT with function name return type.
    pOutFile.newline();
    ::printf("ERROR: RESULT not supported on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
    pOutFile.newline();
  }

  if ((IsVirtual) && (nMode == CPP_MODE_FUNCTION_DECLARATION))
  {
    write(pOutFile, "virtual ");
  }

  if (TypeSpec != 0)
  {
    TypeSpec->writeCPP(pOutFile, nMode);
  }
  else if (Declarations != 0)
  {
    //Need to search for the typedef corresponding to the function name.
    Declarations->writeCPP_ReturnType(pOutFile, FunctionName->name());
  }

  if (FunctionName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, FunctionName->name(), true, true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else if (Declarations != 0)
  {
    write(pOutFile, "(");
    Declarations->writeCPP_ParameterList(pOutFile);
    write(pOutFile, ")");
  }

  if (nMode == CPP_MODE_FUNCTION_DECLARATION)
  {
    write(pOutFile, ";");
    pOutFile.newline();
  }
  else
  {
    pOutFile.newline();
    write(pOutFile, "{");
    pOutFile.incrementIndent();
    pOutFile.newline();

    if (Declarations)
    {
      Declarations->writeCPP_Declarations(pOutFile);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "function ");

  if (FunctionName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, FunctionName->name(), true, true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else if (Declarations != 0)
  {
    write(pOutFile, "(");
    Declarations->writeDelphiParameterList(pOutFile);
    write(pOutFile, ")");
  }

  if (ResultName != 0)
  {
    // Should never happen as we replace RESULT with function name return type.
    pOutFile.newline();
    ::printf("ERROR: RESULT not supported on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
    pOutFile.newline();
  }

  if (TypeSpec != 0)
  {
    write(pOutFile, " : ");
    TypeSpec->writeDelphi(pOutFile, nMode);
  }
  else if (Declarations != 0)
  {
    //Need to search for the typedef corresponding to the function name.
    Declarations->writeDelphiReturnType(pOutFile, FunctionName->name());
  }

  write(pOutFile, ";");

  if ((IsVirtual) && (nMode == DELPHI_MODE_FUNCTION_DECLARATION))
  {
    write(pOutFile, " override;");
  }

  pOutFile.newline();

  if (nMode != DELPHI_MODE_FUNCTION_DECLARATION)
  {
    if (Declarations)
    {
      Declarations->writeDelphiDeclarations(pOutFile);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranFunctionStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Recursive)
  {
    write(pOutFile, "RECURSIVE ");
  }

  if (TypeSpec != 0)
  {
    TypeSpec->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "FUNCTION ");

  if (FunctionName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, FunctionName->name(), true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else
  {
    if (ParameterList != 0)
    {
      write(pOutFile, "(");
      ParameterList->writeFortran(pOutFile, nMode);
      write(pOutFile, ")");
    }
  }

  if (ResultName != 0)
  {
    // Should never happen as we replace RESULT with function name return type.
    write(pOutFile, "RESULT (");
    AdtFortranBase::writeWithChangedPrefix(pOutFile, ResultName->name(), true);
    write(pOutFile, ")");
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranFunctionStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranLblRef method implementations
//  ----------------------------------------------------------------------------
AdtFortranLblRef::AdtFortranLblRef(const char* pIcon)
 : AdtFortranBase()
{
  name(pIcon);
}

//  ----------------------------------------------------------------------------

AdtFortranLblRef::AdtFortranLblRef(const AdtFortranLblRef& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranLblRef::~AdtFortranLblRef()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblRef::writeCPP(AdtFile& pOutFile, int nMode) const
{
  if (name().length() > 0)
  {
    write(pOutFile, "L");
    write(pOutFile, name().c_str());
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblRef::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  if (name().length() > 0)
  {
    write(pOutFile, "L");
    write(pOutFile, name().c_str());
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblRef::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranLblRef, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranName method implementations
//  ----------------------------------------------------------------------------
AdtFile& AdtFortranName::writeChanged(AdtFile& pOutFile, int nMode) const
{
  if ((FindString != 0) && (ReplaceString != 0) && (caseless_string_comparison(name(), FindString) == 0))
  {
    write(pOutFile, ReplaceString);
  }
  else if (PrefixString != 0)
  {
    int     nStart  = 0;
    int     nLength = 0;
    string  sName(name());

    if (AdtParser::hasSubString(sName,
                                PrefixString,
                                nStart,
                                nLength,
                                false) && (nStart == 0))
    {
      const char* pName = sName;

      write(pOutFile, pName + nLength);
    }
    else
    {
      write(pOutFile, name().c_str());
    }
  }
  else
  {
    write(pOutFile, name().c_str());
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFortranName::AdtFortranName(const char* pIdent)
 : AdtFortranBase()
{
  name(pIdent);
}

//  ----------------------------------------------------------------------------

AdtFortranName::AdtFortranName(const AdtFortranName& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranName::~AdtFortranName()
{

}

//  ----------------------------------------------------------------------------

void AdtFortranName::setClearPrefix(const char* pPrefixString)
{
  PrefixString = pPrefixString;
}

//  ----------------------------------------------------------------------------

void AdtFortranName::setSubstitute(const char* pFind, const char* pReplace)
{
  FindString    = pFind;
  ReplaceString = pReplace;
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranName::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (writeChanged(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranName::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (writeChanged(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranName::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranName, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranNameList method implementations
//  ----------------------------------------------------------------------------
AdtFortranNameList::AdtFortranNameList(AdtParser* pNameObj)
 : AdtFortranBase()
{
  add(pNameObj);
}

//  ----------------------------------------------------------------------------

AdtFortranNameList::AdtFortranNameList(const AdtFortranNameList& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranNameList::~AdtFortranNameList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNameList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNameList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranNameList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranNameList, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndFunctionStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndFunctionStmt::AdtFortranEndFunctionStmt(AdtParser* pLblDefObj,
                                                     AdtParser* pFunctionNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,        pLblDefObj,         AdtFortranLblDef,   true);
  initObject(FunctionName,  pFunctionNameObj,   AdtFortranName,     true);

  if (FunctionName != 0)
  {
    name(FunctionName->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranEndFunctionStmt::AdtFortranEndFunctionStmt(const AdtFortranEndFunctionStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,        rCopy, AdtFortranLblDef);
  copyObject(FunctionName,  rCopy, AdtFortranName);
}

//  ----------------------------------------------------------------------------

AdtFortranEndFunctionStmt::~AdtFortranEndFunctionStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(FunctionName);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndFunctionStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndFunctionStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndFunctionStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDFUNCTION ");

  if (FunctionName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, FunctionName->name(), true);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndFunctionStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranSubroutineStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranSubroutineStmt::AdtFortranSubroutineStmt(AdtParser* pLblDefObj,
                                                   AdtParser* pSubroutineNameObj,
                                                   AdtParser* pParameterListObj,
                                                   bool bEmptyParameterList,
                                                   bool bRecursive)
 : AdtFortranBase()
{
  initObject(LblDef,          pLblDefObj,         AdtFortranLblDef,   true);
  initObject(SubroutineName,  pSubroutineNameObj, AdtFortranName,     true);
  initObject(ParameterList,   pParameterListObj,  AdtFortranNameList, true);

  Declarations        = 0;
  EmptyParameterList  = bEmptyParameterList;
  Recursive           = bRecursive;
  IsVirtual           = false;

  if (SubroutineName != 0)
  {
    name(SubroutineName->name());
  }

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranSubroutineStmt::AdtFortranSubroutineStmt(const AdtFortranSubroutineStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,          rCopy, AdtFortranLblDef);
  copyObject(SubroutineName,  rCopy, AdtFortranName);
  copyObject(ParameterList,   rCopy, AdtFortranNameList);

  Declarations        = 0;
  EmptyParameterList  = rCopy.EmptyParameterList;
  Recursive           = rCopy.Recursive;
  IsVirtual           = rCopy.IsVirtual;
  CanBindComments     = true;
}

//  ----------------------------------------------------------------------------

AdtFortranSubroutineStmt::~AdtFortranSubroutineStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(SubroutineName);
  UtlReleaseReference(ParameterList);
  UtlReleaseReference(Declarations);
}

//  ----------------------------------------------------------------------------

void AdtFortranSubroutineStmt::initialise(AdtParserPtrByStringMap* pFunctionMap)
{
  UtlReleaseReference(Declarations);

  if (Parent != 0)
  {
    AdtParser* pBodyObj = Parent->findDescendant("Body");

    if (pBodyObj != 0)
    {
      AdtParserPtrByStringMap rExternalsMap;
      AdtParserPtrListIter    Iter;
      bool                    bHasExternalsMap = false;
      bool                    bHasFunctionMap  = false;

      // Enumerate externals and remove them from the type declarations. We need to
      // do this so that when translating into C++ or Delphi the externals are
      // treated as functions and not variables.
      pBodyObj->enumerateDescendantMap(rExternalsMap, "AdtFortranBodyConstruct,SpecificationPartConstruct,ExternalStmt,NameList");

      if (rExternalsMap.size() > 0)
      {
        bHasExternalsMap = true;
      }

      if ((pFunctionMap != 0) && (pFunctionMap->size() > 0))
      {
        bHasFunctionMap = true;
      }

      if (bHasExternalsMap || bHasFunctionMap)
      {
        AdtParserPtrList  rTypeDeclarationStmtList;

        pBodyObj->enumerateDescendantList(rTypeDeclarationStmtList, "AdtFortranBodyConstruct,SpecificationPartConstruct,TypeDeclarationStmt");

        for (Iter = rTypeDeclarationStmtList.begin() ; Iter != rTypeDeclarationStmtList.end() ; ++Iter)
        {
          AdtParser* pObj = *Iter;

          if ((pObj != 0) && pObj->isType("AdtFortranTypeDeclarationStmt"))
          {
            AdtFortranTypeDeclarationStmt* pTypeDeclarationStmt = (AdtFortranTypeDeclarationStmt*)pObj;

            if (bHasExternalsMap)
            {
              pTypeDeclarationStmt->removeExternals(rExternalsMap);
            }

//            if (bHasFunctionMap)
//            {
// Why is this here? Presumably this has something do do withreturn types.
//              pTypeDeclarationStmt->removeExternals(*pFunctionMap);
//            }
          }
        }

        rTypeDeclarationStmtList.clear();
      }

      rExternalsMap.clear();
    }

    Declarations  = new AdtFortranDeclarations(this, Parent->findDescendant("Body"), ParameterList, pFunctionMap);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeCPP_Initialisations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeCPP_Initialisations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeCPP_Allocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeCPP_Allocations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeCPP_Deallocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeCPP_Deallocations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeDelphiInitialisations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiInitialisations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeDelphiAllocations(AdtFile& pOutFile,
                                                          AdtStringList* pVarList,
                                                          AdtStringList* pDestroyList) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiAllocations(pOutFile, pVarList, pDestroyList);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeDelphiDeallocations(AdtFile& pOutFile) const
{
  if (Declarations != 0)
  {
    Declarations->writeDelphiDeallocations(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeCPP(pOutFile, nMode);
  }

  if ((IsVirtual) && (nMode == CPP_MODE_FUNCTION_DECLARATION))
  {
    write(pOutFile, "virtual ");
  }

  write(pOutFile, "void ");

  if (SubroutineName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, SubroutineName->name(), true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else if (Declarations != 0)
  {
    write(pOutFile, "(");
    Declarations->writeCPP_ParameterList(pOutFile);
    write(pOutFile, ")");
  }

  if (nMode == CPP_MODE_FUNCTION_DECLARATION)
  {
    write(pOutFile, ";");
    pOutFile.newline();
  }
  else
  {
    pOutFile.newline();
    write(pOutFile, "{");
    pOutFile.incrementIndent();
    pOutFile.newline();

    if (Declarations)
    {
      Declarations->writeCPP_Declarations(pOutFile);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "procedure ");

  if (SubroutineName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, SubroutineName->name(), true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else if (Declarations != 0)
  {
    write(pOutFile, "(");
    Declarations->writeDelphiParameterList(pOutFile);
    write(pOutFile, ")");
  }

  write(pOutFile, ";");

  if (IsVirtual)
  {
    write(pOutFile, " override;");
  }

  pOutFile.newline();

  if (nMode != DELPHI_MODE_FUNCTION_DECLARATION)
  {
    if (Declarations)
    {
      Declarations->writeDelphiDeclarations(pOutFile);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranSubroutineStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  if (Recursive)
  {
    write(pOutFile, "RECURSIVE ");
  }

  write(pOutFile, "SUBROUTINE ");

  if (SubroutineName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, SubroutineName->name(), true);
  }

  if (EmptyParameterList)
  {
    write(pOutFile, "()");
  }
  else
  {
    if (ParameterList != 0)
    {
      write(pOutFile, "(");
      ParameterList->writeFortran(pOutFile, nMode);
      write(pOutFile, ")");
    }
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranSubroutineStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranEndSubroutineStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranEndSubroutineStmt::AdtFortranEndSubroutineStmt(AdtParser* pLblDefObj,
                                                         AdtParser* pSubroutineNameObj)
 : AdtFortranBase()
{
  initObject(LblDef,          pLblDefObj,         AdtFortranLblDef,   true);
  initObject(SubroutineName,  pSubroutineNameObj, AdtFortranName,     true);

  if (SubroutineName != 0)
  {
    name(SubroutineName->name());
  }
}

//  ----------------------------------------------------------------------------

AdtFortranEndSubroutineStmt::AdtFortranEndSubroutineStmt(const AdtFortranEndSubroutineStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,          rCopy, AdtFortranLblDef);
  copyObject(SubroutineName,  rCopy, AdtFortranName);
}

//  ----------------------------------------------------------------------------

AdtFortranEndSubroutineStmt::~AdtFortranEndSubroutineStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(SubroutineName);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSubroutineStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSubroutineStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranEndSubroutineStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "ENDSUBROUTINE ");

  if (SubroutineName != 0)
  {
    AdtFortranBase::writeWithChangedPrefix(pOutFile, SubroutineName->name(), true);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranEndSubroutineStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranReturnStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranReturnStmt::AdtFortranReturnStmt(AdtParser* pLblDefObj,
                                           AdtParser* pExprObj)
 : AdtFortranBase()
{
  initObject(LblDef,    pLblDefObj,   AdtFortranLblDef, true);
  initObject(Expr,      pExprObj,     AdtFortranExpr,   true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranReturnStmt::AdtFortranReturnStmt(const AdtFortranReturnStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,    rCopy, AdtFortranLblDef);
  copyObject(Expr,      rCopy, AdtFortranExpr);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranReturnStmt::~AdtFortranReturnStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(Expr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranReturnStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if ((LblDef != 0) && !LblDef->isEmpty())
  {
    ::printf("ERROR: FORTRAN labelled return lost in translation to C++ on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }

  if (Expr != 0)
  {
    ::printf("ERROR: FORTRAN alternate return points can't be translated on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranReturnStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  pOutFile.newline();

  if (LblDef != 0)
  {
    LblDef->writeDelphi(pOutFile, nMode);
  }

  if (Expr != 0)
  {
    ::printf("ERROR: FORTRAN alternate return points can't be translated on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }

  write(pOutFile, "exit;");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranReturnStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "RETURN ");

  if (Expr != 0)
  {
    Expr->writeFortran(pOutFile, nMode);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranReturnStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranLblDef method implementations
//  ----------------------------------------------------------------------------
AdtFortranLblDef::AdtFortranLblDef(AdtParser* pIconObj)
 : AdtFortranBase()
{
  initObject(Icon,  pIconObj, AdtFortranIcon, true);
}

//  ----------------------------------------------------------------------------

AdtFortranLblDef::AdtFortranLblDef(const AdtFortranLblDef& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(Icon,  rCopy, AdtFortranIcon);
}

//  ----------------------------------------------------------------------------

AdtFortranLblDef::~AdtFortranLblDef()
{
  UtlReleaseReference(Icon);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblDef::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  if ((Icon != 0) && (Icon->name().length() > 0))
  {
    pOutFile.newline();

    write(pOutFile, "L");
    Icon->writeFortran(pOutFile);

    write(pOutFile, ":");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblDef::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  if ((Icon != 0) && (Icon->name().length() > 0))
  {
    pOutFile.newline();

    write(pOutFile, "L");
    Icon->writeFortran(pOutFile);

    write(pOutFile, ":");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranLblDef::writeFortran(AdtFile& pOutFile, int nMode) const
{
  if (Icon != 0)
  {
    Icon->writeFortran(pOutFile, nMode);
    write(pOutFile, " ");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranLblDef, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranImplicitStmt method implementations
//  ----------------------------------------------------------------------------
AdtFortranImplicitStmt::AdtFortranImplicitStmt(AdtParser* pLblDefObj,
                                               AdtParser* pImplicitSpecListObj)
 : AdtFortranBase()
{
  initObject(LblDef,            pLblDefObj,           AdtFortranLblDef,           true);
  initObject(ImplicitSpecList,  pImplicitSpecListObj, AdtFortranImplicitSpecList, true);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranImplicitStmt::AdtFortranImplicitStmt(const AdtFortranImplicitStmt& rCopy)
 : AdtFortranBase(rCopy)
{
  copyObject(LblDef,            rCopy, AdtFortranLblDef);
  copyObject(ImplicitSpecList,  rCopy, AdtFortranImplicitSpecList);

  CanBindComments = true;
}

//  ----------------------------------------------------------------------------

AdtFortranImplicitStmt::~AdtFortranImplicitStmt()
{
  UtlReleaseReference(LblDef);
  UtlReleaseReference(ImplicitSpecList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitStmt::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeCPP, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  string rComment;

  translateComment(rComment, AdtParserCodeDelphi, true);
  writeExpanded(pOutFile, rComment);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImplicitStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LblDef != 0)
  {
    LblDef->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, "IMPLICIT ");

  if (ImplicitSpecList != 0)
  {
    ImplicitSpecList->writeFortran(pOutFile, nMode);
  }
  else
  {
    write(pOutFile, "NONE");
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranImplicitStmt, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranIcon method implementations
//  ----------------------------------------------------------------------------
AdtFortranIcon::AdtFortranIcon(const char* pIcon)
 : AdtFortranBase(),
   Size()
{
  string sNumber;

  splitNumericConstant(sNumber, Size, pIcon);
  name(sNumber);
}

//  ----------------------------------------------------------------------------

AdtFortranIcon::AdtFortranIcon(const AdtFortranIcon& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranIcon::~AdtFortranIcon()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIcon::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIcon::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranIcon::writeFortran(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  if (Size.length() > 0)
  {
    pOutFile.write("_");
    pOutFile.write(Size);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranIcon, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranRcon method implementations
//  ----------------------------------------------------------------------------
AdtFortranRcon::AdtFortranRcon(const char* pRcon)
 : AdtFortranBase(),
   Size()
{
  string sNumber;

  splitNumericConstant(sNumber, Size, pRcon);
  name(sNumber);
}

//  ----------------------------------------------------------------------------

AdtFortranRcon::AdtFortranRcon(const AdtFortranRcon& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranRcon::~AdtFortranRcon()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRcon::writeCPP(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRcon::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranRcon::writeFortran(AdtFile& pOutFile, int nMode) const
{
  pOutFile.write(name());

  if (Size.length() > 0)
  {
    pOutFile.write("_");
    pOutFile.write(Size);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtFortranRcon, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranScon method implementations
//  ----------------------------------------------------------------------------
AdtFortranScon::AdtFortranScon(const char* pScon)
 : AdtFortranBase()
{
  name(pScon);
}

//  ----------------------------------------------------------------------------

AdtFortranScon::AdtFortranScon(const AdtFortranScon& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranScon::~AdtFortranScon()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranScon::writeCPP(AdtFile& pOutFile, int nMode) const
{
  string  rString(name());

  rString.trim("'");

  write(pOutFile, "\"");
  write(pOutFile, rString);
  write(pOutFile, "\"");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranScon::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranScon::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranScon, AdtFortranBase);


//  ----------------------------------------------------------------------------
//  AdtFortranImpl method implementations
//  ----------------------------------------------------------------------------
AdtFortranImpl::AdtFortranImpl(const char* pImpl)
 : AdtFortranBase()
{
  name(pImpl);
}

//  ----------------------------------------------------------------------------

AdtFortranImpl::AdtFortranImpl(const AdtFortranImpl& rCopy)
 : AdtFortranBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtFortranImpl::~AdtFortranImpl()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImpl::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImpl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtFortranImpl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

implType(AdtFortranImpl, AdtFortranBase);
