#include <stdio.h>

void hello() {
    printf("Hello from the encrypted dynamic library!\n");
    for(int i = 0; i < 5; ++i)
        printf("%d_", i);
    printf("\n");
}