#pragma once

class Driver;

class Func {
 public:
    virtual int eval(Driver& driver) const = 0;
};
