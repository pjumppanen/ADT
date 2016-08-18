%{
/*
 * fortran.y
 *
 *  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
 *  ORGANISATION (CSIRO), Australia.
 *  All rights reserved.
 *
 *  This file is part of ADT.  The full ADT copyright notice, including
 *  terms governing use, modification, and redistribution, is contained in
 *  the file COPYING. COPYING can be found at the root of the source code
 *  distribution tree;
 *
 * Minimalist Fortran 95 grammar in Yacc format to be used to parse output
 * from TAPENADE into a parse tree for the purpose of conversion into another
 * language (delphi). This mimimalist grammar supports parsing of functions,
 * subroutines and data only modules. This is based on:
 *
 *  "This specification was created originally in January of 1987 by W. M. Waite
 *   and J. Hoffmann. Further development in the fall of 1989 by R. Jakob made
 *   it a basis for an analyzer for the ``Force'' extension of FORTRAN. Both of
 *   these versions only handled ``nice looking'' FORTRAN programs, because of
 *   weakness in the lexical analyzer. These restrictions were removed in the
 *   summer of 1993 by W. M. Waite, while he was a visiting researcher at the
 *   GMD in Berlin. It was modified to be specific to Fortran 95 by W. B. Clodius
 *   in the summer of 1998."
 *
 * Bison -r state -p yyfortran -b yyfortran -d fortran.y
 */


#include <stdio.h>
#include "lexer.h"
#include "adtfortran.hpp"
#include "adtutils.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   fortranType

%}

/* fortran tokens */
%token LBRACKET RBRACKET COMMA COLON ASSIGN PLUS MINUS POWER MULTIPLY DIVIDE BOGUS
%token LOGICAL_EQ LOGICAL_NE LOGICAL_LT LOGICAL_LE LOGICAL_GT LOGICAL_GE LOGICAL_NOT
%token LOGICAL_AND LOGICAL_OR LOGICAL_EQUIV LOGICAL_NEQUIV EQUAL NEQUAL LT LE GT GE
%token LOGICAL_TRUE LOGICAL_FALSE
%token INTEGER UNSIGNED REAL DOUBLEPRECISION DOUBLE PRECISION COMPLEX LOGICAL CHARACTER
%token DIMENSION END PARAMETER PRIVATE PROTECTED PUBLIC IMPLICIT NONE WHERE ELSEWHERE ENDWHERE
%token GOTO IF THEN ELSEIF ELSE ENDIF SELECTCASE SELECT CASE ENDSELECT DEFAULT DO WHILE
%token ENDDO CYCLE EXIT CONTINUE INTRINSIC MODULE ENDMODULE USE CALL RESULT FUNCTION
%token RECURSIVE ENDFUNCTION SUBROUTINE ENDSUBROUTINE RETURN EXTERNAL PROGRAM
%token XNAME XSCON XRCON XICON XRCON_S XICON_S XIMPL xEOS INTENT IN OUT INOUT
%token COMMENT LINE_CONTINUATION
%token CALL_EXPAND ADD_VARIABLES UNKNOWNTYPE

%%
/* R201 */
xExecutableProgram : xProgramUnit
{
  void* pObj;

  pObj        = adtFortranExecutableProgram_create($1.pContext);
  $$.pContext = adtFortran_setRoot(pObj);

  adtFortran_releaseObject(pObj);
}
                   | xExecutableProgram xProgramUnit
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

/* R202 */
xProgramUnit : xFunctionSubprogram
{
  $$.pContext = adtFortranProgramUnit_create($1.pContext, 0, 0, 0, 0);
}
             | xSubroutineSubprogram
{
  $$.pContext = adtFortranProgramUnit_create(0, $1.pContext, 0, 0, 0);
}
             | xModule
{
  $$.pContext = adtFortranProgramUnit_create(0, 0, $1.pContext, 0, 0);
}
             | xCallExpand
{
  $$.pContext = adtFortranProgramUnit_create(0, 0, 0, $1.pContext, 0);
}
             | xProgramConstruct
{
  $$.pContext = adtFortranProgramUnit_create(0, 0, 0, 0, $1.pContext);
}
;

/* We don't normally use the program construct but we have added a
   simplified form of it so that we may use the compiler to build
   parse trees for expressions we wish to add to an existing parse
   tree (ie. an expression builder) */
xProgramConstruct : xBody xLblDef END xEOS
{
  $$.pContext = adtFortranProgramConstruct_create(0, 0, $1.pContext, $2.pContext);
}
                  | xLblDef PROGRAM xName xEOS xBody xLblDef END xEOS
{
  $$.pContext = adtFortranProgramConstruct_create($1.pContext, $3.pContext, $5.pContext, $6.pContext);
}
;

/* This is a special construct introduced to allow us to define FORTRAN inline
   code expansion for subroutine calls in a generalised way. The scanner only
   decodes the CALL_EXPAND and ADD_VARIABLES tokens in a special state that is
   invoked only when compiling a macro definition file. */
xCallExpand : CALL_EXPAND xName xEOS xConditionalBody ADD_VARIABLES xEOS xTypeDeclarationStmtList END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, 0, $4.pContext, $7.pContext, 0);
}
            | CALL_EXPAND xName xEOS xConditionalBody END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, 0, $4.pContext, 0, 0);
}
            | CALL_EXPAND xName LBRACKET RBRACKET xEOS xConditionalBody ADD_VARIABLES xEOS xTypeDeclarationStmtList END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, 0, $6.pContext, $9.pContext, 1);
}
            | CALL_EXPAND xName LBRACKET RBRACKET xEOS xConditionalBody END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, 0, $6.pContext, 0, 1);
}
            | CALL_EXPAND xName LBRACKET xNameList RBRACKET xEOS xConditionalBody ADD_VARIABLES xEOS xTypeDeclarationStmtList END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, $4.pContext, $7.pContext, $10.pContext, 1);
}
            | CALL_EXPAND xName LBRACKET xNameList RBRACKET xEOS xConditionalBody END xEOS
{
  $$.pContext = adtFortranCallExpand_create($2.pContext, $4.pContext, $7.pContext, 0, 1);
}
;

xTypeDeclarationStmtList : xTypeDeclarationStmt
{
  $$.pContext = adtFortranTypeDeclarationStmtList_create($1.pContext);
}
                         | xTypeDeclarationStmtList xTypeDeclarationStmt
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

xBody : xBodyConstruct
{
  $$.pContext = adtFortranBody_create($1.pContext);
}
      | xBody xBodyConstruct
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

xBodyConstruct : xSpecificationPartConstruct
{
  $$.pContext = adtFortranBodyConstruct_create($1.pContext, 0);
}
               | xExecutableConstruct
{
  $$.pContext = adtFortranBodyConstruct_create(0, $1.pContext);
}
;

