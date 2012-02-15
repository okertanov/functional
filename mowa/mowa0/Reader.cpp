/**
    @file       Reader.cpp
    @brief      Reader implementation.

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
    path_(),
    chunk_()
{
}

Reader::Reader(const std::string& path) :
    path_(std::wstring(path.begin(), path.end())),
    chunk_()
{
}

Reader::Reader(const std::wstring& path) :
    path_(path),
    chunk_()
{
}

Reader::~Reader()
{
}

mowa0::SyntaxTree Reader::Read()
{
    mowa0::SyntaxTree tree;

    return (tree);
}

mowa0::SyntaxTree Reader::Read(const std::string& chunk)
{
    mowa0::SyntaxTree tree;

    UNUSED(chunk);

    return (tree);
}

mowa0::SyntaxTree Reader::Read(const std::wstring& chunk)
{
    mowa0::SyntaxTree tree;

    UNUSED(chunk);

    return (tree);
}

}

