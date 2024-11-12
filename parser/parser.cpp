#include "parser.h"

// Constructor
Parser::Parser(std::shared_ptr<Lexer> l) : lexer(l), errors() {
    nextToken();
    nextToken();
}

// Errors function
std::vector<std::string> Parser::Errors() const {
    return errors;
}

// ParseProgram function
std::unique_ptr<Program> Parser::ParseProgram() {
    auto program = std::make_unique<Program>();
    while (!curTokenIs(TokenType::EOF_TOKEN)) {
        auto stmt = parseStatement();
        if (stmt != nullptr) {
            program->statements.push_back(std::move(stmt));
        }
        nextToken();
    }
    return program;
}

// nextToken function
void Parser::nextToken() {
    curToken = peekToken;
    peekToken = lexer->NextToken();
}

// Token checking functions
bool Parser::curTokenIs(TokenType t) const {
    return curToken.type == t;
}

bool Parser::peekTokenIs(TokenType t) const {
    return peekToken.type == t;
}

// expectPeek function
bool Parser::expectPeek(TokenType t) {
    if (peekTokenIs(t)) {
        nextToken();
        return true;
    } else {
        peekError(t);
        return false;
    }
}

// peekError function
void Parser::peekError(TokenType t) {
    std::string msg = "expected next token to be " + TokenTypeToString(t) + ", got " + TokenTypeToString(peekToken.type) + " instead";
    errors.push_back(msg);
}
bool Parser::isVariableDeclaration() const {
    return isType(curToken.type) && peekTokenIs(TokenType::IDENT);
}

bool Parser::isType(TokenType t) const {
    return t == TokenType::INT || t == TokenType::FLOAT || t == TokenType::CHAR ||
           t == TokenType::BOOL || t == TokenType::VARCHAR || t == TokenType::VI;
}

std::unique_ptr<Statement> Parser::parseVariableDeclaration() {
    auto stmt = std::make_unique<VariableDeclaration>();

    // Set the type
    stmt->type = curToken.literal;

    // Expect an identifier
    if (!expectPeek(TokenType::IDENT)) {
        return nullptr;
    }

    stmt->name = curToken.literal;

    // Optional initializer
    if (peekTokenIs(TokenType::ASSIGN)) {
        nextToken(); // Consume ASSIGN token
        nextToken(); // Move to the expression
        stmt->initializer = parseExpression();
    }

    // Expect a semicolon
    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    return stmt;
}


// Implement parseStatement and other parse functions below
std::unique_ptr<Statement> Parser::parseStatement() {
    if (isVariableDeclaration()) {
        return parseVariableDeclaration();
    } else if (isAssignmentStatement()) {
        return parseAssignmentStatement();
    } else if (isExpressionStatement()) {
        return parseExpressionStatement();
    } else if (curTokenIs(TokenType::FOR)) {
        return parseForLoop();
    } else if (curTokenIs(TokenType::WHILE)) {
        return parseWhileLoop();
    } else if (curTokenIs(TokenType::IF)) {
        return parseIfStatement();
    } else if (curTokenIs(TokenType::RETURN)) {
        return parseReturnStatement();
    } else if (curTokenIs(TokenType::LBRACE)) {
        return parseBlock();
    } else {
        // Handle error or skip token
        return nullptr;
    }
}
