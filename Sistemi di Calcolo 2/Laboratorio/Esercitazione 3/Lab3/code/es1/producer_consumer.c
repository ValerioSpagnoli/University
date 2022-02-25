#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include "common.h"

#define BUFFER_SIZE         128 //e
#define INITIAL_DEPOSIT     0   //n
#define MAX_TRANSACTION     10
#define NUM_CONSUMERS       10
#define NUM_PRODUCERS       8
#define PRNG_SEED           0

#define NUM_OPERATIONS      400
#define OPS_PER_CONSUMER    (NUM_OPERATIONS/NUM_CONSUMERS)
#define OPS_PER_PRODUCER    (NUM_OPERATIONS/NUM_PRODUCERS)


//SEMAFORI CASO 1 - M=1, N=1

sem_t s1; //per gestire la sezione critica per produttori -> 1 o 0
sem_t s2; //per gestire la sezione cristica per i consumatori -> 1 o 0
sem_t n; //indica quanti elementi posso consumare
sem_t e; //indica la size del buffer disponibile per mettere i dati prodotti

int sem_val;


// we use the preprocessor to check if our parameters are okay
#if OPS_PER_CONSUMER*NUM_CONSUMERS != OPS_PER_PRODUCER*NUM_PRODUCERS
#error "Choose NUM_CONSUMERS and NUM_PRODUCERS so that we get exactly NUM_OPERATIONS operations"
#endif

// struct used to specify arguments for a thread
typedef struct {
    int threadId;
    int numOps;
} thread_args_t;

// shared data
int transactions[BUFFER_SIZE];
int deposit = INITIAL_DEPOSIT;
int read_index, write_index;

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

// producer thread
void* performTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting producer thread %d\n", args->threadId);

    while (args->numOps > 0) {
        // produce the item
        int currentTransaction = performRandomTransaction();

        sem_wait(&e); //blocca la size del buffer

        sem_getvalue(&e, &sem_val);
        printf("***** IL SEMAFORO e VALE %d *****\n", sem_val);

        sem_wait(&s1); //prende il buffer

        sem_getvalue(&s1, &sem_val);
        printf("***** IL SEMAFORO s1 VALE %d *****\n", sem_val);

        //INIZIO SEZIONE CRITICA

        // write the item and update write_index accordingly
        transactions[write_index] = currentTransaction;
        write_index = (write_index + 1) % BUFFER_SIZE;

        //FINE SEZIONE CRITICA

        sem_post(&s1); //Libera il buffer

        sem_getvalue(&s1, &sem_val);
        printf("***** IL SEMAFORO s1 VALE %d *****\n", sem_val);

        sem_post(&n); //segnala che è disponibile una risorsa

        sem_getvalue(&n, &sem_val);
        printf("***** IL SEMAFORO n VALE %d *****\n", sem_val);

        args->numOps--;
        //printf("P %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

//consumer thread
void* processTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting consumer thread %d\n", args->threadId);

    while (args->numOps > 0) {

        sem_wait(&n);

        sem_getvalue(&n, &sem_val);
        printf("***** IL SEMAFORO n VALE %d *****\n", sem_val);

        sem_wait(&s2);

        sem_getvalue(&s2, &sem_val);
        printf("***** IL SEMAFORO s2 VALE %d *****\n", sem_val);

        //INIZIO SEZIONE CRITICA

        // consume the item and update (shared) variable deposit
        deposit += transactions[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
        if (read_index % 100 == 0)
			printf("After the last 100 transactions balance is now %d.\n", deposit);

        //INIZIO SEZIONE CRITICA

        sem_post(&s2);

        sem_getvalue(&s2, &sem_val);
        printf("***** IL SEMAFORO s2 VALE %d *****\n", sem_val);

        sem_post(&e);

        sem_getvalue(&e, &sem_val);
        printf("***** IL SEMAFORO e VALE %d *****\n", sem_val);

        args->numOps--;
        //printf("C %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    printf("Welcome! This program simulates financial transactions on a deposit.\n");
    printf("\nThe maximum amount of a single transaction is %d (negative or positive).\n", MAX_TRANSACTION);
    printf("\nInitial balance is %d. Press CTRL+C to quit.\n\n", INITIAL_DEPOSIT);

    // initialize read and write indexes
    read_index  = 0;
    write_index = 0;

    // set seed for pseudo-random number generator: we use this to make
    // this code yield the same result across different runs, as long
    // as they are race-free and you make no mistakes :-)
    srand(PRNG_SEED);

    int ret;
    pthread_t producer[NUM_PRODUCERS], consumer[NUM_CONSUMERS];

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);
    sem_init(&n, 0, deposit);
    sem_init(&e, 0, BUFFER_SIZE);

    int i;
    for (i=0; i<NUM_PRODUCERS; ++i) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = i;
        arg->numOps = OPS_PER_PRODUCER;

        ret = pthread_create(&producer[i], NULL, performTransactions, arg);
        if (ret != 0)  handle_error_en(ret,"Error in pthread create (producer)");
    }

    int j;
    for (j=0; j<NUM_CONSUMERS; ++j) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = j;
        arg->numOps = OPS_PER_CONSUMER;

        ret = pthread_create(&consumer[j], NULL, processTransactions, arg);
        if (ret != 0) handle_error_en(ret,"Error in pthread create (consumer)");
    }

    // join on threads
    for (i=0; i<NUM_PRODUCERS; ++i) {
        ret = pthread_join(producer[i], NULL);
        if (ret != 0) handle_error_en(ret,"Error in pthread join (producer)");
    }

    for (j=0; j<NUM_CONSUMERS; ++j) {
        ret = pthread_join(consumer[j], NULL);
        if (ret != 0) handle_error_en(ret,"Error in pthread join (consumer)");
    }

    printf("Final value for deposit: %d\n", deposit);

    exit(EXIT_SUCCESS);
}
