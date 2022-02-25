#include <unistd.h>     // fork, execvp
#include <stdio.h>      // fprintf, perror
#include <stdlib.h>     // exit
#include <sys/wait.h>   // wait

void exec(char* pathname, char* arg) {

    // fork new process
    pid_t pid = fork();

    if (pid == -1) {
        perror("cannot fork");
        exit(1);
    }

    // execute program pathname
    if (pid == 0) { // child
        char* args[] = { pathname, arg, NULL };
        execvp(pathname, args);
        perror("cannot exec");
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    int i, status;

    // check number of arguments
    if (argc < 3) {
        fprintf(stderr, "usage: pardo exec-file arg1 arg2 ... argn\n");
        exit(1);
    }

    // launch processes
    for (i=2; i<argc; i++)
        exec(argv[1], argv[i]);

    // wait for their termination
    for (i=2; i<argc; i++) {
        if (wait(&status) == -1) {
            perror("cannot wait");
            exit(1);
        }

        if (WEXITSTATUS(status) != 0)
            exit(WEXITSTATUS(status));
    }

    return 0;
}
