#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int i = 357;
    int *p = &i;

    ++*p = *p + 10;
    
    printf("i = %d\n", *p);
    
    return EXIT_SUCCESS;
}
