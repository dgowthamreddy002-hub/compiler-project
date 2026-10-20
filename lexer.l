%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
static int lexer_line = 1;
static int lexer_column = 1;
static int saw_input = 0;
static int last_character_was_newline = 0;
static int emitted_final_newline = 0;
#define YY_USER_ACTION \
    do { \
        saw_input = 1; \
        yylloc.first_line = lexer_line; \
        yylloc.first_column = lexer_column; \
        yylloc.last_line = lexer_line; \
        yylloc.last_column = lexer_column + yyleng; \
        for (int i = 0; i < yyleng; i++) { \
            last_character_was_newline = (yytext[i] == '\n'); \
            if (yytext[i] == '\n') { lexer_line++; lexer_column = 1; } \
            else lexer_column++; \
        } \
    } while (0);
%}

%option noyywrap

%%
[0-9]+                         {
                                    errno = 0;
                                    long value = strtol(yytext, NULL, 10);
                                    if (errno == ERANGE || value > INT_MAX) {
                                        fprintf(stderr, "Lexical error at line %d, column %d: integer literal is outside the supported range (0 to %d)\n",
                                            yylloc.first_line, yylloc.first_column, INT_MAX);
                                        return INVALID;
                                    }
                                    yylval.num = (int)value;
                                    printf("TOKEN: NUMBER | Lexeme: %s\n", yytext);
                                    return NUMBER;
                                }
[a-zA-Z_][a-zA-Z0-9_]*         { yylval.str = strdup(yytext); printf("TOKEN: IDENTIFIER | Lexeme: %s\n", yytext); return IDENTIFIER; }
"//"[^\n]*                    ;
[ \t\r]+                       ;
\n                             { puts("TOKEN: STATEMENT_DELIMITER | Lexeme: \\n"); return NEWLINE; }
[-+*/%]                        { printf("TOKEN: ARITHMETIC_OPERATOR | Lexeme: %s\n", yytext); return yytext[0]; }
=                              { printf("TOKEN: ASSIGNMENT_OPERATOR | Lexeme: %s\n", yytext); return yytext[0]; }
[()]                           { printf("TOKEN: PARENTHESIS | Lexeme: %s\n", yytext); return yytext[0]; }
.                              { fprintf(stderr, "Lexical error at line %d, column %d: unexpected character '%s'\n", yylloc.first_line, yylloc.first_column, yytext); return INVALID; }
<<EOF>>                        {
                                    if (saw_input && !last_character_was_newline && !emitted_final_newline) {
                                        emitted_final_newline = 1;
                                        yylloc.first_line = yylloc.last_line = lexer_line;
                                        yylloc.first_column = lexer_column;
                                        yylloc.last_column = lexer_column + 1;
                                        puts("TOKEN: STATEMENT_DELIMITER | Lexeme: \\n");
                                        return NEWLINE;
                                    }
                                    return 0;
                                }
%%
