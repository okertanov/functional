//
// Did you know? This is valid C: void f(int[*]);
//
// Oh, here's the difference:
//
// int f(int[][]) is not valid, but int f(int[*][*]) is.
//
// For a one-dimensional array, [] and [*] are equivalent.
//
// /via @comex
//

int func(int a[8][8])
{
    return 42;
}

int main(int argc, char** argv)
{
    int (*f)(int m[*][*]) = func;

    return f(0);
}

