#include "common.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t *sem_filled, *sem_empty, *sem_cs;

void openSemaphores() {

    /* We have to open three named semaphores created in producer.c:
    * - sem_filled, used to check that our buffer is not empty
    * - sem_empty, used to check that our buffer is not full
    * - sem_cs, to avoid race conditions when accessing the file
    */

    sem_filled = sem_open(SEMNAME_FILLED, 0);
    if (sem_filled == SEM_FAILED) handle_error("sem_open filled");

    sem_empty = sem_open(SEMNAME_EMPTY, 0);
    if (sem_empty == SEM_FAILED) handle_error("sem_open empty");

    sem_cs = sem_open(SEMNAME_CS, 0);
    if (sem_cs == SEM_FAILED) handle_error("sem_open cs");
}

void closeAndDestroySemaphores() {
    /* When the program that controls the consumer(s) terminates, we need
     * to close the three semaphores and also delete (unlink) them. */

    int ret;

    ret = sem_close(sem_filled);
    if(ret != 0) handle_error("Error close sem_filled");

    ret = sem_close(sem_empty);
    if(ret != 0) handle_error("Error close sem_empty");

    ret = sem_close(sem_cs);
    if(ret != 0) handle_error("Error close sem_cs");

    ret = sem_unlink(SEMNAME_FILLED);
    if(ret != 0) handle_error("Error unlink sem_filled");

    ret = sem_unlink(SEMNAME_EMPTY);
    if(ret != 0) handle_error("Error unlink sem_empty");

    ret = sem_unlink(SEMNAME_CS);
    if(ret != 0) handle_error("Error unlink sem_cs");

}

void consume(int id, int numOps) {
    int localSum = 0;
    while (numOps > 0) {

        /* Before accessing the critical section and reading from the
         * buffer, we require that two conditions be verified:
        * - there is at least one value to read in the buffer
        * - access to the buffer is regulated via mutual exclusion
        * We can enforce the first condition by waiting on the sem_filled
        * semaphore, and the second by waiting on the sem_cs semaphore. */

        if(sem_wait(sem_filled) != 0) handle_error("Error sem_wait(sem_filled)");
        if(sem_wait(sem_cs) != 0) handle_error("Error sem_wait(sem_cs)");

        // CRITICAL SECTION
        int value = readFromBufferFile(BUFFER_SIZE, BUFFER_FILENAME);
        localSum += value;

        /* On leaving the critical section we have to "release" the
         * shared resource via sem_cs, and notify the producer(s) that a
         * cell in the buffer is now free using the semaphore sem_empty. */

        if(sem_post(sem_cs) != 0) handle_error("Error sem_post(sem_cs)");
        if(sem_post(sem_empty) != 0) handle_error("Error sem_post(sem_empty)");

        numOps--;
    }
    printf("Consumer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {
    if (access(BUFFER_FILENAME, F_OK) == -1) {
        printf("ERROR: no buffer file. Start the producer(s) first!\n");
        exit(EXIT_FAILURE);
    }

    openSemaphores();

    int i;
    for (i=0; i<NUM_CONSUMERS; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            handle_error("fork");
        } else if (pid == 0) {
            consume(i, OPS_PER_CONSUMER);
            _exit(EXIT_SUCCESS);
        }
    }

    for (i=0; i<NUM_CONSUMERS; ++i) {
        int status;
        wait(&status);
        if (WEXITSTATUS(status)) handle_error("child crashed");
    }

    printf("Consumers have terminated. Exiting...\n");

    closeAndDestroySemaphores();

    exit(EXIT_SUCCESS);
}
