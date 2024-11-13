// ast.h

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>


// AST structure
class ASTNode {
public:
    std::string type;
    std::string varType;
    std::string name;
    std::vector<int> children;
};

#endif // AST_H
