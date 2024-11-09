
#include "lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& input) : input(input), position(0), readPosition(0), ch(0) {
    readChar();
}

void Lexer::readChar() {
    if (readPosition >= (int)input.length()) {
        ch = 0;
    } else {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition++;
}

char Lexer::peekChar() {
    if (readPosition >= (int)input.length()) {
        return 0;
    } else {
        return input[readPosition];
    }
}

std::string Lexer::readIdentifier() {
    int startPosition = position;
    while (isLetter(ch)) {
        readChar();
    }
    return input.substr(startPosition, position - startPosition);
}

std::string Lexer::readNumber() {
    int startPosition = position;
    while (isDigit(ch)) {
        readChar();
    }
    if(isLetter(ch)) return "";
    return input.substr(startPosition, position - startPosition);
}

void Lexer::skipWhitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        readChar();
    }
}

bool Lexer::isLetter(char ch) {
    return std::isalpha(ch) || ch == '_';
}

bool Lexer::isDigit(char ch) {
    return std::isdigit(ch);
}

std::string charToString(char ch) {
    return std::string(1, ch);
}

Token Lexer::newToken(std::string type, const std::string& literal) {
    return Token(type, literal);
}

std::vector<std::string> types = {"int", "vector", "ll", "pair"};
std::vector<std::string> keywords = {"while", "if", "else", "for", "forn"};

// Function to lookup identifiers and keywords
inline std::string LookupIdent(const std::string& ident) {
    for(auto z : types) { 
        if(z == ident) return "TYPE";
    }
    for(auto z : keywords) {
        // std::cout << z << ' ' << ident << '\n';
        if(z == ident) return "KEYWORD";
    }
    return "IDENTIFIER";
}

Token Lexer::nextToken() {
    //create token to begin with with just random value
    Token tok("ILLEGAL", "");
    //we skip all the white space as possible like self loop
    skipWhitespace();
    switch (ch) {
        case '=':
            if (peekChar() == '=') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1, currentCh) + std::string(1, ch);
                tok = newToken("OPERATOR", literal);
            } else {
                tok = newToken("OPERATOR", charToString(ch));
            }
            break;
        case '&':
            if (peekChar() == '&') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1, currentCh) + std::string(1, ch);
                tok = newToken("OPERATOR", literal);
            } else {
                tok = newToken("OPERATOR", charToString(ch));
            }
            break;
        case '|':
            if (peekChar() == '|') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1, currentCh) + std::string(1, ch);
                tok = newToken("OPERATOR", literal);
            } else {
                tok = newToken("OPERATOR", charToString(ch));
            }
            break;
        case '+':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case '-':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case '!':
            if (peekChar() == '=') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1, currentCh) + std::string(1, ch);
                tok = Token{"OPERATOR", literal};
            } else {
                tok = newToken("OPERATOR", charToString(ch));
            }
            break;
        case '/':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case '*':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case '<':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case '>':
            tok = newToken("OPERATOR", charToString(ch));
            break;
        case ';':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case '(':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case ')':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case ',':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case '{':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case '}':
            tok = newToken("SYMBOL", charToString(ch));
            break;
        case 0:
            tok.literal = "";
            tok.type = "EOF";
            break;
        default:
            if (isLetter(ch)) {
                tok.literal = readIdentifier();
                tok.type = LookupIdent(tok.literal);
                return tok;
            } else if (isDigit(ch)) {
                tok.type = "NUMBER";
                tok.literal = readNumber();
                if(tok.literal == "") tok.type = "ILLEGAL";
                return tok;
            } else {
                tok = newToken("ILLEGAL", charToString(ch));
            }
    }

    readChar();
    return tok;
}
