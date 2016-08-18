%{
/*
 * java_y.y
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
 * LALR(1) Grammar for java.
 * Source: http://java.sun.com/docs/books/jls/first_edition/html/19.doc.html
 *
 */

#include <stdio.h>
#include "lexer.h"
#include "adtjava.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   javaType

%}

%token ABSTRACT AND AND_EQUALS BOOL BOOLEAN BOOLEANLITERAL BREAK BYTE CASE CATCH
%token CHAR CHARACTERLITERAL CLASS COLON COMMA CONST CONTINUE DECR DEFAULT
%token DIV DIV_EQUALS DO DOUBLE ELSE EQ EQUALS EXTENDS FINAL FINALLY FLOAT
%token FLOATINGPOINTLITERAL FOR GT GTE IDENTIFIER IF IMPLEMENTS IMPORT INCR
%token INSTANCEOF INT INTEGERLITERAL INTERFACE LAND LBRACKET LCBRACKET LNOT LONG
%token LOR LSQRBRACKET LT LTE MINUS MINUS_EQUALS MOD MOD_EQUALS MULTIPLY NATIVE
%token NE NEW NOT NULLLITERAL OR OR_EQUALS PACKAGE PERIOD PLUS PLUS_EQUALS PRIVATE
%token PROTECTED PUBLIC QUESTION RBRACKET RCBRACKET RETURN RSQRBRACKET SAL SAL_EQUALS
%token SAR SAR_EQUALS SEMICOLON SHORT SHR SHR_EQUALS STATIC STRINGLITERAL SUPER
%token SWITCH SYNCHRONIZED THIS THROW THROWS TIMES_EQUALS TRANSIENT TRY
%token VOID VOLATILE WHILE XOR XOR_EQUALS SCOPE
%token SINGLELINE_COMMENT MULTILINE_COMMENT EMBEDDED_COMMANDS

%%

Goal
 : TypeDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create(0, 0, $1.pContext);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | ImportDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create(0, $1.pContext, 0);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | ImportDeclarations TypeDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create(0, $1.pContext, $2.pContext);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | PackageDeclaration
{
  void* pObj;

  pObj        = adtJavaGoal_Create($1.pContext, 0, 0);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | PackageDeclaration TypeDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create($1.pContext, 0, $2.pContext);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | PackageDeclaration ImportDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create($1.pContext, $2.pContext, 0);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
 | PackageDeclaration ImportDeclarations TypeDeclarations
{
  void* pObj;

  pObj        = adtJavaGoal_Create($1.pContext, $2.pContext, $3.pContext);
  $$.pContext = adtJava_setRoot(pObj);

  adtJava_releaseObject(pObj);
}
;

Literal
 : INTEGERLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 0);
}
 | FLOATINGPOINTLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 1);
}
 | BOOLEANLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 2);
}
 | CHARACTERLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 3);
}
 | STRINGLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 4);
}
 | NULLLITERAL
{
  $$.pContext = adtJavaLiteral_Create($1.sValue, 5);
}
;

Type
 : Name
{
  $$.pContext = adtJavaType_Create($1.pContext, 0, 0, 0);
}
 | PrimitiveType
{
  $$.pContext = adtJavaType_Create(0, $1.pContext, 0, 0);
}
 | ArrayType
{
  $$.pContext = adtJavaType_Create(0, 0, $1.pContext, 0);
}
;

PrimitiveType
 : BYTE
{
  $$.pContext = adtJavaPrimitiveType_Create(0);
}
 | SHORT
{
  $$.pContext = adtJavaPrimitiveType_Create(1);
}
 | INT
{
  $$.pContext = adtJavaPrimitiveType_Create(2);
}
 | LONG
{
  $$.pContext = adtJavaPrimitiveType_Create(3);
}
 | CHAR
{
  $$.pContext = adtJavaPrimitiveType_Create(4);
}
 | FLOAT
{
  $$.pContext = adtJavaPrimitiveType_Create(5);
}
 | DOUBLE
{
  $$.pContext = adtJavaPrimitiveType_Create(6);
}
 | BOOLEAN
{
  $$.pContext = adtJavaPrimitiveType_Create(7);
}
 | BOOL
{
  $$.pContext = adtJavaPrimitiveType_Create(8);
}
;

ArrayType
 : PrimitiveType LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaType_Create(0, $1.pContext, 0, 1);
}
 | Name LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaType_Create($1.pContext, 0, 0, 1);
}
 | ArrayType LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaType_Create(0, 0, $1.pContext, 1);
}
;

Name
 : IDENTIFIER
{
  $$.pContext = adtJavaName(0, $1.sValue, 0);
}
 | Name PERIOD IDENTIFIER
{
  $$.pContext = adtJavaName($1.pContext, $3.sValue, 0);
}
/* Add SCOPE namespacing to support C++ with Java grammar */
 | Name SCOPE IDENTIFIER
{
  $$.pContext = adtJavaName($1.pContext, $3.sValue, 1);
}
;

ImportDeclarations
 : ImportDeclaration
{
  $$.pContext = adtJavaImportDeclarations($1.pContext);
}
 | ImportDeclarations ImportDeclaration
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

ImportDeclaration
 : IMPORT Name SEMICOLON
{
  $$.pContext = adtJavaImportDeclaration($2.pContext, 0);
}
 | IMPORT Name PERIOD MULTIPLY SEMICOLON
{
  $$.pContext = adtJavaImportDeclaration($2.pContext, 0);
}
;

TypeDeclarations
 : TypeDeclaration
{
  $$.pContext = adtJavaTypeDeclarations($1.pContext);
}
 | TypeDeclarations TypeDeclaration
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

