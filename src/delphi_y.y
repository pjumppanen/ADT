%{
/*
 * delphi.y
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
 * delphi grammar in Yacc format, based on BNF given
 * in "BORLAND Delphi 6.0 Object Pascal Language Guide -- Appendix A".
 *
 */

#include <stdio.h>
#include "lexer.h"
#include "adtdelphi.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   delphiType

%}

/* Object pascal keyword tokens */
%token ABSOLUTE AND ANSISTRING ARRAY AS B_BEGIN BOOLEAN BYTE CASE CDECL CHAR CLASS
%token COMP CONST CONSTRUCTOR CONTAINS CURRENCY DEFAULT DESTRUCTOR DIV DO DOUBLE
%token DOWNTO DYNAMIC ELSE B_END EXPORT EXTENDED EXTERNAL FAR P_FILE FINALIZATION
%token FOR FORWARD FUNCTION GOTO IF IMPLEMENTATION IMPLEMENTS IN INDEX INHERITED
%token INITIALIZATION INT64 INTEGER INTERFACE IS LABEL LIBRARY LONGINT LONGWORD
%token MESSAGE MOD NIL NODEFAULT NOT OBJECT OF OLEVARIANT OR OUT OVERLOAD OVERRIDE
%token PACKAGE PACKED PASCAL PCHAR PRIVATE PROCEDURE PROGRAM PROPERTY PROTECTED
%token PUBLIC PUBLISHED READ REAL REAL48 RECORD REGISTER REINTRODUCE REPEAT REQUIRES
%token SAFECALL SET SHL SHORTINT SHR SINGLE SIZEOF SMALLINT STDCALL STORED STRING THEN
%token TO TYPE UNIT UNTIL USES VAR VARIANT VIRTUAL WHILE WIDECHAR WIDESTRING WITH
%token WORD WRITE XOR EXIT POINTER

/* Object pascal special character tokens */
%token COMMA SEMICOLON COLON ASSIGNMENT PLUS_EQUALS MINUS_EQUALS TIMES_EQUALS DIV_EQUALS
%token EQUALS DOT RANGE LPARENTHESIS RPARENTHESIS LBRACKET RBRACKET AT HAT PLUS MINUS
%token GT LT GE LE NE MULTIPLY DIVIDE

/* Object pascal input tokens */
%token IDENTIFIER BOOL_NUMBER INT_NUMBER REAL_NUMBER TEXT

/* Other tokens */
%token SINGLELINE_COMMENT MULTILINE_COMMENT EMBEDDED_COMMANDS

/* Tokens added to support parsing our delphi macros*/
%token ADDVARIABLES


%nonassoc THEN
%nonassoc ELSE


%%
Goal : Program
{
  void* pObj;

  pObj        = adtDelphiGoal_create($1.pContext);
  $$.pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
     | Package
{
  void* pObj;

  pObj        = adtDelphiGoal_create($1.pContext);
  $$.pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
     | Library
{
  void* pObj;

  pObj        = adtDelphiGoal_create($1.pContext);
  $$.pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
     | Unit
{
  void* pObj;

  pObj        = adtDelphiGoal_create($1.pContext);
  $$.pContext = adtDelphi_setRoot(pObj);

  adtDelphi_releaseObject(pObj);
}
     | Macro
{
  $$.pContext = adtDelphiList_add(adtDelphi_getRoot(), $1.pContext);
}
;

/* The Expression case with SEMICOLON trailing creates a reduce reduce conflict
   but without it the macro compiler flags errors when it shouldn't. It seems to
   work correctly with this problem so I think we can safely ignore this issue.
   It should only affect the parsing of macros and not the delphi code in general.*/
Macro : Ident LPARENTHESIS ExprList RPARENTHESIS Expression
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, $5.pContext, 0, 0);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS Expression SEMICOLON
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, $5.pContext, 0, 0);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, 0);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList SEMICOLON
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, 0);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList ADDVARIABLES VarDeclList
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, $7.pContext);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList ADDVARIABLES VarDeclList SEMICOLON
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, $7.pContext);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList SEMICOLON ADDVARIABLES VarDeclList
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, $8.pContext);
}
      | Ident LPARENTHESIS ExprList RPARENTHESIS StmtList SEMICOLON ADDVARIABLES VarDeclList SEMICOLON
{
  $$.pContext = adtDelphiMacro_create($1.pContext, $3.pContext, 0, $5.pContext, $8.pContext);
}
;

Program : PROGRAM Ident LPARENTHESIS IdentList RPARENTHESIS SEMICOLON UsesClause Block DOT
{
  $$.pContext = adtDelphiProgram_create($2.pContext, $4.pContext, $7.pContext, $8.pContext, $1.sComment);
}
        | PROGRAM Ident SEMICOLON UsesClause Block DOT
{
  $$.pContext = adtDelphiProgram_create($2.pContext, 0, $4.pContext, $5.pContext, $1.sComment);
}
        | UsesClause Block DOT
{
  $$.pContext = adtDelphiProgram_create(0, 0, $1.pContext, $2.pContext, $1.sComment);
}
;

Unit : UNIT Ident SEMICOLON InterfaceSection ImplementationSection InitSection DOT
{
  $$.pContext = adtDelphiUnit_create($2.pContext, $4.pContext, $5.pContext, $6.pContext, $1.sComment);
}
;

Package : PACKAGE Ident SEMICOLON B_END DOT
{
  $$.pContext = adtDelphiPackage_create($2.pContext, 0, 0, $1.sComment);
}
        | PACKAGE Ident SEMICOLON CONTAINS IdentList SEMICOLON B_END DOT
{
  $$.pContext = adtDelphiPackage_create($2.pContext, 0, $5.pContext, $1.sComment);
}
        | PACKAGE Ident SEMICOLON REQUIRES IdentList SEMICOLON B_END DOT
{
  $$.pContext = adtDelphiPackage_create($2.pContext, $5.pContext, 0, $1.sComment);
}
        | PACKAGE Ident SEMICOLON REQUIRES IdentList SEMICOLON CONTAINS IdentList SEMICOLON B_END DOT
{
  $$.pContext = adtDelphiPackage_create($2.pContext, $5.pContext, $8.pContext, $1.sComment);
}
;

Library : LIBRARY Ident SEMICOLON UsesClause Block DOT
{
  $$.pContext = adtDelphiLibrary_create($2.pContext, $4.pContext, $5.pContext, $1.sComment);
}
;

UsesClause : USES IdentList SEMICOLON
{
  $$.pContext = adtDelphiUsesClause_create($2.pContext, $1.sComment);
}
           |
{
  $$.pContext = 0;
}
;

InterfaceSection : INTERFACE UsesClause ConstSection TypeSection VarSection ExportedHeadingList
{
  $$.pContext = adtDelphiInterfaceSection_create($2.pContext, $3.pContext, $4.pContext, $5.pContext, $6.pContext, $1.sComment);
}
                 | INTERFACE UsesClause ConstSection TypeSection VarSection
{
  $$.pContext = adtDelphiInterfaceSection_create($2.pContext, $3.pContext, $4.pContext, $5.pContext, 0, $1.sComment);
}
                 |
{
  $$.pContext = 0;
}
;

ExportedHeadingList : ExportedHeadingList ExportedHeading
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                    | ExportedHeading
{
  $$.pContext = adtDelphiExportedHeadingList_create($1.pContext);
}
;

ExportedHeading : ProcedureHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiExportedHeading_create($1.pContext, 0, $3.pContext, $1.sComment);
}
                | FunctionHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiExportedHeading_create(0, $1.pContext, $3.pContext, $1.sComment);
}
                | ProcedureHeading SEMICOLON
{
  $$.pContext = adtDelphiExportedHeading_create($1.pContext, 0, 0, $1.sComment);
}
                | FunctionHeading SEMICOLON
{
  $$.pContext = adtDelphiExportedHeading_create(0, $1.pContext, 0, $1.sComment);
}
;

