#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 500
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
 * SOLUZIONE
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */
 
sem_t filled_sem, empty_sem, write_sem;

void enqueue(int x) {
    
	/**
     * SOLUZIONE
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/single-cons
     * - gestire gli errori
     *
     */
	
	int ret;
    
    ret = sem_wait(&empty_sem);
    ERROR_HELPER(ret, "Errore wait su empty_sem");
    
    ret = sem_wait(&write_sem);
    ERROR_HELPER(ret, "Errore wait su write_sem");
    
    buffer[write_index] = x;
    write_index = (write_index + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&write_sem);
    ERROR_HELPER(ret, "Errore post su write_sem");
    
    ret = sem_post(&filled_sem);
    ERROR_HELPER(ret, "Errore post su filled_sem");
}

int dequeue() {
    
	/**
     * SOLUZIONE
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/single-cons
     * - gestire gli errori
     *
     */
	
	int ret, x;
    
    ret = sem_wait(&filled_sem);
    ERROR_HELPER(ret, "Errore wait su filled_sem");
    
    x = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&empty_sem);
    ERROR_HELPER(ret, "Errore post su empty_sem");
    
    return x;
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
     * SOLUZIONE
     * 
     * Obiettivi
     * - inizializzare i semafori dichiarati
     * - gestire gli errori
     */
	 
    ret = sem_init(&filled_sem, 0, 0);
    ERROR_HELPER(ret, "Errore inizializzazione filled_sem");
    
    ret = sem_init(&empty_sem, 0, BUFFER_LENGTH);
    ERROR_HELPER(ret, "Errore inizializzazione empty_sem");
    
    ret = sem_init(&write_sem, 0, 1);
    ERROR_HELPER(ret, "Errore inizializzazione write_sem");
    
    
	/**
     * SOLUZIONE
     * 
     * Obiettivi: lanciare THREAD_COUNT thread
     * - nota bene: successivamente bisogna attendere il termine di ogni 
     *   thread
     * - per ogni thread, preparare prima i parametri da passargli
     *  (struttura thread_args_t)
     * - l'idx deve essere diverso per ogni thread
     * - il role può assumere come valori PROD_ROLE o CONS_ROLE, ci deve 
     *   essere un solo consumatore, gli altri devono essere dei 
     *   produttori
     * - ogni thread lanciato deve eseguire la funzione thread_routine()
     * - una volta lanciato un thread, gestire gli errori
     */
	 
    // lancio thread
    pthread_t threads[THREAD_COUNT];
    int i = 0;
    for (; i < THREAD_COUNT; i++) {
        
        thread_args_t *args = malloc(sizeof(thread_args_t));
        args->idx = i;
        args->role = (i)?PROD_ROLE:CONS_ROLE;
        
        ret = pthread_create(&threads[i], NULL, thread_routine, args);
        PTHREAD_ERROR_HELPER(ret, "Errore creazione thread");
        printf("[Main Thread] Creato thread %d con ruolo %d\n", args->idx, args->role);
    }
    
    
	/**
     * SOLUZIONE
     * 
     * Obiettivi: attendere il termine dei thread
     * - attendere il termine di ognuno dei THREAD_COUNT thread lanciati
     *   in precedenza
     * - gestire gli errori
     */
	 
    // attesa termine thread
    for (i = 0; i < THREAD_COUNT; i++) {
        ret = pthread_join(threads[i], NULL);
        PTHREAD_ERROR_HELPER(ret, "Errore join su thread");
    }
    
	
	/**
     * SOLUZIONE
     * 
     * Obiettivi: rilasciare i semafori inizializzati in precedenza
     * - per ogni semaforo rilasciato, gestire gli errori
     */
	 
    // chiusura semafori
    ret = sem_destroy(&filled_sem);
    ERROR_HELPER(ret, "Errore destroy filled_sem");
    
    ret = sem_destroy(&empty_sem);
    ERROR_HELPER(ret, "Errore destroy empty_sem");
    
    ret = sem_destroy(&write_sem);
    ERROR_HELPER(ret, "Errore destroy write_sem");
    
    printf("[Main Thread] operazioni completate\n");
    
    return EXIT_SUCCESS;
}