TypeDeclaration
 : ClassDeclaration
{
  $$.pContext = adtJavaTypeDeclaration($1.pContext, 0);
}
 | InterfaceDeclaration
{
  $$.pContext = adtJavaTypeDeclaration(0, $1.pContext);
}
 | SEMICOLON
{
  $$.pContext = adtJavaTypeDeclaration(0, 0);
}
;

PackageDeclaration
 : PACKAGE Name SEMICOLON
{
  $$.pContext = adtJavaPackageDeclaration($2.pContext);
}
;

Modifiers
 : Modifier
{
  $$.pContext = adtJavaModifiers($1.pContext);
}
 | Modifiers Modifier
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

Modifier
 : PUBLIC
{
  $$.pContext = adtJavaModifier(0);
}
 | PROTECTED
{
  $$.pContext = adtJavaModifier(1);
}
 | PRIVATE
{
  $$.pContext = adtJavaModifier(2);
}
 | STATIC
{
  $$.pContext = adtJavaModifier(3);
}
 | ABSTRACT
{
  $$.pContext = adtJavaModifier(4);
}
 | FINAL
{
  $$.pContext = adtJavaModifier(5);
}
 | NATIVE
{
  $$.pContext = adtJavaModifier(6);
}
 | SYNCHRONIZED
{
  $$.pContext = adtJavaModifier(7);
}
 | TRANSIENT
{
  $$.pContext = adtJavaModifier(8);
}
 | VOLATILE
{
  $$.pContext = adtJavaModifier(9);
}
 | CONST
{
  $$.pContext = adtJavaModifier(10);
}
;

ClassDeclaration
 : CLASS IDENTIFIER LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($2.sValue, 0, 0, 0, 0);
}
 | CLASS IDENTIFIER LCBRACKET ClassBodyDeclarations RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($2.sValue, 0, 0, 0, $4.pContext);
}
 | CLASS IDENTIFIER IMPLEMENTS NameList LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($2.sValue, 0, 0, $4.pContext, 0);
}
 | CLASS IDENTIFIER IMPLEMENTS NameList LCBRACKET ClassBodyDeclarations RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($2.sValue, 0, 0, $4.pContext, $6.pContext);
}
 | Modifiers CLASS IDENTIFIER EXTENDS Name LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($3.sValue, 0, $4.pContext, 0, 0);
}
 | Modifiers CLASS IDENTIFIER EXTENDS Name LCBRACKET ClassBodyDeclarations RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($3.sValue, 0, $4.pContext, 0, $6.pContext);
}
 | Modifiers CLASS IDENTIFIER EXTENDS Name IMPLEMENTS NameList LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($3.sValue, $1.pContext, $5.pContext, $7.pContext, 0);
}
 | Modifiers CLASS IDENTIFIER EXTENDS Name IMPLEMENTS NameList LCBRACKET ClassBodyDeclarations RCBRACKET
{
  $$.pContext = adtJavaClassDeclaration($3.sValue, $1.pContext, $5.pContext, $7.pContext, $9.pContext);
}
;

ClassBodyDeclarations
 : ClassBodyDeclaration
{
  $$.pContext = adtJavaClassBodyDeclarations($1.pContext);
}
 | ClassBodyDeclarations ClassBodyDeclaration
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

ClassBodyDeclaration
 : ClassMemberDeclaration
{
  $$.pContext = adtJavaClassBodyDeclaration($1.pContext, 0, 0);
}
 | STATIC Block
{
  $$.pContext = adtJavaClassBodyDeclaration(0, $2.pContext, 0);
}
 | ConstructorDeclaration
{
  $$.pContext = adtJavaClassBodyDeclaration(0, 0, $1.pContext);
}
;

ClassMemberDeclaration
 : FieldDeclaration
{
  $$.pContext = adtJavaClassMemberDeclaration($1.pContext, 0, 0);
}
 | MethodHeader Block
{
  $$.pContext = adtJavaClassMemberDeclaration(0, $1.pContext, $2.pContext);
}
 | MethodHeader SEMICOLON
{
  $$.pContext = adtJavaClassMemberDeclaration(0, $1.pContext, 0);
}
;

FieldDeclaration
 : Type VariableDeclarators SEMICOLON
{
  $$.pContext = adtJavaFieldDeclaration(0, $1.pContext, $2.pContext);
}
 | Modifiers Type VariableDeclarators SEMICOLON
{
  $$.pContext = adtJavaFieldDeclaration($1.pContext, $2.pContext, $3.pContext);
}
;

VariableDeclarators
 : VariableDeclarator
{
  $$.pContext = adtJavaVariableDeclarators($1.pContext);
}
 | VariableDeclarators COMMA VariableDeclarator
{
  $$.pContext = adtJavaList_add($1.pContext, $3.pContext);
}
;

VariableDeclarator
 : VariableDeclaratorId
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, 0, 0, 0, 0);
}
 | VariableDeclaratorId EQUALS Expression
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, $3.pContext, 0, 0, 0);
}
 | VariableDeclaratorId EQUALS LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, 0, 0, 0, 1);
}
 | VariableDeclaratorId EQUALS LCBRACKET COMMA RCBRACKET
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, 0, 0, 1, 1);
}
 | VariableDeclaratorId EQUALS LCBRACKET VariableInitializers RCBRACKET
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, 0, $4.pContext, 0, 1);
}
 | VariableDeclaratorId EQUALS LCBRACKET VariableInitializers COMMA RCBRACKET
{
  $$.pContext = adtJavaVariableDeclarator($1.pContext, 0, $4.pContext, 1, 1);
}
;

VariableDeclaratorId
 : IDENTIFIER
{
  $$.pContext = adtJavaVariableDeclaratorId($1.sValue, 0);
}
 | VariableDeclaratorId LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaVariableDeclaratorId(0, $1.pContext);
}
;

