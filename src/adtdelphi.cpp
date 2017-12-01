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
//    AdtDelphi.cpp
//
//  Purpose:
//    This file includes implementation of classes used to collate information
//    describing the delphi file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtdelphi.hpp"
#include "adtautomate.hpp"
#include "adtexpression.hpp"
#include <sys/stat.h>


//  ----------------------------------------------------------------------------
//  Defines
//  ----------------------------------------------------------------------------
#define FORTRAN_MODE_CLASS_EXTEND_NAME  10
#define FORTRAN_MODE_ARRAY_SLICE        11


//  ----------------------------------------------------------------------------
//  Globals
//  ----------------------------------------------------------------------------
const char*                                  AdtDelphiBase::TypeScope         = 0;
AdtDelphiGoal*                               AdtDelphiBase::DelphiRootObject  = 0;
AdtDelphiToFortranTypeConversionByStringMap  AdtDelphiBase::FortranTypeMap;
AdtDelphiToFortranTypeConversionByStringMap  AdtDelphiBase::DelphiTypeMap;
AdtVisibility                                AdtDelphiClassType::GlobalVisibility = AdtVisibility_PUBLIC;


//  ----------------------------------------------------------------------------
//  "C" callable function implementations
//  ----------------------------------------------------------------------------
void adtDelphi_setTypeScope(void* pIdent)
{
  AdtDelphiBase::typeScope(Obj(pIdent));
}

//  ----------------------------------------------------------------------------

void adtDelphi_clearTypeScope()
{
  AdtDelphiBase::typeScope(0);
}

//  ----------------------------------------------------------------------------

void* adtDelphi_setRoot(void* pRoot)
{
  AdtDelphiBase::delphiRootObject(Obj(pRoot));

  return (pRoot);
}

//  ----------------------------------------------------------------------------

void* adtDelphi_getRoot(void)
{
  return (Hnd(AdtDelphiBase::delphiRootObject()));
}

//  ----------------------------------------------------------------------------

void adtDelphi_releaseRoot(void)
{
  AdtDelphiBase::delphiRootObject(0);
}

//  ----------------------------------------------------------------------------

void adtDelphi_releaseObject(void* pObj)
{
  UtlReleaseReference(Obj(pObj));
}

//  ----------------------------------------------------------------------------

void* adtDelphiList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtDelphiGoal_create(void* pObj)
{
  return (Hnd(new AdtDelphiGoal(ObjAndRelease(pObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiMacro_create(void* pIdentObj, void* pExprListObj, void* pExpressionObj, void* pStmtListObj, void* pVarDeclListObj)
{
  return (Hnd(new AdtDelphiMacro(ObjAndRelease(pIdentObj), ObjAndRelease(pExprListObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pStmtListObj), ObjAndRelease(pVarDeclListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProgram_create(void* pIdentObj, void* pIdentListObj, void* pUsesClauseObj, void* pBlockObj, const char* pComment)
{
  return (Hnd(new AdtDelphiProgram(ObjAndRelease(pIdentObj), ObjAndRelease(pIdentListObj), ObjAndRelease(pUsesClauseObj), ObjAndRelease(pBlockObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiUnit_create(void* pIdentObj, void* pInterfaceSectionObj, void* pImplementationSectionObj, void* pInitSectionObj, const char* pComment)
{
  return (Hnd(new AdtDelphiUnit(ObjAndRelease(pIdentObj), ObjAndRelease(pInterfaceSectionObj), ObjAndRelease(pImplementationSectionObj), ObjAndRelease(pInitSectionObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiPackage_create(void* pIdentObj, void* pRequiresIdentListObj, void* pContainsIdentListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiPackage(ObjAndRelease(pIdentObj), ObjAndRelease(pRequiresIdentListObj), ObjAndRelease(pContainsIdentListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiLibrary_create(void* pIdentObj, void* pUsesClauseObj, void* pBlockObj, const char* pComment)
{
  return (Hnd(new AdtDelphiLibrary(ObjAndRelease(pIdentObj), ObjAndRelease(pUsesClauseObj), ObjAndRelease(pBlockObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiUsesClause_create(void* pIdentListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiUsesClause(ObjAndRelease(pIdentListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiInterfaceSection_create(void* pUsesClauseObj, void* pConstSectionObj, void* pTypeSectionObj, void* pVarSectionObj, void* pExportedHeadingListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiInterfaceSection(ObjAndRelease(pUsesClauseObj), ObjAndRelease(pConstSectionObj), ObjAndRelease(pTypeSectionObj), ObjAndRelease(pVarSectionObj), ObjAndRelease(pExportedHeadingListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExportedHeadingList_create(void* pExportedHeadingObj)
{
  return (Hnd(new AdtDelphiExportedHeadingList(ObjAndRelease(pExportedHeadingObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExportedHeading_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pDirectiveListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiExportedHeading(ObjAndRelease(pProcedureHeadingObj), ObjAndRelease(pFunctionHeadingObj), ObjAndRelease(pDirectiveListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiImplementationSection_create(void* pUsesClauseObj, void* pDeclSectionObj, const char* pComment)
{
  return (Hnd(new AdtDelphiImplementationSection(ObjAndRelease(pUsesClauseObj), ObjAndRelease(pDeclSectionObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiBlock_create(void* pDeclSectionObj, void* pCompoundStmtObj, const char* pComment)
{
  return (Hnd(new AdtDelphiBlock(ObjAndRelease(pDeclSectionObj), ObjAndRelease(pCompoundStmtObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDeclSection_create(void* pLabelDeclSectionObj, void* pConstSectionObj, void* pTypeSectionObj, void* pVarSectionObj, void* pProcedureDeclSectionObj, const char* pComment)
{
  return (Hnd(new AdtDelphiDeclSection(ObjAndRelease(pLabelDeclSectionObj), ObjAndRelease(pConstSectionObj), ObjAndRelease(pTypeSectionObj), ObjAndRelease(pVarSectionObj), ObjAndRelease(pProcedureDeclSectionObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiLabelDeclSection_create(void* pLabelDeclListObj)
{
  return (Hnd(new AdtDelphiLabelDeclSection(ObjAndRelease(pLabelDeclListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiLabelDeclList_create(void* pLabelDeclObj)
{
  return (Hnd(new AdtDelphiLabelDeclList(ObjAndRelease(pLabelDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiLabelDecl_create(void* pLabelIdObj, const char* pComment)
{
  return (Hnd(new AdtDelphiLabelDecl(ObjAndRelease(pLabelIdObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstSection_create(void* pConstantDeclListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiConstSection(ObjAndRelease(pConstantDeclListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstantDeclList_create(void* pConstantDeclObj)
{
  return (Hnd(new AdtDelphiConstantDeclList(ObjAndRelease(pConstantDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstantDecl_create(void* pIdentObj, void* pTypeIdObj, void* pUnitIdObj, void* pConstExprObj, void* pTypedConstantObj)
{
  return (Hnd(new AdtDelphiConstantDecl(ObjAndRelease(pIdentObj), ObjAndRelease(pTypeIdObj), ObjAndRelease(pUnitIdObj), ObjAndRelease(pConstExprObj), ObjAndRelease(pTypedConstantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypeSection_create(void* pTypeDeclListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiTypeSection(ObjAndRelease(pTypeDeclListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypeDeclList_create(void* pTypeDeclObj)
{
  return (Hnd(new AdtDelphiTypeDeclList(ObjAndRelease(pTypeDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypeDecl_create(void* pIdentObj, void* pTypeObj, void* pRestrictedTypeObj)
{
  return (Hnd(new AdtDelphiTypeDecl(ObjAndRelease(pIdentObj), ObjAndRelease(pTypeObj), ObjAndRelease(pRestrictedTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypedConstant_create(void* pConstExprObj, void* pArrayConstantObj, void* pRecordConstantObj)
{
  return (Hnd(new AdtDelphiTypedConstant(ObjAndRelease(pConstExprObj), ObjAndRelease(pArrayConstantObj), ObjAndRelease(pRecordConstantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiArrayConstant_create(void* pTypedConstantListObj)
{
  return (Hnd(new AdtDelphiArrayConstant(ObjAndRelease(pTypedConstantListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypedConstantList_create(void* pTypedConstantObj)
{
  return (Hnd(new AdtDelphiTypedConstantList(ObjAndRelease(pTypedConstantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRecordConstant_create(void* pRecordFieldConstantListObj)
{
  return (Hnd(new AdtDelphiRecordConstant(ObjAndRelease(pRecordFieldConstantListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRecordFieldConstantList_create(void* pRecordFieldConstantObj)
{
  return (Hnd(new AdtDelphiRecordFieldConstantList(ObjAndRelease(pRecordFieldConstantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRecordFieldConstant_create(void* pIdentObj, void* pTypedConstantObj)
{
  return (Hnd(new AdtDelphiRecordFieldConstant(ObjAndRelease(pIdentObj), ObjAndRelease(pTypedConstantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiType_create(void* pTypeIdObj, void* pUnitIdObj, void* pSimpleTypeObj, void* pStructTypeObj, void* pPointerTypeObj, void* pStringTypeObj, void* pProcedureTypeObj, void* pVariantTypeObj, void* pClassRefTypeObj)
{
  return (Hnd(new AdtDelphiType(ObjAndRelease(pTypeIdObj), ObjAndRelease(pUnitIdObj), ObjAndRelease(pSimpleTypeObj), ObjAndRelease(pStructTypeObj), ObjAndRelease(pPointerTypeObj), ObjAndRelease(pStringTypeObj), ObjAndRelease(pProcedureTypeObj), ObjAndRelease(pVariantTypeObj), ObjAndRelease(pClassRefTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRestrictedType_create(void* pObjectTypeObj, void* pClassTypeObj, void* pInterfaceTypeObj)
{
  return (Hnd(new AdtDelphiRestrictedType(ObjAndRelease(pObjectTypeObj), ObjAndRelease(pClassTypeObj), ObjAndRelease(pInterfaceTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassRefType_create(void* pTypeIdObj, void* pUnitIdObj)
{
  return (Hnd(new AdtDelphiClassRefType(ObjAndRelease(pTypeIdObj), ObjAndRelease(pUnitIdObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSimpleType_create(void* pOrdinalTypeObj, void* pRealTypeObj)
{
  return (Hnd(new AdtDelphiSimpleType(ObjAndRelease(pOrdinalTypeObj), ObjAndRelease(pRealTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRealType_create(int nType)
{
  return (Hnd(new AdtDelphiRealType((AdtDelphiRealType::AdtType)nType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiOrdinalType_create(void* pSubrangeTypeObj, void* pEnumeratedTypeObj, void* pOrdIdentObj)
{
  return (Hnd(new AdtDelphiOrdinalType(ObjAndRelease(pSubrangeTypeObj), ObjAndRelease(pEnumeratedTypeObj), ObjAndRelease(pOrdIdentObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiOrdIdent_create(int nType)
{
  return (Hnd(new AdtDelphiOrdIdent((AdtDelphiOrdIdent::AdtType)nType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVariantType_create(int nType)
{
  return (Hnd(new AdtDelphiVariantType((AdtDelphiVariantType::AdtType)nType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSubrangeType_create(void* pFromConstExprObj, void* pToConstExprObj)
{
  return (Hnd(new AdtDelphiSubrangeType(ObjAndRelease(pFromConstExprObj), ObjAndRelease(pToConstExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiEnumeratedType_create(void* pEnumeratedTypeElementListObj)
{
  return (Hnd(new AdtDelphiEnumeratedType(ObjAndRelease(pEnumeratedTypeElementListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiEnumeratedTypeElementList_create(void* pEnumeratedTypeElementObj)
{
  return (Hnd(new AdtDelphiEnumeratedTypeElementList(ObjAndRelease(pEnumeratedTypeElementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiEnumeratedTypeElement_create(void* pIdentObj, void* pConstExprObj)
{
  return (Hnd(new AdtDelphiEnumeratedTypeElement(ObjAndRelease(pIdentObj), ObjAndRelease(pConstExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiStringType_create(int nType, void* pConstExprObj)
{
  return (Hnd(new AdtDelphiStringType((AdtDelphiStringType::AdtType)nType, ObjAndRelease(pConstExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiStructType_create(int bIsPacked, void* pArrayTypeObj, void* pSetTypeObj, void* pFileTypeObj, void* pRecTypeObj)
{
  return (Hnd(new AdtDelphiStructType(bIsPacked != 0, ObjAndRelease(pArrayTypeObj), ObjAndRelease(pSetTypeObj), ObjAndRelease(pFileTypeObj), ObjAndRelease(pRecTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiArrayType_create(void* pOrdinalTypeListObj, void* pTypeObj)
{
  return (Hnd(new AdtDelphiArrayType(ObjAndRelease(pOrdinalTypeListObj), ObjAndRelease(pTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiOrdinalTypeList_create(void* pOrdinalTypeObj)
{
  return (Hnd(new AdtDelphiOrdinalTypeList(ObjAndRelease(pOrdinalTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRecType_create(void* pFieldDeclListObj, void* pVariantSectionListObj)
{
  return (Hnd(new AdtDelphiRecType(ObjAndRelease(pFieldDeclListObj), ObjAndRelease(pVariantSectionListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFieldDeclList_create(void* pFieldDeclObj)
{
  return (Hnd(new AdtDelphiFieldDeclList(ObjAndRelease(pFieldDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFieldDecl_create(void* pIdentListObj, void* pTypeObj)
{
  return (Hnd(new AdtDelphiFieldDecl(ObjAndRelease(pIdentListObj), ObjAndRelease(pTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVariantSectionList_create(void* pVariantSectionObj)
{
  return (Hnd(new AdtDelphiVariantSectionList(ObjAndRelease(pVariantSectionObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVariantSection_create(void* pIdentObj, void* pUnitIdObj, void* pTypeIdObj, void* pRecVariantObj)
{
  return (Hnd(new AdtDelphiVariantSection(ObjAndRelease(pIdentObj), ObjAndRelease(pUnitIdObj), ObjAndRelease(pTypeIdObj), ObjAndRelease(pRecVariantObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRecVariant_create(void* pConstExprListObj, void* pFieldDeclListObj, void* pVariantSectionListObj)
{
  return (Hnd(new AdtDelphiRecVariant(ObjAndRelease(pConstExprListObj), ObjAndRelease(pFieldDeclListObj), ObjAndRelease(pVariantSectionListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstExprList_create(void* pConstExprObj)
{
  return (Hnd(new AdtDelphiConstExprList(ObjAndRelease(pConstExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSetType_create(void* pOrdinalTypeObj)
{
  return (Hnd(new AdtDelphiSetType(ObjAndRelease(pOrdinalTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFileType_create(void* pUnitIdObj, void* pTypeIdObj)
{
  return (Hnd(new AdtDelphiFileType(ObjAndRelease(pUnitIdObj), ObjAndRelease(pTypeIdObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiPointerType_create(void* pUnitIdObj, void* pTypeIdObj)
{
  return (Hnd(new AdtDelphiPointerType(ObjAndRelease(pUnitIdObj), ObjAndRelease(pTypeIdObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProcedureType_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, int bOfObject)
{
  return (Hnd(new AdtDelphiProcedureType(ObjAndRelease(pProcedureHeadingObj), ObjAndRelease(pFunctionHeadingObj), bOfObject != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVarSection_create(void* pVarDeclListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiVarSection(ObjAndRelease(pVarDeclListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVarDeclList_create(void* pVarDeclObj)
{
  return (Hnd(new AdtDelphiVarDeclList(ObjAndRelease(pVarDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiVarDecl_create(void* pIdentListObj, void* pTypeObj, void* pIdentObj, void* pConstExprObj, int nAbsolute)
{
  return (Hnd(new AdtDelphiVarDecl(ObjAndRelease(pIdentListObj), ObjAndRelease(pTypeObj), ObjAndRelease(pIdentObj), ObjAndRelease(pConstExprObj), nAbsolute != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExpression_create(void* pExpressionRelOpListObj)
{
  return (Hnd(new AdtDelphiExpression(ObjAndRelease(pExpressionRelOpListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExpressionRelOpList_create(void* pExpressionRelOpObj)
{
  return (Hnd(new AdtDelphiExpressionRelOpList(ObjAndRelease(pExpressionRelOpObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExpressionRelOp_create(int nRelOp, void* pSimpleExpressionObj)
{
  return (Hnd(new AdtDelphiExpressionRelOp((AdtDelphiExpressionRelOp::AdtRelOp)nRelOp, ObjAndRelease(pSimpleExpressionObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSimpleExpression_create(void* pSimpleExpressionAddOpListObj)
{
  return (Hnd(new AdtDelphiSimpleExpression(ObjAndRelease(pSimpleExpressionAddOpListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSimpleExpressionAddOpList_create(void* pSimpleExpressionAddOpObj)
{
  return (Hnd(new AdtDelphiSimpleExpressionAddOpList(ObjAndRelease(pSimpleExpressionAddOpObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSimpleExpressionAddOp_create(int nAddOp, int nSign, void* pTermObj)
{
  return (Hnd(new AdtDelphiSimpleExpressionAddOp((AdtDelphiSimpleExpressionAddOp::AdtAddOp)nAddOp, (AdtDelphiSimpleExpressionAddOp::AdtSign)nSign, ObjAndRelease(pTermObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTerm_create(void* pFactorMulOpListObj)
{
  return (Hnd(new AdtDelphiTerm(ObjAndRelease(pFactorMulOpListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFactorMulOpList_create(void* pFactorMulOpObj)
{
  return (Hnd(new AdtDelphiFactorMulOpList(ObjAndRelease(pFactorMulOpObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFactorMulOp_create(int nMulOp, void* pFactorObj)
{
  return (Hnd(new AdtDelphiFactorMulOp((AdtDelphiFactorMulOp::AdtMulOp)nMulOp, ObjAndRelease(pFactorObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFactor_create(void* pDesignatorObj, int bHasAt, void* pNumberObj, void* pStringObj, int bHasNil, void* pExpressionObj, void* pFactorObj, void* pSetConstructorObj, void* pSizeofTypeObj, void* pCastExpressionObj)
{
  return (Hnd(new AdtDelphiFactor(ObjAndRelease(pDesignatorObj), bHasAt != 0, ObjAndRelease(pNumberObj), ObjAndRelease(pStringObj), bHasNil != 0, ObjAndRelease(pExpressionObj), ObjAndRelease(pFactorObj), ObjAndRelease(pSetConstructorObj), ObjAndRelease(pSizeofTypeObj), ObjAndRelease(pCastExpressionObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCastExpression_create(void* pOrdIdentObj, void* pRealTypeObj, void* pExpressionObj)
{
  return (Hnd(new AdtDelphiCastExpression(ObjAndRelease(pOrdIdentObj), ObjAndRelease(pRealTypeObj), ObjAndRelease(pExpressionObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDesignator_create(void* pDesignatorObjListObj)
{
  return (Hnd(new AdtDelphiDesignator(ObjAndRelease(pDesignatorObjListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDesignatorObjList_create(void* pDesignatorObj)
{
  return (Hnd(new AdtDelphiDesignatorObjList(ObjAndRelease(pDesignatorObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDesignatorObj_create(void* pIdentObj,  void* pExprListObj, void* pDesignatorRefListObj, int bEmptyParenthesis, int bInherited)
{
  return (Hnd(new AdtDelphiDesignatorObj(ObjAndRelease(pIdentObj), ObjAndRelease(pExprListObj), ObjAndRelease(pDesignatorRefListObj), bEmptyParenthesis != 0, bInherited != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDesignatorRefList_create(void* pDesignatorRefObj)
{
  return (Hnd(new AdtDelphiDesignatorRefList(ObjAndRelease(pDesignatorRefObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDesignatorRef_create(void* pExprListObj)
{
  return (Hnd(new AdtDelphiDesignatorRef(ObjAndRelease(pExprListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSetConstructor_create(void* pSetElementListObj)
{
  return (Hnd(new AdtDelphiSetConstructor(ObjAndRelease(pSetElementListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSetElementList_create(void* pSetElementObj)
{
  return (Hnd(new AdtDelphiSetElementList(ObjAndRelease(pSetElementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSetElement_create(void* pExpressionObj, void* pEndExpressionObj)
{
  return (Hnd(new AdtDelphiSetElement(ObjAndRelease(pExpressionObj), ObjAndRelease(pEndExpressionObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExprList_create(void* pExprObj)
{
  return (Hnd(new AdtDelphiExprList(ObjAndRelease(pExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiStatement_create(void* pLabelIdObj, void* pExitStatementObj, void* pSimpleStatementObj, void* pCompoundStmtObj, void* pIfStmtObj, void* pCaseStmtObj, void* pRepeatStmtObj, void* pWhileStmtObj, void* pForStmtObj, void* pWithStmtObj, const char* pComment)
{
  return (Hnd(new AdtDelphiStatement(ObjAndRelease(pLabelIdObj), ObjAndRelease(pExitStatementObj), ObjAndRelease(pSimpleStatementObj), ObjAndRelease(pCompoundStmtObj), ObjAndRelease(pIfStmtObj), ObjAndRelease(pCaseStmtObj), ObjAndRelease(pRepeatStmtObj), ObjAndRelease(pWhileStmtObj), ObjAndRelease(pForStmtObj), ObjAndRelease(pWithStmtObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiStmtList_create(void* pStmtObj)
{
  return (Hnd(new AdtDelphiStmtList(ObjAndRelease(pStmtObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiExitStatement_create(int nWithParenthesis)
{
  return (Hnd(new AdtDelphiExitStatement(nWithParenthesis != 0 ? true : false), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSimpleStatement_create(void* pDesignatorObj, void* pExpressionObj, void* pSizeofTypeObj, void* pIdentObj, void* pExprListObj, void* pLabelIdObj, void* pCastExpressionObj, int nInherited, int nOpType)
{
  return (Hnd(new AdtDelphiSimpleStatement(ObjAndRelease(pDesignatorObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pSizeofTypeObj), ObjAndRelease(pIdentObj), ObjAndRelease(pExprListObj), ObjAndRelease(pLabelIdObj), ObjAndRelease(pCastExpressionObj), nInherited != 0, (AdtDelphiSimpleStatement::AdtOpType)nOpType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiSizeofType_create(void* pOrdIdentObj, void* pRealTypeObj, void* pVariantTypeObj, void* pDesignatorObj)
{
  return (Hnd(new AdtDelphiSizeofType(ObjAndRelease(pOrdIdentObj), ObjAndRelease(pRealTypeObj), ObjAndRelease(pVariantTypeObj), ObjAndRelease(pDesignatorObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCompoundStmt_create(void* pStmtListObj)
{
  return (Hnd(new AdtDelphiCompoundStmt(ObjAndRelease(pStmtListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiIfStmt_create(void* pExpressionObj, void* pThenStatementObj, void* pElseStatementObj)
{
  return (Hnd(new AdtDelphiIfStmt(ObjAndRelease(pExpressionObj), ObjAndRelease(pThenStatementObj), ObjAndRelease(pElseStatementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCaseStmt_create(void* pExpressionObj, void* pCaseSelectorListObj, void* pStmtListObj)
{
  return (Hnd(new AdtDelphiCaseStmt(ObjAndRelease(pExpressionObj), ObjAndRelease(pCaseSelectorListObj), ObjAndRelease(pStmtListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCaseSelectorList_create(void* pCaseSelectorObj)
{
  return (Hnd(new AdtDelphiCaseSelectorList(ObjAndRelease(pCaseSelectorObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCaseSelector_create(void* pCaseLabelListObj, void* pStatementObj)
{
  return (Hnd(new AdtDelphiCaseSelector(ObjAndRelease(pCaseLabelListObj), ObjAndRelease(pStatementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCaseLabelList_create(void* pCaseLabelObj)
{
  return (Hnd(new AdtDelphiCaseLabelList(ObjAndRelease(pCaseLabelObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiCaseLabel_create(void* pConstExprObj, void* pToConstExprObj)
{
  return (Hnd(new AdtDelphiCaseLabel(ObjAndRelease(pConstExprObj), ObjAndRelease(pToConstExprObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiRepeatStmt_create(void* pStatementObj, void* pExpressionObj, void* pStmtListObj)
{
  return (Hnd(new AdtDelphiRepeatStmt(ObjAndRelease(pStatementObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pStmtListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiWhileStmt_create(void* pExpressionObj, void* pStatementObj)
{
  return (Hnd(new AdtDelphiWhileStmt(ObjAndRelease(pExpressionObj), ObjAndRelease(pStatementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiForStmt_create(void* pUnitIdObj, void* pIdentObj, void* pFromExpressionObj, void* pToExpressionObj, void* pStatementObj, int nDownTo)
{
  return (Hnd(new AdtDelphiForStmt(ObjAndRelease(pUnitIdObj), ObjAndRelease(pIdentObj), ObjAndRelease(pFromExpressionObj), ObjAndRelease(pToExpressionObj), ObjAndRelease(pStatementObj), nDownTo != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiWithStmt_create(void* pDesignatorObj, void* pStatementObj)
{
  return (Hnd(new AdtDelphiWithStmt(ObjAndRelease(pDesignatorObj), ObjAndRelease(pStatementObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProcedureDeclSection_create(void* pProcedureDeclListObj)
{
  return (Hnd(new AdtDelphiProcedureDeclSection(ObjAndRelease(pProcedureDeclListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProcedureDeclList_create(void* pProcedureDeclObj)
{
  return (Hnd(new AdtDelphiProcedureDeclList(ObjAndRelease(pProcedureDeclObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProcedureDecl_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pConstructorHeadingObj, void* pDestructorHeadingObj, void* pDirectiveListObj, void* pBlockObj)
{
  return (Hnd(new AdtDelphiProcedureDecl(ObjAndRelease(pProcedureHeadingObj), ObjAndRelease(pFunctionHeadingObj), ObjAndRelease(pConstructorHeadingObj), ObjAndRelease(pDestructorHeadingObj), ObjAndRelease(pDirectiveListObj), ObjAndRelease(pBlockObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFunctionHeading_create(void* pClassIdentObj, void* pFunctionIdentObj, void* pFormalParametersObj, void* pSimpleTypeObj, void* pTypeIdObj, const char* pComment)
{
  return (Hnd(new AdtDelphiFunctionHeading(ObjAndRelease(pClassIdentObj), ObjAndRelease(pFunctionIdentObj), ObjAndRelease(pFormalParametersObj), ObjAndRelease(pSimpleTypeObj), ObjAndRelease(pTypeIdObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProcedureHeading_create(void* pClassIdentObj, void* pProcedureIdentObj, void* pFormalParametersObj, const char* pComment)
{
  return (Hnd(new AdtDelphiProcedureHeading(ObjAndRelease(pClassIdentObj), ObjAndRelease(pProcedureIdentObj), ObjAndRelease(pFormalParametersObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFormalParameters_create(void* pFormalParamListObj)
{
  return (Hnd(new AdtDelphiFormalParameters(ObjAndRelease(pFormalParamListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFormalParamList_create(void* pFormalParamObj)
{
  return (Hnd(new AdtDelphiFormalParamList(ObjAndRelease(pFormalParamObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiFormalParam_create(int nType, void* pParameterObj)
{
  return (Hnd(new AdtDelphiFormalParam((AdtDelphiFormalParam::AdtType)nType, ObjAndRelease(pParameterObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiParameter_create(void* pIdentListObj, void* pSimpleTypeObj, void* pTypeIdObj, void* pConstExprObj, void* pIdentObj, int nIsArray, int bOfString, int nOfFile)
{
  return (Hnd(new AdtDelphiParameter(ObjAndRelease(pIdentListObj), ObjAndRelease(pSimpleTypeObj), ObjAndRelease(pTypeIdObj), ObjAndRelease(pConstExprObj), ObjAndRelease(pIdentObj), nIsArray != 0, bOfString != 0, nOfFile != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDirective_create(int nType)
{
  return (Hnd(new AdtDelphiDirective((AdtDelphiDirective::AdtType)nType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDirectiveList_create(void* pDirectiveObj)
{
  return (Hnd(new AdtDelphiDirectiveList(ObjAndRelease(pDirectiveObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiObjectType_create(void* pUnitIdObj, void* pIdentObj, void* pObjFieldListObj, void* pMethodListObj)
{
  return (Hnd(new AdtDelphiObjectType(ObjAndRelease(pUnitIdObj), ObjAndRelease(pIdentObj), ObjAndRelease(pObjFieldListObj), ObjAndRelease(pMethodListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiMethodList_create(void* pMethodObj)
{
  return (Hnd(new AdtDelphiMethodList(ObjAndRelease(pMethodObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiMethod_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pConstructorHeadingObj, void* pDestructorHeadingObj, void* pDirectiveListObj)
{
  return (Hnd(new AdtDelphiMethod(ObjAndRelease(pProcedureHeadingObj), ObjAndRelease(pFunctionHeadingObj), ObjAndRelease(pConstructorHeadingObj), ObjAndRelease(pDestructorHeadingObj), ObjAndRelease(pDirectiveListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstructorHeading_create(void* pClassIdentObj, void* pMethodIdentObj, void* pFormalParametersObj, const char* pComment)
{
  return (Hnd(new AdtDelphiConstructorHeading(ObjAndRelease(pClassIdentObj), ObjAndRelease(pMethodIdentObj), ObjAndRelease(pFormalParametersObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiDestructorHeading_create(void* pClassIdentObj, void* pMethodIdentObj, void* pFormalParametersObj, const char* pComment)
{
  return (Hnd(new AdtDelphiDestructorHeading(ObjAndRelease(pClassIdentObj), ObjAndRelease(pMethodIdentObj), ObjAndRelease(pFormalParametersObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiObjFieldList_create(void* pObjFieldObj)
{
  return (Hnd(new AdtDelphiObjFieldList(ObjAndRelease(pObjFieldObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiObjField_create(void* pIdentListObj, void* pTypeObj)
{
  return (Hnd(new AdtDelphiObjField(ObjAndRelease(pIdentListObj), ObjAndRelease(pTypeObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiInitSection_create(void* pStmtListObj, void* pFinalStmtListObj, int bHasInit, const char* pComment)
{
  return (Hnd(new AdtDelphiInitSection(ObjAndRelease(pStmtListObj), ObjAndRelease(pFinalStmtListObj), bHasInit != 0, pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassType_create(void* pIdentListObj, void* pClassFieldListObj, void* pClassMethodListObj, void* pClassPropertyListObj)
{
  return (Hnd(new AdtDelphiClassType(ObjAndRelease(pIdentListObj), ObjAndRelease(pClassFieldListObj), ObjAndRelease(pClassMethodListObj), ObjAndRelease(pClassPropertyListObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassFieldList_create(void* pClassFieldObj)
{
  return (Hnd(new AdtDelphiClassFieldList(ObjAndRelease(pClassFieldObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassField_create(int nVisibility, void* pObjFieldObj)
{
  return (Hnd(new AdtDelphiClassField((AdtVisibility)nVisibility, ObjAndRelease(pObjFieldObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassMethodList_create(void* pClassMethodObj)
{
  return (Hnd(new AdtDelphiClassMethodList(ObjAndRelease(pClassMethodObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassMethod_create(int nVisibility, void* pMethodObj)
{
  return (Hnd(new AdtDelphiClassMethod((AdtVisibility)nVisibility, ObjAndRelease(pMethodObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassPropertyList_create(void* pClassPropertyObj)
{
  return (Hnd(new AdtDelphiClassPropertyList(ObjAndRelease(pClassPropertyObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiClassProperty_create(int nVisibility, void* pPropertyObj)
{
  return (Hnd(new AdtDelphiClassProperty((AdtVisibility)nVisibility, ObjAndRelease(pPropertyObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiProperty_create(void* pClassIdentObj, void* pIdentObj, void* pPropertyParameterListObj, void* pPropertySpecifiersObj)
{
  return (Hnd(new AdtDelphiProperty(ObjAndRelease(pClassIdentObj), ObjAndRelease(pIdentObj), ObjAndRelease(pPropertyParameterListObj), ObjAndRelease(pPropertySpecifiersObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiPropertyParameterList_create(void* pPropertyParameterObj)
{
  return (Hnd(new AdtDelphiPropertyParameterList(ObjAndRelease(pPropertyParameterObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiPropertyParameter_create(void* pIdentListObj, void* pUnitIdObj, void* pTypeIdObj)
{
  return (Hnd(new AdtDelphiPropertyParameter(ObjAndRelease(pIdentListObj), ObjAndRelease(pUnitIdObj), ObjAndRelease(pTypeIdObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiPropertySpecifiers_create(int nType, void* pIdentObj, void* pConstExprObj, void* pUnitIdObj, void* pTypeIdObj)
{
  return (Hnd(new AdtDelphiPropertySpecifiers((AdtDelphiPropertySpecifiers::AdtType)nType, ObjAndRelease(pIdentObj), ObjAndRelease(pConstExprObj), ObjAndRelease(pUnitIdObj), ObjAndRelease(pTypeIdObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiInterfaceType_create(void* pIdentListObj, void* pClassMethodListObj, void* pClassPropertyListObj, const char* pComment)
{
  return (Hnd(new AdtDelphiInterfaceType(ObjAndRelease(pIdentListObj), ObjAndRelease(pClassMethodListObj), ObjAndRelease(pClassPropertyListObj), pComment), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiIdentList_create(void* pIdentObj)
{
  return (Hnd(new AdtDelphiIdentList(ObjAndRelease(pIdentObj)), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiIdent_create(const char* pIdentifier)
{
  return (Hnd(new AdtDelphiIdent(pIdentifier), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiTypeId_create(const char* pTypeId)
{
  return (Hnd(new AdtDelphiTypeId(pTypeId), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiUnitId_create(const char* pUnitId)
{
  return (Hnd(new AdtDelphiUnitId(pUnitId), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiLabelId_create(const char* pLabelId)
{
  return (Hnd(new AdtDelphiLabelId(pLabelId), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiNumber_create(const char* pNumber, int nType)
{
  return (Hnd(new AdtDelphiNumber(pNumber, nType), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiString_create(const char* pString)
{
  return (Hnd(new AdtDelphiString(pString), yyDelphi_lineNumber(), yyDelphi_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtDelphiConstExpr_create(const char* pConstExpr, int bIsNumber)
{
  return (Hnd(new AdtDelphiConstExpr(pConstExpr, bIsNumber != 0), yyDelphi_lineNumber(), yyDelphi_fileName()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiToFortranTypeConversion method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiToFortranTypeConversion::initialise()
{
  int nSize = ::atoi(FortranDimension.c_str());

  if (nSize > 0)
  {
    bool bFirst = true;

    FortranDimensionString = "(";

    for (int cn = 0 ; cn < nSize ; cn++)
    {
      if (bFirst)
      {
        FortranDimensionString += ":";

        bFirst = false;
      }
      else
      {
        FortranDimensionString += ",:";
      }
    }

    FortranDimensionString += ")";
  }
  else
  {
    FortranDimensionString = "";
  }
}


//  ----------------------------------------------------------------------------
//  AdtDelphiBase method implementations
//  ----------------------------------------------------------------------------
AdtFile& AdtDelphiBase::forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
{
  if (pOutFile.isOpen())
  {
    AdtParserPtrListConstIter     Iter;
    size_t                        nSize = objList().size();
    int                           cn    = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
      {
        AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

        pDelphiObj->writeCPP(pOutFile, nMode);

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

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiBase::forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
{
  if (pOutFile.isOpen())
  {
    AdtParserPtrListConstIter     Iter;
    size_t                        nSize = objList().size();
    int                           cn    = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
      {
        AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

        pDelphiObj->writeFortran(pOutFile, nMode);

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

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiBase::forAllWriteDelphi(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast) const
{
  if (pOutFile.isOpen())
  {
    AdtParserPtrListConstIter     Iter;
    size_t                        nSize = objList().size();
    int                           cn    = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
      {
        AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

        pDelphiObj->writeDelphi(pOutFile, nMode);

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

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiBase::writePragmas(AdtFile& pOutFile) const
{
  if (pOutFile.isOpen()        &&
      pOutFile.isFortranFile() &&
      (comment().length() > 0))
  {
    string  sCopy(comment());
    int         nCount    = 0;
    const char* pWord     = 0;
    char*       pStart    = (char*)(sCopy.c_str());
    char*       pEnd      = pStart;
    int         nStrip    = 0;

    while (*pEnd != 0)
    {
      bool  bContinue     = true;
      bool  bStartComment = true;
      bool  bIsPragma     = false;

      switch(*pEnd)
      {
        case '{':
        {
          nStrip = 1;
          pEnd++;
          break;
        }

        case '(':
        {
          nStrip = 2;
          pEnd++;

          if (*pEnd == '*')
          {
            pEnd++;
          }
          break;
        }

        case '/':
        {
          nStrip = 0;
          pEnd++;

          if (*pEnd == '/')
          {
            pEnd++;
          }
          break;
        }

        default:
        {
          bStartComment = false;
          break;
        }
      }

      pEnd  = (char*)AdtParse::nextWord(pEnd);
      pWord = pEnd;

      if (bStartComment && AdtParse::matchWord(pWord, "!$AD", false))
      {
        pStart    = pEnd;
        bIsPragma = true;
      }

      while ((*pEnd != 0) && bContinue)
      {
        switch (*pEnd)
        {
          case '\n':
          {
            nStrip++;
            *pEnd = 0;

            if (*(pEnd + 1) == '\r')
            {
              nStrip++;
              pEnd++;
              *pEnd = 0;
            }

            bContinue = false;
            break;
          }

          case '\r':
          {
            nStrip++;
            *pEnd = 0;

            if (*(pEnd + 1) == '\n')
            {
              nStrip++;
              pEnd++;
              *pEnd = 0;
            }

            bContinue = false;
            break;
          }

          default:
          {
            break;
          }
        }

        pEnd++;
      }

      if (bIsPragma)
      {
        int nLastIndent = pOutFile.indent();

        if ((*pEnd == 0) && (nStrip > 0))
        {
          char* pEOL = pEnd - nStrip;

          *pEOL = 0;
        }

        pOutFile.newline();
        pOutFile.write(pStart);
        pOutFile.newline();
      }

      pStart = pEnd;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtDelphiBase::AdtDelphiBase()
 : AdtParser()
{

}

//  ----------------------------------------------------------------------------

AdtDelphiBase::~AdtDelphiBase()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtDelphiBase::addFortranTypeMap(const string& rDelphiType,
                                      const string& rFortranType,
                                      const string& rFortranSize)
{
  FortranTypeMap.insert(AdtDelphiToFortranTypeConversionStringPair(rDelphiType, AdtDelphiToFortranTypeConversion(rDelphiType, rFortranType, rFortranSize)));
  DelphiTypeMap.insert(AdtDelphiToFortranTypeConversionStringPair(rFortranType + rFortranSize, AdtDelphiToFortranTypeConversion(rDelphiType, rFortranType, rFortranSize)));
}

//  ----------------------------------------------------------------------------

void AdtDelphiBase::typeScope(AdtParser* pIdent)
{
  if (pIdent != 0)
  {
    TypeScope = pIdent->name();
  }
  else
  {
    TypeScope = 0;
  }
}

//  ----------------------------------------------------------------------------

const char* AdtDelphiBase::typeScope()
{
  return (TypeScope);
}

//  ----------------------------------------------------------------------------

void AdtDelphiBase::delphiRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(DelphiRootObject);

  DelphiRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtDelphiGoal"))
    {
      DelphiRootObject = (AdtDelphiGoal*)pRoot;
      DelphiRootObject->lock();
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiGoal* AdtDelphiBase::delphiRootObject()
{
  return (DelphiRootObject);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiBase::mapTypesToFortran(const char* pTypeName,
                                      const char*& pType,
                                      const char*& pDimension)
{
  bool                                                  bFound  = false;
  AdtDelphiToFortranTypeConversionByStringMapConstIter  Iter    = FortranTypeMap.find(pTypeName);

  if (Iter != FortranTypeMap.end())
  {
    pType       = (*Iter).second.FortranType;
    pDimension  = (*Iter).second.FortranDimensionString;
    bFound      = true;
  }
  else
  {
    pType       = 0;
    pDimension  = 0;
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiBase::mapTypesToDelphi(const char* pTypeName,
                                     size_t nDimension,
                                     const char*& pType)
{
  char  pDimension[16] = {0};

  ::sprintf(pDimension, "%zd", nDimension);

  bool                                                  bFound        = false;
  string                                                sTypeAndSize  = string(pTypeName) + pDimension;
  AdtDelphiToFortranTypeConversionByStringMapConstIter  Iter          = DelphiTypeMap.find(sTypeAndSize);

  if (Iter != DelphiTypeMap.end())
  {
    pType       = (*Iter).second.DelphiType;
    bFound      = true;
  }
  else
  {
    pType       = 0;
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtDelphiGoal method implementations
//  ----------------------------------------------------------------------------
AdtDelphiGoal::AdtDelphiGoal(AdtParser* pObj)
 : AdtDelphiBase(),
   AdtSourceRoot(),

   ExportedVariableMap(),
   ExportedTypeMap(),
   ExportedConstMap(),
   ExportedProcedureMap(),

   LocalVariableMap(),
   LocalTypeMap(),
   LocalConstMap(),
   ImplementedProcedureMap()
{
  initObject(Program, pObj, AdtDelphiProgram, false);
  initObject(Package, pObj, AdtDelphiPackage, false);
  initObject(Library, pObj, AdtDelphiLibrary, false);
  initObject(Unit,    pObj, AdtDelphiUnit,    false);

  enumerateDescendantMap(LocalVariableMap,        "Program,Block,DeclSection,VarSection,VarDeclList;Library,Block,DeclSection,VarSection,VarDeclList;Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;");
  enumerateDescendantMap(LocalTypeMap,            "Program,Block,DeclSection,TypeSection,TypeDeclList;Library,Block,DeclSection,TypeSection,TypeDeclList;Unit,ImplementationSection,DeclSection,TypeSection,TypeDeclList;");
  enumerateDescendantMap(LocalConstMap,           "Program,Block,DeclSection,ConstSection,ConstantDeclList;Library,DeclSection,ConstSection,ConstantDeclList;Unit,ImplementationSection,DeclSection,ConstSection,ConstantDeclList;");
  enumerateDescendantMap(ImplementedProcedureMap, "Program,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Library,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Unit,ImplementationSection,DeclSection,ProcedureDeclSection,ProcedureDeclList;");

  enumerateDescendantMap(ExportedVariableMap,   "Unit,InterfaceSection,VarSection,VarDeclList");
  enumerateDescendantMap(ExportedTypeMap,       "Unit,InterfaceSection,TypeSection,TypeDeclList");
  enumerateDescendantMap(ExportedConstMap,      "Unit,InterfaceSection,ConstSection,ConstantDeclList");
  enumerateDescendantMap(ExportedProcedureMap,  "Unit,InterfaceSection,ExportedHeadingList");

  depth(0, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiGoal::AdtDelphiGoal(const AdtDelphiGoal& rCopy)
 : AdtDelphiBase(rCopy),
   AdtSourceRoot(rCopy),

   ExportedVariableMap(),
   ExportedTypeMap(),
   ExportedConstMap(),
   ExportedProcedureMap(),

   LocalVariableMap(),
   LocalTypeMap(),
   LocalConstMap(),
   ImplementedProcedureMap()
{
  copyObject(Program, rCopy, AdtDelphiProgram);
  copyObject(Package, rCopy, AdtDelphiPackage);
  copyObject(Library, rCopy, AdtDelphiLibrary);
  copyObject(Unit,    rCopy, AdtDelphiUnit);

  enumerateDescendantMap(LocalVariableMap,        "Program,Block,DeclSection,VarSection,VarDeclList;Library,Block,DeclSection,VarSection,VarDeclList;Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;");
  enumerateDescendantMap(LocalTypeMap,            "Program,Block,DeclSection,TypeSection,TypeDeclList;Library,Block,DeclSection,TypeSection,TypeDeclList;Unit,ImplementationSection,DeclSection,TypeSection,TypeDeclList;");
  enumerateDescendantMap(LocalConstMap,           "Program,Block,DeclSection,ConstSection,ConstantDeclList;Library,DeclSection,ConstSection,ConstantDeclList;Unit,ImplementationSection,DeclSection,ConstSection,ConstantDeclList;");
  enumerateDescendantMap(ImplementedProcedureMap, "Program,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Library,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Unit,ImplementationSection,DeclSection,ProcedureDeclSection,ProcedureDeclList;");

  enumerateDescendantMap(ExportedVariableMap,   "Unit,InterfaceSection,VarSection,VarDeclList");
  enumerateDescendantMap(ExportedTypeMap,       "Unit,InterfaceSection,TypeSection,TypeDeclList");
  enumerateDescendantMap(ExportedConstMap,      "Unit,InterfaceSection,ConstSection,ConstantDeclList");
  enumerateDescendantMap(ExportedProcedureMap,  "Unit,InterfaceSection,ExportedHeadingList");
}

//  ----------------------------------------------------------------------------

AdtDelphiGoal::~AdtDelphiGoal()
{
  ExportedVariableMap.clear();
  ExportedTypeMap.clear();
  ExportedConstMap.clear();
  ExportedProcedureMap.clear();

  LocalVariableMap.clear();
  LocalTypeMap.clear();
  LocalConstMap.clear();
  ImplementedProcedureMap.clear();

  UtlReleaseReference(Program);
  UtlReleaseReference(Package);
  UtlReleaseReference(Library);
  UtlReleaseReference(Unit);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::findConst(const char* pName, const AdtParser*& pExternal) const
{
  bool bFound = findObject(LocalConstMap, pName, pExternal) || findObject(ExportedConstMap, pName, pExternal);

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::findVar(const char* pName, const AdtParser*& pExternal) const
{
  bool bFound = findObject(LocalVariableMap, pName, pExternal) || findObject(ExportedVariableMap, pName, pExternal);

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::findProc(const char* pName, const char* pClassName, const AdtParser*& pExternal, string& rMatchName) const
{
  bool bFound;

  // Look in class scope first
  rMatchName  = string(pClassName) + "." + pName;
  bFound      = findObject(ImplementedProcedureMap, rMatchName, pExternal);

  if (!bFound)
  {
    // Look in global scope next
    bFound = findObject(ImplementedProcedureMap, pName, pExternal);

    if (bFound)
    {
      rMatchName = pName;
    }
    else
    {
      rMatchName = "";
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::findField(const char* pName, const char* pClassName, const AdtParser*& pExternal) const
{
  const AdtParser*  pClassObj = 0;
  bool              bFound    = false;

  if (findObject(LocalTypeMap, pClassName, pClassObj) || findObject(ExportedTypeMap, pClassName, pClassObj))
  {
    AdtDelphiClassType* pClass = (AdtDelphiClassType*)pClassObj->findObject("AdtDelphiClassType");

    if (pClass != 0)
    {
      bFound = pClass->findField(pName, pExternal);
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::isClassType(const AdtParserPtrByStringMap& rMap,
                                const char* pClassName,
                                AdtDelphiClassType** ppClassTypeObj) const
{
  bool bIsClassType = false;

  if (pClassName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = rMap.find(pClassName);

    if (Iter != rMap.end())
    {
      const AdtParser* pObject = (*Iter).second;

      if (pObject != 0)
      {
        const AdtParser* pClassObject = pObject->findObject("AdtDelphiClassType");

        bIsClassType = (pClassObject != 0);

        if (ppClassTypeObj != 0)
        {
          *ppClassTypeObj = (AdtDelphiClassType*)pClassObject;
        }
      }
    }
  }

  return (bIsClassType);
}

//  ----------------------------------------------------------------------------

void AdtDelphiGoal::buildMacroMap(AdtParserPtrByStringMultiMap& rMacroMap) const
{
  AdtParserPtrListConstIter Iter;

  rMacroMap.clear();

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if ((pObj != 0) && pObj->isType("AdtDelphiMacro"))
    {
      string  sKey(pObj->name());

      sKey.toUpper();
      rMacroMap.insert(AdtParserPtrByStringMap::value_type(sKey, AdtParserContext(pObj)));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiGoal::addDimensionVars(const char* pClassName,
                                     AdtParserPtrByStringMap& rVarsMap) const
{
  const AdtParser*  pClassObj = 0;

  if (findObject(LocalTypeMap, pClassName, pClassObj) || findObject(ExportedTypeMap, pClassName, pClassObj))
  {
    AdtDelphiClassType* pClass = (AdtDelphiClassType*)pClassObj->findObject("AdtDelphiClassType");

    if (pClass != 0)
    {
      AdtParserPtrList      rList;
      AdtParserPtrListIter  Iter;

      pClass->findDimensionVars(rVarsMap, rList);

      for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
      {
        const AdtParser*  pExternal = *Iter;

        if (pExternal != 0)
        {
          char  sKeyName[32]  = {0};

          //Quick and dirty hack to build a unique key name to stop the same
          //object being inserted more than once.
          ::sprintf(sKeyName, "%zx", (size_t)pExternal);

          //Is a class variable
          rVarsMap.insert(AdtParserPtrByStringMap::value_type(sKeyName, AdtParserContext((AdtParser*)pExternal)));
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::compile(const AdtDelphiProcedureDecl* pProcedureDecl,
                            AdtParserPtrByStringMap& rProceduresMap,
                            AdtParserPtrByStringMap& rVarsMap,
                            AdtParserPtrByStringMap& rConstMap,
                            bool bExpandMacros) const
{
  bool bCompiled = false;

  if (pProcedureDecl != 0)
  {
    //Create a copy of the procedure
    AdtDelphiProcedureDecl* pCopyProcedureDecl = new AdtDelphiProcedureDecl(*pProcedureDecl);

    if (pCopyProcedureDecl != 0)
    {
      const char* pClassStart = pCopyProcedureDecl->name();
      const char* pClassEnd   = ::strchr(pCopyProcedureDecl->name(), '.');
      size_t      nLength     = (pClassEnd != 0) ? pClassEnd - pClassStart : 0;
      string      ClassName(pClassStart, 0, nLength);

      ClassName.trim("\n\r\t");

      if (0)
      {
        //Debugging stuff to print the parse tree of the function definition
        AdtFile DescendantsFile;

        DescendantsFile.open(pCopyProcedureDecl->name() + ".txt", "wt");
        pCopyProcedureDecl->printDescendants(DescendantsFile);
      }

      if (bExpandMacros)
      {
        AdtParserPtrByStringMultiMap rMacroMap;

        buildMacroMap(rMacroMap);
        AdtDelphiMacro::forwardSubstitute(pCopyProcedureDecl, rMacroMap);
      }

      //Fixup the return variable to what fortran expects
      pCopyProcedureDecl->fixReturnVariable();

      //Add it to the list of procedures
      rProceduresMap.insert(AdtParserPtrByStringMap::value_type(pCopyProcedureDecl->name(), AdtParserContext(pCopyProcedureDecl)));

      //Find unresolved externals
      AdtStringListConstIter  Iter;
      AdtStringList           ExternalsList;

      if (pCopyProcedureDecl->enumerateExternals(ExternalsList))
      {
        for (Iter = ExternalsList.begin() ; Iter != ExternalsList.end() ; ++Iter)
        {
          char              sKeyName[32]  = {0};
          const string&     rName         = *Iter;
          const AdtParser*  pExternal     = 0;
          string            sMatchName;

          if (findConst(rName, pExternal))
          {
            //Quick and dirty hack to build a unique key name to stop the same
            //object being inserted more than once.
            ::sprintf(sKeyName, "%zx", (size_t)pExternal);

            //Is a constant
            rConstMap.insert(AdtParserPtrByStringMap::value_type(sKeyName, AdtParserContext((AdtParser*)pExternal)));
          }
          else if (findVar(rName, pExternal))
          {
            //Quick and dirty hack to build a unique key name to stop the same
            //object being inserted more than once.
            ::sprintf(sKeyName, "%zx", (size_t)pExternal);

            //Is a variable
            rVarsMap.insert(AdtParserPtrByStringMap::value_type(sKeyName, AdtParserContext((AdtParser*)pExternal)));
          }
          else if (findProc(rName, ClassName, pExternal, sMatchName))
          {
            //Is a procedure
            if (pExternal->isType("AdtDelphiProcedureDecl"))
            {
              const AdtDelphiProcedureDecl* pProcedureDecl = (const AdtDelphiProcedureDecl*)pExternal;

              if (rProceduresMap.find(sMatchName) == rProceduresMap.end())
              {
                compile(pProcedureDecl,
                        rProceduresMap,
                        rVarsMap,
                        rConstMap,
                        bExpandMacros);
              }
            }
            else
            {
              FAIL();
            }
          }
          else if (findField(rName, ClassName, pExternal))
          {
            //Quick and dirty hack to build a unique key name to stop the same
            //object being inserted more than once.
            ::sprintf(sKeyName, "%zx", (size_t)pExternal);

            //Is a class variable
            rVarsMap.insert(AdtParserPtrByStringMap::value_type(sKeyName, AdtParserContext((AdtParser*)pExternal)));
          }
          else
          {
            //warning : unresolved externals
          }
        }
      }

      // Look through VarsMap and add any dimension vars not already in VarsMap (that aren't ragged arrays which aren't allowed in AD'ed code)
      addDimensionVars(ClassName, rVarsMap);

      bCompiled = true;

      UtlReleaseReference(pCopyProcedureDecl);
    }
  }

  return (bCompiled);
}

//  ----------------------------------------------------------------------------

void AdtDelphiGoal::writeArraySizes(AdtFile& pOutFile,
                                    const AdtParserPtrByStringMap& rProceduresMap,
                                    const AdtParserPtrByStringMap& rVarsMap,
                                    const AdtParserPtrByStringMap& rConstMap) const
{
  AdtParserPtrList                  IdentList;
  AdtParserPtrListIter              ListIter;
  AdtParserPtrByStringMapConstIter  MapIter;

  //Search constants definitions.
  for (MapIter = rConstMap.begin() ; MapIter != rConstMap.end() ; ++MapIter)
  {
    AdtParser* pObj = (*MapIter).second;

    if (pObj != 0)
    {
      pObj->findObjects(IdentList, "AdtDelphiIdent", pObj->name());
    }
  }

  //Search variable definitions.
  for (MapIter = rVarsMap.begin() ; MapIter != rVarsMap.end() ; ++MapIter)
  {
    AdtParser* pObj = (*MapIter).second;

    if (pObj != 0)
    {
      pObj->findObjects(IdentList, "AdtDelphiIdent", pObj->name());
    }
  }

  //Search procedures for local definitions of variables and constants.
  for (MapIter = rProceduresMap.begin() ; MapIter != rProceduresMap.end() ; ++MapIter)
  {
    AdtParser* pObj = (*MapIter).second;

    if ((pObj != 0) && pObj->isType("AdtDelphiProcedureDecl"))
    {
      AdtDelphiProcedureDecl* pProcObj = (AdtDelphiProcedureDecl*)pObj;

      pProcObj->enumerateLocalObjects(IdentList);
    }
  }

  AdtStringByStringMap      SimpleMap;
  AdtStringByStringMap      ArraySizeMap;
  AdtStringByStringMapIter  StrIter;

  //Build a map of all the array sizes from the embedded comments on local
  //and class attribute declarations.
  for (ListIter = IdentList.begin() ; ListIter != IdentList.end() ; ++ListIter)
  {
    AdtParser* pObj = (*ListIter);

    if ((pObj != 0) && pObj->isType("AdtDelphiIdent"))
    {
      AdtDelphiIdent* pIdentObj = (AdtDelphiIdent*)pObj;

      pIdentObj->enumerateArraySizes(ArraySizeMap);

      if (pIdentObj->parent()->isType("AdtDelphiDesignatorObj"))
      {
        const AdtDelphiDesignatorObj* pDesignatorObj = (const AdtDelphiDesignatorObj*)pIdentObj->parent();

        if (pDesignatorObj->isSimpleReference())
        {
          SimpleMap[pDesignatorObj->name()] = pDesignatorObj->name();
        }
      }
    }
  }

  pOutFile.write("INTEGER, PARAMETER :: ");

  //Print out the PARAMETER definitions
  for (StrIter = ArraySizeMap.begin() ; StrIter != ArraySizeMap.end() ; ++StrIter)
  {
    const string& rArraySize = (*StrIter).second;

    // Only add objects that aren't arrays
    if (SimpleMap.find(rArraySize) != SimpleMap.end())
    {
      pOutFile.write(rArraySize);
      pOutFile.write(", ");
    }
  }

  pOutFile.write("dim_stack");
  pOutFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtDelphiGoal::enumerateMethodNames(AdtStringList& rMethodList) const
{
  AdtParserPtrList  ObjectList;

  findObjects(ObjectList, "AdtDelphiMethod");
  AdtParser::objListToNameList(rMethodList, ObjectList);
  ObjectList.clear();
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::hasClass(const char* pClassName,
                             string& rParentClassName) const
{
  bool                      bHasClass   = false;
  const AdtDelphiClassType* pClassType  = findClassType(pClassName);

  if (pClassType != 0)
  {
    rParentClassName  = pClassType->parentClassName();
    bHasClass         = true;
  }

  return (bHasClass);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::buildBlackBoxFile(const char* pBlackBoxFileName,
                                      AdtStringByStringMap& rRegardAsClassFunctionMap,
                                      AdtStringByStringMap& rRegardAsClassSubroutineMap)
{
  bool    bBuilt = false;
  string  sBlackBoxDefs;

  //Find all black box containing objects
  AdtBlackBoxDefinitionPtrByStringMap BlackBoxMap;
  AdtParserPtrList                    rBlackBoxList;
  AdtParserPtrListConstIter           Iter;

  findObjects(rBlackBoxList, "AdtDelphiFunctionHeading");

  for (Iter = rBlackBoxList.begin() ; Iter != rBlackBoxList.end() ; ++Iter)
  {
    const AdtDelphiFunctionHeading* pFunctionHeading = (const AdtDelphiFunctionHeading*)Iter->object();

    if ((pFunctionHeading != 0) && (pFunctionHeading->blackBox() != 0))
    {
      AdtBlackBoxDefinition*  pBlackBox = pFunctionHeading->blackBox();
      AdtFile                 DefFile;
      string                  sDef;

      if (DefFile.open(sDef))
      {
        AdtBlackBoxDefinitionPtrByStringMapIter BlackBoxIter;

        pBlackBox->writeDefinition(DefFile);
        DefFile.close();

        BlackBoxIter = BlackBoxMap.find(pBlackBox->name());

        if (BlackBoxIter == BlackBoxMap.end())
        {
          BlackBoxMap[pBlackBox->name()] = pBlackBox;
          addBlackBox(pBlackBox,
                      rRegardAsClassFunctionMap,
                      rRegardAsClassSubroutineMap);
        }
        else
        {
          ::printf("ERROR: The black box definition in file %s on line %d is already defined in file %s on line %d.\n",
                   pBlackBox->fileName(),
                   pBlackBox->lineNumber(),
                   BlackBoxIter->second->fileName(),
                   BlackBoxIter->second->lineNumber());

          AdtExit(-1);
        }

        sBlackBoxDefs += sDef;
      }
    }
  }

  rBlackBoxList.clear();
  findObjects(rBlackBoxList, "AdtDelphiProcedureHeading");

  for (Iter = rBlackBoxList.begin() ; Iter != rBlackBoxList.end() ; ++Iter)
  {
    const AdtDelphiProcedureHeading* pProcedureHeading = (const AdtDelphiProcedureHeading*)Iter->object();

    if ((pProcedureHeading != 0) && (pProcedureHeading->blackBox() != 0))
    {
      AdtBlackBoxDefinition*  pBlackBox = pProcedureHeading->blackBox();
      AdtFile                 DefFile;
      string                  sDef;

      if (DefFile.open(sDef))
      {
        AdtBlackBoxDefinitionPtrByStringMapIter BlackBoxIter;

        pBlackBox->writeDefinition(DefFile);
        DefFile.close();

        BlackBoxIter = BlackBoxMap.find(pBlackBox->name());

        if (BlackBoxIter == BlackBoxMap.end())
        {
          BlackBoxMap[pBlackBox->name()] = pBlackBox;
          addBlackBox(pBlackBox,
                      rRegardAsClassFunctionMap,
                      rRegardAsClassSubroutineMap);
        }
        else
        {
          ::printf("ERROR: The black box definition in file %s on line %d is already defined in file %s on line %d.\n",
                   pBlackBox->fileName(),
                   pBlackBox->lineNumber(),
                   BlackBoxIter->second->fileName(),
                   BlackBoxIter->second->lineNumber());

          AdtExit(-1);
        }

        sBlackBoxDefs += sDef;
      }
    }
  }

  if (pBlackBoxFileName != 0)
  {
    if (sBlackBoxDefs.length() > 0)
    {
      FILE* File = fopen(pBlackBoxFileName, "at");

      if (File != 0)
      {
        ::fprintf(File, "%s", sBlackBoxDefs.c_str());
        ::fclose(File);

        bBuilt = true;
      }
      else
      {
        ::unlink(pBlackBoxFileName);
      }
    }
    else
    {
      struct stat StatBuf;

      bBuilt = (::stat(pBlackBoxFileName, &StatBuf) == 0);
    }
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::flattenClass(const char* pClassName,
                                 const AdtParserPtrList& rGoalList,
                                 string& rUsesList)
{
  bool bFlattened = false;

  //Aggregate all uses clauses into one
  AdtParserPtrList  rOriginalUsesList;

  findObjects(rOriginalUsesList, "AdtDelphiUsesClause");

  AdtParserPtrListIter      UsesIter;
  AdtParserPtrByStringMap   rOriginalUsesIdentMap;
  AdtParserPtrByStringMap   rIncludedUsesIdentMap;

  //Find existing uses includes
  for (UsesIter = rOriginalUsesList.begin() ; UsesIter != rOriginalUsesList.end() ; ++UsesIter)
  {
    const AdtParser* pUsesClauseObj = *UsesIter;

    if (pUsesClauseObj != 0)
    {
      pUsesClauseObj->enumerateDescendantMap(rOriginalUsesIdentMap, "IdentifierList");
    }
  }

  //Find additional uses includes
  AdtParserPtrListConstIter GoalIter;

  for (GoalIter = rGoalList.begin() ; GoalIter != rGoalList.end() ; ++GoalIter)
  {
    const AdtParser* pIncludeGoalObj = *GoalIter;

    if (pIncludeGoalObj != 0)
    {
      AdtParserPtrList  rUsesList;

      pIncludeGoalObj->findObjects(rUsesList, "AdtDelphiUsesClause");

      for (UsesIter = rUsesList.begin() ; UsesIter != rUsesList.end() ; ++UsesIter)
      {
        const AdtParser* pUsesClauseObj = *UsesIter;

        if (pUsesClauseObj != 0)
        {
          pUsesClauseObj->enumerateDescendantMap(rIncludedUsesIdentMap, "IdentifierList");
        }
      }
    }
  }

  //Add uses includes that are not already in the root module
  AdtParserPtrByStringMapIter IncludesIter;

  for (IncludesIter = rIncludedUsesIdentMap.begin() ; IncludesIter != rIncludedUsesIdentMap.end() ; ++IncludesIter)
  {
    const string&   rName     = (*IncludesIter).first;
    AdtParser*      pIdentObj = (*IncludesIter).second;

    if ((pIdentObj != 0) && (rOriginalUsesIdentMap.find(rName) == rOriginalUsesIdentMap.end()))
    {
      //Add the include to the UsesClauses
      for (UsesIter = rOriginalUsesList.begin() ; UsesIter != rOriginalUsesList.end() ; ++UsesIter)
      {
        AdtParser* pUsesClauseObj = *UsesIter;

        if (pUsesClauseObj != 0)
        {
          AdtParser*  pObjCopy = pIdentObj->copy();

          pUsesClauseObj->add(pObjCopy);
          UtlReleaseReference(pObjCopy);
        }
      }

      rOriginalUsesIdentMap.insert(AdtParserPtrByStringMap::value_type(rName, AdtParserContext(pIdentObj)));
    }
  }

  //Build uses list string
  rUsesList = "";

  for (IncludesIter = rOriginalUsesIdentMap.begin() ; IncludesIter != rOriginalUsesIdentMap.end() ; ++IncludesIter)
  {
    const string& rName = (*IncludesIter).first;

    if (IncludesIter != rOriginalUsesIdentMap.begin())
    {
      rUsesList += ",";
    }

    rUsesList += rName;
  }

  //Flatten class
  if (pClassName != 0)
  {
    AdtDelphiClassType* pClassObject = 0;

    //Find class definition
    if (isClassType(ExportedTypeMap, pClassName, &pClassObject) |
        isClassType(LocalTypeMap, pClassName, &pClassObject))
    {
      bFlattened = pClassObject->flattenClass(this, rGoalList);

      LocalVariableMap.clear();
      LocalTypeMap.clear();
      LocalConstMap.clear();
      ImplementedProcedureMap.clear();

      clearSourceRoot();

      ExportedVariableMap.clear();
      ExportedTypeMap.clear();
      ExportedConstMap.clear();
      ExportedProcedureMap.clear();

      enumerateDescendantMap(LocalVariableMap,        "Program,Block,DeclSection,VarSection,VarDeclList;Library,Block,DeclSection,VarSection,VarDeclList;Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;");
      enumerateDescendantMap(LocalTypeMap,            "Program,Block,DeclSection,TypeSection,TypeDeclList;Library,Block,DeclSection,TypeSection,TypeDeclList;Unit,ImplementationSection,DeclSection,TypeSection,TypeDeclList;");
      enumerateDescendantMap(LocalConstMap,           "Program,Block,DeclSection,ConstSection,ConstantDeclList;Library,DeclSection,ConstSection,ConstantDeclList;Unit,ImplementationSection,DeclSection,ConstSection,ConstantDeclList;");
      enumerateDescendantMap(ImplementedProcedureMap, "Program,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Library,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Unit,ImplementationSection,DeclSection,ProcedureDeclSection,ProcedureDeclList;");

      enumerateDescendantMap(ExportedVariableMap,   "Unit,InterfaceSection,VarSection,VarDeclList");
      enumerateDescendantMap(ExportedTypeMap,       "Unit,InterfaceSection,TypeSection,TypeDeclList");
      enumerateDescendantMap(ExportedConstMap,      "Unit,InterfaceSection,ConstSection,ConstantDeclList");
      enumerateDescendantMap(ExportedProcedureMap,  "Unit,InterfaceSection,ExportedHeadingList");
    }
  }

  return (bFlattened);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::optimise(const AdtStringList& rNewMethodList,
                             const AdtStringByStringMap& rNewMethodMap)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::expandMacros()
{
  bool            bExpanded         = false;
  AdtDelphiGoal*  pDelphiRootObject = delphiRootObject();

  if (pDelphiRootObject != 0)
  {
    pDelphiRootObject->lock();
  }

  delphiRootObject((AdtDelphiGoal*)this);

  AdtParserPtrByStringMapIter   Iter;
  AdtParserPtrByStringMultiMap  rMacroMap;

  buildMacroMap(rMacroMap);

  for (Iter = ImplementedProcedureMap.begin() ; Iter != ImplementedProcedureMap.end() ; ++Iter)
  {
    AdtParser* pObject = (*Iter).second;

    if ((pObject != 0) && pObject->isType("AdtDelphiProcedureDecl"))
    {
      AdtParserPtrByStringMultiMap  rNamesMap;
      AdtDelphiProcedureDecl*       pProcedureDecl = (AdtDelphiProcedureDecl*)pObject;

      AdtDelphiMacro::forwardSubstitute(pProcedureDecl, rMacroMap);
    }
  }

  delphiRootObject(pDelphiRootObject);
  UtlReleaseReference(pDelphiRootObject);

  return (bExpanded);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiGoal::writeClassMethodsAsFortran(AdtFile& pOutFile,
                                                   const AdtFortranExecutableProgram* pSavedRoot,
                                                   const char* pClassName,
                                                   const char* pLastClassName,
                                                   bool bExpandMacros) const
{
  if ((pOutFile.isOpen()) && (pClassName != 0))
  {
    AdtParser* pClassObject = findObject("AdtDelphiTypeDecl", pClassName);

    if (pClassObject != 0)
    {
      bool                  bFirst = true;
      AdtParserPtrList      List;
      AdtParserPtrListIter  Iter;
      string                sMethodNames;

      pClassObject->findObjects(List, "AdtDelphiMethod");

      for (Iter = List.begin() ; Iter != List.end() ; ++Iter)
      {
        AdtParser*  pMethod = *Iter;

        if (pMethod != 0)
        {
          string sQualifiedName(pClassName);

          sQualifiedName += ".";
          sQualifiedName += pMethod->name();

          if (bFirst)
          {
            bFirst        = false;
          }
          else
          {
            sMethodNames += ",";
          }

          sMethodNames += sQualifiedName;
        }
      }

      writeFortran(pOutFile,
                   pSavedRoot,
                   pClassName,
                   pLastClassName,
                   sMethodNames,
                   bExpandMacros);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiGoal::writeFortran(AdtFile& pOutFile,
                                     const AdtFortranExecutableProgram* pSavedRoot,
                                     const char* pClassName,
                                     const char* pLastClassName,
                                     const char* pFunctionNames,
                                     bool bExpandMacros) const
{
  AdtDelphiGoal*  pDelphiRootObject = delphiRootObject();

  if (pDelphiRootObject != 0)
  {
    pDelphiRootObject->lock();
  }

  delphiRootObject((AdtDelphiGoal*)this);

  if ((pOutFile.isOpen()) && (pFunctionNames != 0))
  {
    AdtParserPtrByStringMap VarsMap;
    AdtParserPtrByStringMap ConstMap;
    AdtParserPtrByStringMap ProceduresMap;
    bool                    bCompiled = false;
    const char*             pStart    = pFunctionNames;
    const char*             pEnd      = 0;

    do
    {
      pEnd = ::strchr(pStart, ',');

      size_t  nLength = (pEnd == 0) ? ::strlen(pStart) : pEnd - pStart;
      string  FunctionName(pStart, 0, nLength);

      AdtParserPtrByStringMapConstIter Iter = ImplementedProcedureMap.find(FunctionName);

      if (Iter != ImplementedProcedureMap.end())
      {
        const AdtParser* pObject = (*Iter).second;

        if ((pObject != 0) && pObject->isType("AdtDelphiProcedureDecl"))
        {
          const AdtDelphiProcedureDecl* pProcedureDecl = (const AdtDelphiProcedureDecl*)pObject;

          if (compile(pProcedureDecl, ProceduresMap, VarsMap, ConstMap, bExpandMacros))
          {
            bCompiled = true;
          }
        }
      }

      pStart = pEnd + 1;
    }
    while (pEnd != 0);

    if (bCompiled)
    {
      AdtParserPtrByStringMapConstIter Iter;

      //Write Common module definition
      write(pOutFile, "MODULE Common");

      pOutFile.incrementIndent();
      pOutFile.newline();
      pOutFile.newline();

      writeArraySizes(pOutFile,
                      ProceduresMap,
                      VarsMap,
                      ConstMap);

      // Write all constant declarations irrespective of whether they are used
      // in the functions being exported in the module definition
      const AdtParserPtrByStringMap*  ConstMaps[] = {&ExportedConstMap,&LocalConstMap};

      for (int cn = 0 ; cn < (sizeof(ConstMaps) / sizeof(AdtParserPtrByStringMap*)) ; cn++)
      {
        const AdtParserPtrByStringMap&  rConstMap = *(ConstMaps[cn]);

        for (Iter = rConstMap.begin() ; Iter != rConstMap.end() ; ++Iter)
        {
          AdtParser* pObj = (*Iter).second;

          if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
          {
            AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

            pDelphiObj->writeFortran(pOutFile);
          }

          pOutFile.newline();
        }
      }

      for (Iter = VarsMap.begin() ; Iter != VarsMap.end() ; ++Iter)
      {
        AdtParser* pObj = (*Iter).second;

        if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
        {
          AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

          pDelphiObj->writeFortran(pOutFile);
        }

        pOutFile.newline();
      }

      pOutFile.decrementIndent();
      pOutFile.newline();

      write(pOutFile, "END");

      pOutFile.newline();
      pOutFile.newline();
      write(pOutFile, "! ----------------------------------------------------------------------------");
      pOutFile.newline();
      pOutFile.newline();

      //Write procedure definitions
      for (Iter = ProceduresMap.begin() ; Iter != ProceduresMap.end() ; ++Iter)
      {
        AdtParser* pObj = (*Iter).second;

        if ((pObj != 0) && pObj->isType("AdtDelphiBase"))
        {
          AdtDelphiBase* pDelphiObj = (AdtDelphiBase*)pObj;

          pDelphiObj->writeFortran(pOutFile);
        }
      }

      VarsMap.clear();
      ConstMap.clear();
      ProceduresMap.clear();
    }
    else
    {
      // Write Empty module definition. We need to because the fortran compiler
      // will throw an error for empty files
      write(pOutFile, "MODULE COMMON");
      pOutFile.newline();
      write(pOutFile, "END");
      pOutFile.newline();
    }

    if (0)
    {
      //Debugging stuff to print the parse tree of the macro definitions
      AdtFile MacrosFile;

      MacrosFile.open("Macros.txt", "wt");

      AdtParserPtrListConstIter Iter;

      for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
      {
        AdtParser* pObj = *Iter;

        if ((pObj != 0) && pObj->isType("AdtDelphiMacro"))
        {
          AdtDelphiMacro* pMacro = (AdtDelphiMacro*)pObj;

          MacrosFile.newline();
          MacrosFile.newline();
          MacrosFile.newline();

          pMacro->printDescendants(MacrosFile);
        }
      }
    }
  }

  delphiRootObject(pDelphiRootObject);
  UtlReleaseReference(pDelphiRootObject);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

const AdtDelphiProcedureDecl* AdtDelphiGoal::findProcedureDeclaration(const char* pFunctionName) const
{
  const AdtDelphiProcedureDecl* pProcedureDecl = 0;

  if (pFunctionName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = ImplementedProcedureMap.find(pFunctionName);

    if (Iter != ImplementedProcedureMap.end())
    {
      const AdtParser* pObject = (*Iter).second;

      if ((pObject != 0) && pObject->isType("AdtDelphiProcedureDecl"))
      {
        pProcedureDecl = (const AdtDelphiProcedureDecl*)pObject;
      }
    }
  }

  return (pProcedureDecl);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiGoal::writeDelphi(AdtFile& pOutFile, const char* pFunctionName) const
{
  const AdtDelphiProcedureDecl* pProcedureDecl = findProcedureDeclaration(pFunctionName);

  writeExpanded(pOutFile, comment());

  if ((pOutFile.isOpen()) && (pProcedureDecl != 0))
  {
    pProcedureDecl->writeDelphi(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiGoal::writeDelphi(AdtFile& pOutFile) const
{
  writeExpanded(pOutFile, comment());

  if (Program != 0)
  {
    Program->writeDelphi(pOutFile);
  }

  if (Package != 0)
  {
    Package->writeDelphi(pOutFile);
  }

  if (Library != 0)
  {
    Library->writeDelphi(pOutFile);
  }

  if (Unit != 0)
  {
    Unit->writeDelphi(pOutFile);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiGoal::writeNative(AdtFile& pOutFile) const
{
  return (writeDelphi(pOutFile));
}

//  ----------------------------------------------------------------------------

AdtSourceFileType AdtDelphiGoal::sourceFileType() const
{
  return (DelphiSourceFileType);
}

//  ----------------------------------------------------------------------------

void AdtDelphiGoal::extractClassConstructorName(const char* pConstructorDeclaration,
                                                string& rConstructorName) const
{
  rConstructorName = "";

  if (pConstructorDeclaration != 0)
  {
    size_t      nCount;
    const char* pChar = pConstructorDeclaration;

    while (*pChar != '\0')
    {
      nCount  = 0;
      pChar   = AdtParse::nextWord(pChar, &nCount);

      if (AdtParse::matchWord(pChar, "//"))
      {
        string  sComment;

        // Ignore singleline comment
        AdtParse::extractWord(sComment, "\n\r", pChar, true);
      }
      else if (AdtParse::matchWord(pChar, "{"))
      {
        string  sComment;

        // Ignore multiline comment
        AdtParse::extractWord(sComment, "}", pChar, true);
        AdtParse::matchWord(pChar, "}");
      }
      else if (AdtParse::matchWord(pChar, "(*"))
      {
        string  sComment;

        // Ignore multiline comment
        while (*pChar != '\0')
        {
          if (AdtParse::extractWord(sComment, "*", pChar, true))
          {
            AdtParse::matchWord(pChar, "*");

            if (AdtParse::matchWord(pChar, ")"))
            {
              break;
            }
          }
          else
          {
            break;
          }
        }
      }
      else if (AdtParse::matchWord(pChar, "constructor", false))
      {
        // Ignore this bit
      }
      else
      {
        string sInfo;

        // This goes into the name
        AdtParse::extractWord(sInfo, " \t", pChar, false);

        if (nCount != 0)
        {
          rConstructorName += " ";
        }

        rConstructorName += sInfo;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::extractClassConstructors(AdtStringList& rConstructorList,
                                             const char* pClassName,
                                             const char* pParentClassName,
                                             AdtSourceFileType nAsFileType) const
{
  bool bExtracted = AdtAutoClass::buildClassConstructor(rConstructorList,
                                                        pClassName,
                                                        pParentClassName,
                                                        nAsFileType);

  if (!bExtracted)
  {
    bool                      bAsCPP  = ((nAsFileType == CppSourceFileType) || (nAsFileType == CppHeaderFileType));
    const AdtDelphiClassType* pClass  = findClassType(pParentClassName);

    if (pClass != 0)
    {
      AdtParserPtrList      ObjectList;
      AdtParserPtrListIter  Iter;

      pClass->findObjects(ObjectList, "AdtDelphiConstructorHeading");

      bExtracted  = true;

      for (Iter = ObjectList.begin() ; Iter != ObjectList.end() ; ++Iter)
      {
        AdtDelphiConstructorHeading* pObj = (AdtDelphiConstructorHeading*)(AdtParser*)*Iter;

        if (pObj != 0)
        {
          string  rExtraction;
          string  sConstructorDeclaration;
          AdtFile StringOut;

          if (StringOut.open(sConstructorDeclaration))
          {
            if (bAsCPP)
            {
              pObj->writeCPP(StringOut);
            }
            else
            {
              pObj->writeDelphi(StringOut);
              StringOut.write(";");
            }

            StringOut.close();

            extractClassConstructorName(sConstructorDeclaration, rExtraction);
          }

          rConstructorList.push_back(rExtraction);

          string  sConstructorCall;

          if (StringOut.open(sConstructorCall))
          {
            if (bAsCPP)
            {
              pObj->writeCPP(StringOut, 1);
            }
            else
            {
              pObj->writeDelphi(StringOut, 1);
              StringOut.write(";");
            }

            StringOut.close();

            extractClassConstructorName(sConstructorCall, rExtraction);
          }

          rConstructorList.push_back(rExtraction);
        }
      }
    }
  }

  return (bExtracted);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::isProcedure(const char* pProcedureName) const
{
  const AdtDelphiProcedureDecl* pProcedureDecl  = findProcedureDeclaration(pProcedureName);
  bool                          bIsProcedure    = false;

  if (pProcedureDecl != 0)
  {
    bIsProcedure = pProcedureDecl->hasType("AdtDelphiProcedureHeading");
  }

  return (bIsProcedure);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::isFunction(const char* pFunctionName) const
{
  const AdtDelphiProcedureDecl* pProcedureDecl  = findProcedureDeclaration(pFunctionName);
  bool                          bIsFunction     = false;

  if (pProcedureDecl != 0)
  {
    bIsFunction = pProcedureDecl->hasType("AdtDelphiFunctionHeading");
  }

  return (bIsFunction);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::isClassType(const char* pClassName) const
{
  bool bHasClassType = isClassType(ExportedTypeMap, pClassName) |
                       isClassType(LocalTypeMap, pClassName);

  return (bHasClassType);
}

//  ----------------------------------------------------------------------------

const AdtDelphiClassType* AdtDelphiGoal::findClassType(const char* pClassName) const
{
  AdtDelphiClassType* pClassObject = 0;

  if (!isClassType(ExportedTypeMap, pClassName, &pClassObject))
  {
    isClassType(LocalTypeMap, pClassName, &pClassObject);
  }

  return (pClassObject);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiGoal::writeClassPrefix(AdtFile& pOutFile, const char* pFunctionName) const
{
  const char* pClassContext = classContext();
  bool        bWritten      = false;

  if (pClassContext != 0)
  {
    const AdtParser* pExternal = 0;

    if (isIncludeFunction(pFunctionName)    ||
        isIncludeSubroutine(pFunctionName)  ||
        findObject(ImplementedProcedureMap, string(pClassContext) + "." + pFunctionName, pExternal))
    {
      write(pOutFile, pClassContext);
      write(pOutFile, "__");

      bWritten = true;
    }
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiGoal, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProgram method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProgram::AdtDelphiProgram(AdtParser* pIdentObj,
                                   AdtParser* pIdentListObj,
                                   AdtParser* pUsesClauseObj,
                                   AdtParser* pBlockObj,
                                   const char* pComment)
 : AdtDelphiBase()
{
  initObject(Identifier,      pIdentObj,      AdtDelphiIdent,       true);
  initObject(IdentifierList,  pIdentListObj,  AdtDelphiIdentList,   true);
  initObject(UsesClause,      pUsesClauseObj, AdtDelphiUsesClause,  true);
  initObject(Block,           pBlockObj,      AdtDelphiBlock,       true);

  if (Identifier != 0)
  {
    name(Identifier->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiProgram::AdtDelphiProgram(const AdtDelphiProgram& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Identifier,     rCopy, AdtDelphiIdent);
  copyObject(IdentifierList, rCopy, AdtDelphiIdentList);
  copyObject(UsesClause,     rCopy, AdtDelphiUsesClause);
  copyObject(Block,          rCopy, AdtDelphiBlock);
}

//  ----------------------------------------------------------------------------

AdtDelphiProgram::~AdtDelphiProgram()
{
  UtlReleaseReference(Identifier);
  UtlReleaseReference(IdentifierList);
  UtlReleaseReference(UsesClause);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProgram::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "program ");

  if (Identifier != 0)
  {
    Identifier->writeDelphi(pOutFile, nMode);

    if (IdentifierList != 0)
    {
      write(pOutFile, "(");
      IdentifierList->writeDelphi(pOutFile, nMode);
      write(pOutFile, ")");
    }
  }

  write(pOutFile, ";");
  pOutFile.newline();
  pOutFile.newline();

  if (UsesClause != 0)
  {
    UsesClause->writeDelphi(pOutFile, nMode);
    pOutFile.newline();
  }

  if (Block != 0)
  {
    Block->writeDelphi(pOutFile, nMode);
    pOutFile.newline();
  }

  write(pOutFile, ".");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProgram, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiUnit method implementations
//  ----------------------------------------------------------------------------
AdtDelphiUnit::AdtDelphiUnit(AdtParser* pIdentObj,
                             AdtParser* pInterfaceSectionObj,
                             AdtParser* pImplementationSectionObj,
                             AdtParser* pInitSectionObj,
                             const char* pComment)
 : AdtDelphiBase()
{
  initObject(Identifier,            pIdentObj,                  AdtDelphiIdent,                 true);
  initObject(InterfaceSection,      pInterfaceSectionObj,       AdtDelphiInterfaceSection,      true);
  initObject(ImplementationSection, pImplementationSectionObj,  AdtDelphiImplementationSection, true);
  initObject(InitSection,           pInitSectionObj,            AdtDelphiInitSection,           true);

  if (Identifier != 0)
  {
    name(Identifier->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiUnit::AdtDelphiUnit(const AdtDelphiUnit& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Identifier,            rCopy, AdtDelphiIdent);
  copyObject(InterfaceSection,      rCopy, AdtDelphiInterfaceSection);
  copyObject(ImplementationSection, rCopy, AdtDelphiImplementationSection);
  copyObject(InitSection,           rCopy, AdtDelphiInitSection);
}

//  ----------------------------------------------------------------------------

AdtDelphiUnit::~AdtDelphiUnit()
{
  UtlReleaseReference(Identifier);
  UtlReleaseReference(InterfaceSection);
  UtlReleaseReference(ImplementationSection);
  UtlReleaseReference(InitSection);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiUnit::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "unit ");

  if (Identifier != 0)
  {
    Identifier->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();
  pOutFile.newline();

  if (InterfaceSection != 0)
  {
    InterfaceSection->writeDelphi(pOutFile, nMode);
  }

  if (ImplementationSection != 0)
  {
    ImplementationSection->writeDelphi(pOutFile, nMode);
  }

  if (InitSection != 0)
  {
    InitSection->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ".");
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiUnit, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiPackage method implementations
//  ----------------------------------------------------------------------------
AdtDelphiPackage::AdtDelphiPackage(AdtParser* pIdentObj,
                                   AdtParser* pRequiresIdentListObj,
                                   AdtParser* pContainsIdentListObj,
                                   const char* pComment)
: AdtDelphiBase()
{
  initObject(Identifier,        pIdentObj,             AdtDelphiIdent,     true);
  initObject(RequiresIdentList, pRequiresIdentListObj, AdtDelphiIdentList, true);
  initObject(ContainsIdentList, pContainsIdentListObj, AdtDelphiIdentList, true);

  if (Identifier != 0)
  {
    name(Identifier->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiPackage::AdtDelphiPackage(const AdtDelphiPackage& rCopy)
: AdtDelphiBase(rCopy)
{
  copyObject(Identifier,        rCopy, AdtDelphiIdent);
  copyObject(RequiresIdentList, rCopy, AdtDelphiIdentList);
  copyObject(ContainsIdentList, rCopy, AdtDelphiIdentList);
}

//  ----------------------------------------------------------------------------

AdtDelphiPackage::~AdtDelphiPackage()
{
  UtlReleaseReference(Identifier);
  UtlReleaseReference(RequiresIdentList);
  UtlReleaseReference(ContainsIdentList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPackage::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "package ");

  pOutFile.incrementIndent();

  if (Identifier != 0)
  {
    Identifier->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();
  pOutFile.newline();

  if (RequiresIdentList != 0)
  {
    write(pOutFile, "requires ");

    RequiresIdentList->writeDelphi(pOutFile, nMode);

    if (ContainsIdentList != 0)
    {
      pOutFile.newline();
    }
  }

  if (ContainsIdentList != 0)
  {
    write(pOutFile, "contains ");

    ContainsIdentList->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  pOutFile.decrementIndent();

  write(pOutFile, "end.");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiPackage, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiLibrary method implementations
//  ----------------------------------------------------------------------------
AdtDelphiLibrary::AdtDelphiLibrary(AdtParser* pIdentObj,
                                   AdtParser* pUsesClauseObj,
                                   AdtParser* pBlockObj,
                                   const char* pComment)
: AdtDelphiBase()
{
  initObject(Identifier,  pIdentObj,      AdtDelphiIdent,       true);
  initObject(UsesClause,  pUsesClauseObj, AdtDelphiUsesClause,  true);
  initObject(Block,       pBlockObj,      AdtDelphiBlock,       true);

  if (Identifier != 0)
  {
    name(Identifier->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiLibrary::AdtDelphiLibrary(const AdtDelphiLibrary& rCopy)
: AdtDelphiBase(rCopy)
{
  copyObject(Identifier, rCopy, AdtDelphiIdent);
  copyObject(UsesClause, rCopy, AdtDelphiUsesClause);
  copyObject(Block,      rCopy, AdtDelphiBlock);
}

//  ----------------------------------------------------------------------------

AdtDelphiLibrary::~AdtDelphiLibrary()
{
  UtlReleaseReference(Identifier);
  UtlReleaseReference(UsesClause);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiLibrary::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "library ");

  pOutFile.incrementIndent();

  if (Identifier != 0)
  {
    Identifier->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ";");
  pOutFile.newline();
  pOutFile.newline();

  if (UsesClause != 0)
  {
    UsesClause->writeDelphi(pOutFile, nMode);

    if (Block != 0)
    {
      pOutFile.newline();
    }
  }

  if (Block != 0)
  {
    Block->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  pOutFile.decrementIndent();

  write(pOutFile, ".");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiLibrary, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiMacro method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiMacro::substituteArguments(AdtParser* pObj, AdtDelphiExprList* pMacroParamList) const
{
  if ((pObj             != 0) &&
      (ExprList         != 0) &&
      (pMacroParamList  != 0))
  {
    size_t nArg;
    size_t nArgs = ExprList->listSize();

    for (nArg = 0 ; nArg < nArgs ; nArg++)
    {
      AdtParser*      pArgRoot    = ExprList->object(nArg);
      AdtDelphiBase*  pParamRoot  = (AdtDelphiBase*)pMacroParamList->object(nArg);

      if ((pArgRoot   != 0) &&
          (pParamRoot != 0))
      {
        AdtParserPtrListIter  Iter;
        AdtParserPtrList      FoundList;
        AdtParser*            pArgBottom;
        string                sCodeString;
        AdtFile               rDelphiFile;

        // Create the substitution argument as a string
        rDelphiFile.open(sCodeString);
        pParamRoot->writeDelphi(rDelphiFile);
        rDelphiFile.close();

        // Find the bottommost identifier
        pArgRoot->findObjects(FoundList, "AdtDelphiIdent");

        FoundList.sort();
        FoundList.reverse();

        Iter        = FoundList.begin();
        pArgBottom  = *Iter;

        FoundList.clear();

        // Find all AdtDelphiIdent values to replace
        pObj->findObjects(FoundList, pArgBottom->type(), pArgBottom->name(), false);

        // We sort the list into descending depth so that the deepest nested argument
        // replacement is handled first. In that way we are assured that any nested
        // macros will be sustituted correctly.
        FoundList.sort();
        FoundList.reverse();

        for (Iter = FoundList.begin() ; Iter != FoundList.end() ; ++Iter)
        {
          AdtDelphiIdent* pIdent = (AdtDelphiIdent*)(AdtParser*)*Iter;

          if (pIdent != 0)
          {
            // Replace the macro parameter with the substitution argument string.
            // Note that whilst this is a technically incorrect parse tree, this
            // approach will always yield syntactically correct substituted code
            // when printed using the writeDelphi method, so we use this approach
            // here. Upon re-compilation of the code (which we always do after
            // macro substitution) the correct parse tree will be obtained.
            pIdent->name(sCodeString);
          }
        }

        FoundList.clear();
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiMacro::expandMacro(AdtParser* pRoot, AdtDelphiExprList* pMacroArgList) const
{
  if ((pRoot != 0) && (pMacroArgList != 0))
  {
    if (pRoot->isType("AdtDelphiFactor"))
    {
      AdtDelphiFactor*  pFactor = (AdtDelphiFactor*)pRoot;

      if (Expression != 0)
      {
        AdtDelphiExpression*  pExpressionCopy = new AdtDelphiExpression(*Expression);

        if (pExpressionCopy != 0)
        {
          substituteArguments(pExpressionCopy, pMacroArgList);
          pFactor->substituteMacroExpression(pExpressionCopy);
        }

        UtlReleaseReference(pExpressionCopy);
      }
      else if (Designator != 0)
      {
        AdtDelphiDesignator*  pDesignatorCopy = new AdtDelphiDesignator(*Designator);

        if (pDesignatorCopy != 0)
        {
          substituteArguments(pDesignatorCopy, pMacroArgList);
          pFactor->substituteMacroDesignator(pDesignatorCopy);
        }

        UtlReleaseReference(pDesignatorCopy);
      }
    }
    else if (pRoot->isType("AdtDelphiStatement"))
    {
      AdtDelphiStatement*  pStatement = (AdtDelphiStatement*)pRoot;

      if (StmtList != 0)
      {
        AdtDelphiStmtList*  pStmtListCopy = new AdtDelphiStmtList(*StmtList);

        if (pStmtListCopy != 0)
        {
          //If parent of Statement is StmtList then remove Statement from the
          //list and add the contents of the macro StmtList to it, otherwise
          //Leave Statement in place but add the contents of the macro StmtList
          //to it as a compound statement. Simple huh!
          AdtParser* pParent = pStatement->parent();

          substituteArguments(pStmtListCopy, pMacroArgList);

          if ((pParent              != 0) &&
              pParent->isType("AdtDelphiStmtList"))
          {
            //Remove Statement from the list and add contents of StmtList
            pParent->replace(pStatement, pStmtListCopy);
          }
          else
          {
            //Add StmtList to Statement as a compound statement
            pStatement->substituteMacroCompoundStatement(pStmtListCopy);
          }

          UtlReleaseReference(pStmtListCopy);
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiMacro::addVariables(AdtDelphiProcedureDecl* pProcedureDecl) const
{
  AdtParserPtrByStringMap rAddVarDeclMap;

  enumerateDescendantMap(rAddVarDeclMap, "VarDeclList");

  if (!rAddVarDeclMap.empty())
  {
    AdtParserPtrByStringMap     rVarDeclMap;
    AdtDelphiVarDeclList*       pVarDeclList = 0;

    pProcedureDecl->enumerateDescendantMap(rVarDeclMap, "Block,DeclSection,VarSection,VarDeclList");
    pVarDeclList = (AdtDelphiVarDeclList*)pProcedureDecl->findDescendant("Block,DeclSection,VarSection,VarDeclList");

    if (pVarDeclList != 0)
    {
      AdtParserPtrByStringMapIter Iter;

      for (Iter = rAddVarDeclMap.begin() ; Iter != rAddVarDeclMap.end() ; ++Iter)
      {
        const char* pKey = (*Iter).first;

        if (rVarDeclMap.end() == rVarDeclMap.find(pKey))
        {
          //Not defined so we can add it.
          if ((*Iter).second.object()->isType("AdtDelphiVarDecl"))
          {
            AdtDelphiVarDecl* pVarDecl = (AdtDelphiVarDecl*)(*Iter).second.object()->copy();

            if (pVarDecl != 0)
            {
              AdtParser* pIdentList = pVarDecl->findDescendant("IdentList");

              if (pIdentList != 0)
              {
                pIdentList->removeAllExcept(pKey);
              }

              pVarDeclList->add(pVarDecl);
              UtlReleaseReference(pVarDecl);
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtParser* AdtDelphiMacro::findCollapsedMacroRoot(AdtParser* pObject, AdtDelphiExprList** ppExpressionList) const
{
  AdtParser* pRoot = 0;

  if ((pObject != 0) && (ExprList != 0))
  {
    AdtParser* pParent = pObject->parent();

    if ((pParent              != 0) &&
        pParent->isType("AdtDelphiDesignatorObj"))
    {
      AdtDelphiDesignatorObj* pDesignatorObj = (AdtDelphiDesignatorObj*)pParent;

      if (pDesignatorObj->isMacroReplaceable(ExprList->listSize(), ppExpressionList))
      {
        pParent = pParent->parent();

        if ((pParent              != 0) &&
            (pParent->listSize()  == 1) &&
            pParent->isType("AdtDelphiDesignatorObjList"))
        {
          pParent = pParent->parent();

          if ((pParent != 0) &&
              pParent->isType("AdtDelphiDesignator"))
          {
            pParent = pParent->parent();

            if (pParent != 0)
            {
              if (pParent->isType("AdtDelphiFactor"))
              {
                if (Expression != 0)
                {
                  ASSERT(StmtList == 0);

                  pRoot = pParent;
                }
                else if (Designator != 0)
                {
                  pRoot = pParent;
                }
                else
                {
                  ::printf("ERROR: Incompatible macro replacement, %s\n", name().c_str());
                  AdtExit(-1);
                  pRoot = 0;
                }
              }
              else if (pParent->isType("AdtDelphiSimpleStatement"))
              {
                pParent = pParent->parent();

                if ((pParent != 0) &&
                    pParent->isType("AdtDelphiStatement"))
                {
                  pRoot = pParent;

                  if (StmtList != 0)
                  {
                    ASSERT(Expression == 0);

                    pRoot = pParent;
                  }
                  else
                  {
                    ::printf("ERROR: Incompatible macro replacement, %s\n", name().c_str());
                    AdtExit(-1);
                    pRoot = 0;
                  }
                }
              }
              else
              {
                ::printf("ERROR: Incompatible macro replacement, %s\n", name().c_str());
                AdtExit(-1);
                pRoot = 0;
              }
            }
          }
        }
      }
    }
  }

  return (pRoot);
}

//  ----------------------------------------------------------------------------

AdtDelphiMacro::AdtDelphiMacro(AdtParser* pIdentObj,
                               AdtParser* pExprListObj,
                               AdtParser* pExpressionObj,
                               AdtParser* pStmtListObj,
                               AdtParser* pVarDeclListObj)
 : AdtDelphiBase()
{
  initObject(Identifier,  pIdentObj,        AdtDelphiIdent,       true);
  initObject(ExprList,    pExprListObj,     AdtDelphiExprList,    true);
  initObject(Expression,  pExpressionObj,   AdtDelphiExpression,  true);
  initObject(StmtList,    pStmtListObj,     AdtDelphiStmtList,    true);
  initObject(VarDeclList, pVarDeclListObj,  AdtDelphiVarDeclList, true);

  Designator = 0;

  if (Identifier != 0)
  {
    name(Identifier->name());
  }

  //This piece of code is needed to extract the designator from a single
  //statement since expression substition requires an expression or designator
  //and some macros such as,
  //
  //#define ln(a)         LOG(a)
  //
  //compile to a statement list though the context of use is as a designator.
  if ((Expression           == 0) &&
      (Designator           == 0) &&
      (StmtList             != 0) &&
      (StmtList->listSize() == 1))
  {
    //Should also check the statement type in the list as constructs such as
    //for, while, if, switch etc are all single statements though they are
    //of a compound type and are therefore not appropriate for expression
    //substitution.
    AdtParser*  pDesignatorObj = StmtList->findObject("AdtDelphiDesignator");

    if ((pDesignatorObj != 0) && pDesignatorObj->isType("AdtDelphiDesignator"))
    {
      Designator = (AdtDelphiDesignator*)pDesignatorObj;
      Designator->lock();
    }
  }

  depth(0, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiMacro::AdtDelphiMacro(const AdtDelphiMacro& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Identifier,  rCopy, AdtDelphiIdent);
  copyObject(ExprList,    rCopy, AdtDelphiExprList);
  copyObject(Expression,  rCopy, AdtDelphiExpression);
  copyObject(StmtList,    rCopy, AdtDelphiStmtList);
  copyObject(VarDeclList, rCopy, AdtDelphiVarDeclList);
  copyObject(Designator,  rCopy, AdtDelphiDesignator);
}

//  ----------------------------------------------------------------------------

AdtDelphiMacro::~AdtDelphiMacro()
{
  UtlReleaseReference(Identifier);
  UtlReleaseReference(ExprList);
  UtlReleaseReference(Expression);
  UtlReleaseReference(StmtList);
  UtlReleaseReference(VarDeclList);
  UtlReleaseReference(Designator);
}

//  ----------------------------------------------------------------------------

void AdtDelphiMacro::forwardSubstitute(AdtDelphiProcedureDecl* pProcedureDecl,
                                       AdtParserPtrByStringMultiMap& rMacroMap)
{
  if (pProcedureDecl != 0)
  {
    AdtParserPtrList              NameList;
    AdtParserPtrList              FoundList;
    AdtParserPtrListIter          Iter;

    pProcedureDecl->findObjects(NameList, "AdtDelphiIdent", 0, false);

    // Optimise substitution by eliminating all name objects that don't require
    // substitution
    for (Iter = NameList.begin() ; Iter != NameList.end() ; ++Iter)
    {
      AdtParser*  pNameObj = *Iter;

      if (pNameObj != 0)
      {
        string  sKey(pNameObj->name());

        sKey.toUpper();

        if (rMacroMap.find(sKey) != rMacroMap.end())
        {
          FoundList.push_back(pNameObj);
        }
      }
    }

    //We sort the list into descending depth so that the deepest nested macro
    //replacement is handled first. In that way we are assured that any nested
    //macros will be sustituted correctly.
    FoundList.sort();
    FoundList.reverse();

    for (Iter = FoundList.begin() ; Iter != FoundList.end() ; ++Iter)
    {
      AdtParser*  pNameObj = *Iter;

      if (pNameObj != 0)
      {
        bool                              bExpanded = false;
        AdtParserPtrByStringMultiMapIter  rMacroIter;
        string                            sKey(pNameObj->name());

        sKey.toUpper();

        for (rMacroIter = rMacroMap.lower_bound(sKey) ; rMacroIter != rMacroMap.upper_bound(sKey) ; ++rMacroIter)
        {
          AdtDelphiMacro* pMacro = (AdtDelphiMacro*)(AdtParser*)(*rMacroIter).second;

          if (pMacro != 0)
          {
            AdtDelphiExprList*  pMacroArgList = 0;
            AdtParser*          pRoot         = pMacro->findCollapsedMacroRoot(pNameObj, &pMacroArgList);

            if (pRoot != 0)
            {
              pMacro->expandMacro(pRoot, pMacroArgList);

              //Add any variable definitions made by the macro
              pMacro->addVariables(pProcedureDecl);
              bExpanded = true;
              break;
            }
          }
        }

        ASSERT(bExpanded);
      }
    }

    FoundList.clear();
  }
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiMacro, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiUsesClause method implementations
//  ----------------------------------------------------------------------------
AdtDelphiUsesClause::AdtDelphiUsesClause(AdtParser* pIdentListObj,
                                         const char* pComment)
: AdtDelphiBase()
{
  initObject(IdentifierList, pIdentListObj, AdtDelphiIdentList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiUsesClause::AdtDelphiUsesClause(const AdtDelphiUsesClause& rCopy)
: AdtDelphiBase(rCopy)
{
  copyObject(IdentifierList, rCopy, AdtDelphiIdentList);
}

//  ----------------------------------------------------------------------------

AdtDelphiUsesClause::~AdtDelphiUsesClause()
{
  UtlReleaseReference(IdentifierList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiUsesClause::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentifierList != 0)
  {
    write(pOutFile, "uses ");

    IdentifierList->writeDelphi(pOutFile, nMode);

    write(pOutFile, ";");
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiUsesClause, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiInterfaceSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiInterfaceSection::AdtDelphiInterfaceSection(AdtParser* pUsesClauseObj,
                                                     AdtParser* pConstSectionObj,
                                                     AdtParser* pTypeSectionObj,
                                                     AdtParser* pVarSectionObj,
                                                     AdtParser* pExportedHeadingListObj,
                                                     const char* pComment)
: AdtDelphiBase()
{
  initObject(UsesClause,          pUsesClauseObj,           AdtDelphiUsesClause,          true);
  initObject(ConstSection,        pConstSectionObj,         AdtDelphiConstSection,        true);
  initObject(TypeSection,         pTypeSectionObj,          AdtDelphiTypeSection,         true);
  initObject(VarSection,          pVarSectionObj,           AdtDelphiVarSection,          true);
  initObject(ExportedHeadingList, pExportedHeadingListObj,  AdtDelphiExportedHeadingList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiInterfaceSection::AdtDelphiInterfaceSection(const AdtDelphiInterfaceSection& rCopy)
: AdtDelphiBase(rCopy)
{
  copyObject(UsesClause,          rCopy, AdtDelphiUsesClause);
  copyObject(ConstSection,        rCopy, AdtDelphiConstSection);
  copyObject(TypeSection,         rCopy, AdtDelphiTypeSection);
  copyObject(VarSection,          rCopy, AdtDelphiVarSection);
  copyObject(ExportedHeadingList, rCopy, AdtDelphiExportedHeadingList);
}

//  ----------------------------------------------------------------------------

AdtDelphiInterfaceSection::~AdtDelphiInterfaceSection()
{
  UtlReleaseReference(UsesClause);
  UtlReleaseReference(ConstSection);
  UtlReleaseReference(TypeSection);
  UtlReleaseReference(VarSection);
  UtlReleaseReference(ExportedHeadingList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiInterfaceSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "interface ");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (UsesClause != 0)
  {
    UsesClause->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (ConstSection != 0)
  {
    ConstSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (TypeSection != 0)
  {
    TypeSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (VarSection != 0)
  {
    VarSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (ExportedHeadingList != 0)
  {
    ExportedHeadingList->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiInterfaceSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExportedHeadingList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExportedHeadingList::AdtDelphiExportedHeadingList(AdtParser* pExportedHeadingObj)
: AdtDelphiBase()
{
  add(pExportedHeadingObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiExportedHeadingList::AdtDelphiExportedHeadingList(const AdtDelphiExportedHeadingList& rCopy)
: AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiExportedHeadingList::~AdtDelphiExportedHeadingList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExportedHeadingList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExportedHeading method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExportedHeading::AdtDelphiExportedHeading(AdtParser* pProcedureHeadingObj,
                                                   AdtParser* pFunctionHeadingObj,
                                                   AdtParser* pDirectiveListObj,
                                                   const char* pComment)
: AdtDelphiBase()
{
  initObject(ProcedureHeading,  pProcedureHeadingObj, AdtDelphiProcedureHeading,  true);
  initObject(FunctionHeading,   pFunctionHeadingObj,  AdtDelphiFunctionHeading,   true);
  initObject(DirectiveList,     pDirectiveListObj,    AdtDelphiDirectiveList,     true);

  if (ProcedureHeading != 0)
  {
    name(ProcedureHeading->name());
  }
  else if (FunctionHeading != 0)
  {
    name(FunctionHeading->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiExportedHeading::AdtDelphiExportedHeading(const AdtDelphiExportedHeading& rCopy)
: AdtDelphiBase(rCopy)
{
  copyObject(ProcedureHeading, rCopy, AdtDelphiProcedureHeading);
  copyObject(FunctionHeading,  rCopy, AdtDelphiFunctionHeading);
  copyObject(DirectiveList,    rCopy, AdtDelphiDirectiveList);
}

//  ----------------------------------------------------------------------------

AdtDelphiExportedHeading::~AdtDelphiExportedHeading()
{
  UtlReleaseReference(ProcedureHeading);
  UtlReleaseReference(FunctionHeading);
  UtlReleaseReference(DirectiveList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExportedHeading::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ProcedureHeading != 0)
  {
    ProcedureHeading->writeDelphi(pOutFile, nMode);

    write(pOutFile, "; ");
  }

  if (FunctionHeading != 0)
  {
    FunctionHeading->writeDelphi(pOutFile, nMode);

    write(pOutFile, "; ");
  }

  if (DirectiveList != 0)
  {
    DirectiveList->writeDelphi(pOutFile, nMode);

    write(pOutFile, "; ");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExportedHeading, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiImplementationSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiImplementationSection::AdtDelphiImplementationSection(AdtParser* pUsesClauseObj,
                                                               AdtParser* pDeclSectionObj,
                                                               const char* pComment)
 : AdtDelphiBase()
{
  initObject(UsesClause,  pUsesClauseObj,   AdtDelphiUsesClause,  true);
  initObject(DeclSection, pDeclSectionObj,  AdtDelphiDeclSection, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiImplementationSection::AdtDelphiImplementationSection(const AdtDelphiImplementationSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(UsesClause,  rCopy, AdtDelphiUsesClause);
  copyObject(DeclSection, rCopy, AdtDelphiDeclSection);
}

//  ----------------------------------------------------------------------------

AdtDelphiImplementationSection::~AdtDelphiImplementationSection()
{
  UtlReleaseReference(UsesClause);
  UtlReleaseReference(DeclSection);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiImplementationSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "implementation");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (UsesClause != 0)
  {
    UsesClause->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (DeclSection != 0)
  {
    DeclSection->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiImplementationSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiBlock method implementations
//  ----------------------------------------------------------------------------
AdtDelphiBlock::AdtDelphiBlock(AdtParser* pDeclSectionObj,
                               AdtParser* pCompoundStmtObj,
                               const char* pComment)
 : AdtDelphiBase()
{
  initObject(DeclSection,   pDeclSectionObj,  AdtDelphiDeclSection,   true);
  initObject(CompoundStmt,  pCompoundStmtObj, AdtDelphiCompoundStmt,  true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiBlock::AdtDelphiBlock(const AdtDelphiBlock& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(DeclSection,  rCopy, AdtDelphiDeclSection);
  copyObject(CompoundStmt, rCopy, AdtDelphiCompoundStmt);
}

//  ----------------------------------------------------------------------------

AdtDelphiBlock::~AdtDelphiBlock()
{
  UtlReleaseReference(DeclSection);
  UtlReleaseReference(CompoundStmt);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiBlock::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (DeclSection != 0)
  {
    DeclSection->writeFortran(pOutFile, nMode);

    pOutFile.newline();
  }

  if (CompoundStmt != 0)
  {
    CompoundStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiBlock::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (DeclSection != 0)
  {
    DeclSection->writeDelphi(pOutFile, nMode);
  }

  if (CompoundStmt != 0)
  {
    CompoundStmt->writeDelphi(pOutFile, nMode);

    pOutFile.delayedNewlines(1);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiBlock, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDeclSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDeclSection::AdtDelphiDeclSection(AdtParser* pLabelDeclSectionObj,
                                           AdtParser* pConstSectionObj,
                                           AdtParser* pTypeSectionObj,
                                           AdtParser* pVarSectionObj,
                                           AdtParser* pProcedureDeclSectionObj,
                                           const char* pComment)
 : AdtDelphiBase()
{
  initObject(LabelDeclSection,      pLabelDeclSectionObj,     AdtDelphiLabelDeclSection,      true);
  initObject(ConstSection,          pConstSectionObj,         AdtDelphiConstSection,          true);
  initObject(TypeSection,           pTypeSectionObj,          AdtDelphiTypeSection,           true);
  initObject(VarSection,            pVarSectionObj,           AdtDelphiVarSection,            true);
  initObject(ProcedureDeclSection,  pProcedureDeclSectionObj, AdtDelphiProcedureDeclSection,  true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiDeclSection::AdtDelphiDeclSection(const AdtDelphiDeclSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(LabelDeclSection,     rCopy, AdtDelphiLabelDeclSection);
  copyObject(ConstSection,         rCopy, AdtDelphiConstSection);
  copyObject(TypeSection,          rCopy, AdtDelphiTypeSection);
  copyObject(VarSection,           rCopy, AdtDelphiVarSection);
  copyObject(ProcedureDeclSection, rCopy, AdtDelphiProcedureDeclSection);
}

//  ----------------------------------------------------------------------------

AdtDelphiDeclSection::~AdtDelphiDeclSection()
{
  UtlReleaseReference(LabelDeclSection);
  UtlReleaseReference(ConstSection);
  UtlReleaseReference(TypeSection);
  UtlReleaseReference(VarSection);
  UtlReleaseReference(ProcedureDeclSection);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDeclSection::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (LabelDeclSection != 0)
  {
    ::printf("WARNING: Translation of Pascal labels on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());
  }

  if (ConstSection != 0)
  {
    ConstSection->writeFortran(pOutFile, nMode);
  }

  if (TypeSection != 0)
  {
    ::printf("WARNING: Translation of Pascal Type section on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());
  }

  if (VarSection != 0)
  {
    VarSection->writeFortran(pOutFile, nMode);
  }

  if (ProcedureDeclSection != 0)
  {
    ProcedureDeclSection->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDeclSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LabelDeclSection != 0)
  {
    LabelDeclSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (ConstSection != 0)
  {
    ConstSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (TypeSection != 0)
  {
    TypeSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (VarSection != 0)
  {
    VarSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  if (ProcedureDeclSection != 0)
  {
    ProcedureDeclSection->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDeclSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDeclSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiLabelDeclSection::AdtDelphiLabelDeclSection(AdtParser* pLabelDeclListObj)
 : AdtDelphiBase()
{
  initObject(LabelDeclList, pLabelDeclListObj, AdtDelphiLabelDeclList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDeclSection::AdtDelphiLabelDeclSection(const AdtDelphiLabelDeclSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(LabelDeclList, rCopy, AdtDelphiLabelDeclList);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDeclSection::~AdtDelphiLabelDeclSection()
{
  UtlReleaseReference(LabelDeclList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiLabelDeclSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LabelDeclList != 0)
  {
    LabelDeclList->writeDelphi(pOutFile, nMode);

    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiLabelDeclSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiLabelDeclList::AdtDelphiLabelDeclList(AdtParser* pLabelDeclObj)
 : AdtDelphiBase()
{
  add(pLabelDeclObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDeclList::AdtDelphiLabelDeclList(const AdtDelphiLabelDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDeclList::~AdtDelphiLabelDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiLabelDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDecl method implementations
//  ----------------------------------------------------------------------------
AdtDelphiLabelDecl::AdtDelphiLabelDecl(AdtParser* pLabelIdObj,
                                       const char* pComment)
 : AdtDelphiBase()
{
  initObject(LabelId, pLabelIdObj, AdtDelphiLabelId, true);

  if (LabelId != 0)
  {
    name(LabelId->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDecl::AdtDelphiLabelDecl(const AdtDelphiLabelDecl& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(LabelId, rCopy, AdtDelphiLabelId);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelDecl::~AdtDelphiLabelDecl()
{
  UtlReleaseReference(LabelId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiLabelDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LabelId != 0)
  {
    write(pOutFile, "label ");
    LabelId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiLabelDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstSection::AdtDelphiConstSection(AdtParser* pConstantDeclListObj,
                                             const char* pComment)
 : AdtDelphiBase()
{
  initObject(ConstantDeclList, pConstantDeclListObj, AdtDelphiConstantDeclList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstSection::AdtDelphiConstSection(const AdtDelphiConstSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ConstantDeclList, rCopy, AdtDelphiConstantDeclList);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstSection::~AdtDelphiConstSection()
{
  UtlReleaseReference(ConstantDeclList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstSection::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (ConstantDeclList != 0)
  {
    ConstantDeclList->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ConstantDeclList != 0)
  {
    write(pOutFile, "const");

    pOutFile.incrementIndent();
    pOutFile.newline();

    ConstantDeclList->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.homeline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstantDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstantDeclList::AdtDelphiConstantDeclList(AdtParser* pConstantDeclObj)
 : AdtDelphiBase()
{
  add(pConstantDeclObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstantDeclList::AdtDelphiConstantDeclList(const AdtDelphiConstantDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiConstantDeclList::~AdtDelphiConstantDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstantDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstantDecl method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstantDecl::AdtDelphiConstantDecl(AdtParser* pIdentObj,
                                             AdtParser* pTypeIdObj,
                                             AdtParser* pUnitIdObj,
                                             AdtParser* pConstExprObj,
                                             AdtParser* pTypedConstantObj)
 : AdtDelphiBase()
{
  initObject(Ident,         pIdentObj,          AdtDelphiIdent,         true);
  initObject(TypeId,        pTypeIdObj,         AdtDelphiTypeId,        true);
  initObject(UnitId,        pUnitIdObj,         AdtDelphiUnitId,        true);
  initObject(ConstExpr,     pConstExprObj,      AdtDelphiConstExpr,     true);
  initObject(TypedConstant, pTypedConstantObj,  AdtDelphiTypedConstant, true);

  if (Ident != 0)
  {
    name(Ident->name());
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiConstantDecl::AdtDelphiConstantDecl(const AdtDelphiConstantDecl& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,         rCopy, AdtDelphiIdent);
  copyObject(TypeId,        rCopy, AdtDelphiTypeId);
  copyObject(UnitId,        rCopy, AdtDelphiUnitId);
  copyObject(ConstExpr,     rCopy, AdtDelphiConstExpr);
  copyObject(TypedConstant, rCopy, AdtDelphiTypedConstant);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstantDecl::~AdtDelphiConstantDecl()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(TypeId);
  UtlReleaseReference(UnitId);
  UtlReleaseReference(ConstExpr);
  UtlReleaseReference(TypedConstant);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstantDecl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  string  sPrefix;

  writePragmas(pOutFile);

  if (UnitId != 0)
  {
    sPrefix += UnitId->name();
    sPrefix += "__";
  }

  if (TypeId != 0)
  {
    sPrefix += TypeId->name();
    sPrefix += "__";
  }

  if (ConstExpr != 0)
  {
    ConstExpr->writeFortranTypeDeclaration(pOutFile, sPrefix, Ident);
  }

  write(pOutFile, "PARAMETER (");

  if (Ident != 0)
  {
    Ident->writeFortran(pOutFile, nMode);
    write(pOutFile, " = ");
  }

  if (ConstExpr != 0)
  {
    ConstExpr->writeFortran(pOutFile, nMode);
  }
  else if (TypedConstant != 0)
  {
    ::printf("WARNING: Translation of Pascal Typed constant on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());
  }

  write(pOutFile, ")");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstantDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
    write(pOutFile, " = ");
  }

  if (ConstExpr != 0)
  {
    ConstExpr->writeDelphi(pOutFile, nMode);
  }
  else if (TypedConstant != 0)
  {
    TypedConstant->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstantDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypeSection::AdtDelphiTypeSection(AdtParser* pTypeDeclListObj,
                                           const char* pComment)
 : AdtDelphiBase()
{
  initObject(TypeDeclList, pTypeDeclListObj, AdtDelphiTypeDeclList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypeSection::AdtDelphiTypeSection(const AdtDelphiTypeSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(TypeDeclList, rCopy, AdtDelphiTypeDeclList);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypeSection::~AdtDelphiTypeSection()
{
  UtlReleaseReference(TypeDeclList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiTypeSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypeDeclList != 0)
  {
    write(pOutFile, "type");

    pOutFile.incrementIndent();
    pOutFile.newline();

    TypeDeclList->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.homeline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypeSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypeDeclList::AdtDelphiTypeDeclList(AdtParser* pTypeDeclObj)
 : AdtDelphiBase()
{
  add(pTypeDeclObj);
}

//  ----------------------------------------------------------------------------
AdtDelphiTypeDeclList::AdtDelphiTypeDeclList(const AdtDelphiTypeDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiTypeDeclList::~AdtDelphiTypeDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypeDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeDecl method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypeDecl::AdtDelphiTypeDecl(AdtParser* pIdentObj,
                                     AdtParser* pTypeObj,
                                     AdtParser* pRestrictedTypeObj)
 : AdtDelphiBase()
{
  initObject(Ident,           pIdentObj,          AdtDelphiIdent,           true);
  initObject(Type,            pTypeObj,           AdtDelphiType,            true);
  initObject(RestrictedType,  pRestrictedTypeObj, AdtDelphiRestrictedType,  true);

  if (Ident != 0)
  {
    name(Ident->name());
  }
}

//  ----------------------------------------------------------------------------
AdtDelphiTypeDecl::AdtDelphiTypeDecl(const AdtDelphiTypeDecl& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,          rCopy, AdtDelphiIdent);
  copyObject(Type,           rCopy, AdtDelphiType);
  copyObject(RestrictedType, rCopy, AdtDelphiRestrictedType);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypeDecl::~AdtDelphiTypeDecl()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(Type);
  UtlReleaseReference(RestrictedType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiTypeDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);

    write(pOutFile, " = ");
  }

  if (Type != 0)
  {
    Type->writeDelphi(pOutFile, nMode);
  }

  if (RestrictedType != 0)
  {
    RestrictedType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypeDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypedConstant method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypedConstant::AdtDelphiTypedConstant(AdtParser* pConstExprObj,
                                               AdtParser* pArrayConstantObj,
                                               AdtParser* pRecordConstantObj)
 : AdtDelphiBase()
{
  initObject(ConstExpr,       pConstExprObj,      AdtDelphiConstExpr,       true);
  initObject(ArrayConstant,   pArrayConstantObj,  AdtDelphiArrayConstant,   true);
  initObject(RecordConstant,  pRecordConstantObj, AdtDelphiRecordConstant,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypedConstant::AdtDelphiTypedConstant(const AdtDelphiTypedConstant& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ConstExpr,      rCopy, AdtDelphiConstExpr);
  copyObject(ArrayConstant,  rCopy, AdtDelphiArrayConstant);
  copyObject(RecordConstant, rCopy, AdtDelphiRecordConstant);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypedConstant::~AdtDelphiTypedConstant()
{
  UtlReleaseReference(ConstExpr);
  UtlReleaseReference(ArrayConstant);
  UtlReleaseReference(RecordConstant);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiTypedConstant::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ConstExpr != 0)
  {
    ConstExpr->writeDelphi(pOutFile, nMode);
  }
  else if (ArrayConstant != 0)
  {
    ArrayConstant->writeDelphi(pOutFile, nMode);
  }
  else if (RecordConstant != 0)
  {
    RecordConstant->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypedConstant, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiArrayConstant method implementations
//  ----------------------------------------------------------------------------
AdtDelphiArrayConstant::AdtDelphiArrayConstant(AdtParser* pTypedConstantListObj)
 : AdtDelphiBase()
{
  initObject(TypedConstantList, pTypedConstantListObj, AdtDelphiTypedConstantList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiArrayConstant::AdtDelphiArrayConstant(const AdtDelphiArrayConstant& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(TypedConstantList, rCopy, AdtDelphiTypedConstantList);
}

//  ----------------------------------------------------------------------------

AdtDelphiArrayConstant::~AdtDelphiArrayConstant()
{
  UtlReleaseReference(TypedConstantList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiArrayConstant::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypedConstantList != 0)
  {
    write(pOutFile, "(");
    TypedConstantList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiArrayConstant, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypedConstantList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypedConstantList::AdtDelphiTypedConstantList(AdtParser* pTypedConstantObj)
 : AdtDelphiBase()
{
  add(pTypedConstantObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypedConstantList::AdtDelphiTypedConstantList(const AdtDelphiTypedConstantList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiTypedConstantList::~AdtDelphiTypedConstantList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypedConstantList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordConstant method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRecordConstant::AdtDelphiRecordConstant(AdtParser* pRecordFieldConstantListObj)
 : AdtDelphiBase()
{
  initObject(RecordFieldConstantList, pRecordFieldConstantListObj, AdtDelphiRecordFieldConstantList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecordConstant::AdtDelphiRecordConstant(const AdtDelphiRecordConstant& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(RecordFieldConstantList, rCopy, AdtDelphiRecordFieldConstantList);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecordConstant::~AdtDelphiRecordConstant()
{
  UtlReleaseReference(RecordFieldConstantList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRecordConstant::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (RecordFieldConstantList != 0)
  {
    write(pOutFile, "(");
    RecordFieldConstantList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRecordConstant, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordFieldConstantList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRecordFieldConstantList::AdtDelphiRecordFieldConstantList(AdtParser* pRecordFieldConstantObj)
 : AdtDelphiBase()
{
  add(pRecordFieldConstantObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecordFieldConstantList::AdtDelphiRecordFieldConstantList(const AdtDelphiRecordFieldConstantList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiRecordFieldConstantList::~AdtDelphiRecordFieldConstantList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRecordFieldConstantList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordFieldConstant method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRecordFieldConstant::AdtDelphiRecordFieldConstant(AdtParser* pIdentObj,
                                                           AdtParser* pTypedConstantObj)
 : AdtDelphiBase()
{
  initObject(Ident,         pIdentObj,          AdtDelphiIdent,         true);
  initObject(TypedConstant, pTypedConstantObj,  AdtDelphiTypedConstant, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecordFieldConstant::AdtDelphiRecordFieldConstant(const AdtDelphiRecordFieldConstant& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,         rCopy, AdtDelphiIdent);
  copyObject(TypedConstant, rCopy, AdtDelphiTypedConstant);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecordFieldConstant::~AdtDelphiRecordFieldConstant()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(TypedConstant);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRecordFieldConstant::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (TypedConstant != 0)
  {
    TypedConstant->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRecordFieldConstant, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiType::AdtDelphiType(AdtParser* pTypeIdObj,
                             AdtParser* pUnitIdObj,
                             AdtParser* pSimpleTypeObj,
                             AdtParser* pStructTypeObj,
                             AdtParser* pPointerTypeObj,
                             AdtParser* pStringTypeObj,
                             AdtParser* pProcedureTypeObj,
                             AdtParser* pVariantTypeObj,
                             AdtParser* pClassRefTypeObj)
 : AdtDelphiBase()
{
  initObject(TypeId,        pTypeIdObj,         AdtDelphiTypeId,        true);
  initObject(UnitId,        pUnitIdObj,         AdtDelphiUnitId,        true);
  initObject(SimpleType,    pSimpleTypeObj,     AdtDelphiSimpleType,    true);
  initObject(StructType,    pStructTypeObj,     AdtDelphiStructType,    true);
  initObject(PointerType,   pPointerTypeObj,    AdtDelphiPointerType,   true);
  initObject(StringType,    pStringTypeObj,     AdtDelphiStringType,    true);
  initObject(ProcedureType, pProcedureTypeObj,  AdtDelphiProcedureType, true);
  initObject(VariantType,   pVariantTypeObj,    AdtDelphiVariantType,   true);
  initObject(ClassRefType,  pClassRefTypeObj,   AdtDelphiClassRefType,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiType::AdtDelphiType(const AdtDelphiType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(TypeId,        rCopy, AdtDelphiTypeId);
  copyObject(UnitId,        rCopy, AdtDelphiUnitId);
  copyObject(SimpleType,    rCopy, AdtDelphiSimpleType);
  copyObject(StructType,    rCopy, AdtDelphiStructType);
  copyObject(PointerType,   rCopy, AdtDelphiPointerType);
  copyObject(StringType,    rCopy, AdtDelphiStringType);
  copyObject(ProcedureType, rCopy, AdtDelphiProcedureType);
  copyObject(VariantType,   rCopy, AdtDelphiVariantType);
  copyObject(ClassRefType,  rCopy, AdtDelphiClassRefType);
}

//  ----------------------------------------------------------------------------

AdtDelphiType::~AdtDelphiType()
{
  UtlReleaseReference(TypeId);
  UtlReleaseReference(UnitId);
  UtlReleaseReference(SimpleType);
  UtlReleaseReference(StructType);
  UtlReleaseReference(PointerType);
  UtlReleaseReference(StringType);
  UtlReleaseReference(ProcedureType);
  UtlReleaseReference(VariantType);
  UtlReleaseReference(ClassRefType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiType::autoType(const AdtDelphiTypeId* pTypeId,
                                    const AdtDelphiSimpleType* pSimpleType,
                                    int& nDimensions)
{
  AdtAutoType nType       = AdtAutoType_UNDEFINED;
  const char* pType       = 0;
  const char* pDimension  = 0;

  nDimensions = 0;

  if ((pTypeId != 0) && AdtDelphiBase::mapTypesToFortran(pTypeId->name(), pType, pDimension))
  {
    const char* pComma;

    nType       = AdtAutoAttribute::fortranTypeToAutoType(pType);
    nDimensions = 1;
    pComma      = ::strchr(pDimension, ',');

    for ( ; pComma != 0 ; pComma = ::strchr(pComma + 1, ','))
    {
      nDimensions++;
    }
  }
  else if (pSimpleType != 0)
  {
    nType = pSimpleType->autoType();
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiType::autoType(int& nDimensions) const
{
  return (AdtDelphiType::autoType(TypeId, SimpleType, nDimensions));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiType::writeFortran(AdtFile& pOutFile, int nMode, const char*& sDimension, bool& bKeep) const
{
  const char* sType = 0;

  bKeep = true;

  if (TypeId != 0)
  {
    //We do this to map MB arrays into equivalent fortran ones
    delphiRootObject()->mapTypesToFortran(TypeId->name(), sType, sDimension);
    bKeep = (sType != 0);
  }

  if (bKeep)
  {
    if (UnitId != 0)
    {
      UnitId->writeFortran(pOutFile, nMode);
      write(pOutFile, "__");
    }

    if (TypeId != 0)
    {
      if (sType != 0)
      {
        write(pOutFile, sType);
      }
    }
    else if (SimpleType != 0)
    {
      SimpleType->writeFortran(pOutFile, nMode);
    }
    else if (StructType != 0)
    {
      ::printf("ERROR: Translation of Pascal struct type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (PointerType != 0)
    {
      PointerType->writeFortran(pOutFile, nMode);
    }
    else if (StringType != 0)
    {
      StringType->writeFortran(pOutFile, nMode);
    }
    else if (ProcedureType != 0)
    {
      ::printf("ERROR: Translation of Pascal procedure type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (VariantType != 0)
    {
      ::printf("ERROR: Translation of Pascal variant type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (ClassRefType != 0)
    {
      ::printf("ERROR: Translation of Pascal classref type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* sDimension = 0;
  bool        bKeep      = true;

  writePragmas(pOutFile);

  return (writeFortran(pOutFile, nMode, sDimension, bKeep));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
  }
  else if (SimpleType != 0)
  {
    SimpleType->writeDelphi(pOutFile, nMode);
  }
  else if (StructType != 0)
  {
    StructType->writeDelphi(pOutFile, nMode);
  }
  else if (PointerType != 0)
  {
    PointerType->writeDelphi(pOutFile, nMode);
  }
  else if (StringType != 0)
  {
    StringType->writeDelphi(pOutFile, nMode);
  }
  else if (ProcedureType != 0)
  {
    ProcedureType->writeDelphi(pOutFile, nMode);
  }
  else if (VariantType != 0)
  {
    VariantType->writeDelphi(pOutFile, nMode);
  }
  else if (ClassRefType != 0)
  {
    ClassRefType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRestrictedType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRestrictedType::AdtDelphiRestrictedType(AdtParser* pObjectTypeObj,
                                                 AdtParser* pClassTypeObj,
                                                 AdtParser* pInterfaceTypeObj)
 : AdtDelphiBase()
{
  initObject(ObjectType,    pObjectTypeObj,     AdtDelphiObjectType,    true);
  initObject(ClassType,     pClassTypeObj,      AdtDelphiClassType,     true);
  initObject(InterfaceType, pInterfaceTypeObj,  AdtDelphiInterfaceType, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiRestrictedType::AdtDelphiRestrictedType(const AdtDelphiRestrictedType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ObjectType,    rCopy, AdtDelphiObjectType);
  copyObject(ClassType,     rCopy, AdtDelphiClassType);
  copyObject(InterfaceType, rCopy, AdtDelphiInterfaceType);
}

//  ----------------------------------------------------------------------------

AdtDelphiRestrictedType::~AdtDelphiRestrictedType()
{
  UtlReleaseReference(ObjectType);
  UtlReleaseReference(ClassType);
  UtlReleaseReference(InterfaceType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRestrictedType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ObjectType != 0)
  {
    ObjectType->writeDelphi(pOutFile, nMode);
  }
  else if (ClassType != 0)
  {
    ClassType->writeDelphi(pOutFile, nMode);
  }
  else if (InterfaceType != 0)
  {
    InterfaceType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRestrictedType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassRefType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassRefType::AdtDelphiClassRefType(AdtParser* pTypeIdObj,
                                             AdtParser* pUnitIdObj)
 : AdtDelphiBase()
{
  initObject(TypeId, pTypeIdObj, AdtDelphiTypeId, true);
  initObject(UnitId, pUnitIdObj, AdtDelphiUnitId, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassRefType::AdtDelphiClassRefType(const AdtDelphiClassRefType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(TypeId, rCopy, AdtDelphiTypeId);
  copyObject(UnitId, rCopy, AdtDelphiUnitId);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassRefType::~AdtDelphiClassRefType()
{
  UtlReleaseReference(TypeId);
  UtlReleaseReference(UnitId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassRefType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypeId != 0)
  {
    write(pOutFile, "class of ");
  }

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassRefType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSimpleType::AdtDelphiSimpleType(AdtParser* pOrdinalTypeObj,
                                         AdtParser* pRealTypeObj)
 : AdtDelphiBase()
{
  initObject(OrdinalType, pOrdinalTypeObj,  AdtDelphiOrdinalType, true);
  initObject(RealType,    pRealTypeObj,     AdtDelphiRealType,    true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleType::AdtDelphiSimpleType(const AdtDelphiSimpleType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(OrdinalType, rCopy, AdtDelphiOrdinalType);
  copyObject(RealType,    rCopy, AdtDelphiRealType);
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleType::~AdtDelphiSimpleType()
{
  UtlReleaseReference(OrdinalType);
  UtlReleaseReference(RealType);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType AdtDelphiSimpleType::blackBoxArgType() const
{
  AdtBlackBoxArgType  nType = AdtBlackBox_undefined;

  if (OrdinalType != 0)
  {
    nType = OrdinalType->blackBoxArgType();
  }
  else if (RealType != 0)
  {
    nType = RealType->blackBoxArgType();
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiSimpleType::autoType() const
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  if (OrdinalType != 0)
  {
    nType = OrdinalType->autoType();
  }
  else if (RealType != 0)
  {
    nType = RealType->autoType();
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleType::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (OrdinalType != 0)
  {
    OrdinalType->writeCPP(pOutFile, nMode);
  }
  else if (RealType != 0)
  {
    RealType->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (OrdinalType != 0)
  {
    OrdinalType->writeFortran(pOutFile, nMode);
  }
  else if (RealType != 0)
  {
    RealType->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (OrdinalType != 0)
  {
    OrdinalType->writeDelphi(pOutFile, nMode);
  }
  else if (RealType != 0)
  {
    RealType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSimpleType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRealType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRealType::AdtDelphiRealType(AdtType nType)
 : AdtDelphiBase()
{
  RealType = nType;
}

//  ----------------------------------------------------------------------------

AdtDelphiRealType::AdtDelphiRealType(const AdtDelphiRealType& rCopy)
 : AdtDelphiBase(rCopy)
{
  RealType = rCopy.RealType;
}

//  ----------------------------------------------------------------------------

AdtDelphiRealType::~AdtDelphiRealType()
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType AdtDelphiRealType::blackBoxArgType() const
{
  AdtBlackBoxArgType  nType = AdtBlackBox_undefined;

  switch (RealType)
  {
    case AdtType_DOUBLE:
    case AdtType_REAL48:
    case AdtType_REAL:
    case AdtType_SINGLE:
    {
      nType = AdtBlackBox_real;
      break;
    }

    case AdtType_EXTENDED:
    case AdtType_CURRENCY:
    case AdtType_COMP:
    {
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiRealType::autoType() const
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  switch (RealType)
  {
    case AdtType_DOUBLE:
    case AdtType_REAL48:
    case AdtType_REAL:
    {
      nType = AdtAutoType_DOUBLE;
      break;
    }

    case AdtType_SINGLE:
    {
      nType = AdtAutoType_FLOAT;
      break;
    }

    case AdtType_EXTENDED:
    case AdtType_CURRENCY:
    case AdtType_COMP:
    default:
    {
      FAIL();
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRealType::writeCPP(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writePragmas(pOutFile);

  switch (RealType)
  {
    case AdtType_REAL48:
    case AdtType_REAL:
    case AdtType_SINGLE:
    case AdtType_DOUBLE:
    {
      pType = "double";
      break;
    }

    case AdtType_EXTENDED:
    case AdtType_CURRENCY:
    case AdtType_COMP:
    default:
    {
      ::printf("ERROR: Translation of Pascal extended, currency and comp types on line %d in file %s into "
               "C++ not supported\n", lineNumber(),
                                      fileName());

      ::AdtExit(-1);
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRealType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writePragmas(pOutFile);

  switch (RealType)
  {
    case AdtType_REAL48:
    case AdtType_REAL:
    case AdtType_SINGLE:
    case AdtType_DOUBLE:
    {
      pType = "REAL(8)";
      break;
    }

    case AdtType_EXTENDED:
    case AdtType_CURRENCY:
    case AdtType_COMP:
    default:
    {
      ::printf("ERROR: Translation of Pascal extended, currency and comp types on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRealType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writeExpanded(pOutFile, comment());

  switch (RealType)
  {
    case AdtType_REAL48:
    {
      pType = "real48";
      break;
    }

    case AdtType_REAL:
    {
      pType = "real";
      break;
    }

    case AdtType_SINGLE:
    {
      pType = "single";
      break;
    }

    case AdtType_DOUBLE:
    {
      pType = "double";
      break;
    }

    case AdtType_EXTENDED:
    {
      pType = "extended";
      break;
    }

    case AdtType_CURRENCY:
    {
      pType = "currency";
      break;
    }

    case AdtType_COMP:
    {
      pType = "comp";
      break;
    }

    default:
    {
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRealType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdinalType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiOrdinalType::AdtDelphiOrdinalType(AdtParser* pSubrangeTypeObj,
                                           AdtParser* pEnumeratedTypeObj,
                                           AdtParser* pOrdIdentObj)
 : AdtDelphiBase()
{
  initObject(SubrangeType,    pSubrangeTypeObj,   AdtDelphiSubrangeType,    true);
  initObject(EnumeratedType,  pEnumeratedTypeObj, AdtDelphiEnumeratedType,  true);
  initObject(OrdIdent,        pOrdIdentObj,       AdtDelphiOrdIdent,        true);
}

//  ----------------------------------------------------------------------------

AdtDelphiOrdinalType::AdtDelphiOrdinalType(const AdtDelphiOrdinalType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(SubrangeType,   rCopy, AdtDelphiSubrangeType);
  copyObject(EnumeratedType, rCopy, AdtDelphiEnumeratedType);
  copyObject(OrdIdent,       rCopy, AdtDelphiOrdIdent);
}

//  ----------------------------------------------------------------------------

AdtDelphiOrdinalType::~AdtDelphiOrdinalType()
{
  UtlReleaseReference(SubrangeType);
  UtlReleaseReference(EnumeratedType);
  UtlReleaseReference(OrdIdent);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType AdtDelphiOrdinalType::blackBoxArgType() const
{
  AdtBlackBoxArgType  nType = AdtBlackBox_undefined;

  if (SubrangeType)
  {
    // Do nothing
  }
  else if (EnumeratedType)
  {
    // Do nothing
  }
  else if (OrdIdent)
  {
    nType = OrdIdent->blackBoxArgType();
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiOrdinalType::autoType() const
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  if (SubrangeType)
  {
    // Do nothing
  }
  else if (EnumeratedType)
  {
    // Do nothing
  }
  else if (OrdIdent)
  {
    nType = OrdIdent->autoType();
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdinalType::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (SubrangeType)
  {
      ::printf("ERROR: Translation of Pascal subrange type on line %d in file %s into "
               "C++ not supported\n", lineNumber(),
                                      fileName());

      ::AdtExit(-1);
  }
  else if (EnumeratedType)
  {
      ::printf("ERROR: Translation of Pascal enumerated type on line %d in file %s into "
               "C++ not supported\n", lineNumber(),
                                      fileName());

      ::AdtExit(-1);
  }
  else if (OrdIdent)
  {
    OrdIdent->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdinalType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (SubrangeType)
  {
      ::printf("ERROR: Translation of Pascal subrange type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
  }
  else if (EnumeratedType)
  {
      ::printf("ERROR: Translation of Pascal enumerated type on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
  }
  else if (OrdIdent)
  {
    OrdIdent->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdinalType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (SubrangeType)
  {
    SubrangeType->writeDelphi(pOutFile, nMode);
  }
  else if (EnumeratedType)
  {
    EnumeratedType->writeDelphi(pOutFile, nMode);
  }
  else if (OrdIdent)
  {
    OrdIdent->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiOrdinalType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdIdent method implementations
//  ----------------------------------------------------------------------------
AdtDelphiOrdIdent::AdtDelphiOrdIdent(AdtType nType)
 : AdtDelphiBase()
{
  OrdType = nType;
}

//  ----------------------------------------------------------------------------

AdtDelphiOrdIdent::AdtDelphiOrdIdent(const AdtDelphiOrdIdent& rCopy)
 : AdtDelphiBase(rCopy)
{
  OrdType = rCopy.OrdType;
}

//  ----------------------------------------------------------------------------

AdtDelphiOrdIdent::~AdtDelphiOrdIdent()
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType AdtDelphiOrdIdent::blackBoxArgType() const
{
  AdtBlackBoxArgType  nType = AdtBlackBox_undefined;

  switch (OrdType)
  {
    case AdtType_SHORTINT:
    case AdtType_INTEGER:
    case AdtType_BYTE:
    case AdtType_LONGINT:
    case AdtType_INT64:
    case AdtType_WORD:
    case AdtType_LONGWORD:
    {
      nType = AdtBlackBox_integer;
      break;
    }

    case AdtType_BOOLEAN:
    {
      nType = AdtBlackBox_boolean;
      break;
    }

    case AdtType_CHAR:
    case AdtType_WIDECHAR:
    case AdtType_PCHAR:
    case AdtType_POINTER:
    {
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtDelphiOrdIdent::autoType() const
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  switch (OrdType)
  {
    case AdtType_SHORTINT:
    {
      nType = AdtAutoType_SHORT;
      break;
    }

    case AdtType_INTEGER:
    {
      nType = AdtAutoType_INT;
      break;
    }

    case AdtType_BYTE:
    {
      nType = AdtAutoType_UNSIGNED_CHAR;
      break;
    }

    case AdtType_LONGINT:
    {
      nType = AdtAutoType_LONG;
      break;
    }

    case AdtType_INT64:
    {
      nType = AdtAutoType_LONG_LONG;
      break;
    }

    case AdtType_WORD:
    {
      nType = AdtAutoType_UNSIGNED_SHORT;
      break;
    }

    case AdtType_BOOLEAN:
    {
      nType = AdtAutoType_BOOL;
      break;
    }

    case AdtType_CHAR:
    {
      nType = AdtAutoType_CHAR;
      break;
    }

    case AdtType_LONGWORD:
    {
      nType = AdtAutoType_UNSIGNED_LONG;
      break;
    }

    case AdtType_WIDECHAR:
    case AdtType_PCHAR:
    case AdtType_POINTER:
    default:
    {
      FAIL();
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdIdent::writeCPP(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writePragmas(pOutFile);

  switch (OrdType)
  {
    case AdtType_BYTE:
    {
      pType = "char";
      break;
    }

    case AdtType_WORD:
    case AdtType_SHORTINT:
    {
      pType = "short";
      break;
    }

    case AdtType_INTEGER:
    {
      pType = "int";
      break;
    }

    case AdtType_LONGINT:
    {
      pType = "long";
      break;
    }

    case AdtType_LONGWORD:
    case AdtType_INT64:
    {
      pType = "_int64";
      break;
    }

    case AdtType_BOOLEAN:
    {
      pType = "bool";
      break;
    }

    case AdtType_CHAR:
    {
      pType = "char";
      break;
    }

    case AdtType_WIDECHAR:
    case AdtType_PCHAR:
    case AdtType_POINTER:
    default:
    {
      ::printf("ERROR: Translation of Pascal widechar, pchar and pointer types on line %d in file %s into "
               "C++ not supported\n", lineNumber(),
                                      fileName());

      ::AdtExit(-1);
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdIdent::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writePragmas(pOutFile);

  switch (OrdType)
  {
    case AdtType_BYTE:
    {
      pType = "INTEGER(1)";
      break;
    }

    case AdtType_WORD:
    case AdtType_SHORTINT:
    {
      pType = "INTEGER(2)";
      break;
    }

    case AdtType_INTEGER:
    {
      pType = "INTEGER";
      break;
    }

    case AdtType_LONGINT:
    {
      pType = "INTEGER(4)";
      break;
    }

    case AdtType_LONGWORD:
    case AdtType_INT64:
    {
      pType = "INTEGER(8)";
      break;
    }

    case AdtType_BOOLEAN:
    {
      pType = "LOGICAL";
      break;
    }

    case AdtType_CHAR:
    {
      pType = "CHARACTER*1";
      break;
    }

    case AdtType_WIDECHAR:
    case AdtType_PCHAR:
    case AdtType_POINTER:
    default:
    {
      ::printf("ERROR: Translation of Pascal widechar, pchar and pointer types on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiOrdIdent::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writeExpanded(pOutFile, comment());

  switch (OrdType)
  {
    case AdtType_SHORTINT:
    {
      pType = "shortint";
      break;
    }

    case AdtType_INTEGER:
    {
      pType = "integer";
      break;
    }

    case AdtType_BYTE:
    {
      pType = "byte";
      break;
    }

    case AdtType_LONGINT:
    {
      pType = "longint";
      break;
    }

    case AdtType_INT64:
    {
      pType = "int64";
      break;
    }

    case AdtType_WORD:
    {
      pType = "word";
      break;
    }

    case AdtType_BOOLEAN:
    {
      pType = "boolean";
      break;
    }

    case AdtType_CHAR:
    {
      pType = "char";
      break;
    }

    case AdtType_WIDECHAR:
    {
      pType = "widechar";
      break;
    }

    case AdtType_LONGWORD:
    {
      pType = "longword";
      break;
    }

    case AdtType_PCHAR:
    {
      pType = "pchar";
      break;
    }

    case AdtType_POINTER:
    {
      pType = "POINTER";
      break;
    }

    default:
    {
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiOrdIdent, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVariantType::AdtDelphiVariantType(AdtType nType)
 : AdtDelphiBase()
{
  Type = nType;
}

//  ----------------------------------------------------------------------------

AdtDelphiVariantType::AdtDelphiVariantType(const AdtDelphiVariantType& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtDelphiVariantType::~AdtDelphiVariantType()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVariantType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writeExpanded(pOutFile, comment());

  switch (Type)
  {
    case AdtType_VARIANT:
    {
      pType = "variant";
      break;
    }

    case AdtType_OLEVARIANT:
    {
      pType = "olevariant";
      break;
    }

    default:
    {
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVariantType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSubrangeType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSubrangeType::AdtDelphiSubrangeType(AdtParser* pFromConstExprObj,
                                             AdtParser* pToConstExprObj)
 : AdtDelphiBase()
{
  initObject(FromConstExpr, pFromConstExprObj,  AdtDelphiConstExpr, true);
  initObject(ToConstExpr,   pToConstExprObj,    AdtDelphiConstExpr, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSubrangeType::AdtDelphiSubrangeType(const AdtDelphiSubrangeType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(FromConstExpr, rCopy, AdtDelphiConstExpr);
  copyObject(ToConstExpr,   rCopy, AdtDelphiConstExpr);
}

//  ----------------------------------------------------------------------------

AdtDelphiSubrangeType::~AdtDelphiSubrangeType()
{
  UtlReleaseReference(FromConstExpr);
  UtlReleaseReference(ToConstExpr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSubrangeType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (FromConstExpr)
  {
    FromConstExpr->writeDelphi(pOutFile, nMode);
    write(pOutFile, "..");
  }

  if (ToConstExpr)
  {
    ToConstExpr->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSubrangeType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiEnumeratedType::AdtDelphiEnumeratedType(AdtParser* pEnumeratedTypeElementListObj)
 : AdtDelphiBase()
{
  initObject(EnumeratedTypeElementList, pEnumeratedTypeElementListObj,  AdtDelphiEnumeratedTypeElementList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedType::AdtDelphiEnumeratedType(const AdtDelphiEnumeratedType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(EnumeratedTypeElementList, rCopy, AdtDelphiEnumeratedTypeElementList);
}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedType::~AdtDelphiEnumeratedType()
{
  UtlReleaseReference(EnumeratedTypeElementList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiEnumeratedType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (EnumeratedTypeElementList)
  {
    write(pOutFile, "(");
    EnumeratedTypeElementList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiEnumeratedType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedTypeElementList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiEnumeratedTypeElementList::AdtDelphiEnumeratedTypeElementList(AdtParser* pEnumeratedTypeElementObj)
 : AdtDelphiBase()
{
  add(pEnumeratedTypeElementObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedTypeElementList::AdtDelphiEnumeratedTypeElementList(const AdtDelphiEnumeratedTypeElementList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedTypeElementList::~AdtDelphiEnumeratedTypeElementList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiEnumeratedTypeElementList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedTypeElement method implementations
//  ----------------------------------------------------------------------------
AdtDelphiEnumeratedTypeElement::AdtDelphiEnumeratedTypeElement(AdtParser* pIdentObj,
                                                               AdtParser* pConstExprObj)
 : AdtDelphiBase()
{
  initObject(Ident,     pIdentObj,      AdtDelphiIdent,     true);
  initObject(ConstExpr, pConstExprObj,  AdtDelphiConstExpr, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedTypeElement::AdtDelphiEnumeratedTypeElement(const AdtDelphiEnumeratedTypeElement& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,     rCopy, AdtDelphiIdent);
  copyObject(ConstExpr, rCopy, AdtDelphiConstExpr);
}

//  ----------------------------------------------------------------------------

AdtDelphiEnumeratedTypeElement::~AdtDelphiEnumeratedTypeElement()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(ConstExpr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiEnumeratedTypeElement::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Ident)
  {
    Ident->writeDelphi(pOutFile, nMode);
  }

  if (ConstExpr)
  {
    write(pOutFile, " = ");
    ConstExpr->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiEnumeratedTypeElement, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiStringType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiStringType::AdtDelphiStringType(AdtType nType,
                                         AdtParser* pConstExprObj)
 : AdtDelphiBase()
{
  Type  = nType;

  initObject(ConstExpr, pConstExprObj,  AdtDelphiConstExpr, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiStringType::AdtDelphiStringType(const AdtDelphiStringType& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type  = rCopy.Type;

  copyObject(ConstExpr, rCopy, AdtDelphiConstExpr);
}

//  ----------------------------------------------------------------------------

AdtDelphiStringType::~AdtDelphiStringType()
{
  UtlReleaseReference(ConstExpr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiStringType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (ConstExpr != 0)
  {
    ::printf("ERROR: Translation of Pascal string type on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }
  else
  {
    const char* pType = 0;

    switch (Type)
    {
      case AdtType_STRING:
      case AdtType_ANSISTRING:
      case AdtType_WIDESTRING:
      {
        pType = "CHARACTER*512";
        break;
      }

      default:
      {
        break;
      }
    }

    if (pType != 0)
    {
      write(pOutFile, pType);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiStringType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writeExpanded(pOutFile, comment());

  switch (Type)
  {
    case AdtType_STRING:
    {
      pType = "string";
      break;
    }

    case AdtType_ANSISTRING:
    {
      pType = "ansistring";
      break;
    }

    case AdtType_WIDESTRING:
    {
      pType = "widestring";
      break;
    }

    default:
    {
      break;
    }
  }

  if (pType != 0)
  {
    write(pOutFile, pType);
  }

  if (ConstExpr != 0)
  {
    write(pOutFile, "[");
    ConstExpr->writeDelphi(pOutFile, nMode);
    write(pOutFile, "]");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiStringType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiStructType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiStructType::AdtDelphiStructType(bool bIsPacked,
                                         AdtParser* pArrayTypeObj,
                                         AdtParser* pSetTypeObj,
                                         AdtParser* pFileTypeObj,
                                         AdtParser* pRecTypeObj)
 : AdtDelphiBase()
{
  IsPacked  = bIsPacked;

  initObject(ArrayType, pArrayTypeObj,  AdtDelphiArrayType, true);
  initObject(SetType,   pSetTypeObj,    AdtDelphiSetType,   true);
  initObject(FileType,  pFileTypeObj,   AdtDelphiFileType,  true);
  initObject(RecType,   pRecTypeObj,    AdtDelphiRecType,   true);
}

//  ----------------------------------------------------------------------------

AdtDelphiStructType::AdtDelphiStructType(const AdtDelphiStructType& rCopy)
 : AdtDelphiBase(rCopy)
{
  IsPacked  = rCopy.IsPacked;

  copyObject(ArrayType, rCopy, AdtDelphiArrayType);
  copyObject(SetType,   rCopy, AdtDelphiSetType);
  copyObject(FileType,  rCopy, AdtDelphiFileType);
  copyObject(RecType,   rCopy, AdtDelphiRecType);
}

//  ----------------------------------------------------------------------------

AdtDelphiStructType::~AdtDelphiStructType()
{
  UtlReleaseReference(ArrayType);
  UtlReleaseReference(SetType);
  UtlReleaseReference(FileType);
  UtlReleaseReference(RecType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiStructType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IsPacked)
  {
    write(pOutFile, "packed ");
  }

  if (ArrayType != 0)
  {
    ArrayType->writeDelphi(pOutFile, nMode);
  }

  if (SetType != 0)
  {
    SetType->writeDelphi(pOutFile, nMode);
  }

  if (FileType != 0)
  {
    FileType->writeDelphi(pOutFile, nMode);
  }

  if (RecType != 0)
  {
    RecType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiStructType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiArrayType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiArrayType::AdtDelphiArrayType(AdtParser* pOrdinalTypeListObj,
                                       AdtParser* pTypeObj)
 : AdtDelphiBase()
{
  initObject(OrdinalTypeList, pOrdinalTypeListObj,  AdtDelphiOrdinalTypeList, true);
  initObject(Type,            pTypeObj,             AdtDelphiType,            true);
}

//  ----------------------------------------------------------------------------

AdtDelphiArrayType::AdtDelphiArrayType(const AdtDelphiArrayType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(OrdinalTypeList, rCopy, AdtDelphiOrdinalTypeList);
  copyObject(Type,            rCopy, AdtDelphiType);
}

//  ----------------------------------------------------------------------------

AdtDelphiArrayType::~AdtDelphiArrayType()
{
  UtlReleaseReference(OrdinalTypeList);
  UtlReleaseReference(Type);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiArrayType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Type != 0)
  {
    write(pOutFile, "array");
  }

  if (OrdinalTypeList != 0)
  {
    write(pOutFile, "[");
    OrdinalTypeList->writeDelphi(pOutFile, nMode);
    write(pOutFile, "]");
  }

  if (Type != 0)
  {
    write(pOutFile, "of ");
    Type->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiArrayType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdinalTypeList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiOrdinalTypeList::AdtDelphiOrdinalTypeList(AdtParser* pOrdinalTypeObj)
 : AdtDelphiBase()
{
  add(pOrdinalTypeObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiOrdinalTypeList::AdtDelphiOrdinalTypeList(const AdtDelphiOrdinalTypeList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiOrdinalTypeList::~AdtDelphiOrdinalTypeList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiOrdinalTypeList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRecType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRecType::AdtDelphiRecType(AdtParser* pFieldDeclListObj,
                                   AdtParser* pVariantSectionListObj)
 : AdtDelphiBase()
{
  initObject(FieldDeclList,       pFieldDeclListObj,      AdtDelphiFieldDeclList,       true);
  initObject(VariantSectionList,  pVariantSectionListObj, AdtDelphiVariantSectionList,  true);
}

//  ----------------------------------------------------------------------------
AdtDelphiRecType::AdtDelphiRecType(const AdtDelphiRecType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(FieldDeclList,      rCopy, AdtDelphiFieldDeclList);
  copyObject(VariantSectionList, rCopy, AdtDelphiVariantSectionList);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecType::~AdtDelphiRecType()
{
  UtlReleaseReference(FieldDeclList);
  UtlReleaseReference(VariantSectionList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRecType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "record");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (FieldDeclList != 0)
  {
    FieldDeclList->writeDelphi(pOutFile, nMode);
  }

  if (VariantSectionList != 0)
  {
    VariantSectionList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRecType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFieldDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFieldDeclList::AdtDelphiFieldDeclList(AdtParser* pFieldDeclObj)
 : AdtDelphiBase()
{
  add(pFieldDeclObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiFieldDeclList::AdtDelphiFieldDeclList(const AdtDelphiFieldDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiFieldDeclList::~AdtDelphiFieldDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFieldDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFieldDecl method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFieldDecl::AdtDelphiFieldDecl(AdtParser* pIdentListObj,
                                       AdtParser* pTypeObj)
 : AdtDelphiBase()
{
  initObject(IdentList, pIdentListObj,  AdtDelphiIdentList, true);
  initObject(Type,      pTypeObj,       AdtDelphiType,      true);
}

//  ----------------------------------------------------------------------------

AdtDelphiFieldDecl::AdtDelphiFieldDecl(const AdtDelphiFieldDecl& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList, rCopy, AdtDelphiIdentList);
  copyObject(Type,      rCopy, AdtDelphiType);
}

//  ----------------------------------------------------------------------------

AdtDelphiFieldDecl::~AdtDelphiFieldDecl()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(Type);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFieldDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    IdentList->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (Type != 0)
  {
    Type->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFieldDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantSectionList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVariantSectionList::AdtDelphiVariantSectionList(AdtParser* pVariantSectionObj)
 : AdtDelphiBase()
{
  add(pVariantSectionObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiVariantSectionList::AdtDelphiVariantSectionList(const AdtDelphiVariantSectionList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiVariantSectionList::~AdtDelphiVariantSectionList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVariantSectionList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVariantSection::AdtDelphiVariantSection(AdtParser* pIdentObj,
                                                 AdtParser* pUnitIdObj,
                                                 AdtParser* pTypeIdObj,
                                                 AdtParser* pRecVariantObj)
 : AdtDelphiBase()
{
  initObject(Ident,       pIdentObj,      AdtDelphiIdent,       true);
  initObject(UnitId,      pUnitIdObj,     AdtDelphiUnitId,      true);
  initObject(TypeId,      pTypeIdObj,     AdtDelphiTypeId,      true);
  initObject(RecVariant,  pRecVariantObj, AdtDelphiRecVariant,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiVariantSection::AdtDelphiVariantSection(const AdtDelphiVariantSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,      rCopy, AdtDelphiIdent);
  copyObject(UnitId,     rCopy, AdtDelphiUnitId);
  copyObject(TypeId,     rCopy, AdtDelphiTypeId);
  copyObject(RecVariant, rCopy, AdtDelphiRecVariant);
}

//  ----------------------------------------------------------------------------

AdtDelphiVariantSection::~AdtDelphiVariantSection()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(UnitId);
  UtlReleaseReference(TypeId);
  UtlReleaseReference(RecVariant);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVariantSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypeId != 0)
  {
    write(pOutFile, "case ");
  }

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
    write(pOutFile, " of ");
  }

  if (RecVariant != 0)
  {
    RecVariant->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVariantSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRecVariant method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRecVariant::AdtDelphiRecVariant(AdtParser* pConstExprListObj,
                                         AdtParser* pFieldDeclListObj,
                                         AdtParser* pVariantSectionListObj)
 : AdtDelphiBase()
{
  initObject(ConstExprList,       pConstExprListObj,      AdtDelphiConstExprList,       true);
  initObject(FieldDeclList,       pFieldDeclListObj,      AdtDelphiFieldDeclList,       true);
  initObject(VariantSectionList,  pVariantSectionListObj, AdtDelphiVariantSectionList,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecVariant::AdtDelphiRecVariant(const AdtDelphiRecVariant& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ConstExprList,      rCopy, AdtDelphiConstExprList);
  copyObject(FieldDeclList,      rCopy, AdtDelphiFieldDeclList);
  copyObject(VariantSectionList, rCopy, AdtDelphiVariantSectionList);
}

//  ----------------------------------------------------------------------------

AdtDelphiRecVariant::~AdtDelphiRecVariant()
{
  UtlReleaseReference(ConstExprList);
  UtlReleaseReference(FieldDeclList);
  UtlReleaseReference(VariantSectionList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRecVariant::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ConstExprList != 0)
  {
    ConstExprList->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : (");
  }

  if (FieldDeclList != 0)
  {
    FieldDeclList->writeDelphi(pOutFile, nMode);
  }

  if (VariantSectionList != 0)
  {
    VariantSectionList->writeDelphi(pOutFile, nMode);
  }

  if (ConstExprList != 0)
  {
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRecVariant, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstExprList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstExprList::AdtDelphiConstExprList(AdtParser* pConstExprObj)
 : AdtDelphiBase()
{
  add(pConstExprObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstExprList::AdtDelphiConstExprList(const AdtDelphiConstExprList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiConstExprList::~AdtDelphiConstExprList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstExprList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSetType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSetType::AdtDelphiSetType(AdtParser* pOrdinalTypeObj)
 : AdtDelphiBase()
{
  initObject(OrdinalType, pOrdinalTypeObj, AdtDelphiOrdinalType, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetType::AdtDelphiSetType(const AdtDelphiSetType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(OrdinalType, rCopy, AdtDelphiOrdinalType);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetType::~AdtDelphiSetType()
{
  UtlReleaseReference(OrdinalType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSetType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (OrdinalType != 0)
  {
    write(pOutFile, "set of ");
    OrdinalType->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSetType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFileType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFileType::AdtDelphiFileType(AdtParser* pUnitIdObj,
                                     AdtParser* pTypeIdObj)
 : AdtDelphiBase()
{
  initObject(UnitId, pUnitIdObj, AdtDelphiUnitId, true);
  initObject(TypeId, pTypeIdObj, AdtDelphiTypeId, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiFileType::AdtDelphiFileType(const AdtDelphiFileType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(UnitId, rCopy, AdtDelphiUnitId);
  copyObject(TypeId, rCopy, AdtDelphiTypeId);
}

//  ----------------------------------------------------------------------------

AdtDelphiFileType::~AdtDelphiFileType()
{
  UtlReleaseReference(UnitId);
  UtlReleaseReference(TypeId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFileType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypeId != 0)
  {
    write(pOutFile, "file of ");
  }

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFileType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiPointerType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiPointerType::AdtDelphiPointerType(AdtParser* pUnitIdObj,
                                           AdtParser* pTypeIdObj)
 : AdtDelphiBase()
{
  initObject(UnitId, pUnitIdObj, AdtDelphiUnitId, true);
  initObject(TypeId, pTypeIdObj, AdtDelphiTypeId, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiPointerType::AdtDelphiPointerType(const AdtDelphiPointerType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(UnitId, rCopy, AdtDelphiUnitId);
  copyObject(TypeId, rCopy, AdtDelphiTypeId);
}

//  ----------------------------------------------------------------------------

AdtDelphiPointerType::~AdtDelphiPointerType()
{
  UtlReleaseReference(UnitId);
  UtlReleaseReference(TypeId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPointerType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (TypeId != 0)
  {
    write(pOutFile, "^");
  }

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiPointerType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProcedureType::AdtDelphiProcedureType(AdtParser* pProcedureHeadingObj,
                                               AdtParser* pFunctionHeadingObj,
                                               bool bOfObject)
 : AdtDelphiBase()
{
  initObject(ProcedureHeading,  pProcedureHeadingObj, AdtDelphiProcedureHeading,  true);
  initObject(FunctionHeading,   pFunctionHeadingObj,  AdtDelphiFunctionHeading,   true);

  OfObject = bOfObject;
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureType::AdtDelphiProcedureType(const AdtDelphiProcedureType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ProcedureHeading, rCopy, AdtDelphiProcedureHeading);
  copyObject(FunctionHeading,  rCopy, AdtDelphiFunctionHeading);

  OfObject = rCopy.OfObject;
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureType::~AdtDelphiProcedureType()
{
  UtlReleaseReference(ProcedureHeading);
  UtlReleaseReference(FunctionHeading);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ProcedureHeading != 0)
  {
    ProcedureHeading->writeDelphi(pOutFile, nMode);
  }

  if (FunctionHeading != 0)
  {
    FunctionHeading->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProcedureType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVarSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVarSection::AdtDelphiVarSection(AdtParser* pVarDeclListObj,
                                         const char* pComment)
 : AdtDelphiBase()
{
  initObject(VarDeclList, pVarDeclListObj, AdtDelphiVarDeclList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiVarSection::AdtDelphiVarSection(const AdtDelphiVarSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(VarDeclList, rCopy, AdtDelphiVarDeclList);
}

//  ----------------------------------------------------------------------------

AdtDelphiVarSection::~AdtDelphiVarSection()
{
  UtlReleaseReference(VarDeclList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVarSection::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (VarDeclList != 0)
  {
    VarDeclList->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVarSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (VarDeclList != 0)
  {
    write(pOutFile, "var ");

    pOutFile.incrementIndent();
    pOutFile.newline();

    VarDeclList->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.homeline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVarSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVarDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVarDeclList::AdtDelphiVarDeclList(AdtParser* pVarDeclObj)
 : AdtDelphiBase()
{
  add(pVarDeclObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiVarDeclList::AdtDelphiVarDeclList(const AdtDelphiVarDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiVarDeclList::~AdtDelphiVarDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVarDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiVarDecl method implementations
//  ----------------------------------------------------------------------------
AdtDelphiVarDecl::AdtDelphiVarDecl(AdtParser* pIdentListObj,
                                   AdtParser* pTypeObj,
                                   AdtParser* pIdentObj,
                                   AdtParser* pConstExprObj,
                                   bool bAbsolute)
 : AdtDelphiBase()
{
  initObject(IdentList, pIdentListObj,  AdtDelphiIdentList, true);
  initObject(Type,      pTypeObj,       AdtDelphiType,      true);
  initObject(Ident,     pIdentObj,      AdtDelphiIdent,     true);
  initObject(ConstExpr, pConstExprObj,  AdtDelphiConstExpr, true);

  Absolute = bAbsolute;
}

//  ----------------------------------------------------------------------------

AdtDelphiVarDecl::AdtDelphiVarDecl(const AdtDelphiVarDecl& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList, rCopy, AdtDelphiIdentList);
  copyObject(Type,      rCopy, AdtDelphiType);
  copyObject(Ident,     rCopy, AdtDelphiIdent);
  copyObject(ConstExpr, rCopy, AdtDelphiConstExpr);

  Absolute = rCopy.Absolute;
}

//  ----------------------------------------------------------------------------

AdtDelphiVarDecl::~AdtDelphiVarDecl()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(Type);
  UtlReleaseReference(Ident);
  UtlReleaseReference(ConstExpr);
}

//  ----------------------------------------------------------------------------

void AdtDelphiVarDecl::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (IdentList != 0)
  {
    IdentList->enumerateAddByObjList(rMap, pObj);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVarDecl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* sDimension = 0;
  bool        bKeep      = true;

  writePragmas(pOutFile);

  if (Type != 0)
  {
    Type->writeFortran(pOutFile, nMode, sDimension, bKeep);
  }

  if (bKeep)
  {
    write(pOutFile, ' ');

    if (IdentList != 0)
    {
      IdentList->writeArrayBounds(pOutFile, nMode, sDimension);
    }
    else if (Ident != 0)
    {
      Ident->writeFortran(pOutFile);
    }

    if (Absolute)
    {
      ::printf("ERROR: Translation of Pascal absolute var declaration on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }

    if (Ident != 0)
    {
      ::printf("ERROR: Translation of Pascal initialised var declaration on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (ConstExpr != 0)
    {
      ::printf("ERROR: Translation of Pascal initialised var declaration on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiVarDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    IdentList->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (Type != 0)
  {
    Type->writeDelphi(pOutFile, nMode);
  }

  if (Absolute)
  {
    write(pOutFile, " absolute ");
  }
  else if ((Ident != 0) || (ConstExpr != 0))
  {
    write(pOutFile, " = ");
  }

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
  }
  else if (ConstExpr != 0)
  {
    ConstExpr->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiVarDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExpression method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExpression::AdtDelphiExpression(AdtParser* pExpressionRelOpListObj)
 : AdtDelphiBase()
{
  initObject(ExpressionRelOpList, pExpressionRelOpListObj,  AdtDelphiExpressionRelOpList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiExpression::AdtDelphiExpression(const AdtDelphiExpression& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ExpressionRelOpList, rCopy, AdtDelphiExpressionRelOpList);
}

//  ----------------------------------------------------------------------------

AdtDelphiExpression::~AdtDelphiExpression()
{
  UtlReleaseReference(ExpressionRelOpList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExpression::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (ExpressionRelOpList != 0)
  {
    ExpressionRelOpList->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExpression::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ExpressionRelOpList != 0)
  {
    ExpressionRelOpList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExpression, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExpressionRelOpList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExpressionRelOpList::AdtDelphiExpressionRelOpList(AdtParser* pExpressionRelOpObj)
 : AdtDelphiBase()
{
  add(pExpressionRelOpObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiExpressionRelOpList::AdtDelphiExpressionRelOpList(const AdtDelphiExpressionRelOpList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiExpressionRelOpList::~AdtDelphiExpressionRelOpList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExpressionRelOpList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExpressionRelOp method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExpressionRelOp::AdtDelphiExpressionRelOp(AdtRelOp nRelOp,
                                                   AdtParser* pSimpleExpressionObj)
 : AdtDelphiBase()
{
  RelOp = nRelOp;

  initObject(SimpleExpression,  pSimpleExpressionObj, AdtDelphiSimpleExpression,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiExpressionRelOp::AdtDelphiExpressionRelOp(const AdtDelphiExpressionRelOp& rCopy)
 : AdtDelphiBase(rCopy)
{
  RelOp = rCopy.RelOp;

  copyObject(SimpleExpression, rCopy, AdtDelphiSimpleExpression);
}

//  ----------------------------------------------------------------------------

AdtDelphiExpressionRelOp::~AdtDelphiExpressionRelOp()
{
  UtlReleaseReference(SimpleExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExpressionRelOp::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pRelOp = 0;

  writePragmas(pOutFile);

  switch (RelOp)
  {
    case AdtRelOp_GT:
    {
      pRelOp = ".GT.";
      break;
    }

    case AdtRelOp_LT:
    {
      pRelOp = ".LT.";
      break;
    }

    case AdtRelOp_LE:
    {
      pRelOp = ".LE.";
      break;
    }

    case AdtRelOp_GE:
    {
      pRelOp = ".GE.";
      break;
    }

    case AdtRelOp_NE:
    {
      pRelOp = ".NE.";
      break;
    }

    case AdtRelOp_EQ:
    {
      pRelOp = ".EQ.";
      break;
    }

    case AdtRelOp_IN:
    case AdtRelOp_IS:
    case AdtRelOp_AS:
    {
      //NotSupported
      break;
    }

    case AdtRelOp_EMPTY:
    {
      break;
    }
  }

  if (SimpleExpression != 0)
  {
    if (pRelOp != 0)
    {
      write(pOutFile, pRelOp);
    }

    SimpleExpression->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExpressionRelOp::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pRelOp = 0;

  writeExpanded(pOutFile, comment());

  switch (RelOp)
  {
    case AdtRelOp_GT:
    {
      pRelOp = " > ";
      break;
    }

    case AdtRelOp_LT:
    {
      pRelOp = " < ";
      break;
    }

    case AdtRelOp_LE:
    {
      pRelOp = " <= ";
      break;
    }

    case AdtRelOp_GE:
    {
      pRelOp = " >= ";
      break;
    }

    case AdtRelOp_NE:
    {
      pRelOp = " <> ";
      break;
    }

    case AdtRelOp_IN:
    {
      pRelOp = " in ";
      break;
    }

    case AdtRelOp_IS:
    {
      pRelOp = " is ";
      break;
    }

    case AdtRelOp_AS:
    {
      pRelOp = " as ";
      break;
    }

    case AdtRelOp_EQ:
    {
      pRelOp = " = ";
      break;
    }

    case AdtRelOp_EMPTY:
    {
      break;
    }
  }

  if (SimpleExpression != 0)
  {
    if (pRelOp != 0)
    {
      write(pOutFile, pRelOp);
    }

    SimpleExpression->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExpressionRelOp, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpression method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSimpleExpression::AdtDelphiSimpleExpression(AdtParser* pSimpleExpressionAddOpListObj)
 : AdtDelphiBase()
{
  initObject(SimpleExpressionAddOpList, pSimpleExpressionAddOpListObj, AdtDelphiSimpleExpressionAddOpList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpression::AdtDelphiSimpleExpression(const AdtDelphiSimpleExpression& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(SimpleExpressionAddOpList, rCopy, AdtDelphiSimpleExpressionAddOpList);
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpression::~AdtDelphiSimpleExpression()
{
  UtlReleaseReference(SimpleExpressionAddOpList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleExpression::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (SimpleExpressionAddOpList != 0)
  {
    SimpleExpressionAddOpList->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleExpression::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (SimpleExpressionAddOpList != 0)
  {
    SimpleExpressionAddOpList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSimpleExpression, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpressionAddOpList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSimpleExpressionAddOpList::AdtDelphiSimpleExpressionAddOpList(AdtParser* pSimpleExpressionAddOpObj)
 : AdtDelphiBase()
{
  add(pSimpleExpressionAddOpObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpressionAddOpList::AdtDelphiSimpleExpressionAddOpList(const AdtDelphiSimpleExpressionAddOpList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpressionAddOpList::~AdtDelphiSimpleExpressionAddOpList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSimpleExpressionAddOpList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpressionAddOp method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSimpleExpressionAddOp::AdtDelphiSimpleExpressionAddOp(AdtAddOp nAddOp,
                                                               AdtSign nSign,
                                                               AdtParser* pTermObj)
 : AdtDelphiBase()
{
  initObject(Term, pTermObj, AdtDelphiTerm, true);

  AddOp = nAddOp;
  Sign  = nSign;
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpressionAddOp::AdtDelphiSimpleExpressionAddOp(const AdtDelphiSimpleExpressionAddOp& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Term, rCopy, AdtDelphiTerm);

  AddOp = rCopy.AddOp;
  Sign  = rCopy.Sign;
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleExpressionAddOp::~AdtDelphiSimpleExpressionAddOp()
{
  UtlReleaseReference(Term);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleExpressionAddOp::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pAddOp = 0;
  const char* pSign  = 0;

  writePragmas(pOutFile);

  switch (Sign)
  {
    case AdtSign_PLUS:
    {
      pSign = "+";
      break;
    }

    case AdtSign_MINUS:
    {
      pSign = "-";
      break;
    }

    case AdtSign_EMPTY:
    {
      break;
    }
  }

  switch (AddOp)
  {
    case AdtAddOp_PLUS:
    {
      pAddOp = " + ";
      break;
    }

    case AdtAddOp_MINUS:
    {
      pAddOp = " - ";
      break;
    }

    case AdtAddOp_OR:
    {
      pAddOp = ".OR.";
      break;
    }

    case AdtAddOp_XOR:
    {
      pAddOp = ".XOR.";
      break;
    }

    case AdtAddOp_EMPTY:
    {
      break;
    }
  }

  if (Term != 0)
  {
    if (pAddOp != 0)
    {
      write(pOutFile, pAddOp);
    }

    if (pSign != 0)
    {
      write(pOutFile, pSign);
    }

    Term->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleExpressionAddOp::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pAddOp = 0;
  const char* pSign  = 0;

  writeExpanded(pOutFile, comment());

  switch (Sign)
  {
    case AdtSign_PLUS:
    {
      pSign = "+";
      break;
    }

    case AdtSign_MINUS:
    {
      pSign = "-";
      break;
    }

    case AdtSign_EMPTY:
    {
      break;
    }
  }

  switch (AddOp)
  {
    case AdtAddOp_PLUS:
    {
      pAddOp = " + ";
      break;
    }

    case AdtAddOp_MINUS:
    {
      pAddOp = " - ";
      break;
    }

    case AdtAddOp_OR:
    {
      pAddOp = " or ";
      break;
    }

    case AdtAddOp_XOR:
    {
      pAddOp = " xor ";
      break;
    }

    case AdtAddOp_EMPTY:
    {
      break;
    }
  }

  if (Term != 0)
  {
    if (pAddOp != 0)
    {
      write(pOutFile, pAddOp);
    }

    if (pSign != 0)
    {
      write(pOutFile, pSign);
    }

    Term->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSimpleExpressionAddOp, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTerm method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTerm::AdtDelphiTerm(AdtParser* pFactorMulOpListObj)
 : AdtDelphiBase()
{
  initObject(FactorMulOpList, pFactorMulOpListObj, AdtDelphiFactorMulOpList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiTerm::AdtDelphiTerm(const AdtDelphiTerm& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(FactorMulOpList, rCopy, AdtDelphiFactorMulOpList);
}

//  ----------------------------------------------------------------------------

AdtDelphiTerm::~AdtDelphiTerm()
{
  UtlReleaseReference(FactorMulOpList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiTerm::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (FactorMulOpList != 0)
  {
    FactorMulOpList->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiTerm::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (FactorMulOpList != 0)
  {
    FactorMulOpList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTerm, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFactorMulOpList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFactorMulOpList::AdtDelphiFactorMulOpList(AdtParser* pFactorMulOpObj)
 : AdtDelphiBase()
{
  add(pFactorMulOpObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiFactorMulOpList::AdtDelphiFactorMulOpList(const AdtDelphiFactorMulOpList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiFactorMulOpList::~AdtDelphiFactorMulOpList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFactorMulOpList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFactorMulOp method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFactorMulOp::AdtDelphiFactorMulOp(AdtMulOp nMulOp,
                                           AdtParser* pFactorObj)
 : AdtDelphiBase()
{
  MulOp = nMulOp;

  initObject(Factor,  pFactorObj, AdtDelphiFactor,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiFactorMulOp::AdtDelphiFactorMulOp(const AdtDelphiFactorMulOp& rCopy)
 : AdtDelphiBase(rCopy)
{
  MulOp = rCopy.MulOp;

  copyObject(Factor, rCopy, AdtDelphiFactor);
}

//  ----------------------------------------------------------------------------

AdtDelphiFactorMulOp::~AdtDelphiFactorMulOp()
{
  UtlReleaseReference(Factor);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFactorMulOp::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pMulOp = 0;

  writePragmas(pOutFile);

  switch (MulOp)
  {
    case AdtMulOp_MULTIPLY:
    {
      pMulOp = " * ";
      break;
    }

    case AdtMulOp_DIVIDE:
    {
      pMulOp = " / ";
      break;
    }

    case AdtMulOp_DIV:
    {
      ::printf("ERROR: Translation of Pascal DIV op on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }

    case AdtMulOp_MOD:
    {
      ::printf("ERROR: Translation of Pascal MOD op on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }

    case AdtMulOp_AND:
    {
      pMulOp = ".AND.";
      break;
    }

    case AdtMulOp_SHL:
    {
      ::printf("ERROR: Translation of Pascal SHL op on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }

    case AdtMulOp_SHR:
    {
      ::printf("ERROR: Translation of Pascal SHR op on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
      break;
    }

    case AdtMulOp_EMPTY:
    {
      break;
    }
  }

  if (Factor != 0)
  {
    if (pMulOp != 0)
    {
      write(pOutFile, pMulOp);
    }

    Factor->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFactorMulOp::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pMulOp = 0;

  writeExpanded(pOutFile, comment());

  switch (MulOp)
  {
    case AdtMulOp_MULTIPLY:
    {
      pMulOp = " * ";
      break;
    }

    case AdtMulOp_DIVIDE:
    {
      pMulOp = " / ";
      break;
    }

    case AdtMulOp_DIV:
    {
      pMulOp = " div ";
      break;
    }

    case AdtMulOp_MOD:
    {
      pMulOp = " mod ";
      break;
    }

    case AdtMulOp_AND:
    {
      pMulOp = " and ";
      break;
    }

    case AdtMulOp_SHL:
    {
      pMulOp = " shl ";
      break;
    }

    case AdtMulOp_SHR:
    {
      pMulOp = " shr ";
      break;
    }

    case AdtMulOp_EMPTY:
    {
      break;
    }
  }

  if (Factor != 0)
  {
    if (pMulOp != 0)
    {
      write(pOutFile, pMulOp);
    }

    Factor->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFactorMulOp, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFactor method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFactor::AdtDelphiFactor(AdtParser* pDesignatorObj,
                                 bool bHasAt,
                                 AdtParser* pNumberObj,
                                 AdtParser* pStringObj,
                                 bool bHasNil,
                                 AdtParser* pExpressionObj,
                                 AdtParser* pFactorObj,
                                 AdtParser* pSetConstructorObj,
                                 AdtParser* pSizeofTypeObj,
                                 AdtParser* pCastExpressionObj)
 : AdtDelphiBase()
{
  initObject(Designator,      pDesignatorObj,     AdtDelphiDesignator,      true);
  initObject(Number,          pNumberObj,         AdtDelphiNumber,          true);
  initObject(String,          pStringObj,         AdtDelphiString,          true);
  initObject(Expression,      pExpressionObj,     AdtDelphiExpression,      true);
  initObject(Factor,          pFactorObj,         AdtDelphiFactor,          true);
  initObject(SetConstructor,  pSetConstructorObj, AdtDelphiSetConstructor,  true);
  initObject(SizeofType,      pSizeofTypeObj,     AdtDelphiSizeofType,      true);
  initObject(CastExpression,  pCastExpressionObj, AdtDelphiCastExpression,  true);

  HasAt   = bHasAt;
  HasNil  = bHasNil;
}

//  ----------------------------------------------------------------------------

AdtDelphiFactor::AdtDelphiFactor(const AdtDelphiFactor& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Designator,     rCopy, AdtDelphiDesignator);
  copyObject(Number,         rCopy, AdtDelphiNumber);
  copyObject(String,         rCopy, AdtDelphiString);
  copyObject(Expression,     rCopy, AdtDelphiExpression);
  copyObject(Factor,         rCopy, AdtDelphiFactor);
  copyObject(SetConstructor, rCopy, AdtDelphiSetConstructor);
  copyObject(SizeofType,     rCopy, AdtDelphiSizeofType);
  copyObject(CastExpression, rCopy, AdtDelphiCastExpression);

  HasAt   = rCopy.HasAt;
  HasNil  = rCopy.HasNil;
}

//  ----------------------------------------------------------------------------

AdtDelphiFactor::~AdtDelphiFactor()
{
  UtlReleaseReference(Designator);
  UtlReleaseReference(Number);
  UtlReleaseReference(String);
  UtlReleaseReference(Expression);
  UtlReleaseReference(Factor);
  UtlReleaseReference(SetConstructor);
  UtlReleaseReference(SizeofType);
  UtlReleaseReference(CastExpression);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiFactor::substituteMacroExpression(AdtDelphiExpression* pExpression)
{
  bool bSubstitued = false;

  if ((pExpression    != 0) &&
      (Designator     != 0) &&
      (Number         == 0) &&
      (String         == 0) &&
      (Expression     == 0) &&
      (Factor         == 0) &&
      (SetConstructor == 0) &&
      (SizeofType     == 0) &&
      !HasAt                &&
      !HasNil)
  {
    UtlReleaseReference(Designator);

    Designator = 0;
    Expression = pExpression;

    Expression->lock();
    Expression->parent(this);

    bSubstitued = true;
  }
  else
  {
    FAIL();
  }

  return (bSubstitued);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiFactor::substituteMacroDesignator(AdtDelphiDesignator* pDesignator)
{
  bool bSubstitued = false;

  if ((pDesignator    != 0) &&
      (Designator     != 0) &&
      (Number         == 0) &&
      (String         == 0) &&
      (Expression     == 0) &&
      (Factor         == 0) &&
      (SetConstructor == 0) &&
      (SizeofType     == 0) &&
      !HasAt                &&
      !HasNil)
  {
    UtlReleaseReference(Designator);

    Designator = pDesignator;

    Designator->lock();
    Designator->parent(this);

    bSubstitued = true;
  }
  else
  {
    FAIL();
  }

  return (bSubstitued);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFactor::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (HasAt)
  {
    ::printf("ERROR: Translation of Pascal AT keyword on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  if (HasNil)
  {
    ::printf("ERROR: Translation of Pascal NILL keyword on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  if (Designator != 0)
  {
    Designator->writeFortran(pOutFile, nMode);
  }
  else if (Number != 0)
  {
    Number->writeFortran(pOutFile, nMode);
  }
  else if (String != 0)
  {
    String->writeFortran(pOutFile, nMode);
  }
  else if (Expression != 0)
  {
    write(pOutFile, "(");
    Expression->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }
  else if (Factor != 0)
  {
    write(pOutFile, ".NOT.(");
    Factor->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }
  else if (SetConstructor != 0)
  {
    ::printf("ERROR: Translation of Pascal set contructor on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }
  else if (SizeofType != 0)
  {
    ::printf("ERROR: Translation of Pascal sizeof operator on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }
  else if (CastExpression != 0)
  {
    CastExpression->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFactor::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (HasAt)
  {
    write(pOutFile, "@");
  }

  if (HasNil)
  {
    write(pOutFile, "nil ");
  }

  if (Designator != 0)
  {
    Designator->writeDelphi(pOutFile, nMode);
  }
  else if (Number != 0)
  {
    Number->writeDelphi(pOutFile, nMode);
  }
  else if (String != 0)
  {
    String->writeDelphi(pOutFile, nMode);
  }
  else if (Expression != 0)
  {
    write(pOutFile, "(");
    Expression->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }
  else if (Factor != 0)
  {
    write(pOutFile, "not (");
    Factor->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }
  else if (SetConstructor != 0)
  {
    SetConstructor->writeDelphi(pOutFile, nMode);
  }
  else if (SizeofType != 0)
  {
    SizeofType->writeDelphi(pOutFile, nMode);
  }
  else if (CastExpression != 0)
  {
    CastExpression->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFactor, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCastExpression method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCastExpression::AdtDelphiCastExpression(AdtParser* pOrdIdentObj,
                                                 AdtParser* pRealTypeObj,
                                                 AdtParser* pExpressionObj)
  : AdtDelphiBase()
{
  initObject(OrdIdent,    pOrdIdentObj,   AdtDelphiOrdIdent,    true);
  initObject(RealType,    pRealTypeObj,   AdtDelphiRealType,    true);
  initObject(Expression,  pExpressionObj, AdtDelphiExpression,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiCastExpression::AdtDelphiCastExpression(const AdtDelphiCastExpression& rCopy)
  : AdtDelphiBase(rCopy)
{
  copyObject(OrdIdent,    rCopy,  AdtDelphiOrdIdent);
  copyObject(RealType,    rCopy,  AdtDelphiRealType);
  copyObject(Expression,  rCopy,  AdtDelphiExpression);
}

//  ----------------------------------------------------------------------------

AdtDelphiCastExpression::~AdtDelphiCastExpression()
{
  UtlReleaseReference(OrdIdent);
  UtlReleaseReference(RealType);
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCastExpression::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: type casting not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  if ((OrdIdent != 0) || (RealType != 0))
  {
    ::printf("ERROR: Translation of Pascal type casting on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  if (Expression != 0)
  {
    Expression->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCastExpression::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (OrdIdent != 0)
  {
    OrdIdent->writeDelphi(pOutFile, nMode);
  }
  else if (RealType != 0)
  {
    RealType->writeDelphi(pOutFile, nMode);
  }

  if (Expression != 0)
  {
    write(pOutFile, "(");
    Expression->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCastExpression, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignator method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDesignator::AdtDelphiDesignator(AdtParser* pDesignatorObjListObj)
 : AdtDelphiBase()
{
  initObject(DesignatorObjList, pDesignatorObjListObj, AdtDelphiDesignatorObjList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignator::AdtDelphiDesignator(const AdtDelphiDesignator& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(DesignatorObjList, rCopy, AdtDelphiDesignatorObjList);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignator::~AdtDelphiDesignator()
{
  UtlReleaseReference(DesignatorObjList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignator::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (DesignatorObjList != 0)
  {
    //We don't support array slices for dereferenced objects (too hard).
    if ((nMode == FORTRAN_MODE_ARRAY_SLICE) && (DesignatorObjList->listSize() > 1))
    {
      DesignatorObjList->writeFortran(pOutFile, 0);
    }
    else
    {
      DesignatorObjList->writeFortran(pOutFile, nMode);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignator::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (DesignatorObjList != 0)
  {
    DesignatorObjList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDesignator, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorObjList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDesignatorObjList::AdtDelphiDesignatorObjList(AdtParser* pDesignatorObj)
 : AdtDelphiBase()
{
  add(pDesignatorObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorObjList::AdtDelphiDesignatorObjList(const AdtDelphiDesignatorObjList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorObjList::~AdtDelphiDesignatorObjList()
{

}

//  ----------------------------------------------------------------------------

bool AdtDelphiDesignatorObjList::isProcedureCall() const
{
  bool    bIsProcedureCall = true;
  size_t  nSize            = objList().size();
  bool    bGlobalScope     = (nSize == 1);

  AdtParserPtrListConstIter Iter;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtDelphiDesignatorObj*  pObj = (AdtDelphiDesignatorObj*)((*Iter).object());

    nSize--;

    if (pObj != 0)
    {
      if (nSize > 0)
      {
        if (!pObj->isSimpleReference())
        {
          bIsProcedureCall = false;
          break;
        }
      }
      else
      {
        //Last element
        if (!pObj->isProcedureCall(bGlobalScope))
        {
          bIsProcedureCall = false;
          break;
        }
      }
    }
  }

  return (bIsProcedureCall);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDesignatorObjList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorObj method implementations
//  ----------------------------------------------------------------------------
bool AdtDelphiDesignatorObj::buildSliceString(string& rSliceString) const
{
  bool            bBuilt  = false;
  AdtDelphiGoal*  pRoot   = AdtDelphiGoal::delphiRootObject();

  if ((Ident != 0) && (pRoot != 0))
  {
    const string&                 rName             = Ident->name();
    size_t                        nDereferenceCount = (DesignatorRefList != 0) ? DesignatorRefList->listSize() : 0;
    const AdtDelphiProcedureDecl* pProcDecl         = (AdtDelphiProcedureDecl*)findAscendantWithClass("AdtDelphiProcedureDecl");
    const AdtDelphiClassType*     pClassType        = pRoot->findClassType(pProcDecl->className());
    const AdtDelphiTypeId*        pTypeId           = 0;

    if (pProcDecl != 0)
    {
      //Search for variable in argument list
      const AdtDelphiFormalParam* pFormalParam  = pProcDecl->findFormalParam(rName);

      if (pFormalParam != 0)
      {
        pTypeId = (const AdtDelphiTypeId*)pFormalParam->findDescendant("Parameter,TypeId");
      }
      else
      {
        //Search for variable in local declarations
        const AdtDelphiVarDecl* pVarDecl  = pProcDecl->findVarDecl(rName);

        if (pVarDecl != 0)
        {
          pTypeId = (const AdtDelphiTypeId*)pVarDecl->findDescendant("Type,TypeId");
        }
        else if (pClassType != 0)
        {
          //Search for variable in class declarations
          const AdtParser*  pObj = 0;

          if (pClassType->findField(rName, pObj) && pObj->isType("AdtDelphiObjField"))
          {
            const AdtDelphiObjField*  pObjField = (const AdtDelphiObjField*)pObj;

            pTypeId = (const AdtDelphiTypeId*)pObjField->findDescendant("Type,TypeId");
          }
        }
      }

      if (pTypeId != 0)
      {
        const char* pType       = 0;
        const char* pDimension  = 0;

        //Find equivalent Fortran type and the array size.
        if (AdtDelphiBase::mapTypesToFortran(pTypeId->name(), pType, pDimension))
        {
          size_t      nDimensions = 1;
          const char* pComma      = ::strchr(pDimension, ',');

          for ( ; pComma != 0 ; pComma = ::strchr(pComma + 1, ','))
          {
            nDimensions++;
          }

          //Is this a slice?
          if (nDimensions > nDereferenceCount)
          {
            //This is a slice so we need to create a slice string to fully
            //dereference it. Find the root and then find the name of the
            //variable in the object tree. The name object has the array size
            //comment which we use to build the slice.
            const AdtParser*  pRootObj = pTypeId->findAscendantWithClass("AdtDelphiVarDecl");

            if (pRootObj == 0)
            {
              pRootObj = pTypeId->findAscendantWithClass("AdtDelphiParameter");
            }

            if (pRootObj == 0)
            {
              pRootObj = pTypeId->findAscendantWithClass("AdtDelphiObjField");
            }

            if (pRootObj != 0)
            {
              const AdtDelphiIdent* pIdentObj = (const AdtDelphiIdent*)pRootObj->findObject("AdtDelphiIdent", rName, false);

              if (pIdentObj != 0)
              {
                AdtStringList UpperBoundList;
                AdtStringList LowerBoundList;

                pIdentObj->enumerateArraySizes(UpperBoundList, LowerBoundList);

                if (UpperBoundList.size() == nDimensions)
                {
                  size_t            cn;
                  AdtStringListIter UpperBoundIter  = UpperBoundList.begin();
                  AdtStringListIter LowerBoundIter  = LowerBoundList.begin();

                  for (cn = 0 ; cn < nDereferenceCount ; cn++)
                  {
                    UpperBoundIter++;
                    LowerBoundIter++;
                  }

                  for ( ; cn < nDimensions ; cn++)
                  {
                    char          sBuffer[16] = {0};
                    const string& rLowerBound = *LowerBoundIter;
                    const string& rUpperBound = *UpperBoundIter;
                    int           nLowerBound = ::atoi(rLowerBound);

                    ::sprintf(sBuffer, "%d:", nLowerBound);

                    rSliceString += sBuffer;
                    rSliceString += rUpperBound;
                  }

                  bBuilt = true;
                }
                else
                {
                  ::printf("TRANSLATION ERROR : Wrong number of inline comment defined dimensions for variable %s\n"
                           " on line %d in file %s\n Check that the declaration of %s has explicit dimensions.\n "
                           " In Delphi source this is given in trailing inline comments for example\n Foo{FooDim}:ARRAY_1D;\n\n",
                           rName.c_str(),
                           lineNumber(),
                           fileName(),
                           rName.c_str());

                  AdtExit(-1);
                }
              }
            }
            else
            {
              ::printf("TRANSLATION ERROR : can't find definition root for variable named %s\n on line %d in file %s\n", rName.c_str(), lineNumber(), fileName());

              AdtExit(-1);
            }
          }
        }
      }
    }
  }

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

void AdtDelphiDesignatorObj::writeFortranInner(AdtFile& pOutFile,
                                               int nMode,
                                               bool bIsProcedureCall,
                                               int nClassExtendName) const
{
  string  SliceString;
  bool    bHasSlice         = false;
  bool    bEmptyParenthesis = EmptyParenthesis;

  if (Ident)
  {
    if (bIsProcedureCall)
    {
      Ident->writeFortran(pOutFile, nClassExtendName);
    }
    else
    {
      if (Ident->name().eq("break"))
      {
        pOutFile.write("EXIT");

        bEmptyParenthesis = false;
      }
      else if (Ident->name().eq("continue"))
      {
        pOutFile.write("CYLE");

        bEmptyParenthesis = false;
      }
      else
      {
        //function call or variable
        Ident->writeFortran(pOutFile, nClassExtendName);
      }
    }

    if (nMode == FORTRAN_MODE_ARRAY_SLICE)
    {
      if (bIsProcedureCall)
      {
        nMode = 0;
      }
      else
      {
        bHasSlice = buildSliceString(SliceString);
      }
    }
  }

  if ((ExprList != 0) || bEmptyParenthesis)
  {
    write(pOutFile, "(");
  }

  if (ExprList != 0)
  {
    ExprList->writeFortran(pOutFile, nMode);
  }

  if ((ExprList != 0) || bEmptyParenthesis)
  {
    write(pOutFile, ")");
  }

  if (DesignatorRefList)
  {
    write(pOutFile, "(");
    DesignatorRefList->writeFortran(pOutFile, nMode);

    if (bHasSlice)
    {
      //Write extra slice info
      write(pOutFile, ",");
      write(pOutFile, SliceString);
    }

    write(pOutFile, ")");
  }
  else if (bHasSlice)
  {
    write(pOutFile, "(");
    write(pOutFile, SliceString);
    write(pOutFile, ")");
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorObj::AdtDelphiDesignatorObj(AdtParser* pIdentObj,
                                               AdtParser* pExprListObj,
                                               AdtParser* pDesignatorRefListObj,
                                               bool bEmptyParenthesis,
                                               bool bInherited)
 : AdtDelphiBase()
{
  initObject(Ident,             pIdentObj,              AdtDelphiIdent,             true);
  initObject(ExprList,          pExprListObj,           AdtDelphiExprList,          true);
  initObject(DesignatorRefList, pDesignatorRefListObj,  AdtDelphiDesignatorRefList, true);

  EmptyParenthesis  = bEmptyParenthesis;
  Inherited         = bInherited;
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorObj::AdtDelphiDesignatorObj(const AdtDelphiDesignatorObj& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Ident,             rCopy, AdtDelphiIdent);
  copyObject(ExprList,          rCopy, AdtDelphiExprList);
  copyObject(DesignatorRefList, rCopy, AdtDelphiDesignatorRefList);

  EmptyParenthesis  = rCopy.EmptyParenthesis;
  Inherited         = rCopy.Inherited;
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorObj::~AdtDelphiDesignatorObj()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(ExprList);
  UtlReleaseReference(DesignatorRefList);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiDesignatorObj::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowable = AdtDelphiBase::allowableMatch(pObj);

  if (bAllowable)
  {
    AdtDelphiDesignatorObj* pDesignatorObj;

    pDesignatorObj  = (AdtDelphiDesignatorObj*)pObj;
    bAllowable      = isSimpleReference() && pDesignatorObj->isSimpleReference();
  }

  return (bAllowable);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiDesignatorObj::isMacroReplaceable(size_t nListSize, AdtDelphiExprList** ppExpressionList) const
{
  bool bIsReplaceable = false;

  if ((ExprList             != 0        ) &&
      (DesignatorRefList    == 0        ) &&
      (ExprList->listSize() == nListSize))
  {
    bIsReplaceable = true;

    if (ppExpressionList != 0)
    {
      *ppExpressionList = ExprList;
    }
  }

  return (bIsReplaceable);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignatorObj::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (Ident)
  {
    bool  bWrite            = true;
    bool  bIsProcedureCall  = isProcedureCall(true, false);
    int   nClassExtendName  = bIsProcedureCall ? FORTRAN_MODE_CLASS_EXTEND_NAME : 0;

    if (bIsProcedureCall)
    {
      if (Ident->name().eq("XCOPY"))
      {
        string          sCode;
        string          sBuffer;
        AdtFile         WriteFile;
        AdtSliceBuilder SliceBuilder;

        WriteFile.open(sBuffer);

        // Translate XCOPY to slice operation
        writeFortranInner(WriteFile,
                          nMode,
                          bIsProcedureCall,
                          0);

        WriteFile.close();

        // Need to translate the XCOPY expression in sBuffer to equivalent slice operation
        if (!SliceBuilder.convertXCopy(sBuffer, sCode))
        {
          SliceBuilder.reportError(sBuffer, lineNumber(), fileName());
        }

        write(pOutFile, sCode);
        pOutFile.newline();

        bWrite = false;
      }
      else if (Ident->name().eq("ZERO"))
      {
        string          sCode;
        string          sBuffer;
        AdtFile         WriteFile;
        AdtSliceBuilder SliceBuilder;

        WriteFile.open(sBuffer);

        // Translate ZERO to slice operation
        writeFortranInner(WriteFile,
                          nMode,
                          bIsProcedureCall,
                          0);

        WriteFile.close();

        // Need to translate the ZERO expression in sBuffer to equivalent slice operation
        if (!SliceBuilder.convertZero(sBuffer, sCode))
        {
          SliceBuilder.reportError(sBuffer, lineNumber(), fileName());
        }

        write(pOutFile, sCode);
        pOutFile.newline();

        bWrite = false;
      }
      else if (Ident->name().eq("power"))
      {
        AdtParserPtrListConstIter Iter  = ExprList->objList().begin();
        AdtDelphiBase*            pObjA = (AdtDelphiBase*)(AdtParser*)*Iter;

        Iter++;

        AdtDelphiBase*            pObjB = (AdtDelphiBase*)(AdtParser*)*Iter;

        write(pOutFile, "(");

        pObjA->writeFortran(pOutFile, nMode);

        write(pOutFile, " ** ");

        pObjB->writeFortran(pOutFile, nMode);

        write(pOutFile, ")");

        bWrite = false;
      }
    }

    if (bWrite)
    {
      writeFortranInner(pOutFile,
                        nMode,
                        bIsProcedureCall,
                        nClassExtendName);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignatorObj::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Inherited)
  {
    write(pOutFile, "INHERITED ");
  }

  if (Ident)
  {
    Ident->writeDelphi(pOutFile, nMode);
  }

  if ((ExprList != 0) || EmptyParenthesis)
  {
    write(pOutFile, "(");
  }

  if (ExprList != 0)
  {
    ExprList->writeDelphi(pOutFile, nMode);
  }

  if ((ExprList != 0) || EmptyParenthesis)
  {
    write(pOutFile, ")");
  }

  if (DesignatorRefList)
  {
    DesignatorRefList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiDesignatorObj::isProcedureCall(bool bExcludeReservedNames, bool bExcludeSpecial) const
{
  bool bIsProcedureCall = (((Ident != 0) && (ExprList != 0) && (DesignatorRefList == 0) && !EmptyParenthesis) ||
                           ((Ident != 0) && (ExprList == 0) && (DesignatorRefList == 0) &&  EmptyParenthesis));

  if (bIsProcedureCall && bExcludeReservedNames)
  {
    if ((Ident->name().eq("break")   )                     ||
        (Ident->name().eq("continue"))                     ||
       ((Ident->name().eq("XCOPY")   ) && bExcludeSpecial) ||
       ((Ident->name().eq("ZERO")    ) && bExcludeSpecial))
    {
      bIsProcedureCall = false;
    }
  }

  return (bIsProcedureCall);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDesignatorObj, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorRefList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDesignatorRefList::AdtDelphiDesignatorRefList(AdtParser* pDesignatorRefObj)
 : AdtDelphiBase()
{
  add(pDesignatorRefObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorRefList::AdtDelphiDesignatorRefList(const AdtDelphiDesignatorRefList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorRefList::~AdtDelphiDesignatorRefList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignatorRefList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  forAllWriteFortran(pOutFile, nMode, ",", false, true);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDesignatorRefList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorRef method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDesignatorRef::AdtDelphiDesignatorRef(AdtParser* pExprListObj)
 : AdtDelphiBase()
{
  initObject(ExprList, pExprListObj, AdtDelphiExprList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorRef::AdtDelphiDesignatorRef(const AdtDelphiDesignatorRef& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ExprList, rCopy, AdtDelphiExprList);
}

//  ----------------------------------------------------------------------------

AdtDelphiDesignatorRef::~AdtDelphiDesignatorRef()
{
  UtlReleaseReference(ExprList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignatorRef::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (ExprList != 0)
  {
    ExprList->writeFortran(pOutFile, nMode);
  }
  else
  {
    ::printf("ERROR: Translation of Pascal pointer dereferencing on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDesignatorRef::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ExprList != 0)
  {
    write(pOutFile, "[");
    ExprList->writeDelphi(pOutFile, nMode);
    write(pOutFile, "]");
  }
  else
  {
    write(pOutFile, "^");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDesignatorRef, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSetConstructor method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSetConstructor::AdtDelphiSetConstructor(AdtParser* pSetElementListObj)
 : AdtDelphiBase()
{
  initObject(SetElementList, pSetElementListObj, AdtDelphiSetElementList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetConstructor::AdtDelphiSetConstructor(const AdtDelphiSetConstructor& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(SetElementList, rCopy, AdtDelphiSetElementList);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetConstructor::~AdtDelphiSetConstructor()
{
  UtlReleaseReference(SetElementList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSetConstructor::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: sets not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSetConstructor::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "[");

  if (SetElementList != 0)
  {
    SetElementList->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, "]");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSetConstructor, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSetElementList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSetElementList::AdtDelphiSetElementList(AdtParser* pSetElementObj)
 : AdtDelphiBase()
{
  add(pSetElementObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetElementList::AdtDelphiSetElementList(const AdtDelphiSetElementList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiSetElementList::~AdtDelphiSetElementList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSetElementList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSetElement method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSetElement::AdtDelphiSetElement(AdtParser* pExpressionObj, AdtParser* pEndExpressionObj)
 : AdtDelphiBase()
{
  initObject(Expression,    pExpressionObj,     AdtDelphiExpression, true);
  initObject(EndExpression, pEndExpressionObj,  AdtDelphiExpression, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetElement::AdtDelphiSetElement(const AdtDelphiSetElement& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Expression,    rCopy, AdtDelphiExpression);
  copyObject(EndExpression, rCopy, AdtDelphiExpression);
}

//  ----------------------------------------------------------------------------

AdtDelphiSetElement::~AdtDelphiSetElement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(EndExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSetElement::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Expression != 0)
  {
    Expression->writeDelphi(pOutFile, nMode);
  }

  if (EndExpression != 0)
  {
    write(pOutFile, "..");
    EndExpression->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSetElement, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExprList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExprList::AdtDelphiExprList(AdtParser* pExprObj)
 : AdtDelphiBase()
{
  add(pExprObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiExprList::AdtDelphiExprList(const AdtDelphiExprList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiExprList::~AdtDelphiExprList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExprList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiStatement method implementations
//  ----------------------------------------------------------------------------
AdtDelphiStatement::AdtDelphiStatement(AdtParser* pLabelIdObj,
                                       AdtParser* pExitStatementObj,
                                       AdtParser* pSimpleStatementObj,
                                       AdtParser* pCompoundStmtObj,
                                       AdtParser* pIfStmtObj,
                                       AdtParser* pCaseStmtObj,
                                       AdtParser* pRepeatStmtObj,
                                       AdtParser* pWhileStmtObj,
                                       AdtParser* pForStmtObj,
                                       AdtParser* pWithStmtObj,
                                       const char* pComment)
 : AdtDelphiBase()
{
  initObject(LabelId,         pLabelIdObj,          AdtDelphiLabelId,         true);
  initObject(ExitStatement,   pExitStatementObj,    AdtDelphiExitStatement,   true);
  initObject(SimpleStatement, pSimpleStatementObj,  AdtDelphiSimpleStatement, true);
  initObject(CompoundStmt,    pCompoundStmtObj,     AdtDelphiCompoundStmt,    true);
  initObject(IfStmt,          pIfStmtObj,           AdtDelphiIfStmt,          true);
  initObject(CaseStmt,        pCaseStmtObj,         AdtDelphiCaseStmt,        true);
  initObject(RepeatStmt,      pRepeatStmtObj,       AdtDelphiRepeatStmt,      true);
  initObject(WhileStmt,       pWhileStmtObj,        AdtDelphiWhileStmt,       true);
  initObject(ForStmt,         pForStmtObj,          AdtDelphiForStmt,         true);
  initObject(WithStmt,        pWithStmtObj,         AdtDelphiWithStmt,        true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiStatement::AdtDelphiStatement(const AdtDelphiStatement& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(LabelId,         rCopy, AdtDelphiLabelId);
  copyObject(ExitStatement,   rCopy, AdtDelphiExitStatement);
  copyObject(SimpleStatement, rCopy, AdtDelphiSimpleStatement);
  copyObject(CompoundStmt,    rCopy, AdtDelphiCompoundStmt);
  copyObject(IfStmt,          rCopy, AdtDelphiIfStmt);
  copyObject(CaseStmt,        rCopy, AdtDelphiCaseStmt);
  copyObject(RepeatStmt,      rCopy, AdtDelphiRepeatStmt);
  copyObject(WhileStmt,       rCopy, AdtDelphiWhileStmt);
  copyObject(ForStmt,         rCopy, AdtDelphiForStmt);
  copyObject(WithStmt,        rCopy, AdtDelphiWithStmt);
}

//  ----------------------------------------------------------------------------

AdtDelphiStatement::~AdtDelphiStatement()
{
  UtlReleaseReference(LabelId);
  UtlReleaseReference(ExitStatement);
  UtlReleaseReference(SimpleStatement);
  UtlReleaseReference(CompoundStmt);
  UtlReleaseReference(IfStmt);
  UtlReleaseReference(CaseStmt);
  UtlReleaseReference(RepeatStmt);
  UtlReleaseReference(WhileStmt);
  UtlReleaseReference(ForStmt);
  UtlReleaseReference(WithStmt);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiStatement::substituteMacroCompoundStatement(AdtDelphiStmtList* pStatementList)
{
  bool bSubstituted = false;

  if ((pStatementList   != 0) &&
      (SimpleStatement  != 0) &&
      (ExitStatement    == 0) &&
      (CompoundStmt     == 0) &&
      (IfStmt           == 0) &&
      (CaseStmt         == 0) &&
      (RepeatStmt       == 0) &&
      (WhileStmt        == 0) &&
      (ForStmt          == 0) &&
      (WithStmt         == 0))
  {
    AdtDelphiCompoundStmt* pCompoundStmtObj = new AdtDelphiCompoundStmt(pStatementList);

    if (pCompoundStmtObj != 0)
    {
      UtlReleaseReference(SimpleStatement);

      SimpleStatement = 0;

      initObject(CompoundStmt, pCompoundStmtObj, AdtDelphiCompoundStmt, true);
      pCompoundStmtObj->depth(depth() + 1, true);

      UtlReleaseReference(pCompoundStmtObj);

      bSubstituted = true;
    }
  }

  return (bSubstituted);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiStatement::writeFortran(AdtFile& pOutFile, int nMode) const
{
  char  sLabel[7] = {0};

  writePragmas(pOutFile);

  if (LabelId != 0)
  {
    const string& rLabel = LabelId->name();

    if (rLabel.length() <= 5)
    {
      ::sprintf(sLabel, "%5s ", rLabel.c_str());
    }
    else
    {
      //Error, label too long.
    }
  }

  write(pOutFile, sLabel);

  if (ExitStatement != 0)
  {
    ExitStatement->writeFortran(pOutFile, nMode);
  }
  else if (SimpleStatement != 0)
  {
    if (SimpleStatement->isProcedureCall())
    {
      write(pOutFile, "CALL ");
    }

    SimpleStatement->writeFortran(pOutFile, nMode);
  }
  else if (CompoundStmt != 0)
  {
    CompoundStmt->writeFortran(pOutFile, nMode);
  }
  else if (IfStmt != 0)
  {
    IfStmt->writeFortran(pOutFile, nMode);
  }
  else if (CaseStmt != 0)
  {
    CaseStmt->writeFortran(pOutFile, nMode);
  }
  else if (RepeatStmt != 0)
  {
    RepeatStmt->writeFortran(pOutFile, nMode);
  }
  else if (WhileStmt != 0)
  {
    WhileStmt->writeFortran(pOutFile, nMode);
  }
  else if (ForStmt != 0)
  {
    ForStmt->writeFortran(pOutFile, nMode);
  }
  else if (WithStmt != 0)
  {
    WithStmt->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiStatement::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (LabelId != 0)
  {
    LabelId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ":");
  }

  if (ExitStatement != 0)
  {
    ExitStatement->writeDelphi(pOutFile, nMode);
  }
  else if (SimpleStatement != 0)
  {
    SimpleStatement->writeDelphi(pOutFile, nMode);
  }
  else if (CompoundStmt != 0)
  {
    CompoundStmt->writeDelphi(pOutFile, nMode);
  }
  else if (IfStmt != 0)
  {
    IfStmt->writeDelphi(pOutFile, nMode);
  }
  else if (CaseStmt != 0)
  {
    CaseStmt->writeDelphi(pOutFile, nMode);
  }
  else if (RepeatStmt != 0)
  {
    RepeatStmt->writeDelphi(pOutFile, nMode);
  }
  else if (WhileStmt != 0)
  {
    WhileStmt->writeDelphi(pOutFile, nMode);
  }
  else if (ForStmt != 0)
  {
    ForStmt->writeDelphi(pOutFile, nMode);
  }
  else if (WithStmt != 0)
  {
    WithStmt->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiStatement::hasType(const char* pType) const
{
  bool bHasType = false;

  if (ExitStatement != 0)
  {
    bHasType = ExitStatement->isType(pType);
  }
  else if (SimpleStatement != 0)
  {
    bHasType = SimpleStatement->isType(pType);
  }
  else if (CompoundStmt != 0)
  {
    bHasType = CompoundStmt->isType(pType);
  }
  else if (IfStmt != 0)
  {
    bHasType = IfStmt->isType(pType);
  }
  else if (CaseStmt != 0)
  {
    bHasType = CaseStmt->isType(pType);
  }
  else if (RepeatStmt != 0)
  {
    bHasType = RepeatStmt->isType(pType);
  }
  else if (WhileStmt != 0)
  {
    bHasType = WhileStmt->isType(pType);
  }
  else if (ForStmt != 0)
  {
    bHasType = ForStmt->isType(pType);
  }
  else if (WithStmt != 0)
  {
    bHasType = WithStmt->isType(pType);
  }

  return (bHasType);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiStatement, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiStmtList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiStmtList::AdtDelphiStmtList(AdtParser* pStmtObj)
 : AdtDelphiBase()
{
  add(pStmtObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiStmtList::AdtDelphiStmtList(const AdtDelphiStmtList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiStmtList::~AdtDelphiStmtList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiStmtList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiExitStatement method implementations
//  ----------------------------------------------------------------------------
AdtDelphiExitStatement::AdtDelphiExitStatement(bool bWithParenthesis)
 : AdtDelphiBase()
{
  WithParenthesis = bWithParenthesis;
}

//  ----------------------------------------------------------------------------

AdtDelphiExitStatement::AdtDelphiExitStatement(const AdtDelphiExitStatement& rCopy)
 : AdtDelphiBase(rCopy)
{
  WithParenthesis = rCopy.WithParenthesis;
}

//  ----------------------------------------------------------------------------

AdtDelphiExitStatement::~AdtDelphiExitStatement()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExitStatement::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  write(pOutFile, "RETURN");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiExitStatement::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (WithParenthesis)
  {
    write(pOutFile, "exit()");
  }
  else
  {
    write(pOutFile, "exit");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiExitStatement, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleStatement method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSimpleStatement::AdtDelphiSimpleStatement(AdtParser* pDesignatorObj,
                                                   AdtParser* pExpressionObj,
                                                   AdtParser* pSizeofTypeObj,
                                                   AdtParser* pIdentObj,
                                                   AdtParser* pExprListObj,
                                                   AdtParser* pLabelIdObj,
                                                   AdtParser* pCastExpressionObj,
                                                   bool bInherited,
                                                   AdtOpType nOpType)
 : AdtDelphiBase()
{
  initObject(Designator,      pDesignatorObj,     AdtDelphiDesignator,      true);
  initObject(Expression,      pExpressionObj,     AdtDelphiExpression,      true);
  initObject(SizeofType,      pSizeofTypeObj,     AdtDelphiSizeofType,      true);
  initObject(Ident,           pIdentObj,          AdtDelphiIdent,           true);
  initObject(ExprList,        pExprListObj,       AdtDelphiExprList,        true);
  initObject(LabelId,         pLabelIdObj,        AdtDelphiLabelId,         true);
  initObject(CastExpression,  pCastExpressionObj, AdtDelphiCastExpression,  true);

  Inherited = bInherited;
  OpType    = nOpType;
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleStatement::AdtDelphiSimpleStatement(const AdtDelphiSimpleStatement& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Designator,      rCopy, AdtDelphiDesignator);
  copyObject(Expression,      rCopy, AdtDelphiExpression);
  copyObject(SizeofType,      rCopy, AdtDelphiSizeofType);
  copyObject(Ident,           rCopy, AdtDelphiIdent);
  copyObject(ExprList,        rCopy, AdtDelphiExprList);
  copyObject(LabelId,         rCopy, AdtDelphiLabelId);
  copyObject(CastExpression,  rCopy, AdtDelphiCastExpression);

  Inherited = rCopy.Inherited;
  OpType    = rCopy.OpType;
}

//  ----------------------------------------------------------------------------

AdtDelphiSimpleStatement::~AdtDelphiSimpleStatement()
{
  UtlReleaseReference(Designator);
  UtlReleaseReference(Expression);
  UtlReleaseReference(SizeofType);
  UtlReleaseReference(Ident);
  UtlReleaseReference(ExprList);
  UtlReleaseReference(LabelId);
  UtlReleaseReference(CastExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleStatement::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pOperator = 0;

  writePragmas(pOutFile);

  switch(OpType)
  {
    default:
    case AdtOpType_ASSIGN:
    {
      break;
    }

    case AdtOpType_PLUS_EQUALS:
    {
      pOperator = " + ";
      break;
    }

    case AdtOpType_MINUS_EQUALS:
    {
      pOperator = " - ";
      break;
    }

    case AdtOpType_TIMES_EQUALS:
    {
      pOperator = " * ";
      break;
    }

    case AdtOpType_DIV_EQUALS:
    {
      pOperator = " / ";
      break;
    }
  }

  if (Designator != 0)
  {
    Designator->writeFortran(pOutFile, (Expression != 0) ? FORTRAN_MODE_ARRAY_SLICE : 0);
  }

  if (CastExpression != 0)
  {
    CastExpression->writeFortran(pOutFile, nMode);
  }

  if (Expression != 0)
  {
    write(pOutFile, " = ");

    if (pOperator != 0)
    {
      if (Designator != 0)
      {
        Designator->writeFortran(pOutFile, (Expression != 0) ? FORTRAN_MODE_ARRAY_SLICE : 0);
      }

      if (CastExpression != 0)
      {
        CastExpression->writeFortran(pOutFile, nMode);
      }

      write(pOutFile, pOperator);
      write(pOutFile, "(");

      Expression->writeFortran(pOutFile, (Designator != 0) ? FORTRAN_MODE_ARRAY_SLICE : 0);

      write(pOutFile, ")");
    }
    else
    {
      Expression->writeFortran(pOutFile, (Designator != 0) ? FORTRAN_MODE_ARRAY_SLICE : 0);
    }
  }

  if (SizeofType != 0)
  {
    ::printf("ERROR: Translation of Pascal sizeof operator on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  if (Ident != 0)
  {
    //Not supported
  }

  if (ExprList != 0)
  {
    write(pOutFile, "(");
    ExprList->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (LabelId != 0)
  {
    write(pOutFile, "GO TO ");
    LabelId->writeFortran(pOutFile, nMode);
  }

  if (Inherited)
  {
    ::printf("ERROR: Translation of Pascal inherited keyword on line %d in file %s into "
             "Fortran not supported\n", lineNumber(),
                                        fileName());

    ::AdtExit(-1);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSimpleStatement::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  bool bAddAssign = false;

  writeExpanded(pOutFile, comment());

  if (Designator != 0)
  {
    Designator->writeDelphi(pOutFile, nMode);
    bAddAssign = true;
  }

  if (CastExpression != 0)
  {
    CastExpression->writeDelphi(pOutFile, nMode);
    bAddAssign = true;
  }

  if (Expression != 0)
  {
    const char* pOperator = 0;

    switch(OpType)
    {
      default:
      case AdtOpType_ASSIGN:
      {
        pOperator = ":=";
        break;
      }

      case AdtOpType_PLUS_EQUALS:
      {
        pOperator = "+=";
        break;
      }

      case AdtOpType_MINUS_EQUALS:
      {
        pOperator = "-=";
        break;
      }

      case AdtOpType_TIMES_EQUALS:
      {
        pOperator = "*=";
        break;
      }

      case AdtOpType_DIV_EQUALS:
      {
        pOperator = "/=";
        break;
      }
    }

    write(pOutFile, pOperator);

    Expression->writeDelphi(pOutFile, nMode);
  }

  if (SizeofType != 0)
  {
    SizeofType->writeDelphi(pOutFile, nMode);
  }

  if (Ident != 0)
  {
    write(pOutFile, "inherited ");
    Ident->writeDelphi(pOutFile, nMode);
  }

  if (ExprList != 0)
  {
    write(pOutFile, "(");
    ExprList->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  if (LabelId != 0)
  {
    write(pOutFile, "goto ");
    LabelId->writeDelphi(pOutFile, nMode);
  }

  if (Inherited)
  {
    if (bAddAssign)
    {
      write(pOutFile, ":=");
    }

    write(pOutFile, "inherited");
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiSimpleStatement::isProcedureCall() const
{
  bool bIsProcedureCall = false;

  if ((Designator != 0) &&
      (Expression == 0) &&
      (SizeofType == 0) &&
      (Ident      == 0) &&
      (ExprList   == 0) &&
      (LabelId    == 0))
  {
    bIsProcedureCall = Designator->isProcedureCall();
  }

  return (bIsProcedureCall);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSimpleStatement, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiSizeofType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiSizeofType::AdtDelphiSizeofType(AdtParser* pOrdIdentObj,
                                         AdtParser* pRealTypeObj,
                                         AdtParser* pVariantTypeObj,
                                         AdtParser* pDesignatorObj)
 : AdtDelphiBase()
{
  initObject(OrdIdent,    pOrdIdentObj,     AdtDelphiOrdIdent,    true);
  initObject(RealType,    pRealTypeObj,     AdtDelphiRealType,    true);
  initObject(VariantType, pVariantTypeObj,  AdtDelphiVariantType, true);
  initObject(Designator,  pDesignatorObj,   AdtDelphiDesignator,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiSizeofType::AdtDelphiSizeofType(const AdtDelphiSizeofType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(OrdIdent,    rCopy, AdtDelphiOrdIdent);
  copyObject(RealType,    rCopy, AdtDelphiRealType);
  copyObject(VariantType, rCopy, AdtDelphiVariantType);
  copyObject(Designator,  rCopy, AdtDelphiDesignator);
}

//  ----------------------------------------------------------------------------

AdtDelphiSizeofType::~AdtDelphiSizeofType()
{
  UtlReleaseReference(OrdIdent);
  UtlReleaseReference(RealType);
  UtlReleaseReference(VariantType);
  UtlReleaseReference(Designator);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiSizeofType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "sizeof(");

  if (OrdIdent != 0)
  {
    OrdIdent->writeDelphi(pOutFile, nMode);
  }

  if (RealType != 0)
  {
    RealType->writeDelphi(pOutFile, nMode);
  }

  if (VariantType != 0)
  {
    VariantType->writeDelphi(pOutFile, nMode);
  }

  if (Designator != 0)
  {
    Designator->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ")");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiSizeofType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCompoundStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCompoundStmt::AdtDelphiCompoundStmt(AdtParser* pStmtListObj)
 : AdtDelphiBase()
{
  initObject(StmtList, pStmtListObj, AdtDelphiStmtList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiCompoundStmt::AdtDelphiCompoundStmt(const AdtDelphiCompoundStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(StmtList, rCopy, AdtDelphiStmtList);
}

//  ----------------------------------------------------------------------------

AdtDelphiCompoundStmt::~AdtDelphiCompoundStmt()
{
  UtlReleaseReference(StmtList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCompoundStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (StmtList != 0)
  {
    pOutFile.incrementIndent();
    pOutFile.homeline();

    StmtList->writeFortran(pOutFile, nMode);

    pOutFile.decrementIndent();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCompoundStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  write(pOutFile, "begin");

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (StmtList != 0)
  {
    StmtList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCompoundStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiIfStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiIfStmt::AdtDelphiIfStmt(AdtParser* pExpressionObj,
                                 AdtParser* pThenStatementObj,
                                 AdtParser* pElseStatementObj)
 : AdtDelphiBase()
{
  initObject(Expression,    pExpressionObj,    AdtDelphiExpression, true);
  initObject(ThenStatement, pThenStatementObj, AdtDelphiStatement,  true);
  initObject(ElseStatement, pElseStatementObj, AdtDelphiStatement,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiIfStmt::AdtDelphiIfStmt(const AdtDelphiIfStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Expression,    rCopy, AdtDelphiExpression);
  copyObject(ThenStatement, rCopy, AdtDelphiStatement);
  copyObject(ElseStatement, rCopy, AdtDelphiStatement);
}

//  ----------------------------------------------------------------------------

AdtDelphiIfStmt::~AdtDelphiIfStmt()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(ThenStatement);
  UtlReleaseReference(ElseStatement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiIfStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  pOutFile.newline();

  if (Expression != 0)
  {
    write(pOutFile, "IF (");

    Expression->writeFortran(pOutFile, nMode);
  }

  if (ThenStatement != 0)
  {
    bool bIndent = !ThenStatement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, ") THEN ");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    ThenStatement->writeFortran(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }

    if (ElseStatement != 0)
    {
      pOutFile.newline();
    }
  }

  if (ElseStatement != 0)
  {
    bool bIndent = !ElseStatement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, "ELSE ");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    ElseStatement->writeFortran(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.newline();
  write(pOutFile, "END IF");
  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiIfStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.newline();

  if (Expression != 0)
  {
    write(pOutFile, "if ");

    Expression->writeDelphi(pOutFile, nMode);
  }

  if (ThenStatement != 0)
  {
    bool bIndent = !ThenStatement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, " then ");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    ThenStatement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }

    if (ElseStatement != 0)
    {
      pOutFile.newline();
    }
  }

  if (ElseStatement != 0)
  {
    bool bIndent = !ElseStatement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, "else ");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    ElseStatement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiIfStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCaseStmt::AdtDelphiCaseStmt(AdtParser* pExpressionObj,
                                     AdtParser* pCaseSelectorListObj,
                                     AdtParser* pStmtListObj)
 : AdtDelphiBase()
{
  initObject(Expression,        pExpressionObj,       AdtDelphiExpression,        true);
  initObject(CaseSelectorList,  pCaseSelectorListObj, AdtDelphiCaseSelectorList,  true);
  initObject(StmtList,          pStmtListObj,         AdtDelphiStmtList,          true);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseStmt::AdtDelphiCaseStmt(const AdtDelphiCaseStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Expression,       rCopy, AdtDelphiExpression);
  copyObject(CaseSelectorList, rCopy, AdtDelphiCaseSelectorList);
  copyObject(StmtList,         rCopy, AdtDelphiStmtList);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseStmt::~AdtDelphiCaseStmt()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(CaseSelectorList);
  UtlReleaseReference(StmtList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CASE not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.newline();

  if (Expression != 0)
  {
    write(pOutFile, "case ");

    Expression->writeDelphi(pOutFile, nMode);

    write(pOutFile, "of");

    pOutFile.incrementIndent();
    pOutFile.newline();
  }

  if (CaseSelectorList != 0)
  {
    CaseSelectorList->writeDelphi(pOutFile, nMode);
  }

  if (StmtList != 0)
  {
    pOutFile.decrementIndent();
    pOutFile.newline();

    write(pOutFile, "else ");

    pOutFile.incrementIndent();
    pOutFile.newline();

    StmtList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCaseStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseSelectorList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCaseSelectorList::AdtDelphiCaseSelectorList(AdtParser* pCaseSelectorObj)
 : AdtDelphiBase()
{
  add(pCaseSelectorObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseSelectorList::AdtDelphiCaseSelectorList(const AdtDelphiCaseSelectorList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiCaseSelectorList::~AdtDelphiCaseSelectorList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCaseSelectorList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseSelector method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCaseSelector::AdtDelphiCaseSelector(AdtParser* pCaseLabelListObj,
                                             AdtParser* pStatementObj)
 : AdtDelphiBase()
{
  initObject(CaseLabelList, pCaseLabelListObj,  AdtDelphiCaseLabelList, true);
  initObject(Statement,     pStatementObj,      AdtDelphiStatement,     true);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseSelector::AdtDelphiCaseSelector(const AdtDelphiCaseSelector& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(CaseLabelList, rCopy, AdtDelphiCaseLabelList);
  copyObject(Statement,     rCopy, AdtDelphiStatement);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseSelector::~AdtDelphiCaseSelector()
{
  UtlReleaseReference(CaseLabelList);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseSelector::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CASE not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseSelector::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (CaseLabelList != 0)
  {
    CaseLabelList->writeDelphi(pOutFile, nMode);

    write(pOutFile, ":");

    pOutFile.incrementIndent();
    pOutFile.newline();
  }

  if (Statement != 0)
  {
    Statement->writeDelphi(pOutFile, nMode);

    pOutFile.decrementIndent();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCaseSelector, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseLabelList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCaseLabelList::AdtDelphiCaseLabelList(AdtParser* pCaseLabelObj)
 : AdtDelphiBase()
{
  add(pCaseLabelObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseLabelList::AdtDelphiCaseLabelList(const AdtDelphiCaseLabelList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiCaseLabelList::~AdtDelphiCaseLabelList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCaseLabelList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseLabel method implementations
//  ----------------------------------------------------------------------------
AdtDelphiCaseLabel::AdtDelphiCaseLabel(AdtParser* pConstExprObj,
                                       AdtParser* pToConstExprObj)
 : AdtDelphiBase()
{
  initObject(ConstExpr,   pConstExprObj,    AdtDelphiConstExpr, true);
  initObject(ToConstExpr, pToConstExprObj,  AdtDelphiConstExpr, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseLabel::AdtDelphiCaseLabel(const AdtDelphiCaseLabel& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ConstExpr,   rCopy, AdtDelphiConstExpr);
  copyObject(ToConstExpr, rCopy, AdtDelphiConstExpr);
}

//  ----------------------------------------------------------------------------

AdtDelphiCaseLabel::~AdtDelphiCaseLabel()
{
  UtlReleaseReference(ConstExpr);
  UtlReleaseReference(ToConstExpr);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseLabel::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CASE not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiCaseLabel::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ConstExpr != 0)
  {
    ConstExpr->writeDelphi(pOutFile, nMode);
  }

  if (ToConstExpr != 0)
  {
    write(pOutFile, "..");
    ToConstExpr->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiCaseLabel, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiRepeatStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiRepeatStmt::AdtDelphiRepeatStmt(AdtParser* pStatementObj,
                                         AdtParser* pExpressionObj,
                                         AdtParser* pStmtListObj)
 : AdtDelphiBase()
{
  if ((pStmtListObj != 0) && (pStatementObj == 0))
  {
    AdtParser*  pCompoundStmtObj = new AdtDelphiCompoundStmt(pStmtListObj);
    AdtParser*  pNewStatementObj = new AdtDelphiStatement(0,
                                                          0,
                                                          0,
                                                          pCompoundStmtObj,
                                                          0,
                                                          0,
                                                          0,
                                                          0,
                                                          0,
                                                          0,
                                                          0);

    initObject(Statement, pNewStatementObj, AdtDelphiStatement, true);

    UtlReleaseReference(pCompoundStmtObj);
    UtlReleaseReference(pNewStatementObj);
  }
  else
  {
    initObject(Statement, pStatementObj, AdtDelphiStatement, true);
  }

  initObject(Expression, pExpressionObj, AdtDelphiExpression, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiRepeatStmt::AdtDelphiRepeatStmt(const AdtDelphiRepeatStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Statement,  rCopy, AdtDelphiStatement);
  copyObject(Expression, rCopy, AdtDelphiExpression);
}

//  ----------------------------------------------------------------------------

AdtDelphiRepeatStmt::~AdtDelphiRepeatStmt()
{
  UtlReleaseReference(Statement);
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRepeatStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: REPEAT not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiRepeatStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    pOutFile.newline();
    write(pOutFile, "repeat ");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }

    pOutFile.newline();
  }

  if (Expression != 0)
  {
    write(pOutFile, " until ");
    Expression->writeDelphi(pOutFile, nMode);

    pOutFile.delayedNewlines(1);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiRepeatStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiWhileStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiWhileStmt::AdtDelphiWhileStmt(AdtParser* pExpressionObj,
                                       AdtParser* pStatementObj)
 : AdtDelphiBase()
{
  initObject(Expression,  pExpressionObj, AdtDelphiExpression,  true);
  initObject(Statement,   pStatementObj,  AdtDelphiStatement,   true);
}

//  ----------------------------------------------------------------------------

AdtDelphiWhileStmt::AdtDelphiWhileStmt(const AdtDelphiWhileStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Expression, rCopy, AdtDelphiExpression);
  copyObject(Statement,  rCopy, AdtDelphiStatement);
}

//  ----------------------------------------------------------------------------

AdtDelphiWhileStmt::~AdtDelphiWhileStmt()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiWhileStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  pOutFile.newline();
  write(pOutFile, "DO WHILE ");

  if (Expression != 0)
  {
    write(pOutFile, "(");
    Expression->writeFortran(pOutFile, nMode);
    write(pOutFile, ")");
  }

  pOutFile.newline();

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeFortran(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.newline();
  write(pOutFile, "END DO");
  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiWhileStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.newline();
  write(pOutFile, "while ");

  if (Expression != 0)
  {
    Expression->writeDelphi(pOutFile, nMode);
  }

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, " do");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiWhileStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiForStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiForStmt::AdtDelphiForStmt(AdtParser* pUnitIdObj,
                                   AdtParser* pIdentObj,
                                   AdtParser* pFromExpressionObj,
                                   AdtParser* pToExpressionObj,
                                   AdtParser* pStatementObj,
                                   bool bDownTo)
 : AdtDelphiBase()
{
  initObject(UnitId,          pUnitIdObj,         AdtDelphiUnitId,      true);
  initObject(Ident,           pIdentObj,          AdtDelphiIdent,       true);
  initObject(FromExpression,  pFromExpressionObj, AdtDelphiExpression,  true);
  initObject(ToExpression,    pToExpressionObj,   AdtDelphiExpression,  true);
  initObject(Statement,       pStatementObj,      AdtDelphiStatement,   true);

  DownTo = bDownTo;
}

//  ----------------------------------------------------------------------------

AdtDelphiForStmt::AdtDelphiForStmt(const AdtDelphiForStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(UnitId,         rCopy, AdtDelphiUnitId);
  copyObject(Ident,          rCopy, AdtDelphiIdent);
  copyObject(FromExpression, rCopy, AdtDelphiExpression);
  copyObject(ToExpression,   rCopy, AdtDelphiExpression);
  copyObject(Statement,      rCopy, AdtDelphiStatement);

  DownTo = rCopy.DownTo;
}

//  ----------------------------------------------------------------------------

AdtDelphiForStmt::~AdtDelphiForStmt()
{
  UtlReleaseReference(UnitId);
  UtlReleaseReference(Ident);
  UtlReleaseReference(FromExpression);
  UtlReleaseReference(ToExpression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiForStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  pOutFile.newline();
  write(pOutFile, "DO ");

  if (UnitId != 0)
  {
    UnitId->writeFortran(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (Ident != 0)
  {
    Ident->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, " = ");

  if (FromExpression != 0)
  {
    FromExpression->writeFortran(pOutFile, nMode);
  }

  write(pOutFile, ",");

  if (ToExpression != 0)
  {
    ToExpression->writeFortran(pOutFile, nMode);
  }

  if (DownTo)
  {
    write(pOutFile, ",-1");
  }

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeFortran(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }

    pOutFile.newline();
    write(pOutFile, "END DO");
  }

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiForStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.newline();
  write(pOutFile, "for ");

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ":=");

  if (FromExpression != 0)
  {
    FromExpression->writeDelphi(pOutFile, nMode);
  }

  if (DownTo)
  {
    write(pOutFile, " downto ");
  }
  else
  {
    write(pOutFile, " to ");
  }

  if (ToExpression != 0)
  {
    ToExpression->writeDelphi(pOutFile, nMode);
  }

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    write(pOutFile, " do");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiForStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiWithStmt method implementations
//  ----------------------------------------------------------------------------
AdtDelphiWithStmt::AdtDelphiWithStmt(AdtParser* pDesignatorObj,
                                     AdtParser* pStatementObj)
 : AdtDelphiBase()
{
  initObject(Designator, pDesignatorObj, AdtDelphiDesignator, true);
  initObject(Statement,  pStatementObj,  AdtDelphiStatement,  true);
}

//  ----------------------------------------------------------------------------

AdtDelphiWithStmt::AdtDelphiWithStmt(const AdtDelphiWithStmt& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(Designator, rCopy, AdtDelphiDesignator);
  copyObject(Statement,  rCopy, AdtDelphiStatement);
}

//  ----------------------------------------------------------------------------

AdtDelphiWithStmt::~AdtDelphiWithStmt()
{
  UtlReleaseReference(Designator);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiWithStmt::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: WITH not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiWithStmt::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.newline();
  write(pOutFile, "with ");

  if (Designator != 0)
  {
    Designator->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, " do ");

  if (Statement != 0)
  {
    bool bIndent = !Statement->hasType("AdtDelphiCompoundStmt");

    if (bIndent)
    {
      pOutFile.incrementIndent();
    }

    pOutFile.newline();

    Statement->writeDelphi(pOutFile, nMode);

    if (bIndent)
    {
      pOutFile.decrementIndent();
    }
  }

  pOutFile.delayedNewlines(1);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiWithStmt, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDeclSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProcedureDeclSection::AdtDelphiProcedureDeclSection(AdtParser* pProcedureDeclListObj)
 : AdtDelphiBase()
{
  initObject(ProcedureDeclList, pProcedureDeclListObj, AdtDelphiProcedureDeclList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDeclSection::AdtDelphiProcedureDeclSection(const AdtDelphiProcedureDeclSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ProcedureDeclList, rCopy, AdtDelphiProcedureDeclList);
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDeclSection::~AdtDelphiProcedureDeclSection()
{
  UtlReleaseReference(ProcedureDeclList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureDeclSection::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (ProcedureDeclList != 0)
  {
    ProcedureDeclList->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureDeclSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ProcedureDeclList != 0)
  {
    ProcedureDeclList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProcedureDeclSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDeclList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProcedureDeclList::AdtDelphiProcedureDeclList(AdtParser* pProcedureDeclObj)
 : AdtDelphiBase()
{
  add(pProcedureDeclObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDeclList::AdtDelphiProcedureDeclList(const AdtDelphiProcedureDeclList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDeclList::~AdtDelphiProcedureDeclList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProcedureDeclList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDecl method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiProcedureDecl::replaceClassNameWith(AdtParser* pObj,
                                                  const char* pClassName,
                                                  const char* pNewCombinedName)
{
  if (pObj != 0)
  {
    AdtParser* pIdent = pObj->findDescendant("ClassIdent");

    pObj->name(pNewCombinedName);

    if (pIdent != 0)
    {
      pIdent->name(pClassName);
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDecl::AdtDelphiProcedureDecl(AdtParser* pProcedureHeadingObj,
                                               AdtParser* pFunctionHeadingObj,
                                               AdtParser* pConstructorHeadingObj,
                                               AdtParser* pDestructorHeadingObj,
                                               AdtParser* pDirectiveListObj,
                                               AdtParser* pBlockObj)
 : AdtDelphiBase(),
   LocalVariableMap(),
   ArgumentVariableMap()
{
  initObject(ProcedureHeading,    pProcedureHeadingObj,   AdtDelphiProcedureHeading,    true);
  initObject(FunctionHeading,     pFunctionHeadingObj,    AdtDelphiFunctionHeading,     true);
  initObject(ConstructorHeading,  pConstructorHeadingObj, AdtDelphiConstructorHeading,  true);
  initObject(DestructorHeading,   pDestructorHeadingObj,  AdtDelphiDestructorHeading,   true);
  initObject(DirectiveList,       pDirectiveListObj,      AdtDelphiDirectiveList,       true);
  initObject(Block,               pBlockObj,              AdtDelphiBlock,               true);

  if (ProcedureHeading != 0)
  {
    name(ProcedureHeading->name());
  }
  else if (FunctionHeading != 0)
  {
    name(FunctionHeading->name());
  }
  else if (ConstructorHeading != 0)
  {
    name(ConstructorHeading->name());
  }
  else if (DestructorHeading != 0)
  {
    name(DestructorHeading->name());
  }

  enumerateDescendantMap(ArgumentVariableMap, "ProcedureHeading,FormalParameters,FormalParamList;"
                                              "FunctionHeading,FormalParameters,FormalParamList;"
                                              "ConstructorHeading,FormalParameters,FormalParamList;"
                                              "DestructorHeading,FormalParameters,FormalParamList");

  enumerateDescendantMap(LocalVariableMap, "Block,DeclSection,VarSection,VarDeclList");
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDecl::AdtDelphiProcedureDecl(const AdtDelphiProcedureDecl& rCopy)
 : AdtDelphiBase(rCopy),
   LocalVariableMap(),
   ArgumentVariableMap()
{
  copyObject(ProcedureHeading,   rCopy, AdtDelphiProcedureHeading);
  copyObject(FunctionHeading,    rCopy, AdtDelphiFunctionHeading);
  copyObject(ConstructorHeading, rCopy, AdtDelphiConstructorHeading);
  copyObject(DestructorHeading,  rCopy, AdtDelphiDestructorHeading);
  copyObject(DirectiveList,      rCopy, AdtDelphiDirectiveList);
  copyObject(Block,              rCopy, AdtDelphiBlock);

  enumerateDescendantMap(ArgumentVariableMap, "ProcedureHeading,FormalParameters,FormalParamList;"
                                              "FunctionHeading,FormalParameters,FormalParamList;"
                                              "ConstructorHeading,FormalParameters,FormalParamList;"
                                              "DestructorHeading,FormalParameters,FormalParamList");

  enumerateDescendantMap(LocalVariableMap, "Block,DeclSection,VarSection,VarDeclList");
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureDecl::~AdtDelphiProcedureDecl()
{
  UtlReleaseReference(ProcedureHeading);
  UtlReleaseReference(FunctionHeading);
  UtlReleaseReference(ConstructorHeading);
  UtlReleaseReference(DestructorHeading);
  UtlReleaseReference(DirectiveList);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

void AdtDelphiProcedureDecl::fixReturnVariable()
{
  //This function needs to search and replace all instances of "RESULT" with
  //the classname concatenated with the function name with doulbe underscore
  //seperating the two.
  if ((FunctionHeading != 0) && (Block != 0))
  {
    AdtParser*  pClassIdent     = FunctionHeading->findDescendant("ClassIdent");
    AdtParser*  pFunctionIdent  = FunctionHeading->findDescendant("FunctionIdent");

    if (pFunctionIdent != 0)
    {
      AdtParserPtrListIter  Iter;
      AdtParserPtrList      ObjList;
      string                sReturnName(pFunctionIdent->name());

      if (pClassIdent != 0)
      {
        sReturnName = pClassIdent->name() + string("__") + sReturnName;
      }

      Block->findObjects(ObjList, "AdtDelphiIdent", pFunctionIdent->name());
      Block->findObjects(ObjList, "AdtDelphiIdent", "RESULT");

      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        if (pObj != 0)
        {
          pObj->name(sReturnName);
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtDelphiProcedureDecl::replaceClassNameWith(const char* pClassName)
{
  bool bClassNameReplaced = false;

  if (pClassName != 0)
  {
    const char* pName   = name();
    char*       pPeriod = (char*)::strrchr(pName, '.');

    if (pPeriod != 0)
    {
      string  sNewName;
      char*   pNextPeriod;

      *pPeriod    = 0;
      pNextPeriod = (char*)::strrchr(pName, '.');
      *pPeriod    = '.';

      if (pNextPeriod != 0)
      {
        *pNextPeriod = 0;
        sNewName    += pName;
        *pNextPeriod = '.';
      }

      sNewName += pClassName;
      sNewName += pPeriod;

      if (ProcedureHeading != 0)
      {
        replaceClassNameWith(ProcedureHeading, pClassName, sNewName);
      }
      else if (FunctionHeading != 0)
      {
        replaceClassNameWith(FunctionHeading, pClassName, sNewName);
      }
      else if (ConstructorHeading != 0)
      {
        replaceClassNameWith(ConstructorHeading, pClassName, sNewName);
      }
      else if (DestructorHeading != 0)
      {
        replaceClassNameWith(DestructorHeading, pClassName, sNewName);
      }

      name(sNewName);
    }
  }

  return (bClassNameReplaced);
}

//  ----------------------------------------------------------------------------


bool AdtDelphiProcedureDecl::enumerateLocalObjects(AdtParserPtrList& rExternalsList) const
{
  bool bEnumerated = false;

  if (Block != 0)
  {
    //Find all local variables
    AdtParserPtrListIter              ListIter;
    AdtParserPtrList                  LocalsList;
    const AdtDelphiFormalParameters*  FormalParameters  = 0;
    const AdtDelphiDeclSection*       LocalDeclarations = (AdtDelphiDeclSection*)Block->findObject("AdtDelphiDeclSection");

    if (ProcedureHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)ProcedureHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (FunctionHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)FunctionHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (ConstructorHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)ConstructorHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (DestructorHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)DestructorHeading->findObject("AdtDelphiFormalParameters");
    }

    if (FormalParameters != 0)
    {
      FormalParameters->findObjects(LocalsList, "AdtDelphiIdent");
    }

    if (LocalDeclarations != 0)
    {
      LocalDeclarations->findObjects(LocalsList, "AdtDelphiIdent");
    }

    for (ListIter = LocalsList.begin() ; ListIter != LocalsList.end() ; ++ListIter)
    {
      rExternalsList.push_back(*ListIter);
    }

    LocalsList.clear();
  }

  return (bEnumerated);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiProcedureDecl::enumerateExternals(AdtStringList& rExternalsList) const
{
  bool bEnumerated = false;

  if (Block != 0)
  {
    //Find all local variables
    AdtParserPtrListIter              ListIter;
    AdtParserPtrList                  RefList;
    AdtParserPtrList                  LocalsList;
    AdtParserPtrByStringMap           LocalsMap;
    AdtStringByStringMap              ArraySizeMap;
    AdtStringByStringMapIter          MapIter;
    const AdtDelphiFormalParameters*  FormalParameters  = 0;
    const AdtDelphiDeclSection*       LocalDeclarations = (AdtDelphiDeclSection*)Block->findObject("AdtDelphiDeclSection");
    const AdtDelphiCompoundStmt*      CompoundStmt      = (AdtDelphiCompoundStmt*)Block->findObject("AdtDelphiCompoundStmt");

    if (ProcedureHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)ProcedureHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (FunctionHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)FunctionHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (ConstructorHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)ConstructorHeading->findObject("AdtDelphiFormalParameters");
    }
    else if (DestructorHeading != 0)
    {
      FormalParameters = (AdtDelphiFormalParameters*)DestructorHeading->findObject("AdtDelphiFormalParameters");
    }

    if (FormalParameters != 0)
    {
      FormalParameters->findObjects(LocalsList, "AdtDelphiIdent");
    }

    if (LocalDeclarations != 0)
    {
      LocalDeclarations->findObjects(LocalsList, "AdtDelphiIdent");
    }

    //Add it to a map for quick matching
    for (ListIter = LocalsList.begin() ; ListIter != LocalsList.end() ; ++ListIter)
    {
      AdtDelphiIdent* pIdentObj = (AdtDelphiIdent*)((*ListIter).object());

      LocalsMap.insert(AdtParserPtrByStringMap::value_type(pIdentObj->name(), *ListIter));

      // Need to add all array dimension objects as external references
      pIdentObj->enumerateArraySizes(ArraySizeMap);
    }

    //search block for all Idents. These are possible unresolved externals.
    if (CompoundStmt != 0)
    {
      CompoundStmt->findObjects(RefList, "AdtDelphiIdent");
    }

    //Match Idents with locals. Any that don't match must be externals.
    for (ListIter = RefList.begin() ; ListIter != RefList.end() ; ++ListIter)
    {
      AdtDelphiIdent*             pIdentObj = (AdtDelphiIdent*)((*ListIter).object());
      AdtParserPtrByStringMapIter MapIter   = LocalsMap.find(pIdentObj->name());

      if (MapIter == LocalsMap.end())
      {
        rExternalsList.push_back(pIdentObj->name());
        bEnumerated = true;
      }
    }

    for (MapIter = ArraySizeMap.begin() ; MapIter != ArraySizeMap.end(); ++MapIter)
    {
      rExternalsList.push_back(MapIter->first);
    }

    ArraySizeMap.clear();
    RefList.clear();
    LocalsList.clear();
    LocalsMap.clear();
  }

  return (bEnumerated);
}

//  ----------------------------------------------------------------------------

const char* AdtDelphiProcedureDecl::className() const
{
  const char* pClassName  = 0;
  AdtParser*  pSearchObj  = 0;

  if (ProcedureHeading != 0)
  {
    pSearchObj = ProcedureHeading;
  }
  else if (FunctionHeading != 0)
  {
    pSearchObj = FunctionHeading;
  }
  else if (ConstructorHeading != 0)
  {
    pSearchObj = ConstructorHeading;
  }
  else if (DestructorHeading != 0)
  {
    pSearchObj = DestructorHeading;
  }

  if (pSearchObj != 0)
  {
    AdtParser* pIdent = pSearchObj->findDescendant("ClassIdent");

    if (pIdent != 0)
    {
      pClassName = pIdent->name();
    }
  }

  return (pClassName);
}

//  ----------------------------------------------------------------------------

const AdtDelphiFormalParam* AdtDelphiProcedureDecl::findFormalParam(const char* pFormalParamName) const
{
  const AdtDelphiFormalParam* pFormalParam = 0;

  if (pFormalParamName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = ArgumentVariableMap.find(pFormalParamName);

    if (Iter != ArgumentVariableMap.end())
    {
      const AdtParser* pObj = (*Iter).second;

      if ((pObj != 0) && pObj->isType("AdtDelphiFormalParam"))
      {
        pFormalParam = (const AdtDelphiFormalParam*)pObj;
      }
    }
  }

  return (pFormalParam);
}

//  ----------------------------------------------------------------------------

const AdtDelphiVarDecl* AdtDelphiProcedureDecl::findVarDecl(const char* pVarName) const
{
  const AdtDelphiVarDecl* pVarDecl = 0;

  if (pVarName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = LocalVariableMap.find(pVarName);

    if (Iter != LocalVariableMap.end())
    {
      const AdtParser* pObj = (*Iter).second;

      if ((pObj != 0) && pObj->isType("AdtDelphiVarDecl"))
      {
        pVarDecl = (const AdtDelphiVarDecl*)pObj;
      }
    }
  }

  return (pVarDecl);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureDecl::writeFortran(AdtFile& pOutFile, int nMode) const
{
  AdtDelphiGoal*  pDelphiRootObject = delphiRootObject();
  const char*     pClassStart       = name();
  const char*     pClassEnd         = ::strchr(pClassStart, '.');
  size_t          nLength           = pClassEnd != 0 ? pClassEnd - pClassStart : 0;
  string          ClassName(pClassStart, 0, nLength);

  writePragmas(pOutFile);

  if (ProcedureHeading != 0)
  {
    ProcedureHeading->writeFortran(pOutFile, nMode);
  }
  else if (FunctionHeading != 0)
  {
    FunctionHeading->writeFortran(pOutFile, nMode);
  }
  else if ((ConstructorHeading != 0) || (DestructorHeading != 0))
  {
    //No supported.
  }

  pOutFile.newline();
  write(pOutFile, "USE Common");
  pOutFile.newline();
  pOutFile.newline();

  if (pDelphiRootObject != 0)
  {
    pDelphiRootObject->pushClassContext(ClassName);
  }

  if (Block != 0)
  {
    Block->writeFortran(pOutFile, nMode);
  }

  if (pDelphiRootObject != 0)
  {
    pDelphiRootObject->popClassContext();
  }

  pOutFile.newline();
  write(pOutFile, "END");
  pOutFile.newline();
  pOutFile.newline();
  write(pOutFile, "! ----------------------------------------------------------------------------");
  pOutFile.newline();
  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureDecl::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  AdtDelphiGoal*  pRoot        = delphiRootObject();
  bool            bIsBlackBox  = ((pRoot != 0) && pRoot->isBlackBox(name()));

  // Only write if it isn't a black box routine. Black boxes aren't meant to be
  // seen by tapenade and should be ignored.
  if (!bIsBlackBox)
  {
    writeExpanded(pOutFile, comment());

    if (ProcedureHeading != 0)
    {
      ProcedureHeading->writeDelphi(pOutFile, nMode);
    }
    else if (FunctionHeading != 0)
    {
      FunctionHeading->writeDelphi(pOutFile, nMode);
    }
    else if (ConstructorHeading != 0)
    {
      ConstructorHeading->writeDelphi(pOutFile, nMode);
    }
    else if (DestructorHeading != 0)
    {
      DestructorHeading->writeDelphi(pOutFile, nMode);
    }

    if ((DirectiveList != 0) && (DirectiveList->listSize() > 0))
    {
      write(pOutFile, ";");
      DirectiveList->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, ";");

    pOutFile.newline();
    pOutFile.newline();

    if (Block != 0)
    {
      Block->writeDelphi(pOutFile, nMode);
    }

    write(pOutFile, ";");
    pOutFile.newline();
    write(pOutFile, "{ ---------------------------------------------------------------------------- }");
    pOutFile.newline();
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiProcedureDecl::hasType(const char* pType) const
{
  bool bHasType = false;

  if (ProcedureHeading != 0)
  {
    bHasType = ProcedureHeading->isType(pType);
  }
  else if (FunctionHeading != 0)
  {
    bHasType = FunctionHeading->isType(pType);
  }
  else if (ConstructorHeading != 0)
  {
    bHasType = ConstructorHeading->isType(pType);
  }
  else if (DestructorHeading != 0)
  {
    bHasType = DestructorHeading->isType(pType);
  }

  return (bHasType);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProcedureDecl, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFunctionHeading method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFunctionHeading::AdtDelphiFunctionHeading(AdtParser* pClassIdentObj,
                                                   AdtParser* pFunctionIdentObj,
                                                   AdtParser* pFormalParametersObj,
                                                   AdtParser* pSimpleTypeObj,
                                                   AdtParser* pTypeIdObj,
                                                   const char* pComment)
 : AdtDelphiBase()
{
  initObject(ClassIdent,        pClassIdentObj,       AdtDelphiIdent,             true);
  initObject(FunctionIdent,     pFunctionIdentObj,    AdtDelphiIdent,             true);
  initObject(FormalParameters,  pFormalParametersObj, AdtDelphiFormalParameters,  true);
  initObject(SimpleType,        pSimpleTypeObj,       AdtDelphiSimpleType,        true);
  initObject(TypeId,            pTypeIdObj,           AdtDelphiTypeId,            true);

  BlackBox = 0;

  if (ClassIdent != 0)
  {
    name(ClassIdent->name() + ".");
  }

  if (FunctionIdent != 0)
  {
    name(name() + FunctionIdent->name());
  }

  comment(pComment);

  if ((FormalParameters != 0) && ((SimpleType != 0) || (TypeId != 0)) && AdtBlackBoxCompiler::isBlackBox(pComment))
  {
    string      sName;
    const char* pTypeScope = AdtDelphiBase::typeScope();

    if (pTypeScope != 0)
    {
      sName = string(pTypeScope) + "." + name();
    }
    else
    {
      sName = name();
    }

    BlackBox = new AdtBlackBoxDefinition(sName, true, yyCpp_fileName(), yyCpp_lineNumber());

    if (BlackBox != 0)
    {
      AdtParserPtrList        ObjList;
      AdtParserPtrListIter    Iter;

      // Need to initialise black box definition based on argument list and return type
      FormalParameters->enumerateDescendantList(ObjList, "FormalParamList");

      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtDelphiFormalParam* pFormalParam = (AdtDelphiFormalParam*)Iter->object();

        if (pFormalParam != 0)
        {
          pFormalParam->addToBlackBox(*BlackBox, yyDelphi_fileName(), yyDelphi_lineNumber());
        }
      }

      if (SimpleType != 0)
      {
        BlackBox->addReturn(SimpleType->blackBoxArgType(), false);
      }
      else if (TypeId != 0)
      {
        bool                bIsArray  = false;
        AdtBlackBoxArgType  nType     = TypeId->blackBoxArgType(bIsArray);

        BlackBox->addReturn(nType, bIsArray);
      }

      AdtBlackBoxCompiler::parseComments(*BlackBox, pComment, fileName(), lineNumber());
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiFunctionHeading::AdtDelphiFunctionHeading(const AdtDelphiFunctionHeading& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ClassIdent,       rCopy, AdtDelphiIdent);
  copyObject(FunctionIdent,    rCopy, AdtDelphiIdent);
  copyObject(FormalParameters, rCopy, AdtDelphiFormalParameters);
  copyObject(SimpleType,       rCopy, AdtDelphiSimpleType);
  copyObject(TypeId,           rCopy, AdtDelphiTypeId);

  BlackBox = (rCopy.BlackBox != 0) ? new AdtBlackBoxDefinition(*rCopy.BlackBox) : 0;
}

//  ----------------------------------------------------------------------------

AdtDelphiFunctionHeading::~AdtDelphiFunctionHeading()
{
  if (BlackBox != 0)
  {
    delete BlackBox;
  }

  UtlReleaseReference(ClassIdent);
  UtlReleaseReference(FunctionIdent);
  UtlReleaseReference(FormalParameters);
  UtlReleaseReference(SimpleType);
  UtlReleaseReference(TypeId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFunctionHeading::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (SimpleType != 0)
  {
    SimpleType->writeFortran(pOutFile, nMode);
    write(pOutFile, " FUNCTION ");
  }
  else if (TypeId != 0)
  {
    TypeId->writeFortran(pOutFile, nMode);
    write(pOutFile, " FUNCTION ");
  }
  else
  {
    write(pOutFile, "SUBROUTINE ");
  }

  if (ClassIdent != 0)
  {
    ClassIdent->writeFortran(pOutFile, nMode);
    write(pOutFile, "__");
  }

  if (FunctionIdent != 0)
  {
    FunctionIdent->writeFortran(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeFortran(pOutFile, nMode);
  }

  if (ClassIdent != 0)
  {
    //Need to write class members as common blocks. Fix Me
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFunctionHeading::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "function ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeDelphi(pOutFile, nMode);
    write(pOutFile, '.');
  }

  if (FunctionIdent != 0)
  {
    FunctionIdent->writeDelphi(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeDelphi(pOutFile, nMode);
  }

  if (SimpleType != 0)
  {
    write(pOutFile, " : ");
    SimpleType->writeDelphi(pOutFile, nMode);
  }
  else if (TypeId != 0)
  {
    write(pOutFile, " : ");
    TypeId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFunctionHeading, AdtDelphiBase);



//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureHeading method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProcedureHeading::AdtDelphiProcedureHeading(AdtParser* pClassIdentObj,
                                                     AdtParser* pProcedureIdentObj,
                                                     AdtParser* pFormalParametersObj,
                                                     const char* pComment)
 : AdtDelphiBase()
{
  initObject(ClassIdent,        pClassIdentObj,       AdtDelphiIdent,             true);
  initObject(ProcedureIdent,    pProcedureIdentObj,   AdtDelphiIdent,             true);
  initObject(FormalParameters,  pFormalParametersObj, AdtDelphiFormalParameters,  true);

  BlackBox = 0;

  if (ClassIdent != 0)
  {
    name(ClassIdent->name() + ".");
  }

  if (ProcedureIdent != 0)
  {
    name(name() + ProcedureIdent->name());
  }

  comment(pComment);

  if ((FormalParameters != 0) && AdtBlackBoxCompiler::isBlackBox(pComment))
  {
    string      sName;
    const char* pTypeScope = AdtDelphiBase::typeScope();

    if (pTypeScope != 0)
    {
      sName = string(pTypeScope) + "." + name();
    }
    else
    {
      sName = name();
    }

    BlackBox = new AdtBlackBoxDefinition(sName, false, yyCpp_fileName(), yyCpp_lineNumber());

    if (BlackBox != 0)
    {
      AdtParserPtrList        ObjList;
      AdtParserPtrListIter    Iter;

      // Need to initialise black box definition based on argument list
      FormalParameters->enumerateDescendantList(ObjList, "FormalParameterList");

      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtDelphiFormalParam* pFormalParam = (AdtDelphiFormalParam*)Iter->object();

        if (pFormalParam != 0)
        {
          pFormalParam->addToBlackBox(*BlackBox, yyDelphi_fileName(), yyDelphi_lineNumber());
        }
      }

      AdtBlackBoxCompiler::parseComments(*BlackBox, pComment, fileName(), lineNumber());
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureHeading::AdtDelphiProcedureHeading(const AdtDelphiProcedureHeading& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ClassIdent,       rCopy, AdtDelphiIdent);
  copyObject(ProcedureIdent,   rCopy, AdtDelphiIdent);
  copyObject(FormalParameters, rCopy, AdtDelphiFormalParameters);

  BlackBox = (rCopy.BlackBox != 0) ? new AdtBlackBoxDefinition(*rCopy.BlackBox) : 0;
}

//  ----------------------------------------------------------------------------

AdtDelphiProcedureHeading::~AdtDelphiProcedureHeading()
{
  if (BlackBox != 0)
  {
    delete BlackBox;
  }

  UtlReleaseReference(ClassIdent);
  UtlReleaseReference(ProcedureIdent);
  UtlReleaseReference(FormalParameters);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureHeading::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  write(pOutFile, "SUBROUTINE ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeFortran(pOutFile, nMode);
    write(pOutFile, "__");
  }

  if (ProcedureIdent != 0)
  {
    ProcedureIdent->writeFortran(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProcedureHeading::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "procedure ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeDelphi(pOutFile, nMode);
    write(pOutFile, '.');
  }

  if (ProcedureIdent != 0)
  {
    ProcedureIdent->writeDelphi(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProcedureHeading, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParameters method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFormalParameters::AdtDelphiFormalParameters(AdtParser* pFormalParamListObj)
 : AdtDelphiBase()
{
  initObject(FormalParamList, pFormalParamListObj, AdtDelphiFormalParamList, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiFormalParameters::AdtDelphiFormalParameters(const AdtDelphiFormalParameters& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(FormalParamList, rCopy, AdtDelphiFormalParamList);
}

//  ----------------------------------------------------------------------------

AdtDelphiFormalParameters::~AdtDelphiFormalParameters()
{
  UtlReleaseReference(FormalParamList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParameters::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, '(');

  if (FormalParamList != 0)
  {
    FormalParamList->writeCPP(pOutFile, nMode);
  }

  write(pOutFile, ')');

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParameters::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  write(pOutFile, '(');

  if (FormalParamList != 0)
  {
    //Write all formal parameter names into a comma seperated list.
    FormalParamList->writeFortran(pOutFile, 0);
  }

  write(pOutFile, ')');

  pOutFile.newline();

  if (FormalParamList != 0)
  {
    //Write all formal parameter names into a fortran intent list (ie. whether the vars are IN OUT or INOUT).
    FormalParamList->writeFortran(pOutFile, 2);
    pOutFile.newline();

    //Write all formal parameter names and types into a fortran variable
    //declaration list.
    FormalParamList->writeFortran(pOutFile, 1);
  }

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParameters::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, '(');

  if (FormalParamList != 0)
  {
    FormalParamList->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, ')');

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFormalParameters, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParamList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFormalParamList::AdtDelphiFormalParamList(AdtParser* pFormalParamObj)
 : AdtDelphiBase()
{
  add(pFormalParamObj);
}

//  ----------------------------------------------------------------------------
AdtDelphiFormalParamList::AdtDelphiFormalParamList(const AdtDelphiFormalParamList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiFormalParamList::~AdtDelphiFormalParamList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParamList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  const char* pDelimiter = ", ";

  return (forAllWriteCPP(pOutFile, nMode, pDelimiter, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParamList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* pDelimiter = 0;
  bool        bNewLine   = false;

  writePragmas(pOutFile);

  switch (nMode)
  {
    case 0:
    {
      pDelimiter = ", ";
      break;
    }

    case 1:
    case 2:
    {
      pDelimiter = "";
      bNewLine   = true;
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (forAllWriteFortran(pOutFile, nMode, pDelimiter, bNewLine, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParamList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pDelimiter = 0;

  switch (nMode)
  {
    case 0:
    default:
    {
      pDelimiter = " ; ";
      break;
    }

    case 1:
    {
      pDelimiter = " ,";
      break;
    }
  }

  return (forAllWriteDelphi(pOutFile, nMode, pDelimiter, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFormalParamList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParam method implementations
//  ----------------------------------------------------------------------------
AdtDelphiFormalParam::AdtDelphiFormalParam(AdtType nType,
                                           AdtParser* pParameterObj)
 : AdtDelphiBase()
{
  Type = nType;

  initObject(Parameter, pParameterObj, AdtDelphiParameter, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiFormalParam::AdtDelphiFormalParam(const AdtDelphiFormalParam& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;

  copyObject(Parameter, rCopy, AdtDelphiParameter);
}

//  ----------------------------------------------------------------------------

AdtDelphiFormalParam::~AdtDelphiFormalParam()
{
  UtlReleaseReference(Parameter);
}

//  ----------------------------------------------------------------------------

void AdtDelphiFormalParam::addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                         const char* pFile,
                                         int nLine) const
{
  if (Parameter != 0)
  {
    Parameter->addToBlackBox(rBlackBox,
                             autoDirType(),
                             pFile,
                             nLine);
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiFormalParam::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (Parameter != 0)
  {
    Parameter->enumerateAddObj(rMap, pObj);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParam::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Parameter != 0)
  {
    if (nMode == 0)
    {
      switch (Type)
      {
        case AdtType_OUT:
        case AdtType_OUTO:
        case AdtType_VAR:
        {
          nMode = nMode | 2;
          break;
        }

        case AdtType_CONST:
        {
          nMode = nMode | 4;
          break;
        }

        default:
        case AdtType_EMPTY:
        {
          break;
        }
      }
    }

    Parameter->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParam::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if (Parameter != 0)
  {
    if (nMode == 2)
    {
      const char* pIntent = 0;

      switch (Type)
      {
        case AdtType_VAR:
        {
          pIntent = "INTENT (INOUT)";
          break;
        }

        case AdtType_EMPTY:
        case AdtType_CONST:
        {
          pIntent = "INTENT (IN)";
          break;
        }

        case AdtType_OUT:
        case AdtType_OUTO:
        {
          pIntent = "INTENT (OUT)";
          break;
        }

        default:
        {
          FAIL();
          break;
        }
      }

      if (pIntent != 0)
      {
        write(pOutFile, pIntent);
      }
    }

    Parameter->writeFortran(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiFormalParam::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (Parameter != 0)
  {
    if (nMode != 1)
    {
      const char* pType = 0;

      switch (Type)
      {
        case AdtType_VAR:
        {
          pType = "var";
          break;
        }

        case AdtType_CONST:
        {
          pType = "const";
          break;
        }

        case AdtType_OUT:
        {
          pType = "out";
          break;
        }

        case AdtType_OUTO:
        {
          pType = "outo";
          break;
        }

        default:
        case AdtType_EMPTY:
        {
          break;
        }
      }

      if (pType != 0)
      {
        write(pOutFile, pType);
        write(pOutFile, ' ');
      }
    }

    Parameter->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiFormalParam, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiParameter method implementations
//  ----------------------------------------------------------------------------
AdtDelphiParameter::AdtDelphiParameter(AdtParser* pIdentListObj,
                                       AdtParser* pSimpleTypeObj,
                                       AdtParser* pTypeIdObj,
                                       AdtParser* pConstExprObj,
                                       AdtParser* pIdentObj,
                                       bool bIsArray,
                                       bool bOfString,
                                       bool bOfFile)
 : AdtDelphiBase()
{
  initObject(IdentList,   pIdentListObj,  AdtDelphiIdentList,   true);
  initObject(SimpleType,  pSimpleTypeObj, AdtDelphiSimpleType,  true);
  initObject(TypeId,      pTypeIdObj,     AdtDelphiTypeId,      true);
  initObject(ConstExpr,   pConstExprObj,  AdtDelphiConstExpr,   true);
  initObject(Ident,       pIdentObj,      AdtDelphiIdent,       true);

  IsArray   = bIsArray;
  OfString  = bOfString;
  OfFile    = bOfFile;
}

//  ----------------------------------------------------------------------------

AdtDelphiParameter::AdtDelphiParameter(const AdtDelphiParameter& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList,  rCopy, AdtDelphiIdentList);
  copyObject(SimpleType, rCopy, AdtDelphiSimpleType);
  copyObject(TypeId,     rCopy, AdtDelphiTypeId);
  copyObject(ConstExpr,  rCopy, AdtDelphiConstExpr);
  copyObject(Ident,      rCopy, AdtDelphiIdent);

  IsArray   = rCopy.IsArray;
  OfString  = rCopy.OfString;
  OfFile    = rCopy.OfFile;
}

//  ----------------------------------------------------------------------------

AdtDelphiParameter::~AdtDelphiParameter()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(SimpleType);
  UtlReleaseReference(TypeId);
  UtlReleaseReference(ConstExpr);
  UtlReleaseReference(Ident);
}

//  ----------------------------------------------------------------------------

void AdtDelphiParameter::addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                       AdtAutoDir nDir,
                                       const char* pFile,
                                       int nLine) const
{
  bool                bIsArray    = false;
  AdtBlackBoxArgType  nMappedType = AdtBlackBox_undefined;

  if (TypeId != 0)
  {
    nMappedType = TypeId->blackBoxArgType(bIsArray);
  }
  else if (SimpleType != 0)
  {
    nMappedType = SimpleType->blackBoxArgType();
  }

  if (IdentList != 0)
  {
    AdtParserPtrListConstIter  Iter;

    for (Iter = IdentList->objList().begin() ; Iter != IdentList->objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      // Note that we can't tell the difference between OUT and INOUT parameters
      // without analysing the code. It is possible to do so but is it worth the
      // effort. Probably not so I just force it to an INOUT interpretation.
      rBlackBox.addArgument(nMappedType,
                            pObj->name(),
                            (nDir == AdtAutoDir_IN) || (nDir == AdtAutoDir_UNDEFINED),
                            false,
                            false,
                            nDir == AdtAutoDir_INOUT,
                            bIsArray);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiParameter::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (IdentList != 0)
  {
    IdentList->enumerateAddByObjList(rMap, pObj);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiParameter::writeFortran(AdtFile& pOutFile, int nMode, bool& bKeep) const
{
  bKeep = true;

  writePragmas(pOutFile);

  switch (nMode)
  {
    case 0:
    {
      if (IdentList != 0)
      {
        IdentList->writeFortran(pOutFile);
      }
      else if (Ident != 0)
      {
        Ident->writeFortran(pOutFile);
      }
      break;
    }

    case 1:
    {
      const char* sDimension  = 0;
      const char* sType       = 0;

      if (TypeId != 0)
      {
        //We do this to map MB arrays into equivalent fortran ones
        delphiRootObject()->mapTypesToFortran(TypeId->name(), sType, sDimension);
        bKeep = (sType != 0);
      }

      if (bKeep)
      {
        if (SimpleType != 0)
        {
          SimpleType->writeFortran(pOutFile);

          if (ConstExpr != 0)
          {
            ::printf("ERROR: Translation of Pascal parameter initialisation on line %d in file %s into "
                     "Fortran not supported\n", lineNumber(),
                                                fileName());

            ::AdtExit(-1);
          }
        }
        else if (TypeId != 0)
        {
          if (sType != 0)
          {
            write(pOutFile, sType);
          }
        }
        else if (OfString)
        {
          ::printf("ERROR: Translation of Pascal ARRAY OF STRING on line %d in file %s into "
                   "Fortran not supported\n", lineNumber(),
                                              fileName());

          ::AdtExit(-1);
        }
        else if (OfFile)
        {
          ::printf("ERROR: Translation of Pascal ARRAY OF FILE on line %d in file %s into "
                   "Fortran not supported\n", lineNumber(),
                                              fileName());

          ::AdtExit(-1);
        }

        if (IsArray)
        {
          ::printf("ERROR: Translation of Pascal ARRAY OF on line %d in file %s into "
                   "Fortran not supported\n", lineNumber(),
                                              fileName());

          ::AdtExit(-1);
        }

        write(pOutFile, ' ');

        if (IdentList != 0)
        {
          IdentList->writeArrayBounds(pOutFile, nMode, sDimension);
        }
        else if (Ident != 0)
        {
          Ident->writeFortran(pOutFile);
        }
      }
      break;
    }

    case 2:
    {
      write(pOutFile, ' ');

      if (IdentList != 0)
      {
        IdentList->writeFortran(pOutFile);
      }
      else if (Ident != 0)
      {
        Ident->writeFortran(pOutFile);
      }
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiParameter::writeCPP_Var(AdtFile& pOutFile, const AdtDelphiBase* pVar, int nMode) const
{
  if (pVar != 0)
  {
    bool bDeclaration = ((nMode & 1) == 0);

    if (bDeclaration)
    {
      if ((nMode & 4) == 4)
      {
        write(pOutFile, "const ");
      }

      if (SimpleType != 0)
      {
        SimpleType->writeCPP(pOutFile, nMode);
      }
      else if (TypeId != 0)
      {
        TypeId->writeCPP(pOutFile, nMode);
      }

      if (((nMode & 2) == 2) || (TypeId != 0))
      {
        write(pOutFile, "&");
      }

      write(pOutFile, " ");
    }

    pVar->writeCPP(pOutFile, nMode);

    if (bDeclaration)
    {
      if (ConstExpr != 0)
      {
        write(pOutFile, " = ");
        ConstExpr->writeCPP(pOutFile, nMode);
      }
    }

    if (IsArray)
    {
      ::printf("ERROR: Translation of Pascal ARRAY OF on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (OfString)
    {
      ::printf("ERROR: Translation of Pascal ARRAY OF STRING on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
    else if (OfFile)
    {
      ::printf("ERROR: Translation of Pascal ARRAY OF FILE on line %d in file %s into "
               "Fortran not supported\n", lineNumber(),
                                          fileName());

      ::AdtExit(-1);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiParameter::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    AdtParserPtrListConstIter Iter;
    const AdtParserPtrList&   rObjList = IdentList->objList();

    for (Iter = rObjList.begin() ; Iter != rObjList.end() ; ++Iter)
    {
      const AdtDelphiBase*  pObj = (const AdtDelphiBase*)(AdtParser*)*Iter;

      if (Iter != rObjList.begin())
      {
        write(pOutFile, ", ");
      }

      writeCPP_Var(pOutFile, pObj, nMode);
    }
  }
  else if (Ident != 0)
  {
    writeCPP_Var(pOutFile, Ident, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiParameter::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    IdentList->writeDelphi(pOutFile, nMode);
  }
  else if (Ident != 0)
  {
    Ident->writeDelphi(pOutFile, nMode);
  }

  if (nMode != 1)
  {
    write(pOutFile, " : ");

    if (IsArray)
    {
      write(pOutFile, "array of ");
    }

    if (SimpleType != 0)
    {
      SimpleType->writeDelphi(pOutFile, nMode);

      if (ConstExpr != 0)
      {
        write(pOutFile, " = ");
        ConstExpr->writeDelphi(pOutFile, nMode);
      }
    }
    else if (TypeId != 0)
    {
      TypeId->writeDelphi(pOutFile, nMode);
    }
    else if (OfString)
    {
      write(pOutFile, "string");
    }
    else if (OfFile)
    {
      write(pOutFile, "file");
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiParameter, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDirective method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDirective::AdtDelphiDirective(AdtType nType)
 : AdtDelphiBase()
{
  Type = nType;
}

//  ----------------------------------------------------------------------------

AdtDelphiDirective::AdtDelphiDirective(const AdtDelphiDirective& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtDelphiDirective::~AdtDelphiDirective()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDirective::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  const char* pType = 0;

  writeExpanded(pOutFile, comment());

  switch (Type)
  {
    case AdtType_CDECL:
    {
      pType = "cdecl";
      break;
    }

    case AdtType_REGISTER:
    {
      pType = "register";
      break;
    }

    case AdtType_DYNAMIC:
    {
      pType = "dynamic";
      break;
    }

    case AdtType_VIRTUAL:
    {
      pType = "virtual";
      break;
    }

    case AdtType_EXPORT:
    {
      pType = "export";
      break;
    }

    case AdtType_EXTERNAL:
    {
      pType = "external";
      break;
    }

    case AdtType_FAR:
    {
      pType = "far";
      break;
    }

    case AdtType_FORWARD:
    {
      pType = "forward";
      break;
    }

    case AdtType_MESSAGE:
    {
      pType = "message";
      break;
    }

    case AdtType_OVERRIDE:
    {
      pType = "override";
      break;
    }

    case AdtType_OVERLOAD:
    {
      pType = "overload";
      break;
    }

    case AdtType_PASCAL:
    {
      pType = "pascal";
      break;
    }

    case AdtType_REINTRODUCE:
    {
      pType = "reintroduce";
      break;
    }

    case AdtType_SAFECALL:
    {
      pType = "safecall";
      break;
    }

    case AdtType_STDCALL:
    {
      pType = "stdcall";
      break;
    }

    default:
    case AdtType_EMPTY:
    {
      break;
    }
  }

  write(pOutFile, pType);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDirective, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDirectiveList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDirectiveList::AdtDelphiDirectiveList(AdtParser* pDirectiveObj)
 : AdtDelphiBase()
{
  add(pDirectiveObj);
}

//  ----------------------------------------------------------------------------
AdtDelphiDirectiveList::AdtDelphiDirectiveList(const AdtDelphiDirectiveList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiDirectiveList::~AdtDelphiDirectiveList()
{

}

//  ----------------------------------------------------------------------------

bool AdtDelphiDirectiveList::hasDirective(AdtDelphiDirective::AdtType nType) const
{
  bool                      bHasType = false;
  const AdtParserPtrList&   rList    = objList();
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    const AdtParser*  pObj = *Iter;

    if (pObj->isType("AdtDelphiDirective"))
    {
      const AdtDelphiDirective* pDirective = (const AdtDelphiDirective*)pObj;

      if (pDirective->directive() == nType)
      {
        bHasType = true;
        break;
      }
    }
  }

  return (bHasType);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDirectiveList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiObjectType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiObjectType::AdtDelphiObjectType(AdtParser* pUnitIdObj,
                                         AdtParser* pIdentObj,
                                         AdtParser* pObjFieldListObj,
                                         AdtParser* pMethodListObj)
 : AdtDelphiBase()
{
  initObject(UnitId,        pUnitIdObj,       AdtDelphiUnitId,        true);
  initObject(Ident,         pIdentObj,        AdtDelphiIdent,         true);
  initObject(ObjFieldList,  pObjFieldListObj, AdtDelphiObjFieldList,  true);
  initObject(MethodList,    pMethodListObj,   AdtDelphiMethodList,    true);
}

//  ----------------------------------------------------------------------------

AdtDelphiObjectType::AdtDelphiObjectType(const AdtDelphiObjectType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(UnitId,       rCopy, AdtDelphiUnitId);
  copyObject(Ident,        rCopy, AdtDelphiIdent);
  copyObject(ObjFieldList, rCopy, AdtDelphiObjFieldList);
  copyObject(MethodList,   rCopy, AdtDelphiMethodList);
}

//  ----------------------------------------------------------------------------

AdtDelphiObjectType::~AdtDelphiObjectType()
{
  UtlReleaseReference(UnitId);
  UtlReleaseReference(Ident);
  UtlReleaseReference(ObjFieldList);
  UtlReleaseReference(MethodList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiObjectType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: OBJECT not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiObjectType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "object ");

  if (UnitId != 0)
  {
    write(pOutFile, "(");
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (Ident != 0)
  {
    if (UnitId == 0)
    {
      write(pOutFile, "(");
    }

    Ident->writeDelphi(pOutFile, nMode);
    write(pOutFile, ")");
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ObjFieldList != 0)
  {
    ObjFieldList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.newline();

  if (MethodList != 0)
  {
    MethodList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiObjectType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiMethodList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiMethodList::AdtDelphiMethodList(AdtParser* pMethodObj)
 : AdtDelphiBase()
{
  add(pMethodObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiMethodList::AdtDelphiMethodList(const AdtDelphiMethodList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiMethodList::~AdtDelphiMethodList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiMethodList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiMethod method implementations
//  ----------------------------------------------------------------------------
AdtDelphiMethod::AdtDelphiMethod(AdtParser* pProcedureHeadingObj,
                                 AdtParser* pFunctionHeadingObj,
                                 AdtParser* pConstructorHeadingObj,
                                 AdtParser* pDestructorHeadingObj,
                                 AdtParser* pDirectiveListObj)
 : AdtDelphiBase()
{
  initObject(ProcedureHeading,   pProcedureHeadingObj,   AdtDelphiProcedureHeading,   true);
  initObject(FunctionHeading,    pFunctionHeadingObj,    AdtDelphiFunctionHeading,    true);
  initObject(ConstructorHeading, pConstructorHeadingObj, AdtDelphiConstructorHeading, true);
  initObject(DestructorHeading,  pDestructorHeadingObj,  AdtDelphiDestructorHeading,  true);
  initObject(DirectiveList,      pDirectiveListObj,      AdtDelphiDirectiveList,      true);

  if (ProcedureHeading != 0)
  {
    name(ProcedureHeading->name());
  }
  else if (FunctionHeading != 0)
  {
    name(FunctionHeading->name());
  }
  else if (ConstructorHeading != 0)
  {
    name(ConstructorHeading->name());
  }
  else if (DestructorHeading != 0)
  {
    name(DestructorHeading->name());
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiMethod::AdtDelphiMethod(const AdtDelphiMethod& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ProcedureHeading,   rCopy, AdtDelphiProcedureHeading);
  copyObject(FunctionHeading,    rCopy, AdtDelphiFunctionHeading);
  copyObject(ConstructorHeading, rCopy, AdtDelphiConstructorHeading);
  copyObject(DestructorHeading,  rCopy, AdtDelphiDestructorHeading);
  copyObject(DirectiveList,      rCopy, AdtDelphiDirectiveList);
}

//  ----------------------------------------------------------------------------

AdtDelphiMethod::~AdtDelphiMethod()
{
  UtlReleaseReference(ProcedureHeading);
  UtlReleaseReference(FunctionHeading);
  UtlReleaseReference(ConstructorHeading);
  UtlReleaseReference(DestructorHeading);
  UtlReleaseReference(DirectiveList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiMethod::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: methods not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiMethod::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (ProcedureHeading != 0)
  {
    ProcedureHeading->writeDelphi(pOutFile, nMode);
  }

  if (FunctionHeading != 0)
  {
    FunctionHeading->writeDelphi(pOutFile, nMode);
  }

  if (ConstructorHeading != 0)
  {
    ConstructorHeading->writeDelphi(pOutFile, nMode);
  }

  if (DestructorHeading != 0)
  {
    DestructorHeading->writeDelphi(pOutFile, nMode);
  }

  if ((DirectiveList != 0) && (DirectiveList->listSize() > 0))
  {
    write(pOutFile, ";");
    DirectiveList->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiMethod::isVirtual() const
{
  bool bIsVirtual = (DirectiveList != 0) ? DirectiveList->hasDirective(AdtDelphiDirective::AdtType_VIRTUAL) | DirectiveList->hasDirective(AdtDelphiDirective::AdtType_OVERRIDE) : false;

  return (bIsVirtual);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiMethod, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstructorHeading method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstructorHeading::AdtDelphiConstructorHeading(AdtParser* pClassIdentObj,
                                                         AdtParser* pMethodIdentObj,
                                                         AdtParser* pFormalParametersObj,
                                                         const char* pComment)
 : AdtDelphiBase()
{
  initObject(ClassIdent,        pClassIdentObj,       AdtDelphiIdent,             true);
  initObject(MethodIdent,       pMethodIdentObj,      AdtDelphiIdent,             true);
  initObject(FormalParameters,  pFormalParametersObj, AdtDelphiFormalParameters,  true);

  if (ClassIdent != 0)
  {
    name(ClassIdent->name() + ".");
  }

  if (MethodIdent != 0)
  {
    name("CONSTRUCTOR " + name() + MethodIdent->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstructorHeading::AdtDelphiConstructorHeading(const AdtDelphiConstructorHeading& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ClassIdent,       rCopy, AdtDelphiIdent);
  copyObject(MethodIdent,      rCopy, AdtDelphiIdent);
  copyObject(FormalParameters, rCopy, AdtDelphiFormalParameters);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstructorHeading::~AdtDelphiConstructorHeading()
{
  UtlReleaseReference(ClassIdent);
  UtlReleaseReference(MethodIdent);
  UtlReleaseReference(FormalParameters);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstructorHeading::writeCPP(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (FormalParameters != 0)
  {
    FormalParameters->writeCPP(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstructorHeading::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "constructor ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeDelphi(pOutFile, nMode);
    write(pOutFile, '.');
  }

  if (MethodIdent != 0)
  {
    MethodIdent->writeDelphi(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstructorHeading, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiDestructorHeading method implementations
//  ----------------------------------------------------------------------------
AdtDelphiDestructorHeading::AdtDelphiDestructorHeading(AdtParser* pClassIdentObj,
                                                       AdtParser* pMethodIdentObj,
                                                       AdtParser* pFormalParametersObj,
                                                       const char* pComment)
 : AdtDelphiBase()
{
  initObject(ClassIdent,        pClassIdentObj,       AdtDelphiIdent,             true);
  initObject(MethodIdent,       pMethodIdentObj,      AdtDelphiIdent,             true);
  initObject(FormalParameters,  pFormalParametersObj, AdtDelphiFormalParameters,  true);

  if (ClassIdent != 0)
  {
    name(ClassIdent->name() + ".");
  }

  if (MethodIdent != 0)
  {
    name("DESTRUCTOR " + name() + MethodIdent->name());
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiDestructorHeading::AdtDelphiDestructorHeading(const AdtDelphiDestructorHeading& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ClassIdent,       rCopy, AdtDelphiIdent);
  copyObject(MethodIdent,      rCopy, AdtDelphiIdent);
  copyObject(FormalParameters, rCopy, AdtDelphiFormalParameters);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiDestructorHeading::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "destructor ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeDelphi(pOutFile, nMode);
    write(pOutFile, '.');
  }

  if (MethodIdent != 0)
  {
    MethodIdent->writeDelphi(pOutFile, nMode);
  }

  if (FormalParameters != 0)
  {
    FormalParameters->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtDelphiDestructorHeading::~AdtDelphiDestructorHeading()
{
  UtlReleaseReference(ClassIdent);
  UtlReleaseReference(MethodIdent);
  UtlReleaseReference(FormalParameters);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiDestructorHeading, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiObjFieldList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiObjFieldList::AdtDelphiObjFieldList(AdtParser* pObjFieldObj)
 : AdtDelphiBase()
{
  add(pObjFieldObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiObjFieldList::AdtDelphiObjFieldList(const AdtDelphiObjFieldList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiObjFieldList::~AdtDelphiObjFieldList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiObjFieldList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiObjField method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiObjField::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (IdentList != 0)
  {
    IdentList->enumerateAddByObjList(rMap, pObj);
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiObjField::AdtDelphiObjField(AdtParser* pIdentListObj,
                                     AdtParser* pTypeObj)
 : AdtDelphiBase()
{
  initObject(IdentList, pIdentListObj,  AdtDelphiIdentList, true);
  initObject(Type,      pTypeObj,       AdtDelphiType,      true);

  if (AdtAutoClass::automationEnabled())
  {
    // Need to add the types and sizes to the CurrentClass
    AdtAutoClass* pClass = AdtAutoClass::currentClass();

    if ((pClass != 0) && (Type != 0) && (IdentList != 0))
    {
      AdtParserPtrListConstIter Iter;
      const AdtParserPtrList&   rIdentList = IdentList->objList();

      for (Iter = rIdentList.begin() ; Iter != rIdentList.end() ; ++Iter)
      {
        AdtParser*  pObj = *Iter;

        if ((pObj != 0) && pObj->isType("AdtDelphiIdent"))
        {
          AdtDelphiIdent* pIdent      = (AdtDelphiIdent*)pObj;
          int             nDimensions = 0;
          AdtAutoType     nType       = Type->autoType(nDimensions);

          if (nType != AdtAutoType_UNDEFINED)
          {
            // Only add variables that aren't stack related. Stack vars fail
            // automation dependency checking cos dim_stack isn't defined.
            if (strstr(pIdent->name(), "stack") == 0)
            {
              if (nDimensions > 0)
              {
                AdtStringList rArrayUpperBoundList;
                AdtStringList rArrayLowerBoundList;

                pIdent->enumerateArraySizes(rArrayUpperBoundList, rArrayLowerBoundList);

                if ((rArrayLowerBoundList.size() == nDimensions) &&
                    (rArrayUpperBoundList.size() == nDimensions))
                {
                  AdtAutoArray* pArray = pClass->addArray(pIdent->name(),
                                                          nType,
                                                          AdtAutoDir_UNDEFINED,
                                                          nDimensions,
                                                          Type->fileName(),
                                                          Type->lineNumber());

                  if (pArray != 0)
                  {
                    AdtStringListConstIter  IterL = rArrayLowerBoundList.begin();
                    AdtStringListConstIter  IterU = rArrayUpperBoundList.begin();

                    for (int cn = 0 ; cn < nDimensions ; cn++)
                    {
                      const string& rArrayLowerBound = *IterL;
                      const string& rArrayUpperBound = *IterU;

                      pArray->addArrayIndex(rArrayLowerBound,
                                            rArrayUpperBound,
                                            cn);

                      IterL++;
                      IterU++;
                    }
                  }
                }
              }
              else
              {
                pClass->addScalar(pIdent->name(),
                                  nType,
                                  AdtAutoDir_UNDEFINED,
                                  Type->fileName(),
                                  Type->lineNumber());
              }
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiObjField::AdtDelphiObjField(const AdtDelphiObjField& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList, rCopy, AdtDelphiIdentList);
  copyObject(Type,      rCopy, AdtDelphiType);
}

//  ----------------------------------------------------------------------------

AdtDelphiObjField::~AdtDelphiObjField()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(Type);
}

//  ----------------------------------------------------------------------------

void AdtDelphiObjField::removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList)
{
  if (IdentList != 0)
  {
    IdentList->removeMatching(rMap, pRemovedList);

    if (IdentList->listSize() == 0)
    {
      UtlReleaseReference(IdentList);
      UtlReleaseReference(Type);

      IdentList = 0;
      Type      = 0;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiObjField::writeFortran(AdtFile& pOutFile, int nMode) const
{
  const char* sDimension = 0;
  bool        bKeep      = true;

  writePragmas(pOutFile);

  if (Type != 0)
  {
    Type->writeFortran(pOutFile, nMode, sDimension, bKeep);
  }

  if (bKeep)
  {
    write(pOutFile, ' ');

    if (IdentList != 0)
    {
      IdentList->writeArrayBounds(pOutFile, nMode, sDimension);
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiObjField::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    IdentList->writeDelphi(pOutFile, nMode);
  }

  if (Type != 0)
  {
    write(pOutFile, " : ");
    Type->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiObjField, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiInitSection method implementations
//  ----------------------------------------------------------------------------
AdtDelphiInitSection::AdtDelphiInitSection(AdtParser* pStmtListObj,
                                           AdtParser* pFinalStmtListObj,
                                           bool bHasInit,
                                           const char* pComment)
 : AdtDelphiBase()
{
  initObject(StmtList,      pStmtListObj,       AdtDelphiStmtList,  true);
  initObject(FinalStmtList, pFinalStmtListObj,  AdtDelphiStmtList,  true);

  HasInit = bHasInit;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiInitSection::AdtDelphiInitSection(const AdtDelphiInitSection& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(StmtList,      rCopy, AdtDelphiStmtList);
  copyObject(FinalStmtList, rCopy, AdtDelphiStmtList);

  HasInit = rCopy.HasInit;
}

//  ----------------------------------------------------------------------------

AdtDelphiInitSection::~AdtDelphiInitSection()
{
  UtlReleaseReference(StmtList);
  UtlReleaseReference(FinalStmtList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiInitSection::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: INITIALIZATION not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiInitSection::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (HasInit)
  {
    write(pOutFile, "initialization");

    if (StmtList != 0)
    {
      pOutFile.incrementIndent();
      pOutFile.newline();

      StmtList->writeDelphi(pOutFile, nMode);

      pOutFile.decrementIndent();

      if (FinalStmtList != 0)
      {
        pOutFile.newline();
      }
    }

    if (FinalStmtList != 0)
    {
      write(pOutFile, "finalization");

      pOutFile.incrementIndent();
      pOutFile.newline();

      FinalStmtList->writeDelphi(pOutFile, nMode);

      pOutFile.decrementIndent();
      pOutFile.homeline();
    }
  }
  else
  {
    if (StmtList != 0)
    {
      write(pOutFile, "begin");

      pOutFile.incrementIndent();
      pOutFile.newline();

      StmtList->writeDelphi(pOutFile, nMode);

      pOutFile.decrementIndent();
      pOutFile.homeline();
    }
  }

  write(pOutFile, "end");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiInitSection, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassType method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiClassType::listAddOjects(AdtParser* pDestList,
                                       const AdtParser* pSrcList,
                                       const char* pObjectTypeName,
                                       const char* pDestClassName,
                                       const char* pSrcClassName)
{
  if ((pDestList  != 0) &&
      (pSrcList   != 0))
  {
    AdtParserPtrByStringMap DefinedObjMap;

    //Enumerate all the objects defined in this class
    pDestList->enumerate(DefinedObjMap);

    //Enumerate objects to add to class declaration
    const AdtParserPtrList&   NewObjList = pSrcList->objList();
    AdtParserPtrListConstIter NewObjIter;

    for (NewObjIter = NewObjList.begin() ; NewObjIter != NewObjList.end() ; ++NewObjIter)
    {
      AdtParser*  pObj = *NewObjIter;

      if (pObj != 0)
      {
        AdtParser*  pObjCopy = pObj->copy();

        if (pObjCopy != 0)
        {
          AdtParserPtrList      RemovedObjList;
          AdtParserPtrListIter  RemovedObjIter;

          pObjCopy->removeMatching(DefinedObjMap, &RemovedObjList);
          pDestList->add(pObjCopy);

          if ((pObjectTypeName  != 0) &&
              (pDestClassName   != 0) &&
              (pSrcClassName    != 0))
          {
            for (RemovedObjIter = RemovedObjList.begin() ; RemovedObjIter != RemovedObjList.end() ; ++RemovedObjIter)
            {
              AdtParser*  pRemovedObj = *RemovedObjIter;

              if (pRemovedObj != 0)
              {
                ::printf("WARNING : %s %s from class %s \n          already defined in class %s\n",
                         pObjectTypeName,
                         pRemovedObj->name().c_str(),
                         pSrcClassName,
                         pDestClassName);
              }
            }
          }
        }

        UtlReleaseReference(pObjCopy);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassType::addFields(AdtDelphiGoal* pGoal,
                                   const AdtDelphiGoal* pIncludeGoal,
                                   const AdtDelphiClassType* pClass,
                                   const string& rDestClassName,
                                   const string& rSrcClassName)
{
  if (ClassFieldList == 0)
  {
    ClassFieldList = new AdtDelphiClassFieldList(0);

    if (ClassFieldList != 0)
    {
      ClassFieldList->parent(this);
    }
  }

  listAddOjects(ClassFieldList,
                pClass->ClassFieldList,
                "attribute",
                rDestClassName,
                rSrcClassName);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassType::addMethods(AdtDelphiGoal* pGoal,
                                    const AdtDelphiGoal* pIncludeGoal,
                                    const AdtDelphiClassType* pClass,
                                    const string& rDestClassName,
                                    const string& rSrcClassName)
{
  if (ClassMethodList == 0)
  {
    ClassMethodList = new AdtDelphiClassMethodList(0);

    if (ClassMethodList != 0)
    {
      ClassMethodList->parent(this);
    }
  }

  if (ClassMethodList != 0)
  {
    AdtParserPtrList        MethodList;
    AdtParserPtrListIter    MethodIter;
    AdtParserPtrByStringMap DefinedMethodMap;

    //Enumerate all the methods defined in this class
    ClassMethodList->enumerate(DefinedMethodMap);
    pClass->findObjects(MethodList, "AdtDelphiMethod");

    for (MethodIter = MethodList.begin() ; MethodIter != MethodList.end() ; ++MethodIter)
    {
      AdtDelphiMethod*  pMethod = (AdtDelphiMethod*)(AdtParser*)*MethodIter;

      if (pMethod != 0)
      {
        AdtParserPtrByStringMapConstIter  DefinedMethodIter = DefinedMethodMap.find(pMethod->name());

        //If a method of the same name is already defined don't import it
        if (DefinedMethodIter == DefinedMethodMap.end())
        {
          string                            sMethodName(rSrcClassName);
          const AdtDelphiProcedureDecl*     pProcedureDecl      = 0;
          AdtDelphiProcedureDeclList*       pProcedureDeclList  = 0;

          sMethodName += ".";
          sMethodName += pMethod->name();

          //Find the method implementation and add it to pGoal
          pProcedureDecl      = pIncludeGoal->findProcedureDeclaration(sMethodName);
          pProcedureDeclList  = (AdtDelphiProcedureDeclList*)pGoal->findDescendant("Unit,ImplementationSection,DeclSection,ProcedureDeclSection,ProcedureDeclList;Program,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList;Library,Block,DeclSection,ProcedureDeclSection,ProcedureDeclList");

          if ((pProcedureDecl != 0) && (pProcedureDeclList != 0))
          {
            AdtDelphiProcedureDecl* pProcedureDeclCopy = (AdtDelphiProcedureDecl*)pProcedureDecl->copy();

            pProcedureDeclCopy->replaceClassNameWith(rDestClassName);
            pProcedureDeclList->add(pProcedureDeclCopy);
            UtlReleaseReference(pProcedureDeclCopy);
          }
        }
        else
        {
          ::printf("WARNING : method %s from class %s \n          already defined in class %s\n",
                   pMethod->name().c_str(),
                   rSrcClassName.c_str(),
                   rDestClassName.c_str());
        }
      }
    }

    MethodList.clear();

    //Enumerate method definitions to add to class declaration
    const AdtParserPtrList&   NewMethodList = pClass->ClassMethodList->objList();
    AdtParserPtrListConstIter NewMethodIter;

    for (NewMethodIter = NewMethodList.begin() ; NewMethodIter != NewMethodList.end() ; ++NewMethodIter)
    {
      AdtParser*  pObj = *NewMethodIter;

      if (pObj != 0)
      {
        AdtParser*  pMethodObj = pObj->findDescendant("Method");

        if (pMethodObj != 0)
        {
          AdtParserPtrByStringMapConstIter  DefinedMethodIter = DefinedMethodMap.find(pMethodObj->name());

          if (DefinedMethodIter == DefinedMethodMap.end())
          {
            AdtParser*  pObjCopy = pObj->copy();

            ClassMethodList->add(pObjCopy);
            UtlReleaseReference(pObjCopy);
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassType::addProperties(AdtDelphiGoal* pGoal,
                                       const AdtDelphiGoal* pIncludeGoal,
                                       const AdtDelphiClassType* pClass,
                                       const string& rDestClassName,
                                       const string& rSrcClassName)
{
  if (ClassPropertyList == 0)
  {
    ClassPropertyList = new AdtDelphiClassPropertyList(0);

    if (ClassPropertyList != 0)
    {
      ClassPropertyList->parent(this);
    }
  }

  listAddOjects(ClassPropertyList,
                pClass->ClassPropertyList,
                "property",
                rDestClassName,
                rSrcClassName);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::importClass(const string& rDestClassName,
                                     const string& rSrcClassName,
                                     AdtDelphiGoal* pGoal,
                                     const AdtParserPtrList& rGoalList)
{
  bool bImported = false;

  ASSERT(pGoal != 0);

  AdtParserPtrListConstIter GoalIter;

  for (GoalIter = rGoalList.begin() ; GoalIter != rGoalList.end() ; ++GoalIter)
  {
    const AdtDelphiGoal*  pIncludeGoal = (const AdtDelphiGoal*)(const AdtParser*)*GoalIter;

    if (pIncludeGoal != 0)
    {
      const AdtDelphiClassType* pClass = pIncludeGoal->findClassType(rSrcClassName);

      if (pClass != 0)
      {
        // FixMe!
        // ------
        // Somewhere in here I need to check if the symbol names clash with the
        // currently defined array vars (ie. imbedded in comments) and if they do
        // then modify the symbol names to not clash. You must check that the
        // modified names don't clash with the array vars in the original source
        // or else we may be creating a problem at the same time as solving one.
        //
        // To do this I guess it would be helpful if the array vars were already
        // known and cached. Currently that is only determined when a call is
        // made to writeFortran(), which is too late as far as this process is
        // concerned.

        //Add fields, methods and properties
        addFields(pGoal, pIncludeGoal, pClass, rDestClassName, rSrcClassName);
        addMethods(pGoal, pIncludeGoal, pClass, rDestClassName, rSrcClassName);
        addProperties(pGoal, pIncludeGoal, pClass, rDestClassName, rSrcClassName);

        if (pClass->IdentList != 0)
        {
          //import parent class of import class
          flattenClass(rDestClassName, pClass->IdentList->objList(), pGoal, rGoalList);
        }

        bImported = true;
      }
    }
  }

  if (bImported)
  {
    //Re-enumerate the maps
    FieldMap.clear();
    MethodMap.clear();
    PropertyMap.clear();
    SymbolMap.clear();

    enumerateDescendantMap(FieldMap,    "ClassFieldList");
    enumerateDescendantMap(MethodMap,   "ClassMethodList");
    enumerateDescendantMap(PropertyMap, "ClassPropertyList");

    append(SymbolMap, FieldMap);
    append(SymbolMap, MethodMap);
    append(SymbolMap, PropertyMap);
  }
  else
  {
    ::printf("WARNING: Can't import class %s.\n         Check makefile for source file inclusion.\n", rSrcClassName.c_str());
  }

  return (bImported);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::flattenClass(const string& rClassName,
                                      const AdtParserPtrList& rParentList,
                                      AdtDelphiGoal* pGoal,
                                      const AdtParserPtrList& rGoalList)
{
  bool bFlattened = false;

  if ((IdentList != 0) && (pGoal != 0))
  {
    AdtParserPtrListConstIter ParentIter;

    for (ParentIter = rParentList.begin() ; ParentIter != rParentList.end() ; ++ParentIter)
    {
      const AdtParser* pIdent = *ParentIter;

      if (pIdent != 0)
      {
        const string& rParentClassName = pIdent->name();

        importClass(rClassName, rParentClassName, pGoal, rGoalList);
      }
    }
  }

  return (bFlattened);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassType::AdtDelphiClassType(AdtParser* pIdentListObj,
                                       AdtParser* pClassFieldListObj,
                                       AdtParser* pClassMethodListObj,
                                       AdtParser* pClassPropertyListObj)
 : AdtDelphiBase(),
   FieldMap(),
   MethodMap(),
   PropertyMap(),
   SymbolMap()
{
  initObject(IdentList,         pIdentListObj,          AdtDelphiIdentList,         true);
  initObject(ClassFieldList,    pClassFieldListObj,     AdtDelphiClassFieldList,    true);
  initObject(ClassMethodList,   pClassMethodListObj,    AdtDelphiClassMethodList,   true);
  initObject(ClassPropertyList, pClassPropertyListObj,  AdtDelphiClassPropertyList, true);

  enumerateDescendantMap(FieldMap,    "ClassFieldList");
  enumerateDescendantMap(MethodMap,   "ClassMethodList");
  enumerateDescendantMap(PropertyMap, "ClassPropertyList");

  append(SymbolMap, FieldMap);
  append(SymbolMap, MethodMap);
  append(SymbolMap, PropertyMap);

  AdtDelphiClassType::GlobalVisibility = AdtVisibility_PUBLIC;
}

//  ----------------------------------------------------------------------------

AdtDelphiClassType::AdtDelphiClassType(const AdtDelphiClassType& rCopy)
 : AdtDelphiBase(rCopy),
   FieldMap(),
   MethodMap(),
   PropertyMap(),
   SymbolMap()
{
  copyObject(IdentList,         rCopy, AdtDelphiIdentList);
  copyObject(ClassFieldList,    rCopy, AdtDelphiClassFieldList);
  copyObject(ClassMethodList,   rCopy, AdtDelphiClassMethodList);
  copyObject(ClassPropertyList, rCopy, AdtDelphiClassPropertyList);

  enumerateDescendantMap(FieldMap,    "ClassFieldList");
  enumerateDescendantMap(MethodMap,   "ClassMethodList");
  enumerateDescendantMap(PropertyMap, "ClassPropertyList");

  append(SymbolMap, FieldMap);
  append(SymbolMap, MethodMap);
  append(SymbolMap, PropertyMap);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassType::~AdtDelphiClassType()
{
  FieldMap.clear();
  MethodMap.clear();
  PropertyMap.clear();
  SymbolMap.clear();

  UtlReleaseReference(IdentList);
  UtlReleaseReference(ClassFieldList);
  UtlReleaseReference(ClassMethodList);
  UtlReleaseReference(ClassPropertyList);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::flattenClass(AdtDelphiGoal* pGoal, const AdtParserPtrList& rGoalList)
{
  bool                bFlattened  = false;
  AdtDelphiTypeDecl*  pTypeDecl   = (AdtDelphiTypeDecl*)findAscendantWithClassLineage("AdtDelphiRestrictedType,AdtDelphiTypeDecl");

  if (pTypeDecl != 0)
  {
    bFlattened  = flattenClass(pTypeDecl->name(), IdentList->objList(), pGoal, rGoalList);
  }

  return (bFlattened);
}

//  ----------------------------------------------------------------------------

const char* AdtDelphiClassType::parentClassName() const
{
  const char* pParentClassName = 0;

  if ((IdentList != 0) && (IdentList->listSize() == 1))
  {
    AdtParserPtrListConstIter Iter  = IdentList->objList().begin();
    const AdtParser*          pObj  = (*Iter);

    if (pObj != 0)
    {
      pParentClassName = pObj->name();
    }
  }

  return (pParentClassName);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassType::SymbolType AdtDelphiClassType::defined(const char* pName) const
{
  SymbolType        Result    = TypeUndefined;
  const AdtParser*  pExternal = 0;

  if (findObject(FieldMap, pName, pExternal))
  {
    Result = TypeField;
  }
  else if (findObject(MethodMap, pName, pExternal))
  {
    Result = TypeMethod;
  }
  else if (findObject(PropertyMap, pName, pExternal))
  {
    Result = TypeProperty;
  }

  return (Result);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassType::findDimensionVars(const AdtParserPtrByStringMap& rVarsMap,
                                           AdtParserPtrList& rList) const
{
  AdtStringByStringMap              DefinedMap;
  AdtParserPtrByStringMapConstIter  Iter;

  // Make map of object names as a check for whether they are already mapped
  for (Iter = rVarsMap.begin() ; Iter != rVarsMap.end() ; ++Iter)
  {
    const AdtParser* pObj = Iter->second;

    if ((pObj != 0) && pObj->isType("AdtDelphiIdent"))
    {
      AdtDelphiIdent* pIdent;

      pIdent                     = (AdtDelphiIdent*)pObj;
      DefinedMap[pIdent->name()] = pIdent->name();
    }
  }

  // For all the mapped variables check for dimension specs and add dim vars
  for (Iter = rVarsMap.begin() ; Iter != rVarsMap.end() ; ++Iter)
  {
    const AdtParser* pObj = Iter->second;

    if ((pObj != 0) && pObj->isType("AdtDelphiIdent"))
    {
      AdtStringListIter StrIter;
      AdtStringList     rArrayBoundList;
      AdtDelphiIdent*   pIdent = (AdtDelphiIdent*)pObj;

      pIdent->enumerateArraySizes(rArrayBoundList, rArrayBoundList);

      for (StrIter = rArrayBoundList.begin() ; StrIter != rArrayBoundList.end() ; ++StrIter)
      {
        AdtExpressionCompiler Compiler;
        AdtStringList         rDependencyList;
        AdtStringListIter     DepIter;
        const string&         rIndexExpression = *StrIter;

        Compiler.findDependencies(rIndexExpression, rDependencyList);

        for (DepIter = rDependencyList.begin() ; DepIter != rDependencyList.end() ; ++DepIter)
        {
          const string&     rDepName = *DepIter;
          const AdtParser*  pDepObj  = 0;

          if ((DefinedMap.find(rDepName) == DefinedMap.end()) && findField(rDepName, pDepObj))
          {
            DefinedMap[pDepObj->name()] = pDepObj->name();
            rList.push_back((AdtParser*)pDepObj);
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::findField(const char* pName, const AdtParser*& pExternal) const
{
  bool bFound = findObject(FieldMap, pName, pExternal);

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::findMethod(const char* pName, const AdtParser*& pExternal) const
{
  bool bFound = findObject(MethodMap, pName, pExternal);

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtDelphiClassType::findProperty(const char* pName, const AdtParser*& pExternal) const
{
  bool bFound = findObject(PropertyMap, pName, pExternal);

  return (bFound);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CLASS not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "class ");

  if (IdentList != 0)
  {
    write(pOutFile, "(");

    IdentList->writeDelphi(pOutFile, nMode);

    write(pOutFile, ")");
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ClassFieldList != 0)
  {
    ClassFieldList->writeDelphi(pOutFile, nMode);
  }

  if (ClassMethodList != 0)
  {
    if (ClassFieldList != 0)
    {
      pOutFile.newline();
    }

    ClassMethodList->writeDelphi(pOutFile, nMode);
  }

  if (ClassPropertyList != 0)
  {
    if ((ClassFieldList  != 0) ||
        (ClassMethodList != 0))
    {
      pOutFile.newline();
    }

    ClassPropertyList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassFieldList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassFieldList::AdtDelphiClassFieldList(AdtParser* pClassFieldObj)
 : AdtDelphiBase()
{
  add(pClassFieldObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassFieldList::AdtDelphiClassFieldList(const AdtDelphiClassFieldList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiClassFieldList::~AdtDelphiClassFieldList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassFieldList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassField method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassField::AdtDelphiClassField(AdtVisibility nVisibility,
                                         AdtParser* pObjFieldObj)
 : AdtDelphiBase()
{
  Visibility = nVisibility;

  if (Visibility != AdtVisibility_EMPTY)
  {
    AdtDelphiClassType::GlobalVisibility = Visibility;
  }

  initObject(ObjField, pObjFieldObj, AdtDelphiObjField, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassField::AdtDelphiClassField(const AdtDelphiClassField& rCopy)
 : AdtDelphiBase(rCopy)
{
  Visibility = rCopy.Visibility;

  copyObject(ObjField, rCopy, AdtDelphiObjField);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassField::~AdtDelphiClassField()
{
  UtlReleaseReference(ObjField);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassField::removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList)
{
  if (ObjField != 0)
  {
    ObjField->removeMatching(rMap, pRemovedList);
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassField::enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const
{
  AdtDelphiBase::enumerateAddObj(rList, ObjField);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassField::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (ObjField != 0)
  {
    ObjField->enumerateAddObj(rMap, ObjField);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassField::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CLASS not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassField::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.decrementIndent();
  pOutFile.homeline();

  switch (Visibility)
  {
    case AdtVisibility_PUBLIC:
    {
      write(pOutFile, "public");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PROTECTED:
    {
      write(pOutFile, "protected");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PRIVATE:
    {
      write(pOutFile, "private");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PUBLISHED:
    {
      write(pOutFile, "published");
      pOutFile.newline();
      break;
    }

    default:
    case AdtVisibility_EMPTY:
    {
      break;
    }
  }

  pOutFile.incrementIndent();
  pOutFile.homeline();

  if (ObjField != 0)
  {
    ObjField->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassField, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassMethodList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassMethodList::AdtDelphiClassMethodList(AdtParser* pClassMethodObj)
 : AdtDelphiBase()
{
  add(pClassMethodObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassMethodList::AdtDelphiClassMethodList(const AdtDelphiClassMethodList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiClassMethodList::~AdtDelphiClassMethodList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassMethodList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassMethod method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassMethod::AdtDelphiClassMethod(AdtVisibility nVisibility,
                                           AdtParser* pMethodObj)
 : AdtDelphiBase()
{
  Visibility = nVisibility;

  initObject(Method, pMethodObj, AdtDelphiMethod, true);

  if (Visibility != AdtVisibility_EMPTY)
  {
    AdtDelphiClassType::GlobalVisibility = Visibility;
  }

  if (AdtAutoClass::automationEnabled() &&
      (Method != 0)                     &&
      ((AdtDelphiClassType::GlobalVisibility == AdtVisibility_PUBLIC) || (AdtDelphiClassType::GlobalVisibility == AdtVisibility_PUBLISHED)))
  {
    // Need to add class methods
    AdtAutoClass* pClass = AdtAutoClass::currentClass();

    if ((pClass != 0) && (Method != 0))
    {
      bool        bIsFunction = true;
      AdtParser*  pRootObj    = Method->findDescendant("FunctionHeading");
      AdtAutoType nReturnType = AdtAutoType_UNDEFINED;

      if (pRootObj == 0)
      {
        pRootObj    = Method->findDescendant("ProcedureHeading");
        bIsFunction = false;
      }
      else
      {
        AdtDelphiSimpleType*  pReturnType;

        pReturnType = (AdtDelphiSimpleType*)pRootObj->findDescendant("SimpleType");

        if (pReturnType != 0)
        {
          nReturnType = pReturnType->autoType();
        }
      }

      if (pRootObj != 0)
      {
        // Add function
        AdtAutoFunction*  pFunction = pClass->addFunction(pRootObj->name(),
                                                          nReturnType,
                                                          AdtAutoDir_UNDEFINED,
                                                          isVirtual(),
                                                          pRootObj->fileName(),
                                                          pRootObj->lineNumber());

        if (pFunction != 0)
        {
          // Add arguments
          AdtParser* pFormalParamList = pRootObj->findDescendant("FormalParameters,FormalParamList");

          if (pFormalParamList != 0)
          {
            AdtParserPtrListConstIter ParamsIter;
            const AdtParserPtrList&   rParamsList = pFormalParamList->objList();

            for (ParamsIter = rParamsList.begin() ; ParamsIter != rParamsList.end() ; ++ParamsIter)
            {
              const AdtDelphiFormalParam* pFormalParam = (const AdtDelphiFormalParam*)(const AdtParser*)(*ParamsIter);

              if (pFormalParam != 0)
              {
                AdtAutoDir                  nDir        = pFormalParam->autoDirType();
                const AdtParser*            pIdentList  = pFormalParam->findDescendant("Parameter,IdentList");
                const AdtDelphiSimpleType*  pSimpleType = (const AdtDelphiSimpleType*)(const AdtParser*)pFormalParam->findDescendant("Parameter,SimpleType");
                const AdtDelphiTypeId*      pTypeId     = (const AdtDelphiTypeId*)(const AdtParser*)pFormalParam->findDescendant("Parameter,TypeId");

                if (pIdentList != 0)
                {
                  AdtParserPtrListConstIter Iter;
                  const AdtParserPtrList&   rIdentList = pIdentList->objList();

                  for (Iter = rIdentList.begin() ; Iter != rIdentList.end() ; ++Iter)
                  {
                    const AdtDelphiIdent* pIdent = (const AdtDelphiIdent*)(const AdtParser*)*Iter;

                    if (pIdent != 0)
                    {
                      int             nDimensions = 0;
                      AdtAutoType     nType       = AdtDelphiType::autoType(pTypeId,
                                                                            pSimpleType,
                                                                            nDimensions);

                      if (nType != AdtAutoType_UNDEFINED)
                      {
                        if (nDimensions > 0)
                        {
                          AdtStringList rArrayUpperBoundList;
                          AdtStringList rArrayLowerBoundList;

                          pIdent->enumerateArraySizes(rArrayUpperBoundList, rArrayLowerBoundList);

                          if ((rArrayLowerBoundList.size() == nDimensions) &&
                              (rArrayUpperBoundList.size() == nDimensions))
                          {
                            AdtAutoArray* pArray = pFunction->addArray(pIdent->name(),
                                                                       nType,
                                                                       nDir,
                                                                       nDimensions,
                                                                       pIdent->fileName(),
                                                                       pIdent->lineNumber());

                            if (pArray != 0)
                            {
                              AdtStringListConstIter  IterL = rArrayLowerBoundList.begin();
                              AdtStringListConstIter  IterU = rArrayUpperBoundList.begin();

                              for (int cn = 0 ; cn < nDimensions ; cn++)
                              {
                                const string& rArrayLowerBound = *IterL;
                                const string& rArrayUpperBound = *IterU;

                                pArray->addArrayIndex(rArrayLowerBound,
                                                      rArrayUpperBound,
                                                      cn);

                                IterL++;
                                IterU++;
                              }
                            }
                          }
                        }
                        else
                        {
                          pFunction->addScalar(pIdent->name(),
                                               nType,
                                               nDir,
                                               pIdent->fileName(),
                                               pIdent->lineNumber());
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiClassMethod::AdtDelphiClassMethod(const AdtDelphiClassMethod& rCopy)
 : AdtDelphiBase(rCopy)
{
  Visibility = rCopy.Visibility;

  copyObject(Method, rCopy, AdtDelphiMethod);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassMethod::~AdtDelphiClassMethod()
{
  UtlReleaseReference(Method);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassMethod::enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const
{
  AdtDelphiBase::enumerateAddObj(rList, Method);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassMethod::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (Method != 0)
  {
    Method->enumerateAddObj(rMap, Method);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassMethod::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CLASS not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassMethod::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.decrementIndent();
  pOutFile.homeline();

  switch (Visibility)
  {
    case AdtVisibility_PUBLIC:
    {
      write(pOutFile, "public");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PROTECTED:
    {
      write(pOutFile, "protected");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PRIVATE:
    {
      write(pOutFile, "private");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PUBLISHED:
    {
      write(pOutFile, "published");
      pOutFile.newline();
      break;
    }

    default:
    case AdtVisibility_EMPTY:
    {
      break;
    }
  }

  pOutFile.incrementIndent();
  pOutFile.homeline();

  if (Method != 0)
  {
    Method->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}


//  ----------------------------------------------------------------------------

bool AdtDelphiClassMethod::isVirtual() const
{
  bool bIsVirtual = (Method != 0) ? Method->isVirtual() : false;

  return (bIsVirtual);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassMethod, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassPropertyList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassPropertyList::AdtDelphiClassPropertyList(AdtParser* pClassPropertyObj)
 : AdtDelphiBase()
{
  add(pClassPropertyObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassPropertyList::AdtDelphiClassPropertyList(const AdtDelphiClassPropertyList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiClassPropertyList::~AdtDelphiClassPropertyList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassPropertyList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiClassProperty method implementations
//  ----------------------------------------------------------------------------
AdtDelphiClassProperty::AdtDelphiClassProperty(AdtVisibility nVisibility,
                                               AdtParser* pPropertyObj)
 : AdtDelphiBase()
{
  Visibility = nVisibility;

  if (Visibility != AdtVisibility_EMPTY)
  {
    AdtDelphiClassType::GlobalVisibility = Visibility;
  }

  initObject(Property, pPropertyObj, AdtDelphiProperty, true);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassProperty::AdtDelphiClassProperty(const AdtDelphiClassProperty& rCopy)
 : AdtDelphiBase(rCopy)
{
  Visibility = rCopy.Visibility;

  copyObject(Property, rCopy, AdtDelphiProperty);
}

//  ----------------------------------------------------------------------------

AdtDelphiClassProperty::~AdtDelphiClassProperty()
{
  UtlReleaseReference(Property);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassProperty::enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const
{
  AdtDelphiBase::enumerateAddObj(rList, Property);
}

//  ----------------------------------------------------------------------------

void AdtDelphiClassProperty::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if (Property != 0)
  {
    Property->enumerateAddObj(rMap, Property);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassProperty::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: CLASS not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiClassProperty::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  pOutFile.decrementIndent();
  pOutFile.homeline();

  switch (Visibility)
  {
    case AdtVisibility_PUBLIC:
    {
      write(pOutFile, "public");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PROTECTED:
    {
      write(pOutFile, "protected");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PRIVATE:
    {
      write(pOutFile, "private");
      pOutFile.newline();
      break;
    }

    case AdtVisibility_PUBLISHED:
    {
      write(pOutFile, "published");
      pOutFile.newline();
      break;
    }

    default:
    case AdtVisibility_EMPTY:
    {
      break;
    }
  }

  pOutFile.incrementIndent();
  pOutFile.homeline();

  if (Property != 0)
  {
    Property->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiClassProperty, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiProperty method implementations
//  ----------------------------------------------------------------------------
AdtDelphiProperty::AdtDelphiProperty(AdtParser* pClassIdentObj,
                                     AdtParser* pIdentObj,
                                     AdtParser* pPropertyParameterListObj,
                                     AdtParser* pPropertySpecifiersObj)
 : AdtDelphiBase()
{
  initObject(ClassIdent,            pClassIdentObj,             AdtDelphiIdent,                 true);
  initObject(Ident,                 pIdentObj,                  AdtDelphiIdent,                 true);
  initObject(PropertyParameterList, pPropertyParameterListObj,  AdtDelphiPropertyParameterList, true);
  initObject(PropertySpecifiers,    pPropertySpecifiersObj,     AdtDelphiPropertySpecifiers,    true);
}

//  ----------------------------------------------------------------------------

AdtDelphiProperty::AdtDelphiProperty(const AdtDelphiProperty& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(ClassIdent,            rCopy, AdtDelphiIdent);
  copyObject(Ident,                 rCopy, AdtDelphiIdent);
  copyObject(PropertyParameterList, rCopy, AdtDelphiPropertyParameterList);
  copyObject(PropertySpecifiers,    rCopy, AdtDelphiPropertySpecifiers);
}

//  ----------------------------------------------------------------------------

AdtDelphiProperty::~AdtDelphiProperty()
{
  UtlReleaseReference(ClassIdent);
  UtlReleaseReference(Ident);
  UtlReleaseReference(PropertyParameterList);
  UtlReleaseReference(PropertySpecifiers);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProperty::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: PROPERTY not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiProperty::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "property ");

  if (ClassIdent != 0)
  {
    ClassIdent->writeDelphi(pOutFile, nMode);
  }

  if (PropertyParameterList != 0)
  {
    write(pOutFile, " [");
    PropertyParameterList->writeDelphi(pOutFile, nMode);
    write(pOutFile, "] ");
  }

  if (Ident != 0)
  {
    if (ClassIdent != 0)
    {
      write(pOutFile, " : ");
    }

    Ident->writeDelphi(pOutFile, nMode);
    write(pOutFile, " ");
  }

  if (PropertySpecifiers != 0)
  {
    PropertySpecifiers->writeDelphi(pOutFile, nMode);
  }

  write(pOutFile, " ");

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiProperty, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertyParameterList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiPropertyParameterList::AdtDelphiPropertyParameterList(AdtParser* pPropertyParameterObj)
 : AdtDelphiBase()
{
  add(pPropertyParameterObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiPropertyParameterList::AdtDelphiPropertyParameterList(const AdtDelphiPropertyParameterList& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiPropertyParameterList::~AdtDelphiPropertyParameterList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiPropertyParameterList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertyParameter method implementations
//  ----------------------------------------------------------------------------
AdtDelphiPropertyParameter::AdtDelphiPropertyParameter(AdtParser* pIdentListObj,
                                                       AdtParser* pUnitIdObj,
                                                       AdtParser* pTypeIdObj)
 : AdtDelphiBase()
{
  initObject(IdentList, pIdentListObj,  AdtDelphiIdentList, true);
  initObject(UnitId,    pUnitIdObj,     AdtDelphiUnitId,    true);
  initObject(TypeId,    pTypeIdObj,     AdtDelphiTypeId,    true);
}

//  ----------------------------------------------------------------------------

AdtDelphiPropertyParameter::AdtDelphiPropertyParameter(const AdtDelphiPropertyParameter& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList, rCopy, AdtDelphiIdentList);
  copyObject(UnitId,    rCopy, AdtDelphiUnitId);
  copyObject(TypeId,    rCopy, AdtDelphiTypeId);
}

//  ----------------------------------------------------------------------------

AdtDelphiPropertyParameter::~AdtDelphiPropertyParameter()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(UnitId);
  UtlReleaseReference(TypeId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPropertyParameter::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: PROPERTY not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPropertyParameter::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  if (IdentList != 0)
  {
    IdentList->writeDelphi(pOutFile, nMode);
    write(pOutFile, " : ");
  }

  if (UnitId != 0)
  {
    UnitId->writeDelphi(pOutFile, nMode);
    write(pOutFile, ".");
  }

  if (TypeId != 0)
  {
    TypeId->writeDelphi(pOutFile, nMode);
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiPropertyParameter, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertySpecifiers method implementations
//  ----------------------------------------------------------------------------
AdtDelphiPropertySpecifiers::AdtDelphiPropertySpecifiers(AdtType nType,
                                                         AdtParser* pIdentObj,
                                                         AdtParser* pConstExprObj,
                                                         AdtParser* pUnitIdObj,
                                                         AdtParser* pTypeIdObj)
 : AdtDelphiBase()
{
  Type = nType;

  initObject(Ident,     pIdentObj,      AdtDelphiIdent,     true);
  initObject(ConstExpr, pConstExprObj,  AdtDelphiConstExpr, true);
  initObject(UnitId,    pUnitIdObj,     AdtDelphiUnitId,    true);
  initObject(TypeId,    pTypeIdObj,     AdtDelphiTypeId,    true);
}

//  ----------------------------------------------------------------------------

AdtDelphiPropertySpecifiers::AdtDelphiPropertySpecifiers(const AdtDelphiPropertySpecifiers& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;

  copyObject(Ident,     rCopy, AdtDelphiIdent);
  copyObject(ConstExpr, rCopy, AdtDelphiConstExpr);
  copyObject(UnitId,    rCopy, AdtDelphiUnitId);
  copyObject(TypeId,    rCopy, AdtDelphiTypeId);
}

//  ----------------------------------------------------------------------------

AdtDelphiPropertySpecifiers::~AdtDelphiPropertySpecifiers()
{
  UtlReleaseReference(Ident);
  UtlReleaseReference(ConstExpr);
  UtlReleaseReference(UnitId);
  UtlReleaseReference(TypeId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPropertySpecifiers::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: PROPERTY not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiPropertySpecifiers::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());

  switch (Type)
  {
    case AdtType_INDEX:
    {
      write(pOutFile, "index ");

      if (ConstExpr != 0)
      {
        ConstExpr->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    case AdtType_READ:
    {
      write(pOutFile, "read ");

      if (Ident != 0)
      {
        Ident->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    case AdtType_WRITE:
    {
      write(pOutFile, "write ");

      if (Ident != 0)
      {
        Ident->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    case AdtType_STORED:
    {
      write(pOutFile, "stored ");

      if (Ident != 0)
      {
        Ident->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    case AdtType_DEFAULT:
    {
      write(pOutFile, "default ");

      if (ConstExpr != 0)
      {
        ConstExpr->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    case AdtType_NODEFAULT:
    {
      write(pOutFile, "nodefault ");
      break;
    }

    case AdtType_IMPLEMENTS:
    {
      write(pOutFile, "implements ");

      if (UnitId != 0)
      {
        UnitId->writeDelphi(pOutFile, nMode);
        write(pOutFile, ".");
      }

      if (TypeId != 0)
      {
        TypeId->writeDelphi(pOutFile, nMode);
      }
      break;
    }

    default:
    case AdtType_EMPTY:
    {
      break;
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiPropertySpecifiers, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiInterfaceType method implementations
//  ----------------------------------------------------------------------------
AdtDelphiInterfaceType::AdtDelphiInterfaceType(AdtParser* pIdentListObj,
                                               AdtParser* pClassMethodListObj,
                                               AdtParser* pClassPropertyListObj,
                                               const char* pComment)
 : AdtDelphiBase()
{
  initObject(IdentList,         pIdentListObj,          AdtDelphiIdentList,         true);
  initObject(ClassMethodList,   pClassMethodListObj,    AdtDelphiClassMethodList,   true);
  initObject(ClassPropertyList, pClassPropertyListObj,  AdtDelphiClassPropertyList, true);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtDelphiInterfaceType::AdtDelphiInterfaceType(const AdtDelphiInterfaceType& rCopy)
 : AdtDelphiBase(rCopy)
{
  copyObject(IdentList,         rCopy, AdtDelphiIdentList);
  copyObject(ClassMethodList,   rCopy, AdtDelphiClassMethodList);
  copyObject(ClassPropertyList, rCopy, AdtDelphiClassPropertyList);
}

//  ----------------------------------------------------------------------------

AdtDelphiInterfaceType::~AdtDelphiInterfaceType()
{
  UtlReleaseReference(IdentList);
  UtlReleaseReference(ClassMethodList);
  UtlReleaseReference(ClassPropertyList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiInterfaceType::writeFortran(AdtFile& pOutFile, int nMode) const
{
  ::printf("ERROR: INTERFACE not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  writePragmas(pOutFile);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiInterfaceType::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  writeExpanded(pOutFile, comment());
  write(pOutFile, "interface ");

  if (IdentList != 0)
  {
    write(pOutFile, "[");

    IdentList->writeDelphi(pOutFile, nMode);

    write(pOutFile, "] ");
  }

  pOutFile.incrementIndent();
  pOutFile.newline();

  if (ClassMethodList != 0)
  {
    ClassMethodList->writeDelphi(pOutFile, nMode);
  }

  if (ClassPropertyList != 0)
  {
    ClassPropertyList->writeDelphi(pOutFile, nMode);
  }

  pOutFile.decrementIndent();
  pOutFile.homeline();

  write(pOutFile, "end");

  pOutFile.newline();

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiInterfaceType, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiIdentList method implementations
//  ----------------------------------------------------------------------------
AdtDelphiIdentList::AdtDelphiIdentList(AdtParser* pIdentObj)
 : AdtDelphiBase()
{
  add(pIdentObj);
}

//  ----------------------------------------------------------------------------

AdtDelphiIdentList::AdtDelphiIdentList(const AdtDelphiIdentList& rCopy)
 : AdtDelphiBase(rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtDelphiIdentList::~AdtDelphiIdentList()
{

}

//  ----------------------------------------------------------------------------

void AdtDelphiIdentList::writeArrayBounds(AdtFile& pOutFile, int nMode, const char* pAbstractBounds) const
{
  AdtParserPtrListConstIter     Iter;
  size_t                        nSize = objList().size();
  int                           cn    = 0;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    cn++;

    if ((pObj != 0) && pObj->isType("AdtDelphiIdent"))
    {
      AdtDelphiIdent* pDelphiIdent = (AdtDelphiIdent*)pObj;

      pDelphiIdent->writeFortran(pOutFile, nMode);
      pDelphiIdent->writeArrayBounds(pOutFile, pAbstractBounds);

      if (cn != nSize)
      {
        write(pOutFile, ",");
      }
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiIdentList, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiIdent method implementations
//  ----------------------------------------------------------------------------
void AdtDelphiIdent::initialise(const char* pIdentifier)
{
  if (pIdentifier != 0)
  {
    const char* pComment        = 0;
    const char* pNext           = pIdentifier;
    int         nCommentLength  = 0;
    int         nIdentLength    = 0;
    bool        bContinue       = true;

    for ( ; (*pNext != 0) && bContinue ; pNext++)
    {
      switch (*pNext)
      {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        {
          //There should be only whitespace in between the ident name and the
          //comment so we can simply look for the comment open brace rather
          //than process the characters in between.
          for ( ; *pNext != 0 ; pNext++)
          {
            if (*pNext == '{')
            {
              pNext--;
              break;
            }
          }
          break;
        }

        case '{':
        {
          pComment  = pNext;
          bContinue = false;

          nCommentLength++;
          break;
        }

        default:
        {
          nIdentLength++;
          break;
        }
      }
    }

    for ( ; *pNext != 0 ; pNext++)
    {
      nCommentLength++;

      if (*pNext == '}')
      {
        break;
      }
    }

    string  Identifier(pIdentifier, 0, nIdentLength);

    name(Identifier);

    if (pComment != 0)
    {
      EmbeddedComment = string(pComment, 0, nCommentLength);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiIdent::enumerateArraySizes(AdtStringList& ArrayUpperBoundList, AdtStringList& ArrayLowerBoundList) const
{
  //This method is used to obtain the array size and lower bound. This is used
  //internally for determining how to do array slices.
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar           = sComment;
    const char* pDelimiters     = {":,}"};
    const char* pOpenBrackets   = {"(["};
    const char* pCloseBrackets  = {")]"};

    if (AdtParse::matchWord(pChar, "{"))
    {
      while (*pChar != '\0')
      {
        string sName;
        string sLowerBound;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::bracketedExtractWord(sName,
                                       pDelimiters,
                                       pOpenBrackets,
                                       pCloseBrackets,
                                       pChar);

        if (AdtParse::matchWord(pChar, ":"))
        {
          ArrayLowerBoundList.push_back(sName);

          //Take out the lower bound
          pChar = AdtParse::nextWord(pChar);

          AdtParse::bracketedExtractWord(sName,
                                         pDelimiters,
                                         pOpenBrackets,
                                         pCloseBrackets,
                                         pChar);
        }
        else
        {
          ArrayLowerBoundList.push_back("1");
        }

        pChar = AdtParse::nextWord(pChar);

        ArrayUpperBoundList.push_back(sName);

        if (!AdtParse::matchWord(pChar, ","))
        {
          break;
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiIdent::enumerateArraySizes(AdtStringByStringMap& ArraySizeMap) const
{
  //This method is used principally to create the parameters in the MODULE
  //that correspond to array size constants.
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar           = sComment;
    const char* pDelimiters     = {":,}"};
    const char* pOpenBrackets   = {"(["};
    const char* pCloseBrackets  = {")]"};

    if (AdtParse::matchWord(pChar, "{"))
    {
      while (*pChar != '\0')
      {
        string sName;
        string sLowerBound;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::bracketedExtractWord(sName,
                                       pDelimiters,
                                       pOpenBrackets,
                                       pCloseBrackets,
                                       pChar);

        enumerateArraySizesFromString(ArraySizeMap, sName);

        if (AdtParse::matchWord(pChar, ":"))
        {
          //Take out the lower bound
          pChar = AdtParse::nextWord(pChar);

          AdtParse::bracketedExtractWord(sName,
                                         pDelimiters,
                                         pOpenBrackets,
                                         pCloseBrackets,
                                         pChar);

          enumerateArraySizesFromString(ArraySizeMap, sName);
        }

        if (!AdtParse::matchWord(pChar, ","))
        {
          break;
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtDelphiIdent::enumerateArraySizesFromString(AdtStringByStringMap& ArraySizeMap, string& rText) const
{
  if (rText.length() > 0)
  {
    AdtExpressionCompiler Compiler;
    AdtStringList         DependencyList;

    Compiler.findDependencies(rText, DependencyList);

    for (AdtStringListConstIter Iter = DependencyList.begin() ; Iter != DependencyList.end() ; ++Iter)
    {
      const string& sName = *Iter;

      ArraySizeMap.insert(AdtStringByStringMap::value_type(sName, sName));
    }
  }
}

//  ----------------------------------------------------------------------------

AdtDelphiIdent::AdtDelphiIdent(const char* pIdentifier)
 : AdtDelphiBase(),
   EmbeddedComment()
{
  initialise(pIdentifier);
}

//  ----------------------------------------------------------------------------

AdtDelphiIdent::AdtDelphiIdent(const AdtDelphiIdent& rCopy)
 : AdtDelphiBase(rCopy),
   EmbeddedComment(rCopy.EmbeddedComment)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiIdent::~AdtDelphiIdent()
{

}

//  ----------------------------------------------------------------------------

void AdtDelphiIdent::writeArrayBounds(AdtFile& pOutFile, const char* pAbstractBounds) const
{
  //This method is used principally to create the variable definitions in the
  //MODULE and in function bodies. This method should therefore include the
  //lower bound attributes in the comment (if there is any).
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar           = sComment;
    const char* pDelimiters     = {":,}"};
    const char* pOpenBrackets   = {"(["};
    const char* pCloseBrackets  = {")]"};


    if (AdtParse::matchWord(pChar, "{"))
    {
      pOutFile.write("(");

      while (*pChar != '\0')
      {
        string  sName;
        char    sBuffer[32]    = {0};
        int     nLowerBound    = 1;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::bracketedExtractWord(sName,
                                       pDelimiters,
                                       pOpenBrackets,
                                       pCloseBrackets,
                                       pChar);

        if (AdtParse::matchWord(pChar, ":"))
        {
          if (sscanf(sName.c_str(), "%d", &nLowerBound) == 1)
          {
            if (nLowerBound != 1)
            {
              ::sprintf(sBuffer, "%d:", nLowerBound);

              pOutFile.write(sBuffer);
            }
          }
          else
          {
            pOutFile.write(sName);
            pOutFile.write(":");
          }

          pChar = AdtParse::nextWord(pChar);

          AdtParse::bracketedExtractWord(sName,
                                         pDelimiters,
                                         pOpenBrackets,
                                         pCloseBrackets,
                                         pChar);
        }

        pOutFile.write(sName);

        if (AdtParse::matchWord(pChar, ","))
        {
          pOutFile.write(",");
        }
        else
        {
          break;
        }
      }

      pOutFile.write(")");
    }
  }
  else if (pAbstractBounds != 0)
  {
    pOutFile.write(pAbstractBounds);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiIdent::writeFortran(AdtFile& pOutFile, int nMode) const
{
  writePragmas(pOutFile);

  if ((nMode              == FORTRAN_MODE_CLASS_EXTEND_NAME) &&
      (delphiRootObject() != 0))
  {
    delphiRootObject()->writeClassPrefix(pOutFile, name());
  }

  write(pOutFile, name().c_str());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiIdent, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeId method implementations
//  ----------------------------------------------------------------------------
AdtDelphiTypeId::AdtDelphiTypeId(const char* pTypeId)
 : AdtDelphiBase()
{
  name(pTypeId);
}

//  ----------------------------------------------------------------------------

AdtDelphiTypeId::AdtDelphiTypeId(const AdtDelphiTypeId& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiTypeId::~AdtDelphiTypeId()
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType AdtDelphiTypeId::blackBoxArgType(bool& bIsArray) const
{
  AdtBlackBoxArgType  nMappedType = AdtBlackBox_undefined;
  const char*         sDimension  = 0;
  const char*         sType       = 0;

  //We do this to map MB arrays into equivalent fortran ones
  if (delphiRootObject()->mapTypesToFortran(name(), sType, sDimension))
  {
    AdtBlackBoxArgType  pMappedTypes[]  = {AdtBlackBox_real, AdtBlackBox_integer, AdtBlackBox_integer, AdtBlackBox_boolean};
    const char*         pTypes[]        = {"REAL", "INTEGER", "UNSIGNED", "LOGICAL"};
    int                 nWhich          = AdtParse::matchWhichWord(sType, pTypes, sizeof(pTypes) / sizeof(pTypes[0]), false);

    if (nWhich >= 0)
    {
      nMappedType = pMappedTypes[nWhich];
      bIsArray    = true;
    }
  }

  return (nMappedType);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiTypeId, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiUnitId method implementations
//  ----------------------------------------------------------------------------
AdtDelphiUnitId::AdtDelphiUnitId(const char* pUnitId)
 : AdtDelphiBase()
{
  name(pUnitId);
}

//  ----------------------------------------------------------------------------

AdtDelphiUnitId::AdtDelphiUnitId(const AdtDelphiUnitId& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiUnitId::~AdtDelphiUnitId()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiUnitId, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelId method implementations
//  ----------------------------------------------------------------------------
AdtDelphiLabelId::AdtDelphiLabelId(const char* pLabelId)
 : AdtDelphiBase()
{
  name(pLabelId);
}

//  ----------------------------------------------------------------------------

AdtDelphiLabelId::AdtDelphiLabelId(const AdtDelphiLabelId& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiLabelId::~AdtDelphiLabelId()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiLabelId, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiNumber method implementations
//  ----------------------------------------------------------------------------
AdtDelphiNumber::AdtDelphiNumber(const char* pNumber, int nType)
 : AdtDelphiBase()
{
  name(pNumber);

  Type = (AdtType)nType;
}

//  ----------------------------------------------------------------------------

AdtDelphiNumber::AdtDelphiNumber(const AdtDelphiNumber& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtDelphiNumber::~AdtDelphiNumber()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiNumber, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiString method implementations
//  ----------------------------------------------------------------------------
AdtDelphiString::AdtDelphiString(const char* pString)
 : AdtDelphiBase()
{
  name(pString);
}

//  ----------------------------------------------------------------------------

AdtDelphiString::AdtDelphiString(const AdtDelphiString& rCopy)
 : AdtDelphiBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtDelphiString::~AdtDelphiString()
{

}

//  ----------------------------------------------------------------------------

implType(AdtDelphiString, AdtDelphiBase);


//  ----------------------------------------------------------------------------
//  AdtDelphiConstExpr method implementations
//  ----------------------------------------------------------------------------
AdtDelphiConstExpr::AdtDelphiConstExpr(const char* pConstExpr, int nType)
 : AdtDelphiBase()
{
  Type = (AdtType)nType;

  name(pConstExpr);
}

//  ----------------------------------------------------------------------------

AdtDelphiConstExpr::AdtDelphiConstExpr(const AdtDelphiConstExpr& rCopy)
 : AdtDelphiBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtDelphiConstExpr::~AdtDelphiConstExpr()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtDelphiConstExpr::writeFortranTypeDeclaration(AdtFile& pOutFile,
                                                         const string& rPrefix,
                                                         const AdtDelphiIdent* pIdent) const
{
  if (pIdent != 0)
  {
    switch (Type)
    {
      case AdtType_BOOL:
      {
        pOutFile.write("LOGICAL ");
        break;
      }

      case AdtType_INTEGER:
      {
        pOutFile.write("INTEGER ");
        break;
      }

      case AdtType_REAL:
      {
        pOutFile.write("REAL ");
        break;
      }

      case AdtType_TEXT:
      {
        pOutFile.write("CHARACTER ");
        break;
      }

      default:
      {
        FAIL();
      }
    }

    pOutFile.write(rPrefix.c_str());
    pIdent->writeFortran(pOutFile);
    pOutFile.newline();
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtDelphiConstExpr, AdtDelphiBase);
