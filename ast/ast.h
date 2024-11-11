#ifndef AST_H
#define AST_H

#include <vector>
#include <memory>
#include <string>

typedef enum {
    NODE_TYPE_LITERAL,
    NODE_TYPE_VARIABLE,
    NODE_TYPE_BINARY_OP,
    NODE_TYPE_UNARY_OP,
    NODE_TYPE_FUNCTION_CALL,
    NODE_TYPE_ASSIGNMENT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        // For literals
        struct {
            int intValue;
            double doubleValue;
            char charValue;
            const char *stringValue;
        } literal;
        
        // For variables and assignments
        struct {
            const char *name;
            struct ASTNode *value;
        } variable;

        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            char op;
        } binary_op;

        struct {
            struct ASTNode *operand;
            char op;
        } unary_op;

        // For function calls
        struct {
            const char *name;
            struct ASTNode **arguments;
            int argument_count;
        } function_call;
    } data;

    NodeType nodeType;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    // Constructors
    ASTNode(NodeType type, const std::string& value) : type(type), value(value) {}
    ASTNode(const std::string& value) : value(value) {}
    ASTNode(const std::string& value, const std::string& name, const std::string& op, const std::string& left, const std::string& right) : value(value) {
        data.binary_op.left = new ASTNode(NODE_TYPE_VARIABLE, left);
        data.binary_op.right = new ASTNode(NODE_TYPE_VARIABLE, right);
        data.binary_op.op = op[0];
    }
} ASTNode;

ASTNode *createLiteralNode(int intValue, double doubleValue, char charValue, const char *stringValue);
ASTNode *createVariableNode(const char *name);
ASTNode *createAssignmentNode(const char *name, ASTNode *value);
ASTNode *createBinaryOpNode(ASTNode *left, ASTNode *right, char op);
ASTNode *createUnaryOpNode(ASTNode *operand, char op);
ASTNode *createFunctionCallNode(const char *name, ASTNode **arguments, int argument_count);
void freeASTNode(ASTNode *node);

#endif // AST_H