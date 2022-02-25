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

void openFIFO() {
    fifo = open(FIFO_NAME, O_RDONLY);
    if(fifo == -1) handle_error("Errore open fifo");
}

static void closeFIFO() {

    /** [TO DO] Method to close and remove the FIFO
     *
     * - Close the fifo
     * - Destroy the fifo
     * */
    int ret = close(fifo);
    if(ret == -1) handle_error("Errore close fifo");
    ret = unlink(FIFO_NAME);
    if(ret == -1) handle_error("Errore unlink fifo");

}

int readValue(int * value) {

    int ret;

    /** [TO DO] READ THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can read from a FIFO as from a regular file descriptor
     * - In this case you have to receive an integer,
     *   hence you know its size
     * - repeat the read() when interrupted before reading any data
     * - return the number of bytes read
     * - reading 0 bytes means that the other process has closed
     *   the FIFO unexpectedly: this is an error that should be
     *   dealt with!
     **/
    int bytes_read = 0;
    while(bytes_read != sizeof(int)){
        ret = read(fifo, value, sizeof(int));
        if(ret == -1) handle_error("errore read");
        if(ret == 0){
            handle_error("errore read");
            fflush(stdout);
        }
        if (ret < sizeof(int)) handle_error("lettura parziale");
        bytes_read += ret;
    }
    return bytes_read;
}


void consume(int id, int numOps) {
    int localSum = 0;
    int value;
    while (numOps > 0) {

        /**
         * Complete the following code:
         * read the message from FIFO and update the producer position
         */


        readValue(&value);

        localSum += value;
        numOps--;
    }
    printf("Consumer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {

    openFIFO();

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

    closeFIFO();

    exit(EXIT_SUCCESS);
}
