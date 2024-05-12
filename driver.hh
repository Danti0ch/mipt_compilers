#pragma once

#include <map>
#include <set>
#include <string>
#include <fstream>

#include "nterms/Program.h"

#include "scanner.h"
#include "parser.hh"

enum class ErrorType {
   UNDECLARED_VAR,
   UNASSIGNED_VAR,
};

class Driver {
 public:
    Driver();

    void add_var(std::string name);
    int lookup_var(std::string name) const;
    void assign_var(std::string name, int val);

    void print(int val) const;
    void throw_error(ErrorType type) const;

    int Evaluate();
    void PrintTree(const std::string& filename);

    std::map<std::string, int> assigned_vars;
    std::set<std::string> declared_vars;
    int result;
    int parse(const std::string& f);
    std::string file;
    bool trace_parsing;

    void scan_begin();
    void scan_end();

    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
    Program* program;
 private:
    std::ifstream stream;

};
