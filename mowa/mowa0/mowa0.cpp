/**
    @file       mova0.cpp
    @brief      Main file for the Mowa Language interpreter.
                C++ Stage Zero is used to bootstrap itself.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "mowa0.h"

int main(int argc, char** argv)
{

{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}
{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}

    // Posix retcode
    int rc = EXIT_FAILURE;

    // Valid command-line Parameters are:
    static mowa0::Commandline::Arguments valid_arguments =
    {
        _T("--repl"),
        _T("--interpret"),
        _T("--compile"),
        _T("--source"),
        _T("--output"),
        _T("--help"),
        _T("--version")
    };

    try
    {
        // Parse parameters
        mowa0::Commandline parameters(argc, argv, valid_arguments);

        // Create source reader
        mowa0::Reader reader;

        // Read input and build AST
        mowa0::SyntaxTree ast = reader.ReadFile(parameters[_T("--source")]);

        // Evaluate AST using top-level Global environment and return new environment
        mowa0::Environment environment = mowa0::Evaluator().Eval(ast, mowa0::global_environment);

        // Everything is OK, returning 0 to the caller
        rc = EXIT_SUCCESS;
    }
    catch(mowa0::CommandlineException& e)
    {
        LOG(LOG_ERROR, e.what());

        usage(valid_arguments);
    }
    catch(mowa0::LexerException& e)
    {
        LOG(LOG_ERROR, e.what());
    }
    catch(mowa0::ParserException& e)
    {
        LOG(LOG_ERROR, e.what());
    }
    catch(std::exception& e)
    {
        LOG(LOG_ERROR, e.what());
    }
    catch(...)
    {
        LOG(LOG_ERROR, "Unknown error.");
    }

{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}
{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}

    return (rc);
}

static void usage(const mowa0::Commandline::Arguments& args)
{
    // Create prologue
    mowa0::String usagemsg(
        _T("\nUsage: \n")
        _T("\tmowa0 [parameters] [source file], where parameters are:\n")
    );

    ASSERT(args.size());

    // Construct the message
    usagemsg = std::accumulate(args.begin(), args.end(), usagemsg,
            [](mowa0::String& result, const mowa0::Commandline::Argument& item) -> mowa0::String
            {
                result.append(_T("\t\t")).append(item).append(_T("\n"));
                return (result);
            }
    );

    // Display the message
    LOG(LOG_STDOUT, usagemsg);
}

