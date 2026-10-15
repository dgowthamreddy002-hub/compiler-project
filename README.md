# Arithmetic Expression Compiler

A small compiler for line based arithmetic expressions, implemented with Flex and Bison. It builds an expression tree, checks that variables have been assigned before use, and emits three address code (TAC).

## Build

Install GCC, Flex, Bison, and the Flex runtime library, then run:

```sh
make
```

## Run

Pass a source file through standard input:

```sh
./compiler < program.expr
```

Or start `./compiler` and type statements. Each statement is an expression or an assignment, one per line. Use `Ctrl-D` to finish input.

```text
a = 4 + 5 * 2
b = (a - 3) / 2
b
```

Assignments introduce variables. Referencing a variable before its first successful assignment is a semantic error. Supported operators are unary `+` and `-`, binary `+`, `-`, `*`, `/`, `%` (integer remainder), and parentheses. Multiplication, division, and remainder share precedence. `//` starts a line comment.

The compiler prints categorized tokens with their lexemes (number, identifier, arithmetic operator, assignment operator, parenthesis, or statement delimiter), then an abstract syntax tree (AST) for each line, followed by TAC. The lexer labels `+` and `-` as arithmetic operators; the parser determines whether they are unary or binary from context. The AST shows operator grouping and precedence; it is not a concrete parse tree, so grammar-only details such as parentheses are omitted. Each run also writes an HTML view of the AST to `parse_tree.html` in the current directory. When run from a terminal, the compiler asks whether to open that file in the system browser. Answer `y` to open it; the file is replaced on the next run.

For the example above, TAC includes:

```text
t0 = 5 * 2
t1 = 4 + t0
a = t1
```
