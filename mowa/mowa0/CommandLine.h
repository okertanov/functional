/**
    @file       CommandLine.h
    @brief      Command-line parser

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef COMMANDLINE_H_INCLUDED
#define COMMANDLINE_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @class mowa0::CommandLine
    @brief CommandLine class
*/
class CommandLine
{
    public:
        CommandLine();
        CommandLine(int argc, char** argv);
        virtual ~CommandLine();

        std::string operator[](const std::string& param);
        std::wstring operator[](const std::wstring& param);

    private:
        void Parse();

    private:
        const std::map<std::wstring, std::wstring> cmdline_;
};

/**
    @class mowa0::CommandLineException
    @brief CommandLineException class
*/
class CommandLineException :
    public mowa0::Exception
{
};

}

#endif // COMMANDLINE_H_INCLUDED

