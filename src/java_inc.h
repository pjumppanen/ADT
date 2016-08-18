/* 
Bison Flex macro replacements for fortran lexical scanner
*/
#ifndef __JAVA_INC_H__
#define __JAVA_INC_H__


#define yyparse               yyJavaparse
#define yypop_buffer_state    yyJavapop_buffer_state
#define yyget_lineno          yyJavaget_lineno
#define yyget_in              yyJavaget_in
#define yyget_out             yyJavaget_out
#define yyget_leng            yyJavaget_leng
#define yyget_text            yyJavaget_text
#define yyset_lineno          yyJavaset_lineno
#define yyset_in              yyJavaset_in
#define yyset_out             yyJavaset_out
#define yyget_debug           yyJavaget_debug
#define yyset_debug           yyJavaset_debug
#define yylex_destroy         yyJavalex_destroy
#define yypush_buffer_state   yyJavapush_buffer_state
#define yyfree                yyJavafree
#define yyalloc               yyJavaalloc
#define yyrealloc             yyJavarealloc
#define yylineno              yyJavalineno
#define yyerror               yyJavaerror

#define yy_create_buffer      yyJava_create_buffer
#define yy_delete_buffer      yyJava_delete_buffer
#define yy_scan_buffer        yyJava_scan_buffer
#define yy_scan_string        yyJava_scan_string
#define yy_scan_bytes         yyJava_scan_bytes
#define yy_flex_debug         yyJava_flex_debug
#define yy_init_buffer        yyJava_init_buffer
#define yy_flush_buffer       yyJava_flush_buffer
#define yy_load_buffer_state  yyJava_load_buffer_state
#define yy_switch_to_buffer   yyJava_switch_to_buffer
#define yyin                  yyJavain
#define yydebug               yyJavadebug
#define yyleng                yyJavaleng
#define yylex                 yyJavalex
#define yyout                 yyJavaout
#define yyrestart             yyJavarestart
#define yytext                yyJavatext
#define yywrap                yyJavawrap

#define dispatchToken         yyJava_dispatchToken
#define commenteof            yyJava_commenteof
#define growBuffer            yyJava_growBuffer
#define mallocScanComment     yyJava_mallocScanComment

#define YYSTYPE   javaType


#endif
