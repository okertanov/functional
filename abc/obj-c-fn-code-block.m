//
// clang obj-c-fn-code-block.m -o obj-c-fn-code-block -framework Foundation
// clang obj-c-fn-code-block.c -o obj-c-fn-code-block
//

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#else
#include <math.h>
#include <stdio.h>
#endif

int main(int argc, char** argv) {
    double d = trunc(({
        double d = 1.5;
        d;
    }));

#ifdef __OBJC__
    NSLog(@"Truncated: %f", d);
#else
    printf("Truncated: %f\n", d);
#endif

    return 0;
}
