#pragma once

#include "../Ident.h"
#include "../Statement.h"

class LetStatement : public Statement {
 public:
    LetStatement(Ident* ident) : ident_(ident) {}
    int eval(Driver& driver) const override {
      // driver.add_var(ident_->name());
      return 0;
    }

    DEFINE_ACCEPT

    Ident* ident() { return ident_; }
 private:
   Ident* ident_;
};
