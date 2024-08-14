#pragma once
#include <string>
#include <map>
#include <deque>
#include <memory>

namespace frontend {
    class AST {
    public:
        enum class NodeType {
            Program,
            NumericLiteral,
            NullLiteral,
            Identifier,
            BinaryExpr
        };

        struct Stmt {
            NodeType kind;
        };

        struct Program : public Stmt {
            Program() {
                kind = NodeType::Program;
            }

            std::deque<Stmt> body;
        };

        struct Expr : public Stmt {};

        struct BinaryExpr : public Expr {
            BinaryExpr() {
                kind = NodeType::BinaryExpr;
            }
            Expr left;
            Expr right;
            std::string theoperator; // operator is a reserved keyword!
        };

        struct Identifier : public Expr {
            Identifier() {
                kind = NodeType::Identifier;
            };
            std::string symbol;
        };

        struct NumericLiteral : public Expr {
            NumericLiteral() {
                kind = NodeType::NumericLiteral;
            }
            int value;
        };

        struct NullLiteral : public Expr {
            NullLiteral() {
                kind = NodeType::NullLiteral;
            }
            int value = 0;
        };
    };
}