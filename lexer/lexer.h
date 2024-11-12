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

    void ReadChar();
    char PeekChar();
    std::string ReadIdentifier();
    std::string ReadNumber();
    void SkipWhitespace();
    bool IsLetter(char ch);
    bool IsDigit(char ch);

public:
    Lexer(const std::string& input);
    Token NextToken();

    Token NewToken(TokenType type, const std::string& literal);
};

#endif // LEXER_H
