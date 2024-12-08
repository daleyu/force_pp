// processor.h

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <memory>
#include "../ast/ast.h"
#include <iostream>
#include <fstream>

class Processor {
public:
    Processor(std::vector<ASTNode>, std::string);
    std::vector<ASTNode> nodes;
    std::string filename;
    std::ofstream outfile;
    void process();
    void dfs(int);
};

#endif // PROCESSOR_H
