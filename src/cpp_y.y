%{
/*
/*
 * cpp.y
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
 * Simplified C++ Grammar Summary
 *
 * Based on the Annex A of ISO/IEC 14882:1998 (The C++ Standard).
 *
 *Source: http://linuxsoftware.co.nz/cppgrammar.html
 */

#include <stdio.h>
#include "lexer.h"
#include "adtcpp.hpp"
#include "adtutils.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   cppType

const char* adtCpp_pLastFunctionName        = 0;
const char* adtCpp_pLastFunctionComment     = 0;
int         adtCpp_pLastFunctionIsObj       = 0;
int         adtCpp_pLastFunctionIsQualified = 0;
int         adtCpp_pLastFunctionIsVirtual   = 0;

%}

%token OR_EQ MOD PROD XOR DOT XOR_EQ LT_EQ NEQ ELLIPSIS LBRACKET RBRACKET
%token LSBRACKET RSBRACKET LSQBRACKET RSQBRACKET AND_EQ LT GT DECR INCR PLUS
%token MINUS SHR_EQ SHL_EQ GT_EQ COLON COMMA LAND LOR LNOT
%token NOT SEMICOLON LITERAL AND EQEQ SHR M_EQ P_EQ
%token SHL QUESTION MOD_EQ DIV_EQ DIV PROD_EQ EQ OR STRING_LITERAL TYPENAME
%token DOUBLE FLOAT MUTABLE PUBLIC PRIVATE PROTECTED EXTERN DEFAULT
%token WHILE SWITCH ENUM RETURN UNSIGNED ASM DO AUTO
%token CONTINUE BOOL WCHAR_T EXPLICIT IF SIZEOF UNION CHAR
%token CLASS USING VOLATILE SIGNED CONST LONG STATIC INT ELSE SHORT NAMESPACE
%token REGISTER TYPEDEF FRIEND FOR GOTO VIRTUAL INLINE
%token CASE VOID STRUCT BREAK

%token IDENTIFIER QUALIFIED_IDENTIFIER DTOR QUALIFIED_DTOR
%token OBJ_IDENTIFIER QUALIFIED_OBJ_IDENTIFIER

/* Other tokens */
%token SINGLELINE_COMMENT MULTILINE_COMMENT EMBEDDED_COMMANDS

%token ADDVARIABLES

/* we expect 5 shift reduce conflicts. */
%expect 5

%%

translation_unit
 : declaration_seq
{
  void* pObj;

  pObj        = adtCppTranslationUnit_create($1.pContext);
  $$.pContext = adtCpp_setRoot(pObj);

  adtCpp_releaseObject(pObj);
}
 | macro
{
  $$.pContext = adtCppList_add(adtCpp_getRoot(), $1.pContext);
}
;

/* This special case rule is here to support our macro replacement mechanism
   for C++ code in the same manner as is done with the Delphi code. */
macro : IDENTIFIER LBRACKET expression_list RBRACKET statement_seq
{
  $$.pContext = adtCppMacro_create($1.sValue, $3.pContext, $5.pContext, 0);
}
 | IDENTIFIER LBRACKET expression_list RBRACKET statement_seq ADDVARIABLES simple_declaration_list
{
  $$.pContext = adtCppMacro_create($1.sValue, $3.pContext, $5.pContext, $7.pContext);
}
;

simple_declaration_list : simple_declaration
{
  $$.pContext = adtCppSimpleDeclarationList_create($1.pContext);
}
 | simple_declaration_list simple_declaration
{
  $$.pContext = adtCppList_add($1.pContext, $2.pContext);
}
;

postfix_expression
 : LITERAL
{
  $$.pContext = adtCppPostfixExpression_create(0, 0, 0, 0, $1.sValue);
}
 | STRING_LITERAL
{
  $$.pContext = adtCppPostfixExpression_create(0, 0, 0, 0, $1.sValue);
}
 | LBRACKET expression RBRACKET
{
  $$.pContext = adtCppPostfixExpression_create($2.pContext, 0, 0, 0, 0);
}
 | postfix_expression INCR
{
  $$.pContext = adtCppPostfixExpression_create(0, $1.pContext, 0, 1, 0);
}
 | postfix_expression DECR
{
  $$.pContext = adtCppPostfixExpression_create(0, $1.pContext, 0, 0, 0);
}
 | directed_expression
{
  $$.pContext = adtCppPostfixExpression_create(0, 0, $1.pContext, 0, 0);
}
;

expression_list
 : assignment_expression
{
  $$.pContext = adtCppExpressionList_create($1.pContext);
}
 | expression_list COMMA assignment_expression
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

directed_expression
 : declarator_expression
{
  $$.pContext = adtCppDirectedExpression_create($1.pContext);
}
 | directed_expression DOT declarator_expression
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

/* NOTE: this construct yields two shift reduce conflicts but we can safely
   ignore them as the default action of shifting rather than reducing yields
   the correct behaviour as far as our grammar is concerned. */

declarator_expression
 : IDENTIFIER
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, 0, 0, 0, $1.sComment);
}
 | QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, 0, 1, 0, $1.sComment);
}
 | IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, 0, 0, 1, $1.sComment);
}
 | QUALIFIED_IDENTIFIER LBRACKET RBRACKET
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, 0, 1, 1, $1.sComment);
}
 | IDENTIFIER LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, $3.pContext, 0, 0, 1, $1.sComment);
}
 | QUALIFIED_IDENTIFIER LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, $3.pContext, 0, 1, 1, $1.sComment);
}
 | IDENTIFIER declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, $2.pContext, 0, 0, $1.sComment);
}
 | QUALIFIED_IDENTIFIER declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, $2.pContext, 1, 0, $1.sComment);
}
 | IDENTIFIER LBRACKET RBRACKET declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, $4.pContext, 0, 1, $1.sComment);
}
 | QUALIFIED_IDENTIFIER LBRACKET RBRACKET declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, 0, $4.pContext, 1, 1, $1.sComment);
}
 | IDENTIFIER LBRACKET expression_list RBRACKET declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, $3.pContext, $5.pContext, 0, 1, $1.sComment);
}
 | QUALIFIED_IDENTIFIER LBRACKET expression_list RBRACKET declarator_expression_dims
{
  $$.pContext = adtCppDeclaratorExpression_create($1.sValue, $3.pContext, $5.pContext, 1, 1, $1.sComment);
}
;

