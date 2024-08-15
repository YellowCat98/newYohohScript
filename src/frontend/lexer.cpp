#include "lexer.hpp"
#include "../utils.hpp"

using namespace frontend;

std::map<std::string, frontend::Lexer::TokenType> frontend::Lexer::KEYWORDS = {
    {"var", TokenType::Var},
    {"null", TokenType::Null}
};

Lexer::Lexer() {}


Lexer::Token Lexer::token(std::string value, TokenType type) {
    return {value, type};
}

std::deque<Lexer::Token> Lexer::tokenize(std::string sourceCode) {
    std::deque<Token> tokens;
    std::deque<std::string> src = utils::split(sourceCode, "");

    while (src.size() > 0) {
        if (src[0] == "(") {
            auto shiftValue = src.front();
            src.pop_front();
            tokens.push_back(token(shiftValue, TokenType::OpenParen));
        } else if (src[0] == ")") {
            auto shiftValue = src.front();
            src.pop_front();
            tokens.push_back(token(shiftValue, TokenType::CloseParen));
        } else if (src[0] == "+" || src[0] == "-" || src[0] == "*" || src[0] == "/" || src[0] == "%") {
            auto shiftValue = src.front();
            src.pop_front();
            tokens.push_back(token(shiftValue, TokenType::BinaryOperator));
        } else if (src[0] == "=") {
            auto shiftValue = src.front();
            src.pop_front();
            tokens.push_back(token(shiftValue, TokenType::Equals));
        } else {
            if (utils::isInt(src[0])) {
                std::string num = "";
                while (src.size() > 0 && utils::isInt(src[0])) {
                    auto shiftValue = src.front();
                    src.pop_front();
                    num += shiftValue;
                }

                tokens.push_back(token(num, TokenType::Int));
            } else if (utils::isAlpha(src[0])) {
                std::string ident = "";
                while (src.size() > 0 && utils::isAlpha(src[0])) {
                    auto shiftValue = src.front();
                    src.pop_front();
                    ident += shiftValue;
                }
                if (utils::undefined(KEYWORDS, ident)) {
                    tokens.push_back(token(ident, TokenType::Identifier));
                } else {
                    tokens.push_back(token(ident, KEYWORDS[ident]));
                }
            } else if (utils::isSkippable(src[0])) {
                src.pop_front(); // only pop front as we dont need anything to do with the value
            } else {
                std::cout << "Unrecognized character: " << src[0] << std::endl;
                exit(1);
            }
        }
    }

    tokens.push_back(token("EndOfFile", TokenType::END_OF_FILE));

    return tokens;
}