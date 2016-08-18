/*
Bison Flex macro replacements for make lexical scanner
*/
#ifndef __BLACK_BOX_INC_H__
#define __BLACK_BOX_INC_H__


#define yyparse               yyBlackBoxparse
#define yypop_buffer_state    yyBlackBoxpop_buffer_state
#define yyget_lineno          yyBlackBoxget_lineno
#define yyget_in              yyBlackBoxget_in
#define yyget_out             yyBlackBoxget_out
#define yyget_leng            yyBlackBoxget_leng
#define yyget_text            yyBlackBoxget_text
#define yyset_lineno          yyBlackBoxset_lineno
#define yyset_in              yyBlackBoxset_in
#define yyset_out             yyBlackBoxset_out
#define yyget_debug           yyBlackBoxget_debug
#define yyset_debug           yyBlackBoxset_debug
#define yylex_destroy         yyBlackBoxlex_destroy
#define yypush_buffer_state   yyBlackBoxpush_buffer_state
#define yyfree                yyBlackBoxfree
#define yyalloc               yyBlackBoxalloc
#define yyrealloc             yyBlackBoxrealloc
#define yylineno              yyBlackBoxlineno
#define yyerror               yyBlackBoxerror

#define yy_create_buffer      yyBlackBox_create_buffer
#define yy_delete_buffer      yyBlackBox_delete_buffer
#define yy_scan_buffer        yyBlackBox_scan_buffer
#define yy_scan_string        yyBlackBox_scan_string
#define yy_scan_bytes         yyBlackBox_scan_bytes
#define yy_flex_debug         yyBlackBox_flex_debug
#define yy_init_buffer        yyBlackBox_init_buffer
#define yy_flush_buffer       yyBlackBox_flush_buffer
#define yy_load_buffer_state  yyBlackBox_load_buffer_state
#define yy_switch_to_buffer   yyBlackBox_switch_to_buffer
#define yyin                  yyBlackBoxin
#define yydebug               yyBlackBoxdebug
#define yyleng                yyBlackBoxleng
#define yylex                 yyBlackBoxlex
#define yyout                 yyBlackBoxout
#define yyrestart             yyBlackBoxrestart
#define yytext                yyBlackBoxtext
#define yywrap                yyBlackBoxwrap

#define dispatchToken         yyBlackBox_dispatchToken
#define commenteof            yyBlackBox_commenteof
#define growBuffer            yyBlackBox_growBuffer
#define mallocScanComment     yyBlackBox_mallocScanComment

#define YYSTYPE   blackBoxType


#endif
