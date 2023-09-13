// #include "SymbolTable.h"

// SymbolTable::SymbolTable()
//     : parent(nullptr)
// {

// }

// Node* SymbolTable::get(Token name)
// {
//     Node* value = nullptr;
//     try
//     {
//         value = symbols.at(name).get();
//     }
//     catch(const std::exception& e) {}
    
//     if(!value && parent) return parent->get(name);
//     return value;
// }

// void SymbolTable::set(Token name, std::shared_ptr<Node> value)
// {
//     symbols[name] = value;
// }

// void SymbolTable::remove(Token name) { symbols.erase(name); }
