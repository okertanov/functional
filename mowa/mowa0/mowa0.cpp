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

#include "Reader.h"
#include "Evaluator.h"
#include "Printer.h"
#include "CommandLine.h"

/**
    @fn usage()
    @brief Brief usage listing

    @return EXIT_SUCCESS, EXIT_FAILURE
*/
void usage(const std::list<std::string>& args)
{
    // Create prologue
    std::string usagemsg(
        "\nUsage: \n"
        "\tmowa0 [parameters] [source file], where parameters are:\n"
    );

    ASSERT(args.size());

    // Construct the message
    usagemsg = std::accumulate(args.begin(), args.end(), usagemsg,
            [](std::string& result, const std::string& item) -> std::string
            {
                result.append("\t\t").append(item).append("\n");
                return (result);
            }
    );

    // Display the message
    LOG(LOG_STDOUT, usagemsg);
}

/**
    @fn main()
    @brief Main entry point

    @param[in] argc - arguments count
    @param[in] argv - arguments vector
    @return EXIT_SUCCESS, EXIT_FAILURE
*/
int main(int argc, char** argv)
{
    int rc = EXIT_FAILURE;

    try
    {
        // Parse parameters
        mowa0::CommandLine parameters(argc, argv);

        // Valid command-line Parameters are:
        static std::list<std::string> valid_arguments = {
                    "--compile",
                    "--interpret",
                    "--repl",
                    "--source",
                    "--output",
                    "--help",
                    "--version"
        };

        usage(valid_arguments);

        // Create source reader
        mowa0::Reader reader(parameters["source"]);

        // Read input and build AST
        mowa0::SyntaxTree tree = reader.Read();

        // Evaluate AST using top-level Global environment and return new environment
        mowa0::Environment environment = mowa0::Evaluator().Eval(tree, mowa0::GlobalEnvironment);

        // Everything is OK, returning 0 to the caller
        rc = EXIT_SUCCESS;
    }
    catch(mowa0::CommandLineException& e)
    {
        LOG(LOG_ERROR, e.what());
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

    return (rc);
}

