#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../token/token.h"

// Test function declarations
void test_program1();
void test_program2();
void test_program3();
void test_program4();
void test_program5();

// Function to read a file and return its contents as a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        assert(false);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to run the parser on input and print the AST
void runParserTest(const std::string& input) {
    // Create Lexer with input
    Lexer lexer(input);

    // Collect Tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Include EOF token

    // Create Parser with tokens
    Parser parser(tokens);

    // Parse the program
    parser.parseProgram();

    // Optionally, print the nodes
    parser.printNodes();

    // Check for parsing errors
    if (!parser.errors.empty()) {
        std::cerr << "Errors encountered during parsing:" << std::endl;
        for (const auto& err : parser.errors) {
            std::cerr << err << std::endl;
        }
        assert(false);
    }
}

// Test functions
void test_program1() {
    std::string input = readFile("tests/parser_tests/parser_test1.fpp");
    runParserTest(input);
    std::cout << "test_program1 passed" << std::endl;
}

void test_program2() {
    std::string input = readFile("tests/parser_tests/parser_test2.fpp");
    runParserTest(input);
    std::cout << "test_program2 passed" << std::endl;
}

void test_program3() {
    std::string input = readFile("tests/parser_tests/parser_test3.fpp");
    runParserTest(input);
    std::cout << "test_program3 passed" << std::endl;
}

void test_program4() {
    std::string input = readFile("tests/parser_tests/parser_test4.fpp");
    runParserTest(input);
    std::cout << "test_program4 passed" << std::endl;
}

void test_program5() {
    std::string input = readFile("tests/parser_tests/parser_test5.fpp");
    runParserTest(input);
    std::cout << "test_program5 passed" << std::endl;
}

// Main function to run all tests
int main() {
    std::cout << "Running Parser Tests" << std::endl;

    // Run individual tests
    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();

    std::cout << "All parser tests passed!" << std::endl;
    return 0;
}
