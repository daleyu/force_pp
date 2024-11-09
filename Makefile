CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17
LEXER_OBJ = lexer.o
LEXER_TESTS_OBJ = lexer_tests.o
EXECUTABLE = main

# Rule to build the lexer object
$(LEXER_OBJ): lexer/lexer.cpp  
	$(CXX) $(CXXFLAGS) -c lexer/lexer.cpp -o $(LEXER_OBJ)

# Rule to build the lexer_tests object
$(LEXER_TESTS_OBJ): tests/lexer_tests.cpp token/token.h 
	$(CXX) $(CXXFLAGS) -c tests/lexer_tests.cpp -o $(LEXER_TESTS_OBJ)

# Rule to link the executable
run_tests: $(LEXER_OBJ) $(LEXER_TESTS_OBJ)
	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) -o run_tests 

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

main: main.o lexer.o
	$(CXX) $(CXXFLAGS) $(LEXER_OBJ) main.o -o main



# Rule for cleaning up compiled files
clean:
	rm -f $(EXECUTABLE) $(LEXER_OBJ) $(LEXER_TESTS_OBJ) *.o main run_tests

# Default rule
all: $(EXECUTABLE)

.PHONY: clean
