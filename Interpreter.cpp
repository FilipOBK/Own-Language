#include "Interpreter.h"

RuntimeResult Interpreter::Visit(std::shared_ptr<Node> node, std::shared_ptr<Context> context)
{
    if(auto numNode = dynamic_cast<NumberNode*>(node.get()))
        return VisitNumNode(std::make_shared<NumberNode>(numNode->token), context);
    if(auto binNode = dynamic_cast<BinOpNode*>(node.get()))
        return VisitBinOpNode(std::make_shared<BinOpNode>(binNode->leftNode, binNode->rightNode, binNode->opToken), context);
    if(auto unNode = dynamic_cast<UnOpNode*>(node.get()))
        return VisitUnOpNode(std::make_shared<UnOpNode>(unNode->opToken, unNode->node), context);
    if(auto accNode = dynamic_cast<VarAccessNode*>(node.get()))
        return VisitVarAccessNode(std::make_shared<VarAccessNode>(accNode->varNameToken), context);
    if(auto assNode = dynamic_cast<VarAssignNode*>(node.get()))
        return VisitVarAccessNode(std::make_shared<VarAccessNode>(assNode->varNameToken), context);

    return NoVisitMethod(node, context);
}

RuntimeResult Interpreter::VisitNumNode(std::shared_ptr<NumberNode> numNode, std::shared_ptr<Context> context)
{
    Token& tok = numNode->token;
    Number res = 
        tok.type == TT::INT ? 
            Number(std::stoi(tok.val)) :
            Number(std::stof(tok.val));

    res.SetPos(numNode->p_Start, numNode->p_End);
    res.SetContext(context);
    return RuntimeResult().Success(res);
}

RuntimeResult Interpreter::VisitBinOpNode(std::shared_ptr<BinOpNode> BinOpNode, std::shared_ptr<Context> context)
{
    RuntimeResult res;
    Number left = res.Register(Visit(BinOpNode->leftNode, context));
    if(res.error) return res;
    Number right = res.Register(Visit(BinOpNode->rightNode, context));
    if(res.error) return res;

    NumberResult numRes(Number(), nullptr);
    switch(BinOpNode->opToken.type)
    {
        case TT::PLUS:
            numRes = left.Added_to(right);
            break;
        case TT::MINUS:
            numRes = left.Subbed_by(right);
            break;
        case TT::MUL:
            numRes = left.Multed_by(right);
            break;
        case TT::DIV:
            numRes = left.Dived_by(right);
            break;
        case TT::POW:
            numRes = left.Power_of(right);
            break;
        default:
            std::cout << "BinOpNode with invalid opToken: " << BinOpNode->opToken << std::endl;
    }

    if(numRes.error) return res.Failure(numRes.error);

    numRes.value.SetPos(BinOpNode->p_Start, BinOpNode->p_End);
    return res.Success(numRes.value);
}

RuntimeResult Interpreter::VisitUnOpNode(std::shared_ptr<UnOpNode> unNode, std::shared_ptr<Context> context)
{
    RuntimeResult res;
    Number num = res.Register(Visit(unNode->node, context));
    if(res.error) return res;

    NumberResult numRes(Number(), nullptr);

    if(unNode->opToken.type == TT::MINUS)
    {
        numRes = num.Multed_by(Number(-1));
        num = numRes.value;
    }

    if(numRes.error) return res.Failure(numRes.error);

    num.SetPos(unNode->p_Start, unNode->p_End);
    return res.Success(num);
}

RuntimeResult Interpreter::VisitVarAccessNode(std::shared_ptr<VarAccessNode> accNode, std::shared_ptr<Context> context)
{
    // RuntimeResult res;
    // Token varName = accNode->varNameToken;
    // std::shared_ptr<Node> value = std::shared_ptr<Node>(context->symbols.get(varName));
    
    // if(!value)
    // {
    //     return res.Failure(
    //         std::make_shared<Error>(
    //             accNode->p_Start, accNode->p_End, std::string().append(varName.val).append(" is not defined"), context
    //         )
    //     );
    // }

    // // TODO Redo res.success to take in any type of result
    return RuntimeResult();
}

RuntimeResult Interpreter::VisitVarAssignNode(std::shared_ptr<VarAssignNode> assNode, std::shared_ptr<Context> context)
{
    return RuntimeResult();
}

RuntimeResult Interpreter::NoVisitMethod(std::shared_ptr<Node> node, std::shared_ptr<Context> context)
{
    std::cout << "No visit method found for " << *node << std::endl;
    return RuntimeResult().Failure(
        std::make_shared<RuntimeError>(node->p_Start, node->p_End, "No visit method found", context)
    );
}