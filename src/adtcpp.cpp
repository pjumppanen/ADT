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
//    AdtCpp.cpp
//
//  Purpose:
//    This file includes implementation of classes used to collate information
//    describing the CPP file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtcpp.hpp"
#include "adtautomate.hpp"
#include "adtexpression.hpp"
#include <sys/stat.h>


//  ----------------------------------------------------------------------------
//  Defines
//  ----------------------------------------------------------------------------
#define FORTRAN_MODE_CLASS_EXTEND_NAME  10
#define FORTRAN_MODE_ARRAY_SLICE        11
#define WRITE_MODE_INTENTS              12
#define WRITE_MODE_TYPEDECLS            13


//  ----------------------------------------------------------------------------
//  Globals
//  ----------------------------------------------------------------------------
AdtCppTranslationUnit*                      AdtCppBase::CppRootObject  = 0;
AdtCppToFortranTypeConversionByStringMapCS  AdtCppBase::FortranTypeMap;
AdtCppToFortranTypeConversionByStringMap    AdtCppBase::CppTypeMap;


//  ----------------------------------------------------------------------------

AdtIntByStringMapCS                         AdtCppTranslationUnit::ProcedureMap;
AdtIntByStringMapCS                         AdtCppTranslationUnit::FunctionMap;


//  ----------------------------------------------------------------------------
//  "C" callable function implementations
//  ----------------------------------------------------------------------------
void* adtCpp_setRoot(void* pRoot)
{
  AdtCppBase::cppRootObject(Obj(pRoot));

  return (pRoot);
}

//  ----------------------------------------------------------------------------

void* adtCpp_getRoot(void)
{
  return (Hnd(AdtCppBase::cppRootObject()));
}

//  ----------------------------------------------------------------------------

void adtCpp_releaseRoot(void)
{
  AdtCppBase::cppRootObject(0);
}

//  ----------------------------------------------------------------------------

void adtCpp_releaseObject(void* pObj)
{
  UtlReleaseReference(Obj(pObj));
}

//  ----------------------------------------------------------------------------

