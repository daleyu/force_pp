// parser.cpp

#include "parser.h"
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

// // Constructor
Parser::Parser(std::vector<Token> t)
{

    idx = 0;
    tokens = t;
    
    // we need to have this table to know what order to do different operators
    // We need this for the recursive descent parsing
    // precedences = {
    //     {TokenType::EQ, Precedence::EQUALS},
    //     {TokenType::NOT_EQ, Precedence::EQUALS},
    //     {TokenType::LT, Precedence::LESSGREATER},
    //     {TokenType::GT, Precedence::LESSGREATER},
    //     {TokenType::LTE, Precedence::LESSGREATER},
    //     {TokenType::GTE, Precedence::LESSGREATER},
    //     {TokenType::PLUS, Precedence::SUM},
    //     {TokenType::MINUS, Precedence::SUM},
    //     {TokenType::SLASH, Precedence::PRODUCT},
    //     {TokenType::ASTERISK, Precedence::PRODUCT},
    //     {TokenType::AND, Precedence::AND},
    //     {TokenType::OR, Precedence::OR},
    //     {TokenType::LPAREN, Precedence::CALL}
    // };
}

void Parser::printNodes() {

    queue<int> q;
    q.push(0);

    while(q.size()) {
        int cur = q.front();
        q.pop();
        cout << cur << ' ' << nodes[cur].type << ' ' << nodes[cur].name << '\n';
        cout << "children: ";
        for(int z : nodes[cur].children) {
            cout << z << ' ';
            q.push(z);
        }
        cout << '\n';
    }

}

int Parser::createNode() {
    nodes.push_back({"", "", {}});
    return nodes.size()-1;
}

// // Errors function
// std::vector<std::string> Parser::Errors() const {
//     return errors;
// }

// ParseProgram function
void Parser::parseProgram() {
    nodes.clear();
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "PROGRAM";

    while (!curTokenIs(TokenType::EOF_TOKEN)) {
        cout << idx << '\n';
        int stmt = parseFunction();
        if (stmt != -1) {
            nodes[nodeIdx].children.push_back(stmt);
        }
        else return;
    }
}

int Parser::parseFunction() {
    bool valid = true;
    int nodeIdx = createNode();

    valid &= readTokenType();
    valid &= readToken(TokenType::IDENT);
    if(valid) {
        int childIdx = createNode();
        nodes[nodeIdx].children.push_back(childIdx);
        nodes[childIdx].type = TokenTypeToString(tokens[idx-2].type);
        nodes[childIdx].name = tokens[idx-1].literal;
    }
    valid &= readToken(TokenType::LPAREN);
    int ret = parseArguments();
    if(ret == -1) return -1;
    else {
        nodes[nodeIdx].children.push_back(ret);
    }
    valid &= readToken(TokenType::RPAREN);
    valid &= readToken(TokenType::LBRACE);
    ret = parseBlock();
    if(ret == -1) return -1;
    else {
        nodes[nodeIdx].children.push_back(ret);
    }
    valid &= readToken(TokenType::RBRACE);

    if(!valid) return -1;
    return nodeIdx;

}

int Parser::parseArguments() {
    bool valid = true;

    int nodeIdx = createNode();
    nodes[nodeIdx].name = "PARAMS";

    while(true) {
        if(curTokenIs(TokenType::RPAREN)) break;
        valid &= readTokenType();
        valid &= readToken(TokenType::IDENT);
        if(!valid) return -1;
        int childIdx = createNode();
        nodes[nodeIdx].children.push_back(childIdx);
        nodes[childIdx].type = TokenTypeToString(tokens[idx-2].type);
        nodes[childIdx].name = tokens[idx-1].literal;        
        valid &= readToken(TokenType::COMMA);
        if(!valid) break;
    }


    return nodeIdx;

}

// // Token functions
void Parser::nextToken() { idx++;}

Token Parser::curToken() {
    if(idx >= (int)tokens.size()) idx = tokens.size()-1;
    return tokens[idx];
}

