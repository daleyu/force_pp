CXX = g++
CXXFLAGS = -Wall  -std=c++17

# Object files
LEXER_OBJ = lexer.o
TOKEN_OBJ = token.o
LEXER_TESTS_OBJ = lexer_tests.o
PARSER_TESTS_OBJ = parser_tests.o
PARSER_OBJ = parser.o
AST_OBJ = ast/ast.o
PROCESSOR_OBJ = processor.o

MAIN_EXECUTABLE = main
LEXER_TEST_EXECUTABLE = lexer_test
PARSER_TEST_EXECUTABLE = parser_test

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

# Build lexer test separately
lexer_test: $(TOKEN_OBJ) $(LEXER_OBJ) $(LEXER_TESTS_OBJ)
	$(CXX) $(CXXFLAGS) $(TOKEN_OBJ) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) -o $(LEXER_TEST_EXECUTABLE)

# Build parser test executable
parser_test: $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(PARSER_TESTS_OBJ)
	$(CXX) $(CXXFLAGS) $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(PARSER_TESTS_OBJ) -o $(PARSER_TEST_EXECUTABLE)

# Compile processor.o
$(PROCESSOR_OBJ): processor/processor.cpp processor/processor.h
	$(CXX) $(CXXFLAGS) -c processor/processor.cpp -o $(PROCESSOR_OBJ)
	
# Compile main.o
main.o: main.cpp lexer/lexer.h parser/parser.h token/token.h ast/ast.h processor/processor.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Build main executable
main: main.o $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(PROCESSOR_OBJ)
	$(CXX) $(CXXFLAGS) main.o $(TOKEN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(PROCESSOR_OBJ) -o $(MAIN_EXECUTABLE)

tests: lexer_test parser_test

clean:
	rm -f $(MAIN_EXECUTABLE) $(LEXER_TEST_EXECUTABLE) $(PARSER_TEST_EXECUTABLE) \
		$(LEXER_OBJ) $(LEXER_TESTS_OBJ) $(PARSER_TESTS_OBJ) $(TOKEN_OBJ) \
		$(PARSER_OBJ) $(AST_OBJ) *.o

all: main tests

.PHONY: clean all tests lexer_test parser_test
