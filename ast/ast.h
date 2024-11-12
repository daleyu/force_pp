// ast.h

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string tokenLiteral() const = 0;
};

// Program ::= FunctionDefinition*
class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> functions;

    std::string tokenLiteral() const override {
        if (!functions.empty()) {
            return functions.front()->tokenLiteral();
        }
        return "";
    }
};

// FunctionDefinition ::= Type Identifier "(" ParameterList? ")" Block
class FunctionDefinition : public ASTNode {
public:
    std::string returnType;
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> parameters;
    std::unique_ptr<ASTNode> body;

    std::string tokenLiteral() const override {
        return returnType + " " + name;
    }
};

// Parameter ::= Type Identifier
class Parameter : public ASTNode {
public:
    std::string type;
    std::string name;

    std::string tokenLiteral() const override {
        return type + " " + name;
    }
};

// Block ::= "{" StatementList "}"
class Block : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;

    std::string tokenLiteral() const override {
        return "{...}";
    }
};

// Statement base class
class Statement : public ASTNode {
};

// Expression base class
class Expression : public ASTNode {
};

// VariableDeclaration ::= Type Identifier ( "=" Expression )?
class VariableDeclaration : public Statement {
public:
    std::string type;
    std::string name;
    std::unique_ptr<Expression> initializer;

    VariableDeclaration(std::string type, std::string name, std::unique_ptr<Expression> initializer = nullptr)
        : type(std::move(type)), name(std::move(name)), initializer(std::move(initializer)) {}

    std::string tokenLiteral() const override {
        return type + " " + name;
    }
};

// AssignmentStatement ::= Identifier "=" Expression
class AssignmentStatement : public Statement {
public:
    std::string name;
    std::unique_ptr<Expression> value;

    AssignmentStatement(std::string name, std::unique_ptr<Expression> value)
        : name(std::move(name)), value(std::move(value)) {}

    std::string tokenLiteral() const override {
        return name + " = ...";
    }
};

// ExpressionStatement ::= Expression
class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;

    explicit ExpressionStatement(std::unique_ptr<Expression> expression)
        : expression(std::move(expression)) {}

    std::string tokenLiteral() const override {
        return expression ? expression->tokenLiteral() : "";
    }
};

// IfStatement ::= "if" "(" Condition ")" Statement [ "else" Statement ]
class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> consequence;
    std::unique_ptr<Statement> alternative;

    std::string tokenLiteral() const override {
        return "if (...)";
    }
};

// WhileLoop ::= "while" "(" Condition ")" Statement
class WhileLoop : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;

    std::string tokenLiteral() const override {
        return "while (...)";
    }
};

// ForLoop simplified for this example
class ForLoop : public Statement {
public:
    std::unique_ptr<Statement> initializer;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> update;
    std::unique_ptr<Statement> body;

    std::string tokenLiteral() const override {
        return "for (...)";
    }
};

// ReturnStatement ::= "return" [ Expression ]
class ReturnStatement : public Statement {
public:
    std::unique_ptr<Expression> returnValue;

    std::string tokenLiteral() const override {
        return "return";
    }
};

// Identifier
class Identifier : public Expression {
public:
    std::string value;

    explicit Identifier(std::string value) : value(std::move(value)) {}

    std::string tokenLiteral() const override {
        return value;
    }
};

// Literal ::= <DECIMAL_LITERAL> | <FLOAT_LITERAL> | <STRING_LITERAL> | <CHAR_LITERAL> | <BOOLEAN_LITERAL>
class Literal : public Expression {
public:
    enum class Type {
        Integer,
        Float,
        String,
        Char,
        Boolean
    } type;

    std::string value;

    Literal(Type type, std::string value)
        : type(type), value(std::move(value)) {}

    std::string tokenLiteral() const override {
        return value;
    }
};

// BinaryExpression ::= Expression BinaryOperator Expression
class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left;
    std::string op;
    std::unique_ptr<Expression> right;

    BinaryExpression(std::unique_ptr<Expression> left, std::string op, std::unique_ptr<Expression> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    std::string tokenLiteral() const override {
        return "(" + left->tokenLiteral() + " " + op + " " + right->tokenLiteral() + ")";
    }
};

// FunctionCall ::= Identifier "(" ArgumentList? ")"
class FunctionCall : public Expression {
public:
    std::string functionName;
    std::vector<std::unique_ptr<Expression>> arguments;

    FunctionCall(std::string functionName, std::vector<std::unique_ptr<Expression>> arguments)
        : functionName(std::move(functionName)), arguments(std::move(arguments)) {}

    std::string tokenLiteral() const override {
        return functionName + "(...)";
    }
};

#endif // AST_H