#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {

    if (argc != 3) {
        fprintf(stderr, "usage: %s <cmd> <arg>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char * v = getenv("WAIT");
    if (v == NULL || (strcmp(v, "TRUE") != 0 && strcmp(v, "FALSE") != 0)) {
        fprintf(stderr, "Environment variable WAIT is not properly set. Aborting.\n");
        return EXIT_FAILURE;
    }

    pid_t p = fork();
    if (p == -1) {
        perror("errore nella fork");
        return EXIT_FAILURE;
    }

    if (p == 0) {
        execvp(argv[1], argv+1);
        perror("errore nella exec");
        _exit(EXIT_FAILURE);
    }

    if (strcmp(v, "TRUE") == 0) {
        int status;
        p = wait(&status);
        if (p == -1) {
            perror("errore nella wait");
            return EXIT_FAILURE;
        }

        return WEXITSTATUS(status);
    }

    return EXIT_SUCCESS;
}
