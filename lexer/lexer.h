#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "../token/token.h" 

class Lexer {
private:
    std::string input;
    int position;     // current position in input (points to current char)
    int readPosition; // current reading position in input (after current char)
    char ch;          // current char under examination

    void readChar();
    char peekChar();
    std::string readIdentifier();
    std::string readNumber();
    void skipWhitespace();
    bool isLetter(char ch);
    bool isDigit(char ch);

public:
    Lexer(const std::string& input);
    Token nextToken();

    static Token newToken(std::string type, const std::string& literal);
};

#endif // LEXER_H
