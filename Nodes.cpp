#include "Nodes.h"

// * Node
Node::~Node(){}

std::ostream &operator<<(std::ostream &os, Node &node)
{
    node.print(os);
    return os;
}


// * NumberNode
NumberNode::NumberNode(Token tok)
    : token(tok)
{
    p_Start = tok.p_Start;
    p_End = tok.p_End;
}

void NumberNode::print(std::ostream &os) const
{
    os << token;
}

// * VarAccessNode
VarAccessNode::VarAccessNode(Token _varNameToken)
    : varNameToken(_varNameToken)
{
    p_Start = _varNameToken.p_Start;
    p_End = _varNameToken.p_End;
}

void VarAccessNode::print(std::ostream &os) const
{
    os << varNameToken;
}

// * VarAssignNode
VarAssignNode::VarAssignNode(Token _varNameToken, std::shared_ptr<Node> _valueNode)
    : varNameToken(_varNameToken), valueNode(_valueNode)
{
    p_Start = _varNameToken.p_Start;
    p_End = _valueNode->p_End;
}

VarAssignNode::VarAssignNode(Token _varNameToken, Node *_valueNode)
    : varNameToken(_varNameToken)
{
    valueNode = std::shared_ptr<Node>(valueNode);
    p_Start = _varNameToken.p_Start;
    p_End = _valueNode->p_End;
}

void VarAssignNode::print(std::ostream &os) const
{
    os << "(" << varNameToken << ", ";
    valueNode->print(os);
    os << ")";
}

// * BinOpNode
BinOpNode::BinOpNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right, Token opTok)
    : leftNode(left), rightNode(right), opToken(opTok)
{
    p_Start = left->p_Start;
    p_End = right->p_End;   
}

void BinOpNode::print(std::ostream &os) const
{
    os << "(";
    leftNode->print(os);
    os << ", " << opToken << ", ";
    rightNode->print(os);
    os << ")";
}

UnOpNode::UnOpNode(Token _opToken, std::shared_ptr<Node> _node)
    : opToken(_opToken), node(_node)
{
    p_Start = _opToken.p_Start;
    p_End = _node->p_End;
}

void UnOpNode::print(std::ostream &os) const
{
    os << "(" << opToken << ", ";
    node->print(os);
    os << ")";
}

