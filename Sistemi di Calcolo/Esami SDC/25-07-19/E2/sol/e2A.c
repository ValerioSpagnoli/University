#include "../e2A.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void check_error(int res, char* msg) {
    if (res != -1) return;
    perror(msg);
    exit(EXIT_FAILURE);
}

int contains(char* s, char c, int n) {
    int len = strlen(s), i, m = len/n, found = 0;
    for (i=0; i<n; ++i) {
        int from = i*m;
        int to = (i+1)*m;
        pid_t pid = fork();
        check_error(pid, "fork");
        if (pid == 0) {
            for (i=from; i<to; ++i)
                if (s[i] == c) found = 1;
            _exit(found);
        }
    }
    for (i = n*m; i < len; ++i)
        if (s[i] == c) found = 1;
    for (i=0; i<n; ++i) {
        int status;
        pid_t pid = wait(&status);
        check_error(pid, "wait");
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
            found = 1;
    }
    return found;
}
