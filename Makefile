CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L

.PHONY: all test clean

all: compiler

test: compiler
	sh tests/run_tests.sh

compiler: lex.yy.c parser.tab.c parser.tab.h
	$(CC) $(CFLAGS) -o $@ lex.yy.c parser.tab.c -lfl

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex -o $@ lexer.l

clean:
	rm -f compiler lex.yy.c parser.tab.c parser.tab.h
