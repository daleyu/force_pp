// token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <unordered_map>
#include <vector>
class Token {
public:
    std::string type;
    std::string literal;

    Token(const std::string type, const std::string& literal) : type(type), literal(literal) {}
};
#endif // TOKEN_H
