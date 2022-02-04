/* 
Bison Flex macro replacements for make lexical scanner
*/
#ifndef __EXPRESSION_INC_H__
#define __EXPRESSION_INC_H__


#define yyparse               yyExpressionparse
#define yypop_buffer_state    yyExpressionpop_buffer_state
#define yyget_lineno          yyExpressionget_lineno
#define yyget_in              yyExpressionget_in
#define yyget_out             yyExpressionget_out
#define yyget_leng            yyExpressionget_leng
#define yyget_text            yyExpressionget_text
#define yyset_lineno          yyExpressionset_lineno
#define yyset_in              yyExpressionset_in
#define yyset_out             yyExpressionset_out
#define yyget_debug           yyExpressionget_debug
#define yyset_debug           yyExpressionset_debug
#define yylex_destroy         yyExpressionlex_destroy
#define yypush_buffer_state   yyExpressionpush_buffer_state
#define yyfree                yyExpressionfree
#define yyalloc               yyExpressionalloc
#define yyrealloc             yyExpressionrealloc
#define yylineno              yyExpressionlineno
#define yyerror               yyExpressionerror

#define yy_create_buffer      yyExpression_create_buffer
#define yy_delete_buffer      yyExpression_delete_buffer
#define yy_scan_buffer        yyExpression_scan_buffer
#define yy_scan_string        yyExpression_scan_string
#define yy_scan_bytes         yyExpression_scan_bytes
#define yy_flex_debug         yyExpression_flex_debug
#define yy_init_buffer        yyExpression_init_buffer
#define yy_flush_buffer       yyExpression_flush_buffer
#define yy_load_buffer_state  yyExpression_load_buffer_state
#define yy_switch_to_buffer   yyExpression_switch_to_buffer
#define yyin                  yyExpressionin
#define yydebug               yyExpressiondebug
#define yyleng                yyExpressionleng
#define yylex                 yyExpressionlex
#define yyout                 yyExpressionout
#define yyrestart             yyExpressionrestart
#define yytext                yyExpressiontext
#define yywrap                yyExpressionwrap
#define yynerrs               yyExpressionnerrs
#define yychar                yyExpressionchar
#define yylval                yyExpressionlval


#define dispatchToken         yyExpression_dispatchToken
#define commenteof            yyExpression_commenteof
#define growBuffer            yyExpression_growBuffer
#define mallocScanComment     yyExpression_mallocScanComment

#define YYSTYPE   expressionType


#endif
