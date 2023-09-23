#pragma once
#include <unordered_map>
#include <string>
#include "Nodes.h"

struct SymbolTable
{
private:
    // ? Should symbols be returning Nodes?
    std::unordered_map<Token, std::shared_ptr<Node>, TokenHasher> symbols;
public:
    std::shared_ptr<SymbolTable> parent;

    SymbolTable();

    // ? maybe this should change as well
    Node* get(Token name);
    void set(Token name, std::shared_ptr<Node> value);
    void remove(Token name);
};