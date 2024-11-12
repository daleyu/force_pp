CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17
LEXER_OBJ = lexer.o
TOKEN_OBJ = token.o
LEXER_TESTS_OBJ = lexer_tests.o
PARSER_TESTS_OBJ = parser_tests.o
AST_OBJ = ast/ast.o

EXECUTABLE = main
RUN_TESTS_EXECUTABLE = run_tests

# Compile token.o
$(TOKEN_OBJ): token/token.cpp token/token.h
	$(CXX) $(CXXFLAGS) -c token/token.cpp -o $(TOKEN_OBJ)

# Compile lexer.o
$(LEXER_OBJ): lexer/lexer.cpp lexer/lexer.h token/token.h
	$(CXX) $(CXXFLAGS) -c lexer/lexer.cpp -o $(LEXER_OBJ)

# Compile parser.o
$(PARSER_OBJ): parser/parser.cpp parser/parser.h token/token.h lexer/lexer.h ast/ast.h
	$(CXX) $(CXXFLAGS) -c parser/parser.cpp -o $(PARSER_OBJ)

# build the lexer tests
$(LEXER_TESTS_OBJ): tests/lexer_tests.cpp lexer/lexer.h token/token.h
	$(CXX) $(CXXFLAGS) -c tests/lexer_tests.cpp -o $(LEXER_TESTS_OBJ)

# parser tests
$(PARSER_TESTS_OBJ): tests/parser_tests.cpp parser/parser.h
	$(CXX) $(CXXFLAGS) -c tests/parser_tests.cpp -o $(PARSER_TESTS_OBJ)

# run_tests: $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ)
# 	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) -o run_tests 
# Rule to link the executable
# run_tests: $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(TOKEN_OBJ)
# 	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(TOKEN_OBJ) -o run_tests
run_tests: $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ)
	$(CXX) $(CXXFLAGS) $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) -o $(RUN_TESTS_EXECUTABLE)

# Compile main.o
main.o: main.cpp lexer/lexer.h parser/parser.h token/token.h ast/ast.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

main: main.o $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ)
	$(CXX) $(CXXFLAGS) main.o $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) -o $(MAIN_EXECUTABLE)

# Rule for cleaning up compiled files
clean:
	rm -f $(EXECUTABLE) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) *.o main run_tests

# Default rule
all: $(EXECUTABLE)

.PHONY: clean
