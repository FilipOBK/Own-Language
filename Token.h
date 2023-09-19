#pragma once
#include <string>
#include <iostream>
#include "Position.h"

enum class TT
{
    INT,
    FLOAT,
    KEYWORD,
    IDENTIFIER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    POW,
    EQ,
    EoF,
    EMPTY
};

class Token
{
public:
    TT type;
    std::string val;
    Position p_Start;
    Position p_End;

    Token(TT type, std::string val, Position posStart, Position posEnd);
    Token(TT type, std::string val, Position posStart);
    Token();
    ~Token();

    bool operator==(const Token& other) const;
};

std::ostream& operator<<(std::ostream& os, const TT& tt);
std::ostream& operator<<(std::ostream& os, const Token& token);

struct TokenHasher
{
    size_t operator()(const Token& tok) const;
};