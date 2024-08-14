#include "interpreter.hpp"

using namespace runtime;
using namespace frontend;

Interpreter::Interpreter() {}

values::RuntimeVal Interpreter::evaluate(AST::Stmt stmt) {
    switch (stmt.kind) {
        case AST::NodeType::NumericLiteral: {
            auto num = static_cast<AST::NumericLiteral&>(stmt);

            values::NumVal numval;
            numval.value = num.value;
            numval.type = values::ValueType::number;

            return numval;
        }
        default: {
            AST::NullLiteral null;
            values::NullVal thevalues;
            thevalues.type = values::ValueType::null;
            return thevalues;
        }
    }
}