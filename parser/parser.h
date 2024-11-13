// parser.h

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

    // Token methods for interacting with lexer and tokens
    void peekError(TokenType t);
    void nextToken();
    bool curTokenIs(TokenType t) const;
    bool peekTokenIs(TokenType t) const;
    bool expectPeek(TokenType t);

    // Helper methods needed for parsing prefix and infix expressions
    bool isType(TokenType t) const;
    int peekPrecedence() const;
    int curPrecedence() const;
    bool isAssignmentStatement() const;
    bool isExpressionStatement() const;

    // Parsing methods
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseVariableDeclaration(const std::string& typeName, const std::string& ident);
    std::unique_ptr<Statement> parseAssignmentStatement();
    std::unique_ptr<Statement> parseExpressionStatement();
    std::unique_ptr<Statement> parseFunctionDefinition(const std::string& typeName, const std::string& ident);
    std::vector<std::unique_ptr<Parameter> > parseParameterList(); 
std::unique_ptr<Parameter> parseParameter();
    std::unique_ptr<Statement> parseForLoop();
    std::unique_ptr<Statement> parseForNLoop();
    std::unique_ptr<Statement> parseWhileLoop();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<Block> parseBlock();
    std::unique_ptr<Expression> parseExpression(int precedence = 0);
    std::vector<std::unique_ptr<Expression> > parseExpressionList(TokenType end);
    

    // Prefix parsing functions
    std::unique_ptr<Expression> parseIdentifier();
    std::unique_ptr<Expression> parseLiteral();
    std::unique_ptr<Expression> parseIntegerLiteral();
    std::unique_ptr<Expression> parseBooleanLiteral();
    std::unique_ptr<Expression> parseGroupedExpression();
    std::unique_ptr<Expression> parsePrefixExpression();
    std::unique_ptr<Expression> parseFunctionCall(std::unique_ptr<Expression> function);

    // Infix parsing functions
    std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> left);

    // Precedence levels
    enum Precedence {
        LOWEST,
        OR,           // ||
        AND,          // &&
        EQUALS,       // == or !=
        LESSGREATER,  // > or <
        SUM,          // + or -
        PRODUCT,      // * or /
        PREFIX,       // -X or !X
        CALL          // function calls
    };

    // Maps for operator precedences
    std::unordered_map<TokenType, Precedence> precedences;
};

#endif // PARSER_H
