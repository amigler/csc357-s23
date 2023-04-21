#include <stdio.h>

void read_ints(FILE *fp) {
    int oc = 0, i = 0;
    while ((oc = fread(&i, sizeof(int), 1, fp)) == 1) {
        printf("%d\n", i);
    }
}
