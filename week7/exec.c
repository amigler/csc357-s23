#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main(void) {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) { /* specify pathname, specify environment */
        if (execle("/home/ubuntu/csc357/csc357-s23/week7/echoall", "echoall", "arg1",
                   "MY ARG2", (char *)0, env_init) < 0) {
            printf("execle error");
        }
    }
    
    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error");
    }
        
    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) { /* specify filename, inherit environment */
        if (execlp("./echoall", "echoall", "just 1 arg", (char *) 0) < 0) {
            printf("execlp error");
        }
    }
    
    exit(0);
}