declarator_expression_dims
 : LSQBRACKET expression RSQBRACKET
{
  $$.pContext = adtCppDeclaratorExpressionDims_create($2.pContext);
}
 | declarator_expression_dims LSQBRACKET expression RSQBRACKET
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

unary_expression
 : postfix_expression
{
  $$.pContext = adtCppUnaryExpression_create($1.pContext, 0, 0, 0, 0);
}
 | INCR unary_expression
{
  $$.pContext = adtCppUnaryExpression_create(0, $2.pContext, 0, 0, 1);
}
 | DECR unary_expression
{
  $$.pContext = adtCppUnaryExpression_create(0, $2.pContext, 0, 0, 0);
}
 | unary_operator unary_expression
{
  $$.pContext = adtCppUnaryExpression_create(0, $2.pContext, $1.pContext, 0, 0);
}
 | SIZEOF LBRACKET expression RBRACKET
{
  $$.pContext = adtCppUnaryExpression_create(0, 0, 0, $3.pContext, 0);
}
;

unary_operator
 : PLUS
{
  $$.pContext = adtCppUnaryOperator_create(0);
}
 | MINUS
{
  $$.pContext = adtCppUnaryOperator_create(1);
}
 | LNOT
{
  $$.pContext = adtCppUnaryOperator_create(2);
}
 | NOT
{
  $$.pContext = adtCppUnaryOperator_create(3);
}
;

multiplicative_expression
 : unary_expression
{
  $$.pContext = adtCppMultiplicativeExpression_create(0, $1.pContext, 0);
}
 | multiplicative_expression PROD unary_expression
{
  $$.pContext = adtCppMultiplicativeExpression_create(0, $3.pContext, $1.pContext);
}
 | multiplicative_expression DIV unary_expression
{
  $$.pContext = adtCppMultiplicativeExpression_create(1, $3.pContext, $1.pContext);
}
 | multiplicative_expression MOD unary_expression
{
  $$.pContext = adtCppMultiplicativeExpression_create(2, $3.pContext, $1.pContext);
}
;

additive_expression
 : multiplicative_expression
{
  $$.pContext = adtCppAdditiveExpression_create(0, $1.pContext, 0);
}
 | additive_expression PLUS multiplicative_expression
{
  $$.pContext = adtCppAdditiveExpression_create(0, $3.pContext, $1.pContext);
}
 | additive_expression MINUS multiplicative_expression
{
  $$.pContext = adtCppAdditiveExpression_create(1, $3.pContext, $1.pContext);
}
;

shift_expression
 : additive_expression
{
  $$.pContext = adtCppShiftExpression_create(0, $1.pContext, 0);
}
 | shift_expression SHL additive_expression
{
  $$.pContext = adtCppShiftExpression_create(0, $3.pContext, $1.pContext);
}
 | shift_expression SHR additive_expression
{
  $$.pContext = adtCppShiftExpression_create(1, $3.pContext, $1.pContext);
}
;

relational_expression
 : shift_expression
{
  $$.pContext = adtCppRelationalExpression_create(0, $1.pContext, 0);
}
 | relational_expression LT shift_expression
{
  $$.pContext = adtCppRelationalExpression_create(0, $3.pContext, $1.pContext);
}
 | relational_expression GT shift_expression
{
  $$.pContext = adtCppRelationalExpression_create(1, $3.pContext, $1.pContext);
}
 | relational_expression LT_EQ shift_expression
{
  $$.pContext = adtCppRelationalExpression_create(2, $3.pContext, $1.pContext);
}
 | relational_expression GT_EQ shift_expression
{
  $$.pContext = adtCppRelationalExpression_create(3, $3.pContext, $1.pContext);
}
;

equality_expression
 : relational_expression
{
  $$.pContext = adtCppEqualityExpression_create(0, $1.pContext, 0);
}
 | equality_expression EQEQ relational_expression
{
  $$.pContext = adtCppEqualityExpression_create(0, $3.pContext, $1.pContext);
}
 | equality_expression NEQ relational_expression
{
  $$.pContext = adtCppEqualityExpression_create(1, $3.pContext, $1.pContext);
}
;

and_expression
 : equality_expression
{
  $$.pContext = adtCppAndExpression_create($1.pContext, 0);
}
 | and_expression AND equality_expression
{
  $$.pContext = adtCppAndExpression_create($3.pContext, $1.pContext);
}
;

exclusive_or_expression
 : and_expression
{
  $$.pContext = adtCppExclusiveOrExpression_create($1.pContext, 0);
}
 | exclusive_or_expression XOR and_expression
{
  $$.pContext = adtCppExclusiveOrExpression_create($3.pContext, $1.pContext);
}
;

inclusive_or_expression
 : exclusive_or_expression
{
  $$.pContext = adtCppInclusiveOrExpression_create($1.pContext, 0);
}
 | inclusive_or_expression OR exclusive_or_expression
{
  $$.pContext = adtCppInclusiveOrExpression_create($3.pContext, $1.pContext);
}
;

logical_and_expression
 : inclusive_or_expression
{
  $$.pContext = adtCppLogicalAndExpression_create($1.pContext, 0);
}
 | logical_and_expression LAND inclusive_or_expression
{
  $$.pContext = adtCppLogicalAndExpression_create($3.pContext, $1.pContext);
}
;

logical_or_expression
 : logical_and_expression
{
  $$.pContext = adtCppLogicalOrExpression_create($1.pContext, 0);
}
 | logical_or_expression LOR logical_and_expression
{
  $$.pContext = adtCppLogicalOrExpression_create($3.pContext, $1.pContext);
}
;

conditional_expression
 : logical_or_expression
{
  $$.pContext = adtCppConditionalExpression_create($1.pContext, 0, 0);
}
 | logical_or_expression QUESTION expression COLON assignment_expression
{
  $$.pContext = adtCppConditionalExpression_create($1.pContext, $3.pContext, $5.pContext);
}
;

assignment_expression
 : conditional_expression
{
  $$.pContext = adtCppAssignmentExpression_create($1.pContext, 0, 0, 0);
}
 | logical_or_expression assignment_operator assignment_expression
{
  $$.pContext = adtCppAssignmentExpression_create(0, $1.pContext, $2.pContext, $3.pContext);
}
;

