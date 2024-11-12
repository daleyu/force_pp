#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <unordered_map>
#include <vector>

enum class TokenType {
    ILLEGAL,
    EOF_TOKEN,

    // Identifiers + literals
    IDENT,      // food
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    BOOLEAN_LITERAL,

    // Operators
    ASSIGN,
    PLUS,
    MINUS,
    BANG,
    ASTERISK,
    SLASH,

    LT,
    GT,
    LTE,
    GTE,
    AND,
    OR,
    NOT_EQ,
    EQ,

    // Delimiters
    COMMA,
    SEMICOLON,
    COLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,

    // Keywords
    FUNCTION,
    LET,
    TRUE,
    FALSE,
    IF,
    ELSE,
    RETURN,
    INT,
    FLOAT,
    CHAR,
    BOOL,
    VARCHAR,
    VI,
    FOR,
    WHILE,
    FORN,
    VOID,
};

std::string TokenTypeToString(TokenType type);

class Token {
public:
    TokenType type;
    std::string literal;

    Token(TokenType type, const std::string& literal) : type(type), literal(literal) {}
};

#endif // TOKEN_H
