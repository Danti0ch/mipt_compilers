#include "Interpreter.h"

#include "../nterms/elements.h"

#include <iostream>

Interpreter::Interpreter() {
    variables_["one"] = 1;
    variables_["two"] = 2;
    is_tos_expression_ = false;
    tos_value_ = 0;
}

#define DEFINE_BIN_EXPR(base, class_name, op) \
void Interpreter::Visit(class_name* expr) { \
    int value = 0; \
    expr->left()->Accept(this); \
    value = tos_value_; \
    expr->right()->Accept(this); \
    value = value op tos_value_; \
    SetTosValue(value); \
}
#include "../nterms/expr_define.h"
#undef DEFINE_BIN_EXPR

void Interpreter::Visit(ConstExpr* expr) {
    SetTosValue(expr->val());
}

void Interpreter::Visit(Ident* expr) {
    int value = variables_[expr->name()];

    SetTosValue(value);
}

void Interpreter::Visit(LetStatement* st) {
    st->ident()->Accept(this);
    variables_[st->ident()->name()] = tos_value_;

    UnsetTosValue();
}

void Interpreter::Visit(FormStatement* st) {
    st->expr()->Accept(this);
    Statement::ret_flag = true;
}

void Interpreter::Visit(CondStatement* st) {
    st->cond()->Accept(this);
    bool is_true = tos_value_ != 0;

    UnsetTosValue();
    if (is_true) {
        st->stmts()->Accept(this);
    } else {
        st->else_stmts()->Accept(this);
    }
}

void Interpreter::Visit(LoopStatement* st) {
    st->cond()->Accept(this);
    bool is_true = tos_value_ != 0;

    while (is_true) {
        UnsetTosValue();

        st->stmts()->Accept(this);
        if (Statement::ret_flag)
            break;
        st->cond()->Accept(this);
        is_true = tos_value_ != 0;
    }
}

void Interpreter::Visit(AssignStatement* st) {

    st->expr()->Accept(this);
    int val = tos_value_;
    UnsetTosValue();

    st->ident()->Accept(this);
    variables_[st->ident()->name()] = val;
    UnsetTosValue();
}

void Interpreter::Visit(Program* program) {
    program->func()->Accept(this);
}

void Interpreter::Visit(SimpleFunc* program) {
    program->body()->Accept(this);
}

void Interpreter::Visit(PrintCall* program) {
    program->expr()->Accept(this);

    std::cout << tos_value_ << "\n";

    UnsetTosValue();
}

void Interpreter::Visit(Body* body) {
    for (Statement* st : body->statements()) {
        st->Accept(this);
        if (Statement::ret_flag)
            break;
    }
}

void Interpreter::Visit(LocalBody* body) {
    for (Statement* st : body->statements()) {
        st->Accept(this);
        if (Statement::ret_flag)
            break;
    }
}

void Interpreter::SetTosValue(int value) {
    tos_value_ = value;
    is_tos_expression_ = true;
}

void Interpreter::UnsetTosValue() {
    tos_value_ = 0;
    is_tos_expression_ = false;
}

int Interpreter::GetResult(Program *program) {
    UnsetTosValue();
    Visit(program);
    // program->Accept(this);
    return tos_value_;
}