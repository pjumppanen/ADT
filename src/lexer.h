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
//    lexer.h
//
//  Purpose:
//    This file includes declarations of utility functions and globals that are
//    part of the Flex/Bison generated parser.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __LEXER_H
#define __LEXER_H


#include <stdio.h>


//  ----------------------------------------------------------------------------
//  C/C++ compatibility macros
//  ----------------------------------------------------------------------------
#ifdef __cplusplus
  #define C_FUNCTION      extern "C"
  #define C_BLOCK_BEGIN   extern "C" {
  #define C_BLOCK_END     }
#else
  #define C_FUNCTION
  #define C_BLOCK_BEGIN
  #define C_BLOCK_END
#endif


#if defined(_MSC_VER)
  #ifndef fileno
    #define fileno _fileno
  #endif
#endif


//  ----------------------------------------------------------------------------
//  typedefs
//  ----------------------------------------------------------------------------
typedef int (*parse_fn)(void);


//  ----------------------------------------------------------------------------
//  Globals
//  ----------------------------------------------------------------------------
C_BLOCK_BEGIN

typedef struct delphiType
{
  void*         pContext;
  const char*   sValue;
  double        dValue;
  int           nValue;
  int           nBlockDepth;
} delphiType;


typedef struct fortranType
{
  void*         pContext;
  const char*   sValue;
  double        dValue;
  int           nValue;
  int           nBlockDepth;
} fortranType;


typedef struct cppType
{
  void*         pContext;
  const char*   sValue;
  double        dValue;
  int           nValue;
  int           nBlockDepth;
} cppType;


typedef struct javaType
{
  void*         pContext;
  const char*   sValue;
  double        dValue;
  int           nValue;
  int           nBlockDepth;
} javaType;


typedef struct makeType
{
  void*         pContext;
  const char*   sValue;
} makeType;


typedef struct expressionType
{
  void*         pContext;
  const char*   sValue;
  int           nValue;
} expressionType;


typedef struct blackBoxType
{
  void*         pContext;
  const char*   sValue;
  double        dValue;
  int           nValue;
} blackBoxType;


extern FILE*   yyDelphiin;
extern int     yyDelphidebug;
extern void*   adtDelphi_pDelphiContext;

extern FILE*   yyFortranin;
extern int     yyFortrandebug;
extern void*   adtFortran_pFortranContext;

extern FILE*   yyCppin;
extern int     yyCppdebug;
extern void*   adtCpp_pCppContext;
extern void*   adtCpp_ScopeManager;

extern FILE*   yyJavain;
extern int     yyJavadebug;
extern void*   adtJava_pJavaContext;

extern FILE*   yyMakein;
extern int     yyMakedebug;

extern FILE*   yyExpressionin;
extern int     yyExpressiondebug;
extern void*   adtExpression_pContext;

extern FILE*   yyBlackBoxin;
extern int     yyBlackBoxdebug;
extern int     yyBlackBoxIsFile;
extern int     yyBlackBoxReentrancyCount;
extern void*   adtBlackBox_pContext;

C_BLOCK_END


//  ----------------------------------------------------------------------------
//  Function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void*        scopeManager_Create(void);
C_FUNCTION void         scopeManager_Destroy(void* pPtrScopeManager);
C_FUNCTION void         scopeManager_addUsing(void* pPtrScopeManager, const char* pUsing);
C_FUNCTION void         scopeManager_addUsingDeclaration(void* pPtrScopeManager, const char* pTypeName);
C_FUNCTION void         scopeManager_addType(void* pPtrScopeManager, const char* pTypeName);
C_FUNCTION int          scopeManager_isType(void* pPtrScopeManager, const char* pSymbolName);
C_FUNCTION void         scopeManager_pushScope(void* pPtrScopeManager, const char* pScope, int nIsFunction);
C_FUNCTION void         scopeManager_popScope(void* pPtrScopeManager);

C_FUNCTION void         make_AddInclude(const char* pFileName);

C_FUNCTION void         yyDelphi_endParse(void);
C_FUNCTION void         yyDelphi_releaseBuffer(void);
C_FUNCTION int          yyDelphi_lineNumber(void);
C_FUNCTION const char*  yyDelphi_fileName(void);
C_FUNCTION void         yyDelphi_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyDelphi_error(void);

