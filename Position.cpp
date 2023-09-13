#include "Position.h"

Position::Position(int _idx, int _ln, int _col, std::string _fn, std::string _ftxt)
    : idx(_idx), ln(_ln), col(_col), fn(_fn), ftxt(_ftxt)
{
}

Position::Position()
    : idx(-1), ln(-1), col(-1), fn("File not found"), ftxt("")
{
}

Position::~Position()
{
}

void Position::Advance(char currentChar)
{
    idx++;
    col++;

    if(currentChar == '\n')
    {
        ln++;
        col = 0;
    }
}