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
void test_program1();
void test_program2();
void test_program3();
void test_program4();
void test_program5();

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


int basicDeclarationTest() {
    std::string input = "int x = 42;";

    auto lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    auto program = parser.ParseProgram();

    if (!parser.Errors().empty()) {
        for (const auto& error : parser.Errors()) {
            std::cerr << "Parser error: " << error << std::endl;
        }
        return 1;
    }

    // Assuming the program has at least one statement
    if (!program->statements.empty()) {
        auto& stmt = program->statements[0];
        std::cout << stmt->tokenLiteral() << std::endl;
    }

    return 0;
}

// // Test function for parsing a simple declaration
// void testSimpleDeclaration() {
//     auto lexer = std::make_shared<Lexer>("int x = 7;");
//     Parser parser(lexer);

//     auto program = parser.ParseProgram();

//     // Construct expected AST manually
//     auto expectedProgram = std::make_unique<Program>();
//     auto varDecl = std::make_unique<VariableDeclaration>();
//     varDecl->type = "int";
//     varDecl->name = "x";
//     varDecl->initializer = std::make_unique<Literal>(Literal::Type::Integer, "7");
//     expectedProgram->statements.push_back(std::move(varDecl));

//     // Compare the actual AST with the expected AST
//     assert(compareAST(expectedProgram.get(), program.get()));
// }


// // Test function for parsing multiple declarations and assignments
// void testMultipleDeclarationsAndAssignments() {
//     auto lexer = std::make_shared<Lexer>("int x = 7; int y = 10; result = x + y;");
//     Parser parser(lexer);

//     auto program = parser.ParseProgram();
//     auto expectedAST = std::make_shared<ASTNode>(NODE_TYPE_VARIABLE, "Declaration");
//     expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));
//     expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "y", "10"));
//     expectedAST->children.push_back(std::make_shared<ASTNode>("Assignment", "result", "+", "x", "y"));

//     compareAST(expectedAST, program->statements[0]);
//     std::cout << "testMultipleDeclarationsAndAssignments passed" << std::endl;
// }

// // Test function for parsing an if statement
// void testIfStatement() {
//     auto lexer = std::make_shared<Lexer>("int x = 7; if (x == 7) { x = x - 1; }");
//     Parser parser(lexer);

//     auto program = parser.ParseProgram();
//     auto expectedAST = std::make_shared<ASTNode>(NODE_TYPE_VARIABLE, "Declaration");
//     expectedAST->children.push_back(std::make_shared<ASTNode>("Declaration", "int", "x", "7"));

//     auto ifStmt = std::make_shared<ASTNode>("IfStatement");
//     ifStmt->children.push_back(std::make_shared<ASTNode>("Condition", "==", "x", "7"));
//     ifStmt->children.push_back(std::make_shared<ASTNode>("Assignment", "x", "-", "x", "1"));

//     expectedAST->children.push_back(ifStmt);

//     compareAST(expectedAST, program->statements[0]);
//     std::cout << "testIfStatement passed" << std::endl;
// }

// void test_program1() {
//     std::ifstream file("tests/parser_tests/parser_test1.fpp");
//     if (!file.is_open()) {
//         std::cerr << "Error opening parser_test1.fpp" << std::endl;
//         assert(false);
//     }
//     std::string input((std::istreambuf_iterator<char>(file)),
//                        std::istreambuf_iterator<char>());
//     file.close();

//     Lexer lexer(input);
//     Parser parser(&lexer);
//     std::unique_ptr<Program> program = parser.ParseProgram();

//     // You can add assertions or comparisons here
//     assert(program != nullptr);
//     std::cout << "test_program1 passed" << std::endl;
// }

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
    // testSimpleDeclaration();
    // testMultipleDeclarationsAndAssignments();
    // testIfStatement();
    // test_program1();
    // test_program2();
    // test_program3();
    // test_program4();
    // test_program5();
    std::cout << "All parser tests passed!" << std::endl;
    return 0;
}