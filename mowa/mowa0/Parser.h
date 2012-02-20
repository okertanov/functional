/**
    @file       Parser.h
    @brief      The Syntax Parser: issued to convert Tokens -> Syntax tree

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
};

}

#endif // PARSER_H_INCLUDED