/* %R1216 */
xFunctionSubprogram : xFunctionStmt xBody xEndFunctionStmt
{
  $$.pContext = adtFortranFunctionSubprogram_create($1.pContext, $3.pContext, $2.pContext);
}
                    | xFunctionStmt xEndFunctionStmt
{
  $$.pContext = adtFortranFunctionSubprogram_create($1.pContext, $2.pContext, 0);
}
/* Don't allow nested definitions
                    | xFunctionStmt xFunctionSubprogram xEndFunctionStmt
                    | xFunctionStmt xSubroutineSubprogram xEndFunctionStmt */
;

/* % R1221 */
xSubroutineSubprogram : xSubroutineStmt xBody xEndSubroutineStmt
{
  $$.pContext = adtFortranSubroutineSubprogram_create($1.pContext, $3.pContext, $2.pContext);
}
                      | xSubroutineStmt xEndSubroutineStmt
{
  $$.pContext = adtFortranSubroutineSubprogram_create($1.pContext, $2.pContext, 0);
}
/* Don't allow nested definitions
                      | xSubroutineStmt xFunctionSubprogram xEndSubroutineStmt
                      | xSubroutineStmt xSubroutineSubprogram xEndSubroutineStmt */
;

/* % R1104 */
xModule : xModuleStmt xModuleBody xEndModuleStmt
{
  $$.pContext = adtFortranModule_create($1.pContext, $2.pContext, $3.pContext);
}
        | xModuleStmt xEndModuleStmt
{
  $$.pContext = adtFortranModule_create($1.pContext, 0, $2.pContext);
}
;

xModuleBody : xModuleBodyContent
{
  $$.pContext = adtFortranModuleBody_create($1.pContext);
}
            | xModuleBody xModuleBodyContent
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

xModuleBodyContent : xSpecificationPartConstruct
{
  $$.pContext = adtFortranModuleBodyContent_create($1.pContext, 0, 0);
}
                   | xFunctionSubprogram
{
  $$.pContext = adtFortranModuleBodyContent_create(0, $1.pContext, 0);
}
                   | xSubroutineSubprogram
{
  $$.pContext = adtFortranModuleBodyContent_create(0, 0, $1.pContext);
}
;

/* % R204 doesn't ensure ordering as the standard requires */
xSpecificationPartConstruct : xUseStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create($1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
                            | xImplicitStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
                            | xParameterStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
                            | xTypeDeclarationStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
                            | xDimensionStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
                            | xIntrinsicStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
                            | xExternalStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, 0, 0, 0, 0, $1.pContext, 0);
}
                            | xIntentStmt
{
  $$.pContext = adtFortranSpecificationPartConstruct_create(0, 0, 0, 0, 0, 0, 0, $1.pContext);
}
;

/* % R215 */
xExecutableConstruct : xActionStmt
{
  $$.pContext = adtFortranExecutableConstruct_create($1.pContext, 0, 0, 0, 0);
}
                     | xCaseConstruct
{
  $$.pContext = adtFortranExecutableConstruct_create(0, $1.pContext, 0, 0, 0);
}
                     | xDoConstruct
{
  $$.pContext = adtFortranExecutableConstruct_create(0, 0, $1.pContext, 0, 0);
}
                     | xIfConstruct
{
  $$.pContext = adtFortranExecutableConstruct_create(0, 0, 0, $1.pContext, 0);
}
                     | xWhereConstruct
{
  $$.pContext = adtFortranExecutableConstruct_create(0, 0, 0, 0, $1.pContext);
}
;
/* see the note on R818 */

/* % R216 */
xActionStmt : xArithmeticIfStmt
{
  $$.pContext = adtFortranActionStmt_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
            | xAssignmentStmt
{
  $$.pContext = adtFortranActionStmt_create(0, $1.pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
            | xCallStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
            | xContinueStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
            | xCycleStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
            | xExitStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
            | xIfStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
            | xReturnStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
            | xWhereStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, 0, 0, 0, 0, $1.pContext, 0);
}
            | xGotoStmt
{
  $$.pContext = adtFortranActionStmt_create(0, 0, 0, 0, 0, 0, 0, 0, 0, $1.pContext);
}
;

/* % R714 */
xRelOp : LOGICAL_EQ
{
  $$.pContext = adtFortranRelOp_create(0);
}
       | LOGICAL_NE
{
  $$.pContext = adtFortranRelOp_create(1);
}
       | LOGICAL_LT
{
  $$.pContext = adtFortranRelOp_create(2);
}
       | LOGICAL_LE
{
  $$.pContext = adtFortranRelOp_create(3);
}
       | LOGICAL_GT
{
  $$.pContext = adtFortranRelOp_create(4);
}
       | LOGICAL_GE
{
  $$.pContext = adtFortranRelOp_create(5);
}
       | EQUAL
{
  $$.pContext = adtFortranRelOp_create(6);
}
       | NEQUAL
{
  $$.pContext = adtFortranRelOp_create(7);
}
       | LT
{
  $$.pContext = adtFortranRelOp_create(8);
}
       | LE
{
  $$.pContext = adtFortranRelOp_create(9);
}
       | GT
{
  $$.pContext = adtFortranRelOp_create(10);
}
       | GE
{
  $$.pContext = adtFortranRelOp_create(11);
}
;

/* % R501 */
xTypeDeclarationStmt : xLblDef xTypeSpec xAttrSpecSeq COLON COLON xEntityDeclList xEOS
{
  $$.pContext = adtFortranTypeDeclarationStmt_create($1.pContext, $2.pContext, $3.pContext, $6.pContext);
}
                     | xLblDef xTypeSpec COLON COLON xEntityDeclList xEOS
{
  $$.pContext = adtFortranTypeDeclarationStmt_create($1.pContext, $2.pContext, 0, $5.pContext);
}
                     | xLblDef xTypeSpec xEntityDeclList xEOS
{
  $$.pContext = adtFortranTypeDeclarationStmt_create($1.pContext, $2.pContext, 0, $3.pContext);
}
;

xAttrSpecSeq : COMMA xAttrSpec
{
  $$.pContext = adtFortranAttrSpecSeq_create($2.pContext);
}
             | xAttrSpecSeq COMMA xAttrSpec
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

/* % R502 */
xTypeSpec : INTEGER
{
  $$.pContext = adtFortranTypeSpec_create(0, 0);
}
          | INTEGER LBRACKET XICON RBRACKET
{
  $$.pContext = adtFortranTypeSpec_create(0, $3.sValue);
}
          | INTEGER MULTIPLY XICON
{
  $$.pContext = adtFortranTypeSpec_create(0, $3.sValue);
}
          | REAL
{
  $$.pContext = adtFortranTypeSpec_create(1, 0);
}
          | REAL LBRACKET XICON RBRACKET
{
  $$.pContext = adtFortranTypeSpec_create(1, $3.sValue);
}
          | REAL MULTIPLY XICON
{
  $$.pContext = adtFortranTypeSpec_create(1, $3.sValue);
}
          | DOUBLEPRECISION
{
  $$.pContext = adtFortranTypeSpec_create(2, 0);
}
          | COMPLEX
{
  $$.pContext = adtFortranTypeSpec_create(3, 0);
}
          | DOUBLE COMPLEX
{
  $$.pContext = adtFortranTypeSpec_create(4, 0);
}
          | LOGICAL
{
  $$.pContext = adtFortranTypeSpec_create(5, 0);
}
          | CHARACTER
{
  $$.pContext = adtFortranTypeSpec_create(6, 0);
}
          | DOUBLE PRECISION
{
  $$.pContext = adtFortranTypeSpec_create(2, 0);
}
          | UNSIGNED
{
  $$.pContext = adtFortranTypeSpec_create(7, 0);
}
          | UNSIGNED LBRACKET XICON RBRACKET
{
  $$.pContext = adtFortranTypeSpec_create(7, $3.sValue);
}
          | UNSIGNED MULTIPLY XICON
{
  $$.pContext = adtFortranTypeSpec_create(7, $3.sValue);
}
          | UNKNOWNTYPE
{
  $$.pContext = adtFortranTypeSpec_create(8, 0);
}
;

/* % R503 */
xAttrSpec : PARAMETER
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 0);
}
          | PUBLIC
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 1);
}
          | PROTECTED
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 2);
}
          | PRIVATE
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 3);
}
          | INTRINSIC
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 4);
}
          | EXTERNAL
{
  $$.pContext = adtFortranAttrSpec_create(0, 0, 5);
}
          | DIMENSION LBRACKET xShapeSpecList RBRACKET
{
  $$.pContext = adtFortranAttrSpec_create($3.pContext, 0, 6);
}
          | INTENT LBRACKET xIntentSpec RBRACKET
{
  $$.pContext = adtFortranAttrSpec_create(0, $3.pContext, 7);
}
;

