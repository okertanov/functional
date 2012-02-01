#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *a = 1 ? (int *)0 : (void *)0;
    int *b = 1 ? (int *)0 : (void *)1;

    printf("\na = %x b = %x\n", a, b);
}
