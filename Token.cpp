#include "Token.h"

Token::Token(TT _type, std::string _val, Position posStart, Position posEnd)
    : type(_type), val(_val), p_Start(posStart), p_End(posEnd)
{}

Token::Token(TT _type, std::string _val, Position posStart)
    : type(_type), val(_val), p_Start(posStart), p_End(posStart)
{
    p_End.Advance(p_End.ftxt[p_End.idx]);
}

Token::Token()
    : type(TT::EMPTY)
{  
}

Token::~Token(){}

bool Token::operator==(const Token &other) const
{
    return other.type == type && other.val == val;
};

std::ostream& operator<<(std::ostream& os, const TT& tt)
{
    switch(tt)
    {
        case TT::INT:
            os << "INT";
            break;
        case TT::FLOAT:
            os << "FLOAT";
            break;
        case TT::KEYWORD:
            os << "KEYWORD";
            break;
        case TT::IDENTIFIER:
            os << "IDENTIFIER";
            break;
        case TT::PLUS:
            os << "PLUS";
            break;
        case TT::MINUS:
            os << "MINUS";
            break;
        case TT::MUL:
            os << "MUL";
            break;
        case TT::DIV:
            os << "DIV";
            break;
        case TT::LPAREN:
            os << "LPAREN";
            break;
        case TT::RPAREN:
            os << "RPAREN";
            break;
        case TT::POW:
            os << "POW";
            break;
        case TT::EQ:
            os << "EQ";
            break;
        case TT::EoF:
            os << "EoF";
            break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << token.type << ":" << token.val;
    return os;
}

size_t TokenHasher::operator()(const Token &tok) const
{
    size_t type_hash = std::hash<int>()(static_cast<int>(tok.type));
    size_t val_hash = std::hash<std::string>()(tok.val);

    return type_hash ^ (val_hash << 1);
}