assignment_operator
 : EQ
{
  $$.pContext = adtCppAssignmentOperator_create(0);
}
 | PROD_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(1);
}
 | DIV_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(2);
}
 | MOD_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(3);
}
 | P_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(4);
}
 | M_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(5);
}
 | SHL_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(6);
}
 | SHR_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(7);
}
 | AND_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(8);
}
 | XOR_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(9);
}
 | OR_EQ
{
  $$.pContext = adtCppAssignmentOperator_create(10);
}
;

expression
 : assignment_expression
{
  $$.pContext = adtCppExpression_create($1.pContext, 0);
}
 | expression COMMA assignment_expression
{
  $$.pContext = adtCppExpression_create($3.pContext, $1.pContext);
}
;

constant_expression
 : conditional_expression
{
  $$.pContext = adtCppConstantExpression_create($1.pContext);
}
;

statement
 : labeled_statement
{
  $$.pContext = adtCppStatement_create($1.pContext, 0, 0, 0, 0, 0, 0);
}
 | expression_statement
{
  $$.pContext = adtCppStatement_create(0, $1.pContext, 0, 0, 0, 0, 0);
}
 | compound_statement
{
  $$.pContext = adtCppStatement_create(0, 0, $1.pContext, 0, 0, 0, 0);
}
 | selection_statement
{
  $$.pContext = adtCppStatement_create(0, 0, 0, $1.pContext, 0, 0, 0);
}
 | iteration_statement
{
  $$.pContext = adtCppStatement_create(0, 0, 0, 0, $1.pContext, 0, 0);
}
 | jump_statement
{
  $$.pContext = adtCppStatement_create(0, 0, 0, 0, 0, $1.pContext, 0);
}
 | declaration_statement
{
  $$.pContext = adtCppStatement_create(0, 0, 0, 0, 0, 0, $1.pContext);
}
;

labeled_statement
 : IDENTIFIER COLON statement
{
  $$.pContext = adtCppLabeledStatement_create(0, $3.pContext, $1.sValue, 0, $1.sComment);
}
 | CASE constant_expression COLON statement
{
  $$.pContext = adtCppLabeledStatement_create($2.pContext, $4.pContext, 0, 0, $1.sComment);
}
 | DEFAULT COLON statement
{
  $$.pContext = adtCppLabeledStatement_create(0, $3.pContext, 0, 1, $1.sComment);
}
;

expression_statement
 : SEMICOLON
{
  $$.pContext = adtCppExpressionStatement_create(0, $1.sComment);
}
 | expression SEMICOLON
{
  $$.pContext = adtCppExpressionStatement_create($1.pContext, $2.sComment);
}
;

compound_statement
 : LSBRACKET RSBRACKET
{
  $$.pContext = adtCppCompoundStatement_create(0, $1.sComment);
}
 | LSBRACKET statement_seq RSBRACKET
{
  $$.pContext = adtCppCompoundStatement_create($2.pContext, $1.sComment);
}
;

statement_seq
 : statement
{
  $$.pContext = adtCppStatementSeq_create($1.pContext);
}
 | statement_seq statement
{
  $$.pContext = adtCppList_add($1.pContext, $2.pContext);
}
;

/* NOTE: this construct yields one shift reduce conflict (dangling else problem)
   but we can safely ignore them as the default action of shifting rather than
   reducing yields the correct behaviour as far as our grammar is concerned. */

selection_statement
 : IF LBRACKET expression RBRACKET statement
{
  $$.pContext = adtCppSelectionStatement_create($3.pContext, $5.pContext, 0, 1, $1.sComment);
}
 | IF LBRACKET expression RBRACKET statement ELSE statement
{
  $$.pContext = adtCppSelectionStatement_create($3.pContext, $5.pContext, $7.pContext, 1, $1.sComment);
}
 | SWITCH LBRACKET expression RBRACKET statement
{
  $$.pContext = adtCppSelectionStatement_create($3.pContext, $5.pContext, 0, 0, $1.sComment);
}
;

iteration_statement
 : WHILE LBRACKET expression RBRACKET statement
{
  $$.pContext = adtCppIterationStatement_create(0, $3.pContext, 0, $5.pContext, 0, $1.sComment);
}
 | DO statement WHILE LBRACKET expression RBRACKET SEMICOLON
{
  $$.pContext = adtCppIterationStatement_create(0, $5.pContext, 0, $2.pContext, 1, $1.sComment);
}
 | FOR LBRACKET for_init_statement SEMICOLON RBRACKET statement
{
  $$.pContext = adtCppIterationStatement_create($3.pContext, 0, 0, $6.pContext, 0, $1.sComment);
}
 | FOR LBRACKET for_init_statement SEMICOLON expression RBRACKET statement
{
  $$.pContext = adtCppIterationStatement_create($3.pContext, 0, $5.pContext, $7.pContext, 0, $1.sComment);
}
 | FOR LBRACKET for_init_statement expression SEMICOLON RBRACKET statement
{
  $$.pContext = adtCppIterationStatement_create($3.pContext, $4.pContext, 0, $7.pContext, 0, $1.sComment);
}
 | FOR LBRACKET for_init_statement expression SEMICOLON expression RBRACKET statement
{
  $$.pContext = adtCppIterationStatement_create($3.pContext, $4.pContext, $6.pContext, $8.pContext, 0, $1.sComment);
}
;

for_init_statement
 : expression_statement
{
  $$.pContext = adtCppForInitStatement_create($1.pContext, 0);
}
 | simple_declaration
{
  $$.pContext = adtCppForInitStatement_create(0, $1.pContext);
}
;

jump_statement
 : BREAK SEMICOLON
{
  $$.pContext = adtCppJumpStatement_create(0, 0, 0, $1.sComment);
}
 | CONTINUE SEMICOLON
{
  $$.pContext = adtCppJumpStatement_create(0, 0, 1, $1.sComment);
}
 | RETURN SEMICOLON
{
  $$.pContext = adtCppJumpStatement_create(0, 0, 2, $1.sComment);
}
 | RETURN expression SEMICOLON
{
  $$.pContext = adtCppJumpStatement_create($2.pContext, 0, 2, $1.sComment);
}
 | GOTO IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppJumpStatement_create(0, $2.sValue, 3, $1.sComment);
}
;

