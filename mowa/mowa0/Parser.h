/**
    @file       Parser.h
    @brief      The Syntax LL(1) Parser: issued to convert Tokens -> Syntax tree

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "Platform.h"
#include "Exception.h"
#include "Tokens.h"
#include "SyntaxTree.h"

namespace mowa0
{

/**
    @class mowa0::Parser
    @brief Parser class
*/
class Parser
{
    public:
        Parser();
        virtual ~Parser();

        const SyntaxTree Parse(const Tokens& tokens);

    private:
};

/**
    @class mowa0::ParserException
    @brief ParserException class
*/
class ParserException :
    public mowa0::Exception
{
    public:
        explicit ParserException(const std::string& where, std::exception& e) :
            Exception(where, e)
        {
        }

        explicit ParserException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~ParserException() throw()
        {
        }
};

}

#endif // PARSER_H_INCLUDED

