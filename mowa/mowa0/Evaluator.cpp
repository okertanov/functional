/**
    @file       Evaluator.cpp
    @brief      Eval implementation.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Evaluator.h"

namespace mowa0
{

Evaluator::Evaluator()
{
}

Evaluator::~Evaluator()
{
}

Environment Evaluator::Eval(const Syntax& ast, const Environment& env)
{
    mowa0::Environment res_env;

    UNUSED(ast), UNUSED(env);

    return res_env;
}

}