declaration_statement
 : block_declaration
{
  $$.pContext = adtCppDeclarationStatement_create($1.pContext);
}
;

declaration_seq
 : declaration
{
  $$.pContext = adtCppDeclarationSeq_create($1.pContext);
}
 | declaration_seq declaration
{
  $$.pContext = adtCppList_add($1.pContext, $2.pContext);
}
;

declaration
 : block_declaration
{
  $$.pContext = adtCppDeclaration_create($1.pContext, 0, 0, 0, 0);
}
 | function_definition
{
  $$.pContext = adtCppDeclaration_create(0, $1.pContext, 0, 0, 0);
}
 | linkage_specification
{
  $$.pContext = adtCppDeclaration_create(0, 0, $1.pContext, 0, 0);
}
 | namespace_definition
{
  $$.pContext = adtCppDeclaration_create(0, 0, 0, $1.pContext, 0);
}
 | SEMICOLON
{
  $$.pContext = adtCppDeclaration_create(0, 0, 0, 0, $1.sComment);
}
;

block_declaration
 : simple_declaration
{
  $$.pContext = adtCppBlockDeclaration_create($1.pContext, 0, 0, 0, 0);
}
 | asm_definition
{
  $$.pContext = adtCppBlockDeclaration_create(0, $1.pContext, 0, 0, 0);
}
 | namespace_alias_definition
{
  $$.pContext = adtCppBlockDeclaration_create(0, 0, $1.pContext, 0, 0);
}
 | using_declaration
{
  $$.pContext = adtCppBlockDeclaration_create(0, 0, 0, $1.pContext, 0);
}
 | using_directive
{
  $$.pContext = adtCppBlockDeclaration_create(0, 0, 0, 0, $1.pContext);
}
;

simple_declaration
 : class_specifier SEMICOLON
{
  $$.pContext = adtCppSimpleDeclaration_create($1.pContext, 0, 0, 0, 0, 0, 0);
}
 | enum_specifier SEMICOLON
{
  $$.pContext = adtCppSimpleDeclaration_create(0, $1.pContext, 0, 0, 0, 0, 0);
}
 | simple_type_specifier init_declarator_list SEMICOLON
{
  $$.pContext = adtCppSimpleDeclaration_create(0, 0, $1.pContext, $2.pContext, 0, 0, 0);
}
 | TYPEDEF simple_type_specifier init_declarator_list SEMICOLON
{
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, $2.pContext, $3.pContext, 0, 1, $1.sComment);

  $$.pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
 | decl_modifier_list simple_type_specifier init_declarator_list SEMICOLON
{
  $$.pContext = adtCppSimpleDeclaration_create(0, 0, $2.pContext, $3.pContext, $1.pContext, 0, 0);
}
 | TYPEDEF decl_modifier_list simple_type_specifier init_declarator_list SEMICOLON
{
  const char* pAliasName                = 0;
  void*       pCppSimpleDeclarationObj  = adtCppSimpleDeclaration_create(0, 0, $3.pContext, $4.pContext, $2.pContext, 1, $1.sComment);

  $$.pContext = pCppSimpleDeclarationObj;

  if (adtCppSimpleDeclaration_isTypeDef(pCppSimpleDeclarationObj, &pAliasName) != 0)
  {
    scopeManager_addType(adtCpp_ScopeManager, pAliasName);
  }
}
;

decl_modifier
 : AUTO
{
  $$.pContext = adtCppDeclModifier_create(0, $1.sComment);
}
 | REGISTER
{
  $$.pContext = adtCppDeclModifier_create(1, $1.sComment);
}
 | STATIC
{
  $$.pContext = adtCppDeclModifier_create(2, $1.sComment);
}
 | EXTERN
{
  $$.pContext = adtCppDeclModifier_create(3, $1.sComment);
}
 | MUTABLE
{
  $$.pContext = adtCppDeclModifier_create(4, $1.sComment);
}
 | INLINE
{
  $$.pContext = adtCppDeclModifier_create(5, $1.sComment);
}
 | VIRTUAL
{
  $$.pContext = adtCppDeclModifier_create(6, $1.sComment);
}
 | EXPLICIT
{
  $$.pContext = adtCppDeclModifier_create(7, $1.sComment);
}
 | CONST
{
  $$.pContext = adtCppDeclModifier_create(8, $1.sComment);
}
 | VOLATILE
{
  $$.pContext = adtCppDeclModifier_create(9, $1.sComment);
}
 | FRIEND
{
  $$.pContext = adtCppDeclModifier_create(10, $1.sComment);
}
;

decl_modifier_list
 : decl_modifier
{
  $$.pContext = adtCppDeclModifierList_create($1.pContext);
}
 | decl_modifier_list decl_modifier
{
  $$.pContext = adtCppList_add($1.pContext, $2.pContext);
}
;

class_specifier
 : class_key
{
  scopeManager_popScope(adtCpp_ScopeManager);

  $$.pContext = adtCppClassSpecifier_create($1.pContext, 0, 0, 0);
}
 | class_key LSBRACKET RSBRACKET
{
  scopeManager_popScope(adtCpp_ScopeManager);

  $$.pContext = adtCppClassSpecifier_create($1.pContext, 0, 0, 1);
}
 | class_key LSBRACKET member_specification RSBRACKET
{
  scopeManager_popScope(adtCpp_ScopeManager);

  $$.pContext = adtCppClassSpecifier_create($1.pContext, 0, $3.pContext, 1);
}
 | class_key COLON base_specifier_list LSBRACKET RSBRACKET
{
  scopeManager_popScope(adtCpp_ScopeManager);

  $$.pContext = adtCppClassSpecifier_create($1.pContext, $3.pContext, 0, 1);
}
 | class_key COLON base_specifier_list LSBRACKET member_specification RSBRACKET
{
  scopeManager_popScope(adtCpp_ScopeManager);

  $$.pContext = adtCppClassSpecifier_create($1.pContext, $3.pContext, $5.pContext, 1);
}
;

