// #pragma once
// #include <unordered_map>
// #include <string>
// #include "Nodes.h"

// struct SymbolTable
// {
// private:
//     std::unordered_map<Token, std::shared_ptr<Node>> symbols;
// public:
//     std::shared_ptr<SymbolTable> parent;

//     SymbolTable();

//     Node* get(Token name);
//     void set(Token name, std::shared_ptr<Node> value);
//     void remove(Token name);
// };