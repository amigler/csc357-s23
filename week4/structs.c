#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct char_int {
        char c;
        int i;
    };

    struct char_int s = { 'A', 4 };

    printf("s.c = %c\n", s.c);
    printf("s.i = %d\n", s.i);
    
    printf("sizeof(struct char_int) = %lu\n", sizeof(struct char_int));

    printf("&s = %p\n", &s);
    printf("&s.c = %p\n", &s.c);
    printf("&s.i = %p\n", &s.i);
    
    return EXIT_SUCCESS;
}