ImplementationSection : IMPLEMENTATION UsesClause DeclSection
{
  $$.pContext = adtDelphiImplementationSection_create($2.pContext, $3.pContext, $1.sComment);
}
                      |
{
  $$.pContext = 0;
}
;

Block : DeclSection CompoundStmt
{
  $$.pContext = adtDelphiBlock_create($1.pContext, $2.pContext, $1.sComment);
}
;

DeclSection : LabelDeclSection ConstSection TypeSection VarSection ProcedureDeclSection
{
  $$.pContext = adtDelphiDeclSection_create($1.pContext, $2.pContext, $3.pContext, $4.pContext, $5.pContext, $1.sComment);
}
;

LabelDeclSection : LabelDeclList
{
  $$.pContext = adtDelphiLabelDeclSection_create($1.pContext);
}
                 |
{
  $$.pContext = 0;
}
;

LabelDeclList : LabelDeclList LabelDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
              | LabelDecl
{
  $$.pContext = adtDelphiLabelDeclList_create($1.pContext);
}
;

LabelDecl : LABEL LabelId SEMICOLON
{
  $$.pContext = adtDelphiLabelDecl_create($2.pContext, $1.sComment);
}
;

ConstSection : CONST ConstantDeclList
{
  $$.pContext = adtDelphiConstSection_create($2.pContext, $1.sComment);
}
             |
{
  $$.pContext = 0;
}
;

ConstantDeclList : ConstantDeclList ConstantDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                 | ConstantDecl
{
  $$.pContext = adtDelphiConstantDeclList_create($1.pContext);
}
;

ConstantDecl : Ident EQUALS ConstExpr SEMICOLON
{
  $$.pContext = adtDelphiConstantDecl_create($1.pContext, 0, 0, $3.pContext, 0);
}
             | TypeId COLON Ident EQUALS TypedConstant SEMICOLON
{
  $$.pContext = adtDelphiConstantDecl_create($3.pContext, $1.pContext, 0, 0, $5.pContext);
}
             | TypeId COLON UnitId DOT Ident EQUALS TypedConstant SEMICOLON
{
  $$.pContext = adtDelphiConstantDecl_create($5.pContext, $3.pContext, $1.pContext, 0, $7.pContext);
}
;

TypeSection : TYPE TypeDeclList
{
  $$.pContext = adtDelphiTypeSection_create($2.pContext, $1.sComment);
}
            |
{
  $$.pContext = 0;
}
;

TypeDeclList : TypeDeclList TypeDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
             | TypeDecl
{
  $$.pContext = adtDelphiTypeDeclList_create($1.pContext);
}
;

TypeDeclBegin : Ident EQUALS
{
  adtDelphi_setTypeScope($1.pContext);

  $$.pContext = $1.pContext;
}
;

TypeDecl : TypeDeclBegin Type SEMICOLON
{
  $$.pContext = adtDelphiTypeDecl_create($1.pContext, $2.pContext, 0);

  adtDelphi_clearTypeScope();
}
         | TypeDeclBegin RestrictedType SEMICOLON
{
  $$.pContext = adtDelphiTypeDecl_create($1.pContext, 0, $2.pContext);

  adtDelphi_clearTypeScope();
}
;

TypedConstant : ConstExpr
{
  $$.pContext = adtDelphiTypedConstant_create($1.pContext, 0, 0);
}
              | ArrayConstant
{
  $$.pContext = adtDelphiTypedConstant_create(0, $1.pContext, 0);
}
              | RecordConstant
{
  $$.pContext = adtDelphiTypedConstant_create(0, 0, $1.pContext);
}
;

ArrayConstant : LPARENTHESIS TypedConstantList RPARENTHESIS
{
  $$.pContext = adtDelphiArrayConstant_create($2.pContext);
}
;

TypedConstantList : TypedConstantList COMMA TypedConstant
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                  | TypedConstant
{
  $$.pContext = adtDelphiTypedConstantList_create($1.pContext);
}
;

RecordConstant : LPARENTHESIS RecordFieldConstantList RPARENTHESIS
{
  $$.pContext = adtDelphiRecordConstant_create($2.pContext);
}
;

RecordFieldConstantList : RecordFieldConstantList SEMICOLON RecordFieldConstant
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                        | RecordFieldConstant
{
  $$.pContext = adtDelphiRecordFieldConstantList_create($1.pContext);
}
;

RecordFieldConstant : Ident COLON TypedConstant
{
  $$.pContext = adtDelphiRecordFieldConstant_create($1.pContext, $3.pContext);
}
;

