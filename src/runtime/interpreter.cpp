#include "interpreter.hpp"
#include <fmt/core.h>

using namespace runtime;
using namespace frontend;

Interpreter::Interpreter() {}

values::RuntimeVal Interpreter::evaluate_program(AST::Program program) {
    values::RuntimeVal lastEvaluated;
    lastEvaluated.type = values::ValueType::null;
    for (auto statement : program.body) {
        fmt::print("Evaluating\n");
        lastEvaluated = evaluate(statement);
        fmt::print("Finished evaluating, type: {}\n", static_cast<int>(lastEvaluated.type));
    }
    
    return lastEvaluated;
}

values::RuntimeVal Interpreter::evaluate_binary_expr(AST::BinaryExpr binop) {
    auto lhs = evaluate(binop.left);
    auto rhs = evaluate(binop.right);

    if (lhs.type == values::ValueType::number && rhs.type == values::ValueType::number) {
        return evaluate_numeric_binary_expr(static_cast<values::NumVal&>(lhs), static_cast<values::NumVal&>(rhs), binop.theoperator);
    }

    values::NullVal null;
    return null;
}

values::NumVal Interpreter::evaluate_numeric_binary_expr(values::NumVal lhs, values::NumVal rhs, std::string theoperator) {
    int result = 0;
    if (theoperator == "+") {
        result = lhs.value + rhs.value;
    } else if (theoperator == "-") {
        result = lhs.value - rhs.value;
    } else if (theoperator == "*") {
        result = lhs.value * rhs.value;
    } else if (theoperator == "/") {
        result = lhs.value / rhs.value;
    } else if (theoperator == "%") {
        result = lhs.value % rhs.value;
    }

    values::NumVal val;
    val.value = result;
    val.type = values::ValueType::number;
    return val;
}

values::RuntimeVal Interpreter::evaluate(AST::Stmt stmt) {
    switch (stmt.kind) {
        case AST::NodeType::NumericLiteral: {
            fmt::print("NumericLiteral found\n");
            auto num = static_cast<AST::NumericLiteral&>(stmt);

            values::NumVal numval;
            numval.value = num.value;
            numval.type = values::ValueType::number;

            return numval;
        }
        case AST::NodeType::NullLiteral: {
            fmt::print("Null Found\n");
            AST::NullLiteral null;
            values::NullVal thevalues;
            thevalues.type = values::ValueType::null;
            return thevalues;
        }
        case AST::NodeType::BinaryExpr: {
            fmt::print("BinaryExpr found\n");
            return evaluate_binary_expr(static_cast<AST::BinaryExpr&>(stmt));
        }
        case AST::NodeType::Program: {
            fmt::print("Program found\n");
            return evaluate_program(static_cast<AST::Program&>(stmt));
        }
        default: {
            fmt::print("An error had occured.");
            exit(1);
        }
    }
}