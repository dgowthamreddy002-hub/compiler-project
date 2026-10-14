%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#endif

typedef struct Node Node;
struct Node {
    enum { NODE_NUMBER, NODE_IDENTIFIER, NODE_BINARY, NODE_UNARY } kind;
    int value;
    char op;
    char *name;
    struct Node *left;
    struct Node *right;
};

typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;

static Symbol *symbols;
static int temp_count;
static int errors;
static FILE *tree_file;
static Node *make_number(int value);
static Node *make_identifier(char *name);
static Node *make_binary(char op, Node *left, Node *right);
static Node *make_unary(char op, Node *operand);
static int is_defined(const char *name);
static void define_symbol(const char *name);
static int check_expression(Node *node);
static char *generate(Node *node);
static void print_tree(Node *node, int depth);
static void write_tree_html(Node *node);
static void free_node(Node *node);
static void ask_to_open_tree(void);
void yyerror(const char *message);
int yylex(void);
%}

%code requires {
typedef struct Node Node;
}

%union {
    int num;
    char *str;
    Node *node;
}

%token <num> NUMBER
%token <str> IDENTIFIER
%token NEWLINE INVALID
%type <node> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

program:
      %empty
    | program NEWLINE
    | program statement NEWLINE
    ;

statement:
      expr {
          puts("Abstract syntax tree (AST):");
          print_tree($1, 1);
          fputs("<section><h2>Expression</h2><ul>", tree_file);
          write_tree_html($1);
          fputs("</ul></section>\n", tree_file);
          fflush(tree_file);
          if (check_expression($1)) {
              char *result = generate($1);
              printf("Result: %s\n", result);
              free(result);
          }
          free_node($1);
      }
    | IDENTIFIER '=' expr {
          puts("Abstract syntax tree (AST):");
          puts("  Assignment");
          printf("    Identifier: %s\n", $1);
          print_tree($3, 2);
          fputs("<section><h2>Assignment</h2><ul><li>Assign</li><li>Identifier: ", tree_file);
          fprintf(tree_file, "%s</li><li>Expression", $1);
          fputs("<ul>", tree_file);
          write_tree_html($3);
          fputs("</ul></li></ul></section>\n", tree_file);
          fflush(tree_file);
          if (check_expression($3)) {
              char *result = generate($3);
              printf("%s = %s\n", $1, result);
              define_symbol($1);
              free(result);
          }
          free($1);
          free_node($3);
      }
    ;

expr:
      NUMBER                 { $$ = make_number($1); }
    | IDENTIFIER             { $$ = make_identifier($1); }
    | '(' expr ')'           { $$ = $2; }
    | '-' expr %prec UMINUS  { $$ = make_unary('-', $2); }
    | '+' expr %prec UMINUS  { $$ = $2; }
    | expr '+' expr          { $$ = make_binary('+', $1, $3); }
    | expr '-' expr          { $$ = make_binary('-', $1, $3); }
    | expr '*' expr          { $$ = make_binary('*', $1, $3); }
    | expr '/' expr          { $$ = make_binary('/', $1, $3); }
    ;

%%

static Node *new_node(int kind) {
    Node *node = calloc(1, sizeof(*node));
    if (!node) { perror("calloc"); exit(EXIT_FAILURE); }
    node->kind = kind;
    return node;
}

static Node *make_number(int value) {
    Node *node = new_node(NODE_NUMBER);
    node->value = value;
    return node;
}

static Node *make_identifier(char *name) {
    Node *node = new_node(NODE_IDENTIFIER);
    node->name = name;
    return node;
}

