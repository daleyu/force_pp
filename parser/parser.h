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
    std::vector<std::string> Errors() const;
    int createNode();
    int idx;
    std::vector<Token> tokens;
    std::vector<ASTNode> nodes;

    void printNodes();
    void dfs(int, int);

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

//     // Token-related methods
//     void peekError(TokenType t);
    void nextToken();
    bool curTokenIs(TokenType t);
//     bool peekTokenIs(TokenType t) const;
//     bool expectPeek(TokenType t);

//     // Helper methods
    bool isType(TokenType t) const;
//     int peekPrecedence() const;
//     int curPrecedence() const;
    bool isAssignmentStatement();
    bool isExpressionStatement();

//     // Parsing methods
        int parseStatement();
        int parseVariableDeclaration();
    int parseAssignmentStatement();
    int parseExpressionStatement();
    int parseForLoop();
    int parseWhileLoop();
    int parseIfStatement();
    int parseReturnStatement();
        int parseBlock();
    int parseExpression(int precedence = 0);
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

//     // Precedence levels
//     enum Precedence {
//         LOWEST,
//         OR,           // ||
//         AND,          // &&
//         EQUALS,       // == or !=
//         LESSGREATER,  // > or <
//         SUM,          // + or -
//         PRODUCT,      // * or /
//         PREFIX,       // -X or !X
//         CALL          // function calls
//     };

//     // Maps for operator precedences
//     std::unordered_map<TokenType, Precedence> precedences;
};

#endif // PARSER_H
