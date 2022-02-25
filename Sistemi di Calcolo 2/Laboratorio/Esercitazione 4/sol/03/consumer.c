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


void openMemory() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * Request shared memory to the kernel and map the shared memory in the shared_mem_ptr variable.
     **/
    if ((fd_shm = shm_open (SH_MEM_NAME, O_RDWR, 0660)) == -1)
        handle_error("shm_open");

    if ((myshm_ptr = mmap (NULL, sizeof(struct shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED,
            fd_shm, 0)) == MAP_FAILED)
       handle_error ("mmap");
}

void closeMemory() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * unmap the shared memory and close its descriptor
     **/
     int ret;
	// mmap cleanup
	ret = munmap(myshm_ptr, sizeof(struct shared_memory));
	if (ret == -1)
        handle_error("munmap");

    //close descriptor
    close(fd_shm);
}

void consume(int id, int numOps) {
    int localSum = 0;
    int next_pos;

    while (numOps > 0) {


        /**
         * Complete the following code:
         * wait that there is something to read
         * write value in the buffer inside the shared memory and update the producer position
         */

        while (myshm_ptr->read_index == myshm_ptr->write_index); //busy waiting
        int value = myshm_ptr->buf[myshm_ptr->read_index];
    	next_pos = (myshm_ptr->read_index + 1) % BUFFER_SIZE;
        myshm_ptr->read_index = next_pos;

        localSum += value;
        numOps--;
    }
    printf("Consumer %d ended. Local sum is %d\n", id, localSum);
}

int main(int argc, char** argv) {

    openMemory();

    consume(0, OPS_PER_CONSUMER);

    printf("Consumer has terminated. Exiting...\n");

    closeMemory();

    exit(EXIT_SUCCESS);
}
