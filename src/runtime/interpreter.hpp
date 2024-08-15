#pragma once
#include "values.hpp"
#include "../frontend/ast.hpp"

namespace runtime {
    class Interpreter {
    public:
        values::RuntimeVal evaluate(frontend::AST::Stmt stmt);
        Interpreter();
    private:
        values::RuntimeVal evaluate_binary_expr(frontend::AST::BinaryExpr binop);
        values::RuntimeVal evaluate_program(frontend::AST::Program program);
        values::NumVal evaluate_numeric_binary_expr(values::NumVal lhs, values::NumVal rhs, std::string theoperator);
    };
}