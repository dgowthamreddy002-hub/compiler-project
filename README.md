# Arithmetic Expression Compiler

A small compiler for line-based arithmetic expressions, implemented with Flex and Bison. It builds a concrete grammar parse tree for display and a separate AST for analysis, checks variable use and constant division/remainder by zero, then emits three address code (TAC).

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

Run the built-in checks with `make test`. Example input files are in `examples/`.

Or start `./compiler` and type statements. Each statement is an expression or an assignment, one per line. Use `Ctrl-D` to finish input.

```text
a = 4 + 5 * 2
b = (a - 3) / 2
b
```

Assignments introduce variables. Referencing a variable before its first successful assignment is a semantic error. Supported operators are unary `+` and `-`, binary `+`, `-`, `*`, `/`, `%` (integer remainder), and parentheses. Multiplication, division, and remainder share precedence. `//` starts a line comment.

Integer literals are non-negative decimal values from `0` through the maximum signed `int` supported by the build platform. A literal outside that range is reported as a lexical error instead of being silently truncated.

The compiler prints categorized tokens with their lexemes (number, identifier, arithmetic operator, assignment operator, parenthesis, or statement delimiter). It then prints a **concrete parse tree** for each statement, including grammar productions and terminals such as operators and parentheses. Internally, it also builds a separate AST for semantic checks and TAC generation. The lexer labels `+` and `-` as arithmetic operators; the parser grammar determines whether they are unary or binary. Each run writes the concrete parse trees to `parse_tree.html` in the current directory. This standalone browser page draws grammar nodes and token leaves as connected boxes, with controls to expand/collapse branches, filter statements, and zoom. When run from a terminal, the compiler asks whether to open the page in the system browser. Answer `y` to open it; the file is replaced on the next run.

The semantic checks reject variables used before assignment and division or remainder by an expression that is statically known to be zero (for example, `x / (3 - 3)`). A divisor that depends on a variable cannot be checked because this compiler generates TAC but does not execute it. Syntax and lexical errors include a line and column, and the parser skips an invalid line to continue with later statements. The compiler exits with a failure status if any syntax or semantic errors occurred.

For the example above, TAC includes:

```text
t0 = 5 * 2
t1 = 4 + t0
a = t1
```
