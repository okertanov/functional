/**
    @file       CommandLine.cpp
    @brief      Command-line parser implementation

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "CommandLine.h"

namespace mowa0
{

CommandLine::CommandLine() :
    cmdline_()
{
}

CommandLine::CommandLine(int argc, char** argv) :
    cmdline_()
{
    UNUSED(argc), UNUSED(argv);
}

CommandLine::~CommandLine()
{
}

std::string CommandLine::operator[](const std::string& param)
{
    UNUSED(param);

    return std::string();
}

std::wstring CommandLine::operator[](const std::wstring& param)
{
    UNUSED(param);

    return std::wstring();
}

void CommandLine::Parse()
{
}

}

