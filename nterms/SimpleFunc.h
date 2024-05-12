#pragma once

#include "BaseElem.h"
#include "Func.h"
#include "Body.h"

class SimpleFunc: public Func {
 public:
    SimpleFunc(Body* body) : body_(body) {}
   
    int eval(Driver& driver) const override
      { return body_->eval(driver); }

   DEFINE_ACCEPT

    Body* body() { return body_; }
 private:
    Body* body_;
};
