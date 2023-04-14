#include <stdio.h>

// function declaration
void filecopy(FILE *, FILE *);

// cat:  concatenate files, version 1
// From The C Programming Language, Section 7.5
int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 1) { // no args; copy standard input
        filecopy(stdin, stdout);
    } else {
        for (int i = 1; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("cat: can't open %s\n", argv[i]);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}


/* filecopy:  copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}