MethodHeader
 : Type MethodDeclarator
{
  $$.pContext = adtJavaMethodHeader(0, $1.pContext, $2.pContext, 0);
}
 | Type MethodDeclarator THROWS NameList
{
  $$.pContext = adtJavaMethodHeader(0, $1.pContext, $2.pContext, $4.pContext);
}
 | Modifiers Type MethodDeclarator
{
  $$.pContext = adtJavaMethodHeader($1.pContext, $2.pContext, $3.pContext, 0);
}
 | Modifiers Type MethodDeclarator THROWS NameList
{
  $$.pContext = adtJavaMethodHeader($1.pContext, $2.pContext, $3.pContext, $5.pContext);
}
 | VOID MethodDeclarator
{
  $$.pContext = adtJavaMethodHeader(0, 0, $2.pContext, 0);
}
 | VOID MethodDeclarator THROWS NameList
{
  $$.pContext = adtJavaMethodHeader(0, 0, $2.pContext, $4.pContext);
}
 | Modifiers VOID MethodDeclarator
{
  $$.pContext = adtJavaMethodHeader($1.pContext, 0, $3.pContext, 0);
}
 | Modifiers VOID MethodDeclarator THROWS NameList
{
  $$.pContext = adtJavaMethodHeader($1.pContext, 0, $3.pContext, $5.pContext);
}
;

MethodDeclarator
 : IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtJavaMethodDeclarator($1.sValue, 0, 0);
}
 | IDENTIFIER LBRACKET FormalParameterList RBRACKET
{
  $$.pContext = adtJavaMethodDeclarator($1.sValue, $3.pContext, 0);
}
 | MethodDeclarator LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaMethodDeclarator(0, 0, $1.pContext);
}
;

FormalParameterList
 : FormalParameter
{
  $$.pContext = adtJavaFormalParameterList($1.pContext);
}
 | FormalParameterList COMMA FormalParameter
{
  $$.pContext = adtJavaList_add($1.pContext, $3.pContext);
}
;

FormalParameter
 : Type VariableDeclaratorId
{
  $$.pContext = adtJavaFormalParameter($1.pContext, $2.pContext);
}
;

NameList
 : Name
{
  $$.pContext = adtJavaNameList($1.pContext);
}
 | NameList COMMA Name
{
  $$.pContext = adtJavaList_add($1.pContext, $3.pContext);
}
;

ConstructorDeclaration
 : ConstructorDeclarator ConstructorBody
{
  $$.pContext = adtJavaConstructorDeclaration(0, $1.pContext, 0, $2.pContext);
}
 | ConstructorDeclarator THROWS NameList ConstructorBody
{
  $$.pContext = adtJavaConstructorDeclaration(0, $1.pContext, $3.pContext, $4.pContext);
}
 | Modifiers ConstructorDeclarator ConstructorBody
{
  $$.pContext = adtJavaConstructorDeclaration($1.pContext, $2.pContext, 0, $3.pContext);
}
 | Modifiers ConstructorDeclarator THROWS NameList ConstructorBody
{
  $$.pContext = adtJavaConstructorDeclaration($1.pContext, $2.pContext, $4.pContext, $5.pContext);
}
;

ConstructorDeclarator
 : IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtJavaConstructorDeclarator($1.sValue, 0);
}
 | IDENTIFIER LBRACKET FormalParameterList RBRACKET
{
  $$.pContext = adtJavaConstructorDeclarator($1.sValue, $3.pContext);
}
;

ConstructorBody
 : Block
{
  $$.pContext = adtJavaConstructorBody($1.pContext);
}
;

ExplicitConstructorInvocation
 : THIS LBRACKET RBRACKET SEMICOLON
{
  $$.pContext = adtJavaExplicitConstructorInvocation(0, 0);
}
 | THIS LBRACKET ArgumentList RBRACKET SEMICOLON
{
  $$.pContext = adtJavaExplicitConstructorInvocation($3.pContext, 0);
}
 | SUPER LBRACKET RBRACKET SEMICOLON
{
  $$.pContext = adtJavaExplicitConstructorInvocation(0, 1);
}
 | SUPER LBRACKET ArgumentList RBRACKET SEMICOLON
{
  $$.pContext = adtJavaExplicitConstructorInvocation($3.pContext, 1);
}
;

InterfaceDeclaration
 : INTERFACE IDENTIFIER LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($2.sValue, 0, 0, 0);
}
 | INTERFACE IDENTIFIER LCBRACKET InterfaceMemberDeclarations RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($2.sValue, 0, 0, $4.pContext);
}
 | INTERFACE IDENTIFIER ExtendsInterfaces LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($2.sValue, 0, $3.pContext, 0);
}
 | INTERFACE IDENTIFIER ExtendsInterfaces LCBRACKET InterfaceMemberDeclarations RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($2.sValue, 0, $3.pContext, $5.pContext);
}
 | Modifiers INTERFACE IDENTIFIER LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($3.sValue, $1.pContext, 0, 0);
}
 | Modifiers INTERFACE IDENTIFIER LCBRACKET InterfaceMemberDeclarations RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($3.sValue, $1.pContext, 0, $5.pContext);
}
 | Modifiers INTERFACE IDENTIFIER ExtendsInterfaces LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($3.sValue, $1.pContext, $4.pContext, 0);
}
 | Modifiers INTERFACE IDENTIFIER ExtendsInterfaces LCBRACKET InterfaceMemberDeclarations RCBRACKET
{
  $$.pContext = adtJavaInterfaceDeclaration($3.sValue, $1.pContext, $4.pContext, $6.pContext);
}
;

