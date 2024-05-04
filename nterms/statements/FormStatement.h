#pragma once

#include "../Statement.h"
#include "../Expr.h"

class FormStatement : public LocalStatement {
 public:
    FormStatement(Expr* expr) : expr_(expr) {}
    int eval(Driver& driver) const override {
      int res = expr_->eval(driver);
      Statement::ret_flag = 1;

      return res;
    }
 private:
    Expr* expr_;
};
