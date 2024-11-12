#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"
#include <iostream>

// Test function declarations
int test_program1();
int test_program2();
int test_program3();
int test_program4();
int test_program5();

// // Function to compare AST nodes
// bool compareAST(const ASTNode* expected, const ASTNode* actual) {
//     if (!expected && !actual){
//         return true;
//     }
//     if (!expected || !actual){
//         return false;
//     }
//     if (expected->tokenLiteral() != actual->tokenLiteral()) {
//         return false;
//     }

//     // Use dynamic_cast to compare specific node types
//     if (auto expectedProgram = dynamic_cast<const Program*>(expected)) {
//         auto actualProgram = dynamic_cast<const Program*>(actual);
//         if (!actualProgram) return false;
//         if (expectedProgram->functions.size() != actualProgram->functions.size()) return false;
//         for (size_t i = 0; i < expectedProgram->functions.size(); ++i) {
//             if (!compareAST(expectedProgram->functions[i].get(), actualProgram->functions[i].get()))
//                 return false;
//         }
//         return true;
//     }
//     // Add comparisons for other node types similarly...

//     // If node types don't match
//     return false;
// }

// Helper function to print the AST
void printAST(ASTNode* node, int indent = 0) {
    std::string indentStr(indent, ' ');

    if (auto program = dynamic_cast<Program*>(node)) {
        std::cout << indentStr << "Program" << std::endl;
        for (auto& stmt : program->statements) {
            printAST(stmt.get(), indent + 2);
        }
    } else if (auto varDecl = dynamic_cast<VariableDeclaration*>(node)) {
        std::cout << indentStr << "VariableDeclaration" << std::endl;
        std::cout << indentStr << "  Type: " << varDecl->type << std::endl;
        std::cout << indentStr << "  Name: " << varDecl->name << std::endl;
        if (varDecl->initializer) {
            std::cout << indentStr << "  Initializer:" << std::endl;
            printAST(varDecl->initializer.get(), indent + 4);
        } else {
            std::cout << indentStr << "  Initializer: None" << std::endl;
        }
    } else if (auto literal = dynamic_cast<Literal*>(node)) {
        std::cout << indentStr << "Literal" << std::endl;
        std::cout << indentStr << "  Type: ";
        switch (literal->type) {
            case Literal::Type::Integer:
                std::cout << "Integer";
                break;
            case Literal::Type::Float:
                std::cout << "Float";
                break;
            case Literal::Type::String:
                std::cout << "String";
                break;
            case Literal::Type::Char:
                std::cout << "Char";
                break;
            case Literal::Type::Boolean:
                std::cout << "Boolean";
                break;
        }
        std::cout << std::endl;
        std::cout << indentStr << "  Value: " << literal->value << std::endl;
    } else if (auto identifier = dynamic_cast<Identifier*>(node)) {
        std::cout << indentStr << "Identifier" << std::endl;
        std::cout << indentStr << "  Value: " << identifier->value << std::endl;
    } else if (auto exprStmt = dynamic_cast<ExpressionStatement*>(node)) {
        std::cout << indentStr << "ExpressionStatement" << std::endl;
        if (exprStmt->expression) {
            printAST(exprStmt->expression.get(), indent + 2);
        }
    } else if (auto binaryExpr = dynamic_cast<BinaryExpression*>(node)) {
        std::cout << indentStr << "BinaryExpression" << std::endl;
        std::cout << indentStr << "  Operator: " << binaryExpr->op << std::endl;
        std::cout << indentStr << "  Left:" << std::endl;
        printAST(binaryExpr->left.get(), indent + 4);
        std::cout << indentStr << "  Right:" << std::endl;
        printAST(binaryExpr->right.get(), indent + 4);
    } else {
        std::cout << indentStr << "Unknown AST Node" << std::endl;
    }
}

int basicDeclarationTest() {
    std::string input = "int x = 42;";
    std::cout << "Basic Declaration test" << std::endl;

    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    auto program = parser.ParseProgram();

    if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Print the AST
    printAST(program.get());

    std::cout << "Basic Declaration test passed" << std::endl;
    return 0;
}

