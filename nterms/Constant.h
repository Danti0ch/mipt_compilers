#pragma once

#include "BaseElem.h"
#include "Expr.h"

class Driver;

class ConstExpr : public Expr  {
 public:
    ConstExpr(int val) : val_(val) {}
    int eval(Driver& driver) const override {
        return val_;
    }
    
    DEFINE_ACCEPT

    int val() { return val_; }
 private:
    int val_;
};