/* % R504 */
xEntityDeclList : xEntityDecl
{
  $$.pContext = adtFortranEntityDeclList_create($1.pContext);
}
                | xEntityDeclList COMMA xEntityDecl
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xEntityDecl : xName
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, 0, 0, 0, 0);
}
            | xName ASSIGN xExpr
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, $3.pContext, 0, 0, 0);
}
            | xName MULTIPLY xCharLength
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, 0, $3.pContext, 0, 0);
}
            | xName MULTIPLY xCharLength ASSIGN xExpr
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, $5.pContext, $3.pContext, 0, 0);
}
            | xName LBRACKET xShapeSpecList RBRACKET
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, 0, 0, $3.pContext, 0);
}
            | xName LBRACKET xShapeSpecList RBRACKET ASSIGN xExpr
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, $6.pContext, 0, $3.pContext, 0);
}
            | xName LBRACKET xShapeSpecList RBRACKET MULTIPLY xCharLength
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, 0, $6.pContext, $1.pContext, 0);
}
            | xName LBRACKET xShapeSpecList RBRACKET MULTIPLY xCharLength ASSIGN xExpr
{
  $$.pContext = adtFortranEntityDecl_create($1.pContext, $8.pContext, $6.pContext, $3.pContext, 0);
}
            | xInvalidEntityDecl
{
  $$.pContext = adtFortranEntityDecl_create(0, 0, 0, 0, $1.pContext);
}
;

xInvalidEntityDecl : xName MULTIPLY xCharLength LBRACKET xShapeSpecList RBRACKET
{
  $$.pContext = adtFortranInvalidEntityDecl_create($1.pContext, 0, $3.pContext, $5.pContext);
}
                   | xName MULTIPLY xCharLength LBRACKET xShapeSpecList RBRACKET ASSIGN xExpr
{
  $$.pContext = adtFortranInvalidEntityDecl_create($1.pContext, $8.pContext, $3.pContext, $5.pContext);
}
;

/* % R509 */
xCharLength : LBRACKET xExpr RBRACKET
{
  $$.pContext = adtFortranCharLength_create($2.pContext, 0);
}
            | LBRACKET MULTIPLY RBRACKET
{
  $$.pContext = adtFortranCharLength_create(0, 0);
}
            | xIcon
{
  $$.pContext = adtFortranCharLength_create(0, $1.pContext);
}
;

/* % R514 */
xShapeSpecList : xShapeSpec
{
  $$.pContext = adtFortranShapeSpecList_create($1.pContext);
}
               | xShapeSpecList COMMA xShapeSpec
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xShapeSpec : xExpr COLON xExpr
{
  $$.pContext = adtFortranShapeSpec_create($1.pContext, $3.pContext);
}
           | xExpr
{
  $$.pContext = adtFortranShapeSpec_create($1.pContext, 0);
}
           | COLON
{
  $$.pContext = adtFortranShapeSpec_create(0, 0);
}
;

/* % R526 */
xDimensionStmt : xLblDef DIMENSION xArrayDeclaratorList xEOS
{
  $$.pContext = adtFortranDimensionStmt_create($1.pContext, $3.pContext);
}
               | xLblDef DIMENSION COLON COLON xArrayDeclaratorList xEOS
{
  $$.pContext = adtFortranDimensionStmt_create($1.pContext, $5.pContext);
}
;

xArrayDeclaratorList : xArrayDeclarator
{
  $$.pContext = adtFortranArrayDeclaratorList_create($1.pContext);
}
                     | xArrayDeclaratorList COMMA xArrayDeclarator
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xArrayDeclarator : xName LBRACKET xShapeSpecList RBRACKET
{
  $$.pContext = adtFortranArrayDeclarator_create($1.pContext, $3.pContext);
}
;

/* % R530 */
xParameterStmt : xLblDef PARAMETER LBRACKET xNamedConstantDefList RBRACKET xEOS
{
  $$.pContext = adtFortranParameterStmt_create($1.pContext, $4.pContext);
}
;

/* % R531 */
xNamedConstantDefList : xNamedConstantDef
{
  $$.pContext = adtFortranNamedConstantDefList_create($1.pContext);
}
                      | xNamedConstantDefList COMMA xNamedConstantDef
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xNamedConstantDef : xName ASSIGN xExpr
{
  $$.pContext = adtFortranNamedConstantDef_create($1.pContext, $3.pContext);
}
;

/* % R541 */
xImplicitStmt : xLblDef IMPLICIT xImplicitSpecList xEOS
{
  $$.pContext = adtFortranImplicitStmt_create($1.pContext, $3.pContext);
}
              | xLblDef IMPLICIT NONE xEOS
{
  $$.pContext = adtFortranImplicitStmt_create($1.pContext, 0);
}
;

/* % R542 */
xImplicitSpecList : xImplicitSpec
{
  $$.pContext = adtFortranImplicitSpecList_create($1.pContext);
}
                  | xImplicitSpecList COMMA xImplicitSpec
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xImplicitSpec : xTypeSpec xImpl
{
  $$.pContext = adtFortranImplicitSpec_create($1.pContext, $2.pContext);
}
;

/* % R618 Recognized semantically? */
xSectionSubscriptList : xSectionSubscript
{
  $$.pContext = adtFortranSectionSubscriptList_create($1.pContext);
}
                      | xSectionSubscriptList COMMA xSectionSubscript
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xSectionSubscript : xExpr
{
  $$.pContext = adtFortranSectionSubscript_create($1.pContext, 0);
}
                  | xSubscriptTriplet
{
  $$.pContext = adtFortranSectionSubscript_create(0, $1.pContext);
}
;

