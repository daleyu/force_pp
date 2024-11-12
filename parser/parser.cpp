// parser.cpp

#include "parser.h"
#include <unordered_map>
#include <iostream>

// Constructor
Parser::Parser(std::shared_ptr<Lexer> l)
    : lexer(l), curToken(TokenType::ILLEGAL, ""), peekToken(TokenType::ILLEGAL, ""), errors() 
{

    
    // we need to have this table to know what order to do different operators
    // We need this for the recursive descent parsing
    precedences = {
        {TokenType::EQ, Precedence::EQUALS},
        {TokenType::NOT_EQ, Precedence::EQUALS},
        {TokenType::LT, Precedence::LESSGREATER},
        {TokenType::GT, Precedence::LESSGREATER},
        {TokenType::LTE, Precedence::LESSGREATER},
        {TokenType::GTE, Precedence::LESSGREATER},
        {TokenType::PLUS, Precedence::SUM},
        {TokenType::MINUS, Precedence::SUM},
        {TokenType::SLASH, Precedence::PRODUCT},
        {TokenType::ASTERISK, Precedence::PRODUCT},
        {TokenType::AND, Precedence::AND},
        {TokenType::OR, Precedence::OR},
        {TokenType::LPAREN, Precedence::CALL}
    };
    peekToken = lexer->NextToken(); 
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

// Token functions
void Parser::nextToken() {
    curToken = peekToken;
    peekToken = lexer->NextToken();
    // std::cout << "curToken: " << TokenTypeToString(curToken.type) << " (" << curToken.literal << ")\n";
    // std::cout << "peekToken: " << TokenTypeToString(peekToken.type) << " (" << peekToken.literal << ")\n";
}

bool Parser::curTokenIs(TokenType t) const {
    return curToken.type == t;
}

bool Parser::peekTokenIs(TokenType t) const {
    return peekToken.type == t;
}

bool Parser::expectPeek(TokenType t) {
    if (peekTokenIs(t)) {
        nextToken();
        return true;
    } else {
        peekError(t);
        return false;
    }
}

void Parser::peekError(TokenType t) {
    std::string msg = "Unexpected Token Error: Expected" + TokenTypeToString(t) + ", got " + TokenTypeToString(peekToken.type) + " instead";
    errors.push_back(msg);
}

// Helper methods
bool Parser::isType(TokenType t) const {
    return t == TokenType::INT || t == TokenType::FLOAT || t == TokenType::CHAR ||
           t == TokenType::BOOL || t == TokenType::VARCHAR || t == TokenType::VI || t == TokenType::VOID;
}

int Parser::peekPrecedence() const {
    auto it = precedences.find(peekToken.type);
    if (it != precedences.end()) {
        return it->second;
    }
    return Precedence::LOWEST;
}

int Parser::curPrecedence() const {
    auto it = precedences.find(curToken.type);
    if (it != precedences.end()) {
        return it->second;
    }
    return Precedence::LOWEST;
}

bool Parser::isAssignmentStatement() const {
    return curTokenIs(TokenType::IDENT) && peekTokenIs(TokenType::ASSIGN);
}

bool Parser::isExpressionStatement() const {
    // For simplicity, treat any expression starting with an identifier or literal as an expression statement
    return curTokenIs(TokenType::IDENT) || curTokenIs(TokenType::INT_LITERAL) || curTokenIs(TokenType::FLOAT_LITERAL) ||
           curTokenIs(TokenType::STRING_LITERAL) || curTokenIs(TokenType::CHAR_LITERAL) || curTokenIs(TokenType::BOOLEAN_LITERAL);
}

// Parsing methods
std::unique_ptr<Statement> Parser::parseStatement() {
    if (isType(curToken.type) && peekTokenIs(TokenType::IDENT)) {
        return parseVariableDeclaration();
    } else if (isAssignmentStatement()) {
        return parseAssignmentStatement();
    } else if (curTokenIs(TokenType::RETURN)) {
        return parseReturnStatement();
    } else if (curTokenIs(TokenType::FOR)) {
        return parseForLoop();
    } else if (curTokenIs(TokenType::FORN)) {
        return parseForNLoop();
    } else if (curTokenIs(TokenType::WHILE)) {
        return parseWhileLoop();
    } else if (curTokenIs(TokenType::IF)) {
        return parseIfStatement();
    } else if (curTokenIs(TokenType::LBRACE)) {
        return parseBlock();
    } else if (isExpressionStatement()) {
        return parseExpressionStatement();
    } else {
        // Handle error or skip token
        nextToken();
        return nullptr;
    }
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

std::unique_ptr<Statement> Parser::parseAssignmentStatement() {
    auto stmt = std::make_unique<AssignmentStatement>();

    stmt->name = curToken.literal;

    // Expect '='
    if (!expectPeek(TokenType::ASSIGN)) {
        return nullptr;
    }

    nextToken(); // Move to the expression

    stmt->value = parseExpression();

    // Expect a semicolon
    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseExpressionStatement() {
    auto stmt = std::make_unique<ExpressionStatement>();

    stmt->expression = parseExpression();

    // Expect a semicolon
    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
    auto stmt = std::make_unique<ReturnStatement>();

    nextToken(); // Move to the expression

    stmt->returnValue = parseExpression();

    // Expect a semicolon
    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    return stmt;
}

std::unique_ptr<Block> Parser::parseBlock() {
    auto block = std::make_unique<Block>();

    nextToken(); // Consume '{'

    while (!curTokenIs(TokenType::RBRACE) && !curTokenIs(TokenType::EOF_TOKEN)) {
        auto stmt = parseStatement();
        if (stmt != nullptr) {
            block->statements.push_back(std::move(stmt));
        }
        nextToken();
    }

    return block;
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    auto stmt = std::make_unique<IfStatement>();

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    nextToken(); // Move to the condition

    stmt->condition = parseExpression();

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    stmt->consequence = parseBlock();

    if (peekTokenIs(TokenType::ELSE)) {
        nextToken(); // Consume 'else'

        if (!expectPeek(TokenType::LBRACE)) {
            return nullptr;
        }

        stmt->alternative = parseBlock();
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseWhileLoop() {
    auto stmt = std::make_unique<WhileLoop>();

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    nextToken(); // Move to the condition

    stmt->condition = parseExpression();

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    stmt->body = parseBlock();

    return stmt;
}
std::unique_ptr<Statement> Parser::parseForNLoop() {
    auto stmt = std::make_unique<ForNLoop>();

    // Expect and consume '('
    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    // Parse iterator name
    nextToken();
    if (!curTokenIs(TokenType::IDENT)) {
        return nullptr;
    }
    stmt->iterator = curToken.literal;

    // Expect and consume ','
    if (!expectPeek(TokenType::COMMA)) {
        return nullptr;
    }

    // Parse end expression
    nextToken();
    stmt->end = parseExpression();
    if (!stmt->end) {
        return nullptr;
    }

    // Expect and consume ')'
    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    // Expect and consume '{'
    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    // Parse loop body
    stmt->body = std::unique_ptr<Block>(dynamic_cast<Block*>(parseBlock().release()));
    if (!stmt->body) {
        return nullptr;
    }

    return stmt;
}


std::unique_ptr<Statement> Parser::parseForLoop() {
    // Simplified for loop parsing
    auto stmt = std::make_unique<ForLoop>();

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    nextToken(); // Move to the initializer

    // Parse initializer
    if (isType(curToken.type) && peekTokenIs(TokenType::IDENT)) {
        stmt->initializer = parseVariableDeclaration();
    } else if (curTokenIs(TokenType::SEMICOLON)) {
        stmt->initializer = nullptr;
    } else {
        stmt->initializer = parseExpressionStatement();
    }

    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    nextToken(); // Move to the condition

    // Parse condition
    if (!curTokenIs(TokenType::SEMICOLON)) {
        stmt->condition = parseExpression();
    }

    if (!expectPeek(TokenType::SEMICOLON)) {
        return nullptr;
    }

    nextToken(); // Move to the update expression

    // Parse update
    if (!curTokenIs(TokenType::RPAREN)) {
        stmt->update = parseExpressionStatement();
    }

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    stmt->body = parseBlock();

    return stmt;
}

std::unique_ptr<Expression> Parser::parseExpression(int precedence) {
    std::unique_ptr<Expression> leftExp;

    // Parse the left-hand side based on the current token
    switch (curToken.type) {
        case TokenType::IDENT:
            leftExp = parseIdentifier();
            break;
        case TokenType::INT_LITERAL:
        case TokenType::FLOAT_LITERAL:
        case TokenType::STRING_LITERAL:
        case TokenType::CHAR_LITERAL:
        case TokenType::BOOLEAN_LITERAL:
            leftExp = parseLiteral();
            break;
        case TokenType::BANG:
        case TokenType::MINUS:
            leftExp = parsePrefixExpression();
            break;
        case TokenType::LPAREN:
            leftExp = parseGroupedExpression();
            break;
        default:
            // error in expression
            std::string err_msg = "Error in Expression:" + curToken.literal;
            errors.push_back(err_msg);
            return nullptr;
    }

    while (!peekTokenIs(TokenType::SEMICOLON) && precedence < peekPrecedence()) {
        switch (peekToken.type) {
            case TokenType::PLUS:
            case TokenType::MINUS:
            case TokenType::SLASH:
            case TokenType::ASTERISK:
            case TokenType::EQ:
            case TokenType::NOT_EQ:
            case TokenType::LT:
            case TokenType::LTE:
            case TokenType::GT:
            case TokenType::GTE:
            case TokenType::AND:
            case TokenType::OR:
                nextToken();
                leftExp = parseInfixExpression(std::move(leftExp));
                break;
            case TokenType::LPAREN:
                nextToken();
                leftExp = parseFunctionCall(std::move(leftExp));
                break;
            default:
                return leftExp;
        }
    }

    return leftExp;
}

// Prefix parsing functions
std::unique_ptr<Expression> Parser::parseIdentifier() {
    return std::make_unique<Identifier>(curToken.literal);
}

std::unique_ptr<Expression> Parser::parseLiteral() {
    switch (curToken.type) {
        case TokenType::INT_LITERAL:
            return std::make_unique<Literal>(Literal::Type::Integer, curToken.literal);
        case TokenType::FLOAT_LITERAL:
            return std::make_unique<Literal>(Literal::Type::Float, curToken.literal);
        case TokenType::STRING_LITERAL:
            return std::make_unique<Literal>(Literal::Type::String, curToken.literal);
        case TokenType::CHAR_LITERAL:
            return std::make_unique<Literal>(Literal::Type::Char, curToken.literal);
        case TokenType::BOOLEAN_LITERAL:
            return std::make_unique<Literal>(Literal::Type::Boolean, curToken.literal);
        default:
            return nullptr;
    }
}

std::unique_ptr<Expression> Parser::parseGroupedExpression() {
    nextToken(); // Consume '('

    auto exp = parseExpression();

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    return exp;
}

// Parse a prefix expression, such as "!x" or "-x".
// Prefix expressions have the highest precedence of all expressions.
// The precedence of a prefix expression is determined by the operator.
// For example, the precedence of "!x" is the same as the precedence of "!".
std::unique_ptr<Expression> Parser::parsePrefixExpression() {
    auto expr = std::make_unique<UnaryExpression>();

    expr->op = curToken.literal;

    nextToken();

    expr->operand = parseExpression(Precedence::PREFIX);

    return expr;
}

std::unique_ptr<Expression> Parser::parseFunctionCall(std::unique_ptr<Expression> function) {
    auto expr = std::make_unique<FunctionCall>();

    expr->functionName = function->tokenLiteral();
    expr->arguments = parseExpressionList(TokenType::RPAREN);

    return expr;
}

std::vector<std::unique_ptr<Expression>> Parser::parseExpressionList(TokenType end) {
    std::vector<std::unique_ptr<Expression>> args;

    if (peekTokenIs(end)) {
        nextToken();
        return args;
    }

    nextToken();
    args.push_back(parseExpression());

    while (peekTokenIs(TokenType::COMMA)) {
        nextToken(); // Consume ','
        nextToken(); // Move to next expression
        args.push_back(parseExpression());
    }

    if (!expectPeek(end)) {
        return {};
    }

    return args;
}

// Parse an infix expression, such as "x + y" or "x && y".
// Infix expressions have a left operand, an operator, and a right operand.
// The precedence of an infix expression is determined by the operator.
// For example, the precedence of "x + y" is the same as the precedence of "+".
// The precedence of an infix expression is used to determine the order in which
// the expression is evaluated.
// For example, in the expression "x + y * z", the '*' operator has higher
// precedence than the '+' operator, so the expression is evaluated as
// "(x + (y * z))", not as "(x * y) + z".
// The precedence of an infix expression is stored in the curPrecedence() function.
std::unique_ptr<Expression> Parser::parseInfixExpression(std::unique_ptr<Expression> left) {
    auto expr = std::make_unique<BinaryExpression>();

    expr->left = std::move(left);
    expr->op = curToken.literal;

    int precedence = curPrecedence();

    nextToken();

    expr->right = parseExpression(precedence);

    return expr;
}

