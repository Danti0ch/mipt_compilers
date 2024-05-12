%option noyywrap
%option c++
%option yyclass="Scanner"

%option debug

%{

/* noyywrap - disables call of yywrap - indicator of EOF */
/* yyclass - set name of mapped class */
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"

%}

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_CONST(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+ loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"fn"        return yy::parser::make_FUNC(loc);
"main"      return yy::parser::make_MAIN(loc);
"body:"     return yy::parser::make_BODY_DECL(loc);
"{"         return yy::parser::make_BODY_SCOPE_BEGIN(loc);
"}"         return yy::parser::make_BODY_SCOPE_END(loc);
"form"      return yy::parser::make_FORM(loc);
";"         return yy::parser::make_EXPR_CLOSE(loc);
"let"       return yy::parser::make_LET(loc);
"->"        return yy::parser::make_TYPE_POINT(loc);
"int"       return yy::parser::make_INT_TYPE(loc);
"<-"        return yy::parser::make_ASSIGN(loc);
"print"     return yy::parser::make_PRINT_IDENT(loc);
"("         return yy::parser::make_ARG_SCOPE_BEGIN(loc);
")"         return yy::parser::make_ARG_SCOPE_END(loc);
"if"        return yy::parser::make_IF(loc);
"else"      return yy::parser::make_ELSE(loc);
"loop"      return yy::parser::make_LOOP(loc);
"+"         return yy::parser::make_PLUS(loc);
"-"         return yy::parser::make_MINUS(loc);
"*"         return yy::parser::make_MUL(loc);
"/"         return yy::parser::make_DIV(loc);
"%"         return yy::parser::make_REM(loc);
"and"       return yy::parser::make_AND(loc);
"or"        return yy::parser::make_OR(loc);
"<"         return yy::parser::make_LESS(loc);
"<="        return yy::parser::make_ELESS(loc);
">"         return yy::parser::make_MORE(loc);
">="        return yy::parser::make_EMORE(loc);
"eq"        return yy::parser::make_EQ(loc);
"neq"       return yy::parser::make_NEQ(loc);



{int}      return make_CONST(yytext, loc);
{id}       return yy::parser::make_IDENT(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_CONST(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_CONST((int) n, loc);
}
