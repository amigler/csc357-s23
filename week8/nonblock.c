#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// nonblock.c
// read up to 500,000 bytes from the standard input and attempts to write it to the standard output

char buf[500000];

void set_fl(int fd, int flags)   // turn on specified file status flags
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("fcntl F_GETFL error");
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        printf("fcntl F_SETFL error");
    }
}

void clr_fl(int fd, int flags) // turn off specified file status flags
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("fcntl F_GETFL error");
    }

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        printf("fcntl F_SETFL error");
    }
}

int main(void)
{
    int ntowrite, nwrite;
    char* ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);  // enable nonblocking mode for STDOUT

    ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0)
        {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);  // clear nonblocking flag for STDOUT

    exit(0);
}
