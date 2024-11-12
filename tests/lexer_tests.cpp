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
        if (expected[i].type != actual[i].type) {
            std::cerr << "Token type mismatch at position " << i << ": expected "
                      << TokenTypeToString(expected[i].type) << ", got "
                      << TokenTypeToString(actual[i].type) << std::endl;
        }
        assert(expected[i].type == actual[i].type);

        if (expected[i].literal != actual[i].literal) {
            std::cerr << "Token literal mismatch at position " << i << ": expected '"
                      << expected[i].literal << "', got '"
                      << actual[i].literal << "'" << std::endl;
        }
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
    std::cout << "Running Lexer Tests" << std::endl;
    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

// Test Program 1
// Test Program 1
void test_program1() {
    std::ifstream file("tests/lexer_tests/lexer_test1.fpp");
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
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "7"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "10"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "result"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::PLUS, "+"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::EOF_TOKEN, "")
    };

    compareTokens(expectedTokens, tokens);

    std::cout << "test_program1 passed" << std::endl;
}

// Test Program 2
void test_program2() {
    std::ifstream file("tests/lexer_tests/lexer_test2.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test2.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "7"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::IF, "if"),
        Token(TokenType::LPAREN, "("),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::EQ, "=="), // You might need to add EQ to your TokenType enum if not present
        Token(TokenType::INT_LITERAL, "7"),
        Token(TokenType::RPAREN, ")"),
        Token(TokenType::LBRACE, "{"),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::MINUS, "-"),
        Token(TokenType::INT_LITERAL, "1"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::RBRACE, "}"),
        Token(TokenType::EOF_TOKEN, "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program2 passed" << std::endl;
}

// Test Program 3
void test_program3() {

    std::ifstream file("tests/lexer_tests/lexer_test3.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test3.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    // Expected tokens
    std::vector<Token> expectedTokens =  {
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "n"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "3"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "result"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "1"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::FOR, "forn"), // Assuming 'forn' is recognized as 'FOR' keyword
        Token(TokenType::LPAREN, "("),
        Token(TokenType::IDENT, "i"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENT, "n"),
        Token(TokenType::RPAREN, ")"),
        Token(TokenType::LBRACE, "{"),
        Token(TokenType::IDENT, "result"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::IDENT, "result"),
        Token(TokenType::ASTERISK, "*"),
        Token(TokenType::IDENT, "i"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::RBRACE, "}"),
        Token(TokenType::EOF_TOKEN, "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program3 passed" << std::endl;
}

// Test Program 4
void test_program4() {
    std::ifstream file("tests/lexer_tests/lexer_test4.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test4.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "10"),
        Token(TokenType::WHILE, "while"),
        Token(TokenType::LPAREN, "("),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::GT, ">"),
        Token(TokenType::INT_LITERAL, "5"),
        Token(TokenType::RPAREN, ")"),
        Token(TokenType::LBRACE, "{"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::MINUS, "-"),
        Token(TokenType::INT_LITERAL, "1"),
        Token(TokenType::RBRACE, "}"),
        Token(TokenType::EOF_TOKEN, "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token


    compareTokens(expectedTokens, tokens);

    std::cout << "test_program4 passed" << std::endl;
}

// Test Program 5
void test_program5() {
    std::ifstream file("tests/lexer_tests/lexer_test5.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening lexer_test5.fpp" << std::endl;
        return;
    }
    std::string program((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

        // Expected tokens
    std::vector<Token> expectedTokens = {
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "5"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::INT, "int"),
        Token(TokenType::IDENT, "x"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT_LITERAL, "5"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::IF, "if"),
        Token(TokenType::LPAREN, "("),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::EQ, "=="), 
        Token(TokenType::IDENT, "x"),
        Token(TokenType::AND, "&&"),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::EQ, "=="),
        Token(TokenType::INT_LITERAL, "5"),
        Token(TokenType::RPAREN, ")"),
        Token(TokenType::LBRACE, "{"),
        Token(TokenType::IDENT, "DBG"), 
        Token(TokenType::LPAREN, "("),
        Token(TokenType::IDENT, "y"),
        Token(TokenType::RPAREN, ")"),
        Token(TokenType::SEMICOLON, ";"),
        Token(TokenType::RBRACE, "}"),
        Token(TokenType::EOF_TOKEN, "")
    };

    Lexer lexer(program);

    // Get tokens
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token

    compareTokens(expectedTokens, tokens);

    std::cout << "test_program5 passed" << std::endl;
}
