#include <stdlib.h>

int *array_copy(int a[], int size) {
    int i, *a2;
    
    a2 = malloc(size * sizeof(int));
    
    if (a2 == NULL) {
        return NULL;
    }
    
    for (i = 0; i < size; i++) {
        a2[i] = a[i];
    }
    
    return a2;
}

int main(int argc, char *argv[]) {
    int the_array[3] = { 3, 5, 7 };
    
    int *the_copy = array_copy(the_array, 3);
    
    // use the copied array
    
    free(the_copy);
    
    return EXIT_SUCCESS;
}
