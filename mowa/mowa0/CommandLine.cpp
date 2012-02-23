/**
    @file       Commandline.cpp
    @brief      Command-line parser implementation

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Commandline.h"

namespace mowa0
{

bool Commandline::CompareArguments::operator()(const Argument& a, const Argument& b) const
{
    return (a < b);
}

Commandline::Argument Commandline::options_prefix_short = _T("-");
Commandline::Argument Commandline::options_prefix_long  = _T("--");

Commandline::Commandline(int argc, char** argv, const Arguments& options) :
    parameters_()
{
    try
    {
        Parse(argc, argv, options);
    }
    catch(std::exception& e)
    {
        throw CommandlineException(WHERE, e);
    }
    catch(...)
    {
        throw CommandlineException(WHERE);
    }
}

Commandline::~Commandline()
{
}

Commandline::Argument Commandline::operator[](const Argument& key) const
{
    return parameters_[key];
}

void Commandline::Parse(int argc, char** argv, const Arguments& options)
{
    try
    {
        // Actually argv must not be empty, because the command-line arguments
        // specified by argc and argv include the name of the program as the first element
        // if argc is greater than 0.
        if ( argc < 1 || argv == NULL )
            throw CommandlineException(WHERE, "Nothing to Parse.");

        // Catch raw data and remove argv[0] aka the name of the program.
        // 1st ansi version: const Arguments commandline(argv + 1, argv + argc);
        Arguments commandline(argc - 1);
        std::transform(argv + 1, argv + argc, commandline.begin(),
                [](char*& item) -> Argument
                {
                    std::string tmp(item);
                    return Argument(tmp.begin(), tmp.end());
                }
        );

        // Check parameters validity thru valid arguments list.
        if ( !commandline.empty() && !options.empty() )
        {
            // Do not sort original arguments & options.
            Arguments mutable_commandline = commandline,
                      mutable_options     = options;

            // Further algorithm requires lists to be sorted.
            mutable_commandline.sort(CompareArguments()),
            mutable_options.sort(CompareArguments());

            // Filter just plain options with the delimiter like '-' or '--'.
            Arguments::iterator second_group_it =
                std::stable_partition(mutable_commandline.begin(), mutable_commandline.end(),
                    [&](const Argument& argument) -> bool
                    {
                        return ( std::equal(Commandline::options_prefix_short.begin(),
                                            Commandline::options_prefix_short.end(),
                                            argument.begin()) );
                    }
                );

            // The resulting set is to be copied here.
            // This should not overlap with either of the original ranges.
            Arguments difference;

            // The difference is formed by the elements that are present
            // in the first set, but not in the second.
            // @see also std::includes().
            std::set_difference(mutable_commandline.begin(), second_group_it,
                                mutable_options.begin(), mutable_options.end(),
                                std::back_inserter(difference));

            // Will be empty when arguments list is valid, and not empty otherwise.
            if ( !difference.empty() )
            {
                throw CommandlineException(WHERE, "Command line arguments are incorrect.");
            }
        }

        // Captured with the closure to be look-ahead key storage
        // for the value if it follows the key.
        // Empty key is also ok, it's used to capture values w/o parameters.
        Argument prev_key = Argument();

        // Cons Arguments list onto Parameters map.
        // Start over with original commandline list.
        parameters_ = std::accumulate(commandline.begin(), commandline.end(), parameters_,
            [&prev_key](Parameters& result, const Argument& item) -> Parameters
            {
                // Compare current item with the parameter's prefix to
                // distinguish arguments and their values.
                if ( std::equal(Commandline::options_prefix_short.begin(),
                                Commandline::options_prefix_short.end(),
                                item.begin()) )
                {
                    // When item is parameter's name, then store it without value,
                    // then overwrite and propogate current off this closure.
                    result[item] = Argument();
                    prev_key = item;
                }
                else
                {
                    // When item is value - push it to previous key as the value.
                    result[prev_key] = item;
                    prev_key.clear();
                }
                return (result);
            }
        );
    }
    catch(std::exception& e)
    {
        throw CommandlineException(WHERE, e);
    }
    catch(...)
    {
        throw CommandlineException(WHERE);
    }
}

}

