/*/true
outname=${0%.*}
cc $0 -o ./outname && ./outname && rm -f ./outname ./outname.exe
exit 0
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    printf("Hello, World!\n");

    return 0;
}

