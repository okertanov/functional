/*
    Oleg Kertanov (c) 2005
*/


#include <cstdlib>
#include <ciso646>
#include <string>
#include <iostream>

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)


void ciso646_definitions()
{
    _();

    bool b = 0;
    b and_eq not true or false;
    int  x = 1 bitor 2;

    std::cout << b << std::endl;
    std::cout << x << std::endl;
}

int main(int argc, char** argv)
{
    _();
    ciso646_definitions();

    return EXIT_SUCCESS;
}