/**
 * Checks if the current token matches the specified token type.
 *
 * @param t The token type to compare with the current token.
 * @return true if the current token's type is equal to the specified type, false otherwise.
 */
bool Parser::curTokenIs(TokenType t) {
    if(idx >= (int)tokens.size()) idx = tokens.size()-1;

    return tokens[idx].type == t;
}

/**
 * Advances the parser to the next token if the current token matches the specified token type.
 *
 * @param t The token type to compare with the current token.
 * @return true if the current token's type is equal to the specified type and the parser advanced,
 *         false otherwise.
 */
bool Parser::readToken(TokenType t) {
    if(idx >= (int)tokens.size()) idx = tokens.size()-1;
    if(tokens[idx].type == t) {
        idx++;
        return true;
    }
    return false;
}


bool Parser::peekTokenIs(TokenType t){
    if (idx + 1 >= (int)tokens.size()) return false;
    return tokens[idx + 1].type == t;
}

/**
 * Ensures the next token matches the specified token type.
 *
 * @param t The token type to compare with the next token.
 * @return true if the next token's type is equal to the specified type and advances the parser, false otherwise.
 */
bool Parser::expectPeek(TokenType t) {
    if (peekTokenIs(t)) {
        nextToken();
        return true;
    } else {
        peekError(t);
        return false;
    }
}

/**
 * Records an error message when the next token does not match the expected token type.
 */
void Parser::peekError(TokenType t) {
    std::string msg = "Unexpected Token Error: Expected " + TokenTypeToString(t) 
                      + ", got " + TokenTypeToString(tokens[idx + 1].type) + " instead";
    errors.push_back(msg);
}

bool Parser::readTokenType() {
    if(idx >= (int)tokens.size()) idx = tokens.size()-1;
    if(isType(tokens[idx].type)) {
        idx++;
        return true;
    }
    return false;
}

bool Parser::isTokenType() {
    if(idx >= (int)tokens.size()) idx = tokens.size()-1;
    if(isType(tokens[idx].type)) {
        return true;
    }
    return false;
}

// bool Parser::peekTokenIs(TokenType t) const {
//     return peekToken.type == t;
// }

// bool Parser::expectPeek(TokenType t) {
//     if (peekTokenIs(t)) {
//         nextToken();
//         return true;
//     } else {
//         peekError(t);
//         return false;
//     }
// }

// void Parser::peekError(TokenType t) {
//     std::string msg = "expected next token to be " + TokenTypeToString(t) + ", got " + TokenTypeToString(peekToken.type) + " instead";
//     errors.push_back(msg);
// }

// Helper methods
bool Parser::isType(TokenType t) const {
    return t == TokenType::INT || t == TokenType::FLOAT || t == TokenType::CHAR ||
           t == TokenType::BOOL || t == TokenType::VARCHAR || t == TokenType::VI || t == TokenType::VOID;
}

// int Parser::peekPrecedence() const {
//     auto it = precedences.find(peekToken.type);
//     if (it != precedences.end()) {
//         return it->second;
//     }
//     return Precedence::LOWEST;
// }

// int Parser::curPrecedence() const {
//     auto it = precedences.find(curToken.type);
//     if (it != precedences.end()) {
//         return it->second;
//     }
//     return Precedence::LOWEST;
// }

// bool Parser::isAssignmentStatement() const {
//     return curTokenIs(TokenType::IDENT) && peekTokenIs(TokenType::ASSIGN);
// }

// bool Parser::isExpressionStatement() const {
//     // For simplicity, treat any expression starting with an identifier or literal as an expression statement
//     return curTokenIs(TokenType::IDENT) || curTokenIs(TokenType::INT_LITERAL) || curTokenIs(TokenType::FLOAT_LITERAL) ||
//            curTokenIs(TokenType::STRING_LITERAL) || curTokenIs(TokenType::CHAR_LITERAL) || curTokenIs(TokenType::BOOLEAN_LITERAL);
// }

