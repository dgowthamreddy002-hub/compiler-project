%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

%%
[0-9]+                         { yylval.num = (int)strtol(yytext, NULL, 10); printf("TOKEN: NUMBER | Lexeme: %s\n", yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*         { yylval.str = strdup(yytext); printf("TOKEN: IDENTIFIER | Lexeme: %s\n", yytext); return IDENTIFIER; }
"//"[^\n]*                    ;
[ \t\r]+                       ;
\n                             { puts("TOKEN: STATEMENT_DELIMITER | Lexeme: \\n"); return NEWLINE; }
[-+*/%]                        { printf("TOKEN: ARITHMETIC_OPERATOR | Lexeme: %s\n", yytext); return yytext[0]; }
=                              { printf("TOKEN: ASSIGNMENT_OPERATOR | Lexeme: %s\n", yytext); return yytext[0]; }
[()]                           { printf("TOKEN: PARENTHESIS | Lexeme: %s\n", yytext); return yytext[0]; }
.                              { fprintf(stderr, "Lexical error: unexpected character '%s'\n", yytext); return INVALID; }
%%
