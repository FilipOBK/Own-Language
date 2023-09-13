#include "Context.h"

Context::Context(const std::string _displayName, std::shared_ptr<Context> _parent, const Position _parEntryPos)
    : displayName(_displayName), parent(_parent), parentEntryPos(_parEntryPos)
{
}

Context::Context(const std::string _displayName, std::shared_ptr<Context> _parent)
    : displayName(_displayName), parent(_parent), parentEntryPos(Position())
{
}

Context::Context(const std::string _displayName)
    : displayName(_displayName), parent(nullptr), parentEntryPos(Position())
{
}

Context::Context()
    : displayName("Undefined context"), parent(nullptr), parentEntryPos(Position())
{
}