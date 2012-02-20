/**
    @file       Reader.cpp
    @brief      Reader implementation: recursive-descent parser.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Reader.h"

namespace mowa0
{

Reader::Reader() :
    file_(),
    chunk_()
{
    try
    {
    }
    catch(std::exception& e)
    {
        throw ReaderException(e);
    }
    catch(...)
    {
        throw ReaderException(WHERE);
    }
}

Reader::~Reader()
{
}

mowa0::Syntax Reader::Read(const mowa0::String& chunk)
{
    mowa0::Syntax ast;

    try
    {
        chunk_ = chunk;
    }
    catch(std::exception& e)
    {
        throw ReaderException(e);
    }
    catch(...)
    {
        throw ReaderException(WHERE);
    }

    return (ast);
}

mowa0::Syntax Reader::ReadFile(const mowa0::String& file)
{
    mowa0::Syntax ast;

    try
    {
        file_ = file;

        std::string file_ansi = WtoA(file_);

        std::wifstream ifs(file_ansi.c_str(), std::ios::in | std::ios::binary);

        if (!ifs || !ifs.is_open() || !ifs.good())
            throw ReaderException(WHERE, "Can't open file " + file_ansi);

        mowa0::String chunk;
        std::copy(std::istreambuf_iterator<wchar_t>(ifs), std::istreambuf_iterator<wchar_t>(),
                    std::back_inserter(chunk));
        ifs.close();

        Read(chunk);
    }
    catch(std::exception& e)
    {
        throw ReaderException(e);
    }
    catch(...)
    {
        throw ReaderException(WHERE);
    }

    return (ast);
}

}

