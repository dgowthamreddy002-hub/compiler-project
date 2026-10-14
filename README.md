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

Assignments introduce variables. Referencing a variable before its first successful assignment is a semantic error. Supported operators are unary `+` and `-`, binary `+`, `-`, `*`, `/`, and parentheses. `//` starts a line comment.

The compiler prints TAC as it compiles each line. For the example above, the output includes:

```text
t0 = 5 * 2
t1 = 4 + t0
a = t1
```
