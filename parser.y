%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
    
    #include "nterms/forward_decl.h"
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "nterms/Program.h"
    #include "nterms/Body.h"
    #include "nterms/Constant.h"
    #include "nterms/Expr.h"
    #include "nterms/Func.h"
    #include "nterms/Ident.h"
    #include "nterms/SimpleFunc.h"
    #include "nterms/Statement.h"

    #include "nterms/statements/AssignStatement.h"
    #include "nterms/statements/CondStatement.h"
    #include "nterms/statements/FormStatement.h"
    #include "nterms/statements/LetStatement.h"
    #include "nterms/statements/LoopStatement.h"
    #include "nterms/statements/PrintCall.h"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    FUNC                "fn"
    MAIN                "main"
    BODY_DECL           "body:"
    BODY_SCOPE_BEGIN    "{"
    BODY_SCOPE_END      "}"
    FORM                "form"
    EXPR_CLOSE          ";"
    LET                 "let"
    TYPE_POINT          "->"
    INT_TYPE            "int"
    ASSIGN              "<-"
    PRINT_IDENT         "print"
    ARG_SCOPE_BEGIN     "("
    ARG_SCOPE_END       ")"
    IF                  "if"
    ELSE                "else"
    LOOP                "loop"

    PLUS    "+"
    MINUS   "-"
    MUL     "*"
    DIV     "/"
    REM     "%"

    AND     "and"
    OR      "or"
    LESS    "<"
    ELESS   "<="
    MORE    ">"
    EMORE   ">="
    EQ      "eq"
    NEQ     "neq"
;

%token <std::string> IDENT "ident"
%token <int> CONST "const"

%nterm <Ident*> ident_expr
%nterm <ConstExpr*> const_expr

%nterm <Program*> unit
%nterm <Func*> func
%nterm <SimpleFunc*> simple_func
%nterm <Body*> body_sec
%nterm <LocalBody*> local_body
%nterm <Statement*> statement
%nterm <LocalStatement*> local_statement
%nterm <Expr*> expr
%nterm <BoolExpr*> bool_expr
%nterm <ArithmExpr*> arithm_expr

// %printer { yyo << $$; } <*>;

%%
%start unit;

unit: func {
        $$ = new Program($1);
        driver.program = $$;
    };

func: simple_func {
    $$ = $1;
};

simple_func: "fn" "main" "body:" "{" body_sec "}" {
    $$ = new SimpleFunc($5);
};

body_sec:
    %empty { $$ = new Body(); /* A -> eps */}
    | body_sec statement {
        $1->AddStatement($2);
        $$ = $1;
    };

statement:
    local_statement {
        $$ = $1;
    } |
    "let" ident_expr "->" "int" ";" {
        $$ = new LetStatement($2);
        driver.add_var($2->name());
    };

local_statement:
    "form" expr ";" {
        $$ = new FormStatement($2);
    } |
    ident_expr "<-" expr ";" {
        $$ = new AssignStatement($1, $3);
        driver.assign_var($1->name(), $$->eval(driver));
    } |
    "print" "(" expr ")" ";" {
        $$ = new PrintCall($3);
    } |
    "if" "(" bool_expr ")" "{" local_body "}" "else" "{" local_body "}" {
        $$ = new CondStatement($3, $6, $10);
    } |
    "if" "(" bool_expr ")" "{" local_body "}" {
        $$ = new CondStatement($3, $6);
    } |
    "loop" "(" bool_expr ")" "{" local_body "}" {
        $$ = new LoopStatement($3, $6);
    };

local_body:
    %empty { $$ = new LocalBody(); /* A -> eps */}
    | local_body local_statement {
        $1->AddStatement($2);
        $$ = $1;
    };

%right "and";
%right "or";
%right "eq" "neq";
%left  "<" "<=";
%right ">" ">=";

// todo: to macros
bool_expr:
    expr "and" expr  { $$ = new AndExpr($1, $3); } |
    expr "or" expr   { $$ = new OrExpr($1, $3); } |
    expr "eq" expr   { $$ = new EqExpr($1, $3); } |
    expr "neq" expr  { $$ = new NEqExpr($1, $3); } |
    expr "<" expr    { $$ = new LessExpr($1, $3); } |
    expr "<=" expr   { $$ = new ELessExpr($1, $3); } |
    expr ">" expr    { $$ = new MoreExpr($1, $3); } |
    expr ">=" expr   { $$ = new EMoreExpr($1, $3); };

expr:
    bool_expr { $$ = $1; } |
    arithm_expr { $$ = $1; } |
    const_expr    { $$ = $1; } |
    ident_expr    { $$ = $1; } |
    "(" expr ")" { $$ = $2; };

ident_expr: "ident" { $$ = new Ident($1); };
const_expr: "const" { $$ = new ConstExpr($1); };

%right "%";
%right "*" "/";
%right "+" "-";

arithm_expr:
    expr "%" expr { $$ = new ModExpr($1, $3); } |
    expr "*" expr { $$ = new MulExpr($1, $3); } |
    expr "/" expr { $$ = new DivExpr($1, $3); } |
    expr "+" expr { $$ = new AddExpr($1, $3); } |
    expr "-" expr { $$ = new SubExpr($1, $3); };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
