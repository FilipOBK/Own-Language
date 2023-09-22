#pragma once
#include <variant>
#include <iostream>
#include <memory>
#include <cmath>
#include "Position.h"
#include "Errors.h"
#include "Context.h"

struct Type
{
    virtual void print(std::ostream& os) = 0;
};

struct NumberResult;

struct Number : public Type
{
    std::variant<int, float> value;
    Position pos_Start;
    Position pos_End;
    std::shared_ptr<Context> context;

    Number();
    Number(int val);
    Number(float val);

    void SetPos(Position posStart = Position(), Position posEnd = Position());
    void SetContext(std::shared_ptr<Context> _context = std::make_shared<Context>());
    
    NumberResult Added_to(Number other);
    NumberResult Subbed_by(Number other);
    NumberResult Multed_by(Number other);
    NumberResult Dived_by(Number other);
    NumberResult Power_of(Number other);

    void print(std::ostream& os) override;
};

struct NumberResult
{
    Number value;
    std::shared_ptr<Error> error;

    NumberResult(Number _val, std::shared_ptr<Error> _error);
};

std::ostream& operator<<(std::ostream& os, Type& num);