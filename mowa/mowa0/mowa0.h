/**
    @file       mova0.h
    @brief      Main file for the Mowa Language interpreter.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef MOWA0_H_INCLUDED
#define MOWA0_H_INCLUDED

#include "Reader.h"
#include "Evaluator.h"
#include "Printer.h"
#include "Commandline.h"

/**
    @fn main()
    @brief Main entry point

    @param[in] argc - arguments count
    @param[in] argv - arguments vector
    @return EXIT_SUCCESS, EXIT_FAILURE
*/
extern int main(int argc, char** argv);

/**
    @fn usage()
    @brief Brief usage listing

    @return EXIT_SUCCESS, EXIT_FAILURE
*/
static void usage(const mowa0::Commandline::Arguments& args);

#endif // MOWA0_H_INCLUDED

