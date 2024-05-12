#include "driver.hh"
#include "parser.hh"

#include "visitors/Interpreter.h"
#include "visitors/PrintVisitor.h"



Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
    // variables["one"] = 1;
    // variables["two"] = 2;
}

void Driver::add_var(std::string name) {
  declared_vars.insert(name);
}

int Driver::lookup_var(std::string name) const {

  if (declared_vars.count(name) == 0)
      this->throw_error(ErrorType::UNDECLARED_VAR);

  if (assigned_vars.count(name) == 0)
      this->throw_error(ErrorType::UNASSIGNED_VAR);

  int res = static_cast<int>(assigned_vars.at(name));

  return res;
}

void Driver::assign_var(std::string name, int val) {
  if (declared_vars.count(name) == 0)
      this->throw_error(ErrorType::UNDECLARED_VAR);

  assigned_vars[name] = val;
}

void Driver::print(int val) const {
  std::cout << "Hello! That is what you want to see -> " << val << "\n";
}

void Driver::throw_error(ErrorType type) const {
  std::cerr << "Error: ";
  switch (type) {
    case ErrorType::UNDECLARED_VAR:
      std::cerr << "Undeclared variable\n";
      break;
    case ErrorType::UNASSIGNED_VAR:
      std::cerr << "Unassigned variable\n";
      break;
  }
  exit(1);
}

int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();

    std::cout << program << std::endl;
    result = program->eval(*this);

    for (const auto& [name, value]: assigned_vars) {
      std::cerr << name << " " << value << std::endl;
    }
    scan_end();
    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

int Driver::Evaluate() {
    Interpreter interpreter;
    return interpreter.GetResult(program);
}

void Driver::PrintTree(const std::string& filename) {
    SymbolTreeVisitor visitor(filename);
    visitor.Visit(program);
}
