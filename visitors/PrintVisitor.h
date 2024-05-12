#pragma once

#include "Visitor.h"

#include <fstream>
#include <string>

class SymbolTreeVisitor: public Visitor {
 public:
    SymbolTreeVisitor(const std::string& filename);
    ~SymbolTreeVisitor();
    #define DEFINE_TERM(nterm) \
       void Visit(nterm* expression) override;
    #include "../nterms/terms_define.h"
    #undef DEFINE_TERM
 private:

    void PrintTabs();
    std::ofstream stream_;
    int num_tabs_ = 0;

};
