#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {

    if (argc != 3) {
        fprintf(stderr, "usage: %s <cmd> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[2]);
    int i;

    for (i = 0; i < n; i++) {

        pid_t p = fork();
        if (p == -1) {
            perror("errore nella fork");
            return EXIT_FAILURE;
        }
    
        if (p == 0) {

            char arg[4];
            sprintf(arg, "%d", i);
            char * myargv[] = { argv[1], arg, NULL};
            printf("%s %s\n", myargv[0], myargv[1]);
            execvp(argv[1], myargv);
            perror("errore nella exec");
            _exit(EXIT_FAILURE);
        
        }
    }

    for (i = 0; i < n; i++) {

        int status;
        pid_t p = wait(&status);

        if (p == -1) {
            perror("errore nella wait");
            return EXIT_FAILURE;
        }

        if (WEXITSTATUS(status) != 0)
            return WEXITSTATUS(status);
    }

    return EXIT_SUCCESS;
}
