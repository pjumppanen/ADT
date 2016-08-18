/* 
Bison Flex macro replacements for delphi lexical scanner
*/
#ifndef __DELPHI_INC_H__
#define __DELPHI_INC_H__


#define yyparse               yyDelphiparse
#define yypop_buffer_state    yyDelphipop_buffer_state
#define yyget_lineno          yyDelphiget_lineno
#define yyget_in              yyDelphiget_in
#define yyget_out             yyDelphiget_out
#define yyget_leng            yyDelphiget_leng
#define yyget_text            yyDelphiget_text
#define yyset_lineno          yyDelphiset_lineno
#define yyset_in              yyDelphiset_in
#define yyset_out             yyDelphiset_out
#define yyget_debug           yyDelphiget_debug
#define yyset_debug           yyDelphiset_debug
#define yylex_destroy         yyDelphilex_destroy
#define yypush_buffer_state   yyDelphipush_buffer_state
#define yyfree                yyDelphifree
#define yyalloc               yyDelphialloc
#define yyrealloc             yyDelphirealloc
#define yylineno              yyDelphilineno
#define yyerror               yyDelphierror

#define yy_create_buffer      yyDelphi_create_buffer
#define yy_delete_buffer      yyDelphi_delete_buffer
#define yy_scan_buffer        yyDelphi_scan_buffer
#define yy_scan_string        yyDelphi_scan_string
#define yy_scan_bytes         yyDelphi_scan_bytes
#define yy_flex_debug         yyDelphi_flex_debug
#define yy_init_buffer        yyDelphi_init_buffer
#define yy_flush_buffer       yyDelphi_flush_buffer
#define yy_load_buffer_state  yyDelphi_load_buffer_state
#define yy_switch_to_buffer   yyDelphi_switch_to_buffer
#define yyin                  yyDelphiin
#define yydebug               yyDelphidebug
#define yyleng                yyDelphileng
#define yylex                 yyDelphilex
#define yyout                 yyDelphiout
#define yyrestart             yyDelphirestart
#define yytext                yyDelphitext
#define yywrap                yyDelphiwrap

#define dispatchToken         yyDelphi_dispatchToken
#define commenteof            yyDelphi_commenteof
#define growBuffer            yyDelphi_growBuffer
#define mallocScanComment     yyDelphi_mallocScanComment

#define YYSTYPE   delphiType


#endif
