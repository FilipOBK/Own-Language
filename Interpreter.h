#pragma once
#include <iostream>
#include "Nodes.h"
#include "Values.h"
#include "RuntimeResult.h"

struct Interpreter
{
    RuntimeResult Visit(std::shared_ptr<Node> node, std::shared_ptr<Context> context);

private:
    RuntimeResult VisitNumNode(std::shared_ptr<NumberNode> numNode, std::shared_ptr<Context> context);
    RuntimeResult VisitBinOpNode(std::shared_ptr<BinOpNode> binNode, std::shared_ptr<Context> context);
    RuntimeResult VisitUnOpNode(std::shared_ptr<UnOpNode> unNode, std::shared_ptr<Context> context);
    RuntimeResult VisitVarAccessNode(std::shared_ptr<VarAccessNode> accNode, std::shared_ptr<Context> context);
    RuntimeResult VisitVarAssignNode(std::shared_ptr<VarAssignNode> assNode, std::shared_ptr<Context> context);


    RuntimeResult NoVisitMethod(std::shared_ptr<Node> node, std::shared_ptr<Context> context);
};