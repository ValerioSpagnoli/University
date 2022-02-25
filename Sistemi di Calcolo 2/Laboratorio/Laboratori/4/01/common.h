#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// macros for handling errors
#define handle_error_en(en, msg)    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg)           do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Configuration parameters */

#define SHM_NAME "/shmem-example"

#define NUM 3

#define SIZE (NUM * sizeof(int))

#define SEM_NAME_REQ         "/mysemreq"
#define SEM_NAME_WRK         "/mysemwrk"

#endif
