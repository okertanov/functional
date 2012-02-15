/**
    @file       Exception.h
    @brief      Cmd-line parser

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include "Platform.h"

namespace mowa0
{

class Exception :
    public std::exception
{
    public:
        Exception(const std::string& what) :
            what_(what)
        {
        }

        virtual ~Exception() throw()
        {
        }

        virtual const char * what() const throw()
        {
            return what_.c_str();
        }

    private:
        const std::string what_;
};

}

#endif // EXCEPTION_H_INCLUDED

