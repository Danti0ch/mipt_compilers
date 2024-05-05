#pragma once

#include <iostream>

class Driver;

class Expr {
 public:
    virtual int eval(Driver& driver) const = 0;
};

class BoolExpr : public Expr {
 public:
    virtual int eval(Driver& driver) const override = 0;
};

class ArithmExpr : public Expr {
 public:
    virtual int eval(Driver& driver) const override = 0;
};

#define DECLARE_BIN_EXPR(base_class, class_name, op) \
class class_name : public base_class { \
 public: \
    class_name(Expr* left, Expr* right) : left_(left), right_(right) {} \
 \
    int eval(Driver& driver) const override { \
        int res = left_->eval(driver) op right_->eval(driver); \
        return res; \
    } \
 private:\
    Expr *left_, *right_; \
}

#define DECLARE_ARITHM_EXPR(class_name, op) \
    DECLARE_BIN_EXPR(ArithmExpr, class_name, op)

#define DECLARE_BOOL_EXPR(class_name, op) \
    DECLARE_BIN_EXPR(BoolExpr, class_name, op)

DECLARE_BOOL_EXPR(AndExpr, &&);
DECLARE_BOOL_EXPR(OrExpr, ||);
DECLARE_BOOL_EXPR(LessExpr, <);
DECLARE_BOOL_EXPR(ELessExpr, <=);
DECLARE_BOOL_EXPR(MoreExpr, >);
DECLARE_BOOL_EXPR(EMoreExpr, >=);
DECLARE_BOOL_EXPR(EqExpr, ==);
DECLARE_BOOL_EXPR(NEqExpr, !=);

DECLARE_ARITHM_EXPR(AddExpr, +);
DECLARE_ARITHM_EXPR(SubExpr, -);
DECLARE_ARITHM_EXPR(MulExpr, *);
DECLARE_ARITHM_EXPR(DivExpr, /);
DECLARE_ARITHM_EXPR(ModExpr, %);
