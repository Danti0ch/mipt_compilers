#pragma once

#include "BaseElem.h"

#include <iostream>

class Driver;

class Expr : public BaseElem {};

class BinExpr : public Expr {
public:
    Expr* left() { return left_; }
    Expr* right() { return right_; }
 protected:
    Expr *left_, *right_; \
};

class BoolExpr : public BinExpr {};

class ArithmExpr : public BinExpr {};

#define DECLARE_BIN_EXPR(base_class, class_name, op) \
class class_name : public base_class { \
 public: \
    class_name(Expr* left, Expr* right) \
        { left_ = left; right_ = right; } \
 \
    int eval(Driver& driver) const override { \
        int res = left_->eval(driver) op right_->eval(driver); \
        return res; \
    } \
    DEFINE_ACCEPT \
}

#define DEFINE_BIN_EXPR(base, class_expr, op) \
    DECLARE_BIN_EXPR(base, class_expr, op);
#include "expr_define.h"
#undef DEFINE_BIN_EXPR
#undef DECLARE_BIN_EXPR
