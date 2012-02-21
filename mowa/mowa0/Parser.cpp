/**
    @file       Parser.cpp
    @brief      The Syntax Parser implementation.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Parser.h"

namespace mowa0
{

Parser::Parser()
{
}

Parser::~Parser()
{
}

const SyntaxTree Parser::Parse(const Tokens& tokens)
{
    SyntaxTree ast;

    try
    {
        if ( !tokens.empty() )
        {
            for (const Token& token : tokens)
            {
                mowa0::String dump = mowa0::String(1, token.type_ + 32) + _T("->") + token.body_;
                LOG(LOG_DEBUG, dump);
            }
        }
    }
    catch(std::exception& e)
    {
        throw ParserException(e);
    }
    catch(...)
    {
        throw ParserException(WHERE);
    }

    return (ast);
}

}

