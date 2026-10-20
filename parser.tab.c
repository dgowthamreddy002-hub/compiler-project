/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 145 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_NEWLINE = 5,                    /* NEWLINE  */
  YYSYMBOL_INVALID = 6,                    /* INVALID  */
  YYSYMBOL_7_ = 7,                         /* '='  */
  YYSYMBOL_8_ = 8,                         /* '+'  */
  YYSYMBOL_9_ = 9,                         /* '-'  */
  YYSYMBOL_10_ = 10,                       /* '*'  */
  YYSYMBOL_11_ = 11,                       /* '/'  */
  YYSYMBOL_12_ = 12,                       /* '%'  */
  YYSYMBOL_13_ = 13,                       /* '('  */
  YYSYMBOL_14_ = 14,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 15,                  /* $accept  */
  YYSYMBOL_program = 16,                   /* program  */
  YYSYMBOL_line = 17,                      /* line  */
  YYSYMBOL_statement = 18,                 /* statement  */
  YYSYMBOL_expr = 19,                      /* expr  */
  YYSYMBOL_term = 20,                      /* term  */
  YYSYMBOL_unary = 21,                     /* unary  */
  YYSYMBOL_primary = 22                    /* primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   32

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  15
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  21
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  35

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   261


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    12,     2,     2,
      13,    14,    10,     8,     2,     9,     2,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     7,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    96,    96,    97,   101,   102,   103,   110,   114,   122,
     123,   124,   128,   129,   130,   131,   135,   136,   137,   141,
     146,   149
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "IDENTIFIER",
  "NEWLINE", "INVALID", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'('",
  "')'", "$accept", "program", "line", "statement", "expr", "term",
  "unary", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-8)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -8,     2,    -8,     8,    -8,    18,    -8,    13,    13,    13,
      -8,    27,    15,    17,    -8,    -8,    -8,    13,    -8,    -8,
      -8,     0,    -8,    13,    13,    13,    13,    13,    15,    -8,
      17,    17,    -8,    -8,    -8
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,    19,    20,     4,     0,     0,     0,
       3,     0,     7,    11,    15,    18,     6,     0,    20,    16,
      17,     0,     5,     0,     0,     0,     0,     0,     8,    21,
       9,    10,    12,    13,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -8,    -8,    -8,    -8,    -5,     7,    -7,    -8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    10,    11,    12,    13,    14,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    20,     2,     3,    21,     4,     5,     6,    23,    24,
       7,     8,    28,    16,    29,     9,     4,    18,    32,    33,
      34,     7,     8,    23,    24,    17,     9,    25,    26,    27,
      30,    31,    22
};

static const yytype_int8 yycheck[] =
{
       7,     8,     0,     1,     9,     3,     4,     5,     8,     9,
       8,     9,    17,     5,    14,    13,     3,     4,    25,    26,
      27,     8,     9,     8,     9,     7,    13,    10,    11,    12,
      23,    24,     5
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,     0,     1,     3,     4,     5,     8,     9,    13,
      17,    18,    19,    20,    21,    22,     5,     7,     4,    21,
      21,    19,     5,     8,     9,    10,    11,    12,    19,    14,
      20,    20,    21,    21,    21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    15,    16,    16,    17,    17,    17,    18,    18,    19,
      19,    19,    20,    20,    20,    20,    21,    21,    21,    22,
      22,    22
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     1,     1,
       1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_IDENTIFIER: /* IDENTIFIER  */
#line 89 "parser.y"
            { free(((*yyvaluep).str)); }
#line 995 "parser.tab.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 90 "parser.y"
            { free_expr_value(((*yyvaluep).expr)); }
#line 1001 "parser.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 90 "parser.y"
            { free_expr_value(((*yyvaluep).expr)); }
#line 1007 "parser.tab.c"
        break;

    case YYSYMBOL_unary: /* unary  */
#line 90 "parser.y"
            { free_expr_value(((*yyvaluep).expr)); }
#line 1013 "parser.tab.c"
        break;

    case YYSYMBOL_primary: /* primary  */
#line 90 "parser.y"
            { free_expr_value(((*yyvaluep).expr)); }
#line 1019 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* line: error NEWLINE  */
#line 103 "parser.y"
                    {
          fputs("Skipping the invalid line; continuing with the next line.\n", stderr);
          yyerrok;
      }
#line 1317 "parser.tab.c"
    break;

  case 7: /* statement: expr  */
#line 110 "parser.y"
           {
          compile_expression((yyvsp[0].expr));
          free_expr_value((yyvsp[0].expr));
      }
