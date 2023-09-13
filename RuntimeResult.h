#pragma once
#include <memory>

#include "Values.h"
#include "Errors.h"

struct RuntimeResult
{
    // TODO see if can change value from Number to Node*
    Number value;
    std::shared_ptr<Error> error;

    RuntimeResult();

    Number Register(RuntimeResult res);
    RuntimeResult Success(Number _value);
    RuntimeResult Failure(std::shared_ptr<Error> _error);
};