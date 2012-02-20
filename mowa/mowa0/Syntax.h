/**
    @file       Syntax.h
    @brief      AST

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef SYNTAX_H_INCLUDED
#define SYNTAX_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @class mowa0::Syntax
    @brief Syntax class
*/
class Syntax
{
    public:
        Syntax();
        virtual ~Syntax();

    private:
};

/**
    @class mowa0::SyntaxException
    @brief SyntaxException class
*/
class SyntaxException :
    public mowa0::Exception
{
    public:
        explicit SyntaxException(std::exception& e) :
            Exception(e)
        {
        }

        explicit SyntaxException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~SyntaxException() throw()
        {
        }
};

}

#endif // SYNTAX_H_INCLUDED

