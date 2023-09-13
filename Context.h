#pragma once
#include <string>
#include <memory>
#include "Position.h"
#include "SymbolTable.h"

struct Context
{
    std::string displayName;
    std::shared_ptr<Context> parent;
    Position parentEntryPos;
    // SymbolTable symbols;

    Context(const std::string _displayName, std::shared_ptr<Context> const _parent, const Position _parEntryPos);
    Context(const std::string _displayName, std::shared_ptr<Context> const _parent);
    Context(const std::string _displayName);
    Context();
};