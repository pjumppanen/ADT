/* 
Bison Flex macro replacements for cpp lexical scanner
*/
#ifndef __CPP_INC_H__
#define __CPP_INC_H__


#define yyparse               yyCppparse
#define yypop_buffer_state    yyCpppop_buffer_state
#define yyget_lineno          yyCppget_lineno
#define yyget_in              yyCppget_in
#define yyget_out             yyCppget_out
#define yyget_leng            yyCppget_leng
#define yyget_text            yyCppget_text
#define yyset_lineno          yyCppset_lineno
#define yyset_in              yyCppset_in
#define yyset_out             yyCppset_out
#define yyget_debug           yyCppget_debug
#define yyset_debug           yyCppset_debug
#define yylex_destroy         yyCpplex_destroy
#define yypush_buffer_state   yyCpppush_buffer_state
#define yyfree                yyCppfree
#define yyalloc               yyCppalloc
#define yyrealloc             yyCpprealloc
#define yylineno              yyCpplineno
#define yyerror               yyCpperror

#define yy_create_buffer      yyCpp_create_buffer
#define yy_delete_buffer      yyCpp_delete_buffer
#define yy_scan_buffer        yyCpp_scan_buffer
#define yy_scan_string        yyCpp_scan_string
#define yy_scan_bytes         yyCpp_scan_bytes
#define yy_flex_debug         yyCpp_flex_debug
#define yy_init_buffer        yyCpp_init_buffer
#define yy_flush_buffer       yyCpp_flush_buffer
#define yy_load_buffer_state  yyCpp_load_buffer_state
#define yy_switch_to_buffer   yyCpp_switch_to_buffer
#define yyin                  yyCppin
#define yydebug               yyCppdebug
#define yyleng                yyCppleng
#define yylex                 yyCpplex
#define yyout                 yyCppout
#define yyrestart             yyCpprestart
#define yytext                yyCpptext
#define yywrap                yyCppwrap
#define yynerrs               yyCppnerrs
#define yychar                yyCppchar
#define yylval                yyCpplval

#define dispatchToken         yyCpp_dispatchToken
#define commenteof            yyCpp_commenteof
#define growBuffer            yyCpp_growBuffer
#define mallocScanComment     yyCpp_mallocScanComment

#define YYSTYPE   cppType


#endif