/* % R619 */
xSubscriptTriplet : COLON
{
  $$.pContext = adtFortranSubscriptTriplet_create(0, 0, 0, 0);
}
                  | COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(1, $2.pContext, 0, 0);
}
                  | xExpr COLON
{
  $$.pContext = adtFortranSubscriptTriplet_create(2, $1.pContext, 0, 0);
}
                  | xExpr COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(3, $1.pContext, $3.pContext, 0);
}
                  | xExpr COLON xExpr COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(4, $1.pContext, $3.pContext, $5.pContext);
}
                  | xExpr COLON COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(5, $1.pContext, $4.pContext, 0);
}
/* Slicing produces conflicts that I can't be bothered fixing now. For now don't
   support slicing and only add it if needed.
                  | COLON xExpr COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(6, $2.pContext, $4.pContext, 0);
}
                  | COLON COLON xExpr
{
  $$.pContext = adtFortranSubscriptTriplet_create(7, $3.pContext, 0, 0);
}
*/
;

/* % R701 - remove xFunctionReference as it is not needed. Function references
            are recognised as Arrays (xName LBRACKET xSectionSubscriptList RBRACKET)
            and are only determined to be functions rather than arrays though
            what function definitions appear in the symbol table.
*/
xPrimary : LOGICAL_TRUE
{
  $$.pContext = adtFortranPrimary_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
         | LOGICAL_FALSE
{
  $$.pContext = adtFortranPrimary_create(0, 0, 0, 0, 0, 0, 0, 0, 0);
}
         | xScon
{
  $$.pContext = adtFortranPrimary_create(0, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
         | xIcon
{
  $$.pContext = adtFortranPrimary_create(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
         | xRcon
{
  $$.pContext = adtFortranPrimary_create(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
         | LBRACKET xExpr COMMA xExpr RBRACKET /* complex constant */
{
  $$.pContext = adtFortranPrimary_create(0, 0, 0, 0, $2.pContext, $4.pContext, 0, 0, 1);
}
         | xName
{
  $$.pContext = adtFortranPrimary_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
         | xName LBRACKET RBRACKET
{
  $$.pContext = adtFortranPrimary_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
         | xName LBRACKET xSectionSubscriptList RBRACKET
{
  $$.pContext = adtFortranPrimary_create($1.pContext, 0, 0, 0, 0, 0, $3.pContext, 0, 1);
}
         | LBRACKET xExpr RBRACKET
{
  $$.pContext = adtFortranPrimary_create(0, 0, 0, 0, $2.pContext, 0, 0, 0, 1);
}
;

/* % R705 */
xMultOperand : xPrimary
{
  $$.pContext = adtFortranMultOperand_create($1.pContext, 0);
}
             | xPrimary POWER xMultOperand
{
  $$.pContext = adtFortranMultOperand_create($1.pContext, $3.pContext);
}
;

/* % R706 */
xAddOperand : xMultOperand
{
  $$.pContext = adtFortranAddOperand_create($1.pContext, 0, 0);
}
            | xAddOperand MULTIPLY xMultOperand
{
  $$.pContext = adtFortranAddOperand_create($3.pContext, $1.pContext, 1);
}
            | xAddOperand DIVIDE xMultOperand
{
  $$.pContext = adtFortranAddOperand_create($3.pContext, $1.pContext, 0);
}
;

/* % R707 */
xLevel2Expr : xAddOperand
{
  $$.pContext = adtFortranLevel2Expr_create($1.pContext, 0, 0, 0);
}
            | xLevel2Expr PLUS xAddOperand
{
  $$.pContext = adtFortranLevel2Expr_create($3.pContext, $1.pContext, 1, 1);
}
            | xLevel2Expr MINUS xAddOperand
{
  $$.pContext = adtFortranLevel2Expr_create($3.pContext, $1.pContext, 0, 1);
}
            | PLUS xAddOperand
{
  $$.pContext = adtFortranLevel2Expr_create($2.pContext, 0, 1, 1);
}
            | MINUS xAddOperand
{
  $$.pContext = adtFortranLevel2Expr_create($2.pContext, 0, 0, 1);
}
;

/* % R713 */
xLevel4Expr : xLevel2Expr
{
  $$.pContext = adtFortranLevel4Expr_create($1.pContext, 0, 0);
}
            | xLevel2Expr xRelOp xLevel2Expr
{
  $$.pContext = adtFortranLevel4Expr_create($1.pContext, $2.pContext, $3.pContext);
}
;

/* % R715 */
xAndOperand : xLevel4Expr
{
  $$.pContext = adtFortranAndOperand_create($1.pContext, 0);
}
            | LOGICAL_NOT xLevel4Expr
{
  $$.pContext = adtFortranAndOperand_create($2.pContext, 1);
}
;

/* % R716 */
xOrOperand : xAndOperand
{
  $$.pContext = adtFortranOrOperand_create($1.pContext, 0);
}
           | xOrOperand LOGICAL_AND xAndOperand
{
  $$.pContext = adtFortranOrOperand_create($3.pContext, $1.pContext);
}
;

/* % R717 */
xEquivOperand : xOrOperand
{
  $$.pContext = adtFortranEquivOperand_create($1.pContext, 0);
}
              | xEquivOperand LOGICAL_OR xOrOperand
{
  $$.pContext = adtFortranEquivOperand_create($3.pContext, $1.pContext);
}
;

/* % R718 */
xExpr : xEquivOperand
{
  $$.pContext = adtFortranExpr_create($1.pContext, 0, 0);
}
      | xExpr LOGICAL_EQUIV xEquivOperand
{
  $$.pContext = adtFortranExpr_create($3.pContext, $1.pContext, 1);
}
      | xExpr LOGICAL_NEQUIV xEquivOperand
{
  $$.pContext = adtFortranExpr_create($3.pContext, $1.pContext, 0);
}
;

xSFExprList : xSFExprList COLON xExpr COLON xExpr
{
  $$.pContext = adtFortranSFExprList_create($1.pContext, $3.pContext, $5.pContext);
}
            | xSFExprList COLON COLON xExpr
{
  $$.pContext = adtFortranSFExprList_create($1.pContext, 0, $4.pContext);
}
            | COLON xExpr COLON xExpr
{
  $$.pContext = adtFortranSFExprList_create(0, $2.pContext, $4.pContext);
}
            | COLON COLON xExpr
{
  $$.pContext = adtFortranSFExprList_create(0, 0, $3.pContext);
}
;

/* % R735 */
xAssignmentStmt : xLblDef xName ASSIGN xExpr xEOS
{
  $$.pContext = adtFortranAssignmentStmt_create($1.pContext, $2.pContext, $4.pContext, 0, 0);
}
                | xLblDef xName LBRACKET xSectionSubscriptList RBRACKET ASSIGN xExpr xEOS
{
  $$.pContext = adtFortranAssignmentStmt_create($1.pContext, $2.pContext, $7.pContext, 0, $4.pContext);
}
                | xLblDef xName LBRACKET xSFExprList RBRACKET ASSIGN xExpr xEOS
{
  $$.pContext = adtFortranAssignmentStmt_create($1.pContext, $2.pContext, $7.pContext, $4.pContext, 0);
}
                | xLblDef xName LBRACKET xSFExprList RBRACKET LBRACKET xSectionSubscriptList RBRACKET ASSIGN xExpr xEOS
{
  $$.pContext = adtFortranAssignmentStmt_create($1.pContext, $2.pContext, $10.pContext, $4.pContext, $7.pContext);
}
;

/* % R738 */
xWhereStmt : xLblDef WHERE LBRACKET xExpr RBRACKET xAssignmentStmt
{
  $$.pContext = adtFortranWhereStmt_create($1.pContext, $4.pContext, $6.pContext);
}
;

/* % R739 parallels if ... then ...elseif... else ... endif construct */
xWhereConstruct : xWhereConstructStmt xWhereRange
{
  $$.pContext = adtFortranWhereConstruct_create($1.pContext, $2.pContext);
}
;

xWhereRange : xEndWhereStmt
{
  $$.pContext = adtFortranWhereRange_create(0, 0, 0, $1.pContext);
}
            | xWhereBodyConstructBlock xEndWhereStmt
{
  $$.pContext = adtFortranWhereRange_create($1.pContext, 0, 0, $2.pContext);
}
            | xMaskedElsewhereConstruct
{
  $$.pContext = adtFortranWhereRange_create(0, 0, $1.pContext, 0);
}
            | xWhereBodyConstructBlock xMaskedElsewhereConstruct
{
  $$.pContext = adtFortranWhereRange_create($1.pContext, 0, $2.pContext, 0);
}
            | xElsewhereConstruct
{
  $$.pContext = adtFortranWhereRange_create(0, $1.pContext, 0, 0);
}
            | xWhereBodyConstructBlock xElsewhereConstruct
{
  $$.pContext = adtFortranWhereRange_create($1.pContext, $2.pContext, 0, 0);
}
;

xMaskedElsewhereConstruct : xMaskedElsewhereStmt xWhereRange
{
  $$.pContext = adtFortranMaskedElsewhereConstruct_create($1.pContext, $2.pContext);
}
;

xElsewhereConstruct : xElsewhereStmt xElsewherePart
{
  $$.pContext = adtFortranElsewhereConstruct_create($1.pContext, $2.pContext);
}
;

xElsewherePart : xEndWhereStmt
{
  $$.pContext = adtFortranElsewherePart_create(0, $1.pContext);
}
               | xWhereBodyConstructBlock xEndWhereStmt
{
  $$.pContext = adtFortranElsewherePart_create($2.pContext, $1.pContext);
}
;

xWhereBodyConstructBlock : xWhereBodyConstruct
{
  $$.pContext = adtFortranWhereBodyConstructBlock_create($1.pContext);
}
                         | xWhereBodyConstructBlock xWhereBodyConstruct
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

/* % R740 */
xWhereConstructStmt : xLblDef xName COLON WHERE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranWhereBodyConstructBlock_create($1.pContext);
}
                    | xLblDef WHERE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranWhereBodyConstructBlock_create($1.pContext);
}
;

/* % R741 */
xWhereBodyConstruct : xAssignmentStmt
{
  $$.pContext = adtFortranWhereBodyConstruct_create($1.pContext, 0, 0);
}
                    | xWhereStmt
{
  $$.pContext = adtFortranWhereBodyConstruct_create(0, $1.pContext, 0);
}
                    | xWhereConstruct
{
  $$.pContext = adtFortranWhereBodyConstruct_create(0, 0, $1.pContext);
}
;

/* % R744 */
xMaskedElsewhereStmt : xLblDef ELSEWHERE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranMaskedElsewhereStmt_create($1.pContext, $4.pContext, 0);
}
                     | xLblDef ELSEWHERE LBRACKET xExpr RBRACKET xName xEOS
{
  $$.pContext = adtFortranMaskedElsewhereStmt_create($1.pContext, $4.pContext, $6.pContext);
}
;

/* % R745 */
xElsewhereStmt : xLblDef ELSEWHERE xEOS
{
  $$.pContext = adtFortranElsewhereStmt_create($1.pContext, 0);
}
               | xLblDef ELSEWHERE xName xEOS
{
  $$.pContext = adtFortranElsewhereStmt_create($1.pContext, $3.pContext);
}
;

/* % R746 */
xEndWhereStmt : xLblDef ENDWHERE xEOS
{
  $$.pContext = adtFortranEndWhereStmt_create($1.pContext, 0);
}
              | xLblDef ENDWHERE xName xEOS
{
  $$.pContext = adtFortranEndWhereStmt_create($1.pContext, $3.pContext);
}
              | xLblDef END WHERE xEOS
{
  $$.pContext = adtFortranEndWhereStmt_create($1.pContext, 0);
}
              | xLblDef END WHERE xName xEOS
{
  $$.pContext = adtFortranEndWhereStmt_create($1.pContext, $4.pContext);
}
;

/* % R802 */
xIfConstruct : xIfThenStmt xThenPart
{
  $$.pContext = adtFortranIfConstruct_create($1.pContext, $2.pContext);
}
;

xThenPart : xEndIfStmt
{
  $$.pContext = adtFortranThenPart_create($1.pContext, 0, 0, 0);
}
          | xConditionalBody xEndIfStmt
{
  $$.pContext = adtFortranThenPart_create($2.pContext, $1.pContext, 0, 0);
}
          | xElseIfConstruct
{
  $$.pContext = adtFortranThenPart_create(0, 0, $1.pContext, 0);
}
          | xConditionalBody xElseIfConstruct
{
  $$.pContext = adtFortranThenPart_create(0, $1.pContext, $2.pContext, 0);
}
          | xElseConstruct
{
  $$.pContext = adtFortranThenPart_create(0, 0, 0, $1.pContext);
}
          | xConditionalBody xElseConstruct
{
  $$.pContext = adtFortranThenPart_create(0, $1.pContext, 0, $2.pContext);
}
;

xElseIfConstruct : xElseIfStmt xThenPart
{
  $$.pContext = adtFortranElseIfConstruct_create($1.pContext, $2.pContext);
}
;

xElseConstruct : xElseStmt xElsePart
{
  $$.pContext = adtFortranElseConstruct_create($1.pContext, $2.pContext);
}
;

xElsePart : xEndIfStmt
{
  $$.pContext = adtFortranElsePart_create($1.pContext, 0);
}
          | xConditionalBody xEndIfStmt
{
  $$.pContext = adtFortranElsePart_create($2.pContext, $1.pContext);
}
;

xConditionalBody : xExecutableConstruct
{
  $$.pContext = adtFortranConditionalBody_create($1.pContext);
}
                 | xConditionalBody xExecutableConstruct
{
  $$.pContext = adtFortranList_add($1.pContext, $2.pContext);
}
;

/* % R803 */
xIfThenStmt : xLblDef IF LBRACKET xExpr RBRACKET THEN xEOS
{
  $$.pContext = adtFortranIfThenStmt_create($1.pContext, $4.pContext, 0);
}
            | xLblDef xName COLON IF LBRACKET xExpr RBRACKET THEN xEOS
{
  $$.pContext = adtFortranIfThenStmt_create($1.pContext, $6.pContext, $2.pContext);
}
;

/* % R804 */
xElseIfStmt : xLblDef ELSEIF LBRACKET xExpr RBRACKET THEN xEOS
{
  $$.pContext = adtFortranElseIfStmt_create($1.pContext, $4.pContext, 0);
}
            | xLblDef ELSEIF LBRACKET xExpr RBRACKET THEN xName xEOS
{
  $$.pContext = adtFortranElseIfStmt_create($1.pContext, $4.pContext, $7.pContext);
}
            | xLblDef ELSE IF LBRACKET xExpr RBRACKET THEN xEOS
{
  $$.pContext = adtFortranElseIfStmt_create($1.pContext, $5.pContext, 0);
}
            | xLblDef ELSE IF LBRACKET xExpr RBRACKET THEN xName xEOS
{
  $$.pContext = adtFortranElseIfStmt_create($1.pContext, $5.pContext, $8.pContext);
}
;

/* % R805 */
xElseStmt : xLblDef ELSE xEOS
{
  $$.pContext = adtFortranElseStmt_create($1.pContext, 0);
}
          | xLblDef ELSE xName xEOS
{
  $$.pContext = adtFortranElseStmt_create($1.pContext, $3.pContext);
}
;

/* % R806 */
xEndIfStmt : xLblDef ENDIF xEOS
{
  $$.pContext = adtFortranEndIfStmt_create($1.pContext, 0);
}
           | xLblDef ENDIF xName xEOS
{
  $$.pContext = adtFortranEndIfStmt_create($1.pContext, $3.pContext);
}
           | xLblDef END IF xEOS
{
  $$.pContext = adtFortranEndIfStmt_create($1.pContext, 0);
}
           | xLblDef END IF xName xEOS
{
  $$.pContext = adtFortranEndIfStmt_create($1.pContext, $4.pContext);
}
;

/* % R807 */
xIfStmt : xLblDef IF LBRACKET xExpr RBRACKET xActionStmt
{
  $$.pContext = adtFortranIfStmt_create($1.pContext, $4.pContext, $6.pContext);
}
;

/* % R808 */
xCaseConstruct : xSelectCaseStmt xSelectCaseBody xEndSelectStmt
{
  $$.pContext = adtFortranCaseConstruct_create($1.pContext, $2.pContext, $3.pContext);
}
               | xSelectCaseStmt xEndSelectStmt
{
  $$.pContext = adtFortranCaseConstruct_create($1.pContext, 0, $2.pContext);
}
;

xSelectCaseBody : xCaseStmt
{
  $$.pContext = adtFortranSelectCaseBody_create($1.pContext, 0, 0);
}
                | xSelectCaseBody xCaseBodyConstruct
{
  $$.pContext = adtFortranSelectCaseBody_create(0, $1.pContext, $2.pContext);
}
;

xCaseBodyConstruct : xCaseStmt
{
  $$.pContext = adtFortranCaseBodyConstruct_create($1.pContext, 0);
}
                   | xExecutableConstruct
{
  $$.pContext = adtFortranCaseBodyConstruct_create(0, $1.pContext);
}
;

/* % R809 chain rule eliminated */
xSelectCaseStmt : xLblDef xName COLON SELECTCASE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranSelectCaseStmt_create($1.pContext, $2.pContext, $6.pContext);
}
                | xLblDef SELECTCASE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranSelectCaseStmt_create($1.pContext, 0, $4.pContext);
}
                | xLblDef xName COLON SELECT CASE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranSelectCaseStmt_create($1.pContext, $2.pContext, $7.pContext);
}
                | xLblDef SELECT CASE LBRACKET xExpr RBRACKET xEOS
{
  $$.pContext = adtFortranSelectCaseStmt_create($1.pContext, 0, $5.pContext);
}
;

/* % R810 */
xCaseStmt : xLblDef CASE xCaseSelector xEOS
{
  $$.pContext = adtFortranCaseStmt_create($1.pContext, $3.pContext, 0);
}
          | xLblDef CASE xCaseSelector xName xEOS
{
  $$.pContext = adtFortranCaseStmt_create($1.pContext, $3.pContext, $4.pContext);
}
;

/* % R811 */
xEndSelectStmt : xLblDef ENDSELECT xEOS
{
  $$.pContext = adtFortranEndSelectStmt_create($1.pContext, 0);
}
               | xLblDef ENDSELECT xName xEOS
{
  $$.pContext = adtFortranEndSelectStmt_create($1.pContext, $3.pContext);
}
               | xLblDef END SELECT xEOS
{
  $$.pContext = adtFortranEndSelectStmt_create($1.pContext, 0);
}
               | xLblDef END SELECT xName xEOS
{
  $$.pContext = adtFortranEndSelectStmt_create($1.pContext, $4.pContext);
}
;

/* % R813 */
xCaseSelector : LBRACKET xCaseValueRangeList RBRACKET
{
  $$.pContext = adtFortranCaseSelector_create($2.pContext);
}
              | DEFAULT
{
  $$.pContext = adtFortranCaseSelector_create(0);
}
;

xCaseValueRangeList : xCaseValueRange
{
  $$.pContext = adtFortranCaseValueRangeList_create($1.pContext);
}
                    | xCaseValueRangeList COMMA xCaseValueRange
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

/* % R814 */
xCaseValueRange : xExpr
{
  $$.pContext = adtFortranCaseValueRange_create($1.pContext, 0, 0);
}
                | xExpr COLON
{
  $$.pContext = adtFortranCaseValueRange_create($1.pContext, 0, 1);
}
                | COLON xExpr
{
  $$.pContext = adtFortranCaseValueRange_create(0, $2.pContext, 1);
}
                | xExpr COLON xExpr
{
  $$.pContext = adtFortranCaseValueRange_create($1.pContext, $3.pContext, 1);
}
;

/* % R816 */
xDoConstruct : xLblDef DO xLblRef COMMA xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $3.pContext, $5.pContext, 0, $7.pContext, $8.pContext, 1);
}
             | xLblDef DO xLblRef xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $3.pContext, $4.pContext, 0, $6.pContext, $7.pContext, 0);
}
             | xLblDef DO xLblRef xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $3.pContext, 0, 0, $5.pContext, $6.pContext, 0);
}
             | xLblDef DO COMMA xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, $4.pContext, 0, $6.pContext, $7.pContext, 1);
}
             | xLblDef DO xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, $3.pContext, 0, $5.pContext, $6.pContext, 0);
}
             | xLblDef DO xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, 0, 0, $4.pContext, $5.pContext, 0);
}
             | xLblDef xName COLON DO xLblRef COMMA xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $5.pContext, $7.pContext, $2.pContext, $9.pContext, $10.pContext, 1);
}
             | xLblDef xName COLON DO xLblRef xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $5.pContext, $6.pContext, $2.pContext, $8.pContext, $9.pContext, 0);
}
             | xLblDef xName COLON DO xLblRef xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, $5.pContext, 0, $2.pContext, $7.pContext, $8.pContext, 0);
}
             | xLblDef xName COLON DO COMMA xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, $6.pContext, $2.pContext, $8.pContext, $9.pContext, 1);
}
             | xLblDef xName COLON DO xLoopControl xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, $5.pContext, $2.pContext, $7.pContext, $8.pContext, 0);
}
             | xLblDef xName COLON DO xEOS xConditionalBody xEndDoStmt
{
  $$.pContext = adtFortranDoConstruct_create($1.pContext, 0, 0, $2.pContext, $6.pContext, $7.pContext, 0);
}
;

