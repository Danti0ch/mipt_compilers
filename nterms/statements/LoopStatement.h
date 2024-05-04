#pragma once

#include "../Expr.h"
#include "../Statement.h"
#include "../Body.h"

#include <vector>

class LoopStatement : public LocalStatement {
 public:
    LoopStatement(BoolExpr* cond, LocalBody* body) :
        cond_(cond), stmts_(body) {}

    int eval(Driver& driver) const override {
        int res = 0;
        while (cond_->eval(driver)) {
            res = stmts_->eval(driver);
            if (Statement::ret_flag)
                return res;
        }
        return res;
    }

 private:
   BoolExpr* cond_;
   LocalBody* stmts_;
};
