#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "../token/token.h"
#include "../lexer/lexer.h"

// Function to compare expected and actual tokens
void compareTokens(const std::vector<Token>& expected, const std::vector<Token>& actual) {
    assert(expected.size() == actual.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        assert(expected[i].type == actual[i].type);
        assert(expected[i].literal == actual[i].literal);
    }
}

// Test function declarations
void test_program1();
void test_program2();
void test_program3();
void test_program4();
void test_program5();

int main() {
    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

// Test Program 1
void test_program1() {
    std::ifstream file("tests/test-files/lexer_test1.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test1.fpp" << std::endl;
        return;
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
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token("TYPE", "int"),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "="),
        Token("NUMBER", "7"),
        Token("SYMBOL", ";"),
        Token("TYPE", "int"),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "="),
        Token("NUMBER", "10"),
        Token("SYMBOL", ";"),
        Token("TYPE", "int"),
        Token("IDENTIFIER", "result"),
        Token("OPERATOR", "="),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "+"),
        Token("IDENTIFIER", "y"),
        Token("SYMBOL", ";"),
        Token("EOF", "")
    };

    compareTokens(expectedTokens, tokens);

    std::cout << "test_program1 passed" << std::endl;
}

// Test Program 2
void test_program2() {
    std::ifstream file("tests/test-files/lexer_test2.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test2.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token("TYPE", "int"),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "="),
        Token("NUMBER", "7"),
        Token("SYMBOL", ";"),
        Token("KEYWORD", "if"),
        Token("SYMBOL", "("),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "=="),
        Token("NUMBER", "7"),
        Token("SYMBOL", ")"),
        Token("SYMBOL", "{"),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "="),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "-"),
        Token("NUMBER", "1"),
        Token("SYMBOL", ";"),
        Token("SYMBOL", "}"),
        Token("EOF", "")
    };


    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.nextToken();
    while (tok.type != "EOF") {
        tokens.push_back(tok);
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program2 passed" << std::endl;
}

// Test Program 3
void test_program3() {

    std::ifstream file("tests/test-files/lexer_test3.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test3.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    // Expected tokens
    std::vector<Token> expectedTokens =  {
        Token("TYPE", "int"),
        Token("IDENTIFIER", "n"),
        Token("OPERATOR", "="),
        Token("NUMBER", "3"),
        Token("SYMBOL", ";"),
        Token("TYPE", "int"),
        Token("IDENTIFIER", "result"),
        Token("OPERATOR", "="),
        Token("NUMBER", "1"),
        Token("SYMBOL", ";"),
        Token("KEYWORD", "forn"),
        Token("SYMBOL", "("),
        Token("IDENTIFIER", "i"),
        Token("SYMBOL", ","),
        Token("IDENTIFIER", "n"),
        Token("SYMBOL", ")"),
        Token("SYMBOL", "{"),
        Token("IDENTIFIER", "result"),
        Token("OPERATOR", "="),
        Token("IDENTIFIER", "result"),
        Token("OPERATOR", "*"),
        Token("IDENTIFIER", "i"),
        Token("SYMBOL", ";"),
        Token("SYMBOL", "}"),
        Token("EOF", "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.nextToken();
    while (tok.type != "EOF") {
        tokens.push_back(tok);
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program3 passed" << std::endl;
}

// Test Program 4
void test_program4() {
    std::ifstream file("tests/test-files/lexer_test4.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test4.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token("TYPE", "int"),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "="),
        Token("NUMBER", "10"),
        Token("KEYWORD", "while"),
        Token("SYMBOL", "("),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", ">"),
        Token("NUMBER", "5"),
        Token("SYMBOL", ")"),
        Token("SYMBOL", "{"),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "="),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "-"),
        Token("NUMBER", "1"),
        Token("SYMBOL", "}"),
        Token("EOF", "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.nextToken();
    while (tok.type != "EOF") {
        tokens.push_back(tok);
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program4 passed" << std::endl;
}

// Test Program 5
void test_program5() {
    std::ifstream file("tests/test-files/lexer_test5.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test5.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

        // Expected tokens
    std::vector<Token> expectedTokens = {
        Token("TYPE", "int"),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "="),
        Token("NUMBER", "5"),
        Token("SYMBOL", ";"),
        Token("TYPE", "int"),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "="),
        Token("NUMBER", "5"),
        Token("SYMBOL", ";"),
        Token("KEYWORD", "if"),
        Token("SYMBOL", "("),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "=="),
        Token("IDENTIFIER", "x"),
        Token("OPERATOR", "&&"),
        Token("IDENTIFIER", "y"),
        Token("OPERATOR", "=="),
        Token("NUMBER", "5"),
        Token("SYMBOL", ")"),
        Token("SYMBOL", "{"),
        Token("IDENTIFIER", "DBG"),
        Token("SYMBOL", "("),
        Token("IDENTIFIER", "y"),
        Token("SYMBOL", ")"),
        Token("SYMBOL", ";"),
        Token("SYMBOL", "}"),
        Token("EOF", "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.nextToken();
    while (tok.type != "EOF") {
        tokens.push_back(tok);
        tok = lexer.nextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    compareTokens(expectedTokens, tokens);

    std::cout << "test_program5 passed" << std::endl;
}