xLoopControl : xName ASSIGN xExpr COMMA xExpr
{
  $$.pContext = adtFortranLoopControl_create($1.pContext, $3.pContext, $5.pContext, 0);
}
             | xName ASSIGN xExpr COMMA xExpr COMMA xExpr
{
  $$.pContext = adtFortranLoopControl_create($1.pContext, $3.pContext, $5.pContext, $7.pContext);
}
             | WHILE LBRACKET xExpr RBRACKET
{
  $$.pContext = adtFortranLoopControl_create(0, $3.pContext, 0, 0);
}
;

/* % R825 */
xEndDoStmt : xLblDef ENDDO xEOS
{
  $$.pContext = adtFortranEndDoStmt_create($1.pContext, 0);
}
           | xLblDef ENDDO xName xEOS
{
  $$.pContext = adtFortranEndDoStmt_create($1.pContext, $3.pContext);
}
           | xLblDef END DO xEOS
{
  $$.pContext = adtFortranEndDoStmt_create($1.pContext, 0);
}
           | xLblDef END DO xName xEOS
{
  $$.pContext = adtFortranEndDoStmt_create($1.pContext, $4.pContext);
}
;

/* % R834 */
xCycleStmt : xLblDef CYCLE xEOS
{
  $$.pContext = adtFortranCycleStmt_create($1.pContext, 0);
}
           | xLblDef CYCLE xName xEOS
{
  $$.pContext = adtFortranCycleStmt_create($1.pContext, $3.pContext);
}
;

