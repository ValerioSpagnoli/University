#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define SEED 91735

// numero produttori/consumatori/buffer
#define N 3

// dimensione del singolo buffer
#define BUFFER_LENGTH 3

// numero elementi inseriti da ogni produttore/letti da ogni consumatore
#define ELEMENT_COUNT 5

#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    // identificativo del produttore/consumatore, varia tra 0 e N-1
    int id;
    
    // specifica se il thread è un produttore (PROD_ROLE) o un 
    // consumatore (CONS_ROLE)
    int role;
    
    // numero elementi inseriti nel/letti dal buffer
    int element_count; 
} thread_args_t;

/**
 * buffer[i] è il buffer dove l'i-esimo produttore scrive e l'i-esimo 
 * consumatore legge, i varia tra 0 e N-1
 * 
 * buffer[i][j] è il j-esimo elemento del buffer i-esimo, j varia tra 0 
 * e BUFFER_LENGTH-1
 */
int buffer[N][BUFFER_LENGTH];

/**
 * write_index[i] è l'indice di scrittura del buffer i-esimo
 * read_index[i] è l'indice di lettura del buffer i-esimo
 * i varia tra 0 e N-1
 */
int write_index[N], read_index[N];

/**
 * SOLUZIONE
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */
sem_t filled_sem[N], empty_sem[N];

/**
 * Questa funzione gestisce l'enqueue dell'elemento x nel buffer id
 */
void enqueue(int id, int x) {
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */
    int ret;
    
    ret = sem_wait(&empty_sem[id]);
    ERROR_HELPER(ret, "Errore wait su empty_sem");
    
    buffer[id][write_index[id]] = x;
    write_index[id] = (write_index[id] + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&filled_sem[id]);
    ERROR_HELPER(ret, "Errore post su filled_sem");
}

/**
 * Questa funzione gestisce la dequeue dal buffer id
 */
int dequeue(int id) {
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */
    int ret, x;
    
    ret = sem_wait(&filled_sem[id]);
    ERROR_HELPER(ret, "Errore wait su filled_sem");
    
    x = buffer[id][read_index[id]];
    read_index[id] = (read_index[id] + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&empty_sem[id]);
    ERROR_HELPER(ret, "Errore post su empty_sem");
    
    return x;
}

void *thread_routine(void *args) {
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - sulla base dei valori in args, implementare la logica del 
     *   produttore o del consumatore
     *   * il produttore con identificativo id deve fare element_count 
     *     enqueue() nel buffer id
     *   * per scegliere il valore dell'elemento da inserire, usare la 
     *     funzione rand()
     *   * il consumatore con identificativo id deve fare element_count 
     *     dequeue() dal buffer id
     * - rilasciare le risorse occupate dal thread
     * - uscire dal thread
     *
     */
     
    thread_args_t *thread_args = (thread_args_t*)args;
    
    int i = 0, value;
    for (; i < thread_args->element_count; i++)
        if (thread_args->role == PROD_ROLE) {
            value = rand();
            enqueue(thread_args->id, value);
            printf("Il producer %d ha inserito nel buffer l'elemento numero %d con valore %d\n", thread_args->id, (i+1), value);
        } else if (thread_args->role == CONS_ROLE) {
            value = dequeue(thread_args->id);
            printf("Il consumer %d ha letto dal buffer l'elemento numero %d con valore %d\n", thread_args->id, (i+1), value);
        } else {
            printf("RUOLO SCONOSCIUTO: %d\n", thread_args->role);
        }
    
    free(args);
    
    pthread_exit(NULL);
}

void *orchestrator_routine(void *arg) {
    
    int role = *(int*)arg;
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - creare ed avviare in parallelo N thread
     * - ogni thread deve eseguire la funzione thread_routine()
     * - per ogni thread, preparare un'istanza di thread_args_t
     *   * il thread i-esimo deve avere id pari ad i
     *   * il ruolo è dato dall'argomento di input di questa funzione
     *   * il numero di elementi è dato dalla macro ELEMENT_COUNT
     * - dopo aver creato questi thread, attenderne il termine
     * - gestire gli errori
     * - uscire dal thread
     * 
     */
    
    int i = 0, ret;
    pthread_t threads[N];
    for (; i < N; i++) {
    
        thread_args_t *args = malloc(sizeof(thread_args_t));
        args->id = i;
        args->element_count = ELEMENT_COUNT;
        args->role = role;
    
        ret = pthread_create(&threads[i], NULL, thread_routine, args);
        PTHREAD_ERROR_HELPER(ret, "Errore creazione thread");
        printf("Creato thread %d con ruolo %d\n", i, role);
    }    
    
    for (i = 0; i < N; i++) {
        ret = pthread_join(threads[i], NULL);
        PTHREAD_ERROR_HELPER(ret, "Errore join su thread");
        printf("Terminato thread %d con ruolo %d\n", i, role);
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    
    srand(SEED);
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - inizializzare gli indici di lettura/scrittura dei buffer
     * - inizializzare i semafori
     * - creare ed avviare in parallelo i due thread orchestratori
     *   * uno deve avere ruolo PROD_ROLE, l'altro CONS_ROLE
     *   * entrambi devono eseguire la funzione orchestrator_routine()
     *   * suggerimento: utilizzare una variabile int per il ruolo
     * - dopo aver creato questi thread, attenderne il termine
     * - rilasciare le risorse create in questa funzione
     * - gestire gli errori
     *
     */
    
    int ret, i = 0;
    
    // inizializzazioni
    for (; i < N; i++) {
        read_index[i] = write_index[i] = 0;
        
        int ret = sem_init(&filled_sem[i], 0, 0);
        ERROR_HELPER(ret, "Errore inizializzazione filled_sem");

        ret = sem_init(&empty_sem[i], 0, BUFFER_LENGTH);
        ERROR_HELPER(ret, "Errore inizializzazione empty_sem");
    }
     
    int prod_role = PROD_ROLE;
    pthread_t prod_orchestrator;
    ret = pthread_create(&prod_orchestrator, NULL, orchestrator_routine, &prod_role);
    PTHREAD_ERROR_HELPER(ret, "Errore creazione orchestratore produttori");
    printf("Creato orchestratore produttori\n");
     
    int cons_role = CONS_ROLE;
    pthread_t cons_orchestrator;
    ret = pthread_create(&cons_orchestrator, NULL, orchestrator_routine, &cons_role);
    PTHREAD_ERROR_HELPER(ret, "Errore creazione orchestratore consumatori");
    printf("Creato orchestratore consumatori\n");
    
    ret = pthread_join(prod_orchestrator, NULL);
    PTHREAD_ERROR_HELPER(ret, "Errore join su orchestratore produttori");
    printf("Terminato orchestratore produttori\n");
    
    ret = pthread_join(cons_orchestrator, NULL);
    PTHREAD_ERROR_HELPER(ret, "Errore join su orchestratore consumatori");
    printf("Terminato orchestratore consumatori\n");
    
    // chiusura semafori
    for (i = 0; i < N; i++) {
        ret = sem_destroy(&filled_sem[i]);
        ERROR_HELPER(ret, "Errore destroy filled_sem");
        
        ret = sem_destroy(&empty_sem[i]);
        ERROR_HELPER(ret, "Errore destroy empty_sem");
    }
    
    return EXIT_SUCCESS;
}
