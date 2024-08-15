#pragma once
#include "lexer.hpp"
#include "ast.hpp"
#include <deque>
#include <iostream>

namespace frontend {
    class Parser {
    private:
        std::deque<Lexer::Token> tokens;
        Lexer lexer;
        bool isNotEOF();
        Lexer::Token at();

        AST::Stmt parse_stmt();
        AST::Expr parse_expr();
        AST::Expr parse_primary_expr();
        AST::Expr parse_additive_expr();
        AST::Expr parse_multiplicative_expr();

        Lexer::Token eat();
        Lexer::Token expect(Lexer::TokenType type, std::string err);
    public:
        AST::Program produceAST(std::string sourceCode);
        Parser();
    };
}