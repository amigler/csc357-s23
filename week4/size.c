#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    struct s {
        int i;
        char c, c2, c3, c4;
        long l;
    };

    printf("sizeof(struct s) = %lu\n", sizeof(struct s));

    printf("sizeof(char) = %lu\n", sizeof(char));
    printf("sizeof(int) = %lu\n", sizeof(int));
    printf("sizeof(long) = %lu\n", sizeof(long));
    
    return EXIT_SUCCESS;
}
