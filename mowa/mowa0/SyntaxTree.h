/**
    @file       SyntaxTree.h
    @brief      AST

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef SYNTAXTREE_H_INCLUDED
#define SYNTAXTREE_H_INCLUDED

#include "Platform.h"
#include "Exception.h"
#include "Lexer.h"

namespace mowa0
{

/**
    @brief Forward declarations
*/
class SyntaxNode;
class SyntaxTree;

/**
    @typedef mowa0::SyntaxNodePtr
    @brief
*/
typedef std::shared_ptr<SyntaxNode> SyntaxNodePtr;

/**
    @typedef mowa0::SyntaxNodeList
    @brief
*/
typedef std::list<SyntaxNodePtr> SyntaxNodeList;

/**
    @typedef mowa0::SyntaxNodeListPtr
    @brief
*/
typedef std::shared_ptr<SyntaxNodeList> SyntaxNodeListPtr;

/**
    @class mowa0::SyntaxNode
    @brief SyntaxNode class
*/
class SyntaxNode
{
    public:
        SyntaxNode();
        ~SyntaxNode();

        SyntaxNodeList& Children();

    private:
        Token token_; //TODO: subject to change
        SyntaxNodeListPtr children_;
};

/**
    @class mowa0::SyntaxTree
    @brief SyntaxTree class
*/
class SyntaxTree
{
    public:
        SyntaxTree();
        virtual ~SyntaxTree();

        SyntaxNode& Root();

    private:
        SyntaxNodePtr root_;
};

/**
    @class mowa0::SyntaxTreeException
    @brief SyntaxTreeException class
*/
class SyntaxTreeException :
    public mowa0::Exception
{
    public:
        explicit SyntaxTreeException(std::exception& e) :
            Exception(e)
        {
        }

        explicit SyntaxTreeException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~SyntaxTreeException() throw()
        {
        }
};

}

#endif // SYNTAXTREE_H_INCLUDED

