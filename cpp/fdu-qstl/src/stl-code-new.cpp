/*
    Oleg Kertanov (c) 2005
*/

#include <new>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "benchmark.h"

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)


void new_test()
{
    _();

    class A
    {
    public:
        A()  { _(); }
        ~A() { _(); }
    };

    A *a_ = new (std::nothrow) A;
    delete a_;

    A *a = (A*) operator new (sizeof (A));
    new (a) A;
    delete (a);
}

int main(int argc, char** argv)
{
    _();
    new_test();
    return EXIT_SUCCESS;
}

