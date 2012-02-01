#
#include <stdio.h>
#

/*
One common, useful use of self-reference is to create a macro which expands to itself. If you write 
#define EPERM EPERM
then the macro EPERM expands to EPERM. Effectively, it is left alone by the preprocessor whenever it's used in running text.
You can tell that it's a macro with `#ifdef'. You might do this if you want to define numeric constants with an enum, but have `#ifdef' be true for each constant.
*/
#define EPERM EPERM

#define STRINGIFY(P) #P

#define min(X, Y)                \
     ({ typeof (X) x_ = (X);     \
        typeof (Y) y_ = (Y);     \
        (x_ < y_) ? x_ : y_;     \
      })


#pragma GCC poison fprintf
_Pragma("GCC poison fprintf")

void f()
{
    void f() {return;};
    f();
}

void main()
{
    typedef typeof(1) T;
    T t = 1;

    int $a = -1;
    int a = __COUNTER__;
    int b = __COUNTER__;
    const char *v = __VERSION__;
    const char *m = __TIMESTAMP__;
    const char *n = STRINGIFY(42);
    printf("v = %s, m = %s, n = %s, a = %d, b = %d, $a = %d\n", v, m, n, a, b, $a);
    f();
}
