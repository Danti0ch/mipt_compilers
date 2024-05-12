#pragma once

#include "Expr.h"

#include <string>

// todo: will be fixe next iteration
#include "../driver.hh"

class Ident : public Expr {
 public:
    Ident(const std::string& name) : name_(name) {}
    std::string name() const { return name_; }
    int eval(Driver& driver) const override { return driver.lookup_var(name_); }
    
    DEFINE_ACCEPT
 private:
    std::string name_;
};