enum_specifier_name
 : ENUM IDENTIFIER
{
  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppEnumSpecifierName_create($2.sValue, 0, $1.sComment);
}
 | ENUM QUALIFIED_IDENTIFIER
{
  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppEnumSpecifierName_create($2.sValue, 1, $1.sComment);
}
 | ENUM OBJ_IDENTIFIER
{
  $$.pContext = adtCppEnumSpecifierName_create($2.sValue, 0, $1.sComment);
}
 | ENUM QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppEnumSpecifierName_create($2.sValue, 1, $1.sComment);
}
;

enum_specifier
 : enum_specifier_name
{
  $$.pContext = adtCppEnumSpecifier_create(0, $1.pContext, 0);
}
 | enum_specifier_name LSBRACKET RSBRACKET
{
  $$.pContext = adtCppEnumSpecifier_create(0, $1.pContext, 1);
}
 | enum_specifier_name LSBRACKET enumerator_list RSBRACKET
{
  $$.pContext = adtCppEnumSpecifier_create($3.pContext, $1.pContext, 1);
}
;

/* To eliminate grammar ambiguity it is necessary for the lexer and parser to
   keep track of object symbol names (basically class and typedef names) and
   if the IDENTIFIER found in lexing corresponds to an already defined type the
   lexer needs to return OBJ_IDENTIFIER rather than IDENTIFIER as the token.
   Only then can we disambiguate the use of Ampersands to define variable
   references from their use as logical and bitwise operators. */

simple_type_specifier
 : OBJ_IDENTIFIER
{
  $$.pContext = adtCppSimpleTypeSpecifier_create($1.sValue, 0, 0, $1.sComment);
}
 | QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppSimpleTypeSpecifier_create($1.sValue, 1, 0, $1.sComment);
}
 | WCHAR_T
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 2, 0, $1.sComment);
}
 | CHAR
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 3, 0, $1.sComment);
}
 | BOOL
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 4, 0, $1.sComment);
}
 | INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 5, 0, $1.sComment);
}
 | SHORT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 6, 0, $1.sComment);
}
 | SHORT INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 7, 0, $1.sComment);
}
 | LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 8, 0, $1.sComment);
}
 | LONG INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 9, 0, $1.sComment);
}
 | SIGNED
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 10, 0, $1.sComment);
}
 | SIGNED INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 11, 0, $1.sComment);
}
 | SIGNED SHORT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 12, 0, $1.sComment);
}
 | SIGNED SHORT INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 13, 0, $1.sComment);
}
 | SIGNED LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 14, 0, $1.sComment);
}
 | SIGNED LONG INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 15, 0, $1.sComment);
}
 | SIGNED CHAR
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 16, 0, $1.sComment);
}
 | UNSIGNED
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 17, 0, $1.sComment);
}
 | UNSIGNED INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 18, 0, $1.sComment);
}
 | UNSIGNED SHORT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 19, 0, $1.sComment);
}
 | UNSIGNED SHORT INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 20, 0, $1.sComment);
}
 | UNSIGNED LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 21, 0, $1.sComment);
}
 | UNSIGNED LONG INT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 22, 0, $1.sComment);
}
 | UNSIGNED CHAR
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 23, 0, $1.sComment);
}
 | FLOAT
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 24, 0, $1.sComment);
}
 | DOUBLE
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 25, 0, $1.sComment);
}
 | LONG DOUBLE
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 26, 0, $1.sComment);
}
 | LONG LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 27, 0, $1.sComment);
}
 | SIGNED LONG LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 28, 0, $1.sComment);
}
 | UNSIGNED LONG LONG
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 29, 0, $1.sComment);
}
 | VOID
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 30, 0, $1.sComment);
}
 | OBJ_IDENTIFIER AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create($1.sValue, 0, 1, $1.sComment);
}
 | QUALIFIED_OBJ_IDENTIFIER AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create($1.sValue, 1, 1, $1.sComment);
}
 | WCHAR_T AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 2, 1, $1.sComment);
}
 | CHAR AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 3, 1, $1.sComment);
}
 | BOOL AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 4, 1, $1.sComment);
}
 | INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 5, 1, $1.sComment);
}
 | SHORT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 6, 1, $1.sComment);
}
 | SHORT INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 7, 1, $1.sComment);
}
 | LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 8, 1, $1.sComment);
}
 | LONG INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 9, 1, $1.sComment);
}
 | SIGNED AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 10, 1, $1.sComment);
}
 | SIGNED INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 11, 1, $1.sComment);
}
 | SIGNED SHORT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 12, 1, $1.sComment);
}
 | SIGNED SHORT INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 13, 1, $1.sComment);
}
 | SIGNED LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 14, 1, $1.sComment);
}
 | SIGNED LONG INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 15, 1, $1.sComment);
}
 | SIGNED CHAR AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 16, 1, $1.sComment);
}
 | UNSIGNED AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 17, 1, $1.sComment);
}
 | UNSIGNED INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 18, 1, $1.sComment);
}
 | UNSIGNED SHORT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 19, 1, $1.sComment);
}
 | UNSIGNED SHORT INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 20, 1, $1.sComment);
}
 | UNSIGNED LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 21, 1, $1.sComment);
}
 | UNSIGNED LONG INT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 22, 1, $1.sComment);
}
 | UNSIGNED CHAR AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 23, 1, $1.sComment);
}
 | FLOAT AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 24, 1, $1.sComment);
}
 | DOUBLE AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 25, 1, $1.sComment);
}
 | LONG DOUBLE AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 26, 1, $1.sComment);
}
 | LONG LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 27, 1, $1.sComment);
}
 | SIGNED LONG LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 28, 1, $1.sComment);
}
 | UNSIGNED LONG LONG AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 29, 1, $1.sComment);
}
 | VOID AND
{
  $$.pContext = adtCppSimpleTypeSpecifier_create(0, 30, 1, $1.sComment);
}
;

enumerator_list
 : enumerator_definition
{
  $$.pContext = adtCppEnumeratorList_create($1.pContext);
}
 | enumerator_list COMMA enumerator_definition
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

enumerator_definition
 : IDENTIFIER
{
  $$.pContext = adtCppEnumeratorDefinition_create(0, $1.sValue, $1.sComment);
}
 | IDENTIFIER EQ constant_expression
{
  $$.pContext = adtCppEnumeratorDefinition_create($3.pContext, $1.sValue, $1.sComment);
}
;

