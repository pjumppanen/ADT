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
//    AdtJava.hpp
//
//  Purpose:
//    This file includes declarations of classes used to collate information
//    describing the Java file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTJAVA_HPP
#define __ADTJAVA_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void* adtJava_setRoot(void* pRoot);
C_FUNCTION void* adtJava_getRoot(void);
C_FUNCTION void  adtJava_releaseRoot(void);
C_FUNCTION void  adtJava_releaseObject(void* pObj);
C_FUNCTION void* adtJavaList_add(void* pList, void* pObj);
C_FUNCTION void* adtJavaGoal_Create(void* pPackageDeclarationObj, void* pImportDeclarationsObj, void* pTypeDeclarationsObj);
C_FUNCTION void* adtJavaLiteral_Create(const char* pLiteral, int nType);
C_FUNCTION void* adtJavaType_Create(void* pNameObj, void* pPrimitiveTypeObj, void* pArrayTypeObj, int nIsArray);
C_FUNCTION void* adtJavaPrimitiveType_Create(int nType);
C_FUNCTION void* adtJavaName(void* pNameObj, const char* pIdentifier, int nIsCpp);
C_FUNCTION void* adtJavaNameList(void* pNameObj);
C_FUNCTION void* adtJavaImportDeclarations(void* pImportDeclarationObj);
C_FUNCTION void* adtJavaImportDeclaration(void* pNameObj, int nHasPeriodMultiply);
C_FUNCTION void* adtJavaTypeDeclarations(void* pTypeDeclarationObj);
C_FUNCTION void* adtJavaTypeDeclaration(void* pClassDeclarationObj, void* pInterfaceDeclarationObj);
C_FUNCTION void* adtJavaPackageDeclaration(void* pNameObj);
C_FUNCTION void* adtJavaModifiers(void* pModifierObj);
C_FUNCTION void* adtJavaModifier(int nModifier);
C_FUNCTION void* adtJavaClassDeclaration(const char* pIdentifier, void* pModifiersObj, void* pNameObj, void* pNameListObj, void* pClassBodyDeclarationsObj);
C_FUNCTION void* adtJavaClassBodyDeclarations(void* pClassBodyDeclarationObj);
C_FUNCTION void* adtJavaClassBodyDeclaration(void* pClassMemberDeclarationObj, void* pBlockObj, void* pConstructorDeclarationObj);
C_FUNCTION void* adtJavaClassMemberDeclaration(void* pFieldDeclarationObj, void* pMethodHeaderObj, void* pBlockObj);
C_FUNCTION void* adtJavaFieldDeclaration(void* pModifiersObj, void* pTypeObj, void* pVariableDeclaratorsObj);
C_FUNCTION void* adtJavaVariableDeclarators(void* pVariableDeclaratorObj);
C_FUNCTION void* adtJavaVariableDeclarator(void* pVariableDeclaratorIdObj, void* pExpressionObj, void* pVariableInitializersObj, int nHasComma, int nHasBracket);
C_FUNCTION void* adtJavaVariableDeclaratorId(const char* pIdentifier, void* pVariableDeclaratorIdObj);
C_FUNCTION void* adtJavaMethodHeader(void* pModifiersObj, void* pTypeObj, void* pMethodDeclaratorObj, void* pNameListObj);
C_FUNCTION void* adtJavaMethodDeclarator(const char* pIdentifier, void* pFormalParameterListObj, void* pMethodDeclaratorObj);
C_FUNCTION void* adtJavaFormalParameterList(void* pFormalParameterObj);
C_FUNCTION void* adtJavaFormalParameter(void* pTypeObj, void* pVariableDeclaratorIdObj);
C_FUNCTION void* adtJavaConstructorDeclaration(void* pModifiersObj, void* pConstructorDeclaratorObj, void* pNameListObj, void* pConstructorBodyObj);
C_FUNCTION void* adtJavaConstructorDeclarator(const char* pIdentifier, void* pFormalParameterListObj);
C_FUNCTION void* adtJavaConstructorBody(void* pBlockObj);
C_FUNCTION void* adtJavaExplicitConstructorInvocation(void* pArgumentListObj, int nIsSuper);
C_FUNCTION void* adtJavaInterfaceDeclaration(const char* pIdentifier, void* pModifiersObj, void* pExtendsInterfacesObj, void* pInterfaceMemberDeclarationsObj);
C_FUNCTION void* adtJavaExtendsInterfaces(void* pNameObj, void* pExtendsInterfacesObj);
C_FUNCTION void* adtJavaInterfaceMemberDeclarations(void* pInterfaceMemberDeclarationObj);
C_FUNCTION void* adtJavaInterfaceMemberDeclaration(void* pFieldDeclarationObj, void* pMethodHeaderObj);
C_FUNCTION void* adtJavaVariableInitializers(void* pVariableInitializerObj);
C_FUNCTION void* adtJavaVariableInitializer(void* pExpressionObj, void* pVariableInitializersObj, int nWithComma);
C_FUNCTION void* adtJavaBlock(void* pBlockStatementsObj, void* pExplicitConstructorInvocationObj);
C_FUNCTION void* adtJavaBlockStatements(void* pBlockStatementObj);
C_FUNCTION void* adtJavaBlockStatement(void* pTypeObj, void* pVariableDeclaratorsObj, void* pStatementObj);
C_FUNCTION void* adtJavaStatement(const char* pIdentifier, void* pStatementWithoutTrailingSubstatementObj, void* pStatementObj, void* pIfThenStatementObj, void* pIfThenElseStatementObj, void* pWhileStatementObj, void* pForStatementObj, int nNoShortIf);
C_FUNCTION void* adtJavaStatementWithoutTrailingSubstatement(void* pBlockObj, void* pStatementExpressionObj, void* pSwitchStatementObj, void* pDoStatementObj, void* pBreakStatementObj, void* pContinueStatementObj, void* pReturnStatementObj, void* pSynchronizedStatementObj, void* pThrowStatementObj, void* pTryStatementObj, int nHasSemiColon);
C_FUNCTION void* adtJavaStatementExpression(void* pAssignmentObj, void* pPreIncDecExpressionObj, void* pPostIncDecExpressionObj, void* pMethodInvocationObj, void* pClassInstanceCreationExpressionObj);
C_FUNCTION void* adtJavaIfThenStatement(void* pExpressionObj, void* pStatementObj);
C_FUNCTION void* adtJavaIfThenElseStatement(void* pExpressionObj, void* pStatementNoShortIfObj, void* pStatementObj, int nNoShortIf);
C_FUNCTION void* adtJavaSwitchStatement(void* pExpressionObj, void* pSwitchBlockObj);
C_FUNCTION void* adtJavaSwitchBlock(void* pSwitchLabelsObj, void* pSwitchBlockStatementGroupsObj);
C_FUNCTION void* adtJavaSwitchBlockStatementGroups(void* pSwitchBlockStatementGroupObj);
C_FUNCTION void* adtJavaSwitchBlockStatementGroup(void* pSwitchLabelsObj, void* pBlockStatementsObj);
C_FUNCTION void* adtJavaSwitchLabels(void* pSwitchLabelObj);
C_FUNCTION void* adtJavaSwitchLabel(void* pExpressionObj);
C_FUNCTION void* adtJavaWhileStatement(void* pExpressionObj, void* pStatementObj, int nNoShortIf);
C_FUNCTION void* adtJavaDoStatement(void* pExpressionObj, void* pStatementObj);
C_FUNCTION void* adtJavaForStatement(void* pForInitObj, void* pExpressionObj, void* pStatementExpressionListObj, void* pStatementObj, int nNoShortIf);
C_FUNCTION void* adtJavaForInit(void* pTypeObj, void* pStatementExpressionListObj, void* pVariableDeclaratorsObj);
C_FUNCTION void* adtJavaStatementExpressionList(void* pStatementExpressionObj);
C_FUNCTION void* adtJavaBreakStatement(const char* pIdentifier);
C_FUNCTION void* adtJavaContinueStatement(const char* pIdentifier);
C_FUNCTION void* adtJavaReturnStatement(void* pExpressionObj);
C_FUNCTION void* adtJavaThrowStatement(void* pExpressionObj);
C_FUNCTION void* adtJavaSynchronizedStatement(void* pExpressionObj, void* pBlockObj);
C_FUNCTION void* adtJavaTryStatement(void* pBlockObj, void* pCatchesObj, void* pFinallyObj);
C_FUNCTION void* adtJavaCatches(void* pCatchClauseObj);
C_FUNCTION void* adtJavaCatchClause(void* pFormalParameterObj, void* pBlockObj);
C_FUNCTION void* adtJavaFinally(void* pBlockObj);
C_FUNCTION void* adtJavaPrimary(void* pPrimaryNoNewArrayObj, void* pPrimitiveTypeObj, void* pDimExprsObj, void* pDimsObj, void* pNameObj);
C_FUNCTION void* adtJavaPrimaryNoNewArray(const char* pIdentifier, void* pLiteralObj, void* pExpressionObj, void* pClassInstanceCreationExpressionObj, void* pPrimaryObj, void* pMethodInvocationObj, void* pNameObj, void* pPrimaryNoNewArrayObj, int nIsSuper);
C_FUNCTION void* adtJavaClassInstanceCreationExpression(void* pNameObj, void* pArgumentListObj);
C_FUNCTION void* adtJavaArgumentList(void* pExpressionObj);
C_FUNCTION void* adtJavaDimExprs(void* pDimExprObj);
C_FUNCTION void* adtJavaDimExpr(void* pExpressionObj);
C_FUNCTION void* adtJavaDims(void* pDimsObj);
C_FUNCTION void* adtJavaMethodInvocation(const char* pIdentifier, void* pNameObj, void* pPrimaryObj, void* pArgumentListObj);
C_FUNCTION void* adtJavaPostfixExpression(void* pNameObj, void* pPrimaryObj, void* pPostIncDecExpressionObj);
C_FUNCTION void* adtJavaPostIncDecExpression(void* pPostfixExpressionObj, int nIncrement);
C_FUNCTION void* adtJavaPreIncDecExpression(void* pUnaryExpressionObj, int nIncrement);
C_FUNCTION void* adtJavaUnaryExpression(void* pPreIncDecExpressionObj, void* pUnaryExpressionObj, void* pUnaryExpressionNotPlusMinusObj, int nIsPlus);
C_FUNCTION void* adtJavaUnaryExpressionNotPlusMinus(void* pPostfixExpressionObj, void* pUnaryExpressionObj, void* pCastExpressionObj, int nLogical);
C_FUNCTION void* adtJavaCastExpression(void* pPrimitiveTypeObj, void* pUnaryExpressionObj, void* pUnaryExpressionNotPlusMinusObj, void* pExpressionObj, void* pDimsObj, void* pNameObj);
C_FUNCTION void* adtJavaMultiplicativeExpression(void* pUnaryExpressionObj, void* pMultiplicativeExpressionObj, int nOp);
C_FUNCTION void* adtJavaAdditiveExpression(void* pMultiplicativeExpressionObj, void* pAdditiveExpressionObj, int nOp);
C_FUNCTION void* adtJavaShiftExpression(void* pAdditiveExpressionObj, void* pShiftExpressionObj, int nOp);
C_FUNCTION void* adtJavaRelationalExpression(void* pShiftExpressionObj, void* pRelationalExpressionObj, void* pNameObj, void* pArrayTypeObj, int nOp);
C_FUNCTION void* adtJavaEqualityExpression(void* pRelationalExpressionObj, void* pEqualityExpressionObj, int nOp);
C_FUNCTION void* adtJavaAndExpression(void* pEqualityExpressionObj, void* pAndExpressionObj);
C_FUNCTION void* adtJavaExclusiveOrExpression(void* pAndExpressionObj, void* pExclusiveOrExpressionObj);
C_FUNCTION void* adtJavaInclusiveOrExpression(void* pExclusiveOrExpressionObj, void* pInclusiveOrExpressionObj);
C_FUNCTION void* adtJavaConditionalAndExpression(void* pInclusiveOrExpressionObj, void* pConditionalAndExpressionObj);
C_FUNCTION void* adtJavaConditionalOrExpression(void* pConditionalAndExpressionObj, void* pConditionalOrExpressionObj);
C_FUNCTION void* adtJavaConditionalExpression(void* pConditionalOrExpressionObj, void* pExpressionObj, void* pConditionalExpressionObj);
C_FUNCTION void* adtJavaExpression(void* pConditionalExpressionObj, void* pAssignmentObj);
C_FUNCTION void* adtJavaAssignment(const char* pIdentifier, void* pNameObj, void* pAssignmentOperatorObj, void* pExpressionObj, void* pPrimaryObj, void* pPrimaryNoNewArrayObj, void* pExpression2Obj, int nIsSuper);
C_FUNCTION void* adtJavaAssignmentOperator(int nOp);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtJavaGoal;
class AdtJavaLiteral;
class AdtJavaType;
class AdtJavaPrimitiveType;
class AdtJavaName;
class AdtJavaNameList;
class AdtJavaImportDeclarations;
class AdtJavaImportDeclaration;
class AdtJavaTypeDeclarations;
class AdtJavaTypeDeclaration;
class AdtJavaPackageDeclaration;
class AdtJavaModifiers;
class AdtJavaModifier;
class AdtJavaClassDeclaration;
class AdtJavaClassBodyDeclarations;
class AdtJavaClassBodyDeclaration;
class AdtJavaClassMemberDeclaration;
class AdtJavaFieldDeclaration;
class AdtJavaVariableDeclarators;
class AdtJavaVariableDeclarator;
class AdtJavaVariableDeclaratorId;
class AdtJavaMethodHeader;
class AdtJavaMethodDeclarator;
class AdtJavaFormalParameterList;
class AdtJavaFormalParameter;
class AdtJavaConstructorDeclaration;
class AdtJavaConstructorDeclarator;
class AdtJavaConstructorBody;
class AdtJavaExplicitConstructorInvocation;
class AdtJavaInterfaceDeclaration;
class AdtJavaExtendsInterfaces;
class AdtJavaInterfaceMemberDeclarations;
class AdtJavaInterfaceMemberDeclaration;
class AdtJavaVariableInitializers;
class AdtJavaVariableInitializer;
class AdtJavaBlock;
class AdtJavaBlockStatements;
class AdtJavaBlockStatement;
class AdtJavaStatement;
class AdtJavaStatementWithoutTrailingSubstatement;
class AdtJavaStatementExpression;
class AdtJavaIfThenStatement;
class AdtJavaIfThenElseStatement;
class AdtJavaSwitchStatement;
class AdtJavaSwitchBlock;
class AdtJavaSwitchBlockStatementGroups;
class AdtJavaSwitchBlockStatementGroup;
class AdtJavaSwitchLabels;
class AdtJavaSwitchLabel;
class AdtJavaWhileStatement;
class AdtJavaDoStatement;
class AdtJavaForStatement;
class AdtJavaForInit;
class AdtJavaStatementExpressionList;
class AdtJavaBreakStatement;
class AdtJavaContinueStatement;
class AdtJavaReturnStatement;
class AdtJavaThrowStatement;
class AdtJavaSynchronizedStatement;
class AdtJavaTryStatement;
class AdtJavaCatches;
class AdtJavaCatcheClause;
class AdtJavaFinally;
class AdtJavaPrimary;
class AdtJavaPrimaryNoNewArray;
class AdtJavaClassInstanceCreationExpression;
class AdtJavaArgumentList;
class AdtJavaDimExprs;
class AdtJavaDimExpr;
class AdtJavaDims;
class AdtJavaMethodInvocation;
class AdtJavaPostfixExpression;
class AdtJavaPostIncDecExpression;
class AdtJavaPreIncDecExpression;
class AdtJavaUnaryExpression;
class AdtJavaUnaryExpressionNotPlusMinus;
class AdtJavaCastExpression;
class AdtJavaMultiplicativeExpression;
class AdtJavaAdditiveExpression;
class AdtJavaShiftExpression;
class AdtJavaRelationalExpression;
class AdtJavaEqualityExpression;
class AdtJavaAndExpression;
class AdtJavaExclusiveOrExpression;
class AdtJavaInclusiveOrExpression;
class AdtJavaConditionalAndExpression;
class AdtJavaConditionalOrExpression;
class AdtJavaConditionalExpression;
class AdtJavaExpression;
class AdtJavaAssignment;
class AdtJavaAssignmentOperator;


