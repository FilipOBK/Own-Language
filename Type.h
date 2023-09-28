#pragma once
#include <iostream>

struct Type
{
    virtual void print(std::ostream& os) = 0;
};