ExtendsInterfaces
 : EXTENDS Name
{
  $$.pContext = adtJavaExtendsInterfaces($2.pContext, 0);
}
 | ExtendsInterfaces COMMA Name
{
  $$.pContext = adtJavaExtendsInterfaces($3.pContext, $1.pContext);
}
;

InterfaceMemberDeclarations
 : InterfaceMemberDeclaration
{
  $$.pContext = adtJavaInterfaceMemberDeclarations($1.pContext);
}
 | InterfaceMemberDeclarations InterfaceMemberDeclaration
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

InterfaceMemberDeclaration
 : FieldDeclaration
{
  $$.pContext = adtJavaInterfaceMemberDeclaration($1.pContext, 0);

}
 | MethodHeader SEMICOLON
{
  $$.pContext = adtJavaInterfaceMemberDeclaration(0, $1.pContext);
}
;

VariableInitializers
 : VariableInitializer
{
  $$.pContext = adtJavaVariableInitializers($1.pContext);
}
 | VariableInitializers COMMA VariableInitializer
{
  $$.pContext = adtJavaList_add($1.pContext, $3.pContext);
}
;

VariableInitializer
 : Expression
{
  $$.pContext = adtJavaVariableInitializer($1.pContext, 0, 0);
}
 | LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaVariableInitializer(0, 0, 0);
}
 | LCBRACKET COMMA RCBRACKET
{
  $$.pContext = adtJavaVariableInitializer(0, 0, 1);
}
 | LCBRACKET VariableInitializers RCBRACKET
{
  $$.pContext = adtJavaVariableInitializer(0, $2.pContext, 0);
}
 | LCBRACKET VariableInitializers COMMA RCBRACKET
{
  $$.pContext = adtJavaVariableInitializer(0, $2.pContext, 1);
}
;

Block
 : LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaBlock(0, 0);
}
 | LCBRACKET BlockStatements RCBRACKET
{
  $$.pContext = adtJavaBlock($2.pContext, 0);
}
 | LCBRACKET ExplicitConstructorInvocation BlockStatements RCBRACKET
{
  $$.pContext = adtJavaBlock($3.pContext, $2.pContext);
}
 | LCBRACKET ExplicitConstructorInvocation RCBRACKET
{
  $$.pContext = adtJavaBlock(0, $2.pContext);
}
;

BlockStatements
 : BlockStatement
{
  $$.pContext = adtJavaBlockStatements($1.pContext);
}
 | BlockStatements BlockStatement
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

BlockStatement
 : Type VariableDeclarators SEMICOLON
{
  $$.pContext = adtJavaBlockStatement($1.pContext, $2.pContext, 0);
}
 | Statement
{
  $$.pContext = adtJavaBlockStatement(0, 0, $1.pContext);
}
;

Statement
 : StatementWithoutTrailingSubstatement
{
  $$.pContext = adtJavaStatement(0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
 | IDENTIFIER COLON Statement
{
  $$.pContext = adtJavaStatement($1.sValue, 0, $3.pContext, 0, 0, 0, 0, 0);
}
 | IfThenStatement
{
  $$.pContext = adtJavaStatement(0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
 | IfThenElseStatement
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
 | WhileStatement
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
 | ForStatement
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, 0, 0, $1.pContext, 0);
}
;

StatementNoShortIf
 : StatementWithoutTrailingSubstatement
{
  $$.pContext = adtJavaStatement(0, $1.pContext, 0, 0, 0, 0, 0, 1);
}
 | IDENTIFIER COLON StatementNoShortIf
{
  $$.pContext = adtJavaStatement($1.sValue, 0, $3.pContext, 0, 0, 0, 0, 1);
}
 | IfThenElseStatementNoShortIf
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, $1.pContext, 0, 0, 1);
}
 | WhileStatementNoShortIf
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, 0, $1.pContext, 0, 1);
}
 | ForStatementNoShortIf
{
  $$.pContext = adtJavaStatement(0, 0, 0, 0, 0, 0, $1.pContext, 1);
}
;

StatementWithoutTrailingSubstatement
 : Block
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement($1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
 | SEMICOLON
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
}
 | StatementExpression SEMICOLON
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, $1.pContext, 0, 0, 0, 0, 0, 0, 0, 0, 1);
}
 | SwitchStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, 0, 0);
}
 | DoStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
 | BreakStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, $1.pContext, 0, 0, 0, 0, 0, 0);
}
 | ContinueStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
 | ReturnStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
 | SynchronizedStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
 | ThrowStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
 | TryStatement
{
  $$.pContext = adtJavaStatementWithoutTrailingSubstatement(0, 0, 0, 0, 0, 0, 0, 0, 0, $1.pContext, 0);
}
;

StatementExpression
 : Assignment
{
  $$.pContext = adtJavaStatementExpression($1.pContext, 0, 0, 0, 0);
}
 | PreIncrementExpression
{
  $$.pContext = adtJavaStatementExpression(0, $1.pContext, 0, 0, 0);
}
 | PreDecrementExpression
{
  $$.pContext = adtJavaStatementExpression(0, $1.pContext, 0, 0, 0);
}
 | PostIncrementExpression
{
  $$.pContext = adtJavaStatementExpression(0, 0, $1.pContext, 0, 0);
}
 | PostDecrementExpression
{
  $$.pContext = adtJavaStatementExpression(0, 0, $1.pContext, 0, 0);
}
 | MethodInvocation
{
  $$.pContext = adtJavaStatementExpression(0, 0, 0, $1.pContext, 0);
}
 | ClassInstanceCreationExpression
{
  $$.pContext = adtJavaStatementExpression(0, 0, 0, 0, $1.pContext);
}
;

IfThenStatement
 : IF LBRACKET Expression RBRACKET Statement
{
  $$.pContext = adtJavaIfThenStatement($3.pContext, $5.pContext);
}
;

