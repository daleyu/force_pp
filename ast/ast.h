// ast.h

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

// AST structure
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string tokenLiteral() const = 0;
};

// Base class for all statements
class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

// Base class for all expressions
class Expression : public ASTNode {
public:
    virtual ~Expression() = default;
};

// Forward declarations
class Parameter;
class Block;
class Identifier;
class Literal;
class UnaryExpression;
class BinaryExpression;
class FunctionCall;

// Parameter ::= Type Identifier
class Parameter : public ASTNode {
public:
    std::string type;
    std::string name;

    Parameter() = default;

    std::string tokenLiteral() const override {
        return type + " " + name;
    }
};

// Block ::= "{" StatementList "}"
class Block : public Statement {
public:
    std::vector<std::unique_ptr<Statement> > statements;

    std::string tokenLiteral() const override {
        return "{...}";
    }
};

// this is the main block that we care about for our ast parsing. 
// Program ::= FunctionDefinition*
class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<Statement> > statements;

    std::string tokenLiteral() const override {
        if (!statements.empty()) {
            return statements.front()->tokenLiteral();
        }
        return "";
    }
};

// FunctionDefinition ::= Type Identifier "(" ParameterList? ")" Block
class FunctionDefinition : public Statement {
public:
    std::string returnType;
    std::string name;
    std::vector<std::unique_ptr<Parameter> > parameters;
    std::unique_ptr<Block> body;

    std::string tokenLiteral() const override {
        return returnType + " " + name;
    }
};

// VariableDeclaration ::= Type Identifier ( "=" Expression )?
class VariableDeclaration : public Statement {
public:
    std::string type;
    std::string name;
    std::unique_ptr<Expression> initializer;

    VariableDeclaration() = default;

    std::string tokenLiteral() const override {
        return type + " " + name;
    }
};

// AssignmentStatement ::= Identifier "=" Expression
class AssignmentStatement : public Statement {
public:
    std::string name;
    std::unique_ptr<Expression> value;

    AssignmentStatement() = default;

    std::string tokenLiteral() const override {
        return name + " = ...";
    }
};

// ExpressionStatement ::= Expression
class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;

    ExpressionStatement() = default;

    std::string tokenLiteral() const override {
        return expression ? expression->tokenLiteral() : "";
    }
};

// ReturnStatement ::= "return" [ Expression ]
class ReturnStatement : public Statement {
public:
    std::unique_ptr<Expression> returnValue;

    ReturnStatement() = default;

    std::string tokenLiteral() const override {
        return "return";
    }
};

// IfStatement ::= "if" "(" Condition ")" Block [ "else" Block ]
class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> consequence;
    std::unique_ptr<Block> alternative;

    IfStatement() = default;

    std::string tokenLiteral() const override {
        return "if (...)";
    }
};

// WhileLoop ::= "while" "(" Condition ")" Block
class WhileLoop : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> body;

    WhileLoop() = default;

    std::string tokenLiteral() const override {
        return "while (...)";
    }
};

// ForLoop
class ForLoop : public Statement {
public:
    std::unique_ptr<Statement> initializer;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> update;
    std::unique_ptr<Block> body;

    ForLoop() = default;

    std::string tokenLiteral() const override {
        return "for (...)";
    }
};

class ForNLoop : public Statement {
public:
    std::string iterator;        // loop variable
    std::unique_ptr<Expression> end;  // End value
    std::unique_ptr<Block> body;      // Loop body

    ForNLoop() = default;
    
    ForNLoop(std::string iter, std::unique_ptr<Expression> endVal, std::unique_ptr<Block> loopBody)
        : iterator(std::move(iter)),
          end(std::move(endVal)),
          body(std::move(loopBody)) {}

    std::string tokenLiteral() const override {
        return "forn";
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

// UnaryExpression ::= UnaryOperator Expression
class UnaryExpression : public Expression {
public:
    std::string op;
    std::unique_ptr<Expression> operand;

    UnaryExpression() = default;

    std::string tokenLiteral() const override {
        return "(" + op + operand->tokenLiteral() + ")";
    }
};

// BinaryExpression ::= Expression BinaryOperator Expression
class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left;
    std::string op;
    std::unique_ptr<Expression> right;

    BinaryExpression() = default;

    std::string tokenLiteral() const override {
        return "(" + left->tokenLiteral() + " " + op + " " + right->tokenLiteral() + ")";
    }
};

// FunctionCall ::= Identifier "(" ArgumentList? ")"
class FunctionCall : public Expression {
public:
    std::string functionName;
    std::vector<std::unique_ptr<Expression> > arguments;

    FunctionCall() = default;

    std::string tokenLiteral() const override {
        return functionName + "(...)";
    }
};

#endif // AST_H