Type : TypeId
{
  $$.pContext = adtDelphiType_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
     | UnitId DOT TypeId
{
  $$.pContext = adtDelphiType_create($3.pContext, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
     | SimpleType
{
  $$.pContext = adtDelphiType_create(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
     | StructType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
     | PointerType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
     | StringType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
     | ProcedureType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
     | VariantType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, 0, $1.pContext, 0);
}
     | ClassRefType
{
  $$.pContext = adtDelphiType_create(0, 0, 0, 0, 0, 0, 0, 0, $1.pContext);
}
;

RestrictedType : ObjectType
{
  $$.pContext = adtDelphiRestrictedType_create($1.pContext, 0, 0);
}
               | ClassType
{
  $$.pContext = adtDelphiRestrictedType_create(0, $1.pContext, 0);
}
               | InterfaceType
{
  $$.pContext = adtDelphiRestrictedType_create(0, 0, $1.pContext);
}
;

ClassRefType : CLASS OF TypeId
{
  $$.pContext = adtDelphiClassRefType_create($3.pContext, 0);
}
             | CLASS OF UnitId DOT TypeId
{
  $$.pContext = adtDelphiClassRefType_create($5.pContext, $3.pContext);
}
;

SimpleType : OrdinalType
{
  $$.pContext = adtDelphiSimpleType_create($1.pContext, 0);
}
           | RealType
{
  $$.pContext = adtDelphiSimpleType_create(0, $1.pContext);
}
;

RealType : REAL48
{
  $$.pContext = adtDelphiRealType_create(0);
}
         | REAL
{
  $$.pContext = adtDelphiRealType_create(1);
}
         | SINGLE
{
  $$.pContext = adtDelphiRealType_create(2);
}
         | DOUBLE
{
  $$.pContext = adtDelphiRealType_create(3);
}
         | EXTENDED
{
  $$.pContext = adtDelphiRealType_create(4);
}
         | CURRENCY
{
  $$.pContext = adtDelphiRealType_create(5);
}
         | COMP
{
  $$.pContext = adtDelphiRealType_create(6);
}
;

OrdinalType : SubrangeType
{
  $$.pContext = adtDelphiOrdinalType_create($1.pContext, 0, 0);
}
            | EnumeratedType
{
  $$.pContext = adtDelphiOrdinalType_create(0, $1.pContext, 0);
}
            | OrdIdent
{
  $$.pContext = adtDelphiOrdinalType_create(0, 0, $1.pContext);
}
;

OrdIdent : SHORTINT
{
  $$.pContext = adtDelphiOrdIdent_create(0);
}
         | SMALLINT
{
  $$.pContext = adtDelphiOrdIdent_create(1);
}
         | INTEGER
{
  $$.pContext = adtDelphiOrdIdent_create(2);
}
         | BYTE
{
  $$.pContext = adtDelphiOrdIdent_create(3);
}
         | LONGINT
{
  $$.pContext = adtDelphiOrdIdent_create(4);
}
         | INT64
{
  $$.pContext = adtDelphiOrdIdent_create(5);
}
         | WORD
{
  $$.pContext = adtDelphiOrdIdent_create(6);
}
         | BOOLEAN
{
  $$.pContext = adtDelphiOrdIdent_create(7);
}
         | CHAR
{
  $$.pContext = adtDelphiOrdIdent_create(8);
}
         | WIDECHAR
{
  $$.pContext = adtDelphiOrdIdent_create(9);
}
         | LONGWORD
{
  $$.pContext = adtDelphiOrdIdent_create(10);
}
         | PCHAR
{
  $$.pContext = adtDelphiOrdIdent_create(11);
}
         | POINTER
{
  $$.pContext = adtDelphiOrdIdent_create(12);
}
;

VariantType : VARIANT
{
  $$.pContext = adtDelphiVariantType_create(0);
}
            | OLEVARIANT
{
  $$.pContext = adtDelphiVariantType_create(1);
}
;

SubrangeType : ConstExpr RANGE ConstExpr
{
  $$.pContext = adtDelphiSubrangeType_create($1.pContext, $3.pContext);
}
;

EnumeratedType : LPARENTHESIS EnumeratedTypeElementList RPARENTHESIS
{
  $$.pContext = adtDelphiEnumeratedType_create($2.pContext);
}
;

EnumeratedTypeElementList : EnumeratedTypeElementList COMMA EnumeratedTypeElement
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                          | EnumeratedTypeElement
{
  $$.pContext = adtDelphiEnumeratedTypeElementList_create($1.pContext);
}
;

EnumeratedTypeElement : Ident EQUALS ConstExpr
{
  $$.pContext = adtDelphiEnumeratedTypeElement_create($1.pContext, $3.pContext);
}
                      | Ident
{
  $$.pContext = adtDelphiEnumeratedTypeElement_create($1.pContext, 0);
}
;

StringType : STRING
{
  $$.pContext = adtDelphiStringType_create(0, 0);
}
           | ANSISTRING
{
  $$.pContext = adtDelphiStringType_create(1, 0);
}
           | WIDESTRING
{
  $$.pContext = adtDelphiStringType_create(2, 0);
}
           | STRING LBRACKET ConstExpr RBRACKET
{
  $$.pContext = adtDelphiStringType_create(0, $3.pContext);
}
;

StructType : PACKED ArrayType
{
  $$.pContext = adtDelphiStructType_create(1, $1.pContext, 0, 0, 0);
}
           | PACKED SetType
{
  $$.pContext = adtDelphiStructType_create(1, 0, $1.pContext, 0, 0);
}
           | PACKED FileType
{
  $$.pContext = adtDelphiStructType_create(1, 0, 0, $1.pContext, 0);
}
           | PACKED RecType
{
  $$.pContext = adtDelphiStructType_create(1, 0, 0, 0, $1.pContext);
}
           | ArrayType
{
  $$.pContext = adtDelphiStructType_create(0, $1.pContext, 0, 0, 0);
}
           | SetType
{
  $$.pContext = adtDelphiStructType_create(0, 0, $1.pContext, 0, 0);
}
           | FileType
{
  $$.pContext = adtDelphiStructType_create(0, 0, 0, $1.pContext, 0);
}
           | RecType
{
  $$.pContext = adtDelphiStructType_create(0, 0, 0, 0, $1.pContext);
}
;

ArrayType : ARRAY LBRACKET OrdinalTypeList RBRACKET OF Type
{
  $$.pContext = adtDelphiArrayType_create($3.pContext, $6.pContext);
}
          | ARRAY OF Type
{
  $$.pContext = adtDelphiArrayType_create(0, $3.pContext);
}
;

OrdinalTypeList : OrdinalTypeList COMMA OrdinalType
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                | OrdinalType
{
  $$.pContext = adtDelphiOrdinalTypeList_create($1.pContext);
}
;

RecType : RECORD FieldDeclList B_END
{
  $$.pContext = adtDelphiRecType_create($2.pContext, 0);
}
        | RECORD FieldDeclList SEMICOLON B_END
{
  $$.pContext = adtDelphiRecType_create($2.pContext, 0);
}
        | RECORD FieldDeclList VariantSectionList B_END
{
  $$.pContext = adtDelphiRecType_create($2.pContext, $3.pContext);
}
        | RECORD FieldDeclList VariantSectionList SEMICOLON B_END
{
  $$.pContext = adtDelphiRecType_create($2.pContext, $3.pContext);
}
        | RECORD B_END
{
  $$.pContext = adtDelphiRecType_create(0, 0);
}
;

FieldDeclList : FieldDeclList SEMICOLON FieldDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
              | FieldDecl
{
  $$.pContext = adtDelphiFieldDeclList_create($1.pContext);
}
;

FieldDecl : IdentList COLON Type
{
  $$.pContext = adtDelphiFieldDecl_create($1.pContext, $3.pContext);
}
;

VariantSectionList : VariantSectionList VariantSection
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                   | VariantSection
{
  $$.pContext = adtDelphiVariantSectionList_create($1.pContext);
}
;

VariantSection : CASE Ident COLON TypeId OF RecVariant SEMICOLON
{
  $$.pContext = adtDelphiVariantSection_create($2.pContext, 0, $4.pContext, $6.pContext);
}
               | CASE Ident COLON UnitId DOT TypeId OF RecVariant SEMICOLON
{
  $$.pContext = adtDelphiVariantSection_create($2.pContext, $4.pContext, $6.pContext, $8.pContext);
}
               | CASE TypeId OF RecVariant SEMICOLON
{
  $$.pContext = adtDelphiVariantSection_create(0, 0, $2.pContext, $4.pContext);
}
               | CASE UnitId DOT TypeId OF RecVariant SEMICOLON
{
  $$.pContext = adtDelphiVariantSection_create(0, $2.pContext, $4.pContext, $6.pContext);
}
;

RecVariant : ConstExprList COLON LPARENTHESIS FieldDeclList RPARENTHESIS
{
  $$.pContext = adtDelphiRecVariant_create($1.pContext, $4.pContext, 0);
}
           | ConstExprList COLON LPARENTHESIS FieldDeclList SEMICOLON RPARENTHESIS
{
  $$.pContext = adtDelphiRecVariant_create($1.pContext, $4.pContext, 0);
}
           | ConstExprList COLON LPARENTHESIS FieldDeclList VariantSectionList RPARENTHESIS
{
  $$.pContext = adtDelphiRecVariant_create($1.pContext, $4.pContext, $5.pContext);
}
           | ConstExprList COLON LPARENTHESIS FieldDeclList VariantSectionList SEMICOLON RPARENTHESIS
{
  $$.pContext = adtDelphiRecVariant_create($1.pContext, $4.pContext, $5.pContext);
}
           | ConstExprList COLON LPARENTHESIS RPARENTHESIS
{
  $$.pContext = adtDelphiRecVariant_create($1.pContext, 0, 0);
}
;

ConstExprList : ConstExprList COMMA ConstExpr
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
              | ConstExpr
{
  $$.pContext = adtDelphiConstExprList_create($1.pContext);
}
;

SetType : SET OF OrdinalType
{
  $$.pContext = adtDelphiSetType_create($3.pContext);
}
;

FileType : P_FILE OF TypeId
{
  $$.pContext = adtDelphiFileType_create(0, $3.pContext);
}
         | P_FILE OF UnitId DOT TypeId
{
  $$.pContext = adtDelphiFileType_create($3.pContext, $5.pContext);
}
;

PointerType : HAT TypeId
{
  $$.pContext = adtDelphiPointerType_create(0, $2.pContext);
}
            | HAT UnitId DOT TypeId
{
  $$.pContext = adtDelphiPointerType_create($2.pContext, $4.pContext);
}
;

ProcedureType : ProcedureHeading OF OBJECT
{
  $$.pContext = adtDelphiProcedureType_create($1.pContext, 0, 1);
}
              | ProcedureHeading
{
  $$.pContext = adtDelphiProcedureType_create($1.pContext, 0, 0);
}
              | FunctionHeading OF OBJECT
{
  $$.pContext = adtDelphiProcedureType_create(0, $1.pContext, 1);
}
              | FunctionHeading
{
  $$.pContext = adtDelphiProcedureType_create(0, $1.pContext, 0);
}
;

VarSection : VAR VarDeclList
{
  $$.pContext = adtDelphiVarSection_create($2.pContext, $1.sComment);
}
           |
{
  $$.pContext = 0;
}
;

VarDeclList : VarDeclList VarDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
            | VarDecl
{
  $$.pContext = adtDelphiVarDeclList_create($1.pContext);
}
;

VarDecl : IdentList COLON Type ABSOLUTE Ident SEMICOLON
{
  $$.pContext = adtDelphiVarDecl_create($1.pContext, $3.pContext, $5.pContext, 0, 1);
}
        | IdentList COLON Type ABSOLUTE ConstExpr SEMICOLON
{
  $$.pContext = adtDelphiVarDecl_create($1.pContext, $3.pContext, 0, $5.pContext, 1);
}
        | IdentList COLON Type EQUALS Ident SEMICOLON
{
  $$.pContext = adtDelphiVarDecl_create($1.pContext, $3.pContext, $5.pContext, 0, 0);
}
        | IdentList COLON Type EQUALS ConstExpr SEMICOLON
{
  $$.pContext = adtDelphiVarDecl_create($1.pContext, $3.pContext, 0, $5.pContext, 0);
}
        | IdentList COLON Type SEMICOLON
{
  $$.pContext = adtDelphiVarDecl_create($1.pContext, $3.pContext, 0, 0, 0);
}
;

Expression : ExpressionRelOpList
{
  $$.pContext = adtDelphiExpression_create($1.pContext);
}
;

ExpressionRelOpList : ExpressionRelOpList GT SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(1, $3.pContext));
}
                    | ExpressionRelOpList LT SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(2, $3.pContext));
}
                    | ExpressionRelOpList LE SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(3, $3.pContext));
}
                    | ExpressionRelOpList GE SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(4, $3.pContext));
}
                    | ExpressionRelOpList NE SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(5, $3.pContext));
}
                    | ExpressionRelOpList IN SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(6, $3.pContext));
}
                    | ExpressionRelOpList IS SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(7, $3.pContext));
}
                    | ExpressionRelOpList AS SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(8, $3.pContext));
}
                    | ExpressionRelOpList EQUALS SimpleExpression
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiExpressionRelOp_create(9, $3.pContext));
}
                    | SimpleExpression
{
  $$.pContext = adtDelphiExpressionRelOpList_create(adtDelphiExpressionRelOp_create(0, $1.pContext));
}
;

