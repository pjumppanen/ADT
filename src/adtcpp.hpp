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
//    AdtCpp.hpp
//
//  Purpose:
//    This file includes declarations of classes used to collate information
//    describing the CPP file being auto-differentiated.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTCPP_HPP
#define __ADTCPP_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void* adtCpp_setRoot(void* pRoot);
C_FUNCTION void* adtCpp_getRoot(void);
C_FUNCTION void  adtCpp_releaseRoot(void);
C_FUNCTION void  adtCpp_releaseObject(void* pObj);
C_FUNCTION void* adtCppList_add(void* pList, void* pObj);
C_FUNCTION void* adtCppTranslationUnit_create(void* pObj);
C_FUNCTION void* adtCppMacro_create(const char* pIdentifier, void* pExpressionListObj, void* pStatementSeqObj, void* pSimpleDeclarationListObj);
C_FUNCTION void* adtCppSimpleDeclarationList_create(void* pSimpleDeclarationObj);
C_FUNCTION void* adtCppPostfixExpression_create(void* pExpressionObj, void* pPostfixExpressionObj, void* pDirectedExpressionObj, int nIncrement, const char* pLiteral);
C_FUNCTION void* adtCppExpressionList_create(void* pAssignmentExpressionObj);
C_FUNCTION void* adtCppDirectedExpression_create(void* pDeclaratorExpressionObj);
C_FUNCTION void* adtCppDeclaratorExpression_create(const char* pIdentifier, void* pExpressionListObj, void* pDeclaratorExpressionDimsObj, int nQualified, int nHasBrackets);
C_FUNCTION void* adtCppDeclaratorExpressionDims_create(void* pExpressionObj);
C_FUNCTION void* adtCppUnaryExpression_create(void* pPostfixExpressionObj, void* pUnaryExpressionObj, void* pUnaryOperatorObj, void* pExpressionObj, int nIncrement);
C_FUNCTION void* adtCppUnaryOperator_create(int nOp);
C_FUNCTION void* adtCppMultiplicativeExpression_create(int nOp, void* pUnaryExpressionObj, void* pMultiplicativeExpressionObj);
C_FUNCTION void* adtCppAdditiveExpression_create(int nOp, void* pMultiplicativeExpressionObj, void* pAdditiveExpressionObj);
C_FUNCTION void* adtCppShiftExpression_create(int nOp, void* pAdditiveExpressionObj, void* pShiftExpressionObj);
C_FUNCTION void* adtCppRelationalExpression_create(int nOp, void* pShiftExpressionObj, void* pRelationalExpressionObj);
C_FUNCTION void* adtCppEqualityExpression_create(int nOp, void* pRelationalExpressionObj, void* pEqualityExpressionObj);
C_FUNCTION void* adtCppAndExpression_create(void* pEqualityExpressionObj, void* pAndExpressionObj);
C_FUNCTION void* adtCppExclusiveOrExpression_create(void* pAndExpressionObj, void* pExclusiveOrExpressionObj);
C_FUNCTION void* adtCppInclusiveOrExpression_create(void* pExclusiveOrExpressionObj, void* pInclusiveOrExpressionObj);
C_FUNCTION void* adtCppLogicalAndExpression_create(void* pInclusiveOrExpressionObj, void* pLogicalAndExpressionObj);
C_FUNCTION void* adtCppLogicalOrExpression_create(void* pLogicalAndExpressionObj, void* pLogicalOrExpressionObj);
C_FUNCTION void* adtCppConditionalExpression_create(void* pLogicalOrExpressionObj, void* pExpressionObj, void* pAssignmentExpressionObj);
C_FUNCTION void* adtCppAssignmentExpression_create(void* pConditionalExpressionObj, void* pLogicalOrExpressionObj, void* pAssignmentOperatorObj, void* pAssignmentExpressionObj);
C_FUNCTION void* adtCppAssignmentOperator_create(int nOp);
C_FUNCTION void* adtCppExpression_create(void* pAssignmentExpressionObj, void* pExpressionObj);
C_FUNCTION void* adtCppConstantExpression_create(void* pConditionalExpressionObj);
C_FUNCTION void* adtCppStatement_create(void* pLabeledStatementObj, void* pExpressionStatementObj, void* pCompoundStatementObj, void* pSelectionStatementObj, void* pIterationStatementObj, void* pJumpStatementObj, void* pDeclarationStatementObj);
C_FUNCTION void* adtCppLabeledStatement_create(void* pConstantExpressionObj, void* pStatementObj, const char* pIdentifier, int nIsDefault);
C_FUNCTION void* adtCppExpressionStatement_create(void* pExpressionObj);
C_FUNCTION void* adtCppCompoundStatement_create(void* pStatementSeqObj);
C_FUNCTION void* adtCppStatementSeq_create(void* pStatementObj);
C_FUNCTION void* adtCppSelectionStatement_create(void* pExpressionObj, void* pStatementObj, void* pStatement2Obj, int nIsIf);
C_FUNCTION void* adtCppIterationStatement_create(void* pForInitStatementObj, void* pExpressionObj, void* pExpression2Obj, void* pStatementObj, int nIsDo);
C_FUNCTION void* adtCppForInitStatement_create(void* pExpressionStatementObj, void* pSimpleDeclarationObj);
C_FUNCTION void* adtCppJumpStatement_create(void* pExpressionObj, const char* pIndentifier, int nType);
C_FUNCTION void* adtCppDeclarationStatement_create(void* pBlockDeclarationObj);
C_FUNCTION void* adtCppDeclarationSeq_create(void* pDeclarationObj);
C_FUNCTION void* adtCppDeclaration_create(void* pBlockDeclarationObj, void* pFunctionDefinitionObj, void* pLinkageSpecificationObj, void* pNamespaceDefinitionObj);
C_FUNCTION void* adtCppBlockDeclaration_create(void* pSimpleDeclarationObj, void* pAsmDefinitionObj, void* pNamespaceAliasDefinitionObj, void* pUsingDeclarationObj, void* pUsingDirectiveObj);
C_FUNCTION void* adtCppSimpleDeclaration_create(void* pClassSpecifierObj, void* pEnumSpecifierObj, void* pSimpleTypeSpecifierObj, void* pInitDeclaratorListObj, void* pDeclModifierListObj, int nHasTypeDef);
C_FUNCTION int   adtCppSimpleDeclaration_isTypeDef(void* pCppSimpleDeclarationObj, const char** ppAliasName);
C_FUNCTION void* adtCppDeclModifier_create(int nType);
C_FUNCTION void* adtCppDeclModifierList_create(void* pDeclModifierObj);
C_FUNCTION void* adtCppClassSpecifier_create(void* pClassKeyObj, void* pBaseSpecifierListObj, void* pMemberSpecificationObj, int nWithBrackets);
C_FUNCTION void* adtCppEnumSpecifierName_create(const char* pIdentifier, int nQualified);
C_FUNCTION void* adtCppEnumSpecifier_create(void* pEnumeratorListObj, void* pEnumSpecifierName, int nWithBrackets);
C_FUNCTION void* adtCppSimpleTypeSpecifier_create(const char* pIdentifier, int nType, int nByRef);
C_FUNCTION void* adtCppEnumeratorList_create(void* pEnumeratorDefinitionObj);
C_FUNCTION void* adtCppEnumeratorDefinition_create(void* pConstantExpressionObj, const char* pIdentifier);
C_FUNCTION void* adtCppNamespaceDefinition_create(void* pDeclarationSeqObj, const char* pIdentifier);
C_FUNCTION void* adtCppNamespaceAliasDefinition_create(const char* pIdentifier, const char* pQualifiedIdentifier);
C_FUNCTION void* adtCppUsingDeclaration_create(const char* pQualifiedIdentifier, int nWithTypename);
C_FUNCTION void* adtCppUsingDirective_create(const char* pIdentifier, int nQualified);
C_FUNCTION void* adtCppAsmDefinition_create(const char* pStringLiteral);
C_FUNCTION void* adtCppLinkageSpecification_create(void* pDeclarationSeqObj, void* pDeclarationObj, const char* pStringLiteral);
C_FUNCTION void* adtCppInitDeclaratorList_create(void* pInitDeclaratorObj);
C_FUNCTION void* adtCppInitDeclarator_create(void* pDeclaratorObj, void* pInitializerObj);
C_FUNCTION void* adtCppDeclarator_create(void* pParameterDeclarationClauseObj, void* pExpressionListObj, void* pDeclaratorDimsObj, const char* pIdentifier, int nWithBrackets, int nQualified, int nIsObj, int nVirtual, int nType, int nInitQualifiedName);
C_FUNCTION void* adtCppDeclaratorDims_create(void* pConstantExpressionObj, void* pDeclaratorDimsObj);
C_FUNCTION void* adtCppParameterDeclarationClause_create(void* pParameterDeclarationListObj, int nHasEllipsis, int nHasComma);
C_FUNCTION void* adtCppParameterDeclarationList_create(void* pParameterDeclarationObj);
C_FUNCTION void* adtCppParameterDeclaration_create(void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pDeclaratorObj, void* pAssignmentExpressionObj);
C_FUNCTION void* adtCppFunctionDefinition_create(void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pDeclaratorObj, void* pCtorInitializerObj, void* pFunctionBodyObj, int nHasSemiColon);
C_FUNCTION void* adtCppFunctionBody_create(void* pCompoundStatementObj);
C_FUNCTION void* adtCppInitializer_create(void* pInitializerClauseObj, void* pExpressionListObj);
C_FUNCTION void* adtCppInitializerClause_create(void* pAssignmentExpressionObj, void* pInitializerListObj, int nHasComma);
C_FUNCTION void* adtCppInitializerList_create(void* pInitializerClauseObj);
C_FUNCTION void* adtCppClassKey_create(int nType, const char* pIdentifier, int nQualified);
C_FUNCTION void* adtCppMemberSpecification_create(void* pMemberDeclarationObj);
C_FUNCTION void* adtCppMemberDeclaration_create(void* pClassSpecifierObj, void* pEnumSpecifierObj, void* pDeclModifierListObj, void* pSimpleTypeSpecifierObj, void* pMemberDeclarationListObj, void* pFunctionDefinitionObj, void* pUsingDeclarationObj, int nType, int nHasSemicolon);
C_FUNCTION void* adtCppMemberDeclarationList_create(void* pMemberDeclaratorObj);
C_FUNCTION void* adtCppMemberDeclarator_create(void* pDeclaratorObj, const char* pIdentifier);
C_FUNCTION void* adtCppBaseSpecifierList_create(void* pBaseSpecifierObj);
C_FUNCTION void* adtCppBaseSpecifier_create(int nType, int nVirtual, int nQualified, const char* pIdentifier);
C_FUNCTION void* adtCppCtorInitializer_create(void* pMemInitializerListObj);
C_FUNCTION void* adtCppMemInitializerList_create(void* pMemInitializerObj);
C_FUNCTION void* adtCppMemInitializer_create(void* pMemInitializerIdObj, void* pExpressionListObj);
C_FUNCTION void* adtCppMemInitializerId_create(int nQualified, const char* pIdentifier);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"
#include "adtblackbox.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtCppTranslationUnit;
class AdtCppMacro;
class AdtCppSimpleDeclarationList;
class AdtCppDeclarationSeq;
class AdtCppExpression;
class AdtCppPostfixExpression;
class AdtCppExpressionList;
class AdtCppDirectedExpression;
class AdtCppDeclaratorExpression;
class AdtCppDeclaratorExpressionDims;
class AdtCppUnaryExpression;
class AdtCppUnaryOperator;
class AdtCppMultiplicativeExpression;
class AdtCppAdditiveExpression;
class AdtCppShiftExpression;
class AdtCppRelationalExpression;
class AdtCppEqualityExpression;
class AdtCppAndExpression;
class AdtCppExclusiveOrExpression;
class AdtCppInclusiveOrExpression;
class AdtCppLogicalAndExpression;
class AdtCppLogicalOrExpression;
class AdtCppConditionalExpression;
class AdtCppAssignmentExpression;
class AdtCppAssignmentOperator;
class AdtCppExpression;
class AdtCppConstantExpression;
class AdtCppLabeledStatement;
class AdtCppStatement;
class AdtCppExpressionStatement;
class AdtCppCompoundStatement;
class AdtCppSelectionStatement;
class AdtCppIterationStatement;
class AdtCppJumpStatement;
class AdtCppDeclarationStatement;
class AdtCppStatementSeq;
class AdtCppForInitStatement;
class AdtCppSimpleDeclaration;
class AdtCppBlockDeclaration;
class AdtCppDeclaration;
class AdtCppFunctionDefinition;
class AdtCppLinkageSpecification;
class AdtCppNamespaceDefinition;
class AdtCppInitDeclaratorList;
class AdtCppDeclModifierList;
class AdtCppDeclModifier;
class AdtCppSimpleTypeSpecifier;
class AdtCppClassSpecifier;
class AdtCppClassKey;
class AdtCppBaseSpecifierList;
class AdtCppMemberSpecification;
class AdtCppEnumSpecifierName;
class AdtCppEnumSpecifier;
class AdtCppEnumeratorList;
class AdtCppEnumeratorDefinition;
class AdtCppNamespaceAliasDefinition;
class AdtCppUsingDeclaration;
class AdtCppUsingDirective;
class AdtCppAsmDefinition;
class AdtCppInitDeclarator;
class AdtCppDeclarator;
class AdtCppInitializer;
class AdtCppDeclaratorDims;
class AdtCppParameterDeclarationClause;
class AdtCppParameterDeclarationList;
class AdtCppParameterDeclaration;
class AdtCppCtorInitializer;
class AdtCppFunctionBody;
class AdtCppInitializerClause;
class AdtCppInitializerList;
class AdtCppMemberDeclaration;
class AdtCppMemberDeclarationList;
class AdtCppMemberDeclarator;
class AdtCppBaseSpecifier;
class AdtCppMemInitializerList;
class AdtCppMemInitializer;
class AdtCppMemInitializerId;