int Parser::parseBlock() {
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "CODE BLOCK";

    while (!curTokenIs(TokenType::RBRACE) && !curTokenIs(TokenType::EOF_TOKEN)) {
        int stmt = parseStatement();
        if (stmt != -1) nodes[nodeIdx].children.push_back(stmt);
    }

    return nodeIdx;
}

// Parsing methods
int Parser::parseStatement() {
    if (isTokenType()) {
        return parseVariableDeclaration();
    } 
    else if (isAssignmentStatement()) {
        return parseAssignmentStatement();
    } else if (curTokenIs(TokenType::RETURN)) {
        return parseReturnStatement();
    } else if (curTokenIs(TokenType::FOR)) {
        return parseForLoop();
    } else if (curTokenIs(TokenType::WHILE)) {
        return parseWhileLoop();
    } else if (curTokenIs(TokenType::IF)) {
        return parseIfStatement();
    } else if (curTokenIs(TokenType::LBRACE)) {
        return parseBlock();
    } else if (isExpressionStatement()) {
        return parseExpressionStatement();
    } 
    else {
        // Handle error or skip token
        nextToken();
        return -1;
    }
}

bool Parser::isExpressionStatement(){
    return curTokenIs(TokenType::IDENT) || curTokenIs(TokenType::INT_LITERAL) ||
           curTokenIs(TokenType::FLOAT_LITERAL) || curTokenIs(TokenType::STRING_LITERAL) ||
           curTokenIs(TokenType::CHAR_LITERAL) || curTokenIs(TokenType::BOOLEAN_LITERAL);
}

int Parser::getPrecedence(TokenType type) {
    if (precedences.find(type) != precedences.end()) {
        return precedences[type];
    }
    return Precedence::LOWEST;
}

bool Parser::isBinaryOperator(TokenType type) {
    return type == TokenType::PLUS || type == TokenType::MINUS ||
           type == TokenType::ASTERISK || type == TokenType::SLASH;
}

bool Parser::isBooleanOperator(TokenType type) {
    return type == TokenType::EQ || type == TokenType::NOT_EQ ||
           type == TokenType::LT || type == TokenType::LTE ||
           type == TokenType::GT || type == TokenType::GTE ||
           type == TokenType::AND || type == TokenType::OR;
}

// end of helper functions

bool Parser::isAssignmentStatement() {
    // Ensure current token is an identifier and the next token is an assignment operator
    return curTokenIs(TokenType::IDENT) && peekTokenIs(TokenType::ASSIGN);
}

int Parser::parseVariableDeclaration() {
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "DECLARATION";
    // Set the type
    nodes[nodeIdx].type = curToken().literal;
    nextToken();

    // Expect an identifier
    if (!curTokenIs(TokenType::IDENT)) return -1;
    nodes[nodeIdx].name = curToken().literal;
    nextToken();

    // Optional initializer
    if (curTokenIs(TokenType::ASSIGN)) {
        nextToken(); // Consume ASSIGN token
        int ret = parseExpressionStatement();
        if(ret == -1) return -1;
        nodes[nodeIdx].children.push_back(ret);
    }

    // Expect a semicolon
    if (!readToken(TokenType::SEMICOLON)) {
        return -1;
    }

    return nodeIdx;
}

int Parser::parseAssignmentStatement() {
    return -1;
}

// std::unique_ptr<Statement> Parser::parseAssignmentStatement() {
//     auto stmt = std::make_unique<AssignmentStatement>();

//     stmt->name = curToken.literal;

//     // Expect '='
//     if (!expectPeek(TokenType::ASSIGN)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the expression

//     stmt->value = parseExpression();

//     // Expect a semicolon
//     if (!expectPeek(TokenType::SEMICOLON)) {
//         return nullptr;
//     }

//     return stmt;
// }

