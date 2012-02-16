/**
    @file       Commandline.h
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
    @class mowa0::Commandline
    @brief Commandline class
*/
class Commandline
{
    public:
        /**
            @typedef mowa0::Commandline::Value
            @brief
        */
        typedef std::string Value;

        /**
            @typedef mowa0::Commandline::Argument
            @brief
        */
        typedef std::string Argument;

        /**
            @typedef mowa0::Commandline::Arguments
            @brief
        */
        typedef std::list<Argument> Arguments;

        /**
            @typedef mowa0::Commandline::Parameters
            @brief
        */
        typedef std::map<Argument, Value> Parameters;

        /**
            @class mowa0::Commandline::CompareArguments
            @brief CompareArguments functor
        */
        class CompareArguments
        {
            public:
                bool operator()(const Argument& a, const Argument& b) const;
        };

        /**
            @var mowa0::Commandline::options_prefix_short
            @brief
        */
        static Argument options_prefix_short;

        /**
            @var mowa0::Commandline::options_prefix_long
            @brief
        */
        static Argument options_prefix_long;

    public:
        Commandline(int argc, char** argv, const Arguments& options);
        virtual ~Commandline();

        std::string operator[](const Argument& key) const;

    private:
        void Parse(int argc, char** argv, const Arguments& options);

    private:
        mutable Parameters parameters_;
};

/**
    @class mowa0::CommandlineException
    @brief CommandlineException class
*/
class CommandlineException :
    public mowa0::Exception
{
    public:
        explicit CommandlineException(std::exception& e) :
            Exception(e)
        {
        }

        explicit CommandlineException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~CommandlineException() throw()
        {
        }
};

}

#endif // COMMANDLINE_H_INCLUDED

