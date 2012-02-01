#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

__attribute__((noreturn))
void sigfpe(int sn)
{
    exit(0);
}

__attribute__((constructor))
void init()
{
    signal(SIGFPE, sigfpe);
}

int main(int argc)
{
    printf("%d \n", argc++, (argc/(argc%1001)));
    return main(argc);
}

