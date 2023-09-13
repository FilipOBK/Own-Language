#include "Parser.h"

Parser::Parser(std::vector<Token> toks)
    : tokens(toks), tok_Idx(-1), curr_Token(Token()) { Advance(); }

Token Parser::Advance()
{
    tok_Idx++;
    if(tok_Idx < tokens.size())
    {
        curr_Token = tokens[tok_Idx];
    }
    return curr_Token;
}

ParseResult Parser::Parse()
{
    ParseResult res = Expr();
    if(!res.error && curr_Token.type != TT::EoF)
    {
        std::shared_ptr<InvalidSyntaxError> err =
        std::make_shared<InvalidSyntaxError>(
            curr_Token.p_Start,
            curr_Token.p_End,
            "Expected '+', '-', '*', or '/'"
        );

        return res.Failure(err);
    }

    return res;
}

ParseResult Parser::Atom()
{
    ParseResult res;
    Token tok = curr_Token;

    if(tok.type == TT::INT || tok.type == TT::FLOAT)
    {
        res.Register(Advance());
        return res.Success(std::make_shared<NumberNode>(tok));
    }
    else if(tok.type == TT::IDENTIFIER)
    {
        res.Register(Advance());
        return res.Success(std::make_shared<VarAccessNode>(tok));
    }
    else if(tok.type == TT::LPAREN)
    {
        res.Register(Advance());
        std::shared_ptr<Node> expr = res.Register(Expr());
        
        if(res.error) return res;
        if(curr_Token.type == TT::RPAREN)
        {
            res.Register(Advance());
            return res.Success(expr);
        }
        else
        {
            std::shared_ptr<InvalidSyntaxError> err = 
                std::make_shared<InvalidSyntaxError>(curr_Token.p_Start, curr_Token.p_End, "Expected ')'");
            return res.Failure(err);
        }
    }

    std::shared_ptr<InvalidSyntaxError> err = 
        std::make_shared<InvalidSyntaxError>(curr_Token.p_Start, curr_Token.p_End, "Expected int, float, '+', '-', or '('");
    return res.Failure(err);
}

ParseResult Parser::Power()
{
    ParseResult res;
    std::shared_ptr<Node> left = res.Register(Atom());
    if(res.error) return res;

    while(curr_Token.type == TT::POW)
    {
        Token opToken = curr_Token;
        res.Register(Advance());
        std::shared_ptr<Node> right = res.Register(Factor());
        if(res.error) return res;
        left = std::make_shared<BinOpNode>(left, right, opToken);
    }
    return res.Success(left);
}

ParseResult Parser::Factor()
{
    ParseResult res;
    Token tok = curr_Token;

    if(tok.type == TT::PLUS || tok.type == TT::MINUS)
    {
        res.Register(Advance());
        std::shared_ptr<Node> factor = res.Register(Factor());
        
        if(res.error) return res;
        return res.Success(std::make_shared<UnOpNode>(tok, factor));
    }

    return Power();
}

ParseResult Parser::Term()
{
    ParseResult res;
    std::shared_ptr<Node> left = res.Register(Factor());
    if(res.error) return res;

    while(curr_Token.type == TT::MUL || curr_Token.type == TT::DIV)
    {
        Token opToken = curr_Token;
        res.Register(Advance());
        std::shared_ptr<Node> right = res.Register(Factor());
        if(res.error) return res;
        left = std::make_shared<BinOpNode>(left, right, opToken);
    }
    return res.Success(left);
}

ParseResult Parser::Expr()
{
    ParseResult res;
    
    if(curr_Token == Token(TT::KEYWORD, "VAR", Position()))
    {
        res.Register(Advance());
        if(res.error) return res;

        if(curr_Token.type != TT::IDENTIFIER)
        {
            std::shared_ptr<InvalidSyntaxError> err =
                std::make_shared<InvalidSyntaxError>(
                    curr_Token.p_Start, curr_Token.p_End,
                    "Expected Identifier"    
                );
            
            return res.Failure(err);
        }

        Token varName = curr_Token;
        res.Register(Advance());
        if(res.error) return res;

        if(curr_Token.type != TT::EQ)
        {
            std::shared_ptr<InvalidSyntaxError> err =
                std::make_shared<InvalidSyntaxError>(
                    curr_Token.p_Start, curr_Token.p_End,
                    "Expected '='"    
                );

            return res.Failure(err);
        }

        res.Register(Advance());
        if(res.error) return res;
        std::shared_ptr<Node> expr = res.Register(Expr());
        if(res.error) return res;
        return res.Success(std::make_shared<VarAssignNode>(varName, expr));
    }

    std::shared_ptr<Node> left = res.Register(Term());
    if(res.error) return res;

    while(curr_Token.type == TT::PLUS || curr_Token.type == TT::MINUS)
    {
        Token opToken = curr_Token;
        res.Register(Advance());
        std::shared_ptr<Node> right = res.Register(Term());
        if(res.error) return res;
        left = std::make_shared<BinOpNode>(left, right, opToken);
    }
    return res.Success(left);
}



ParseResult::ParseResult()
    : node(nullptr), error(nullptr)
{}

std::shared_ptr<Node> ParseResult::Register(ParseResult parseResult)
{
    if(parseResult.error) error = parseResult.error;
    return parseResult.node;
}

std::shared_ptr<Node> ParseResult::Register(std::shared_ptr<Node> p_Node)
{
    return p_Node;
}

std::shared_ptr<Node> ParseResult::Register(Token token)
{
    return std::make_shared<NumberNode>(token);
}

ParseResult ParseResult::Success(std::shared_ptr<Node> _node)
{
    node = _node;
    return *this;
}

ParseResult ParseResult::Failure(std::shared_ptr<Error> _err)
{
    error = _err;
    return *this;
}