#include "PrintVisitor.h"

#include "../nterms/elements.h"
#include "Visitor.h"

#include <iostream>

SymbolTreeVisitor::SymbolTreeVisitor(const std::string& filename) : stream_(filename) {
}

#define DEFINE_BIN_EXPR(base, class_name, op) \
void SymbolTreeVisitor::Visit(class_name* expr) { \
    PrintTabs(); \
    stream_ << #class_name " is: \n"; \
 \
    ++num_tabs_; \
    expr->left()->Accept(this); \
    expr->right()->Accept(this); \
    --num_tabs_; \
}
#include "../nterms/expr_define.h"
#undef DEFINE_BIN_EXPR

void SymbolTreeVisitor::Visit(ConstExpr* expr) {
    PrintTabs();
    stream_ << "ConstExpr " << expr->val() << "\n";
}

void SymbolTreeVisitor::Visit(Ident* expr) {
    PrintTabs();
    stream_ << "Ident " << expr->name() << "\n";
}

void SymbolTreeVisitor::Visit(LetStatement* st) {
    PrintTabs();
    stream_ << "LetStatement \n";

    ++num_tabs_;
    st->ident()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(FormStatement* st) {
    PrintTabs();
    stream_ << "FormStatement \n";

    ++num_tabs_;
    st->expr()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(CondStatement* st) {
    PrintTabs();
    stream_ << "CondStatement \n";

    ++num_tabs_;
    st->cond()->Accept(this);
    if (st->stmts())
        st->stmts()->Accept(this);
    else
        st->else_stmts()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(LoopStatement* st) {
    PrintTabs();
    stream_ << "LoopStatement \n";

    ++num_tabs_;
    st->cond()->Accept(this);
    st->stmts()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(AssignStatement* st) {
    PrintTabs();
    stream_ << "AssignStatement \n";

    ++num_tabs_;
    st->ident()->Accept(this);
    st->expr()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(Program* program) {
    PrintTabs();
    stream_ << "Program \n";
    ++num_tabs_;
    program->func()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(SimpleFunc* program) {
    PrintTabs();
    stream_ << "SimpleFunc \n";

    ++num_tabs_;
    program->body()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(PrintCall* program) {
    PrintTabs();
    stream_ << "PrintCall \n";

    ++num_tabs_;
    program->expr()->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(Body* body) {
    PrintTabs();
    stream_ << "Body: \n";

    ++num_tabs_;
    for (Statement* st : body->statements())
        st->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::Visit(LocalBody* body) {
    PrintTabs();
    stream_ << "LocalBody: \n";

    ++num_tabs_;
    for (Statement* st : body->statements())
        st->Accept(this);
    --num_tabs_;
}

void SymbolTreeVisitor::PrintTabs() {
    for (int i = 0; i < num_tabs_; ++i) {
        stream_ << '\t';
    }
}

SymbolTreeVisitor::~SymbolTreeVisitor() {
    stream_.close();
}
