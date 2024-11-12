// token.cpp

#include "token.h"


std::string TokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::ILLEGAL: return "ILLEGAL";
        case TokenType::EOF_TOKEN: return "EOF";
        case TokenType::IDENT: return "IDENT";
        case TokenType::INT_LITERAL: return "INT_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
        case TokenType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::BANG: return "BANG";
        case TokenType::ASTERISK: return "ASTERISK";
        case TokenType::SLASH: return "SLASH";
        case TokenType::LT: return "LT";
        case TokenType::GT: return "GT";
        case TokenType::EQ: return "EQ";
        case TokenType::NOT_EQ: return "NOT_EQ";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::COMMA: return "COMMA";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COLON: return "COLON";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::LBRACE: return "LBRACE";
        case TokenType::RBRACE: return "RBRACE";
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::LET: return "LET";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::RETURN: return "RETURN";
        case TokenType::INT: return "INT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::CHAR: return "CHAR";
        case TokenType::BOOL: return "BOOL";
        case TokenType::VARCHAR: return "VARCHAR";
        case TokenType::VI: return "VI";
        case TokenType::FOR: return "FOR";
        case TokenType::WHILE: return "WHILE";
        // Add cases for any other TokenType enums you've added
        default: return "UNKNOWN";
    }
}