static Node *make_binary(char op, Node *left, Node *right) {
    Node *node = new_node(NODE_BINARY);
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

static Node *make_unary(char op, Node *operand) {
    Node *node = new_node(NODE_UNARY);
    node->op = op;
    node->left = operand;
    return node;
}

static int is_defined(const char *name) {
    for (Symbol *symbol = symbols; symbol; symbol = symbol->next)
        if (strcmp(symbol->name, name) == 0) return 1;
    return 0;
}

static void define_symbol(const char *name) {
    if (is_defined(name)) return;
    Symbol *symbol = malloc(sizeof(*symbol));
    if (!symbol) { perror("malloc"); exit(EXIT_FAILURE); }
    symbol->name = strdup(name);
    symbol->next = symbols;
    symbols = symbol;
}

static int check_expression(Node *node) {
    if (!node) return 0;
    if (node->kind == NODE_IDENTIFIER) {
        if (!is_defined(node->name)) {
            fprintf(stderr, "Semantic error: '%s' used before assignment\n", node->name);
            errors++;
            return 0;
        }
        return 1;
    }
    if (node->kind == NODE_UNARY) return check_expression(node->left);
    if (node->kind == NODE_BINARY) {
        int left_ok = check_expression(node->left);
        int right_ok = check_expression(node->right);
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
        char *temp = malloc(32);
        if (!temp) { perror("malloc"); exit(EXIT_FAILURE); }
        snprintf(temp, 32, "t%d", temp_count++);
        printf("%s = %c%s\n", temp, node->op, operand);
        free(operand);
        return temp;
    }
    char *left = generate(node->left);
    char *right = generate(node->right);
    char *temp = malloc(32);
    if (!temp) { perror("malloc"); exit(EXIT_FAILURE); }
    snprintf(temp, 32, "t%d", temp_count++);
    printf("%s = %s %c %s\n", temp, left, node->op, right);
    free(left);
    free(right);
    return temp;
}

static void print_tree(Node *node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    if (node->kind == NODE_NUMBER) {
        printf("Number: %d\n", node->value);
    } else if (node->kind == NODE_IDENTIFIER) {
        printf("Identifier: %s\n", node->name);
    } else if (node->kind == NODE_UNARY) {
        printf("Unary '%c'\n", node->op);
        print_tree(node->left, depth + 1);
    } else {
        printf("Binary '%c'\n", node->op);
        print_tree(node->left, depth + 1);
        print_tree(node->right, depth + 1);
    }
}

static void write_tree_html(Node *node) {
    fputs("<li>", tree_file);
    if (node->kind == NODE_NUMBER) {
        fprintf(tree_file, "Number: %d", node->value);
    } else if (node->kind == NODE_IDENTIFIER) {
        fprintf(tree_file, "Identifier: %s", node->name);
    } else if (node->kind == NODE_UNARY) {
        fprintf(tree_file, "Unary '%c'", node->op);
        fputs("<ul>", tree_file);
        write_tree_html(node->left);
        fputs("</ul>", tree_file);
    } else {
        fprintf(tree_file, "Binary '%c'", node->op);
        fputs("<ul>", tree_file);
        write_tree_html(node->left);
        write_tree_html(node->right);
        fputs("</ul>", tree_file);
    }
    fputs("</li>", tree_file);
}

static void free_node(Node *node) {
    if (!node) return;
    free_node(node->left);
    free_node(node->right);
    free(node->name);
    free(node);
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
    if (!fgets(answer, sizeof(answer), terminal) ||
        (answer[0] != 'y' && answer[0] != 'Y')) {
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
    if (opened != 0)
        opened = system("gio open \"parse_tree.html\" >/dev/null 2>&1");
    if (opened != 0)
        opened = system("explorer.exe \"$(wslpath -w \"$PWD/parse_tree.html\")\" >/dev/null 2>&1");
    if (opened != 0)
        fprintf(stderr, "Could not open the browser. Try: explorer.exe \"$(wslpath -w parse_tree.html)\"\n");
#endif
}

void yyerror(const char *message) {
    fprintf(stderr, "Syntax error: %s\n", message);
    errors++;
}

int main(void) {
    tree_file = fopen("parse_tree.html", "w");
    if (!tree_file) {
        perror("parse_tree.html");
        return EXIT_FAILURE;
    }
    fputs("<!doctype html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Compiler AST</title><style>body{font:16px system-ui,sans-serif;max-width:900px;margin:40px auto;padding:0 20px;background:#f6f8fa;color:#17202a}h1{margin-bottom:4px}section{background:white;border:1px solid #d0d7de;border-radius:10px;padding:16px 22px;margin:20px 0}ul{list-style:none;border-left:2px solid #9aa4b2;margin:8px 0 0 12px;padding:0 0 0 20px}li{position:relative;margin:8px 0}li:before{content:'';position:absolute;left:-22px;top:.7em;width:14px;border-top:2px solid #9aa4b2}</style></head><body><h1>Compiler abstract syntax tree</h1><p>Generated from the parsed input. Parentheses are represented through tree grouping and are not separate AST nodes.</p>", tree_file);
    fflush(tree_file);
    int parse_status = yyparse();
    fputs("</body></html>\n", tree_file);
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
