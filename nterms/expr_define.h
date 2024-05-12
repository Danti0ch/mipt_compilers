#ifdef DEFINE_BIN_EXPR

#define DECLARE_ARITHM_EXPR(class_name, op) \
    DEFINE_BIN_EXPR(ArithmExpr, class_name, op)

#define DECLARE_BOOL_EXPR(class_name, op) \
    DEFINE_BIN_EXPR(BoolExpr, class_name, op)

DECLARE_BOOL_EXPR(AndExpr, &&)
DECLARE_BOOL_EXPR(OrExpr, ||)
DECLARE_BOOL_EXPR(EqExpr, ==)
DECLARE_BOOL_EXPR(NEqExpr, !=)
DECLARE_BOOL_EXPR(LessExpr, <)
DECLARE_BOOL_EXPR(ELessExpr, <=)
DECLARE_BOOL_EXPR(MoreExpr, >)
DECLARE_BOOL_EXPR(EMoreExpr, >=)

DECLARE_ARITHM_EXPR(ModExpr, %)
DECLARE_ARITHM_EXPR(MulExpr, *)
DECLARE_ARITHM_EXPR(DivExpr, /)
DECLARE_ARITHM_EXPR(AddExpr, +)
DECLARE_ARITHM_EXPR(SubExpr, -)

#endif
