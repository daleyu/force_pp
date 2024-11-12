CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17
LEXER_OBJ = lexer.o
TOKEN_OBJ = token.o
LEXER_TESTS_OBJ = lexer_tests.o
# PARSER_TESTS_OBJ = parser_tests.o
EXECUTABLE = main

# Compile token.o
$(TOKEN_OBJ): token/token.cpp token/token.h
	$(CXX) $(CXXFLAGS) -c token/token.cpp -o $(TOKEN_OBJ)

# Compile lexer.o
$(LEXER_OBJ): lexer/lexer.cpp lexer/lexer.h token/token.h
	$(CXX) $(CXXFLAGS) -c lexer/lexer.cpp -o $(LEXER_OBJ)

# Rule to build the lexer_tests object
$(LEXER_TESTS_OBJ): tests/lexer_tests.cpp lexer/lexer.h token/token.h
	$(CXX) $(CXXFLAGS) -c tests/lexer_tests.cpp -o $(LEXER_TESTS_OBJ)

# Rule to build the parser_tests object
# $(PARSER_TESTS_OBJ): tests/parser_tests.cpp token/token.h
# 	$(CXX) $(CXXFLAGS) -c tests/parser_tests.cpp -o $(PARSER_TESTS_OBJ)

# Rule to link the executable
# run_tests: $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ)
# 	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) -o run_tests 
# Rule to link the executable
run_tests: $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(TOKEN_OBJ)
	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(TOKEN_OBJ) -o run_tests

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

main: main.o lexer.o
	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) main.o -o main

# Rule for cleaning up compiled files
clean:
	rm -f $(EXECUTABLE) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) *.o main run_tests

# Default rule
all: $(EXECUTABLE)

.PHONY: clean