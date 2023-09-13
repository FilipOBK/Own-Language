#include "Values.h"

NumberResult::NumberResult(Number _val, std::shared_ptr<Error> _error)
    : value(_val), error(_error)
{
}

Number::Number()
    : value(0)
{
    SetPos();
    SetContext();
}

Number::Number(int val)
    : value(val)
{
    SetPos();
    SetContext();
}

Number::Number(float val)
    : value(val)
{
    SetPos();
    SetContext();
}

void Number::SetPos(Position posStart, Position posEnd)
{
    pos_Start = posStart;
    pos_End = posEnd;
}

void Number::SetContext(std::shared_ptr<Context> _context)
{
    context = _context;
}

NumberResult Number::Added_to(Number other)
{
    if(value.index() == 0 && other.value.index() == 0)
    {
        int res = std::get<0>(value) + std::get<0>(other.value);
        Number result(res);
        result.SetContext(context);
        return NumberResult(result, nullptr);
    }

    float val1{};
    float val2{};

    if(float* ptr = std::get_if<float>(&value))
        val1 = *ptr;
    else val1 = static_cast<float>(std::get<0>(value));

    if(float* ptr = std::get_if<float>(&other.value))
        val2 = *ptr;
    else val2 = static_cast<float>(std::get<0>(other.value));

    float res = val1 + val2;
    Number result(res);
    result.SetContext(context);
    return NumberResult(result, nullptr);
}

NumberResult Number::Subbed_by(Number other)
{
    if(value.index() == 0 && other.value.index() == 0)
    {
        int res = std::get<0>(value) - std::get<0>(other.value);
        Number result(res);
        result.SetContext(context);
        return NumberResult(result, nullptr);
    }

    float val1{};
    float val2{};

    if(float* ptr = std::get_if<float>(&value))
        val1 = *ptr;
    else val1 = static_cast<float>(std::get<0>(value));

    if(float* ptr = std::get_if<float>(&other.value))
        val2 = *ptr;
    else val2 = static_cast<float>(std::get<0>(other.value));

    float res = val1 - val2;
    Number result(res);
    result.SetContext(context);
    return NumberResult(result, nullptr);
}

NumberResult Number::Multed_by(Number other)
{
    if(value.index() == 0 && other.value.index() == 0)
    {
        int res = std::get<0>(value) * std::get<0>(other.value);
        Number result(res);
        result.SetContext(context);
        return NumberResult(result, nullptr);
    }

        float val1{};
    float val2{};

    if(float* ptr = std::get_if<float>(&value))
        val1 = *ptr;
    else val1 = static_cast<float>(std::get<0>(value));

    if(float* ptr = std::get_if<float>(&other.value))
        val2 = *ptr;
    else val2 = static_cast<float>(std::get<0>(other.value));

    float res = val1 * val2;
    Number result(res);
    result.SetContext(context);
    return NumberResult(result, nullptr);
}

NumberResult Number::Dived_by(Number other)
{

    if(value.index() == 0 && other.value.index() == 0)
    {
        if(std::get<0>(other.value) == 0)
        {
            Number res;
            res.SetContext(context);
            return NumberResult(
                res,
                std::make_shared<RuntimeError>(other.pos_Start, other.pos_End, "Division by 0", context)
            );
        }

        int res = std::get<0>(value) / std::get<0>(other.value);
        Number result(res);
        result.SetContext(context);
        return NumberResult(result, nullptr);
    }

    float val1{};
    float val2{};

    if(float* ptr = std::get_if<float>(&value))
        val1 = *ptr;
    else val1 = static_cast<float>(std::get<0>(value));

    if(float* ptr = std::get_if<float>(&other.value))
        val2 = *ptr;
    else val2 = static_cast<float>(std::get<0>(other.value));
    if(val2 == 0)
    {
        return NumberResult(
            Number(),
            std::make_shared<RuntimeError>(other.pos_Start, other.pos_End, "Division by 0", context)
        );
    }

    float res = val1 / val2;
    Number result(res);
    result.SetContext(context);
    return NumberResult(result, nullptr);
}

NumberResult Number::Power_of(Number other)
{
    if(value.index() == 0 && other.value.index() == 0)
    {
        int res = std::pow(std::get<0>(value), std::get<0>(other.value));
        Number result(res);
        result.SetContext(context);
        return NumberResult(result, nullptr);
    }

    float val1{};
    float val2{};

    if(float* ptr = std::get_if<float>(&value))
        val1 = *ptr;
    else val1 = static_cast<float>(std::get<0>(value));

    if(float* ptr = std::get_if<float>(&other.value))
        val2 = *ptr;
    else val2 = static_cast<float>(std::get<0>(other.value));

    float res = std::pow(val1, val2);
    Number result(res);
    result.SetContext(context);
    return NumberResult(result, nullptr);
}

std::ostream &operator<<(std::ostream &os, const Number &num)
{
    if(num.value.index() == 0)
    {
        os << std::get<0>(num.value);
        return os;
    }
    os << std::get<1>(num.value);
    return os;
}