#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <map>

/*
 * example code:
 * var x = 5 + (2 * 4)
*/
namespace frontend {
    class Lexer {
    public:
        enum class TokenType {
            Int,
            Identifier,
            Equals,
            OpenParen,
            CloseParen,
            BinaryOperator,
            Var,
            Null,
            END_OF_FILE,
        };
        struct Token {
            std::string value;
            TokenType type;
        };

        static std::map<std::string, TokenType> KEYWORDS;

        Token token(std::string value, TokenType type);
        Lexer();

        std::deque<Token> tokenize(std::string sourceCode);
    };
}