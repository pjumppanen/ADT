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
//    AdtJava.cpp
//
//  Purpose:
//    This file includes implementation of classes used to collate information
//    describing the Java file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtjava.hpp"


//  ----------------------------------------------------------------------------
//  Defines
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
//  Globals
//  ----------------------------------------------------------------------------
AdtJavaGoal*                               AdtJavaBase::JavaRootObject  = 0;
AdtJavaToFortranTypeConversionByStringMap  AdtJavaBase::FortranTypeMap;
AdtJavaToFortranTypeConversionByStringMap  AdtJavaBase::JavaTypeMap;


//  ----------------------------------------------------------------------------
//  "C" callable function implementations
//  ----------------------------------------------------------------------------
void* adtJava_setRoot(void* pRoot)
{
  AdtJavaBase::javaRootObject(Obj(pRoot));

  return (pRoot);
}

//  ----------------------------------------------------------------------------

void* adtJava_getRoot(void)
{
  return (Hnd(AdtJavaBase::javaRootObject()));
}

//  ----------------------------------------------------------------------------

void adtJava_releaseRoot(void)
{
  AdtJavaBase::javaRootObject(0);
}

//  ----------------------------------------------------------------------------

void adtJava_releaseObject(void* pObj)
{
  UtlReleaseReference(Obj(pObj));
}

//  ----------------------------------------------------------------------------