/* % R835 */
xExitStmt : xLblDef EXIT xEOS
{
  $$.pContext = adtFortranExitStmt_create($1.pContext, 0);
}
          | xLblDef EXIT xName xEOS
{
  $$.pContext = adtFortranExitStmt_create($1.pContext, $3.pContext);
}
;

xGotoStmt : xLblDef GOTO xLblRef xEOS
{
  $$.pContext = adtFortranGotoStmt_create($1.pContext, $3.pContext);
}
;

/* % R838 */
xArithmeticIfStmt : xLblDef IF LBRACKET xExpr RBRACKET xLblRef COMMA xLblRef COMMA xLblRef xEOS
{
  $$.pContext = adtFortranArithmeticIfStmt_create($1.pContext, $4.pContext, $6.pContext, $8.pContext, $10.pContext);
}
;

/* % R839 */
xContinueStmt : xLblDef CONTINUE xEOS
{
  $$.pContext = adtFortranContinueStmt_create($1.pContext);
}
;

/* % R1105 */
xModuleStmt : xLblDef MODULE xName xEOS
{
  $$.pContext = adtFortranModuleStmt_create($1.pContext, $3.pContext);
}
;

/* % R1106 */
xEndModuleStmt : xLblDef END xEOS
{
  $$.pContext = adtFortranEndModuleStmt_create($1.pContext, 0);
}
               | xLblDef ENDMODULE xEOS
{
  $$.pContext = adtFortranEndModuleStmt_create($1.pContext, 0);
}
               | xLblDef ENDMODULE xName xEOS
{
  $$.pContext = adtFortranEndModuleStmt_create($1.pContext, $3.pContext);
}
               | xLblDef END MODULE xEOS
{
  $$.pContext = adtFortranEndModuleStmt_create($1.pContext, 0);
}
               | xLblDef END MODULE xName xEOS
{
  $$.pContext = adtFortranEndModuleStmt_create($1.pContext, $4.pContext);
}
;

