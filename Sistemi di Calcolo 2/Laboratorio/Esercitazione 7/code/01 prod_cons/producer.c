#define _GNU_SOURCE
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

//definizione semafori named
int fifo;

void initFIFO() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * Request the kernel to create a FIFO and open it
     **/
    int ret;
    unlink(FIFO_NAME);
    ret = mkfifo(FIFO_NAME, 0666);
    if(ret == -1) handle_error("Errore mkfifo");
    fifo = open(FIFO_NAME, O_WRONLY);
    if(fifo == -1) handle_error("Errore open fifo");
    fcntl(fifo, F_SETPIPE_SZ, 10*sizeof(int));
}

static void closeFIFO() {

    /** [TO DO] Method to close and remove the FIFO
     *
     * - Close the fifo
     * */
    int ret = close(fifo);
    if(ret == -1) handle_error("Errore close fifo");
}




// generates a number between -MAX_TRANSACTION and +MAX_TRANSACTION
static inline int performRandomTransaction() {
    struct timespec pause = {0};
    pause.tv_nsec = 10000000; // 10 ms (100*10^6 ns)
    nanosleep(&pause, NULL);

    int amount = rand() % (2 * MAX_TRANSACTION); // {0, ..., 2*MAX_TRANSACTION - 1}
    if (amount >= MAX_TRANSACTION) {
        return MAX_TRANSACTION - (amount+1); // {-MAX_TRANSACTION, ..., -1}
    } else {
        return amount + 1; // {1, ..., MAX_TRANSACTION}
    }
}

int writeValue(int value) {

    int ret = 0;
    /** [TO DO] SEND THE VALUE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can write on the FIFO as on a regular file descriptor
     * - make sure that all the bytes have been written: use a while
     *   cycle in the implementation as we did for file descriptors!
     **/
    int bytes_sent = 0;
    while(bytes_sent != sizeof(int)){
        ret = write(fifo, &value, sizeof(int));
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("errore write");
        if (ret != sizeof(int)) handle_error("scrittura parziale");
        bytes_sent = ret;
    }
    return bytes_sent;
}

void produce(int id, int numOps) {
    int localSum = 0;
    while (numOps > 0) {
        // producer, just do your thing!
        int value = performRandomTransaction();

        // SEND THE VALUE THROUGH THE FIFO DESCRIPTOR
        writeValue(value);

        localSum += value;
        numOps--;
    }
    printf("Producer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {
    srand(PRNG_SEED);
    initFIFO();

    int i, ret;
    for (i=0; i<NUM_PRODUCERS; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            handle_error("fork");
        } else if (pid == 0) {
            produce(i, OPS_PER_PRODUCER);
            _exit(EXIT_SUCCESS);
        }
    }

    for (i=0; i<NUM_PRODUCERS; ++i) {
        int status;
        ret = wait(&status);
        if (ret == -1) handle_error("wait");
        if (WEXITSTATUS(status)) handle_error_en(WEXITSTATUS(status), "child crashed");
    }

    printf("Producers have terminated. Exiting...\n");
    closeFIFO();

    exit(EXIT_SUCCESS);
}

