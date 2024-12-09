#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"
#include "../processor/processor.h"

// Test function declarations
void test_program1();
void test_program2();
void test_program3();
void test_program4();
void test_program5();

// Utility function to run a shell command and capture its output.
static std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) { 
        throw std::runtime_error("popen() failed!"); 
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    // Here you could run multiple tests by looping over test input files if you have more.
    // For demonstration, we do one test: "processor_tests1.fpp"
    
    std::string test_input = "processor_tests1.fpp";
    std::ifstream file(test_input);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << test_input << std::endl;
        return 1;
    }

    std::string program((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();

    // Initialize Lexer with the input program
    Lexer lexer(program);

    // Tokenize the input
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok); // Add the EOF token at the end

    // Parse the tokens into an AST
    Parser parser(tokens);
    parser.parseProgram();

    // Check for parse errors
    std::vector<std::string> errors = parser.Errors();
    for (const std::string &error : errors) {
        std::cerr << "Parse error: " << error << '\n';
    }
    assert(errors.empty()); // We expect no parse errors

    // Get the AST nodes
    std::vector<ASTNode> nodes = parser.nodes;

    // Process the AST to generate a C++ file (test.cpp)
    std::string output_filename = "test.cpp";
    Processor processor(nodes, output_filename);
    processor.process();

    // Compile the generated code
    int ret = system("g++ test.cpp -o test_exe");
    if (ret != 0) {
        std::cerr << "Compilation of test.cpp failed!\n";
        return 1;
    }

    // Run the compiled executable and capture its output
    std::string result = exec("./test_exe");

    // Print the output from the generated program
    std::cout << "Test program output:\n" << result << "\n";

    // Here you can define what you expect the output to be and assert it.
    // For example:
    // std::string expected_output = "Hello, world!\n";
    // assert(result == expected_output);

    std::cout << "Test completed successfully.\n";
    return 0;
}
