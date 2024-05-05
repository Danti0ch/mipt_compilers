#pragma once

#include "Func.h"
#include <vector>

class Driver;

class Program {
 public:
    Program(Func* func) : func_(func) {}
    int eval(Driver& driver)
      { return func_->eval(driver); }
 private:
   Func* func_;
};
