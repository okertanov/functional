/**
    @file       Lexer.h
    @brief      Lexer for the context-free grammars.
                The part of the LL(1) Parser: issued to convert Characters -> Tokens

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
#include "Tokens.h"

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
        virtual ~Lexer();

        Lexer& Tokenize(const mowa0::String& chunk);

        const Tokens& GetTokens() const;

    private:
        mowa0::String chunk_;
        Tokens tokens_;
};

/**
    @class mowa0::LexerException
    @brief LexerException class
*/
class LexerException :
    public mowa0::Exception
{
    public:
        explicit LexerException(std::exception& e) :
            Exception(e)
        {
        }

        explicit LexerException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~LexerException() throw()
        {
        }
};

}

#endif // LEXER_H_INCLUDED

