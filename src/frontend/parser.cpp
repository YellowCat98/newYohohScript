#include "parser.hpp"

using namespace frontend;

Parser::Parser() : lexer() {}

Parser::~Parser() = default;

bool Parser::isNotEOF() {
    return tokens[0].type != Lexer::TokenType::END_OF_FILE;
}

Lexer::Token Parser::at() {
    return tokens[0];
}

Lexer::Token Parser::eat() {
    auto prev = tokens.front();
    tokens.pop_front();
    return prev;
}

Lexer::Token Parser::expect(Lexer::TokenType type, std::string err) {
    auto prev = tokens.front();
    tokens.pop_front();
    if (prev.type != type) {
        std::cerr << "Parser error: " << err << std::endl;
        exit(1);
    }

    return prev;
}

AST::Program Parser::produceAST(std::string sourceCode) {
    tokens = lexer.tokenize(sourceCode);

    AST::Program program;
    while (isNotEOF()) {
        program.body.push_back(parse_stmt());
    }
    

    return program;
}

AST::Expr Parser::parse_additive_expr() {
    auto left = parse_multiplicative_expr();

    while (at().value == "+" || at().value == "-" || at().value == "%") {
        auto theoperator = eat().value;
        auto right = parse_multiplicative_expr();

        AST::BinaryExpr binExpr;
        binExpr.kind = AST::NodeType::BinaryExpr;
        binExpr.left = left;
        binExpr.right = right;
        binExpr.theoperator = theoperator;

        left = binExpr; // if only there was an easier way to do this
        //std::cout << "left: " << static_cast<int>(binExpr.left.kind) << std::endl;
        //std::cout << "right: " << static_cast<int>(binExpr.right.kind) << std::endl;
        //std::cout << "operator: " << binExpr.theoperator << std::endl;
    }

    

    return left;
}

AST::Expr Parser::parse_multiplicative_expr() {
    auto left = parse_primary_expr();

    while (at().value == "/" || at().value == "*") {
        auto theoperator = eat().value;
        auto right = parse_primary_expr();

        AST::BinaryExpr binExpr;
        binExpr.kind = AST::NodeType::BinaryExpr;
        binExpr.left = left;
        binExpr.right = right;
        binExpr.theoperator = theoperator;

        left = binExpr; // if only there was an easier way to do this
        //std::cout << "left: " << static_cast<int>(binExpr.left.kind) << std::endl;
        //std::cout << "right: " << static_cast<int>(binExpr.right.kind) << std::endl;
        //std::cout << "operator: " << binExpr.theoperator << std::endl;
    }

    

    return left;
}


AST::Stmt Parser::parse_stmt() {
    return parse_expr();
}

AST::Expr Parser::parse_expr() {
    return parse_additive_expr();
}

AST::Expr Parser::parse_primary_expr() {
    auto tk = at().type;


    switch (tk) {
        case Lexer::TokenType::Identifier: {
            AST::Identifier ident;
            ident.kind = AST::NodeType::Identifier;
            ident.symbol = eat().value;
            return ident;
        }
        case Lexer::TokenType::Null: {
            eat();
            AST::NullLiteral nullliteral;
            return nullliteral; // return this, useful comment, isnt it?
        }
        case Lexer::TokenType::Int: {
            AST::NumericLiteral num;
            num.kind = AST::NodeType::NumericLiteral;
            num.value = std::stoi(eat().value);
            return num;
        }
        case Lexer::TokenType::OpenParen: {
            eat();
            auto value = parse_expr();
            expect(Lexer::TokenType::CloseParen, "Unexpected Token found, expected closing parenthesis.");
            return value;
        }
        default: {
            std::cerr << "Unexpected token found: " << at().value;
            exit(1);
        }
    }
}