// Test function for parsing a simple function declaration
int testSimpleDeclaration() {
    std::string input = "int add(int a, int b) { return a + b; }";
    std::cout << "Basic Function test" << std::endl;
    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    auto program = parser.ParseProgram();

    if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Print the AST
    printAST(program.get());

    std::cout << "Basic function declaration test passed" << std::endl;
    return 0;
}


// Test function for parsing multiple declarations and assignments
int testMultipleDeclarationsAndAssignments() {
    std::cout << "Test Multiple Declarations" << std::endl;
    std::string input = "int x = 7; int y = 10; result = x + y;";
    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    auto program = parser.ParseProgram();

    if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Print the AST
    printAST(program.get());

    std::cout << "multiple declarations test passed" << std::endl;
    return 0;
}

// Test function for parsing an if statement
int testIfStatement() {
    std::cout << "testIfStatement" << std::endl;
    std::string input = "int x = 7; if (x == 7) { x = x - 1; }";
    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    auto program = parser.ParseProgram();

    if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Print the AST
    printAST(program.get());

    std::cout << "Basic function declaration test passed" << std::endl;
    return 0;
}

int test_program1() {
    std::ifstream file("tests/parser_tests/parser_test1.fpp");
    if (!file.is_open()) {
        std::cerr << "Error opening parser_test1.fpp" << std::endl;
        assert(false);
    }
    std::string input((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();

    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);
    std::unique_ptr<Program> program = parser.ParseProgram();

    // You can add assertions or comparisons here
        if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Print the AST
    printAST(program.get());

    std::cout << "test_program1 passed" << std::endl;
    return 0;
}

// void test_program2() {
//     std::ifstream file("tests/parser_tests/parser_test2.fpp");
//     if (!file.is_open()) {
//         std::cerr << "Error opening parser_test2.fpp" << std::endl;
//         assert(false);
//     }
//     std::string input((std::istreambuf_iterator<char>(file)),
//                        std::istreambuf_iterator<char>());
//     file.close();

//     Lexer lexer(input);
//     Parser parser(&lexer);
//     std::unique_ptr<Program> program = parser.ParseProgram();

//     assert(program != nullptr);
//     std::cout << "test_program2 passed" << std::endl;
// }

// void test_program3() {
//     std::ifstream file("tests/parser_tests/parser_test3.fpp");
//     if (!file.is_open()) {
//         std::cerr << "Error opening parser_test3.fpp" << std::endl;
//         assert(false);
//     }
//     std::string input((std::istreambuf_iterator<char>(file)),
//                        std::istreambuf_iterator<char>());
//     file.close();

//     Lexer lexer(input);
//     Parser parser(&lexer);
//     std::unique_ptr<Program> program = parser.ParseProgram();

//     assert(program != nullptr);
//     std::cout << "test_program3 passed" << std::endl;
// }
// void test_program4() {
//     std::ifstream file("tests/parser_tests/parser_test4.fpp");
//     if (!file.is_open()) {
//         std::cerr << "Error opening parser_test4.fpp" << std::endl;
//         assert(false);
//     }
//     std::string input((std::istreambuf_iterator<char>(file)),
//                        std::istreambuf_iterator<char>());
//     file.close();

//     Lexer lexer(input);
//     Parser parser(&lexer);
//     std::unique_ptr<Program> program = parser.ParseProgram();

//     assert(program != nullptr);
//     std::cout << "test_program4 passed" << std::endl;
// }

// void test_program5() {
//     std::ifstream file("tests/parser_tests/parser_test5.fpp");
//     if (!file.is_open()) {
//         std::cerr << "Error opening parser_test5.fpp" << std::endl;
//         assert(false);
//     }
//     std::string input((std::istreambuf_iterator<char>(file)),
//                        std::istreambuf_iterator<char>());
//     file.close();

//     Lexer lexer(input);
//     Parser parser(&lexer);
//     std::unique_ptr<Program> program = parser.ParseProgram();

//     assert(program != nullptr);
//     std::cout << "test_program5 passed" << std::endl;
// }

// Main function to run all tests
int main() {
    std::cout << "Running Parser Tests" << std::endl;
    basicDeclarationTest();
    testSimpleDeclaration();
    testMultipleDeclarationsAndAssignments();
    testIfStatement();
    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();
    std::cout << "All parser tests passed!" << std::endl;
    return 0;
}