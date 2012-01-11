/*
    Oleg Kertanov (c) 2005
*/

#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "benchmark.h"

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)

char* reverse(const char *src)
{
    assert(src != 0);
    int len = strlen(src);
    char *dst  = new char[len + 1];
    assert(dst != 0);
    char *from = const_cast<char*>(&src[0]),
         *to = &dst[len - 1];
    while( (*(to--) = *(from++)) ) { }
    dst[len] = 0;
    return dst;
}

void rev_test()
{
    _();

    std::string orig = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::string reversed1("");
    std::string reversed2("");
    std::string reversed3("");

    {
        benchmark::timer::PerfTimer timer("Calibrate");
        #if defined(WIN32)
            Sleep(1000);
        #else
            sleep(1);
        #endif
    }

    {
        benchmark::timer::PerfTimer timer("std::copy");
        std::copy(orig.rbegin(), orig.rend(), std::back_inserter(reversed1));
    }
    std::cout << "reversed1: " << reversed1 << std::endl;

    {
        benchmark::timer::PerfTimer timer("std::reverse_copy");
        std::reverse_copy(orig.begin(), orig.end(), std::back_inserter(reversed2));
    }
    std::cout << "reversed2: " << reversed2 << std::endl;

    char *rs = 0;
    {
        benchmark::timer::PerfTimer timer("plain reverse");
        rs = reverse(orig.c_str());
    }
    std::cout << "reversed3: " << rs << std::endl;
    delete[] rs;
}

int main(int argc, char** argv)
{
    _();
    rev_test();
    return EXIT_SUCCESS;
}

