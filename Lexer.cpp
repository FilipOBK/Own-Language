#include "Lexer.h"

#define null '\0'

Lexer::Lexer(std::string _text, std::string fn)
    : text(_text), fileName(fn),
      pos(Position(-1, 0, -1, fn, text)), curr_char(null)
{
    Advance();
}

void Lexer::Advance()
{
    pos.Advance(curr_char);
    curr_char = pos.idx < text.size() ? text[pos.idx] : null;
}

std::variant<std::vector<Token>, std::shared_ptr<Error>> Lexer::MakeTokens()
{
    std::vector<Token> tokens;

    while(curr_char != null)
    {
        switch(curr_char)
        {
            case ' ':
                Advance();
                break;
            case '\t':
                Advance();
                break;

            case '+':
                tokens.push_back(Token(TT::PLUS, "+", pos));
                Advance();
                break;
            case '-':
                tokens.push_back(Token(TT::MINUS, "-", pos));
                Advance();
                break;
            case '*':
                tokens.push_back(Token(TT::MUL, "*", pos));
                Advance();
                break;
            case '/':
                tokens.push_back(Token(TT::DIV, "/", pos));
                Advance();
                break;
            case '(':
                tokens.push_back(Token(TT::LPAREN, "(", pos));
                Advance();
                break;
            case ')':
                tokens.push_back(Token(TT::RPAREN, ")", pos));
                Advance();
                break;
            case '=':
                tokens.push_back(Token(TT::EQ, "=", pos));
                Advance();
                break;
            case '^':
                tokens.push_back(Token(TT::POW, "^", pos));
                Advance();
                break;
            default:
            {
                if(isdigit(curr_char))
                    tokens.push_back(MakeNumber());
                else if(isascii(curr_char))
                {
                    tokens.push_back(MakeIdentifier());
                }
                else
                {
                    Position p_Start = pos;
                    std::string details = {'\'', curr_char, '\'', '\0'};
                    Advance();
                    return std::make_shared<IllegalCharError>(p_Start, pos, details);
                }
            }
        }
    }

    tokens.push_back(Token(TT::EoF, "eof", pos));
    return tokens;
}

Token Lexer::MakeNumber()
{
    Position startPos = pos;
    std::string numStr;
    bool dot;

    while(curr_char != null && (curr_char == '.' || isdigit(curr_char)))
    {
        if(curr_char == '.')
        {
            if(dot) break;
            dot = true;
            numStr.append(".");
        }
        else numStr.append(std::string(1, curr_char));

        Advance();
    }

    return Token(dot ? TT::FLOAT : TT::INT, numStr, startPos, pos);
}

Token Lexer::MakeIdentifier()
{
    std::string idStr = "";
    Position p_Start = pos;

    while(curr_char != null && (isalnum(curr_char) || curr_char == '_'))
    {
        idStr.append(std::string(1, curr_char));
        Advance();
    }

    TT type = std::find(KEYWORDS.begin(), KEYWORDS.end(), idStr) != KEYWORDS.end() ?
        TT::KEYWORD : TT::IDENTIFIER;
    return Token(type, idStr, p_Start, pos);
}