SimpleExpression : SimpleExpressionAddOpList
{
  $$.pContext = adtDelphiSimpleExpression_create($1.pContext);
}
;

SimpleExpressionAddOpList : SimpleExpressionAddOpList PLUS PLUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(1, 1, $4.pContext));
}
                          | SimpleExpressionAddOpList MINUS PLUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(2, 1, $4.pContext));
}
                          | SimpleExpressionAddOpList OR PLUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(3, 1, $4.pContext));
}
                          | SimpleExpressionAddOpList XOR PLUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(4, 1, $4.pContext));
}
                          | SimpleExpressionAddOpList PLUS MINUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(1, 2, $4.pContext));
}
                          | SimpleExpressionAddOpList MINUS MINUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(2, 2, $4.pContext));
}
                          | SimpleExpressionAddOpList OR MINUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(3, 2, $4.pContext));
}
                          | SimpleExpressionAddOpList XOR MINUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(4, 2, $4.pContext));
}
                          | SimpleExpressionAddOpList PLUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(1, 0, $3.pContext));
}
                          | SimpleExpressionAddOpList MINUS Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(2, 0, $3.pContext));
}
                          | SimpleExpressionAddOpList OR Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(3, 0, $3.pContext));
}
                          | SimpleExpressionAddOpList XOR Term
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiSimpleExpressionAddOp_create(4, 0, $3.pContext));
}
                          | PLUS Term
{
  $$.pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 1, $2.pContext));
}
                          | MINUS Term
{
  $$.pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 2, $2.pContext));
}
                          | Term
{
  $$.pContext = adtDelphiSimpleExpressionAddOpList_create(adtDelphiSimpleExpressionAddOp_create(0, 0, $1.pContext));
}
;

Term : FactorMulOpList
{
  $$.pContext = adtDelphiTerm_create($1.pContext);
}
;

FactorMulOpList : FactorMulOpList MULTIPLY Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(1, $3.pContext));
}
                | FactorMulOpList DIVIDE Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(2, $3.pContext));
}
                | FactorMulOpList DIV Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(3, $3.pContext));
}
                | FactorMulOpList MOD Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(4, $3.pContext));
}
                | FactorMulOpList AND Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(5, $3.pContext));
}
                | FactorMulOpList SHL Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(6, $3.pContext));
}
                | FactorMulOpList SHR Factor
{
  $$.pContext = adtDelphiList_add($1.pContext, adtDelphiFactorMulOp_create(7, $3.pContext));
}
                | Factor
{
  $$.pContext = adtDelphiFactorMulOpList_create(adtDelphiFactorMulOp_create(0, $1.pContext));
}
;

/*
Removed these from Factor as Designator LPARENTHESIS ExprList RPARENTHESIS
encompases them:

       | TypeId LPARENTHESIS Expression RPARENTHESIS
       | UnitId DOT TypeId LPARENTHESIS Expression RPARENTHESIS
*/
Factor : Designator
{
  $$.pContext = adtDelphiFactor_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
       | AT Designator
{
  $$.pContext = adtDelphiFactor_create($2.pContext, 1, 0, 0, 0, 0, 0, 0, 0, 0);
}
       | Number
{
  $$.pContext = adtDelphiFactor_create(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
       | String
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
       | NIL
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
}
       | LPARENTHESIS Expression RPARENTHESIS
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, $2.pContext, 0, 0, 0, 0);
}
       | NOT Factor
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, $2.pContext, 0, 0, 0);
}
       | SetConstructor
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
       | SIZEOF LPARENTHESIS SizeofType RPARENTHESIS
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, 0, $3.pContext, 0);
}
       | CastExpression
{
  $$.pContext = adtDelphiFactor_create(0, 0, 0, 0, 0, 0, 0, 0, 0, $1.pContext);
}
;

CastExpression : OrdIdent LPARENTHESIS Expression RPARENTHESIS
{
  $$.pContext = adtDelphiCastExpression_create($1.pContext, 0, $3.pContext);
}
               | RealType LPARENTHESIS Expression RPARENTHESIS
{
  $$.pContext = adtDelphiCastExpression_create(0, $1.pContext, $3.pContext);
}
;

Designator : DesignatorObjList
{
  $$.pContext = adtDelphiDesignator_create($1.pContext);
}
;

DesignatorObjList : DesignatorObjList DOT DesignatorObj
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                  | DesignatorObj
{
  $$.pContext = adtDelphiDesignatorObjList_create($1.pContext);
}
;

DesignatorObj : Ident LPARENTHESIS ExprList RPARENTHESIS DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, $3.pContext, $5.pContext, 0, 0);
}
              | Ident LPARENTHESIS RPARENTHESIS DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, 0, $4.pContext, 1, 0);
}
              | Ident DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, 0, $2.pContext, 0, 0);
}
              | Ident LPARENTHESIS ExprList RPARENTHESIS
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, $3.pContext, 0, 0, 0);
}
              | Ident LPARENTHESIS RPARENTHESIS
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, 0, 0, 1, 0);
}
              | Ident
{
  $$.pContext = adtDelphiDesignatorObj_create($1.pContext, 0, 0, 0, 0);
}
              | INHERITED Ident LPARENTHESIS ExprList RPARENTHESIS DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, $4.pContext, $6.pContext, 0, 1);
}
              | INHERITED Ident LPARENTHESIS RPARENTHESIS DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, 0, $5.pContext, 1, 1);
}
              | INHERITED Ident DesignatorRefList
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, 0, $3.pContext, 0, 1);
}
              | INHERITED Ident LPARENTHESIS ExprList RPARENTHESIS
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, $4.pContext, 0, 0, 1);
}
              | INHERITED Ident LPARENTHESIS RPARENTHESIS
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, 0, 0, 1, 1);
}
              | INHERITED Ident
{
  $$.pContext = adtDelphiDesignatorObj_create($2.pContext, 0, 0, 0, 1);
}
;

DesignatorRefList : DesignatorRefList DesignatorRef
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                  | DesignatorRef
{
  $$.pContext = adtDelphiDesignatorRefList_create($1.pContext);
}
;

