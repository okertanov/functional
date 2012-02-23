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

SyntaxNode::SyntaxNode() try :
    token_(),
    children_(std::make_shared<SyntaxNodeList>())
{
}
catch(std::exception& e)
{
    throw SyntaxTreeException(WHERE, e);
}
catch(...)
{
    throw SyntaxTreeException(WHERE);
}

SyntaxNode::~SyntaxNode()
{
}

SyntaxNodeList& SyntaxNode::Children()
{
    return (*children_);
}

SyntaxTree::SyntaxTree() try :
    root_(std::make_shared<SyntaxNode>())
{
}
catch(std::exception& e)
{
    throw SyntaxTreeException(WHERE, e);
}
catch(...)
{
    throw SyntaxTreeException(WHERE);
}

SyntaxTree::~SyntaxTree()
{
}

SyntaxNode& SyntaxTree::Root()
{
    return (*root_);
}

}

