/**
    @file       Lexer.h
    @brief      Lexer part of the Parser: issued to convert Characters -> Tokens

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @class mowa0::Lexer
    @brief Lexer class
*/
class Lexer
{
    public:
        Lexer();
        Lexer(const std::wstring& chunk);
        virtual ~Lexer();

        void Scan();
        void Tokenize();

    private:
        const std::wstring chunk_;
};

/**
    @class mowa0::LexerException
    @brief LexerException class
*/
class LexerException :
    public mowa0::Exception
{
};

}

#endif // LEXER_H_INCLUDED

