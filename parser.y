%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#endif

typedef struct Node Node;
typedef struct ParseNode ParseNode;
typedef struct ExprValue ExprValue;

struct Node {
    enum { NODE_NUMBER, NODE_IDENTIFIER, NODE_BINARY, NODE_UNARY } kind;
    int value;
    char op;
    char *name;
    int line;
    Node *left;
    Node *right;
};

struct ParseNode {
    char *label;
    char *lexeme;
    ParseNode **children;
    size_t child_count;
};

struct ExprValue {
    Node *ast;
    ParseNode *tree;
};

typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;

static Symbol *symbols;
static int temp_count;
static int errors;
static int tree_count;
static FILE *tree_file;
static Node *make_number(int value, int line);
static Node *make_identifier(char *name, int line);
static Node *make_binary(char op, Node *left, Node *right, int line);
static Node *make_unary(char op, Node *operand, int line);
static ParseNode *make_leaf(const char *label, const char *lexeme);
static ParseNode *make_branch(const char *label, size_t child_count, ...);
static ExprValue *make_expr_value(Node *ast, ParseNode *tree);
static ExprValue *promote_expr(const char *label, ExprValue *value);
static ExprValue *combine_expr(const char *label, ExprValue *left, char op, ExprValue *right, int line);
static int is_defined(const char *name);
static void define_symbol(const char *name);
static int check_expression(Node *node);
static int constant_value(Node *node, long long *value);
static char *generate(Node *node);
static void print_parse_tree(ParseNode *node, int depth);
static void write_parse_tree_html(ParseNode *node);
static void free_node(Node *node);
static void free_parse_tree(ParseNode *node);
static void free_expr_value(ExprValue *value);
static void compile_expression(ExprValue *value);
static void compile_assignment(char *name, ExprValue *value);
static void ask_to_open_tree(void);
void yyerror(const char *message);
int yylex(void);
%}

%code requires {
typedef struct ExprValue ExprValue;
}

%union {
    int num;
    char *str;
    ExprValue *expr;
}

%token <num> NUMBER
%token <str> IDENTIFIER
%token NEWLINE INVALID
%type <expr> expr term unary primary
%destructor { free($$); } <str>
%destructor { free_expr_value($$); } <expr>
%locations

%%

program:
      %empty
    | program line
    ;

line:
      NEWLINE
    | statement NEWLINE
    | error NEWLINE {
          fputs("Skipping the invalid line; continuing with the next line.\n", stderr);
          yyerrok;
      }
    ;

statement:
      expr {
          compile_expression($1);
          free_expr_value($1);
      }
    | IDENTIFIER '=' expr {
          compile_assignment($1, $3);
          free($1);
          free_expr_value($3);
      }
    ;

expr:
      expr '+' term { $$ = combine_expr("Expr", $1, '+', $3, @2.first_line); }
    | expr '-' term { $$ = combine_expr("Expr", $1, '-', $3, @2.first_line); }
    | term          { $$ = promote_expr("Expr", $1); }
    ;

term:
      term '*' unary { $$ = combine_expr("Term", $1, '*', $3, @2.first_line); }
    | term '/' unary { $$ = combine_expr("Term", $1, '/', $3, @2.first_line); }
    | term '%' unary { $$ = combine_expr("Term", $1, '%', $3, @2.first_line); }
    | unary          { $$ = promote_expr("Term", $1); }
    ;

unary:
      '+' unary      { $$ = make_expr_value($2->ast, make_branch("Unary", 2, make_leaf("PLUS", "+"), $2->tree)); free($2); }
    | '-' unary      { $$ = make_expr_value(make_unary('-', $2->ast, @1.first_line), make_branch("Unary", 2, make_leaf("MINUS", "-"), $2->tree)); free($2); }
    | primary        { $$ = promote_expr("Unary", $1); }
    ;

primary:
      NUMBER {
          char text[32];
          snprintf(text, sizeof(text), "%d", $1);
          $$ = make_expr_value(make_number($1, @1.first_line), make_branch("Primary", 1, make_leaf("NUMBER", text)));
      }
    | IDENTIFIER {
          $$ = make_expr_value(make_identifier($1, @1.first_line), make_branch("Primary", 1, make_leaf("IDENTIFIER", $1)));
      }
    | '(' expr ')' {
          $$ = make_expr_value($2->ast, make_branch("Primary", 3,
              make_leaf("LPAREN", "("), $2->tree, make_leaf("RPAREN", ")")));
          free($2);
      }
    ;

