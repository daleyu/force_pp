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
    Parser(std::vector<Token>);
    std::vector<std::string> errors;
    std::vector<std::string> Errors() const{
        return errors;
    }
    int createNode();
    int idx;
    std::vector<Token> tokens;
    std::vector<ASTNode> nodes;

    void printNodes();

    void parseProgram();
    int parseFunction();
    int parseArguments();

    Token curToken();
    bool readToken(TokenType);
    bool readTokenType();
    bool isTokenType();

//     std::shared_ptr<Lexer> lexer;
//     Token curToken;
//     Token peekToken;
//     std::vector<std::string> errors;

// Token-related methods
    void nextToken();
    bool curTokenIs(TokenType t);
    bool peekTokenIs(TokenType t);
    bool expectPeek(TokenType t);
    void peekError(TokenType t);
//     void peekError(TokenType t);
//     bool peekTokenIs(TokenType t) const;
//     bool expectPeek(TokenType t);

    // Helper methods
    bool isType(TokenType t) const;
    bool isExpressionStatement();
    bool isAssignmentStatement();
    int getPrecedence(TokenType type);
    bool isBinaryOperator(TokenType type);
    bool isBooleanOperator(TokenType type);
//     int peekPrecedence() const;
//     int curPrecedence() const;
//     bool isAssignmentStatement() const;
//     bool isExpressionStatement() const;

    // Parsing methods
    int parseStatement();
    int parseAssignmentStatement();
    int parseVariableDeclaration();
    int parseVariableDeclarationList();
    int parseForLoop();
    int parseWhileLoop();
    int parseIfStatement();
    int parseReturnStatement();
    int parseExpression(int precedence = 0);
    int parseExpressionStatement();
    int parseBlock();

//     std::unique_ptr<Statement> parseAssignmentStatement();
//     std::unique_ptr<Statement> parseExpressionStatement();
//     std::unique_ptr<Statement> parseForLoop();
//     std::unique_ptr<Statement> parseWhileLoop();
//     std::unique_ptr<Statement> parseIfStatement();
//     std::unique_ptr<Statement> parseReturnStatement();
//     std::unique_ptr<Expression> parseExpression(int precedence = 0);
//     std::vector<std::unique_ptr<Expression> > parseExpressionList(TokenType end);
    

//     // Prefix parsing functions
//     std::unique_ptr<Expression> parseIdentifier();
//     std::unique_ptr<Expression> parseLiteral();
//     std::unique_ptr<Expression> parseIntegerLiteral();
//     std::unique_ptr<Expression> parseBooleanLiteral();
//     std::unique_ptr<Expression> parseGroupedExpression();
//     std::unique_ptr<Expression> parsePrefixExpression();
//     std::unique_ptr<Expression> parseFunctionCall(std::unique_ptr<Expression> function);

//     // Infix parsing functions
//     std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> left);

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
