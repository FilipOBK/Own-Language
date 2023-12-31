#include "RuntimeResult.h"

RuntimeResult::RuntimeResult()
    : value(nullptr), error(nullptr)
{
}

std::shared_ptr<Type> RuntimeResult::Register(RuntimeResult res)
{
    if(res.error) error = res.error;
    return res.value;
}

RuntimeResult RuntimeResult::Success(Type* _value)
{
    if(auto val = dynamic_cast<Number*>(_value))
        value = std::shared_ptr<Number>(val);
    return *this;
}

// ! This function is not required but then you gotta refactor all of Interpreter
RuntimeResult RuntimeResult::Success(Number _value)
{
    value = std::make_shared<Number>(_value);
    return *this;
}

RuntimeResult RuntimeResult::Failure(std::shared_ptr<Error> _error)
{
    error = _error;
    return *this;
}