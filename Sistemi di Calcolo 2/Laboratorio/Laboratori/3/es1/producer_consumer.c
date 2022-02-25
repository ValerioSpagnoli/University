#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include "common.h"

#define BUFFER_SIZE         128
#define INITIAL_DEPOSIT     0
#define MAX_TRANSACTION     1000
#define NUM_CONSUMERS       2
#define NUM_PRODUCERS       4
#define PRNG_SEED           0

#define NUM_OPERATIONS      400
#define OPS_PER_CONSUMER    (NUM_OPERATIONS/NUM_CONSUMERS)
#define OPS_PER_PRODUCER    (NUM_OPERATIONS/NUM_PRODUCERS)

// we use the preprocessor to check if our parameters are okay
#if OPS_PER_CONSUMER*NUM_CONSUMERS != OPS_PER_PRODUCER*NUM_PRODUCERS
#error "Choose NUM_CONSUMERS and NUM_PRODUCERS so that we get exactly NUM_OPERATIONS operations"
#endif

/* SEMAFORI NECESSARI
 *
 * Sono necessari due semafori distinti per i producer e i consumer (sem_write e sem_read), così che sia
 * possibile per i producer scrivere anche se i consumer stanno leggendo e sia possibile per i consumer
 * leggere anche se i producer stanno scrivendo (ovviamente se sono rispettate le altre condizioni gestite
 * da sem_fill e sem_empty). Più producer e non possono scrivere contemporaneamente e più consumer
 * non possono leggere contemporaneamente.
 *
 * E' necessario un semaforo sem_fill per segnalare (da parte del producer) che il buffer contiene risorse che
 * possono essere consumate, e per controllare (da parte del consumer) che ci siano risorse da consumare
 *
 * E' necessario un semaforo sem_empty per segnalare (da parte del consumer) che c'è spazio disponibile nel
 * buffer per poter scrivere, e per controllare (da parte del producer) che ci sia spazio per scrivere.
 *
 */

sem_t sem_write;
sem_t sem_read;
sem_t sem_fill;
sem_t sem_empty;

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

    int ret;

    while (args->numOps > 0) {
        // produce the item
        int currentTransaction = performRandomTransaction();

        // segnala che sarà disponibile uno spazio in meno nel buffer. Se non c'è spazio rimane
        // bloccato finchè un consumer non fa la sem_post(&sem_empty) per segnalare che è disponibile
        // uno spazio nel buffer
        ret = sem_wait(&sem_empty);
        if(ret != 0) handle_error_en(ret, "[performTransaction] Errore sem_wait(&sem_empty)");

        // prende il buffer in scrittura, in modo che altri producer non possano scrivere finchè non ha finito
        ret = sem_wait(&sem_write);
        if(ret != 0) handle_error_en(ret, "[performTransaction] Errore sem_wait(&sem_write)");

        // CRITICAL SECTION
        transactions[write_index] = currentTransaction;
        write_index = (write_index + 1) % BUFFER_SIZE;

        // rilascia il buffer in scrittura
        ret = sem_post(&sem_write);
        if(ret != 0) handle_error_en(ret, "[performTransaction] Errore sem_post(&sem_write)");

        // segnala che è disponibile una risorsa nel buffer
        ret = sem_post(&sem_fill);
        if(ret != 0) handle_error_en(ret, "[performTransaction] Errore sem_post(&sem_fill)");

        args->numOps--;
    }

    free(args);
    pthread_exit(NULL);
}

// client thread
void* processTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting consumer thread %d\n", args->threadId);

    int ret;

    while (args->numOps > 0) {

        // segnala che sta per consumare una risorsa del buffer. Se non sono disponibili risorse
        // nel buffer rimane bloccato finchè un producer non fa sem_post(&sem_fill) per segnalare
        // che è disponibile una risorsa nel buffer
        ret = sem_wait(&sem_fill);
        if(ret != 0) handle_error_en(ret, "[processTransaction] Errore sem_wait(&sem_fill)");

        // prende il buffer in lettura, in modo che altri consumer non possano leggere finchè non ha finito
        ret = sem_wait(&sem_read);
        if(ret != 0) handle_error_en(ret, "[processTransaction] Errore sem_wait(&sem_read)");

        // CRITICAL SECTION
        deposit += transactions[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
        if (read_index % 100 == 0)
			printf("After the last 100 transactions balance is now %d.\n", deposit);

        // rilascia il buffer in lettura
        ret = sem_post(&sem_read);
        if(ret != 0) handle_error_en(ret, "[processTransaction] Errore sem_post(&sem_read)");

        // segnala che è disponibile uno spazio in più nel buffer
        ret = sem_post(&sem_empty);
        if(ret != 0) handle_error_en(ret, "[processTransaction] Errore sem_wait(&sem_empty)");

        args->numOps--;
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

    int ret;

    // set seed for pseudo-random number generator: we use this to make
    // this code yield the same result across different runs, as long
    // as they are race-free and you make no mistakes :-)
    srand(PRNG_SEED);

    ret = sem_init(&sem_write, 0, 1);
    if(ret != 0) handle_error_en(ret, "[Main] Errore inizializzazione sem_write");

    ret = sem_init(&sem_read, 0, 1);
    if(ret != 0) handle_error_en(ret, "[Main] Errore inizializzazione sem_read");

    ret = sem_init(&sem_fill, 0, INITIAL_DEPOSIT);
    if(ret != 0) handle_error_en(ret, "[Main] Errore inizializzazione sem_fill");

    ret = sem_init(&sem_empty, 0, BUFFER_SIZE);
    if(ret != 0) handle_error_en(ret, "[Main] Errore inizializzazione sem_empty");


    pthread_t producer[NUM_PRODUCERS], consumer[NUM_CONSUMERS];

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

    ret = sem_destroy(&sem_write);
    if(ret != 0) handle_error_en(ret, "[Main] Errore distruzzione sem_write");

    ret = sem_destroy(&sem_read);
    if(ret != 0) handle_error_en(ret, "[Main] Errore distruzzione sem_read");

    ret = sem_destroy(&sem_fill);
    if(ret != 0) handle_error_en(ret, "[Main] Errore distruzzione sem_fill");

    ret = sem_destroy(&sem_empty);
    if(ret != 0) handle_error_en(ret, "[Main] Errore distruzzione sem_empty");

    exit(EXIT_SUCCESS);
}