DesignatorRef : LBRACKET ExprList RBRACKET
{
  $$.pContext = adtDelphiDesignatorRef_create($2.pContext);
}
              | HAT
{
  $$.pContext = adtDelphiDesignatorRef_create(0);
}
;

SetConstructor : LBRACKET SetElementList RBRACKET
{
  $$.pContext = adtDelphiSetConstructor_create($2.pContext);
}
               | LBRACKET RBRACKET
{
  $$.pContext = adtDelphiSetConstructor_create(0);
}
;

SetElementList : SetElementList COMMA SetElement
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
               | SetElement
{
  $$.pContext = adtDelphiSetElementList_create($1.pContext);
}
;

SetElement : Expression RANGE Expression
{
  $$.pContext = adtDelphiSetElement_create($1.pContext, $3.pContext);
}
           | Expression
{
  $$.pContext = adtDelphiSetElement_create($1.pContext, 0);
}
;

ExprList : ExprList COMMA Expression
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
         | Expression
{
  $$.pContext = adtDelphiExprList_create($1.pContext);
}
;

Statement : ExitStatement
{
  $$.pContext = adtDelphiStatement_create(0, $1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | SimpleStatement
{
  $$.pContext = adtDelphiStatement_create(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | CompoundStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | IfStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, $1.sComment);
}
          | CaseStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, $1.pContext, 0, 0, 0, 0, $1.sComment);
}
          | RepeatStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, $1.pContext, 0, 0, 0, $1.sComment);
}
          | WhileStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, 0, $1.sComment);
}
          | ForStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, $1.sComment);
}
          | WithStmt
{
  $$.pContext = adtDelphiStatement_create(0, 0, 0, 0, 0, 0, 0, 0, 0, $1.pContext, $1.sComment);
}
          | LabelId COLON
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON ExitStatement
{
  $$.pContext = adtDelphiStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON SimpleStatement
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, $3.pContext, 0, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON CompoundStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, $3.pContext, 0, 0, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON IfStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, $3.pContext, 0, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON CaseStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, $3.pContext, 0, 0, 0, 0, $1.sComment);
}
          | LabelId COLON RepeatStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, 0, $3.pContext, 0, 0, 0, $1.sComment);
}
          | LabelId COLON WhileStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, $3.pContext, 0, 0, $1.sComment);
}
          | LabelId COLON ForStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, $3.pContext, 0, $1.sComment);
}
          | LabelId COLON WithStmt
{
  $$.pContext = adtDelphiStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, $3.pContext, $1.sComment);
}
;

StmtList : StmtList Statement SEMICOLON
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
         | Statement SEMICOLON
{
  $$.pContext = adtDelphiStmtList_create($1.pContext);
}
;

ExitStatement : EXIT
{
  $$.pContext = adtDelphiExitStatement_create(0);
}
              | EXIT LPARENTHESIS RPARENTHESIS
{
  $$.pContext = adtDelphiExitStatement_create(1);
};

SimpleStatement : Designator
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
                | Designator PLUS_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 1);
}
                | Designator MINUS_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 2);
}
                | Designator TIMES_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 3);
}
                | Designator DIV_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 4);
}
                | Designator ASSIGNMENT Expression
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0, 0);
}
                | Designator ASSIGNMENT INHERITED
{
  $$.pContext = adtDelphiSimpleStatement_create($1.pContext, 0, 0, 0, 0, 0, 0, 1, 0);
}
                | SIZEOF LPARENTHESIS SizeofType RPARENTHESIS
{
  $$.pContext = adtDelphiSimpleStatement_create(0, 0, $3.pContext, 0, 0, 0, 0, 0, 0);
}
                | INHERITED
{
  $$.pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
                | GOTO LabelId
{
  $$.pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, $2.pContext, 0, 0, 0);
}
                | CastExpression PLUS_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create(0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0, 1);
}
                | CastExpression MINUS_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create(0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0, 2);
}
                | CastExpression TIMES_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create(0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0, 3);
}
                | CastExpression DIV_EQUALS Expression
{
  $$.pContext = adtDelphiSimpleStatement_create(0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0, 4);
}
                | CastExpression ASSIGNMENT Expression
{
  $$.pContext = adtDelphiSimpleStatement_create(0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0, 0);
}
                | CastExpression ASSIGNMENT INHERITED
{
  $$.pContext = adtDelphiSimpleStatement_create(0, 0, 0, 0, 0, 0, $1.pContext, 1, 0);
}
;

SizeofType : OrdIdent
{
  $$.pContext = adtDelphiSizeofType_create($1.pContext, 0, 0, 0);
}
           | RealType
{
  $$.pContext = adtDelphiSizeofType_create(0, $1.pContext, 0, 0);
}
           | VariantType
{
  $$.pContext = adtDelphiSizeofType_create(0, 0, $1.pContext, 0);
}
           | Designator
{
  $$.pContext = adtDelphiSizeofType_create(0, 0, 0, $1.pContext);
}
;

CompoundStmt : B_BEGIN StmtList B_END
{
  $$.pContext = adtDelphiCompoundStmt_create($2.pContext);
}
             | B_BEGIN B_END
{
  $$.pContext = adtDelphiCompoundStmt_create(0);
}
;

IfStmt : IF Expression THEN Statement
{
  $$.pContext = adtDelphiIfStmt_create($2.pContext, $4.pContext, 0);
}
       | IF Expression THEN Statement ELSE Statement
{
  $$.pContext = adtDelphiIfStmt_create($2.pContext, $4.pContext, $6.pContext);
}
;

CaseStmt : CASE Expression OF CaseSelectorList B_END
{
  $$.pContext = adtDelphiCaseStmt_create($2.pContext, $4.pContext, 0);
}
         | CASE Expression OF CaseSelectorList ELSE StmtList B_END
{
  $$.pContext = adtDelphiCaseStmt_create($2.pContext, $4.pContext, $6.pContext);
}
         | CASE Expression OF CaseSelectorList ELSE StmtList SEMICOLON B_END
{
  $$.pContext = adtDelphiCaseStmt_create($2.pContext, $4.pContext, $6.pContext);
}
;

CaseSelectorList : CaseSelectorList CaseSelector
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                 | CaseSelector
{
  $$.pContext = adtDelphiCaseSelectorList_create($1.pContext);
}
;

CaseSelector : CaseLabelList COLON Statement
{
  $$.pContext = adtDelphiCaseSelector_create($1.pContext, $3.pContext);
}
;

CaseLabelList : CaseLabelList COMMA CaseLabel
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
              | CaseLabel
{
  $$.pContext = adtDelphiCaseLabelList_create($1.pContext);
}
;

CaseLabel : ConstExpr RANGE ConstExpr
{
  $$.pContext = adtDelphiCaseLabel_create($1.pContext, $3.pContext);
}
          | ConstExpr
{
  $$.pContext = adtDelphiCaseLabel_create($1.pContext, 0);
}
;

RepeatStmt : REPEAT Statement UNTIL Expression
{
  $$.pContext = adtDelphiRepeatStmt_create($2.pContext, $4.pContext, 0);
}
           | REPEAT StmtList UNTIL Expression
{
  $$.pContext = adtDelphiRepeatStmt_create(0, $4.pContext, $2.pContext);
}
;

WhileStmt : WHILE Expression DO Statement
{
  $$.pContext = adtDelphiWhileStmt_create($2.pContext, $4.pContext);
}
;

ForStmt : FOR UnitId DOT Ident ASSIGNMENT Expression TO Expression DO Statement
{
  $$.pContext = adtDelphiForStmt_create($2.pContext, $4.pContext, $6.pContext, $8.pContext, $10.pContext, 0);
}
        | FOR Ident ASSIGNMENT Expression TO Expression DO Statement
{
  $$.pContext = adtDelphiForStmt_create(0, $2.pContext, $4.pContext, $6.pContext, $8.pContext, 0);
}
        | FOR UnitId DOT Ident ASSIGNMENT Expression DOWNTO Expression DO Statement
{
  $$.pContext = adtDelphiForStmt_create($2.pContext, $4.pContext, $6.pContext, $8.pContext, $10.pContext, 1);
}
        | FOR Ident ASSIGNMENT Expression DOWNTO Expression DO Statement
{
  $$.pContext = adtDelphiForStmt_create(0, $2.pContext, $4.pContext, $6.pContext, $8.pContext, 1);
}
;

