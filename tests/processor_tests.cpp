#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>
#include <chrono>
#include <thread>

#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../processor/processor.h"

// Test function declarations
void run_processor_test(const std::string& input_file);
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


void run_processor_test(const std::string& input_file) {
    std::cout << "\nRunning test: " << input_file << std::endl;
    
    std::string program = readFile(input_file);
    
    Lexer lexer(program);
    std::vector<Token> tokens;
    Token tok = lexer.NextToken();
    while (tok.type != TokenType::EOF_TOKEN) {
        tokens.push_back(tok);
        tok = lexer.NextToken();
    }
    tokens.push_back(tok);

    Parser parser(tokens);
    parser.parseProgram();

    std::vector<std::string> errors = parser.Errors();
    for (const std::string &error : errors) {
        std::cerr << "Parse error: " << error << '\n';
    }
    if (errors.size() > 0) {
        throw std::runtime_error("Parser errors encountered.");
    }
    assert(errors.empty());

    std::string output_filename = input_file.substr(0, input_file.find_last_of('.')) + ".cpp";
    Processor processor(parser.nodes, output_filename);
    processor.process();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::string exe_name = input_file.substr(0, input_file.find_last_of('.')) + "_exe";


    // std::string compile_cmd = "g++ -Wall -std=c++17 " + output_filename + " -o " + 
    //                         "test_exe";
    
    // std::cout << "\nExecuting compilation command: " << compile_cmd << std::endl;
    
    // int compile_result = system(compile_cmd.c_str());
    // if (compile_result != 0) {
    //     throw std::runtime_error("Compilation failed for: " + output_filename +
    //                             "\nCommand used: " + compile_cmd);
    // }

    // std::string result = exec(("./" + input_file.substr(0, input_file.find_last_of('.')) + "_exe").c_str());
    // std::cout << "Test output:\n" << result;

    // std::string expected_output = "Hello, world!\n";
    // assert(result == expected_output);
}
void test_program1() {
    run_processor_test("tests/processor_tests/processor_test1.fpp");
    std::cout << "Processor Test 1 completed successfully.\n";
}

void test_program2() {
    run_processor_test("tests/processor_tests/processor_test2.fpp");
    std::cout << "Processor Test 2 completed successfully.\n";
}

void test_program3() {
    run_processor_test("tests/processor_tests/processor_test3.fpp");
    std::cout << "Processor Test 3 completed successfully.\n";
}

void test_program4() {
    run_processor_test("tests/processor_tests/processor_test4.fpp");
    std::cout << "Processor Test 4 completed successfully.\n";
}

void test_program5() {
    run_processor_test("tests/processor_tests/processor_test5.fpp");
    std::cout << "Processor Test 5 completed successfully.\n";
}

int main() {
    std::cout << "Running Processor tests..." << std::endl;

    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();

    std::cout << "All Processor tests pased!" << std::endl;
    return 0;
}