//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//std-terminate.cpp
//build: cl /EHsc std-terminate.cpp

#include <iostream>
#include <exception>

void std_terminate(void)
{
    std::cout << "Inside our std_terminate handler" << std::endl;
    //exit(-1); // <--- uncomment to fix
    //crt abort() ugly says that "This application has requested the
    //Runtime to terminate it in an unusual way."
}

int main()
{
    set_terminate(std_terminate);

    throw 0; //or std::terminate(); even is enough for that issue

    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

