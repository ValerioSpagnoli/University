#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>


// data array
int * data; // puntatore dove deve essere mappata la shared memory
/** COMPLETE THE FOLLOWING CODE BLOCK
*
* Add any needed resource
**/

int shm; // descrittore della shared memory;
sem_t* sem_req; // semaforo per notifica
sem_t* sem_wrk; // semaforo per critical section;


int request() {
    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * map the shared memory in the data array
    **/

    data = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    if(data == MAP_FAILED) handle_error("[Request] mmap error");

    printf("request: mapped address: %p\n", data);

    int i;
    for (i = 0; i < NUM; ++i) {
    data[i] = i;
    }
    printf("request: data generated\n");

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the worker that it can start the elaboration
    * and wait it has terminated
    **/

    sem_post(sem_req);
    sem_wait(sem_wrk);

    printf("request: acquire updated data\n");

    printf("request: updated data:\n");
    for (i = 0; i < NUM; ++i) {
    printf("%d\n", data[i]);
    }

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/

    if(munmap(data, SIZE) == -1) handle_error("[Request] munmap error");

    return EXIT_SUCCESS;
}

int work() {

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * map the shared memory in the data array
    **/

    data = mmap(0, SIZE, PROT_READ| PROT_WRITE, MAP_SHARED, shm, 0);
    if(data == MAP_FAILED) handle_error("[Work] mmap error");

    printf("worker: mapped address: %p\n", data);

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Wait that the request() process generated data
    **/

    printf("worker: waiting initial data\n");

    sem_wait(sem_req);

    printf("worker: initial data acquired\n");

    printf("worker: update data\n");
    int i;
    for (i = 0; i < NUM; ++i) {
    data[i] = data[i] * data[i];
    }

    printf("worker: release updated data\n");

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the requester that elaboration terminated
    **/

    sem_post(sem_wrk);

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/

    if(munmap(data, SIZE) == -1) handle_error("[Work] munmap error");

    return EXIT_SUCCESS;
}



int main(int argc, char **argv){

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Create and open the needed resources
    **/

    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME_REQ);
    sem_unlink(SEM_NAME_WRK);

    shm = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(shm == -1) handle_error("[Main] shm opening error");

    if(ftruncate(shm, SIZE) == -1) handle_error("[Main] ftruncate error");

    sem_req = sem_open(SEM_NAME_REQ, O_CREAT | O_EXCL, 0666, 0);
    if(sem_req == SEM_FAILED) handle_error("[Main] shm_req opening error");

    sem_wrk = sem_open(SEM_NAME_WRK, O_CREAT | O_EXCL, 0666, 0);
    if(sem_wrk == SEM_FAILED) handle_error("[Main] shm_req opening error");

    int ret;
    pid_t pid = fork();
    if (pid == -1) {
        handle_error("main: fork");
    } else if (pid == 0) {
        work();
        _exit(EXIT_SUCCESS);
    }

    request();
    int status;
    ret = wait(&status);
    if (ret == -1)
      handle_error("main: wait");
    if (WEXITSTATUS(status)) handle_error_en(WEXITSTATUS(status), "request() crashed");


   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Close and release resources
    **/

    if(sem_close(sem_req) == -1) handle_error("[Main] sem_req closing error");
    if(sem_unlink(SEM_NAME_REQ) == -1) handle_error("[Main] sem_req unlinking error");

    if(sem_close(sem_wrk) == -1) handle_error("[Main] sem_wrk closing error");
    if(sem_unlink(SEM_NAME_WRK) == -1) handle_error("[Main] sem_wrk unlinking error");

    if(close(shm) == -1) handle_error("[Main] shm closing error");
    if(shm_unlink(SHM_NAME) == -1) handle_error("[Main] shm unlinking error");

    _exit(EXIT_SUCCESS);

}
