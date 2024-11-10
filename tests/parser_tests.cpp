Given your request to adapt the code to test whether a parser is functioning correctly, we can update the tests to focus on parsing features rather than just tokenization. This involves using a `Parser` object and constructing an abstract syntax tree (AST) to verify. We'll assume the existence of a `Parser` class with appropriate methods for this task.

Here is a rewritten version of the original code to test parser functionality:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "../token/token.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../ast/ast.h"  // Hypothetical AST header

// Function to compare expected and actual AST nodes
void compareASTNodes(const std::shared_ptr<ASTNode>& expected, const std::shared_ptr<ASTNode>& actual) {
    assert(expected->nodeType == actual->nodeType);
    assert(expected->value == actual->value);
    assert(expected->children.size() == actual->children.size());

    for (size_t i = 0; i < expected->children.size(); ++i) {
        compareASTNodes(expected->children[i], actual->children[i]);
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
    std::cout << "All parser tests passed!" << std::endl;
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

    // Initialize Lexer and Parser
    Lexer lexer(program);
    Parser parser(lexer);

    // Get the AST
    std::shared_ptr<ASTNode> actualAST = parser.parseProgram();

    // Expected AST
    std::shared_ptr<ASTNode> expectedAST = std::make_shared<ASTNode>("Program");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "y", "10"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Assignment", "result", "+", "x", "y"));

    compareASTNodes(expectedAST, actualAST);
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
    Lexer lexer(program);
    Parser parser(lexer);

    std::shared_ptr<ASTNode> actualAST = parser.parseProgram();

    std::shared_ptr<ASTNode> expectedAST = std::make_shared<ASTNode>("Program");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));
    auto ifStmt = std::make_shared<ASTNode>("IfStatement");
    ifStmt->children.push_back(std::make_shared<ASTNode>("Condition", "==", "x", "7"));
    ifStmt->children.push_back(std::make_shared<ASTNode>("Assignment", "x", "-", "x", "1"));
    expectedAST->children.push_back(ifStmt);

    compareASTNodes(expectedAST, actualAST);
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

    Lexer lexer(program);
    Parser parser(lexer);

    std::shared_ptr<ASTNode> actualAST = parser.parseProgram();

    std::shared_ptr<ASTNode> expectedAST = std::make_shared<ASTNode>("Program");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "n", "3"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "result", "1"));
    auto forStmt = std::make_shared<ASTNode>("ForLoop");
    forStmt->children.push_back(std::make_shared<ASTNode>("Iterator", "i", "n"));
    forStmt->children.push_back(std::make_shared<ASTNode>("Assignment", "result", "*", "result", "i"));
    expectedAST->children.push_back(forStmt);

    compareASTNodes(expectedAST, actualAST);
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
    Lexer lexer(program);
    Parser parser(lexer);

    std::shared_ptr<ASTNode> actualAST = parser.parseProgram();

    std::shared_ptr<ASTNode> expectedAST = std::make_shared<ASTNode>("Program");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "y", "10"));
    auto whileStmt = std::make_shared<ASTNode>("WhileLoop");
    whileStmt->children.push_back(std::make_shared<ASTNode>("Condition", ">", "y", "5"));
    whileStmt->children.push_back(std::make_shared<ASTNode>("Assignment", "y", "-", "y", "1"));
    expectedAST->children.push_back(whileStmt);

    compareASTNodes(expectedAST, actualAST);
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

    Lexer lexer(program);
    Parser parser(lexer);

    std::shared_ptr<ASTNode> actualAST = parser.parseProgram();

    std::shared_ptr<ASTNode> expectedAST = std::make_shared<ASTNode>("Program");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "y", "5"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "5"));

    auto ifStmt = std::make_shared<ASTNode>("IfStatement");
    ifStmt->children.push_back(std::make_shared<ASTNode>("Condition", "&&",
                        std::make_shared<ASTNode>("Condition", "==", "y", "x"),
                        std::make_shared<ASTNode>("Condition", "==", "y", "5")));
    auto dbgStmt = std::make_shared<ASTNode>("FunctionCall", "DBG");
    dbgStmt->children.push_back(std::make_shared<ASTNode>("Argument", "y"));
    ifStmt->children.push_back(dbgStmt);

    expectedAST->children.push_back(ifStmt);

    compareASTNodes(expectedAST, actualAST);
    std::cout << "test_program5 passed" << std::endl;
}
