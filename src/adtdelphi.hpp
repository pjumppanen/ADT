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
//    AdtDelphi.hpp
//
//  Purpose:
//    This file includes declarations of classes used to collate information
//    describing the delphi file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTDELPHI_HPP
#define __ADTDELPHI_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void  adtDelphi_setTypeScope(void* pIdent);
C_FUNCTION void  adtDelphi_clearTypeScope();
C_FUNCTION void* adtDelphi_setRoot(void* pRoot);
C_FUNCTION void* adtDelphi_getRoot(void);
C_FUNCTION void  adtDelphi_releaseRoot(void);
C_FUNCTION void  adtDelphi_releaseObject(void* pObj);
C_FUNCTION void* adtDelphiList_add(void* pList, void* pObj);
C_FUNCTION void* adtDelphiGoal_create(void* pObj);
C_FUNCTION void* adtDelphiMacro_create(void* pIdentObj, void* pExprListObj, void* pExpressionObj, void* pStmtListObj, void* pVarDeclListObj);
C_FUNCTION void* adtDelphiProgram_create(void* pIdentObj, void* pIdentListObj, void* pUsesClauseObj, void* pBlockObj, const char* pComment);
C_FUNCTION void* adtDelphiUnit_create(void* pIdentObj, void* pInterfaceSectionObj, void* pImplementationSectionObj, void* pInitSectionObj, const char* pComment);
C_FUNCTION void* adtDelphiPackage_create(void* pIdentObj, void* pRequiresIdentListObj, void* pContainsIdentListObj, const char* pComment);
C_FUNCTION void* adtDelphiLibrary_create(void* pIdentObj, void* pUsesClauseObj, void* pBlockObj, const char* pComment);
C_FUNCTION void* adtDelphiUsesClause_create(void* pIdentListObj, const char* pComment);
C_FUNCTION void* adtDelphiInterfaceSection_create(void* pUsesClauseObj, void* pConstSectionObj, void* pTypeSectionObj, void* pVarSectionObj, void* pExportedHeadingListObj, const char* pComment);
C_FUNCTION void* adtDelphiExportedHeadingList_create(void* pExportedHeadingObj);
C_FUNCTION void* adtDelphiExportedHeading_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pDirectiveListObj, const char* pComment);
C_FUNCTION void* adtDelphiImplementationSection_create(void* pUsesClauseObj, void* pDeclSectionObj, const char* pComment);
C_FUNCTION void* adtDelphiBlock_create(void* pDeclSectionObj, void* pCompoundStmtObj, const char* pComment);
C_FUNCTION void* adtDelphiDeclSection_create(void* pLabelDeclSectionObj, void* pConstSectionObj, void* pTypeSectionObj, void* pVarSectionObj, void* pProcedureDeclSectionObj, const char* pComment);
C_FUNCTION void* adtDelphiLabelDeclSection_create(void* pLabelDeclListObj);
C_FUNCTION void* adtDelphiLabelDeclList_create(void* pLabelDeclObj);
C_FUNCTION void* adtDelphiLabelDecl_create(void* pLabelIdObj, const char* pComment);
C_FUNCTION void* adtDelphiConstSection_create(void* pConstantDeclListObj, const char* pComment);
C_FUNCTION void* adtDelphiConstantDeclList_create(void* pConstantDeclObj);
C_FUNCTION void* adtDelphiConstantDecl_create(void* pIdentObj, void* pTypeIdObj, void* pUnitIdObj, void* pConstExprObj, void* pTypedConstantObj);
C_FUNCTION void* adtDelphiTypeSection_create(void* pTypeDeclListObj, const char* pComment);
C_FUNCTION void* adtDelphiTypeDeclList_create(void* pTypeDeclObj);
C_FUNCTION void* adtDelphiTypeDecl_create(void* pIdentObj, void* pTypeObj, void* pRestrictedTypeObj);
C_FUNCTION void* adtDelphiTypedConstant_create(void* pConstExprObj, void* pArrayConstantObj, void* pRecordConstantObj);
C_FUNCTION void* adtDelphiArrayConstant_create(void* pTypedConstantListObj);
C_FUNCTION void* adtDelphiTypedConstantList_create(void* pTypedConstantObj);
C_FUNCTION void* adtDelphiRecordConstant_create(void* pRecordFieldConstantListObj);
C_FUNCTION void* adtDelphiRecordFieldConstantList_create(void* pRecordFieldConstantObj);
C_FUNCTION void* adtDelphiRecordFieldConstant_create(void* pIdentObj, void* pTypedConstantObj);
C_FUNCTION void* adtDelphiType_create(void* pTypeIdObj, void* pUnitIdObj, void* pSimpleTypeObj, void* pStructTypeObj, void* pPointerTypeObj, void* pStringTypeObj, void* pProcedureTypeObj, void* pVariantTypeObj, void* pClassRefTypeObj);
C_FUNCTION void* adtDelphiRestrictedType_create(void* pObjectTypeObj, void* pClassTypeObj, void* pInterfaceTypeObj);
C_FUNCTION void* adtDelphiClassRefType_create(void* pTypeIdObj, void* pUnitIdObj);
C_FUNCTION void* adtDelphiSimpleType_create(void* pOrdinalTypeObj, void* pRealTypeObj);
C_FUNCTION void* adtDelphiRealType_create(int nType);
C_FUNCTION void* adtDelphiOrdinalType_create(void* pSubrangeTypeObj, void* pEnumeratedTypeObj, void* pOrdIdentObj);
C_FUNCTION void* adtDelphiOrdIdent_create(int nType);
C_FUNCTION void* adtDelphiVariantType_create(int nType);
C_FUNCTION void* adtDelphiSubrangeType_create(void* pFromConstExprObj, void* pToConstExprObj);
C_FUNCTION void* adtDelphiEnumeratedType_create(void* pEnumeratedTypeElementListObj);
C_FUNCTION void* adtDelphiEnumeratedTypeElementList_create(void* pEnumeratedTypeElementObj);
C_FUNCTION void* adtDelphiEnumeratedTypeElement_create(void* pIdentObj, void* pConstExprObj);
C_FUNCTION void* adtDelphiStringType_create(int nType, void* pConstExprObj);
C_FUNCTION void* adtDelphiStructType_create(int bIsPacked, void* pArrayTypeObj, void* pSetTypeObj, void* pFileTypeObj, void* pRecTypeObj);
C_FUNCTION void* adtDelphiArrayType_create(void* pOrdinalTypeListObj, void* pTypeObj);
C_FUNCTION void* adtDelphiOrdinalTypeList_create(void* pOrdinalTypeObj);
C_FUNCTION void* adtDelphiRecType_create(void* pFieldDeclListObj, void* pVariantSectionListObj);
C_FUNCTION void* adtDelphiFieldDeclList_create(void* pFieldDeclObj);
C_FUNCTION void* adtDelphiFieldDecl_create(void* pIdentListObj, void* pTypeObj);
C_FUNCTION void* adtDelphiVariantSectionList_create(void* pVariantSectionObj);
C_FUNCTION void* adtDelphiVariantSection_create(void* pIdentObj, void* pUnitIdObj, void* pTypeIdObj, void* pRecVariantObj);
C_FUNCTION void* adtDelphiRecVariant_create(void* pConstExprListObj, void* pFieldDeclListObj, void* pVariantSectionListObj);
C_FUNCTION void* adtDelphiConstExprList_create(void* pConstExprObj);
C_FUNCTION void* adtDelphiSetType_create(void* pOrdinalTypeObj);
C_FUNCTION void* adtDelphiFileType_create(void* pUnitIdObj, void* pTypeIdObj);
C_FUNCTION void* adtDelphiPointerType_create(void* pUnitIdObj, void* pTypeIdObj);
C_FUNCTION void* adtDelphiProcedureType_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, int bOfObject);
C_FUNCTION void* adtDelphiVarSection_create(void* pVarDeclListObj, const char* pComment);
C_FUNCTION void* adtDelphiVarDeclList_create(void* pVarDeclObj);
C_FUNCTION void* adtDelphiVarDecl_create(void* pIdentListObj, void* pTypeObj, void* pIdentObj, void* pConstExprObj, int nAbsolute);
C_FUNCTION void* adtDelphiExpression_create(void* pExpressionRelOpListObj);
C_FUNCTION void* adtDelphiExpressionRelOpList_create(void* pExpressionRelOpObj);
C_FUNCTION void* adtDelphiExpressionRelOp_create(int nRelOp, void* pSimpleExpressionObj);
C_FUNCTION void* adtDelphiSimpleExpression_create(void* pSimpleExpressionAddOpListObj);
C_FUNCTION void* adtDelphiSimpleExpressionAddOpList_create(void* pSimpleExpressionAddOpObj);
C_FUNCTION void* adtDelphiSimpleExpressionAddOp_create(int nAddOp, int nSign, void* pTermObj);
C_FUNCTION void* adtDelphiTerm_create(void* pFactorMulOpListObj);
C_FUNCTION void* adtDelphiFactorMulOpList_create(void* pFactorMulOpObj);
C_FUNCTION void* adtDelphiFactorMulOp_create(int nMulOp, void* pFactorObj);
C_FUNCTION void* adtDelphiFactor_create(void* pDesignatorObj, int bHasAt, void* pNumberObj, void* pStringObj, int bHasNil, void* pExpressionObj, void* pFactorObj, void* pSetConstructorObj, void* pSizeofTypeObj, void* pCastExpressionObj);
C_FUNCTION void* adtDelphiCastExpression_create(void* pOrdIdentObj, void* pRealTypeObj, void* pExpressionObj);
C_FUNCTION void* adtDelphiDesignator_create(void* pDesignatorObjListObj);
C_FUNCTION void* adtDelphiDesignatorObjList_create(void* pDesignatorObj);
C_FUNCTION void* adtDelphiDesignatorObj_create(void* pIdentObj,  void* pExprListObj, void* pDesignatorRefListObj, int bEmptyParenthesis, int bInherited);
C_FUNCTION void* adtDelphiDesignatorRefList_create(void* pDesignatorRefObj);
C_FUNCTION void* adtDelphiDesignatorRef_create(void* pExprListObj);
C_FUNCTION void* adtDelphiSetConstructor_create(void* pSetElementListObj);
C_FUNCTION void* adtDelphiSetElementList_create(void* pSetElementObj);
C_FUNCTION void* adtDelphiSetElement_create(void* pExpressionObj, void* pEndExpressionObj);
C_FUNCTION void* adtDelphiExprList_create(void* pExprObj);
C_FUNCTION void* adtDelphiStatement_create(void* pLabelIdObj, void* pExitStatementObj, void* pSimpleStatementObj, void* pCompoundStmtObj, void* pIfStmtObj, void* pCaseStmtObj, void* pRepeatStmtObj, void* pWhileStmtObj, void* pForStmtObj, void* pWithStmtObj, const char* pComment);
C_FUNCTION void* adtDelphiStmtList_create(void* pStmtObj);
C_FUNCTION void* adtDelphiExitStatement_create(int nWithParenthesis);
C_FUNCTION void* adtDelphiSimpleStatement_create(void* pDesignatorObj, void* pExpressionObj, void* pSizeofTypeObj, void* pIdentObj, void* pExprListObj, void* pLabelIdObj, void* pCastExpressionObj, int nInherited, int nOpType);
C_FUNCTION void* adtDelphiSizeofType_create(void* pOrdIdentObj, void* pRealTypeObj, void* pVariantTypeObj, void* pDesignatorObj);
C_FUNCTION void* adtDelphiCompoundStmt_create(void* pStmtListObj);
C_FUNCTION void* adtDelphiIfStmt_create(void* pExpressionObj, void* pThenStatementObj, void* pElseStatementObj);
C_FUNCTION void* adtDelphiCaseStmt_create(void* pExpressionObj, void* pCaseSelectorListObj, void* pStmtListObj);
C_FUNCTION void* adtDelphiCaseSelectorList_create(void* pCaseSelectorObj);
C_FUNCTION void* adtDelphiCaseSelector_create(void* pCaseLabelListObj, void* pStatementObj);
C_FUNCTION void* adtDelphiCaseLabelList_create(void* pCaseLabelObj);
C_FUNCTION void* adtDelphiCaseLabel_create(void* pConstExprObj, void* pToConstExprObj);
C_FUNCTION void* adtDelphiRepeatStmt_create(void* pStatementObj, void* pExpressionObj, void* pStmtListObj);
C_FUNCTION void* adtDelphiWhileStmt_create(void* pExpressionObj, void* pStatementObj);
C_FUNCTION void* adtDelphiForStmt_create(void* pUnitIdObj, void* pIdentObj, void* pFromExpressionObj, void* pToExpressionObj, void* pStatementObj, int nDownTo);
C_FUNCTION void* adtDelphiWithStmt_create(void* pDesignatorObj, void* pStatementObj);
C_FUNCTION void* adtDelphiProcedureDeclSection_create(void* pProcedureDeclListObj);
C_FUNCTION void* adtDelphiProcedureDeclList_create(void* pProcedureDeclObj);
C_FUNCTION void* adtDelphiProcedureDecl_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pConstructorHeadingObj, void* pDestructorHeadingObj, void* pDirectiveListObj, void* pBlockObj);
C_FUNCTION void* adtDelphiFunctionHeading_create(void* pClassIdentObj, void* pFunctionIdentObj, void* pFormalParametersObj, void* pSimpleTypeObj, void* pTypeIdObj, const char* pComment);
C_FUNCTION void* adtDelphiProcedureHeading_create(void* pClassIdentObj, void* pProcedureIdentObj, void* pFormalParametersObj, const char* pComment);
C_FUNCTION void* adtDelphiFormalParameters_create(void* pFormalParamListObj);
C_FUNCTION void* adtDelphiFormalParamList_create(void* pFormalParamObj);
C_FUNCTION void* adtDelphiFormalParam_create(int nType, void* pParameterObj);
C_FUNCTION void* adtDelphiParameter_create(void* pIdentListObj, void* pSimpleTypeObj, void* pTypeIdObj, void* pConstExprObj, void* pIdentObj, int bIsArray, int nOfString, int nOfFile);
C_FUNCTION void* adtDelphiDirective_create(int nType);
C_FUNCTION void* adtDelphiDirectiveList_create(void* pDirectiveObj);
C_FUNCTION void* adtDelphiObjectType_create(void* pUnitIdObj, void* pIdentObj, void* pObjFieldListObj, void* pMethodListObj);
C_FUNCTION void* adtDelphiMethodList_create(void* pMethodObj);
C_FUNCTION void* adtDelphiMethod_create(void* pProcedureHeadingObj, void* pFunctionHeadingObj, void* pConstructorHeadingObj, void* pDestructorHeadingObj, void* pDirectiveListObj);
C_FUNCTION void* adtDelphiConstructorHeading_create(void* pClassIdentObj, void* pMethodIdentObj, void* pFormalParametersObj, const char* pComment);
C_FUNCTION void* adtDelphiDestructorHeading_create(void* pClassIdentObj, void* pMethodIdentObj, void* pFormalParametersObj, const char* pComment);
C_FUNCTION void* adtDelphiObjFieldList_create(void* pObjFieldObj);
C_FUNCTION void* adtDelphiObjField_create(void* pIdentListObj, void* pTypeObj);
C_FUNCTION void* adtDelphiInitSection_create(void* pStmtListObj, void* pFinalStmtListObj, int bHasInit, const char* pComment);
C_FUNCTION void* adtDelphiClassType_create(void* pIdentListObj, void* pClassFieldListObj, void* pClassMethodListObj, void* pClassPropertyListObj);
C_FUNCTION void* adtDelphiClassFieldList_create(void* pClassFieldObj);
C_FUNCTION void* adtDelphiClassField_create(int nVisibility, void* pObjFieldObj);
C_FUNCTION void* adtDelphiClassMethodList_create(void* pClassMethodObj);
C_FUNCTION void* adtDelphiClassMethod_create(int nVisibility, void* pMethodObj);
C_FUNCTION void* adtDelphiClassPropertyList_create(void* pClassPropertyObj);
C_FUNCTION void* adtDelphiClassProperty_create(int nVisibility, void* pPropertyObj);
C_FUNCTION void* adtDelphiProperty_create(void* pClassIdentObj, void* pIdentObj, void* pPropertyParameterListObj, void* pPropertySpecifiersObj);
C_FUNCTION void* adtDelphiPropertyParameterList_create(void* pPropertyParameterObj);
C_FUNCTION void* adtDelphiPropertyParameter_create(void* pIdentListObj, void* pUnitIdObj, void* pTypeIdObj);
C_FUNCTION void* adtDelphiPropertySpecifiers_create(int nType, void* pIdentObj, void* pConstExprObj, void* pUnitIdObj, void* pTypeIdObj);
C_FUNCTION void* adtDelphiInterfaceType_create(void* pIdentListObj, void* pClassMethodListObj, void* pClassPropertyListObj, const char* pComment);
C_FUNCTION void* adtDelphiIdentList_create(void* pIdentObj);
C_FUNCTION void* adtDelphiIdent_create(const char* pIdentifier);
C_FUNCTION void* adtDelphiTypeId_create(const char* pTypeId);
C_FUNCTION void* adtDelphiUnitId_create(const char* pUnitId);
C_FUNCTION void* adtDelphiLabelId_create(const char* pLabelId);
C_FUNCTION void* adtDelphiNumber_create(const char* pNumber, int nType);
C_FUNCTION void* adtDelphiString_create(const char* pString);
C_FUNCTION void* adtDelphiConstExpr_create(const char* pConstExpr, int nType);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"
#include "adtblackbox.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtDelphiGoal;
class AdtDelphiProgram;
class AdtDelphiPackage;
class AdtDelphiLibrary;
class AdtDelphiUnit;
class AdtDelphiIdent;
class AdtDelphiIdentList;
class AdtDelphiUsesClause;
class AdtDelphiBlock;
class AdtDelphiInterfaceSection;
class AdtDelphiImplementationSection;
class AdtDelphiInitSection;
class AdtDelphiRequiresClause;
class AdtDelphiContainsClause;
class AdtDelphiConstSection;
class AdtDelphiTypeSection;
class AdtDelphiVarSection;
class AdtDelphiExportedHeadingList;
class AdtDelphiExportedHeading;
class AdtDelphiProcedureHeading;
class AdtDelphiFunctionHeading;
class AdtDelphiDirective;
class AdtDelphiDirectiveList;
class AdtDelphiDeclSection;
class AdtDelphiCompoundStmt;
class AdtDelphiLabelDeclSection;
class AdtDelphiProcedureDeclSection;
class AdtDelphiLabelDeclList;
class AdtDelphiLabelDecl;
class AdtDelphiConstantDeclList;
class AdtDelphiConstantDecl;
class AdtDelphiTypeDeclList;
class AdtDelphiTypeDecl;
class AdtDelphiLabelId;
class AdtDelphiTypeId;
class AdtDelphiUnitId;
class AdtDelphiConstExpr;
class AdtDelphiType;
class AdtDelphiRestrictedType;
class AdtDelphiTypedConstant;
class AdtDelphiArrayConstant;
class AdtDelphiTypedConstantList;
class AdtDelphiRecordConstant;
class AdtDelphiRecordFieldConstantList;
class AdtDelphiRecordFieldConstant;
class AdtDelphiSimpleType;
class AdtDelphiStructType;
class AdtDelphiPointerType;
class AdtDelphiStringType;
class AdtDelphiProcedureType;
class AdtDelphiVariantType;
class AdtDelphiClassRefType;
class AdtDelphiObjectType;
class AdtDelphiClassType;
class AdtDelphiOrdinalType;
class AdtDelphiRealType;
class AdtDelphiInterfaceType;
class AdtDelphiSubrangeType;
class AdtDelphiEnumeratedType;
class AdtDelphiOrdIdent;
class AdtDelphiEnumeratedTypeElementList;
class AdtDelphiEnumeratedTypeElement;
class AdtDelphiArrayType;
class AdtDelphiSetType;
class AdtDelphiFileType;
class AdtDelphiRecType;
class AdtDelphiOrdinalTypeList;
class AdtDelphiFieldDeclList;
class AdtDelphiFieldDecl;
class AdtDelphiVariantSectionList;
class AdtDelphiVariantSection;
class AdtDelphiRecVariant;
class AdtDelphiConstExprList;
class AdtDelphiVarDeclList;
class AdtDelphiExpressionRelOpList;
class AdtDelphiSimpleExpression;
class AdtDelphiSimpleExpressionAddOpList;
class AdtDelphiTerm;
class AdtDelphiFactorMulOpList;
class AdtDelphiFactor;
class AdtDelphiDesignator;
class AdtDelphiNumber;
class AdtDelphiString;
class AdtDelphiSetConstructor;
class AdtDelphiSizeofType;
class AdtDelphiDesignatorObjList;
class AdtDelphiExprList;
class AdtDelphiExpression;
class AdtDelphiStmtList;
class AdtDelphiDesignatorRefList;
class AdtDelphiSetElementList;
class AdtDelphiExitStatement;
class AdtDelphiSimpleStatement;
class AdtDelphiIfStmt;
class AdtDelphiCaseStmt;
class AdtDelphiRepeatStmt;
class AdtDelphiWhileStmt;
class AdtDelphiForStmt;
class AdtDelphiWithStmt;
class AdtDelphiCaseSelectorList;
class AdtDelphiCaseSelector;
class AdtDelphiCaseLabelList;
class AdtDelphiCaseLabel;
class AdtDelphiProcedureDeclList;
class AdtDelphiProcedureDecl;
class AdtDelphiConstructorHeading;
class AdtDelphiDestructorHeading;
class AdtDelphiFunctionHeading;
class AdtDelphiDirective;
class AdtDelphiFormalParameters;
class AdtDelphiFormalParamList;
class AdtDelphiFormalParam;
class AdtDelphiVarDecl;
class AdtDelphiParameter;
class AdtDelphiObjFieldList;
class AdtDelphiMethodList;
class AdtDelphiClassFieldList;
class AdtDelphiClassMethodList;
class AdtDelphiClassPropertyList;
class AdtDelphiProperty;
class AdtDelphiPropertyParameterList;
class AdtDelphiPropertySpecifiers;
class AdtDelphiCastExpression;