namespace_definition
 : namespace_identifier LSBRACKET declaration_seq RSBRACKET
{
  $$.pContext = adtCppNamespaceDefinition_create($3.pContext, $1.sValue, $1.sComment);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | NAMESPACE LSBRACKET declaration_seq RSBRACKET
{
  $$.pContext = adtCppNamespaceDefinition_create($3.pContext, 0, $1.sComment);
}
;

namespace_identifier
 : NAMESPACE IDENTIFIER
{
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);

  $$.sValue   = $2.sValue;
  $$.sComment = $1.sComment;
};

namespace_alias_definition
 : NAMESPACE IDENTIFIER EQ QUALIFIED_IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppNamespaceAliasDefinition_create($2.sValue, $4.sValue, $1.sComment);
}
;

using_declaration
 : USING QUALIFIED_IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppUsingDeclaration_create($2.sValue, 0, $1.sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, $2.sValue);
}
 | USING TYPENAME QUALIFIED_IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppUsingDeclaration_create($3.sValue, 1, $1.sComment);

  scopeManager_addUsingDeclaration(adtCpp_ScopeManager, $3.sValue);
}
;

using_directive
 : USING NAMESPACE OBJ_IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppUsingDirective_create($3.sValue, 0, $1.sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, $3.sValue);
}
 | USING NAMESPACE QUALIFIED_OBJ_IDENTIFIER SEMICOLON
{
  $$.pContext = adtCppUsingDirective_create($3.sValue, 1, $1.sComment);

  scopeManager_addUsing(adtCpp_ScopeManager, $3.sValue);
}
;

asm_definition
 : ASM LSBRACKET STRING_LITERAL RSBRACKET SEMICOLON
{
  $$.pContext = adtCppAsmDefinition_create($3.sValue, $1.sComment);
}
;

linkage_specification
 : EXTERN STRING_LITERAL LSBRACKET RSBRACKET
{
  $$.pContext = adtCppLinkageSpecification_create(0, 0, $2.sValue, $1.sComment);
}
 | EXTERN STRING_LITERAL LSBRACKET declaration_seq RSBRACKET
{
  $$.pContext = adtCppLinkageSpecification_create($4.pContext, 0, $2.sValue, $1.sComment);
}
 | EXTERN STRING_LITERAL declaration
{
  $$.pContext = adtCppLinkageSpecification_create(0, $3.pContext, $2.sValue, $1.sComment);
}
;

init_declarator_list
 : init_declarator
{
  $$.pContext = adtCppInitDeclaratorList_create($1.pContext);
}
 | init_declarator_list COMMA init_declarator
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

init_declarator
 : var_declarator
{
  $$.pContext = adtCppInitDeclarator_create($1.pContext, 0);
}
 | var_declarator initializer
{
  $$.pContext = adtCppInitDeclarator_create($1.pContext, $2.pContext);
}
;

/* Fix me - I need to check the shift reduce conflicts this generates to make
 sure it is safe and if not find a solution */
declarator
 : var_declarator
{
  $$.pContext = $1.pContext;
}
 | fn_declarator
{
  $$.pContext = $1.pContext;
}
;

var_declarator
 : IDENTIFIER
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, $1.sValue, 0, 0, 0, 0, 0, $1.sComment, 1);
}
 | OBJ_IDENTIFIER
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, $1.sValue, 0, 0, 1, 0, 0, $1.sComment, 0);
}
 | QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, $1.sValue, 0, 1, 0, 0, 0, $1.sComment, 1);
}
 | QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, $1.sValue, 0, 1, 1, 0, 0, $1.sComment, 0);
}
 | IDENTIFIER declarator_dims
{
  $$.pContext = adtCppDeclarator_create(0, 0, $2.pContext, $1.sValue, 0, 0, 0, 0, 0, $1.sComment, 1);
}
 | QUALIFIED_IDENTIFIER declarator_dims
{
  $$.pContext = adtCppDeclarator_create(0, 0, $2.pContext, $1.sValue, 0, 1, 0, 0, 0, $1.sComment, 1);
};
/*
 These rules dealing with function variable declarations are excluded because
 there is no equivalent in Fortran and it results in a shift reduce conflict
 that hides function calls.
 | IDENTIFIER LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppDeclarator_create(0, $3.pContext, 0, $1.sValue, 1, 0, 0, 0, 0, $1.sComment, 1);

  adtCpp_pLastFunctionName = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue);
}
 | QUALIFIED_IDENTIFIER LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppDeclarator_create(0, $3.pContext, 0, $1.sValue, 1, 1, 0, 0, 0, $1.sComment, 1);

  adtCpp_pLastFunctionName = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue);
}
;
*/

/*
 We need to split the fn_declarator clause into a begin and end rule because
 we need to set the scope for class methods to the class, otherwise if we
 don't the map names process will fail on the comment dimension specifications
 in the argument list.
*/
fn_declarator
 : fn_declarator_begin fn_declarator_end
{
 $$.pContext = $2.pContext;
}
;

