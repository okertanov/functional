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

    UNUSED(tokens);

    return (ast);
}

}