%%

static void *checked_alloc(size_t size) {
    void *memory = calloc(1, size);
    if (!memory) { perror("memory allocation"); exit(EXIT_FAILURE); }
    return memory;
}

static Node *new_node(int kind) {
    Node *node = checked_alloc(sizeof(*node));
    node->kind = kind;
    return node;
}

static Node *make_number(int value, int line) {
    Node *node = new_node(NODE_NUMBER);
    node->value = value;
    node->line = line;
    return node;
}

static Node *make_identifier(char *name, int line) {
    Node *node = new_node(NODE_IDENTIFIER);
    node->name = name;
    node->line = line;
    return node;
}

static Node *make_binary(char op, Node *left, Node *right, int line) {
    Node *node = new_node(NODE_BINARY);
    node->op = op;
    node->left = left;
    node->right = right;
    node->line = line;
    return node;
}

static Node *make_unary(char op, Node *operand, int line) {
    Node *node = new_node(NODE_UNARY);
    node->op = op;
    node->left = operand;
    node->line = line;
    return node;
}

static ParseNode *make_leaf(const char *label, const char *lexeme) {
    ParseNode *node = checked_alloc(sizeof(*node));
    node->label = strdup(label);
    node->lexeme = strdup(lexeme);
    if (!node->label || !node->lexeme) { perror("strdup"); exit(EXIT_FAILURE); }
    return node;
}

static ParseNode *make_branch(const char *label, size_t child_count, ...) {
    ParseNode *node = checked_alloc(sizeof(*node));
    node->label = strdup(label);
    node->child_count = child_count;
    node->children = checked_alloc(child_count * sizeof(*node->children));
    if (!node->label) { perror("strdup"); exit(EXIT_FAILURE); }
    va_list children;
    va_start(children, child_count);
    for (size_t i = 0; i < child_count; i++) node->children[i] = va_arg(children, ParseNode *);
    va_end(children);
    return node;
}

static ExprValue *make_expr_value(Node *ast, ParseNode *tree) {
    ExprValue *value = checked_alloc(sizeof(*value));
    value->ast = ast;
    value->tree = tree;
    return value;
}

static ExprValue *promote_expr(const char *label, ExprValue *value) {
    value->tree = make_branch(label, 1, value->tree);
    return value;
}

static ExprValue *combine_expr(const char *label, ExprValue *left, char op, ExprValue *right, int line) {
    Node *ast = make_binary(op, left->ast, right->ast, line);
    char lexeme[2] = { op, '\0' };
    ParseNode *tree = make_branch(label, 3, left->tree, make_leaf("OPERATOR", lexeme), right->tree);
    free(left);
    free(right);
    return make_expr_value(ast, tree);
}

static int is_defined(const char *name) {
    for (Symbol *symbol = symbols; symbol; symbol = symbol->next)
        if (strcmp(symbol->name, name) == 0) return 1;
    return 0;
}

static void define_symbol(const char *name) {
    if (is_defined(name)) return;
    Symbol *symbol = checked_alloc(sizeof(*symbol));
    symbol->name = strdup(name);
    if (!symbol->name) { perror("strdup"); exit(EXIT_FAILURE); }
    symbol->next = symbols;
    symbols = symbol;
}

static int constant_value(Node *node, long long *value) {
    if (node->kind == NODE_NUMBER) { *value = node->value; return 1; }
    if (node->kind == NODE_IDENTIFIER) return 0;
    if (node->kind == NODE_UNARY) {
        if (!constant_value(node->left, value)) return 0;
        if (node->op == '-') {
            if (*value == LLONG_MIN) return 0;
            *value = -*value;
        }
        return 1;
    }
    long long left, right, result;
    if (!constant_value(node->left, &left) || !constant_value(node->right, &right)) return 0;
    switch (node->op) {
        case '+': if (__builtin_add_overflow(left, right, &result)) return 0; break;
        case '-': if (__builtin_sub_overflow(left, right, &result)) return 0; break;
        case '*': if (__builtin_mul_overflow(left, right, &result)) return 0; break;
        case '/':
        case '%':
            if (right == 0 || (left == LLONG_MIN && right == -1)) return 0;
            result = node->op == '/' ? left / right : left % right;
            break;
        default: return 0;
    }
    *value = result;
    return 1;
}

