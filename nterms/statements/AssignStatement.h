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

    DEFINE_ACCEPT

    Ident* ident() { return ident_; }
    Expr* expr() { return expr_; }
 private:
    Ident* ident_;
    Expr* expr_;
};
