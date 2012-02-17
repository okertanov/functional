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
        Reader(const mowa0::String& path);
        virtual ~Reader();

        mowa0::SyntaxTree Read();
        mowa0::SyntaxTree Read(const mowa0::String& chunk);

    private:
        const mowa0::String path_;
        const mowa0::String chunk_;
};

/**
    @class mowa0::ReaderException
    @brief ReaderException class
*/
class ReaderException :
    public mowa0::Exception
{
};


}

#endif // READER_H_INCLUDED

