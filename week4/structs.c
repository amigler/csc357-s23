#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /*
    struct char_int {
        char c;
        int i;
    };

    struct char_int s = { 'A', 4 };

    struct char_int s2 = s;

    s2.c = 'B';
    
    printf("s.c = %c\n", s.c);
    printf("s.i = %d\n", s.i);
    printf("s2.c = %c\n", s2.c);
    printf("s2.i = %d\n", s2.i);
    
    printf("sizeof(struct char_int) = %lu\n", sizeof(struct char_int));

    printf("&s = %p\n", &s);
    printf("&s.c = %p\n", &s.c);
    printf("&s.i = %p\n", &s.i);

    printf("&s2 = %p\n", &s2);
    printf("&s2.c = %p\n", &s2.c);
    printf("&s2.i = %p\n", &s2.i);

*/    

    struct int_string {
        int i;
        char *s;
    };

    struct int_string is = { 1, "hello" };
    
    printf("is.i = %i\n", is.i);
    printf("is.s = %s\n", is.s);

    struct int_string is2 = is;

    printf("is2.i = %i\n", is2.i);
    printf("is2.s = %s\n", is2.s);

    printf("is.s = %p\n", (is.s));
    printf("is2.s = %p\n", (is2.s));
    
    return EXIT_SUCCESS;
}
