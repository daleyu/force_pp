#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "../lexer/lexer.h"
#include "../token/token.h"

void test_keyword();
void test_type();
void test_symbol();
void test_operator();
void test_number();
void test_identifier();

int main() {
    // Main testing function
    test_keyword();
    test_type();
    test_symbol();
    test_operator();
    test_number();
    test_identifier();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

void test_keyword() {
    std::vector<std::string> keywords = {"while", "if", "else", "for", "forn"};
    for (const auto& kw : keywords) {
        Lexer lexer(kw);
        Token token = lexer.nextToken();
        assert(token.type == LookupIdent(kw));
        assert(token.literal == kw);
    }
    std::cout << "test_keyword passed" << std::endl;
}

void test_type() {
    std::vector<std::string> types = {"int", "vector", "ll", "pair"};
    for (const auto& ty : types) {
        Lexer lexer(ty);
        Token token = lexer.nextToken();
        assert(token.type == LookupIdent(ty));
        assert(token.literal == ty);
    }
    std::cout << "test_type passed" << std::endl;
}

void test_symbol() {
    std::vector<std::string> symbols = {"(", ")", "{", "}", ";"};
    std::unordered_map<std::string, TokenType> symbolMap{
        {"(", TokenType::LPAREN},  {")", TokenType::RPAREN},
        {"{", TokenType::LBRACE},  {"}", TokenType::RBRACE},
        {";", TokenType::SEMICOLON}
    };
    for (const auto& sym : symbols) {
        Lexer lexer(sym);
        Token token = lexer.nextToken();
        assert(token.type == symbolMap[sym]);
        assert(token.literal == sym);
    }
    std::cout << "test_symbol passed" << std::endl;
}

void test_operator() {
    std::vector<std::string> operators = {"+", "-", "/", "*", "=", "=="};
    std::unordered_map<std::string, TokenType> opMap{
        {"+", TokenType::PLUS},    {"-", TokenType::MINUS},
        {"/", TokenType::SLASH},   {"*", TokenType::ASTERISK},
        {"=", TokenType::ASSIGN},  {"==", TokenType::EQUAL}
    };
    for (const auto& op : operators) {
        Lexer lexer(op);
        Token token = lexer.nextToken();
        assert(token.type == opMap[op]);
        assert(token.literal == op);
    }
    std::cout << "test_operator passed" << std::endl;
}

void test_number() {
    std::vector<std::string> numbers = {"0", "123", "456789"};
    for (const auto& num : numbers) {
        Lexer lexer(num);
        Token token = lexer.nextToken();
        assert(token.type == TokenType::NUMBER);
        assert(token.literal == num);
    }
    std::cout << "test_number passed" << std::endl;
}

void test_identifier() {
    std::vector<std::string> identifiers = {"a", "abc", "a1b2c3", "variable", "x0"};
    for (const auto& id : identifiers) {
        Lexer lexer(id);
        Token token = lexer.nextToken();
        assert(token.type == TokenType::IDENTIFIER);
        assert(token.literal == id);
    }
    std::cout << "test_identifier passed" << std::endl;
}
