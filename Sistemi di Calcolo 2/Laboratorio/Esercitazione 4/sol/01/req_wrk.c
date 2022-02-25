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
int * data;
/** COMPLETE THE FOLLOWING CODE BLOCK
*
* Add any needed resource
**/
int fd;
sem_t *sem_worker, *sem_request;

int request() {
  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/

  if ((data = (int *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))== MAP_FAILED)
        handle_error ("main: mmap");
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


  if (sem_post(sem_worker) != 0)
    handle_error("request: cannot unlock the worker semaphore");

  if (sem_wait(sem_request) != 0)
    handle_error("request: cannot unlock the request semaphore");

  printf("request: acquire updated data\n");

  printf("request: updated data:\n");
  for (i = 0; i < NUM; ++i) {
    printf("%d\n", data[i]);
  }

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/

    if (munmap(data, SIZE) == -1)
        handle_error("main: munmap");

  return EXIT_SUCCESS;
}

int work() {

  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  if ((data = (int *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))== MAP_FAILED)
        handle_error ("main: mmap");
  printf("worker: mapped address: %p\n", data);

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Wait that the request() process generated data
    **/

  printf("worker: waiting initial data\n");
  if (sem_wait(sem_worker) != 0)
    handle_error("worker: cannot lock the worker semaphore");

  printf("worker: acquire initial data\n");

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

  if (sem_post(sem_request) != 0)
    handle_error("worker: cannot lock the request semaphore");

  /** COMPLETE THE FOLLOWING CODE BLOCK
   *
   * Release resources
   **/
  if (munmap(data, SIZE) == -1)
      handle_error("main: munmap");

  return EXIT_SUCCESS;
}



int main(int argc, char **argv){

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Create and open the needed resources
    **/
    sem_unlink(SEM_NAME_REQ);
    sem_unlink(SEM_NAME_WRK);

    sem_request = sem_open(SEM_NAME_REQ, O_CREAT | O_EXCL, 0600, 0);
    if (sem_request == SEM_FAILED) handle_error("sem_open filled");

    sem_worker = sem_open(SEM_NAME_WRK, O_CREAT | O_EXCL, 0600, 0);
    if (sem_worker == SEM_FAILED) handle_error("sem_open filled");

    shm_unlink(SHM_NAME);

    fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
      if (fd < 0)
        handle_error("main: error in shm_open");

      if(ftruncate(fd, SIZE) == -1)
           handle_error ("main: ftruncate");

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
    ret = sem_close(sem_worker);
    if (ret) handle_error("main: sem_close worker");
    ret = sem_close(sem_request);
    if (ret) handle_error("main: sem_close request");

    // then unlink
    ret = sem_unlink(SEM_NAME_REQ);
    if (ret) handle_error("main: sem_unlink request");
    ret = sem_unlink(SEM_NAME_WRK);
    if (ret) handle_error("main: sem_unlink worker");

    ret = close(fd);
	  if (ret == -1)
        handle_error("main: cannot close the shared memory");

    ret = shm_unlink(SHM_NAME);
    if (ret) handle_error("main: shm_unlink");


    _exit(EXIT_SUCCESS);

}