void* adtCppList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtCppTranslationUnit_create(void* pObj)
{
  return (Hnd(new AdtCppTranslationUnit(ObjAndRelease(pObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMacro_create(const char* pIdentifier, void* pExpressionListObj, void* pStatementSeqObj, void* pSimpleDeclarationListObj)
{
  return (Hnd(new AdtCppMacro(pIdentifier, ObjAndRelease(pExpressionListObj), ObjAndRelease(pStatementSeqObj), ObjAndRelease(pSimpleDeclarationListObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppSimpleDeclarationList_create(void* pSimpleDeclarationObj)
{
  return (Hnd(new AdtCppSimpleDeclarationList(ObjAndRelease(pSimpleDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppPostfixExpression_create(void* pExpressionObj, void* pPostfixExpressionObj, void* pDirectedExpressionObj, int nIncrement, const char* pLiteral)
{
  return (Hnd(new AdtCppPostfixExpression(ObjAndRelease(pExpressionObj), ObjAndRelease(pPostfixExpressionObj), ObjAndRelease(pDirectedExpressionObj), nIncrement != 0, pLiteral), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppExpressionList_create(void* pAssignmentExpressionObj)
{
  return (Hnd(new AdtCppExpressionList(ObjAndRelease(pAssignmentExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDirectedExpression_create(void* pDeclaratorExpressionObj)
{
  return (Hnd(new AdtCppDirectedExpression(ObjAndRelease(pDeclaratorExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclaratorExpression_create(const char* pIdentifier, void* pExpressionListObj, void* pDeclaratorExpressionDimsObj, int nQualified, int nHasBrackets, const char* pComment)
{
  return (Hnd(new AdtCppDeclaratorExpression(pIdentifier, ObjAndRelease(pExpressionListObj), ObjAndRelease(pDeclaratorExpressionDimsObj), nQualified != 0, nHasBrackets != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclaratorExpressionDims_create(void* pExpressionObj)
{
  return (Hnd(new AdtCppDeclaratorExpressionDims(ObjAndRelease(pExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppUnaryExpression_create(void* pPostfixExpressionObj, void* pUnaryExpressionObj, void* pUnaryOperatorObj, void* pExpressionObj, int nIncrement)
{
  return (Hnd(new AdtCppUnaryExpression(ObjAndRelease(pPostfixExpressionObj), ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pUnaryOperatorObj), ObjAndRelease(pExpressionObj), nIncrement != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppUnaryOperator_create(int nOp)
{
  return (Hnd(new AdtCppUnaryOperator((AdtCppUnaryOp)nOp), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMultiplicativeExpression_create(int nOp, void* pUnaryExpressionObj, void* pMultiplicativeExpressionObj)
{
  return (Hnd(new AdtCppMultiplicativeExpression((AdtCppMultiplicativeOp)nOp, ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pMultiplicativeExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppAdditiveExpression_create(int nOp, void* pMultiplicativeExpressionObj, void* pAdditiveExpressionObj)
{
  return (Hnd(new AdtCppAdditiveExpression((AdtCppAdditiveOp)nOp, ObjAndRelease(pMultiplicativeExpressionObj), ObjAndRelease(pAdditiveExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppShiftExpression_create(int nOp, void* pAdditiveExpressionObj, void* pShiftExpressionObj)
{
  return (Hnd(new AdtCppShiftExpression((AdtCppShiftOp)nOp, ObjAndRelease(pAdditiveExpressionObj), ObjAndRelease(pShiftExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppRelationalExpression_create(int nOp, void* pShiftExpressionObj, void* pRelationalExpressionObj)
{
  return (Hnd(new AdtCppRelationalExpression((AdtCppRelationalOp)nOp, ObjAndRelease(pShiftExpressionObj), ObjAndRelease(pRelationalExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppEqualityExpression_create(int nOp, void* pRelationalExpressionObj, void* pEqualityExpressionObj)
{
  return (Hnd(new AdtCppEqualityExpression((AdtCppEqualityOp)nOp, ObjAndRelease(pRelationalExpressionObj), ObjAndRelease(pEqualityExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppAndExpression_create(void* pEqualityExpressionObj, void* pAndExpressionObj)
{
  return (Hnd(new AdtCppAndExpression(ObjAndRelease(pEqualityExpressionObj), ObjAndRelease(pAndExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppExclusiveOrExpression_create(void* pAndExpressionObj, void* pExclusiveOrExpressionObj)
{
  return (Hnd(new AdtCppExclusiveOrExpression(ObjAndRelease(pAndExpressionObj), ObjAndRelease(pExclusiveOrExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInclusiveOrExpression_create(void* pExclusiveOrExpressionObj, void* pInclusiveOrExpressionObj)
{
  return (Hnd(new AdtCppInclusiveOrExpression(ObjAndRelease(pExclusiveOrExpressionObj), ObjAndRelease(pInclusiveOrExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppLogicalAndExpression_create(void* pInclusiveOrExpressionObj, void* pLogicalAndExpressionObj)
{
  return (Hnd(new AdtCppLogicalAndExpression(ObjAndRelease(pInclusiveOrExpressionObj), ObjAndRelease(pLogicalAndExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppLogicalOrExpression_create(void* pLogicalAndExpressionObj, void* pLogicalOrExpressionObj)
{
  return (Hnd(new AdtCppLogicalOrExpression(ObjAndRelease(pLogicalAndExpressionObj), ObjAndRelease(pLogicalOrExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppConditionalExpression_create(void* pLogicalOrExpressionObj, void* pExpressionObj, void* pAssignmentExpressionObj)
{
  return (Hnd(new AdtCppConditionalExpression(ObjAndRelease(pLogicalOrExpressionObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pAssignmentExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppAssignmentExpression_create(void* pConditionalExpressionObj, void* pLogicalOrExpressionObj, void* pAssignmentOperator, void* pAssignmentExpressionObj)
{
  return (Hnd(new AdtCppAssignmentExpression(ObjAndRelease(pConditionalExpressionObj), ObjAndRelease(pLogicalOrExpressionObj), ObjAndRelease(pAssignmentOperator), ObjAndRelease(pAssignmentExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppAssignmentOperator_create(int nOp)
{
  return (Hnd(new AdtCppAssignmentOperator((AdtCppAssignmentOp)nOp), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppExpression_create(void* pAssignmentExpressionObj, void* pExpressionObj)
{
  return (Hnd(new AdtCppExpression(ObjAndRelease(pAssignmentExpressionObj), ObjAndRelease(pExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppConstantExpression_create(void* pConditionalExpressionObj)
{
  return (Hnd(new AdtCppConstantExpression(ObjAndRelease(pConditionalExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppStatement_create(void* pLabeledStatementObj, void* pExpressionStatementObj, void* pCompoundStatementObj, void* pSelectionStatementObj, void* pIterationStatementObj, void* pJumpStatementObj, void* pDeclarationStatementObj)
{
  return (Hnd(new AdtCppStatement(ObjAndRelease(pLabeledStatementObj), ObjAndRelease(pExpressionStatementObj), ObjAndRelease(pCompoundStatementObj), ObjAndRelease(pSelectionStatementObj), ObjAndRelease(pIterationStatementObj), ObjAndRelease(pJumpStatementObj), ObjAndRelease(pDeclarationStatementObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppLabeledStatement_create(void* pConstantExpressionObj, void* pStatementObj, const char* pIdentifier, int nIsDefault, const char* pComment)
{
  return (Hnd(new AdtCppLabeledStatement(ObjAndRelease(pConstantExpressionObj), ObjAndRelease(pStatementObj), pIdentifier, nIsDefault != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppExpressionStatement_create(void* pExpressionObj, const char* pComment)
{
  return (Hnd(new AdtCppExpressionStatement(ObjAndRelease(pExpressionObj), pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppCompoundStatement_create(void* pStatementSeqObj, const char* pComment)
{
  return (Hnd(new AdtCppCompoundStatement(ObjAndRelease(pStatementSeqObj), pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppStatementSeq_create(void* pStatementObj)
{
  return (Hnd(new AdtCppStatementSeq(ObjAndRelease(pStatementObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppSelectionStatement_create(void* pExpressionObj, void* pStatementObj, void* pStatement2Obj, int nIsIf, const char* pComment)
{
  return (Hnd(new AdtCppSelectionStatement(ObjAndRelease(pExpressionObj), ObjAndRelease(pStatementObj), ObjAndRelease(pStatement2Obj), nIsIf != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppIterationStatement_create(void* pForInitStatementObj, void* pExpressionObj, void* pExpression2Obj, void* pStatementObj, int nIsDo, const char* pComment)
{
  return (Hnd(new AdtCppIterationStatement(ObjAndRelease(pForInitStatementObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pExpression2Obj), ObjAndRelease(pStatementObj), nIsDo != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppForInitStatement_create(void* pExpressionStatementObj, void* pSimpleDeclarationObj)
{
  return (Hnd(new AdtCppForInitStatement(ObjAndRelease(pExpressionStatementObj), ObjAndRelease(pSimpleDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppJumpStatement_create(void* pExpressionObj, const char* pIndentifier, int nType, const char* pComment)
{
  return (Hnd(new AdtCppJumpStatement(ObjAndRelease(pExpressionObj), pIndentifier, (AdtCppJumpType)nType, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclarationStatement_create(void* pBlockDeclarationObj)
{
  return (Hnd(new AdtCppDeclarationStatement(ObjAndRelease(pBlockDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclarationSeq_create(void* pDeclarationObj)
{
  return (Hnd(new AdtCppDeclarationSeq(ObjAndRelease(pDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclaration_create(void* pBlockDeclarationObj, void* pFunctionDefinitionObj, void* pLinkageSpecificationObj, void* pNamespaceDefinitionObj, const char* pComment)
{
  return (Hnd(new AdtCppDeclaration(ObjAndRelease(pBlockDeclarationObj), ObjAndRelease(pFunctionDefinitionObj), ObjAndRelease(pLinkageSpecificationObj), ObjAndRelease(pNamespaceDefinitionObj), pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppBlockDeclaration_create(void* pSimpleDeclarationObj, void* pAsmDefinitionObj, void* pNamespaceAliasDefinitionObj, void* pUsingDeclarationObj, void* pUsingDirectiveObj)
{
  return (Hnd(new AdtCppBlockDeclaration(ObjAndRelease(pSimpleDeclarationObj), ObjAndRelease(pAsmDefinitionObj), ObjAndRelease(pNamespaceAliasDefinitionObj), ObjAndRelease(pUsingDeclarationObj), ObjAndRelease(pUsingDirectiveObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppSimpleDeclaration_create(void* pClassSpecifierObj, void* pEnumSpecifierObj, void* pSimpleTypeSpecifierObj, void* pInitDeclaratorListObj, void* pDeclModifierListObj, int nHasTypeDef, const char* pComment)
{
  return (Hnd(new AdtCppSimpleDeclaration(ObjAndRelease(pClassSpecifierObj), ObjAndRelease(pEnumSpecifierObj), ObjAndRelease(pSimpleTypeSpecifierObj), ObjAndRelease(pInitDeclaratorListObj), ObjAndRelease(pDeclModifierListObj), nHasTypeDef != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

int adtCppSimpleDeclaration_isTypeDef(void* pCppSimpleDeclarationObj, const char** ppAliasName)
{
  bool                      bIsTypeDef                = false;
  AdtCppSimpleDeclaration*  pAdtCppSimpleDeclaration  = (AdtCppSimpleDeclaration*)pCppSimpleDeclarationObj;

  if (pAdtCppSimpleDeclaration != 0)
  {
    bIsTypeDef = pAdtCppSimpleDeclaration->isTypeDef(ppAliasName);
  }

  return (bIsTypeDef ? 1 : 0);
}

//  ----------------------------------------------------------------------------

void* adtCppDeclModifier_create(int nType, const char* pComment)
{
  return (Hnd(new AdtCppDeclModifier((AdtCppDeclModifierType)nType, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclModifierList_create(void* pDeclModifierObj)
{
  return (Hnd(new AdtCppDeclModifierList(ObjAndRelease(pDeclModifierObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppClassSpecifier_create(void* pClassKeyObj, void* pBaseSpecifierListObj, void* pMemberSpecificationObj, int nWithBrackets)
{
  return (Hnd(new AdtCppClassSpecifier(ObjAndRelease(pClassKeyObj), ObjAndRelease(pBaseSpecifierListObj), ObjAndRelease(pMemberSpecificationObj), nWithBrackets != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppEnumSpecifierName_create(const char* pIdentifier, int nQualified, const char* pComment)
{
  return (Hnd(new AdtCppEnumSpecifierName(pIdentifier, nQualified != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppEnumSpecifier_create(void* pEnumeratorListObj, void* pEnumSpecifierName, int nWithBrackets)
{
  return (Hnd(new AdtCppEnumSpecifier(ObjAndRelease(pEnumeratorListObj), ObjAndRelease(pEnumSpecifierName), nWithBrackets != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppSimpleTypeSpecifier_create(const char* pIdentifier, int nType, int nByRef, const char* pComment)
{
  return (Hnd(new AdtCppSimpleTypeSpecifier(pIdentifier, (AdtCppSimpleType)nType, nByRef != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppEnumeratorList_create(void* pEnumeratorDefinitionObj)
{
  return (Hnd(new AdtCppEnumeratorList(ObjAndRelease(pEnumeratorDefinitionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppEnumeratorDefinition_create(void* pConstantExpressionObj, const char* pIdentifier, const char* pComment)
{
  return (Hnd(new AdtCppEnumeratorDefinition(ObjAndRelease(pConstantExpressionObj), pIdentifier, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppNamespaceDefinition_create(void* pDeclarationSeqObj, const char* pIdentifier, const char* pComment)
{
  return (Hnd(new AdtCppNamespaceDefinition(ObjAndRelease(pDeclarationSeqObj), pIdentifier, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppNamespaceAliasDefinition_create(const char* pIdentifier, const char* pQualifiedIdentifier, const char* pComment)
{
  return (Hnd(new AdtCppNamespaceAliasDefinition(pIdentifier, pQualifiedIdentifier, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppUsingDeclaration_create(const char* pQualifiedIdentifier, int nWithTypename, const char* pComment)
{
  return (Hnd(new AdtCppUsingDeclaration(pQualifiedIdentifier, nWithTypename != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppUsingDirective_create(const char* pIdentifier, int nQualified, const char* pComment)
{
  return (Hnd(new AdtCppUsingDirective(pIdentifier, nQualified != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppAsmDefinition_create(const char* pStringLiteral, const char* pComment)
{
  return (Hnd(new AdtCppAsmDefinition(pStringLiteral, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppLinkageSpecification_create(void* pDeclarationSeqObj, void* pDeclarationObj, const char* pStringLiteral, const char* pComment)
{
  return (Hnd(new AdtCppLinkageSpecification(ObjAndRelease(pDeclarationSeqObj), ObjAndRelease(pDeclarationObj), pStringLiteral, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInitDeclaratorList_create(void* pInitDeclaratorObj)
{
  return (Hnd(new AdtCppInitDeclaratorList(ObjAndRelease(pInitDeclaratorObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInitDeclarator_create(void* pDeclaratorObj, void* pInitializerObj)
{
  return (Hnd(new AdtCppInitDeclarator(ObjAndRelease(pDeclaratorObj), ObjAndRelease(pInitializerObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclarator_create(void* pParameterDeclarationClauseObj, void* pExpressionListObj, void* pDeclaratorDimsObj, const char* pIdentifier, int nWithBrackets, int nQualified, int nIsObj, int nIsVirtual, int nType, const char* pComment, int nInitQualifiedName)
{
  return (Hnd(new AdtCppDeclarator(ObjAndRelease(pParameterDeclarationClauseObj), ObjAndRelease(pExpressionListObj), ObjAndRelease(pDeclaratorDimsObj), pIdentifier, nWithBrackets != 0, nQualified != 0, nIsObj != 0, nIsVirtual != 0, (AdtCppDeclaratorCV_Type)nType, pComment, nInitQualifiedName != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppDeclaratorDims_create(void* pConstantExpressionObj, void* pDeclaratorDimsObj)
{
  return (Hnd(new AdtCppDeclaratorDims(ObjAndRelease(pConstantExpressionObj), ObjAndRelease(pDeclaratorDimsObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppParameterDeclarationClause_create(void* pParameterDeclarationListObj, int nHasEllipsis, int nHasComma)
{
  return (Hnd(new AdtCppParameterDeclarationClause(ObjAndRelease(pParameterDeclarationListObj), nHasEllipsis != 0, nHasComma != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppParameterDeclarationList_create(void* pParameterDeclarationObj)
{
  return (Hnd(new AdtCppParameterDeclarationList(ObjAndRelease(pParameterDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppParameterDeclaration_create(void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pDeclaratorObj, void* pAssignmentExpressionObj)
{
  return (Hnd(new AdtCppParameterDeclaration(ObjAndRelease(pDeclModifierListObj), ObjAndRelease(pSimpleTypeSpecifierObj), ObjAndRelease(pDeclaratorObj), ObjAndRelease(pAssignmentExpressionObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppFunctionDefinition_create(void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pDeclaratorObj, void* pCtorInitializerObj, void* pFunctionBodyObj, int nHasSemiColon)
{
  return (Hnd(new AdtCppFunctionDefinition(ObjAndRelease(pDeclModifierListObj), ObjAndRelease(pSimpleTypeSpecifierObj), ObjAndRelease(pDeclaratorObj), ObjAndRelease(pCtorInitializerObj), ObjAndRelease(pFunctionBodyObj), nHasSemiColon != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppFunctionBody_create(void* pCompoundStatementObj)
{
  return (Hnd(new AdtCppFunctionBody(ObjAndRelease(pCompoundStatementObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInitializer_create(void* pInitializerClauseObj, void* pExpressionListObj)
{
  return (Hnd(new AdtCppInitializer(ObjAndRelease(pInitializerClauseObj), ObjAndRelease(pExpressionListObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInitializerClause_create(void* pAssignmentExpressionObj, void* pInitializerListObj, int nHasComma)
{
  return (Hnd(new AdtCppInitializerClause(ObjAndRelease(pAssignmentExpressionObj), ObjAndRelease(pInitializerListObj), nHasComma != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppInitializerList_create(void* pInitializerClauseObj)
{
  return (Hnd(new AdtCppInitializerList(ObjAndRelease(pInitializerClauseObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppClassKey_create(int nType, const char* pIdentifier, int nQualified, const char* pComment)
{
  return (Hnd(new AdtCppClassKey((AdtCppClassKeyType)nType, pIdentifier, nQualified != 0, pComment), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemberSpecification_create(void* pMemberDeclarationObj)
{
  return (Hnd(new AdtCppMemberSpecification(ObjAndRelease(pMemberDeclarationObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemberDeclaration_create(void* pClassSpecifierObj, void* pEnumSpecifierObj, void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pMemberDeclarationListObj, void* pFunctionDefinitionObj, void* pUsingDeclarationObj,int nType, int nHasSemicolon)
{
  return (Hnd(new AdtCppMemberDeclaration(ObjAndRelease(pClassSpecifierObj), ObjAndRelease(pEnumSpecifierObj), ObjAndRelease(pDeclModifierListObj), ObjAndRelease(pSimpleTypeSpecifierObj), ObjAndRelease(pMemberDeclarationListObj), ObjAndRelease(pFunctionDefinitionObj), ObjAndRelease(pUsingDeclarationObj), (AdtCppMemberScopeType)nType, nHasSemicolon != 0), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemberDeclarationList_create(void* pMemberDeclaratorObj)
{
  return (Hnd(new AdtCppMemberDeclarationList(ObjAndRelease(pMemberDeclaratorObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemberDeclarator_create(void* pDeclaratorObj, const char* pIdentifier)
{
  return (Hnd(new AdtCppMemberDeclarator(ObjAndRelease(pDeclaratorObj), pIdentifier), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppBaseSpecifierList_create(void* pBaseSpecifierObj)
{
  return (Hnd(new AdtCppBaseSpecifierList(ObjAndRelease(pBaseSpecifierObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppBaseSpecifier_create(int nType, int nVirtual, int nQualified, const char* pIdentifier)
{
  return (Hnd(new AdtCppBaseSpecifier((AdtCppMemberScopeType)nType, nVirtual != 0, nQualified != 0, pIdentifier), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppCtorInitializer_create(void* pMemInitializerListObj)
{
  return (Hnd(new AdtCppCtorInitializer(ObjAndRelease(pMemInitializerListObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemInitializerList_create(void* pMemInitializerObj)
{
  return (Hnd(new AdtCppMemInitializerList(ObjAndRelease(pMemInitializerObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemInitializer_create(void* pMemInitializerIdObj, void* pExpressionListObj)
{
  return (Hnd(new AdtCppMemInitializer(ObjAndRelease(pMemInitializerIdObj), ObjAndRelease(pExpressionListObj)), yyCpp_lineNumber(), yyCpp_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtCppMemInitializerId_create(int nQualified, const char* pIdentifier)
{
  return (Hnd(new AdtCppMemInitializerId(nQualified != 0, pIdentifier), yyCpp_lineNumber(), yyCpp_fileName()));
}


//  ----------------------------------------------------------------------------
//  AdtCppToFortranTypeConversion method implementations
//  ----------------------------------------------------------------------------
void AdtCppToFortranTypeConversion::initialise()
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
//  AdtCppBase method implementations
//  ----------------------------------------------------------------------------
AdtFile& AdtCppBase::forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
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

      if ((pObj != 0) && pObj->isType("AdtCppBase"))
      {
        AdtCppBase* pCppObj = (AdtCppBase*)pObj;

        pCppObj->writeFortran(pOutFile, nMode);

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

AdtFile& AdtCppBase::forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast) const
{
  if (pOutFile.isOpen())
  {
    AdtParserPtrListConstIter Iter;
    size_t                    nSize           = objList().size();
    int                       cn              = 0;
    bool                      bPreLineSpace   = false;
    bool                      bPostLineSpace  = false;
    AdtCppBase*               pLastCppObj     = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser* pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtCppBase"))
      {
        AdtCppBase* pCppObj = (AdtCppBase*)pObj;

        if (bNewline && (cn > 1))
        {
          pCppObj->linespace(pOutFile, bPreLineSpace, pLastCppObj, true);
        }

        pCppObj->writeCPP(pOutFile, nMode);

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
            pCppObj->linespace(pOutFile, bPostLineSpace, pLastCppObj, false);

            bPreLineSpace   = bPostLineSpace;
            bPostLineSpace  = false;
          }
        }

        pLastCppObj = pCppObj;
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtCppBase::AdtCppBase()
 : AdtParser()
{

}

//  ----------------------------------------------------------------------------

AdtCppBase::~AdtCppBase()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtCppBase::initialise()
{
  //Do whatever is required. Possibly not needed anymore
}

//  ----------------------------------------------------------------------------

void AdtCppBase::nameToFortran(const char* pName, string& rConvertedName)
{
  int nPos;

  // Replace any :: constructs with __ to convert from C++ to fortran compatible naming
  rConvertedName = pName;

  for (nPos = (int)rConvertedName.find("::") ; nPos >= 0 ; nPos = (int)rConvertedName.find("::"))
  {
    rConvertedName.replace(nPos, 2, "__");
  }
}

//  ----------------------------------------------------------------------------

void AdtCppBase::prefixFromQualifiedName(const char* pName, string& rPrefix)
{
  if (pName != 0)
  {
    const char* pPrefixStart  = pName;
    const char* pPrefixEnd    = ::strstr(pName, "::");
    size_t      nLength       = (pPrefixEnd != 0) ? pPrefixEnd - pPrefixStart : 0;
    string      sPrefix(pPrefixStart, 0, nLength);

    sPrefix.trim("\n\r\t");

    rPrefix = sPrefix;
  }
}

//  ----------------------------------------------------------------------------

AdtCppStatementSeq* AdtCppBase::expressionBuild(const char* pCodeString)
{
  AdtCppStatementSeq* pCodeObject = 0;

  if (pCodeString != 0)
  {
    AdtCpp      CppContext;
    AdtParser*  pRoot = 0;
    string      rCodeString("void dummy()\n{\n");

    rCodeString += pCodeString;
    rCodeString += "\n}\n";

    CppContext.parseString(pRoot,
                           rCodeString);

    if (pRoot != 0)
    {
      pCodeObject = (AdtCppStatementSeq*)pRoot->findObject("AdtCppStatementSeq");

      if (pCodeObject != 0)
      {
        pCodeObject->lock();
        pCodeObject->replaceInParent(0);

        if (0)
        {
          string  sTest;
          AdtFile CppOut;

          if (CppOut.open(sTest))
          {
            pCodeObject->writeCPP(CppOut);
            CppOut.close();
          }
        }
      }
    }
  }

  return (pCodeObject);
}

//  ----------------------------------------------------------------------------

AdtCppStatement* AdtCppBase::createSimpleVariableDeclarationStatementFrom(AdtParser* pInitDeclaratorObj)
{
  AdtCppStatement* pStatement = 0;

  if ((pInitDeclaratorObj != 0) &&
       pInitDeclaratorObj->isType("AdtCppInitDeclarator"))
  {
    AdtParser*  pSimpleDeclarationObj = pInitDeclaratorObj->findAscendantWithClassLineage("AdtCppInitDeclaratorList,AdtCppSimpleDeclaration");

    if (pSimpleDeclarationObj != 0)
    {
      AdtParser* pSimpleDeclarationCopy   = pSimpleDeclarationObj->copy();

      AdtParser* pBlockDeclarationObj     = new AdtCppBlockDeclaration(pSimpleDeclarationCopy,
                                                                       0,
                                                                       0,
                                                                       0,
                                                                       0);

      AdtParser* pDeclarationStatementObj = new AdtCppDeclarationStatement(pBlockDeclarationObj);

      pStatement = new AdtCppStatement(0,
                                       0,
                                       0,
                                       0,
                                       0,
                                       0,
                                       pDeclarationStatementObj);

      UtlReleaseReference(pDeclarationStatementObj);
      UtlReleaseReference(pBlockDeclarationObj);
      UtlReleaseReference(pSimpleDeclarationCopy);

      if (pStatement != 0)
      {
        AdtParser*  pInitDeclaratorListObj = pInitDeclaratorObj->findAscendantWithClassLineage("AdtCppInitDeclaratorList");

        if (pInitDeclaratorListObj != 0)
        {
          pInitDeclaratorListObj->removeAllExcept(pInitDeclaratorObj->name());
        }
        else
        {
          FAIL();
        }
      }
    }
  }

  return (pStatement);
}

//  ----------------------------------------------------------------------------

void AdtCppBase::addFortranTypeMap(const string& rCppType,
                                   const string& rFortranType,
                                   const string& rFortranSize)
{
  FortranTypeMap.insert(AdtCppToFortranTypeConversionStringPair(rCppType, AdtCppToFortranTypeConversion(rCppType, rFortranType, rFortranSize)));
  CppTypeMap.insert(AdtCppToFortranTypeConversionStringPair(rFortranType + rFortranSize, AdtCppToFortranTypeConversion(rCppType, rFortranType, rFortranSize)));
}

//  ----------------------------------------------------------------------------

void AdtCppBase::cppRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(CppRootObject);

  CppRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtCppTranslationUnit"))
    {
      CppRootObject = (AdtCppTranslationUnit*)pRoot;
      CppRootObject->lock();
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppTranslationUnit* AdtCppBase::cppRootObject()
{
  return (CppRootObject);
}

//  ----------------------------------------------------------------------------

bool AdtCppBase::mapTypesToFortran(const char* pTypeName,
                                   const char*& pType,
                                   const char*& pDimension)
{
  bool                                                bFound  = false;
  AdtCppToFortranTypeConversionByStringMapCSConstIter Iter    = FortranTypeMap.find(pTypeName);

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

bool AdtCppBase::mapTypesToCpp(const char* pTypeName,
                               size_t nDimension,
                               const char*& pType)
{
  char  pDimension[16] = {0};

  ::sprintf(pDimension, "%zd", nDimension);

  bool                                                bFound        = false;
  string                                              sTypeAndSize  = string(pTypeName) + pDimension;
  AdtCppToFortranTypeConversionByStringMapConstIter   Iter          = CppTypeMap.find(sTypeAndSize);

  if (Iter != CppTypeMap.end())
  {
    pType       = (*Iter).second.CppType;
    bFound      = true;
  }
  else
  {
    pType       = 0;
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

void AdtCppBase::nameWithComment(const char* pName, string* pComment)
{
  if (pName != 0)
  {
    AdtCppSplitNameAndComment NameAndComment(pName);

    mapName(NameAndComment.name(), false);

    if (pComment != 0)
    {
      *pComment = NameAndComment.comment();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppBase::mapName(const char* pName, bool bWithComment)
{
  if (AdtCppScopeManager::mapNames() && (pName != 0) && (AdtCppScopeManager::globalScopeManager() != 0))
  {
    if (bWithComment)
    {
      string                    sMappedSymbolName;
      AdtCppSplitNameAndComment NameAndComment(pName);

      AdtCppScopeManager::globalScopeManager()->mapSymbolCase(sMappedSymbolName, NameAndComment.name());

      sMappedSymbolName += NameAndComment.comment();

      name(sMappedSymbolName);
    }
    else
    {
      string  sMappedSymbolName;

      AdtCppScopeManager::globalScopeManager()->mapSymbolCase(sMappedSymbolName, pName);

      name(sMappedSymbolName);
    }
  }
  else
  {
    name(pName);
  }
}

//  ----------------------------------------------------------------------------

void AdtCppBase::linespace(AdtFile& pOutFile,
                           bool& bLineSpace,
                           const AdtCppBase* pLastObj,
                           bool bPre) const
{
  bLineSpace = false;
}

//  ----------------------------------------------------------------------------

bool AdtCppBase::simpleLineageTo(const char* pParentClass) const
{
  bool bSimple = false;

  if ((Parent != 0) && this->isSimple())
  {
    if (Parent->isType(pParentClass))
    {
      bSimple = true;
    }
    else
    {
      const AdtCppBase* pParent = (const AdtCppBase*)Parent;

      bSimple = pParent->simpleLineageTo(pParentClass);
    }
  }

  return (bSimple);
}

//  ----------------------------------------------------------------------------

bool AdtCppBase::parentSimpleLineageTo(const char* pParentClass) const
{
  bool bSimple = false;

  if (Parent != 0)
  {
    const AdtCppBase* pParent = (const AdtCppBase*)Parent;

    bSimple = pParent->simpleLineageTo(pParentClass);
  }

  return (bSimple);
}

//  ----------------------------------------------------------------------------

bool AdtCppBase::isSimple() const
{
  return (false);
}

//  ----------------------------------------------------------------------------

implType(AdtCppBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtCppCheckDeclaration method implementations
//  ----------------------------------------------------------------------------
void AdtCppCheckDeclaration::initialiseQualifiedName()
{
  string sQualifiedName = name();

  QualifiedName = 0;

  AdtCppScopeManager::globalScopeManager()->qualifyName(sQualifiedName);
  AdtCommon::allocString(sQualifiedName, &QualifiedName);
}

//  ----------------------------------------------------------------------------

AdtCppCheckDeclaration::AdtCppCheckDeclaration()
 : AdtCppBase()
{
  QualifiedName = 0;
}

//  ----------------------------------------------------------------------------

AdtCppCheckDeclaration::AdtCppCheckDeclaration(const AdtCppCheckDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  QualifiedName = rCopy.QualifiedName;
}

//  ----------------------------------------------------------------------------

AdtCppCheckDeclaration::~AdtCppCheckDeclaration()
{

}

//  ----------------------------------------------------------------------------

implType(AdtCppCheckDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppEmbeddedComment method implementations
//  ----------------------------------------------------------------------------
void AdtCppEmbeddedComment::initialise(const char* pIdentifier)
{
  string  sEmbeddedComment;

  EmbeddedComment = 0;

  nameWithComment(pIdentifier, &sEmbeddedComment);
  AdtCommon::allocString(sEmbeddedComment, &EmbeddedComment);
}

//  ----------------------------------------------------------------------------

void AdtCppEmbeddedComment::enumerateArraySizesFromString(AdtStringByStringMap& ArraySizeMap, string& rText) const
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

AdtCppEmbeddedComment::AdtCppEmbeddedComment()
 : AdtCppCheckDeclaration()
{
  EmbeddedComment = 0;
}

//  ----------------------------------------------------------------------------

AdtCppEmbeddedComment::AdtCppEmbeddedComment(const char* pIdentifier)
 : AdtCppCheckDeclaration()
{
  EmbeddedComment = 0;

  initialise(pIdentifier);
}

//  ----------------------------------------------------------------------------

AdtCppEmbeddedComment::AdtCppEmbeddedComment(const AdtCppEmbeddedComment& rCopy)
 : AdtCppCheckDeclaration(rCopy)
{
  EmbeddedComment = rCopy.EmbeddedComment;
}

//  ----------------------------------------------------------------------------

AdtCppEmbeddedComment::~AdtCppEmbeddedComment()
{

}

//  ----------------------------------------------------------------------------

void AdtCppEmbeddedComment::writeArrayBounds(AdtFile& pOutFile, const char* pAbstractBounds) const
{
  //This method is used principally to create the variable definitions in the
  //MODULE and in function bodies. This method should therefore include the
  //lower bound attributes in the comment (if there is any).
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar           = sComment;
    const char* ppDelimeters[]  = {":", "*/", ",", ""};

    if (AdtParse::matchWord(pChar, "/*"))
    {
      pOutFile.write("(");

      while (*pChar != '\0')
      {
        string  sName;
        char    sBuffer[32]    = {0};
        int     nLowerBound    = 1;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::extractWord(sName, ppDelimeters, pChar);
//        AdtParse::extractWord(sName, ":*,", pChar);

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

          AdtParse::extractWord(sName, ppDelimeters, pChar);
//          AdtParse::extractWord(sName, ":*,", pChar);
        }

        pChar = AdtParse::nextWord(pChar);

        if (AdtParse::matchWord(pChar, "*/"))
        {
          //Take out end of comment
        }
//        else if (AdtParse::matchWord(pChar, "*"))
//        {
//          //Is variable size array definition
//        }

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

void AdtCppEmbeddedComment::enumerateArraySizes(AdtStringList& ArrayUpperBoundList, AdtStringList& ArrayLowerBoundList) const
{
  //This method is used to obtain the array size and lower bound. This is used
  //internally for determining how to do array slices.
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar             = sComment;
    const char* ppDelimiters[]    = {":", "*/", ",", ""};
    const char* ppOpenBrackets[]  = {"(", "[", ""};
    const char* ppCloseBrackets[] = {")", "]", ""};

    if (AdtParse::matchWord(pChar, "/*"))
    {
      while (*pChar != '\0')
      {
        string sName;
        string sLowerBound;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::bracketedExtractWord(sName,
                                       ppDelimiters,
                                       ppOpenBrackets,
                                       ppCloseBrackets,
                                       pChar);

        if (AdtParse::matchWord(pChar, ":"))
        {
          ArrayLowerBoundList.push_back(sName);

          //Take out the lower bound
          pChar = AdtParse::nextWord(pChar);

          AdtParse::bracketedExtractWord(sName,
                                         ppDelimiters,
                                         ppOpenBrackets,
                                         ppCloseBrackets,
                                         pChar);
        }
        else
        {
          ArrayLowerBoundList.push_back("1");
        }

        pChar = AdtParse::nextWord(pChar);

        if (AdtParse::matchWord(pChar, "*/"))
        {
          //Take out end of comment
        }

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

void AdtCppEmbeddedComment::enumerateArraySizes(AdtStringByStringMap& ArraySizeMap) const
{
  //This method is used principally to create the parameters in the MODULE
  //that correspond to array size constants.
  if (embeddedComment().length() > 0)
  {
    string      sComment(embeddedComment());
    const char* pChar             = sComment;
    const char* ppDelimiters[]    = {":", "*/", ",", ""};
    const char* ppOpenBrackets[]  = {"(", "[", ""};
    const char* ppCloseBrackets[] = {")", "]", ""};

    if (AdtParse::matchWord(pChar, "/*"))
    {
      while (*pChar != '\0')
      {
        string sName;
        string sLowerBound;

        pChar = AdtParse::nextWord(pChar);

        AdtParse::bracketedExtractWord(sName,
                                       ppDelimiters,
                                       ppOpenBrackets,
                                       ppCloseBrackets,
                                       pChar);

        enumerateArraySizesFromString(ArraySizeMap, sName);

        if (AdtParse::matchWord(pChar, ":"))
        {
          //Take out the lower bound
          pChar = AdtParse::nextWord(pChar);

          AdtParse::bracketedExtractWord(sName,
                                         ppDelimiters,
                                         ppOpenBrackets,
                                         ppCloseBrackets,
                                         pChar);

          enumerateArraySizesFromString(ArraySizeMap, sName);
        }

        pChar = AdtParse::nextWord(pChar);

        if (AdtParse::matchWord(pChar, "*/"))
        {
          //Take out end of comment
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

implType(AdtCppEmbeddedComment, AdtCppCheckDeclaration);


//  ----------------------------------------------------------------------------
//  AdtCppTranslationUnit method implementations
//  ----------------------------------------------------------------------------
void AdtCppTranslationUnit::buildMacroMap(AdtParserPtrByStringMultiMapCS& rMacroMap) const
{
  AdtParserPtrListConstIter Iter;

  rMacroMap.clear();

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if ((pObj != 0) && pObj->isType("AdtCppMacro"))
    {
      rMacroMap.insert(AdtParserPtrByStringMapCS::value_type(pObj->name(), AdtParserContext(pObj)));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppTranslationUnit::writeArraySizes(AdtFile& rOutFile,
                                            const AdtParserPtrByStringMap& rFunctionsMap,
                                            const AdtParserPtrByStringMap& rVarsMap) const
{
  AdtParserPtrList                  IdentList;
  AdtParserPtrListIter              ListIter;
  AdtParserPtrByStringMapConstIter  MapIter;

  //Search variable definitions.
  for (MapIter = rVarsMap.begin() ; MapIter != rVarsMap.end() ; ++MapIter)
  {
    AdtParser* pObj = (*MapIter).second;

    if (pObj != 0)
    {
      pObj->findObjects(IdentList, "AdtCppDeclarator", pObj->name());
    }
  }

  //Search procedures for local definitions of variables and constants.
  for (MapIter = rFunctionsMap.begin() ; MapIter != rFunctionsMap.end() ; ++MapIter)
  {
    AdtParser* pObj = (*MapIter).second;

    if ((pObj != 0) && pObj->isType("AdtCppFunctionDefinition"))
    {
      AdtCppFunctionDefinition* pFunctionObj = (AdtCppFunctionDefinition*)pObj;

      pFunctionObj->enumerateLocalObjects(IdentList);
    }
  }

  AdtStringByStringMap      ArraySizeMap;
  AdtStringByStringMap      SimpleMap;
  AdtStringByStringMapIter  StrIter;

  //Build a map of all the array sizes from the embedded comments on local
  //and class attribute declarations.
  for (ListIter = IdentList.begin() ; ListIter != IdentList.end() ; ++ListIter)
  {
    AdtParser* pObj = (*ListIter);

    if ((pObj != 0) && pObj->isType("AdtCppDeclarator"))
    {
      AdtCppDeclarator* pDeclaratorObj = (AdtCppDeclarator*)pObj;

      pDeclaratorObj->enumerateArraySizes(ArraySizeMap);

      if (pDeclaratorObj->isSimple())
      {
        SimpleMap[pDeclaratorObj->name()] = pDeclaratorObj->name();
      }
    }
  }

  rOutFile.write("INTEGER, PARAMETER :: ");

  //Print out the PARAMETER definitions
  for (StrIter = ArraySizeMap.begin() ; StrIter != ArraySizeMap.end() ; ++StrIter)
  {
    const string& rArraySize = (*StrIter).second;

    // Only add objects that aren't arrays
    if (SimpleMap.find(rArraySize) != SimpleMap.end())
    {
      rOutFile.write(rArraySize);
      rOutFile.write(", ");
    }
  }

  rOutFile.write("dim_stack");
  rOutFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtCppTranslationUnit::addDimensionVars(const char* pClassName,
                                             AdtParserPtrByStringMap& rVarsMap) const
{
  string                ParentClassName;
  AdtCppClassSpecifier* pClass = findClass(pClassName, ParentClassName);

  if (pClass != 0)
  {
    AdtParserPtrList      rList;
    AdtParserPtrListIter  Iter;

    pClass->findDimensionVars(this, rVarsMap, rList);

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

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::compile(const AdtCppFunctionDefinition* pFunction,
                                    AdtParserPtrByStringMap& rFunctionsMap,
                                    AdtParserPtrByStringMap& rVarsMap,
                                    bool bExpandMacros) const
{
  bool bCompiled = false;

  if (pFunction != 0)
  {
    if (pFunction->isProcedure())
    {
      ProcedureMap[pFunction->qualifiedName()] = 1;
    }
    else
    {
      FunctionMap[pFunction->qualifiedName()] = 1;
    }

    //Create a copy of the procedure
    AdtCppFunctionDefinition* pCopyFunction = (AdtCppFunctionDefinition*)pFunction->copy();

    if (pCopyFunction != 0)
    {
      string  ClassName;

      AdtCppBase::prefixFromQualifiedName(pCopyFunction->name(), ClassName);

      if (0)
      {
        //Debugging stuff to print the parse tree of the function definition
        AdtFile DescendantsFile;

        DescendantsFile.open(pCopyFunction->name() + ".txt", "wt");
        pCopyFunction->printDescendants(DescendantsFile);
      }

      if (bExpandMacros)
      {
        AdtParserPtrByStringMultiMapCS rMacroMap;

        buildMacroMap(rMacroMap);
        AdtCppMacro::forwardSubstitute(pCopyFunction, rMacroMap);
      }

      //Add it to the list of functions
      rFunctionsMap.insert(AdtParserPtrByStringMap::value_type(pCopyFunction->name(), AdtParserContext(pCopyFunction)));

      //Find unresolved externals
      AdtStringListConstIter  Iter;
      AdtStringList           ExternalsList;

      if (pCopyFunction->enumerateExternals(ExternalsList))
      {
        for (Iter = ExternalsList.begin() ; Iter != ExternalsList.end() ; ++Iter)
        {
          char              sKeyName[32]  = {0};
          const string&     rName         = *Iter;
          const AdtParser*  pExternal     = 0;
          string            sMatchName;

          if (findVar(rName, pExternal))
          {
            //Quick and dirty hack to build a unique key name to stop the same
            //object being inserted more than once.
            ::sprintf(sKeyName, "%zx", (size_t)pExternal);

            //Is a variable
            rVarsMap.insert(AdtParserPtrByStringMap::value_type(sKeyName, AdtParserContext((AdtParser*)pExternal)));
          }
          else if (findFunction(rName, ClassName, pExternal, sMatchName))
          {
            //Is a procedure
            if (pExternal->isType("AdtCppFunctionDefinition"))
            {
              const AdtCppFunctionDefinition* pFunctionDefinition = (const AdtCppFunctionDefinition*)pExternal;

              if (rFunctionsMap.find(sMatchName) == rFunctionsMap.end())
              {
                compile(pFunctionDefinition,
                        rFunctionsMap,
                        rVarsMap,
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

      UtlReleaseReference(pCopyFunction);
    }
  }

  return (bCompiled);
}

//  ----------------------------------------------------------------------------

AdtCppTranslationUnit::AdtCppTranslationUnit(AdtParser* pObj)
 : AdtCppBase(),
   AdtSourceRoot()
{
  AdtParserPtrList  rFunctionList;

  initObject(DeclarationSeq, pObj, AdtCppDeclarationSeq, false);

  if (DeclarationSeq != 0)
  {
    DeclarationSeq->initialise();

    mapToList(rFunctionList, DeclarationSeq->functionDefinitionMap());
  }

  depth(0, true);

  if (rFunctionList.size() > 0)
  {
    AdtParserPtrListIter  Iter;

    for (Iter = rFunctionList.begin() ; Iter != rFunctionList.end() ; ++Iter)
    {
      const AdtParser*                pObj                = *Iter;
      const AdtCppFunctionDefinition* pFunctionDefinition = (const AdtCppFunctionDefinition*)pObj;

      if (pFunctionDefinition != 0)
      {
        pFunctionDefinition->checkDeclarations(this);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppTranslationUnit::AdtCppTranslationUnit(const AdtCppTranslationUnit& rCopy)
 : AdtCppBase(rCopy),
   AdtSourceRoot(rCopy)
{
  copyObject(DeclarationSeq, rCopy, AdtCppDeclarationSeq);

  if (DeclarationSeq != 0)
  {
    DeclarationSeq->initialise();
  }

  depth(0, true);
}

//  ----------------------------------------------------------------------------

AdtCppTranslationUnit::~AdtCppTranslationUnit()
{
  UtlReleaseReference(DeclarationSeq);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::isProcedure(const char* pName)
{
  bool bIsProc = false;

  if (pName != 0)
  {
    bIsProc = (ProcedureMap.find(pName) != ProcedureMap.end());
  }

  return (bIsProc);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::isFunction(const char* pName)
{
  bool bIsProc = false;

  if (pName != 0)
  {
    bIsProc = (FunctionMap.find(pName) != FunctionMap.end());
  }

  return (bIsProc);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::findVar(const char* pName,
                                    const AdtParser*& pObj) const
{
  bool bFound = false;

  if (DeclarationSeq != 0)
  {
    const AdtParser*  pVar = 0;

    bFound = DeclarationSeq->findVarDefinition(pName, pVar);
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::findField(const char* pName,
                                      const char* pClassName,
                                      const AdtParser*& pObj) const
{
  string                ParentClassName;
  bool                  bFound  = false;
  AdtCppClassSpecifier* pClass  = findClass(pClassName, ParentClassName);

  if (pClass != 0)
  {
    bFound = pClass->findField(this, pName, pObj);
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::findFunction(const char* pName,
                                         const char* pClassName,
                                         const AdtParser*& pObj,
                                         string& rMatchName) const
{
  bool bFound = false;

  if (DeclarationSeq != 0)
  {
    // Look in class scope first
    rMatchName  = string(pClassName) + "::" + pName;
    bFound      = DeclarationSeq->findFunctionDefinition(rMatchName, pObj);

    if (!bFound)
    {
      // Look in global scope
      bFound = DeclarationSeq->findFunctionDefinition(pName, pObj);

      if (bFound)
      {
        rMatchName = pName;
      }
      else
      {
        rMatchName = "";
      }
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

AdtCppClassSpecifier* AdtCppTranslationUnit::findClass(const char* pClassName,
                                                       string& rParentClassName) const
{
  AdtCppClassSpecifier* pClassSpecifier = 0;
  const char*           pTypeName       = pClassName;
  AdtParserPtrList      rDeclSeqList;

  AdtCppDeclarationInfo::enumerateScopes(rDeclSeqList,
                                         DeclarationSeq,
                                         pClassName,
                                         pTypeName,
                                         false);

  if (rDeclSeqList.size() > 0)
  {
    AdtParserPtrListIter  DeclSeqIter;

    for (DeclSeqIter = rDeclSeqList.begin() ; DeclSeqIter != rDeclSeqList.end() ; ++DeclSeqIter)
    {
      const AdtCppDeclarationSeq* pDeclSeq = (const AdtCppDeclarationSeq*)(AdtParser*)(*DeclSeqIter);

      if (pDeclSeq != 0)
      {
        pClassSpecifier = pDeclSeq->findClassSpecifier(pTypeName);

        if (pClassSpecifier != 0)
        {
          rParentClassName = pClassSpecifier->parentClassName();
          break;
        }
      }
    }
  }

  return (pClassSpecifier);
}

//  ----------------------------------------------------------------------------

AdtCppFunctionDefinition* AdtCppTranslationUnit::findFunction(const char* pQualifiedFunctionName,
                                                              string& rFunctionBaseName) const
{
  AdtCppFunctionDefinition* pFunctionDefinition = 0;
  const char*               pName               = pQualifiedFunctionName;
  AdtParserPtrList          rDeclSeqList;

  AdtCppDeclarationInfo::enumerateScopes(rDeclSeqList,
                                         DeclarationSeq,
                                         pQualifiedFunctionName,
                                         pName,
                                         true);

  if (rDeclSeqList.size() > 0)
  {
    AdtParserPtrListIter  DeclSeqIter;

    for (DeclSeqIter = rDeclSeqList.begin() ; DeclSeqIter != rDeclSeqList.end() ; ++DeclSeqIter)
    {
      const AdtCppDeclarationSeq* pDeclSeq = (const AdtCppDeclarationSeq*)(AdtParser*)(*DeclSeqIter);

      if (pDeclSeq != 0)
      {
        pFunctionDefinition = pDeclSeq->findFunctionDefinition(pName);
        rFunctionBaseName   = pName;
      }
    }
  }

  return (pFunctionDefinition);
}

//  ----------------------------------------------------------------------------

void AdtCppTranslationUnit::addFunction(AdtCppFunctionDefinition* pFunctionDefinition)
{
  if ((pFunctionDefinition != 0) && (DeclarationSeq != 0))
  {
    AdtCppDeclaration*  pDeclaration = new AdtCppDeclaration(0, pFunctionDefinition, 0, 0, 0);

    if (pDeclaration != 0)
    {
      DeclarationSeq->add(pDeclaration);
      UtlReleaseReference(pDeclaration);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppTranslationUnit::enumerateMethodNames(AdtStringList& rMethodList) const
{
  AdtParserPtrList  ObjectList;

  findObjects(ObjectList, "AdtCppFunctionDefinition");
  AdtParser::objListToNameList(rMethodList, ObjectList);
  ObjectList.clear();
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::hasClass(const char* pClassName,
                                     string& rParentClassName) const
{
  bool bHasClass = (findClass(pClassName, rParentClassName) != 0);

  return (bHasClass);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::buildBlackBoxFile(const char* pBlackBoxFileName,
                                              AdtStringByStringMap& rRegardAsClassFunctionMap,
                                              AdtStringByStringMap& rRegardAsClassSubroutineMap)
{
  bool    bBuilt = false;
  string  sBlackBoxDefs;

  //Find all black box containing objects
  AdtBlackBoxDefinitionPtrByStringMap BlackBoxMap;
  AdtParserPtrList                    rBlackBoxList;
  AdtParserPtrListConstIter           Iter;

  findObjects(rBlackBoxList, "AdtCppFunctionDefinition");

  for (Iter = rBlackBoxList.begin() ; Iter != rBlackBoxList.end() ; ++Iter)
  {
    const AdtCppFunctionDefinition* pFunctionDefinition = (const AdtCppFunctionDefinition*)Iter->object();

    if ((pFunctionDefinition != 0) && (pFunctionDefinition->blackBox() != 0))
    {
      AdtBlackBoxDefinition*  pBlackBox = pFunctionDefinition->blackBox();
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

bool AdtCppTranslationUnit::flattenClass(const char* pClassName,
                                         const AdtParserPtrList& rRootList,
                                         string& rUsesList)
{
  string                rParentClassName;
  bool                  bFlattened = false;
  AdtCppClassSpecifier* pClass     = findClass(pClassName, rParentClassName);

  if (pClass != 0)
  {
    bFlattened = pClass->flattenClass(this,
                                      rRootList,
                                      rUsesList);
  }

  return (bFlattened);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::optimise(const AdtStringList& rNewMethodList,
                                     const AdtStringByStringMap& rNewMethodMap)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtCppTranslationUnit::expandMacros()
{
  bool  bExpanded = false;

  if (DeclarationSeq != 0)
  {
    AdtCppTranslationUnit*  pCppRootObject = cppRootObject();

    if (pCppRootObject != 0)
    {
      pCppRootObject->lock();
    }

    cppRootObject(this);

    AdtParserPtrByStringMapConstIter  Iter;
    AdtParserPtrByStringMultiMapCS    rMacroMap;

    buildMacroMap(rMacroMap);

    for (Iter = DeclarationSeq->functionDefinitionMap().begin() ; Iter != DeclarationSeq->functionDefinitionMap().end() ; ++Iter)
    {
      AdtParser* pObject = (*Iter).second;

      if ((pObject != 0) && pObject->isType("AdtCppFunctionDefinition"))
      {
        AdtParserPtrByStringMultiMap  rNamesMap;
        AdtCppFunctionDefinition*     pFunctionDefinition = (AdtCppFunctionDefinition*)pObject;

        AdtCppMacro::forwardSubstitute(pFunctionDefinition, rMacroMap);
      }
    }

    cppRootObject(pCppRootObject);
    UtlReleaseReference(pCppRootObject);
  }

  return (bExpanded);
}

//  ----------------------------------------------------------------------------

void AdtCppTranslationUnit::extractClassConstructorName(const char* pConstructorDeclaration,
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
      else if (AdtParse::matchWord(pChar, "/*"))
      {
        string  sComment;

        // Ignore multiline comment
        AdtParse::extractWord(sComment, "*/", pChar, true);
        AdtParse::matchWord(pChar, "*/");
      }
      else if (AdtParse::matchWord(pChar, ";"))
      {
        // Do nothing.
      }
      else
      {
        string sInfo;

        // This goes into the name, ignore terminal ';'
        AdtParse::extractWord(sInfo, " ;\t", pChar, false);

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

bool AdtCppTranslationUnit::extractClassConstructors(AdtStringList& rConstructorList,
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
    string                      sParentClassName;
    bool                        bAsDelphi = (nAsFileType == DelphiSourceFileType);
    const AdtCppClassSpecifier* pClass    = findClass(pParentClassName, sParentClassName);

    if (pClass != 0)
    {
      AdtParserPtrList      ObjectList;
      AdtParserPtrListIter  Iter;

      pClass->findObjects(ObjectList, "AdtCppFunctionDefinition");

      bExtracted  = true;

      for (Iter = ObjectList.begin() ; Iter != ObjectList.end() ; ++Iter)
      {
        AdtCppFunctionDefinition* pObj = (AdtCppFunctionDefinition*)(AdtParser*)*Iter;

        if ((pObj != 0) && pObj->isCtor() && (pObj->name().at(0) != '~'))
        {
          string  rExtraction;
          string  sConstructorDeclaration;
          AdtFile StringOut;

          if (StringOut.open(sConstructorDeclaration))
          {
            if (bAsDelphi)
            {
              pObj->writeDelphi(StringOut, 2);
              StringOut.write(";");
            }
            else
            {
              pObj->writeCPP(StringOut, 2);
            }

            StringOut.close();

            extractClassConstructorName(sConstructorDeclaration, rExtraction);
          }

          rConstructorList.push_back(rExtraction);

          string  sConstructorCall;

          if (StringOut.open(sConstructorCall))
          {
            if (bAsDelphi)
            {
              pObj->writeDelphi(StringOut, 1);
              StringOut.write(";");
            }
            else
            {
              pObj->writeCPP(StringOut, 1);
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

AdtFile& AdtCppTranslationUnit::writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                           const AdtFortranExecutableProgram* pSavedRoot,
                                                           const char* pClassName,
                                                           const char* pLastClassName,
                                                           bool bExpandMacros) const
{
  if ((rOutFile.isOpen()) && (pClassName != 0))
  {
    string                      sParentClassName;
    const AdtCppClassSpecifier* pClass = findClass(pClassName, sParentClassName);

    if (pClass != 0)
    {
      bool                  bFirst = true;
      AdtParserPtrList      List;
      AdtParserPtrListIter  Iter;
      string                sMethodNames;

      pClass->findObjects(List, "AdtCppFunctionDefinition");

      for (Iter = List.begin() ; Iter != List.end() ; ++Iter)
      {
        AdtParser*                pMethodObj  = *Iter;
        AdtCppFunctionDefinition* pMethod     = (AdtCppFunctionDefinition*)pMethodObj;

        if ((pMethod != 0) && !pMethod->isCtor())
        {
          string sQualifiedName(pClassName);

          sQualifiedName += "::";
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

      writeFortran(rOutFile,
                   pSavedRoot,
                   pClassName,
                   pLastClassName,
                   sMethodNames,
                   bExpandMacros);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppTranslationUnit::writeFortran(AdtFile& rOutFile,
                                             const AdtFortranExecutableProgram* pSavedRoot,
                                             const char* pClassName,
                                             const char* pLastClassName,
                                             const char* pFunctionNames,
                                             bool bExpandMacros) const
{
  AdtCppTranslationUnit*  pCppRootObject = cppRootObject();

  if (pCppRootObject != 0)
  {
    pCppRootObject->lock();
  }

  cppRootObject((AdtCppTranslationUnit*)this);

  ProcedureMap.clear();
  FunctionMap.clear();

  if ((rOutFile.isOpen()) && (pFunctionNames != 0))
  {
    AdtParserPtrByStringMap VarsMap;
    AdtParserPtrByStringMap FunctionsMap;
    bool                    bCompiled = false;
    const char*             pStart    = pFunctionNames;
    const char*             pEnd      = 0;

    do
    {
      pEnd = ::strchr(pStart, ',');

      size_t                    nLength = (pEnd == 0) ? ::strlen(pStart) : pEnd - pStart;
      string                    FunctionName(pStart, 0, nLength);
      string                    FunctionBaseName;
      AdtCppFunctionDefinition* pFunction = findFunction(FunctionName, FunctionBaseName);

      if (pFunction != 0)
      {
        if (compile(pFunction, FunctionsMap, VarsMap, bExpandMacros))
        {
          bCompiled = true;
        }
      }

      pStart = pEnd + 1;
    }
    while (pEnd != 0);

    if (bCompiled)
    {
      AdtParserPtrByStringMapConstIter Iter;

      //Write Common module definition
      write(rOutFile, "MODULE COMMON");

      rOutFile.incrementIndent();
      rOutFile.newline();
      rOutFile.newline();

      writeArraySizes(rOutFile,
                      FunctionsMap,
                      VarsMap);

      rOutFile.newline();

      for (Iter = VarsMap.begin() ; Iter != VarsMap.end() ; ++Iter)
      {
        AdtParser* pObj = (*Iter).second;

        if ((pObj != 0) && pObj->isType("AdtCppDeclarator"))
        {
          const AdtCppDeclarator*         pDeclarator         = (const AdtCppDeclarator*)pObj;
          const AdtCppMemberDeclaration*  pMemberDeclaration  = (const AdtCppMemberDeclaration*)pDeclarator->findAscendantWithClassLineage("AdtCppMemberDeclarator,AdtCppMemberDeclarationList,AdtCppMemberDeclaration");

          if (pMemberDeclaration != 0)
          {
            pMemberDeclaration->writeFortranDeclaration(rOutFile, pDeclarator);
          }
          else
          {
            const AdtCppSimpleDeclaration*  pSimpleDeclaration  = (const AdtCppSimpleDeclaration*)pDeclarator->findAscendantWithClassLineage("AdtCppInitDeclarator,AdtCppInitDeclaratorList,AdtCppSimpleDeclaration");

            if (pSimpleDeclaration != 0)
            {
              pSimpleDeclaration->writeFortranDeclaration(rOutFile, pDeclarator);
            }
            else
            {
              FAIL();
            }
          }
        }

        rOutFile.newline();
      }

      rOutFile.decrementIndent();
      rOutFile.newline();

      write(rOutFile, "END");

      rOutFile.newline();
      rOutFile.newline();
      write(rOutFile, "! ----------------------------------------------------------------------------");
      rOutFile.newline();

      //Write procedure definitions
      for (Iter = FunctionsMap.begin() ; Iter != FunctionsMap.end() ; ++Iter)
      {
        AdtParser* pObj = (*Iter).second;

        if ((pObj != 0) && pObj->isType("AdtCppBase"))
        {
          AdtCppBase* pCppObj = (AdtCppBase*)pObj;

          pCppObj->writeFortran(rOutFile);
          rOutFile.newline();
        }
      }

      VarsMap.clear();
      FunctionsMap.clear();
    }
    else
    {
      // Write Empty module definition. We need to because the fortran compiler
      // will throw an error for empty files
      write(rOutFile, "MODULE COMMON");
      rOutFile.newline();
      write(rOutFile, "END");
      rOutFile.newline();
    }
  }

  cppRootObject(pCppRootObject);
  UtlReleaseReference(pCppRootObject);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppTranslationUnit::writeNative(AdtFile& rOutFile) const
{
  return (writeCPP(rOutFile));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppTranslationUnit::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (DeclarationSeq != 0)
  {
    DeclarationSeq->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppTranslationUnit::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (DeclarationSeq != 0)
  {
    DeclarationSeq->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtSourceFileType AdtCppTranslationUnit::sourceFileType() const
{
  return (CppSourceFileType);
}

//  ----------------------------------------------------------------------------

implType(AdtCppTranslationUnit, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMacro method implementations
//  ----------------------------------------------------------------------------
bool AdtCppMacro::isCompatible(AdtCppDeclaratorExpression* pNameObj) const
{
  bool bIsCompatible = false;

  if (pNameObj != 0)
  {
    size_t nArgs = 0;

    if ((ExpressionList != 0) && pNameObj->isCallDeclaration(&nArgs))
    {
      bIsCompatible = (ExpressionList->listSize() == nArgs);
    }
    else if (pNameObj->isSimpleDeclaration())
    {
      bIsCompatible = true;
    }
  }

  return (bIsCompatible);
}

//  ----------------------------------------------------------------------------

void AdtCppMacro::addVariables(AdtParser* pStatementSeqObj) const
{
  if ((SimpleDeclarationList != 0) && (pStatementSeqObj != 0))
  {
    AdtParserPtrListConstIter   Iter;
    AdtParserPtrByStringMap     DeclMap;
    AdtParserPtrByStringMap     ToAddMap;
    AdtParserPtrByStringMapIter MapIter;

    // enumerate all declared variables in this scope
    for (Iter = pStatementSeqObj->objList().begin() ; Iter != pStatementSeqObj->objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        AdtParser*  pInitDeclaratorListObj = pObj->findDescendant("DeclarationStatement,BlockDeclaration,SimpleDeclaration,InitDeclaratorList");

        if (pInitDeclaratorListObj != 0)
        {
          pInitDeclaratorListObj->enumerate(DeclMap);
        }
      }
    }

    // Search for undefined addvar variables in this scope
    for (Iter = SimpleDeclarationList->objList().begin() ; Iter != SimpleDeclarationList->objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        AdtParser*  pInitDeclaratorListObj  = pObj->findDescendant("InitDeclaratorList");

        if (pInitDeclaratorListObj != 0)
        {
          AdtParserPtrListConstIter VarIter;

          for (VarIter = pInitDeclaratorListObj->objList().begin() ; VarIter != pInitDeclaratorListObj->objList().end() ; ++VarIter)
          {
            AdtParser*  pInitDeclaratorObj = *VarIter;

            if ((pInitDeclaratorObj != 0) && (DeclMap.find(pInitDeclaratorObj->name()) == DeclMap.end()))
            {
              ToAddMap.insert(AdtParserPtrByStringMap::value_type(pInitDeclaratorObj->name(), pInitDeclaratorObj));
            }
          }
        }
      }
    }

    // Add missing variables
    for (MapIter = ToAddMap.begin() ; MapIter != ToAddMap.end() ; ++MapIter)
    {
      AdtCppBase*   pStatementObj;
      AdtParser*    pInitDeclaratorObj  = (*MapIter).second;

      // Create and insert new variable declaration in this scope
      pStatementObj = AdtCppBase::createSimpleVariableDeclarationStatementFrom(pInitDeclaratorObj);

      pStatementSeqObj->add(pStatementObj, false);

      UtlReleaseReference(pStatementObj);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtCppMacro::expandMacro(AdtCppDeclaratorExpression* pNameObj,
                              AdtCppBase* pSubstitutionRoot,
                              bool bAllowMultiline) const
{
  // For each expression in the expression list of the macro call
  // create the C++ code as text for it and substitute it into the
  // text representation of the macro. Then compile the text to
  // obtain a C++ parse tree and sustitute it in place of what is there.

  // Create a copy of StatementSeq, for each expression in ExpressionList find
  // the name and search pCopy for objects of that name, then use the text
  // representation of the arguments of pNameObj to reset the object names,
  // then create a text representation for pCopy and compile it into a parse
  // tree and finally subtitute it into the correct location in pSubstitutionRoot
  if ((pNameObj != 0) && (pSubstitutionRoot != 0))
  {
    // Find the object containing the macro parameter values to substitute.
    AdtParser*  pSrcExpressionList = pNameObj->findDescendant("ExpressionList");

    if ((pSrcExpressionList != 0) && (ExpressionList != 0))
    {
      // Create a copy of the macro object to substitute into
      const AdtParserPtrList& rSrcArgList     = pSrcExpressionList->objList();
      const AdtParserPtrList& rSearchArgList  = ExpressionList->objList();
      AdtCppStatementSeq*     pCopy           = (AdtCppStatementSeq*)StatementSeq->copy();

      if (pCopy != 0)
      {
        AdtParserPtrListConstIter SrcArgIter;
        AdtParserPtrListConstIter SearchArgIter;
        string                    sCppText;
        AdtFile                   CppFile;

        // Loop through arguments doing textual substitution
        for (SrcArgIter = rSrcArgList.begin(), SearchArgIter = rSearchArgList.begin() ; (SrcArgIter != rSrcArgList.end()) && (SearchArgIter != rSearchArgList.end()) ; ++SrcArgIter, ++SearchArgIter)
        {
          AdtCppBase* pSrcArg     = (AdtCppBase*)(AdtParser*)*SrcArgIter;
          AdtParser*  pSearchArg  = *SearchArgIter;

          if (pSearchArg != 0)
          {
            pSearchArg = pSearchArg->findObject("AdtCppDeclaratorExpression");
          }

          if ((pSrcArg != 0) && (pSearchArg != 0))
          {
            AdtParserPtrList      SubstituteList;
            AdtParserPtrListIter  SubstIter;

            // create test representation of argument
            CppFile.open(sCppText);
            pSrcArg->writeCPP(CppFile);
            CppFile.close();

            // search for all objects with the same name as pSearchArg
            pCopy->findObjects(SubstituteList, "AdtCppBase", pSearchArg->name(), true);

            // Do textual substitution
            for (SubstIter = SubstituteList.begin() ; SubstIter != SubstituteList.end() ; ++SubstIter)
            {
              AdtParser*  pSubstObj = *SubstIter;

              if (pSubstObj != 0)
              {
                pSubstObj->name(sCppText);
              }
            }

            sCppText = "";
          }
        }

        sCppText = "";

        // Create code text and compile it.
        CppFile.open(sCppText);
        pCopy->writeCPP(CppFile);
        CppFile.close();

        AdtCppStatementSeq* pCode = AdtCppBase::expressionBuild(sCppText);

        if (pCode != 0)
        {
          if (bAllowMultiline)
          {
            if (pSubstitutionRoot->isType("AdtCppAssignmentExpression"))
            {
              // Multiline replacement
              AdtParser*  pStatement  = 0;
              AdtParser*  pParent     = pSubstitutionRoot->findAscendantWithClassLineage("AdtCppExpression,"
                                                                                         "AdtCppExpressionStatement,"
                                                                                         "AdtCppStatement,"
                                                                                         "AdtCppStatementSeq", &pStatement);

              if ((pParent != 0) && (pStatement))
              {
                if (pCode->listSize() > 0)
                {
                  AdtParser* pFirst = (*pCode->objList().begin());

                  if (pFirst != 0)
                  {
                    pFirst->comment(pNameObj->comment());
                  }
                }

                pCode->depth(pParent->depth());
                pParent->replace(pStatement, pCode);
                addVariables(pParent);
              }
            }
            else
            {
              FAIL();
            }
          }
          else
          {
            AdtParser*  pReplaceObj = pCode->findObject(pSubstitutionRoot->type());

            if (pReplaceObj != 0)
            {
              if (0)
              {
                sCppText = "";

                // Create code text and compile it.
                CppFile.open(sCppText);
                pSubstitutionRoot->writeCPP(CppFile);
                CppFile.close();
              }

              pReplaceObj->lock();
              pReplaceObj->replaceInParent(0);
              pReplaceObj->depth(pSubstitutionRoot->depth());
              pReplaceObj->comment(pNameObj->comment());
              pSubstitutionRoot->replaceInParent(pReplaceObj);
              UtlReleaseReference(pReplaceObj);

              if (0)
              {
                sCppText = "";

                // Create code text and compile it.
                CppFile.open(sCppText);
                ((AdtCppBase*)pReplaceObj)->writeCPP(CppFile);
                CppFile.close();
              }
            }
            else
            {
              FAIL();
            }
          }

          UtlReleaseReference(pCode);
        }

        UtlReleaseReference(pCopy);
      }
    }
    else
    {
      // Simple name translation. No parse tree building required.
      AdtParser*  pDeclaratorExpression = StatementSeq->findObject("AdtCppDeclaratorExpression");

      if (pDeclaratorExpression != 0)
      {
        pNameObj->name(pDeclaratorExpression->name());
      }
      else
      {
        FAIL();
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppMacro::AdtCppMacro(const char* pIdentifier,
                         AdtParser* pExpressionListObj,
                         AdtParser* pStatementSeqObj,
                         AdtParser* pSimpleDeclarationListObj)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);

  initObject(ExpressionList,        pExpressionListObj,         AdtCppExpressionList,         false);
  initObject(StatementSeq,          pStatementSeqObj,           AdtCppStatementSeq,           false);
  initObject(SimpleDeclarationList, pSimpleDeclarationListObj,  AdtCppSimpleDeclarationList,  false);
}

//  ----------------------------------------------------------------------------

AdtCppMacro::AdtCppMacro(const AdtCppMacro& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ExpressionList,        rCopy, AdtCppExpressionList);
  copyObject(StatementSeq,          rCopy, AdtCppStatementSeq);
  copyObject(SimpleDeclarationList, rCopy, AdtCppSimpleDeclarationList);
}

//  ----------------------------------------------------------------------------

AdtCppMacro::~AdtCppMacro()
{
  UtlReleaseReference(ExpressionList);
  UtlReleaseReference(StatementSeq);
  UtlReleaseReference(SimpleDeclarationList);
}

//  ----------------------------------------------------------------------------

void AdtCppMacro::forwardSubstitute(AdtCppFunctionDefinition* pFunctionDefinition,
                                    AdtParserPtrByStringMultiMapCS& rMacroMap)
{
  if (pFunctionDefinition != 0)
  {
    AdtParserPtrList              NameList;
    AdtParserPtrList              FoundList;
    AdtParserPtrListIter          Iter;

    pFunctionDefinition->findObjects(NameList, "AdtCppDeclaratorExpression", 0, false);

    // Optimise substitution by eliminating all name objects that don't require
    // substitution
    for (Iter = NameList.begin() ; Iter != NameList.end() ; ++Iter)
    {
      AdtParser*  pNameObj = *Iter;

      if (pNameObj != 0)
      {
        if (rMacroMap.find(pNameObj->name()) != rMacroMap.end())
        {
          FoundList.push_back(pNameObj);
        }
      }
    }

    //We sort the list into descending depth so that the deepest nested macro
    //replacement is handled first. In that way we are assured that any nested
    //macros will be substituted correctly.
    FoundList.sort();
    FoundList.reverse();

    for (Iter = FoundList.begin() ; Iter != FoundList.end() ; ++Iter)
    {
      AdtCppDeclaratorExpression* pNameObj = (AdtCppDeclaratorExpression*)(AdtParser*)*Iter;

      if (pNameObj != 0)
      {
        AdtParserPtrByStringMultiMapCSIter  rMacroIter;

        for (rMacroIter = rMacroMap.lower_bound(pNameObj->name()) ; rMacroIter != rMacroMap.upper_bound(pNameObj->name()) ; ++rMacroIter)
        {
          AdtCppMacro*  pMacro = (AdtCppMacro*)(AdtParser*)(*rMacroIter).second;

          if ((pMacro != 0) && pMacro->isCompatible(pNameObj) && (pMacro->StatementSeq != 0))
          {
            AdtParser*  pRoot             = pNameObj->findAscendantWithClass("AdtCppAssignmentExpression");
            AdtCppBase* pSubstitutionRoot = pNameObj->substituitionRoot("AdtCppAssignmentExpression");

            if ((pRoot != 0) && (pSubstitutionRoot != 0))
            {
              const char* pErrorFormat    = 0;
              bool        bOk             = true;
              bool        bAllowMultiline = false;

              if (pRoot->findAscendantWithClassLineage("AdtCppExpression,AdtCppExpressionStatement,AdtCppStatement,AdtCppStatementSeq", &pRoot) != 0)
              {
                // Multi-line expansion allowed
                bAllowMultiline = true;
              }
              else
              {
                // Single-line expansion allowed
                if (pMacro->StatementSeq->listSize() != 1)
                {
                  // multiline expansion not allowed in this context
                  pErrorFormat = "ERROR: multiline macro expansion not allowed in this context\n Macro:\n%s\nContext: Line %d of file %s\n";

                  bOk = false;
                }

                if (pMacro->SimpleDeclarationList != 0)
                {
                  // add var macro replacement not allowed in this context
                  pErrorFormat = "ERROR: add var macro expansion not allowed in this context\n Macro:\n%s\nContext: Line %d of file %s\n";

                  bOk = false;
                }
              }

              if (bOk)
              {
                pMacro->expandMacro(pNameObj, pSubstitutionRoot, bAllowMultiline);
                break;
              }
              else
              {
                ::printf(pErrorFormat, pMacro->name().c_str(), pRoot->lineNumber(), pRoot->fileName());
              }
            }
            else
            {
              // Should never happen
              FAIL();
            }
          }
        }
      }
    }

    FoundList.clear();
  }
}

//  ----------------------------------------------------------------------------

implType(AdtCppMacro, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationInfo method implementations
//  ----------------------------------------------------------------------------
void AdtCppDeclarationInfo::flush()
{
  NamespaceDefinitionMultiMap.clear();
  FunctionDefinitionMap.clear();
  VarDefinitionMap.clear();
  EnumSpecifierMap.clear();
  ClassSpecifierMap.clear();
}

//  ----------------------------------------------------------------------------

void AdtCppDeclarationInfo::enumerateObjects(AdtParserPtrByStringMap& rMap,
                                             const char* pSearchPath,
                                             const char* pClassName,
                                             bool bClassScope)
{
  AdtParserPtrListIter  Iter;
  AdtParserPtrList      rObjList;

  enumerateDescendantList(rObjList, pSearchPath);

  for (Iter = rObjList.begin() ; Iter != rObjList.end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if ((pObj != 0) && pObj->isType(pClassName) && pObj->isType("AdtCppCheckDeclaration"))
    {
      AdtCppCheckDeclaration* pCheckDeclaration = (AdtCppCheckDeclaration*)pObj;

      if (!pCheckDeclaration->isForwardDeclaration(bClassScope))
      {
        AdtParserPtrByStringMapIter Iter = rMap.find(pCheckDeclaration->qualifiedName());

        if (Iter == rMap.end())
        {
          rMap[pCheckDeclaration->name()]           = pCheckDeclaration;
          rMap[pCheckDeclaration->qualifiedName()]  = pCheckDeclaration;
        }
        else
        {
          bool        bIsCtor       = false;
          AdtParser*  pExistingObj  = (*Iter).second;

          if (pExistingObj->isType("AdtCppFunctionDefinition"))
          {
            AdtCppFunctionDefinition* pFunctionDefinition = (AdtCppFunctionDefinition*)pExistingObj;

            bIsCtor = pFunctionDefinition->isCtor();
          }

          if (!bIsCtor)
          {
            ::printf("ERROR: Object definition %s on line %d in file %s "
                     "differs only by case from definition %s on line %d in file %s "
                     "making translation to fortran ambiguous\n",
                     pObj->name().c_str(),
                     pObj->lineNumber(),
                     pObj->fileName(),
                     pExistingObj->name().c_str(),
                     pExistingObj->lineNumber(),
                     pExistingObj->fileName());

            AdtExit(-1);
          }
        }
      }
    }
    else
    {
      // Warm me something is wrong
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppDeclarationInfo::AdtCppDeclarationInfo()
 : AdtCppBase(),
   NamespaceDefinitionMultiMap(),
   FunctionDefinitionMap(),
   VarDefinitionMap(),
   EnumSpecifierMap(),
   ClassSpecifierMap()
{

}

//  ----------------------------------------------------------------------------

AdtCppDeclarationInfo::AdtCppDeclarationInfo(const AdtCppDeclarationInfo& rCopy)
 : AdtCppBase(rCopy),
   NamespaceDefinitionMultiMap(),
   FunctionDefinitionMap(),
   VarDefinitionMap(),
   EnumSpecifierMap(),
   ClassSpecifierMap()
{

}

//  ----------------------------------------------------------------------------

AdtCppDeclarationInfo::~AdtCppDeclarationInfo()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtCppDeclarationInfo::enumerateScopes(AdtParserPtrList& rList,
                                            AdtCppDeclarationSeq* pDeclSeq,
                                            const char* pTypeName,
                                            const char*& pBaseName,
                                            bool bAllowUpToLast)
{
  string      sScopeName;
  const char* pPossibleBaseName = pTypeName;

  if (AdtCppScopeManager::nestedNameSpecifier(sScopeName, pTypeName))
  {
    if ((sScopeName.length() != 0) && (pDeclSeq != 0))
    {
      bool                                  bNoMatch  = true;
      AdtParserPtrByStringMultiMapConstIter ClassIter = pDeclSeq->namespaceDefinitionMultiMap().lower_bound(sScopeName);
      AdtParserPtrByStringMultiMapConstIter UpperIter = pDeclSeq->namespaceDefinitionMultiMap().upper_bound(sScopeName);

      for ( ; ClassIter != UpperIter ; ++ClassIter)
      {
        AdtParser*  pObj = (*ClassIter).second;

        if (pObj != 0)
        {
          AdtCppNamespaceDefinition*  pNamespaceDefinition = (AdtCppNamespaceDefinition*)pObj;
          AdtCppDeclarationSeq*       pNextDeclSeq         = pNamespaceDefinition->declarationSeq();

          enumerateScopes(rList, pNextDeclSeq, pTypeName, pBaseName, bAllowUpToLast);
        }

        bNoMatch = false;
      }

      if (bAllowUpToLast && bNoMatch)
      {
        // If we don't have a match and bAllowUpToLast is true then check if
        // the non-matching scope is the last in the series before the symbol
        // name. If it is then add the scope. This is to allow searching for
        // symbols in the "class" namespace.
        if (!AdtCppScopeManager::nestedNameSpecifier(sScopeName, pTypeName))
        {
          rList.push_back(pDeclSeq);

          pBaseName = pPossibleBaseName;
        }
      }
    }
    else
    {
      enumerateScopes(rList, 0, pTypeName, pBaseName, bAllowUpToLast);
    }
  }
  else
  {
    rList.push_back(pDeclSeq);

    pBaseName = pTypeName;
  }
}


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationSeq method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclarationSeq::AdtCppDeclarationSeq(AdtParser* pDeclarationObj)
 : AdtCppDeclarationInfo()
{
  add(pDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtCppDeclarationSeq::AdtCppDeclarationSeq(const AdtCppDeclarationSeq& rCopy)
 : AdtCppDeclarationInfo(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppDeclarationSeq::~AdtCppDeclarationSeq()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtCppDeclarationSeq::initialise()
{
  flush();

  enumerateFunctionDefinitions("AdtCppDeclaration,FunctionDefinition");
  enumerateVarDefinitions("AdtCppDeclaration,BlockDeclaration,SimpleDeclaration,InitDeclaratorList,AdtCppInitDeclarator,Declarator");
  enumerateEnumSpecifiers("AdtCppDeclaration,BlockDeclaration,SimpleDeclaration,EnumSpecifier");
  enumerateClassSpecifiers("AdtCppDeclaration,BlockDeclaration,SimpleDeclaration,ClassSpecifier");

  AdtParserPtrList  ObjList;

  enumerateDescendantList(ObjList, "AdtCppDeclaration,NamespaceDefinition");

  listToMap(NamespaceDefinitionMultiMap, ObjList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarationSeq::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, "", true, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarationSeq::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, "", true, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclarationSeq, AdtCppDeclarationInfo);


//  ----------------------------------------------------------------------------
//  AdtCppSimpleDeclarationList method imlementations
//  ----------------------------------------------------------------------------
AdtCppSimpleDeclarationList::AdtCppSimpleDeclarationList(AdtParser* pSimpleDeclarationObj)
 : AdtCppBase()
{
  add(pSimpleDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtCppSimpleDeclarationList::AdtCppSimpleDeclarationList(const AdtCppSimpleDeclarationList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppSimpleDeclarationList::~AdtCppSimpleDeclarationList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleDeclarationList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteCPP(rOutFile, nMode, " ", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleDeclarationList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, " ", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtCppSimpleDeclarationList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppPostfixExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppPostfixExpression::AdtCppPostfixExpression(AdtParser* pExpressionObj,
                                                 AdtParser* pPostfixExpressionObj,
                                                 AdtParser* pDirectedExpressionObj,
                                                 bool bIncrement,
                                                 const char* pLiteral)
 : AdtCppBase()
{
  nameWithComment(pLiteral);

  initObject(Expression,          pExpressionObj,         AdtCppExpression,         false);
  initObject(PostfixExpression,   pPostfixExpressionObj,  AdtCppPostfixExpression,  false);
  initObject(DirectedExpression,  pDirectedExpressionObj, AdtCppDirectedExpression, false);

  Increment = bIncrement;
}

//  ----------------------------------------------------------------------------

AdtCppPostfixExpression::AdtCppPostfixExpression(const AdtCppPostfixExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Expression,          rCopy, AdtCppExpression);
  copyObject(PostfixExpression,   rCopy, AdtCppPostfixExpression);
  copyObject(DirectedExpression,  rCopy, AdtCppDirectedExpression);

  Increment = rCopy.Increment;
}

//  ----------------------------------------------------------------------------

AdtCppPostfixExpression::~AdtCppPostfixExpression()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(PostfixExpression);
  UtlReleaseReference(DirectedExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppPostfixExpression::isSimple() const
{
  bool bIsSimple = ((PostfixExpression  == 0) &&
                    (Expression         == 0) &&
                    (DirectedExpression != 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppPostfixExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if ((Expression         == 0) &&
      (PostfixExpression  == 0) &&
      (DirectedExpression == 0))
  {
    write(rOutFile, name());
  }
  else
  {
    if (Expression != 0)
    {
      write(rOutFile, "(");
      Expression->writeCPP(rOutFile, nMode);
      write(rOutFile, ")");
    }

    if (PostfixExpression != 0)
    {
      PostfixExpression->writeCPP(rOutFile, nMode);

      if (Increment)
      {
        write(rOutFile, "++");
      }
      else
      {
        write(rOutFile, "--");
      }
    }

    if (DirectedExpression != 0)
    {
      DirectedExpression->writeCPP(rOutFile, nMode);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppPostfixExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if ((Expression         == 0) &&
      (PostfixExpression  == 0) &&
      (DirectedExpression == 0))
  {
    string sConvertedName;

    nameToFortran(name(), sConvertedName);
    write(rOutFile, sConvertedName);
  }
  else
  {
    if (Expression != 0)
    {
      write(rOutFile, "(");
      Expression->writeFortran(rOutFile, nMode);
      write(rOutFile, ")");
    }

    if (PostfixExpression != 0)
    {
      if (parentSimpleLineageTo("AdtCppAssignmentExpression"))
      {
        AdtFile File;
        string  sArg;

        File.open(sArg);
        PostfixExpression->writeFortran(File, nMode);
        File.close();

        write(rOutFile, sArg);
        write(rOutFile, " = ");
        write(rOutFile, sArg);

        if (Increment)
        {
          write(rOutFile, " + 1");
        }
        else
        {
          write(rOutFile, " - 1");
        }
      }
      else
      {
        if (Increment)
        {
          write(rOutFile, "POSTINC(");
        }
        else
        {
          write(rOutFile, "POSTDEC(");
        }

        PostfixExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, ")");
      }
    }

    if (DirectedExpression != 0)
    {
      DirectedExpression->writeFortran(rOutFile, nMode);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppPostfixExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppExpressionList method implementations
//  ----------------------------------------------------------------------------
AdtCppExpressionList::AdtCppExpressionList(AdtParser* pAssignmentExpressionObj)
 : AdtCppBase()
{
  add(pAssignmentExpressionObj);
}

//  ----------------------------------------------------------------------------

AdtCppExpressionList::AdtCppExpressionList(const AdtCppExpressionList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppExpressionList::~AdtCppExpressionList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpressionList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteCPP(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpressionList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtCppExpressionList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDirectedExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppDirectedExpression::AdtCppDirectedExpression(AdtParser* pDeclaratorExpressionObj)
 : AdtCppBase()
{
  add(pDeclaratorExpressionObj);
}

//  ----------------------------------------------------------------------------

AdtCppDirectedExpression::AdtCppDirectedExpression(const AdtCppExpressionList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppDirectedExpression::~AdtCppDirectedExpression()
{

}

//  ----------------------------------------------------------------------------

bool AdtCppDirectedExpression::isSimple() const
{
  bool bIsSimple = (listSize() == 1);

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDirectedExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteCPP(rOutFile, nMode, ".", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDirectedExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, "__", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtCppDirectedExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorExpression method implementations
//  ----------------------------------------------------------------------------
void AdtCppDeclaratorExpression::writeFortranInner(AdtFile& rOutFile,
                                                   int nMode,
                                                   const string& sQualifiedName,
                                                   bool bAddCall) const
{
  if (bAddCall)
  {
    write(rOutFile, "CALL ");
  }

  string sConvertedName;

  nameToFortran(sQualifiedName, sConvertedName);
  write(rOutFile, sConvertedName);

  if (HasBrackets)
  {
    write(rOutFile, "(");
  }

  if (ExpressionList != 0)
  {
    ExpressionList->writeFortran(rOutFile, nMode);
  }

  if (HasBrackets)
  {
    write(rOutFile, ")");
  }

  if (DeclaratorExpressionDims != 0)
  {
    DeclaratorExpressionDims->writeFortran(rOutFile, nMode);
  }
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorExpression::AdtCppDeclaratorExpression(const char* pIdentifier,
                                                       AdtParser* pExpressionListObj,
                                                       AdtParser* pDeclaratorExpressionDimsObj,
                                                       bool bQualified,
                                                       bool bHasBrackets,
                                                       const char* pComment)
 : AdtCppBase()
{
  if (pIdentifier != 0)
  {
    nameWithComment(pIdentifier);
  }

  initObject(ExpressionList,            pExpressionListObj,           AdtCppExpressionList,           false);
  initObject(DeclaratorExpressionDims,  pDeclaratorExpressionDimsObj, AdtCppDeclaratorExpressionDims, false);

  Qualified   = bQualified;
  HasBrackets = bHasBrackets;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorExpression::AdtCppDeclaratorExpression(const AdtCppDeclaratorExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ExpressionList,            rCopy, AdtCppExpressionList);
  copyObject(DeclaratorExpressionDims,  rCopy, AdtCppDeclaratorExpressionDims);

  Qualified   = rCopy.Qualified;
  HasBrackets = rCopy.HasBrackets;
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorExpression::~AdtCppDeclaratorExpression()
{
  UtlReleaseReference(ExpressionList);
  UtlReleaseReference(DeclaratorExpressionDims);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclaratorExpression::isSimple() const
{
  bool bIsSimple = (DeclaratorExpressionDims == 0);

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtCppBase* AdtCppDeclaratorExpression::substituitionRoot(const char* pTerminalClass) const
{
  AdtCppBase* pRoot     = (AdtCppBase*)this;
  AdtCppBase* pNextRoot = pRoot;

  while ((pNextRoot != 0) && !pRoot->isType(pTerminalClass) && pNextRoot->isSimple())
  {
    pRoot     = pNextRoot;
    pNextRoot = (AdtCppBase*)pNextRoot->parent();
  }

  return (pRoot);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclaratorExpression::isSimpleDeclaration(const char** ppIdentifier) const
{
  bool bIsSimple = false;

  if ((ExpressionList           == 0    ) &&
      (DeclaratorExpressionDims == 0    ) &&
      (HasBrackets              == false))
  {
    if (ppIdentifier)
    {
      *ppIdentifier = name();
    }

    bIsSimple = true;
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclaratorExpression::isCallDeclaration(size_t* pnArgs) const
{
  bool bIsCall = false;

  if ((ExpressionList           != 0   ) &&
      (DeclaratorExpressionDims == 0   ) &&
      (HasBrackets              == true))
  {
    if (pnArgs)
    {
      *pnArgs = ExpressionList->listSize();
    }

    bIsCall = true;
  }

  return (bIsCall);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, name());

  if (HasBrackets)
  {
    write(rOutFile, "(");
  }

  if (ExpressionList != 0)
  {
    ExpressionList->writeCPP(rOutFile, nMode);
  }

  if (HasBrackets)
  {
    write(rOutFile, ")");
  }

  if (DeclaratorExpressionDims != 0)
  {
    DeclaratorExpressionDims->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  bool                              bAddCall = false;
  string                            sCode;
  string                            sQualifiedName(name());
  const AdtCppAssignmentExpression* pAssignmentExpression = (const AdtCppAssignmentExpression*)this->findAscendantWithClass("AdtCppAssignmentExpression");

  if (HasBrackets && (pAssignmentExpression != 0))
  {
    // Function call. We need to determine if this Declarator is in an
    // expression or a statement context.
    //
    // In an expression context we need to find the definition of the name()
    // function and check that it has a non-void return value. If it does
    // not then we need to flag an error and halt as only FUNCTIONs can appear
    // in expressions.
    //
    // In a statement context we need to find the definition of the name()
    // function and check that it has a void return value. If it does not
    // then we need to flag and error and halt as only SUBROUTINEs can appear
    // in statements.
    //
    // The symbol name in name() must be fully qualified.
    //
    // If name() is xcopy or zero then we need to convert/expand the function
    // call into an equivalent slice operation.
    //
    // If name() is pow then we need to convert to equivalent ** operator
    // construct
    if (name() == "xcopy")
    {
      string          sBuffer;
      AdtFile         WriteFile;
      AdtSliceBuilder SliceBuilder;

      WriteFile.open(sBuffer);

      // Translate xcopy to slice operation
      writeFortranInner(WriteFile,
                        nMode,
                        sQualifiedName,
                        false);

      WriteFile.close();

      if (!SliceBuilder.convertXCopy(sBuffer, sCode))
      {
        SliceBuilder.reportError(sBuffer, lineNumber(), fileName());
      }
    }
    else if (name() == "zero")
    {
      string          sBuffer;
      AdtFile         WriteFile;
      AdtSliceBuilder SliceBuilder;

      WriteFile.open(sBuffer);

      // Translate zero to slice operation
      writeFortranInner(WriteFile,
                        nMode,
                        sQualifiedName,
                        false);

      WriteFile.close();

      if (!SliceBuilder.convertZero(sBuffer, sCode))
      {
        SliceBuilder.reportError(sBuffer, lineNumber(), fileName());
      }
    }
    else if ((name() == "pow") && (ExpressionList != 0) && (ExpressionList->listSize() == 2))
    {
      AdtParserPtrListConstIter Iter  = ExpressionList->objList().begin();
      AdtCppBase*               pObjA = (AdtCppBase*)(AdtParser*)*Iter;

      Iter++;

      AdtCppBase*               pObjB = (AdtCppBase*)(AdtParser*)*Iter;

      write(rOutFile, "(");

      pObjA->writeFortran(rOutFile, nMode);

      write(rOutFile, " ** ");

      pObjB->writeFortran(rOutFile, nMode);

      write(rOutFile, ")");

      return (rOutFile);
    }
    else
    {
      bool                            bIsStatement      = (pAssignmentExpression->findAscendantWithClassLineage("AdtCppExpression,AdtCppExpressionStatement,AdtCppStatement") != 0);
      const AdtCppFunctionDefinition* pFunctionContext  = (const AdtCppFunctionDefinition*)this->findAscendantWithClass("AdtCppFunctionDefinition");

      if (pFunctionContext != 0)
      {
        if (name().rfind("::") == string::npos)
        {
          // If not qualified then impose the function scope onto this call and
          // search for the function definition.
          const string& rContextName = pFunctionContext->qualifiedName();
          int           nPos         = (int)rContextName.rfind("::");

          if (nPos != string::npos)
          {
            string  sScope(rContextName, 0, nPos + 2);

            sQualifiedName = sScope + name();
          }
        }
      }

      // Is the function a FUNCTION or a SUBROUTINE or not known / intrinsic
      if (AdtCppTranslationUnit::isProcedure(sQualifiedName) ||
          (cppRootObject() != 0) && cppRootObject()->isIncludeSubroutine(name()))
      {
        if (!bIsStatement)
        {
          ::printf("ERROR: Cannot translate subroutine call in assignment to Fortran on "
                   "line %d in file %s\n", lineNumber(),
                                           fileName());
          AdtExit(-1);
        }

        bAddCall = true;
      }
      else if (AdtCppTranslationUnit::isFunction(sQualifiedName) ||
               (cppRootObject() != 0) && cppRootObject()->isIncludeFunction(name()))
      {
        if (bIsStatement)
        {
          ::printf("ERROR: Cannot translate function call without assignment to Fortran on "
                   "line %d in file %s\n", lineNumber(),
                                           fileName());
          AdtExit(-1);
        }
      }
      else
      {
        AdtParser* pExprStmt;

        sQualifiedName = name();

        // Guess if a subroutine by looking at the usage context.
        pExprStmt = findAscendantWithClassLineage("AdtCppDirectedExpression,AdtCppPostfixExpression,AdtCppUnaryExpression,"
                                                  "AdtCppMultiplicativeExpression,AdtCppAdditiveExpression,AdtCppShiftExpression,"
                                                  "AdtCppRelationalExpression,AdtCppEqualityExpression,AdtCppAndExpression,"
                                                  "AdtCppExclusiveOrExpression,AdtCppInclusiveOrExpression,AdtCppLogicalAndExpression,"
                                                  "AdtCppLogicalOrExpression,AdtCppConditionalExpression,AdtCppAssignmentExpression,"
                                                  "AdtCppExpression,AdtCppExpressionStatement");

        if (pExprStmt != 0)
        {
          // We are calling a function and ignore return value so assume it has
          // a void return type, hence procedure.
          bAddCall = true;
        }
      }
    }
  }

  if (sCode.length() > 0)
  {
    write(rOutFile, sCode);
    rOutFile.newline();
  }
  else
  {
    writeFortranInner(rOutFile,
                      nMode,
                      sQualifiedName,
                      bAddCall);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclaratorExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorExpressionDims method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclaratorExpressionDims::AdtCppDeclaratorExpressionDims(AdtParser* pExpressionObj)
 : AdtCppBase()
{
  add(pExpressionObj);
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorExpressionDims::AdtCppDeclaratorExpressionDims(const AdtCppDeclaratorExpressionDims& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorExpressionDims::~AdtCppDeclaratorExpressionDims()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorExpressionDims::writeCPP(AdtFile& rOutFile, int nMode) const
{
  rOutFile.write("[");
  forAllWriteCPP(rOutFile, nMode, "][", false, true);
  rOutFile.write("]");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorExpressionDims::writeFortran(AdtFile& rOutFile, int nMode) const
{
  rOutFile.write("(");
  forAllWriteFortran(rOutFile, nMode, ",", false, true);
  rOutFile.write(")");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclaratorExpressionDims, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppUnaryExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppUnaryExpression::AdtCppUnaryExpression(AdtParser* pPostfixExpressionObj,
                                             AdtParser* pUnaryExpressionObj,
                                             AdtParser* pUnaryOperatorObj,
                                             AdtParser* pExpressionObj,
                                             bool bIncrement)
 : AdtCppBase()
{
  initObject(PostfixExpression, pPostfixExpressionObj,  AdtCppPostfixExpression,  false);
  initObject(UnaryExpression,   pUnaryExpressionObj,    AdtCppUnaryExpression,    false);
  initObject(UnaryOperator,     pUnaryOperatorObj,      AdtCppUnaryOperator,      false);
  initObject(Expression,        pExpressionObj,         AdtCppExpression,         false);

  Increment = bIncrement;
}

//  ----------------------------------------------------------------------------

AdtCppUnaryExpression::AdtCppUnaryExpression(const AdtCppUnaryExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(PostfixExpression, rCopy, AdtCppPostfixExpression);
  copyObject(UnaryExpression,   rCopy, AdtCppUnaryExpression);
  copyObject(UnaryOperator,     rCopy, AdtCppUnaryOperator);
  copyObject(Expression,        rCopy, AdtCppExpression);

  Increment = rCopy.Increment;
}

//  ----------------------------------------------------------------------------

AdtCppUnaryExpression::~AdtCppUnaryExpression()
{
  UtlReleaseReference(PostfixExpression);
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(UnaryOperator);
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

bool AdtCppUnaryExpression::isSimple() const
{
  bool bIsSimple = ((PostfixExpression  != 0) &&
                    (UnaryExpression    == 0) &&
                    (UnaryOperator      == 0) &&
                    (Expression         == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUnaryExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if ((UnaryExpression    != 0) &&
      (PostfixExpression  == 0) &&
      (UnaryOperator      == 0) &&
      (Expression         == 0))
  {
    if (Increment)
    {
      write(rOutFile, "++");
    }
    else
    {
      write(rOutFile, "--");
    }

    UnaryExpression->writeCPP(rOutFile, nMode);
  }
  else if ((UnaryExpression    != 0) &&
           (UnaryOperator      != 0) &&
           (PostfixExpression  == 0) &&
           (Expression         == 0))
  {
    UnaryOperator->writeCPP(rOutFile, nMode);
    UnaryExpression->writeCPP(rOutFile, nMode);
  }
  else if (Expression != 0)
  {
    write(rOutFile, "sizeof(");
    Expression->writeCPP(rOutFile, nMode);
    write(rOutFile, ")");
  }
  else if (PostfixExpression != 0)
  {
    PostfixExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUnaryExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if ((UnaryExpression    != 0) &&
      (PostfixExpression  == 0) &&
      (UnaryOperator      == 0) &&
      (Expression         == 0))
  {
    if (parentSimpleLineageTo("AdtCppAssignmentExpression"))
    {
      AdtFile File;
      string  sArg;

      File.open(sArg);
      UnaryExpression->writeFortran(File, nMode);
      File.close();

      write(rOutFile, sArg);
      write(rOutFile, " = ");
      write(rOutFile, sArg);

      if (Increment)
      {
        write(rOutFile, " + 1");
      }
      else
      {
        write(rOutFile, " - 1");
      }
    }
    else
    {
      if (Increment)
      {
        write(rOutFile, "PREINC(");
      }
      else
      {
        write(rOutFile, "PREDEC(");
      }

      UnaryExpression->writeFortran(rOutFile, nMode);

      write(rOutFile, ")");
    }
  }
  else if ((UnaryExpression    != 0) &&
           (UnaryOperator      != 0) &&
           (PostfixExpression  == 0) &&
           (Expression         == 0))
  {
    switch (UnaryOperator->op())
    {
      case UnaryOp_PLUS:
      {
        write(rOutFile, "+");
        UnaryExpression->writeFortran(rOutFile, nMode);
        break;
      }

      case UnaryOp_MINUS:
      {
        write(rOutFile, "-");
        UnaryExpression->writeFortran(rOutFile, nMode);
        break;
      }

      case UnaryOp_LNOT:
      {
        write(rOutFile, ".NOT.");
        UnaryExpression->writeFortran(rOutFile, nMode);
        break;
      }

      case UnaryOp_NOT:
      {
        write(rOutFile, "INOT(");
        UnaryExpression->writeFortran(rOutFile, nMode);
        write(rOutFile, ")");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }
  else if (Expression != 0)
  {
    ::printf("ERROR: sizeof not supported in translation to Fortran on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }
  else if (PostfixExpression != 0)
  {
    PostfixExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppUnaryExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppUnaryOperator method implementations
//  ----------------------------------------------------------------------------
AdtCppUnaryOperator::AdtCppUnaryOperator(AdtCppUnaryOp nOp)
 : AdtCppBase()
{
  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppUnaryOperator::AdtCppUnaryOperator(const AdtCppUnaryOperator& rCopy)
 : AdtCppBase(rCopy)
{
  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppUnaryOperator::~AdtCppUnaryOperator()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUnaryOperator::writeCPP(AdtFile& rOutFile, int nMode) const
{
  switch (Op)
  {
    case UnaryOp_PLUS:
    {
      write(rOutFile, "+");
      break;
    }

    case UnaryOp_MINUS:
    {
      write(rOutFile, "-");
      break;
    }

    case UnaryOp_LNOT:
    {
      write(rOutFile, "!");
      break;
    }

    case UnaryOp_NOT:
    {
      write(rOutFile, "~");
      break;
    }

    default:
    {
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUnaryOperator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppUnaryOperator, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMultiplicativeExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppMultiplicativeExpression::AdtCppMultiplicativeExpression(AdtCppMultiplicativeOp nOp,
                                                               AdtParser* pUnaryExpressionObj,
                                                               AdtParser* pMultiplicativeExpressionObj)
 : AdtCppBase()
{
  initObject(UnaryExpression,           pUnaryExpressionObj,          AdtCppUnaryExpression,          false);
  initObject(MultiplicativeExpression,  pMultiplicativeExpressionObj, AdtCppMultiplicativeExpression, false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppMultiplicativeExpression::AdtCppMultiplicativeExpression(const AdtCppMultiplicativeExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(UnaryExpression,           rCopy, AdtCppUnaryExpression);
  copyObject(MultiplicativeExpression,  rCopy, AdtCppMultiplicativeExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppMultiplicativeExpression::~AdtCppMultiplicativeExpression()
{
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(MultiplicativeExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppMultiplicativeExpression::isSimple() const
{
  bool bIsSimple = ((UnaryExpression          != 0) &&
                    (MultiplicativeExpression == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMultiplicativeExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (MultiplicativeExpression != 0)
  {
    MultiplicativeExpression->writeCPP(rOutFile, nMode);

    switch (Op)
    {
      case MultiplicativeOp_PROD:
      {
        write(rOutFile, " * ");
        break;
      }

      case MultiplicativeOp_DIV:
      {
        write(rOutFile, " / ");
        break;
      }

      case MultiplicativeOp_MOD:
      {
        write(rOutFile, " % ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (UnaryExpression != 0)
  {
    UnaryExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMultiplicativeExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  bool bAddBracket = false;

  if (MultiplicativeExpression != 0)
  {
    switch (Op)
    {
      case MultiplicativeOp_PROD:
      {
        MultiplicativeExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, " * ");
        break;
      }

      case MultiplicativeOp_DIV:
      {
        MultiplicativeExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, " / ");
        break;
      }

      case MultiplicativeOp_MOD:
      {
        write(rOutFile, "MOD(");

        MultiplicativeExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, ",");
        bAddBracket = true;
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (UnaryExpression != 0)
  {
    UnaryExpression->writeFortran(rOutFile, nMode);
  }

  if (bAddBracket)
  {
    write(rOutFile, ")");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMultiplicativeExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppAdditiveExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppAdditiveExpression::AdtCppAdditiveExpression(AdtCppAdditiveOp nOp,
                                                   AdtParser* pMultiplicativeExpressionObj,
                                                   AdtParser* pAdditiveExpressionObj)
 : AdtCppBase()
{
  initObject(MultiplicativeExpression,  pMultiplicativeExpressionObj, AdtCppMultiplicativeExpression, false);
  initObject(AdditiveExpression,        pAdditiveExpressionObj,       AdtCppAdditiveExpression,       false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppAdditiveExpression::AdtCppAdditiveExpression(const AdtCppAdditiveExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(MultiplicativeExpression,  rCopy, AdtCppMultiplicativeExpression);
  copyObject(AdditiveExpression,        rCopy, AdtCppAdditiveExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppAdditiveExpression::~AdtCppAdditiveExpression()
{
  UtlReleaseReference(MultiplicativeExpression);
  UtlReleaseReference(AdditiveExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppAdditiveExpression::isSimple() const
{
  bool bIsSimple = ((MultiplicativeExpression != 0) &&
                    (AdditiveExpression       == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAdditiveExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (AdditiveExpression != 0)
  {
    AdditiveExpression->writeCPP(rOutFile, nMode);

    switch (Op)
    {
      case AdditiveOp_PLUS:
      {
        write(rOutFile, " + ");
        break;
      }

      case AdditiveOp_MINUS:
      {
        write(rOutFile, " - ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (MultiplicativeExpression != 0)
  {
    MultiplicativeExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAdditiveExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (AdditiveExpression != 0)
  {
    AdditiveExpression->writeFortran(rOutFile, nMode);

    switch (Op)
    {
      case AdditiveOp_PLUS:
      {
        write(rOutFile, " + ");
        break;
      }

      case AdditiveOp_MINUS:
      {
        write(rOutFile, " - ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (MultiplicativeExpression != 0)
  {
    MultiplicativeExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppAdditiveExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppShiftExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppShiftExpression::AdtCppShiftExpression(AdtCppShiftOp nOp,
                                             AdtParser* pAdditiveExpressionObj,
                                             AdtParser* pShiftExpressionObj)
 : AdtCppBase()
{
  initObject(AdditiveExpression,  pAdditiveExpressionObj, AdtCppAdditiveExpression, false);
  initObject(ShiftExpression,     pShiftExpressionObj,    AdtCppShiftExpression,    false);
;

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppShiftExpression::AdtCppShiftExpression(const AdtCppShiftExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(AdditiveExpression,  rCopy, AdtCppAdditiveExpression);
  copyObject(ShiftExpression,     rCopy, AdtCppShiftExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppShiftExpression::~AdtCppShiftExpression()
{
  UtlReleaseReference(AdditiveExpression);
  UtlReleaseReference(ShiftExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppShiftExpression::isSimple() const
{
  bool bIsSimple = ((AdditiveExpression != 0) &&
                    (ShiftExpression    == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppShiftExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ShiftExpression != 0)
  {
    ShiftExpression->writeCPP(rOutFile, nMode);

    switch (Op)
    {
      case AdtCppShiftOp_SHL:
      {
        write(rOutFile, " << ");
        break;
      }

      case AdtCppShiftOp_SHR:
      {
        write(rOutFile, " >> ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (AdditiveExpression != 0)
  {
    AdditiveExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppShiftExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  bool bHasShift = false;

  if (ShiftExpression != 0)
  {
    switch (Op)
    {
      case AdtCppShiftOp_SHL:
      {
        write(rOutFile, "LSHIFT(");

        ShiftExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, ",");

        bHasShift = true;
        break;
      }

      case AdtCppShiftOp_SHR:
      {
        write(rOutFile, "RSHIFT(");

        ShiftExpression->writeFortran(rOutFile, nMode);

        write(rOutFile, ",");

        bHasShift = true;
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (AdditiveExpression != 0)
  {
    AdditiveExpression->writeFortran(rOutFile, nMode);
  }

  if (bHasShift)
  {
    write(rOutFile, ")");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppShiftExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppRelationalExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppRelationalExpression::AdtCppRelationalExpression(AdtCppRelationalOp nOp,
                                                       AdtParser* pShiftExpressionObj,
                                                       AdtParser* pRelationalExpressionObj)
 : AdtCppBase()
{
  initObject(ShiftExpression,       pShiftExpressionObj,      AdtCppShiftExpression,      false);
  initObject(RelationalExpression,  pRelationalExpressionObj, AdtCppRelationalExpression, false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppRelationalExpression::AdtCppRelationalExpression(const AdtCppRelationalExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ShiftExpression,       rCopy, AdtCppShiftExpression);
  copyObject(RelationalExpression,  rCopy, AdtCppRelationalExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppRelationalExpression::~AdtCppRelationalExpression()
{
  UtlReleaseReference(ShiftExpression);
  UtlReleaseReference(RelationalExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppRelationalExpression::isSimple() const
{
  bool bIsSimple = ((ShiftExpression      != 0) &&
                    (RelationalExpression == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppRelationalExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (RelationalExpression != 0)
  {
    RelationalExpression->writeCPP(rOutFile, nMode);

    switch (Op)
    {
      case AdtCppRelationalOp_LT:
      {
        write(rOutFile, " < ");
        break;
      }

      case AdtCppRelationalOp_GT:
      {
        write(rOutFile, " > ");
        break;
      }

      case AdtCppRelationalOp_LT_EQ:
      {
        write(rOutFile, " <= ");
        break;
      }

      case AdtCppRelationalOp_GT_EQ:
      {
        write(rOutFile, " >= ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (ShiftExpression != 0)
  {
    ShiftExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppRelationalExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (RelationalExpression != 0)
  {
    RelationalExpression->writeFortran(rOutFile, nMode);

    switch (Op)
    {
      case AdtCppRelationalOp_LT:
      {
        write(rOutFile, " .LT. ");
        break;
      }

      case AdtCppRelationalOp_GT:
      {
        write(rOutFile, " .GT. ");
        break;
      }

      case AdtCppRelationalOp_LT_EQ:
      {
        write(rOutFile, " .LE. ");
        break;
      }

      case AdtCppRelationalOp_GT_EQ:
      {
        write(rOutFile, " .GE. ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (ShiftExpression != 0)
  {
    ShiftExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppRelationalExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppEqualityExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppEqualityExpression::AdtCppEqualityExpression(AdtCppEqualityOp nOp,
                                                   AdtParser* pRelationalExpressionObj,
                                                   AdtParser* pEqualityExpressionObj)
 : AdtCppBase()
{
  initObject(RelationalExpression,  pRelationalExpressionObj, AdtCppRelationalExpression, false);
  initObject(EqualityExpression,    pEqualityExpressionObj,   AdtCppEqualityExpression,   false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppEqualityExpression::AdtCppEqualityExpression(const AdtCppEqualityExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(RelationalExpression,  rCopy, AdtCppRelationalExpression);
  copyObject(EqualityExpression,    rCopy, AdtCppEqualityExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppEqualityExpression::~AdtCppEqualityExpression()
{
  UtlReleaseReference(RelationalExpression);
  UtlReleaseReference(EqualityExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppEqualityExpression::isSimple() const
{
  bool bIsSimple = ((RelationalExpression != 0) &&
                    (EqualityExpression   == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEqualityExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (EqualityExpression != 0)
  {
    EqualityExpression->writeCPP(rOutFile, nMode);

    switch (Op)
    {
      case AdtCppEqualityOp_EQEQ:
      {
        write(rOutFile, " == ");
        break;
      }

      case AdtCppEqualityOp_NEQ:
      {
        write(rOutFile, " != ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (RelationalExpression != 0)
  {
    RelationalExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEqualityExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (EqualityExpression != 0)
  {
    EqualityExpression->writeFortran(rOutFile, nMode);

    switch (Op)
    {
      case AdtCppEqualityOp_EQEQ:
      {
        write(rOutFile, " .EQ. ");
        break;
      }

      case AdtCppEqualityOp_NEQ:
      {
        write(rOutFile, " .NE. ");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }

  if (RelationalExpression != 0)
  {
    RelationalExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppEqualityExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppAndExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppAndExpression::AdtCppAndExpression(AdtParser* pEqualityExpressionObj,
                                         AdtParser* pAndExpressionObj)
 : AdtCppBase()
{
  initObject(EqualityExpression,  pEqualityExpressionObj, AdtCppEqualityExpression, false);
  initObject(AndExpression,       pAndExpressionObj,      AdtCppAndExpression,      false);
;
}

//  ----------------------------------------------------------------------------

AdtCppAndExpression::AdtCppAndExpression(const AdtCppAndExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(EqualityExpression,  rCopy, AdtCppEqualityExpression);
  copyObject(AndExpression,       rCopy, AdtCppAndExpression);
}

//  ----------------------------------------------------------------------------

AdtCppAndExpression::~AdtCppAndExpression()
{
  UtlReleaseReference(EqualityExpression);
  UtlReleaseReference(AndExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppAndExpression::isSimple() const
{
  bool bIsSimple = ((EqualityExpression != 0) &&
                    (AndExpression      == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAndExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (AndExpression != 0)
  {
    AndExpression->writeCPP(rOutFile, nMode);

    write(rOutFile, " & ");
  }

  if (EqualityExpression != 0)
  {
    EqualityExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAndExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (AndExpression != 0)
  {
    write(rOutFile, "IAND(");
    AndExpression->writeFortran(rOutFile, nMode);
    write(rOutFile, ",");

    if (EqualityExpression != 0)
    {
      EqualityExpression->writeFortran(rOutFile, nMode);
    }
    write(rOutFile, ")");
  }
  else if (EqualityExpression != 0)
  {
    EqualityExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppAndExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppExclusiveOrExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppExclusiveOrExpression::AdtCppExclusiveOrExpression(AdtParser* pAndExpressionObj,
                                                         AdtParser* pExclusiveOrExpressionObj)
 : AdtCppBase()
{
  initObject(AndExpression,         pAndExpressionObj,          AdtCppAndExpression,          false);
  initObject(ExclusiveOrExpression, pExclusiveOrExpressionObj,  AdtCppExclusiveOrExpression,  false);
}

//  ----------------------------------------------------------------------------

AdtCppExclusiveOrExpression::AdtCppExclusiveOrExpression(const AdtCppExclusiveOrExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(AndExpression,         rCopy, AdtCppAndExpression);
  copyObject(ExclusiveOrExpression, rCopy, AdtCppExclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtCppExclusiveOrExpression::~AdtCppExclusiveOrExpression()
{
  UtlReleaseReference(AndExpression);
  UtlReleaseReference(ExclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppExclusiveOrExpression::isSimple() const
{
  bool bIsSimple = ((AndExpression          != 0) &&
                    (ExclusiveOrExpression  == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExclusiveOrExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ExclusiveOrExpression != 0)
  {
    ExclusiveOrExpression->writeCPP(rOutFile, nMode);

    write(rOutFile, " ^ ");
  }

  if (AndExpression != 0)
  {
    AndExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExclusiveOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ExclusiveOrExpression != 0)
  {
    write(rOutFile, "IEOR(");
    ExclusiveOrExpression->writeFortran(rOutFile, nMode);
    write(rOutFile, ",");

    if (AndExpression != 0)
    {
      AndExpression->writeFortran(rOutFile, nMode);
    }

    write(rOutFile, ")");
  }
  else if (AndExpression != 0)
  {
    AndExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppExclusiveOrExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInclusiveOrExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppInclusiveOrExpression::AdtCppInclusiveOrExpression(AdtParser* pExclusiveOrExpressionObj,
                                                         AdtParser* pInclusiveOrExpressionObj)
 : AdtCppBase()
{
  initObject(ExclusiveOrExpression, pExclusiveOrExpressionObj,  AdtCppExclusiveOrExpression,  false);
  initObject(InclusiveOrExpression, pInclusiveOrExpressionObj,  AdtCppInclusiveOrExpression,  false);
}

//  ----------------------------------------------------------------------------

AdtCppInclusiveOrExpression::AdtCppInclusiveOrExpression(const AdtCppInclusiveOrExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ExclusiveOrExpression, rCopy, AdtCppExclusiveOrExpression);
  copyObject(InclusiveOrExpression, rCopy, AdtCppInclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtCppInclusiveOrExpression::~AdtCppInclusiveOrExpression()
{
  UtlReleaseReference(ExclusiveOrExpression);
  UtlReleaseReference(InclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppInclusiveOrExpression::isSimple() const
{
  bool bIsSimple = ((ExclusiveOrExpression  != 0) &&
                    (InclusiveOrExpression  == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInclusiveOrExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (InclusiveOrExpression != 0)
  {
    InclusiveOrExpression->writeCPP(rOutFile, nMode);

    write(rOutFile, " | ");
  }

  if (ExclusiveOrExpression != 0)
  {
    ExclusiveOrExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInclusiveOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (InclusiveOrExpression != 0)
  {
    write(rOutFile, "IOR(");
    InclusiveOrExpression->writeFortran(rOutFile, nMode);
    write(rOutFile, ",");

    if (ExclusiveOrExpression != 0)
    {
      ExclusiveOrExpression->writeFortran(rOutFile, nMode);
    }

    write(rOutFile, ")");
  }
  else if (ExclusiveOrExpression != 0)
  {
    ExclusiveOrExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInclusiveOrExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppLogicalAndExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppLogicalAndExpression::AdtCppLogicalAndExpression(AdtParser* pInclusiveOrExpressionObj,
                                                       AdtParser* pLogicalAndExpressionObj)
 : AdtCppBase()
{
  initObject(InclusiveOrExpression, pInclusiveOrExpressionObj,  AdtCppInclusiveOrExpression,  false);
  initObject(LogicalAndExpression,  pLogicalAndExpressionObj,   AdtCppLogicalAndExpression,   false);
}

//  ----------------------------------------------------------------------------

AdtCppLogicalAndExpression::AdtCppLogicalAndExpression(const AdtCppLogicalAndExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(InclusiveOrExpression, rCopy, AdtCppInclusiveOrExpression);
  copyObject(LogicalAndExpression,  rCopy, AdtCppLogicalAndExpression);
}

//  ----------------------------------------------------------------------------

AdtCppLogicalAndExpression::~AdtCppLogicalAndExpression()
{
  UtlReleaseReference(InclusiveOrExpression);
  UtlReleaseReference(LogicalAndExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppLogicalAndExpression::isSimple() const
{
  bool bIsSimple = ((InclusiveOrExpression  != 0) &&
                    (LogicalAndExpression   == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLogicalAndExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (LogicalAndExpression != 0)
  {
    LogicalAndExpression->writeCPP(rOutFile, nMode);

    write(rOutFile, " && ");
  }

  if (InclusiveOrExpression != 0)
  {
    InclusiveOrExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLogicalAndExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (LogicalAndExpression != 0)
  {
    LogicalAndExpression->writeFortran(rOutFile, nMode);

    write(rOutFile, " .AND. ");
  }

  if (InclusiveOrExpression != 0)
  {
    InclusiveOrExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppLogicalAndExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppLogicalOrExpression class
//  ----------------------------------------------------------------------------
AdtCppLogicalOrExpression::AdtCppLogicalOrExpression(AdtParser* pLogicalAndExpressionObj,
                                                     AdtParser* pLogicalOrExpressionObj)
 : AdtCppBase()
{
  initObject(LogicalAndExpression,  pLogicalAndExpressionObj, AdtCppLogicalAndExpression, false);
  initObject(LogicalOrExpression,   pLogicalOrExpressionObj,  AdtCppLogicalOrExpression,  false);
}

//  ----------------------------------------------------------------------------

AdtCppLogicalOrExpression::AdtCppLogicalOrExpression(const AdtCppLogicalOrExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(LogicalAndExpression,  rCopy, AdtCppLogicalAndExpression);
  copyObject(LogicalOrExpression,   rCopy, AdtCppLogicalOrExpression);
}

//  ----------------------------------------------------------------------------

AdtCppLogicalOrExpression::~AdtCppLogicalOrExpression()
{
  UtlReleaseReference(LogicalAndExpression);
  UtlReleaseReference(LogicalOrExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppLogicalOrExpression::isSimple() const
{
  bool bIsSimple = ((LogicalAndExpression != 0) &&
                    (LogicalOrExpression  == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLogicalOrExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (LogicalOrExpression != 0)
  {
    LogicalOrExpression->writeCPP(rOutFile, nMode);

    write(rOutFile, " || ");
  }

  if (LogicalAndExpression != 0)
  {
    LogicalAndExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLogicalOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (LogicalOrExpression != 0)
  {
    LogicalOrExpression->writeFortran(rOutFile, nMode);

    write(rOutFile, " .OR. ");
  }

  if (LogicalAndExpression != 0)
  {
    LogicalAndExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppLogicalOrExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppConditionalExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppConditionalExpression::AdtCppConditionalExpression(AdtParser* pLogicalOrExpressionObj,
                                                         AdtParser* pExpressionObj,
                                                         AdtParser* pAssignmentExpressionObj)
 : AdtCppBase()
{
  initObject(LogicalOrExpression,   pLogicalOrExpressionObj,  AdtCppLogicalOrExpression,  false);
  initObject(Expression,            pExpressionObj,           AdtCppExpression,           false);
  initObject(AssignmentExpression,  pAssignmentExpressionObj, AdtCppAssignmentExpression, false);
}

//  ----------------------------------------------------------------------------

AdtCppConditionalExpression::AdtCppConditionalExpression(const AdtCppConditionalExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(LogicalOrExpression,   rCopy, AdtCppLogicalOrExpression);
  copyObject(Expression,            rCopy, AdtCppExpression);
  copyObject(AssignmentExpression,  rCopy, AdtCppAssignmentExpression);
}

//  ----------------------------------------------------------------------------

AdtCppConditionalExpression::~AdtCppConditionalExpression()
{
  UtlReleaseReference(LogicalOrExpression);
  UtlReleaseReference(Expression);
  UtlReleaseReference(AssignmentExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppConditionalExpression::isSimple() const
{
  bool bIsSimple = ((LogicalOrExpression  != 0) &&
                    (Expression           == 0) &&
                    (AssignmentExpression == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppConditionalExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (LogicalOrExpression != 0)
  {
    LogicalOrExpression->writeCPP(rOutFile, nMode);
  }

  if ((Expression != 0) && (AssignmentExpression != 0))
  {
    write(rOutFile, " ? ");

    Expression->writeCPP(rOutFile, nMode);

    write(rOutFile, " : ");

    AssignmentExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppConditionalExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (LogicalOrExpression != 0)
  {
    LogicalOrExpression->writeFortran(rOutFile, nMode);
  }

  if ((Expression != 0) && (AssignmentExpression != 0))
  {
    ::printf("ERROR: ? : ternary expression not supported in translation to Fortran on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppConditionalExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppAssignmentExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppAssignmentExpression::AdtCppAssignmentExpression(AdtParser* pConditionalExpressionObj,
                                                       AdtParser* pLogicalOrExpressionObj,
                                                       AdtParser* pAssignmentOperatorObj,
                                                       AdtParser* pAssignmentExpressionObj)
 : AdtCppBase()
{
  initObject(ConditionalExpression, pConditionalExpressionObj,  AdtCppConditionalExpression,  false);
  initObject(AssignmentExpression,  pAssignmentExpressionObj,   AdtCppAssignmentExpression,   false);
  initObject(AssignmentOperator,    pAssignmentOperatorObj,     AdtCppAssignmentOperator,     false);
  initObject(LogicalOrExpression,   pLogicalOrExpressionObj,    AdtCppLogicalOrExpression,    false);
}

//  ----------------------------------------------------------------------------

AdtCppAssignmentExpression::AdtCppAssignmentExpression(const AdtCppAssignmentExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ConditionalExpression, rCopy, AdtCppConditionalExpression);
  copyObject(AssignmentExpression,  rCopy, AdtCppAssignmentExpression);
  copyObject(AssignmentOperator,    rCopy, AdtCppAssignmentOperator);
  copyObject(LogicalOrExpression,   rCopy, AdtCppLogicalOrExpression);
}

//  ----------------------------------------------------------------------------

AdtCppAssignmentExpression::~AdtCppAssignmentExpression()
{
  UtlReleaseReference(ConditionalExpression);
  UtlReleaseReference(LogicalOrExpression);
  UtlReleaseReference(AssignmentOperator);
  UtlReleaseReference(AssignmentExpression);
}

//  ----------------------------------------------------------------------------

bool AdtCppAssignmentExpression::isSimple() const
{
  bool bIsSimple = ((ConditionalExpression  != 0) &&
                    (LogicalOrExpression    == 0) &&
                    (AssignmentOperator     == 0) &&
                    (AssignmentExpression   == 0));

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAssignmentExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ConditionalExpression != 0)
  {
    ConditionalExpression->writeCPP(rOutFile, nMode);
  }

  if (LogicalOrExpression != 0)
  {
    LogicalOrExpression->writeCPP(rOutFile, nMode);
  }

  if (AssignmentOperator != 0)
  {
    AssignmentOperator->writeCPP(rOutFile, nMode);
  }

  if (AssignmentExpression != 0)
  {
    AssignmentExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAssignmentExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ConditionalExpression != 0)
  {
    ConditionalExpression->writeFortran(rOutFile, nMode);
  }
  else
  {
    string  sLHS;
    string  sRHS;
    string  sAssignment(" = ");
    AdtFile StringFile;
    bool    bRHS = true;

    StringFile.open(sLHS);

    if (LogicalOrExpression != 0)
    {
      LogicalOrExpression->writeFortran(StringFile, nMode);
    }

    StringFile.close();

    StringFile.open(sRHS);

    if (AssignmentExpression != 0)
    {
      AssignmentExpression->writeFortran(StringFile, nMode);
    }

    StringFile.close();

    if (AssignmentOperator != 0)
    {
      bRHS = false;

      switch (AssignmentOperator->op())
      {
        case AdtCppAssignmentOp_EQ:
        {
          bRHS = true;
          break;
        }

        case AdtCppAssignmentOp_PROD_EQ:
        {
          sAssignment += sLHS + " * (" + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_DIV_EQ:
        {
          sAssignment += sLHS + " / (" + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_MOD_EQ:
        {
          sAssignment += "MOD(" + sLHS + "," + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_P_EQ:
        {
          sAssignment += sLHS + " + (" + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_M_EQ:
        {
          sAssignment += sLHS + " - (" + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_SHL_EQ:
        {
          sAssignment += "LSHIFT(" + sLHS + "," + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_SHR_EQ:
        {
          sAssignment += "RSHIFT(" + sLHS + "," + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_AND_EQ:
        {
          sAssignment += "IAND(" + sLHS + "," + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_XOR_EQ:
        {
          sAssignment += "IEOR(" + sLHS + "," + sRHS + ")";
          break;
        }

        case AdtCppAssignmentOp_OR_EQ:
        {
          sAssignment += "IOR(" + sLHS + "," + sRHS + ")";
          break;
        }

        default:
        {
          FAIL();
          break;
        }
      }
    }

    write(rOutFile, sLHS);
    write(rOutFile, sAssignment);

    if (bRHS)
    {
      write(rOutFile, sRHS);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppAssignmentExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppAssignmentOperator method implementations
//  ----------------------------------------------------------------------------
AdtCppAssignmentOperator::AdtCppAssignmentOperator(AdtCppAssignmentOp nOp)
 : AdtCppBase()
{
  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtCppAssignmentOperator::AdtCppAssignmentOperator(const AdtCppAssignmentOperator& rCopy)
 : AdtCppBase(rCopy)
{
  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtCppAssignmentOperator::~AdtCppAssignmentOperator()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAssignmentOperator::writeCPP(AdtFile& rOutFile, int nMode) const
{
  switch (Op)
  {
    case AdtCppAssignmentOp_EQ:
    {
      write(rOutFile, " = ");
      break;
    }

    case AdtCppAssignmentOp_PROD_EQ:
    {
      write(rOutFile, " *= ");
      break;
    }

    case AdtCppAssignmentOp_DIV_EQ:
    {
      write(rOutFile, " /= ");
      break;
    }

    case AdtCppAssignmentOp_MOD_EQ:
    {
      write(rOutFile, " %= ");
      break;
    }

    case AdtCppAssignmentOp_P_EQ:
    {
      write(rOutFile, " += ");
      break;
    }

    case AdtCppAssignmentOp_M_EQ:
    {
      write(rOutFile, " -= ");
      break;
    }

    case AdtCppAssignmentOp_SHL_EQ:
    {
      write(rOutFile, " <<= ");
      break;
    }

    case AdtCppAssignmentOp_SHR_EQ:
    {
      write(rOutFile, " >>= ");
      break;
    }

    case AdtCppAssignmentOp_AND_EQ:
    {
      write(rOutFile, " &= ");
      break;
    }

    case AdtCppAssignmentOp_XOR_EQ:
    {
      write(rOutFile, " ^= ");
      break;
    }

    case AdtCppAssignmentOp_OR_EQ:
    {
      write(rOutFile, " |= ");
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAssignmentOperator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppAssignmentOperator, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppExpression::AdtCppExpression(AdtParser* pAssignmentExpressionObj,
                                   AdtParser* pExpressionObj)
 : AdtCppBase()
{
  initObject(AssignmentExpression,  pAssignmentExpressionObj, AdtCppAssignmentExpression, false);
  initObject(Expression,            pExpressionObj,           AdtCppExpression,           false);
}

//  ----------------------------------------------------------------------------

AdtCppExpression::AdtCppExpression(const AdtCppExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(AssignmentExpression,  rCopy, AdtCppAssignmentExpression);
  copyObject(Expression,            rCopy, AdtCppExpression);
}

//  ----------------------------------------------------------------------------

AdtCppExpression::~AdtCppExpression()
{
  UtlReleaseReference(AssignmentExpression);
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (Expression != 0)
  {
    Expression->writeCPP(rOutFile, nMode);

    write(rOutFile, " = ");
  }

  if (AssignmentExpression != 0)
  {
    AssignmentExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (Expression != 0)
  {
    Expression->writeFortran(rOutFile, nMode);

    write(rOutFile, " = ");
  }

  if (AssignmentExpression != 0)
  {
    AssignmentExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppConstantExpression method implementations
//  ----------------------------------------------------------------------------
AdtCppConstantExpression::AdtCppConstantExpression(AdtParser* pConditionalExpressionObj)
 : AdtCppBase()
{
  initObject(ConditionalExpression, pConditionalExpressionObj, AdtCppConditionalExpression, false);
}

//  ----------------------------------------------------------------------------

AdtCppConstantExpression::AdtCppConstantExpression(const AdtCppConstantExpression& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ConditionalExpression, rCopy, AdtCppConditionalExpression);
}

//  ----------------------------------------------------------------------------

AdtCppConstantExpression::~AdtCppConstantExpression()
{
  UtlReleaseReference(ConditionalExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppConstantExpression::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ConditionalExpression != 0)
  {
    ConditionalExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppConstantExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ConditionalExpression != 0)
  {
    ConditionalExpression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppConstantExpression, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppStatement::AdtCppStatement(AdtParser* pLabeledStatementObj,
                                 AdtParser* pExpressionStatementObj,
                                 AdtParser* pCompoundStatementObj,
                                 AdtParser* pSelectionStatementObj,
                                 AdtParser* pIterationStatementObj,
                                 AdtParser* pJumpStatementObj,
                                 AdtParser* pDeclarationStatementObj)
 : AdtCppBase()
{
  initObject(LabeledStatement,      pLabeledStatementObj,     AdtCppLabeledStatement,     false);
  initObject(ExpressionStatement,   pExpressionStatementObj,  AdtCppExpressionStatement,  false);
  initObject(CompoundStatement,     pCompoundStatementObj,    AdtCppCompoundStatement,    false);
  initObject(SelectionStatement,    pSelectionStatementObj,   AdtCppSelectionStatement,   false);
  initObject(IterationStatement,    pIterationStatementObj,   AdtCppIterationStatement,   false);
  initObject(JumpStatement,         pJumpStatementObj,        AdtCppJumpStatement,        false);
  initObject(DeclarationStatement,  pDeclarationStatementObj, AdtCppDeclarationStatement, false);
;
}

//  ----------------------------------------------------------------------------

AdtCppStatement::AdtCppStatement(const AdtCppStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(LabeledStatement,      rCopy, AdtCppLabeledStatement);
  copyObject(ExpressionStatement,   rCopy, AdtCppExpressionStatement);
  copyObject(CompoundStatement,     rCopy, AdtCppCompoundStatement);
  copyObject(SelectionStatement,    rCopy, AdtCppSelectionStatement);
  copyObject(IterationStatement,    rCopy, AdtCppIterationStatement);
  copyObject(JumpStatement,         rCopy, AdtCppJumpStatement);
  copyObject(DeclarationStatement,  rCopy, AdtCppDeclarationStatement);
}

//  ----------------------------------------------------------------------------

AdtCppStatement::~AdtCppStatement()
{
  UtlReleaseReference(LabeledStatement);
  UtlReleaseReference(ExpressionStatement);
  UtlReleaseReference(CompoundStatement);
  UtlReleaseReference(SelectionStatement);
  UtlReleaseReference(IterationStatement);
  UtlReleaseReference(JumpStatement);
  UtlReleaseReference(DeclarationStatement);
}

//  ----------------------------------------------------------------------------

void AdtCppStatement::linespace(AdtFile& pOutFile,
                                bool& bLineSpace,
                                const AdtCppBase* pLastObj,
                                bool bPre) const
{
  if (LabeledStatement != 0)
  {
    LabeledStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (ExpressionStatement != 0)
  {
    ExpressionStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (CompoundStatement != 0)
  {
    CompoundStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (SelectionStatement != 0)
  {
    SelectionStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (IterationStatement != 0)
  {
    IterationStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (JumpStatement != 0)
  {
    JumpStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }

  if (DeclarationStatement != 0)
  {
    DeclarationStatement->linespace(pOutFile, bLineSpace, pLastObj, bPre);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (LabeledStatement != 0)
  {
    LabeledStatement->writeCPP(rOutFile, nMode);
  }

  if (ExpressionStatement != 0)
  {
    ExpressionStatement->writeCPP(rOutFile, nMode);
  }

  if (CompoundStatement != 0)
  {
    CompoundStatement->writeCPP(rOutFile, nMode);
  }

  if (SelectionStatement != 0)
  {
    SelectionStatement->writeCPP(rOutFile, nMode);
  }

  if (IterationStatement != 0)
  {
    IterationStatement->writeCPP(rOutFile, nMode);
  }

  if (JumpStatement != 0)
  {
    JumpStatement->writeCPP(rOutFile, nMode);
  }

  if (DeclarationStatement != 0)
  {
    DeclarationStatement->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (LabeledStatement != 0)
  {
    LabeledStatement->writeFortran(rOutFile, nMode);
  }

  if (ExpressionStatement != 0)
  {
    ExpressionStatement->writeFortran(rOutFile, nMode);
  }

  if (CompoundStatement != 0)
  {
    CompoundStatement->writeFortran(rOutFile, nMode);
  }

  if (SelectionStatement != 0)
  {
    SelectionStatement->writeFortran(rOutFile, nMode);
  }

  if (IterationStatement != 0)
  {
    IterationStatement->writeFortran(rOutFile, nMode);
  }

  if (JumpStatement != 0)
  {
    JumpStatement->writeFortran(rOutFile, nMode);
  }

  if (DeclarationStatement != 0)
  {
    DeclarationStatement->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppLabeledStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppLabeledStatement::AdtCppLabeledStatement(AdtParser* pConstantExpressionObj,
                                               AdtParser* pStatementObj,
                                               const char* pIdentifier,
                                               bool bIsDefault,
                                               const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);

  initObject(ConstantExpression,  pConstantExpressionObj, AdtCppConstantExpression, false);
  initObject(Statement,           pStatementObj,          AdtCppStatement,          false);

  IsDefault = bIsDefault;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppLabeledStatement::AdtCppLabeledStatement(const AdtCppLabeledStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ConstantExpression,  rCopy, AdtCppConstantExpression);
  copyObject(Statement,           rCopy, AdtCppStatement);

  IsDefault = rCopy.IsDefault;
}

//  ----------------------------------------------------------------------------

AdtCppLabeledStatement::~AdtCppLabeledStatement()
{
  UtlReleaseReference(ConstantExpression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLabeledStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (ConstantExpression != 0)
  {
    write(rOutFile, "case ");

    ConstantExpression->writeCPP(rOutFile, nMode);
  }
  else if (IsDefault)
  {
    write(rOutFile, "default");
  }
  else
  {
    write(rOutFile, name());
  }

  write(rOutFile, ":");

  if (Statement != 0)
  {
    if (!IsDefault)
    {
      rOutFile.newline();
    }

    Statement->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLabeledStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ConstantExpression != 0)
  {
    write(rOutFile, "CASE (");

    ConstantExpression->writeFortran(rOutFile, nMode);
    write(rOutFile, ") ");
  }
  else if (IsDefault)
  {
    write(rOutFile, "CASE DEFAULT ");
  }
  else
  {
    write(rOutFile, name());
  }

  if (Statement != 0)
  {
    if (!IsDefault)
    {
      rOutFile.newline();
    }

    Statement->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppLabeledStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppExpressionStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppExpressionStatement::AdtCppExpressionStatement(AdtParser* pExpressionObj,
                                                     const char* pComment)
 : AdtCppBase()
{
  initObject(Expression, pExpressionObj, AdtCppExpression, false);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppExpressionStatement::AdtCppExpressionStatement(const AdtCppExpressionStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Expression, rCopy, AdtCppExpression);
}

//  ----------------------------------------------------------------------------

AdtCppExpressionStatement::~AdtCppExpressionStatement()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpressionStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (Expression != 0)
  {
    Expression->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, ";");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppExpressionStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (Expression != 0)
  {
    Expression->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppExpressionStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppCompoundStatement meethod implementations
//  ----------------------------------------------------------------------------
AdtCppCompoundStatement::AdtCppCompoundStatement(AdtParser* pStatementSeqObj,
                                                 const char* pComment)
 : AdtCppBase()
{
  initObject(StatementSeq, pStatementSeqObj, AdtCppStatementSeq, false);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppCompoundStatement::AdtCppCompoundStatement(const AdtCppCompoundStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(StatementSeq, rCopy, AdtCppStatementSeq);
}

//  ----------------------------------------------------------------------------

AdtCppCompoundStatement::~AdtCppCompoundStatement()
{
  UtlReleaseReference(StatementSeq);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppCompoundStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "{");

  rOutFile.incrementIndent();
  rOutFile.newline();

  if (StatementSeq != 0)
  {
    StatementSeq->writeCPP(rOutFile, nMode);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();

  write(rOutFile, "}");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppCompoundStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  rOutFile.incrementIndent();
  rOutFile.newline();

  if (StatementSeq != 0)
  {
    StatementSeq->writeFortran(rOutFile, nMode);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppCompoundStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppStatementSeq method implementations
//  ----------------------------------------------------------------------------
AdtCppStatementSeq::AdtCppStatementSeq(AdtParser* pStatementObj)
 : AdtCppBase()
{
  add(pStatementObj);
}

//  ----------------------------------------------------------------------------

AdtCppStatementSeq::AdtCppStatementSeq(const AdtCppStatementSeq& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppStatementSeq::~AdtCppStatementSeq()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppStatementSeq::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, "", true, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppStatementSeq::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, "", true, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppStatementSeq, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppSelectionStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppSelectionStatement::AdtCppSelectionStatement(AdtParser* pExpressionObj,
                                                   AdtParser* pStatementObj,
                                                   AdtParser* pStatement2Obj,
                                                   bool bIsIf,
                                                   const char* pComment)
 : AdtCppBase()
{
  initObject(Expression,  pExpressionObj, AdtCppExpression, false);
  initObject(Statement,   pStatementObj,  AdtCppStatement,  false);
  initObject(Statement2,  pStatement2Obj, AdtCppStatement,  false);

  IsIf = bIsIf;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppSelectionStatement::AdtCppSelectionStatement(const AdtCppSelectionStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Expression,  rCopy, AdtCppExpression);
  copyObject(Statement,   rCopy, AdtCppStatement);
  copyObject(Statement2,  rCopy, AdtCppStatement);

  IsIf = rCopy.IsIf;
}

//  ----------------------------------------------------------------------------

AdtCppSelectionStatement::~AdtCppSelectionStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Statement);
  UtlReleaseReference(Statement2);
}

//  ----------------------------------------------------------------------------

void AdtCppSelectionStatement::linespace(AdtFile& pOutFile,
                                         bool& bLineSpace,
                                         const AdtCppBase* pLastObj,
                                         bool bPre) const
{
  if (!bLineSpace)
  {
    pOutFile.newline();

    bLineSpace = true;
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSelectionStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (IsIf)
  {
    write(rOutFile, "if (");

    if (Expression != 0)
    {
      Expression->writeCPP(rOutFile, nMode);
    }

    write(rOutFile, ")");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeCPP(rOutFile, nMode);
    }

    if (Statement2 != 0)
    {
      rOutFile.newline();

      write(rOutFile, "else");

      if (Statement2->findDescendant("SelectionStatement") == 0)
      {
        rOutFile.newline();
      }
      else
      {
        write(rOutFile, " ");
      }

      Statement2->writeCPP(rOutFile, nMode);
    }
  }
  else
  {
    write(rOutFile, "switch (");

    if (Expression != 0)
    {
      Expression->writeCPP(rOutFile, nMode);
    }

    write(rOutFile, ")");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeCPP(rOutFile, nMode);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSelectionStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (IsIf)
  {
    bool bWithEndIf = true;

    write(rOutFile, "IF (");

    if (Expression != 0)
    {
      Expression->writeFortran(rOutFile, nMode);
    }

    write(rOutFile, ") THEN ");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeFortran(rOutFile, nMode);
    }

    if (Statement2 != 0)
    {
      rOutFile.newline();

      write(rOutFile, "ELSE ");

      if (Statement2->findDescendant("SelectionStatement") == 0)
      {
        rOutFile.newline();
      }
      else
      {
        bWithEndIf = false;
      }

      Statement2->writeFortran(rOutFile, nMode);
    }

    if (bWithEndIf)
    {
      write(rOutFile, "END IF ");
    }

    rOutFile.newline();
  }
  else
  {
    write(rOutFile, "SELECT CASE (");

    if (Expression != 0)
    {
      Expression->writeFortran(rOutFile, nMode);
    }

    write(rOutFile, ")");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeFortran(rOutFile, nMode);
    }

    rOutFile.newline();

    write(rOutFile, "END SELECT ");

    rOutFile.newline();
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppSelectionStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppIterationStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppIterationStatement::AdtCppIterationStatement(AdtParser* pForInitStatementObj,
                                                   AdtParser* pExpressionObj,
                                                   AdtParser* pExpression2Obj,
                                                   AdtParser* pStatementObj,
                                                   bool bIsDo,
                                                   const char* pComment)
 : AdtCppBase()
{
  initObject(ForInitStatement,  pForInitStatementObj, AdtCppForInitStatement, false);
  initObject(Expression,        pExpressionObj,       AdtCppExpression,       false);
  initObject(Expression2,       pExpression2Obj,      AdtCppExpression,       false);
  initObject(Statement,         pStatementObj,        AdtCppStatement,        false);

  IsDo = bIsDo;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppIterationStatement::AdtCppIterationStatement(const AdtCppIterationStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ForInitStatement,  rCopy, AdtCppForInitStatement);
  copyObject(Expression,        rCopy, AdtCppExpression);
  copyObject(Expression2,       rCopy, AdtCppExpression);
  copyObject(Statement,         rCopy, AdtCppStatement);

  IsDo = rCopy.IsDo;
}

//  ----------------------------------------------------------------------------

AdtCppIterationStatement::~AdtCppIterationStatement()
{
  UtlReleaseReference(ForInitStatement);
  UtlReleaseReference(Expression);
  UtlReleaseReference(Expression2);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

void AdtCppIterationStatement::linespace(AdtFile& pOutFile,
                                         bool& bLineSpace,
                                         const AdtCppBase* pLastObj,
                                         bool bPre) const
{
  if (!bLineSpace)
  {
    pOutFile.newline();

    bLineSpace = true;
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppIterationStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if ((Statement        != 0) &&
      (Expression       != 0) &&
      (Expression2      == 0) &&
      (ForInitStatement == 0))
  {
    if (IsDo)
    {
      write(rOutFile, "do ");

      rOutFile.newline();
      Statement->writeCPP(rOutFile, nMode);

      write(rOutFile, "while (");

      Expression->writeCPP(rOutFile, nMode);

      write(rOutFile, ");");
    }
    else
    {
      write(rOutFile, "while (");

      Expression->writeCPP(rOutFile, nMode);

      write(rOutFile, ")");

      rOutFile.newline();

      Statement->writeCPP(rOutFile, nMode);
    }
  }
  else
  {
    write(rOutFile, "for (");

    if (ForInitStatement != 0)
    {
      ForInitStatement->writeCPP(rOutFile, nMode);
    }

    if (Expression != 0)
    {
      Expression->writeCPP(rOutFile, nMode);
    }

    write(rOutFile, "; ");

    if (Expression2 != 0)
    {
      Expression2->writeCPP(rOutFile, nMode);
    }

    write(rOutFile, ")");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeCPP(rOutFile, nMode);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppIterationStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if ((Statement        != 0) &&
      (Expression       != 0) &&
      (Expression2      == 0) &&
      (ForInitStatement == 0))
  {
    if (IsDo)
    {
      // Build an equivalent fortran construct
      // DO WHILE (.TRUE.)
      //  {Statement}
      //  IF (.NOT.{Expression})
      //    EXIT
      //  END IF
      // END DO
      write(rOutFile, "DO WHILE (.TRUE.)");

      rOutFile.newline();

      Statement->writeCPP(rOutFile, nMode);

      rOutFile.newline();

      write(rOutFile, "IF (.NOT.");
      Expression->writeCPP(rOutFile, nMode);
      write(rOutFile, ")");

      rOutFile.incrementIndent();
      rOutFile.newline();

      write(rOutFile, "EXIT");

      rOutFile.decrementIndent();
      rOutFile.newline();

      write(rOutFile, "END IF");

      rOutFile.newline();
    }
    else
    {
      write(rOutFile, "DO WHILE (");

      Expression->writeFortran(rOutFile, nMode);

      write(rOutFile, ")");

      rOutFile.newline();

      Statement->writeFortran(rOutFile, nMode);

      rOutFile.newline();

      write(rOutFile, "END DO ");

      rOutFile.newline();
    }
  }
  else
  {
    // C++ for loop form does not universally translate into DO contruct so
    // we instead make use of DO WHILE for which we can universally implement
    // the loop. General form is,
    // {ForInitStatement}
    // DO WHILE ({Expression})
    //   {Statement}
    //   {Expression2}
    // END DO
    if (ForInitStatement != 0)
    {
      ForInitStatement->writeFortran(rOutFile, nMode);
    }

    rOutFile.newline();

    write(rOutFile, "DO WHILE(");

    if (Expression != 0)
    {
      Expression->writeFortran(rOutFile, nMode);
    }

    write(rOutFile, ")");

    rOutFile.newline();

    if (Statement != 0)
    {
      Statement->writeFortran(rOutFile, nMode);
    }

    rOutFile.newline();

    if (Expression2 != 0)
    {
      Expression2->writeFortran(rOutFile, nMode);
    }

    rOutFile.newline();

    write(rOutFile, "END DO ");

    rOutFile.newline();
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppIterationStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppForInitStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppForInitStatement::AdtCppForInitStatement(AdtParser* pExpressionStatementObj,
                                               AdtParser* pSimpleDeclarationObj)
 : AdtCppBase()
{
  initObject(ExpressionStatement, pExpressionStatementObj,  AdtCppExpressionStatement, false);
  initObject(SimpleDeclaration,   pSimpleDeclarationObj,    AdtCppSimpleDeclaration,   false);

  if (SimpleDeclaration != 0)
  {
    ::printf("ERROR: For statement intialiser on line %d in file %s contains a "
             "variable declaration which does not translate to fortran. Please "
             "move the declaration to the outermost functional scope.\n",
             SimpleDeclaration->lineNumber(),
             SimpleDeclaration->fileName());

    ::AdtExit(-1);
  }
}

//  ----------------------------------------------------------------------------

AdtCppForInitStatement::AdtCppForInitStatement(const AdtCppForInitStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ExpressionStatement, rCopy, AdtCppExpressionStatement);
  copyObject(SimpleDeclaration,   rCopy, AdtCppSimpleDeclaration);
}

//  ----------------------------------------------------------------------------

AdtCppForInitStatement::~AdtCppForInitStatement()
{
  UtlReleaseReference(ExpressionStatement);
  UtlReleaseReference(SimpleDeclaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppForInitStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ExpressionStatement != 0)
  {
    ExpressionStatement->writeCPP(rOutFile, nMode);
  }

  if (SimpleDeclaration != 0)
  {
    SimpleDeclaration->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppForInitStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ExpressionStatement != 0)
  {
    ExpressionStatement->writeFortran(rOutFile, nMode);
  }

  if (SimpleDeclaration != 0)
  {
    SimpleDeclaration->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppForInitStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppJumpStatement mehod implementations
//  ----------------------------------------------------------------------------
AdtCppJumpStatement::AdtCppJumpStatement(AdtParser* pExpressionObj,
                                         const char* pIndentifier,
                                         AdtCppJumpType nType,
                                         const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIndentifier);
  initObject(Expression, pExpressionObj, AdtCppExpression, false);

  Type = nType;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppJumpStatement::AdtCppJumpStatement(const AdtCppJumpStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Expression, rCopy, AdtCppExpression);

  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtCppJumpStatement::~AdtCppJumpStatement()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppJumpStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  switch (Type)
  {
    case AdtCppJumpType_BREAK:
    {
      write(rOutFile, "break");
      break;
    }

    case AdtCppJumpType_CONTINUE:
    {
      write(rOutFile, "continue");
      break;
    }

    case AdtCppJumpType_RETURN:
    {
      write(rOutFile, "return");

      if (Expression != 0)
      {
        write(rOutFile, " ");
        Expression->writeCPP(rOutFile, nMode);
      }
      break;
    }

    case AdtCppJumpType_GOTO:
    {
      write(rOutFile, "goto ");
      write(rOutFile, name());
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  write(rOutFile, ";");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppJumpStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  switch (Type)
  {
    case AdtCppJumpType_BREAK:
    {
      write(rOutFile, "EXIT");
      break;
    }

    case AdtCppJumpType_CONTINUE:
    {
      write(rOutFile, "CYCLE");
      break;
    }

    case AdtCppJumpType_RETURN:
    {
      if (Expression != 0)
      {
        const AdtCppFunctionDefinition* pFunctionDefinition = (const AdtCppFunctionDefinition*)findAscendantWithClass("AdtCppFunctionDefinition");

        if (pFunctionDefinition != 0)
        {
          string sFunctionName;

          nameToFortran(pFunctionDefinition->name(), sFunctionName);

          write(rOutFile, sFunctionName);
          write(rOutFile, " = ");

          Expression->writeFortran(rOutFile, nMode);

          rOutFile.newline();

          write(rOutFile, "RETURN ");
        }
        else
        {
          write(rOutFile, "RETURN");
        }
      }
      else
      {
        write(rOutFile, "RETURN");
      }
      break;
    }

    case AdtCppJumpType_GOTO:
    {
      write(rOutFile, "GO TO ");
      write(rOutFile, name());
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppJumpStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationStatement method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclarationStatement::AdtCppDeclarationStatement(AdtParser* pBlockDeclarationObj)
 : AdtCppBase()
{
  initObject(BlockDeclaration, pBlockDeclarationObj, AdtCppBlockDeclaration, false);
}

//  ----------------------------------------------------------------------------

AdtCppDeclarationStatement::AdtCppDeclarationStatement(const AdtCppDeclarationStatement& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(BlockDeclaration, rCopy, AdtCppBlockDeclaration);
}

//  ----------------------------------------------------------------------------

AdtCppDeclarationStatement::~AdtCppDeclarationStatement()
{
  UtlReleaseReference(BlockDeclaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarationStatement::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (BlockDeclaration != 0)
  {
    BlockDeclaration->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarationStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (BlockDeclaration != 0)
  {
    BlockDeclaration->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclarationStatement, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclaration method implementations
//  ----------------------------------------------------------------------------
bool    AdtCppDeclaration::Print          = false;
bool    AdtCppDeclaration::WriteFlatFile  = false;
string  AdtCppDeclaration::LastFileName;

//  ----------------------------------------------------------------------------

AdtCppDeclaration::AdtCppDeclaration(AdtParser* pBlockDeclarationObj,
                                     AdtParser* pFunctionDefinitionObj,
                                     AdtParser* pLinkageSpecificationObj,
                                     AdtParser* pNamespaceDefinitionObj,
                                     const char* pComment)
 : AdtCppBase()
{
  initObject(BlockDeclaration,      pBlockDeclarationObj,     AdtCppBlockDeclaration,     false);
  initObject(FunctionDefinition,    pFunctionDefinitionObj,   AdtCppFunctionDefinition,   false);
  initObject(LinkageSpecification,  pLinkageSpecificationObj, AdtCppLinkageSpecification, false);
  initObject(NamespaceDefinition,   pNamespaceDefinitionObj,  AdtCppNamespaceDefinition,  false);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppDeclaration::AdtCppDeclaration(const AdtCppDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(BlockDeclaration,      rCopy, AdtCppBlockDeclaration);
  copyObject(FunctionDefinition,    rCopy, AdtCppFunctionDefinition);
  copyObject(LinkageSpecification,  rCopy, AdtCppLinkageSpecification);
  copyObject(NamespaceDefinition,   rCopy, AdtCppNamespaceDefinition);
;
}

//  ----------------------------------------------------------------------------

AdtCppDeclaration::~AdtCppDeclaration()
{
  UtlReleaseReference(BlockDeclaration);
  UtlReleaseReference(FunctionDefinition);
  UtlReleaseReference(LinkageSpecification);
  UtlReleaseReference(NamespaceDefinition);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if ((fileName() != 0) && (LastFileName != fileName()))
  {
    LastFileName = fileName();

    UtlFilePath Path(LastFileName);

    Print = (Path.extension() != ".hpp") || WriteFlatFile;

    if (!Print)
    {
      rOutFile.newline();
      rOutFile.newline();
      write(rOutFile, "#include \"");
      write(rOutFile, LastFileName);
      write(rOutFile, "\"");
      rOutFile.newline();
      rOutFile.newline();
    }
  }

  if (Print)
  {
    writeExpanded(rOutFile, comment());

    if (BlockDeclaration != 0)
    {
      BlockDeclaration->writeCPP(rOutFile, nMode);
    }

    if (FunctionDefinition != 0)
    {
      FunctionDefinition->writeCPP(rOutFile, nMode);
    }

    if (LinkageSpecification != 0)
    {
      LinkageSpecification->writeCPP(rOutFile, nMode);
    }

    if (NamespaceDefinition != 0)
    {
      NamespaceDefinition->writeCPP(rOutFile, nMode);
    }

    if ((BlockDeclaration     == 0) &&
        (FunctionDefinition   == 0) &&
        (LinkageSpecification == 0) &&
        (NamespaceDefinition  == 0))
    {
      write(rOutFile, ";");
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (BlockDeclaration != 0)
  {
    BlockDeclaration->writeFortran(rOutFile, nMode);
  }

  if (FunctionDefinition != 0)
  {
    FunctionDefinition->writeFortran(rOutFile, nMode);
  }

  if (LinkageSpecification != 0)
  {
    LinkageSpecification->writeFortran(rOutFile, nMode);
  }

  if (NamespaceDefinition != 0)
  {
    NamespaceDefinition->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppBlockDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtCppBlockDeclaration::AdtCppBlockDeclaration(AdtParser* pSimpleDeclarationObj,
                                               AdtParser* pAsmDefinitionObj,
                                               AdtParser* pNamespaceAliasDefinitionObj,
                                               AdtParser* pUsingDeclarationObj,
                                               AdtParser* pUsingDirectiveObj)
 : AdtCppBase()
{
  initObject(SimpleDeclaration,         pSimpleDeclarationObj,        AdtCppSimpleDeclaration,        false);
  initObject(AsmDefinition,             pAsmDefinitionObj,            AdtCppAsmDefinition,            false);
  initObject(NamespaceAliasDefinition,  pNamespaceAliasDefinitionObj, AdtCppNamespaceAliasDefinition, false);
  initObject(UsingDeclaration,          pUsingDeclarationObj,         AdtCppUsingDeclaration,         false);
  initObject(UsingDirective,            pUsingDirectiveObj,           AdtCppUsingDirective,           false);
}

//  ----------------------------------------------------------------------------

AdtCppBlockDeclaration::AdtCppBlockDeclaration(const AdtCppBlockDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(SimpleDeclaration,         rCopy, AdtCppSimpleDeclaration);
  copyObject(AsmDefinition,             rCopy, AdtCppAsmDefinition);
  copyObject(NamespaceAliasDefinition,  rCopy, AdtCppNamespaceAliasDefinition);
  copyObject(UsingDeclaration,          rCopy, AdtCppUsingDeclaration);
  copyObject(UsingDirective,            rCopy, AdtCppUsingDirective);
}

//  ----------------------------------------------------------------------------

AdtCppBlockDeclaration::~AdtCppBlockDeclaration()
{
  UtlReleaseReference(SimpleDeclaration);
  UtlReleaseReference(AsmDefinition);
  UtlReleaseReference(NamespaceAliasDefinition);
  UtlReleaseReference(UsingDeclaration);
  UtlReleaseReference(UsingDirective);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBlockDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (SimpleDeclaration != 0)
  {
    SimpleDeclaration->writeCPP(rOutFile, nMode);
  }

  if (AsmDefinition != 0)
  {
    AsmDefinition->writeCPP(rOutFile, nMode);
  }

  if (NamespaceAliasDefinition != 0)
  {
    NamespaceAliasDefinition->writeCPP(rOutFile, nMode);
  }

  if (UsingDeclaration != 0)
  {
    UsingDeclaration->writeCPP(rOutFile, nMode);
  }

  if (UsingDirective != 0)
  {
    UsingDirective->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBlockDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (SimpleDeclaration != 0)
  {
    SimpleDeclaration->writeFortran(rOutFile, nMode);
  }

  if (AsmDefinition != 0)
  {
    AsmDefinition->writeFortran(rOutFile, nMode);
  }

  if (NamespaceAliasDefinition != 0)
  {
    NamespaceAliasDefinition->writeFortran(rOutFile, nMode);
  }

  if (UsingDeclaration != 0)
  {
    UsingDeclaration->writeFortran(rOutFile, nMode);
  }

  if (UsingDirective != 0)
  {
    UsingDirective->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppBlockDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppSimpleDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtCppSimpleDeclaration::AdtCppSimpleDeclaration(AdtParser* pClassSpecifierObj,
                                                 AdtParser* pEnumSpecifierObj,
                                                 AdtParser* pSimpleTypeSpecifierObj,
                                                 AdtParser* pInitDeclaratorListObj,
                                                 AdtParser* pDeclModifierListObj,
                                                 bool bHasTypeDef,
                                                 const char* pComment)
 : AdtCppBase()
{
  initObject(ClassSpecifier,      pClassSpecifierObj,       AdtCppClassSpecifier,       false);
  initObject(EnumSpecifier,       pEnumSpecifierObj,        AdtCppEnumSpecifier,        false);
  initObject(SimpleTypeSpecifier, pSimpleTypeSpecifierObj,  AdtCppSimpleTypeSpecifier,  false);
  initObject(InitDeclaratorList,  pInitDeclaratorListObj,   AdtCppInitDeclaratorList,   false);
  initObject(DeclModifierList,    pDeclModifierListObj,     AdtCppDeclModifierList,     false);

  HasTypeDef = bHasTypeDef;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppSimpleDeclaration::AdtCppSimpleDeclaration(const AdtCppSimpleDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ClassSpecifier,      rCopy, AdtCppClassSpecifier);
  copyObject(EnumSpecifier,       rCopy, AdtCppEnumSpecifier);
  copyObject(SimpleTypeSpecifier, rCopy, AdtCppSimpleTypeSpecifier);
  copyObject(InitDeclaratorList,  rCopy, AdtCppInitDeclaratorList);
  copyObject(DeclModifierList,    rCopy, AdtCppDeclModifierList);

  HasTypeDef = rCopy.HasTypeDef;
}

//  ----------------------------------------------------------------------------

AdtCppSimpleDeclaration::~AdtCppSimpleDeclaration()
{
  UtlReleaseReference(ClassSpecifier);
  UtlReleaseReference(EnumSpecifier);
  UtlReleaseReference(SimpleTypeSpecifier);
  UtlReleaseReference(InitDeclaratorList);
  UtlReleaseReference(DeclModifierList);
}

//  ----------------------------------------------------------------------------

bool AdtCppSimpleDeclaration::isTypeDef(const char** ppAliasName) const
{
  bool        bIsTypeDef  = false;
  const char* pIdentifier = 0;

  if (HasTypeDef                  &&
      (SimpleTypeSpecifier  != 0) &&
      (InitDeclaratorList   != 0) &&
       InitDeclaratorList->isSimpleDeclaration(&pIdentifier))
  {
    if (ppAliasName != 0)
    {
      *ppAliasName = pIdentifier;
    }

    bIsTypeDef = true;
  }

  return (bIsTypeDef);
}

//  ----------------------------------------------------------------------------

void AdtCppSimpleDeclaration::writeFortranDeclaration(AdtFile& rOutFile, const AdtCppDeclarator* pDeclarator) const
{
  if ((pDeclarator != 0) && (SimpleTypeSpecifier != 0))
  {
    SimpleTypeSpecifier->writeFortran(rOutFile, WRITE_MODE_TYPEDECLS);
    pDeclarator->writeFortran(rOutFile, 0);
    SimpleTypeSpecifier->writeArrayBounds(rOutFile, pDeclarator);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (ClassSpecifier != 0)
  {
    ClassSpecifier->writeCPP(rOutFile, nMode);
  }

  if (EnumSpecifier != 0)
  {
    EnumSpecifier->writeCPP(rOutFile, nMode);
  }

  if (HasTypeDef)
  {
    write(rOutFile, "typedef ");
  }

  if (DeclModifierList != 0)
  {
    DeclModifierList->writeCPP(rOutFile, nMode);
  }

  if (SimpleTypeSpecifier != 0)
  {
    SimpleTypeSpecifier->writeCPP(rOutFile, nMode);
  }

  if (InitDeclaratorList != 0)
  {
    InitDeclaratorList->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, ";");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ClassSpecifier != 0)
  {
    ClassSpecifier->writeFortran(rOutFile, nMode);
  }

  if (EnumSpecifier != 0)
  {
    EnumSpecifier->writeFortran(rOutFile, nMode);
  }

  if (HasTypeDef)
  {
    ::printf("ERROR: typedefs not supported in translation to Fortran on "
             "line %d in file %s\n", lineNumber(),
                                     fileName());
    AdtExit(-1);
  }

  if (DeclModifierList != 0)
  {
    DeclModifierList->writeFortran(rOutFile, nMode);
  }

  if (SimpleTypeSpecifier != 0)
  {
    SimpleTypeSpecifier->writeFortran(rOutFile, nMode);
  }

  if (InitDeclaratorList != 0)
  {
    InitDeclaratorList->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppSimpleDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclModifier method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclModifier::AdtCppDeclModifier(AdtCppDeclModifierType nType, const char* pComment)
 : AdtCppBase()
{
  Type = nType;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppDeclModifier::AdtCppDeclModifier(const AdtCppDeclModifier& rCopy)
 : AdtCppBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtCppDeclModifier::~AdtCppDeclModifier()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclModifier::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  switch (Type)
  {
    case AdtCppDeclModifierType_AUTO:
    {
      write(rOutFile, "auto ");
      break;
    }

    case AdtCppDeclModifierType_REGISTER:
    {
      write(rOutFile, "register ");
      break;
    }

    case AdtCppDeclModifierType_STATIC:
    {
      write(rOutFile, "static ");
      break;
    }

    case AdtCppDeclModifierType_EXTERN:
    {
      write(rOutFile, "extern ");
      break;
    }

    case AdtCppDeclModifierType_MUTABLE:
    {
      write(rOutFile, "mutable ");
      break;
    }

    case AdtCppDeclModifierType_INLINE:
    {
      write(rOutFile, "inline ");
      break;
    }

    case AdtCppDeclModifierType_VIRTUAL:
    {
      write(rOutFile, "virtual ");
      break;
    }

    case AdtCppDeclModifierType_EXPLICIT:
    {
      write(rOutFile, "explicit ");
      break;
    }

    case AdtCppDeclModifierType_CONST:
    {
      write(rOutFile, "const ");
      break;
    }

    case AdtCppDeclModifierType_VOLATILE:
    {
      write(rOutFile, "volatile ");
      break;
    }

    case AdtCppDeclModifierType_FRIEND:
    {
      write(rOutFile, "friend ");
      break;
    }

    default:
    {
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclModifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  switch (Type)
  {
    case AdtCppDeclModifierType_AUTO:
    {
      write(rOutFile, "AUTOMATIC ");
      break;
    }

    case AdtCppDeclModifierType_REGISTER:
    {
      break;
    }

    case AdtCppDeclModifierType_STATIC:
    {
      write(rOutFile, "STATIC ");
      break;
    }

    case AdtCppDeclModifierType_EXTERN:
    {
      write(rOutFile, "EXTERNAL ");
      break;
    }

    case AdtCppDeclModifierType_MUTABLE:
    {
      break;
    }

    case AdtCppDeclModifierType_INLINE:
    {
      break;
    }

    case AdtCppDeclModifierType_VIRTUAL:
    {
      break;
    }

    case AdtCppDeclModifierType_EXPLICIT:
    {
      break;
    }

    case AdtCppDeclModifierType_CONST:
    {
      break;
    }

    case AdtCppDeclModifierType_VOLATILE:
    {
      write(rOutFile, "VOLATILE ");
      break;
    }

    case AdtCppDeclModifierType_FRIEND:
    {
      break;
    }

    default:
    {
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclModifier, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclModifierList method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclModifierList::AdtCppDeclModifierList(AdtParser* pDeclModifierObj)
 : AdtCppBase()
{
  add(pDeclModifierObj);
}

//  ----------------------------------------------------------------------------

AdtCppDeclModifierList::AdtCppDeclModifierList(const AdtCppDeclModifierList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppDeclModifierList::~AdtCppDeclModifierList()
{

}

//  ----------------------------------------------------------------------------

AdtAutoDir AdtCppDeclModifierList::autoDir(AdtAutoDir nDir) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    AdtCppDeclModifier* pObj = (AdtCppDeclModifier*)(AdtParser*)*Iter;

    if (pObj != 0)
    {
      nDir = pObj->autoDir(nDir);
    }
  }

  return (nDir);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclModifierList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, "", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclModifierList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, "", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclModifierList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppClassSpecifier method implementations
//  ----------------------------------------------------------------------------
bool AdtCppClassSpecifier::importParentClasses(AdtCppClassSpecifier* pDestClass,
                                               AdtCppTranslationUnit* pRoot,
                                               AdtIntByStringMap& rImportMap,
                                               const AdtParserPtrList& rRootList,
                                               string& rUsesList)
{
  bool bImported = false;

  if ((BaseSpecifierList  != 0) &&
      (pDestClass         != 0) &&
      (pRoot              != 0))
  {
    AdtParserPtrListConstIter Iter;
    AdtCppClassSpecifier*     pImportClass = 0;

    for (Iter = BaseSpecifierList->objList().begin() ; Iter != BaseSpecifierList->objList().end() ; ++Iter)
    {
      const AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        // Look for class definition in pRoot
        string                      rParentClassName;
        const AdtCppBaseSpecifier*  pBaseSpecifier  = (const AdtCppBaseSpecifier*)pObj;
        const string&               rClassName      = pBaseSpecifier->name();

        pImportClass = pRoot->findClass(rClassName, rParentClassName);

        if (pImportClass == 0)
        {
          // Look for class definition in rRootList
          AdtParserPtrListConstIter RootIter;

          for (RootIter = rRootList.begin() ; RootIter != rRootList.end() ; ++RootIter)
          {
            const AdtParser*  pRootObj = *RootIter;

            if ((pRootObj != 0) && pRootObj->isType("AdtCppTranslationUnit"))
            {
              AdtCppTranslationUnit*  pTranslationUnit = (AdtCppTranslationUnit*)pRootObj;

              pImportClass = pTranslationUnit->findClass(rClassName, rParentClassName);
              break;
            }
          }
        }

        if (pImportClass != 0)
        {
          AdtStringList ImportDefinitionList;

          // Import class into pDestClass
          if (pImportClass->MemberSpecification != 0)
          {
            if (pDestClass->MemberSpecification == 0)
            {
              copyObjectExplicit(pDestClass, MemberSpecification, *pImportClass, AdtCppMemberSpecification);
            }
            else
            {
              AdtParserPtrListConstIter DeclIter;

              for (DeclIter = pImportClass->MemberSpecification->objList().begin() ; DeclIter != pImportClass->MemberSpecification->objList().end() ; ++DeclIter)
              {
                AdtParser*  pDeclObj = *DeclIter;

                if ((pDeclObj != 0) && pDeclObj->isType("AdtCppMemberDeclaration"))
                {
                  AdtCppMemberDeclaration*  pMemberDeclaration = (AdtCppMemberDeclaration*)pDeclObj;

                  if (pMemberDeclaration->shouldImport(rImportMap))
                  {
                    AdtCppMemberDeclaration*  pMemberDeclarationCopy = (AdtCppMemberDeclaration*)pMemberDeclaration->copy();

                    pMemberDeclarationCopy->updateScope(pBaseSpecifier);
                    pMemberDeclarationCopy->checkLookForDefinition(ImportDefinitionList);
                    pDestClass->MemberSpecification->add(pMemberDeclarationCopy);
                    UtlReleaseReference(pMemberDeclarationCopy);
                  }
                }
              }
            }
          }

          // Import associated method implementations and static var defs into
          // the appropriate scope in pRoot.
          AdtStringListIter DefNameIter;
          string            rFunctionBaseName;

          for (DefNameIter = ImportDefinitionList.begin() ; DefNameIter != ImportDefinitionList.end() ; ++DefNameIter)
          {
            string                    sQualifiedDefName   = pImportClass->qualifiedName() + "::" + *DefNameIter;
            AdtCppFunctionDefinition* pFunctionDefinition = 0;

            // Search for implementation of the function in all sources.
            pFunctionDefinition = pRoot->findFunction(sQualifiedDefName, rFunctionBaseName);

            if (pFunctionDefinition == 0)
            {
              // Look for class definition in rRootList
              AdtParserPtrListConstIter RootIter;

              for (RootIter = rRootList.begin() ; RootIter != rRootList.end() ; ++RootIter)
              {
                const AdtParser*  pRootObj = *RootIter;

                if ((pRootObj != 0) && pRootObj->isType("AdtCppTranslationUnit"))
                {
                  AdtCppTranslationUnit*  pTranslationUnit = (AdtCppTranslationUnit*)pRootObj;

                  pFunctionDefinition = pTranslationUnit->findFunction(sQualifiedDefName, rFunctionBaseName);
                  break;
                }
              }
            }

            if (pFunctionDefinition != 0)
            {
              // Definition found. Add copy and replace class qualifier with
              // flattened class name.
              AdtCppFunctionDefinition* pFunctionDefinitionCopy = (AdtCppFunctionDefinition*)pFunctionDefinition->copy();

              if (pFunctionDefinitionCopy != 0)
              {
                string      rSrcClassName;
                const char* pFunctionBaseName = rFunctionBaseName;
                const char* pDestClassName    = pDestClass->qualifiedName();

                AdtCppScopeManager::nestedNameSpecifier(rSrcClassName, pFunctionBaseName);
                pFunctionDefinitionCopy->replaceScopeName(rSrcClassName, pDestClassName);
                pRoot->addFunction(pFunctionDefinitionCopy);
                UtlReleaseReference(pFunctionDefinitionCopy);
              }
            }
          }

          // Recurse the import process
          pImportClass->importParentClasses(pDestClass,
                                            pRoot,
                                            rImportMap,
                                            rRootList,
                                            rUsesList);

          bImported = true;
        }
      }
    }
  }

  return (bImported);
}

//  ----------------------------------------------------------------------------

void AdtCppClassSpecifier::expandOutInlineImplementations(AdtCppTranslationUnit* pRoot)
{
  if (MemberSpecification != 0)
  {
    // Re initialise MemberSpecification so that the maps are up to date
    MemberSpecification->initialise();

    if (pRoot != 0)
    {
      AdtParserPtrListConstIter DeclIter;

      // Convert inline function to out of line implementation in pRoot
      for (DeclIter = MemberSpecification->objList().begin() ; DeclIter != MemberSpecification->objList().end() ; ++DeclIter)
      {
        AdtParser*  pDeclObj = *DeclIter;

        if ((pDeclObj != 0) && pDeclObj->isType("AdtCppMemberDeclaration"))
        {
          AdtCppMemberDeclaration*  pMemberDeclaration = (AdtCppMemberDeclaration*)pDeclObj;

          pMemberDeclaration->exportFunctionImplementation(pRoot);
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppClassSpecifier::AdtCppClassSpecifier(AdtParser* pClassKeyObj,
                                           AdtParser* pBaseSpecifierListObj,
                                           AdtParser* pMemberSpecificationObj,
                                           bool bWithBrackets)
 : AdtCppCheckDeclaration()
{
  initObject(ClassKey,            pClassKeyObj,             AdtCppClassKey,             false);
  initObject(BaseSpecifierList,   pBaseSpecifierListObj,    AdtCppBaseSpecifierList,    false);
  initObject(MemberSpecification, pMemberSpecificationObj,  AdtCppMemberSpecification,  false);

  WithBrackets = bWithBrackets;

  if (WithBrackets && (ClassKey != 0))
  {
    name(ClassKey->name());
    initialiseQualifiedName();
  }

  if (MemberSpecification != 0)
  {
    MemberSpecification->initialise();
  }
}

//  ----------------------------------------------------------------------------

AdtCppClassSpecifier::AdtCppClassSpecifier(const AdtCppClassSpecifier& rCopy)
 : AdtCppCheckDeclaration(rCopy)
{
  copyObject(ClassKey,            rCopy, AdtCppClassKey);
  copyObject(BaseSpecifierList,   rCopy, AdtCppBaseSpecifierList);
  copyObject(MemberSpecification, rCopy, AdtCppMemberSpecification);

  WithBrackets = rCopy.WithBrackets;

  if (MemberSpecification != 0)
  {
    MemberSpecification->initialise();
  }
}

//  ----------------------------------------------------------------------------

AdtCppClassSpecifier::~AdtCppClassSpecifier()
{
  UtlReleaseReference(ClassKey);
  UtlReleaseReference(BaseSpecifierList);
  UtlReleaseReference(MemberSpecification);
}

//  ----------------------------------------------------------------------------

bool AdtCppClassSpecifier::isForwardDeclaration(bool bClassScope) const
{
  bool bIsForwardDeclaration = !WithBrackets;

  return (bIsForwardDeclaration);
}

//  ----------------------------------------------------------------------------

bool AdtCppClassSpecifier::isEmpty() const
{
  bool bIsEmpty = ((BaseSpecifierList == 0) && (MemberSpecification == 0));

  return (bIsEmpty);
}

//  ----------------------------------------------------------------------------

bool AdtCppClassSpecifier::flattenClass(AdtCppTranslationUnit* pRoot,
                                        const AdtParserPtrList& rRootList,
                                        string& rUsesList)
{
  AdtIntByStringMap ImportMap;

  // Include all inherited code into this class and remove the BaseSpecifierList
  bool bFlattened = importParentClasses(this, pRoot, ImportMap, rRootList, rUsesList);

  // Take embedded class method implementations and expand them out of class (get rid of inline implementations).
  expandOutInlineImplementations(pRoot);

  UtlReleaseReference(BaseSpecifierList);

  BaseSpecifierList = 0;

  return (bFlattened);
}

//  ----------------------------------------------------------------------------

void AdtCppClassSpecifier::findDimensionVars(const AdtCppTranslationUnit* pRoot,
                                             const AdtParserPtrByStringMap& rVarsMap,
                                             AdtParserPtrList& rList) const
{
  AdtStringByStringMap              DefinedMap;
  AdtParserPtrByStringMapConstIter  Iter;

  // Make map of object names as a check for whether they are already mapped
  for (Iter = rVarsMap.begin() ; Iter != rVarsMap.end() ; ++Iter)
  {
    const AdtParser* pObj = Iter->second;

    if ((pObj != 0) && pObj->isType("AdtCppDeclarator"))
    {
      AdtCppDeclarator* pDeclarator;

      pDeclarator                     = (AdtCppDeclarator*)pObj;
      DefinedMap[pDeclarator->name()] = pDeclarator->name();
    }
  }

  // For all the mapped variables check for dimension specs and add dim vars
  for (Iter = rVarsMap.begin() ; Iter != rVarsMap.end() ; ++Iter)
  {
    const AdtParser* pObj = Iter->second;

    if ((pObj != 0) && pObj->isType("AdtCppDeclarator"))
    {
      AdtStringListIter StrIter;
      AdtStringList     rArrayBoundList;
      AdtCppDeclarator* pDeclarator = (AdtCppDeclarator*)pObj;

      pDeclarator->enumerateArraySizes(rArrayBoundList, rArrayBoundList);

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

          if ((DefinedMap.find(rDepName) == DefinedMap.end()) && findField(pRoot, rDepName, pDepObj))
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

bool AdtCppClassSpecifier::findField(const AdtCppTranslationUnit* pRoot,
                                     const char* pName,
                                     const AdtParser*& pObj) const
{
  bool bFound = false;

  if (!isEmpty())
  {
    // Search locally for the field.
    if (MemberSpecification != 0)
    {
      bFound = MemberSpecification->findVarDefinition(pName, pObj);
    }

    // If not found look into parent class
    if (!bFound                   &&
        (BaseSpecifierList  != 0) &&
        (pRoot              != 0))
    {
      AdtParserPtrListConstIter Iter;
      AdtCppClassSpecifier*     pClass = 0;

      for (Iter = BaseSpecifierList->objList().begin() ; Iter != BaseSpecifierList->objList().end() ; ++Iter)
      {
        const AdtParser*  pBaseSpecifierObj = *Iter;

        if (pBaseSpecifierObj != 0)
        {
          // Look for class definition in pRoot
          string                      rParentClassName;
          const AdtCppBaseSpecifier*  pBaseSpecifier  = (const AdtCppBaseSpecifier*)pBaseSpecifierObj;
          const string&               rClassName      = pBaseSpecifier->name();

          pClass = pRoot->findClass(rClassName, rParentClassName);

          if ((pClass != 0) && pClass->findField(pRoot, pName, pObj))
          {
            bFound = true;
            break;
          }
        }
      }
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtCppClassSpecifier::findMethod(const AdtCppTranslationUnit* pRoot,
                                      const char* pName,
                                      const AdtParser*& pObj) const
{
  bool bFound = false;

  if (!isEmpty())
  {
    // Search locally for the method.
    if (MemberSpecification != 0)
    {
      bFound = MemberSpecification->findFunctionDefinition(pName, pObj);
    }

    // If not found look into parent class
    if (!bFound                   &&
        (BaseSpecifierList  != 0) &&
        (pRoot              != 0))
    {
      AdtParserPtrListConstIter Iter;
      AdtCppClassSpecifier*     pClass = 0;

      for (Iter = BaseSpecifierList->objList().begin() ; Iter != BaseSpecifierList->objList().end() ; ++Iter)
      {
        const AdtParser*  pBaseSpecifierObj = *Iter;

        if (pBaseSpecifierObj != 0)
        {
          // Look for class definition in pRoot
          string                      rParentClassName;
          const AdtCppBaseSpecifier*  pBaseSpecifier  = (const AdtCppBaseSpecifier*)pBaseSpecifierObj;
          const string&               rClassName      = pBaseSpecifier->name();

          pClass = pRoot->findClass(rClassName, rParentClassName);

          if ((pClass != 0) && pClass->findMethod(pRoot, pName, pObj))
          {
            bFound = true;
            break;
          }
        }
      }
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppClassSpecifier::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ClassKey != 0)
  {
    ClassKey->writeCPP(rOutFile, nMode);
  }

  if (BaseSpecifierList != 0)
  {
    write(rOutFile, " : ");

    BaseSpecifierList->writeCPP(rOutFile, nMode);
  }

  if (WithBrackets)
  {
    rOutFile.newline();

    write(rOutFile, "{");

    if (MemberSpecification != 0)
    {
      rOutFile.incrementIndent();
      rOutFile.newline();

      MemberSpecification->writeCPP(rOutFile, nMode);

      rOutFile.decrementIndent();
      rOutFile.newline();
    }

    write(rOutFile, "}");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppClassSpecifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

const char* AdtCppClassSpecifier::parentClassName() const
{
  const char* pParentClassName = "";

  if (BaseSpecifierList != 0)
  {
    AdtParserPtrListConstIter Iter = BaseSpecifierList->objList().begin();

    if (Iter != BaseSpecifierList->objList().end())
    {
      const AdtParser* pObj = *Iter;

      if (pObj != 0)
      {
        pParentClassName = pObj->name().c_str();
      }
    }
  }

  return (pParentClassName);
}

//  ----------------------------------------------------------------------------

implType(AdtCppClassSpecifier, AdtCppCheckDeclaration);


//  ----------------------------------------------------------------------------
//  AdtCppEnumSpecifierName class
//  ----------------------------------------------------------------------------
AdtCppEnumSpecifierName::AdtCppEnumSpecifierName(const char* pIdentifier, bool bQualified, const char* pComment)
 : AdtCppBase()
{
  Qualified = bQualified;

  nameWithComment(pIdentifier);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppEnumSpecifierName::AdtCppEnumSpecifierName(const AdtCppEnumSpecifierName& rCopy)
 : AdtCppBase(rCopy)
{
  Qualified = rCopy.Qualified;
}

//  ----------------------------------------------------------------------------

AdtCppEnumSpecifierName::~AdtCppEnumSpecifierName()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumSpecifierName::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "enum ");
  write(rOutFile, name());
  write(rOutFile, " ");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumSpecifierName::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: enum not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppEnumSpecifierName, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppEnumSpecifier class
//  ----------------------------------------------------------------------------
AdtCppEnumSpecifier::AdtCppEnumSpecifier(AdtParser* pEnumeratorListObj,
                                         AdtParser* pEnumSpecifierNameObj,
                                         bool bWithBrackets)
 : AdtCppCheckDeclaration()
{
  initObject(EnumeratorList,    pEnumeratorListObj,     AdtCppEnumeratorList,     false);
  initObject(EnumSpecifierName, pEnumSpecifierNameObj,  AdtCppEnumSpecifierName,  false);

  WithBrackets = bWithBrackets;

  if (pEnumSpecifierNameObj != 0)
  {
    name(pEnumSpecifierNameObj->name());
    initialiseQualifiedName();
  }
}

//  ----------------------------------------------------------------------------

AdtCppEnumSpecifier::AdtCppEnumSpecifier(const AdtCppEnumSpecifier& rCopy)
 : AdtCppCheckDeclaration(rCopy)
{
  copyObject(EnumeratorList,    rCopy, AdtCppEnumeratorList);
  copyObject(EnumSpecifierName, rCopy, AdtCppEnumSpecifierName);

  WithBrackets = rCopy.WithBrackets;
}

//  ----------------------------------------------------------------------------

AdtCppEnumSpecifier::~AdtCppEnumSpecifier()
{
  UtlReleaseReference(EnumeratorList);
  UtlReleaseReference(EnumSpecifierName);
}

//  ----------------------------------------------------------------------------

bool AdtCppEnumSpecifier::isForwardDeclaration(bool bClassScope) const
{
  bool bIsForwardDeclaration = !WithBrackets;

  return (bIsForwardDeclaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumSpecifier::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (EnumSpecifierName != 0)
  {
    EnumSpecifierName->writeCPP(rOutFile, nMode);
  }

  if (WithBrackets)
  {
    write(rOutFile, "{");

    if (EnumeratorList != 0)
    {
      rOutFile.incrementIndent();
      rOutFile.newline();

      EnumeratorList->writeCPP(rOutFile, nMode);

      rOutFile.decrementIndent();
      rOutFile.newline();
    }

    write(rOutFile, "}");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumSpecifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: enum not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppEnumSpecifier, AdtCppCheckDeclaration);


//  ----------------------------------------------------------------------------
//  AdtCppSimpleTypeSpecifier method implementations
//  ----------------------------------------------------------------------------
AdtCppSimpleTypeSpecifier::AdtCppSimpleTypeSpecifier(const char* pIdentifier,
                                                     AdtCppSimpleType nType,
                                                     bool bByRef,
                                                     const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);

  Type  = nType;
  ByRef = bByRef;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppSimpleTypeSpecifier::AdtCppSimpleTypeSpecifier(const AdtCppSimpleTypeSpecifier& rCopy)
 : AdtCppBase(rCopy)
{
  Type  = rCopy.Type;
  ByRef = rCopy.ByRef;
}

//  ----------------------------------------------------------------------------

AdtCppSimpleTypeSpecifier::~AdtCppSimpleTypeSpecifier()
{

}

//  ----------------------------------------------------------------------------

void AdtCppSimpleTypeSpecifier::writeArrayBounds(AdtFile& rOutFile,
                                                 const AdtCppEmbeddedComment* pEmbeddedComment) const
{
  if (pEmbeddedComment != 0)
  {
    switch(Type)
    {
      case AdtCppSimpleType_OBJ_IDENTIFIER:
      case AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER:
      {
        const char* sDimension  = 0;
        const char* pType       = 0;

        cppRootObject()->mapTypesToFortran(name(), pType, sDimension);

        pEmbeddedComment->writeArrayBounds(rOutFile, sDimension);
        break;
      }

      case AdtCppSimpleType_WCHAR_T:
      case AdtCppSimpleType_CHAR:
      case AdtCppSimpleType_SIGNED_CHAR:
      case AdtCppSimpleType_BOOL:
      case AdtCppSimpleType_INT:
      case AdtCppSimpleType_SIGNED:
      case AdtCppSimpleType_SIGNED_INT:
      case AdtCppSimpleType_SHORT:
      case AdtCppSimpleType_SHORT_INT:
      case AdtCppSimpleType_SIGNED_SHORT:
      case AdtCppSimpleType_SIGNED_SHORT_INT:
      case AdtCppSimpleType_LONG:
      case AdtCppSimpleType_LONG_INT:
      case AdtCppSimpleType_SIGNED_LONG:
      case AdtCppSimpleType_SIGNED_LONG_INT:
      case AdtCppSimpleType_UNSIGNED:
      case AdtCppSimpleType_UNSIGNED_INT:
      case AdtCppSimpleType_UNSIGNED_SHORT:
      case AdtCppSimpleType_UNSIGNED_SHORT_INT:
      case AdtCppSimpleType_UNSIGNED_LONG:
      case AdtCppSimpleType_UNSIGNED_LONG_INT:
      case AdtCppSimpleType_UNSIGNED_CHAR:
      case AdtCppSimpleType_FLOAT:
      case AdtCppSimpleType_DOUBLE:
      case AdtCppSimpleType_LONG_DOUBLE:
      case AdtCppSimpleType_LONG_LONG:
      case AdtCppSimpleType_SIGNED_LONG_LONG:
      case AdtCppSimpleType_UNSIGNED_LONG_LONG:
      case AdtCppSimpleType_VOID:
      {
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtAutoType AdtCppSimpleTypeSpecifier::autoType(int& nDimensions) const
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  nDimensions = 0;

  switch(Type)
  {
    case AdtCppSimpleType_OBJ_IDENTIFIER:
    case AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER:
    {
      const char* pDimension  = 0;
      const char* pType       = 0;

      if (cppRootObject()->mapTypesToFortran(name(), pType, pDimension))
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
      break;
    }

    case AdtCppSimpleType_CHAR:
    case AdtCppSimpleType_SIGNED_CHAR:
    {
      nType = AdtAutoType_CHAR;
      break;
    }

    case AdtCppSimpleType_UNSIGNED_CHAR:
    {
      nType = AdtAutoType_UNSIGNED_CHAR;
      break;
    }

    case AdtCppSimpleType_BOOL:
    {
      nType = AdtAutoType_BOOL;
      break;
    }

    case AdtCppSimpleType_INT:
    case AdtCppSimpleType_SIGNED:
    case AdtCppSimpleType_SIGNED_INT:
    {
      nType = AdtAutoType_INT;
      break;
    }

    case AdtCppSimpleType_SHORT:
    case AdtCppSimpleType_SHORT_INT:
    case AdtCppSimpleType_SIGNED_SHORT:
    case AdtCppSimpleType_SIGNED_SHORT_INT:
    {
      nType = AdtAutoType_SHORT;
      break;
    }

    case AdtCppSimpleType_LONG:
    case AdtCppSimpleType_LONG_INT:
    case AdtCppSimpleType_SIGNED_LONG:
    case AdtCppSimpleType_SIGNED_LONG_INT:
    {
      nType = AdtAutoType_LONG;
      break;
    }

    case AdtCppSimpleType_UNSIGNED:
    case AdtCppSimpleType_UNSIGNED_INT:
    {
      nType = AdtAutoType_UNSIGNED_INT;
      break;
    }

    case AdtCppSimpleType_UNSIGNED_SHORT:
    case AdtCppSimpleType_UNSIGNED_SHORT_INT:
    {
      nType = AdtAutoType_UNSIGNED_SHORT;
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG:
    case AdtCppSimpleType_UNSIGNED_LONG_INT:
    {
      nType = AdtAutoType_UNSIGNED_LONG;
      break;
    }

    case AdtCppSimpleType_FLOAT:
    {
      nType = AdtAutoType_FLOAT;
      break;
    }

    case AdtCppSimpleType_DOUBLE:
    case AdtCppSimpleType_LONG_DOUBLE:
    {
      nType = AdtAutoType_DOUBLE;
      break;
    }

    case AdtCppSimpleType_LONG_LONG:
    case AdtCppSimpleType_SIGNED_LONG_LONG:
    {
      nType = AdtAutoType_LONG_LONG;
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG_LONG:
    {
      nType = AdtAutoType_UNSIGNED_LONG_LONG;
      break;
    }

    case AdtCppSimpleType_WCHAR_T:
    case AdtCppSimpleType_VOID:
    {
      nType = AdtAutoType_UNDEFINED;
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

void AdtCppSimpleTypeSpecifier::addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                              const char* pName,
                                              bool bReturnType,
                                              const char* pFile,
                                              int nLine) const
{
  bool                bIsArray    = false;
  AdtBlackBoxArgType  nMappedType = AdtBlackBox_undefined;

  switch(Type)
  {
    case AdtCppSimpleType_OBJ_IDENTIFIER:
    case AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER:
    {
      const char* pDimension  = 0;
      const char* pType       = 0;

      if (cppRootObject()->mapTypesToFortran(name(), pType, pDimension))
      {
        AdtBlackBoxArgType  pMappedTypes[]  = {AdtBlackBox_real, AdtBlackBox_integer, AdtBlackBox_integer, AdtBlackBox_boolean};
        const char*         pTypes[]        = {"REAL", "INTEGER", "UNSIGNED", "LOGICAL"};
        int                 nWhich          = AdtParse::matchWhichWord(pType, pTypes, sizeof(pTypes) / sizeof(pTypes[0]), false);

        if (nWhich >= 0)
        {
          nMappedType = pMappedTypes[nWhich];
          bIsArray    = true;
        }
      }
      break;
    }

    case AdtCppSimpleType_BOOL:
    {
      nMappedType = AdtBlackBox_boolean;
      break;
    }

    case AdtCppSimpleType_CHAR:
    case AdtCppSimpleType_SIGNED_CHAR:
    case AdtCppSimpleType_UNSIGNED_CHAR:
    case AdtCppSimpleType_INT:
    case AdtCppSimpleType_SIGNED:
    case AdtCppSimpleType_SIGNED_INT:
    case AdtCppSimpleType_SHORT:
    case AdtCppSimpleType_SHORT_INT:
    case AdtCppSimpleType_SIGNED_SHORT:
    case AdtCppSimpleType_SIGNED_SHORT_INT:
    case AdtCppSimpleType_LONG:
    case AdtCppSimpleType_LONG_INT:
    case AdtCppSimpleType_SIGNED_LONG:
    case AdtCppSimpleType_SIGNED_LONG_INT:
    case AdtCppSimpleType_UNSIGNED:
    case AdtCppSimpleType_UNSIGNED_INT:
    case AdtCppSimpleType_UNSIGNED_SHORT:
    case AdtCppSimpleType_UNSIGNED_SHORT_INT:
    case AdtCppSimpleType_UNSIGNED_LONG:
    case AdtCppSimpleType_UNSIGNED_LONG_INT:
    case AdtCppSimpleType_LONG_LONG:
    case AdtCppSimpleType_SIGNED_LONG_LONG:
    case AdtCppSimpleType_UNSIGNED_LONG_LONG:
    {
      nMappedType = AdtBlackBox_integer;
      break;
    }

    case AdtCppSimpleType_FLOAT:
    case AdtCppSimpleType_DOUBLE:
    case AdtCppSimpleType_LONG_DOUBLE:
    {
      nMappedType = AdtBlackBox_real;
      break;
    }

    case AdtCppSimpleType_WCHAR_T:
    case AdtCppSimpleType_VOID:
    {
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  if (nMappedType == AdtBlackBox_undefined)
  {
    ::printf("ERROR: Argument types used not supported in black box definition on line %d in file %s.\n",
             nLine,
             pFile);

    AdtExit(-1);
  }

  AdtAutoDir nDir = autoDir();

  // Need to look for modifier list and change nDir in accordance to any modifiers
  if (Parent != 0)
  {
    AdtCppDeclModifierList* pDeclModifierList = (AdtCppDeclModifierList*)Parent->findDescendant("DeclModifierList");

    if (pDeclModifierList != 0)
    {
      nDir = pDeclModifierList->autoDir(nDir);
    }
  }

  if (bReturnType)
  {
    rBlackBox.addReturn(nMappedType,
                        bIsArray);
  }
  else
  {
    // Note that we can't tell the difference between OUT and INOUT parameters
    // without analysing the code. It is possible to do so but is it worth the
    // effort. Probably not so I just force it to an INOUT interpretation.
    rBlackBox.addArgument(nMappedType,
                          pName,
                          (nDir == AdtAutoDir_IN) || (nDir == AdtAutoDir_UNDEFINED),
                          false,
                          false,
                          nDir == AdtAutoDir_INOUT,
                          bIsArray);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleTypeSpecifier::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  const char* pType = 0;

  switch(Type)
  {
    case AdtCppSimpleType_OBJ_IDENTIFIER:
    case AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER:
    {
      pType = name();
      break;
    }

    case AdtCppSimpleType_WCHAR_T:
    {
      pType = "wchar_t";
      break;
    }

    case AdtCppSimpleType_CHAR:
    {
      pType = "char";
      break;
    }

    case AdtCppSimpleType_BOOL:
    {
      pType = "bool";
      break;
    }

    case AdtCppSimpleType_INT:
    {
      pType = "int";
      break;
    }

    case AdtCppSimpleType_SHORT:
    {
      pType = "short";
      break;
    }

    case AdtCppSimpleType_SHORT_INT:
    {
      pType = "short int";
      break;
    }

    case AdtCppSimpleType_LONG:
    {
      pType = "long";
      break;
    }

    case AdtCppSimpleType_LONG_INT:
    {
      pType = "long int";
      break;
    }

    case AdtCppSimpleType_SIGNED:
    {
      pType = "signed";
      break;
    }

    case AdtCppSimpleType_SIGNED_INT:
    {
      pType = "signed int";
      break;
    }

    case AdtCppSimpleType_SIGNED_SHORT:
    {
      pType = "signed short";
      break;
    }

    case AdtCppSimpleType_SIGNED_SHORT_INT:
    {
      pType = "signed short int";
      break;
    }

    case AdtCppSimpleType_SIGNED_LONG:
    {
      pType = "signed long";
      break;
    }

    case AdtCppSimpleType_SIGNED_LONG_INT:
    {
      pType = "signed long int";
      break;
    }

    case AdtCppSimpleType_SIGNED_CHAR:
    {
      pType = "signed char";
      break;
    }

    case AdtCppSimpleType_UNSIGNED:
    {
      pType = "unsigned";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_INT:
    {
      pType = "unsigned int";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_SHORT:
    {
      pType = "unsigned short";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_SHORT_INT:
    {
      pType = "unsigned short int";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG:
    {
      pType = "unsigned long";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG_INT:
    {
      pType = "unsigned long int";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_CHAR:
    {
      pType = "unsigned char";
      break;
    }

    case AdtCppSimpleType_FLOAT:
    {
      pType = "float";
      break;
    }

    case AdtCppSimpleType_DOUBLE:
    {
      pType = "double";
      break;
    }

    case AdtCppSimpleType_LONG_DOUBLE:
    {
      pType = "long double";
      break;
    }

    case AdtCppSimpleType_LONG_LONG:
    {
      pType = "long long";
      break;
    }

    case AdtCppSimpleType_SIGNED_LONG_LONG:
    {
      pType = "signed long long";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG_LONG:
    {
      pType = "unsigned long long";
      break;
    }

    case AdtCppSimpleType_VOID:
    {
      pType = "void";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  if (pType != 0)
  {
    write(rOutFile, pType);

    if (ByRef)
    {
      write(rOutFile, "&");
    }

    write(rOutFile, " ");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppSimpleTypeSpecifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  const char* sDimension  = 0;
  const char* pType       = 0;

  switch(Type)
  {
    case AdtCppSimpleType_OBJ_IDENTIFIER:
    case AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER:
    {
      cppRootObject()->mapTypesToFortran(name(), pType, sDimension);
      break;
    }

    case AdtCppSimpleType_WCHAR_T:
    {
      pType = "INTEGER(2)";
      break;
    }

    case AdtCppSimpleType_CHAR:
    case AdtCppSimpleType_SIGNED_CHAR:
    {
      pType = "INTEGER(1)";
      break;
    }

    case AdtCppSimpleType_BOOL:
    {
      pType = "LOGICAL";
      break;
    }

    case AdtCppSimpleType_INT:
    case AdtCppSimpleType_SIGNED:
    case AdtCppSimpleType_SIGNED_INT:
    {
      pType = "INTEGER";
      break;
    }

    case AdtCppSimpleType_SHORT:
    case AdtCppSimpleType_SHORT_INT:
    case AdtCppSimpleType_SIGNED_SHORT:
    case AdtCppSimpleType_SIGNED_SHORT_INT:
    {
      pType = "INTEGER(2)";
      break;
    }

    case AdtCppSimpleType_LONG:
    case AdtCppSimpleType_LONG_INT:
    case AdtCppSimpleType_SIGNED_LONG:
    case AdtCppSimpleType_SIGNED_LONG_INT:
    {
      pType = "INTEGER(4)";
      break;
    }

    case AdtCppSimpleType_UNSIGNED:
    case AdtCppSimpleType_UNSIGNED_INT:
    {
      pType = "UNSIGNED";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_SHORT:
    case AdtCppSimpleType_UNSIGNED_SHORT_INT:
    {
      pType = "UNSIGNED(2)";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG:
    case AdtCppSimpleType_UNSIGNED_LONG_INT:
    {
      pType = "UNSIGNED(4)";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_CHAR:
    {
      pType = "UNSIGNED(1)";
      break;
    }

    case AdtCppSimpleType_FLOAT:
    case AdtCppSimpleType_DOUBLE:
    case AdtCppSimpleType_LONG_DOUBLE:
    {
      pType = "REAL(8)";
      break;
    }

    case AdtCppSimpleType_LONG_LONG:
    case AdtCppSimpleType_SIGNED_LONG_LONG:
    {
      pType = "INTEGER(8)";
      break;
    }

    case AdtCppSimpleType_UNSIGNED_LONG_LONG:
    {
      pType = "UNSIGNED(8)";
      break;
    }

    case AdtCppSimpleType_VOID:
    {
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  if (pType != 0)
  {
    write(rOutFile, pType);
    write(rOutFile, " ");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtAutoDir AdtCppSimpleTypeSpecifier::autoDir() const
{
  AdtAutoDir nDir;

  if (isInOut())
  {
    nDir = AdtAutoDir_INOUT;
  }
  else if (isVoid())
  {
    nDir = AdtAutoDir_UNDEFINED;
  }
  else
  {
    nDir = AdtAutoDir_IN;
  }

  return (nDir);
}

//  ----------------------------------------------------------------------------

implType(AdtCppSimpleTypeSpecifier, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppEnumeratorList method implementations
//  ----------------------------------------------------------------------------
AdtCppEnumeratorList::AdtCppEnumeratorList(AdtParser* pEnumeratorDefinitionObj)
 : AdtCppBase()
{
  add(pEnumeratorDefinitionObj);
}

//  ----------------------------------------------------------------------------

AdtCppEnumeratorList::AdtCppEnumeratorList(const AdtCppEnumeratorList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppEnumeratorList::~AdtCppEnumeratorList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumeratorList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumeratorList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppEnumeratorList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppEnumeratorDefinition method implementations
//  ----------------------------------------------------------------------------
AdtCppEnumeratorDefinition::AdtCppEnumeratorDefinition(AdtParser* pConstantExpressionObj,
                                                       const char* pIdentifier,
                                                       const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);
  initObject(ConstantExpression, pConstantExpressionObj, AdtCppConstantExpression, false);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppEnumeratorDefinition::AdtCppEnumeratorDefinition(const AdtCppEnumeratorDefinition& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ConstantExpression, rCopy, AdtCppConstantExpression);
}

//  ----------------------------------------------------------------------------

AdtCppEnumeratorDefinition::~AdtCppEnumeratorDefinition()
{
  UtlReleaseReference(ConstantExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumeratorDefinition::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, name());

  if (ConstantExpression != 0)
  {
    write(rOutFile, " = ");

    ConstantExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppEnumeratorDefinition::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: enum not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppEnumeratorDefinition, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppNamespaceDefinition method implementations
//  ----------------------------------------------------------------------------
AdtCppNamespaceDefinition::AdtCppNamespaceDefinition(AdtParser* pDeclarationSeqObj,
                                                     const char* pIdentifier,
                                                     const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);
  initObject(DeclarationSeq, pDeclarationSeqObj, AdtCppDeclarationSeq, false);

  if (DeclarationSeq != 0)
  {
    DeclarationSeq->initialise();
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppNamespaceDefinition::AdtCppNamespaceDefinition(const AdtCppNamespaceDefinition& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(DeclarationSeq, rCopy, AdtCppDeclarationSeq);

  if (DeclarationSeq != 0)
  {
    DeclarationSeq->initialise();
  }
}

//  ----------------------------------------------------------------------------

AdtCppNamespaceDefinition::~AdtCppNamespaceDefinition()
{
  UtlReleaseReference(DeclarationSeq);
}

//  ----------------------------------------------------------------------------

AdtCppDeclarationSeq* AdtCppNamespaceDefinition::declarationSeq() const
{
  AdtCppDeclarationSeq* pDeclarationSeq = (AdtCppDeclarationSeq*)findDescendant("DeclarationSeq");

  return (pDeclarationSeq);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppNamespaceDefinition::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "namespace ");
  write(rOutFile, name());
  write(rOutFile, "{");

  if (DeclarationSeq != 0)
  {
    DeclarationSeq->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, "}");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppNamespaceDefinition::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: namespace not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppNamespaceDefinition, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppNamespaceAliasDefinition method implementations
//  ----------------------------------------------------------------------------
AdtCppNamespaceAliasDefinition::AdtCppNamespaceAliasDefinition(const char* pIdentifier,
                                                               const char* pQualifiedIdentifier,
                                                               const char* pComment)
 : AdtCppBase(),
   QualifiedIdentifier()
{
  nameWithComment(pIdentifier);

  if (pQualifiedIdentifier != 0)
  {
    QualifiedIdentifier = pQualifiedIdentifier;
  }

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppNamespaceAliasDefinition::AdtCppNamespaceAliasDefinition(const AdtCppNamespaceAliasDefinition& rCopy)
 : AdtCppBase(rCopy),
   QualifiedIdentifier(rCopy.QualifiedIdentifier)
{

}

//  ----------------------------------------------------------------------------

AdtCppNamespaceAliasDefinition::~AdtCppNamespaceAliasDefinition()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppNamespaceAliasDefinition::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "namespace ");
  write(rOutFile, name());
  write(rOutFile, " = ");
  write(rOutFile, QualifiedIdentifier);
  write(rOutFile, "; ");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppNamespaceAliasDefinition::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: namespace alias not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppNamespaceAliasDefinition, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppUsingDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtCppUsingDeclaration::AdtCppUsingDeclaration(const char* pQualifiedIdentifier,
                                               bool bWithTypename,
                                               const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pQualifiedIdentifier);

  WithTypename = bWithTypename;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppUsingDeclaration::AdtCppUsingDeclaration(const AdtCppUsingDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  WithTypename = rCopy.WithTypename;
}

//  ----------------------------------------------------------------------------

AdtCppUsingDeclaration::~AdtCppUsingDeclaration()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUsingDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (WithTypename)
  {
    write(rOutFile, "using typename ");
  }
  else
  {
    write(rOutFile, "using ");
  }

  write(rOutFile, name());
  write(rOutFile, ";");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUsingDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: using not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppUsingDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppUsingDirective method implementations
//  ----------------------------------------------------------------------------
AdtCppUsingDirective::AdtCppUsingDirective(const char* pIdentifier,
                                           bool bQualified,
                                           const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);

  Qualified = bQualified;

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppUsingDirective::AdtCppUsingDirective(const AdtCppUsingDirective& rCopy)
 : AdtCppBase(rCopy)
{
  Qualified = rCopy.Qualified;
}

//  ----------------------------------------------------------------------------

AdtCppUsingDirective::~AdtCppUsingDirective()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUsingDirective::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "using namespace ");
  write(rOutFile, name());
  write(rOutFile, ";");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppUsingDirective::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: using not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppUsingDirective, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppAsmDefinition method implementations
//  ----------------------------------------------------------------------------
AdtCppAsmDefinition::AdtCppAsmDefinition(const char* pStringLiteral, const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pStringLiteral);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppAsmDefinition::AdtCppAsmDefinition(const AdtCppAsmDefinition& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppAsmDefinition::~AdtCppAsmDefinition()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAsmDefinition::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "asm {");
  write(rOutFile, name());
  write(rOutFile, "};");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppAsmDefinition::writeFortran(AdtFile& rOutFile, int nMode) const
{
  ::printf("ERROR: asm not supported in translation to Fortran on "
           "line %d in file %s\n", lineNumber(),
                                   fileName());
  AdtExit(-1);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppAsmDefinition, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppLinkageSpecification class
//  ----------------------------------------------------------------------------
AdtCppLinkageSpecification::AdtCppLinkageSpecification(AdtParser* pDeclarationSeqObj,
                                                       AdtParser* pDeclarationObj,
                                                       const char* pStringLiteral,
                                                       const char* pComment)
 : AdtCppBase()
{
  nameWithComment(pStringLiteral);

  initObject(DeclarationSeq,  pDeclarationSeqObj, AdtCppDeclarationSeq, false);
  initObject(Declaration,     pDeclarationObj,    AdtCppDeclaration,    false);

  comment(pComment);
}

//  ----------------------------------------------------------------------------

AdtCppLinkageSpecification::AdtCppLinkageSpecification(const AdtCppLinkageSpecification& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(DeclarationSeq,  rCopy, AdtCppDeclarationSeq);
  copyObject(Declaration,     rCopy, AdtCppDeclaration);
}

//  ----------------------------------------------------------------------------

AdtCppLinkageSpecification::~AdtCppLinkageSpecification()
{
  UtlReleaseReference(DeclarationSeq);
  UtlReleaseReference(Declaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLinkageSpecification::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  write(rOutFile, "extern ");
  write(rOutFile, name());
  write(rOutFile, " ");

  if (DeclarationSeq != 0)
  {
    write(rOutFile, "{");

    DeclarationSeq->writeCPP(rOutFile, nMode);

    write(rOutFile, "}");
  }
  else
  {
    write(rOutFile, " ");
  }

  if (Declaration != 0)
  {
    Declaration->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppLinkageSpecification::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (DeclarationSeq != 0)
  {
    DeclarationSeq->writeFortran(rOutFile, nMode);
  }

  if (Declaration != 0)
  {
    Declaration->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppLinkageSpecification, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInitDeclaratorList method implementations
//  ----------------------------------------------------------------------------
AdtCppInitDeclaratorList::AdtCppInitDeclaratorList(AdtParser* pInitDeclaratorObj)
 : AdtCppBase()
{
  add(pInitDeclaratorObj);
}

//  ----------------------------------------------------------------------------

AdtCppInitDeclaratorList::AdtCppInitDeclaratorList(const AdtCppInitDeclaratorList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppInitDeclaratorList::~AdtCppInitDeclaratorList()
{

}

//  ----------------------------------------------------------------------------

bool AdtCppInitDeclaratorList::isSimpleDeclaration(const char** ppIdentifier) const
{
  bool bIsSimple = false;

  if (listSize() == 1)
  {
    AdtParserPtrListConstIter   Iter            = objList().begin();
    const AdtParser*            pObj            = (*Iter);
    const AdtCppInitDeclarator* pInitDeclarator = (const AdtCppInitDeclarator*)pObj;

    if ((pInitDeclarator != 0) && pInitDeclarator->isSimpleDeclaration(ppIdentifier))
    {
      bIsSimple = true;
    }
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitDeclaratorList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitDeclaratorList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInitDeclaratorList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInitDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtCppInitDeclarator::AdtCppInitDeclarator(AdtParser* pDeclaratorObj,
                                           AdtParser* pInitializerObj)
 : AdtCppBase()
{
  initObject(Declarator,  pDeclaratorObj,   AdtCppDeclarator, false);
  initObject(Initializer, pInitializerObj,  AdtCppInitializer, false);

  if (Declarator != 0)
  {
    name(Declarator->name());
  }
}

//  ----------------------------------------------------------------------------

AdtCppInitDeclarator::AdtCppInitDeclarator(const AdtCppInitDeclarator& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Declarator,  rCopy, AdtCppDeclarator);
  copyObject(Initializer, rCopy, AdtCppInitializer);

  if (Declarator != 0)
  {
    name(Declarator->name());
  }
}

//  ----------------------------------------------------------------------------

AdtCppInitDeclarator::~AdtCppInitDeclarator()
{
  UtlReleaseReference(Declarator);
  UtlReleaseReference(Initializer);
}

//  ----------------------------------------------------------------------------

bool AdtCppInitDeclarator::isSimpleDeclaration(const char** ppIdentifier) const
{
  bool bIsSimple = false;

  if ((Declarator  != 0) &&
      (Initializer == 0))
  {
    bIsSimple = Declarator->isSimpleDeclaration(ppIdentifier);
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitDeclarator::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (Declarator != 0)
  {
    Declarator->writeCPP(rOutFile, nMode);
  }

  if (Initializer != 0)
  {
    Initializer->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (Declarator != 0)
  {
    Declarator->writeFortran(rOutFile, nMode);
  }

  if (Initializer != 0)
  {
    Initializer->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInitDeclarator, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclarator::AdtCppDeclarator(AdtParser* pParameterDeclarationClauseObj,
                                   AdtParser* pExpressionListObj,
                                   AdtParser* pDeclaratorDimsObj,
                                   const char* pIdentifier,
                                   bool bWithBrackets,
                                   bool bQualified,
                                   bool bIsObj,
                                   bool bIsVirtual,
                                   AdtCppDeclaratorCV_Type nType,
                                   const char* pComment,
                                   bool bInitQualifiedName)
 : AdtCppEmbeddedComment()
{
  initialise(pIdentifier);

  initObject(ParameterDeclarationClause,  pParameterDeclarationClauseObj, AdtCppParameterDeclarationClause, false);
  initObject(ExpressionList,              pExpressionListObj,             AdtCppExpressionList,             false);
  initObject(DeclaratorDims,              pDeclaratorDimsObj,             AdtCppDeclaratorDims,             false);

  WithBrackets  = bWithBrackets;
  Qualified     = bQualified;
  Type          = nType;
  IsObj         = bIsObj;
  IsVirtual     = bIsVirtual;

  comment(pComment);

  if (bInitQualifiedName)
  {
    initialiseQualifiedName();
  }
}

//  ----------------------------------------------------------------------------

AdtCppDeclarator::AdtCppDeclarator(const AdtCppDeclarator& rCopy)
 : AdtCppEmbeddedComment(rCopy)
{
  copyObject(ParameterDeclarationClause,  rCopy, AdtCppParameterDeclarationClause);
  copyObject(ExpressionList,              rCopy, AdtCppExpressionList);
  copyObject(DeclaratorDims,              rCopy, AdtCppDeclaratorDims);

  WithBrackets  = rCopy.WithBrackets;
  Qualified     = rCopy.Qualified;
  Type          = rCopy.Type;
  IsObj         = rCopy.IsObj;
  IsVirtual     = rCopy.IsVirtual;
}

//  ----------------------------------------------------------------------------

AdtCppDeclarator::~AdtCppDeclarator()
{
  UtlReleaseReference(ParameterDeclarationClause);
  UtlReleaseReference(ExpressionList);
  UtlReleaseReference(DeclaratorDims);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclarator::isSimpleDeclaration(const char** ppIdentifier) const
{
  bool bIsSimple = false;

  if ((ParameterDeclarationClause  == 0     ) &&
      (ExpressionList              == 0     ) &&
      (DeclaratorDims              == 0     ) &&
      (WithBrackets                == false ) &&
      (Type                        == AdtCppDeclaratorCV_None))
  {
    if (ppIdentifier)
    {
      *ppIdentifier = name();
    }

    bIsSimple = true;
  }

  return (bIsSimple);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclarator::isCallDeclaration(size_t* pnArgs) const
{
  bool bIsCall = false;

  if ((ParameterDeclarationClause  == 0   ) &&
      (ExpressionList              != 0   ) &&
      (DeclaratorDims              == 0   ) &&
      (WithBrackets                == true) &&
      (Type                        == AdtCppDeclaratorCV_None))
  {
    if (pnArgs)
    {
      *pnArgs = ExpressionList->listSize();
    }

    bIsCall = true;
  }

  return (bIsCall);
}

//  ----------------------------------------------------------------------------

bool AdtCppDeclarator::isFunctionDeclaration() const
{
  bool bIsFunction = false;

  if ((Parent != 0) && Parent->isType("AdtCppFunctionDefinition"))
  {
    bIsFunction = true;
  }

  return (bIsFunction);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarator::writeCPP(AdtFile& rOutFile, int nMode) const
{
  writeExpanded(rOutFile, comment());

  if (IsVirtual)
  {
    write(rOutFile, "virtual ");
  }

  if ((nMode != 2) || !WithBrackets)
  {
    write(rOutFile, name());
  }

  if (DeclaratorDims != 0)
  {
    DeclaratorDims->writeCPP(rOutFile, nMode);
  }

  if (WithBrackets)
  {
    write(rOutFile, "(");
  }

  if (ParameterDeclarationClause != 0)
  {
    ParameterDeclarationClause->writeCPP(rOutFile, nMode);
  }

  if (ExpressionList != 0)
  {
    ExpressionList->writeCPP(rOutFile, nMode);
  }

  if (WithBrackets)
  {
    write(rOutFile, ")");
  }

  switch(Type)
  {
    case AdtCppDeclaratorCV_None:
    default:
    {
      break;
    }

    case AdtCppDeclaratorCV_Const:
    {
      write(rOutFile, "const ");
      break;
    }

    case AdtCppDeclaratorCV_Volatile:
    {
      write(rOutFile, "volatile ");
      break;
    }
  }

  write(rOutFile, embeddedComment());

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  switch (nMode)
  {
    case WRITE_MODE_INTENTS:
    case WRITE_MODE_TYPEDECLS:
    {
      if (ParameterDeclarationClause != 0)
      {
        ParameterDeclarationClause->writeFortran(rOutFile, nMode);
      }
      break;
    }

    default:
    {
      string sConvertedName;

      nameToFortran(name(), sConvertedName);
      write(rOutFile, sConvertedName);

      if (DeclaratorDims != 0)
      {
        DeclaratorDims->writeFortran(rOutFile, nMode);
      }

      if (WithBrackets)
      {
        write(rOutFile, "(");
      }

      if (ParameterDeclarationClause != 0)
      {
        ParameterDeclarationClause->writeFortran(rOutFile, nMode);
      }

      if (ExpressionList != 0)
      {
        ExpressionList->writeFortran(rOutFile, nMode);
      }

      if (WithBrackets)
      {
        write(rOutFile, ")");
      }
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclarator, AdtCppEmbeddedComment);


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorDims method implementations
//  ----------------------------------------------------------------------------
AdtCppDeclaratorDims::AdtCppDeclaratorDims(AdtParser* pConstantExpressionObj,
                                           AdtParser* pDeclaratorDimsObj)
 : AdtCppBase()
{
  initObject(ConstantExpression,  pConstantExpressionObj, AdtCppConstantExpression, false);
  initObject(DeclaratorDims,      pDeclaratorDimsObj,     AdtCppDeclaratorDims,     false);
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorDims::AdtCppDeclaratorDims(const AdtCppDeclaratorDims& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ConstantExpression,  rCopy, AdtCppConstantExpression);
  copyObject(DeclaratorDims,      rCopy, AdtCppDeclaratorDims);
}

//  ----------------------------------------------------------------------------

AdtCppDeclaratorDims::~AdtCppDeclaratorDims()
{
  UtlReleaseReference(ConstantExpression);
  UtlReleaseReference(DeclaratorDims);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorDims::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (DeclaratorDims != 0)
  {
    DeclaratorDims->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, "[");

  if (ConstantExpression != 0)
  {
    ConstantExpression->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, "]");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppDeclaratorDims::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppDeclaratorDims, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclarationClause method implementations
//  ----------------------------------------------------------------------------
AdtCppParameterDeclarationClause::AdtCppParameterDeclarationClause(AdtParser* pParameterDeclarationListObj,
                                                                   bool bHasEllipsis,
                                                                   bool bHasComma)
 : AdtCppBase()
{
  initObject(ParameterDeclarationList, pParameterDeclarationListObj, AdtCppParameterDeclarationList, false);

  HasEllipsis = bHasEllipsis;
  HasComma    = bHasComma;
}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclarationClause::AdtCppParameterDeclarationClause(const AdtCppParameterDeclarationClause& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ParameterDeclarationList, rCopy, AdtCppParameterDeclarationList);

  HasEllipsis = rCopy.HasEllipsis;
  HasComma    = rCopy.HasComma;
}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclarationClause::~AdtCppParameterDeclarationClause()
{
  UtlReleaseReference(ParameterDeclarationList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclarationClause::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (ParameterDeclarationList != 0)
  {
    ParameterDeclarationList->writeCPP(rOutFile, nMode);
  }

  if (HasComma)
  {
    write(rOutFile, ", ");
  }

  if (HasEllipsis)
  {
    write(rOutFile, "... ");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclarationClause::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (ParameterDeclarationList != 0)
  {
    ParameterDeclarationList->writeFortran(rOutFile, nMode);
  }

  if (HasComma)
  {
    write(rOutFile, ", ");
  }

  if (HasEllipsis)
  {
    write(rOutFile, "... ");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppParameterDeclarationClause, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclarationList method implementations
//  ----------------------------------------------------------------------------
AdtCppParameterDeclarationList::AdtCppParameterDeclarationList(AdtParser* pParameterDeclarationObj)
 : AdtCppBase()
{
  add(pParameterDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclarationList::AdtCppParameterDeclarationList(const AdtCppParameterDeclarationList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclarationList::~AdtCppParameterDeclarationList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclarationList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclarationList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  switch (nMode)
  {
    case WRITE_MODE_INTENTS:
    case WRITE_MODE_TYPEDECLS:
    {
      forAllWriteFortran(rOutFile, nMode, " ", true, false);
      break;
    }

    default:
    {
      forAllWriteFortran(rOutFile, nMode, ", ", false, true);
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppParameterDeclarationList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtCppParameterDeclaration::AdtCppParameterDeclaration(AdtParser* pDeclModifierListObj,
                                                       AdtParser* pSimpleTypeSpecifierObj,
                                                       AdtParser* pDeclaratorObj,
                                                       AdtParser* pAssignmentExpressionObj)
 : AdtCppBase()
{
  initObject(DeclModifierList,      pDeclModifierListObj,     AdtCppDeclModifierList,     false);
  initObject(SimpleTypeSpecifier,   pSimpleTypeSpecifierObj,  AdtCppSimpleTypeSpecifier,  false);
  initObject(Declarator,            pDeclaratorObj,           AdtCppDeclarator,           false);
  initObject(AssignmentExpression,  pAssignmentExpressionObj, AdtCppAssignmentExpression, false);

  if (Declarator != 0)
  {
    name(Declarator->name());
  }
}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclaration::AdtCppParameterDeclaration(const AdtCppParameterDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(DeclModifierList,      rCopy, AdtCppDeclModifierList);
  copyObject(SimpleTypeSpecifier,   rCopy, AdtCppSimpleTypeSpecifier);
  copyObject(Declarator,            rCopy, AdtCppDeclarator);
  copyObject(AssignmentExpression,  rCopy, AdtCppAssignmentExpression);
}

//  ----------------------------------------------------------------------------

AdtCppParameterDeclaration::~AdtCppParameterDeclaration()
{
  UtlReleaseReference(DeclModifierList);
  UtlReleaseReference(SimpleTypeSpecifier);
  UtlReleaseReference(Declarator);
  UtlReleaseReference(AssignmentExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if ((DeclModifierList != 0) && (nMode != 1))
  {
    DeclModifierList->writeCPP(rOutFile, nMode);
  }

  if ((SimpleTypeSpecifier != 0) && (nMode != 1))
  {
    SimpleTypeSpecifier->writeCPP(rOutFile, nMode);
  }

  if (Declarator != 0)
  {
    Declarator->writeCPP(rOutFile, nMode);
  }

  if ((AssignmentExpression != 0) && (nMode != 1))
  {
    write(rOutFile, " = ");
    AssignmentExpression->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppParameterDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  switch (nMode)
  {
    case WRITE_MODE_INTENTS:
    {
      write(rOutFile, "INTENT (");

      // Any const vars or vars passed by value need to be declared IN
      // Any non const pass by reference or ARRAY types need to be of INOUT
      // intent
      bool bIsInOut = true;

      if (DeclModifierList != 0)
      {
        AdtParserPtrListConstIter  Iter;

        for (Iter = DeclModifierList->objList().begin() ; Iter != DeclModifierList->objList().end() ; ++Iter)
        {
          const AdtParser*          pObj          = *Iter;
          const AdtCppDeclModifier* pDeclModifier = (const AdtCppDeclModifier*)pObj;

          if ((pDeclModifier != 0) && pDeclModifier->isConst())
          {
            bIsInOut = false;
            break;
          }
        }
      }

      if (SimpleTypeSpecifier != 0)
      {
        bIsInOut = bIsInOut & SimpleTypeSpecifier->isInOut();
      }

      if (bIsInOut)
      {
        write(rOutFile, "INOUT");
      }
      else
      {
        write(rOutFile, "IN");
      }

      write(rOutFile, ") ");

      if (Declarator != 0)
      {
        Declarator->writeFortran(rOutFile, 0);
      }
      break;
    }

    case WRITE_MODE_TYPEDECLS:
    {
      if (DeclModifierList != 0)
      {
        DeclModifierList->writeFortran(rOutFile, nMode);
      }

      if (SimpleTypeSpecifier != 0)
      {
        SimpleTypeSpecifier->writeFortran(rOutFile, nMode);
      }

      if (Declarator != 0)
      {
        Declarator->writeFortran(rOutFile, 0);

        if (SimpleTypeSpecifier != 0)
        {
          SimpleTypeSpecifier->writeArrayBounds(rOutFile, Declarator);
        }
      }

      if (AssignmentExpression != 0)
      {
        write(rOutFile, " = ");
        AssignmentExpression->writeFortran(rOutFile, nMode);
      }
      break;
    }

    default:
    {
      if (Declarator != 0)
      {
        Declarator->writeFortran(rOutFile, nMode);
      }
      break;
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppParameterDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppFunctionDefinition method implementations
//  ----------------------------------------------------------------------------
AdtCppFunctionDefinition::AdtCppFunctionDefinition(AdtParser* pDeclModifierListObj,
                                                   AdtParser* pSimpleTypeSpecifierObj,
                                                   AdtParser* pDeclaratorObj,
                                                   AdtParser* pCtorInitializerObj,
                                                   AdtParser* pFunctionBodyObj,
                                                   bool bHasSemiColon)
 : AdtCppCheckDeclaration()
{
  initObject(DeclModifierList,    pDeclModifierListObj,     AdtCppDeclModifierList,     false);
  initObject(SimpleTypeSpecifier, pSimpleTypeSpecifierObj,  AdtCppSimpleTypeSpecifier,  false);
  initObject(Declarator,          pDeclaratorObj,           AdtCppDeclarator,           false);
  initObject(CtorInitializer,     pCtorInitializerObj,      AdtCppCtorInitializer,      false);
  initObject(FunctionBody,        pFunctionBodyObj,         AdtCppFunctionBody,         false);

  BlackBox     = 0;
  HasSemiColon = bHasSemiColon;

  if (Declarator != 0)
  {
    name(Declarator->name());
    initialiseQualifiedName();
  }

  if ((SimpleTypeSpecifier != 0) && (Declarator != 0) && AdtBlackBoxCompiler::isBlackBox(SimpleTypeSpecifier->comment()))
  {
    string  sQualifiedName(name());
    bool    bIsFunction = !SimpleTypeSpecifier->isVoid();

    AdtCppScopeManager::globalScopeManager()->qualifyName(sQualifiedName);

    BlackBox = new AdtBlackBoxDefinition(sQualifiedName, bIsFunction, yyCpp_fileName(), yyCpp_lineNumber());

    if (BlackBox != 0)
    {
      AdtParserPtrList        ObjList;
      AdtParserPtrListIter    Iter;

      // Need to initialise black box definition based on argument list and return type
      Declarator->enumerateDescendantList(ObjList, "ParameterDeclarationClause,ParameterDeclarationList");

      for (Iter = ObjList.begin() ; Iter != ObjList.end() ; ++Iter)
      {
        AdtCppParameterDeclaration* pParameterDeclaration = (AdtCppParameterDeclaration*)Iter->object();

        if (pParameterDeclaration != 0)
        {
          AdtCppSimpleTypeSpecifier* pSimpleTypeSpecifier = (AdtCppSimpleTypeSpecifier*)pParameterDeclaration->findDescendant("SimpleTypeSpecifier");

          if (pSimpleTypeSpecifier != 0)
          {
            pSimpleTypeSpecifier->addToBlackBox(*BlackBox, pParameterDeclaration->name(), false, yyCpp_fileName(), yyCpp_lineNumber());
          }
        }
      }

      if (bIsFunction)
      {
        SimpleTypeSpecifier->addToBlackBox(*BlackBox, 0, true, yyCpp_fileName(), yyCpp_lineNumber());
      }

      AdtBlackBoxCompiler::parseComments(*BlackBox, SimpleTypeSpecifier->comment(), yyCpp_fileName(), yyCpp_lineNumber());
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppFunctionDefinition::AdtCppFunctionDefinition(const AdtCppFunctionDefinition& rCopy)
 : AdtCppCheckDeclaration(rCopy)
{
  copyObject(DeclModifierList,    rCopy, AdtCppDeclModifierList);
  copyObject(SimpleTypeSpecifier, rCopy, AdtCppSimpleTypeSpecifier);
  copyObject(Declarator,          rCopy, AdtCppDeclarator);
  copyObject(CtorInitializer,     rCopy, AdtCppCtorInitializer);
  copyObject(FunctionBody,        rCopy, AdtCppFunctionBody);

  BlackBox      = (rCopy.BlackBox != 0) ? new AdtBlackBoxDefinition(*rCopy.BlackBox) : 0;
  HasSemiColon  = rCopy.HasSemiColon;
}

//  ----------------------------------------------------------------------------

AdtCppFunctionDefinition::~AdtCppFunctionDefinition()
{
  if (BlackBox != 0)
  {
    delete BlackBox;
  }

  UtlReleaseReference(DeclModifierList);
  UtlReleaseReference(SimpleTypeSpecifier);
  UtlReleaseReference(Declarator);
  UtlReleaseReference(CtorInitializer);
  UtlReleaseReference(FunctionBody);
}

//  ----------------------------------------------------------------------------

void AdtCppFunctionDefinition::checkDeclarations(const AdtCppTranslationUnit* pTranslationUnit) const
{
  if (!isCtor() && (FunctionBody != 0) && (pTranslationUnit != 0))
  {
    string                rClassName;
    string                rParentClassName;
    AdtCppClassSpecifier* pClassSpecifier = 0;

    AdtCppBase::prefixFromQualifiedName(qualifiedName(), rClassName);

    if (rClassName.length() > 0)
    {
      pClassSpecifier = pTranslationUnit->findClass(rClassName, rParentClassName);
    }

    FunctionBody->checkDeclarations(pTranslationUnit, pClassSpecifier);
  }
}

//  ----------------------------------------------------------------------------

bool AdtCppFunctionDefinition::isProcedure() const
{
  bool bIsProcedure = false;

  if ((Declarator           != 0) &&
      (SimpleTypeSpecifier  != 0) &&
      (FunctionBody         != 0))
  {
    bIsProcedure = SimpleTypeSpecifier->isVoid();
  }

  return (bIsProcedure);
}

//  ----------------------------------------------------------------------------

bool AdtCppFunctionDefinition::enumerateLocalObjects(AdtParserPtrList& rExternalsList) const
{
  bool bEnumerated = false;

  if (FunctionBody != 0)
  {
    //Find all local variable declarations
    AdtParserPtrListIter                  ListIter;
    AdtParserPtrList                      LocalsList;
    const AdtCppParameterDeclarationList* ParameterDeclarations = 0;

    if (Declarator != 0)
    {
      ParameterDeclarations = (const AdtCppParameterDeclarationList*)Declarator->findObject("AdtCppParameterDeclarationList");
    }

    if (ParameterDeclarations != 0)
    {
      ParameterDeclarations->findObjects(LocalsList, "AdtCppDeclarator", 0, false, "AdtCppParameterDeclaration");
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

bool AdtCppFunctionDefinition::enumerateExternals(AdtStringList& rExternalsList) const
{
  bool bEnumerated = false;

  if (FunctionBody != 0)
  {
    //Find all local variable declarations
    AdtParserPtrListIter                  ListIter;
    AdtParserPtrList                      RefList;
    AdtParserPtrList                      LocalsList;
    AdtParserPtrByStringMultiMap          LocalsMap;
    AdtStringByStringMap                  ArraySizeMap;
    AdtStringByStringMapIter              MapIter;
    const AdtCppParameterDeclarationList* ParameterDeclarations = 0;

    if (Declarator != 0)
    {
      ParameterDeclarations = (const AdtCppParameterDeclarationList*)Declarator->findObject("AdtCppParameterDeclarationList");
    }

    if (ParameterDeclarations != 0)
    {
      ParameterDeclarations->findObjects(LocalsList, "AdtCppDeclarator", 0, false, "AdtCppParameterDeclaration");
    }

    if (FunctionBody != 0)
    {
      FunctionBody->findObjects(LocalsList, "AdtCppDeclarator", 0, false, "AdtCppInitDeclarator");
    }

    //Add it to a map for quick matching
    for (ListIter = LocalsList.begin() ; ListIter != LocalsList.end() ; ++ListIter)
    {
      AdtCppDeclarator* pDeclaratorObj = (AdtCppDeclarator*)((*ListIter).object());

      LocalsMap.insert(AdtParserPtrByStringMap::value_type(pDeclaratorObj->name(), *ListIter));

      // Need to add all array dimension objects as external references
      pDeclaratorObj->enumerateArraySizes(ArraySizeMap);
    }

    //search block for all uses of vars. These are possible unresolved externals.
    if (FunctionBody != 0)
    {
      FunctionBody->findObjects(RefList, "AdtCppDeclaratorExpression");
    }

    //Match Idents with locals. Any that don't match must be externals. We need to
    //check that the depth of the declaration in the map is less than the code for
    //it to match. If it is not then the var use is out of scope.
    for (ListIter = RefList.begin() ; ListIter != RefList.end() ; ++ListIter)
    {
      AdtParser*  pRefObj = *ListIter;

      if (pRefObj != 0)
      {
        AdtParserPtrByStringMultiMapIter  MapIter;
        bool                              bNotDefined = true;

        for (MapIter = LocalsMap.lower_bound(pRefObj->name()) ; MapIter != LocalsMap.upper_bound(pRefObj->name()) ; ++MapIter)
        {
          AdtParser*  pDeclObj = (*MapIter).second;

          if ((pDeclObj != 0) && (pDeclObj->parent() != 0))
          {
            if (pDeclObj->parent()->isType("AdtCppInitDeclarator"))
            {
              // Need to check if in scope
              AdtParser* pDeclStatementObj  = pDeclObj->findAscendantWithClass("AdtCppStatement");
              AdtParser* pRefStatementObj   = pRefObj->findAscendantWithClass("AdtCppStatement");

              if ((pDeclStatementObj != 0) && (pRefStatementObj != 0))
              {
                if (pDeclStatementObj->depth() <= pRefStatementObj->depth())
                {
                  // The referenced var is a local and in scope
                  bNotDefined = false;
                  break;
                }
              }
              else
              {
                FAIL();
              }
            }
            else
            {
              // This is a function parameter so is always in scope
              bNotDefined = false;
              break;
            }
          }
        }

        if (bNotDefined)
        {
          rExternalsList.push_back(pRefObj->name());
          bEnumerated = true;
        }
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

void AdtCppFunctionDefinition::replaceScopeName(const char* pSearchName,
                                                const char* pReplaceName)
{
  if ((Declarator != 0) && (pSearchName != 0) && (pReplaceName != 0))
  {
    string  sNewName(Declarator->name());
    size_t  nLength = ::strlen(pSearchName);
    size_t  nPos;

    for (nPos = sNewName.find(pSearchName) ; nPos >= 0 ; nPos = sNewName.find(pSearchName))
    {
      sNewName.replace(nPos, nLength, pReplaceName);
    }

    Declarator->name(sNewName);
    name(sNewName);
    initialiseQualifiedName();
  }
}

//  ----------------------------------------------------------------------------

void AdtCppFunctionDefinition::promoteToFullyQualified()
{
  if (Declarator != 0)
  {
    // replace the function name with the fully qualified one
    name(qualifiedName());
    Declarator->name(qualifiedName());
  }
}

//  ----------------------------------------------------------------------------

void AdtCppFunctionDefinition::removeFunctionBody()
{
  UtlReleaseReference(FunctionBody);

  FunctionBody = 0;
}

//  ----------------------------------------------------------------------------

bool AdtCppFunctionDefinition::isForwardDeclaration(bool bClassScope) const
{
  bool bIsForwardDeclaration = !(hasBody() || (bClassScope && !isCtor()));

  return (bIsForwardDeclaration);
}

//  ----------------------------------------------------------------------------

bool AdtCppFunctionDefinition::isCtor() const
{
  return ((Declarator != 0) && Declarator->isObj());
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppFunctionDefinition::writeCPP(AdtFile& rOutFile, int nMode) const
{
  AdtCppTranslationUnit* pRoot        = cppRootObject();
  bool                   bIsBlackBox  = ((pRoot != 0) && pRoot->isBlackBox(qualifiedName()));

  // Only write if it isn't a black box routine. Black boxes aren't meant to be
  // seen by tapenade and should be ignored.
  if (!bIsBlackBox)
  {
    if (FunctionBody != 0)
    {
      rOutFile.newline();
      write(rOutFile, "// ----------------------------------------------------------------------------");
      rOutFile.newline();
      rOutFile.newline();
    }

    if (DeclModifierList != 0)
    {
      DeclModifierList->writeCPP(rOutFile, nMode);
    }

    if (SimpleTypeSpecifier != 0)
    {
      SimpleTypeSpecifier->writeCPP(rOutFile, nMode);
    }

    if (Declarator != 0)
    {
      Declarator->writeCPP(rOutFile, nMode);
    }

    if (CtorInitializer != 0)
    {
      CtorInitializer->writeCPP(rOutFile, nMode);
    }

    if (FunctionBody != 0)
    {
      FunctionBody->writeCPP(rOutFile, nMode);
    }

    if (HasSemiColon)
    {
      write(rOutFile, ";");
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppFunctionDefinition::writeFortran(AdtFile& rOutFile, int nMode) const
{
  bool bFunction  = false;
  bool bIsCall    = (Declarator != 0) ? Declarator->isFunctionDeclaration() : false;

  if (FunctionBody != 0)
  {
    rOutFile.newline();
    rOutFile.newline();
    rOutFile.newline();
  }

  if (DeclModifierList != 0)
  {
    DeclModifierList->writeFortran(rOutFile, nMode);
  }

  if ((SimpleTypeSpecifier != 0) && !SimpleTypeSpecifier->isVoid())
  {
    SimpleTypeSpecifier->writeFortran(rOutFile, nMode);

    if (bIsCall)
    {
      write(rOutFile, "FUNCTION ");

      bFunction = true;
    }
  }
  else
  {
    if (bIsCall)
    {
      write(rOutFile, "SUBROUTINE ");
    }
  }

  if (Declarator != 0)
  {
    Declarator->writeFortran(rOutFile, nMode);
  }

  if (CtorInitializer != 0)
  {
    CtorInitializer->writeFortran(rOutFile, nMode);
  }

  if (bIsCall)
  {
    rOutFile.newline();

    if (Declarator != 0)
    {
      //Write INTENTs
      Declarator->writeFortran(rOutFile, WRITE_MODE_INTENTS);

      //Write argument types
      Declarator->writeFortran(rOutFile, WRITE_MODE_TYPEDECLS);
    }

    rOutFile.newline();
    write(rOutFile, "USE COMMON");
  }

  if (FunctionBody != 0)
  {
    FunctionBody->writeFortran(rOutFile, nMode);
  }

  if (bIsCall)
  {
    write(rOutFile, "END ");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppFunctionDefinition, AdtCppCheckDeclaration);


//  ----------------------------------------------------------------------------
//  AdtCppFunctionBody method implementations
//  ----------------------------------------------------------------------------
AdtCppFunctionBody::AdtCppFunctionBody(AdtParser* pCompoundStatementObj)
 : AdtCppBase()
{
  initObject(CompoundStatement, pCompoundStatementObj, AdtCppCompoundStatement, false);
}

//  ----------------------------------------------------------------------------

AdtCppFunctionBody::AdtCppFunctionBody(const AdtCppFunctionBody& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(CompoundStatement, rCopy, AdtCppCompoundStatement);
}

//  ----------------------------------------------------------------------------

AdtCppFunctionBody::~AdtCppFunctionBody()
{
  UtlReleaseReference(CompoundStatement);
}

//  ----------------------------------------------------------------------------

void AdtCppFunctionBody::checkDeclarations(const AdtCppTranslationUnit* pTranslationUnit,
                                           const AdtCppClassSpecifier* pClassSpecifier) const
{
  if (CompoundStatement != 0)
  {
    const AdtCppStatementSeq* pStatementSeq = (const AdtCppStatementSeq*)CompoundStatement->findDescendant("StatementSeq");

    if (pStatementSeq != 0)
    {
      bool                      bOtherStatements = false;
      AdtParserPtrListConstIter Iter;
      AdtIntByStringMap         RedefMap;

      // Check that variable declarations are only present at the beginning of the
      // body and before any code. Also check that all declarations are caselessly
      // different from each other, the variables are in the current scope and
      // the variables don't have initialisers.
      for (Iter = pStatementSeq->objList().begin() ; Iter != pStatementSeq->objList().end() ; ++Iter)
      {
        const AdtParser*  pObj = *Iter;

        if (pObj != 0)
        {
          if (pObj->findDescendant("DeclarationStatement"))
          {
            if (bOtherStatements)
            {
              ::printf("ERROR: Local declaration on line %d in file %s occurs after "
                       "functional statements making translation to fortran impossible\n",
                       pObj->lineNumber(),
                       pObj->fileName());

              AdtExit(-1);
            }

            AdtParserPtrList          DeclList;
            AdtParserPtrListConstIter DeclIter;

            pObj->enumerateDescendantList(DeclList, "DeclarationStatement,BlockDeclaration,SimpleDeclaration,InitDeclaratorList");

            for (DeclIter = DeclList.begin() ; DeclIter != DeclList.end() ; ++DeclIter)
            {
              const AdtParser*  pDeclObj            = *DeclIter;
              const AdtParser*  pInitializer        = pDeclObj->findDescendant("Initializer");
              const AdtParser*  pSimpleDeclaration  = pDeclObj->findAscendantWithClass("AdtCppSimpleDeclaration");

              if ((pInitializer != 0) && (pSimpleDeclaration != 0))
              {
                const AdtParser*  pSimpleTypeSpecifier = pSimpleDeclaration->findDescendant("SimpleTypeSpecifier");

                if ((pSimpleTypeSpecifier != 0) && (pSimpleTypeSpecifier->name() != "AdtArrayPlan"))
                {
                  ::printf("ERROR: Local declaration %s on line %d in file %s has "
                           "inline initialisation which is not supported in fortran. "
                           "Please remove the initialisation part and put it in a "
                           "seperate initialisation expression\n",
                           pDeclObj->name().c_str(),
                           pDeclObj->lineNumber(),
                           pDeclObj->fileName());

                  AdtExit(-1);
                }
              }

              if (RedefMap.find(pDeclObj->name()) == RedefMap.end())
              {
                if ((pClassSpecifier  != 0) &&
                    (pTranslationUnit != 0))
                {
                  const AdtParser*  pExistingObj = 0;
                  string            rQualifiedName(pClassSpecifier->qualifiedName());

                  rQualifiedName += "::" + pDeclObj->name();

                  // Check if the local declaration conflicts with class
                  // attributes.
                  if (pClassSpecifier->findField(pTranslationUnit,
                                                 pDeclObj->name(),
                                                 pExistingObj))
                  {
                    ::printf("WARNING: Local declaration %s on line %d in file %s masks "
                             "class attribute %s on line %d in file %s.\n",
                             pDeclObj->name().c_str(),
                             pDeclObj->lineNumber(),
                             pDeclObj->fileName(),
                             pExistingObj->name().c_str(),
                             pExistingObj->lineNumber(),
                             pExistingObj->fileName());
                  }
                  else if (pClassSpecifier->findMethod(pTranslationUnit,
                                                       pDeclObj->name(),
                                                       pExistingObj))
                  {
                    ::printf("WARNING: Local declaration %s on line %d in file %s masks "
                             "class method %s on line %d in file %s.\n",
                             pDeclObj->name().c_str(),
                             pDeclObj->lineNumber(),
                             pDeclObj->fileName(),
                             pExistingObj->name().c_str(),
                             pExistingObj->lineNumber(),
                             pExistingObj->fileName());
                  }
                }

                RedefMap[pDeclObj->name()];
              }
              else
              {
                ::printf("ERROR: Local declaration %s on line %d in file %s differs only by case "
                         "from another one in the same scope.\n",
                         pDeclObj->name().c_str(),
                         pDeclObj->lineNumber(),
                         pDeclObj->fileName());

                AdtExit(-1);
              }
            }
          }
          else
          {
            const AdtParser*  pDeclObj;

            bOtherStatements  = true;
            pDeclObj          = pObj->findObject("AdtCppDeclarationStatement");

            if (pDeclObj != 0)
            {
              ::printf("ERROR: Local declaration on line %d in file %s occurs after "
                       "functional statements making translation to fortran impossible\n",
                       pDeclObj->lineNumber(),
                       pDeclObj->fileName());

              AdtExit(-1);
            }
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppFunctionBody::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (CompoundStatement != 0)
  {
    rOutFile.newline();

    CompoundStatement->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppFunctionBody::writeFortran(AdtFile& rOutFile, int nMode) const
{
  if (CompoundStatement != 0)
  {
    rOutFile.newline();

    CompoundStatement->writeFortran(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppFunctionBody, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInitializer class
//  ----------------------------------------------------------------------------
AdtCppInitializer::AdtCppInitializer(AdtParser* pInitializerClauseObj,
                                     AdtParser* pExpressionListObj)
 : AdtCppBase()
{
  initObject(InitializerClause, pInitializerClauseObj,  AdtCppInitializerClause,  false);
  initObject(ExpressionList,    pExpressionListObj,     AdtCppExpressionList,     false);
}

//  ----------------------------------------------------------------------------

AdtCppInitializer::AdtCppInitializer(const AdtCppInitializer& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(InitializerClause, rCopy, AdtCppInitializerClause);
  copyObject(ExpressionList,    rCopy, AdtCppExpressionList);
}

//  ----------------------------------------------------------------------------

AdtCppInitializer::~AdtCppInitializer()
{
  UtlReleaseReference(InitializerClause);
  UtlReleaseReference(ExpressionList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializer::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (InitializerClause != 0)
  {
    write(rOutFile, " = ");
    InitializerClause->writeCPP(rOutFile, nMode);
  }

  if (ExpressionList != 0)
  {
    write(rOutFile, "(");
    ExpressionList->writeCPP(rOutFile, nMode);
    write(rOutFile, ")");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializer::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInitializer, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInitializerClause method implementations
//  ----------------------------------------------------------------------------
AdtCppInitializerClause::AdtCppInitializerClause(AdtParser* pAssignmentExpressionObj,
                                                 AdtParser* pInitializerListObj,
                                                 bool bHasComma)
 : AdtCppBase()
{
  initObject(AssignmentExpression,  pAssignmentExpressionObj, AdtCppAssignmentExpression, false);
  initObject(InitializerList,       pInitializerListObj,      AdtCppInitializerList,      false);

  HasComma = bHasComma;
}

//  ----------------------------------------------------------------------------

AdtCppInitializerClause::AdtCppInitializerClause(const AdtCppInitializerClause& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(AssignmentExpression,  rCopy, AdtCppAssignmentExpression);
  copyObject(InitializerList,       rCopy, AdtCppInitializerList);

  HasComma = rCopy.HasComma;
}

//  ----------------------------------------------------------------------------

AdtCppInitializerClause::~AdtCppInitializerClause()
{
  UtlReleaseReference(AssignmentExpression);
  UtlReleaseReference(InitializerList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializerClause::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (AssignmentExpression != 0)
  {
    AssignmentExpression->writeCPP(rOutFile, nMode);
  }

  if ((InitializerList != 0) || ((AssignmentExpression == 0) && (InitializerList == 0)))
  {
    write(rOutFile, "{");

    if (InitializerList != 0)
    {
      InitializerList->writeCPP(rOutFile, nMode);
    }

    if (HasComma)
    {
      write(rOutFile, ",}");
    }
    else
    {
      write(rOutFile, "}");
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializerClause::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInitializerClause, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppInitializerList method implementations
//  ----------------------------------------------------------------------------
AdtCppInitializerList::AdtCppInitializerList(AdtParser* pInitializerClauseObj)
 : AdtCppBase()
{
  add(pInitializerClauseObj);
}

//  ----------------------------------------------------------------------------

AdtCppInitializerList::AdtCppInitializerList(const AdtCppInitializerList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppInitializerList::~AdtCppInitializerList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializerList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppInitializerList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppInitializerList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppClassKey method implementations
//  ----------------------------------------------------------------------------
AdtCppClassKey::AdtCppClassKey(AdtCppClassKeyType nType, const char* pIdentifier, bool bQualified, const char* pComment)
 : AdtCppBase()
{
  Type      = nType;
  Qualified = bQualified;

  nameWithComment(pIdentifier);
  comment(pComment);

  switch (Type)
  {
    case AdtCppClassKeyType_CLASS:
    {
      AdtCppMemberDeclaration::GlobalType = AdtCppMemberScopeType_PRIVATE;
      break;
    }

    case AdtCppClassKeyType_UNION:
    case AdtCppClassKeyType_STRUCT:
    default:
    {
      AdtCppMemberDeclaration::GlobalType = AdtCppMemberScopeType_PUBLIC;
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtCppClassKey::AdtCppClassKey(const AdtCppClassKey& rCopy)
 : AdtCppBase(rCopy)
{
  Type      = rCopy.Type;
  Qualified = rCopy.Qualified;
}

//  ----------------------------------------------------------------------------

AdtCppClassKey::~AdtCppClassKey()
{

}

//  ----------------------------------------------------------------------------

AdtCppMemberScopeType AdtCppClassKey::scopeType() const
{
  AdtCppMemberScopeType nType = AdtCppMemberScopeType_NONE;

  switch (Type)
  {
    case AdtCppClassKeyType_CLASS:
    {
      nType = AdtCppMemberScopeType_PRIVATE;
      break;
    }

    default:
    case AdtCppClassKeyType_STRUCT:
    case AdtCppClassKeyType_UNION:
    {
      nType = AdtCppMemberScopeType_PUBLIC;
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppClassKey::writeCPP(AdtFile& rOutFile, int nMode) const
{
  switch (Type)
  {
    case AdtCppClassKeyType_CLASS:
    {
      write(rOutFile, "class ");
      break;
    }

    case AdtCppClassKeyType_STRUCT:
    {
      write(rOutFile, "struct ");
      break;
    }

    case AdtCppClassKeyType_UNION:
    {
      write(rOutFile, "union ");
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  write(rOutFile, name());
  write(rOutFile, " ");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppClassKey::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppClassKey, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemberSpecification method implementations
//  ----------------------------------------------------------------------------
AdtCppMemberSpecification::AdtCppMemberSpecification(AdtParser* pMemberDeclarationObj)
 : AdtCppDeclarationInfo()
{
  add(pMemberDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtCppMemberSpecification::AdtCppMemberSpecification(const AdtCppMemberSpecification& rCopy)
 : AdtCppDeclarationInfo(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppMemberSpecification::~AdtCppMemberSpecification()
{

}

//  ----------------------------------------------------------------------------

void AdtCppMemberSpecification::initialise()
{
  flush();

  enumerateFunctionDefinitions("AdtCppMemberDeclaration,FunctionDefinition", true);
  enumerateVarDefinitions("AdtCppMemberDeclaration,MemberDeclarationList,AdtCppMemberDeclarator,Declarator");
  enumerateEnumSpecifiers("AdtCppMemberDeclaration,EnumSpecifier");
  enumerateClassSpecifiers("AdtCppMemberDeclaration,ClassSpecifier");
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberSpecification::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, "", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberSpecification::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, "", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemberSpecification, AdtCppDeclarationInfo);


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclaration class
//  ----------------------------------------------------------------------------
AdtCppMemberScopeType AdtCppMemberDeclaration::GlobalType = AdtCppMemberScopeType_PUBLIC;

//  ----------------------------------------------------------------------------

AdtCppMemberDeclaration::AdtCppMemberDeclaration(AdtParser* pClassSpecifierObj,
                                                 AdtParser* pEnumSpecifierObj,
                                                 AdtParser* pDeclModifierListObj,
                                                 AdtParser* pSimpleTypeSpecifierObj,
                                                 AdtParser* pMemberDeclarationListObj,
                                                 AdtParser* pFunctionDefinitionObj,
                                                 AdtParser* pUsingDeclarationObj,
                                                 AdtCppMemberScopeType nType,
                                                 bool bHasSemicolon)
 : AdtCppBase()
{
  initObject(ClassSpecifier,        pClassSpecifierObj,         AdtCppClassSpecifier,         false);
  initObject(EnumSpecifier,         pEnumSpecifierObj,          AdtCppEnumSpecifier,          false);
  initObject(DeclModifierList,      pDeclModifierListObj,       AdtCppDeclModifierList,       false);
  initObject(SimpleTypeSpecifier,   pSimpleTypeSpecifierObj,    AdtCppSimpleTypeSpecifier,    false);
  initObject(MemberDeclarationList, pMemberDeclarationListObj,  AdtCppMemberDeclarationList,  false);
  initObject(FunctionDefinition,    pFunctionDefinitionObj,     AdtCppFunctionDefinition,     false);
  initObject(UsingDeclaration,      pUsingDeclarationObj,       AdtCppUsingDeclaration,       false);

  Type          = nType;
  HasSemicolon  = bHasSemicolon;

  if (Type != AdtCppMemberScopeType_NONE)
  {
    AdtCppMemberDeclaration::GlobalType = Type;
  }

  if (AdtAutoClass::automationEnabled())
  {
    // Need to add the types and sizes to the CurrentClass
    AdtAutoClass* pClass = AdtAutoClass::currentClass();

    if (pClass != 0)
    {
      if ((SimpleTypeSpecifier != 0) && (MemberDeclarationList != 0))
      {
        int         nDimensions = 0;
        AdtAutoType nType       = SimpleTypeSpecifier->autoType(nDimensions);

        if (nType != AdtAutoType_UNDEFINED)
        {
          AdtParserPtrListConstIter Iter;
          const AdtParserPtrList&   rIdentList = MemberDeclarationList->objList();

          for (Iter = rIdentList.begin() ; Iter != rIdentList.end() ; ++Iter)
          {
            AdtParser*  pObj = *Iter;

            if (pObj != 0)
            {
              AdtCppEmbeddedComment* pDeclaratorObj = (AdtCppEmbeddedComment*)pObj->findDescendant("Declarator");

              // Only add variables that aren't stack related. Stack vars fail
              // automation dependency checking cos dim_stack isn't defined.
              if (strstr(pDeclaratorObj->name(), "stack") == 0)
              {
                if (nDimensions > 0)
                {
                  AdtStringList rArrayUpperBoundList;
                  AdtStringList rArrayLowerBoundList;

                  pDeclaratorObj->enumerateArraySizes(rArrayUpperBoundList, rArrayLowerBoundList);

                  if ((rArrayLowerBoundList.size() == nDimensions) &&
                      (rArrayUpperBoundList.size() == nDimensions))
                  {
                    AdtAutoArray* pArray = pClass->addArray(pDeclaratorObj->name(),
                                                            nType,
                                                            AdtAutoDir_UNDEFINED,
                                                            nDimensions,
                                                            pDeclaratorObj->fileName(),
                                                            pDeclaratorObj->lineNumber());

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
                  pClass->addScalar(pDeclaratorObj->name(),
                                    nType,
                                    AdtAutoDir_UNDEFINED,
                                    pDeclaratorObj->fileName(),
                                    pDeclaratorObj->lineNumber());
                }
              }
            }
          }
        }
      }
      else if ((FunctionDefinition != 0)                                              &&
               !FunctionDefinition->isCtor()                                          &&
               (AdtCppMemberDeclaration::GlobalType == AdtCppMemberScopeType_PUBLIC)  &&
               (!AdtCppScopeManager::globalScopeManager()->isType(FunctionDefinition->name())))
      {
        // Need to add function declaration
        int               nDimensions = 0;
        AdtAutoType       nReturnType = FunctionDefinition->autoType(nDimensions);
        AdtAutoFunction*  pFunction   = pClass->addFunction(FunctionDefinition->name(),
                                                            nReturnType,
                                                            AdtAutoDir_UNDEFINED,
                                                            FunctionDefinition->fileName(),
                                                            FunctionDefinition->lineNumber());

        if (pFunction != 0)
        {
          AdtParser* pParamDeclList = FunctionDefinition->findDescendant("Declarator,ParameterDeclarationClause,ParameterDeclarationList");

          if (pParamDeclList != 0)
          {
            AdtParserPtrListConstIter ParamDeclIter;
            const AdtParserPtrList&   rParamDeclList = pParamDeclList->objList();

            for (ParamDeclIter = rParamDeclList.begin() ; ParamDeclIter != rParamDeclList.end() ; ++ParamDeclIter)
            {
              const AdtParser* pParameterDeclaration = *ParamDeclIter;

              if (pParameterDeclaration != 0)
              {
                const AdtCppSimpleTypeSpecifier*  pSimpleTypeSpecifier  = (const AdtCppSimpleTypeSpecifier*)pParameterDeclaration->findDescendant("SimpleTypeSpecifier");
                const AdtCppDeclarator*           pDeclarator           = (const AdtCppDeclarator*)pParameterDeclaration->findDescendant("Declarator");
                const AdtCppDeclModifierList*     pModifierList         = (const AdtCppDeclModifierList*)pParameterDeclaration->findDescendant("DeclModifierList");

                if ((pSimpleTypeSpecifier != 0) && (pDeclarator != 0))
                {
                  int         nDimensions = 0;
                  AdtAutoType nType       = pSimpleTypeSpecifier->autoType(nDimensions);
                  AdtAutoDir  nDir        = pSimpleTypeSpecifier->autoDir();

                  if (pModifierList != 0)
                  {
                    nDir = pModifierList->autoDir(nDir);
                  }

                  if (nType != AdtAutoType_UNDEFINED)
                  {
                    if (nDimensions > 0)
                    {
                      AdtStringList rArrayUpperBoundList;
                      AdtStringList rArrayLowerBoundList;

                      pDeclarator->enumerateArraySizes(rArrayUpperBoundList, rArrayLowerBoundList);

                      if ((rArrayLowerBoundList.size() == nDimensions) &&
                          (rArrayUpperBoundList.size() == nDimensions))
                      {
                        AdtAutoArray* pArray = pFunction->addArray(pDeclarator->name(),
                                                                   nType,
                                                                   nDir,
                                                                   nDimensions,
                                                                   pDeclarator->fileName(),
                                                                   pDeclarator->lineNumber());

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
                      pFunction->addScalar(pDeclarator->name(),
                                           nType,
                                           nDir,
                                           pDeclarator->fileName(),
                                           pDeclarator->lineNumber());
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

AdtCppMemberDeclaration::AdtCppMemberDeclaration(const AdtCppMemberDeclaration& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(ClassSpecifier,        rCopy, AdtCppClassSpecifier);
  copyObject(EnumSpecifier,         rCopy, AdtCppEnumSpecifier);
  copyObject(DeclModifierList,      rCopy, AdtCppDeclModifierList);
  copyObject(SimpleTypeSpecifier,   rCopy, AdtCppSimpleTypeSpecifier);
  copyObject(MemberDeclarationList, rCopy, AdtCppMemberDeclarationList);
  copyObject(FunctionDefinition,    rCopy, AdtCppFunctionDefinition);
  copyObject(UsingDeclaration,      rCopy, AdtCppUsingDeclaration);

  Type          = rCopy.Type;
  HasSemicolon  = rCopy.HasSemicolon;
}

//  ----------------------------------------------------------------------------

AdtCppMemberDeclaration::~AdtCppMemberDeclaration()
{
  UtlReleaseReference(ClassSpecifier);
  UtlReleaseReference(EnumSpecifier);
  UtlReleaseReference(DeclModifierList);
  UtlReleaseReference(SimpleTypeSpecifier);
  UtlReleaseReference(MemberDeclarationList);
  UtlReleaseReference(FunctionDefinition);
  UtlReleaseReference(UsingDeclaration);
}

//  ----------------------------------------------------------------------------

bool AdtCppMemberDeclaration::shouldImport(AdtIntByStringMap& rImportMap) const
{
  bool bShouldImport = false;

  if ((FunctionDefinition != 0)     &&
      !FunctionDefinition->isCtor() &&
      (rImportMap.find(FunctionDefinition->name()) == rImportMap.end()))
  {
    rImportMap[FunctionDefinition->name()]  = 1;
    bShouldImport                           = true;
  }

  return (bShouldImport);
}

//  ----------------------------------------------------------------------------

bool AdtCppMemberDeclaration::isCtor() const
{
  bool bIsCtor = ((FunctionDefinition != 0) && FunctionDefinition->isCtor());

  return (bIsCtor);
}

//  ----------------------------------------------------------------------------

bool AdtCppMemberDeclaration::isInlineFunction() const
{
  bool bIsInlineFunction = ((FunctionDefinition != 0) && FunctionDefinition->hasBody());

  return (bIsInlineFunction);
}

//  ----------------------------------------------------------------------------

void AdtCppMemberDeclaration::checkLookForDefinition(AdtStringList& rImportDefinitionList) const
{
  if ((FunctionDefinition != 0) && !FunctionDefinition->hasBody())
  {
    rImportDefinitionList.push_back(FunctionDefinition->name());
  }
}

//  ----------------------------------------------------------------------------

void AdtCppMemberDeclaration::exportFunctionImplementation(AdtCppTranslationUnit* pTarget)
{
  if ((pTarget != 0) && isInlineFunction())
  {
    AdtCppFunctionDefinition* pCopy = (AdtCppFunctionDefinition*)FunctionDefinition->copy();

    if (pCopy != 0)
    {
      pCopy->promoteToFullyQualified();
      pTarget->addFunction(pCopy);

      UtlReleaseReference(pCopy);
    }

    FunctionDefinition->removeFunctionBody();
  }
}

//  ----------------------------------------------------------------------------

void AdtCppMemberDeclaration::updateScope(const AdtCppBaseSpecifier* pBaseSpecifier)
{
  if (pBaseSpecifier != 0)
  {
    Type = pBaseSpecifier->combineScopeType(Type);
  }
}

//  ----------------------------------------------------------------------------

void AdtCppMemberDeclaration::writeFortranDeclaration(AdtFile& rOutFile, const AdtCppDeclarator* pDeclarator) const
{
  if ((pDeclarator != 0) && (SimpleTypeSpecifier != 0))
  {
    SimpleTypeSpecifier->writeFortran(rOutFile, WRITE_MODE_TYPEDECLS);
    pDeclarator->writeFortran(rOutFile, 0);
    SimpleTypeSpecifier->writeArrayBounds(rOutFile, pDeclarator);
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclaration::writeCPP(AdtFile& rOutFile, int nMode) const
{
  const char* pScopeModifier = 0;

  switch (Type)
  {
    case AdtCppMemberScopeType_NONE:
    default:
    {
      break;
    }

    case AdtCppMemberScopeType_PRIVATE:
    {
      pScopeModifier = "private: ";
      break;
    }

    case AdtCppMemberScopeType_PROTECTED:
    {
      pScopeModifier = "protected: ";
      break;
    }

    case AdtCppMemberScopeType_PUBLIC:
    {
      pScopeModifier = "public: ";
      break;
    }
  }

  if (ClassSpecifier != 0)
  {
    ClassSpecifier->writeCPP(rOutFile, nMode);
  }

  if (EnumSpecifier != 0)
  {
    EnumSpecifier->writeCPP(rOutFile, nMode);
  }

  if (pScopeModifier != 0)
  {
    rOutFile.decrementIndent();
    rOutFile.homeline();
    write(rOutFile, pScopeModifier);
    rOutFile.incrementIndent();
    rOutFile.newline();
  }

  if (DeclModifierList != 0)
  {
    DeclModifierList->writeCPP(rOutFile, nMode);
  }

  if (SimpleTypeSpecifier != 0)
  {
    SimpleTypeSpecifier->writeCPP(rOutFile, nMode);
  }

  if (MemberDeclarationList != 0)
  {
    MemberDeclarationList->writeCPP(rOutFile, nMode);
  }

  if (FunctionDefinition != 0)
  {
    FunctionDefinition->writeCPP(rOutFile, nMode);
  }

  if (UsingDeclaration != 0)
  {
    UsingDeclaration->writeCPP(rOutFile, nMode);
  }

  if (HasSemicolon != 0)
  {
    write(rOutFile, ";");
  }

  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemberDeclaration, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclarationList class
//  ----------------------------------------------------------------------------
AdtCppMemberDeclarationList::AdtCppMemberDeclarationList(AdtParser* pMemberDeclaratorObj)
 : AdtCppBase()
{
  add(pMemberDeclaratorObj);
}

//  ----------------------------------------------------------------------------

AdtCppMemberDeclarationList::AdtCppMemberDeclarationList(const AdtCppMemberDeclarationList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppMemberDeclarationList::~AdtCppMemberDeclarationList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclarationList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclarationList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemberDeclarationList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtCppMemberDeclarator::AdtCppMemberDeclarator(AdtParser* pDeclaratorObj,
                                               const char* pIdentifier)
 : AdtCppBase()
{
  initObject(Declarator, pDeclaratorObj, AdtCppDeclarator, false);

  mapName(pIdentifier, true);
}

//  ----------------------------------------------------------------------------

AdtCppMemberDeclarator::AdtCppMemberDeclarator(const AdtCppMemberDeclarator& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(Declarator, rCopy, AdtCppDeclarator);
}

//  ----------------------------------------------------------------------------

AdtCppMemberDeclarator::~AdtCppMemberDeclarator()
{
  UtlReleaseReference(Declarator);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclarator::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (Declarator != 0)
  {
    Declarator->writeCPP(rOutFile, nMode);
  }

  if (name().length() > 0)
  {
    write(rOutFile, " = ");
    write(rOutFile, name());
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemberDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemberDeclarator, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppBaseSpecifierList method implementations
//  ----------------------------------------------------------------------------
AdtCppBaseSpecifierList::AdtCppBaseSpecifierList(AdtParser* pBaseSpecifierObj)
 : AdtCppBase()
{
  add(pBaseSpecifierObj);
}

//  ----------------------------------------------------------------------------

AdtCppBaseSpecifierList::AdtCppBaseSpecifierList(const AdtCppBaseSpecifierList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppBaseSpecifierList::~AdtCppBaseSpecifierList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBaseSpecifierList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBaseSpecifierList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppBaseSpecifierList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppBaseSpecifier method implementations
//  ----------------------------------------------------------------------------
AdtCppBaseSpecifier::AdtCppBaseSpecifier(AdtCppMemberScopeType nType,
                                         bool bVirtual,
                                         bool bQualified,
                                         const char* pIdentifier)
 : AdtCppBase()
{
  Type      = nType;
  Virtual   = bVirtual;
  Qualified = bQualified;

  nameWithComment(pIdentifier);
}

//  ----------------------------------------------------------------------------

AdtCppBaseSpecifier::AdtCppBaseSpecifier(const AdtCppBaseSpecifier& rCopy)
 : AdtCppBase(rCopy)
{
  Type      = rCopy.Type;
  Virtual   = rCopy.Virtual;
  Qualified = rCopy.Qualified;
}

//  ----------------------------------------------------------------------------

AdtCppBaseSpecifier::~AdtCppBaseSpecifier()
{

}

//  ----------------------------------------------------------------------------

AdtCppMemberScopeType AdtCppBaseSpecifier::combineScopeType(AdtCppMemberScopeType nType) const
{
  AdtCppMemberScopeType nResult = AdtCppMemberScopeType_NONE;

  switch(Type)
  {
    default:
    case AdtCppMemberScopeType_NONE:
    case AdtCppMemberScopeType_PUBLIC:
    {
      nResult = nType;
      break;
    }

    case AdtCppMemberScopeType_PRIVATE:
    {
      nResult = AdtCppMemberScopeType_PRIVATE;
      break;
    }

    case AdtCppMemberScopeType_PROTECTED:
    {
      switch(nType)
      {
        default:
        case AdtCppMemberScopeType_NONE:
        case AdtCppMemberScopeType_PROTECTED:
        case AdtCppMemberScopeType_PUBLIC:
        {
          nResult = AdtCppMemberScopeType_PROTECTED;
          break;
        }

        case AdtCppMemberScopeType_PRIVATE:
        {
          nResult = AdtCppMemberScopeType_PRIVATE;
          break;
        }
      }
      break;
    }
  }

  return (nResult);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBaseSpecifier::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (Virtual)
  {
    write(rOutFile, "virtual ");
  }

  switch (Type)
  {
    case AdtCppMemberScopeType_NONE:
    default:
    {
      break;
    }

    case AdtCppMemberScopeType_PRIVATE:
    {
      write(rOutFile, "private ");
      break;
    }

    case AdtCppMemberScopeType_PROTECTED:
    {
      write(rOutFile, "protected ");
      break;
    }

    case AdtCppMemberScopeType_PUBLIC:
    {
      write(rOutFile, "public ");
      break;
    }
  }

  write(rOutFile, name());

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppBaseSpecifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppBaseSpecifier, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppCtorInitializer method implementations
//  ----------------------------------------------------------------------------
AdtCppCtorInitializer::AdtCppCtorInitializer(AdtParser* pMemInitializerListObj)
 : AdtCppBase()
{
  initObject(MemInitializerList, pMemInitializerListObj, AdtCppMemInitializerList, false);
}

//  ----------------------------------------------------------------------------

AdtCppCtorInitializer::AdtCppCtorInitializer(const AdtCppCtorInitializer& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(MemInitializerList, rCopy, AdtCppMemInitializerList);
}

//  ----------------------------------------------------------------------------

AdtCppCtorInitializer::~AdtCppCtorInitializer()
{
  UtlReleaseReference(MemInitializerList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppCtorInitializer::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (MemInitializerList != 0)
  {
    rOutFile.newline();
    write(rOutFile, " : ");

    MemInitializerList->writeCPP(rOutFile, nMode);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppCtorInitializer::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppCtorInitializer, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializerList method implementations
//  ----------------------------------------------------------------------------
AdtCppMemInitializerList::AdtCppMemInitializerList(AdtParser* pMemInitializerObj)
 : AdtCppBase()
{
  add(pMemInitializerObj);
}

//  ----------------------------------------------------------------------------

AdtCppMemInitializerList::AdtCppMemInitializerList(const AdtCppMemInitializerList& rCopy)
 : AdtCppBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtCppMemInitializerList::~AdtCppMemInitializerList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializerList::writeCPP(AdtFile& rOutFile, int nMode) const
{
  forAllWriteCPP(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializerList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  forAllWriteFortran(rOutFile, nMode, ", ", false, true);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemInitializerList, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializer method implementations
//  ----------------------------------------------------------------------------
AdtCppMemInitializer::AdtCppMemInitializer(AdtParser* pMemInitializerIdObj,
                                           AdtParser* pExpressionListObj)
 : AdtCppBase()
{
  initObject(MemInitializerId,  pMemInitializerIdObj, AdtCppMemInitializerId, false);
  initObject(ExpressionList,    pExpressionListObj,   AdtCppExpressionList,   false);
}

//  ----------------------------------------------------------------------------

AdtCppMemInitializer::AdtCppMemInitializer(const AdtCppMemInitializer& rCopy)
 : AdtCppBase(rCopy)
{
  copyObject(MemInitializerId,  rCopy, AdtCppMemInitializerId);
  copyObject(ExpressionList,    rCopy, AdtCppExpressionList);
}

//  ----------------------------------------------------------------------------

AdtCppMemInitializer::~AdtCppMemInitializer()
{
  UtlReleaseReference(MemInitializerId);
  UtlReleaseReference(ExpressionList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializer::writeCPP(AdtFile& rOutFile, int nMode) const
{
  if (MemInitializerId != 0)
  {
    MemInitializerId->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, "(");

  if (ExpressionList != 0)
  {
    ExpressionList->writeCPP(rOutFile, nMode);
  }

  write(rOutFile, ")");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializer::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemInitializer, AdtCppBase);


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializerId method implementations
//  ----------------------------------------------------------------------------
AdtCppMemInitializerId::AdtCppMemInitializerId(bool bQualified,
                                               const char* pIdentifier)
 : AdtCppBase()
{
  nameWithComment(pIdentifier);

  Qualified = bQualified;
}

//  ----------------------------------------------------------------------------

AdtCppMemInitializerId::AdtCppMemInitializerId(const AdtCppMemInitializerId& rCopy)
 : AdtCppBase(rCopy)
{
  Qualified = rCopy.Qualified;
}

//  ----------------------------------------------------------------------------

AdtCppMemInitializerId::~AdtCppMemInitializerId()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializerId::writeCPP(AdtFile& rOutFile, int nMode) const
{
  write(rOutFile, name());

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtCppMemInitializerId::writeFortran(AdtFile& rOutFile, int nMode) const
{
  FAIL();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtCppMemInitializerId, AdtCppBase);
