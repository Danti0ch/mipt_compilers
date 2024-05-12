#pragma once

#include "../nterms/forward_decl.h"

class Visitor {
 public:
    #define DEFINE_TERM(nterm) \
        virtual void Visit(nterm* expression) = 0;
    #include "../nterms/terms_define.h"
    #undef DEFINE_TERM
};
