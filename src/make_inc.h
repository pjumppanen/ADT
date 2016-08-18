/* 
Bison Flex macro replacements for make lexical scanner
*/
#ifndef __MAKE_INC_H__
#define __MAKE_INC_H__


#define yyparse               yyMakeparse
#define yypop_buffer_state    yyMakepop_buffer_state
#define yyget_lineno          yyMakeget_lineno
#define yyget_in              yyMakeget_in
#define yyget_out             yyMakeget_out
#define yyget_leng            yyMakeget_leng
#define yyget_text            yyMakeget_text
#define yyset_lineno          yyMakeset_lineno
#define yyset_in              yyMakeset_in
#define yyset_out             yyMakeset_out
#define yyget_debug           yyMakeget_debug
#define yyset_debug           yyMakeset_debug
#define yylex_destroy         yyMakelex_destroy
#define yypush_buffer_state   yyMakepush_buffer_state
#define yyfree                yyMakefree
#define yyalloc               yyMakealloc
#define yyrealloc             yyMakerealloc
#define yylineno              yyMakelineno
#define yyerror               yyMakeerror

#define yy_create_buffer      yyMake_create_buffer
#define yy_delete_buffer      yyMake_delete_buffer
#define yy_scan_buffer        yyMake_scan_buffer
#define yy_scan_string        yyMake_scan_string
#define yy_scan_bytes         yyMake_scan_bytes
#define yy_flex_debug         yyMake_flex_debug
#define yy_init_buffer        yyMake_init_buffer
#define yy_flush_buffer       yyMake_flush_buffer
#define yy_load_buffer_state  yyMake_load_buffer_state
#define yy_switch_to_buffer   yyMake_switch_to_buffer
#define yyin                  yyMakein
#define yydebug               yyMakedebug
#define yyleng                yyMakeleng
#define yylex                 yyMakelex
#define yyout                 yyMakeout
#define yyrestart             yyMakerestart
#define yytext                yyMaketext
#define yywrap                yyMakewrap

#define dispatchToken         yyMake_dispatchToken
#define commenteof            yyMake_commenteof
#define growBuffer            yyMake_growBuffer
#define mallocScanComment     yyMake_mallocScanComment

#define YYSTYPE   makeType


#endif