/* % R1107 */
xUseStmt : xLblDef USE xName xEOS
{
  $$.pContext = adtFortranUseStmt_create($1.pContext, $3.pContext);
}


/* % R520 */
xIntentStmt : xLblDef INTENT LBRACKET xIntentSpec RBRACKET xIntentNameList xEOS
{
  $$.pContext = adtFortranIntentStmt_create($1.pContext, $4.pContext, $6.pContext, 0);
}
            | xLblDef INTENT LBRACKET xIntentSpec RBRACKET COLON COLON xIntentNameList xEOS
{
  $$.pContext = adtFortranIntentStmt_create($1.pContext, $4.pContext, $8.pContext, 1);
}
;

xIntentSpec : IN
{
  $$.pContext = adtFortranIntentSpec_create(0);
}
            | OUT
{
  $$.pContext = adtFortranIntentSpec_create(1);
}
            | INOUT
{
  $$.pContext = adtFortranIntentSpec_create(2);
}
            | IN OUT
{
  $$.pContext = adtFortranIntentSpec_create(3);
}
;

/* % R1209 */
xIntrinsicStmt : xLblDef INTRINSIC xNameList xEOS
{
  $$.pContext = adtFortranIntrinsicStmt_create($1.pContext, $3.pContext);
}
               | xLblDef INTRINSIC COLON COLON xNameList xEOS
{
  $$.pContext = adtFortranIntrinsicStmt_create($1.pContext, $5.pContext);
}
;

xExternalStmt : xLblDef EXTERNAL xNameList xEOS
{
  $$.pContext = adtFortranExternalStmt_create($1.pContext, $3.pContext, 0);
}
              | xLblDef EXTERNAL COLON COLON xNameList xEOS
{
  $$.pContext = adtFortranExternalStmt_create($1.pContext, $5.pContext, 1);
}
;

/* % R1211 */
xCallStmt : xLblDef CALL xName xEOS
{
  $$.pContext = adtFortranCallStmt_create($1.pContext, $3.pContext, 0);
}
          | xLblDef CALL xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranCallStmt_create($1.pContext, $3.pContext, 0);
}
          | xLblDef CALL xName LBRACKET xSectionSubscriptList RBRACKET xEOS
{
  $$.pContext = adtFortranCallStmt_create($1.pContext, $3.pContext, $5.pContext);
}
;

