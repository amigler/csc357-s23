#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int i = 357;
    int *p = &i;
    
    int i2 = 123;
    
    *p = *p + 10;

    p = &i2;  // change p to the location of i2
    
    
    printf("i = %d\n", *p);
    
    return EXIT_SUCCESS;
}
