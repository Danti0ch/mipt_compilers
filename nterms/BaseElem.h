#pragma once

#include "../visitors/Visitor.h"

class Driver;

class BaseElem {
 public:
    virtual void Accept(Visitor* visitor) = 0;
    virtual int eval(Driver& visitor) const = 0;
    virtual ~BaseElem() = default;
};

#define DEFINE_ACCEPT \
void Accept(Visitor* visitor) override \
{ visitor->Visit(this); }
