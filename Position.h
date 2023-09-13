#pragma once
#include <string>

struct Position
{
    int idx;
    int ln;
    int col;
    std::string fn;
    std::string ftxt;
    Position(int idx, int ln, int col, std::string fn, std::string ftxt);
    Position();
    ~Position();

    void Advance(char currentChar);
};