#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Abstract base class representing a node in the AST
class Node {
public:
    virtual ~Node() {}
    virtual std::string tokenLiteral() const = 0;
};

// Interface for statements in the AST
class Statement : public Node {
public:
    virtual ~Statement() {}
    virtual void statementNode() = 0;
};

// Interface for expressions in the AST
class Expression : public Node {
public:
    virtual ~Expression() {}
    virtual void expressionNode() = 0;
};

// Class representing an identifier
class Identifier : public Expression {
    std::string value;
public:
    Identifier(const std::string &val, const std::string &token) 
        : value(val), tokenLiteralValue(token) {}
    
    std::string tokenLiteral() const override {
        return tokenLiteralValue;
    }

    void expressionNode() override {}

private:
    std::string tokenLiteralValue;
};

// Class representing a Let statement
class LetStatement : public Statement {
    std::string tokenLiteralValue;
    std::unique_ptr<Identifier> name;
    std::unique_ptr<Expression> value;
public:
    LetStatement(const std::string &token, std::unique_ptr<Identifier> name, std::unique_ptr<Expression> value)
        : tokenLiteralValue(token), name(std::move(name)), value(std::move(value)) {}

    std::string tokenLiteral() const override {
        return tokenLiteralValue;
    }

    void statementNode() override {}
};

// Class representing a Return statement
class ReturnStatement : public Statement {
    std::string tokenLiteralValue;
    std::unique_ptr<Expression> returnValue;
public:
    ReturnStatement(const std::string &token, std::unique_ptr<Expression> returnValue)
        : tokenLiteralValue(token), returnValue(std::move(returnValue)) {}

    std::string tokenLiteral() const override {
        return tokenLiteralValue;
    }

    void statementNode() override {}
};

// Class representing a program which contains statements
class Program {
    std::vector<std::unique_ptr<Statement>> statements;

public:
    void addStatement(std::unique_ptr<Statement> stmt) {
        statements.push_back(std::move(stmt));
    }

    std::string tokenLiteral() const {
        if (!statements.empty()) {
            return statements[0]->tokenLiteral();
        }
        return "";
    }
};

// Example usage
int main() {
    auto identifier = std::make_unique<Identifier>("x", "IDENT");
    auto letStmt = std::make_unique<LetStatement>("LET", std::move(identifier), nullptr);

    Program program;
    program.addStatement(std::move(letStmt));

    std::cout << program.tokenLiteral() << std::endl;
    return 0;
}