//  ----------------------------------------------------------------------------
//  AdtCppToFortranTypeConversion class
//  ----------------------------------------------------------------------------
//  This class is used in conjunction with a map to maintain a substitution
//  mapping from CPP complex types to equivalent fortran ones (ie. MB's
//  arrays mapped into fortran equivalents).
//  ----------------------------------------------------------------------------
class AdtCppToFortranTypeConversion
{
public:
  string  CppType;
  string  FortranType;
  string  FortranDimension;
  string  FortranDimensionString;

private:
  void    initialise();

public:
  AdtCppToFortranTypeConversion();
  AdtCppToFortranTypeConversion(const char* pCppType,
                                const char* pFortranType,
                                const char* pFortranDimension);
  AdtCppToFortranTypeConversion(const AdtCppToFortranTypeConversion& rCopy);
  virtual ~AdtCppToFortranTypeConversion();
};

//  ----------------------------------------------------------------------------

inline AdtCppToFortranTypeConversion::AdtCppToFortranTypeConversion()
 : CppType(),
   FortranType(),
   FortranDimension(),
   FortranDimensionString()
{

}

//  ----------------------------------------------------------------------------

inline AdtCppToFortranTypeConversion::AdtCppToFortranTypeConversion(const char* pCppType,
                                                                    const char* pFortranType,
                                                                    const char* pFortranDimension)
 : CppType(pCppType),
   FortranType(pFortranType),
   FortranDimension(pFortranDimension),
   FortranDimensionString()
{
  initialise();
}

//  ----------------------------------------------------------------------------

inline AdtCppToFortranTypeConversion::AdtCppToFortranTypeConversion(const AdtCppToFortranTypeConversion& rCopy)
 : CppType(rCopy.CppType),
   FortranType(rCopy.FortranType),
   FortranDimension(rCopy.FortranDimension),
   FortranDimensionString(rCopy.FortranDimensionString)
{

}

//  ----------------------------------------------------------------------------