static int check_expression(Node *node) {
    if (!node) return 0;
    if (node->kind == NODE_IDENTIFIER) {
        if (!is_defined(node->name)) {
            fprintf(stderr, "Semantic error at line %d: '%s' used before assignment\n", node->line, node->name);
            errors++;
            return 0;
        }
        return 1;
    }
    if (node->kind == NODE_UNARY) return check_expression(node->left);
    if (node->kind == NODE_BINARY) {
        int left_ok = check_expression(node->left);
        int right_ok = check_expression(node->right);
        if ((node->op == '/' || node->op == '%') && right_ok) {
            long long divisor;
            if (constant_value(node->right, &divisor) && divisor == 0) {
                fprintf(stderr, "Semantic error at line %d: division or remainder by zero\n", node->line);
                errors++;
                return 0;
            }
        }
        return left_ok && right_ok;
    }
    return 1;
}

static char *generate(Node *node) {
    char buffer[64];
    if (node->kind == NODE_NUMBER) {
        snprintf(buffer, sizeof(buffer), "%d", node->value);
        return strdup(buffer);
    }
    if (node->kind == NODE_IDENTIFIER) return strdup(node->name);
    if (node->kind == NODE_UNARY) {
        char *operand = generate(node->left);
        char *temp = checked_alloc(32);
        snprintf(temp, 32, "t%d", temp_count++);
        printf("%s = %c%s\n", temp, node->op, operand);
        free(operand);
        return temp;
    }
    char *left = generate(node->left);
    char *right = generate(node->right);
    char *temp = checked_alloc(32);
    snprintf(temp, 32, "t%d", temp_count++);
    printf("%s = %s %c %s\n", temp, left, node->op, right);
    free(left);
    free(right);
    return temp;
}

static void print_parse_tree(ParseNode *node, int depth) {
    for (int i = 0; i < depth; i++) fputs("  ", stdout);
    if (node->lexeme) printf("%s: %s\n", node->label, node->lexeme);
    else printf("%s\n", node->label);
    for (size_t i = 0; i < node->child_count; i++) print_parse_tree(node->children[i], depth + 1);
}

static void write_parse_tree_html(ParseNode *node) {
    fputs("<li><span class=\"tree-node ", tree_file);
    fputs(node->lexeme ? "terminal\">" : "nonterminal\">", tree_file);
    if (node->lexeme) fprintf(tree_file, "%s: %s", node->label, node->lexeme);
    else fputs(node->label, tree_file);
    fputs("</span>", tree_file);
    if (node->child_count) {
        fputs("<ul class=\"tree-children\">", tree_file);
        for (size_t i = 0; i < node->child_count; i++) write_parse_tree_html(node->children[i]);
        fputs("</ul>", tree_file);
    }
    fputs("</li>", tree_file);
}

static void write_statement_tree(ParseNode *tree) {
    puts("Concrete parse tree:");
    print_parse_tree(tree, 1);
    fprintf(tree_file, "<section class=\"statement-card\"><h2>Statement %d</h2><div class=\"tree-scroll\"><ul class=\"tree-root\">", ++tree_count);
    write_parse_tree_html(tree);
    fputs("</ul></div></section>\n", tree_file);
    fflush(tree_file);
}

static void compile_expression(ExprValue *value) {
    ParseNode *tree = make_branch("Statement", 1, value->tree);
    value->tree = NULL;
    write_statement_tree(tree);
    if (check_expression(value->ast)) {
        char *result = generate(value->ast);
        printf("Result: %s\n", result);
        free(result);
    }
    free_parse_tree(tree);
}

static void compile_assignment(char *name, ExprValue *value) {
    ParseNode *tree = make_branch("Statement", 3,
        make_leaf("IDENTIFIER", name), make_leaf("ASSIGN", "="), value->tree);
    value->tree = NULL;
    write_statement_tree(tree);
    if (check_expression(value->ast)) {
        char *result = generate(value->ast);
        printf("%s = %s\n", name, result);
        define_symbol(name);
        free(result);
    }
    free_parse_tree(tree);
}

