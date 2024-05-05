#pragma once

#include "Statement.h"

#include <vector>
#include <cassert>
#include <iostream>
class Driver;

class Body {
 public:
   void AddStatement(Statement* statement)
      {     statements_.push_back(statement); }
   int eval(Driver& driver) const {
      int ret = 0;

      for (Statement* st : statements_) {
         ret = st->eval(driver);
         if (Statement::ret_flag)
            return ret;
      }
      
      assert(0 && "main() without return value. Halt");
      return 0;
    }
   
 private:
    std::vector<Statement*> statements_;
};


class LocalBody {
 public:

   LocalBody() :
      statements_() {      }

   void AddStatement(LocalStatement* statement)
      {     statements_.push_back(statement); }
   
   int eval(Driver& driver) const {
      int ret = 0;

      for (LocalStatement* st : statements_) {
         ret = st->eval(driver);
         if (Statement::ret_flag)
            return ret;
      }
      return ret;
    }
   
 private:
    std::vector<LocalStatement*> statements_;
};
