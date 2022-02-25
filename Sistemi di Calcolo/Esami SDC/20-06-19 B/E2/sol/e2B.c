#include "../e2B.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void check_error(int res, char* msg) {
    if (res != -1) return;
    perror(msg);
    exit(EXIT_FAILURE);
}

void make_files(int n, void (*f)(int i, char name[64], char buf[256])) {
    int i;
    for (i=0; i<n; ++i) {
        pid_t pid = fork();
        check_error(pid, "fork");
        if (pid == 0) {
            char name[64];
            char buf[256];
            f(i, name, buf);
            int fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
            check_error(fd, "open");
            int res = write(fd, buf, 256);
            check_error(res, "write");
            res = close(fd);
            check_error(res, "close");
            _exit(0);
        }
    }
    for (i=0; i<n; ++i) {
        pid_t pid = wait(NULL);
        check_error(pid, "wait");
    }
}