IfThenElseStatement
 : IF LBRACKET Expression RBRACKET StatementNoShortIf ELSE Statement
{
  $$.pContext = adtJavaIfThenElseStatement($3.pContext, $5.pContext, $7.pContext, 0);
}
;

IfThenElseStatementNoShortIf
 : IF LBRACKET Expression RBRACKET StatementNoShortIf ELSE StatementNoShortIf
{
  $$.pContext = adtJavaIfThenElseStatement($3.pContext, $5.pContext, $7.pContext, 1);
}
;

SwitchStatement
 : SWITCH LBRACKET Expression RBRACKET SwitchBlock
{
  $$.pContext = adtJavaSwitchStatement($3.pContext, $5.pContext);
}
;

SwitchBlock
 : LCBRACKET RCBRACKET
{
  $$.pContext = adtJavaSwitchBlock(0, 0);
}
 | LCBRACKET SwitchLabels RCBRACKET
{
  $$.pContext = adtJavaSwitchBlock($2.pContext, 0);
}
 | LCBRACKET SwitchBlockStatementGroups RCBRACKET
{
  $$.pContext = adtJavaSwitchBlock(0, $2.pContext);
}
 | LCBRACKET SwitchBlockStatementGroups SwitchLabels RCBRACKET
{
  $$.pContext = adtJavaSwitchBlock($3.pContext, $2.pContext);
}
;

SwitchBlockStatementGroups
 : SwitchBlockStatementGroup
{
  $$.pContext = adtJavaSwitchBlockStatementGroups($1.pContext);
}
 | SwitchBlockStatementGroups SwitchBlockStatementGroup
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

SwitchBlockStatementGroup
 : SwitchLabels BlockStatements
{
  $$.pContext = adtJavaSwitchBlockStatementGroup($1.pContext, $2.pContext);
}
;

SwitchLabels
 : SwitchLabel
{
  $$.pContext = adtJavaSwitchLabels($1.pContext);
}
 | SwitchLabels SwitchLabel
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

SwitchLabel
 : CASE Expression COLON
{
  $$.pContext = adtJavaSwitchLabel($2.pContext);
}
 | DEFAULT COLON
{
  $$.pContext = adtJavaSwitchLabel(0);
}
;

WhileStatement
 : WHILE LBRACKET Expression RBRACKET Statement
{
  $$.pContext = adtJavaWhileStatement($3.pContext, $5.pContext, 0);
}
;

WhileStatementNoShortIf
 : WHILE LBRACKET Expression RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaWhileStatement($3.pContext, $5.pContext, 1);
}
;

DoStatement
 : DO Statement WHILE LBRACKET Expression RBRACKET SEMICOLON
{
  $$.pContext = adtJavaDoStatement($2.pContext, $5.pContext);
}
;

ForStatement
 : FOR LBRACKET SEMICOLON SEMICOLON RBRACKET Statement
{
  $$.pContext = adtJavaForStatement(0, 0, 0, $6.pContext, 0);
}
 | FOR LBRACKET SEMICOLON SEMICOLON StatementExpressionList RBRACKET Statement
{
  $$.pContext = adtJavaForStatement(0, 0, $5.pContext, $7.pContext, 0);
}
 | FOR LBRACKET SEMICOLON Expression SEMICOLON RBRACKET Statement
{
  $$.pContext = adtJavaForStatement(0, $4.pContext, 0, $7.pContext, 0);
}
 | FOR LBRACKET SEMICOLON Expression SEMICOLON StatementExpressionList RBRACKET Statement
{
  $$.pContext = adtJavaForStatement(0, $4.pContext, $6.pContext, $8.pContext, 0);
}
 | FOR LBRACKET ForInit SEMICOLON SEMICOLON RBRACKET Statement
{
  $$.pContext = adtJavaForStatement($3.pContext, 0, 0, $7.pContext, 0);
}
 | FOR LBRACKET ForInit SEMICOLON SEMICOLON StatementExpressionList RBRACKET Statement
{
  $$.pContext = adtJavaForStatement($3.pContext, 0, $6.pContext, $8.pContext, 0);
}
 | FOR LBRACKET ForInit SEMICOLON Expression SEMICOLON RBRACKET Statement
{
  $$.pContext = adtJavaForStatement($3.pContext, $5.pContext, 0, $8.pContext, 0);
}
 | FOR LBRACKET ForInit SEMICOLON Expression SEMICOLON StatementExpressionList RBRACKET Statement
{
  $$.pContext = adtJavaForStatement($3.pContext, $5.pContext, $7.pContext, $9.pContext, 0);
}
;

ForStatementNoShortIf
 : FOR LBRACKET SEMICOLON SEMICOLON RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement(0, 0, 0, $6.pContext, 1);
}
 | FOR LBRACKET SEMICOLON SEMICOLON StatementExpressionList RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement(0, 0, $5.pContext, $7.pContext, 1);
}
 | FOR LBRACKET SEMICOLON Expression SEMICOLON RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement(0, $4.pContext, 0, $7.pContext, 1);
}
 | FOR LBRACKET SEMICOLON Expression SEMICOLON StatementExpressionList RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement(0, $4.pContext, $6.pContext, $8.pContext, 1);
}
 | FOR LBRACKET ForInit SEMICOLON SEMICOLON RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement($3.pContext, 0, 0, $7.pContext, 1);
}
 | FOR LBRACKET ForInit SEMICOLON SEMICOLON StatementExpressionList RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement($3.pContext, 0, $6.pContext, $8.pContext, 1);
}
 | FOR LBRACKET ForInit SEMICOLON Expression SEMICOLON RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement($3.pContext, $5.pContext, 0, $8.pContext, 1);
}
 | FOR LBRACKET ForInit SEMICOLON Expression SEMICOLON StatementExpressionList RBRACKET StatementNoShortIf
{
  $$.pContext = adtJavaForStatement($3.pContext, $5.pContext, $7.pContext, $9.pContext, 1);
}
;

