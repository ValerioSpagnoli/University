#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 5
#define THREAD_COUNT 4
#define ITERATION_COUNT 10
#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    int idx;
    int role;
} thread_args_t;

int buffer[BUFFER_LENGTH];
int write_index, read_index;

/**
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */

sem_t sem_cons;
sem_t sem_prod;
sem_t sem_empty;
sem_t sem_filled;


/***/


void producer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {
        int value = idx*ITERATION_COUNT + i;

        ret = sem_wait(&sem_empty);
        if(ret != 0) handle_error("errore sem_wait");
        ret = sem_wait(&sem_prod);
        if(ret != 0) handle_error("errore sem_wait");

        buffer[write_index] = value;
        write_index = (write_index + 1) % BUFFER_LENGTH;

        printf("[Thread #%d] inserito %d nel buffer\n", idx, value);

        ret = sem_post(&sem_prod);
        if(ret != 0) handle_error("errore sem_post");
        ret = sem_post(&sem_filled);
        if(ret != 0) handle_error("errore sem_post");
     }
}

void consumer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {

        ret = sem_wait(&sem_filled);
        if(ret != 0) handle_error("errore sem_wait");
        ret = sem_wait(&sem_cons);
        if(ret != 0) handle_error("errore sem_wait");

        int value = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_LENGTH;

        printf("[Thread #%d] letto %d dal buffer\n", idx, value);

        ret = sem_post(&sem_cons);
        if(ret != 0) handle_error("errore sem_post");
        ret = sem_post(&sem_empty);
        if(ret != 0) handle_error("errore sem_post");
     }
}


void *thread_routine(void *args) {

    thread_args_t *thread_args = (thread_args_t*)args;
    if (thread_args->role == PROD_ROLE) {
        producer_routine(thread_args->idx);
    } else if (thread_args->role == CONS_ROLE) {
        consumer_routine(thread_args->idx);
    } else {
        printf("[Thread #%d] ruolo sconosciuto: %d\n", thread_args->idx, thread_args->role);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    int ret;

    // inizializzazioni
    read_index = write_index = 0;

    /**
     * COMPLETARE QUI
     *
     * Obiettivi
     * - inizializzare i semafori dichiarati
     * - gestire gli errori
     */

    ret = sem_init(&sem_prod, 0, 1);
    if(ret != 0) handle_error("errore sem_init");
    ret = sem_init(&sem_cons, 0, 1);
    if(ret != 0) handle_error("errore sem_init");
    ret = sem_init(&sem_empty, 0, BUFFER_LENGTH);
    if(ret != 0) handle_error("errore sem_init");
    ret = sem_init(&sem_filled, 0, 0);
    if(ret != 0) handle_error("errore sem_init");

    /***/

    /**
     * COMPLETARE QUI
     *
     * Obiettivi: creazione thread
     * - ogni thread deve invocare la funzione thread_routine()
     * - gli argomenti per il thread devono essere specificati
     *   all'interno di una struttura thread_args_t
     * - il campo role può assumere come valori PROD_ROLE o CONS_ROLE
     * - ogni thread ha un valore di idx diverso tra 0 e THREAD_COUNT-1
     * - ci dovranno essere THREAD_COUNT/2 thread con ruolo produttore
     *   ed altrettanti con ruolo consumatore (THREAD_COUNT è pari)
     * - gestire glie errori
     * - N.B.: si tenga presente che successivamente il programma
     *   dovrà attendere la terminazione di ogni thread
     *
     */


    int threadID = 0, i;

    pthread_t* thread = (pthread_t*)malloc(THREAD_COUNT*sizeof(pthread_t));

    for(i = 0; i<(THREAD_COUNT/2); i++){
        thread_args_t* args = (thread_args_t*)malloc(sizeof(thread_args_t));
        args->idx = threadID;
        args->role = PROD_ROLE;
        ret = pthread_create(&thread[threadID], NULL, thread_routine, args);
        if(ret != 0) handle_error_en(ret, "errore pthread_create");
        threadID++;
    }

    for(i = 0; i<(THREAD_COUNT/2); i++){
        thread_args_t* args = (thread_args_t*)malloc(sizeof(thread_args_t));
        args->idx = threadID;
        args->role = CONS_ROLE;
        ret = pthread_create(&thread[threadID], NULL, thread_routine, args);
        if(ret != 0) handle_error_en(ret, "errore pthread_create");
        threadID++;
    }


    /***/


    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - attendere la terminazione dei thread lanciati in precedenza
     * - gestire gli errori
     */

    for(i = 0; i<THREAD_COUNT; i++){
        ret = pthread_join(thread[i], NULL);
        if(ret != 0) handle_error_en(ret, "errore pthread_join");
    }

    /***/

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - rilasciare i semafori inizializzati in precedenza
     * - gestire gli errori
     */

    if(sem_destroy(&sem_prod) != 0) handle_error("errore sem_destroy");
    if(sem_destroy(&sem_cons) != 0) handle_error("errore sem_destroy");
    if(sem_destroy(&sem_empty) != 0) handle_error("errore sem_destroy");
    if(sem_destroy(&sem_filled) != 0) handle_error("errore sem_destroy");

    /***/

    printf("[Main Thread] operazioni completate\n");

    return EXIT_SUCCESS;
}


read_bytes = 0
while(buf[read_bytes] != '\n'){
        ---
    read_bytes++;
}




