/* 
Bison Flex macro replacements for fortran lexical scanner
*/
#ifndef __FORTRAN_INC_H__
#define __FORTRAN_INC_H__


#define yyparse               yyFortranparse
#define yypop_buffer_state    yyFortranpop_buffer_state
#define yyget_lineno          yyFortranget_lineno
#define yyget_in              yyFortranget_in
#define yyget_out             yyFortranget_out
#define yyget_leng            yyFortranget_leng
#define yyget_text            yyFortranget_text
#define yyset_lineno          yyFortranset_lineno
#define yyset_in              yyFortranset_in
#define yyset_out             yyFortranset_out
#define yyget_debug           yyFortranget_debug
#define yyset_debug           yyFortranset_debug
#define yylex_destroy         yyFortranlex_destroy
#define yypush_buffer_state   yyFortranpush_buffer_state
#define yyfree                yyFortranfree
#define yyalloc               yyFortranalloc
#define yyrealloc             yyFortranrealloc
#define yylineno              yyFortranlineno
#define yyerror               yyFortranerror

#define yy_create_buffer      yyFortran_create_buffer
#define yy_delete_buffer      yyFortran_delete_buffer
#define yy_scan_buffer        yyFortran_scan_buffer
#define yy_scan_string        yyFortran_scan_string
#define yy_scan_bytes         yyFortran_scan_bytes
#define yy_flex_debug         yyFortran_flex_debug
#define yy_init_buffer        yyFortran_init_buffer
#define yy_flush_buffer       yyFortran_flush_buffer
#define yy_load_buffer_state  yyFortran_load_buffer_state
#define yy_switch_to_buffer   yyFortran_switch_to_buffer
#define yyin                  yyFortranin
#define yydebug               yyFortrandebug
#define yyleng                yyFortranleng
#define yylex                 yyFortranlex
#define yyout                 yyFortranout
#define yyrestart             yyFortranrestart
#define yytext                yyFortrantext
#define yywrap                yyFortranwrap

#define dispatchToken         yyFortran_dispatchToken
#define commenteof            yyFortran_commenteof
#define growBuffer            yyFortran_growBuffer
#define mallocScanComment     yyFortran_mallocScanComment

#define YYSTYPE   fortranType


#endif
