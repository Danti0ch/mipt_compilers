#pragma once

#include "../Expr.h"
#include "../Statement.h"
#include "../Body.h"

#include <vector>
#include <iostream>

class CondStatement : public LocalStatement {
 public:
    CondStatement(BoolExpr* cond, LocalBody* stmts) :
        cond_(cond), stmts_(stmts), else_stmts_(NULL) {}

    CondStatement(BoolExpr* cond, LocalBody* stmts, LocalBody* else_stmts) :
        cond_(cond), stmts_(stmts), else_stmts_(else_stmts) {}

    int eval(Driver& driver) const override {
        int res = 0;

        if (cond_->eval(driver))
            { res = stmts_->eval(driver); }
        else if (else_stmts_)
            { res = else_stmts_->eval(driver); }
        return res;
    }

 private:
   BoolExpr* cond_;
   LocalBody* stmts_;
   LocalBody* else_stmts_;
};
