#pragma once
#include <memory>

#include "Values.h"
#include "Errors.h"

struct RuntimeResult
{
    // TODO check that the Type pointer works
    std::shared_ptr<Type> value;
    std::shared_ptr<Error> error;

    RuntimeResult();

    Number Register(RuntimeResult res);
    RuntimeResult Success(Type* _value);
    RuntimeResult Success(Number _value);
    RuntimeResult Failure(std::shared_ptr<Error> _error);
};