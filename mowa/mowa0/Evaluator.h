/**
    @file       Evaluator.h
    @brief      Eval part of REPL

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Platform.h"
#include "Exception.h"
#include "Syntax.h"
#include "Environment.h"

namespace mowa0
{

/**
    @class mowa0::Evaluator
    @brief Evaluator class
*/
class Evaluator
{
    public:
        Evaluator();
        virtual ~Evaluator();

        Environment Eval(const Syntax& ast, const Environment& env);

    private:
};

/**
    @class mowa0::EvaluatorException
    @brief EvaluatorException class
*/
class EvaluatorException :
    public mowa0::Exception
{
};

}

#endif // EVAL_H_INCLUDED

