#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>
#include "../token/token.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

class Parser {
public:
    Parser(std::shared_ptr<Lexer> l);
    std::vector<std::string> Errors() const;
    std::unique_ptr<Program> ParseProgram();

private:
    std::shared_ptr<Lexer> lexer;
    Token curToken;
    Token peekToken;
    std::vector<std::string> errors;

    void peekError(TokenType t);
    void nextToken();
    bool curTokenIs(TokenType t) const;
    bool peekTokenIs(TokenType t) const;
    bool expectPeek(TokenType t);
    std::unique_ptr<Statement> parseLetStatement();
    std::unique_ptr<Statement> parseStatement();
};

#endif // PARSER_H