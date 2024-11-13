#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "token/token.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "Usage: ./main <file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    file.close();

    // Initialize Lexer
    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        std::cout << TokenTypeToString(tok.type) << '\n';
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    Parser parser(tokens);
    parser.parseProgram();

    parser.printNodes();

    //print out the errors
    std::vector<std::string> errors = parser.Errors();
    for (std::string error : errors) {
        std::cout << error << '\n';
    }



    return 0;
}
