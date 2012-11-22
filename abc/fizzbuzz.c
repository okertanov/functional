/*
    http://www.codinghorror.com/blog/2007/02/why-cant-programmers-program.html

    Write a program that prints the numbers from 1 to 100.
    But for multiples of three print "Fizz" instead of the number and
    for the multiples of five print "Buzz".
    For numbers which are multiples of both three and five print "FizzBuzz".

    gcc -std=c99 -D_POSIX_SOURCE fizzbuzz.c -o fizzbuzz
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char snum[16] = {0};
    for (int i = 1; i <= 100; i++)
        snprintf(snum, 16, "%d", i) &&
            printf(
                "%s\n",
                (i % 3 == 0 &&
                 i % 5 == 0) ?
                    "FizzBuzz" :
                    (i % 3 == 0) ?
                        "Fizz" :
                        (i % 5 == 0) ?
                            "Buzz":
                             snum);
    return 0;
}

