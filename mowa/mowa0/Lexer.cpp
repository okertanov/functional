/**
    @file       Lexer.cpp
    @brief      Lexer implementation

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Lexer.h"

namespace mowa0
{

Lexer::Lexer() :
    chunk_(),
    tokens_()
{
}

Lexer::~Lexer()
{
}


Lexer& Lexer::Tokenize(const mowa0::String& chunk)
{
    chunk_ = chunk;

    return *this;
}

const Tokens& Lexer::GetTokens() const
{
    return tokens_;
}

}

