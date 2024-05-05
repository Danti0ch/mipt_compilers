#pragma once

class Driver;

class Statement {
 public:
    virtual int eval(Driver& driver) const = 0;
  static int ret_flag;
};

class LocalStatement : public Statement {
 public:
    virtual int eval(Driver& driver) const = 0;
};