static void free_node(Node *node) {
    if (!node) return;
    free_node(node->left);
    free_node(node->right);
    free(node->name);
    free(node);
}

static void free_parse_tree(ParseNode *node) {
    if (!node) return;
    for (size_t i = 0; i < node->child_count; i++) free_parse_tree(node->children[i]);
    free(node->children);
    free(node->label);
    free(node->lexeme);
    free(node);
}

static void free_expr_value(ExprValue *value) {
    if (!value) return;
    free_node(value->ast);
    free_parse_tree(value->tree);
    free(value);
}

static void ask_to_open_tree(void) {
    FILE *terminal = NULL;
#ifndef _WIN32
    terminal = fopen("/dev/tty", "r");
    if (!terminal && isatty(fileno(stdin))) terminal = stdin;
#else
    if (_isatty(_fileno(stdin))) terminal = stdin;
#endif
    if (!terminal) return;
    char answer[16];
    fprintf(stderr, "Open parse_tree.html in your browser? [y/N] ");
    fflush(stderr);
    if (!fgets(answer, sizeof(answer), terminal) || (answer[0] != 'y' && answer[0] != 'Y')) {
        if (terminal != stdin) fclose(terminal);
        return;
    }
    if (terminal != stdin) fclose(terminal);
#ifdef _WIN32
    if (system("start \"\" \"parse_tree.html\"") != 0)
        fprintf(stderr, "Could not open the browser. Open parse_tree.html manually.\n");
#elif defined(__APPLE__)
    if (system("open \"parse_tree.html\"") != 0)
        fprintf(stderr, "Could not open the browser. Open parse_tree.html manually.\n");
#else
    int opened = system("xdg-open \"parse_tree.html\" >/dev/null 2>&1");
    if (opened != 0) opened = system("gio open \"parse_tree.html\" >/dev/null 2>&1");
    if (opened != 0) opened = system("explorer.exe \"$(wslpath -w \"$PWD/parse_tree.html\")\" >/dev/null 2>&1");
    if (opened != 0) fprintf(stderr, "Could not open the browser; open parse_tree.html manually.\n");
#endif
}

void yyerror(const char *message) {
    fprintf(stderr, "Syntax error at line %d, column %d: %s\n",
        yylloc.first_line, yylloc.first_column, message);
    errors++;
}