inline AdtCppToFortranTypeConversion::~AdtCppToFortranTypeConversion()
{
  //Do nothing
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtCppToFortranTypeConversion by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtCppToFortranTypeConversion>                        AdtCppToFortranTypeConversionStringPair;
typedef std::map<string, AdtCppToFortranTypeConversion, string_less>                  AdtCppToFortranTypeConversionByStringMap;
typedef std::map<string, AdtCppToFortranTypeConversion, string_less>::iterator        AdtCppToFortranTypeConversionByStringMapIter;
typedef std::map<string, AdtCppToFortranTypeConversion, string_less>::const_iterator  AdtCppToFortranTypeConversionByStringMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::map<string, AdtCppToFortranTypeConversion>                               AdtCppToFortranTypeConversionByStringMapCS;
typedef std::map<string, AdtCppToFortranTypeConversion>::iterator                     AdtCppToFortranTypeConversionByStringMapCSIter;
typedef std::map<string, AdtCppToFortranTypeConversion>::const_iterator               AdtCppToFortranTypeConversionByStringMapCSConstIter;


//  ----------------------------------------------------------------------------
//  These class definitions map 1:1 to the grammar rules for the parser
//  ----------------------------------------------------------------------------
class AdtCppBase : public AdtParser
{
protected:
  static AdtCppTranslationUnit*                     CppRootObject;
  static AdtCppToFortranTypeConversionByStringMapCS FortranTypeMap;
  static AdtCppToFortranTypeConversionByStringMap   CppTypeMap;

protected:
  AdtFile&                      forAllWriteFortran(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false, const char* pSuffix = 0, bool bReverse = false) const;
  AdtFile&                      forAllWriteCPP(AdtFile& pOutFile, int nMode, const char* pDelimiter = 0, bool bNewline = false, bool bExcludeLast = false) const;
  AdtFile&                      writePragmas(AdtFile& rOutFile) const;

public:
  AdtCppBase();
  AdtCppBase(const AdtCppBase& rCopy);
  virtual ~AdtCppBase();

  static void                   rootBindComments(AdtCommon* pCompilerBase);

  static void                   nameToFortran(const char* pName, string& rConvertedName);

  static void                   prefixFromQualifiedName(const char* pName, string& rPrefix);
  static bool                   qualifiedName(string& rName, const char* pPrefix);

  static AdtCppStatementSeq*    expressionBuild(const char* pCodeString);

  static AdtCppStatement*       createSimpleVariableDeclarationStatementFrom(AdtParser* pInitDeclaratorObj);

  static void                   addFortranTypeMap(const string& rCppType,
                                                  const string& rFortranType,
                                                  const string& rFortranSize);

  static void                   cppRootObject(AdtParser* pRoot);
  static AdtCppTranslationUnit* cppRootObject();

  static bool                   mapTypesToFortran(const char* pTypeName,
                                                  const char*& pType,
                                                  const char*& pDimension);

  static bool                   mapTypesToCpp(const char* pTypeName,
                                              size_t nDimension,
                                              const char*& pType);

  void                          nameWithComment(const char* pName, string* pComment = 0);
  void                          mapName(const char* pName, bool bWithComment);

  virtual AdtFile&              writeFortran(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeDelphi(AdtFile& pOutFile, int nMode = 0) const;
  virtual AdtFile&              writeCPP(AdtFile& pOutFile, int nMode = 0) const;

  bool                          simpleLineageTo(const char* pParentClass) const;
  bool                          parentSimpleLineageTo(const char* pParentClass) const;

  virtual bool                  isSimple() const;

  virtual void                  linespace(AdtFile& pOutFile,
                                          bool& bLineSpace,
                                          const AdtCppBase* pLastObj,
                                          bool bPre) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtCppBase::AdtCppBase(const AdtCppBase& rCopy)
 : AdtParser(rCopy)
{

}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtCppBase::writeFortran(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtCppBase::writeDelphi(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}

//  ----------------------------------------------------------------------------

inline AdtFile& AdtCppBase::writeCPP(AdtFile& pOutFile, int nMode) const
{
  return (pOutFile);
}


//  ----------------------------------------------------------------------------
//  AdtCppCheckDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppCheckDeclaration : public AdtCppBase
{
protected:
  const string*                 QualifiedName;
  bool                          IsForwardDeclaration;

protected:
  void                          initialiseQualifiedName();

public:
  AdtCppCheckDeclaration();
  AdtCppCheckDeclaration(const AdtCppCheckDeclaration& rCopy);
  virtual ~AdtCppCheckDeclaration();

  void                          setForwardDeclaration(bool bIsForward);
  virtual bool                  isForwardDeclaration(bool bClassScope) const;
  const string&                 qualifiedName() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline void AdtCppCheckDeclaration::setForwardDeclaration(bool bIsForward)
{
  IsForwardDeclaration = bIsForward;
}

//  ----------------------------------------------------------------------------

inline bool AdtCppCheckDeclaration::isForwardDeclaration(bool bClassScope) const
{
  return (IsForwardDeclaration);
}

//  ----------------------------------------------------------------------------

inline const string& AdtCppCheckDeclaration::qualifiedName() const
{
  return (QualifiedName != 0 ? *QualifiedName : EmptyString);
}


//  ----------------------------------------------------------------------------
//  AdtCppEmbeddedComment class
//  ----------------------------------------------------------------------------
class AdtCppEmbeddedComment : public AdtCppCheckDeclaration
{
protected:
  const string*               EmbeddedComment;

protected:
  void                        initialise(const char* pIdentifier);
  void                        enumerateArraySizesFromString(AdtStringByStringMap& ArraySizeMap, string& rText) const;

public:
  AdtCppEmbeddedComment();
  AdtCppEmbeddedComment(const char* pIdentifier);
  AdtCppEmbeddedComment(const AdtCppEmbeddedComment& rCopy);
  virtual ~AdtCppEmbeddedComment();

  void                        writeArrayBounds(AdtFile& pOutFile, const char* pAbstractBounds = 0) const;

  void                        enumerateArraySizes(AdtStringList& ArrayUpperBoundList, AdtStringList& ArrayLowerBoundList) const;
  void                        enumerateArraySizes(AdtStringByStringMap& ArraySizeMap) const;
  const string&               embeddedComment() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline const string& AdtCppEmbeddedComment::embeddedComment() const
{
  return (EmbeddedComment != 0 ? *EmbeddedComment : EmptyString);
}


//  ----------------------------------------------------------------------------
//  AdtCppTranslationUnit class
//  ----------------------------------------------------------------------------
class AdtCppTranslationUnit : public AdtCppBase, public AdtSourceRoot
{
private:
  static AdtIntByStringMapCS    ProcedureMap;
  static AdtIntByStringMapCS    FunctionMap;
  static AdtParserPtrList       BlackBoxCommentsList;
  AdtCppDeclarationSeq*         DeclarationSeq;

protected:
  void                          buildMacroMap(AdtParserPtrByStringMultiMapCS& rMacroMap) const;

  void                          writeArraySizes(AdtFile& rOutFile,
                                                const AdtParserPtrByStringMap& rFunctionsMap,
                                                const AdtParserPtrByStringMap& rVarsMap) const;

  void                          addDimensionVars(const char* pClassName,
                                                 AdtParserPtrByStringMap& rVarsMap) const;

  bool                          compile(const AdtCppFunctionDefinition* pFunction,
                                        AdtParserPtrByStringMap& rFunctionsMap,
                                        AdtParserPtrByStringMap& rVarsMap,
                                        bool bExpandMacros) const;

  AdtFile&                      writeFortran(AdtFile& rOutFile,
                                             const AdtFortranExecutableProgram* pSavedRoot,
                                             const char* pClassName,
                                             const char* pLastClassName,
                                             const char* pFunctionNames,
                                             bool bExpandMacros) const;

  void                          extractClassConstructorName(const char* pConstructorDeclaration,
                                                            string& rConstructorName) const;

public:
  AdtCppTranslationUnit(AdtParser* pObj);
  AdtCppTranslationUnit(const AdtCppTranslationUnit& rCopy);
  virtual ~AdtCppTranslationUnit();

  static void                   addBlackBoxCommentsObject(AdtParser* pObj);

  static bool                   isProcedure(const char* pName);
  static bool                   isFunction(const char* pName);

  bool                          findEnum(const char* pName,
                                         const AdtParser*& pObj) const;

  bool                          findVar(const char* pName,
                                        const AdtParser*& pObj) const;

  bool                          findField(const char* pName,
                                          const char* pClassName,
                                          const AdtParser*& pObj) const;

  bool                          findFunction(const char* pName,
                                             const char* pClassName,
                                             const AdtParser*& pObj,
                                             string& rMatchName) const;

  AdtCppClassSpecifier*         findClass(const char* pClassName,
                                          string& rParentClassName) const;

  AdtCppFunctionDefinition*     findFunction(const char* pQualifiedFunctionName,
                                             string& rFunctionBaseName) const;

  void                          addFunction(AdtCppFunctionDefinition* pFunctionDefinition);

  virtual void                  enumerateMethodNames(AdtStringList& rMethodList) const;

  virtual bool                  hasClass(const char* pClassName,
                                         string& rParentClassName) const;

  virtual bool                  buildBlackBoxFile(const char* pBlackBoxFileName,
                                                  AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                  AdtStringByStringMap& rRegardAsClassSubroutineMap,
                                                  double dVersionNumber);

  virtual bool                  flattenClass(const char* pClassName,
                                             const AdtParserPtrList& rRootList,
                                             string& rUsesList,
                                             AdtStringByStringMap& rPublicMethodsMap);

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
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;

  virtual AdtSourceFileType     sourceFileType() const;

  declListType(AdtCppMacro);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMacro class
//  ----------------------------------------------------------------------------
class AdtCppMacro : public AdtCppBase
{
private:
  AdtCppExpressionList*         ExpressionList;
  AdtCppStatementSeq*           StatementSeq;
  AdtCppSimpleDeclarationList*  SimpleDeclarationList;

protected:
  bool                          isCompatible(AdtCppDeclaratorExpression* pNameObj) const;
  void                          addVariables(AdtParser* pStatementSeqObj) const;

  void                          expandMacro(AdtCppDeclaratorExpression* pNameObj,
                                            AdtCppBase* pSubstitutionRoot,
                                            bool bAllowMultiline) const;

public:
  AdtCppMacro(const char* pIdentifier,
              AdtParser* pExpressionListObj,
              AdtParser* pStatementSeqObj,
              AdtParser* pSimpleDeclarationListObj);

  AdtCppMacro(const AdtCppMacro& rCopy);
  virtual ~AdtCppMacro();

  static void                   forwardSubstitute(AdtCppFunctionDefinition* pFunctionDefinition,
                                                  AdtParserPtrByStringMultiMapCS& rMacroMap);

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationInfo class
//  ----------------------------------------------------------------------------
class AdtCppDeclarationInfo : public AdtCppBase
{
protected:
  // using namespace name list
  // InitDeclaratorList
  AdtParserPtrByStringMultiMap          NamespaceDefinitionMultiMap;
  AdtParserPtrByStringMap               FunctionDefinitionMap;
  AdtParserPtrByStringMap               VarDefinitionMap;
  AdtParserPtrByStringMap               EnumSpecifierMap;
  AdtParserPtrByStringMap               EnumSpecifierByConstantMap;
  AdtParserPtrByStringMap               ClassSpecifierMap;

protected:
  void                                  flush();

  void                                  enumerateEnumSpecifierByConstants();
  void                                  enumerateObjects(AdtParserPtrByStringMap& rMap,
                                                         const char* pSearchPath,
                                                         const char* pClassName,
                                                         bool bClassScope = false);

public:
  AdtCppDeclarationInfo();
  AdtCppDeclarationInfo(const AdtCppDeclarationInfo& rCopy);
  virtual ~AdtCppDeclarationInfo();

  static void                           enumerateScopes(AdtParserPtrList& rList,
                                                        AdtCppDeclarationSeq* pDeclSeq,
                                                        const char* pTypeName,
                                                        const char*& pBaseName,
                                                        bool bAllowUpToLast);

  void                                  enumerateFunctionDefinitions(const char* pSearchPath, bool bClassScope = false);
  void                                  enumerateVarDefinitions(const char* pSearchPath);
  void                                  enumerateEnumSpecifiers(const char* pSearchPath);
  void                                  enumerateClassSpecifiers(const char* pSearchPath);

  const AdtParserPtrByStringMultiMap&   namespaceDefinitionMultiMap() const;
  const AdtParserPtrByStringMap&        functionDefinitionMap() const;
  const AdtParserPtrByStringMap&        varDefinitionMap() const;
  const AdtParserPtrByStringMap&        enumSpecifierMap() const;
  const AdtParserPtrByStringMap&        enumSpecifierByConstantMap() const;
  const AdtParserPtrByStringMap&        classSpecifierMap() const;

  AdtCppFunctionDefinition*             findFunctionDefinition(const char* pObjName) const;
  AdtCppDeclarator*                     findVarDefinition(const char* pObjName) const;
  AdtCppEnumSpecifier*                  findEnumSpecifier(const char* pObjName) const;
  AdtCppClassSpecifier*                 findClassSpecifier(const char* pObjName) const;
  AdtCppEnumSpecifier*                  findEnumSpecifierByConst(const char* pConstName) const;

  bool                                  findFunctionDefinition(const char* pObjName, const AdtParser*& pObj) const;
  bool                                  findVarDefinition(const char* pObjName, const AdtParser*& pObj) const;
  bool                                  findEnumSpecifier(const char* pObjName, const AdtParser*& pObj) const;
  bool                                  findClassSpecifier(const char* pObjName, const AdtParser*& pObj) const;
  bool                                  findEnumSpecifierByConst(const char* pConstName, const AdtParser*& pObj) const;
};

//  ----------------------------------------------------------------------------

inline void AdtCppDeclarationInfo::enumerateFunctionDefinitions(const char* pSearchPath, bool bClassScope)
{
  enumerateObjects(FunctionDefinitionMap,
                   pSearchPath,
                   "AdtCppFunctionDefinition",
                   bClassScope);
}

//  ----------------------------------------------------------------------------

inline void AdtCppDeclarationInfo::enumerateVarDefinitions(const char* pSearchPath)
{
  enumerateObjects(VarDefinitionMap,
                   pSearchPath,
                   "AdtCppDeclarator");
}

//  ----------------------------------------------------------------------------

inline void AdtCppDeclarationInfo::enumerateEnumSpecifiers(const char* pSearchPath)
{
  enumerateObjects(EnumSpecifierMap,
                   pSearchPath,
                   "AdtCppEnumSpecifier");

  enumerateEnumSpecifierByConstants();
}

//  ----------------------------------------------------------------------------

inline void AdtCppDeclarationInfo::enumerateClassSpecifiers(const char* pSearchPath)
{
  enumerateObjects(ClassSpecifierMap,
                   pSearchPath,
                   "AdtCppClassSpecifier");
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMultiMap& AdtCppDeclarationInfo::namespaceDefinitionMultiMap() const
{
  return (NamespaceDefinitionMultiMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtCppDeclarationInfo::functionDefinitionMap() const
{
  return (FunctionDefinitionMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtCppDeclarationInfo::varDefinitionMap() const
{
  return (VarDefinitionMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtCppDeclarationInfo::enumSpecifierMap() const
{
  return (EnumSpecifierMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtCppDeclarationInfo::enumSpecifierByConstantMap() const
{
  return (EnumSpecifierByConstantMap);
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrByStringMap& AdtCppDeclarationInfo::classSpecifierMap() const
{
  return (ClassSpecifierMap);
}

//  ----------------------------------------------------------------------------

inline AdtCppFunctionDefinition* AdtCppDeclarationInfo::findFunctionDefinition(const char* pObjName) const
{
  const AdtParser*  pObj = 0;

  findObject(FunctionDefinitionMap, pObjName, pObj);

  return ((AdtCppFunctionDefinition*)pObj);
}

//  ----------------------------------------------------------------------------

inline AdtCppDeclarator* AdtCppDeclarationInfo::findVarDefinition(const char* pObjName) const
{
  const AdtParser*  pObj = 0;

  findObject(VarDefinitionMap, pObjName, pObj);

  return ((AdtCppDeclarator*)pObj);
}

//  ----------------------------------------------------------------------------

inline AdtCppEnumSpecifier* AdtCppDeclarationInfo::findEnumSpecifier(const char* pObjName) const
{
  const AdtParser*  pObj = 0;

  findObject(EnumSpecifierMap, pObjName, pObj);

  return ((AdtCppEnumSpecifier*)pObj);
}

//  ----------------------------------------------------------------------------

inline AdtCppClassSpecifier* AdtCppDeclarationInfo::findClassSpecifier(const char* pObjName) const
{
  const AdtParser*  pObj = 0;

  findObject(ClassSpecifierMap, pObjName, pObj);

  return ((AdtCppClassSpecifier*)pObj);
}

//  ----------------------------------------------------------------------------

inline AdtCppEnumSpecifier* AdtCppDeclarationInfo::findEnumSpecifierByConst(const char* pConstName) const
{
  const AdtParser*  pObj = 0;

  findObject(EnumSpecifierByConstantMap, pConstName, pObj);

  return ((AdtCppEnumSpecifier*)pObj);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarationInfo::findFunctionDefinition(const char* pObjName, const AdtParser*& pObj) const
{
  return (findObject(FunctionDefinitionMap, pObjName, pObj));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarationInfo::findVarDefinition(const char* pObjName, const AdtParser*& pObj) const
{
  return (findObject(VarDefinitionMap, pObjName, pObj));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarationInfo::findEnumSpecifier(const char* pObjName, const AdtParser*& pObj) const
{
  return (findObject(EnumSpecifierMap, pObjName, pObj));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarationInfo::findClassSpecifier(const char* pObjName, const AdtParser*& pObj) const
{
  return (findObject(ClassSpecifierMap, pObjName, pObj));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarationInfo::findEnumSpecifierByConst(const char* pConstName, const AdtParser*& pObj) const
{
  return (findObject(EnumSpecifierByConstantMap, pConstName, pObj));
}


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationSeq class
//  ----------------------------------------------------------------------------
class AdtCppDeclarationSeq : public AdtCppDeclarationInfo
{
protected:

public:
  AdtCppDeclarationSeq(AdtParser* pDeclarationObj);
  AdtCppDeclarationSeq(const AdtCppDeclarationSeq& rCopy);
  virtual ~AdtCppDeclarationSeq();

  void                          initialise();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppSimpleDeclarationList class
//  ----------------------------------------------------------------------------
class AdtCppSimpleDeclarationList : public AdtCppBase
{
public:
  AdtCppSimpleDeclarationList(AdtParser* pSimpleDeclarationObj);
  AdtCppSimpleDeclarationList(const AdtCppSimpleDeclarationList& rCopy);
  virtual ~AdtCppSimpleDeclarationList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppSimpleDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppPostfixExpression class
//  ----------------------------------------------------------------------------
class AdtCppPostfixExpression : public AdtCppBase
{
private:
  AdtCppExpression*             Expression;
  AdtCppPostfixExpression*      PostfixExpression;
  AdtCppDirectedExpression*     DirectedExpression;
  bool                          Increment;

public:
  AdtCppPostfixExpression(AdtParser* pExpressionObj,
                          AdtParser* pPostfixExpressionObj,
                          AdtParser* pDirectedExpressionObj,
                          bool bIncrement,
                          const char* pLiteral);

  AdtCppPostfixExpression(const AdtCppPostfixExpression& rCopy);
  virtual ~AdtCppPostfixExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppExpressionList class
//  ----------------------------------------------------------------------------
class AdtCppExpressionList : public AdtCppBase
{
public:
  AdtCppExpressionList(AdtParser* pAssignmentExpressionObj);
  AdtCppExpressionList(const AdtCppExpressionList& rCopy);
  virtual ~AdtCppExpressionList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppAssignmentExpression);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDirectedExpression class
//  ----------------------------------------------------------------------------
class AdtCppDirectedExpression : public AdtCppBase
{
public:
  AdtCppDirectedExpression(AdtParser* pDeclaratorExpressionObj);
  AdtCppDirectedExpression(const AdtCppExpressionList& rCopy);
  virtual ~AdtCppDirectedExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppDeclaratorExpression);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorExpression class
//  ----------------------------------------------------------------------------
class AdtCppDeclaratorExpression : public AdtCppBase
{
private:
  AdtCppExpressionList*           ExpressionList;
  AdtCppDeclaratorExpressionDims* DeclaratorExpressionDims;
  bool                            Qualified;
  bool                            HasBrackets;

protected:
  void                          writeFortranInner(AdtFile& rOutFile,
                                                  int nMode,
                                                  const string& sQualifiedName,
                                                  bool bAddCall) const;

public:
  AdtCppDeclaratorExpression(const char* pIdentifier,
                             AdtParser* pExpressionListObj,
                             AdtParser* pDeclaratorExpressionDimsObj,
                             bool bQualified,
                             bool bHasBrackets);

  AdtCppDeclaratorExpression(const AdtCppDeclaratorExpression& rCopy);
  virtual ~AdtCppDeclaratorExpression();

  virtual bool                  isSimple() const;

  AdtCppBase*                   substituitionRoot(const char* pTerminalClass) const;
  bool                          isSimpleDeclaration(const char** ppIdentifier = 0) const;
  bool                          isCallDeclaration(size_t* pnArgs = 0) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorExpressionDims class
//  ----------------------------------------------------------------------------
class AdtCppDeclaratorExpressionDims : public AdtCppBase
{
public:
  AdtCppDeclaratorExpressionDims(AdtParser* pExpressionObj);
  AdtCppDeclaratorExpressionDims(const AdtCppDeclaratorExpressionDims& rCopy);
  virtual ~AdtCppDeclaratorExpressionDims();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppExpression);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppUnaryExpression class
//  ----------------------------------------------------------------------------
class AdtCppUnaryExpression : public AdtCppBase
{
private:
  AdtCppPostfixExpression*      PostfixExpression;
  AdtCppUnaryExpression*        UnaryExpression;
  AdtCppUnaryOperator*          UnaryOperator;
  AdtCppExpression*             Expression;
  bool                          Increment;

public:
  AdtCppUnaryExpression(AdtParser* pPostfixExpressionObj,
                        AdtParser* pUnaryExpressionObj,
                        AdtParser* pUnaryOperatorObj,
                        AdtParser* pExpressionObj,
                        bool bIncrement);

  AdtCppUnaryExpression(const AdtCppUnaryExpression& rCopy);
  virtual ~AdtCppUnaryExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppUnaryOp
{
  UnaryOp_PLUS  = 0,
  UnaryOp_MINUS = 1,
  UnaryOp_LNOT  = 2,
  UnaryOp_NOT   = 3
};

//  ----------------------------------------------------------------------------
//  AdtCppUnaryOperator class
//  ----------------------------------------------------------------------------
class AdtCppUnaryOperator : public AdtCppBase
{
private:
  AdtCppUnaryOp                 Op;

public:
  AdtCppUnaryOperator(AdtCppUnaryOp nOp);
  AdtCppUnaryOperator(const AdtCppUnaryOperator& rCopy);
  virtual ~AdtCppUnaryOperator();

  AdtCppUnaryOp                 op() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtCppUnaryOp AdtCppUnaryOperator::op() const
{
  return (Op);
}


//  ----------------------------------------------------------------------------

enum AdtCppMultiplicativeOp
{
  MultiplicativeOp_PROD  = 0,
  MultiplicativeOp_DIV   = 1,
  MultiplicativeOp_MOD   = 2
};

//  ----------------------------------------------------------------------------
//  AdtCppMultiplicativeExpression class
//  ----------------------------------------------------------------------------
class AdtCppMultiplicativeExpression : public AdtCppBase
{
private:
  AdtCppUnaryExpression*          UnaryExpression;
  AdtCppMultiplicativeExpression* MultiplicativeExpression;
  AdtCppMultiplicativeOp          Op;

public:
  AdtCppMultiplicativeExpression(AdtCppMultiplicativeOp nOp,
                                 AdtParser* pUnaryExpressionObj,
                                 AdtParser* pMultiplicativeExpressionObj);

  AdtCppMultiplicativeExpression(const AdtCppMultiplicativeExpression& rCopy);
  virtual ~AdtCppMultiplicativeExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppAdditiveOp
{
  AdditiveOp_PLUS   = 0,
  AdditiveOp_MINUS  = 1
};

//  ----------------------------------------------------------------------------
//  AdtCppAdditiveExpression class
//  ----------------------------------------------------------------------------
class AdtCppAdditiveExpression : public AdtCppBase
{
private:
  AdtCppMultiplicativeExpression* MultiplicativeExpression;
  AdtCppAdditiveExpression*       AdditiveExpression;
  AdtCppAdditiveOp                Op;

public:
  AdtCppAdditiveExpression(AdtCppAdditiveOp nOp,
                           AdtParser* pMultiplicativeExpressionObj,
                           AdtParser* pAdditiveExpressionObj);

  AdtCppAdditiveExpression(const AdtCppAdditiveExpression& rCopy);
  virtual ~AdtCppAdditiveExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppShiftOp
{
  AdtCppShiftOp_SHL = 0,
  AdtCppShiftOp_SHR = 1
};

//  ----------------------------------------------------------------------------
//  AdtCppShiftExpression class
//  ----------------------------------------------------------------------------
class AdtCppShiftExpression : public AdtCppBase
{
private:
  AdtCppAdditiveExpression*       AdditiveExpression;
  AdtCppShiftExpression*          ShiftExpression;
  AdtCppShiftOp                   Op;

public:
  AdtCppShiftExpression(AdtCppShiftOp nOp,
                        AdtParser* pAdditiveExpressionObj,
                        AdtParser* pShiftExpressionObj);

  AdtCppShiftExpression(const AdtCppShiftExpression& rCopy);
  virtual ~AdtCppShiftExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppRelationalOp
{
  AdtCppRelationalOp_LT     = 0,
  AdtCppRelationalOp_GT     = 1,
  AdtCppRelationalOp_LT_EQ  = 2,
  AdtCppRelationalOp_GT_EQ  = 3
};

//  ----------------------------------------------------------------------------
//  AdtCppRelationalExpression class
//  ----------------------------------------------------------------------------
class AdtCppRelationalExpression : public AdtCppBase
{
private:
  AdtCppShiftExpression*          ShiftExpression;
  AdtCppRelationalExpression*     RelationalExpression;
  AdtCppRelationalOp              Op;

public:
  AdtCppRelationalExpression(AdtCppRelationalOp nOp,
                             AdtParser* pShiftExpressionObj,
                             AdtParser* pRelationalExpressionObj);

  AdtCppRelationalExpression(const AdtCppRelationalExpression& rCopy);
  virtual ~AdtCppRelationalExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppEqualityOp
{
  AdtCppEqualityOp_EQEQ = 0,
  AdtCppEqualityOp_NEQ  = 1
};

//  ----------------------------------------------------------------------------
//  AdtCppEqualityExpression class
//  ----------------------------------------------------------------------------
class AdtCppEqualityExpression : public AdtCppBase
{
private:
  AdtCppRelationalExpression*     RelationalExpression;
  AdtCppEqualityExpression*       EqualityExpression;
  AdtCppEqualityOp                Op;

public:
  AdtCppEqualityExpression(AdtCppEqualityOp nOp,
                           AdtParser* pRelationalExpressionObj,
                           AdtParser* pEqualityExpressionObj);

  AdtCppEqualityExpression(const AdtCppEqualityExpression& rCopy);
  virtual ~AdtCppEqualityExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppAndExpression class
//  ----------------------------------------------------------------------------
class AdtCppAndExpression : public AdtCppBase
{
private:
  AdtCppEqualityExpression*     EqualityExpression;
  AdtCppAndExpression*          AndExpression;

public:
  AdtCppAndExpression(AdtParser* pEqualityExpressionObj,
                      AdtParser* pAndExpressionObj);

  AdtCppAndExpression(const AdtCppAndExpression& rCopy);
  virtual ~AdtCppAndExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppExclusiveOrExpression class
//  ----------------------------------------------------------------------------
class AdtCppExclusiveOrExpression : public AdtCppBase
{
private:
  AdtCppAndExpression*          AndExpression;
  AdtCppExclusiveOrExpression*  ExclusiveOrExpression;

public:
  AdtCppExclusiveOrExpression(AdtParser* pAndExpressionObj,
                              AdtParser* pExclusiveOrExpressionObj);

  AdtCppExclusiveOrExpression(const AdtCppExclusiveOrExpression& rCopy);
  virtual ~AdtCppExclusiveOrExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInclusiveOrExpression class
//  ----------------------------------------------------------------------------
class AdtCppInclusiveOrExpression : public AdtCppBase
{
private:
  AdtCppExclusiveOrExpression*  ExclusiveOrExpression;
  AdtCppInclusiveOrExpression*  InclusiveOrExpression;

public:
  AdtCppInclusiveOrExpression(AdtParser* pExclusiveOrExpressionObj,
                              AdtParser* pInclusiveOrExpressionObj);

  AdtCppInclusiveOrExpression(const AdtCppInclusiveOrExpression& rCopy);
  virtual ~AdtCppInclusiveOrExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppLogicalAndExpression class
//  ----------------------------------------------------------------------------
class AdtCppLogicalAndExpression : public AdtCppBase
{
private:
  AdtCppInclusiveOrExpression*  InclusiveOrExpression;
  AdtCppLogicalAndExpression*   LogicalAndExpression;

public:
  AdtCppLogicalAndExpression(AdtParser* pInclusiveOrExpressionObj,
                             AdtParser* pLogicalAndExpressionObj);

  AdtCppLogicalAndExpression(const AdtCppLogicalAndExpression& rCopy);
  virtual ~AdtCppLogicalAndExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppLogicalOrExpression class
//  ----------------------------------------------------------------------------
class AdtCppLogicalOrExpression : public AdtCppBase
{
private:
  AdtCppLogicalAndExpression*   LogicalAndExpression;
  AdtCppLogicalOrExpression*    LogicalOrExpression;

public:
  AdtCppLogicalOrExpression(AdtParser* pLogicalAndExpressionObj,
                            AdtParser* pLogicalOrExpressionObj);

  AdtCppLogicalOrExpression(const AdtCppLogicalOrExpression& rCopy);
  virtual ~AdtCppLogicalOrExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppConditionalExpression class
//  ----------------------------------------------------------------------------
class AdtCppConditionalExpression : public AdtCppBase
{
private:
  AdtCppLogicalOrExpression*    LogicalOrExpression;
  AdtCppExpression*             Expression;
  AdtCppAssignmentExpression*   AssignmentExpression;

public:
  AdtCppConditionalExpression(AdtParser* pLogicalOrExpressionObj,
                              AdtParser* pExpressionObj,
                              AdtParser* pAssignmentExpressionObj);

  AdtCppConditionalExpression(const AdtCppConditionalExpression& rCopy);
  virtual ~AdtCppConditionalExpression();

  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppAssignmentExpression class
//  ----------------------------------------------------------------------------
class AdtCppAssignmentExpression : public AdtCppBase
{
private:
  AdtCppConditionalExpression*  ConditionalExpression;
  AdtCppLogicalOrExpression*    LogicalOrExpression;
  AdtCppAssignmentOperator*     AssignmentOperator;
  AdtCppAssignmentExpression*   AssignmentExpression;

public:
  AdtCppAssignmentExpression(AdtParser* pConditionalExpressionObj,
                             AdtParser* pLogicalOrExpressionObj,
                             AdtParser* pAssignmentOperatorObj,
                             AdtParser* pAssignmentExpressionObj);

  AdtCppAssignmentExpression(const AdtCppAssignmentExpression& rCopy);
  virtual ~AdtCppAssignmentExpression();

  bool                          isAssignment() const;
  virtual bool                  isSimple() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppAssignmentExpression::isAssignment() const
{
  bool bIsAssignment = ((ConditionalExpression  == 0) &&
                        (LogicalOrExpression    != 0) &&
                        (AssignmentExpression   != 0));

  return (bIsAssignment);
}

//  ----------------------------------------------------------------------------

enum AdtCppAssignmentOp
{
  AdtCppAssignmentOp_EQ       = 0,
  AdtCppAssignmentOp_PROD_EQ  = 1,
  AdtCppAssignmentOp_DIV_EQ   = 2,
  AdtCppAssignmentOp_MOD_EQ   = 3,
  AdtCppAssignmentOp_P_EQ     = 4,
  AdtCppAssignmentOp_M_EQ     = 5,
  AdtCppAssignmentOp_SHL_EQ   = 6,
  AdtCppAssignmentOp_SHR_EQ   = 7,
  AdtCppAssignmentOp_AND_EQ   = 8,
  AdtCppAssignmentOp_XOR_EQ   = 9,
  AdtCppAssignmentOp_OR_EQ    = 10
};

//  ----------------------------------------------------------------------------
//  AdtCppAssignmentOperator class
//  ----------------------------------------------------------------------------
class AdtCppAssignmentOperator : public AdtCppBase
{
private:
  AdtCppAssignmentOp            Op;

public:
  AdtCppAssignmentOperator(AdtCppAssignmentOp nOp);
  AdtCppAssignmentOperator(const AdtCppAssignmentOperator& rCopy);
  virtual ~AdtCppAssignmentOperator();

  const AdtCppAssignmentOp      op() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline const AdtCppAssignmentOp AdtCppAssignmentOperator::op() const
{
  return (Op);
}


//  ----------------------------------------------------------------------------
//  AdtCppExpression class
//  ----------------------------------------------------------------------------
class AdtCppExpression : public AdtCppBase
{
private:
  AdtCppAssignmentExpression*   AssignmentExpression;
  AdtCppExpression*             Expression;

public:
  AdtCppExpression(AdtParser* pAssignmentExpressionObj,
                   AdtParser* pExpressionObj);

  AdtCppExpression(const AdtCppExpression& rCopy);
  virtual ~AdtCppExpression();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppConstantExpression class
//  ----------------------------------------------------------------------------
class AdtCppConstantExpression : public AdtCppBase
{
private:
  AdtCppConditionalExpression*  ConditionalExpression;

public:
  AdtCppConstantExpression(AdtParser* pConditionalExpressionObj);
  AdtCppConstantExpression(const AdtCppConstantExpression& rCopy);
  virtual ~AdtCppConstantExpression();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppStatement class
//  ----------------------------------------------------------------------------
class AdtCppStatement : public AdtCppBase
{
private:
  AdtCppLabeledStatement*       LabeledStatement;
  AdtCppExpressionStatement*    ExpressionStatement;
  AdtCppCompoundStatement*      CompoundStatement;
  AdtCppSelectionStatement*     SelectionStatement;
  AdtCppIterationStatement*     IterationStatement;
  AdtCppJumpStatement*          JumpStatement;
  AdtCppDeclarationStatement*   DeclarationStatement;

public:
  AdtCppStatement(AdtParser* pLabeledStatementObj,
                  AdtParser* pExpressionStatementObj,
                  AdtParser* pCompoundStatementObj,
                  AdtParser* pSelectionStatementObj,
                  AdtParser* pIterationStatementObj,
                  AdtParser* pJumpStatementObj,
                  AdtParser* pDeclarationStatementObj);

  AdtCppStatement(const AdtCppStatement& rCopy);
  virtual ~AdtCppStatement();

  virtual void                  linespace(AdtFile& pOutFile,
                                          bool& bLineSpace,
                                          const AdtCppBase* pLastObj,
                                          bool bPre) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  bool                          isEmpty() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppStatement::isEmpty() const
{
  bool bIsEmpty = ((LabeledStatement     == 0) &&
                   (ExpressionStatement  == 0) &&
                   (CompoundStatement    == 0) &&
                   (SelectionStatement   == 0) &&
                   (IterationStatement   == 0) &&
                   (JumpStatement        == 0) &&
                   (DeclarationStatement == 0));

  return (bIsEmpty);
}


//  ----------------------------------------------------------------------------
//  AdtCppLabeledStatement class
//  ----------------------------------------------------------------------------
class AdtCppLabeledStatement : public AdtCppBase
{
private:
  AdtCppConstantExpression*     ConstantExpression;
  AdtCppStatement*              Statement;
  bool                          IsDefault;

public:
  AdtCppLabeledStatement(AdtParser* pConstantExpressionObj,
                         AdtParser* pStatementObj,
                         const char* pIdentifier,
                         bool bIsDefault);

  AdtCppLabeledStatement(const AdtCppLabeledStatement& rCopy);
  virtual ~AdtCppLabeledStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppExpressionStatement class
//  ----------------------------------------------------------------------------
class AdtCppExpressionStatement : public AdtCppBase
{
private:
  AdtCppExpression*             Expression;

public:
  AdtCppExpressionStatement(AdtParser* pExpressionObj);

  AdtCppExpressionStatement(const AdtCppExpressionStatement& rCopy);
  virtual ~AdtCppExpressionStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppCompoundStatement class
//  ----------------------------------------------------------------------------
class AdtCppCompoundStatement : public AdtCppBase
{
private:
  AdtCppStatementSeq*           StatementSeq;

public:
  AdtCppCompoundStatement(AdtParser* pStatementSeqObj);

  AdtCppCompoundStatement(const AdtCppCompoundStatement& rCopy);
  virtual ~AdtCppCompoundStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppStatementSeq class
//  ----------------------------------------------------------------------------
class AdtCppStatementSeq : public AdtCppBase
{
public:
  AdtCppStatementSeq(AdtParser* pStatementObj);
  AdtCppStatementSeq(const AdtCppStatementSeq& rCopy);
  virtual ~AdtCppStatementSeq();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppStatement);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppSelectionStatement class
//  ----------------------------------------------------------------------------
class AdtCppSelectionStatement : public AdtCppBase
{
private:
  AdtCppExpression*             Expression;
  AdtCppStatement*              Statement;
  AdtCppStatement*              Statement2;
  bool                          IsIf;

public:
  AdtCppSelectionStatement(AdtParser* pExpressionObj,
                           AdtParser* pStatementObj,
                           AdtParser* pStatement2Obj,
                           bool bIsIf);

  AdtCppSelectionStatement(const AdtCppSelectionStatement& rCopy);
  virtual ~AdtCppSelectionStatement();

  virtual void                  linespace(AdtFile& pOutFile,
                                          bool& bLineSpace,
                                          const AdtCppBase* pLastObj,
                                          bool bPre) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppIterationStatement class
//  ----------------------------------------------------------------------------
class AdtCppIterationStatement : public AdtCppBase
{
private:
  AdtCppForInitStatement*       ForInitStatement;
  AdtCppExpression*             Expression;
  AdtCppExpression*             Expression2;
  AdtCppStatement*              Statement;
  bool                          IsDo;

public:
  AdtCppIterationStatement(AdtParser* pForInitStatementObj,
                           AdtParser* pExpressionObj,
                           AdtParser* pExpression2Obj,
                           AdtParser* pStatementObj,
                           bool bIsDo);

  AdtCppIterationStatement(const AdtCppIterationStatement& rCopy);
  virtual ~AdtCppIterationStatement();

  virtual void                  linespace(AdtFile& pOutFile,
                                          bool& bLineSpace,
                                          const AdtCppBase* pLastObj,
                                          bool bPre) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppForInitStatement class
//  ----------------------------------------------------------------------------
class AdtCppForInitStatement : public AdtCppBase
{
private:
  AdtCppExpressionStatement*    ExpressionStatement;
  AdtCppSimpleDeclaration*      SimpleDeclaration;

public:
  AdtCppForInitStatement(AdtParser* pExpressionStatementObj,
                         AdtParser* pSimpleDeclarationObj);

  AdtCppForInitStatement(const AdtCppForInitStatement& rCopy);
  virtual ~AdtCppForInitStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppJumpType
{
  AdtCppJumpType_BREAK    = 0,
  AdtCppJumpType_CONTINUE = 1,
  AdtCppJumpType_RETURN   = 2,
  AdtCppJumpType_GOTO     = 3
};

//  ----------------------------------------------------------------------------
//  AdtCppJumpStatement class
//  ----------------------------------------------------------------------------
class AdtCppJumpStatement : public AdtCppBase
{
private:
  AdtCppExpression*             Expression;
  AdtCppJumpType                Type;

public:
  AdtCppJumpStatement(AdtParser* pExpressionObj,
                      const char* pIndentifier,
                      AdtCppJumpType nType);

  AdtCppJumpStatement(const AdtCppJumpStatement& rCopy);
  virtual ~AdtCppJumpStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclarationStatement class
//  ----------------------------------------------------------------------------
class AdtCppDeclarationStatement : public AdtCppBase
{
private:
  AdtCppBlockDeclaration*       BlockDeclaration;

public:
  AdtCppDeclarationStatement(AdtParser* pBlockDeclarationObj);
  AdtCppDeclarationStatement(const AdtCppDeclarationStatement& rCopy);
  virtual ~AdtCppDeclarationStatement();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppDeclaration : public AdtCppBase
{
private:
  AdtCppBlockDeclaration*       BlockDeclaration;
  AdtCppFunctionDefinition*     FunctionDefinition;
  AdtCppLinkageSpecification*   LinkageSpecification;
  AdtCppNamespaceDefinition*    NamespaceDefinition;
  static bool                   Print;
  static bool                   WriteFlatFile;
  static string                 LastFileName;

public:
  AdtCppDeclaration(AdtParser* pBlockDeclarationObj,
                    AdtParser* pFunctionDefinitionObj,
                    AdtParser* pLinkageSpecificationObj,
                    AdtParser* pNamespaceDefinitionObj);

  AdtCppDeclaration(const AdtCppDeclaration& rCopy);
  virtual ~AdtCppDeclaration();

  static void                   writeFlatFile(bool bFlat);

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline void AdtCppDeclaration::writeFlatFile(bool bFlat)
{
  WriteFlatFile = bFlat;
}


//  ----------------------------------------------------------------------------
//  AdtCppBlockDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppBlockDeclaration : public AdtCppBase
{
private:
  AdtCppSimpleDeclaration*        SimpleDeclaration;
  AdtCppAsmDefinition*            AsmDefinition;
  AdtCppNamespaceAliasDefinition* NamespaceAliasDefinition;
  AdtCppUsingDeclaration*         UsingDeclaration;
  AdtCppUsingDirective*           UsingDirective;

public:
  AdtCppBlockDeclaration(AdtParser* pSimpleDeclarationObj,
                         AdtParser* pAsmDefinitionObj,
                         AdtParser* pNamespaceAliasDefinitionObj,
                         AdtParser* pUsingDeclarationObj,
                         AdtParser* pUsingDirectiveObj);

  AdtCppBlockDeclaration(const AdtCppBlockDeclaration& rCopy);
  virtual ~AdtCppBlockDeclaration();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppDeclModifierType
{
  AdtCppDeclModifierType_AUTO     = 0,
  AdtCppDeclModifierType_REGISTER = 1,
  AdtCppDeclModifierType_STATIC   = 2,
  AdtCppDeclModifierType_EXTERN   = 3,
  AdtCppDeclModifierType_MUTABLE  = 4,
  AdtCppDeclModifierType_INLINE   = 5,
  AdtCppDeclModifierType_VIRTUAL  = 6,
  AdtCppDeclModifierType_EXPLICIT = 7,
  AdtCppDeclModifierType_CONST    = 8,
  AdtCppDeclModifierType_VOLATILE = 9,
  AdtCppDeclModifierType_FRIEND   = 10
};


//  ----------------------------------------------------------------------------
//  AdtCppDeclModifier class
//  ----------------------------------------------------------------------------
class AdtCppDeclModifier : public AdtCppBase
{
private:
  AdtCppDeclModifierType        Type;

public:
  AdtCppDeclModifier(AdtCppDeclModifierType nType);
  AdtCppDeclModifier(const AdtCppDeclModifier& rCopy);
  virtual ~AdtCppDeclModifier();

  bool                          isConst() const;
  AdtCppDeclModifierType        modifier() const;
  AdtAutoDir                    autoDir(AdtAutoDir nDir) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtCppDeclModifierType AdtCppDeclModifier::modifier() const
{
  return (Type);
}

//  ----------------------------------------------------------------------------

inline AdtAutoDir AdtCppDeclModifier::autoDir(AdtAutoDir nDir) const
{
  if (isConst())
  {
    switch(nDir)
    {
      case AdtAutoDir_INOUT:
      {
        nDir = AdtAutoDir_IN;
        break;
      }

      case AdtAutoDir_IN:
      case AdtAutoDir_OUT:
      case AdtAutoDir_UNDEFINED:
      default:
      {
        break;
      }
    }
  }

  return (nDir);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclModifier::isConst() const
{
  bool bIsConst = (Type == AdtCppDeclModifierType_CONST);

  return bIsConst;
}


//  ----------------------------------------------------------------------------
//  AdtCppDeclModifierList class
//  ----------------------------------------------------------------------------
class AdtCppDeclModifierList : public AdtCppBase
{
public:
  AdtCppDeclModifierList(AdtParser* pDeclModifierObj);
  AdtCppDeclModifierList(const AdtCppDeclModifierList& rCopy);
  virtual ~AdtCppDeclModifierList();

  AdtAutoDir                    autoDir(AdtAutoDir nDir) const;
  bool                          hasModifier(AdtCppDeclModifierType nType) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppDeclModifier);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppSimpleDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppSimpleDeclaration : public AdtCppBase
{
private:
  AdtCppClassSpecifier*         ClassSpecifier;
  AdtCppEnumSpecifier*          EnumSpecifier;
  AdtCppSimpleTypeSpecifier*    SimpleTypeSpecifier;
  AdtCppInitDeclaratorList*     InitDeclaratorList;
  AdtCppDeclModifierList*       DeclModifierList;
  bool                          HasTypeDef;

public:
  AdtCppSimpleDeclaration(AdtParser* pClassSpecifierObj,
                          AdtParser* pEnumSpecifierObj,
                          AdtParser* pSimpleTypeSpecifierObj,
                          AdtParser* pInitDeclaratorListObj,
                          AdtParser* pDeclModifierListObj,
                          bool bHasTypeDef);

  AdtCppSimpleDeclaration(const AdtCppSimpleDeclaration& rCopy);
  virtual ~AdtCppSimpleDeclaration();

  bool                          isTypeDef(const char** ppAliasName = 0) const;
  bool                          isVirtual() const;

  void                          writeFortranDeclaration(AdtFile& rOutFile, const AdtCppDeclarator* pDeclarator) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppSimpleDeclaration::isVirtual() const
{
  bool bIsVirtual = (DeclModifierList != 0) ? DeclModifierList->hasModifier(AdtCppDeclModifierType_VIRTUAL) : false;
}


//  ----------------------------------------------------------------------------
//  AdtCppClassSpecifier class
//  ----------------------------------------------------------------------------
class AdtCppClassSpecifier : public AdtCppCheckDeclaration
{
private:
  AdtCppClassKey*               ClassKey;
  AdtCppBaseSpecifierList*      BaseSpecifierList;
  AdtCppMemberSpecification*    MemberSpecification;
  bool                          WithBrackets;

protected:
  bool                          importParentClasses(AdtCppClassSpecifier* pDestClass,
                                                    AdtCppTranslationUnit* pRoot,
                                                    AdtIntByStringMap& rImportMap,
                                                    const AdtParserPtrList& rRootList,
                                                    string& rUsesList);

  void                          expandOutInlineImplementations(AdtCppTranslationUnit* pRoot,
                                                               AdtStringByStringMap& rPublicMethodsMap);

public:
  AdtCppClassSpecifier(AdtParser* pClassKeyObj,
                       AdtParser* pBaseSpecifierListObj,
                       AdtParser* pMemberSpecificationObj,
                       bool bWithBrackets);

  AdtCppClassSpecifier(const AdtCppClassSpecifier& rCopy);
  virtual ~AdtCppClassSpecifier();

  virtual bool                  isForwardDeclaration(bool bClassScope) const;
  bool                          isEmpty() const;

  void                          enumerateVariables(AdtParserPtrByStringMap& rMap) const;

  bool                          flattenClass(AdtCppTranslationUnit* pRoot,
                                             const AdtParserPtrList& rRootList,
                                             string& rUsesList,
                                             AdtStringByStringMap& rPublicMethodsMap);

  void                          findDimensionVars(const AdtCppTranslationUnit* pRoot,
                                                  const AdtParserPtrByStringMap& rVarsMap,
                                                  AdtParserPtrByStringMap& rDimsMap) const;

  bool                          findField(const AdtCppTranslationUnit* pRoot,
                                          const char* pName,
                                          const AdtParser*& pObj) const;

  bool                          findMethod(const AdtCppTranslationUnit* pRoot,
                                           const char* pName,
                                           const AdtParser*& pObj) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  const char*                   parentClassName() const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppEnumSpecifierName class
//  ----------------------------------------------------------------------------
class AdtCppEnumSpecifierName : public AdtCppBase
{
private:
  bool                          Qualified;

public:
  AdtCppEnumSpecifierName(const char* pIdentifier, bool bQualified);
  AdtCppEnumSpecifierName(const AdtCppEnumSpecifierName& rCopy);
  virtual ~AdtCppEnumSpecifierName();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppEnumSpecifier class
//  ----------------------------------------------------------------------------
class AdtCppEnumSpecifier : public AdtCppCheckDeclaration
{
private:
  AdtCppEnumSpecifierName*      EnumSpecifierName;
  AdtCppEnumeratorList*         EnumeratorList;
  bool                          WithBrackets;

public:
  AdtCppEnumSpecifier(AdtParser* pEnumeratorListObj,
                      AdtParser* pEnumSpecifierNameObj,
                      bool bWithBrackets);

  AdtCppEnumSpecifier(const AdtCppEnumSpecifier& rCopy);
  virtual ~AdtCppEnumSpecifier();

  virtual bool                  isForwardDeclaration(bool bClassScope) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppSimpleType
{
  AdtCppSimpleType_OBJ_IDENTIFIER           = 0,
  AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER = 1,
  AdtCppSimpleType_WCHAR_T                  = 2,
  AdtCppSimpleType_CHAR                     = 3,
  AdtCppSimpleType_BOOL                     = 4,
  AdtCppSimpleType_INT                      = 5,
  AdtCppSimpleType_SHORT                    = 6,
  AdtCppSimpleType_SHORT_INT                = 7,
  AdtCppSimpleType_LONG                     = 8,
  AdtCppSimpleType_LONG_INT                 = 9,
  AdtCppSimpleType_SIGNED                   = 10,
  AdtCppSimpleType_SIGNED_INT               = 11,
  AdtCppSimpleType_SIGNED_SHORT             = 12,
  AdtCppSimpleType_SIGNED_SHORT_INT         = 13,
  AdtCppSimpleType_SIGNED_LONG              = 14,
  AdtCppSimpleType_SIGNED_LONG_INT          = 15,
  AdtCppSimpleType_SIGNED_CHAR              = 16,
  AdtCppSimpleType_UNSIGNED                 = 17,
  AdtCppSimpleType_UNSIGNED_INT             = 18,
  AdtCppSimpleType_UNSIGNED_SHORT           = 19,
  AdtCppSimpleType_UNSIGNED_SHORT_INT       = 20,
  AdtCppSimpleType_UNSIGNED_LONG            = 21,
  AdtCppSimpleType_UNSIGNED_LONG_INT        = 22,
  AdtCppSimpleType_UNSIGNED_CHAR            = 23,
  AdtCppSimpleType_FLOAT                    = 24,
  AdtCppSimpleType_DOUBLE                   = 25,
  AdtCppSimpleType_LONG_DOUBLE              = 26,
  AdtCppSimpleType_LONG_LONG                = 27,
  AdtCppSimpleType_SIGNED_LONG_LONG         = 28,
  AdtCppSimpleType_UNSIGNED_LONG_LONG       = 29,
  AdtCppSimpleType_VOID                     = 30,
  AdtCppSimpleType_LONGBOOL                 = 31
};

//  ----------------------------------------------------------------------------
//  AdtCppSimpleTypeSpecifier class
//  ----------------------------------------------------------------------------
class AdtCppSimpleTypeSpecifier : public AdtCppBase
{
private:
  AdtCppSimpleType              Type;
  bool                          ByRef;

public:
  AdtCppSimpleTypeSpecifier(const char* pIdentifier,
                            AdtCppSimpleType nType,
                            bool bByRef);

  AdtCppSimpleTypeSpecifier(const AdtCppSimpleTypeSpecifier& rCopy);
  virtual ~AdtCppSimpleTypeSpecifier();

  bool                          isVoid() const;
  bool                          isByRef() const;
  bool                          isInOut() const;
  AdtCppSimpleType              cppType() const;
  AdtAutoType                   autoType(int& nDimensions) const;
  AdtAutoDir                    autoDir() const;

  void                          addToBlackBox(AdtBlackBoxDefinition& rBlackBox,
                                              const char* pName,
                                              bool bReturnType,
                                              const char* pFile,
                                              int nLine) const;

  void                          writeArrayBounds(AdtFile& rOutFile,
                                                 const AdtCppEmbeddedComment* pEmbeddedComment) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppSimpleTypeSpecifier::isVoid() const
{
  return ((Type == AdtCppSimpleType_VOID) && !ByRef);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppSimpleTypeSpecifier::isByRef() const
{
  return (ByRef);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppSimpleTypeSpecifier::isInOut() const
{
  bool bIsInOut = (ByRef                                               ||
                   (Type == AdtCppSimpleType_OBJ_IDENTIFIER          ) ||
                   (Type == AdtCppSimpleType_QUALIFIED_OBJ_IDENTIFIER));

  return (bIsInOut);
}

//  ----------------------------------------------------------------------------

inline AdtCppSimpleType AdtCppSimpleTypeSpecifier::cppType() const
{
  return (Type);
}


//  ----------------------------------------------------------------------------
//  AdtCppEnumeratorList class
//  ----------------------------------------------------------------------------
class AdtCppEnumeratorList : public AdtCppBase
{
public:
  AdtCppEnumeratorList(AdtParser* pEnumeratorDefinitionObj);
  AdtCppEnumeratorList(const AdtCppEnumeratorList& rCopy);
  virtual ~AdtCppEnumeratorList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppEnumeratorDefinition);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppEnumeratorDefinition class
//  ----------------------------------------------------------------------------
class AdtCppEnumeratorDefinition : public AdtCppBase
{
private:
  AdtCppConstantExpression*     ConstantExpression;

public:
  AdtCppEnumeratorDefinition(AdtParser* pConstantExpressionObj,
                             const char* pIdentifier);

  AdtCppEnumeratorDefinition(const AdtCppEnumeratorDefinition& rCopy);
  virtual ~AdtCppEnumeratorDefinition();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppNamespaceDefinition class
//  ----------------------------------------------------------------------------
class AdtCppNamespaceDefinition : public AdtCppBase
{
private:
  AdtCppDeclarationSeq*         DeclarationSeq;

public:
  AdtCppNamespaceDefinition(AdtParser* pDeclarationSeqObj,
                             const char* pIdentifier);

  AdtCppNamespaceDefinition(const AdtCppNamespaceDefinition& rCopy);
  virtual ~AdtCppNamespaceDefinition();

  AdtCppDeclarationSeq*         declarationSeq() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppNamespaceAliasDefinition class
//  ----------------------------------------------------------------------------
class AdtCppNamespaceAliasDefinition : public AdtCppBase
{
private:
  string                        QualifiedIdentifier;

public:
  AdtCppNamespaceAliasDefinition(const char* pIdentifier,
                                 const char* pQualifiedIdentifier);

  AdtCppNamespaceAliasDefinition(const AdtCppNamespaceAliasDefinition& rCopy);
  virtual ~AdtCppNamespaceAliasDefinition();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppUsingDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppUsingDeclaration : public AdtCppBase
{
private:
  bool                          WithTypename;

public:
  AdtCppUsingDeclaration(const char* pQualifiedIdentifier,
                         bool bWithTypename);

  AdtCppUsingDeclaration(const AdtCppUsingDeclaration& rCopy);
  virtual ~AdtCppUsingDeclaration();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppUsingDirective class
//  ----------------------------------------------------------------------------
class AdtCppUsingDirective : public AdtCppBase
{
private:
  bool                          Qualified;

public:
  AdtCppUsingDirective(const char* pIdentifier,
                       bool bQualified);

  AdtCppUsingDirective(const AdtCppUsingDirective& rCopy);
  virtual ~AdtCppUsingDirective();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppAsmDefinition class
//  ----------------------------------------------------------------------------
class AdtCppAsmDefinition : public AdtCppBase
{
public:
  AdtCppAsmDefinition(const char* pStringLiteral);
  AdtCppAsmDefinition(const AdtCppAsmDefinition& rCopy);
  virtual ~AdtCppAsmDefinition();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppLinkageSpecification class
//  ----------------------------------------------------------------------------
class AdtCppLinkageSpecification : public AdtCppBase
{
private:
  AdtCppDeclarationSeq*         DeclarationSeq;
  AdtCppDeclaration*            Declaration;

public:
  AdtCppLinkageSpecification(AdtParser* pDeclarationSeqObj,
                             AdtParser* pDeclarationObj,
                             const char* pStringLiteral);

  AdtCppLinkageSpecification(const AdtCppLinkageSpecification& rCopy);
  virtual ~AdtCppLinkageSpecification();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInitDeclaratorList class
//  ----------------------------------------------------------------------------
class AdtCppInitDeclaratorList : public AdtCppBase
{
public:
  AdtCppInitDeclaratorList(AdtParser* pInitDeclaratorObj);
  AdtCppInitDeclaratorList(const AdtCppInitDeclaratorList& rCopy);
  virtual ~AdtCppInitDeclaratorList();

  bool                          isSimpleDeclaration(const char** ppIdentifier = 0) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppInitDeclarator);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInitDeclarator class
//  ----------------------------------------------------------------------------
class AdtCppInitDeclarator : public AdtCppBase
{
private:
  AdtCppDeclarator*             Declarator;
  AdtCppInitializer*            Initializer;

public:
  AdtCppInitDeclarator(AdtParser* pDeclaratorObj,
                       AdtParser* pInitializerObj);

  AdtCppInitDeclarator(const AdtCppInitDeclarator& rCopy);
  virtual ~AdtCppInitDeclarator();

  bool                          isSimpleDeclaration(const char** ppIdentifier = 0) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppDeclaratorCV_Type
{
  AdtCppDeclaratorCV_None     = 0,
  AdtCppDeclaratorCV_Const    = 1,
  AdtCppDeclaratorCV_Volatile = 2
};

//  ----------------------------------------------------------------------------
//  AdtCppDeclarator class
//  ----------------------------------------------------------------------------
class AdtCppDeclarator : public AdtCppEmbeddedComment
{
private:
  AdtCppParameterDeclarationClause* ParameterDeclarationClause;
  AdtCppExpressionList*             ExpressionList;
  AdtCppDeclaratorDims*             DeclaratorDims;
  bool                              WithBrackets;
  bool                              Qualified;
  bool                              IsObj;
  bool                              IsVirtual;
  AdtCppDeclaratorCV_Type           Type;

public:
  AdtCppDeclarator(AdtParser* pParameterDeclarationClauseObj,
                   AdtParser* pExpressionListObj,
                   AdtParser* pDeclaratorDimsObj,
                   const char* pIdentifier,
                   bool bWithBrackets,
                   bool bQualified,
                   bool bIsObj,
                   bool bIsVirtual,
                   AdtCppDeclaratorCV_Type nType,
                   bool bInitQualifiedName);

  AdtCppDeclarator(const AdtCppDeclarator& rCopy);
  virtual ~AdtCppDeclarator();

  bool                          isSimpleDeclaration(const char** ppIdentifier = 0) const;
  bool                          isCallDeclaration(size_t* pnArgs = 0) const;
  bool                          isFunctionDeclaration() const;
  bool                          isObj() const;
  bool                          isVirtual() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarator::isObj() const
{
  return (IsObj);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppDeclarator::isVirtual() const
{
  return (IsVirtual);
}


//  ----------------------------------------------------------------------------
//  AdtCppDeclaratorDims class
//  ----------------------------------------------------------------------------
class AdtCppDeclaratorDims : public AdtCppBase
{
private:
  AdtCppConstantExpression*     ConstantExpression;
  AdtCppDeclaratorDims*         DeclaratorDims;

public:
  AdtCppDeclaratorDims(AdtParser* pConstantExpressionObj,
                       AdtParser* pDeclaratorDimsObj);

  AdtCppDeclaratorDims(const AdtCppDeclaratorDims& rCopy);
  virtual ~AdtCppDeclaratorDims();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclarationClause class
//  ----------------------------------------------------------------------------
class AdtCppParameterDeclarationClause : public AdtCppBase
{
private:
  AdtCppParameterDeclarationList* ParameterDeclarationList;
  bool                            HasEllipsis;
  bool                            HasComma;

public:
  AdtCppParameterDeclarationClause(AdtParser* pParameterDeclarationListObj,
                                   bool bHasEllipsis,
                                   bool bHasComma);

  AdtCppParameterDeclarationClause(const AdtCppParameterDeclarationClause& rCopy);
  virtual ~AdtCppParameterDeclarationClause();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclarationList class
//  ----------------------------------------------------------------------------
class AdtCppParameterDeclarationList : public AdtCppBase
{
public:
  AdtCppParameterDeclarationList(AdtParser* pParameterDeclarationObj);
  AdtCppParameterDeclarationList(const AdtCppParameterDeclarationList& rCopy);
  virtual ~AdtCppParameterDeclarationList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppParameterDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppParameterDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppParameterDeclaration : public AdtCppBase
{
private:
  AdtCppDeclModifierList*     DeclModifierList;
  AdtCppSimpleTypeSpecifier*  SimpleTypeSpecifier;
  AdtCppDeclarator*           Declarator;
  AdtCppAssignmentExpression* AssignmentExpression;

public:
  AdtCppParameterDeclaration(AdtParser* pDeclModifierListObj,
                             AdtParser* pSimpleTypeSpecifierObj,
                             AdtParser* pDeclaratorObj,
                             AdtParser* pAssignmentExpressionObj);

  AdtCppParameterDeclaration(const AdtCppParameterDeclaration& rCopy);
  virtual ~AdtCppParameterDeclaration();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppFunctionDefinition class
//  ----------------------------------------------------------------------------
class AdtCppFunctionDefinition : public AdtCppCheckDeclaration
{
private:
  AdtCppDeclModifierList*       DeclModifierList;
  AdtCppSimpleTypeSpecifier*    SimpleTypeSpecifier;
  AdtCppDeclarator*             Declarator;
  AdtCppCtorInitializer*        CtorInitializer;
  AdtCppFunctionBody*           FunctionBody;
  AdtBlackBoxDefinition*        BlackBox;
  bool                          HasSemiColon;

protected:
  virtual void                  bindComment(const string* pComment);

public:
  AdtCppFunctionDefinition(AdtParser* pDeclModifierListObj,
                           AdtParser* pSimpleTypeSpecifierObj,
                           AdtParser* pDeclaratorObj,
                           AdtParser* pCtorInitializerObj,
                           AdtParser* pFunctionBodyObj,
                           bool bHasSemiColon);

  AdtCppFunctionDefinition(const AdtCppFunctionDefinition& rCopy);
  virtual ~AdtCppFunctionDefinition();

  AdtBlackBoxDefinition*        compileBlackBoxDefinition();

  AdtBlackBoxDefinition*        blackBox() const;

  bool                          isProcedure() const;

  bool                          isVirtual() const;

  void                          checkDeclarations(const AdtCppTranslationUnit* pTranslationUnit) const;

  bool                          enumerateLocalObjects(AdtParserPtrList& rExternalsList) const;

  bool                          enumerateExternals(AdtStringList& rExternalsList) const;

  void                          replaceScopeName(const char* pSearchName,
                                                 const char* pReplaceName);

  void                          promoteToFullyQualified();
  void                          removeFunctionBody();
  virtual bool                  isForwardDeclaration(bool bClassScope) const;
  bool                          isCtor() const;
  bool                          hasBody() const;
  AdtAutoType                   autoType(int& nDimensions) const;
  AdtAutoDir                    autoDir() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtBlackBoxDefinition* AdtCppFunctionDefinition::blackBox() const
{
  return (BlackBox);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppFunctionDefinition::hasBody() const
{
  return (FunctionBody != 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppFunctionDefinition::isVirtual() const
{
  bool bIsVirtual = (DeclModifierList != 0) ? DeclModifierList->hasModifier(AdtCppDeclModifierType_VIRTUAL) : false;

  return (bIsVirtual);
}

//  ----------------------------------------------------------------------------

inline AdtAutoType AdtCppFunctionDefinition::autoType(int& nDimensions) const
{
  AdtAutoType nType;

  nDimensions = 0;
  nType       = (SimpleTypeSpecifier != 0) ? SimpleTypeSpecifier->autoType(nDimensions) : AdtAutoType_UNDEFINED;

  return (nType);
}

//  ----------------------------------------------------------------------------

inline AdtAutoDir AdtCppFunctionDefinition::autoDir() const
{
  AdtAutoDir nDir = (SimpleTypeSpecifier != 0) ? SimpleTypeSpecifier->autoDir() : AdtAutoDir_UNDEFINED;

  return (nDir);
}


//  ----------------------------------------------------------------------------
//  AdtCppFunctionBody class
//  ----------------------------------------------------------------------------
class AdtCppFunctionBody : public AdtCppBase
{
private:
  AdtCppCompoundStatement*      CompoundStatement;

public:
  AdtCppFunctionBody(AdtParser* pCompoundStatementObj);
  AdtCppFunctionBody(const AdtCppFunctionBody& rCopy);
  virtual ~AdtCppFunctionBody();

  void                          checkDeclarations(const AdtCppTranslationUnit* pTranslationUnit,
                                                  const AdtCppClassSpecifier* pClassSpecifier) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInitializer class
//  ----------------------------------------------------------------------------
class AdtCppInitializer : public AdtCppBase
{
private:
  AdtCppInitializerClause*      InitializerClause;
  AdtCppExpressionList*         ExpressionList;

public:
  AdtCppInitializer(AdtParser* pInitializerClauseObj,
                    AdtParser* pExpressionListObj);

  AdtCppInitializer(const AdtCppInitializer& rCopy);
  virtual ~AdtCppInitializer();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInitializerClause class
//  ----------------------------------------------------------------------------
class AdtCppInitializerClause : public AdtCppBase
{
private:
  AdtCppAssignmentExpression*   AssignmentExpression;
  AdtCppInitializerList*        InitializerList;
  bool                          HasComma;

public:
  AdtCppInitializerClause(AdtParser* pAssignmentExpressionObj,
                          AdtParser* pInitializerListObj,
                          bool bHasComma);

  AdtCppInitializerClause(const AdtCppInitializerClause& rCopy);
  virtual ~AdtCppInitializerClause();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppInitializerList class
//  ----------------------------------------------------------------------------
class AdtCppInitializerList : public AdtCppBase
{
public:
  AdtCppInitializerList(AdtParser* pInitializerClauseObj);
  AdtCppInitializerList(const AdtCppInitializerList& rCopy);
  virtual ~AdtCppInitializerList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppInitializerClause);
  declType;
};


//  ----------------------------------------------------------------------------

enum AdtCppClassKeyType
{
  AdtCppClassKeyType_CLASS  = 0,
  AdtCppClassKeyType_STRUCT = 1,
  AdtCppClassKeyType_UNION  = 2
};

//  ----------------------------------------------------------------------------

enum AdtCppMemberScopeType
{
  AdtCppMemberScopeType_NONE      = 0,
  AdtCppMemberScopeType_PRIVATE   = 1,
  AdtCppMemberScopeType_PROTECTED = 2,
  AdtCppMemberScopeType_PUBLIC    = 3
};

//  ----------------------------------------------------------------------------
//  AdtCppClassKey class
//  ----------------------------------------------------------------------------
class AdtCppClassKey : public AdtCppBase
{
private:
  AdtCppClassKeyType            Type;
  bool                          Qualified;

public:
  AdtCppClassKey(AdtCppClassKeyType nType, const char* pIdentifier, bool bQualified);
  AdtCppClassKey(const AdtCppClassKey& rCopy);
  virtual ~AdtCppClassKey();

  AdtCppMemberScopeType         scopeType() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemberSpecification class
//  ----------------------------------------------------------------------------
class AdtCppMemberSpecification : public AdtCppDeclarationInfo
{
protected:

public:
  AdtCppMemberSpecification(AdtParser* pMemberDeclarationObj);
  AdtCppMemberSpecification(const AdtCppMemberSpecification& rCopy);
  virtual ~AdtCppMemberSpecification();

  void                          initialise();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppMemberDeclaration);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclaration class
//  ----------------------------------------------------------------------------
class AdtCppMemberDeclaration : public AdtCppBase
{
private:
  AdtCppClassSpecifier*         ClassSpecifier;
  AdtCppEnumSpecifier*          EnumSpecifier;
  AdtCppDeclModifierList*       DeclModifierList;
  AdtCppSimpleTypeSpecifier*    SimpleTypeSpecifier;
  AdtCppMemberDeclarationList*  MemberDeclarationList;
  AdtCppFunctionDefinition*     FunctionDefinition;
  AdtCppUsingDeclaration*       UsingDeclaration;
  AdtCppMemberScopeType         Type;
  bool                          HasSemicolon;

public:
  static AdtCppMemberScopeType  GlobalType;

  AdtCppMemberDeclaration(AdtParser* pClassSpecifierObj,
                          AdtParser* pEnumSpecifierObj,
                          AdtParser* pDeclModifierListObj,
                          AdtParser* pSimpleTypeSpecifierObj,
                          AdtParser* pMemberDeclarationListObj,
                          AdtParser* pFunctionDefinitionObj,
                          AdtParser* pUsingDeclarationObj,
                          AdtCppMemberScopeType nType,
                          bool bHasSemicolon);

  AdtCppMemberDeclaration(const AdtCppMemberDeclaration& rCopy);
  virtual ~AdtCppMemberDeclaration();

  bool                          shouldImport(AdtIntByStringMap& rImportMap) const;
  bool                          isCtor() const;
  bool                          isInlineFunction() const;
  bool                          isVirtual() const;
  AdtCppMemberScopeType         scopeType() const;
  void                          checkLookForDefinition(AdtStringList& rImportDefinitionList) const;
  void                          addPublicMethods(AdtStringByStringMap& rPublicMethodsMap, 
                                                 const string& rClassName, 
                                                 AdtCppMemberScopeType& nType) const;

  void                          exportFunctionImplementation(AdtCppTranslationUnit* pTarget);
  void                          updateScope(const AdtCppBaseSpecifier* pBaseSpecifier);

  void                          writeFortranDeclaration(AdtFile& rOutFile, const AdtCppDeclarator* pDeclarator) const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppMemberDeclaration::isVirtual() const
{
  bool bIsVirtual = (DeclModifierList != 0) ? DeclModifierList->hasModifier(AdtCppDeclModifierType_VIRTUAL) : false;

  return (bIsVirtual);
}

//  ----------------------------------------------------------------------------

inline AdtCppMemberScopeType AdtCppMemberDeclaration::scopeType() const
{
  return (Type);
}


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclarationList class
//  ----------------------------------------------------------------------------
class AdtCppMemberDeclarationList : public AdtCppBase
{
public:
  AdtCppMemberDeclarationList(AdtParser* pMemberDeclaratorObj);
  AdtCppMemberDeclarationList(const AdtCppMemberDeclarationList& rCopy);
  virtual ~AdtCppMemberDeclarationList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppMemberDeclarator);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemberDeclarator class
//  ----------------------------------------------------------------------------
class AdtCppMemberDeclarator : public AdtCppBase
{
private:
  AdtCppDeclarator*             Declarator;

public:
  AdtCppMemberDeclarator(AdtParser* pDeclaratorObj,
                         const char* pIdentifier);

  AdtCppMemberDeclarator(const AdtCppMemberDeclarator& rCopy);
  virtual ~AdtCppMemberDeclarator();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppBaseSpecifierList class
//  ----------------------------------------------------------------------------
class AdtCppBaseSpecifierList : public AdtCppBase
{
public:
  AdtCppBaseSpecifierList(AdtParser* pBaseSpecifierObj);
  AdtCppBaseSpecifierList(const AdtCppBaseSpecifierList& rCopy);
  virtual ~AdtCppBaseSpecifierList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppBaseSpecifier);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppBaseSpecifier class
//  ----------------------------------------------------------------------------
class AdtCppBaseSpecifier : public AdtCppBase
{
private:
  AdtCppMemberScopeType         Type;
  bool                          Virtual;
  bool                          Qualified;

public:
  AdtCppBaseSpecifier(AdtCppMemberScopeType nType,
                      bool bVirtual,
                      bool bQualified,
                      const char* pIdentifier);

  AdtCppBaseSpecifier(const AdtCppBaseSpecifier& rCopy);
  virtual ~AdtCppBaseSpecifier();

  AdtCppMemberScopeType         combineScopeType(AdtCppMemberScopeType nType) const;
  AdtCppMemberScopeType         scopeType() const;
  bool                          isVirtual() const;
  bool                          qualified() const;

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtCppMemberScopeType AdtCppBaseSpecifier::scopeType() const
{
  return (Type);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppBaseSpecifier::isVirtual() const
{
  return (Virtual);
}

//  ----------------------------------------------------------------------------

inline bool AdtCppBaseSpecifier::qualified() const
{
  return (Qualified);
}


//  ----------------------------------------------------------------------------
//  AdtCppCtorInitializer class
//  ----------------------------------------------------------------------------
class AdtCppCtorInitializer : public AdtCppBase
{
private:
  AdtCppMemInitializerList*     MemInitializerList;

public:
  AdtCppCtorInitializer(AdtParser* pMemInitializerListObj);
  AdtCppCtorInitializer(const AdtCppCtorInitializer& rCopy);
  virtual ~AdtCppCtorInitializer();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializerList class
//  ----------------------------------------------------------------------------
class AdtCppMemInitializerList : public AdtCppBase
{
public:
  AdtCppMemInitializerList(AdtParser* pMemInitializerObj);
  AdtCppMemInitializerList(const AdtCppMemInitializerList& rCopy);
  virtual ~AdtCppMemInitializerList();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declListType(AdtCppMemInitializer);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializer class
//  ----------------------------------------------------------------------------
class AdtCppMemInitializer : public AdtCppBase
{
private:
  AdtCppMemInitializerId*       MemInitializerId;
  AdtCppExpressionList*         ExpressionList;

public:
  AdtCppMemInitializer(AdtParser* pMemInitializerIdObj,
                       AdtParser* pExpressionListObj);

  AdtCppMemInitializer(const AdtCppMemInitializer& rCopy);
  virtual ~AdtCppMemInitializer();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtCppMemInitializerId class
//  ----------------------------------------------------------------------------
class AdtCppMemInitializerId : public AdtCppBase
{
private:
  bool                          Qualified;

public:
  AdtCppMemInitializerId(bool bQualified,
                         const char* pIdentifier);

  AdtCppMemInitializerId(const AdtCppMemInitializerId& rCopy);
  virtual ~AdtCppMemInitializerId();

  virtual AdtFile&              writeCPP(AdtFile& rOutFile, int nMode = 0) const;
  virtual AdtFile&              writeFortran(AdtFile& rOutFile, int nMode = 0) const;

  declType;
};


#endif //__cplusplus
#endif //__ADTCPP_HPP
