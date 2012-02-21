/**
    @file       SyntaxTree.cpp
    @brief      AST implementation.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "SyntaxTree.h"

namespace mowa0
{

SyntaxNode::SyntaxNode() :
    token_(),
    children_(std::make_shared<SyntaxNodeList>())
{
}

SyntaxNode::~SyntaxNode()
{
}

SyntaxNodeList& SyntaxNode::Children()
{
    return (*children_);
}

SyntaxTree::SyntaxTree() :
    root_(std::make_shared<SyntaxNode>())
{
}

SyntaxTree::~SyntaxTree()
{
}

SyntaxNode& SyntaxTree::Root()
{
    return (*root_);
}

}