fn_declarator_begin
 : IDENTIFIER LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | OBJ_IDENTIFIER LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | QUALIFIED_IDENTIFIER LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 0;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | QUALIFIED_OBJ_IDENTIFIER LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | DTOR LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | QUALIFIED_DTOR LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $1.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $1.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 1;
  adtCpp_pLastFunctionIsVirtual   = 0;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
 | VIRTUAL DTOR LBRACKET
{
  adtCpp_pLastFunctionName        = adtCpp_AllocString(adtCpp_pCppContext, $2.sValue, 0);
  adtCpp_pLastFunctionComment     = adtCpp_AllocString(adtCpp_pCppContext, $2.sComment, 0);
  adtCpp_pLastFunctionIsObj       = 1;
  adtCpp_pLastFunctionIsQualified = 0;
  adtCpp_pLastFunctionIsVirtual   = 1;

  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
;

fn_declarator_end
 : RBRACKET
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | RBRACKET CONST
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | RBRACKET VOLATILE
{
  $$.pContext = adtCppDeclarator_create(0, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | parameter_declaration_clause RBRACKET
{
  $$.pContext = adtCppDeclarator_create($1.pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 0, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | parameter_declaration_clause RBRACKET CONST
{
  $$.pContext = adtCppDeclarator_create($1.pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 1, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | parameter_declaration_clause RBRACKET VOLATILE
{
  $$.pContext = adtCppDeclarator_create($1.pContext, 0, 0, adtCpp_pLastFunctionName, 1, adtCpp_pLastFunctionIsQualified, adtCpp_pLastFunctionIsObj, adtCpp_pLastFunctionIsVirtual, 2, adtCpp_pLastFunctionComment, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
;

declarator_dims
 : LSQBRACKET RSQBRACKET
{
  $$.pContext = adtCppDeclaratorDims_create(0, 0);
}
 | LSQBRACKET constant_expression RSQBRACKET
{
  $$.pContext = adtCppDeclaratorDims_create($2.pContext, 0);
}
 | declarator_dims LSQBRACKET RSQBRACKET
{
  $$.pContext = adtCppDeclaratorDims_create(0, $1.pContext);
}
 | declarator_dims LSQBRACKET constant_expression RSQBRACKET
{
  $$.pContext = adtCppDeclaratorDims_create($3.pContext, $1.pContext);
}
;

parameter_declaration_clause
 : ELLIPSIS
{
  $$.pContext = adtCppParameterDeclarationClause_create(0, 1, 0);
}
 | parameter_declaration_list
{
  $$.pContext = adtCppParameterDeclarationClause_create($1.pContext, 0, 0);
}
 | parameter_declaration_list ELLIPSIS
{
  $$.pContext = adtCppParameterDeclarationClause_create($1.pContext, 1, 0);
}
 | parameter_declaration_list COMMA ELLIPSIS
{
  $$.pContext = adtCppParameterDeclarationClause_create($1.pContext, 1, 1);
}
;

parameter_declaration_list
 : parameter_declaration
{
  $$.pContext = adtCppParameterDeclarationList_create($1.pContext);
}
 | parameter_declaration_list COMMA parameter_declaration
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

parameter_declaration
 : simple_type_specifier declarator
{
  $$.pContext = adtCppParameterDeclaration_create(0, $1.pContext, $2.pContext, 0);
}
 | decl_modifier_list simple_type_specifier declarator
{
  $$.pContext = adtCppParameterDeclaration_create($1.pContext, $2.pContext, $3.pContext, 0);
}
 | simple_type_specifier declarator EQ assignment_expression
{
  $$.pContext = adtCppParameterDeclaration_create(0, $1.pContext, $2.pContext, $4.pContext);
}
 | decl_modifier_list simple_type_specifier declarator EQ assignment_expression
{
  $$.pContext = adtCppParameterDeclaration_create($1.pContext, $2.pContext, $3.pContext, $5.pContext);
}
 | simple_type_specifier
{
  $$.pContext = adtCppParameterDeclaration_create(0, $1.pContext, 0, 0);
}
 | decl_modifier_list simple_type_specifier
{
  $$.pContext = adtCppParameterDeclaration_create($1.pContext, $2.pContext, 0, 0);
}
;

function_definition
 : fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, 0, 0, 1);
}
 | simple_type_specifier fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, $1.pContext, $2.pContext, 0, 0, 1);
}
 | decl_modifier_list simple_type_specifier fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create($1.pContext, $2.pContext, $3.pContext, 0, 0, 1);
}
 | fn_declarator function_body
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, 0, $2.pContext, 0);
}
 | fn_declarator ctor_initializer function_body
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, $2.pContext, $3.pContext, 0);
}
 | simple_type_specifier fn_declarator function_body
{
  $$.pContext = adtCppFunctionDefinition_create(0, $1.pContext, $2.pContext, 0, $3.pContext, 0);
}
 | decl_modifier_list simple_type_specifier fn_declarator function_body
{
  $$.pContext = adtCppFunctionDefinition_create($1.pContext, $2.pContext, $3.pContext, 0, $4.pContext, 0);
}
;

class_function_definition
 : fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, 0, 0, 1);
}
 | simple_type_specifier fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, $1.pContext, $2.pContext, 0, 0, 1);
}
 | decl_modifier_list simple_type_specifier fn_declarator SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create($1.pContext, $2.pContext, $3.pContext, 0, 0, 1);
}
 | fn_declarator function_body SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, 0, $2.pContext, 1);
}
 | fn_declarator ctor_initializer function_body SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, 0, $1.pContext, $2.pContext, $3.pContext, 1);
}
 | simple_type_specifier fn_declarator function_body SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create(0, $1.pContext, $2.pContext, 0, $3.pContext, 1);
}
 | decl_modifier_list simple_type_specifier fn_declarator function_body SEMICOLON
{
  $$.pContext = adtCppFunctionDefinition_create($1.pContext, $2.pContext, $3.pContext, 0, $4.pContext, 1);
}
;

/* Note that we break the function body up into start and end so that we can
   correctly manage scope. We need to break the compound statement apart so
   we have a point to push and pop scope. */
function_body
 : function_body_start function_body_end
{
  $$.pContext = adtCppFunctionBody_create($2.pContext);
}
;

function_body_start
 : LSBRACKET
{
  scopeManager_pushScope(adtCpp_ScopeManager, adtCpp_pLastFunctionName, 1);
}
;

