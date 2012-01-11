/*
    Oleg Kertanov (c) 2005
*/

#include <cstdlib>
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <stack>
#include <queue>

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)

void stack_adaptor()
{
    _();
}

void queue_adaptor()
{
    _();
}

void priority_queue_adaptor()
{
    _();
}

int main(int argc, char** argv)
{
    _();

    stack_adaptor();
    queue_adaptor();
    priority_queue_adaptor();

    return EXIT_SUCCESS;
}

