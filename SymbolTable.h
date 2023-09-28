#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Type.h"
#include "Token.h"

struct SymbolTable
{
private:
    std::unordered_map<Token, std::shared_ptr<Type>, TokenHasher> symbols;
public:
    std::shared_ptr<SymbolTable> parent;

    SymbolTable();

    // ? maybe this should change as well
    std::shared_ptr<Type> get(Token name);
    void set(Token name, std::shared_ptr<Type> value);
    void remove(Token name);
};