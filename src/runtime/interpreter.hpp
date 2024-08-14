#pragma once
#include "values.hpp"
#include "../frontend/ast.hpp"

namespace runtime {
    class Interpreter {
    public:
        values::RuntimeVal evaluate(frontend::AST::Stmt stmt);
        Interpreter();
    };
}