int Parser::parseReturnStatement() {
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "RETURN";

    nextToken(); // Move to the expression
    int ret = parseExpressionStatement();
    if(ret == -1) return ret;
    nodes[nodeIdx].children.push_back(ret);

    // Expect a semicolon
    if (!expectPeek(TokenType::SEMICOLON)) {
        return -1;
    }

    return nodeIdx;
}



int Parser::parseIfStatement(){
    return -1;
}
// std::unique_ptr<Statement> Parser::parseIfStatement() {
//     auto stmt = std::make_unique<IfStatement>();

//     if (!expectPeek(TokenType::LPAREN)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the condition

//     stmt->condition = parseExpression();

//     if (!expectPeek(TokenType::RPAREN)) {
//         return nullptr;
//     }

//     if (!expectPeek(TokenType::LBRACE)) {
//         return nullptr;
//     }

//     stmt->consequence = parseBlock();

//     if (peekTokenIs(TokenType::ELSE)) {
//         nextToken(); // Consume 'else'

//         if (!expectPeek(TokenType::LBRACE)) {
//             return nullptr;
//         }

//         stmt->alternative = parseBlock();
//     }

//     return stmt;
// }

int Parser::parseWhileLoop(){
    return -1;
}
// std::unique_ptr<Statement> Parser::parseWhileLoop() {
//     auto stmt = std::make_unique<WhileLoop>();

//     if (!expectPeek(TokenType::LPAREN)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the condition

//     stmt->condition = parseExpression();

//     if (!expectPeek(TokenType::RPAREN)) {
//         return nullptr;
//     }

//     if (!expectPeek(TokenType::LBRACE)) {
//         return nullptr;
//     }

//     stmt->body = parseBlock();

//     return stmt;
// }

int Parser::parseForLoop(){
    return -1;
}
// std::unique_ptr<Statement> Parser::parseForLoop() {
//     // Simplified for loop parsing
//     auto stmt = std::make_unique<ForLoop>();

//     if (!expectPeek(TokenType::LPAREN)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the initializer

//     // Parse initializer
//     if (isType(curToken.type) && peekTokenIs(TokenType::IDENT)) {
//         stmt->initializer = parseVariableDeclaration();
//     } else if (curTokenIs(TokenType::SEMICOLON)) {
//         stmt->initializer = nullptr;
//     } else {
//         stmt->initializer = parseExpressionStatement();
//     }

//     if (!expectPeek(TokenType::SEMICOLON)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the condition

//     // Parse condition
//     if (!curTokenIs(TokenType::SEMICOLON)) {
//         stmt->condition = parseExpression();
//     }

//     if (!expectPeek(TokenType::SEMICOLON)) {
//         return nullptr;
//     }

//     nextToken(); // Move to the update expression

//     // Parse update
//     if (!curTokenIs(TokenType::RPAREN)) {
//         stmt->update = parseExpressionStatement();
//     }

//     if (!expectPeek(TokenType::RPAREN)) {
//         return nullptr;
//     }

//     if (!expectPeek(TokenType::LBRACE)) {
//         return nullptr;
//     }

//     stmt->body = parseBlock();

//     return stmt;
// }
int Parser::parseExpressionStatement() {
    int exprIdx = parseExpression();
    if (exprIdx == -1) {
        return -1;
    }

    // Expect a semicolon
    if (!readToken(TokenType::SEMICOLON)) {
        return -1;
    }

    return exprIdx;
}

