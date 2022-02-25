#include "../e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_error(int res, char* msg) {
    if (res != -1) return;
    perror(msg);
    exit(EXIT_FAILURE);
}

void run(int* v, int n, int (*f)(int i)) {
    int i;
    for (i=0; i<n; ++i) {
        pid_t pid = fork();
        check_error(pid, "fork");
        if (pid == 0) {
            int res = f(i);
            _exit(res);
        }
    }
    for (i=0; i<n; ++i) {
        int status;
        pid_t pid = wait(&status);
        check_error(pid, "wait");
        if (WIFEXITED(status))
            v[i] = WEXITSTATUS(status);
    }
}
