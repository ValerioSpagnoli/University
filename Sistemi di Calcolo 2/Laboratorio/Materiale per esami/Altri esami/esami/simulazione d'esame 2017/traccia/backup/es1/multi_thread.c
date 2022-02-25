#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 5
#define THREAD_COUNT 10
#define ITERATION_COUNT 50
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


void enqueue(int x) {

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma multi-prod/multi-cons
     * - gestire gli errori
     *
     */

}

int dequeue() {

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma multi-prod/multi-cons
     * - gestire gli errori
     *
     */

}

void *thread_routine(void *args) {

	thread_args_t *thread_args = (thread_args_t*)args;

    int i = 0;
    for (; i < ITERATION_COUNT; i++) {
        if (thread_args->role == PROD_ROLE) {
            int value = thread_args->idx * i;
            enqueue(value);
            printf("[Thread #%d] inserito %d nel buffer\n", thread_args->idx, value);
        } else if (thread_args->role == CONS_ROLE) {
            int value = dequeue();
            printf("[Thread #%d] letto %d dal buffer\n", thread_args->idx, value);
        } else {
            printf("[Thread #%d] ruolo sconosciuto: %d\n", thread_args->idx, thread_args->role);
        }
    }

    free(thread_args);

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


    /**
     * COMPLETARE QUI
     *
     * Obiettivi: lanciare THREAD_COUNT thread
     * - nota bene: successivamente bisogna attendere il termine di ogni thread
     * - per ogni thread, preparare prima i parametri da passargli (struttura
     *   thread_args_t); NB: fare attenzione a come questa struttura dati viene
     *   gestita mella funzione thread_routine()
     * - l'idx deve essere diverso per ogni thread
     * - il role può assumere come valori PROD_ROLE o CONS_ROLE, ci devono essere tanti consumatori quanti produttori
     * - ogni thread lanciato deve eseguire la funzione thread_routine()
     * - gestire gli errori
     */


	/**
     * COMPLETARE QUI
     *
     * Obiettivi: attendere il termine dei thread
     * - attendere il termine di ognuno dei THREAD_COUNT thread lanciati in precedenza
     * - gestire gli errori
     */


	/**
     * COMPLETARE QUI
     *
     * Obiettivi: rilasciare i semafori inizializzati in precedenza
     * - gestire gli errori
     */


    printf("[Main Thread] operazioni completate\n");

    return EXIT_SUCCESS;
}
