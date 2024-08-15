#include <iostream>
#include <string>
#include "utils.hpp"
#include "frontend/lexer.hpp"
#include "frontend/parser.hpp"
#include "runtime/interpreter.hpp"
#include <fstream>
#include <fmt/core.h>

using namespace runtime;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        auto source = utils::readFile(argv[1]);
        if (source.empty()) {
            std::cerr << "There was an error opening file " << argv[1] << std::endl;
            return 1;
        }
        //frontend::Lexer lexer;
        //auto tokens = lexer.tokenize(source);
        //for (auto token : tokens) {
        //    int tokken = static_cast<int>(token.type);
        //    std::cout << "{" << "type: " << tokken << ", value: " << '"' << token.value << '"' << "}\n";
        //}
        frontend::Parser parser;

        auto program = parser.produceAST(source);

        Interpreter interpret;
        auto thing = interpret.evaluate(program);
        try {
            auto result = thing;
        } catch (std::invalid_argument& e) {
            fmt::print("Error: {}", e.what());
        } catch (std::out_of_range& e) {
            fmt::print("Out of range error: {}", e.what());
        } catch (...) {
            fmt::print("Unknown error.");
        }
        

        

    } else {
        std::cout << "Missing argument: Yohohoscript file" << std::endl << "Usage: " << argv[0] << " <YohohoScript file>";
        return 1;
    }

    return 0;
}