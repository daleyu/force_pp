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
    std::unique_ptr<Statement> parseStatement();
    // Add declarations for other parse functions
    std::unique_ptr<Statement> parseVariableDeclaration();
    std::unique_ptr<Statement> parseAssignmentStatement();
    std::unique_ptr<Statement> parseExpressionStatement();
    std::unique_ptr<Statement> parseForLoop();
    std::unique_ptr<Statement> parseWhileLoop();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<Block> parseBlock();
    std::unique_ptr<Expression> parseExpression(int precedence = 0);
    // ... Add more as needed
};

#endif // PARSER_H
