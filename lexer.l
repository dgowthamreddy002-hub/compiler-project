%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

%%
[0-9]+                         { yylval.num = (int)strtol(yytext, NULL, 10); printf("TOKEN NUMBER(%s)\n", yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*         { yylval.str = strdup(yytext); printf("TOKEN IDENTIFIER(%s)\n", yytext); return IDENTIFIER; }
"//"[^\n]*                    ;
[ \t\r]+                       ;
\n                             { puts("TOKEN NEWLINE"); return NEWLINE; }
[-+*/=()]                      { printf("TOKEN '%c'\n", yytext[0]); return yytext[0]; }
.                              { fprintf(stderr, "Lexical error: unexpected character '%s'\n", yytext); return INVALID; }
%%