WithStmt : WITH Designator DO Statement
{
  $$.pContext = adtDelphiWithStmt_create($2.pContext, $4.pContext);
}
;

ProcedureDeclSection : ProcedureDeclList
{
  $$.pContext = adtDelphiProcedureDeclSection_create($1.pContext);
}
                     |
{
  $$.pContext = 0;
}
;

ProcedureDeclList : ProcedureDeclList ProcedureDecl
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                  | ProcedureDecl
{
  $$.pContext = adtDelphiProcedureDeclList_create($1.pContext);
}
;

ProcedureDecl : ProcedureHeading SEMICOLON DirectiveList SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create($1.pContext, 0, 0, 0, $3.pContext, $5.pContext);
}
              | ProcedureHeading SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create($1.pContext, 0, 0, 0, 0, $3.pContext);
}
              | ConstructorHeading SEMICOLON DirectiveList SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, 0, $1.pContext, 0, $3.pContext, $5.pContext);
}
              | ConstructorHeading SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, 0, $1.pContext, 0, 0, $3.pContext);
}
              | DestructorHeading SEMICOLON DirectiveList SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, 0, 0, $1.pContext, $3.pContext, $5.pContext);
}
              | DestructorHeading SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, 0, 0, $1.pContext, 0, $3.pContext);
}
              | FunctionHeading SEMICOLON DirectiveList SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, $1.pContext, 0, 0, $3.pContext, $5.pContext);
}
              | FunctionHeading SEMICOLON Block SEMICOLON
{
  $$.pContext = adtDelphiProcedureDecl_create(0, $1.pContext, 0, 0, 0, $3.pContext);
}
;

FunctionHeading : FUNCTION Ident DOT Ident FormalParameters COLON SimpleType
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, $5.pContext, $7.pContext, 0, $1.sComment);
}
                | FUNCTION Ident FormalParameters COLON SimpleType
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, $3.pContext, $5.pContext, 0, $1.sComment);
}
                | FUNCTION Ident DOT Ident COLON SimpleType
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, 0, $6.pContext, 0, $1.sComment);
}
                | FUNCTION Ident COLON SimpleType
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, 0, $4.pContext, 0, $1.sComment);
}
                | FUNCTION Ident DOT Ident FormalParameters COLON TypeId
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, $5.pContext, 0, $7.pContext, $1.sComment);
}
                | FUNCTION Ident FormalParameters COLON TypeId
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, $3.pContext, 0, $5.pContext, $1.sComment);
}
                | FUNCTION Ident DOT Ident COLON TypeId
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, 0, 0, $6.pContext, $1.sComment);
}
                | FUNCTION Ident COLON TypeId
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, 0, 0, $4.pContext, $1.sComment);
}
                | FUNCTION Ident DOT Ident FormalParameters COLON STRING
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, $5.pContext, 0, 0, $1.sComment);
}
                | FUNCTION Ident FormalParameters COLON STRING
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, $3.pContext, 0, 0, $1.sComment);
}
                | FUNCTION Ident DOT Ident COLON STRING
{
  $$.pContext = adtDelphiFunctionHeading_create($2.pContext, $4.pContext, 0, 0, 0, $1.sComment);
}
                | FUNCTION Ident COLON STRING
{
  $$.pContext = adtDelphiFunctionHeading_create(0, $2.pContext, 0, 0, 0, $1.sComment);
}
;

ProcedureHeading : PROCEDURE Ident DOT Ident FormalParameters
{
  $$.pContext = adtDelphiProcedureHeading_create($2.pContext, $4.pContext, $5.pContext, $1.sComment);
}
                 | PROCEDURE Ident FormalParameters
{
  $$.pContext = adtDelphiProcedureHeading_create(0, $2.pContext, $3.pContext, $1.sComment);
}
                 | PROCEDURE Ident DOT Ident
{
  $$.pContext = adtDelphiProcedureHeading_create($2.pContext, $4.pContext, 0, $1.sComment);
}
                 | PROCEDURE Ident
{
  $$.pContext = adtDelphiProcedureHeading_create(0, $2.pContext, 0, $1.sComment);
}
;

FormalParameters : LPARENTHESIS FormalParamList RPARENTHESIS
{
  $$.pContext = adtDelphiFormalParameters_create($2.pContext);
}
                 | LPARENTHESIS RPARENTHESIS
{
  $$.pContext = adtDelphiFormalParameters_create(0);
}
;

FormalParamList : FormalParamList SEMICOLON FormalParam
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                | FormalParam
{
  $$.pContext = adtDelphiFormalParamList_create($1.pContext);
}
;

FormalParam : VAR Parameter
{
  $$.pContext = adtDelphiFormalParam_create(1, $2.pContext);
}
            | CONST Parameter
{
  $$.pContext = adtDelphiFormalParam_create(2, $2.pContext);
}
            | OUT Parameter
{
  $$.pContext = adtDelphiFormalParam_create(3, $2.pContext);
}
            | Parameter
{
  $$.pContext = adtDelphiFormalParam_create(0, $1.pContext);
}
;

Parameter : IdentList COLON ARRAY OF SimpleType
{
  $$.pContext = adtDelphiParameter_create($1.pContext, $5.pContext, 0, 0, 0, 1, 0, 0);
}
          | IdentList COLON SimpleType
{
  $$.pContext = adtDelphiParameter_create($1.pContext, $3.pContext, 0, 0, 0, 0, 0, 0);
}
          | IdentList COLON ARRAY OF TypeId
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, $5.pContext, 0, 0, 1, 0, 0);
}
          | IdentList COLON TypeId
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, $3.pContext, 0, 0, 0, 0, 0);
}
          | IdentList COLON ARRAY OF STRING
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, 0, 0, 0, 1, 1, 0);
}
          | IdentList COLON STRING
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, 0, 0, 0, 0, 1, 0);
}
          | IdentList COLON ARRAY OF P_FILE
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, 0, 0, 0, 1, 0, 1);
}
          | IdentList COLON P_FILE
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, 0, 0, 0, 0, 0, 1);
}
          | IdentList
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
          | IdentList COLON ARRAY OF SimpleType EQUALS ConstExpr
{
  $$.pContext = adtDelphiParameter_create($1.pContext, $5.pContext, 0, $7.pContext, 0, 1, 0, 0);
}
          | IdentList COLON SimpleType EQUALS ConstExpr
{
  $$.pContext = adtDelphiParameter_create($1.pContext, $3.pContext, 0, $5.pContext, 0, 0, 0, 0);
}
          | IdentList COLON ARRAY OF TypeId EQUALS Ident
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, $5.pContext, 0, $7.pContext, 1, 0, 0);
}
          | IdentList COLON TypeId EQUALS Ident
{
  $$.pContext = adtDelphiParameter_create($1.pContext, 0, $3.pContext, 0, $5.pContext, 0, 0, 0);
}
;

Directive : CDECL
{
  $$.pContext = adtDelphiDirective_create(1);
}
          | REGISTER
{
  $$.pContext = adtDelphiDirective_create(2);
}
          | DYNAMIC
{
  $$.pContext = adtDelphiDirective_create(3);
}
          | VIRTUAL
{
  $$.pContext = adtDelphiDirective_create(4);
}
          | EXPORT
{
  $$.pContext = adtDelphiDirective_create(5);
}
          | EXTERNAL
{
  $$.pContext = adtDelphiDirective_create(6);
}
          | FAR
{
  $$.pContext = adtDelphiDirective_create(7);
}
          | FORWARD
{
  $$.pContext = adtDelphiDirective_create(8);
}
          | MESSAGE
{
  $$.pContext = adtDelphiDirective_create(9);
}
          | OVERRIDE
{
  $$.pContext = adtDelphiDirective_create(10);
}
          | OVERLOAD
{
  $$.pContext = adtDelphiDirective_create(11);
}
          | PASCAL
{
  $$.pContext = adtDelphiDirective_create(12);
}
          | REINTRODUCE
{
  $$.pContext = adtDelphiDirective_create(13);
}
          | SAFECALL
{
  $$.pContext = adtDelphiDirective_create(14);
}
          | STDCALL
{
  $$.pContext = adtDelphiDirective_create(15);
}
;