//  ----------------------------------------------------------------------------
//  AdtJavaToFortranTypeConversion class
//  ----------------------------------------------------------------------------
//  This class is used in conjunction with a map to maintain a substitution
//  mapping from Java complex types to equivalent fortran ones (ie. MB's
//  arrays mapped into fortran equivalents).
//  ----------------------------------------------------------------------------
class AdtJavaToFortranTypeConversion
{
public:
  string  JavaType;
  string  FortranType;
  string  FortranDimension;
  string  FortranDimensionString;

private:
  void    initialise();

public:
  AdtJavaToFortranTypeConversion();
  AdtJavaToFortranTypeConversion(const char* pJavaType,
                                 const char* pFortranType,
                                 const char* pFortranDimension);
  AdtJavaToFortranTypeConversion(const AdtJavaToFortranTypeConversion& rCopy);
  virtual ~AdtJavaToFortranTypeConversion();
};

//  ----------------------------------------------------------------------------

inline AdtJavaToFortranTypeConversion::AdtJavaToFortranTypeConversion()
 : JavaType(),
   FortranType(),
   FortranDimension(),
   FortranDimensionString()
{

}

//  ----------------------------------------------------------------------------

inline AdtJavaToFortranTypeConversion::AdtJavaToFortranTypeConversion(const char* pJavaType,
                                                                      const char* pFortranType,
                                                                      const char* pFortranDimension)
 : JavaType(pJavaType),
   FortranType(pFortranType),
   FortranDimension(pFortranDimension),
   FortranDimensionString()
{
  initialise();
}

//  ----------------------------------------------------------------------------

inline AdtJavaToFortranTypeConversion::AdtJavaToFortranTypeConversion(const AdtJavaToFortranTypeConversion& rCopy)
 : JavaType(rCopy.JavaType),
   FortranType(rCopy.FortranType),
   FortranDimension(rCopy.FortranDimension),
   FortranDimensionString(rCopy.FortranDimensionString)
{

}

//  ----------------------------------------------------------------------------

