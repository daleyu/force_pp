#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "token/token.h"
#include "lexer/lexer.h"

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
    Token tok = lexer.nextToken();
    while (tok.type != "EOF") {
        tokens.push_back(tok);
        std::cout << tok.type << ' ' << tok.literal << std::endl;
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    return 0;
}