DirectiveList : DirectiveList SEMICOLON Directive
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
              | Directive
{
  $$.pContext = adtDelphiDirectiveList_create($1.pContext);
}
;

ObjectType : OBJECT B_END
{
  $$.pContext = adtDelphiObjectType_create(0, 0, 0, 0);
}
           | OBJECT MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create(0, 0, 0, $2.pContext);
}
           | OBJECT ObjFieldList SEMICOLON B_END
{
  $$.pContext = adtDelphiObjectType_create(0, 0, $2.pContext, 0);
}
           | OBJECT ObjFieldList SEMICOLON MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create(0, 0, $2.pContext, $4.pContext);
}
           | OBJECT LPARENTHESIS UnitId DOT Ident RPARENTHESIS B_END
{
  $$.pContext = adtDelphiObjectType_create($3.pContext, $5.pContext, 0, 0);
}
           | OBJECT LPARENTHESIS Ident RPARENTHESIS B_END
{
  $$.pContext = adtDelphiObjectType_create(0, $3.pContext, 0, 0);
}
           | OBJECT LPARENTHESIS UnitId DOT Ident RPARENTHESIS MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create($3.pContext, $5.pContext, 0, $7.pContext);
}
           | OBJECT LPARENTHESIS Ident RPARENTHESIS MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create(0, $3.pContext, 0, $5.pContext);
}
           | OBJECT LPARENTHESIS UnitId DOT Ident RPARENTHESIS ObjFieldList SEMICOLON B_END
{
  $$.pContext = adtDelphiObjectType_create($3.pContext, $5.pContext, $7.pContext, 0);
}
           | OBJECT LPARENTHESIS Ident RPARENTHESIS ObjFieldList SEMICOLON B_END
{
  $$.pContext = adtDelphiObjectType_create(0, $3.pContext, $5.pContext, 0);
}
           | OBJECT LPARENTHESIS UnitId DOT Ident RPARENTHESIS ObjFieldList SEMICOLON MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create($3.pContext, $5.pContext, $7.pContext, $9.pContext);
}
           | OBJECT LPARENTHESIS Ident RPARENTHESIS ObjFieldList SEMICOLON MethodList B_END
{
  $$.pContext = adtDelphiObjectType_create(0, $3.pContext, $5.pContext, $7.pContext);
}
;

MethodList : MethodList Method
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
           | Method
{
  $$.pContext = adtDelphiMethodList_create($1.pContext);
}
;

Method : ProcedureHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiMethod_create($1.pContext, 0, 0, 0, $3.pContext);
}
       | ProcedureHeading SEMICOLON
{
  $$.pContext = adtDelphiMethod_create($1.pContext, 0, 0, 0, 0);
}
       | FunctionHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, $1.pContext, 0, 0, $3.pContext);
}
       | FunctionHeading SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, $1.pContext, 0, 0, 0);
}
       | ConstructorHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, 0, $1.pContext, 0, $3.pContext);
}
       | ConstructorHeading SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, 0, $1.pContext, 0, 0);
}
       | DestructorHeading SEMICOLON DirectiveList SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, 0, 0, $1.pContext, $3.pContext);
}
       | DestructorHeading SEMICOLON
{
  $$.pContext = adtDelphiMethod_create(0, 0, 0, $1.pContext, 0);
}
;

ConstructorHeading : CONSTRUCTOR Ident DOT Ident FormalParameters
{
  $$.pContext = adtDelphiConstructorHeading_create($2.pContext, $4.pContext, $5.pContext, $1.sComment);
}
                   | CONSTRUCTOR Ident FormalParameters
{
  $$.pContext = adtDelphiConstructorHeading_create(0, $2.pContext, $3.pContext, $1.sComment);
}
                   | CONSTRUCTOR Ident DOT Ident
{
  $$.pContext = adtDelphiConstructorHeading_create($2.pContext, $4.pContext, 0, $1.sComment);
}
                   | CONSTRUCTOR Ident
{
  $$.pContext = adtDelphiConstructorHeading_create(0, $2.pContext, 0, $1.sComment);
}
;

DestructorHeading : DESTRUCTOR Ident DOT Ident FormalParameters
{
  $$.pContext = adtDelphiDestructorHeading_create($2.pContext, $4.pContext, $5.pContext, $1.sComment);
}
                  | DESTRUCTOR Ident FormalParameters
{
  $$.pContext = adtDelphiDestructorHeading_create(0, $2.pContext, $3.pContext, $1.sComment);
}
                  | DESTRUCTOR Ident DOT Ident
{
  $$.pContext = adtDelphiDestructorHeading_create($2.pContext, $4.pContext, 0, $1.sComment);
}
                  | DESTRUCTOR Ident
{
  $$.pContext = adtDelphiDestructorHeading_create(0, $2.pContext, 0, $1.sComment);
}
;

ObjFieldList : ObjFieldList SEMICOLON ObjField
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
             | ObjField
{
  $$.pContext = adtDelphiObjFieldList_create($1.pContext);
}
;

ObjField : IdentList COLON Type
{
  $$.pContext = adtDelphiObjField_create($1.pContext, $3.pContext);
}
;

InitSection : INITIALIZATION StmtList B_END
{
  $$.pContext = adtDelphiInitSection_create($2.pContext, 0, 1, $1.sComment);
}
            | INITIALIZATION StmtList FINALIZATION StmtList B_END
{
  $$.pContext = adtDelphiInitSection_create($2.pContext, $4.pContext, 1, $1.sComment);
}
            | B_BEGIN StmtList B_END
{
  $$.pContext = adtDelphiInitSection_create($2.pContext, 0, 0, $1.sComment);
}
            | B_END
{
  $$.pContext = adtDelphiInitSection_create(0, 0, 0, $1.sComment);
}
;

ClassType : CLASS B_END
{
  $$.pContext = adtDelphiClassType_create(0, 0, 0, 0);
}
          | CLASS ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create(0, 0, 0, $2.pContext);
}
          | CLASS ClassMethodList B_END
{
  $$.pContext = adtDelphiClassType_create(0, 0, $2.pContext, 0);
}
          | CLASS ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create(0, 0, $2.pContext, $3.pContext);
}
          | CLASS ClassFieldList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create(0, $2.pContext, 0, 0);
}
          | CLASS ClassFieldList SEMICOLON ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create(0, $2.pContext, 0, $4.pContext);
}
          | CLASS ClassFieldList SEMICOLON ClassMethodList B_END
{
  $$.pContext = adtDelphiClassType_create(0, $2.pContext, $4.pContext, 0);
}
          | CLASS ClassFieldList SEMICOLON ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create(0, $2.pContext, $4.pContext, $5.pContext);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, 0, 0, 0);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, 0, 0, $5.pContext);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassMethodList B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, 0, $5.pContext, 0);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, 0, $5.pContext, $6.pContext);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassFieldList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, $5.pContext, 0, 0);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassFieldList SEMICOLON ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, $5.pContext, 0, $7.pContext);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassFieldList SEMICOLON ClassMethodList B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, $5.pContext, $7.pContext, 0);
}
          | CLASS LPARENTHESIS IdentList RPARENTHESIS ClassFieldList SEMICOLON ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiClassType_create($3.pContext, $5.pContext, $7.pContext, $8.pContext);
}
;

ClassFieldList : ClassFieldList SEMICOLON ClassField
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
               | ClassField
{
  $$.pContext = adtDelphiClassFieldList_create($1.pContext);
}
;

