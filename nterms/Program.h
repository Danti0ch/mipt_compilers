#pragma once

#include "BaseElem.h"
#include "Func.h"
#include "Statement.h"
#include <vector>

class Driver;

class Program : public BaseElem {
 public:
    Program(Func* func) : func_(func) {}
    int eval(Driver& driver) const override {
      Statement::ret_flag = false;
      return func_->eval(driver);
    }

    DEFINE_ACCEPT

    Func* func() { return func_; }
 private:
   Func* func_;
};
