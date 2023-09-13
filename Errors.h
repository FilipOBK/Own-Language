#pragma once
#include <string>
#include "Position.h"
#include "Context.h"

class Error
{
protected:
    std::string errorName;
    std::string errorDetails;
    Position p_Start;
    Position p_End;

    std::string StringWithArrows(std::string text, Position pos_Start, Position pos_End);
public:
    Error(Position posStart, Position posEnd, std::string errName, std::string errDet);
    virtual std::string As_String();
};

class IllegalCharError : public Error
{
public:
    IllegalCharError(Position posStart, Position posEnd, std::string errDet);
};

class InvalidSyntaxError : public Error
{
public:
    InvalidSyntaxError(Position posStart, Position posEnd, std::string errDet);
};

class RuntimeError : public Error
{
public:
    std::shared_ptr<Context> context;
    RuntimeError(Position posStart, Position posEnd, std::string errDet, std::shared_ptr<Context> _context);

    std::string GenerateTraceback();
    std::string As_String() override;
};