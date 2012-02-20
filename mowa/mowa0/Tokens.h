/**
    @file       Tokens.h
    @brief      AST

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @class mowa0::Tokens
    @brief Tokens class
*/
class Tokens
{
    public:
        Tokens();
        virtual ~Tokens();

    private:
};

/**
    @class mowa0::TokensException
    @brief TokensxException class
*/
class TokensException :
    public mowa0::Exception
{
    public:
        explicit TokensException(std::exception& e) :
            Exception(e)
        {
        }

        explicit TokensException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~TokensException() throw()
        {
        }
};

}

#endif // TOKENS_H_INCLUDED