function_body_end
 : RSBRACKET
{
  $$.pContext = adtCppCompoundStatement_create(0, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
 | statement_seq RSBRACKET
{
  $$.pContext = adtCppCompoundStatement_create($1.pContext, 0);

  scopeManager_popScope(adtCpp_ScopeManager);
}
;

initializer
 : EQ initializer_clause
{
  $$.pContext = adtCppInitializer_create($2.pContext, 0);
}
 | LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppInitializer_create(0, $2.pContext);
}
;

initializer_clause
 : assignment_expression
{
  $$.pContext = adtCppInitializerClause_create($1.pContext, 0, 0);
}
 | LSBRACKET initializer_list RSBRACKET
{
  $$.pContext = adtCppInitializerClause_create(0, $2.pContext, 0);
}
 | LSBRACKET initializer_list COMMA RSBRACKET
{
  $$.pContext = adtCppInitializerClause_create(0, $2.pContext, 1);
}
 | LSBRACKET RSBRACKET
{
  $$.pContext = adtCppInitializerClause_create(0, 0, 0);
}
;

initializer_list
 : initializer_clause
{
  $$.pContext = adtCppInitializerList_create($1.pContext);
}
 | initializer_list COMMA initializer_clause
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

class_key
 : CLASS IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(0, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | CLASS OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(0, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | CLASS QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(0, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | CLASS QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(0, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | STRUCT IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(1, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | STRUCT OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(1, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | STRUCT QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(1, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | STRUCT QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(1, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | UNION IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(2, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | UNION OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(2, $2.sValue, 0, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | UNION QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(2, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
 | UNION QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppClassKey_create(2, $2.sValue, 1, $1.sComment);

  scopeManager_addType(adtCpp_ScopeManager, $2.sValue);
  scopeManager_pushScope(adtCpp_ScopeManager, $2.sValue, 0);
}
;

member_specification
 : member_declaration
{
  $$.pContext = adtCppMemberSpecification_create($1.pContext);
}
 | member_specification member_declaration
{
  $$.pContext = adtCppList_add($1.pContext, $2.pContext);
}
;

member_declaration
 : simple_type_specifier member_declarator_list SEMICOLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, $1.pContext, $2.pContext, 0, 0, 0, 1);
}
 | decl_modifier_list simple_type_specifier member_declarator_list SEMICOLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, $1.pContext, $2.pContext, $3.pContext, 0, 0, 0, 1);
}
 | class_function_definition
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, $1.pContext, 0, 0, 0);
}
 | using_declaration
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, $1.pContext, 0, 0);
}
 | class_specifier SEMICOLON
{
  $$.pContext = adtCppMemberDeclaration_create($1.pContext, 0, 0, 0, 0, 0, 0, 0, 1);
}
 | enum_specifier SEMICOLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, $1.pContext, 0, 0, 0, 0, 0, 0, 1);
}
 | PRIVATE   COLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 1, 0);
}
 | PROTECTED COLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 2, 0);
}
 | PUBLIC    COLON
{
  $$.pContext = adtCppMemberDeclaration_create(0, 0, 0, 0, 0, 0, 0, 3, 0);
}
;

member_declarator_list
 : member_declarator
{
  $$.pContext = adtCppMemberDeclarationList_create($1.pContext);
}
 | member_declarator_list COMMA member_declarator
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

member_declarator
 : var_declarator
{
  $$.pContext = adtCppMemberDeclarator_create($1.pContext, 0);
}
 | var_declarator EQ IDENTIFIER
{
  $$.pContext = adtCppMemberDeclarator_create($1.pContext, $3.sValue);
}
;

base_specifier_list
 : base_specifier
{
  $$.pContext = adtCppBaseSpecifierList_create($1.pContext);
}
 | base_specifier_list COMMA base_specifier
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

base_specifier
 : OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $1.sValue);

  $$.pContext = adtCppBaseSpecifier_create(0, 0, 0, $1.sValue);
}
 | PRIVATE   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 0, 0, $2.sValue);
}
 | PROTECTED OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 0, 0, $2.sValue);
}
 | PUBLIC    OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 0, 0, $2.sValue);
}
 | QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $1.sValue);

  $$.pContext = adtCppBaseSpecifier_create(0, 0, 1, $1.sValue);
}
 | PRIVATE   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 0, 1, $2.sValue);
}
 | PROTECTED QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 0, 1, $2.sValue);
}
 | PUBLIC    QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 0, 1, $2.sValue);
}
 | VIRTUAL   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(0, 1, 0, $2.sValue);
}
 | VIRTUAL   PRIVATE   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 1, 0, $3.sValue);
}
 | VIRTUAL   PROTECTED OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 1, 0, $3.sValue);
}
 | VIRTUAL   PUBLIC    OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 1, 0, $3.sValue);
}
 | VIRTUAL   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $2.sValue);

  $$.pContext = adtCppBaseSpecifier_create(0, 1, 1, $2.sValue);
}
 | VIRTUAL   PRIVATE   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 1, 1, $3.sValue);
}
 | VIRTUAL   PROTECTED QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 1, 1, $3.sValue);
}
 | VIRTUAL   PUBLIC    QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 1, 1, $3.sValue);
}
 | PRIVATE   VIRTUAL   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 1, 0, $3.sValue);
}
 | PROTECTED VIRTUAL   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 1, 0, $3.sValue);
}
 | PUBLIC    VIRTUAL   OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 1, 0, $3.sValue);
}
 | PRIVATE   VIRTUAL   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(1, 1, 1, $3.sValue);
}
 | PROTECTED VIRTUAL   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(2, 1, 1, $3.sValue);
}
 | PUBLIC    VIRTUAL   QUALIFIED_OBJ_IDENTIFIER
{
  scopeManager_inheritsFrom(adtCpp_ScopeManager, $3.sValue);

  $$.pContext = adtCppBaseSpecifier_create(3, 1, 1, $3.sValue);
}
;

ctor_initializer
 : COLON mem_initializer_list
{
  $$.pContext = adtCppCtorInitializer_create($2.pContext);
}
;

mem_initializer_list
 : mem_initializer
{
  $$.pContext = adtCppMemInitializerList_create($1.pContext);
}
 | mem_initializer_list COMMA mem_initializer
{
  $$.pContext = adtCppList_add($1.pContext, $3.pContext);
}
;

mem_initializer
 : mem_initializer_id LBRACKET RBRACKET
{
  $$.pContext = adtCppMemInitializer_create($1.pContext, 0);
}
 | mem_initializer_id LBRACKET expression_list RBRACKET
{
  $$.pContext = adtCppMemInitializer_create($1.pContext, $3.pContext);
}
;

mem_initializer_id
 : IDENTIFIER
{
  $$.pContext = adtCppMemInitializerId_create(0, $1.sValue);
}
 | QUALIFIED_IDENTIFIER
{
  $$.pContext = adtCppMemInitializerId_create(1, $1.sValue);
}
 | OBJ_IDENTIFIER
{
  $$.pContext = adtCppMemInitializerId_create(0, $1.sValue);
}
 | QUALIFIED_OBJ_IDENTIFIER
{
  $$.pContext = adtCppMemInitializerId_create(1, $1.sValue);
}
;
