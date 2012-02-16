/**
    @file       Environment.h
    @brief      Evaluation environment. Holds scope, memory, stack.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @class mowa0::Environment
    @brief Environment class
*/
class Environment
{
    public:
        Environment();
        virtual ~Environment();

    private:
};

/**
    @class mowa0::EnvironmentException
    @brief Environment class
*/
class EnvironmentException :
    public mowa0::Exception
{
};

/**
    @var mowa0::global_environment
    @brief
*/
extern mowa0::Environment global_environment;

}

#endif // ENVIRONMENT_H_INCLUDED

