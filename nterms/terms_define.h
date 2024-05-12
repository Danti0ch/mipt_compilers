#ifdef DEFINE_ATERM
#define DEFINE_VIRT_TERM DEFINE_ATERM
#define DEFINE_TERM DEFINE_ATERM
#endif

#ifdef DEFINE_VIRT_TERM

DEFINE_VIRT_TERM(Statement)
DEFINE_VIRT_TERM(LocalStatement)
DEFINE_VIRT_TERM(Func)

DEFINE_VIRT_TERM(Expr)
DEFINE_VIRT_TERM(BoolExpr)
DEFINE_VIRT_TERM(ArithmExpr)

#endif

#ifdef DEFINE_TERM

DEFINE_TERM(LetStatement)
DEFINE_TERM(FormStatement)
DEFINE_TERM(CondStatement)
DEFINE_TERM(LoopStatement)
DEFINE_TERM(AssignStatement)
DEFINE_TERM(PrintCall)

DEFINE_TERM(Program)
DEFINE_TERM(SimpleFunc)
DEFINE_TERM(Body)
DEFINE_TERM(LocalBody)

DEFINE_TERM(ConstExpr)
DEFINE_TERM(Ident)

#define DEFINE_BIN_EXPR(base, expr, op) DEFINE_TERM(expr)
#include "expr_define.h"
#undef DEFINE_BIN_EXPR

#endif

#ifdef DEFINE_ATERM
#undef DEFINE_VIRT_TERM
#undef DEFINE_TERM
#endif
