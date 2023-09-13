#pragma once
#include <iostream>
#include <memory>
#include "Token.h"

struct Node
{
    Position p_Start;
    Position p_End; 

    virtual ~Node() = 0;
    virtual void print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, Node& node);

struct NumberNode : public Node
{
    Token token;
    NumberNode(Token tok);

    void print(std::ostream& os) const override;
};

struct VarAccessNode : public Node
{
    Token varNameToken;
    
    VarAccessNode(Token _varNameToken);
    
    void print(std::ostream& os) const override;
};

struct VarAssignNode : public Node
{
    Token varNameToken;
    std::shared_ptr<Node> valueNode;

    VarAssignNode(Token _varNameToken, std::shared_ptr<Node> _valueNode);
    VarAssignNode(Token _varNameToken, Node* _valueNode);

    void print(std::ostream& os) const override;
};

struct BinOpNode : public Node
{
    std::shared_ptr<Node> leftNode;
    std::shared_ptr<Node> rightNode;
    Token opToken;

    BinOpNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right, Token opTok);

    void print(std::ostream& os) const override;
};

struct UnOpNode : public Node
{
    Token opToken;
    std::shared_ptr<Node> node;

    UnOpNode(Token _opToken, std::shared_ptr<Node> _node);

    void print(std::ostream& os) const override;
};