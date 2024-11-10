#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"

// Function to compare AST nodes
void compareASTNodes(const std::shared_ptr<ASTNode>& expected, const std::shared_ptr<ASTNode>& actual) {
    assert(expected->nodeType == actual->nodeType);
    assert(expected->value == actual->value);
    assert(expected->children.size() == actual->children.size());

    for (size_t i = 0; i < expected->children.size(); ++i) {
        compareASTNodes(expected->children[i], actual->children[i]);
    }
}

// Test function for parsing a simple declaration
void testSimpleDeclaration() {
    auto lexer = std::make_shared<Lexer>("int x = 7;");
    Parser parser(lexer);

    auto program = parser.ParseProgram();
    auto expectedAST = std::make_shared<ASTNode>(NODE_TYPE_VARIABLE, "Declaration");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));

    compareASTNodes(expectedAST, program->statements[0]);
}

// Test function for parsing multiple declarations and assignments
void testMultipleDeclarationsAndAssignments() {
    auto lexer = std::make_shared<Lexer>("int x = 7; int y = 10; result = x + y;");
    Parser parser(lexer);

    auto program = parser.ParseProgram();
    auto expectedAST = std::make_shared<ASTNode>(NODE_TYPE_VARIABLE, "Declaration");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "y", "10"));
    expectedAST->children.push_back(std::make_shared<ASTNode>("Assignment", "result", "+", "x", "y"));

    compareASTNodes(expectedAST, program->statements[0]);
}

// Test function for parsing an if statement
void testIfStatement() {
    auto lexer = std::make_shared<Lexer>("int x = 7; if (x == 7) { x = x - 1; }");
    Parser parser(lexer);

    auto program = parser.ParseProgram();
    auto expectedAST = std::make_shared<ASTNode>(NODE_TYPE_VARIABLE, "Declaration");
    expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));

    auto ifStmt = std::make_shared<ASTNode>("IfStatement");
    ifStmt->children.push_back(std::make_shared<ASTNode>("Condition", "==", "x", "7"));
    ifStmt->children.push_back(std::make_shared<ASTNode>("Assignment", "x", "-", "x", "1"));

    expectedAST->children.push_back(ifStmt);

    compareASTNodes(expectedAST, program->statements[0]);
}

// Main function to run all tests
int main() {
    testSimpleDeclaration();
    testMultipleDeclarationsAndAssignments();
    testIfStatement();
    return 0;
}