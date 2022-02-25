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
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * Request the kernel to create a FIFO and open it
     **/

    fifo = open(FIFO_NAME, O_RDONLY);
    if(fifo == -1) handle_error("Cannot open FIFO for writing");

}

static void closeFIFO() {

    /** [TO DO] Method to close and remove the FIFO
     *
     * - Close the fifo
     * - Destroy the fifo
     * */

    // close the descriptors
    int ret = close(fifo);
    if(ret) handle_error("Cannot close FIFO");

    // destroy the FIFO
    ret = unlink(FIFO_NAME);
    if(ret) handle_error("Cannot unlink FIFO");
}

int readValue(int * value) {

    int ret;

    /** [SOLUTION] READ THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - We assume that the read of a small amount of bytes cannot
     *   be interrupted in the mid of the operation or we have only a reader. 
     *   Otherwise we should introduce all the controls for partial reads and
     *   need sincronization mechanism for multiple readers.
     * - You can read from a FIFO as from a regular file descriptor.
     * - Since you know the length of the message, just
     *   read the correct size in a time from the socket
     * - repeat the read() when interrupted before reading any data
     * - return the number of bytes read
     * - reading 0 bytes means that the other process has closed
     *   the FIFO unexpectedly: this is an error that should be
     *   dealt with!
     * - reading less bytes than the message size involve a possible interleaving
     *   problem between multiple readers. I suggest to abort
     **/
    int bytes_read = 0;
    do {
        ret = read(fifo, value, sizeof(int));
        if (ret == -1 && errno == EINTR) continue;
        if (ret == -1) handle_error("Cannot read from FIFO");
        if (ret ==  0) handle_error("Process has closed the FIFO unexpectedly! Exiting...\n");
        if (ret < sizeof(int)) handle_error_en(ret, "partial read from FIFO");
        // we use post-increment on bytes_read so that we first read the
        // byte that has just been written, then we do the increment
        bytes_read += ret;
    } while(bytes_read != sizeof(int));
    return bytes_read;
}


void consume(int id, int numOps) {
    int localSum = 0;
    int value;
    while (numOps > 0) {

        /**
         * Complete the following code:
         * write value in the buffer inside the shared memory and update the producer position
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