C_FUNCTION int          yyDelphiparse(void);
C_FUNCTION void         yyDelphirestart(FILE* pFile);
C_FUNCTION void         yyDelphierror(char const*);
C_FUNCTION int          yyDelphilex(void);
C_FUNCTION int          yyDelphi_canIncludeComment(int yychar);
C_FUNCTION void         adtDelphi_releaseRoot(void);

C_FUNCTION const char*  yyFortran_LastComment(void);
C_FUNCTION void         yyFortran_endParse(void);
C_FUNCTION int          yyFortran_lineNumber(void);
C_FUNCTION const char*  yyFortran_fileName(void);
C_FUNCTION void         yyFortran_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyFortran_error(void);
C_FUNCTION void         yyFortran_releaseBuffer(void);
C_FUNCTION int          yyFortranparse(void);
C_FUNCTION void         yyFortranrestart(FILE* pFile);
C_FUNCTION void         yyFortranerror(char const*);
C_FUNCTION int          yyFortranlex(void);
C_FUNCTION void         adtFortran_releaseRoot(void);

C_FUNCTION void         yyCpp_endParse(void);
C_FUNCTION void         yyCpp_releaseBuffer(void);
C_FUNCTION int          yyCpp_lineNumber(void);
C_FUNCTION const char*  yyCpp_fileName(void);
C_FUNCTION void         yyCpp_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyCpp_error(void);
C_FUNCTION int          yyCppparse(void);
C_FUNCTION void         yyCpprestart(FILE* pFile);
C_FUNCTION void         yyCpperror(char const*);
C_FUNCTION int          yyCpplex(void);
C_FUNCTION int          yyCpp_canIncludeComment(int yychar);
C_FUNCTION void         adtCpp_releaseRoot(void);

C_FUNCTION void         yyJava_endParse(void);
C_FUNCTION void         yyJava_releaseBuffer(void);
C_FUNCTION int          yyJava_lineNumber(void);
C_FUNCTION const char*  yyJava_fileName(void);
C_FUNCTION void         yyJava_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyJava_error(void);
C_FUNCTION int          yyJavaparse(void);
C_FUNCTION void         yyJavarestart(FILE* pFile);
C_FUNCTION void         yyJavaerror(char const*);
C_FUNCTION int          yyJavalex(void);
C_FUNCTION void         adtJava_releaseRoot(void);

C_FUNCTION void         yyMake_endParse(void);
C_FUNCTION void         yyMake_releaseBuffer(void);
C_FUNCTION int          yyMake_lineNumber(void);
C_FUNCTION const char*  yyMake_fileName(void);
C_FUNCTION void         yyMake_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyMake_error(void);
C_FUNCTION int          yyMakeparse(void);
C_FUNCTION void         yyMakerestart(FILE* pFile);
C_FUNCTION void         yyMakeerror(char const*);
C_FUNCTION int          yyMakelex(void);

C_FUNCTION void         yyExpression_endParse(void);
C_FUNCTION void         yyExpression_releaseBuffer(void);
C_FUNCTION void         yyExpression_resetError(void);
C_FUNCTION int          yyExpression_error(void);
C_FUNCTION const char*  yyExpression_errorMsg(void);
C_FUNCTION int          yyExpressionparse(void);
C_FUNCTION void         yyExpressionrestart(FILE* pFile);
C_FUNCTION void         yyExpressionerror(char const*);
C_FUNCTION int          yyExpressionlex(void);

C_FUNCTION void         yyBlackBox_endParse(void);
C_FUNCTION void         yyBlackBox_releaseBuffer(void);
C_FUNCTION int          yyBlackBox_lineNumber(void);
C_FUNCTION const char*  yyBlackBox_fileName(void);
C_FUNCTION void         yyBlackBox_resetLineNumber(const char* pFileName);
C_FUNCTION int          yyBlackBox_error(void);
C_FUNCTION const char*  yyBlackBox_errorMsg(void);
C_FUNCTION int          yyBlackBoxparse(void);
C_FUNCTION void         yyBlackBoxrestart(FILE* pFile);
C_FUNCTION void         yyBlackBoxerror(char const*);
C_FUNCTION int          yyBlackBoxlex(void);
C_FUNCTION void         yyBlackBox_pushState(int nState);
C_FUNCTION void         yyBlackBox_popState(void);
C_FUNCTION int          yyBlackBox_topState(void);


#endif  //__LEXER_H
