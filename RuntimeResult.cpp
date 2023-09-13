#include "RuntimeResult.h"

RuntimeResult::RuntimeResult()
    : value(Number()), error(nullptr)
{
}

Number RuntimeResult::Register(RuntimeResult res)
{
    if(res.error) error = res.error;
    return res.value;
}

RuntimeResult RuntimeResult::Success(Number _value)
{
    value = _value;
    return *this;
}

RuntimeResult RuntimeResult::Failure(std::shared_ptr<Error> _error)
{
    error = _error;
    return *this;
}