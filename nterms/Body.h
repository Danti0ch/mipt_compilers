#pragma once

#include "BaseElem.h"
#include "Statement.h"

#include <vector>
#include <cassert>
#include <iostream>
class Driver;

class Body : BaseElem {
 public:
   void AddStatement(Statement* statement)
      {     statements_.push_back(statement); }
   int eval(Driver& driver) const override {
      int ret = 0;

      for (Statement* st : statements_) {
         ret = st->eval(driver);
         if (Statement::ret_flag)
            return ret;
      }
      
      assert(0 && "main() without return value. Halt");
      return 0;
    }
   
   DEFINE_ACCEPT

   std::vector<Statement*>& statements() { return statements_; }
 private:
    std::vector<Statement*> statements_;
};


class LocalBody : BaseElem {
 public:

   LocalBody() :
      statements_() {      }

   void AddStatement(LocalStatement* statement)
      {     statements_.push_back(statement); }
   
   int eval(Driver& driver) const override {
      int ret = 0;

      for (LocalStatement* st : statements_) {
         ret = st->eval(driver);
         if (Statement::ret_flag)
            return ret;
      }
      return ret;
    }
   
   DEFINE_ACCEPT

   std::vector<LocalStatement*>& statements() { return statements_; }
 private:
    std::vector<LocalStatement*> statements_;
};
