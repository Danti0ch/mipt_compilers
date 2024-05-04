#pragma once

#include "../Expr.h"
#include "../Statement.h"

// todo: will be fixe next iteration
#include "../../driver.hh"

class PrintCall : public LocalStatement {
 public:
    PrintCall(Expr* expr) : expr_(expr) {}
    int eval(Driver& driver) const override {
        int val = expr_->eval(driver);
        driver.print(val);

        return 0;
    }
 private:
   Expr* expr_;
};
