#include "repl.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include <iostream>
#include <string>
#include <unordered_map>

namespace repl {

const std::string PROM_PROMPT = ">> ";

// Helper function to convert TokenType to string for display
std::string TokenTypeToString(token::TokenType type) {
    static std::unordered_map<token::TokenType, std::string> tokenTypeStrings = {
        {token::TokenType::ILLEGAL, "ILLEGAL"},
        {token::TokenType::EOF_T, "EOF"},
        {token::TokenType::IDENTIFIER, "IDENTIFIER"},
        {token::TokenType::NUMBER, "NUMBER"},
        {token::TokenType::ASSIGN, "ASSIGN"},
        {token::TokenType::PLUS, "PLUS"},
        {token::TokenType::MINUS, "MINUS"},
        {token::TokenType::ASTERISK, "ASTERISK"},
        {token::TokenType::SLASH, "SLASH"},
        {token::TokenType::EQUAL, "EQUAL"},
        {token::TokenType::SEMICOLON, "SEMICOLON"},
        {token::TokenType::COMMA, "COMMA"},
        {token::TokenType::LPAREN, "LPAREN"},
        {token::TokenType::RPAREN, "RPAREN"},
        {token::TokenType::LBRACE, "LBRACE"},
        {token::TokenType::RBRACE, "RBRACE"},
        {token::TokenType::WHILE, "WHILE"},
        {token::TokenType::IF, "IF"},
        {token::TokenType::ELSE, "ELSE"},
        {token::TokenType::FOR, "FOR"},
        {token::TokenType::FORN, "FORN"},
        {token::TokenType::INT, "INT"},
        {token::TokenType::VECTOR, "VECTOR"},
        {token::TokenType::LL, "LL"},
        {token::TokenType::PAIR, "PAIR"},
        // Add any additional TokenType mappings here
    };

    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end()) {
        return it->second;
    } else {
        return "UNKNOWN";
    }
}

void Start(std::istream& in, std::ostream& out) {
    std::string line;
    while (true) {
        out << PROMPT << std::flush;
        if (!std::getline(in, line)) {
            break;  // EOF or error
        }
        Lexer lexer(line);
        token::Token tok;

        do {
            tok = lexer.nextToken();
            if (tok.type != token::TokenType::EOF_T) {
                out << "Token Type: " << TokenTypeTo(tok.type)
                    << ", Literal: \"" << tok.literal << "\"" << std::endl;
            }
        } while (tok.type != token::TokenType::EOF_T && tok.type != token::TokenType::ILLEGAL);

        if (tok.type == token::TokenType::ILLEGAL) {
            out << "Encountered an illegal token. Exiting REPL." << std::endl;
            break;
        }
    }
}

}  // namespace repl
