#include "Visitor.h"

#include <map>
#include <string>

class Interpreter : public Visitor {
 public:
    Interpreter();
    #define DEFINE_TERM(nterm) \
       void Visit(nterm* expression) override;
    #include "../nterms/terms_define.h"
    #undef DEFINE_TERM

    int GetResult(Program* program);

 private:
    std::map<std::string, int> variables_;
    bool is_tos_expression_;
    int tos_value_;

    void SetTosValue(int value);
    void UnsetTosValue();
    
};