int Parser::parseExpression(int precedence) {
    int nodeIdx = -1;

    // Parse left-hand side (could be a primary expression)
    if (curTokenIs(TokenType::IDENT)) {
        // It could be a FunctionCall or an Identifier
        int identIdx = createNode();
        nodes[identIdx].name = curToken().literal;
        nodes[identIdx].type = "IDENTIFIER";
        nextToken(); // Move past the identifier

        if (curTokenIs(TokenType::LPAREN)) {
            // FunctionCall
            nodeIdx = createNode();
            nodes[nodeIdx].name = "FUNCTION CALL";
            nodes[nodeIdx].children.push_back(identIdx);

            if (!readToken(TokenType::LPAREN)) {
                return -1;
            }

            // Parse arguments
            int argsIdx = createNode();
            nodes[argsIdx].name = "ARGUMENTS";
            nodes[nodeIdx].children.push_back(argsIdx);

            while (!curTokenIs(TokenType::RPAREN) && !curTokenIs(TokenType::EOF_TOKEN)) {
                int argIdx = parseExpression();
                if (argIdx == -1) return -1;
                nodes[argsIdx].children.push_back(argIdx);

                if (curTokenIs(TokenType::COMMA)) {
                    readToken(TokenType::COMMA);
                } else {
                    break;
                }
            }

            if (!readToken(TokenType::RPAREN)) {
                return -1;
            }

        } else {
            // Just an identifier
            nodeIdx = identIdx;
        }

    } else if (curTokenIs(TokenType::INT_LITERAL) || curTokenIs(TokenType::FLOAT_LITERAL) ||
               curTokenIs(TokenType::STRING_LITERAL) || curTokenIs(TokenType::CHAR_LITERAL) ||
               curTokenIs(TokenType::BOOLEAN_LITERAL)) {
        // Literal
        nodeIdx = createNode();
        nodes[nodeIdx].name = "LITERAL";
        nodes[nodeIdx].type = TokenTypeToString(curToken().type);
        nodes[nodeIdx].name = curToken().literal;

        nextToken(); // Move past the literal

    } else if (curTokenIs(TokenType::LPAREN)) {
        // Grouped Expression
        readToken(TokenType::LPAREN);
        nodeIdx = parseExpression();
        if (!readToken(TokenType::RPAREN)) {
            return -1;
        }

    } else if (curTokenIs(TokenType::MINUS) || curTokenIs(TokenType::BANG)) {
        // Unary Operator
        int unaryNodeIdx = createNode();
        nodes[unaryNodeIdx].name = "UNARY OPERATOR";
        nodes[unaryNodeIdx].type = curToken().literal;

        nextToken(); // Move past the unary operator

        int operandIdx = parseExpression(Precedence::PREFIX);
        if (operandIdx == -1) {
            return -1;
        }
        nodes[unaryNodeIdx].children.push_back(operandIdx);

        nodeIdx = unaryNodeIdx;
    } else {
        // Error or unhandled case
        return -1;
    }

    // Now, handle binary operators (left-associative)
    while (true) {
        int currentPrecedence = getPrecedence(curToken().type);

        if (currentPrecedence < precedence) {
            break;
        }

        // Handle BinaryOperator or BooleanOperator
        TokenType opType = curToken().type;
        if (isBinaryOperator(opType) || isBooleanOperator(opType)) {
            int binNodeIdx = createNode();
            nodes[binNodeIdx].name = "BINARY OPERATOR";
            nodes[binNodeIdx].type = curToken().literal;

            nextToken(); // Move past the operator

            // Parse the right-hand side expression
            int rightIdx = parseExpression(currentPrecedence);
            if (rightIdx == -1) {
                return -1;
            }

            // Left side is nodeIdx
            nodes[binNodeIdx].children.push_back(nodeIdx);
            nodes[binNodeIdx].children.push_back(rightIdx);

            nodeIdx = binNodeIdx;
        } else {
            break;
        }
    }

    return nodeIdx;
}
    // std::unique_ptr<Expression> leftExp;

    // // Parse the left-hand side based on the current token
    // switch (curToken.type) {
    //     case TokenType::IDENT:
    //         leftExp = parseIdentifier();
    //         break;
    //     case TokenType::INT_LITERAL:
    //     case TokenType::FLOAT_LITERAL:
    //     case TokenType::STRING_LITERAL:
    //     case TokenType::CHAR_LITERAL:
    //     case TokenType::BOOLEAN_LITERAL:
    //         leftExp = parseLiteral();
    //         break;
    //     case TokenType::BANG:
    //     case TokenType::MINUS:
    //         leftExp = parsePrefixExpression();
    //         break;
    //     case TokenType::LPAREN:
    //         leftExp = parseGroupedExpression();
    //         break;
    //     default:
    //         // Handle error
    //         return nullptr;
    // }

    // while (!peekTokenIs(TokenType::SEMICOLON) && precedence < peekPrecedence()) {
    //     switch (peekToken.type) {
    //         case TokenType::PLUS:
    //         case TokenType::MINUS:
    //         case TokenType::SLASH:
    //         case TokenType::ASTERISK:
    //         case TokenType::EQ:
    //         case TokenType::NOT_EQ:
    //         case TokenType::LT:
    //         case TokenType::LTE:
    //         case TokenType::GT:
    //         case TokenType::GTE:
    //         case TokenType::AND:
    //         case TokenType::OR:
    //             nextToken();
    //             leftExp = parseInfixExpression(std::move(leftExp));
    //             break;
    //         case TokenType::LPAREN:
    //             nextToken();
    //             leftExp = parseFunctionCall(std::move(leftExp));
    //             break;
    //         default:
    //             return leftExp;
    //     }
    // }

    // return leftExp;

