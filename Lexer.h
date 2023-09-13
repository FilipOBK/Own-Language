#pragma once
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "Token.h"
#include "Errors.h"
#include "Position.h"

const std::vector<std::string> KEYWORDS {
  "VAR"  
};

class Lexer
{
public:
    std::string text;
    std::string fileName;
    Position pos;
    char curr_char;

    Lexer(std::string text, std::string fn);

    void Advance();
    std::variant<std::vector<Token>, std::shared_ptr<Error>> MakeTokens();
    Token MakeNumber();
    Token MakeIdentifier();

};