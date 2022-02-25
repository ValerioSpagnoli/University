#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "common.h"

// definizione struttura memoria
struct shared_memory {
    int buf [BUFFER_SIZE];
    int read_index;
    int write_index;
};

//definizione shared memory
struct shared_memory *myshm_ptr;
int fd_shm;

//definizione semafori named
sem_t *sem_empty, *sem_filled, *sem_cs;


void openMemory() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * Request shared memory to the kernel and map the shared memory in the shared_mem_ptr variable.
     **/

    fd_shm = shm_open(SH_MEM_NAME, O_RDWR, 0666);
    if(fd_shm == -1) handle_error("[openMemory] shm_open error");

    myshm_ptr = mmap(0, sizeof(struct shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if(myshm_ptr == MAP_FAILED) handle_error("[openMemory] mmap error");
    printf("openMemory completato\n");
}

void closeMemory() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * unmap the shared memory and close its descriptor
     **/

    if(munmap(myshm_ptr, sizeof(struct shared_memory)) == -1) handle_error("[closeMemory] munmap error");
    if(close(fd_shm) == -1) handle_error("[closeMemory] closing fd_shm error");
}



void openSemaphores() {
    sem_filled = sem_open(SEMNAME_FILLED, 0);
    if (sem_filled == SEM_FAILED) handle_error("sem_open filled");

    sem_empty = sem_open(SEMNAME_EMPTY, 0);
    if (sem_empty == SEM_FAILED) handle_error("sem_open empty");

    sem_cs = sem_open(SEMNAME_CS_CONS, O_CREAT | O_EXCL, 0600, 1);
    if (sem_cs == SEM_FAILED) handle_error("sem_open cs cons");
    printf("initSemaphores completato\n");
}

void closeAndDestroySemaphores() {
    int ret;

    // first close
    ret = sem_close(sem_filled);
    if (ret) handle_error("sem_close filled");

    ret = sem_close(sem_empty);
    if (ret) handle_error("sem_close empty");

    ret = sem_close(sem_cs);
    if (ret) handle_error("sem_close cs");

    // then unlink
    ret = sem_unlink(SEMNAME_FILLED);
    if (ret) handle_error("sem_unlink filled");

    ret = sem_unlink(SEMNAME_EMPTY);
    if (ret) handle_error("sem_unlink empty");

    ret = sem_unlink(SEMNAME_CS_PROD);
    if (ret) handle_error("sem_unlink cs prod");

    ret = sem_unlink(SEMNAME_CS_CONS);
    if (ret) handle_error("sem_unlink cs cons");

}

void consume(int id, int numOps) {
    int localSum = 0;
    while (numOps > 0) {
        int ret = sem_wait(sem_filled);
        if (ret) handle_error("sem_wait filled");

        ret = sem_wait(sem_cs);
        if (ret) handle_error("sem_wait cs");

        /**
         * Complete the following code:
         * read value from buffer inside the shared memory and update the consumer position
         */

        int value = myshm_ptr->buf[myshm_ptr->read_index];
        myshm_ptr->read_index++;
        if (myshm_ptr->read_index == BUFFER_SIZE) myshm_ptr->read_index = 0;

        ret = sem_post(sem_cs);
        if (ret) handle_error("sem_post cs");

        ret = sem_post(sem_empty);
        if (ret) handle_error("sem_post empty");

        localSum += value;
        numOps--;
    }
    printf("Consumer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {

    printf("openSemaphores\n");
    openSemaphores();
    printf("openMemory\n");
    openMemory();

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
    closeMemory();

    exit(EXIT_SUCCESS);
}