//  ----------------------------------------------------------------------------

enum  AdtVisibility{AdtVisibility_PUBLIC    = 1,
                    AdtVisibility_PROTECTED = 2,
                    AdtVisibility_PRIVATE   = 3,
                    AdtVisibility_PUBLISHED = 4,
                    AdtVisibility_EMPTY     = 0};


//  ----------------------------------------------------------------------------
//  AdtDelphiToFortranTypeConversion class
//  ----------------------------------------------------------------------------
//  This class is used in conjunction with a map to maintain a substitution
//  mapping from delphi complex types to equivalent fortran ones (ie. MB's
//  arrays mapped into fortran equivalents).
//  ----------------------------------------------------------------------------
class AdtDelphiToFortranTypeConversion
{
public:
  string  DelphiType;
  string  FortranType;
  string  FortranDimension;
  string  FortranDimensionString;

private:
  void    initialise();

public:
  AdtDelphiToFortranTypeConversion();
  AdtDelphiToFortranTypeConversion(const char* pDelphiType,
                                   const char* pFortranType,
                                   const char* pFortranDimension);
  AdtDelphiToFortranTypeConversion(const AdtDelphiToFortranTypeConversion& rCopy);
  virtual ~AdtDelphiToFortranTypeConversion();
};

//  ----------------------------------------------------------------------------

inline AdtDelphiToFortranTypeConversion::AdtDelphiToFortranTypeConversion()
 : DelphiType(),
   FortranType(),
   FortranDimension(),
   FortranDimensionString()
{

}

//  ----------------------------------------------------------------------------

inline AdtDelphiToFortranTypeConversion::AdtDelphiToFortranTypeConversion(const char* pDelphiType,
                                                                          const char* pFortranType,
                                                                          const char* pFortranDimension)
 : DelphiType(pDelphiType),
   FortranType(pFortranType),
   FortranDimension(pFortranDimension),
   FortranDimensionString()
{
  initialise();
}

//  ----------------------------------------------------------------------------

inline AdtDelphiToFortranTypeConversion::AdtDelphiToFortranTypeConversion(const AdtDelphiToFortranTypeConversion& rCopy)
 : DelphiType(rCopy.DelphiType),
   FortranType(rCopy.FortranType),
   FortranDimension(rCopy.FortranDimension),
   FortranDimensionString(rCopy.FortranDimensionString)
{

}

//  ----------------------------------------------------------------------------