void* adtJavaList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtJavaGoal_Create(void* pPackageDeclarationObj, void* pImportDeclarationsObj, void* pTypeDeclarationsObj)
{
  return (Hnd(new AdtJavaGoal(ObjAndRelease(pPackageDeclarationObj),ObjAndRelease(pImportDeclarationsObj),ObjAndRelease(pTypeDeclarationsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaLiteral_Create(const char* pLiteral, int nType)
{
  return (Hnd(new AdtJavaLiteral(pLiteral,(AdtJavaLiteralEnum)nType)));
}

//  ----------------------------------------------------------------------------

void* adtJavaType_Create(void* pNameObj, void* pPrimitiveTypeObj, void* pArrayTypeObj, int nIsArray)
{
  return (Hnd(new AdtJavaType(ObjAndRelease(pNameObj),ObjAndRelease(pPrimitiveTypeObj),ObjAndRelease(pArrayTypeObj), (nIsArray != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPrimitiveType_Create(int nType)
{
  return (Hnd(new AdtJavaPrimitiveType((AdtJavaPrimitiveEnum)nType)));
}

//  ----------------------------------------------------------------------------

void* adtJavaName(void* pNameObj, const char* pIdentifier, int nIsCpp)
{
  return (Hnd(new AdtJavaName(ObjAndRelease(pNameObj),pIdentifier,(nIsCpp != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaNameList(void* pNameObj)
{
  return (Hnd(new AdtJavaNameList(ObjAndRelease(pNameObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaImportDeclarations(void* pImportDeclarationObj)
{
  return (Hnd(new AdtJavaImportDeclarations(ObjAndRelease(pImportDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaImportDeclaration(void* pNameObj, int nHasPeriodMultiply)
{
  return (Hnd(new AdtJavaImportDeclaration(ObjAndRelease(pNameObj), (nHasPeriodMultiply != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaTypeDeclarations(void* pTypeDeclarationObj)
{
  return (Hnd(new AdtJavaTypeDeclarations(ObjAndRelease(pTypeDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaTypeDeclaration(void* pClassDeclarationObj, void* pInterfaceDeclarationObj)
{
  return (Hnd(new AdtJavaTypeDeclaration(ObjAndRelease(pClassDeclarationObj), ObjAndRelease(pInterfaceDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPackageDeclaration(void* pNameObj)
{
  return (Hnd(new AdtJavaPackageDeclaration(ObjAndRelease(pNameObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaModifiers(void* pModifierObj)
{
  return (Hnd(new AdtJavaModifiers(ObjAndRelease(pModifierObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaModifier(int nModifier)
{
  return (Hnd(new AdtJavaModifier((AdtJavaModifierEnum)nModifier)));
}

//  ----------------------------------------------------------------------------

void* adtJavaClassDeclaration(const char* pIdentifier, void* pModifiersObj, void* pNameObj, void* pNameListObj, void* pClassBodyDeclarationsObj)
{
  return (Hnd(new AdtJavaClassDeclaration(pIdentifier, ObjAndRelease(pModifiersObj), ObjAndRelease(pNameObj), ObjAndRelease(pNameListObj), ObjAndRelease(pClassBodyDeclarationsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaClassBodyDeclarations(void* pClassBodyDeclarationObj)
{
  return (Hnd(new AdtJavaClassBodyDeclarations(ObjAndRelease(pClassBodyDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaClassBodyDeclaration(void* pClassMemberDeclarationObj, void* pBlockObj, void* pConstructorDeclarationObj)
{
  return (Hnd(new AdtJavaClassBodyDeclaration(ObjAndRelease(pClassMemberDeclarationObj), ObjAndRelease(pBlockObj), ObjAndRelease(pConstructorDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaClassMemberDeclaration(void* pFieldDeclarationObj, void* pMethodHeaderObj, void* pBlockObj)
{
  return (Hnd(new AdtJavaClassMemberDeclaration(ObjAndRelease(pFieldDeclarationObj), ObjAndRelease(pMethodHeaderObj), ObjAndRelease(pBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaFieldDeclaration(void* pModifiersObj, void* pTypeObj, void* pVariableDeclaratorsObj)
{
  return (Hnd(new AdtJavaFieldDeclaration(ObjAndRelease(pModifiersObj), ObjAndRelease(pTypeObj), ObjAndRelease(pVariableDeclaratorsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaVariableDeclarators(void* pVariableDeclaratorObj)
{
  return (Hnd(new AdtJavaVariableDeclarators(ObjAndRelease(pVariableDeclaratorObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaVariableDeclarator(void* pVariableDeclaratorIdObj, void* pExpressionObj, void* pVariableInitializersObj, int nHasComma, int nHasBracket)
{
  return (Hnd(new AdtJavaVariableDeclarator(ObjAndRelease(pVariableDeclaratorIdObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pVariableInitializersObj), (nHasComma != 0), (nHasBracket != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaVariableDeclaratorId(const char* pIdentifier, void* pVariableDeclaratorIdObj)
{
  return (Hnd(new AdtJavaVariableDeclaratorId(pIdentifier, ObjAndRelease(pVariableDeclaratorIdObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaMethodHeader(void* pModifiersObj, void* pTypeObj, void* pMethodDeclaratorObj, void* pNameListObj)
{
  return (Hnd(new AdtJavaMethodHeader(ObjAndRelease(pModifiersObj),ObjAndRelease(pTypeObj),ObjAndRelease(pMethodDeclaratorObj),ObjAndRelease(pNameListObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaMethodDeclarator(const char* pIdentifier, void* pFormalParameterListObj, void* pMethodDeclaratorObj)
{
  return (Hnd(new AdtJavaMethodDeclarator(pIdentifier, ObjAndRelease(pFormalParameterListObj),ObjAndRelease(pMethodDeclaratorObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaFormalParameterList(void* pFormalParameterObj)
{
  return (Hnd(new AdtJavaFormalParameterList(ObjAndRelease(pFormalParameterObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaFormalParameter(void* pTypeObj, void* pVariableDeclaratorIdObj)
{
  return (Hnd(new AdtJavaFormalParameter(ObjAndRelease(pTypeObj), ObjAndRelease(pVariableDeclaratorIdObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConstructorDeclaration(void* pModifiersObj, void* pConstructorDeclaratorObj, void* pNameListObj, void* pConstructorBodyObj)
{
  return (Hnd(new AdtJavaConstructorDeclaration(ObjAndRelease(pModifiersObj),ObjAndRelease(pConstructorDeclaratorObj),ObjAndRelease(pNameListObj),ObjAndRelease(pConstructorBodyObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConstructorDeclarator(const char* pIdentifier, void* pFormalParameterListObj)
{
  return (Hnd(new AdtJavaConstructorDeclarator(pIdentifier, ObjAndRelease(pFormalParameterListObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConstructorBody(void* pBlockObj)
{
  return (Hnd(new AdtJavaConstructorBody(ObjAndRelease(pBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaExplicitConstructorInvocation(void* pArgumentListObj, int nIsSuper)
{
  return (Hnd(new AdtJavaExplicitConstructorInvocation(ObjAndRelease(pArgumentListObj), (nIsSuper != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaInterfaceDeclaration(const char* pIdentifier, void* pModifiersObj, void* pExtendsInterfacesObj, void* pInterfaceMemberDeclarationsObj)
{
  return (Hnd(new AdtJavaInterfaceDeclaration(pIdentifier, ObjAndRelease(pModifiersObj), ObjAndRelease(pExtendsInterfacesObj), ObjAndRelease(pInterfaceMemberDeclarationsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaExtendsInterfaces(void* pNameObj, void* pExtendsInterfacesObj)
{
  return (Hnd(new AdtJavaExtendsInterfaces(ObjAndRelease(pNameObj), ObjAndRelease(pExtendsInterfacesObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaInterfaceMemberDeclarations(void* pInterfaceMemberDeclarationObj)
{
  return (Hnd(new AdtJavaInterfaceMemberDeclarations(ObjAndRelease(pInterfaceMemberDeclarationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaInterfaceMemberDeclaration(void* pFieldDeclarationObj, void* pMethodHeaderObj)
{
  return (Hnd(new AdtJavaInterfaceMemberDeclaration(ObjAndRelease(pFieldDeclarationObj),ObjAndRelease(pMethodHeaderObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaVariableInitializers(void* pVariableInitializerObj)
{
  return (Hnd(new AdtJavaVariableInitializers(ObjAndRelease(pVariableInitializerObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaVariableInitializer(void* pExpressionObj, void* pVariableInitializersObj, int nWithComma)
{
  return (Hnd(new AdtJavaVariableInitializer(ObjAndRelease(pExpressionObj),ObjAndRelease(pVariableInitializersObj), (nWithComma != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaBlock(void* pBlockStatementsObj, void* pExplicitConstructorInvocationObj)
{
  return (Hnd(new AdtJavaBlock(ObjAndRelease(pBlockStatementsObj), ObjAndRelease(pExplicitConstructorInvocationObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaBlockStatements(void* pBlockStatementObj)
{
  return (Hnd(new AdtJavaBlockStatements(ObjAndRelease(pBlockStatementObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaBlockStatement(void* pTypeObj, void* pVariableDeclaratorsObj, void* pStatementObj)
{
  return (Hnd(new AdtJavaBlockStatement(ObjAndRelease(pTypeObj),ObjAndRelease(pVariableDeclaratorsObj),ObjAndRelease(pStatementObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaStatement(const char* pIdentifier, void* pStatementWithoutTrailingSubstatementObj, void* pStatementObj, void* pIfThenStatementObj, void* pIfThenElseStatementObj, void* pWhileStatementObj, void* pForStatementObj, int nNoShortIf)
{
  return (Hnd(new AdtJavaStatement(pIdentifier, ObjAndRelease(pStatementWithoutTrailingSubstatementObj),ObjAndRelease(pStatementObj),ObjAndRelease(pIfThenStatementObj),ObjAndRelease(pIfThenElseStatementObj),ObjAndRelease(pWhileStatementObj),ObjAndRelease(pForStatementObj),(nNoShortIf != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaStatementWithoutTrailingSubstatement(void* pBlockObj, void* pStatementExpressionObj, void* pSwitchStatementObj, void* pDoStatementObj, void* pBreakStatementObj, void* pContinueStatementObj, void* pReturnStatementObj, void* pSynchronizedStatementObj, void* pThrowStatementObj, void* pTryStatementObj, int nHasSemiColon)
{
  return (Hnd(new AdtJavaStatementWithoutTrailingSubstatement(ObjAndRelease(pBlockObj),ObjAndRelease(pStatementExpressionObj),ObjAndRelease(pSwitchStatementObj),ObjAndRelease(pDoStatementObj),ObjAndRelease(pBreakStatementObj),ObjAndRelease(pContinueStatementObj),ObjAndRelease(pReturnStatementObj),ObjAndRelease(pSynchronizedStatementObj),ObjAndRelease(pThrowStatementObj),ObjAndRelease(pTryStatementObj),(nHasSemiColon != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaStatementExpression(void* pAssignmentObj, void* pPreIncDecExpressionObj, void* pPostIncDecExpressionObj, void* pMethodInvocationObj, void* pClassInstanceCreationExpressionObj)
{
  return (Hnd(new AdtJavaStatementExpression(ObjAndRelease(pAssignmentObj),ObjAndRelease(pPreIncDecExpressionObj),ObjAndRelease(pPostIncDecExpressionObj),ObjAndRelease(pMethodInvocationObj),ObjAndRelease(pClassInstanceCreationExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaIfThenStatement(void* pExpressionObj, void* pStatementObj)
{
  return (Hnd(new AdtJavaIfThenStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pStatementObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaIfThenElseStatement(void* pExpressionObj, void* pStatementNoShortIfObj, void* pStatementObj, int nNoShortIf)
{
  return (Hnd(new AdtJavaIfThenElseStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pStatementNoShortIfObj),ObjAndRelease(pStatementObj), (nNoShortIf != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchStatement(void* pExpressionObj, void* pSwitchBlockObj)
{
  return (Hnd(new AdtJavaSwitchStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pSwitchBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchBlock(void* pSwitchLabelsObj, void* pSwitchBlockStatementGroupsObj)
{
  return (Hnd(new AdtJavaSwitchBlock(ObjAndRelease(pSwitchLabelsObj),ObjAndRelease(pSwitchBlockStatementGroupsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchBlockStatementGroups(void* pSwitchBlockStatementGroupObj)
{
  return (Hnd(new AdtJavaSwitchBlockStatementGroups(ObjAndRelease(pSwitchBlockStatementGroupObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchBlockStatementGroup(void* pSwitchLabelsObj, void* pBlockStatementsObj)
{
  return (Hnd(new AdtJavaSwitchBlockStatementGroup(ObjAndRelease(pSwitchLabelsObj),ObjAndRelease(pBlockStatementsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchLabels(void* pSwitchLabelObj)
{
  return (Hnd(new AdtJavaSwitchLabels(ObjAndRelease(pSwitchLabelObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSwitchLabel(void* pExpressionObj)
{
  return (Hnd(new AdtJavaSwitchLabel(ObjAndRelease(pExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaWhileStatement(void* pExpressionObj, void* pStatementObj, int nNoShortIf)
{
  return (Hnd(new AdtJavaWhileStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pStatementObj),(nNoShortIf != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaDoStatement(void* pExpressionObj, void* pStatementObj)
{
  return (Hnd(new AdtJavaDoStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pStatementObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaForStatement(void* pForInitObj, void* pExpressionObj, void* pStatementExpressionListObj, void* pStatementObj, int nNoShortIf)
{
  return (Hnd(new AdtJavaForStatement(ObjAndRelease(pForInitObj),ObjAndRelease(pExpressionObj),ObjAndRelease(pStatementExpressionListObj),ObjAndRelease(pStatementObj), (nNoShortIf != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaForInit(void* pTypeObj, void* pStatementExpressionListObj, void* pVariableDeclaratorsObj)
{
  return (Hnd(new AdtJavaForInit(ObjAndRelease(pTypeObj),ObjAndRelease(pStatementExpressionListObj),ObjAndRelease(pVariableDeclaratorsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaStatementExpressionList(void* pStatementExpressionObj)
{
  return (Hnd(new AdtJavaStatementExpressionList(ObjAndRelease(pStatementExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaBreakStatement(const char* pIdentifier)
{
  return (Hnd(new AdtJavaBreakStatement(pIdentifier)));
}

//  ----------------------------------------------------------------------------

void* adtJavaContinueStatement(const char* pIdentifier)
{
  return (Hnd(new AdtJavaContinueStatement(pIdentifier)));
}

//  ----------------------------------------------------------------------------

void* adtJavaReturnStatement(void* pExpressionObj)
{
  return (Hnd(new AdtJavaReturnStatement(ObjAndRelease(pExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaThrowStatement(void* pExpressionObj)
{
  return (Hnd(new AdtJavaThrowStatement(ObjAndRelease(pExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaSynchronizedStatement(void* pExpressionObj, void* pBlockObj)
{
  return (Hnd(new AdtJavaSynchronizedStatement(ObjAndRelease(pExpressionObj),ObjAndRelease(pBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaTryStatement(void* pBlockObj, void* pCatchesObj, void* pFinallyObj)
{
  return (Hnd(new AdtJavaTryStatement(ObjAndRelease(pBlockObj),ObjAndRelease(pCatchesObj),ObjAndRelease(pFinallyObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaCatches(void* pCatchClauseObj)
{
  return (Hnd(new AdtJavaCatches(ObjAndRelease(pCatchClauseObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaCatchClause(void* pFormalParameterObj, void* pBlockObj)
{
  return (Hnd(new AdtJavaCatchClause(ObjAndRelease(pFormalParameterObj), ObjAndRelease(pBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaFinally(void* pBlockObj)
{
  return (Hnd(new AdtJavaFinally(ObjAndRelease(pBlockObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPrimary(void* pPrimaryNoNewArrayObj, void* pPrimitiveTypeObj, void* pDimExprsObj, void* pDimsObj, void* pNameObj)
{
  return (Hnd(new AdtJavaPrimary(ObjAndRelease(pPrimaryNoNewArrayObj), ObjAndRelease(pPrimitiveTypeObj), ObjAndRelease(pDimExprsObj), ObjAndRelease(pDimsObj), ObjAndRelease(pNameObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPrimaryNoNewArray(const char* pIdentifier, void* pLiteralObj, void* pExpressionObj, void* pClassInstanceCreationExpressionObj, void* pPrimaryObj, void* pMethodInvocationObj, void* pNameObj, void* pPrimaryNoNewArrayObj, int nIsSuper)
{
  return (Hnd(new AdtJavaPrimaryNoNewArray(pIdentifier, ObjAndRelease(pLiteralObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pClassInstanceCreationExpressionObj), ObjAndRelease(pPrimaryObj), ObjAndRelease(pMethodInvocationObj), ObjAndRelease(pNameObj), ObjAndRelease(pPrimaryNoNewArrayObj), (nIsSuper != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaClassInstanceCreationExpression(void* pNameObj, void* pArgumentListObj)
{
  return (Hnd(new AdtJavaClassInstanceCreationExpression(ObjAndRelease(pNameObj), ObjAndRelease(pArgumentListObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaArgumentList(void* pExpressionObj)
{
  return (Hnd(new AdtJavaArgumentList(ObjAndRelease(pExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaDimExprs(void* pDimExprObj)
{
  return (Hnd(new AdtJavaDimExprs(ObjAndRelease(pDimExprObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaDimExpr(void* pExpressionObj)
{
  return (Hnd(new AdtJavaDimExpr(ObjAndRelease(pExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaDims(void* pDimsObj)
{
  return (Hnd(new AdtJavaDims(ObjAndRelease(pDimsObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaMethodInvocation(const char* pIdentifier, void* pNameObj, void* pPrimaryObj, void* pArgumentListObj)
{
  return (Hnd(new AdtJavaMethodInvocation(pIdentifier, ObjAndRelease(pNameObj), ObjAndRelease(pPrimaryObj), ObjAndRelease(pArgumentListObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPostfixExpression(void* pNameObj, void* pPrimaryObj, void* pPostIncDecExpressionObj)
{
  return (Hnd(new AdtJavaPostfixExpression(ObjAndRelease(pNameObj), ObjAndRelease(pPrimaryObj), ObjAndRelease(pPostIncDecExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPostIncDecExpression(void* pPostfixExpressionObj, int nIncrement)
{
  return (Hnd(new AdtJavaPostIncDecExpression(ObjAndRelease(pPostfixExpressionObj), (nIncrement != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaPreIncDecExpression(void* pUnaryExpressionObj, int nIncrement)
{
  return (Hnd(new AdtJavaPreIncDecExpression(ObjAndRelease(pUnaryExpressionObj), (nIncrement != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaUnaryExpression(void* pPreIncDecExpressionObj, void* pUnaryExpressionObj, void* pUnaryExpressionNotPlusMinusObj, int nIsPlus)
{
  return (Hnd(new AdtJavaUnaryExpression(ObjAndRelease(pPreIncDecExpressionObj), ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pUnaryExpressionNotPlusMinusObj), (nIsPlus != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaUnaryExpressionNotPlusMinus(void* pPostfixExpressionObj, void* pUnaryExpressionObj, void* pCastExpressionObj, int nLogical)
{
  return (Hnd(new AdtJavaUnaryExpressionNotPlusMinus(ObjAndRelease(pPostfixExpressionObj), ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pCastExpressionObj), (nLogical != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaCastExpression(void* pPrimitiveTypeObj, void* pUnaryExpressionObj, void* pUnaryExpressionNotPlusMinusObj, void* pExpressionObj, void* pDimsObj, void* pNameObj)
{
  return (Hnd(new AdtJavaCastExpression(ObjAndRelease(pPrimitiveTypeObj), ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pUnaryExpressionNotPlusMinusObj),ObjAndRelease(pExpressionObj),ObjAndRelease(pDimsObj),ObjAndRelease(pNameObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaMultiplicativeExpression(void* pUnaryExpressionObj, void* pMultiplicativeExpressionObj, int nOp)
{
  return (Hnd(new AdtJavaMultiplicativeExpression(ObjAndRelease(pUnaryExpressionObj), ObjAndRelease(pMultiplicativeExpressionObj), (AdtJavaMultOpEnum)nOp)));
}

//  ----------------------------------------------------------------------------

void* adtJavaAdditiveExpression(void* pMultiplicativeExpressionObj, void* pAdditiveExpressionObj, int nOp)
{
  return (Hnd(new AdtJavaAdditiveExpression(ObjAndRelease(pMultiplicativeExpressionObj), ObjAndRelease(pAdditiveExpressionObj), (AdtJavaAddOpEnum)nOp)));
}

//  ----------------------------------------------------------------------------

void* adtJavaShiftExpression(void* pAdditiveExpressionObj, void* pShiftExpressionObj, int nOp)
{
  return (Hnd(new AdtJavaShiftExpression(ObjAndRelease(pAdditiveExpressionObj), ObjAndRelease(pShiftExpressionObj), (AdtJavaShiftOpEnum)nOp)));
}

//  ----------------------------------------------------------------------------

void* adtJavaRelationalExpression(void* pShiftExpressionObj, void* pRelationalExpressionObj, void* pNameObj, void* pArrayTypeObj, int nOp)
{
  return (Hnd(new AdtJavaRelationalExpression(ObjAndRelease(pShiftExpressionObj), ObjAndRelease(pRelationalExpressionObj), ObjAndRelease(pNameObj), ObjAndRelease(pArrayTypeObj), (AdtJavaRelOpEnum)nOp)));
}

//  ----------------------------------------------------------------------------

void* adtJavaEqualityExpression(void* pRelationalExpressionObj, void* pEqualityExpressionObj, int nOp)
{
  return (Hnd(new AdtJavaEqualityExpression(ObjAndRelease(pRelationalExpressionObj), ObjAndRelease(pEqualityExpressionObj), (AdtJavaEqualityOpEnum)nOp)));
}

//  ----------------------------------------------------------------------------

void* adtJavaAndExpression(void* pEqualityExpressionObj, void* pAndExpressionObj)
{
  return (Hnd(new AdtJavaAndExpression(ObjAndRelease(pEqualityExpressionObj), ObjAndRelease(pAndExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaExclusiveOrExpression(void* pAndExpressionObj, void* pExclusiveOrExpressionObj)
{
  return (Hnd(new AdtJavaExclusiveOrExpression(ObjAndRelease(pAndExpressionObj), ObjAndRelease(pExclusiveOrExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaInclusiveOrExpression(void* pExclusiveOrExpressionObj, void* pInclusiveOrExpressionObj)
{
  return (Hnd(new AdtJavaInclusiveOrExpression(ObjAndRelease(pExclusiveOrExpressionObj), ObjAndRelease(pInclusiveOrExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConditionalAndExpression(void* pInclusiveOrExpressionObj, void* pConditionalAndExpressionObj)
{
  return (Hnd(new AdtJavaConditionalAndExpression(ObjAndRelease(pInclusiveOrExpressionObj), ObjAndRelease(pConditionalAndExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConditionalOrExpression(void* pConditionalAndExpressionObj, void* pConditionalOrExpressionObj)
{
  return (Hnd(new AdtJavaConditionalOrExpression(ObjAndRelease(pConditionalAndExpressionObj), ObjAndRelease(pConditionalOrExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaConditionalExpression(void* pConditionalOrExpressionObj, void* pExpressionObj, void* pConditionalExpressionObj)
{
  return (Hnd(new AdtJavaConditionalExpression(ObjAndRelease(pConditionalOrExpressionObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pConditionalExpressionObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaExpression(void* pConditionalExpressionObj, void* pAssignmentObj)
{
  return (Hnd(new AdtJavaExpression(ObjAndRelease(pConditionalExpressionObj), ObjAndRelease(pAssignmentObj))));
}

//  ----------------------------------------------------------------------------

void* adtJavaAssignment(const char* pIdentifier, void* pNameObj, void* pAssignmentOperatorObj, void* pExpressionObj, void* pPrimaryObj, void* pPrimaryNoNewArrayObj, void* pExpression2Obj, int nIsSuper)
{
  return (Hnd(new AdtJavaAssignment(pIdentifier, ObjAndRelease(pNameObj), ObjAndRelease(pAssignmentOperatorObj), ObjAndRelease(pExpressionObj), ObjAndRelease(pPrimaryObj), ObjAndRelease(pPrimaryNoNewArrayObj), ObjAndRelease(pExpression2Obj), (nIsSuper != 0))));
}

//  ----------------------------------------------------------------------------

void* adtJavaAssignmentOperator(int nOp)
{
  return (Hnd(new AdtJavaAssignmentOperator((AdtJavaAssignmentOpEnum)nOp)));
}


//  ----------------------------------------------------------------------------
//  AdtJavaToFortranTypeConversion method implementations
//  ----------------------------------------------------------------------------
void AdtJavaToFortranTypeConversion::initialise()
{
  const char*   pString;
  int           nSize = ::atoi(FortranDimension.c_str());

  switch (nSize)
  {
    default:
    case 0:
    {
      pString = "";
      break;
    }

    case 1:
    {
      pString = "(:)";
      break;
    }

    case 2:
    {
      pString = "(:,:)";
      break;
    }

    case 3:
    {
      pString = "(:,:,:)";
      break;
    }

    case 4:
    {
      pString = "(:,:,:,:)";
      break;
    }
  }

  FortranDimensionString = pString;
}


//  ----------------------------------------------------------------------------
//  AdtJavaBase method implementations
//  ----------------------------------------------------------------------------
AdtFile& AdtJavaBase::forAllWriteFortran(AdtFile& rOutFile, int nMode, const char* pDelimiter, bool bNewline, bool bExcludeLast, const char* pSuffix) const
{
  if (rOutFile.isOpen())
  {
    AdtParserPtrListConstIter     Iter;
    size_t                        nSize = objList().size();
    size_t                        cn    = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtJavaBase"))
      {
        AdtJavaBase* pDelphiObj = (AdtJavaBase*)pObj;

        pDelphiObj->writeFortran(rOutFile, nMode);

        if (pSuffix != 0)
        {
          write(rOutFile, pSuffix);
        }

        if (bExcludeLast && (cn == nSize))
        {
          //Do nothing
        }
        else
        {
          write(rOutFile, pDelimiter);

          if (bNewline)
          {
            rOutFile.newline();
          }
        }
      }
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBase::forAllWriteJava(AdtFile& rOutFile, const char* pDelimiter, bool bNewline, bool bExcludeLast) const
{
  if (rOutFile.isOpen())
  {
    AdtParserPtrListConstIter     Iter;
    size_t                        nSize = objList().size();
    size_t                        cn    = 0;

    for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      cn++;

      if ((pObj != 0) && pObj->isType("AdtJavaBase"))
      {
        AdtJavaBase* pDelphiObj = (AdtJavaBase*)pObj;

        pDelphiObj->writeJava(rOutFile);

        if (bExcludeLast && (cn == nSize))
        {
          //Do nothing
        }
        else
        {
          write(rOutFile, pDelimiter);

          if (bNewline)
          {
            rOutFile.newline();
          }
        }
      }
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtJavaBase::AdtJavaBase()
 : AdtParser()
{

}

//  ----------------------------------------------------------------------------

AdtJavaBase::~AdtJavaBase()
{
  flush();
}

//  ----------------------------------------------------------------------------

void AdtJavaBase::rootBindComments(AdtCommon* pCompilerBase)
{
  if (JavaRootObject != 0)
  {
    JavaRootObject->bindComments(pCompilerBase);
  }
}

//  ----------------------------------------------------------------------------

void AdtJavaBase::addFortranTypeMap(const string& rJavaType,
                                    const string& rFortranType,
                                    const string& rFortranSize)
{
  FortranTypeMap.insert(AdtJavaToFortranTypeConversionStringPair(rJavaType, AdtJavaToFortranTypeConversion(rJavaType, rFortranType, rFortranSize)));
  JavaTypeMap.insert(AdtJavaToFortranTypeConversionStringPair(rFortranType + rFortranSize, AdtJavaToFortranTypeConversion(rJavaType, rFortranType, rFortranSize)));
}

//  ----------------------------------------------------------------------------

void AdtJavaBase::javaRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(JavaRootObject);

  JavaRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtJavaGoal"))
    {
      JavaRootObject = (AdtJavaGoal*)pRoot;
      JavaRootObject->lock();
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtJavaGoal* AdtJavaBase::javaRootObject()
{
  return (JavaRootObject);
}

//  ----------------------------------------------------------------------------

bool AdtJavaBase::mapTypesToFortran(const char* pTypeName,
                                    const char*& pType,
                                    const char*& pDimension)
{
  bool                                                bFound  = false;
  AdtJavaToFortranTypeConversionByStringMapConstIter   Iter    = FortranTypeMap.find(pTypeName);

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

bool AdtJavaBase::mapTypesToJava(const char* pTypeName,
                               int nDimension,
                               const char*& pType)
{
  char  pDimension[16] = {0};

  ::sprintf(pDimension, "%d", nDimension);

  bool                                                bFound        = false;
  string                                              sTypeAndSize  = string(pTypeName) + pDimension;
  AdtJavaToFortranTypeConversionByStringMapConstIter   Iter          = JavaTypeMap.find(sTypeAndSize);

  if (Iter != JavaTypeMap.end())
  {
    pType       = (*Iter).second.JavaType;
    bFound      = true;
  }
  else
  {
    pType       = 0;
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtJavaGoal method implementations
//  ----------------------------------------------------------------------------
AdtJavaGoal::AdtJavaGoal(AdtParser* pPackageDeclarationObj,
                         AdtParser* pImportDeclarationsObj,
                         AdtParser* pTypeDeclarationsObj)
 : AdtJavaBase(),
   AdtSourceRoot()
{
  initObject(PackageDeclaration,  pPackageDeclarationObj, AdtJavaPackageDeclaration,  false);
  initObject(ImportDeclarations,  pImportDeclarationsObj, AdtJavaImportDeclarations,  false);
  initObject(TypeDeclarations,    pTypeDeclarationsObj,   AdtJavaTypeDeclarations,    false);

  depth(0, true);
}

//  ----------------------------------------------------------------------------

AdtJavaGoal::AdtJavaGoal(const AdtJavaGoal& rCopy)
 : AdtJavaBase(rCopy),
   AdtSourceRoot(rCopy)
{
  copyObject(PackageDeclaration,  rCopy, AdtJavaPackageDeclaration);
  copyObject(ImportDeclarations,  rCopy, AdtJavaImportDeclarations);
  copyObject(TypeDeclarations,    rCopy, AdtJavaTypeDeclarations);
}

//  ----------------------------------------------------------------------------

AdtJavaGoal::~AdtJavaGoal()
{
  UtlReleaseReference(PackageDeclaration);
  UtlReleaseReference(ImportDeclarations);
  UtlReleaseReference(TypeDeclarations);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaGoal::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaGoal::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

void AdtJavaGoal::enumerateMethodNames(AdtStringList& rMethodList) const
{

}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::hasClass(const char* pClassName,
                           string& rParentClassName) const
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::buildBlackBoxFile(const char* pBlackBoxFileName,
                                    AdtStringByStringMap& rRegardAsClassFunctionMap,
                                    AdtStringByStringMap& rRegardAsClassSubroutineMap,
                                    double dVersionNumber)
{
  bool bBuilt = false;

  return (bBuilt);
}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::flattenClass(const char* pClassName,
                               const AdtParserPtrList& rRootList,
                               string& rUsesList)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::optimise(const AdtStringList& rNewMethodList,
                           const AdtStringByStringMap& rNewMethodMap)
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::expandMacros()
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtJavaGoal::extractClassConstructors(AdtStringList& rConstructorList,
                                           const char* pClassName,
                                           const char* pParentClassName,
                                           const char* pPathPrefix,
                                           AdtSourceFileType nAsFileType) const
{
  return (false);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaGoal::writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                 const AdtFortranExecutableProgram* pSavedRoot,
                                                 const char* pClassName,
                                                 const char* pLastClassName,
                                                 bool bExpandMacros) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaGoal::writeNative(AdtFile& rOutFile) const
{
  return (writeJava(rOutFile));
}

//  ----------------------------------------------------------------------------

AdtSourceFileType AdtJavaGoal::sourceFileType() const
{
  return (JavaSourceFileType);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaGoal, AdtJavaBase);



//  ----------------------------------------------------------------------------
//  AdtJavaLiteral method implementations
//  ----------------------------------------------------------------------------
AdtJavaLiteral::AdtJavaLiteral(const char* pLiteral, AdtJavaLiteralEnum nType)
 : AdtJavaBase()
{
  name(pLiteral);

  LiteralType = nType;
}

//  ----------------------------------------------------------------------------

AdtJavaLiteral::AdtJavaLiteral(const AdtJavaLiteral& rCopy)
 : AdtJavaBase(rCopy)
{
  LiteralType = rCopy.LiteralType;
}

//  ----------------------------------------------------------------------------

AdtJavaLiteral::~AdtJavaLiteral()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaLiteral::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaLiteral::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaLiteral, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaType method implementations
//  ----------------------------------------------------------------------------
AdtJavaType::AdtJavaType(AdtParser* pNameObj,
                         AdtParser* pPrimitiveTypeObj,
                         AdtParser* pArrayTypeObj,
                         bool bIsArray)
 : AdtJavaBase()
{
  IsArray = bIsArray;

  initObject(Name,          pNameObj,          AdtJavaName,          false);
  initObject(PrimitiveType, pPrimitiveTypeObj, AdtJavaPrimitiveType, false);
  initObject(ArrayType,     pArrayTypeObj,     AdtJavaType,          false);
}

//  ----------------------------------------------------------------------------

AdtJavaType::AdtJavaType(const AdtJavaType& rCopy)
 : AdtJavaBase(rCopy)
{
  IsArray = rCopy.IsArray;

  copyObject(Name,          rCopy, AdtJavaName);
  copyObject(PrimitiveType, rCopy, AdtJavaPrimitiveType);
  copyObject(ArrayType,     rCopy, AdtJavaType);
}

//  ----------------------------------------------------------------------------

AdtJavaType::~AdtJavaType()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(PrimitiveType);
  UtlReleaseReference(ArrayType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaType::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaType::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaType, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPrimitiveType method implementations
//  ----------------------------------------------------------------------------
AdtJavaPrimitiveType::AdtJavaPrimitiveType(AdtJavaPrimitiveEnum nType)
 : AdtJavaBase()
{
  Type = nType;
}

//  ----------------------------------------------------------------------------

AdtJavaPrimitiveType::AdtJavaPrimitiveType(const AdtJavaPrimitiveType& rCopy)
 : AdtJavaBase(rCopy)
{
  Type = rCopy.Type;
}

//  ----------------------------------------------------------------------------

AdtJavaPrimitiveType::~AdtJavaPrimitiveType()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimitiveType::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimitiveType::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPrimitiveType, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaName method implementations
//  ----------------------------------------------------------------------------
AdtJavaName::AdtJavaName(AdtParser* pNameObj,
                         const char* pIdentifier,
                         bool bIsCpp)
 : AdtJavaBase()
{
  name(pIdentifier);

  IsCpp = bIsCpp;

  initObject(Name, pNameObj, AdtJavaName, false);
}

//  ----------------------------------------------------------------------------

AdtJavaName::AdtJavaName(const AdtJavaName& rCopy)
 : AdtJavaBase(rCopy)
{
  IsCpp = rCopy.IsCpp;

  copyObject(Name, rCopy, AdtJavaName);
}

//  ----------------------------------------------------------------------------

AdtJavaName::~AdtJavaName()
{
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaName::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaName::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaName, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaNameList method implementations
//  ----------------------------------------------------------------------------
AdtJavaNameList::AdtJavaNameList(AdtParser* pNameObj)
 : AdtJavaBase()
{
  add(pNameObj);
}

//  ----------------------------------------------------------------------------

AdtJavaNameList::AdtJavaNameList(const AdtJavaNameList& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaNameList::~AdtJavaNameList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaNameList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaNameList::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaNameList, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaImportDeclarations method implementations
//  ----------------------------------------------------------------------------
AdtJavaImportDeclarations::AdtJavaImportDeclarations(AdtParser* pImportDeclarationObj)
 : AdtJavaBase()
{
  add(pImportDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtJavaImportDeclarations::AdtJavaImportDeclarations(const AdtJavaImportDeclarations& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaImportDeclarations::~AdtJavaImportDeclarations()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaImportDeclarations::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaImportDeclarations::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaImportDeclarations, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaImportDeclaration class
//  ----------------------------------------------------------------------------
AdtJavaImportDeclaration::AdtJavaImportDeclaration(AdtParser* pNameObj,
                                                   bool bHasPeriodMultiply)
 : AdtJavaBase()
{
  HasPeriodMultiply = bHasPeriodMultiply;

  initObject(Name, pNameObj, AdtJavaName, false);
}

//  ----------------------------------------------------------------------------

AdtJavaImportDeclaration::AdtJavaImportDeclaration(const AdtJavaImportDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  HasPeriodMultiply = rCopy.HasPeriodMultiply;

  copyObject(Name, rCopy, AdtJavaName);
}

//  ----------------------------------------------------------------------------

AdtJavaImportDeclaration::~AdtJavaImportDeclaration()
{
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaImportDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaImportDeclaration::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaImportDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaTypeDeclarations method implementations
//  ----------------------------------------------------------------------------
AdtJavaTypeDeclarations::AdtJavaTypeDeclarations(AdtParser* pTypeDeclarationObj)
 : AdtJavaBase()
{
  add(pTypeDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtJavaTypeDeclarations::AdtJavaTypeDeclarations(const AdtJavaTypeDeclarations& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaTypeDeclarations::~AdtJavaTypeDeclarations()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTypeDeclarations::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTypeDeclarations::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaTypeDeclarations, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaTypeDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaTypeDeclaration::AdtJavaTypeDeclaration(AdtParser* pClassDeclarationObj,
                                               AdtParser* pInterfaceDeclarationObj)
 : AdtJavaBase()
{
  initObject(ClassDeclaration,      pClassDeclarationObj,      AdtJavaClassDeclaration,      false);
  initObject(InterfaceDeclaration,  pInterfaceDeclarationObj,  AdtJavaInterfaceDeclaration,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaTypeDeclaration::AdtJavaTypeDeclaration(const AdtJavaTypeDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ClassDeclaration,      rCopy, AdtJavaClassDeclaration);
  copyObject(InterfaceDeclaration,  rCopy, AdtJavaInterfaceDeclaration);
}

//  ----------------------------------------------------------------------------

AdtJavaTypeDeclaration::~AdtJavaTypeDeclaration()
{
  UtlReleaseReference(ClassDeclaration);
  UtlReleaseReference(InterfaceDeclaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTypeDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTypeDeclaration::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaTypeDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPackageDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaPackageDeclaration::AdtJavaPackageDeclaration(AdtParser* pNameObj)
 : AdtJavaBase()
{
  initObject(Name, pNameObj, AdtJavaName, false);
}

//  ----------------------------------------------------------------------------

AdtJavaPackageDeclaration::AdtJavaPackageDeclaration(const AdtJavaPackageDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name, rCopy, AdtJavaName);
}

//  ----------------------------------------------------------------------------

AdtJavaPackageDeclaration::~AdtJavaPackageDeclaration()
{
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPackageDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPackageDeclaration::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPackageDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaModifiers method implementations
//  ----------------------------------------------------------------------------
AdtJavaModifiers::AdtJavaModifiers(AdtParser* pModifierObj)
 : AdtJavaBase()
{
  add(pModifierObj);
}

//  ----------------------------------------------------------------------------

AdtJavaModifiers::AdtJavaModifiers(const AdtJavaModifiers& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaModifiers::~AdtJavaModifiers()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaModifiers::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaModifiers::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaModifiers, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaModifier class
//  ----------------------------------------------------------------------------
AdtJavaModifier::AdtJavaModifier(AdtJavaModifierEnum nModifier)
 : AdtJavaBase()
{
  Modifier = nModifier;
}

//  ----------------------------------------------------------------------------

AdtJavaModifier::AdtJavaModifier(const AdtJavaModifier& rCopy)
 : AdtJavaBase(rCopy)
{
  Modifier = rCopy.Modifier;
}

//  ----------------------------------------------------------------------------

AdtJavaModifier::~AdtJavaModifier()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaModifier::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaModifier::writeJava(AdtFile& rOutFile) const
{
  const char* pModifier = 0;

  switch (Modifier)
  {
    case JavaModifier_PUBLIC:
    {
      pModifier = "public ";
      break;
    }

    case JavaModifier_PROTECTED:
    {
      pModifier = "protected ";
      break;
    }

    case JavaModifier_PRIVATE:
    {
      pModifier = "private ";
      break;
    }

    case JavaModifier_STATIC:
    {
      pModifier = "static ";
      break;
    }

    case JavaModifier_ABSTRACT:
    {
      pModifier = "abstract ";
      break;
    }

    case JavaModifier_FINAL:
    {
      pModifier = "final ";
      break;
    }

    case JavaModifier_NATIVE:
    {
      pModifier = "native ";
      break;
    }

    case JavaModifier_SYNCHRONIZED:
    {
      pModifier = "synchronized ";
      break;
    }

    case JavaModifier_TRANSIENT:
    {
      pModifier = "transient ";
      break;
    }

    case JavaModifier_VOLATILE:
    {
      pModifier = "volatile ";
      break;
    }

    case JavaModifier_CONST:
    {
      pModifier = "const ";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  write(rOutFile, pModifier);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaModifier, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaClassDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaClassDeclaration::AdtJavaClassDeclaration(const char* pIdentifier,
                                                 AdtParser* pModifiersObj,
                                                 AdtParser* pNameObj,
                                                 AdtParser* pNameListObj,
                                                 AdtParser* pClassBodyDeclarationsObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(Modifiers,             pModifiersObj,              AdtJavaModifiers,             false);
  initObject(Name,                  pNameObj,                   AdtJavaName,                  false);
  initObject(NameList,              pNameListObj,               AdtJavaNameList,              false);
  initObject(ClassBodyDeclarations, pClassBodyDeclarationsObj,  AdtJavaClassBodyDeclarations, false);
}

//  ----------------------------------------------------------------------------

AdtJavaClassDeclaration::AdtJavaClassDeclaration(const AdtJavaClassDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Modifiers,             rCopy, AdtJavaModifiers            );
  copyObject(Name,                  rCopy, AdtJavaName                 );
  copyObject(NameList,              rCopy, AdtJavaNameList             );
  copyObject(ClassBodyDeclarations, rCopy, AdtJavaClassBodyDeclarations);
}

//  ----------------------------------------------------------------------------

AdtJavaClassDeclaration::~AdtJavaClassDeclaration()
{
  UtlReleaseReference(Modifiers);
  UtlReleaseReference(Name);
  UtlReleaseReference(NameList);
  UtlReleaseReference(ClassBodyDeclarations);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (Modifiers != 0)
  {
    Modifiers->writeJava(rOutFile);
  }

  write(rOutFile, " class ");
  write(rOutFile, name());

  if (Name != 0)
  {
    write(rOutFile, " extends ");

    Name->writeJava(rOutFile);
  }

  if (NameList != 0)
  {
    write(rOutFile, " implements ");

    NameList->writeJava(rOutFile);
  }

  write(rOutFile, "{");
  rOutFile.incrementIndent();
  rOutFile.newline();

  if (ClassBodyDeclarations != 0)
  {
    ClassBodyDeclarations->writeJava(rOutFile);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();
  write(rOutFile, "}");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaClassDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaClassBodyDeclarations method implementations
//  ----------------------------------------------------------------------------
AdtJavaClassBodyDeclarations::AdtJavaClassBodyDeclarations(AdtParser* pClassBodyDeclarationsObj)
 : AdtJavaBase()
{
  add(pClassBodyDeclarationsObj);
}

//  ----------------------------------------------------------------------------

AdtJavaClassBodyDeclarations::AdtJavaClassBodyDeclarations(const AdtJavaClassBodyDeclarations& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaClassBodyDeclarations::~AdtJavaClassBodyDeclarations()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassBodyDeclarations::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassBodyDeclarations::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaClassBodyDeclarations, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaClassBodyDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaClassBodyDeclaration::AdtJavaClassBodyDeclaration(AdtParser* pClassMemberDeclarationObj,
                                                         AdtParser* pBlockObj,
                                                         AdtParser* pConstructorDeclarationObj)
 : AdtJavaBase()
{
  initObject(ClassMemberDeclaration, pClassMemberDeclarationObj,  AdtJavaClassMemberDeclaration, false);
  initObject(Block,                  pBlockObj,                   AdtJavaBlock,                  false);
  initObject(ConstructorDeclaration, pConstructorDeclarationObj,  AdtJavaConstructorDeclaration, false);
}

//  ----------------------------------------------------------------------------

AdtJavaClassBodyDeclaration::AdtJavaClassBodyDeclaration(const AdtJavaClassBodyDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ClassMemberDeclaration, rCopy, AdtJavaClassMemberDeclaration);
  copyObject(Block,                  rCopy, AdtJavaBlock                 );
  copyObject(ConstructorDeclaration, rCopy, AdtJavaConstructorDeclaration);
}

//  ----------------------------------------------------------------------------

AdtJavaClassBodyDeclaration::~AdtJavaClassBodyDeclaration()
{
  UtlReleaseReference(ClassMemberDeclaration);
  UtlReleaseReference(Block);
  UtlReleaseReference(ConstructorDeclaration);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassBodyDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassBodyDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (ClassMemberDeclaration != 0)
  {
    ClassMemberDeclaration->writeJava(rOutFile);
  }
  else if (ConstructorDeclaration != 0)
  {
    ConstructorDeclaration->writeJava(rOutFile);
  }
  else if (Block != 0)
  {
    write(rOutFile, "static ");
    Block->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaClassBodyDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaClassMemberDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaClassMemberDeclaration::AdtJavaClassMemberDeclaration(AdtParser* pFieldDeclarationObj,
                                                             AdtParser* pMethodHeaderObj,
                                                             AdtParser* pBlockObj)
 : AdtJavaBase()
{
  initObject(FieldDeclaration, pFieldDeclarationObj,  AdtJavaFieldDeclaration, false);
  initObject(MethodHeader,     pMethodHeaderObj,      AdtJavaMethodHeader,     false);
  initObject(Block,            pBlockObj,             AdtJavaBlock,            false);
}

//  ----------------------------------------------------------------------------

AdtJavaClassMemberDeclaration::AdtJavaClassMemberDeclaration(const AdtJavaClassMemberDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(FieldDeclaration, rCopy, AdtJavaFieldDeclaration);
  copyObject(MethodHeader,     rCopy, AdtJavaMethodHeader    );
  copyObject(Block,            rCopy, AdtJavaBlock           );
}

//  ----------------------------------------------------------------------------

AdtJavaClassMemberDeclaration::~AdtJavaClassMemberDeclaration()
{
  UtlReleaseReference(FieldDeclaration);
  UtlReleaseReference(MethodHeader);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassMemberDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassMemberDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (FieldDeclaration != 0)
  {
    FieldDeclaration->writeJava(rOutFile);
  }
  else if (MethodHeader != 0)
  {
    MethodHeader->writeJava(rOutFile);

    if (Block != 0)
    {
      Block->writeJava(rOutFile);
    }
    else
    {
      write(rOutFile, ";");
      rOutFile.newline();
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaClassMemberDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaFieldDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaFieldDeclaration::AdtJavaFieldDeclaration(AdtParser* pModifiersObj,
                                                 AdtParser* pTypeObj,
                                                 AdtParser* pVariableDeclaratorsObj)
 : AdtJavaBase()
{
  initObject(Modifiers,           pModifiersObj,           AdtJavaModifiers,           false);
  initObject(Type,                pTypeObj,                AdtJavaType,                false);
  initObject(VariableDeclarators, pVariableDeclaratorsObj, AdtJavaVariableDeclarators, false);
}

//  ----------------------------------------------------------------------------

AdtJavaFieldDeclaration::AdtJavaFieldDeclaration(const AdtJavaFieldDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Modifiers,           rCopy, AdtJavaModifiers          );
  copyObject(Type,                rCopy, AdtJavaType               );
  copyObject(VariableDeclarators, rCopy, AdtJavaVariableDeclarators);
}

//  ----------------------------------------------------------------------------

AdtJavaFieldDeclaration::~AdtJavaFieldDeclaration()
{
  UtlReleaseReference(Modifiers);
  UtlReleaseReference(Type);
  UtlReleaseReference(VariableDeclarators);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFieldDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFieldDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (Modifiers != 0)
  {
    Modifiers->writeJava(rOutFile);
  }

  if (Type != 0)
  {
    Type->writeJava(rOutFile);
  }

  if (VariableDeclarators != 0)
  {
    VariableDeclarators->writeJava(rOutFile);
  }

  write(rOutFile, ";");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaFieldDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclarators method implementations
//  ----------------------------------------------------------------------------
AdtJavaVariableDeclarators::AdtJavaVariableDeclarators(AdtParser* pVariableDeclaratorObj)
 : AdtJavaBase()
{
  add(pVariableDeclaratorObj);
}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclarators::AdtJavaVariableDeclarators(const AdtJavaVariableDeclarators& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclarators::~AdtJavaVariableDeclarators()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclarators::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclarators::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaVariableDeclarators, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtJavaVariableDeclarator::AdtJavaVariableDeclarator(AdtParser* pVariableDeclaratorIdObj,
                                                     AdtParser* pExpressionObj,
                                                     AdtParser* pVariableInitializersObj,
                                                     bool bHasComma,
                                                     bool bHasBracket)
 : AdtJavaBase()
{
  initObject(VariableDeclaratorId, pVariableDeclaratorIdObj, AdtJavaVariableDeclaratorId, false);
  initObject(Expression,           pExpressionObj,           AdtJavaExpression,           false);
  initObject(VariableInitializers, pVariableInitializersObj, AdtJavaVariableInitializers, false);

  HasComma    = bHasComma;
  HasBracket  = bHasBracket;
}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclarator::AdtJavaVariableDeclarator(const AdtJavaVariableDeclarator& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(VariableDeclaratorId, rCopy, AdtJavaVariableDeclaratorId);
  copyObject(Expression,           rCopy, AdtJavaExpression);
  copyObject(VariableInitializers, rCopy, AdtJavaVariableInitializers);

  HasComma    = rCopy.HasComma;
  HasBracket  = rCopy.HasBracket;
}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclarator::~AdtJavaVariableDeclarator()
{
  UtlReleaseReference(VariableDeclaratorId);
  UtlReleaseReference(Expression);
  UtlReleaseReference(VariableInitializers);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclarator::writeJava(AdtFile& rOutFile) const
{
  if (VariableDeclaratorId != 0)
  {
    VariableDeclaratorId->writeJava(rOutFile);
  }

  if ((Expression           != 0) ||
      (VariableInitializers != 0) ||
      HasBracket)
  {
    write(rOutFile, " = ");
  }

  if (HasBracket)
  {
    write(rOutFile, "{");
  }

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }
  else if (VariableInitializers != 0)
  {
    VariableInitializers->writeJava(rOutFile);
  }

  if (HasBracket)
  {
    if (HasComma)
    {
      write(rOutFile, ",");
    }

    write(rOutFile, "}");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaVariableDeclarator, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclaratorId method implementations
//  ----------------------------------------------------------------------------
AdtJavaVariableDeclaratorId::AdtJavaVariableDeclaratorId(const char* pIdentifier, AdtParser* pVariableDeclaratorIdObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(VariableDeclaratorId, pVariableDeclaratorIdObj, AdtJavaVariableDeclaratorId, false);
}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclaratorId::AdtJavaVariableDeclaratorId(const AdtJavaVariableDeclaratorId& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(VariableDeclaratorId, rCopy, AdtJavaVariableDeclaratorId);
}

//  ----------------------------------------------------------------------------

AdtJavaVariableDeclaratorId::~AdtJavaVariableDeclaratorId()
{
  UtlReleaseReference(VariableDeclaratorId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclaratorId::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableDeclaratorId::writeJava(AdtFile& rOutFile) const
{
  if (VariableDeclaratorId != 0)
  {
    VariableDeclaratorId->writeJava(rOutFile);
    write(rOutFile, "[]");
  }
  else
  {
    write(rOutFile, name());
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaVariableDeclaratorId, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaMethodHeader method implementations
//  ----------------------------------------------------------------------------
AdtJavaMethodHeader::AdtJavaMethodHeader(AdtParser* pModifiersObj,
                                         AdtParser* pTypeObj,
                                         AdtParser* pMethodDeclaratorObj,
                                         AdtParser* pNameListObj)
 : AdtJavaBase()
{
  initObject(Modifiers,        pModifiersObj,        AdtJavaModifiers,        false);
  initObject(Type,             pTypeObj,             AdtJavaType,             false);
  initObject(MethodDeclarator, pMethodDeclaratorObj, AdtJavaMethodDeclarator, false);
  initObject(NameList,         pNameListObj,         AdtJavaNameList,         false);
}

//  ----------------------------------------------------------------------------

AdtJavaMethodHeader::AdtJavaMethodHeader(const AdtJavaMethodHeader& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Modifiers,        rCopy, AdtJavaModifiers       );
  copyObject(Type,             rCopy, AdtJavaType            );
  copyObject(MethodDeclarator, rCopy, AdtJavaMethodDeclarator);
  copyObject(NameList,         rCopy, AdtJavaNameList        );
}

//  ----------------------------------------------------------------------------

AdtJavaMethodHeader::~AdtJavaMethodHeader()
{
  UtlReleaseReference(Modifiers);
  UtlReleaseReference(Type);
  UtlReleaseReference(MethodDeclarator);
  UtlReleaseReference(NameList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodHeader::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodHeader::writeJava(AdtFile& rOutFile) const
{
  if (Modifiers != 0)
  {
    Modifiers->writeJava(rOutFile);
  }

  if (Type != 0)
  {
    Type->writeJava(rOutFile);
  }
  else
  {
    write(rOutFile, " void ");
  }

  if (MethodDeclarator != 0)
  {
    MethodDeclarator->writeJava(rOutFile);
  }

  if (NameList != 0)
  {
    write(rOutFile, " throws ");
    NameList->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaMethodHeader, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaMethodDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtJavaMethodDeclarator::AdtJavaMethodDeclarator(const char* pIdentifier,
                                                 AdtParser* pFormalParameterListObj,
                                                 AdtParser* pMethodDeclaratorObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(FormalParameterList, pFormalParameterListObj, AdtJavaFormalParameterList, false);
  initObject(MethodDeclarator,    pMethodDeclaratorObj,    AdtJavaMethodDeclarator,    false);
}

//  ----------------------------------------------------------------------------

AdtJavaMethodDeclarator::AdtJavaMethodDeclarator(const AdtJavaMethodDeclarator& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(FormalParameterList, rCopy, AdtJavaFormalParameterList);
  copyObject(MethodDeclarator,    rCopy, AdtJavaMethodDeclarator   );
}

//  ----------------------------------------------------------------------------

AdtJavaMethodDeclarator::~AdtJavaMethodDeclarator()
{
  UtlReleaseReference(FormalParameterList);
  UtlReleaseReference(MethodDeclarator);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodDeclarator::writeJava(AdtFile& rOutFile) const
{
  if (MethodDeclarator != 0)
  {
    MethodDeclarator->writeJava(rOutFile);
    write(rOutFile, "[]");
  }
  else
  {
    write(rOutFile, name());
    write(rOutFile, "(");

    if (FormalParameterList != 0)
    {
      FormalParameterList->writeJava(rOutFile);
    }

    write(rOutFile, ")");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaMethodDeclarator, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaFormalParameterList method implementations
//  ----------------------------------------------------------------------------
AdtJavaFormalParameterList::AdtJavaFormalParameterList(AdtParser* pFormalParameterObj)
 : AdtJavaBase()
{
  add(pFormalParameterObj);
}

//  ----------------------------------------------------------------------------

AdtJavaFormalParameterList::AdtJavaFormalParameterList(const AdtJavaFormalParameterList& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaFormalParameterList::~AdtJavaFormalParameterList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFormalParameterList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFormalParameterList::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaFormalParameterList, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaFormalParameter method implementations
//  ----------------------------------------------------------------------------
AdtJavaFormalParameter::AdtJavaFormalParameter(AdtParser* pTypeObj,
                                               AdtParser* pVariableDeclaratorIdObj)
 : AdtJavaBase()
{
  initObject(Type,                 pTypeObj,                 AdtJavaType,                 false);
  initObject(VariableDeclaratorId, pVariableDeclaratorIdObj, AdtJavaVariableDeclaratorId, false);
}

//  ----------------------------------------------------------------------------

AdtJavaFormalParameter::AdtJavaFormalParameter(const AdtJavaFormalParameter& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Type,                 rCopy, AdtJavaType);
  copyObject(VariableDeclaratorId, rCopy, AdtJavaVariableDeclaratorId);
}

//  ----------------------------------------------------------------------------

AdtJavaFormalParameter::~AdtJavaFormalParameter()
{
  UtlReleaseReference(Type);
  UtlReleaseReference(VariableDeclaratorId);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFormalParameter::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFormalParameter::writeJava(AdtFile& rOutFile) const
{
  if (Type != 0)
  {
    Type->writeJava(rOutFile);
  }

  if (VariableDeclaratorId != 0)
  {
    VariableDeclaratorId->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaFormalParameter, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaConstructorDeclaration::AdtJavaConstructorDeclaration(AdtParser* pModifiersObj,
                                                             AdtParser* pConstructorDeclaratorObj,
                                                             AdtParser* pNameListObj,
                                                             AdtParser* pConstructorBodyObj)
 : AdtJavaBase()
{
  initObject(Modifiers,             pModifiersObj,             AdtJavaModifiers,             false);
  initObject(ConstructorDeclarator, pConstructorDeclaratorObj, AdtJavaConstructorDeclarator, false);
  initObject(NameList,              pNameListObj,              AdtJavaNameList,              false);
  initObject(ConstructorBody,       pConstructorBodyObj,       AdtJavaConstructorBody,       false);
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorDeclaration::AdtJavaConstructorDeclaration(const AdtJavaConstructorDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Modifiers,             rCopy, AdtJavaModifiers            );
  copyObject(ConstructorDeclarator, rCopy, AdtJavaConstructorDeclarator);
  copyObject(NameList,              rCopy, AdtJavaNameList             );
  copyObject(ConstructorBody,       rCopy, AdtJavaConstructorBody      );
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorDeclaration::~AdtJavaConstructorDeclaration()
{
  UtlReleaseReference(Modifiers);
  UtlReleaseReference(ConstructorDeclarator);
  UtlReleaseReference(NameList);
  UtlReleaseReference(ConstructorBody);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (Modifiers != 0)
  {
    Modifiers->writeJava(rOutFile);
  }

  if (ConstructorDeclarator != 0)
  {
    ConstructorDeclarator->writeJava(rOutFile);
  }

  if (NameList != 0)
  {
    write(rOutFile, " throws ");
    NameList->writeJava(rOutFile);
  }

  if (ConstructorBody != 0)
  {
    ConstructorBody->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConstructorDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorDeclarator method implementations
//  ----------------------------------------------------------------------------
AdtJavaConstructorDeclarator::AdtJavaConstructorDeclarator(const char* pIdentifier,
                                                           AdtParser* pFormalParameterListObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(FormalParameterList, pFormalParameterListObj, AdtJavaFormalParameterList, false);
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorDeclarator::AdtJavaConstructorDeclarator(const AdtJavaConstructorDeclarator& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(FormalParameterList, rCopy, AdtJavaFormalParameterList);
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorDeclarator::~AdtJavaConstructorDeclarator()
{
  UtlReleaseReference(FormalParameterList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorDeclarator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorDeclarator::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, name());
  write(rOutFile, "(");

  if (FormalParameterList != 0)
  {
    FormalParameterList->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConstructorDeclarator, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorBody method implementations
//  ----------------------------------------------------------------------------
AdtJavaConstructorBody::AdtJavaConstructorBody(AdtParser* pBlockObj)
 : AdtJavaBase()
{
  initObject(Block, pBlockObj, AdtJavaBlock, false);
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorBody::AdtJavaConstructorBody(const AdtJavaConstructorBody& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Block, rCopy, AdtJavaBlock);
}

//  ----------------------------------------------------------------------------

AdtJavaConstructorBody::~AdtJavaConstructorBody()
{
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorBody::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConstructorBody::writeJava(AdtFile& rOutFile) const
{
  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConstructorBody, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaExplicitConstructorInvocation method implementations
//  ----------------------------------------------------------------------------
AdtJavaExplicitConstructorInvocation::AdtJavaExplicitConstructorInvocation(AdtParser* pArgumentListObj,
                                                                           bool bIsSuper)
 : AdtJavaBase()
{
  IsSuper = bIsSuper;

  initObject(ArgumentList, pArgumentListObj, AdtJavaArgumentList, false);
}

//  ----------------------------------------------------------------------------

AdtJavaExplicitConstructorInvocation::AdtJavaExplicitConstructorInvocation(const AdtJavaExplicitConstructorInvocation& rCopy)
 : AdtJavaBase(rCopy)
{
  IsSuper = rCopy.IsSuper;

  copyObject(ArgumentList, rCopy, AdtJavaArgumentList);
}

//  ----------------------------------------------------------------------------

AdtJavaExplicitConstructorInvocation::~AdtJavaExplicitConstructorInvocation()
{
  UtlReleaseReference(ArgumentList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExplicitConstructorInvocation::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExplicitConstructorInvocation::writeJava(AdtFile& rOutFile) const
{
  if (IsSuper)
  {
    write(rOutFile, "super(");
  }
  else
  {
    write(rOutFile, "this(");
  }

  if (ArgumentList != 0)
  {
    ArgumentList->writeJava(rOutFile);
  }

  write(rOutFile, ");");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaExplicitConstructorInvocation, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaInterfaceDeclaration::AdtJavaInterfaceDeclaration(const char* pIdentifier,
                                                         AdtParser* pModifiersObj,
                                                         AdtParser* pExtendsInterfacesObj,
                                                         AdtParser* pInterfaceMemberDeclarationsObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(Modifiers,                   pModifiersObj,                   AdtJavaModifiers,                   false);
  initObject(ExtendsInterfaces,           pExtendsInterfacesObj,           AdtJavaExtendsInterfaces,           false);
  initObject(InterfaceMemberDeclarations, pInterfaceMemberDeclarationsObj, AdtJavaInterfaceMemberDeclarations, false);
}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceDeclaration::AdtJavaInterfaceDeclaration(const AdtJavaInterfaceDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Modifiers,                   rCopy, AdtJavaModifiers                  );
  copyObject(ExtendsInterfaces,           rCopy, AdtJavaExtendsInterfaces          );
  copyObject(InterfaceMemberDeclarations, rCopy, AdtJavaInterfaceMemberDeclarations);
}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceDeclaration::~AdtJavaInterfaceDeclaration()
{
  UtlReleaseReference(Modifiers);
  UtlReleaseReference(ExtendsInterfaces);
  UtlReleaseReference(InterfaceMemberDeclarations);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (Modifiers != 0)
  {
    Modifiers->writeJava(rOutFile);
    write(rOutFile, " ");
  }

  write(rOutFile, "interface ");
  write(rOutFile, name());

  if (ExtendsInterfaces != 0)
  {
    ExtendsInterfaces->writeJava(rOutFile);
  }

  rOutFile.newline();
  write(rOutFile, "{");
  rOutFile.incrementIndent();
  rOutFile.newline();

  if (InterfaceMemberDeclarations != 0)
  {
    InterfaceMemberDeclarations->writeJava(rOutFile);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();
  write(rOutFile, "}");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaInterfaceDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaExtendsInterfaces class
//  ----------------------------------------------------------------------------
AdtJavaExtendsInterfaces::AdtJavaExtendsInterfaces(AdtParser* pNameObj,
                                                   AdtParser* pExtendsInterfacesObj)
 : AdtJavaBase()
{
  initObject(Name,              pNameObj,               AdtJavaName,              false);
  initObject(ExtendsInterfaces, pExtendsInterfacesObj,  AdtJavaExtendsInterfaces, false);
}

//  ----------------------------------------------------------------------------

AdtJavaExtendsInterfaces::AdtJavaExtendsInterfaces(const AdtJavaExtendsInterfaces& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name,              rCopy, AdtJavaName             );
  copyObject(ExtendsInterfaces, rCopy, AdtJavaExtendsInterfaces);
}

//  ----------------------------------------------------------------------------

AdtJavaExtendsInterfaces::~AdtJavaExtendsInterfaces()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(ExtendsInterfaces);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExtendsInterfaces::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExtendsInterfaces::writeJava(AdtFile& rOutFile) const
{
  if (ExtendsInterfaces != 0)
  {
    ExtendsInterfaces->writeJava(rOutFile);
  }

  if (Name != 0)
  {
    write(rOutFile, " extends ");
    Name->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaExtendsInterfaces, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceMemberDeclarations method implementations
//  ----------------------------------------------------------------------------
AdtJavaInterfaceMemberDeclarations::AdtJavaInterfaceMemberDeclarations(AdtParser* pInterfaceMemberDeclarationObj)
 : AdtJavaBase()
{
  add(pInterfaceMemberDeclarationObj);
}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceMemberDeclarations::AdtJavaInterfaceMemberDeclarations(const AdtJavaInterfaceMemberDeclarations& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceMemberDeclarations::~AdtJavaInterfaceMemberDeclarations()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceMemberDeclarations::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceMemberDeclarations::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaInterfaceMemberDeclarations, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceMemberDeclaration method implementations
//  ----------------------------------------------------------------------------
AdtJavaInterfaceMemberDeclaration::AdtJavaInterfaceMemberDeclaration(AdtParser* pFieldDeclarationObj,
                                                                     AdtParser* pMethodHeaderObj)
 : AdtJavaBase()
{
  initObject(FieldDeclaration, pFieldDeclarationObj, AdtJavaFieldDeclaration, false);
  initObject(MethodHeader,     pMethodHeaderObj,     AdtJavaMethodHeader,     false);
}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceMemberDeclaration::AdtJavaInterfaceMemberDeclaration(const AdtJavaInterfaceMemberDeclaration& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(FieldDeclaration, rCopy, AdtJavaFieldDeclaration);
  copyObject(MethodHeader,     rCopy, AdtJavaMethodHeader    );
}

//  ----------------------------------------------------------------------------

AdtJavaInterfaceMemberDeclaration::~AdtJavaInterfaceMemberDeclaration()
{
  UtlReleaseReference(FieldDeclaration);
  UtlReleaseReference(MethodHeader);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceMemberDeclaration::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInterfaceMemberDeclaration::writeJava(AdtFile& rOutFile) const
{
  if (FieldDeclaration != 0)
  {
    FieldDeclaration->writeJava(rOutFile);
  }
  else if (MethodHeader != 0)
  {
    MethodHeader->writeJava(rOutFile);

    write(rOutFile, ";");
    rOutFile.newline();
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaInterfaceMemberDeclaration, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaVariableInitializers method implementations
//  ----------------------------------------------------------------------------
AdtJavaVariableInitializers::AdtJavaVariableInitializers(AdtParser* pVariableInitializerObj)
 : AdtJavaBase()
{
  add(pVariableInitializerObj);
}

//  ----------------------------------------------------------------------------

AdtJavaVariableInitializers::AdtJavaVariableInitializers(const AdtJavaVariableInitializers& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaVariableInitializers::~AdtJavaVariableInitializers()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableInitializers::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableInitializers::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaVariableInitializers, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaVariableInitializer method implementations
//  ----------------------------------------------------------------------------
AdtJavaVariableInitializer::AdtJavaVariableInitializer(AdtParser* pExpressionObj,
                                                       AdtParser* pVariableInitializersObj,
                                                       bool bWithComma)
 : AdtJavaBase()
{
  initObject(Expression,            pExpressionObj,           AdtJavaExpression,            false);
  initObject(VariableInitializers,  pVariableInitializersObj, AdtJavaVariableInitializers,  false);

  WithComma = bWithComma;
}

//  ----------------------------------------------------------------------------

AdtJavaVariableInitializer::AdtJavaVariableInitializer(const AdtJavaVariableInitializer& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression,            rCopy, AdtJavaExpression);
  copyObject(VariableInitializers,  rCopy, AdtJavaVariableInitializers);

  WithComma = rCopy.WithComma;
}

//  ----------------------------------------------------------------------------

AdtJavaVariableInitializer::~AdtJavaVariableInitializer()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(VariableInitializers);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableInitializer::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaVariableInitializer::writeJava(AdtFile& rOutFile) const
{
  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }
  else if (VariableInitializers != 0)
  {
    write(rOutFile, "{");

    VariableInitializers->writeJava(rOutFile);

    if (WithComma)
    {
      write(rOutFile, ",");
    }

    write(rOutFile, "}");
  }
  else
  {
    write(rOutFile, "{");

    if (WithComma)
    {
      write(rOutFile, ",");
    }

    write(rOutFile, "}");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaVariableInitializer, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaBlock method implementations
//  ----------------------------------------------------------------------------
AdtJavaBlock::AdtJavaBlock(AdtParser* pBlockStatementsObj,
                           AdtParser* pExplicitConstructorInvocationObj)
 : AdtJavaBase()
{
  initObject(BlockStatements,               pBlockStatementsObj,                AdtJavaBlockStatements,               false);
  initObject(ExplicitConstructorInvocation, pExplicitConstructorInvocationObj,  AdtJavaExplicitConstructorInvocation, false);
}

//  ----------------------------------------------------------------------------

AdtJavaBlock::AdtJavaBlock(const AdtJavaBlock& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(BlockStatements,               rCopy, AdtJavaBlockStatements              );
  copyObject(ExplicitConstructorInvocation, rCopy, AdtJavaExplicitConstructorInvocation);
}

//  ----------------------------------------------------------------------------

AdtJavaBlock::~AdtJavaBlock()
{
  UtlReleaseReference(BlockStatements);
  UtlReleaseReference(ExplicitConstructorInvocation);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlock::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlock::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "{");
  rOutFile.newline();
  rOutFile.incrementIndent();

  if (ExplicitConstructorInvocation != 0)
  {
    ExplicitConstructorInvocation->writeJava(rOutFile);

    rOutFile.newline();
  }

  if (BlockStatements != 0)
  {
    BlockStatements->writeJava(rOutFile);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();
  write(rOutFile, "}");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaBlock, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaBlockStatements method implementations
//  ----------------------------------------------------------------------------
AdtJavaBlockStatements::AdtJavaBlockStatements(AdtParser* pBlockStatementObj)
 : AdtJavaBase()
{
  add(pBlockStatementObj);
}

//  ----------------------------------------------------------------------------

AdtJavaBlockStatements::AdtJavaBlockStatements(const AdtJavaBlockStatements& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaBlockStatements::~AdtJavaBlockStatements()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlockStatements::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlockStatements::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaBlockStatements, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaBlockStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaBlockStatement::AdtJavaBlockStatement(AdtParser* pTypeObj,
                                             AdtParser* pVariableDeclaratorsObj,
                                             AdtParser* pStatementObj)
 : AdtJavaBase()
{
  initObject(Type,                pTypeObj,                 AdtJavaType,                false);
  initObject(VariableDeclarators, pVariableDeclaratorsObj,  AdtJavaVariableDeclarators, false);
  initObject(Statement,           pStatementObj,            AdtJavaStatement,           false);
}

//  ----------------------------------------------------------------------------

AdtJavaBlockStatement::AdtJavaBlockStatement(const AdtJavaBlockStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Type,                rCopy, AdtJavaType);
  copyObject(VariableDeclarators, rCopy, AdtJavaVariableDeclarators);
  copyObject(Statement,           rCopy, AdtJavaStatement);
}

//  ----------------------------------------------------------------------------

AdtJavaBlockStatement::~AdtJavaBlockStatement()
{
  UtlReleaseReference(Type);
  UtlReleaseReference(VariableDeclarators);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlockStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBlockStatement::writeJava(AdtFile& rOutFile) const
{
  if (Statement != 0)
  {
    Statement->writeJava(rOutFile);
  }
  else
  {
    if (Type != 0)
    {
      Type->writeJava(rOutFile);
    }

    if (VariableDeclarators != 0)
    {
      VariableDeclarators->writeJava(rOutFile);
    }

    write(rOutFile, ";");
    rOutFile.newline();
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaBlockStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaStatement::AdtJavaStatement(const char* pIdentifier,
                                   AdtParser* pStatementWithoutTrailingSubstatementObj,
                                   AdtParser* pStatementObj,
                                   AdtParser* pIfThenStatementObj,
                                   AdtParser* pIfThenElseStatementObj,
                                   AdtParser* pWhileStatementObj,
                                   AdtParser* pForStatementObj,
                                   bool bNoShortIf)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(StatementWithoutTrailingSubstatement, pStatementWithoutTrailingSubstatementObj, AdtJavaStatementWithoutTrailingSubstatement, false);
  initObject(Statement,           pStatementObj,            AdtJavaStatement,           false);
  initObject(IfThenStatement,     pIfThenStatementObj,      AdtJavaIfThenStatement,     false);
  initObject(IfThenElseStatement, pIfThenElseStatementObj,  AdtJavaIfThenElseStatement, false);
  initObject(WhileStatement,      pWhileStatementObj,       AdtJavaWhileStatement,      false);
  initObject(ForStatement,        pForStatementObj,         AdtJavaForStatement,        false);

  NoShortIf = bNoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaStatement::AdtJavaStatement(const AdtJavaStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(StatementWithoutTrailingSubstatement, rCopy, AdtJavaStatementWithoutTrailingSubstatement);
  copyObject(Statement,           rCopy, AdtJavaStatement);
  copyObject(IfThenStatement,     rCopy, AdtJavaIfThenStatement);
  copyObject(IfThenElseStatement, rCopy, AdtJavaIfThenElseStatement);
  copyObject(WhileStatement,      rCopy, AdtJavaWhileStatement);
  copyObject(ForStatement,        rCopy, AdtJavaForStatement);

  NoShortIf = rCopy.NoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaStatement::~AdtJavaStatement()
{
  UtlReleaseReference(StatementWithoutTrailingSubstatement);
  UtlReleaseReference(Statement);
  UtlReleaseReference(IfThenStatement);
  UtlReleaseReference(IfThenElseStatement);
  UtlReleaseReference(WhileStatement);
  UtlReleaseReference(ForStatement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatement::writeJava(AdtFile& rOutFile) const
{
  if (StatementWithoutTrailingSubstatement != 0)
  {
    StatementWithoutTrailingSubstatement->writeJava(rOutFile);
  }
  else if (Statement != 0)
  {
    write(rOutFile, name());
    write(rOutFile, " : ");
    Statement->writeJava(rOutFile);
  }
  else if (IfThenStatement != 0)
  {
    IfThenStatement->writeJava(rOutFile);
  }
  else if (IfThenElseStatement != 0)
  {
    IfThenElseStatement->writeJava(rOutFile);
  }
  else if (WhileStatement != 0)
  {
    WhileStatement->writeJava(rOutFile);
  }
  else if (ForStatement != 0)
  {
    ForStatement->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaStatementWithoutTrailingSubstatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaStatementWithoutTrailingSubstatement::AdtJavaStatementWithoutTrailingSubstatement(AdtParser* pBlockObj,
                                                                                         AdtParser* pStatementExpressionObj,
                                                                                         AdtParser* pSwitchStatementObj,
                                                                                         AdtParser* pDoStatementObj,
                                                                                         AdtParser* pBreakStatementObj,
                                                                                         AdtParser* pContinueStatementObj,
                                                                                         AdtParser* pReturnStatementObj,
                                                                                         AdtParser* pSynchronizedStatementObj,
                                                                                         AdtParser* pThrowStatementObj,
                                                                                         AdtParser* pTryStatementObj,
                                                                                         bool bHasSemiColon)
 : AdtJavaBase()
{
  initObject(Block,                 pBlockObj,                 AdtJavaBlock,                 false);
  initObject(StatementExpression,   pStatementExpressionObj,   AdtJavaStatementExpression,   false);
  initObject(SwitchStatement,       pSwitchStatementObj,       AdtJavaSwitchStatement,       false);
  initObject(DoStatement,           pDoStatementObj,           AdtJavaDoStatement,           false);
  initObject(BreakStatement,        pBreakStatementObj,        AdtJavaBreakStatement,        false);
  initObject(ContinueStatement,     pContinueStatementObj,     AdtJavaContinueStatement,     false);
  initObject(ReturnStatement,       pReturnStatementObj,       AdtJavaReturnStatement,       false);
  initObject(SynchronizedStatement, pSynchronizedStatementObj, AdtJavaSynchronizedStatement, false);
  initObject(ThrowStatement,        pThrowStatementObj,        AdtJavaThrowStatement,        false);
  initObject(TryStatement,          pTryStatementObj,          AdtJavaTryStatement,          false);

  HasSemiColon = bHasSemiColon;
}

//  ----------------------------------------------------------------------------

AdtJavaStatementWithoutTrailingSubstatement::AdtJavaStatementWithoutTrailingSubstatement(const AdtJavaStatementWithoutTrailingSubstatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Block,                 rCopy, AdtJavaBlock);
  copyObject(StatementExpression,   rCopy, AdtJavaStatementExpression);
  copyObject(SwitchStatement,       rCopy, AdtJavaSwitchStatement);
  copyObject(DoStatement,           rCopy, AdtJavaDoStatement);
  copyObject(BreakStatement,        rCopy, AdtJavaBreakStatement);
  copyObject(ContinueStatement,     rCopy, AdtJavaContinueStatement);
  copyObject(ReturnStatement,       rCopy, AdtJavaReturnStatement);
  copyObject(SynchronizedStatement, rCopy, AdtJavaSynchronizedStatement);
  copyObject(ThrowStatement,        rCopy, AdtJavaThrowStatement);
  copyObject(TryStatement,          rCopy, AdtJavaTryStatement);

  HasSemiColon = rCopy.HasSemiColon;
}

//  ----------------------------------------------------------------------------

AdtJavaStatementWithoutTrailingSubstatement::~AdtJavaStatementWithoutTrailingSubstatement()
{
  UtlReleaseReference(Block);
  UtlReleaseReference(StatementExpression);
  UtlReleaseReference(SwitchStatement);
  UtlReleaseReference(DoStatement);
  UtlReleaseReference(BreakStatement);
  UtlReleaseReference(ContinueStatement);
  UtlReleaseReference(ReturnStatement);
  UtlReleaseReference(SynchronizedStatement);
  UtlReleaseReference(ThrowStatement);
  UtlReleaseReference(TryStatement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementWithoutTrailingSubstatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementWithoutTrailingSubstatement::writeJava(AdtFile& rOutFile) const
{
  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }
  else if (StatementExpression != 0)
  {
    StatementExpression->writeJava(rOutFile);
    write(rOutFile, ";");
   rOutFile.newline();
  }
  else if (SwitchStatement != 0)
  {
    SwitchStatement->writeJava(rOutFile);
  }
  else if (DoStatement != 0)
  {
    DoStatement->writeJava(rOutFile);
  }
  else if (BreakStatement != 0)
  {
    BreakStatement->writeJava(rOutFile);
  }
  else if (ContinueStatement != 0)
  {
    ContinueStatement->writeJava(rOutFile);
  }
  else if (ReturnStatement != 0)
  {
    ReturnStatement->writeJava(rOutFile);
  }
  else if (SynchronizedStatement != 0)
  {
    SynchronizedStatement->writeJava(rOutFile);
  }
  else if (ThrowStatement != 0)
  {
    ThrowStatement->writeJava(rOutFile);
  }
  else if (TryStatement != 0)
  {
    TryStatement->writeJava(rOutFile);
  }
  else
  {
    write(rOutFile, ";");
    rOutFile.newline();
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaStatementWithoutTrailingSubstatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaStatementExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaStatementExpression::AdtJavaStatementExpression(AdtParser* pAssignmentObj,
                                                       AdtParser* pPreIncDecExpressionObj,
                                                       AdtParser* pPostIncDecExpressionObj,
                                                       AdtParser* pMethodInvocationObj,
                                                       AdtParser* pClassInstanceCreationExpressionObj)
 : AdtJavaBase()
{
  initObject(Assignment,                      pAssignmentObj,                      AdtJavaAssignment,                      false);
  initObject(PreIncDecExpression,             pPreIncDecExpressionObj,             AdtJavaPreIncDecExpression,             false);
  initObject(PostIncDecExpression,            pPostIncDecExpressionObj,            AdtJavaPostIncDecExpression,            false);
  initObject(MethodInvocation,                pMethodInvocationObj,                AdtJavaMethodInvocation,                false);
  initObject(ClassInstanceCreationExpression, pClassInstanceCreationExpressionObj, AdtJavaClassInstanceCreationExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaStatementExpression::AdtJavaStatementExpression(const AdtJavaStatementExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Assignment,                      rCopy, AdtJavaAssignment                     );
  copyObject(PreIncDecExpression,             rCopy, AdtJavaPreIncDecExpression            );
  copyObject(PostIncDecExpression,            rCopy, AdtJavaPostIncDecExpression           );
  copyObject(MethodInvocation,                rCopy, AdtJavaMethodInvocation               );
  copyObject(ClassInstanceCreationExpression, rCopy, AdtJavaClassInstanceCreationExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaStatementExpression::~AdtJavaStatementExpression()
{
  UtlReleaseReference(Assignment);
  UtlReleaseReference(PreIncDecExpression);
  UtlReleaseReference(PostIncDecExpression);
  UtlReleaseReference(MethodInvocation);
  UtlReleaseReference(ClassInstanceCreationExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementExpression::writeJava(AdtFile& rOutFile) const
{
  if (Assignment != 0)
  {
    Assignment->writeJava(rOutFile);
  }
  else if (PreIncDecExpression != 0)
  {
    PreIncDecExpression->writeJava(rOutFile);
  }
  else if (PostIncDecExpression != 0)
  {
    PreIncDecExpression->writeJava(rOutFile);
  }
  else if (MethodInvocation != 0)
  {
    MethodInvocation->writeJava(rOutFile);
  }
  else if (ClassInstanceCreationExpression != 0)
  {
    ClassInstanceCreationExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaStatementExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaIfThenStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaIfThenStatement::AdtJavaIfThenStatement(AdtParser* pExpressionObj,
                                               AdtParser* pStatementObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
  initObject(Statement,  pStatementObj,  AdtJavaStatement,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaIfThenStatement::AdtJavaIfThenStatement(const AdtJavaIfThenStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
  copyObject(Statement,  rCopy, AdtJavaStatement );
}

//  ----------------------------------------------------------------------------

AdtJavaIfThenStatement::~AdtJavaIfThenStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaIfThenStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaIfThenStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "if (");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");
  rOutFile.newline();

  if (Statement != 0)
  {
    Statement->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaIfThenStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaIfThenElseStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaIfThenElseStatement::AdtJavaIfThenElseStatement(AdtParser* pExpressionObj,
                                                       AdtParser* pStatementNoShortIfObj,
                                                       AdtParser* pStatementObj,
                                                       bool bNoShortIf)
 : AdtJavaBase()
{
  initObject(Expression,          pExpressionObj,         AdtJavaExpression, false);
  initObject(StatementNoShortIf,  pStatementNoShortIfObj, AdtJavaStatement,  false);
  initObject(Statement,           pStatementObj,          AdtJavaStatement,  false);

  NoShortIf = bNoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaIfThenElseStatement::AdtJavaIfThenElseStatement(const AdtJavaIfThenElseStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression,          rCopy, AdtJavaExpression);
  copyObject(StatementNoShortIf,  rCopy, AdtJavaStatement );
  copyObject(Statement,           rCopy, AdtJavaStatement );

  NoShortIf = rCopy.NoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaIfThenElseStatement::~AdtJavaIfThenElseStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(StatementNoShortIf);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaIfThenElseStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaIfThenElseStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "if (");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");
  rOutFile.newline();

  if (StatementNoShortIf != 0)
  {
    StatementNoShortIf->writeJava(rOutFile);
  }

  if (Statement != 0)
  {
    write(rOutFile, "else");
    rOutFile.newline();

    Statement->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaIfThenElseStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaSwitchStatement::AdtJavaSwitchStatement(AdtParser* pExpressionObj,
                                               AdtParser* pSwitchBlockObj)
 : AdtJavaBase()
{
  initObject(Expression,  pExpressionObj,   AdtJavaExpression,  false);
  initObject(SwitchBlock, pSwitchBlockObj,  AdtJavaSwitchBlock, false);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchStatement::AdtJavaSwitchStatement(const AdtJavaSwitchStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression,  rCopy, AdtJavaExpression);
  copyObject(SwitchBlock, rCopy, AdtJavaSwitchBlock);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchStatement::~AdtJavaSwitchStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(SwitchBlock);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "switch (");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");
  rOutFile.newline();

  if (SwitchBlock != 0)
  {
    SwitchBlock->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlock class
//  ----------------------------------------------------------------------------
AdtJavaSwitchBlock::AdtJavaSwitchBlock(AdtParser* pSwitchLabelsObj,
                                       AdtParser* pSwitchBlockStatementGroupsObj)
 : AdtJavaBase()
{
  initObject(SwitchLabels,               pSwitchLabelsObj,                AdtJavaSwitchLabels,               false);
  initObject(SwitchBlockStatementGroups, pSwitchBlockStatementGroupsObj,  AdtJavaSwitchBlockStatementGroups, false);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlock::AdtJavaSwitchBlock(const AdtJavaSwitchBlock& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(SwitchLabels,               rCopy, AdtJavaSwitchLabels              );
  copyObject(SwitchBlockStatementGroups, rCopy, AdtJavaSwitchBlockStatementGroups);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlock::~AdtJavaSwitchBlock()
{
  UtlReleaseReference(SwitchLabels);
  UtlReleaseReference(SwitchBlockStatementGroups);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlock::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlock::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "{");
  rOutFile.incrementIndent();
  rOutFile.newline();

  if (SwitchBlockStatementGroups != 0)
  {
    SwitchBlockStatementGroups->writeJava(rOutFile);
  }

  if (SwitchLabels != 0)
  {
    SwitchLabels->writeJava(rOutFile);
  }

  rOutFile.decrementIndent();
  rOutFile.newline();
  write(rOutFile, "}");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchBlock, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlockStatementGroups method implementations
//  ----------------------------------------------------------------------------
AdtJavaSwitchBlockStatementGroups::AdtJavaSwitchBlockStatementGroups(AdtParser* pSwitchBlockStatementGroupObj)
 : AdtJavaBase()
{
  add(pSwitchBlockStatementGroupObj);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlockStatementGroups::AdtJavaSwitchBlockStatementGroups(const AdtJavaSwitchBlockStatementGroups& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlockStatementGroups::~AdtJavaSwitchBlockStatementGroups()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlockStatementGroups::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, true, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlockStatementGroups::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, true, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchBlockStatementGroups, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlockStatementGroup method implementations
//  ----------------------------------------------------------------------------
AdtJavaSwitchBlockStatementGroup::AdtJavaSwitchBlockStatementGroup(AdtParser* pSwitchLabelsObj,
                                                                   AdtParser* pBlockStatementsObj)
 : AdtJavaBase()
{
  initObject(SwitchLabels,    pSwitchLabelsObj,     AdtJavaSwitchLabels,    false);
  initObject(BlockStatements, pBlockStatementsObj,  AdtJavaBlockStatements, false);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlockStatementGroup::AdtJavaSwitchBlockStatementGroup(const AdtJavaSwitchBlockStatementGroup& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(SwitchLabels,    rCopy, AdtJavaSwitchLabels   );
  copyObject(BlockStatements, rCopy, AdtJavaBlockStatements);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchBlockStatementGroup::~AdtJavaSwitchBlockStatementGroup()
{
  UtlReleaseReference(SwitchLabels);
  UtlReleaseReference(BlockStatements);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlockStatementGroup::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchBlockStatementGroup::writeJava(AdtFile& rOutFile) const
{
  if (SwitchLabels != 0)
  {
    SwitchLabels->writeJava(rOutFile);
  }

  rOutFile.incrementIndent();
  rOutFile.newline();

  if (BlockStatements != 0)
  {
    BlockStatements->writeJava(rOutFile);
  }

  rOutFile.decrementIndent();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchBlockStatementGroup, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchLabels class
//  ----------------------------------------------------------------------------
AdtJavaSwitchLabels::AdtJavaSwitchLabels(AdtParser* pSwitchLabelObj)
 : AdtJavaBase()
{
  add(pSwitchLabelObj);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchLabels::AdtJavaSwitchLabels(const AdtJavaSwitchLabels& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaSwitchLabels::~AdtJavaSwitchLabels()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchLabels::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchLabels::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, true, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchLabels, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchLabel method implementations
//  ----------------------------------------------------------------------------
AdtJavaSwitchLabel::AdtJavaSwitchLabel(AdtParser* pExpressionObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchLabel::AdtJavaSwitchLabel(const AdtJavaSwitchLabel& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaSwitchLabel::~AdtJavaSwitchLabel()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchLabel::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSwitchLabel::writeJava(AdtFile& rOutFile) const
{
  if (Expression != 0)
  {
    write(rOutFile, "case ");
    Expression->writeJava(rOutFile);
  }
  else
  {
    write(rOutFile, "default");
  }

  write(rOutFile, ": ");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSwitchLabel, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaWhileStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaWhileStatement::AdtJavaWhileStatement(AdtParser* pExpressionObj,
                                             AdtParser* pStatementObj,
                                             bool bNoShortIf)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
  initObject(Statement,  pStatementObj,  AdtJavaStatement,  false);

  NoShortIf = bNoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaWhileStatement::AdtJavaWhileStatement(const AdtJavaWhileStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
  copyObject(Statement,  rCopy, AdtJavaStatement );

  NoShortIf = rCopy.NoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaWhileStatement::~AdtJavaWhileStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaWhileStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaWhileStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "while(");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");
  rOutFile.newline();

  if (Statement != 0)
  {
    Statement->writeJava(rOutFile);
  }

  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaWhileStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaDoStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaDoStatement::AdtJavaDoStatement(AdtParser* pExpressionObj,
                                       AdtParser* pStatementObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
  initObject(Statement,  pStatementObj,  AdtJavaStatement,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaDoStatement::AdtJavaDoStatement(const AdtJavaDoStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
  copyObject(Statement,  rCopy, AdtJavaStatement );
}

//  ----------------------------------------------------------------------------

AdtJavaDoStatement::~AdtJavaDoStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDoStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDoStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "do ");
  rOutFile.newline();

  if (Statement != 0)
  {
    Statement->writeJava(rOutFile);
  }

  rOutFile.newline();
  write(rOutFile, "while(");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ");");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaDoStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaForStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaForStatement::AdtJavaForStatement(AdtParser* pForInitObj,
                                         AdtParser* pExpressionObj,
                                         AdtParser* pStatementExpressionListObj,
                                         AdtParser* pStatementObj,
                                         bool bNoShortIf)
 : AdtJavaBase()
{
  initObject(ForInit,                 pForInitObj,                  AdtJavaForInit,                 false);
  initObject(Expression,              pExpressionObj,               AdtJavaExpression,              false);
  initObject(StatementExpressionList, pStatementExpressionListObj,  AdtJavaStatementExpressionList, false);
  initObject(Statement,               pStatementObj,                AdtJavaStatement,               false);

  NoShortIf = bNoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaForStatement::AdtJavaForStatement(const AdtJavaForStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ForInit,                 rCopy, AdtJavaForInit);
  copyObject(Expression,              rCopy, AdtJavaExpression);
  copyObject(StatementExpressionList, rCopy, AdtJavaStatementExpressionList);
  copyObject(Statement,               rCopy, AdtJavaStatement);

  NoShortIf = rCopy.NoShortIf;
}

//  ----------------------------------------------------------------------------

AdtJavaForStatement::~AdtJavaForStatement()
{
  UtlReleaseReference(ForInit);
  UtlReleaseReference(Expression);
  UtlReleaseReference(StatementExpressionList);
  UtlReleaseReference(Statement);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaForStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaForStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "for (");

  if (ForInit != 0)
  {
    ForInit->writeJava(rOutFile);
  }

  write(rOutFile, " ; ");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, " ; ");

  if (StatementExpressionList != 0)
  {
    StatementExpressionList->writeJava(rOutFile);
  }

  write(rOutFile, ")");
  rOutFile.newline();

  if (Statement != 0)
  {
    Statement->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaForStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaForInit method implementations
//  ----------------------------------------------------------------------------
AdtJavaForInit::AdtJavaForInit(AdtParser* pTypeObj,
                               AdtParser* pStatementExpressionListObj,
                               AdtParser* pVariableDeclaratorsObj)
 : AdtJavaBase()
{
  initObject(Type,                    pTypeObj,                     AdtJavaType,                    false);
  initObject(StatementExpressionList, pStatementExpressionListObj,  AdtJavaStatementExpressionList, false);
  initObject(VariableDeclarators,     pVariableDeclaratorsObj,      AdtJavaVariableDeclarators,     false);
}

//  ----------------------------------------------------------------------------

AdtJavaForInit::AdtJavaForInit(const AdtJavaForInit& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Type,                    rCopy, AdtJavaType);
  copyObject(StatementExpressionList, rCopy, AdtJavaStatementExpressionList);
  copyObject(VariableDeclarators,     rCopy, AdtJavaVariableDeclarators);
}

//  ----------------------------------------------------------------------------

AdtJavaForInit::~AdtJavaForInit()
{
  UtlReleaseReference(Type);
  UtlReleaseReference(StatementExpressionList);
  UtlReleaseReference(VariableDeclarators);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaForInit::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaForInit::writeJava(AdtFile& rOutFile) const
{
  if (StatementExpressionList != 0)
  {
    StatementExpressionList->writeJava(rOutFile);
  }

  if (Type != 0)
  {
    Type->writeJava(rOutFile);
  }

  if (VariableDeclarators != 0)
  {
    VariableDeclarators->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaForInit, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaStatementExpressionList method implementations
//  ----------------------------------------------------------------------------
AdtJavaStatementExpressionList::AdtJavaStatementExpressionList(AdtParser* pStatementExpressionObj)
 : AdtJavaBase()
{
  add(pStatementExpressionObj);
}

//  ----------------------------------------------------------------------------

AdtJavaStatementExpressionList::AdtJavaStatementExpressionList(const AdtJavaStatementExpressionList& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaStatementExpressionList::~AdtJavaStatementExpressionList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementExpressionList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaStatementExpressionList::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaStatementExpressionList, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaBreakStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaBreakStatement::AdtJavaBreakStatement(const char* pIdentifier)
 : AdtJavaBase()
{
  name(pIdentifier);
}

//  ----------------------------------------------------------------------------

AdtJavaBreakStatement::AdtJavaBreakStatement(const AdtJavaBreakStatement& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaBreakStatement::~AdtJavaBreakStatement()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBreakStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaBreakStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "break ");
  write(rOutFile, name());
  write(rOutFile, ";");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaBreakStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaContinueStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaContinueStatement::AdtJavaContinueStatement(const char* pIdentifier)
 : AdtJavaBase()
{
  name(pIdentifier);
}

//  ----------------------------------------------------------------------------

AdtJavaContinueStatement::AdtJavaContinueStatement(const AdtJavaContinueStatement& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaContinueStatement::~AdtJavaContinueStatement()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaContinueStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaContinueStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "continue ");
  write(rOutFile, name());
  write(rOutFile, ";");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaContinueStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaReturnStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaReturnStatement::AdtJavaReturnStatement(AdtParser* pExpressionObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaReturnStatement::AdtJavaReturnStatement(const AdtJavaReturnStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaReturnStatement::~AdtJavaReturnStatement()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaReturnStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaReturnStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "return ");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ";");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaReturnStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaThrowStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaThrowStatement::AdtJavaThrowStatement(AdtParser* pExpressionObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaThrowStatement::AdtJavaThrowStatement(const AdtJavaThrowStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaThrowStatement::~AdtJavaThrowStatement()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaThrowStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaThrowStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "throw ");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ";");
  rOutFile.newline();

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaThrowStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaSynchronizedStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaSynchronizedStatement::AdtJavaSynchronizedStatement(AdtParser* pExpressionObj,
                                                           AdtParser* pBlockObj)
 : AdtJavaBase()
{
  initObject(Expression,  pExpressionObj, AdtJavaExpression,  false);
  initObject(Block,       pBlockObj,      AdtJavaBlock,       false);
}

//  ----------------------------------------------------------------------------

AdtJavaSynchronizedStatement::AdtJavaSynchronizedStatement(const AdtJavaSynchronizedStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression,  rCopy, AdtJavaExpression);
  copyObject(Block,       rCopy, AdtJavaBlock);
}

//  ----------------------------------------------------------------------------

AdtJavaSynchronizedStatement::~AdtJavaSynchronizedStatement()
{
  UtlReleaseReference(Expression);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSynchronizedStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaSynchronizedStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "synchronised(");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaSynchronizedStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaTryStatement method implementations
//  ----------------------------------------------------------------------------
AdtJavaTryStatement::AdtJavaTryStatement(AdtParser* pBlockObj,
                                         AdtParser* pCatchesObj,
                                         AdtParser* pFinallyObj)
 : AdtJavaBase()
{
  initObject(Block,   pBlockObj,    AdtJavaBlock,   false);
  initObject(Catches, pCatchesObj,  AdtJavaCatches, false);
  initObject(Finally, pFinallyObj,  AdtJavaFinally, false);
}

//  ----------------------------------------------------------------------------

AdtJavaTryStatement::AdtJavaTryStatement(const AdtJavaTryStatement& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Block,   rCopy, AdtJavaBlock);
  copyObject(Catches, rCopy, AdtJavaCatches);
  copyObject(Finally, rCopy, AdtJavaFinally);
}

//  ----------------------------------------------------------------------------

AdtJavaTryStatement::~AdtJavaTryStatement()
{
  UtlReleaseReference(Block);
  UtlReleaseReference(Catches);
  UtlReleaseReference(Finally);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTryStatement::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaTryStatement::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "try ");

  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }

  if (Catches != 0)
  {
    Catches->writeJava(rOutFile);
  }

  if (Finally != 0)
  {
    Finally->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaTryStatement, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaCatches class
//  ----------------------------------------------------------------------------
AdtJavaCatches::AdtJavaCatches(AdtParser* pCatchClauseObj)
 : AdtJavaBase()
{
  add(pCatchClauseObj);
}

//  ----------------------------------------------------------------------------

AdtJavaCatches::AdtJavaCatches(const AdtJavaCatches& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaCatches::~AdtJavaCatches()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCatches::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCatches::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, true, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaCatches, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaCatchClause method implementations
//  ----------------------------------------------------------------------------
AdtJavaCatchClause::AdtJavaCatchClause(AdtParser* pFormalParameterObj,
                                       AdtParser* pBlockObj)
 : AdtJavaBase()
{
  initObject(FormalParameter, pFormalParameterObj,  AdtJavaFormalParameter, false);
  initObject(Block,           pBlockObj,            AdtJavaBlock,           false);
}

//  ----------------------------------------------------------------------------

AdtJavaCatchClause::AdtJavaCatchClause(const AdtJavaCatchClause& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(FormalParameter, rCopy, AdtJavaFormalParameter);
  copyObject(Block,           rCopy, AdtJavaBlock          );
}

//  ----------------------------------------------------------------------------

AdtJavaCatchClause::~AdtJavaCatchClause()
{
  UtlReleaseReference(FormalParameter);
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCatchClause::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCatchClause::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "catch(");

  if (FormalParameter != 0)
  {
    FormalParameter->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaCatchClause, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaFinally method implementations
//  ----------------------------------------------------------------------------
AdtJavaFinally::AdtJavaFinally(AdtParser* pBlockObj)
 : AdtJavaBase()
{
  initObject(Block, pBlockObj, AdtJavaBlock, false);
}

//  ----------------------------------------------------------------------------

AdtJavaFinally::AdtJavaFinally(const AdtJavaFinally& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Block, rCopy, AdtJavaBlock);
}

//  ----------------------------------------------------------------------------

AdtJavaFinally::~AdtJavaFinally()
{
  UtlReleaseReference(Block);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFinally::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaFinally::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "finally");

  if (Block != 0)
  {
    Block->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaFinally, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPrimary method implementations
//  ----------------------------------------------------------------------------
AdtJavaPrimary::AdtJavaPrimary(AdtParser* pPrimaryNoNewArrayObj,
                               AdtParser* pPrimitiveTypeObj,
                               AdtParser* pDimExprsObj,
                               AdtParser* pDimsObj,
                               AdtParser* pNameObj)
 : AdtJavaBase()
{
  initObject(PrimaryNoNewArray, pPrimaryNoNewArrayObj,  AdtJavaPrimaryNoNewArray, false);
  initObject(PrimitiveType,     pPrimitiveTypeObj,      AdtJavaPrimitiveType,     false);
  initObject(DimExprs,          pDimExprsObj,           AdtJavaDimExprs,          false);
  initObject(Dims,              pDimsObj,               AdtJavaDims,              false);
  initObject(Name,              pNameObj,               AdtJavaName,              false);
}

//  ----------------------------------------------------------------------------

AdtJavaPrimary::AdtJavaPrimary(const AdtJavaPrimary& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(PrimaryNoNewArray, rCopy, AdtJavaPrimaryNoNewArray);
  copyObject(PrimitiveType,     rCopy, AdtJavaPrimitiveType);
  copyObject(DimExprs,          rCopy, AdtJavaDimExprs);
  copyObject(Dims,              rCopy, AdtJavaDims);
  copyObject(Name,              rCopy, AdtJavaName);
}

//  ----------------------------------------------------------------------------

AdtJavaPrimary::~AdtJavaPrimary()
{
  UtlReleaseReference(PrimaryNoNewArray);
  UtlReleaseReference(PrimitiveType);
  UtlReleaseReference(DimExprs);
  UtlReleaseReference(Dims);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimary::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimary::writeJava(AdtFile& rOutFile) const
{
  if (PrimaryNoNewArray != 0)
  {
    PrimaryNoNewArray->writeJava(rOutFile);
  }
  else
  {
    write(rOutFile, "new ");

    if (PrimitiveType != 0)
    {
      PrimitiveType->writeJava(rOutFile);
    }

    if (Name != 0)
    {
      Name->writeJava(rOutFile);
    }

    if (DimExprs != 0)
    {
      DimExprs->writeJava(rOutFile);
    }

    if (Dims != 0)
    {
      Dims->writeJava(rOutFile);
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPrimary, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPrimaryNoNewArray method implementations
//  ----------------------------------------------------------------------------
AdtJavaPrimaryNoNewArray::AdtJavaPrimaryNoNewArray(const char* pIdentifier,
                                                   AdtParser* pLiteralObj,
                                                   AdtParser* pExpressionObj,
                                                   AdtParser* pClassInstanceCreationExpressionObj,
                                                   AdtParser* pPrimaryObj,
                                                   AdtParser* pMethodInvocationObj,
                                                   AdtParser* pNameObj,
                                                   AdtParser* pPrimaryNoNewArrayObj,
                                                   bool bIsSuper)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(Literal,           pLiteralObj,            AdtJavaLiteral,           false);
  initObject(Expression,        pExpressionObj,         AdtJavaExpression,        false);
  initObject(ClassInstanceCreationExpression, pClassInstanceCreationExpressionObj, AdtJavaClassInstanceCreationExpression, false);
  initObject(Primary,           pPrimaryObj,            AdtJavaPrimary,           false);
  initObject(MethodInvocation,  pMethodInvocationObj,   AdtJavaMethodInvocation,  false);
  initObject(Name,              pNameObj,               AdtJavaName,              false);
  initObject(PrimaryNoNewArray, pPrimaryNoNewArrayObj,  AdtJavaPrimaryNoNewArray, false);

  IsSuper = bIsSuper;
}

//  ----------------------------------------------------------------------------

AdtJavaPrimaryNoNewArray::AdtJavaPrimaryNoNewArray(const AdtJavaPrimaryNoNewArray& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Literal,                         rCopy, AdtJavaLiteral);
  copyObject(Expression,                      rCopy, AdtJavaExpression);
  copyObject(ClassInstanceCreationExpression, rCopy, AdtJavaClassInstanceCreationExpression);
  copyObject(Primary,                         rCopy, AdtJavaPrimary);
  copyObject(MethodInvocation,                rCopy, AdtJavaMethodInvocation);
  copyObject(Name,                            rCopy, AdtJavaName);
  copyObject(PrimaryNoNewArray,               rCopy, AdtJavaPrimaryNoNewArray);

  IsSuper = rCopy.IsSuper;
}

//  ----------------------------------------------------------------------------

AdtJavaPrimaryNoNewArray::~AdtJavaPrimaryNoNewArray()
{
  UtlReleaseReference(Literal);
  UtlReleaseReference(Expression);
  UtlReleaseReference(ClassInstanceCreationExpression);
  UtlReleaseReference(Primary);
  UtlReleaseReference(MethodInvocation);
  UtlReleaseReference(Name);
  UtlReleaseReference(PrimaryNoNewArray);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimaryNoNewArray::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPrimaryNoNewArray::writeJava(AdtFile& rOutFile) const
{
  bool bHasIndex = false;

  if (Literal != 0)
  {
    Literal->writeJava(rOutFile);
  }
  else if (ClassInstanceCreationExpression != 0)
  {
    ClassInstanceCreationExpression->writeJava(rOutFile);
  }
  else if (Primary != 0)
  {
    Primary->writeJava(rOutFile);
    write(rOutFile, ".");
    write(rOutFile, name());
  }
  else if (Name != 0)
  {
    Name->writeJava(rOutFile);

    bHasIndex = true;
  }
  else if (PrimaryNoNewArray != 0)
  {
    PrimaryNoNewArray->writeJava(rOutFile);

    bHasIndex = true;
  }
  else if (IsSuper)
  {
    write(rOutFile, "super.");
    write(rOutFile, name());
  }
  else if (Expression != 0)
  {
    write(rOutFile, "(");
    Expression->writeJava(rOutFile);
    write(rOutFile, ")");
  }
  else
  {
    write(rOutFile, "this");
  }

  if (bHasIndex)
  {
    write(rOutFile, "[");

    if (Expression != 0)
    {
      Expression->writeJava(rOutFile);
    }

    write(rOutFile, "]");
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPrimaryNoNewArray, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaClassInstanceCreationExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaClassInstanceCreationExpression::AdtJavaClassInstanceCreationExpression(AdtParser* pNameObj,
                                                                               AdtParser* pArgumentListObj)
 : AdtJavaBase()
{
  initObject(Name,          pNameObj,         AdtJavaName,          false);
  initObject(ArgumentList,  pArgumentListObj, AdtJavaArgumentList,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaClassInstanceCreationExpression::AdtJavaClassInstanceCreationExpression(const AdtJavaClassInstanceCreationExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name,          rCopy, AdtJavaName);
  copyObject(ArgumentList,  rCopy, AdtJavaArgumentList);
}

//  ----------------------------------------------------------------------------

AdtJavaClassInstanceCreationExpression::~AdtJavaClassInstanceCreationExpression()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(ArgumentList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassInstanceCreationExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaClassInstanceCreationExpression::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "new ");

  if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }

  write(rOutFile, "(");

  if (ArgumentList != 0)
  {
    ArgumentList->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaClassInstanceCreationExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaArgumentList method implementations
//  ----------------------------------------------------------------------------
AdtJavaArgumentList::AdtJavaArgumentList(AdtParser* pExpressionObj)
 : AdtJavaBase()
{
  add(pExpressionObj);
}

//  ----------------------------------------------------------------------------

AdtJavaArgumentList::AdtJavaArgumentList(const AdtJavaArgumentList& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaArgumentList::~AdtJavaArgumentList()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaArgumentList::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, ",", false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaArgumentList::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, ",", false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaArgumentList, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaDimExprs method implementations
//  ----------------------------------------------------------------------------
AdtJavaDimExprs::AdtJavaDimExprs(AdtParser* pDimExprObj)
 : AdtJavaBase()
{
  add(pDimExprObj);
}

//  ----------------------------------------------------------------------------

AdtJavaDimExprs::AdtJavaDimExprs(const AdtJavaDimExprs& rCopy)
 : AdtJavaBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtJavaDimExprs::~AdtJavaDimExprs()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDimExprs::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (forAllWriteFortran(rOutFile, nMode, 0, false, true));
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDimExprs::writeJava(AdtFile& rOutFile) const
{
  return (forAllWriteJava(rOutFile, 0, false, true));
}

//  ----------------------------------------------------------------------------

implType(AdtJavaDimExprs, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaDimExpr method implementations
//  ----------------------------------------------------------------------------
AdtJavaDimExpr::AdtJavaDimExpr(AdtParser* pExpressionObj)
 : AdtJavaBase()
{
  initObject(Expression, pExpressionObj, AdtJavaExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaDimExpr::AdtJavaDimExpr(const AdtJavaDimExpr& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Expression, rCopy, AdtJavaExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaDimExpr::~AdtJavaDimExpr()
{
  UtlReleaseReference(Expression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDimExpr::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDimExpr::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "[");

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, "]");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaDimExpr, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaDims method implementations
//  ----------------------------------------------------------------------------
AdtJavaDims::AdtJavaDims(AdtParser* pDimsObj)
 : AdtJavaBase()
{
  initObject(Dims, pDimsObj, AdtJavaDims, false);
}

//  ----------------------------------------------------------------------------

AdtJavaDims::AdtJavaDims(const AdtJavaDims& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Dims, rCopy, AdtJavaDims);
}

//  ----------------------------------------------------------------------------

AdtJavaDims::~AdtJavaDims()
{
  UtlReleaseReference(Dims);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDims::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaDims::writeJava(AdtFile& rOutFile) const
{
  if (Dims != 0)
  {
    Dims->writeJava(rOutFile);
  }

  write(rOutFile, "[]");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaDims, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaMethodInvocation method implementations
//  ----------------------------------------------------------------------------
AdtJavaMethodInvocation::AdtJavaMethodInvocation(const char* pIdentifier,
                                                 AdtParser* pNameObj,
                                                 AdtParser* pPrimaryObj,
                                                 AdtParser* pArgumentListObj)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(Name,          pNameObj,         AdtJavaName,          false);
  initObject(Primary,       pPrimaryObj,      AdtJavaPrimary,       false);
  initObject(ArgumentList,  pArgumentListObj, AdtJavaArgumentList,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaMethodInvocation::AdtJavaMethodInvocation(const AdtJavaMethodInvocation& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name,          rCopy, AdtJavaName);
  copyObject(Primary,       rCopy, AdtJavaPrimary);
  copyObject(ArgumentList,  rCopy, AdtJavaArgumentList);
}

//  ----------------------------------------------------------------------------

AdtJavaMethodInvocation::~AdtJavaMethodInvocation()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Primary);
  UtlReleaseReference(ArgumentList);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodInvocation::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMethodInvocation::writeJava(AdtFile& rOutFile) const
{
  if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }

  if (name().length() > 0)
  {
    if (Primary != 0)
    {
      Primary->writeJava(rOutFile);
    }
    else
    {
      write(rOutFile, "super");
    }

    write(rOutFile, ".");
    write(rOutFile, name());
  }

  write(rOutFile, "(");

  if (ArgumentList != 0)
  {
    ArgumentList->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaMethodInvocation, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPostfixExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaPostfixExpression::AdtJavaPostfixExpression(AdtParser* pNameObj,
                                                   AdtParser* pPrimaryObj,
                                                   AdtParser* pPostIncDecExpressionObj)
 : AdtJavaBase()
{
  initObject(Name,                  pNameObj,                 AdtJavaName,                  false);
  initObject(Primary,               pPrimaryObj,              AdtJavaPrimary,               false);
  initObject(PostIncDecExpression,  pPostIncDecExpressionObj, AdtJavaPostIncDecExpression,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaPostfixExpression::AdtJavaPostfixExpression(const AdtJavaPostfixExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name,                  rCopy, AdtJavaName);
  copyObject(Primary,               rCopy, AdtJavaPrimary);
  copyObject(PostIncDecExpression,  rCopy, AdtJavaPostIncDecExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaPostfixExpression::~AdtJavaPostfixExpression()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(Primary);
  UtlReleaseReference(PostIncDecExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPostfixExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPostfixExpression::writeJava(AdtFile& rOutFile) const
{
  if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }

  if (Primary != 0)
  {
    Primary->writeJava(rOutFile);
  }

  if (PostIncDecExpression != 0)
  {
    PostIncDecExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPostfixExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPostIncDecExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaPostIncDecExpression::AdtJavaPostIncDecExpression(AdtParser* pPostfixExpressionObj,
                                                         bool bIncrement)
 : AdtJavaBase()
{
  initObject(PostfixExpression, pPostfixExpressionObj,  AdtJavaPostfixExpression, false);

  Increment = bIncrement;
}

//  ----------------------------------------------------------------------------

AdtJavaPostIncDecExpression::AdtJavaPostIncDecExpression(const AdtJavaPostIncDecExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(PostfixExpression, rCopy, AdtJavaPostfixExpression);

  Increment = rCopy.Increment;
}

//  ----------------------------------------------------------------------------

AdtJavaPostIncDecExpression::~AdtJavaPostIncDecExpression()
{
  UtlReleaseReference(PostfixExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPostIncDecExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPostIncDecExpression::writeJava(AdtFile& rOutFile) const
{
  if (PostfixExpression != 0)
  {
    PostfixExpression->writeJava(rOutFile);

    if (Increment)
    {
      write(rOutFile, "++");
    }
    else
    {
      write(rOutFile, "--");
    }
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPostIncDecExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaPreIncDecExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaPreIncDecExpression::AdtJavaPreIncDecExpression(AdtParser* pUnaryExpressionObj,
                                                       bool bIncrement)
 : AdtJavaBase()
{
  initObject(UnaryExpression, pUnaryExpressionObj, AdtJavaUnaryExpression, false);

  Increment = bIncrement;
}

//  ----------------------------------------------------------------------------

AdtJavaPreIncDecExpression::AdtJavaPreIncDecExpression(const AdtJavaPreIncDecExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(UnaryExpression, rCopy, AdtJavaUnaryExpression);

  Increment = rCopy.Increment;
}

//  ----------------------------------------------------------------------------

AdtJavaPreIncDecExpression::~AdtJavaPreIncDecExpression()
{
  UtlReleaseReference(UnaryExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPreIncDecExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaPreIncDecExpression::writeJava(AdtFile& rOutFile) const
{
  if (UnaryExpression != 0)
  {
    if (Increment)
    {
      write(rOutFile, "++");
    }
    else
    {
      write(rOutFile, "--");
    }

    UnaryExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaPreIncDecExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaUnaryExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaUnaryExpression::AdtJavaUnaryExpression(AdtParser* pPreIncDecExpressionObj,
                                               AdtParser* pUnaryExpressionObj,
                                               AdtParser* pUnaryExpressionNotPlusMinusObj,
                                               bool bIsPlus)
 : AdtJavaBase()
{
  initObject(PreIncDecExpression,         pPreIncDecExpressionObj,          AdtJavaPreIncDecExpression,         false);
  initObject(UnaryExpression,             pUnaryExpressionObj,              AdtJavaUnaryExpression,             false);
  initObject(UnaryExpressionNotPlusMinus, pUnaryExpressionNotPlusMinusObj,  AdtJavaUnaryExpressionNotPlusMinus, false);

  IsPlus = bIsPlus;
}

//  ----------------------------------------------------------------------------

AdtJavaUnaryExpression::AdtJavaUnaryExpression(const AdtJavaUnaryExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(PreIncDecExpression,         rCopy, AdtJavaPreIncDecExpression);
  copyObject(UnaryExpression,             rCopy, AdtJavaUnaryExpression);
  copyObject(UnaryExpressionNotPlusMinus, rCopy, AdtJavaUnaryExpressionNotPlusMinus);

  IsPlus = rCopy.IsPlus;
}

//  ----------------------------------------------------------------------------

AdtJavaUnaryExpression::~AdtJavaUnaryExpression()
{
  UtlReleaseReference(PreIncDecExpression);
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(UnaryExpressionNotPlusMinus);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaUnaryExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaUnaryExpression::writeJava(AdtFile& rOutFile) const
{
  if (PreIncDecExpression != 0)
  {
    PreIncDecExpression->writeJava(rOutFile);
  }

  if (UnaryExpression != 0)
  {
    if (IsPlus)
    {
      write(rOutFile, "+");
    }
    else
    {
      write(rOutFile, "-");
    }

    UnaryExpression->writeJava(rOutFile);
  }

  if (UnaryExpressionNotPlusMinus != 0)
  {
    UnaryExpressionNotPlusMinus->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaUnaryExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaUnaryExpressionNotPlusMinus method implementations
//  ----------------------------------------------------------------------------
AdtJavaUnaryExpressionNotPlusMinus::AdtJavaUnaryExpressionNotPlusMinus(AdtParser* pPostfixExpressionObj,
                                                                       AdtParser* pUnaryExpressionObj,
                                                                       AdtParser* pCastExpressionObj,
                                                                       bool bLogical)
 : AdtJavaBase()
{
  initObject(PostfixExpression, pPostfixExpressionObj,  AdtJavaPostfixExpression, false);
  initObject(UnaryExpression,   pUnaryExpressionObj,    AdtJavaUnaryExpression,   false);
  initObject(CastExpression,    pCastExpressionObj,     AdtJavaCastExpression,    false);

  Logical = bLogical;
}

//  ----------------------------------------------------------------------------

AdtJavaUnaryExpressionNotPlusMinus::AdtJavaUnaryExpressionNotPlusMinus(const AdtJavaUnaryExpressionNotPlusMinus& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(PostfixExpression, rCopy, AdtJavaPostfixExpression);
  copyObject(UnaryExpression,   rCopy, AdtJavaUnaryExpression);
  copyObject(CastExpression,    rCopy, AdtJavaCastExpression);

  Logical = rCopy.Logical;
}

//  ----------------------------------------------------------------------------

AdtJavaUnaryExpressionNotPlusMinus::~AdtJavaUnaryExpressionNotPlusMinus()
{
  UtlReleaseReference(PostfixExpression);
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(CastExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaUnaryExpressionNotPlusMinus::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaUnaryExpressionNotPlusMinus::writeJava(AdtFile& rOutFile) const
{
  if (PostfixExpression != 0)
  {
    PostfixExpression->writeJava(rOutFile);
  }

  if (UnaryExpression != 0)
  {
    if (Logical)
    {
      write(rOutFile, "!");
    }
    else
    {
      write(rOutFile, "~");
    }

    UnaryExpression->writeJava(rOutFile);
  }

  if (CastExpression != 0)
  {
    CastExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaUnaryExpressionNotPlusMinus, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaCastExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaCastExpression::AdtJavaCastExpression(AdtParser* pPrimitiveTypeObj,
                                             AdtParser* pUnaryExpressionObj,
                                             AdtParser* pUnaryExpressionNotPlusMinusObj,
                                             AdtParser* pExpressionObj,
                                             AdtParser* pDimsObj,
                                             AdtParser* pNameObj)
 : AdtJavaBase()
{
  initObject(PrimitiveType,               pPrimitiveTypeObj,                AdtJavaPrimitiveType,               false);
  initObject(UnaryExpression,             pUnaryExpressionObj,              AdtJavaUnaryExpression,             false);
  initObject(UnaryExpressionNotPlusMinus, pUnaryExpressionNotPlusMinusObj,  AdtJavaUnaryExpressionNotPlusMinus, false);
  initObject(Expression,                  pExpressionObj,                   AdtJavaExpression,                  false);
  initObject(Dims,                        pDimsObj,                         AdtJavaDims,                        false);
  initObject(Name,                        pNameObj,                         AdtJavaName,                        false);
}

//  ----------------------------------------------------------------------------

AdtJavaCastExpression::AdtJavaCastExpression(const AdtJavaCastExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(PrimitiveType,               rCopy, AdtJavaPrimitiveType);
  copyObject(UnaryExpression,             rCopy, AdtJavaUnaryExpression);
  copyObject(UnaryExpressionNotPlusMinus, rCopy, AdtJavaUnaryExpressionNotPlusMinus);
  copyObject(Expression,                  rCopy, AdtJavaExpression);
  copyObject(Dims,                        rCopy, AdtJavaDims);
  copyObject(Name,                        rCopy, AdtJavaName);
}

//  ----------------------------------------------------------------------------

AdtJavaCastExpression::~AdtJavaCastExpression()
{
  UtlReleaseReference(PrimitiveType);
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(UnaryExpressionNotPlusMinus);
  UtlReleaseReference(Expression);
  UtlReleaseReference(Dims);
  UtlReleaseReference(Name);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCastExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaCastExpression::writeJava(AdtFile& rOutFile) const
{
  write(rOutFile, "(");

  if (PrimitiveType != 0)
  {
    PrimitiveType->writeJava(rOutFile);
  }

  if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }

  if (Dims != 0)
  {
    Dims->writeJava(rOutFile);
  }

  if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  write(rOutFile, ")");

  if (UnaryExpression != 0)
  {
    UnaryExpression->writeJava(rOutFile);
  }
  else if (UnaryExpressionNotPlusMinus != 0)
  {
    UnaryExpressionNotPlusMinus->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaCastExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaMultiplicativeExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaMultiplicativeExpression::AdtJavaMultiplicativeExpression(AdtParser* pUnaryExpressionObj,
                                                                 AdtParser* pMultiplicativeExpressionObj,
                                                                 AdtJavaMultOpEnum nOp)
 : AdtJavaBase()
{
  initObject(UnaryExpression,           pUnaryExpressionObj,          AdtJavaUnaryExpression,           false);
  initObject(MultiplicativeExpression,  pMultiplicativeExpressionObj, AdtJavaMultiplicativeExpression,  false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaMultiplicativeExpression::AdtJavaMultiplicativeExpression(const AdtJavaMultiplicativeExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(UnaryExpression,          rCopy, AdtJavaUnaryExpression);
  copyObject(MultiplicativeExpression, rCopy, AdtJavaMultiplicativeExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaMultiplicativeExpression::~AdtJavaMultiplicativeExpression()
{
  UtlReleaseReference(UnaryExpression);
  UtlReleaseReference(MultiplicativeExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMultiplicativeExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaMultiplicativeExpression::writeJava(AdtFile& rOutFile) const
{
  if (MultiplicativeExpression != 0)
  {
    const char* pOp = 0;

    MultiplicativeExpression->writeJava(rOutFile);

    switch (Op)
    {
      case JavaMultOp_MULTIPLY:
      {
        pOp = " * ";
        break;
      }

      case JavaMultOp_DIV:
      {
        pOp = " / ";
        break;
      }

      case JavaMultOp_MOD:
      {
        pOp = " % ";
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }

    write(rOutFile, pOp);
  }

  if (UnaryExpression != 0)
  {
    UnaryExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaMultiplicativeExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaAdditiveExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaAdditiveExpression::AdtJavaAdditiveExpression(AdtParser* pMultiplicativeExpressionObj,
                                                     AdtParser* pAdditiveExpressionObj,
                                                     AdtJavaAddOpEnum nOp)
 : AdtJavaBase()
{
  initObject(MultiplicativeExpression,  pMultiplicativeExpressionObj, AdtJavaMultiplicativeExpression,  false);
  initObject(AdditiveExpression,        pAdditiveExpressionObj,       AdtJavaAdditiveExpression,        false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaAdditiveExpression::AdtJavaAdditiveExpression(const AdtJavaAdditiveExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(MultiplicativeExpression,  rCopy, AdtJavaMultiplicativeExpression);
  copyObject(AdditiveExpression,        rCopy, AdtJavaAdditiveExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaAdditiveExpression::~AdtJavaAdditiveExpression()
{
  UtlReleaseReference(MultiplicativeExpression);
  UtlReleaseReference(AdditiveExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAdditiveExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAdditiveExpression::writeJava(AdtFile& rOutFile) const
{
  if (AdditiveExpression != 0)
  {
    const char* pOp = 0;

    AdditiveExpression->writeJava(rOutFile);

    switch (Op)
    {
      case JavaAddOp_PLUS:
      {
        pOp = " + ";
        break;
      }

      case JavaAddOp_MINUS:
      {
        pOp = " - ";
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }

    write(rOutFile, pOp);
  }

  if (MultiplicativeExpression != 0)
  {
    MultiplicativeExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaAdditiveExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaShiftExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaShiftExpression::AdtJavaShiftExpression(AdtParser* pAdditiveExpressionObj,
                                               AdtParser* pShiftExpressionObj,
                                               AdtJavaShiftOpEnum nOp)
 : AdtJavaBase()
{
  initObject(AdditiveExpression,  pAdditiveExpressionObj, AdtJavaAdditiveExpression,  false);
  initObject(ShiftExpression,     pShiftExpressionObj,    AdtJavaShiftExpression,     false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaShiftExpression::AdtJavaShiftExpression(const AdtJavaShiftExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(AdditiveExpression,  rCopy, AdtJavaAdditiveExpression);
  copyObject(ShiftExpression,     rCopy, AdtJavaShiftExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaShiftExpression::~AdtJavaShiftExpression()
{
  UtlReleaseReference(AdditiveExpression);
  UtlReleaseReference(ShiftExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaShiftExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaShiftExpression::writeJava(AdtFile& rOutFile) const
{
  if (ShiftExpression != 0)
  {
    const char* pOp = 0;

    ShiftExpression->writeJava(rOutFile);

    switch (Op)
    {
      case JavaShiftOp_SAL:
      {
        pOp = " << ";
        break;
      }

      case JavaShiftOp_SAR:
      {
        pOp = " >> ";
        break;
      }

      case JavaShiftOp_SHR:
      {
        pOp = " >>> ";
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }

    write(rOutFile, pOp);
  }

  if (AdditiveExpression != 0)
  {
    AdditiveExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaShiftExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaRelationalExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaRelationalExpression::AdtJavaRelationalExpression(AdtParser* pShiftExpressionObj,
                                                         AdtParser* pRelationalExpressionObj,
                                                         AdtParser* pNameObj,
                                                         AdtParser* pArrayTypeObj,
                                                         AdtJavaRelOpEnum nOp)
 : AdtJavaBase()
{
  initObject(ShiftExpression,       pShiftExpressionObj,      AdtJavaShiftExpression,       false);
  initObject(RelationalExpression,  pRelationalExpressionObj, AdtJavaRelationalExpression,  false);
  initObject(Name,                  pNameObj,                 AdtJavaName,                  false);
  initObject(ArrayType,             pArrayTypeObj,            AdtJavaType,                  false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaRelationalExpression::AdtJavaRelationalExpression(const AdtJavaRelationalExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ShiftExpression,       rCopy, AdtJavaShiftExpression);
  copyObject(RelationalExpression,  rCopy, AdtJavaRelationalExpression);
  copyObject(Name,                  rCopy, AdtJavaName);
  copyObject(ArrayType,             rCopy, AdtJavaType);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaRelationalExpression::~AdtJavaRelationalExpression()
{
  UtlReleaseReference(ShiftExpression);
  UtlReleaseReference(RelationalExpression);
  UtlReleaseReference(Name);
  UtlReleaseReference(ArrayType);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaRelationalExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaRelationalExpression::writeJava(AdtFile& rOutFile) const
{
  if (RelationalExpression != 0)
  {
    const char* pOp = 0;

    RelationalExpression->writeJava(rOutFile);

    switch (Op)
    {
      case JavaRelOp_LT:
      {
        pOp = " < ";
        break;
      }

      case JavaRelOp_GT:
      {
        pOp = " > ";
        break;
      }

      case JavaRelOp_LTE:
      {
        pOp = " <= ";
        break;
      }

      case JavaRelOp_GTE:
      {
        pOp = " >= ";
        break;
      }

      case JavaRelOp_INSTANCEOF:
      {
        pOp = " instanceof ";
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }

    write(rOutFile, pOp);
  }

  if (ShiftExpression != 0)
  {
    ShiftExpression->writeJava(rOutFile);
  }
  else if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }
  else if (ArrayType != 0)
  {
    ArrayType->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaRelationalExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaEqualityExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaEqualityExpression::AdtJavaEqualityExpression(AdtParser* pRelationalExpressionObj,
                                                     AdtParser* pEqualityExpressionObj,
                                                     AdtJavaEqualityOpEnum nOp)
 : AdtJavaBase()
{
  initObject(RelationalExpression,  pRelationalExpressionObj, AdtJavaRelationalExpression,  false);
  initObject(EqualityExpression,    pEqualityExpressionObj,   AdtJavaEqualityExpression,    false);

  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaEqualityExpression::AdtJavaEqualityExpression(const AdtJavaEqualityExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(RelationalExpression,  rCopy, AdtJavaRelationalExpression);
  copyObject(EqualityExpression,    rCopy, AdtJavaEqualityExpression);

  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaEqualityExpression::~AdtJavaEqualityExpression()
{
  UtlReleaseReference(RelationalExpression);
  UtlReleaseReference(EqualityExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaEqualityExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaEqualityExpression::writeJava(AdtFile& rOutFile) const
{
  if (EqualityExpression != 0)
  {
    const char* pOp = 0;

    EqualityExpression->writeJava(rOutFile);

    switch (Op)
    {
      case AdtJavaEqualityOp_EQ:
      {
        pOp = " == ";
        break;
      }

      case AdtJavaEqualityOp_NE:
      {
        pOp = " != ";
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }

    write(rOutFile, pOp);
  }

  if (RelationalExpression != 0)
  {
    RelationalExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaEqualityExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaAndExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaAndExpression::AdtJavaAndExpression(AdtParser* pEqualityExpressionObj,
                                           AdtParser* pAndExpressionObj)
 : AdtJavaBase()
{
  initObject(EqualityExpression,  pEqualityExpressionObj, AdtJavaEqualityExpression,  false);
  initObject(AndExpression,       pAndExpressionObj,      AdtJavaAndExpression,       false);
}

//  ----------------------------------------------------------------------------

AdtJavaAndExpression::AdtJavaAndExpression(const AdtJavaAndExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(EqualityExpression,  rCopy, AdtJavaEqualityExpression);
  copyObject(AndExpression,       rCopy, AdtJavaAndExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaAndExpression::~AdtJavaAndExpression()
{
  UtlReleaseReference(EqualityExpression);
  UtlReleaseReference(AndExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAndExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAndExpression::writeJava(AdtFile& rOutFile) const
{
  if (AndExpression != 0)
  {
    AndExpression->writeJava(rOutFile);
    write(rOutFile, " & ");
  }

  if (EqualityExpression != 0)
  {
    EqualityExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaAndExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaExclusiveOrExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaExclusiveOrExpression::AdtJavaExclusiveOrExpression(AdtParser* pAndExpressionObj,
                                                           AdtParser* pExclusiveOrExpressionObj)
 : AdtJavaBase()
{
  initObject(AndExpression,         pAndExpressionObj,          AdtJavaAndExpression,         false);
  initObject(ExclusiveOrExpression, pExclusiveOrExpressionObj,  AdtJavaExclusiveOrExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaExclusiveOrExpression::AdtJavaExclusiveOrExpression(const AdtJavaExclusiveOrExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(AndExpression,         rCopy, AdtJavaAndExpression);
  copyObject(ExclusiveOrExpression, rCopy, AdtJavaExclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaExclusiveOrExpression::~AdtJavaExclusiveOrExpression()
{
  UtlReleaseReference(AndExpression);
  UtlReleaseReference(ExclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExclusiveOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExclusiveOrExpression::writeJava(AdtFile& rOutFile) const
{
  if (ExclusiveOrExpression != 0)
  {
    ExclusiveOrExpression->writeJava(rOutFile);
    write(rOutFile, " ^ ");
  }

  if (AndExpression != 0)
  {
    AndExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaExclusiveOrExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaInclusiveOrExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaInclusiveOrExpression::AdtJavaInclusiveOrExpression(AdtParser* pExclusiveOrExpressionObj,
                                                           AdtParser* pInclusiveOrExpressionObj)
 : AdtJavaBase()
{
  initObject(ExclusiveOrExpression, pExclusiveOrExpressionObj,  AdtJavaExclusiveOrExpression, false);
  initObject(InclusiveOrExpression, pInclusiveOrExpressionObj,  AdtJavaInclusiveOrExpression, false);
}

//  ----------------------------------------------------------------------------

AdtJavaInclusiveOrExpression::AdtJavaInclusiveOrExpression(const AdtJavaInclusiveOrExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ExclusiveOrExpression, rCopy, AdtJavaExclusiveOrExpression);
  copyObject(InclusiveOrExpression, rCopy, AdtJavaInclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaInclusiveOrExpression::~AdtJavaInclusiveOrExpression()
{
  UtlReleaseReference(ExclusiveOrExpression);
  UtlReleaseReference(InclusiveOrExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInclusiveOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaInclusiveOrExpression::writeJava(AdtFile& rOutFile) const
{
  if (InclusiveOrExpression != 0)
  {
    InclusiveOrExpression->writeJava(rOutFile);
    write(rOutFile, " | ");
  }

  if (ExclusiveOrExpression != 0)
  {
    ExclusiveOrExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaInclusiveOrExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalAndExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaConditionalAndExpression::AdtJavaConditionalAndExpression(AdtParser* pInclusiveOrExpressionObj,
                                                                 AdtParser* pConditionalAndExpressionObj)
 : AdtJavaBase()
{
  initObject(InclusiveOrExpression,     pInclusiveOrExpressionObj,    AdtJavaInclusiveOrExpression,     false);
  initObject(ConditionalAndExpression,  pConditionalAndExpressionObj, AdtJavaConditionalAndExpression,  false);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalAndExpression::AdtJavaConditionalAndExpression(const AdtJavaConditionalAndExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(InclusiveOrExpression,     rCopy, AdtJavaInclusiveOrExpression);
  copyObject(ConditionalAndExpression,  rCopy, AdtJavaConditionalAndExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalAndExpression::~AdtJavaConditionalAndExpression()
{
  UtlReleaseReference(InclusiveOrExpression);
  UtlReleaseReference(ConditionalAndExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalAndExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalAndExpression::writeJava(AdtFile& rOutFile) const
{
  if (ConditionalAndExpression != 0)
  {
    ConditionalAndExpression->writeJava(rOutFile);
    write(rOutFile, " && ");
  }

  if (InclusiveOrExpression != 0)
  {
    InclusiveOrExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConditionalAndExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalOrExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaConditionalOrExpression::AdtJavaConditionalOrExpression(AdtParser* pConditionalAndExpressionObj,
                                                                 AdtParser* pConditionalOrExpressionObj)
 : AdtJavaBase()
{
  initObject(ConditionalAndExpression,  pConditionalAndExpressionObj, AdtJavaConditionalAndExpression,  false);
  initObject(ConditionalOrExpression,   pConditionalOrExpressionObj,  AdtJavaConditionalOrExpression,   false);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalOrExpression::AdtJavaConditionalOrExpression(const AdtJavaConditionalOrExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ConditionalAndExpression,  rCopy, AdtJavaConditionalAndExpression);
  copyObject(ConditionalOrExpression,   rCopy, AdtJavaConditionalOrExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalOrExpression::~AdtJavaConditionalOrExpression()
{
  UtlReleaseReference(ConditionalAndExpression);
  UtlReleaseReference(ConditionalOrExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalOrExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalOrExpression::writeJava(AdtFile& rOutFile) const
{
  if (ConditionalOrExpression != 0)
  {
    ConditionalOrExpression->writeJava(rOutFile);
    write(rOutFile, " || ");
  }

  if (ConditionalAndExpression != 0)
  {
    ConditionalAndExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConditionalOrExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaConditionalExpression::AdtJavaConditionalExpression(AdtParser* pConditionalOrExpressionObj,
                                                           AdtParser* pExpressionObj,
                                                           AdtParser* pConditionalExpressionObj)
 : AdtJavaBase()
{
  initObject(ConditionalOrExpression, pConditionalOrExpressionObj,  AdtJavaConditionalOrExpression, false);
  initObject(Expression,              pExpressionObj,               AdtJavaExpression,              false);
  initObject(ConditionalExpression,   pConditionalExpressionObj,    AdtJavaConditionalExpression,   false);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalExpression::AdtJavaConditionalExpression(const AdtJavaConditionalExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ConditionalOrExpression, rCopy, AdtJavaConditionalOrExpression);
  copyObject(Expression,              rCopy, AdtJavaExpression);
  copyObject(ConditionalExpression,   rCopy, AdtJavaConditionalExpression);
}

//  ----------------------------------------------------------------------------

AdtJavaConditionalExpression::~AdtJavaConditionalExpression()
{
  UtlReleaseReference(ConditionalOrExpression);
  UtlReleaseReference(Expression);
  UtlReleaseReference(ConditionalExpression);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaConditionalExpression::writeJava(AdtFile& rOutFile) const
{
  if (Expression != 0)
  {
    write(rOutFile, " ? ");
    Expression->writeJava(rOutFile);
    write(rOutFile, " : ");
  }

  if (ConditionalOrExpression != 0)
  {
    ConditionalOrExpression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaConditionalExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaExpression method implementations
//  ----------------------------------------------------------------------------
AdtJavaExpression::AdtJavaExpression(AdtParser* pConditionalExpressionObj,
                                     AdtParser* pAssignmentObj)
 : AdtJavaBase()
{
  initObject(ConditionalExpression, pConditionalExpressionObj,  AdtJavaConditionalExpression, false);
  initObject(Assignment,            pAssignmentObj,             AdtJavaAssignment,            false);
}

//  ----------------------------------------------------------------------------

AdtJavaExpression::AdtJavaExpression(const AdtJavaExpression& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(ConditionalExpression, rCopy, AdtJavaConditionalExpression);
  copyObject(Assignment,            rCopy, AdtJavaAssignment);
}

//  ----------------------------------------------------------------------------

AdtJavaExpression::~AdtJavaExpression()
{
  UtlReleaseReference(ConditionalExpression);
  UtlReleaseReference(Assignment);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExpression::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaExpression::writeJava(AdtFile& rOutFile) const
{
  if (ConditionalExpression != 0)
  {
    ConditionalExpression->writeJava(rOutFile);
  }

  if (Assignment != 0)
  {
    Assignment->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaExpression, AdtJavaBase);


//  ----------------------------------------------------------------------------
//  AdtJavaAssignment method implementations
//  ----------------------------------------------------------------------------
AdtJavaAssignment::AdtJavaAssignment(const char* pIdentifier,
                                     AdtParser* pNameObj,
                                     AdtParser* pAssignmentOperatorObj,
                                     AdtParser* pExpressionObj,
                                     AdtParser* pPrimaryObj,
                                     AdtParser* pPrimaryNoNewArrayObj,
                                     AdtParser* pExpression2Obj,
                                     bool bIsSuper)
 : AdtJavaBase()
{
  name(pIdentifier);

  initObject(Name,                pNameObj,               AdtJavaName,                false);
  initObject(AssignmentOperator,  pAssignmentOperatorObj, AdtJavaAssignmentOperator,  false);
  initObject(Expression,          pExpressionObj,         AdtJavaExpression,          false);
  initObject(Expression2,         pExpression2Obj,        AdtJavaExpression,          false);
  initObject(Primary,             pPrimaryObj,            AdtJavaPrimary,             false);
  initObject(PrimaryNoNewArray,   pPrimaryNoNewArrayObj,  AdtJavaPrimaryNoNewArray,   false);

  IsSuper = bIsSuper;
}

//  ----------------------------------------------------------------------------

AdtJavaAssignment::AdtJavaAssignment(const AdtJavaAssignment& rCopy)
 : AdtJavaBase(rCopy)
{
  copyObject(Name,               rCopy, AdtJavaName);
  copyObject(AssignmentOperator, rCopy, AdtJavaAssignmentOperator);
  copyObject(Expression,         rCopy, AdtJavaExpression);
  copyObject(Expression2,        rCopy, AdtJavaExpression);
  copyObject(Primary,            rCopy, AdtJavaPrimary);
  copyObject(PrimaryNoNewArray,  rCopy, AdtJavaPrimaryNoNewArray);

  IsSuper = rCopy.IsSuper;
}

//  ----------------------------------------------------------------------------

AdtJavaAssignment::~AdtJavaAssignment()
{
  UtlReleaseReference(Name);
  UtlReleaseReference(AssignmentOperator);
  UtlReleaseReference(Expression);
  UtlReleaseReference(Expression2);
  UtlReleaseReference(Primary);
  UtlReleaseReference(PrimaryNoNewArray);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAssignment::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAssignment::writeJava(AdtFile& rOutFile) const
{
  bool bIdentifier = false;

  if (Name != 0)
  {
    Name->writeJava(rOutFile);
  }

  if (PrimaryNoNewArray != 0)
  {
    PrimaryNoNewArray->writeJava(rOutFile);
  }

  if (Primary != 0)
  {
    Primary->writeJava(rOutFile);

    bIdentifier = true;
  }
  else if (IsSuper)
  {
    write(rOutFile, "super");

    bIdentifier = true;
  }

  if (bIdentifier)
  {
    write(rOutFile, ".");
    write(rOutFile, name());
  }

  if ((Expression2 != 0) && (Expression != 0))
  {
    write(rOutFile, "[");
    Expression->writeJava(rOutFile);
    write(rOutFile, "]");
  }

  if (AssignmentOperator != 0)
  {
    AssignmentOperator->writeJava(rOutFile);
  }

  if (Expression2 != 0)
  {
    Expression2->writeJava(rOutFile);
  }
  else if (Expression != 0)
  {
    Expression->writeJava(rOutFile);
  }

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaAssignment, AdtJavaBase);



//  ----------------------------------------------------------------------------
//  AdtJavaAssignmentOperator method implementations
//  ----------------------------------------------------------------------------
AdtJavaAssignmentOperator::AdtJavaAssignmentOperator(AdtJavaAssignmentOpEnum nOp)
 : AdtJavaBase()
{
  Op = nOp;
}

//  ----------------------------------------------------------------------------

AdtJavaAssignmentOperator::AdtJavaAssignmentOperator(const AdtJavaAssignmentOperator& rCopy)
 : AdtJavaBase(rCopy)
{
  Op = rCopy.Op;
}

//  ----------------------------------------------------------------------------

AdtJavaAssignmentOperator::~AdtJavaAssignmentOperator()
{

}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAssignmentOperator::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtJavaAssignmentOperator::writeJava(AdtFile& rOutFile) const
{
  const char* pOp = 0;

  switch (Op)
  {
    case AdtJavaAssignmentOp_EQUALS:
    {
      pOp = " = ";
      break;
    }

    case AdtJavaAssignmentOp_TIMES_EQUALS:
    {
      pOp = " *= ";
      break;
    }

    case AdtJavaAssignmentOp_DIV_EQUALS:
    {
      pOp = " /= ";
      break;
    }

    case AdtJavaAssignmentOp_MOD_EQUALS:
    {
      pOp = " %= ";
      break;
    }

    case AdtJavaAssignmentOp_PLUS_EQUALS:
    {
      pOp = " += ";
      break;
    }

    case AdtJavaAssignmentOp_MINUS_EQUALS:
    {
      pOp = " -= ";
      break;
    }

    case AdtJavaAssignmentOp_SAL_EQUALS:
    {
      pOp = " <<= ";
      break;
    }

    case AdtJavaAssignmentOp_SAR_EQUALS:
    {
      pOp = " >>= ";
      break;
    }

    case AdtJavaAssignmentOp_SHR_EQUALS:
    {
      pOp = " >>>= ";
      break;
    }

    case AdtJavaAssignmentOp_AND_EQUALS:
    {
      pOp = " &= ";
      break;
    }

    case AdtJavaAssignmentOp_XOR_EQUALS:
    {
      pOp = " ^= ";
      break;
    }

    case AdtJavaAssignmentOp_OR_EQUALS:
    {
      pOp = " |= ";
      break;
    }

    default:
    {
      FAIL();
    }
  }

  write(rOutFile, pOp);

  return (rOutFile);
}

//  ----------------------------------------------------------------------------

implType(AdtJavaAssignmentOperator, AdtJavaBase);
