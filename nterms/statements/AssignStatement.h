#pragma once

#include "../Statement.h"
#include "../Expr.h"
#include "../Ident.h"

class AssignStatement : public LocalStatement {
 public:
    AssignStatement(Ident* ident, Expr* expr) : ident_(ident), expr_(expr) {}
    int eval(Driver& driver) const override {
      int val = expr_->eval(driver);
      driver.assign_var(ident_->name(), val);
      return 0;
    }
 private:
    Ident* ident_;
    Expr* expr_;
};
