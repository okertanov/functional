/**
    @file       Reader.h
    @brief      Read part of REPL

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "Platform.h"
#include "Exception.h"
#include "SyntaxTree.h"
#include "Lexer.h"
#include "Parser.h"

namespace mowa0
{

/**
    @class mowa0::Reader
    @brief Reader class
*/
class Reader
{
    public:
        Reader();
        virtual ~Reader();

        mowa0::SyntaxTree Read(const mowa0::String& chunk);
        mowa0::SyntaxTree ReadFile(const mowa0::String& file);

    private:
        mowa0::String file_;
        mowa0::String chunk_;
};
/**
    @class mowa0::ReaderException
    @brief ReaderException class
*/
class ReaderException :
    public mowa0::Exception
{
    public:
        explicit ReaderException(std::exception& e) :
            Exception(e)
        {
        }

        explicit ReaderException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~ReaderException() throw()
        {
        }
};


}

#endif // READER_H_INCLUDED