ForInit
 : StatementExpressionList
{
  $$.pContext = adtJavaForInit(0, $1.pContext, 0);
}
 | Type VariableDeclarators
{
  $$.pContext = adtJavaForInit($1.pContext, 0, $2.pContext);
}
;

StatementExpressionList
 : StatementExpression
{
  $$.pContext = adtJavaStatementExpressionList($1.pContext);
}
 | StatementExpressionList COMMA StatementExpression
{
  $$.pContext = adtJavaList_add($1.pContext, $3.pContext);
}
;

BreakStatement
 : BREAK SEMICOLON
{
  $$.pContext = adtJavaBreakStatement(0);
}
 | BREAK IDENTIFIER SEMICOLON
{
  $$.pContext = adtJavaBreakStatement($2.sValue);
}
;

ContinueStatement
 : CONTINUE SEMICOLON
{
  $$.pContext = adtJavaContinueStatement(0);
}
 | CONTINUE IDENTIFIER SEMICOLON
{
  $$.pContext = adtJavaContinueStatement($2.sValue);
}
;

ReturnStatement
 : RETURN SEMICOLON
{
  $$.pContext = adtJavaReturnStatement(0);
}
 | RETURN Expression SEMICOLON
{
  $$.pContext = adtJavaReturnStatement($2.pContext);
}
;

ThrowStatement
 : THROW Expression SEMICOLON
{
  $$.pContext = adtJavaThrowStatement($2.pContext);
}
;

SynchronizedStatement
 : SYNCHRONIZED LBRACKET Expression RBRACKET Block
{
  $$.pContext = adtJavaSynchronizedStatement($3.pContext, $5.pContext);
}
;

TryStatement
 : TRY Block Catches
{
  $$.pContext = adtJavaTryStatement($2.pContext, $3.pContext, 0);
}
 | TRY Block Finally
{
  $$.pContext = adtJavaTryStatement($2.pContext, 0, $3.pContext);
}
 | TRY Block Catches Finally
{
  $$.pContext = adtJavaTryStatement($2.pContext, $3.pContext, $4.pContext);
}
;

Catches
 : CatchClause
{
  $$.pContext = adtJavaCatches($1.pContext);
}
 | Catches CatchClause
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

CatchClause
 : CATCH LBRACKET FormalParameter RBRACKET Block
{
  $$.pContext = adtJavaCatchClause($3.pContext, $5.pContext);
}
;

Finally
 : FINALLY Block
{
  $$.pContext = adtJavaFinally($2.pContext);
}
;

Primary
 : PrimaryNoNewArray
{
  $$.pContext = adtJavaPrimary($1.pContext, 0, 0, 0, 0);
}
 | NEW PrimitiveType DimExprs
{
  $$.pContext = adtJavaPrimary(0, $2.pContext, $3.pContext, 0, 0);
}
 | NEW PrimitiveType DimExprs Dims
{
  $$.pContext = adtJavaPrimary(0, $2.pContext, $3.pContext, $4.pContext, 0);
}
 | NEW Name DimExprs
{
  $$.pContext = adtJavaPrimary(0, 0, $3.pContext, 0, $2.pContext);
}
 | NEW Name DimExprs Dims
{
  $$.pContext = adtJavaPrimary(0, 0, $3.pContext, $4.pContext, $2.pContext);
}
;

PrimaryNoNewArray
 : Literal
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, $1.pContext, 0, 0, 0, 0, 0, 0, 0);
}
 | THIS
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, 0, 0, 0, 0, 0, 0, 0, 0);
}
 | LBRACKET Expression RBRACKET
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, 0, $2.pContext, 0, 0, 0, 0, 0, 0);
}
 | ClassInstanceCreationExpression
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, 0, 0, $1.pContext, 0, 0, 0, 0, 0);
}
 | Primary PERIOD IDENTIFIER
{
  $$.pContext = adtJavaPrimaryNoNewArray($3.sValue, 0, 0, 0, $1.pContext, 0, 0, 0, 0);
}
 | SUPER PERIOD IDENTIFIER
{
  $$.pContext = adtJavaPrimaryNoNewArray($3.sValue, 0, 0, 0, 0, 0, 0, 0, 1);
}
 | Name LSQRBRACKET Expression RSQRBRACKET
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, 0, $3.pContext, 0, 0, 0, $1.pContext, 0, 0);
}
 | PrimaryNoNewArray LSQRBRACKET Expression RSQRBRACKET
{
  $$.pContext = adtJavaPrimaryNoNewArray(0, 0, $3.pContext, 0, 0, 0, 0, $1.pContext, 0);
}
;

ClassInstanceCreationExpression
 : NEW Name LBRACKET RBRACKET
{
  $$.pContext = adtJavaClassInstanceCreationExpression($2.pContext, 0);
}
 | NEW Name LBRACKET ArgumentList RBRACKET
{
  $$.pContext = adtJavaClassInstanceCreationExpression($2.pContext, $4.pContext);
}
;

ArgumentList
 : Expression
{
  $$.pContext = adtJavaArgumentList($1.pContext);
}
 | ArgumentList COMMA Expression
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

DimExprs
 : DimExpr
{
  $$.pContext = adtJavaDimExprs($1.pContext);
}
 | DimExprs DimExpr
{
  $$.pContext = adtJavaList_add($1.pContext, $2.pContext);
}
;

