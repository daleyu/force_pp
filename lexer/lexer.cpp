// lexer.cpp

#include "lexer.h"
#include <cctype>
#include <unordered_map>

// Define keywords map
std::unordered_map<std::string, TokenType> keywords = {
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"char", TokenType::CHAR},
    {"bool", TokenType::BOOL},
    {"varchar", TokenType::VARCHAR},
    {"vi", TokenType::VI},
    {"void", TokenType::VOID},
    {"for", TokenType::FOR},
    {"forn", TokenType::FOR},
    {"while", TokenType::WHILE},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"return", TokenType::RETURN},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    // Add other keywords as necessary
};

// Function to lookup identifiers and keywords
TokenType LookupIdent(const std::string& ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) {
        return it->second;
    }
    return TokenType::IDENT;
}

Lexer::Lexer(const std::string& input)
    : input(input), position(0), readPosition(0), ch(0) {
    ReadChar();
}

void Lexer::ReadChar() {
    if (readPosition >= (int)input.size()) {
        ch = 0;
    } else {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition++;
}

char Lexer::PeekChar() {
    if (readPosition >= (int)input.size()) {
        return 0;
    } else {
        return input[readPosition];
    }
}

void Lexer::SkipWhitespace() {
    while (std::isspace(ch)) {
        ReadChar();
    }
}

bool Lexer::IsLetter(char ch) {
    return std::isalpha(ch) || ch == '_';
}

bool Lexer::IsDigit(char ch) {
    return std::isdigit(ch);
}

std::string Lexer::ReadIdentifier() {
    size_t startPosition = position;
    while (IsLetter(ch) || IsDigit(ch)) {
        ReadChar();
    }
    return input.substr(startPosition, position - startPosition);
}

std::string Lexer::ReadNumber() {
    size_t startPosition = position;
    while (IsDigit(ch)) {
        ReadChar();
    }
    if (ch == '.') {
        ReadChar(); // Consume '.'
        while (IsDigit(ch)) {
            ReadChar();
        }
    }
    return input.substr(startPosition, position - startPosition);
}

Token Lexer::NewToken(TokenType type, const std::string& literal) {
    return Token(type, literal);
}

Token Lexer::NextToken() {
    Token tok(TokenType::ILLEGAL, "");

    SkipWhitespace();

    switch (ch) {
        case '=':
            if (PeekChar() == '=') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::EQ, literal);
            } else {
                tok = NewToken(TokenType::ASSIGN, std::string(1, ch));
            }
            break;
        case '+':
            tok = NewToken(TokenType::PLUS, std::string(1, ch));
            break;
        case '-':
            tok = NewToken(TokenType::MINUS, std::string(1, ch));
            break;
        case '!':
            if (PeekChar() == '=') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::NOT_EQ, literal);
            } else {
                tok = NewToken(TokenType::BANG, std::string(1, ch));
            }
            break;
        case '/':
            tok = NewToken(TokenType::SLASH, std::string(1, ch));
            break;
        case '*':
            tok = NewToken(TokenType::ASTERISK, std::string(1, ch));
            break;
        case '<':
            if (PeekChar() == '=') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::LTE, literal);
            } else {
                tok = NewToken(TokenType::LT, std::string(1, ch));
            }
            break;
        case '>':
            if (PeekChar() == '=') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::GTE, literal);
            } else {
                tok = NewToken(TokenType::GT, std::string(1, ch));
            }
            break;
        case '&':
            if (PeekChar() == '&') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::AND, literal);
            } else {
                tok = NewToken(TokenType::ILLEGAL, std::string(1, ch));
            }
            break;
        case '|':
            if (PeekChar() == '|') {
                char currentCh = ch;
                ReadChar();
                std::string literal = std::string(1, currentCh) + ch;
                tok = NewToken(TokenType::OR, literal);
            } else {
                tok = NewToken(TokenType::ILLEGAL, std::string(1, ch));
            }
            break;
        case ';':
            tok = NewToken(TokenType::SEMICOLON, std::string(1, ch));
            break;
        case ',':
            tok = NewToken(TokenType::COMMA, std::string(1, ch));
            break;
        case ':':
            tok = NewToken(TokenType::COLON, std::string(1, ch));
            break;
        case '(':
            tok = NewToken(TokenType::LPAREN, std::string(1, ch));
            break;
        case ')':
            tok = NewToken(TokenType::RPAREN, std::string(1, ch));
            break;
        case '{':
            tok = NewToken(TokenType::LBRACE, std::string(1, ch));
            break;
        case '}':
            tok = NewToken(TokenType::RBRACE, std::string(1, ch));
            break;
        case '[':
            tok = NewToken(TokenType::LBRACKET, std::string(1, ch));
            break;
        case ']':
            tok = NewToken(TokenType::RBRACKET, std::string(1, ch));
            break;
        case 0:
            tok.type = TokenType::EOF_TOKEN;
            tok.literal = "";
            break;
        default:
            if (IsLetter(ch)) {
                std::string ident = ReadIdentifier();
                TokenType type = LookupIdent(ident);
                tok = Token(type, ident);
                return tok;  // Early return
            } else if (IsDigit(ch)) {
                std::string number = ReadNumber();
                if (number.find('.') != std::string::npos) {
                    tok = Token(TokenType::FLOAT_LITERAL, number);
                } else {
                    tok = Token(TokenType::INT_LITERAL, number);
                }
                return tok;  // Early return
            } else {
                tok = NewToken(TokenType::ILLEGAL, std::string(1, ch));
            }
            break;
    }

    ReadChar();
    return tok;
}