inline AdtJavaToFortranTypeConversion::~AdtJavaToFortranTypeConversion()
{
  //Do nothing
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtJavaToFortranTypeConversion by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtJavaToFortranTypeConversion>                        AdtJavaToFortranTypeConversionStringPair;
typedef std::map<string, AdtJavaToFortranTypeConversion, string_less>                  AdtJavaToFortranTypeConversionByStringMap;
typedef std::map<string, AdtJavaToFortranTypeConversion, string_less>::iterator        AdtJavaToFortranTypeConversionByStringMapIter;
typedef std::map<string, AdtJavaToFortranTypeConversion, string_less>::const_iterator  AdtJavaToFortranTypeConversionByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  These class definitions map 1:1 to the grammar rules for the parser
//  ----------------------------------------------------------------------------
class AdtJavaBase : public AdtParser
{
protected:
  static AdtJavaGoal*                                JavaRootObject;
  static AdtJavaToFortranTypeConversionByStringMap   FortranTypeMap;
  static AdtJavaToFortranTypeConversionByStringMap   JavaTypeMap;

protected:
  AdtFile&                      forAllWriteFortran(AdtFile& rOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0) const;
  AdtFile&                      forAllWriteJava(AdtFile& rOutFile, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false) const;

public:
  AdtJavaBase();
  AdtJavaBase(const AdtJavaBase& rCopy);
  virtual ~AdtJavaBase();

  static void                   rootBindComments(AdtCommon* pCompilerBase);

  static void                   addFortranTypeMap(const string& rJavaType,
                                                  const string& rFortranType,
                                                  const string& rFortranSize);

  static void                   javaRootObject(AdtParser* pRoot);
  static AdtJavaGoal*           javaRootObject();

  static bool                   mapTypesToFortran(const char* pTypeName,
                                                  const char*& pType,
                                                  const char*& pDimension);

  static bool                   mapTypesToJava(const char* pTypeName,
                                               int nDimension,
                                               const char*& pType);

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtJavaBase::AdtJavaBase(const AdtJavaBase& rCopy)
 : AdtParser(rCopy)
{

}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtJavaBase::writeFortran(AdtFile& rOutFile, int nMode) const
{
  return (rOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtJavaBase::writeJava(AdtFile& rOutFile) const
{
  return (rOutFile);
}


//  ----------------------------------------------------------------------------
//  AdtJavaGoal class
//  ----------------------------------------------------------------------------
class AdtJavaGoal : public AdtJavaBase, public AdtSourceRoot
{
private:
  AdtJavaPackageDeclaration*    PackageDeclaration;
  AdtJavaImportDeclarations*    ImportDeclarations;
  AdtJavaTypeDeclarations*      TypeDeclarations;

public:
  AdtJavaGoal(AdtParser* pPackageDeclarationObj,
              AdtParser* pImportDeclarationsObj,
              AdtParser* pTypeDeclarationsObj);

  AdtJavaGoal(const AdtJavaGoal& rCopy);
  virtual ~AdtJavaGoal();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  virtual void                  enumerateMethodNames(AdtStringList& rMethodList) const;

  virtual bool                  hasClass(const char* pClassName,
                                         string& rParentClassName) const;

  virtual bool                  buildBlackBoxFile(const char* pBlackBoxFileName,
                                                  AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                  AdtStringByStringMap& rRegardAsClassSubroutineMap,
                                                  double dVersionNumber);

  virtual bool                  flattenClass(const char* pClassName,
                                             const AdtParserPtrList& rRootList,
                                             string& rUsesList);

  virtual bool                  optimise(const AdtStringList& rNewMethodList,
                                         const AdtStringByStringMap& rNewMethodMap);

  virtual bool                  expandMacros();

  virtual bool                  extractClassConstructors(AdtStringList& rConstructorList,
                                                         const char* pClassName,
                                                         const char* pParentClassName,
                                                         const char* pPathPrefix,
                                                         AdtSourceFileType nAsFileType) const;

  virtual AdtFile&              writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                           const AdtFortranExecutableProgram* pSavedRoot,
                                                           const char* pClassName,
                                                           const char* pLastClassName,
                                                           bool bExpandMacros) const;

  virtual AdtFile&              writeNative(AdtFile& rOutFile) const;

  virtual AdtSourceFileType     sourceFileType() const;

//  declListType(AdtJavaMacro);
  declType;
};

//  ----------------------------------------------------------------------------

enum AdtJavaLiteralEnum
{
 JavaLiteral_INTEGER        = 0,
 JavaLiteral_FLOATINGPOINT  = 1,
 JavaLiteral_BOOLEAN        = 2,
 JavaLiteral_CHARACTER      = 3,
 JavaLiteral_STRING         = 4,
 JavaLiteral_NULL           = 5
};

//  ----------------------------------------------------------------------------
//  AdtJavaLiteral class
//  ----------------------------------------------------------------------------
class AdtJavaLiteral : public AdtJavaBase
{
private:
  AdtJavaLiteralEnum            LiteralType;

public:
  AdtJavaLiteral(const char* pLiteral, AdtJavaLiteralEnum nType);
  AdtJavaLiteral(const AdtJavaLiteral& rCopy);
  virtual ~AdtJavaLiteral();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaType class
//  ----------------------------------------------------------------------------
class AdtJavaType : public AdtJavaBase
{
private:
  AdtJavaName*                  Name;
  AdtJavaPrimitiveType*         PrimitiveType;
  AdtJavaType*                  ArrayType;
  bool                          IsArray;

public:
  AdtJavaType(AdtParser* pNameObj,
              AdtParser* pPrimitiveTypeObj,
              AdtParser* pArrayTypeObj,
              bool bIsArray);

  AdtJavaType(const AdtJavaType& rCopy);
  virtual ~AdtJavaType();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtJavaPrimitiveEnum
{
  JavaPrimitive_BYTE    = 0,
  JavaPrimitive_SHORT   = 1,
  JavaPrimitive_INT     = 2,
  JavaPrimitive_LONG    = 3,
  JavaPrimitive_CHAR    = 4,
  JavaPrimitive_FLOAT   = 5,
  JavaPrimitive_DOUBLE  = 6,
  JavaPrimitive_BOOLEAN = 7,
  JavaPrimitive_BOOL    = 8
};

//  ----------------------------------------------------------------------------
//  AdtJavaPrimitiveType class
//  ----------------------------------------------------------------------------
class AdtJavaPrimitiveType : public AdtJavaBase
{
private:
  AdtJavaPrimitiveEnum          Type;

public:
  AdtJavaPrimitiveType(AdtJavaPrimitiveEnum nType);
  AdtJavaPrimitiveType(const AdtJavaPrimitiveType& rCopy);
  virtual ~AdtJavaPrimitiveType();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaName class
//  ----------------------------------------------------------------------------
class AdtJavaName : public AdtJavaBase
{
private:
  AdtJavaName*                  Name;
  bool                          IsCpp;

public:
  AdtJavaName(AdtParser* pNameObj,
              const char* pIdentifier,
              bool bIsCpp);

  AdtJavaName(const AdtJavaName& rCopy);
  virtual ~AdtJavaName();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaNameList class
//  ----------------------------------------------------------------------------
class AdtJavaNameList : public AdtJavaBase
{
public:
  AdtJavaNameList(AdtParser* pNameObj);
  AdtJavaNameList(const AdtJavaNameList& rCopy);
  virtual ~AdtJavaNameList();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaName);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaImportDeclarations class
//  ----------------------------------------------------------------------------
class AdtJavaImportDeclarations : public AdtJavaBase
{
public:
  AdtJavaImportDeclarations(AdtParser* pImportDeclarationObj);
  AdtJavaImportDeclarations(const AdtJavaImportDeclarations& rCopy);
  virtual ~AdtJavaImportDeclarations();

  virtual AdtFile&               writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&               writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaImportDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaImportDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaImportDeclaration : public AdtJavaBase
{
private:
  AdtJavaName*                  Name;
  bool                          HasPeriodMultiply;

public:
  AdtJavaImportDeclaration(AdtParser* pNameObj,
                           bool bHasPeriodMultiply);

  AdtJavaImportDeclaration(const AdtJavaImportDeclaration& rCopy);
  virtual ~AdtJavaImportDeclaration();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaTypeDeclarations class
//  ----------------------------------------------------------------------------
class AdtJavaTypeDeclarations : public AdtJavaBase
{
public:
  AdtJavaTypeDeclarations(AdtParser* pTypeDeclarationObj);
  AdtJavaTypeDeclarations(const AdtJavaTypeDeclarations& rCopy);
  virtual ~AdtJavaTypeDeclarations();

  virtual AdtFile&               writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&               writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaTypeDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaTypeDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaTypeDeclaration : public AdtJavaBase
{
private:
  AdtJavaClassDeclaration*      ClassDeclaration;
  AdtJavaInterfaceDeclaration*  InterfaceDeclaration;

public:
  AdtJavaTypeDeclaration(AdtParser* pClassDeclarationObj,
                         AdtParser* pInterfaceDeclarationObj);

  AdtJavaTypeDeclaration(const AdtJavaTypeDeclaration& rCopy);
  virtual ~AdtJavaTypeDeclaration();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPackageDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaPackageDeclaration : public AdtJavaBase
{
private:
  AdtJavaName*                  Name;

public:
  AdtJavaPackageDeclaration(AdtParser* pNameObj);
  AdtJavaPackageDeclaration(const AdtJavaPackageDeclaration& rCopy);
  virtual ~AdtJavaPackageDeclaration();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaModifiers class
//  ----------------------------------------------------------------------------
class AdtJavaModifiers : public AdtJavaBase
{
public:
  AdtJavaModifiers(AdtParser* pModifierObj);
  AdtJavaModifiers(const AdtJavaModifiers& rCopy);
  virtual ~AdtJavaModifiers();

  virtual AdtFile&               writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&               writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaModifier);
  declType;
};


//  ----------------------------------------------------------------------------

enum AdtJavaModifierEnum
{
  JavaModifier_PUBLIC       = 0,
  JavaModifier_PROTECTED    = 1,
  JavaModifier_PRIVATE      = 2,
  JavaModifier_STATIC       = 3,
  JavaModifier_ABSTRACT     = 4,
  JavaModifier_FINAL        = 5,
  JavaModifier_NATIVE       = 6,
  JavaModifier_SYNCHRONIZED = 7,
  JavaModifier_TRANSIENT    = 8,
  JavaModifier_VOLATILE     = 9,
  JavaModifier_CONST        = 10
};

//  ----------------------------------------------------------------------------
//  AdtJavaModifier class
//  ----------------------------------------------------------------------------
class AdtJavaModifier : public AdtJavaBase
{
private:
  AdtJavaModifierEnum           Modifier;

public:
  AdtJavaModifier(AdtJavaModifierEnum nModifier);
  AdtJavaModifier(const AdtJavaModifier& rCopy);
  virtual ~AdtJavaModifier();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaClassDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaClassDeclaration : public AdtJavaBase
{
private:
  AdtJavaModifiers*             Modifiers;
  AdtJavaName*                  Name;
  AdtJavaNameList*              NameList;
  AdtJavaClassBodyDeclarations* ClassBodyDeclarations;

public:
  AdtJavaClassDeclaration(const char* pIdentifier,
                          AdtParser* pModifiersObj,
                          AdtParser* pNameObj,
                          AdtParser* pNameListObj,
                          AdtParser* pClassBodyDeclarationsObj);

  AdtJavaClassDeclaration(const AdtJavaClassDeclaration& rCopy);
  virtual ~AdtJavaClassDeclaration();

  AdtFile&                      writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  AdtFile&                      writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaClassBodyDeclarations class
//  ----------------------------------------------------------------------------
class AdtJavaClassBodyDeclarations : public AdtJavaBase
{
public:
  AdtJavaClassBodyDeclarations(AdtParser* pClassBodyDeclarationObj);
  AdtJavaClassBodyDeclarations(const AdtJavaClassBodyDeclarations& rCopy);
  virtual ~AdtJavaClassBodyDeclarations();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaClassBodyDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaClassBodyDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaClassBodyDeclaration : public AdtJavaBase
{
private:
  AdtJavaClassMemberDeclaration*  ClassMemberDeclaration;
  AdtJavaBlock*                   Block;
  AdtJavaConstructorDeclaration*  ConstructorDeclaration;

public:
  AdtJavaClassBodyDeclaration(AdtParser* pClassMemberDeclarationObj,
                              AdtParser* pBlockObj,
                              AdtParser* pConstructorDeclarationObj);

  AdtJavaClassBodyDeclaration(const AdtJavaClassBodyDeclaration& rCopy);
  virtual ~AdtJavaClassBodyDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaClassMemberDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaClassMemberDeclaration : public AdtJavaBase
{
private:
  AdtJavaFieldDeclaration*      FieldDeclaration;
  AdtJavaMethodHeader*          MethodHeader;
  AdtJavaBlock*                 Block;

public:
  AdtJavaClassMemberDeclaration(AdtParser* pFieldDeclarationObj,
                                AdtParser* pMethodHeaderObj,
                                AdtParser* pBlock);

  AdtJavaClassMemberDeclaration(const AdtJavaClassMemberDeclaration& rCopy);
  virtual ~AdtJavaClassMemberDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaFieldDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaFieldDeclaration : public AdtJavaBase
{
private:
  AdtJavaModifiers*             Modifiers;
  AdtJavaType*                  Type;
  AdtJavaVariableDeclarators*   VariableDeclarators;

public:
  AdtJavaFieldDeclaration(AdtParser* pModifiersObj,
                          AdtParser* pTypeObj,
                          AdtParser* pVariableDeclaratorsObj);

  AdtJavaFieldDeclaration(const AdtJavaFieldDeclaration& rCopy);
  virtual ~AdtJavaFieldDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclarators class
//  ----------------------------------------------------------------------------
class AdtJavaVariableDeclarators : public AdtJavaBase
{
public:
  AdtJavaVariableDeclarators(AdtParser* pVariableDeclaratorObj);
  AdtJavaVariableDeclarators(const AdtJavaVariableDeclarators& rCopy);
  virtual ~AdtJavaVariableDeclarators();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaVariableDeclarator);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclarator class
//  ----------------------------------------------------------------------------
class AdtJavaVariableDeclarator : public AdtJavaBase
{
private:
  AdtJavaVariableDeclaratorId*  VariableDeclaratorId;
  AdtJavaExpression*            Expression;
  AdtJavaVariableInitializers*  VariableInitializers;
  bool                          HasComma;
  bool                          HasBracket;

public:
  AdtJavaVariableDeclarator(AdtParser* pVariableDeclaratorIdObj,
                            AdtParser* pExpressionObj,
                            AdtParser* pVariableInitializersObj,
                            bool bHasComma,
                            bool bHasBracket);

  AdtJavaVariableDeclarator(const AdtJavaVariableDeclarator& rCopy);
  virtual ~AdtJavaVariableDeclarator();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaVariableDeclaratorId class
//  ----------------------------------------------------------------------------
class AdtJavaVariableDeclaratorId : public AdtJavaBase
{
protected:
  AdtJavaVariableDeclaratorId*  VariableDeclaratorId;

public:
  AdtJavaVariableDeclaratorId(const char* pIdentifier, AdtParser* pVariableDeclaratorIdObj);
  AdtJavaVariableDeclaratorId(const AdtJavaVariableDeclaratorId& rCopy);
  virtual ~AdtJavaVariableDeclaratorId();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaMethodHeader class
//  ----------------------------------------------------------------------------
class AdtJavaMethodHeader : public AdtJavaBase
{
protected:
  AdtJavaModifiers*             Modifiers;
  AdtJavaType*                  Type;
  AdtJavaMethodDeclarator*      MethodDeclarator;
  AdtJavaNameList*              NameList;

public:
  AdtJavaMethodHeader(AdtParser* pModifiersObj,
                      AdtParser* pTypeObj,
                      AdtParser* pMethodDeclaratorObj,
                      AdtParser* pNameListObj);

  AdtJavaMethodHeader(const AdtJavaMethodHeader& rCopy);
  virtual ~AdtJavaMethodHeader();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaMethodDeclarator class
//  ----------------------------------------------------------------------------
class AdtJavaMethodDeclarator : public AdtJavaBase
{
protected:
  AdtJavaFormalParameterList*   FormalParameterList;
  AdtJavaMethodDeclarator*      MethodDeclarator;

public:
  AdtJavaMethodDeclarator(const char* pIdentifier,
                          AdtParser* pFormalParameterListObj,
                          AdtParser* pMethodDeclaratorObj);

  AdtJavaMethodDeclarator(const AdtJavaMethodDeclarator& rCopy);
  virtual ~AdtJavaMethodDeclarator();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaFormalParameterList class
//  ----------------------------------------------------------------------------
class AdtJavaFormalParameterList : public AdtJavaBase
{
public:
  AdtJavaFormalParameterList(AdtParser* pFormalParameterObj);
  AdtJavaFormalParameterList(const AdtJavaFormalParameterList& rCopy);
  virtual ~AdtJavaFormalParameterList();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaFormalParameter);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaFormalParameter class
//  ----------------------------------------------------------------------------
class AdtJavaFormalParameter : public AdtJavaBase
{
protected:
  AdtJavaType*                  Type;
  AdtJavaVariableDeclaratorId*  VariableDeclaratorId;

public:
  AdtJavaFormalParameter(AdtParser* pTypeObj,
                         AdtParser* pVariableDeclaratorIdObj);

  AdtJavaFormalParameter(const AdtJavaFormalParameter& rCopy);
  virtual ~AdtJavaFormalParameter();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaConstructorDeclaration : public AdtJavaBase
{
protected:
  AdtJavaModifiers*             Modifiers;
  AdtJavaConstructorDeclarator* ConstructorDeclarator;
  AdtJavaNameList*              NameList;
  AdtJavaConstructorBody*       ConstructorBody;

public:
  AdtJavaConstructorDeclaration(AdtParser* pModifiersObj,
                                AdtParser* pConstructorDeclaratorObj,
                                AdtParser* pNameListObj,
                                AdtParser* pConstructorBodyObj);

  AdtJavaConstructorDeclaration(const AdtJavaConstructorDeclaration& rCopy);
  virtual ~AdtJavaConstructorDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorDeclarator class
//  ----------------------------------------------------------------------------
class AdtJavaConstructorDeclarator : public AdtJavaBase
{
protected:
  AdtJavaFormalParameterList*   FormalParameterList;

public:
  AdtJavaConstructorDeclarator(const char* pIdentifier,
                               AdtParser* pFormalParameterListObj);

  AdtJavaConstructorDeclarator(const AdtJavaConstructorDeclarator& rCopy);
  virtual ~AdtJavaConstructorDeclarator();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConstructorBody class
//  ----------------------------------------------------------------------------
class AdtJavaConstructorBody : public AdtJavaBase
{
protected:
  AdtJavaBlock*                 Block;

public:
  AdtJavaConstructorBody(AdtParser* pBlockObj);
  AdtJavaConstructorBody(const AdtJavaConstructorBody& rCopy);
  virtual ~AdtJavaConstructorBody();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaExplicitConstructorInvocation class
//  ----------------------------------------------------------------------------
class AdtJavaExplicitConstructorInvocation : public AdtJavaBase
{
protected:
  AdtJavaArgumentList*          ArgumentList;
  bool                          IsSuper;

public:
  AdtJavaExplicitConstructorInvocation(AdtParser* pArgumentListObj,
                                       bool bIsSuper);

  AdtJavaExplicitConstructorInvocation(const AdtJavaExplicitConstructorInvocation& rCopy);
  virtual ~AdtJavaExplicitConstructorInvocation();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaInterfaceDeclaration : public AdtJavaBase
{
protected:
  AdtJavaModifiers*                   Modifiers;
  AdtJavaExtendsInterfaces*           ExtendsInterfaces;
  AdtJavaInterfaceMemberDeclarations* InterfaceMemberDeclarations;

public:
  AdtJavaInterfaceDeclaration(const char* pIdentifier,
                              AdtParser* pModifiersObj,
                              AdtParser* pExtendsInterfacesObj,
                              AdtParser* pInterfaceMemberDeclarationsObj);

  AdtJavaInterfaceDeclaration(const AdtJavaInterfaceDeclaration& rCopy);
  virtual ~AdtJavaInterfaceDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaExtendsInterfaces class
//  ----------------------------------------------------------------------------
class AdtJavaExtendsInterfaces : public AdtJavaBase
{
protected:
  AdtJavaName*                  Name;
  AdtJavaExtendsInterfaces*     ExtendsInterfaces;

public:
  AdtJavaExtendsInterfaces(AdtParser* pNameObj,
                           AdtParser* pExtendsInterfacesObj);

  AdtJavaExtendsInterfaces(const AdtJavaExtendsInterfaces& rCopy);
  virtual ~AdtJavaExtendsInterfaces();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceMemberDeclarations class
//  ----------------------------------------------------------------------------
class AdtJavaInterfaceMemberDeclarations : public AdtJavaBase
{
public:
  AdtJavaInterfaceMemberDeclarations(AdtParser* pInterfaceMemberDeclarationObj);
  AdtJavaInterfaceMemberDeclarations(const AdtJavaInterfaceMemberDeclarations& rCopy);
  virtual ~AdtJavaInterfaceMemberDeclarations();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaInterfaceMemberDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaInterfaceMemberDeclaration class
//  ----------------------------------------------------------------------------
class AdtJavaInterfaceMemberDeclaration : public AdtJavaBase
{
protected:
  AdtJavaFieldDeclaration*      FieldDeclaration;
  AdtJavaMethodHeader*          MethodHeader;

public:
  AdtJavaInterfaceMemberDeclaration(AdtParser* pFieldDeclarationObj,
                                    AdtParser* pMethodHeaderObj);

  AdtJavaInterfaceMemberDeclaration(const AdtJavaInterfaceMemberDeclaration& rCopy);
  virtual ~AdtJavaInterfaceMemberDeclaration();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaVariableInitializers class
//  ----------------------------------------------------------------------------
class AdtJavaVariableInitializers : public AdtJavaBase
{
public:
  AdtJavaVariableInitializers(AdtParser* pVariableInitializerObj);
  AdtJavaVariableInitializers(const AdtJavaVariableInitializers& rCopy);
  virtual ~AdtJavaVariableInitializers();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaVariableInitializer);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaVariableInitializer class
//  ----------------------------------------------------------------------------
class AdtJavaVariableInitializer : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaVariableInitializers*  VariableInitializers;
  bool                          WithComma;

public:
  AdtJavaVariableInitializer(AdtParser* pExpressionObj,
                             AdtParser* pVariableInitializersObj,
                             bool bWithComma);

  AdtJavaVariableInitializer(const AdtJavaVariableInitializer& rCopy);
  virtual ~AdtJavaVariableInitializer();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaBlock class
//  ----------------------------------------------------------------------------
class AdtJavaBlock : public AdtJavaBase
{
private:
  AdtJavaBlockStatements*               BlockStatements;
  AdtJavaExplicitConstructorInvocation* ExplicitConstructorInvocation;

public:
  AdtJavaBlock(AdtParser* pBlockStatementsObj,
               AdtParser* pExplicitConstructorInvocationObj);

  AdtJavaBlock(const AdtJavaBlock& rCopy);
  virtual ~AdtJavaBlock();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaBlockStatements class
//  ----------------------------------------------------------------------------
class AdtJavaBlockStatements : public AdtJavaBase
{
public:
  AdtJavaBlockStatements(AdtParser* pBlockStatementObj);
  AdtJavaBlockStatements(const AdtJavaBlockStatements& rCopy);
  virtual ~AdtJavaBlockStatements();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaBlockStatement);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaBlockStatement class
//  ----------------------------------------------------------------------------
class AdtJavaBlockStatement : public AdtJavaBase
{
protected:
  AdtJavaType*                  Type;
  AdtJavaVariableDeclarators*   VariableDeclarators;
  AdtJavaStatement*             Statement;

public:
  AdtJavaBlockStatement(AdtParser* pTypeObj,
                        AdtParser* pVariableDeclaratorsObj,
                        AdtParser* pStatementObj);

  AdtJavaBlockStatement(const AdtJavaBlockStatement& rCopy);
  virtual ~AdtJavaBlockStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaStatement class
//  ----------------------------------------------------------------------------
class AdtJavaStatement : public AdtJavaBase
{
protected:
  AdtJavaStatementWithoutTrailingSubstatement*  StatementWithoutTrailingSubstatement;
  AdtJavaStatement*                             Statement;
  AdtJavaIfThenStatement*                       IfThenStatement;
  AdtJavaIfThenElseStatement*                   IfThenElseStatement;
  AdtJavaWhileStatement*                        WhileStatement;
  AdtJavaForStatement*                          ForStatement;
  bool                                          NoShortIf;

public:
  AdtJavaStatement(const char* pIdentifier,
                   AdtParser* pStatementWithoutTrailingSubstatementObj,
                   AdtParser* pStatementObj,
                   AdtParser* pIfThenStatementObj,
                   AdtParser* pIfThenElseStatementObj,
                   AdtParser* pWhileStatementObj,
                   AdtParser* pForStatementObj,
                   bool bNoShortIf);

  AdtJavaStatement(const AdtJavaStatement& rCopy);
  virtual ~AdtJavaStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaStatementWithoutTrailingSubstatement class
//  ----------------------------------------------------------------------------
class AdtJavaStatementWithoutTrailingSubstatement : public AdtJavaBase
{
protected:
  AdtJavaBlock*                 Block;
  AdtJavaStatementExpression*   StatementExpression;
  AdtJavaSwitchStatement*       SwitchStatement;
  AdtJavaDoStatement*           DoStatement;
  AdtJavaBreakStatement*        BreakStatement;
  AdtJavaContinueStatement*     ContinueStatement;
  AdtJavaReturnStatement*       ReturnStatement;
  AdtJavaSynchronizedStatement* SynchronizedStatement;
  AdtJavaThrowStatement*        ThrowStatement;
  AdtJavaTryStatement*          TryStatement;
  bool                          HasSemiColon;

public:
  AdtJavaStatementWithoutTrailingSubstatement(AdtParser* pBlockObj,
                                              AdtParser* pStatementExpressionObj,
                                              AdtParser* pSwitchStatementObj,
                                              AdtParser* pDoStatementObj,
                                              AdtParser* pBreakStatementObj,
                                              AdtParser* pContinueStatementObj,
                                              AdtParser* pReturnStatementObj,
                                              AdtParser* pSynchronizedStatementObj,
                                              AdtParser* pThrowStatementObj,
                                              AdtParser* pTryStatementObj,
                                              bool bHasSemiColon);

  AdtJavaStatementWithoutTrailingSubstatement(const AdtJavaStatementWithoutTrailingSubstatement& rCopy);
  virtual ~AdtJavaStatementWithoutTrailingSubstatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaStatementExpression class
//  ----------------------------------------------------------------------------
class AdtJavaStatementExpression : public AdtJavaBase
{
protected:
  AdtJavaAssignment*                      Assignment;
  AdtJavaPreIncDecExpression*             PreIncDecExpression;
  AdtJavaPostIncDecExpression*            PostIncDecExpression;
  AdtJavaMethodInvocation*                MethodInvocation;
  AdtJavaClassInstanceCreationExpression* ClassInstanceCreationExpression;

public:
  AdtJavaStatementExpression(AdtParser* pAssignmentObj,
                             AdtParser* pPreIncDecExpressionObj,
                             AdtParser* pPostIncDecExpressionObj,
                             AdtParser* pMethodInvocationObj,
                             AdtParser* pClassInstanceCreationExpressionObj);

  AdtJavaStatementExpression(const AdtJavaStatementExpression& rCopy);
  virtual ~AdtJavaStatementExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaIfThenStatement class
//  ----------------------------------------------------------------------------
class AdtJavaIfThenStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaStatement*             Statement;

public:
  AdtJavaIfThenStatement(AdtParser* pExpressionObj,
                         AdtParser* pStatementObj);

  AdtJavaIfThenStatement(const AdtJavaIfThenStatement& rCopy);
  virtual ~AdtJavaIfThenStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaIfThenElseStatement class
//  ----------------------------------------------------------------------------
class AdtJavaIfThenElseStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaStatement*             StatementNoShortIf;
  AdtJavaStatement*             Statement;
  bool                          NoShortIf;

public:
  AdtJavaIfThenElseStatement(AdtParser* pExpressionObj,
                             AdtParser* pStatementNoShortIfObj,
                             AdtParser* pStatementObj,
                             bool bNoShortIf);

  AdtJavaIfThenElseStatement(const AdtJavaIfThenElseStatement& rCopy);
  virtual ~AdtJavaIfThenElseStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchStatement class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaSwitchBlock*           SwitchBlock;

public:
  AdtJavaSwitchStatement(AdtParser* pExpressionObj,
                         AdtParser* pSwitchBlockObj);

  AdtJavaSwitchStatement(const AdtJavaSwitchStatement& rCopy);
  virtual ~AdtJavaSwitchStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlock class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchBlock : public AdtJavaBase
{
protected:
  AdtJavaSwitchLabels*                SwitchLabels;
  AdtJavaSwitchBlockStatementGroups*  SwitchBlockStatementGroups;

public:
  AdtJavaSwitchBlock(AdtParser* pSwitchLabelsObj,
                     AdtParser* pSwitchBlockStatementGroupsObj);

  AdtJavaSwitchBlock(const AdtJavaSwitchBlock& rCopy);
  virtual ~AdtJavaSwitchBlock();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlockStatementGroups class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchBlockStatementGroups : public AdtJavaBase
{
public:
  AdtJavaSwitchBlockStatementGroups(AdtParser* pSwitchBlockStatementGroupObj);
  AdtJavaSwitchBlockStatementGroups(const AdtJavaSwitchBlockStatementGroups& rCopy);
  virtual ~AdtJavaSwitchBlockStatementGroups();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaSwitchBlockStatementGroup);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchBlockStatementGroup class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchBlockStatementGroup : public AdtJavaBase
{
protected:
  AdtJavaSwitchLabels*          SwitchLabels;
  AdtJavaBlockStatements*       BlockStatements;

public:
  AdtJavaSwitchBlockStatementGroup(AdtParser* pSwitchLabelsObj,
                                   AdtParser* pBlockStatementsObj);

  AdtJavaSwitchBlockStatementGroup(const AdtJavaSwitchBlockStatementGroup& rCopy);
  virtual ~AdtJavaSwitchBlockStatementGroup();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchLabels class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchLabels : public AdtJavaBase
{
public:
  AdtJavaSwitchLabels(AdtParser* pSwitchLabelObj);
  AdtJavaSwitchLabels(const AdtJavaSwitchLabels& rCopy);
  virtual ~AdtJavaSwitchLabels();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaSwitchLabel);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSwitchLabel class
//  ----------------------------------------------------------------------------
class AdtJavaSwitchLabel : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;

public:
  AdtJavaSwitchLabel(AdtParser* pExpressionObj);
  AdtJavaSwitchLabel(const AdtJavaSwitchLabel& rCopy);
  virtual ~AdtJavaSwitchLabel();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaWhileStatement class
//  ----------------------------------------------------------------------------
class AdtJavaWhileStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaStatement*             Statement;
  bool                          NoShortIf;

public:
  AdtJavaWhileStatement(AdtParser* pExpressionObj,
                        AdtParser* pStatementObj,
                        bool bNoShortIf);

  AdtJavaWhileStatement(const AdtJavaWhileStatement& rCopy);
  virtual ~AdtJavaWhileStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaDoStatement class
//  ----------------------------------------------------------------------------
class AdtJavaDoStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaStatement*             Statement;

public:
  AdtJavaDoStatement(AdtParser* pExpressionObj,
                     AdtParser* pStatementObj);

  AdtJavaDoStatement(const AdtJavaDoStatement& rCopy);
  virtual ~AdtJavaDoStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaForStatement class
//  ----------------------------------------------------------------------------
class AdtJavaForStatement : public AdtJavaBase
{
protected:
  AdtJavaForInit*                 ForInit;
  AdtJavaExpression*              Expression;
  AdtJavaStatementExpressionList* StatementExpressionList;
  AdtJavaStatement*               Statement;
  bool                            NoShortIf;

public:
  AdtJavaForStatement(AdtParser* pForInitObj,
                      AdtParser* pExpressionObj,
                      AdtParser* pStatementExpressionListObj,
                      AdtParser* pStatementObj,
                      bool bNoShortIf);

  AdtJavaForStatement(const AdtJavaForStatement& rCopy);
  virtual ~AdtJavaForStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaForInit class
//  ----------------------------------------------------------------------------
class AdtJavaForInit : public AdtJavaBase
{
protected:
  AdtJavaType*                    Type;
  AdtJavaStatementExpressionList* StatementExpressionList;
  AdtJavaVariableDeclarators*     VariableDeclarators;

public:
  AdtJavaForInit(AdtParser* pTypeObj,
                 AdtParser* pStatementExpressionListObj,
                 AdtParser* pVariableDeclaratorsObj);

  AdtJavaForInit(const AdtJavaForInit& rCopy);
  virtual ~AdtJavaForInit();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaStatementExpressionList class
//  ----------------------------------------------------------------------------
class AdtJavaStatementExpressionList : public AdtJavaBase
{
public:
  AdtJavaStatementExpressionList(AdtParser* pStatementExpressionObj);
  AdtJavaStatementExpressionList(const AdtJavaStatementExpressionList& rCopy);
  virtual ~AdtJavaStatementExpressionList();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaStatementExpression);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaBreakStatement class
//  ----------------------------------------------------------------------------
class AdtJavaBreakStatement : public AdtJavaBase
{
public:
  AdtJavaBreakStatement(const char* pIdentifier);
  AdtJavaBreakStatement(const AdtJavaBreakStatement& rCopy);
  virtual ~AdtJavaBreakStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaContinueStatement class
//  ----------------------------------------------------------------------------
class AdtJavaContinueStatement : public AdtJavaBase
{
public:
  AdtJavaContinueStatement(const char* pIdentifier);
  AdtJavaContinueStatement(const AdtJavaContinueStatement& rCopy);
  virtual ~AdtJavaContinueStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaReturnStatement class
//  ----------------------------------------------------------------------------
class AdtJavaReturnStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;

public:
  AdtJavaReturnStatement(AdtParser* pExpressionObj);
  AdtJavaReturnStatement(const AdtJavaReturnStatement& rCopy);
  virtual ~AdtJavaReturnStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaThrowStatement class
//  ----------------------------------------------------------------------------
class AdtJavaThrowStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;

public:
  AdtJavaThrowStatement(AdtParser* pExpressionObj);
  AdtJavaThrowStatement(const AdtJavaThrowStatement& rCopy);
  virtual ~AdtJavaThrowStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaSynchronizedStatement class
//  ----------------------------------------------------------------------------
class AdtJavaSynchronizedStatement : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;
  AdtJavaBlock*                 Block;

public:
  AdtJavaSynchronizedStatement(AdtParser* pExpressionObj,
                               AdtParser* pBlockObj);

  AdtJavaSynchronizedStatement(const AdtJavaSynchronizedStatement& rCopy);
  virtual ~AdtJavaSynchronizedStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaTryStatement class
//  ----------------------------------------------------------------------------
class AdtJavaTryStatement : public AdtJavaBase
{
protected:
  AdtJavaBlock*                 Block;
  AdtJavaCatches*               Catches;
  AdtJavaFinally*               Finally;

public:
  AdtJavaTryStatement(AdtParser* pBlockObj,
                      AdtParser* pCatchesObj,
                      AdtParser* pFinallyObj);

  AdtJavaTryStatement(const AdtJavaTryStatement& rCopy);
  virtual ~AdtJavaTryStatement();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaCatches class
//  ----------------------------------------------------------------------------
class AdtJavaCatches : public AdtJavaBase
{
public:
  AdtJavaCatches(AdtParser* pCatchClauseObj);
  AdtJavaCatches(const AdtJavaCatches& rCopy);
  virtual ~AdtJavaCatches();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaCatch);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaCatchClause class
//  ----------------------------------------------------------------------------
class AdtJavaCatchClause : public AdtJavaBase
{
protected:
  AdtJavaBlock*                 Block;
  AdtJavaFormalParameter*       FormalParameter;

public:
  AdtJavaCatchClause(AdtParser* pFormalParameterObj,
                     AdtParser* pBlockObj);

  AdtJavaCatchClause(const AdtJavaCatchClause& rCopy);
  virtual ~AdtJavaCatchClause();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaFinally class
//  ----------------------------------------------------------------------------
class AdtJavaFinally : public AdtJavaBase
{
protected:
  AdtJavaBlock*                 Block;

public:
  AdtJavaFinally(AdtParser* pBlockObj);
  AdtJavaFinally(const AdtJavaFinally& rCopy);
  virtual ~AdtJavaFinally();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPrimary class
//  ----------------------------------------------------------------------------
class AdtJavaPrimary : public AdtJavaBase
{
protected:
  AdtJavaPrimaryNoNewArray*     PrimaryNoNewArray;
  AdtJavaPrimitiveType*         PrimitiveType;
  AdtJavaDimExprs*              DimExprs;
  AdtJavaDims*                  Dims;
  AdtJavaName*                  Name;

public:
  AdtJavaPrimary(AdtParser* pPrimaryNoNewArrayObj,
                 AdtParser* pPrimitiveTypeObj,
                 AdtParser* pDimExprsObj,
                 AdtParser* pDimsObj,
                 AdtParser* pNameObj);

  AdtJavaPrimary(const AdtJavaPrimary& rCopy);
  virtual ~AdtJavaPrimary();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPrimaryNoNewArray class
//  ----------------------------------------------------------------------------
class AdtJavaPrimaryNoNewArray : public AdtJavaBase
{
protected:
  AdtJavaLiteral*                         Literal;
  AdtJavaExpression*                      Expression;
  AdtJavaClassInstanceCreationExpression* ClassInstanceCreationExpression;
  AdtJavaPrimary*                         Primary;
  AdtJavaMethodInvocation*                MethodInvocation;
  AdtJavaName*                            Name;
  AdtJavaPrimaryNoNewArray*               PrimaryNoNewArray;
  bool                                    IsSuper;

public:
  AdtJavaPrimaryNoNewArray(const char* pIdentifier,
                           AdtParser* pLiteralObj,
                           AdtParser* pExpressionObj,
                           AdtParser* pClassInstanceCreationExpressionObj,
                           AdtParser* pPrimaryObj,
                           AdtParser* pMethodInvocationObj,
                           AdtParser* pNameObj,
                           AdtParser* pPrimaryNoNewArrayObj,
                           bool bIsSuper);

  AdtJavaPrimaryNoNewArray(const AdtJavaPrimaryNoNewArray& rCopy);
  virtual ~AdtJavaPrimaryNoNewArray();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaClassInstanceCreationExpression class
//  ----------------------------------------------------------------------------
class AdtJavaClassInstanceCreationExpression : public AdtJavaBase
{
protected:
  AdtJavaName*             Name;
  AdtJavaArgumentList*     ArgumentList;

public:
  AdtJavaClassInstanceCreationExpression(AdtParser* pNameObj,
                                         AdtParser* pArgumentListObj);

  AdtJavaClassInstanceCreationExpression(const AdtJavaClassInstanceCreationExpression& rCopy);
  virtual ~AdtJavaClassInstanceCreationExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaArgumentList class
//  ----------------------------------------------------------------------------
class AdtJavaArgumentList : public AdtJavaBase
{
public:
  AdtJavaArgumentList(AdtParser* pExpressionObj);
  AdtJavaArgumentList(const AdtJavaArgumentList& rCopy);
  virtual ~AdtJavaArgumentList();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaExpression);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaDimExprs class
//  ----------------------------------------------------------------------------
class AdtJavaDimExprs : public AdtJavaBase
{
public:
  AdtJavaDimExprs(AdtParser* pDimExprObj);
  AdtJavaDimExprs(const AdtJavaDimExprs& rCopy);
  virtual ~AdtJavaDimExprs();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declListType(AdtJavaDimExpr);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaDimExpr class
//  ----------------------------------------------------------------------------
class AdtJavaDimExpr : public AdtJavaBase
{
protected:
  AdtJavaExpression*            Expression;

public:
  AdtJavaDimExpr(AdtParser* pExpressionObj);
  AdtJavaDimExpr(const AdtJavaDimExpr& rCopy);
  virtual ~AdtJavaDimExpr();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaDims class
//  ----------------------------------------------------------------------------
class AdtJavaDims : public AdtJavaBase
{
protected:
  AdtJavaDims*                  Dims;

public:
  AdtJavaDims(AdtParser* pDimsObj);
  AdtJavaDims(const AdtJavaDims& rCopy);
  virtual ~AdtJavaDims();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaMethodInvocation class
//  ----------------------------------------------------------------------------
class AdtJavaMethodInvocation : public AdtJavaBase
{
protected:
  AdtJavaName*             Name;
  AdtJavaPrimary*          Primary;
  AdtJavaArgumentList*     ArgumentList;

public:
  AdtJavaMethodInvocation(const char* pIdentifier,
                          AdtParser* pNameObj,
                          AdtParser* pPrimaryObj,
                          AdtParser* pArgumentListObj);

  AdtJavaMethodInvocation(const AdtJavaMethodInvocation& rCopy);
  virtual ~AdtJavaMethodInvocation();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPostfixExpression class
//  ----------------------------------------------------------------------------
class AdtJavaPostfixExpression : public AdtJavaBase
{
protected:
  AdtJavaName*                    Name;
  AdtJavaPrimary*                 Primary;
  AdtJavaPostIncDecExpression*    PostIncDecExpression;

public:
  AdtJavaPostfixExpression(AdtParser* pNameObj,
                           AdtParser* pPrimaryObj,
                           AdtParser* pPostIncDecExpressionObj);

  AdtJavaPostfixExpression(const AdtJavaPostfixExpression& rCopy);
  virtual ~AdtJavaPostfixExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPostIncDecExpression class
//  ----------------------------------------------------------------------------
class AdtJavaPostIncDecExpression : public AdtJavaBase
{
protected:
  AdtJavaPostfixExpression*     PostfixExpression;
  bool                          Increment;

public:
  AdtJavaPostIncDecExpression(AdtParser* pPostfixExpressionObj,
                              bool bIncrement);

  AdtJavaPostIncDecExpression(const AdtJavaPostIncDecExpression& rCopy);
  virtual ~AdtJavaPostIncDecExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaPreIncDecExpression class
//  ----------------------------------------------------------------------------
class AdtJavaPreIncDecExpression : public AdtJavaBase
{
protected:
  AdtJavaUnaryExpression*       UnaryExpression;
  bool                          Increment;

public:
  AdtJavaPreIncDecExpression(AdtParser* pUnaryExpressionObj,
                             bool bIncrement);

  AdtJavaPreIncDecExpression(const AdtJavaPreIncDecExpression& rCopy);
  virtual ~AdtJavaPreIncDecExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaUnaryExpression class
//  ----------------------------------------------------------------------------
class AdtJavaUnaryExpression : public AdtJavaBase
{
protected:
  AdtJavaPreIncDecExpression*         PreIncDecExpression;
  AdtJavaUnaryExpression*             UnaryExpression;
  AdtJavaUnaryExpressionNotPlusMinus* UnaryExpressionNotPlusMinus;
  bool                                IsPlus;

public:
  AdtJavaUnaryExpression(AdtParser* pPreIncDecExpressionObj,
                         AdtParser* pUnaryExpressionObj,
                         AdtParser* pUnaryExpressionNotPlusMinusObj,
                         bool bIsPlus);

  AdtJavaUnaryExpression(const AdtJavaUnaryExpression& rCopy);
  virtual ~AdtJavaUnaryExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaUnaryExpressionNotPlusMinus class
//  ----------------------------------------------------------------------------
class AdtJavaUnaryExpressionNotPlusMinus : public AdtJavaBase
{
protected:
  AdtJavaPostfixExpression*     PostfixExpression;
  AdtJavaUnaryExpression*       UnaryExpression;
  AdtJavaCastExpression*        CastExpression;
  bool                          Logical;

public:
  AdtJavaUnaryExpressionNotPlusMinus(AdtParser* pPostfixExpressionObj,
                                     AdtParser* pUnaryExpressionObj,
                                     AdtParser* pCastExpressionObj,
                                     bool bLogical);

  AdtJavaUnaryExpressionNotPlusMinus(const AdtJavaUnaryExpressionNotPlusMinus& rCopy);
  virtual ~AdtJavaUnaryExpressionNotPlusMinus();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaCastExpression class
//  ----------------------------------------------------------------------------
class AdtJavaCastExpression : public AdtJavaBase
{
protected:
  AdtJavaPrimitiveType*               PrimitiveType;
  AdtJavaUnaryExpression*             UnaryExpression;
  AdtJavaUnaryExpressionNotPlusMinus* UnaryExpressionNotPlusMinus;
  AdtJavaExpression*                  Expression;
  AdtJavaDims*                        Dims;
  AdtJavaName*                        Name;

public:
  AdtJavaCastExpression(AdtParser* pPrimitiveTypeObj,
                        AdtParser* pUnaryExpressionObj,
                        AdtParser* pUnaryExpressionNotPlusMinusObj,
                        AdtParser* pExpressionObj,
                        AdtParser* pDimsObj,
                        AdtParser* pNameObj);

  AdtJavaCastExpression(const AdtJavaCastExpression& rCopy);
  virtual ~AdtJavaCastExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtJavaMultOpEnum
{
  JavaMultOp_MULTIPLY = 0,
  JavaMultOp_DIV      = 1,
  JavaMultOp_MOD      = 2
};


//  ----------------------------------------------------------------------------
//  AdtJavaMultiplicativeExpression class
//  ----------------------------------------------------------------------------
class AdtJavaMultiplicativeExpression : public AdtJavaBase
{
protected:
  AdtJavaUnaryExpression*           UnaryExpression;
  AdtJavaMultiplicativeExpression*  MultiplicativeExpression;
  AdtJavaMultOpEnum                 Op;

public:
  AdtJavaMultiplicativeExpression(AdtParser* pUnaryExpressionObj,
                                  AdtParser* pMultiplicativeExpressionObj,
                                  AdtJavaMultOpEnum nOp);

  AdtJavaMultiplicativeExpression(const AdtJavaMultiplicativeExpression& rCopy);
  virtual ~AdtJavaMultiplicativeExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtJavaAddOpEnum
{
  JavaAddOp_PLUS  = 0,
  JavaAddOp_MINUS = 1
};


//  ----------------------------------------------------------------------------
//  AdtJavaAdditiveExpression class
//  ----------------------------------------------------------------------------
class AdtJavaAdditiveExpression : public AdtJavaBase
{
protected:
  AdtJavaMultiplicativeExpression*  MultiplicativeExpression;
  AdtJavaAdditiveExpression*        AdditiveExpression;
  AdtJavaAddOpEnum                  Op;

public:
  AdtJavaAdditiveExpression(AdtParser* pMultiplicativeExpressionObj,
                            AdtParser* pAdditiveExpressionObj,
                            AdtJavaAddOpEnum nOp);

  AdtJavaAdditiveExpression(const AdtJavaAdditiveExpression& rCopy);
  virtual ~AdtJavaAdditiveExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtJavaShiftOpEnum
{
  JavaShiftOp_SAL = 0,
  JavaShiftOp_SAR = 1,
  JavaShiftOp_SHR = 2
};


//  ----------------------------------------------------------------------------
//  AdtJavaShiftExpression class
//  ----------------------------------------------------------------------------
class AdtJavaShiftExpression : public AdtJavaBase
{
protected:
  AdtJavaAdditiveExpression*    AdditiveExpression;
  AdtJavaShiftExpression*       ShiftExpression;
  AdtJavaShiftOpEnum            Op;

public:
  AdtJavaShiftExpression(AdtParser* pAdditiveExpressionObj,
                         AdtParser* pShiftExpressionObj,
                         AdtJavaShiftOpEnum nOp);

  AdtJavaShiftExpression(const AdtJavaShiftExpression& rCopy);
  virtual ~AdtJavaShiftExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtJavaRelOpEnum
{
  JavaRelOp_LT          = 0,
  JavaRelOp_GT          = 1,
  JavaRelOp_LTE         = 2,
  JavaRelOp_GTE         = 3,
  JavaRelOp_INSTANCEOF  = 4
};


//  ----------------------------------------------------------------------------
//  AdtJavaRelationalExpression class
//  ----------------------------------------------------------------------------
class AdtJavaRelationalExpression : public AdtJavaBase
{
protected:
  AdtJavaShiftExpression*       ShiftExpression;
  AdtJavaRelationalExpression*  RelationalExpression;
  AdtJavaName*                  Name;
  AdtJavaType*                  ArrayType;
  AdtJavaRelOpEnum              Op;

public:
  AdtJavaRelationalExpression(AdtParser* pShiftExpressionObj,
                              AdtParser* pRelationalExpressionObj,
                              AdtParser* pNameObj,
                              AdtParser* pArrayTypeObj,
                              AdtJavaRelOpEnum nOp);

  AdtJavaRelationalExpression(const AdtJavaRelationalExpression& rCopy);
  virtual ~AdtJavaRelationalExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtJavaEqualityOpEnum
{
  AdtJavaEqualityOp_EQ = 0,
  AdtJavaEqualityOp_NE = 1
};


//  ----------------------------------------------------------------------------
//  AdtJavaEqualityExpression class
//  ----------------------------------------------------------------------------
class AdtJavaEqualityExpression : public AdtJavaBase
{
protected:
  AdtJavaRelationalExpression*  RelationalExpression;
  AdtJavaEqualityExpression*    EqualityExpression;
  AdtJavaEqualityOpEnum         Op;

public:
  AdtJavaEqualityExpression(AdtParser* pRelationalExpressionObj,
                            AdtParser* pEqualityExpressionObj,
                            AdtJavaEqualityOpEnum nOp);

  AdtJavaEqualityExpression(const AdtJavaEqualityExpression& rCopy);
  virtual ~AdtJavaEqualityExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaAndExpression class
//  ----------------------------------------------------------------------------
class AdtJavaAndExpression : public AdtJavaBase
{
protected:
  AdtJavaEqualityExpression*    EqualityExpression;
  AdtJavaAndExpression*         AndExpression;

public:
  AdtJavaAndExpression(AdtParser* pEqualityExpressionObj,
                       AdtParser* pAndExpressionObj);

  AdtJavaAndExpression(const AdtJavaAndExpression& rCopy);
  virtual ~AdtJavaAndExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaExclusiveOrExpression class
//  ----------------------------------------------------------------------------
class AdtJavaExclusiveOrExpression : public AdtJavaBase
{
protected:
  AdtJavaAndExpression*         AndExpression;
  AdtJavaExclusiveOrExpression* ExclusiveOrExpression;

public:
  AdtJavaExclusiveOrExpression(AdtParser* pAndExpressionObj,
                               AdtParser* pExclusiveOrExpressionObj);

  AdtJavaExclusiveOrExpression(const AdtJavaExclusiveOrExpression& rCopy);
  virtual ~AdtJavaExclusiveOrExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaInclusiveOrExpression class
//  ----------------------------------------------------------------------------
class AdtJavaInclusiveOrExpression : public AdtJavaBase
{
protected:
  AdtJavaExclusiveOrExpression* ExclusiveOrExpression;
  AdtJavaInclusiveOrExpression* InclusiveOrExpression;

public:
  AdtJavaInclusiveOrExpression(AdtParser* pExclusiveOrExpressionObj,
                               AdtParser* pInclusiveOrExpressionObj);

  AdtJavaInclusiveOrExpression(const AdtJavaInclusiveOrExpression& rCopy);
  virtual ~AdtJavaInclusiveOrExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalAndExpression class
//  ----------------------------------------------------------------------------
class AdtJavaConditionalAndExpression : public AdtJavaBase
{
protected:
  AdtJavaInclusiveOrExpression*     InclusiveOrExpression;
  AdtJavaConditionalAndExpression*  ConditionalAndExpression;

public:
  AdtJavaConditionalAndExpression(AdtParser* pInclusiveOrExpressionObj,
                                  AdtParser* pConditionalAndExpressionObj);

  AdtJavaConditionalAndExpression(const AdtJavaConditionalAndExpression& rCopy);
  virtual ~AdtJavaConditionalAndExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalOrExpression class
//  ----------------------------------------------------------------------------
class AdtJavaConditionalOrExpression : public AdtJavaBase
{
protected:
  AdtJavaConditionalAndExpression* ConditionalAndExpression;
  AdtJavaConditionalOrExpression*  ConditionalOrExpression;

public:
  AdtJavaConditionalOrExpression(AdtParser* pConditionalAndExpressionObj,
                                 AdtParser* pConditionalOrExpressionObj);

  AdtJavaConditionalOrExpression(const AdtJavaConditionalOrExpression& rCopy);
  virtual ~AdtJavaConditionalOrExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaConditionalExpression class
//  ----------------------------------------------------------------------------
class AdtJavaConditionalExpression : public AdtJavaBase
{
protected:
  AdtJavaConditionalOrExpression* ConditionalOrExpression;
  AdtJavaConditionalExpression*   ConditionalExpression;
  AdtJavaExpression*              Expression;

public:
  AdtJavaConditionalExpression(AdtParser* pConditionalOrExpressionObj,
                               AdtParser* pExpressionObj,
                               AdtParser* pConditionalExpressionObj);

  AdtJavaConditionalExpression(const AdtJavaConditionalExpression& rCopy);
  virtual ~AdtJavaConditionalExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaExpression class
//  ----------------------------------------------------------------------------
class AdtJavaExpression : public AdtJavaBase
{
protected:
  AdtJavaConditionalExpression* ConditionalExpression;
  AdtJavaAssignment*            Assignment;

public:
  AdtJavaExpression(AdtParser* pConditionalExpressionObj,
                    AdtParser* pAssignmentObj);

  AdtJavaExpression(const AdtJavaExpression& rCopy);
  virtual ~AdtJavaExpression();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtJavaAssignment class
//  ----------------------------------------------------------------------------
class AdtJavaAssignment : public AdtJavaBase
{
protected:
  AdtJavaName*                  Name;
  AdtJavaAssignmentOperator*    AssignmentOperator;
  AdtJavaExpression*            Expression;
  AdtJavaExpression*            Expression2;
  AdtJavaPrimary*               Primary;
  AdtJavaPrimaryNoNewArray*     PrimaryNoNewArray;
  bool                          IsSuper;

public:
  AdtJavaAssignment(const char* pIdentifier,
                    AdtParser* pNameObj,
                    AdtParser* pAssignmentOperatorObj,
                    AdtParser* pExpressionObj,
                    AdtParser* pPrimaryObj,
                    AdtParser* pPrimaryNoNewArrayObj,
                    AdtParser* pExpression2Obj,
                    bool bIsSuper);

  AdtJavaAssignment(const AdtJavaAssignment& rCopy);
  virtual ~AdtJavaAssignment();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};

//  ----------------------------------------------------------------------------

enum AdtJavaAssignmentOpEnum
{
  AdtJavaAssignmentOp_EQUALS        = 0,
  AdtJavaAssignmentOp_TIMES_EQUALS  = 1,
  AdtJavaAssignmentOp_DIV_EQUALS    = 2,
  AdtJavaAssignmentOp_MOD_EQUALS    = 3,
  AdtJavaAssignmentOp_PLUS_EQUALS   = 4,
  AdtJavaAssignmentOp_MINUS_EQUALS  = 5,
  AdtJavaAssignmentOp_SAL_EQUALS    = 6,
  AdtJavaAssignmentOp_SAR_EQUALS    = 7,
  AdtJavaAssignmentOp_SHR_EQUALS    = 8,
  AdtJavaAssignmentOp_AND_EQUALS    = 9,
  AdtJavaAssignmentOp_XOR_EQUALS    = 10,
  AdtJavaAssignmentOp_OR_EQUALS     = 11
};


//  ----------------------------------------------------------------------------
//  AdtJavaAssignmentOperator class
//  ----------------------------------------------------------------------------
class AdtJavaAssignmentOperator : public AdtJavaBase
{
protected:
  AdtJavaAssignmentOpEnum       Op;

public:
  AdtJavaAssignmentOperator(AdtJavaAssignmentOpEnum nOp);
  AdtJavaAssignmentOperator(const AdtJavaAssignmentOperator& rCopy);
  virtual ~AdtJavaAssignmentOperator();

  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeJava(AdtFile& rOutFile) const;

  declType;
};


#endif //__cplusplus
#endif //__ADTJava_HPP
