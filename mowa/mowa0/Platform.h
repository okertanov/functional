/**
    @file       Platform.h
    @brief      Platform-dependent code & includes

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "Config.h"

#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <exception>
#include <algorithm>
#include <functional>

/**
    @brief quick-fix definitions, should be implemented
*/
#define ASSERT(E)               assert(E)
#define UNUSED(X)               (void)X
#define LOG(L, M)               LOG1(L, M)
#define LOG1(L, M)              do {std::cout << M << std::endl;} while(0)
#define LOG2(L, M, N)           do {std::cout << M << N << std::endl;} while(0)
#define LOG3(L, M, N, O)        do {std::cout << M << N << O << std::endl;} while(0)
#define LOG4(L, M, N, O, P)     do {std::cout << M << N << O << P << std::endl;} while(0)

namespace mowa0
{
}

#endif // PLATFORM_H_INCLUDED