DimExpr
 : LSQRBRACKET Expression RSQRBRACKET
{
  $$.pContext = adtJavaDimExpr($2.pContext);
}
;

Dims
 : LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaDims(0);
}
 | Dims LSQRBRACKET RSQRBRACKET
{
  $$.pContext = adtJavaDims($1.pContext);
}
;

MethodInvocation
 : Name LBRACKET RBRACKET
{
  $$.pContext = adtJavaMethodInvocation(0, $1.pContext, 0, 0);
}
 | Name LBRACKET ArgumentList RBRACKET
{
  $$.pContext = adtJavaMethodInvocation(0, $1.pContext, 0, $3.pContext);
}
 | Primary PERIOD IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtJavaMethodInvocation($3.sValue, 0, $1.pContext, 0);
}
 | Primary PERIOD IDENTIFIER LBRACKET ArgumentList RBRACKET
{
  $$.pContext = adtJavaMethodInvocation($3.sValue, 0, $1.pContext, $5.pContext);
}
 | SUPER PERIOD IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtJavaMethodInvocation($3.sValue, 0, 0, 0);
}
 | SUPER PERIOD IDENTIFIER LBRACKET ArgumentList RBRACKET
{
  $$.pContext = adtJavaMethodInvocation($3.sValue, 0, 0, $5.pContext);
}
;

PostfixExpression
 : Primary
{
  $$.pContext = adtJavaPostfixExpression(0, $1.pContext, 0);
}
 | Name
{
  $$.pContext = adtJavaPostfixExpression($1.pContext, 0, 0);
}
 | PostIncrementExpression
{
  $$.pContext = adtJavaPostfixExpression(0, 0, $1.pContext);
}
 | PostDecrementExpression
{
  $$.pContext = adtJavaPostfixExpression(0, 0, $1.pContext);
}
;

PostIncrementExpression
 : PostfixExpression INCR
{
  $$.pContext = adtJavaPostIncDecExpression($1.pContext, 1);
}
;

PostDecrementExpression
 : PostfixExpression DECR
{
  $$.pContext = adtJavaPostIncDecExpression($1.pContext, 0);
}
;

UnaryExpression
 : PreIncrementExpression
{
  $$.pContext = adtJavaUnaryExpression($1.pContext, 0, 0, 0);
}
 | PreDecrementExpression
{
  $$.pContext = adtJavaUnaryExpression($1.pContext, 0, 0, 0);
}
 | PLUS UnaryExpression
{
  $$.pContext = adtJavaUnaryExpression(0, $2.pContext, 0, 1);
}
 | MINUS UnaryExpression
{
  $$.pContext = adtJavaUnaryExpression(0, $2.pContext, 0, 0);
}
 | UnaryExpressionNotPlusMinus
{
  $$.pContext = adtJavaUnaryExpression(0, 0, $1.pContext,0);
}
;

PreIncrementExpression
 : INCR UnaryExpression
{
  $$.pContext = adtJavaPreIncDecExpression($2.pContext, 1);
}
;

PreDecrementExpression
 : DECR UnaryExpression
{
  $$.pContext = adtJavaPreIncDecExpression($2.pContext, 0);
}
;

UnaryExpressionNotPlusMinus
 : PostfixExpression
{
  $$.pContext = adtJavaUnaryExpressionNotPlusMinus($1.pContext, 0, 0, 0);
}
 | NOT UnaryExpression
{
  $$.pContext = adtJavaUnaryExpressionNotPlusMinus(0, $1.pContext, 0, 0);
}
 | LNOT UnaryExpression
{
  $$.pContext = adtJavaUnaryExpressionNotPlusMinus(0, $1.pContext, 0, 1);
}
 | CastExpression
{
  $$.pContext = adtJavaUnaryExpressionNotPlusMinus(0, 0, $1.pContext, 0);
}
;

CastExpression
 : LBRACKET PrimitiveType RBRACKET UnaryExpression
{
  $$.pContext = adtJavaCastExpression($2.pContext, $4.pContext, 0, 0, 0, 0);
}
 | LBRACKET PrimitiveType Dims RBRACKET UnaryExpression
{
  $$.pContext = adtJavaCastExpression($2.pContext, $5.pContext, 0, 0, $3.pContext, 0);
}
 | LBRACKET Expression RBRACKET UnaryExpressionNotPlusMinus
{
  $$.pContext = adtJavaCastExpression(0, 0, $4.pContext, $2.pContext, 0, 0);
}
 | LBRACKET Name Dims RBRACKET UnaryExpressionNotPlusMinus
{
  $$.pContext = adtJavaCastExpression(0, 0, $5.pContext, 0, $3.pContext, $2.pContext);
}
;

MultiplicativeExpression
 : UnaryExpression
{
  $$.pContext = adtJavaMultiplicativeExpression($1.pContext, 0, 0);
}
 | MultiplicativeExpression MULTIPLY UnaryExpression
{
  $$.pContext = adtJavaMultiplicativeExpression($3.pContext, $1.pContext, 0);
}
 | MultiplicativeExpression DIV UnaryExpression
{
  $$.pContext = adtJavaMultiplicativeExpression($3.pContext, $1.pContext, 1);
}
 | MultiplicativeExpression MOD UnaryExpression
{
  $$.pContext = adtJavaMultiplicativeExpression($3.pContext, $1.pContext, 2);
}
;

AdditiveExpression
 : MultiplicativeExpression
{
  $$.pContext = adtJavaAdditiveExpression($1.pContext, 0, 0);
}
 | AdditiveExpression PLUS MultiplicativeExpression
{
  $$.pContext = adtJavaAdditiveExpression($3.pContext, $1.pContext, 0);
}
 | AdditiveExpression MINUS MultiplicativeExpression
{
  $$.pContext = adtJavaAdditiveExpression($3.pContext, $1.pContext, 1);
}
;

