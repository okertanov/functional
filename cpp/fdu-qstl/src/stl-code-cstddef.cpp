/*
    Oleg Kertanov (c) 2005
*/


#include <cstdlib>
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)

int main(int argc, char** argv);

void cstddef_definitions()
{
    _();

    int *a = reinterpret_cast<int*>(&cstddef_definitions);
    int *b = reinterpret_cast<int*>(&main);
    ptrdiff_t addrdiff = b - a;
    size_t    addrsize = sizeof (&main);

    //                       0         4            8         16
    struct offstruct {size_t a; size_t b; long long c; size_t d;} ostruct;
    ostruct.a = offsetof(offstruct, a);
    ostruct.b = offsetof(offstruct, b);
    ostruct.c = offsetof(offstruct, c);
    ostruct.d = offsetof(offstruct, d);

    std::cout << std::setw(16) << std::left << std::hex << addrdiff 
              << std::setw(16) << std::left << std::dec << addrsize 
              << std::endl;
    std::cout << std::setw(16) << std::left << ostruct.a 
              << std::setw(16) << std::left << ostruct.b 
              << std::setw(16) << std::left << ostruct.c 
              << std::setw(16) << std::left << ostruct.d
              << std::endl;
}

int main(int argc, char** argv)
{
    _();
    cstddef_definitions();

    return EXIT_SUCCESS;
}

