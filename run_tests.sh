#!/bin/bash

make tests

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."
    echo "----------------------------------------"
    ./lexer_test
    echo "----------------------------------------"
    echo "Lexer Tests Completed. Running tests..."
    ./parser_test
    echo "----------------------------------------"
else
    echo "Compilation failed."
fi
