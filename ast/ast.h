#ifndef AST_H
#define AST_H

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

        // For binary operations like addition, subtraction, etc.
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            char op;
        } binary_op;

        // For unary operations like negation, etc.
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
} ASTNode;

ASTNode *createLiteralNode(int intValue, double doubleValue, char charValue, const char *stringValue);
ASTNode *createVariableNode(const char *name);
ASTNode *createAssignmentNode(const char *name, ASTNode *value);
ASTNode *createBinaryOpNode(ASTNode *left, ASTNode *right, char op);
ASTNode *createUnaryOpNode(ASTNode *operand, char op);
ASTNode *createFunctionCallNode(const char *name, ASTNode **arguments, int argument_count);
void freeASTNode(ASTNode *node);

#endif // AST_H
