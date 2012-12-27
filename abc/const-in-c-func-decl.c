#include <stdlib.h>
#include <stdio.h>

// It's valid C
// What is "const" there?
// http://stackoverflow.com/questions/3693429/c-parameter-array-declarators
int fn(int x[const 10])
{
    return x[0];
}

int main()
{
    int a[10] = {1};

    printf("%x", fn(a));

    return 0;
}

