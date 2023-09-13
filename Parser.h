#pragma once
#include <vector>
#include "Token.h"
#include "Nodes.h"
#include "Errors.h"

struct ParseResult
{
    std::shared_ptr<Error> error;
    std::shared_ptr<Node> node;

    ParseResult();

    std::shared_ptr<Node> Register(ParseResult parseResult);
    std::shared_ptr<Node> Register(std::shared_ptr<Node> p_Node);
    std::shared_ptr<Node> Register(Token token);
    ParseResult Success(std::shared_ptr<Node> _node);
    ParseResult Failure(std::shared_ptr<Error> _err);
};

struct Parser
{
    std::vector<Token> tokens;
    int tok_Idx;
    Token curr_Token;

    Parser(std::vector<Token> toks);

    Token Advance();
    ParseResult Parse();

    ParseResult Atom();
    ParseResult Power();
    ParseResult Factor();
    ParseResult Term();
    ParseResult Expr();
};