ClassField : ObjField
{
  $$.pContext = adtDelphiClassField_create(0, $1.pContext);
}
           | PUBLIC ObjField
{
  $$.pContext = adtDelphiClassField_create(1, $2.pContext);
}
           | PROTECTED ObjField
{
  $$.pContext = adtDelphiClassField_create(1, $2.pContext);
}
           | PRIVATE ObjField
{
  $$.pContext = adtDelphiClassField_create(2, $2.pContext);
}
           | PUBLISHED ObjField
{
  $$.pContext = adtDelphiClassField_create(3, $2.pContext);
}
;

ClassMethodList : ClassMethodList ClassMethod
{
  $$.pContext = adtDelphiList_add($1.pContext, $2.pContext);
}
                | ClassMethod
{
  $$.pContext = adtDelphiClassMethodList_create($1.pContext);
}
;

ClassMethod : Method
{
  $$.pContext = adtDelphiClassMethod_create(0, $1.pContext);
}
            | PUBLIC Method
{
  $$.pContext = adtDelphiClassMethod_create(1, $2.pContext);
}
            | PROTECTED Method
{
  $$.pContext = adtDelphiClassMethod_create(2, $2.pContext);
}
            | PRIVATE Method
{
  $$.pContext = adtDelphiClassMethod_create(3, $2.pContext);
}
            | PUBLISHED Method
{
  $$.pContext = adtDelphiClassMethod_create(4, $2.pContext);
}
;

ClassPropertyList : ClassPropertyList SEMICOLON ClassProperty
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                  | ClassProperty
{
  $$.pContext = adtDelphiClassPropertyList_create($1.pContext);
}
;

ClassProperty : Property
{
  $$.pContext = adtDelphiClassProperty_create(0, $1.pContext);
}
              | PUBLIC Property
{
  $$.pContext = adtDelphiClassProperty_create(1, $2.pContext);
}
              | PROTECTED Property
{
  $$.pContext = adtDelphiClassProperty_create(2, $2.pContext);
}
              | PRIVATE Property
{
  $$.pContext = adtDelphiClassProperty_create(3, $2.pContext);
}
              | PUBLISHED Property
{
  $$.pContext = adtDelphiClassProperty_create(4, $2.pContext);
}
;

Property : PROPERTY Ident LBRACKET PropertyParameterList RBRACKET COLON Ident PropertySpecifiers
{
  $$.pContext = adtDelphiProperty_create($2.pContext, $7.pContext, $4.pContext, $8.pContext);
}
         | PROPERTY Ident COLON Ident PropertySpecifiers
{
  $$.pContext = adtDelphiProperty_create($2.pContext, $4.pContext, 0, $5.pContext);
}
         | PROPERTY Ident PropertySpecifiers
{
  $$.pContext = adtDelphiProperty_create(0, $2.pContext, 0, $3.pContext);
}
;

PropertyParameterList : PropertyParameterList SEMICOLON PropertyParameter
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
                      | PropertyParameter
{
  $$.pContext = adtDelphiPropertyParameterList_create($1.pContext);
}
;

PropertyParameter : IdentList COLON TypeId
{
  $$.pContext = adtDelphiPropertyParameter_create($1.pContext, 0, $3.pContext);
}
                  | IdentList COLON UnitId DOT TypeId
{
  $$.pContext = adtDelphiPropertyParameter_create($1.pContext, $3.pContext, $5.pContext);
}
;

/*
Removed this from PropertySpecifiers for simplicity sake
                   | STORED Constant
*/
PropertySpecifiers : INDEX ConstExpr
{
  $$.pContext = adtDelphiPropertySpecifiers_create(1, 0, $2.pContext, 0, 0);
}
                   | READ Ident
{
  $$.pContext = adtDelphiPropertySpecifiers_create(2, $2.pContext, 0, 0, 0);
}
                   | WRITE Ident
{
  $$.pContext = adtDelphiPropertySpecifiers_create(3, $2.pContext, 0, 0, 0);
}
                   | STORED Ident
{
  $$.pContext = adtDelphiPropertySpecifiers_create(4, $2.pContext, 0, 0, 0);
}
                   | DEFAULT ConstExpr
{
  $$.pContext = adtDelphiPropertySpecifiers_create(5, 0, $2.pContext, 0, 0);
}
                   | NODEFAULT
{
  $$.pContext = adtDelphiPropertySpecifiers_create(6, 0, 0, 0, 0);
}
                   | IMPLEMENTS TypeId
{
  $$.pContext = adtDelphiPropertySpecifiers_create(7, 0, 0, 0, $2.pContext);
}
                   | IMPLEMENTS UnitId DOT TypeId
{
  $$.pContext = adtDelphiPropertySpecifiers_create(7, 0, 0, $2.pContext, $4.pContext);
}
                   |
{
  $$.pContext = adtDelphiPropertySpecifiers_create(0, 0, 0, 0, 0);
}
;

InterfaceType : INTERFACE B_END
{
  $$.pContext = adtDelphiInterfaceType_create(0, 0, 0, $1.sComment);
}
              | INTERFACE ClassMethodList B_END
{
  $$.pContext = adtDelphiInterfaceType_create(0, $2.pContext, 0, $1.sComment);
}
              | INTERFACE ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiInterfaceType_create(0, 0, $2.pContext, $1.sComment);
}
              | INTERFACE ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiInterfaceType_create(0, $2.pContext, $3.pContext, $1.sComment);
}
              | INTERFACE LPARENTHESIS IdentList RPARENTHESIS B_END
{
  $$.pContext = adtDelphiInterfaceType_create($3.pContext, 0, 0, $1.sComment);
}
              | INTERFACE LPARENTHESIS IdentList RPARENTHESIS ClassMethodList B_END
{
  $$.pContext = adtDelphiInterfaceType_create($3.pContext, $5.pContext, 0, $1.sComment);
}
              | INTERFACE LPARENTHESIS IdentList RPARENTHESIS ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiInterfaceType_create($3.pContext, 0, $5.pContext, $1.sComment);
}
              | INTERFACE LPARENTHESIS IdentList RPARENTHESIS ClassMethodList ClassPropertyList SEMICOLON B_END
{
  $$.pContext = adtDelphiInterfaceType_create($3.pContext, $5.pContext, $6.pContext, $1.sComment);
}
;

IdentList : IdentList COMMA Ident
{
  $$.pContext = adtDelphiList_add($1.pContext, $3.pContext);
}
          | Ident
{
  $$.pContext = adtDelphiIdentList_create($1.pContext);
}
;

/*
  Ideally a constant expression should be something else than this as it should
  be possible to include operations that can be evaluated statically by the
  compiler rather than just a single value. However, this is rather envolved to
  do properly so we just leave it as a restriction on the grammar.
*/
ConstExpr : REAL_NUMBER
{
  $$.pContext = adtDelphiConstExpr_create($1.sValue, 1);
}
          | INT_NUMBER
{
  $$.pContext = adtDelphiConstExpr_create($1.sValue, 1);
}
          | TEXT
{
  $$.pContext = adtDelphiConstExpr_create($1.sValue, 0);
}
;

TypeId : IDENTIFIER
{
  $$.pContext = adtDelphiTypeId_create($1.sValue);
}
;

UnitId : IDENTIFIER
{
  $$.pContext = adtDelphiUnitId_create($1.sValue);
}
;

Ident : IDENTIFIER
{
  $$.pContext = adtDelphiIdent_create($1.sValue);
}
;

LabelId : IDENTIFIER
{
  $$.pContext = adtDelphiLabelId_create($1.sValue);
}
;

Number : BOOL_NUMBER
{
  $$.pContext = adtDelphiNumber_create($1.sValue, 0);
}
       | INT_NUMBER
{
  $$.pContext = adtDelphiNumber_create($1.sValue, 1);
}
       | REAL_NUMBER
{
  $$.pContext = adtDelphiNumber_create($1.sValue, 2);
}
;

String : TEXT
{
  $$.pContext = adtDelphiString_create($1.sValue);
}
;