ShiftExpression
 : AdditiveExpression
 | ShiftExpression SAL AdditiveExpression
 | ShiftExpression SAR AdditiveExpression
 | ShiftExpression SHR AdditiveExpression
;

RelationalExpression
 : ShiftExpression
{
  $$.pContext = adtJavaRelationalExpression($1.pContext, 0, 0, 0, 0);
}
 | RelationalExpression LT ShiftExpression
{
  $$.pContext = adtJavaRelationalExpression($3.pContext, $1.pContext, 0, 0, 0);
}
 | RelationalExpression GT ShiftExpression
{
  $$.pContext = adtJavaRelationalExpression($3.pContext, $1.pContext, 0, 0, 1);
}
 | RelationalExpression LTE ShiftExpression
{
  $$.pContext = adtJavaRelationalExpression($3.pContext, $1.pContext, 0, 0, 2);
}
 | RelationalExpression GTE ShiftExpression
{
  $$.pContext = adtJavaRelationalExpression($3.pContext, $1.pContext, 0, 0, 3);
}
 | RelationalExpression INSTANCEOF Name
{
  $$.pContext = adtJavaRelationalExpression(0, $1.pContext, $3.pContext, 0, 4);
}
 | RelationalExpression INSTANCEOF ArrayType
{
  $$.pContext = adtJavaRelationalExpression(0, $1.pContext, 0, $3.pContext, 4);
}
;

EqualityExpression
 : RelationalExpression
{
  $$.pContext = adtJavaEqualityExpression($1.pContext, 0, 0);
}
 | EqualityExpression EQ RelationalExpression
{
  $$.pContext = adtJavaEqualityExpression($3.pContext, $1.pContext, 0);
}
 | EqualityExpression NE RelationalExpression
{
  $$.pContext = adtJavaEqualityExpression($3.pContext, $1.pContext, 1);
}
;

AndExpression
 : EqualityExpression
{
  $$.pContext = adtJavaAndExpression($1.pContext, 0);
}
 | AndExpression AND EqualityExpression
{
  $$.pContext = adtJavaAndExpression($3.pContext, $1.pContext);
}
;

ExclusiveOrExpression
 : AndExpression
{
  $$.pContext = adtJavaExclusiveOrExpression($1.pContext, 0);
}
 | ExclusiveOrExpression XOR AndExpression
{
  $$.pContext = adtJavaExclusiveOrExpression($3.pContext, $1.pContext);
}
;

InclusiveOrExpression
 : ExclusiveOrExpression
{
  $$.pContext = adtJavaInclusiveOrExpression($1.pContext, 0);
}
 | InclusiveOrExpression OR ExclusiveOrExpression
{
  $$.pContext = adtJavaInclusiveOrExpression($3.pContext, $1.pContext);
}
;

ConditionalAndExpression
 : InclusiveOrExpression
{
  $$.pContext = adtJavaConditionalAndExpression($1.pContext, 0);
}
 | ConditionalAndExpression LAND InclusiveOrExpression
{
  $$.pContext = adtJavaConditionalAndExpression($3.pContext, $1.pContext);
}
;

ConditionalOrExpression
 : ConditionalAndExpression
{
  $$.pContext = adtJavaConditionalOrExpression($1.pContext, 0);
}
 | ConditionalOrExpression LOR ConditionalAndExpression
{
  $$.pContext = adtJavaConditionalOrExpression($3.pContext, $1.pContext);
}
;

ConditionalExpression
 : ConditionalOrExpression
{
  $$.pContext = adtJavaConditionalExpression($1.pContext, 0, 0);
}
 | ConditionalOrExpression QUESTION Expression COLON ConditionalExpression
{
  $$.pContext = adtJavaConditionalExpression($1.pContext, $3.pContext, $5.pContext);
}
;

Expression
 : ConditionalExpression
{
  $$.pContext = adtJavaExpression($1.pContext, 0);
}
 | Assignment
{
  $$.pContext = adtJavaExpression(0, $1.pContext);
}
;

Assignment
 : Name AssignmentOperator Expression
{
  $$.pContext = adtJavaAssignment(0, $1.pContext, $2.pContext, $3.pContext, 0, 0, 0, 0);
}
 | Primary PERIOD IDENTIFIER AssignmentOperator Expression
{
  $$.pContext = adtJavaAssignment($3.sValue, 0, $4.pContext, $5.pContext, $1.pContext, 0, 0, 0);
}
 | SUPER PERIOD IDENTIFIER AssignmentOperator Expression
{
  $$.pContext = adtJavaAssignment($3.sValue, 0, $4.pContext, $5.pContext, 0, 0, 0, 1);
}
 | Name LSQRBRACKET Expression RSQRBRACKET AssignmentOperator Expression
{
  $$.pContext = adtJavaAssignment(0, $1.pContext, $5.pContext, $3.pContext, 0, 0, $6.pContext, 0);
}
 | PrimaryNoNewArray LSQRBRACKET Expression RSQRBRACKET AssignmentOperator Expression
{
  $$.pContext = adtJavaAssignment(0, 0, $5.pContext, $3.pContext, 0, $1.pContext, $6.pContext, 0);
}
;

AssignmentOperator
 : EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(0);
}
 | TIMES_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(1);
}
 | DIV_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(2);
}
 | MOD_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(3);
}
 | PLUS_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(4);
}
 | MINUS_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(5);
}
 | SAL_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(6);
}
 | SAR_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(7);
}
 | SHR_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(8);
}
 | AND_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(9);
}
 | XOR_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(10);
}
 | OR_EQUALS
{
  $$.pContext = adtJavaAssignmentOperator(11);
}
;