#line 1326 "parser.tab.c"
    break;

  case 8: /* statement: IDENTIFIER '=' expr  */
#line 114 "parser.y"
                          {
          compile_assignment((yyvsp[-2].str), (yyvsp[0].expr));
          free((yyvsp[-2].str));
          free_expr_value((yyvsp[0].expr));
      }
#line 1336 "parser.tab.c"
    break;

  case 9: /* expr: expr '+' term  */
#line 122 "parser.y"
                    { (yyval.expr) = combine_expr("Expr", (yyvsp[-2].expr), '+', (yyvsp[0].expr), (yylsp[-1]).first_line); }
#line 1342 "parser.tab.c"
    break;

  case 10: /* expr: expr '-' term  */
#line 123 "parser.y"
                    { (yyval.expr) = combine_expr("Expr", (yyvsp[-2].expr), '-', (yyvsp[0].expr), (yylsp[-1]).first_line); }
#line 1348 "parser.tab.c"
    break;

  case 11: /* expr: term  */
#line 124 "parser.y"
                    { (yyval.expr) = promote_expr("Expr", (yyvsp[0].expr)); }
#line 1354 "parser.tab.c"
    break;

  case 12: /* term: term '*' unary  */
#line 128 "parser.y"
                     { (yyval.expr) = combine_expr("Term", (yyvsp[-2].expr), '*', (yyvsp[0].expr), (yylsp[-1]).first_line); }
#line 1360 "parser.tab.c"
    break;

  case 13: /* term: term '/' unary  */
#line 129 "parser.y"
                     { (yyval.expr) = combine_expr("Term", (yyvsp[-2].expr), '/', (yyvsp[0].expr), (yylsp[-1]).first_line); }
#line 1366 "parser.tab.c"
    break;

  case 14: /* term: term '%' unary  */
#line 130 "parser.y"
                     { (yyval.expr) = combine_expr("Term", (yyvsp[-2].expr), '%', (yyvsp[0].expr), (yylsp[-1]).first_line); }
#line 1372 "parser.tab.c"
    break;

  case 15: /* term: unary  */
#line 131 "parser.y"
                     { (yyval.expr) = promote_expr("Term", (yyvsp[0].expr)); }
#line 1378 "parser.tab.c"
    break;

  case 16: /* unary: '+' unary  */
#line 135 "parser.y"
                     { (yyval.expr) = make_expr_value((yyvsp[0].expr)->ast, make_branch("Unary", 2, make_leaf("PLUS", "+"), (yyvsp[0].expr)->tree)); free((yyvsp[0].expr)); }
#line 1384 "parser.tab.c"
    break;

  case 17: /* unary: '-' unary  */
#line 136 "parser.y"
                     { (yyval.expr) = make_expr_value(make_unary('-', (yyvsp[0].expr)->ast, (yylsp[-1]).first_line), make_branch("Unary", 2, make_leaf("MINUS", "-"), (yyvsp[0].expr)->tree)); free((yyvsp[0].expr)); }
#line 1390 "parser.tab.c"
    break;

  case 18: /* unary: primary  */
#line 137 "parser.y"
                     { (yyval.expr) = promote_expr("Unary", (yyvsp[0].expr)); }
#line 1396 "parser.tab.c"
    break;

  case 19: /* primary: NUMBER  */
#line 141 "parser.y"
             {
          char text[32];
          snprintf(text, sizeof(text), "%d", (yyvsp[0].num));
          (yyval.expr) = make_expr_value(make_number((yyvsp[0].num), (yylsp[0]).first_line), make_branch("Primary", 1, make_leaf("NUMBER", text)));
      }
#line 1406 "parser.tab.c"
    break;

  case 20: /* primary: IDENTIFIER  */
#line 146 "parser.y"
                 {
          (yyval.expr) = make_expr_value(make_identifier((yyvsp[0].str), (yylsp[0]).first_line), make_branch("Primary", 1, make_leaf("IDENTIFIER", (yyvsp[0].str))));
      }
#line 1414 "parser.tab.c"
    break;

  case 21: /* primary: '(' expr ')'  */
#line 149 "parser.y"
                   {
          (yyval.expr) = make_expr_value((yyvsp[-1].expr)->ast, make_branch("Primary", 3,
              make_leaf("LPAREN", "("), (yyvsp[-1].expr)->tree, make_leaf("RPAREN", ")")));
          free((yyvsp[-1].expr));
      }
#line 1424 "parser.tab.c"
    break;


#line 1428 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 156 "parser.y"


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