// // Prefix parsing functions
// std::unique_ptr<Expression> Parser::parseIdentifier() {
//     return std::make_unique<Identifier>(curToken.literal);
// }

// std::unique_ptr<Expression> Parser::parseLiteral() {
//     switch (curToken.type) {
//         case TokenType::INT_LITERAL:
//             return std::make_unique<Literal>(Literal::Type::Integer, curToken.literal);
//         case TokenType::FLOAT_LITERAL:
//             return std::make_unique<Literal>(Literal::Type::Float, curToken.literal);
//         case TokenType::STRING_LITERAL:
//             return std::make_unique<Literal>(Literal::Type::String, curToken.literal);
//         case TokenType::CHAR_LITERAL:
//             return std::make_unique<Literal>(Literal::Type::Char, curToken.literal);
//         case TokenType::BOOLEAN_LITERAL:
//             return std::make_unique<Literal>(Literal::Type::Boolean, curToken.literal);
//         default:
//             return nullptr;
//     }
// }

// std::unique_ptr<Expression> Parser::parseGroupedExpression() {
//     nextToken(); // Consume '('

//     auto exp = parseExpression();

//     if (!expectPeek(TokenType::RPAREN)) {
//         return nullptr;
//     }

//     return exp;
// }

// std::unique_ptr<Expression> Parser::parsePrefixExpression() {
//     auto expr = std::make_unique<UnaryExpression>();

//     expr->op = curToken.literal;

//     nextToken();

//     expr->operand = parseExpression(Precedence::PREFIX);

//     return expr;
// }

// std::unique_ptr<Expression> Parser::parseFunctionCall(std::unique_ptr<Expression> function) {
//     auto expr = std::make_unique<FunctionCall>();

//     expr->functionName = function->tokenLiteral();
//     expr->arguments = parseExpressionList(TokenType::RPAREN);

//     return expr;
// }

// std::vector<std::unique_ptr<Expression>> Parser::parseExpressionList(TokenType end) {
//     std::vector<std::unique_ptr<Expression>> args;

//     if (peekTokenIs(end)) {
//         nextToken();
//         return args;
//     }

//     nextToken();
//     args.push_back(parseExpression());

//     while (peekTokenIs(TokenType::COMMA)) {
//         nextToken(); // Consume ','
//         nextToken(); // Move to next expression
//         args.push_back(parseExpression());
//     }

//     if (!expectPeek(end)) {
//         return {};
//     }

//     return args;
// }

// // Infix parsing functions
// std::unique_ptr<Expression> Parser::parseInfixExpression(std::unique_ptr<Expression> left) {
//     auto expr = std::make_unique<BinaryExpression>();

//     expr->left = std::move(left);
//     expr->op = curToken.literal;

//     int precedence = curPrecedence();

//     nextToken();

//     expr->right = parseExpression(precedence);

//     return expr;
// }

