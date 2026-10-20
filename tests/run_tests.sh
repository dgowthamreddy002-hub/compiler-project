#!/bin/sh
set -eu

project_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
work_dir=$(mktemp -d)
trap 'rm -rf "$work_dir"' EXIT HUP INT TERM
cd "$work_dir"

"$project_dir/compiler" < "$project_dir/examples/arithmetic.expr" >valid.out 2>valid.err
grep -q 'TOKEN: ARITHMETIC_OPERATOR | Lexeme: %' valid.out
grep -q 'Concrete parse tree:' valid.out
grep -q 'LPAREN: (' valid.out
grep -q 'PLUS: +' valid.out
grep -q 'Unary' valid.out
grep -q 't0 = 17 % 5' valid.out
grep -q 'b = t3' valid.out
grep -q 'tree-node nonterminal' parse_tree.html
grep -q 'tree-node terminal' parse_tree.html
grep -q 'id="expand"' parse_tree.html

if "$project_dir/compiler" < "$project_dir/examples/errors.expr" >errors.out 2>errors.err; then
    echo "Expected semantic and syntax errors, but the compiler succeeded." >&2
    exit 1
fi
grep -q 'Semantic error at line 2: division or remainder by zero' errors.err
grep -q 'Semantic error at line 3: division or remainder by zero' errors.err
grep -q "Semantic error at line 6: 'missing' used before assignment" errors.err
grep -q 'Syntax error at line 9' errors.err
grep -q 'Lexical error at line 12, column 19' errors.err
grep -q 'Syntax error at line 12' errors.err
grep -q 'good = t0' errors.out

printf 'last = 7' | "$project_dir/compiler" >no-final-newline.out 2>no-final-newline.err
grep -q 'last = 7' no-final-newline.out
grep -q 'STATEMENT_DELIMITER' no-final-newline.out

echo "All compiler checks passed."
