#include <stdio.h>

#define ABS1(a) (a < 0 ? -a : a)
#define ABS2(a) (a >= 0 ?: -a)

int main()
{
    int i1 = 0;
    int ai1 = ABS1(i1--);

    int i2 = 0;
    int ai2 = ABS2(i2--);

    printf("abs1 = %d, abs2 = %d\n", ai1, ai2);

    return 0;
}

