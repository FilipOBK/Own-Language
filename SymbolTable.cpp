#include "SymbolTable.h"

SymbolTable::SymbolTable()
    : parent(nullptr)
{

}

std::shared_ptr<Type> SymbolTable::get(Token name)
{
    std::shared_ptr<Type> value = nullptr;
    try
    {
        value = symbols.at(name);
    }
    catch(const std::exception& e) {}
    
    if(!value && parent) return parent->get(name);
    return value;
}

void SymbolTable::set(Token name, std::shared_ptr<Type> value)
{
    symbols[name] = value;
}

void SymbolTable::remove(Token name) { symbols.erase(name); }
