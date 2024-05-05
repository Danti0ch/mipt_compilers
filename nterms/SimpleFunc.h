#pragma once

#include "Func.h"
#include "Body.h"

class SimpleFunc: public Func {
 public:
    SimpleFunc(Body* body) : body_(body) {}
   
    int eval(Driver& driver) const override
      { return body_->eval(driver); }
 private:
    Body* body_;
};
