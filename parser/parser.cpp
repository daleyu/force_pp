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

// Errors function moved to parser.h now 

// ParseProgram function
void Parser::parseProgram() {
    nodes.clear();
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "PROGRAM";

    while (!curTokenIs(TokenType::EOF_TOKEN)) {
        int stmt = parseStatement();
        if (stmt != -1) {
            nodes[nodeIdx].children.push_back(stmt);
        }
        else {
            nextToken();
        }
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
    if (isTokenType() && peekTokenIs(TokenType::IDENT) && tokens[idx + 2].type == TokenType::LPAREN) {
        return parseFunction();
    } else if (isTokenType()) {
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
    auto it = precedences.find(type);
    if (it != precedences.end()) {
        return it->second;
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
        int ret = parseExpression();
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
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "ASSIGNMENT";

    // Ensure current token is Identifier
    if (!curTokenIs(TokenType::IDENT)) {
        return -1;
    }
    nodes[nodeIdx].type = "Identifier";
    nodes[nodeIdx].name = curToken().literal;  // the identifier name
    nextToken();  // Move past the identifier

    // Expect '='
    if (!readToken(TokenType::ASSIGN)) {
        return -1;
    }

    // Parse Expression
    int exprIdx = parseExpression();
    if (exprIdx == -1) {
        return -1;
    }
    nodes[nodeIdx].children.push_back(exprIdx);

    // Expect a semicolon
    if (!readToken(TokenType::SEMICOLON)) {
        return -1;
    }

    return nodeIdx;
}

int Parser::parseReturnStatement() {
    int nodeIdx = createNode();
    nodes[nodeIdx].name = "RETURN";

    nextToken();
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


int Parser::parseWhileLoop(){
    return -1;
}

int Parser::parseForLoop(){
    return -1;
}
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
        // FunctionCall or an Identifier at first check thingy
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
        errors.push_back("expected expression, got " + TokenTypeToString(curToken().type) + " instead");
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

            nodes[binNodeIdx].children.push_back(nodeIdx);
            nodes[binNodeIdx].children.push_back(rightIdx);

            nodeIdx = binNodeIdx;
        } else {
            errors.push_back("expected binary operator, got " + TokenTypeToString(curToken().type) + " instead");
            break;
        }
    }

    return nodeIdx;
}