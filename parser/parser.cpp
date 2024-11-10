#include <vector>
#include <string>
#include <memory>
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"

class Parser {
public:
    Parser(std::shared_ptr<Lexer> l) : lexer(l), errors() {
        nextToken();
        nextToken();
    }

    std::vector<std::string> Errors() const {
        return errors;
    }

    std::unique_ptr<Program> ParseProgram() {
        auto program = std::make_unique<Program>();
        while (!curTokenIs(TokenType::EOF_TOKEN)) {
            auto stmt = parseStatement();
            if (stmt != nullptr) {
                program->statements.push_back(move(stmt));
            }
            nextToken();
        }
        return program;
    }
    
private:
    std::shared_ptr<Lexer> lexer;
    Token curToken;
    Token peekToken;
    std::vector<std::string> errors;

    void peekError(TokenType t) {
        std::string msg = "expected next token to be " + Token::TypeToString(t) + ", got " + Token::TypeToString(peekToken.type) + " instead";
        errors.push_back(msg);
    }

    void nextToken() {
        curToken = peekToken;
        peekToken = lexer->NextToken();
    }

    bool curTokenIs(TokenType t) const {
        return curToken.type == t;
    }

    bool peekTokenIs(TokenType t) const {
        return peekToken.type == t;
    }

    bool expectPeek(TokenType t) {
        if (peekTokenIs(t)) {
            nextToken();
            return true;
        } else {
            peekError(t);
            return false;
        }
    }

    std::unique_ptr<Statement> parseLetStatement() {
        auto stmt = std::make_unique<LetStatement>();
        stmt->token = curToken;

        if (!expectPeek(TokenType::IDENT)) {
            return nullptr;
        }

        stmt->name = std::make_unique<Identifier>(curToken, curToken.literal);

        if (!expectPeek(TokenType::ASSIGN)) {
            return nullptr;
        }

        // Skip expressions until encounter a semicolon
        while (!curTokenIs(TokenType::SEMICOLON)) {
            nextToken();
        }

        return stmt;
    }

    std::unique_ptr<Statement> parseStatement() {
        switch (curToken.type) {
            case TokenType::LET:
                return parseLetStatement();
            default:
                return nullptr;
        }
    }
};
