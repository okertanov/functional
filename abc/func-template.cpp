#include <iostream>

typedef int (*FuncType)(void* reserved);

extern int Do(void*);

template <typename F>
void DoVia(F f)
{
    f(0);
}

int Do(void*)
{
    return 1;
}

int main()
{
    DoVia<FuncType>(Do);

    return 0;
}