int main(void) {
    tree_file = fopen("parse_tree.html", "w");
    if (!tree_file) { perror("parse_tree.html"); return EXIT_FAILURE; }
    fputs("<!doctype html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Parse Tree Viewer</title><style>\n"
          ":root{font-family:Inter,system-ui,-apple-system,BlinkMacSystemFont,\"Segoe UI\",sans-serif;color:#172033;background:#f2f5fa}*{box-sizing:border-box}body{margin:0}.topbar{padding:28px clamp(18px,4vw,56px);background:#172554;color:white}.topbar h1{margin:0 0 6px;font-size:clamp(24px,3vw,36px)}.topbar p{margin:0;color:#cbd5e1}.toolbar{position:sticky;top:0;z-index:5;display:flex;align-items:center;gap:12px;flex-wrap:wrap;padding:14px clamp(18px,4vw,56px);background:#fff;border-bottom:1px solid #dbe2ed;box-shadow:0 3px 12px #17255410}.toolbar button{border:1px solid #cbd5e1;border-radius:8px;background:#fff;padding:9px 13px;font:inherit;color:#172033;cursor:pointer}.toolbar button:hover{background:#eef4ff;border-color:#8aa9e8}.toolbar input[type=search]{min-width:210px;border:1px solid #cbd5e1;border-radius:8px;padding:9px 12px;font:inherit}.zoom-control{display:flex;align-items:center;gap:8px;color:#475569}.zoom-control input{width:130px}main{padding:10px clamp(12px,3vw,40px) 50px}.status{color:#64748b;margin:14px 0}.statement-card{background:#fff;border:1px solid #dbe2ed;border-radius:14px;margin:18px 0;box-shadow:0 8px 24px #1725540a;overflow:hidden}.statement-card h2{font-size:16px;margin:0;padding:14px 20px;border-bottom:1px solid #edf0f5;color:#334155}.tree-scroll{overflow:auto;padding:30px 26px 38px}.tree-root,.tree-children{display:flex;justify-content:center;position:relative;padding:28px 0 0;margin:0;min-width:max-content}.tree-root{padding-top:4px;zoom:var(--tree-zoom,1)}.tree-root li{list-style:none;position:relative;text-align:center;padding:28px 9px 0}.tree-root>li{padding-top:0}.tree-root li:before,.tree-root li:after{content:\"\";position:absolute;top:0;right:50%;width:50%;height:28px;border-top:2px solid #a9b9cf}.tree-root li:after{right:auto;left:50%;border-left:2px solid #a9b9cf}.tree-root li:only-child:before,.tree-root li:only-child:after{display:none}.tree-root li:first-child:before{border:0}.tree-root li:last-child:after{border:0}.tree-root ul:before{content:\"\";position:absolute;top:0;left:50%;height:28px;border-left:2px solid #a9b9cf}.tree-root>li:before,.tree-root>li:after{display:none}.tree-node{display:inline-flex;position:relative;z-index:1;align-items:center;justify-content:center;min-height:40px;padding:9px 13px;border:1px solid;border-radius:10px;white-space:nowrap;font:600 13px/1.25 ui-monospace,SFMono-Regular,Menlo,monospace;box-shadow:0 3px 10px #1725540d}.nonterminal{background:#eaf1ff;border-color:#a8c2fa;color:#214b9b}.terminal{background:#eaf8f1;border-color:#a5dfc0;color:#17633f}.empty{margin:38px;padding:30px;border:1px dashed #b8c4d5;border-radius:12px;background:white;color:#64748b;text-align:center}.statement-card[hidden]{display:none}@media(max-width:650px){.toolbar{gap:8px}.tree-scroll{padding:24px 10px}.tree-root li{padding-left:5px;padding-right:5px}.tree-node{padding:8px 9px;font-size:12px}}\n"
          "</style></head><body><header class=\"topbar\"><h1>Parse Tree Viewer</h1><p>Concrete grammar trees generated from your compiler input.</p></header><nav class=\"toolbar\"><button id=\"expand\" type=\"button\">Expand all</button><button id=\"collapse\" type=\"button\">Collapse all</button><input id=\"search\" type=\"search\" placeholder=\"Filter statements or nodes\" aria-label=\"Filter parse trees\"><label class=\"zoom-control\">Zoom <input id=\"zoom\" type=\"range\" min=\"60\" max=\"140\" value=\"100\"><span id=\"zoom-value\">100%</span></label></nav><main id=\"trees\" style=\"--tree-zoom:1\"><p class=\"status\">Grammar nodes are blue; input tokens are green. Scroll horizontally for wide trees.</p>", tree_file);
    fflush(tree_file);
    int parse_status = yyparse();
    if (tree_count == 0) fputs("<div class=\"empty\">No valid statements were parsed. Enter an expression or assignment, then run the compiler again.</div>", tree_file);
    else fprintf(tree_file, "<p class=\"status\">Rendered %d statement tree%s.</p>", tree_count, tree_count == 1 ? "" : "s");
    fputs("</main><script>\n"
          "const cards=[...document.querySelectorAll('.statement-card')];\n"
          "document.getElementById('expand').addEventListener('click',()=>document.querySelectorAll('.tree-children').forEach(x=>x.hidden=false));\n"
          "document.getElementById('collapse').addEventListener('click',()=>document.querySelectorAll('.tree-children').forEach(x=>x.hidden=true));\n"
          "document.getElementById('search').addEventListener('input',e=>{const q=e.target.value.toLowerCase();cards.forEach(c=>c.hidden=!c.textContent.toLowerCase().includes(q));});\n"
          "document.getElementById('zoom').addEventListener('input',e=>{const n=Number(e.target.value);document.getElementById('trees').style.setProperty('--tree-zoom',n/100);document.getElementById('zoom-value').textContent=n+'%';});\n"
          "</script></body></html>\n", tree_file);
    fclose(tree_file);
    ask_to_open_tree();
    while (symbols) {
        Symbol *next = symbols->next;
        free(symbols->name);
        free(symbols);
        symbols = next;
    }
    return parse_status || errors ? EXIT_FAILURE : EXIT_SUCCESS;
}
