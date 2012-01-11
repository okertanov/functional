#include <stdio.h>
#include <stdlib.h>
int main()
{
    static void *labels[] = { &&Label0, &&Label1, &&Label2, &&Label3 };
Label0:    printf("1. me at: %p\n", labels[0]);
Label1:    printf("2. me at: %p\n", labels[1]);
           printf("skipping: %p\n", labels[2]); goto *labels[3];
Label2:    printf("2. me at: %p\n", labels[2]);
Label3:    return(0);
}