inline AdtDelphiToFortranTypeConversion::~AdtDelphiToFortranTypeConversion()
{
  //Do nothing
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtDelphiToFortranTypeConversion by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtDelphiToFortranTypeConversion>                       AdtDelphiToFortranTypeConversionStringPair;
typedef std::map<string, AdtDelphiToFortranTypeConversion, string_less>                 AdtDelphiToFortranTypeConversionByStringMap;
typedef std::map<string, AdtDelphiToFortranTypeConversion, string_less>::iterator       AdtDelphiToFortranTypeConversionByStringMapIter;
typedef std::map<string, AdtDelphiToFortranTypeConversion, string_less>::const_iterator AdtDelphiToFortranTypeConversionByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  These class definitions map 1:1 to the grammar rules for the parser
//  ----------------------------------------------------------------------------
class AdtDelphiBase : public AdtParser
{
protected:
  static const char*                                  TypeScope;
  static AdtDelphiGoal*                               DelphiRootObject;
  static AdtDelphiToFortranTypeConversionByStringMap  FortranTypeMap;
  static AdtDelphiToFortranTypeConversionByStringMap  DelphiTypeMap;

protected:
  AdtFile&                      forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                      forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                      forAllWriteDelphi(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false) const;
  AdtFile&                      writePragmas(AdtFile& rOutFile) const;

public:
  AdtDelphiBase();
  AdtDelphiBase(const AdtDelphiBase& rCopy);
  virtual ~AdtDelphiBase();

  static void                   addFortranTypeMap(const string& rDelphiType,
                                                  const string& rFortranType,
                                                  const string& rFortranSize);

  static void                   typeScope(AdtParser* pIdent);
  static const char*            typeScope();

  static void                   delphiRootObject(AdtParser* pRoot);
  static AdtDelphiGoal*         delphiRootObject();

  static bool                   mapTypesToFortran(const char* pTypeName,
                                                  const char*& pType,
                                                  const char*& pDimension);

  static bool                   mapTypesToDelphi(const char* pTypeName,
                                                 size_t nDimension,
                                                 const char*& pType);

  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtDelphiBase::AdtDelphiBase(const AdtDelphiBase& rCopy)
 : AdtParser(rCopy)
{

}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiBase::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiBase::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiBase::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}


//  ----------------------------------------------------------------------------
//  Goal class
//  ----------------------------------------------------------------------------
class AdtDelphiGoal : public AdtDelphiBase, public AdtSourceRoot
{
private:
  AdtDelphiProgram*             Program;
  AdtDelphiPackage*             Package;
  AdtDelphiLibrary*             Library;
  AdtDelphiUnit*                Unit;

  AdtParserPtrByStringMap       ExportedVariableMap;
  AdtParserPtrByStringMap       ExportedTypeMap;
  AdtParserPtrByStringMap       ExportedConstMap;
  AdtParserPtrByStringMap       ExportedProcedureMap;

  AdtParserPtrByStringMap       LocalVariableMap;
  AdtParserPtrByStringMap       LocalTypeMap;
  AdtParserPtrByStringMap       LocalConstMap;
  AdtParserPtrByStringMap       ImplementedProcedureMap;

protected:
  bool                          findConst(const char* pName, const AdtParser*& pExternal) const;
  bool                          findVar(const char* pName, const AdtParser*& pExternal) const;
  bool                          findProc(const char* pName, const char* pClassName, const AdtParser*& pExternal, string& rMatchName) const;
  bool                          findField(const char* pName, const char* pClassName, const AdtParser*& pExternal) const;

  bool                          isClassType(const AdtParserPtrByStringMap& rMap,
                                            const char* pClassName,
                                            AdtDelphiClassType** ppClassTypeObj = 0) const;

  void                          buildMacroMap(AdtParserPtrByStringMultiMap& rMacroMap) const;

  void                          addDimensionVars(const char* pClassName,
                                                 AdtParserPtrByStringMap& rVarsMap) const;

  bool                          compile(const AdtDelphiProcedureDecl* pProcedureDecl,
                                        AdtParserPtrByStringMap& rProceduresMap,
                                        AdtParserPtrByStringMap& rVarsMap,
                                        AdtParserPtrByStringMap& rConstMap,
                                        bool bExpandMacros) const;

  void                          writeArraySizes(AdtFile& pOutFile,
                                                const AdtParserPtrByStringMap& rProceduresMap,
                                                const AdtParserPtrByStringMap& rVarsMap,
                                                const AdtParserPtrByStringMap& rConstMap) const;

  AdtFile&                      writeFortran(AdtFile& pOutFile,
                                             const AdtFortranExecutableProgram* pSavedRoot,
                                             const char* pClassName,
                                             const char* pLastClassName,
                                             const char* pFunctionNames,
                                             bool bExpandMacros) const;

  void                          extractClassConstructorName(const char* pConstructorDeclaration,
                                                            string& rConstructorName) const;

public:
  AdtDelphiGoal(AdtParser* pObj);
  AdtDelphiGoal(const AdtDelphiGoal& rCopy);
  virtual ~AdtDelphiGoal();

  bool                          writeClassPrefix(AdtFile& pOutFile, const char* pFunctionName) const;

  virtual void                  enumerateMethodNames(AdtStringList& rMethodList) const;

  virtual bool                  hasClass(const char* pClassName,
                                         string& rParentClassName) const;

  virtual bool                  buildBlackBoxFile(const char* pBlackBoxFileName,
                                                  AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                  AdtStringByStringMap& rRegardAsClassSubroutineMap);

  virtual bool                  flattenClass(const char* pClassName,
                                             const AdtParserPtrList& rGoalList,
                                             string& rUsesList);

  virtual bool                  optimise(const AdtStringList& rNewMethodList,
                                         const AdtStringByStringMap& rNewMethodMap);

  virtual bool                  expandMacros();

  const AdtDelphiProcedureDecl* findProcedureDeclaration(const char* pFunctionName) const;

  virtual AdtFile&              writeClassMethodsAsFortran(AdtFile& pOutFile,
                                                           const AdtFortranExecutableProgram* pSavedRoot,
                                                           const char* pClassName,
                                                           const char* pLastClassName,
                                                           bool bExpandMacros) const;

  AdtFile&                      writeDelphi(AdtFile& pOutFile, const char* pFunctionName) const;
  AdtFile&                      writeDelphi(AdtFile& pOutFile) const;

  virtual AdtFile&              writeNative(AdtFile& pOutFile) const;

  virtual bool                  extractClassConstructors(AdtStringList& rConstructorList,
                                                         const char* pClassName,
                                                         const char* pParentClassName,
                                                         AdtSourceFileType nAsFileType) const;

  bool                          isProcedure(const char* pProcedureName) const;
  bool                          isFunction(const char* pProcedureName) const;
  bool                          isClassType(const char* pClassName) const;
  const AdtDelphiClassType*     findClassType(const char* pClassName) const;

  virtual AdtSourceFileType     sourceFileType() const;

  declListType(AdtDelphiMacro);
  declType;
};


//  ----------------------------------------------------------------------------
//  Program class
//  ----------------------------------------------------------------------------
class AdtDelphiProgram : public AdtDelphiBase
{
private:
  AdtDelphiIdent*       Identifier;
  AdtDelphiIdentList*   IdentifierList;
  AdtDelphiUsesClause*  UsesClause;
  AdtDelphiBlock*       Block;

public:
  AdtDelphiProgram(AdtParser* pIdentObj,
                   AdtParser* pIdentListObj,
                   AdtParser* pUsesClauseObj,
                   AdtParser* pBlockObj,
                   const char* pComment);

  AdtDelphiProgram(const AdtDelphiProgram& rCopy);
  virtual ~AdtDelphiProgram();

  virtual AdtFile&         writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  Unit class
//  ----------------------------------------------------------------------------
class AdtDelphiUnit : public AdtDelphiBase
{
private:
  AdtDelphiIdent*                 Identifier;
  AdtDelphiInterfaceSection*      InterfaceSection;
  AdtDelphiImplementationSection* ImplementationSection;
  AdtDelphiInitSection*           InitSection;

public:
  AdtDelphiUnit(AdtParser* pIdentObj,
                AdtParser* pInterfaceSectionObj,
                AdtParser* pImplementationSectionObj,
                AdtParser* pInitSectionObj,
                const char* pComment);

  AdtDelphiUnit(const AdtDelphiUnit& rCopy);
  virtual ~AdtDelphiUnit();

  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  Package class
//  ----------------------------------------------------------------------------
class AdtDelphiPackage : public AdtDelphiBase
{
private:
  AdtDelphiIdent*     Identifier;
  AdtDelphiIdentList* RequiresIdentList;
  AdtDelphiIdentList* ContainsIdentList;

public:
  AdtDelphiPackage(AdtParser* pIdentObj,
                   AdtParser* pRequiresIdentListObj,
                   AdtParser* pContainsIdentListObj,
                   const char* pComment);

  AdtDelphiPackage(const AdtDelphiPackage& rCopy);
  virtual ~AdtDelphiPackage();

  virtual AdtFile&         writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  Library class
//  ----------------------------------------------------------------------------
class AdtDelphiLibrary : public AdtDelphiBase
{
private:
  AdtDelphiIdent*       Identifier;
  AdtDelphiUsesClause*  UsesClause;
  AdtDelphiBlock*       Block;

public:
  AdtDelphiLibrary(AdtParser* pIdentObj,
                   AdtParser* pUsesClauseObj,
                   AdtParser* pBlockObj,
                   const char* pComment);

  AdtDelphiLibrary(const AdtDelphiLibrary& rCopy);
  virtual ~AdtDelphiLibrary();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  Macro class
//  ----------------------------------------------------------------------------
class AdtDelphiMacro : public AdtDelphiBase
{
private:
  AdtDelphiIdent*       Identifier;
  AdtDelphiExprList*    ExprList;
  AdtDelphiExpression*  Expression;
  AdtDelphiStmtList*    StmtList;
  AdtDelphiVarDeclList* VarDeclList;
  AdtDelphiDesignator*  Designator;

protected:
  void                  substituteArguments(AdtParser* pObj, AdtDelphiExprList* pMacroParamList) const;
  void                  expandMacro(AdtParser* pRoot, AdtDelphiExprList* pMacroArgList) const;
  void                  addVariables(AdtDelphiProcedureDecl* pProcedureDecl) const;
  AdtParser*            findCollapsedMacroRoot(AdtParser* pObject, AdtDelphiExprList** ppExpressionList = 0) const;

public:
  AdtDelphiMacro(AdtParser* pIdentObj,
                 AdtParser* pExprListObj,
                 AdtParser* pExpressionObj,
                 AdtParser* pStmtListObj,
                 AdtParser* pVarDeclListObj);

  AdtDelphiMacro(const AdtDelphiMacro& rCopy);
  virtual ~AdtDelphiMacro();

  static void           forwardSubstitute(AdtDelphiProcedureDecl* pProcedureDecl,
                                          AdtParserPtrByStringMultiMap& rMacroMap);

  declType;
};


//  ----------------------------------------------------------------------------
//  UsesClause class
//  ----------------------------------------------------------------------------
class AdtDelphiUsesClause : public AdtDelphiBase
{
private:
  AdtDelphiIdentList* IdentifierList;

public:
  AdtDelphiUsesClause(AdtParser* pIdentListObj,
                      const char* pComment);

  AdtDelphiUsesClause(const AdtDelphiUsesClause& rCopy);
  virtual ~AdtDelphiUsesClause();

  virtual AdtFile&       writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  InterfaceSection class
//  ----------------------------------------------------------------------------
class AdtDelphiInterfaceSection : public AdtDelphiBase
{
private:
  AdtDelphiUsesClause*          UsesClause;
  AdtDelphiConstSection*        ConstSection;
  AdtDelphiTypeSection*         TypeSection;
  AdtDelphiVarSection*          VarSection;
  AdtDelphiExportedHeadingList* ExportedHeadingList;

public:
  AdtDelphiInterfaceSection(AdtParser* pUsesClauseObj,
                            AdtParser* pConstSectionObj,
                            AdtParser* pTypeSectionObj,
                            AdtParser* pVarSectionObj,
                            AdtParser* pExportedHeadingListObj,
                            const char* pComment);

  AdtDelphiInterfaceSection(const AdtDelphiInterfaceSection& rCopy);
  virtual ~AdtDelphiInterfaceSection();

  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiExportedHeadingList class
//  ----------------------------------------------------------------------------
class AdtDelphiExportedHeadingList : public AdtDelphiBase
{
public:
  AdtDelphiExportedHeadingList(AdtParser* pExportedHeadingObj);
  AdtDelphiExportedHeadingList(const AdtDelphiExportedHeadingList& rCopy);
  virtual ~AdtDelphiExportedHeadingList();

  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiExportedHeading);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiExportedHeadingList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiExportedHeading class
//  ----------------------------------------------------------------------------
class AdtDelphiExportedHeading : public AdtDelphiBase
{
protected:
  AdtDelphiProcedureHeading*  ProcedureHeading;
  AdtDelphiFunctionHeading*   FunctionHeading;
  AdtDelphiDirectiveList*     DirectiveList;

public:
  AdtDelphiExportedHeading(AdtParser* pProcedureHeadingObj,
                           AdtParser* pFunctionHeadingObj,
                           AdtParser* pDirectiveListObj,
                           const char* pComment);

  AdtDelphiExportedHeading(const AdtDelphiExportedHeading& rCopy);
  virtual ~AdtDelphiExportedHeading();

  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiImplementationSection class
//  ----------------------------------------------------------------------------
class AdtDelphiImplementationSection : public AdtDelphiBase
{
protected:
  AdtDelphiUsesClause*  UsesClause;
  AdtDelphiDeclSection* DeclSection;

public:
  AdtDelphiImplementationSection(AdtParser* pUsesClauseObj,
                                 AdtParser* pDeclSectionObj,
                                 const char* pComment);

  AdtDelphiImplementationSection(const AdtDelphiImplementationSection& rCopy);
  virtual ~AdtDelphiImplementationSection();

  virtual AdtFile&         writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiBlock class
//  ----------------------------------------------------------------------------
class AdtDelphiBlock : public AdtDelphiBase
{
protected:
  AdtDelphiDeclSection*   DeclSection;
  AdtDelphiCompoundStmt*  CompoundStmt;

public:
  AdtDelphiBlock(AdtParser* pDeclSectionObj,
                 AdtParser* pCompoundStmtObj,
                 const char* pComment);

  AdtDelphiBlock(const AdtDelphiBlock& rCopy);
  virtual ~AdtDelphiBlock();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiDeclSection class
//  ----------------------------------------------------------------------------
class AdtDelphiDeclSection : public AdtDelphiBase
{
protected:
  AdtDelphiLabelDeclSection*      LabelDeclSection;
  AdtDelphiConstSection*          ConstSection;
  AdtDelphiTypeSection*           TypeSection;
  AdtDelphiVarSection*            VarSection;
  AdtDelphiProcedureDeclSection*  ProcedureDeclSection;

public:
  AdtDelphiDeclSection(AdtParser* pLabelDeclSectionObj,
                       AdtParser* pConstSectionObj,
                       AdtParser* pTypeSectionObj,
                       AdtParser* pVarSectionObj,
                       AdtParser* pProcedureDeclSectionObj,
                       const char* pComment);

  AdtDelphiDeclSection(const AdtDelphiDeclSection& rCopy);
  virtual ~AdtDelphiDeclSection();

  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDeclSection class
//  ----------------------------------------------------------------------------
class AdtDelphiLabelDeclSection : public AdtDelphiBase
{
protected:
  AdtDelphiLabelDeclList* LabelDeclList;

public:
  AdtDelphiLabelDeclSection(AdtParser* pLabelDeclListObj);
  AdtDelphiLabelDeclSection(const AdtDelphiLabelDeclSection& rCopy);
  virtual ~AdtDelphiLabelDeclSection();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiLabelDeclList : public AdtDelphiBase
{
public:
  AdtDelphiLabelDeclList(AdtParser* pLabelDeclObj);
  AdtDelphiLabelDeclList(const AdtDelphiLabelDeclList& rCopy);
  virtual ~AdtDelphiLabelDeclList();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiLabelDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiLabelDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiLabelDecl : public AdtDelphiBase
{
protected:
  AdtDelphiLabelId*       LabelId;

public:
  AdtDelphiLabelDecl(AdtParser* pLabelIdObj,
                    const char* pComment);

  AdtDelphiLabelDecl(const AdtDelphiLabelDecl& rCopy);
  virtual ~AdtDelphiLabelDecl();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiConstSection class
//  ----------------------------------------------------------------------------
class AdtDelphiConstSection : public AdtDelphiBase
{
protected:
  AdtDelphiConstantDeclList*  ConstantDeclList;

public:
  AdtDelphiConstSection(AdtParser* pConstantDeclListObj,
                        const char* pComment);

  AdtDelphiConstSection(const AdtDelphiConstSection& rCopy);
  virtual ~AdtDelphiConstSection();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiConstantDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiConstantDeclList : public AdtDelphiBase
{
public:
  AdtDelphiConstantDeclList(AdtParser* pConstantDeclObj);
  AdtDelphiConstantDeclList(const AdtDelphiConstantDeclList& rCopy);
  virtual ~AdtDelphiConstantDeclList();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiConstantDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstantDeclList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstantDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiConstantDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiConstantDecl : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*         Ident;
  AdtDelphiTypeId*        TypeId;
  AdtDelphiUnitId*        UnitId;
  AdtDelphiConstExpr*     ConstExpr;
  AdtDelphiTypedConstant* TypedConstant;

public:
  AdtDelphiConstantDecl(AdtParser* pIdentObj,
                        AdtParser* pTypeIdObj,
                        AdtParser* pUnitIdObj,
                        AdtParser* pConstExprObj,
                        AdtParser* pTypedConstantObj);

  AdtDelphiConstantDecl(const AdtDelphiConstantDecl& rCopy);
  virtual ~AdtDelphiConstantDecl();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeSection class
//  ----------------------------------------------------------------------------
class AdtDelphiTypeSection : public AdtDelphiBase
{
protected:
  AdtDelphiTypeDeclList*  TypeDeclList;

public:
  AdtDelphiTypeSection(AdtParser* pTypeDeclListObj,
                       const char* pComment);

  AdtDelphiTypeSection(const AdtDelphiTypeSection& rCopy);
  virtual ~AdtDelphiTypeSection();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiTypeDeclList : public AdtDelphiBase
{
public:
  AdtDelphiTypeDeclList(AdtParser* pTypeDeclObj);
  AdtDelphiTypeDeclList(const AdtDelphiTypeDeclList& rCopy);
  virtual ~AdtDelphiTypeDeclList();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiTypeDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiTypeDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiTypeDecl : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*           Ident;
  AdtDelphiType*            Type;
  AdtDelphiRestrictedType*  RestrictedType;

public:
  AdtDelphiTypeDecl(AdtParser* pIdentObj,
                    AdtParser* pTypeObj,
                    AdtParser* pRestrictedTypeObj);

  AdtDelphiTypeDecl(const AdtDelphiTypeDecl& rCopy);
  virtual ~AdtDelphiTypeDecl();

  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiTypedConstant class
//  ----------------------------------------------------------------------------
class AdtDelphiTypedConstant : public AdtDelphiBase
{
protected:
  AdtDelphiConstExpr*       ConstExpr;
  AdtDelphiArrayConstant*   ArrayConstant;
  AdtDelphiRecordConstant*  RecordConstant;

public:
  AdtDelphiTypedConstant(AdtParser* pConstExprObj,
                         AdtParser* pArrayConstantObj,
                         AdtParser* pRecordConstantObj);

  AdtDelphiTypedConstant(const AdtDelphiTypedConstant& rCopy);
  virtual ~AdtDelphiTypedConstant();

  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiArrayConstant class
//  ----------------------------------------------------------------------------
class AdtDelphiArrayConstant : public AdtDelphiBase
{
protected:
  AdtDelphiTypedConstantList* TypedConstantList;

public:
  AdtDelphiArrayConstant(AdtParser* pTypedConstantListObj);
  AdtDelphiArrayConstant(const AdtDelphiArrayConstant& rCopy);
  virtual ~AdtDelphiArrayConstant();

  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiTypedConstantList class
//  ----------------------------------------------------------------------------
class AdtDelphiTypedConstantList : public AdtDelphiBase
{
public:
  AdtDelphiTypedConstantList(AdtParser* pTypedConstantObj);
  AdtDelphiTypedConstantList(const AdtDelphiTypedConstantList& rCopy);
  virtual ~AdtDelphiTypedConstantList();

  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiTypedConstant);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiTypedConstantList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordConstant class
//  ----------------------------------------------------------------------------
class AdtDelphiRecordConstant : public AdtDelphiBase
{
protected:
  AdtDelphiRecordFieldConstantList* RecordFieldConstantList;

public:
  AdtDelphiRecordConstant(AdtParser* pRecordFieldConstantListObj);
  AdtDelphiRecordConstant(const AdtDelphiRecordConstant& rCopy);
  virtual ~AdtDelphiRecordConstant();

  virtual AdtFile&                  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordFieldConstantList class
//  ----------------------------------------------------------------------------
class AdtDelphiRecordFieldConstantList : public AdtDelphiBase
{
public:
  AdtDelphiRecordFieldConstantList(AdtParser* pRecordFieldConstantObj);
  AdtDelphiRecordFieldConstantList(const AdtDelphiRecordFieldConstantList& rCopy);
  virtual ~AdtDelphiRecordFieldConstantList();

  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiRecordFieldConstant);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiRecordFieldConstantList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiRecordFieldConstant class
//  ----------------------------------------------------------------------------
class AdtDelphiRecordFieldConstant : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*         Ident;
  AdtDelphiTypedConstant* TypedConstant;

public:
  AdtDelphiRecordFieldConstant(AdtParser* pIdentObj,
                               AdtParser* pTypedConstantObj);

  AdtDelphiRecordFieldConstant(const AdtDelphiRecordFieldConstant& rCopy);
  virtual ~AdtDelphiRecordFieldConstant();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiType class
//  ----------------------------------------------------------------------------
class AdtDelphiType : public AdtDelphiBase
{
protected:
  AdtDelphiTypeId*        TypeId;
  AdtDelphiUnitId*        UnitId;
  AdtDelphiSimpleType*    SimpleType;
  AdtDelphiStructType*    StructType;
  AdtDelphiPointerType*   PointerType;
  AdtDelphiStringType*    StringType;
  AdtDelphiProcedureType* ProcedureType;
  AdtDelphiVariantType*   VariantType;
  AdtDelphiClassRefType*  ClassRefType;

public:
  AdtDelphiType(AdtParser* pTypeIdObj,
                AdtParser* pUnitIdObj,
                AdtParser* pSimpleTypeObj,
                AdtParser* pStructTypeObj,
                AdtParser* pPointerTypeObj,
                AdtParser* pStringTypeObj,
                AdtParser* pProcedureTypeObj,
                AdtParser* pVariantTypeObj,
                AdtParser* pClassRefTypeObj);

  AdtDelphiType(const AdtDelphiType& rCopy);
  virtual ~AdtDelphiType();

  static AdtAutoType      autoType(const AdtDelphiTypeId* pTypeId,
                                   const AdtDelphiSimpleType* pSimpleType,
                                   int& nDimensions);

  AdtAutoType             autoType(int& nDimensions) const;

  AdtFile&                writeFortran(AdtFile& pOutFile, int nMode, const char*& sDimension, bool& bKeep) const;

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiRestrictedType class
//  ----------------------------------------------------------------------------
class AdtDelphiRestrictedType : public AdtDelphiBase
{
protected:
  AdtDelphiObjectType*    ObjectType;
  AdtDelphiClassType*     ClassType;
  AdtDelphiInterfaceType* InterfaceType;

public:
  AdtDelphiRestrictedType(AdtParser* pObjectTypeObj,
                          AdtParser* pClassTypeObj,
                          AdtParser* pInterfaceTypeObj);

  AdtDelphiRestrictedType(const AdtDelphiRestrictedType& rCopy);
  virtual ~AdtDelphiRestrictedType();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiClassRefType class
//  ----------------------------------------------------------------------------
class AdtDelphiClassRefType : public AdtDelphiBase
{
protected:
  AdtDelphiTypeId*  TypeId;
  AdtDelphiUnitId*  UnitId;

public:
  AdtDelphiClassRefType(AdtParser* pTypeIdObj,
                        AdtParser* pUnitIdObj);

  AdtDelphiClassRefType(const AdtDelphiClassRefType& rCopy);
  virtual ~AdtDelphiClassRefType();

  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleType class
//  ----------------------------------------------------------------------------
class AdtDelphiSimpleType : public AdtDelphiBase
{
protected:
  AdtDelphiOrdinalType* OrdinalType;
  AdtDelphiRealType*    RealType;

public:
  AdtDelphiSimpleType(AdtParser* pOrdinalTypeObj,
                      AdtParser* pRealTypeObj);

  AdtDelphiSimpleType(const AdtDelphiSimpleType& rCopy);
  virtual ~AdtDelphiSimpleType();

  AdtBlackBoxArgType      blackBoxArgType() const;

  AdtAutoType             autoType() const;

  virtual AdtFile&        writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiRealType class
//  ----------------------------------------------------------------------------
class AdtDelphiRealType : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_REAL48    = 0,
              AdtType_REAL      = 1,
              AdtType_SINGLE    = 2,
              AdtType_DOUBLE    = 3,
              AdtType_EXTENDED  = 4,
              AdtType_CURRENCY  = 5,
              AdtType_COMP      = 6};

protected:
  AdtType RealType;

public:
  AdtDelphiRealType(AdtType nType);
  AdtDelphiRealType(const AdtDelphiRealType& rCopy);
  virtual ~AdtDelphiRealType();

  AdtBlackBoxArgType      blackBoxArgType() const;

  AdtAutoType             autoType() const;

  virtual AdtFile&        writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdinalType class
//  ----------------------------------------------------------------------------
class AdtDelphiOrdinalType : public AdtDelphiBase
{
protected:
  AdtDelphiSubrangeType*    SubrangeType;
  AdtDelphiEnumeratedType*  EnumeratedType;
  AdtDelphiOrdIdent*        OrdIdent;

public:
  AdtDelphiOrdinalType(AdtParser* pSubrangeTypeObj,
                       AdtParser* pEnumeratedTypeObj,
                       AdtParser* pOrdIdentObj);

  AdtDelphiOrdinalType(const AdtDelphiOrdinalType& rCopy);
  virtual ~AdtDelphiOrdinalType();

  AdtBlackBoxArgType        blackBoxArgType() const;

  AdtAutoType               autoType() const;

  virtual AdtFile&          writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdIdent class
//  ----------------------------------------------------------------------------
class AdtDelphiOrdIdent : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_SHORTINT  = 0,
              AdtType_SMALLINT  = 1,
              AdtType_INTEGER   = 2,
              AdtType_BYTE      = 3,
              AdtType_LONGINT   = 4,
              AdtType_INT64     = 5,
              AdtType_WORD      = 6,
              AdtType_BOOLEAN   = 7,
              AdtType_CHAR      = 8,
              AdtType_WIDECHAR  = 9,
              AdtType_LONGWORD  = 10,
              AdtType_PCHAR     = 11,
              AdtType_POINTER   = 12};

protected:
  AdtType OrdType;

public:
  AdtDelphiOrdIdent(AdtType nType);
  AdtDelphiOrdIdent(const AdtDelphiOrdIdent& rCopy);
  virtual ~AdtDelphiOrdIdent();

  AdtBlackBoxArgType         blackBoxArgType() const;

  AdtAutoType                autoType() const;

  virtual AdtFile&           writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&           writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&           writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantType class
//  ----------------------------------------------------------------------------
class AdtDelphiVariantType : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_VARIANT     = 0,
              AdtType_OLEVARIANT  = 1};

protected:
  AdtType Type;

public:
  AdtDelphiVariantType(AdtType nType);
  AdtDelphiVariantType(const AdtDelphiVariantType& rCopy);
  virtual ~AdtDelphiVariantType();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSubrangeType class
//  ----------------------------------------------------------------------------
class AdtDelphiSubrangeType : public AdtDelphiBase
{
protected:
  AdtDelphiConstExpr* FromConstExpr;
  AdtDelphiConstExpr* ToConstExpr;

public:
  AdtDelphiSubrangeType(AdtParser* pFromConstExprObj,
                        AdtParser* pToConstExprObj);

  AdtDelphiSubrangeType(const AdtDelphiSubrangeType& rCopy);
  virtual ~AdtDelphiSubrangeType();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedType class
//  ----------------------------------------------------------------------------
class AdtDelphiEnumeratedType : public AdtDelphiBase
{
protected:
  AdtDelphiEnumeratedTypeElementList* EnumeratedTypeElementList;

public:
  AdtDelphiEnumeratedType(AdtParser* pEnumeratedTypeElementListObj);
  AdtDelphiEnumeratedType(const AdtDelphiEnumeratedType& rCopy);
  virtual ~AdtDelphiEnumeratedType();

  virtual AdtFile&                    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedTypeElementList class
//  ----------------------------------------------------------------------------
class AdtDelphiEnumeratedTypeElementList : public AdtDelphiBase
{
public:
  AdtDelphiEnumeratedTypeElementList(AdtParser* pEnumeratedTypeElementObj);
  AdtDelphiEnumeratedTypeElementList(const AdtDelphiEnumeratedTypeElementList& rCopy);
  virtual ~AdtDelphiEnumeratedTypeElementList();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiEnumeratedTypeElement);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiEnumeratedTypeElementList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiEnumeratedTypeElement class
//  ----------------------------------------------------------------------------
class AdtDelphiEnumeratedTypeElement : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*     Ident;
  AdtDelphiConstExpr* ConstExpr;

public:
  AdtDelphiEnumeratedTypeElement(AdtParser* pIdentObj,
                                 AdtParser* pConstExprObj);

  AdtDelphiEnumeratedTypeElement(const AdtDelphiEnumeratedTypeElement& rCopy);
  virtual ~AdtDelphiEnumeratedTypeElement();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiStringType class
//  ----------------------------------------------------------------------------
class AdtDelphiStringType : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_STRING      = 0,
              AdtType_ANSISTRING  = 1,
              AdtType_WIDESTRING  = 2};

protected:
  AdtType             Type;
  AdtDelphiConstExpr* ConstExpr;

public:
  AdtDelphiStringType(AdtType nType,
                      AdtParser* pConstExprObj);

  AdtDelphiStringType(const AdtDelphiStringType& rCopy);
  virtual ~AdtDelphiStringType();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiStructType class
//  ----------------------------------------------------------------------------
class AdtDelphiStructType : public AdtDelphiBase
{
protected:
  bool                IsPacked;
  AdtDelphiArrayType* ArrayType;
  AdtDelphiSetType*   SetType;
  AdtDelphiFileType*  FileType;
  AdtDelphiRecType*   RecType;

public:
  AdtDelphiStructType(bool bIsPacked,
                      AdtParser* pArrayTypeObj,
                      AdtParser* pSetTypeObj,
                      AdtParser* pFileTypeObj,
                      AdtParser* pRecTypeObj);

  AdtDelphiStructType(const AdtDelphiStructType& rCopy);
  virtual ~AdtDelphiStructType();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiArrayType class
//  ----------------------------------------------------------------------------
class AdtDelphiArrayType : public AdtDelphiBase
{
protected:
  AdtDelphiOrdinalTypeList* OrdinalTypeList;
  AdtDelphiType*            Type;

public:
  AdtDelphiArrayType(AdtParser* pOrdinalTypeListObj,
                     AdtParser* pTypeObj);

  AdtDelphiArrayType(const AdtDelphiArrayType& rCopy);
  virtual ~AdtDelphiArrayType();

  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiOrdinalTypeList class
//  ----------------------------------------------------------------------------
class AdtDelphiOrdinalTypeList : public AdtDelphiBase
{
public:
  AdtDelphiOrdinalTypeList(AdtParser* pOrdinalTypeObj);
  AdtDelphiOrdinalTypeList(const AdtDelphiOrdinalTypeList& rCopy);
  virtual ~AdtDelphiOrdinalTypeList();

  virtual AdtFile&             writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiOrdinalType);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiOrdinalTypeList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiRecType class
//  ----------------------------------------------------------------------------
class AdtDelphiRecType : public AdtDelphiBase
{
protected:
  AdtDelphiFieldDeclList*       FieldDeclList;
  AdtDelphiVariantSectionList*  VariantSectionList;

public:
  AdtDelphiRecType(AdtParser* pFieldDeclListObj,
                   AdtParser* pVariantSectionListObj);

  AdtDelphiRecType(const AdtDelphiRecType& rCopy);
  virtual ~AdtDelphiRecType();

  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFieldDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiFieldDeclList : public AdtDelphiBase
{
public:
  AdtDelphiFieldDeclList(AdtParser* pFieldDeclObj);
  AdtDelphiFieldDeclList(const AdtDelphiFieldDeclList& rCopy);
  virtual ~AdtDelphiFieldDeclList();

  virtual AdtFile&       writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiFieldDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiFieldDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiFieldDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiFieldDecl : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList* IdentList;
  AdtDelphiType*      Type;

public:
  AdtDelphiFieldDecl(AdtParser* pIdentListObj,
                     AdtParser* pTypeObj);

  AdtDelphiFieldDecl(const AdtDelphiFieldDecl& rCopy);
  virtual ~AdtDelphiFieldDecl();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantSectionList class
//  ----------------------------------------------------------------------------
class AdtDelphiVariantSectionList : public AdtDelphiBase
{
public:
  AdtDelphiVariantSectionList(AdtParser* pVariantSectionObj);
  AdtDelphiVariantSectionList(const AdtDelphiVariantSectionList& rCopy);
  virtual ~AdtDelphiVariantSectionList();

  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiVariantSection);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiVariantSectionList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiVariantSection class
//  ----------------------------------------------------------------------------
class AdtDelphiVariantSection : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*       Ident;
  AdtDelphiUnitId*      UnitId;
  AdtDelphiTypeId*      TypeId;
  AdtDelphiRecVariant*  RecVariant;

public:
  AdtDelphiVariantSection(AdtParser* pIdentObj,
                          AdtParser* pUnitIdObj,
                          AdtParser* pTypeIdObj,
                          AdtParser* pRecVariantObj);

  AdtDelphiVariantSection(const AdtDelphiVariantSection& rCopy);
  virtual ~AdtDelphiVariantSection();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiRecVariant class
//  ----------------------------------------------------------------------------
class AdtDelphiRecVariant : public AdtDelphiBase
{
protected:
  AdtDelphiConstExprList*       ConstExprList;
  AdtDelphiFieldDeclList*       FieldDeclList;
  AdtDelphiVariantSectionList*  VariantSectionList;

public:
  AdtDelphiRecVariant(AdtParser* pConstExprListObj,
                      AdtParser* pFieldDeclListObj,
                      AdtParser* pVariantSectionListObj);

  AdtDelphiRecVariant(const AdtDelphiRecVariant& rCopy);
  virtual ~AdtDelphiRecVariant();

  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiConstExprList class
//  ----------------------------------------------------------------------------
class AdtDelphiConstExprList : public AdtDelphiBase
{
public:
  AdtDelphiConstExprList(AdtParser* pConstExprObj);
  AdtDelphiConstExprList(const AdtDelphiConstExprList& rCopy);
  virtual ~AdtDelphiConstExprList();

  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiConstExpr);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstExprList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiSetType class
//  ----------------------------------------------------------------------------
class AdtDelphiSetType : public AdtDelphiBase
{
protected:
  AdtDelphiOrdinalType* OrdinalType;

public:
  AdtDelphiSetType(AdtParser* pOrdinalTypeObj);
  AdtDelphiSetType(const AdtDelphiSetType& rCopy);
  virtual ~AdtDelphiSetType();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFileType class
//  ----------------------------------------------------------------------------
class AdtDelphiFileType : public AdtDelphiBase
{
protected:
  AdtDelphiUnitId*  UnitId;
  AdtDelphiTypeId*  TypeId;

public:
  AdtDelphiFileType(AdtParser* pUnitIdObj,
                    AdtParser* pTypeIdObj);

  AdtDelphiFileType(const AdtDelphiFileType& rCopy);
  virtual ~AdtDelphiFileType();

  virtual AdtFile&  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiPointerType class
//  ----------------------------------------------------------------------------
class AdtDelphiPointerType : public AdtDelphiBase
{
protected:
  AdtDelphiUnitId*  UnitId;
  AdtDelphiTypeId*  TypeId;

public:
  AdtDelphiPointerType(AdtParser* pUnitIdObj,
                       AdtParser* pTypeIdObj);

  AdtDelphiPointerType(const AdtDelphiPointerType& rCopy);
  virtual ~AdtDelphiPointerType();

  virtual AdtFile&  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureType class
//  ----------------------------------------------------------------------------
class AdtDelphiProcedureType : public AdtDelphiBase
{
protected:
  AdtDelphiProcedureHeading*  ProcedureHeading;
  AdtDelphiFunctionHeading*   FunctionHeading;
  bool                        OfObject;

public:
  AdtDelphiProcedureType(AdtParser* pProcedureHeadingObj,
                         AdtParser* pFunctionHeadingObj,
                         bool bOfObject);

  AdtDelphiProcedureType(const AdtDelphiProcedureType& rCopy);
  virtual ~AdtDelphiProcedureType();

  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiVarSection class
//  ----------------------------------------------------------------------------
class AdtDelphiVarSection : public AdtDelphiBase
{
protected:
  AdtDelphiVarDeclList* VarDeclList;

public:
  AdtDelphiVarSection(AdtParser* pVarDeclListObj,
                      const char* pComment);

  AdtDelphiVarSection(const AdtDelphiVarSection& rCopy);
  virtual ~AdtDelphiVarSection();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiVarDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiVarDeclList : public AdtDelphiBase
{
public:
  AdtDelphiVarDeclList(AdtParser* pVarDeclObj);
  AdtDelphiVarDeclList(const AdtDelphiVarDeclList& rCopy);
  virtual ~AdtDelphiVarDeclList();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiVarDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiVarDeclList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiVarDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiVarDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiVarDecl : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList* IdentList;
  AdtDelphiType*      Type;
  AdtDelphiIdent*     Ident;
  AdtDelphiConstExpr* ConstExpr;
  bool                Absolute;

public:
  AdtDelphiVarDecl(AdtParser* pIdentListObj,
                   AdtParser* pTypeObj,
                   AdtParser* pIdentObj,
                   AdtParser* pConstExprObj,
                   bool bAbsolute);

  AdtDelphiVarDecl(const AdtDelphiVarDecl& rCopy);
  virtual ~AdtDelphiVarDecl();

  virtual void        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiExpression class
//  ----------------------------------------------------------------------------
class AdtDelphiExpression : public AdtDelphiBase
{
protected:
  AdtDelphiExpressionRelOpList* ExpressionRelOpList;

public:
  AdtDelphiExpression(AdtParser* pExpressionRelOpListObj);
  AdtDelphiExpression(const AdtDelphiExpression& rCopy);
  virtual ~AdtDelphiExpression();

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiExpressionRelOpList class
//  ----------------------------------------------------------------------------
class AdtDelphiExpressionRelOpList : public AdtDelphiBase
{
public:
  AdtDelphiExpressionRelOpList(AdtParser* pExpressionRelOpObj);
  AdtDelphiExpressionRelOpList(const AdtDelphiExpressionRelOpList& rCopy);
  virtual ~AdtDelphiExpressionRelOpList();

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiExpressionRelOp);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiExpressionRelOpList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiExpressionRelOpList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiExpressionRelOp class
//  ----------------------------------------------------------------------------
class AdtDelphiExpressionRelOp : public AdtDelphiBase
{
public:
enum AdtRelOp{AdtRelOp_GT     = 1,
              AdtRelOp_LT     = 2,
              AdtRelOp_LE     = 3,
              AdtRelOp_GE     = 4,
              AdtRelOp_NE     = 5,
              AdtRelOp_IN     = 6,
              AdtRelOp_IS     = 7,
              AdtRelOp_AS     = 8,
              AdtRelOp_EQ     = 9,
              AdtRelOp_EMPTY  = 0};

protected:
  AdtRelOp                    RelOp;
  AdtDelphiSimpleExpression*  SimpleExpression;

public:
  AdtDelphiExpressionRelOp(AdtRelOp nRelOp,
                           AdtParser* pSimpleExpressionObj);

  AdtDelphiExpressionRelOp(const AdtDelphiExpressionRelOp& rCopy);
  virtual ~AdtDelphiExpressionRelOp();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpression class
//  ----------------------------------------------------------------------------
class AdtDelphiSimpleExpression : public AdtDelphiBase
{
protected:
  AdtDelphiSimpleExpressionAddOpList* SimpleExpressionAddOpList;

public:
  AdtDelphiSimpleExpression(AdtParser* pSimpleExpressionAddOpListObj);
  AdtDelphiSimpleExpression(const AdtDelphiSimpleExpression& rCopy);
  virtual ~AdtDelphiSimpleExpression();

  virtual AdtFile&                    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpressionAddOpList class
//  ----------------------------------------------------------------------------
class AdtDelphiSimpleExpressionAddOpList : public AdtDelphiBase
{
public:
  AdtDelphiSimpleExpressionAddOpList(AdtParser* pSimpleExpressionAddOpObj);
  AdtDelphiSimpleExpressionAddOpList(const AdtDelphiSimpleExpressionAddOpList& rCopy);
  virtual ~AdtDelphiSimpleExpressionAddOpList();

  virtual AdtFile&                    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiSimpleExpressionAddOp);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiSimpleExpressionAddOpList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiSimpleExpressionAddOpList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleExpressionAddOp class
//  ----------------------------------------------------------------------------
class AdtDelphiSimpleExpressionAddOp : public AdtDelphiBase
{
public:
enum  AdtSign{AdtSign_PLUS  = 1,
              AdtSign_MINUS = 2,
              AdtSign_EMPTY = 0};

enum  AdtAddOp{AdtAddOp_PLUS  = 1,
               AdtAddOp_MINUS = 2,
               AdtAddOp_OR    = 3,
               AdtAddOp_XOR   = 4,
               AdtAddOp_EMPTY = 0};

protected:
  AdtAddOp        AddOp;
  AdtDelphiTerm*  Term;
  AdtSign         Sign;

public:
  AdtDelphiSimpleExpressionAddOp(AdtAddOp nAddOp,
                                 AdtSign nSign,
                                 AdtParser* pTermObj);

  AdtDelphiSimpleExpressionAddOp(const AdtDelphiSimpleExpressionAddOp& rCopy);
  virtual ~AdtDelphiSimpleExpressionAddOp();

  virtual AdtFile&writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiTerm class
//  ----------------------------------------------------------------------------
class AdtDelphiTerm : public AdtDelphiBase
{
protected:
  AdtDelphiFactorMulOpList* FactorMulOpList;

public:
  AdtDelphiTerm(AdtParser* pFactorMulOpListObj);
  AdtDelphiTerm(const AdtDelphiTerm& rCopy);
  virtual ~AdtDelphiTerm();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFactorMulOpList class
//  ----------------------------------------------------------------------------
class AdtDelphiFactorMulOpList : public AdtDelphiBase
{
public:
  AdtDelphiFactorMulOpList(AdtParser* pFactorMulOpObj);
  AdtDelphiFactorMulOpList(const AdtDelphiFactorMulOpList& rCopy);
  virtual ~AdtDelphiFactorMulOpList();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiFactorMulOp);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiFactorMulOpList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiFactorMulOpList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiFactorMulOp class
//  ----------------------------------------------------------------------------
class AdtDelphiFactorMulOp : public AdtDelphiBase
{
public:
enum  AdtMulOp{AdtMulOp_MULTIPLY  = 1,
               AdtMulOp_DIVIDE    = 2,
               AdtMulOp_DIV       = 3,
               AdtMulOp_MOD       = 4,
               AdtMulOp_AND       = 5,
               AdtMulOp_SHL       = 6,
               AdtMulOp_SHR       = 7,
               AdtMulOp_EMPTY     = 0};
;

protected:
  AdtMulOp          MulOp;
  AdtDelphiFactor*  Factor;

public:
  AdtDelphiFactorMulOp(AdtMulOp nMulOp,
                       AdtParser* pFactorObj);

  AdtDelphiFactorMulOp(const AdtDelphiFactorMulOp& rCopy);
  virtual ~AdtDelphiFactorMulOp();

  virtual AdtFile&  writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFactor class
//  ----------------------------------------------------------------------------
class AdtDelphiFactor : public AdtDelphiBase
{
protected:
  AdtDelphiDesignator*      Designator;
  bool                      HasAt;
  AdtDelphiNumber*          Number;
  AdtDelphiString*          String;
  bool                      HasNil;
  AdtDelphiExpression*      Expression;
  AdtDelphiFactor*          Factor;
  AdtDelphiSetConstructor*  SetConstructor;
  AdtDelphiSizeofType*      SizeofType;
  AdtDelphiCastExpression*  CastExpression;

public:
  AdtDelphiFactor(AdtParser* pDesignatorObj,
                  bool bHasAt,
                  AdtParser* pNumberObj,
                  AdtParser* pStringObj,
                  bool bHasNil,
                  AdtParser* pExpressionObj,
                  AdtParser* pFactorObj,
                  AdtParser* pSetConstructorObj,
                  AdtParser* pSizeofTypeObj,
                  AdtParser* pCastExpressionObj);

  AdtDelphiFactor(const AdtDelphiFactor& rCopy);
  virtual ~AdtDelphiFactor();

  bool                      substituteMacroExpression(AdtDelphiExpression* pExpression);
  bool                      substituteMacroDesignator(AdtDelphiDesignator* pDesignator);

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiCastExpression class
//  ----------------------------------------------------------------------------
class AdtDelphiCastExpression : public AdtDelphiBase
{
protected:
  AdtDelphiOrdIdent*        OrdIdent;
  AdtDelphiRealType*        RealType;
  AdtDelphiExpression*      Expression;

public:
  AdtDelphiCastExpression(AdtParser* pOrdIdentObj,
                          AdtParser* pRealTypeObj,
                          AdtParser* pExpressionObj);

  AdtDelphiCastExpression(const AdtDelphiCastExpression& rCopy);
  virtual ~AdtDelphiCastExpression();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignator class
//  ----------------------------------------------------------------------------
class AdtDelphiDesignator : public AdtDelphiBase
{
protected:
  AdtDelphiDesignatorObjList* DesignatorObjList;

public:
  AdtDelphiDesignator(AdtParser* pDesignatorObjListObj);
  AdtDelphiDesignator(const AdtDelphiDesignator& rCopy);
  virtual ~AdtDelphiDesignator();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  bool                        isProcedureCall() const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorObjList class
//  ----------------------------------------------------------------------------
class AdtDelphiDesignatorObjList : public AdtDelphiBase
{
public:
  AdtDelphiDesignatorObjList(AdtParser* pDesignatorObj);
  AdtDelphiDesignatorObjList(const AdtDelphiDesignatorObjList& rCopy);
  virtual ~AdtDelphiDesignatorObjList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  bool                        isProcedureCall() const;

  declListType(AdtDelphiDesignatorObj);
  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtDelphiDesignator::isProcedureCall() const
{
  bool bIsProcedureCall = false;

  if (DesignatorObjList != 0)
  {
    bIsProcedureCall = DesignatorObjList->isProcedureCall();
  }

  return (bIsProcedureCall);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiDesignatorObjList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "__",false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiDesignatorObjList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ".", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorObj class
//  ----------------------------------------------------------------------------
class AdtDelphiDesignatorObj : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*             Ident;
  AdtDelphiExprList*          ExprList;
  AdtDelphiDesignatorRefList* DesignatorRefList;
  bool                        EmptyParenthesis;
  bool                        Inherited;

protected:
  bool                        buildSliceString(string& rSliceString) const;

  void                        writeFortranInner(AdtFile& pOutFile,
                                                int nMode,
                                                bool bIsProcedureCall,
                                                int nClassExtendName) const;

public:
  AdtDelphiDesignatorObj(AdtParser* pIdentObj,
                         AdtParser* pExprListObj,
                         AdtParser* pDesignatorRefListObj,
                         bool bEmptyParenthesis,
                         bool bInherited);

  AdtDelphiDesignatorObj(const AdtDelphiDesignatorObj& rCopy);
  virtual ~AdtDelphiDesignatorObj();

  bool                        isMacroReplaceable(size_t nListSize, AdtDelphiExprList** ppExpressionList = 0) const;

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  virtual bool                allowableMatch(const AdtParser* pObj) const;

  bool                        isSimpleReference() const;
  bool                        isProcedureCall(bool bExcludeReservedNames = false, bool bExcludeSpecial = true) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtDelphiDesignatorObj::isSimpleReference() const
{
  bool bIsSimpleReference = ((Ident != 0) && (ExprList == 0) && (DesignatorRefList == 0) && !EmptyParenthesis);

  return (bIsSimpleReference);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorRefList class
//  ----------------------------------------------------------------------------
class AdtDelphiDesignatorRefList : public AdtDelphiBase
{
public:
  AdtDelphiDesignatorRefList(AdtParser* pDesignatorRefObj);
  AdtDelphiDesignatorRefList(const AdtDelphiDesignatorRefList& rCopy);
  virtual ~AdtDelphiDesignatorRefList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiDesignatorRef);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiDesignatorRefList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}



//  ----------------------------------------------------------------------------
//  AdtDelphiDesignatorRef class
//  ----------------------------------------------------------------------------
class AdtDelphiDesignatorRef : public AdtDelphiBase
{
protected:
  AdtDelphiExprList*  ExprList;

public:
  AdtDelphiDesignatorRef(AdtParser* pExprListObj);
  AdtDelphiDesignatorRef(const AdtDelphiDesignatorRef& rCopy);
  virtual ~AdtDelphiDesignatorRef();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSetConstructor class
//  ----------------------------------------------------------------------------
class AdtDelphiSetConstructor : public AdtDelphiBase
{
protected:
  AdtDelphiSetElementList*  SetElementList;

public:
  AdtDelphiSetConstructor(AdtParser* pSetElementListObj);
  AdtDelphiSetConstructor(const AdtDelphiSetConstructor& rCopy);
  virtual ~AdtDelphiSetConstructor();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSetElementList class
//  ----------------------------------------------------------------------------
class AdtDelphiSetElementList : public AdtDelphiBase
{
public:
  AdtDelphiSetElementList(AdtParser* pSetElementObj);
  AdtDelphiSetElementList(const AdtDelphiSetElementList& rCopy);
  virtual ~AdtDelphiSetElementList();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiSetElement);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiSetElementList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiSetElementList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiSetElement class
//  ----------------------------------------------------------------------------
class AdtDelphiSetElement : public AdtDelphiBase
{
protected:
  AdtDelphiExpression*  Expression;
  AdtDelphiExpression*  EndExpression;

public:
  AdtDelphiSetElement(AdtParser* pExpressionObj,
                      AdtParser* pEndExpressionObj);

  AdtDelphiSetElement(const AdtDelphiSetElement& rCopy);
  virtual ~AdtDelphiSetElement();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiExprList class
//  ----------------------------------------------------------------------------
class AdtDelphiExprList : public AdtDelphiBase
{
public:
  AdtDelphiExprList(AdtParser* pExprObj);
  AdtDelphiExprList(const AdtDelphiExprList& rCopy);
  virtual ~AdtDelphiExprList();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiExpression);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiExprList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiExprList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiStatement class
//  ----------------------------------------------------------------------------
class AdtDelphiStatement : public AdtDelphiBase
{
protected:
  AdtDelphiLabelId*         LabelId;
  AdtDelphiExitStatement*   ExitStatement;
  AdtDelphiSimpleStatement* SimpleStatement;
  AdtDelphiCompoundStmt*    CompoundStmt;
  AdtDelphiIfStmt*          IfStmt;
  AdtDelphiCaseStmt*        CaseStmt;
  AdtDelphiRepeatStmt*      RepeatStmt;
  AdtDelphiWhileStmt*       WhileStmt;
  AdtDelphiForStmt*         ForStmt;
  AdtDelphiWithStmt*        WithStmt;

public:
  AdtDelphiStatement(AdtParser* pLabelIdObj,
                     AdtParser* pExitStatementObj,
                     AdtParser* pSimpleStatementObj,
                     AdtParser* pCompoundStmtObj,
                     AdtParser* pIfStmtObj,
                     AdtParser* pCaseStmtObj,
                     AdtParser* pRepeatStmtObj,
                     AdtParser* pWhileStmtObj,
                     AdtParser* pForStmtObj,
                     AdtParser* pWithStmtObj,
                     const char* pComment);

  AdtDelphiStatement(const AdtDelphiStatement& rCopy);
  virtual ~AdtDelphiStatement();

  bool                      substituteMacroCompoundStatement(AdtDelphiStmtList* pStatementList);

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual bool              hasType(const char* pType) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiStmtList class
//  ----------------------------------------------------------------------------
class AdtDelphiStmtList : public AdtDelphiBase
{
public:
  AdtDelphiStmtList(AdtParser* pStmtObj);
  AdtDelphiStmtList(const AdtDelphiStmtList& rCopy);
  virtual ~AdtDelphiStmtList();

  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiStatement);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiStmtList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "", true, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiStmtList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiExitStatement class
//  ----------------------------------------------------------------------------
class AdtDelphiExitStatement : public AdtDelphiBase
{
protected:
  bool                    WithParenthesis;

public:
  AdtDelphiExitStatement(bool bWithParenthesis);
  AdtDelphiExitStatement(const AdtDelphiExitStatement& rCopy);
  virtual ~AdtDelphiExitStatement();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSimpleStatement class
//  ----------------------------------------------------------------------------
class AdtDelphiSimpleStatement : public AdtDelphiBase
{
public:
enum  AdtOpType{AdtOpType_ASSIGN        = 0,
                AdtOpType_PLUS_EQUALS   = 1,
                AdtOpType_MINUS_EQUALS  = 2,
                AdtOpType_TIMES_EQUALS  = 3,
                AdtOpType_DIV_EQUALS    = 4};

protected:
  AdtOpType                 OpType;
  AdtDelphiDesignator*      Designator;
  AdtDelphiExpression*      Expression;
  AdtDelphiSizeofType*      SizeofType;
  AdtDelphiIdent*           Ident;
  AdtDelphiExprList*        ExprList;
  AdtDelphiLabelId*         LabelId;
  AdtDelphiCastExpression*  CastExpression;
  bool                      Inherited;

public:
  AdtDelphiSimpleStatement(AdtParser* pDesignatorObj,
                           AdtParser* pExpressionObj,
                           AdtParser* pSizeofTypeObj,
                           AdtParser* pIdentObj,
                           AdtParser* pExprListObj,
                           AdtParser* pLabelIdObj,
                           AdtParser* pCastExpressionObj,
                           bool bInherited,
                           AdtOpType nOpType);

  AdtDelphiSimpleStatement(const AdtDelphiSimpleStatement& rCopy);
  virtual ~AdtDelphiSimpleStatement();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  bool                  isProcedureCall() const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiSizeofType class
//  ----------------------------------------------------------------------------
class AdtDelphiSizeofType : public AdtDelphiBase
{
protected:
  AdtDelphiOrdIdent*    OrdIdent;
  AdtDelphiRealType*    RealType;
  AdtDelphiVariantType* VariantType;
  AdtDelphiDesignator*  Designator;

public:
  AdtDelphiSizeofType(AdtParser* pOrdIdentObj,
                      AdtParser* pRealTypeObj,
                      AdtParser* pVariantTypeObj,
                      AdtParser* pDesignatorObj);

  AdtDelphiSizeofType(const AdtDelphiSizeofType& rCopy);
  virtual ~AdtDelphiSizeofType();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiCompoundStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiCompoundStmt : public AdtDelphiBase
{
protected:
  AdtDelphiStmtList*    StmtList;

public:
  AdtDelphiCompoundStmt(AdtParser* pStmtListObj);
  AdtDelphiCompoundStmt(const AdtDelphiCompoundStmt& rCopy);
  virtual ~AdtDelphiCompoundStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiIfStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiIfStmt : public AdtDelphiBase
{
protected:
  AdtDelphiExpression*  Expression;
  AdtDelphiStatement*   ThenStatement;
  AdtDelphiStatement*   ElseStatement;

public:
  AdtDelphiIfStmt(AdtParser* pExpressionObj,
                  AdtParser* pThenStatementObj,
                  AdtParser* pElseStatementObj);

  AdtDelphiIfStmt(const AdtDelphiIfStmt& rCopy);
  virtual ~AdtDelphiIfStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiCaseStmt : public AdtDelphiBase
{
protected:
  AdtDelphiExpression*        Expression;
  AdtDelphiCaseSelectorList*  CaseSelectorList;
  AdtDelphiStmtList*          StmtList;

public:
  AdtDelphiCaseStmt(AdtParser* pExpressionObj,
                    AdtParser* pCaseSelectorListObj,
                    AdtParser* pStmtListObj);

  AdtDelphiCaseStmt(const AdtDelphiCaseStmt& rCopy);
  virtual ~AdtDelphiCaseStmt();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseSelectorList class
//  ----------------------------------------------------------------------------
class AdtDelphiCaseSelectorList : public AdtDelphiBase
{
public:
  AdtDelphiCaseSelectorList(AdtParser* pCaseSelectorObj);
  AdtDelphiCaseSelectorList(const AdtDelphiCaseSelectorList& rCopy);
  virtual ~AdtDelphiCaseSelectorList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiCaseSelector);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiCaseSelectorList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiCaseSelectorList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseSelector class
//  ----------------------------------------------------------------------------
class AdtDelphiCaseSelector : public AdtDelphiBase
{
protected:
  AdtDelphiCaseLabelList* CaseLabelList;
  AdtDelphiStatement*     Statement;

public:
  AdtDelphiCaseSelector(AdtParser* pCaseLabelListObj,
                        AdtParser* pStatementObj);

  AdtDelphiCaseSelector(const AdtDelphiCaseSelector& rCopy);
  virtual ~AdtDelphiCaseSelector();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseLabelList class
//  ----------------------------------------------------------------------------
class AdtDelphiCaseLabelList : public AdtDelphiBase
{
public:
  AdtDelphiCaseLabelList(AdtParser* pCaseLabelObj);
  AdtDelphiCaseLabelList(const AdtDelphiCaseLabelList& rCopy);
  virtual ~AdtDelphiCaseLabelList();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiCaseLabel);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiCaseLabelList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiCaseLabelList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiCaseLabel class
//  ----------------------------------------------------------------------------
class AdtDelphiCaseLabel : public AdtDelphiBase
{
protected:
  AdtDelphiConstExpr* ConstExpr;
  AdtDelphiConstExpr* ToConstExpr;

public:
  AdtDelphiCaseLabel(AdtParser* pConstExprObj,
                     AdtParser* pToConstExprObj);

  AdtDelphiCaseLabel(const AdtDelphiCaseLabel& rCopy);
  virtual ~AdtDelphiCaseLabel();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiRepeatStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiRepeatStmt : public AdtDelphiBase
{
protected:
  AdtDelphiStatement*   Statement;
  AdtDelphiExpression*  Expression;

public:
  AdtDelphiRepeatStmt(AdtParser* pStatementObj,
                      AdtParser* pExpressionObj,
                      AdtParser* pStmtListObj);

  AdtDelphiRepeatStmt(const AdtDelphiRepeatStmt& rCopy);
  virtual ~AdtDelphiRepeatStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiWhileStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiWhileStmt : public AdtDelphiBase
{
protected:
  AdtDelphiExpression*  Expression;
  AdtDelphiStatement*   Statement;

public:
  AdtDelphiWhileStmt(AdtParser* pExpressionObj,
                     AdtParser* pStatementObj);

  AdtDelphiWhileStmt(const AdtDelphiWhileStmt& rCopy);
  virtual ~AdtDelphiWhileStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiForStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiForStmt : public AdtDelphiBase
{
protected:
  AdtDelphiUnitId*      UnitId;
  AdtDelphiIdent*       Ident;
  AdtDelphiExpression*  FromExpression;
  AdtDelphiExpression*  ToExpression;
  AdtDelphiStatement*   Statement;
  bool                  DownTo;

public:
  AdtDelphiForStmt(AdtParser* pUnitIdObj,
                   AdtParser* pIdentObj,
                   AdtParser* pFromExpressionObj,
                   AdtParser* pToExpressionObj,
                   AdtParser* pStatementObj,
                   bool bDownTo);

  AdtDelphiForStmt(const AdtDelphiForStmt& rCopy);
  virtual ~AdtDelphiForStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiWithStmt class
//  ----------------------------------------------------------------------------
class AdtDelphiWithStmt : public AdtDelphiBase
{
protected:
  AdtDelphiDesignator*  Designator;
  AdtDelphiStatement*   Statement;

public:
  AdtDelphiWithStmt(AdtParser* pDesignatorObj,
                    AdtParser* pStatementObj);

  AdtDelphiWithStmt(const AdtDelphiWithStmt& rCopy);
  virtual ~AdtDelphiWithStmt();

  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDeclSection class
//  ----------------------------------------------------------------------------
class AdtDelphiProcedureDeclSection : public AdtDelphiBase
{
protected:
  AdtDelphiProcedureDeclList* ProcedureDeclList;

public:
  AdtDelphiProcedureDeclSection(AdtParser* pProcedureDeclListObj);
  AdtDelphiProcedureDeclSection(const AdtDelphiProcedureDeclSection& rCopy);
  virtual ~AdtDelphiProcedureDeclSection();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDeclList class
//  ----------------------------------------------------------------------------
class AdtDelphiProcedureDeclList : public AdtDelphiBase
{
public:
  AdtDelphiProcedureDeclList(AdtParser* pProcedureDeclObj);
  AdtDelphiProcedureDeclList(const AdtDelphiProcedureDeclList& rCopy);
  virtual ~AdtDelphiProcedureDeclList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiProcedureDecl);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiProcedureDeclList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiProcedureDeclList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureDecl class
//  ----------------------------------------------------------------------------
class AdtDelphiProcedureDecl : public AdtDelphiBase
{
protected:
  AdtDelphiProcedureHeading*    ProcedureHeading;
  AdtDelphiFunctionHeading*     FunctionHeading;
  AdtDelphiConstructorHeading*  ConstructorHeading;
  AdtDelphiDestructorHeading*   DestructorHeading;
  AdtDelphiDirectiveList*       DirectiveList;
  AdtDelphiBlock*               Block;
  AdtParserPtrByStringMap       ArgumentVariableMap;
  AdtParserPtrByStringMap       LocalVariableMap;

protected:
  void                          replaceClassNameWith(AdtParser* pObj,
                                                     const char* pClassName,
                                                     const char* pNewCombinedName);

public:
  AdtDelphiProcedureDecl(AdtParser* pProcedureHeadingObj,
                         AdtParser* pFunctionHeadingObj,
                         AdtParser* pConstructorHeadingObj,
                         AdtParser* pDestructorHeadingObj,
                         AdtParser* pDirectiveListObj,
                         AdtParser* pBlockObj);

  AdtDelphiProcedureDecl(const AdtDelphiProcedureDecl& rCopy);
  virtual ~AdtDelphiProcedureDecl();

  void                          fixReturnVariable();
  bool                          replaceClassNameWith(const char* pClassName);

  bool                          enumerateLocalObjects(AdtParserPtrList& rExternalsList) const;

  bool                          enumerateExternals(AdtStringList& rExternalsList) const;

  const char*                   className() const;

  const AdtDelphiFormalParam*   findFormalParam(const char* pFormalParamName) const;
  const AdtDelphiVarDecl*       findVarDecl(const char* pVarName) const;

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  virtual bool                  hasType(const char* pType) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFunctionHeading class
//  ----------------------------------------------------------------------------
class AdtDelphiFunctionHeading : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*               ClassIdent;
  AdtDelphiIdent*               FunctionIdent;
  AdtDelphiFormalParameters*    FormalParameters;
  AdtDelphiSimpleType*          SimpleType;
  AdtDelphiTypeId*              TypeId;
  AdtBlackBoxDefinition*        BlackBox;

public:
  AdtDelphiFunctionHeading(AdtParser* pClassIdentObj,
                           AdtParser* pFunctionIdentObj,
                           AdtParser* pFormalParametersObj,
                           AdtParser* pSimpleTypeObj,
                           AdtParser* pTypeIdObj,
                           const char* pComment);

  AdtDelphiFunctionHeading(const AdtDelphiFunctionHeading& rCopy);
  virtual ~AdtDelphiFunctionHeading();

  AdtBlackBoxDefinition*        blackBox() const;

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtBlackBoxDefinition* AdtDelphiFunctionHeading::blackBox() const
{
  return (BlackBox);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiProcedureHeading class
//  ----------------------------------------------------------------------------
class AdtDelphiProcedureHeading : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*               ClassIdent;
  AdtDelphiIdent*               ProcedureIdent;
  AdtDelphiFormalParameters*    FormalParameters;
  AdtBlackBoxDefinition*        BlackBox;

public:
  AdtDelphiProcedureHeading(AdtParser* pClassIdentObj,
                            AdtParser* pProcedureIdentObj,
                            AdtParser* pFormalParametersObj,
                            const char* pComment);

  AdtDelphiProcedureHeading(const AdtDelphiProcedureHeading& rCopy);
  virtual ~AdtDelphiProcedureHeading();

  AdtBlackBoxDefinition*        blackBox() const;

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtBlackBoxDefinition* AdtDelphiProcedureHeading::blackBox() const
{
  return (BlackBox);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParameters class
//  ----------------------------------------------------------------------------
class AdtDelphiFormalParameters : public AdtDelphiBase
{
protected:
  AdtDelphiFormalParamList* FormalParamList;

public:
  AdtDelphiFormalParameters(AdtParser* pFormalParamListObj);
  AdtDelphiFormalParameters(const AdtDelphiFormalParameters& rCopy);
  virtual ~AdtDelphiFormalParameters();

  virtual AdtFile&          writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParamList class
//  ----------------------------------------------------------------------------
class AdtDelphiFormalParamList : public AdtDelphiBase
{
public:
  AdtDelphiFormalParamList(AdtParser* pFormalParamObj);
  AdtDelphiFormalParamList(const AdtDelphiFormalParamList& rCopy);
  virtual ~AdtDelphiFormalParamList();

  virtual AdtFile&          writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&          writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiFormalParam);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiFormalParam class
//  ----------------------------------------------------------------------------
class AdtDelphiFormalParam : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_VAR   = 1,
              AdtType_CONST = 2,
              AdtType_OUT   = 3,
              AdtType_EMPTY = 0};

protected:
  AdtType             Type;
  AdtDelphiParameter* Parameter;

public:
  AdtDelphiFormalParam(AdtType nType,
                       AdtParser* pParameterObj);

  AdtDelphiFormalParam(const AdtDelphiFormalParam& rCopy);
  virtual ~AdtDelphiFormalParam();

  void                addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                    const char* pFile,
                                    int nLine) const;

  virtual void        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual AdtFile&    writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  AdtAutoDir          autoDirType() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtAutoDir AdtDelphiFormalParam::autoDirType() const
{
  AdtAutoDir nDir;

  switch (Type)
  {
    case AdtType_VAR:
    {
      nDir = AdtAutoDir_INOUT;
      break;
    }

    case AdtType_CONST:
    {
      nDir = AdtAutoDir_IN;
      break;
    }

    case AdtType_OUT:
    {
      nDir = AdtAutoDir_OUT;
      break;
    }

    case AdtType_EMPTY:
    {
      nDir = AdtAutoDir_UNDEFINED;
      break;
    }

    default:
    {
      FAIL();
    }
  }

  return (nDir);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiParameter class
//  ----------------------------------------------------------------------------
class AdtDelphiParameter : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList*   IdentList;
  AdtDelphiSimpleType*  SimpleType;
  AdtDelphiTypeId*      TypeId;
  AdtDelphiConstExpr*   ConstExpr;
  AdtDelphiIdent*       Ident;
  bool                  IsArray;
  bool                  OfString;
  bool                  OfFile;

public:
  AdtDelphiParameter(AdtParser* pIdentListObj,
                     AdtParser* pSimpleTypeObj,
                     AdtParser* pTypeIdObj,
                     AdtParser* pConstExprObj,
                     AdtParser* pIdentObj,
                     bool bIsArray = false,
                     bool bOfString = false,
                     bool bOfFile = false);

  AdtDelphiParameter(const AdtDelphiParameter& rCopy);
  virtual ~AdtDelphiParameter();

  void                  addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                      AdtAutoDir nDir,
                                      const char* pFile,
                                      int nLine) const;

  virtual void          enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  AdtFile&              writeFortran(AdtFile& pOutFile, int nMode, bool& bKeep) const;
  AdtFile&              writeCPP_Var(AdtFile& pOutFile, const AdtDelphiBase* pVar, int nMode) const;

  virtual AdtFile&      writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiParameter::writeFortran(AdtFile& pOutFile, int nMode) const
{
  bool bKeep = true;

  return (writeFortran(pOutFile, nMode, bKeep));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiDirective class
//  ----------------------------------------------------------------------------
class AdtDelphiDirective : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_CDECL       = 1,
              AdtType_REGISTER    = 2,
              AdtType_DYNAMIC     = 3,
              AdtType_VIRTUAL     = 4,
              AdtType_EXPORT      = 5,
              AdtType_EXTERNAL    = 6,
              AdtType_FAR         = 7,
              AdtType_FORWARD     = 8,
              AdtType_MESSAGE     = 9,
              AdtType_OVERRIDE    = 10,
              AdtType_OVERLOAD    = 11,
              AdtType_PASCAL      = 12,
              AdtType_REINTRODUCE = 13,
              AdtType_SAFECALL    = 14,
              AdtType_STDCALL     = 15,
              AdtType_EMPTY       = 0};

protected:
  AdtType               Type;

public:
  AdtDelphiDirective(AdtType nType);
  AdtDelphiDirective(const AdtDelphiDirective& rCopy);
  virtual ~AdtDelphiDirective();

  virtual AdtFile&      writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  AdtType               directive() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtDelphiDirective::AdtType AdtDelphiDirective::directive() const
{
  return (Type);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiDirectiveList class
//  ----------------------------------------------------------------------------
class AdtDelphiDirectiveList : public AdtDelphiBase
{
public:
  AdtDelphiDirectiveList(AdtParser* pDirectiveObj);
  AdtDelphiDirectiveList(const AdtDelphiDirectiveList& rCopy);
  virtual ~AdtDelphiDirectiveList();

  bool                           hasDirective(AdtDelphiDirective::AdtType nType) const;
  virtual AdtFile&               writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiDirective);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiDirectiveList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiObjectType class
//  ----------------------------------------------------------------------------
class AdtDelphiObjectType : public AdtDelphiBase
{
protected:
  AdtDelphiUnitId*        UnitId;
  AdtDelphiIdent*         Ident;
  AdtDelphiObjFieldList*  ObjFieldList;
  AdtDelphiMethodList*    MethodList;

public:
  AdtDelphiObjectType(AdtParser* pUnitIdObj,
                      AdtParser* pIdentObj,
                      AdtParser* pObjFieldListObj,
                      AdtParser* pMethodListObj);

  AdtDelphiObjectType(const AdtDelphiObjectType& rCopy);
  virtual ~AdtDelphiObjectType();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiMethodList class
//  ----------------------------------------------------------------------------
class AdtDelphiMethodList : public AdtDelphiBase
{
public:
  AdtDelphiMethodList(AdtParser* pMethodObj);
  AdtDelphiMethodList(const AdtDelphiMethodList& rCopy);
  virtual ~AdtDelphiMethodList();

  virtual AdtFile&        writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&        writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiMethod);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiMethodList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiMethodList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiMethod class
//  ----------------------------------------------------------------------------
class AdtDelphiMethod : public AdtDelphiBase
{
protected:
  AdtDelphiProcedureHeading*    ProcedureHeading;
  AdtDelphiFunctionHeading*     FunctionHeading;
  AdtDelphiConstructorHeading*  ConstructorHeading;
  AdtDelphiDestructorHeading*   DestructorHeading;
  AdtDelphiDirectiveList*       DirectiveList;

public:
  AdtDelphiMethod(AdtParser* pProcedureHeadingObj,
                  AdtParser* pFunctionHeadingObj,
                  AdtParser* pConstructorHeadingObj,
                  AdtParser* pDestructorHeadingObj,
                  AdtParser* pDirectiveListObj);

  AdtDelphiMethod(const AdtDelphiMethod& rCopy);
  virtual ~AdtDelphiMethod();

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  bool                          isProcedure() const;
  bool                          isFunction() const;
  bool                          isConstructor() const;
  bool                          isDestructor() const;
  bool                          isVirtual() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtDelphiMethod::isProcedure() const
{
  return (ProcedureHeading != 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtDelphiMethod::isFunction() const
{
  return (FunctionHeading != 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtDelphiMethod::isConstructor() const
{
  return (ConstructorHeading != 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtDelphiMethod::isDestructor() const
{
  return (DestructorHeading != 0);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiConstructorHeading class
//  ----------------------------------------------------------------------------
class AdtDelphiConstructorHeading : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*             ClassIdent;
  AdtDelphiIdent*             MethodIdent;
  AdtDelphiFormalParameters*  FormalParameters;

public:
  AdtDelphiConstructorHeading(AdtParser* pClassIdentObj,
                              AdtParser* pMethodIdentObj,
                              AdtParser* pFormalParametersObj,
                              const char* pComment);

  AdtDelphiConstructorHeading(const AdtDelphiConstructorHeading& rCopy);
  virtual ~AdtDelphiConstructorHeading();

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiDestructorHeading class
//  ----------------------------------------------------------------------------
class AdtDelphiDestructorHeading : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*             ClassIdent;
  AdtDelphiIdent*             MethodIdent;
  AdtDelphiFormalParameters*  FormalParameters;

public:
  AdtDelphiDestructorHeading(AdtParser* pClassIdentObj,
                             AdtParser* pMethodIdentObj,
                             AdtParser* pFormalParametersObj,
                             const char* pComment);

  AdtDelphiDestructorHeading(const AdtDelphiDestructorHeading& rCopy);
  virtual ~AdtDelphiDestructorHeading();

  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiObjFieldList class
//  ----------------------------------------------------------------------------
class AdtDelphiObjFieldList : public AdtDelphiBase
{
public:
  AdtDelphiObjFieldList(AdtParser* pObjFieldObj);
  AdtDelphiObjFieldList(const AdtDelphiObjFieldList& rCopy);
  virtual ~AdtDelphiObjFieldList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiObjField);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiObjFieldList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ";", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiObjFieldList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiObjField class
//  ----------------------------------------------------------------------------
class AdtDelphiObjField : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList* IdentList;
  AdtDelphiType*      Type;

public:
  AdtDelphiObjField(AdtParser* pIdentListObj,
                    AdtParser* pTypeObj);

  AdtDelphiObjField(const AdtDelphiObjField& rCopy);
  virtual ~AdtDelphiObjField();

  virtual void        removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList = 0);

  virtual void        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;
  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;


  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiInitSection class
//  ----------------------------------------------------------------------------
class AdtDelphiInitSection : public AdtDelphiBase
{
protected:
  AdtDelphiStmtList*  StmtList;
  AdtDelphiStmtList*  FinalStmtList;
  bool                HasInit;

public:
  AdtDelphiInitSection(AdtParser* pStmtListObj,
                       AdtParser* pFinalStmtListObj,
                       bool bHasInit,
                       const char* pComment);

  AdtDelphiInitSection(const AdtDelphiInitSection& rCopy);
  virtual ~AdtDelphiInitSection();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiClassType class
//  ----------------------------------------------------------------------------
class AdtDelphiClassType : public AdtDelphiBase
{
public:
  enum SymbolType{TypeUndefined = 0,
                  TypeField     = 1,
                  TypeMethod    = 2,
                  TypeProperty  = 3};

  static AdtVisibility            GlobalVisibility;

protected:
  AdtDelphiIdentList*             IdentList;
  AdtDelphiClassFieldList*        ClassFieldList;
  AdtDelphiClassMethodList*       ClassMethodList;
  AdtDelphiClassPropertyList*     ClassPropertyList;

  AdtParserPtrByStringMap         FieldMap;
  AdtParserPtrByStringMap         MethodMap;
  AdtParserPtrByStringMap         PropertyMap;
  AdtParserPtrByStringMap         SymbolMap;

protected:
  void                            listAddOjects(AdtParser* pDestList,
                                                const AdtParser* pSrcList,
                                                const char* pObjectTypeName,
                                                const char* pDestClassName,
                                                const char* pSrcClassName);

  void                            addFields(AdtDelphiGoal* pGoal,
                                            const AdtDelphiGoal* pIncludeGoal,
                                            const AdtDelphiClassType* pClass,
                                            const string& rDestClassName,
                                            const string& rSrcClassName);

  void                            addMethods(AdtDelphiGoal* pGoal,
                                             const AdtDelphiGoal* pIncludeGoal,
                                             const AdtDelphiClassType* pClass,
                                             const string& rDestClassName,
                                             const string& rSrcClassName);

  void                            addProperties(AdtDelphiGoal* pGoal,
                                                const AdtDelphiGoal* pIncludeGoal,
                                                const AdtDelphiClassType* pClass,
                                                const string& rDestClassName,
                                                const string& rSrcClassName);

  bool                            importClass(const string& rDestClassName,
                                              const string& rSrcClassName,
                                              AdtDelphiGoal* pGoal,
                                              const AdtParserPtrList& rGoalList);

  bool                            flattenClass(const string& rClassName,
                                               const AdtParserPtrList& rParentList,
                                               AdtDelphiGoal* pGoal,
                                               const AdtParserPtrList& rGoalList);

public:
  AdtDelphiClassType(AdtParser* pIdentListObj,
                     AdtParser* pClassFieldListObj,
                     AdtParser* pClassMethodListObj,
                     AdtParser* pClassPropertyListObj);

  AdtDelphiClassType(const AdtDelphiClassType& rCopy);
  virtual ~AdtDelphiClassType();

  bool                            flattenClass(AdtDelphiGoal* pGoal, const AdtParserPtrList& rGoalList);
  const char*                     parentClassName() const;

  AdtDelphiClassType::SymbolType  defined(const char* pName) const;

  void                            findDimensionVars(const AdtParserPtrByStringMap& rVarsMap,
                                                    AdtParserPtrList& rList) const;

  bool                            findField(const char* pName, const AdtParser*& pExternal) const;
  bool                            findMethod(const char* pName, const AdtParser*& pExternal) const;
  bool                            findProperty(const char* pName, const AdtParser*& pExternal) const;

  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiClassFieldList class
//  ----------------------------------------------------------------------------
class AdtDelphiClassFieldList : public AdtDelphiBase
{
public:
  AdtDelphiClassFieldList(AdtParser* pClassFieldObj);
  AdtDelphiClassFieldList(const AdtDelphiClassFieldList& rCopy);
  virtual ~AdtDelphiClassFieldList();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiClassField);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassFieldList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ";", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassFieldList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiClassField class
//  ----------------------------------------------------------------------------
class AdtDelphiClassField : public AdtDelphiBase
{
protected:
  AdtVisibility       Visibility;
  AdtDelphiObjField*  ObjField;

public:
  AdtDelphiClassField(AdtVisibility nVisibility,
                      AdtParser* pObjFieldObj);

  AdtDelphiClassField(const AdtDelphiClassField& rCopy);
  virtual ~AdtDelphiClassField();

  virtual void        removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList = 0);

  virtual void        enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const;
  virtual void        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiClassMethodList class
//  ----------------------------------------------------------------------------
class AdtDelphiClassMethodList : public AdtDelphiBase
{
public:
  AdtDelphiClassMethodList(AdtParser* pClassMethodObj);
  AdtDelphiClassMethodList(const AdtDelphiClassMethodList& rCopy);
  virtual ~AdtDelphiClassMethodList();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiClassMethod);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassMethodList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ";", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassMethodList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiClassMethod class
//  ----------------------------------------------------------------------------
class AdtDelphiClassMethod : public AdtDelphiBase
{
public:
protected:
  AdtVisibility     Visibility;
  AdtDelphiMethod*  Method;

public:
  AdtDelphiClassMethod(AdtVisibility nVisibility,
                       AdtParser* pMethodObj);

  AdtDelphiClassMethod(const AdtDelphiClassMethod& rCopy);
  virtual ~AdtDelphiClassMethod();

  virtual void      enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const;
  virtual void      enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual AdtFile&  writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  bool              isVirtual() const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiClassPropertyList class
//  ----------------------------------------------------------------------------
class AdtDelphiClassPropertyList : public AdtDelphiBase
{
public:
  AdtDelphiClassPropertyList(AdtParser* pClassPropertyObj);
  AdtDelphiClassPropertyList(const AdtDelphiClassPropertyList& rCopy);
  virtual ~AdtDelphiClassPropertyList();

  virtual AdtFile&  writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&  writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiClassProperty);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassPropertyList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ";", true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiClassPropertyList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ";", true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiClassProperty class
//  ----------------------------------------------------------------------------
class AdtDelphiClassProperty : public AdtDelphiBase
{
protected:
  AdtVisibility       Visibility;
  AdtDelphiProperty*  Property;

public:
  AdtDelphiClassProperty(AdtVisibility nVisibility,
                         AdtParser* pPropertyObj);

  AdtDelphiClassProperty(const AdtDelphiClassProperty& rCopy);
  virtual ~AdtDelphiClassProperty();

  virtual void        enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const;
  virtual void        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiProperty class
//  ----------------------------------------------------------------------------
class AdtDelphiProperty : public AdtDelphiBase
{
protected:
  AdtDelphiIdent*                 ClassIdent;
  AdtDelphiIdent*                 Ident;
  AdtDelphiPropertyParameterList* PropertyParameterList;
  AdtDelphiPropertySpecifiers*    PropertySpecifiers;

public:
  AdtDelphiProperty(AdtParser* pClassIdentObj,
                    AdtParser* pIdentObj,
                    AdtParser* pPropertyParameterListObj,
                    AdtParser* pPropertySpecifiersObj);

  AdtDelphiProperty(const AdtDelphiProperty& rCopy);
  virtual ~AdtDelphiProperty();

  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertyParameterList class
//  ----------------------------------------------------------------------------
class AdtDelphiPropertyParameterList : public AdtDelphiBase
{
public:
  AdtDelphiPropertyParameterList(AdtParser* pPropertyParameterObj);
  AdtDelphiPropertyParameterList(const AdtDelphiPropertyParameterList& rCopy);
  virtual ~AdtDelphiPropertyParameterList();

  virtual AdtFile&                writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&                writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiPropertyParameterList);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiPropertyParameterList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, "; ", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiPropertyParameterList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, "; ", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertyParameter class
//  ----------------------------------------------------------------------------
class AdtDelphiPropertyParameter : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList* IdentList;
  AdtDelphiUnitId*    UnitId;
  AdtDelphiTypeId*    TypeId;

public:
  AdtDelphiPropertyParameter(AdtParser* pIdentListObj,
                             AdtParser* pUnitIdObj,
                             AdtParser* pTypeIdObj);

  AdtDelphiPropertyParameter(const AdtDelphiPropertyParameter& rCopy);
  virtual ~AdtDelphiPropertyParameter();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiPropertySpecifiers class
//  ----------------------------------------------------------------------------
class AdtDelphiPropertySpecifiers : public AdtDelphiBase
{
public:
enum  AdtType{AdtType_INDEX       = 1,
              AdtType_READ        = 2,
              AdtType_WRITE       = 3,
              AdtType_STORED      = 4,
              AdtType_DEFAULT     = 5,
              AdtType_NODEFAULT   = 6,
              AdtType_IMPLEMENTS  = 7,
              AdtType_EMPTY       = 0};

protected:
  AdtType             Type;
  AdtDelphiIdent*     Ident;
  AdtDelphiConstExpr* ConstExpr;
  AdtDelphiUnitId*    UnitId;
  AdtDelphiTypeId*    TypeId;

public:
  AdtDelphiPropertySpecifiers(AdtType nType,
                              AdtParser* pIdentObj,
                              AdtParser* pConstExprObj,
                              AdtParser* pUnitIdObj,
                              AdtParser* pTypeIdObj);

  AdtDelphiPropertySpecifiers(const AdtDelphiPropertySpecifiers& rCopy);
  virtual ~AdtDelphiPropertySpecifiers();

  virtual AdtFile&    writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&    writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiInterfaceType class
//  ----------------------------------------------------------------------------
class AdtDelphiInterfaceType : public AdtDelphiBase
{
protected:
  AdtDelphiIdentList*         IdentList;
  AdtDelphiClassMethodList*   ClassMethodList;
  AdtDelphiClassPropertyList* ClassPropertyList;

public:
  AdtDelphiInterfaceType(AdtParser* pIdentListObj,
                         AdtParser* pClassMethodListObj,
                         AdtParser* pClassPropertyListObj,
                         const char* pComment);

  AdtDelphiInterfaceType(const AdtDelphiInterfaceType& rCopy);
  virtual ~AdtDelphiInterfaceType();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtDelphiIdentList class
//  ----------------------------------------------------------------------------
class AdtDelphiIdentList : public AdtDelphiBase
{
public:
  AdtDelphiIdentList(AdtParser* pIdentObj);
  AdtDelphiIdentList(const AdtDelphiIdentList& rCopy);
  virtual ~AdtDelphiIdentList();

  void                        writeArrayBounds(AdtFile& pOutFile, int nMode, const char* pAbstractBounds = 0) const;
  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declListType(AdtDelphiIdent);
  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiIdentList::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteCPP(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiIdentList::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteFortran(pOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiIdentList::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (forAllWriteDelphi(pOutFile, nMode, ",", false, true));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiIdent class
//  ----------------------------------------------------------------------------
class AdtDelphiIdent : public AdtDelphiBase
{
protected:
  string                      EmbeddedComment;

protected:
  void                        initialise(const char* pIdentifier);
  void                        enumerateArraySizesFromString(AdtStringByStringMap& ArraySizeMap, string& rText) const;

public:
  AdtDelphiIdent(const char* pIdentifier);
  AdtDelphiIdent(const AdtDelphiIdent& rCopy);
  virtual ~AdtDelphiIdent();

  void                        writeArrayBounds(AdtFile& pOutFile, const char* pAbstractBounds = 0) const;

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  void                        enumerateArraySizes(AdtStringList& ArrayUpperBoundList, AdtStringList& ArrayLowerBoundList) const;
  void                        enumerateArraySizes(AdtStringByStringMap& ArraySizeMap) const;
  const string&               embeddedComment() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline const string& AdtDelphiIdent::embeddedComment() const
{
  return (EmbeddedComment);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiIdent::writeCPP(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());
  write(pOutFile, name().c_str());
  write(pOutFile, embeddedComment());

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiIdent::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());
  write(pOutFile, name().c_str());
  write(pOutFile, embeddedComment());

  return (pOutFile);
}


//  ----------------------------------------------------------------------------
//  AdtDelphiTypeId class
//  ----------------------------------------------------------------------------
class AdtDelphiTypeId : public AdtDelphiBase
{
protected:

public:
  AdtDelphiTypeId(const char* pTypeId);
  AdtDelphiTypeId(const AdtDelphiTypeId& rCopy);
  virtual ~AdtDelphiTypeId();

  AdtBlackBoxArgType          blackBoxArgType(bool& bIsArray) const;

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiTypeId::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiTypeId::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiTypeId::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiUnitId class
//  ----------------------------------------------------------------------------
class AdtDelphiUnitId : public AdtDelphiBase
{
protected:

public:
  AdtDelphiUnitId(const char* pUnitId);
  AdtDelphiUnitId(const AdtDelphiUnitId& rCopy);
  virtual ~AdtDelphiUnitId();

  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiUnitId::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiUnitId::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiLabelId class
//  ----------------------------------------------------------------------------
class AdtDelphiLabelId : public AdtDelphiBase
{
protected:

public:
  AdtDelphiLabelId(const char* pLabelId);
  AdtDelphiLabelId(const AdtDelphiLabelId& rCopy);
  virtual ~AdtDelphiLabelId();

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiLabelId::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiLabelId::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiLabelId::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiNumber class
//  ----------------------------------------------------------------------------
class AdtDelphiNumber : public AdtDelphiBase
{
protected:
  enum  AdtType{AdtType_BOOL      = 0,
                AdtType_INTEGER   = 1,
                AdtType_REAL      = 2};

  AdtType                     Type;

public:
  AdtDelphiNumber(const char* pNumber, int nType);
  AdtDelphiNumber(const AdtDelphiNumber& rCopy);
  virtual ~AdtDelphiNumber();

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiNumber::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiNumber::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiNumber::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiString class
//  ----------------------------------------------------------------------------
class AdtDelphiString : public AdtDelphiBase
{
protected:

public:
  AdtDelphiString(const char* pString);
  AdtDelphiString(const AdtDelphiString& rCopy);
  virtual ~AdtDelphiString();

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiString::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiString::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiString::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


//  ----------------------------------------------------------------------------
//  AdtDelphiConstExpr class
//  ----------------------------------------------------------------------------
class AdtDelphiConstExpr : public AdtDelphiBase
{
protected:
  enum  AdtType{AdtType_BOOL      = 0,
                AdtType_INTEGER   = 1,
                AdtType_REAL      = 2,
                AdtType_TEXT      = 3};

  AdtType                     Type;

public:
  AdtDelphiConstExpr(const char* pConstExpr, int nType);
  AdtDelphiConstExpr(const AdtDelphiConstExpr& rCopy);
  virtual ~AdtDelphiConstExpr();

  AdtFile&                    writeFortranTypeDeclaration(AdtFile& pOutFile,
                                                          const string& rPrefix,
                                                          const AdtDelphiIdent* pIdent) const;

  virtual AdtFile&            writeCPP(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&            writeDelphi(AdtFile& pOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstExpr::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstExpr::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (write(pOutFile, name().c_str()));
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtDelphiConstExpr::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  write(pOutFile, comment());

  return (write(pOutFile, name().c_str()));
}


#endif //__cplusplus
#endif //__ADTDELPHI_HPP
