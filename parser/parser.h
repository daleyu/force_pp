#ifndef PARSER_H
#define PARSER_H

// Include necessary libraries
#include <stdbool.h>

// Define any constants
#define MAX_TOKEN_LENGTH 100

// Enum to represent different token types
typedef enum {
    TOKEN_TYPE_UNKNOWN,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_END
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

// Function declarations

/**
 * Initializes the parser.
 * This could involve setting up necessary state or buffers.
 */
void parser_init();

/**
 * Takes input from a string or file and processes it.
 * @param input The input string to be parsed.
 * @return True on success, false on failure.
 */
bool parse_input(const char* input);

/**
 * Gets the next token from the input.
 * @param token Pointer to a Token structure where the next token will be stored.
 * @return True if a token was successfully retrieved, false if the end of input is reached.
 */
bool get_next_token(Token* token);

/**
 * Cleans up any resources used by the parser.
 */
void parser_cleanup();

#endif // PARSER_H