/* % R1217 chain rule deleted */
xFunctionStmt : xLblDef FUNCTION xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $3.pContext, 0, 1, 0, 0);
}
              | xLblDef FUNCTION xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $3.pContext, $5.pContext, 0, 0, 0);
}
              | xLblDef xTypeSpec FUNCTION xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $4.pContext, 0, 1, 0, 0);
}
              | xLblDef xTypeSpec FUNCTION xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $4.pContext, $6.pContext, 0, 0, 0);
}
              | xLblDef xTypeSpec RECURSIVE FUNCTION xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $5.pContext, 0, 1, 1, 0);
}
              | xLblDef xTypeSpec RECURSIVE FUNCTION xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $5.pContext, $7.pContext, 0, 1, 0);
}
              | xLblDef RECURSIVE xTypeSpec FUNCTION xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $3.pContext, $5.pContext, 0, 1, 1, 0);
}
              | xLblDef RECURSIVE xTypeSpec FUNCTION xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $3.pContext, $5.pContext, $7.pContext, 0, 1, 0);
}
              | xLblDef RECURSIVE FUNCTION xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $4.pContext, 0, 1, 1, 0);
}
              | xLblDef RECURSIVE FUNCTION xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $4.pContext, $6.pContext, 0, 1, 0);
}
              | xLblDef FUNCTION xName LBRACKET RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $3.pContext, 0, 1, 0, $8.pContext);
}
              | xLblDef FUNCTION xName LBRACKET xNameList RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $3.pContext, $5.pContext, 0, 0, $9.pContext);
}
              | xLblDef xTypeSpec FUNCTION xName LBRACKET RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $4.pContext, 0, 1, 0, $9.pContext);
}
              | xLblDef xTypeSpec FUNCTION xName LBRACKET xNameList RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $4.pContext, $6.pContext, 0, 0, $10.pContext);
}
              | xLblDef xTypeSpec RECURSIVE FUNCTION xName LBRACKET RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $5.pContext, 0, 1, 1, $10.pContext);
}
              | xLblDef xTypeSpec RECURSIVE FUNCTION xName LBRACKET xNameList RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $2.pContext, $5.pContext, $7.pContext, 0, 1, $11.pContext);
}
              | xLblDef RECURSIVE xTypeSpec FUNCTION xName LBRACKET RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $3.pContext, $5.pContext, 0, 1, 1, $10.pContext);
}
              | xLblDef RECURSIVE xTypeSpec FUNCTION xName LBRACKET xNameList RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, $3.pContext, $5.pContext, $7.pContext, 0, 1, $11.pContext);
}
              | xLblDef RECURSIVE FUNCTION xName LBRACKET RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $4.pContext, 0, 1, 1, $9.pContext);
}
              | xLblDef RECURSIVE FUNCTION xName LBRACKET xNameList RBRACKET RESULT LBRACKET xName RBRACKET xEOS
{
  $$.pContext = adtFortranFunctionStmt_create($1.pContext, 0, $4.pContext, $6.pContext, 0, 1, $10.pContext);
}
;

xLblRef : XICON
{
  $$.pContext = adtFortranLblRef_create($1.sValue);
}
;

xName : XNAME
{
  $$.pContext = adtFortranName_create($1.sValue);
}
;

xNameList : xName
{
  $$.pContext = adtFortranNameList_create($1.pContext);
}
          | xNameList COMMA xName
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xIntentNameList : xIntentName
{
  $$.pContext = adtFortranNameList_create($1.pContext);
}
                | xIntentNameList COMMA xIntentName
{
  $$.pContext = adtFortranList_add($1.pContext, $3.pContext);
}
;

xIntentName : XNAME
{
  $$.pContext = adtFortranName_create($1.sValue);
}
            | XNAME LBRACKET xShapeSpecList RBRACKET
{
  $$.pContext = adtFortranName_create($1.sValue);

  /* Ignore the shape info in intent statments */
  adtFortran_releaseObject($3.pContext);
}
;

/* % R1220 */
xEndFunctionStmt : xLblDef END xEOS
{
  $$.pContext = adtFortranEndFunctionStmt_create($1.pContext, 0);
}
                 | xLblDef ENDFUNCTION xEOS
{
  $$.pContext = adtFortranEndFunctionStmt_create($1.pContext, 0);
}
                 | xLblDef ENDFUNCTION xName xEOS
{
  $$.pContext = adtFortranEndFunctionStmt_create($1.pContext, $3.pContext);
}
                 | xLblDef END FUNCTION xEOS
{
  $$.pContext = adtFortranEndFunctionStmt_create($1.pContext, 0);
}
                 | xLblDef END FUNCTION xName xEOS
{
  $$.pContext = adtFortranEndFunctionStmt_create($1.pContext, $4.pContext);
}
;

/* % R1222 */
xSubroutineStmt : xLblDef SUBROUTINE xName xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $3.pContext, 0, 0, 0);
}
                | xLblDef RECURSIVE SUBROUTINE xName xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $4.pContext, 0, 0, 0);
}
                | xLblDef SUBROUTINE xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $3.pContext, 0, 1, 0);
}
                | xLblDef SUBROUTINE xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $3.pContext, $5.pContext, 0, 0);
}
                | xLblDef RECURSIVE SUBROUTINE xName LBRACKET RBRACKET xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $4.pContext, 0, 1, 1);
}
                | xLblDef RECURSIVE SUBROUTINE xName LBRACKET xNameList RBRACKET xEOS
{
  $$.pContext = adtFortranSubroutineStmt_create($1.pContext, $4.pContext, $6.pContext, 0, 1);
}
;

/* % R1224 */
xEndSubroutineStmt : xLblDef END xEOS
{
  $$.pContext = adtFortranEndSubroutineStmt_create($1.pContext, 0);
}
                   | xLblDef ENDSUBROUTINE xEOS
{
  $$.pContext = adtFortranEndSubroutineStmt_create($1.pContext, 0);
}
                   | xLblDef ENDSUBROUTINE xName xEOS
{
  $$.pContext = adtFortranEndSubroutineStmt_create($1.pContext, $3.pContext);
}
                   | xLblDef END SUBROUTINE xEOS
{
  $$.pContext = adtFortranEndSubroutineStmt_create($1.pContext, 0);
}
                   | xLblDef END SUBROUTINE xName xEOS
{
  $$.pContext = adtFortranEndSubroutineStmt_create($1.pContext, $4.pContext);
}
;

/* % R1226 */
xReturnStmt : xLblDef RETURN xEOS
{
  $$.pContext = adtFortranReturnStmt_create($1.pContext, 0);
}
            | xLblDef RETURN xExpr xEOS
{
  $$.pContext = adtFortranReturnStmt_create($1.pContext, $3.pContext);
}
;

xLblDef :
{
  $$.pContext = adtFortranLblDef_create(0, yyFortran_LastComment());
}
        | xIcon
{
  $$.pContext = adtFortranLblDef_create($1.pContext, $1.sComment);
}
;

xIcon : XICON
{
  $$.pContext = adtFortranIcon_create($1.sValue);
}
 | XICON_S
{
  $$.pContext = adtFortranIcon_create($1.sValue);
}
;

xRcon : XRCON
{
  $$.pContext = adtFortranRcon_create($1.sValue);
}
 | XRCON_S
{
  $$.pContext = adtFortranRcon_create($1.sValue);
}
;

xScon : XSCON
{
  $$.pContext = adtFortranScon_create($1.sValue);
}
;

xImpl : XIMPL
{
  $$.pContext = adtFortranImpl_create($1.sValue);
}
;
