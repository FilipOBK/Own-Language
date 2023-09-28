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
    std::cout << "Visiting NumNode\n";
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
    std::cout << "Visiting BinOpNode\n";
    RuntimeResult res;
    std::cout << "\tleft: " << *BinOpNode->leftNode << ",\n";
    std::cout << "\tright: " << *BinOpNode->rightNode << "\n";

    auto left = dynamic_cast<Number*>(res.Register(Visit(BinOpNode->leftNode, context)).get());
    if(!left) std::cout << "Error at VisitBinOpNode, leftNode does not resolve to a Number\n";
    if(res.error) return res;
    std::cout << "\tleft after cast: " << *left << "\n";

    // ! Error here, Visit returns a RuntimeResult with a value pointing to leftNode???
    auto right = dynamic_cast<Number*>(res.Register(Visit(BinOpNode->rightNode, context)).get());
    if(!right) std::cout << "Error at VisitBinOpNode, rightNode does not resolve to a Number\n";
    if(res.error) return res;
    std::cout << "\tright after cast: " << *right << "\n";

    std::cout << "\t--left after both casts: " << *left << "\n";
    std::cout << "Is left == right? " << (left == right ? "Yes" : "No") << std::endl;
    NumberResult numRes(Number(), nullptr);
    switch(BinOpNode->opToken.type)
    {
        case TT::PLUS:
            numRes = left->Added_to(*right);
            std::cout << "Adding " << *left << " to " << *right << std::endl;
            break;
        case TT::MINUS:
            numRes = left->Subbed_by(*right);
            std::cout << "Subbing " << *left << " to " << " right\n";
            break;
        case TT::MUL:
            numRes = left->Multed_by(*right);
            std::cout << "Multing " << *left << " to " << " right\n";
            break;
        case TT::DIV:
            numRes = left->Dived_by(*right);
            std::cout << "Diving " << *left << " to " << " right\n";
            break;
        case TT::POW:
            numRes = left->Power_of(*right);
            std::cout << "Adding " << *left << " to " << " right\n";
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
    std::cout << "Visiting UnOpNode\n";
    RuntimeResult res;
    auto num = dynamic_cast<Number*>(res.Register(Visit(unNode->node, context)).get());
    if(!num) std::cout << "Error at VisitUnOpNode\n";
    if(res.error) return res;

    NumberResult numRes(Number(), nullptr);

    if(unNode->opToken.type == TT::MINUS)
    {
        numRes = num->Multed_by(Number(-1));
        num = std::make_shared<Number>(numRes.value).get();
    }

    if(numRes.error) return res.Failure(numRes.error);

    num->SetPos(unNode->p_Start, unNode->p_End);
    return res.Success(num);
}

RuntimeResult Interpreter::VisitVarAccessNode(std::shared_ptr<VarAccessNode> accNode, std::shared_ptr<Context> context)
{
    std::cout << "Visiting VarAccessNode\n";
    RuntimeResult res;
    Token varName = accNode->varNameToken;
    std::shared_ptr<Type> value = context->symbols.get(varName);
    
    if(!value.get())
    {
        return res.Failure(
            std::make_shared<RuntimeError>(
                accNode->p_Start, accNode->p_End, std::string().append(varName.val).append(" is not defined"), context
            )
        );
    }

    return res.Success(value.get());
}

RuntimeResult Interpreter::VisitVarAssignNode(std::shared_ptr<VarAssignNode> assNode, std::shared_ptr<Context> context)
{
    std::cout << "Visiting VarAssignNode\n";
    RuntimeResult res;
    Token varName = assNode->varNameToken;
    auto value = res.Register(Visit(assNode->valueNode, context));
    return RuntimeResult(); // TEMP
}

RuntimeResult Interpreter::NoVisitMethod(std::shared_ptr<Node> node, std::shared_ptr<Context> context)
{
    std::cout << "No visit method found for " << *node << std::endl;
    return RuntimeResult().Failure(
        std::make_shared<RuntimeError>(node->p_Start, node->p_End, "No visit method found", context)
    );
}