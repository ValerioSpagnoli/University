#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 3
#define SEED 91735
#define CHILD_COUNT 3
#define READ_COUNT 9
#define WRITE_COUNT 6
#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    int child_id;
    int role;
    int read_count;
    int write_count;
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
sem_t filled_sem, empty_sem;

void enqueue(int x) {
    
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
    
    ret = sem_wait(&empty_sem);
    ERROR_HELPER(ret, "Errore wait su empty_sem");
    
    buffer[write_index] = x;
    write_index = (write_index + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&filled_sem);
    ERROR_HELPER(ret, "Errore post su filled_sem");
}

int dequeue() {
    
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
    
    ret = sem_wait(&filled_sem);
    ERROR_HELPER(ret, "Errore wait su filled_sem");
    
    x = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_LENGTH;
    
    ret = sem_post(&empty_sem);
    ERROR_HELPER(ret, "Errore post su empty_sem");
    
    return x;
}

void producer(int child_id, int write_count) {
    int i = 0, value;
    for (; i < write_count; i++) {
        value = rand();
        enqueue(value);
        printf("[Proc. figlio %d] Producer ha inserito elemento %d con valore %d\n", child_id, (i+1), value);
    }
}

void consumer(int child_id, int read_count) {
    int i = 0, value;
    for (; i < read_count; i++) {
        value = dequeue();
        printf("[Proc. figlio %d] Consumer ha letto elemento %d con valore %d\n", child_id, (i+1), value);
    }
}

void *thread_routine(void *args) {
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - sulla base dei valori dei campi della struttura data passata come
     *   argomento, questa funzione deve invocare o la funzione producer()
     *   oppure la funzione consumer(), passando loro i parametri opportuni
     * - prima di invocare la funzione consumer(), verificare che il valore
     *   da passare per il suo argomento read_count non causi una attesa
     *   infinita da parte del consumer, e in tal caso ricalibrarne il
     *   valore in modo che vengano letti tutti e soli gli elementi
     *   effettivamente inseriti dal producer
     * - uscire dal thread
     *
     */
     
    thread_args_t *thread_args = (thread_args_t*)args;
    
    if (thread_args->role == PROD_ROLE) {
        producer(thread_args->child_id, thread_args->write_count);
    } else if (thread_args->role == CONS_ROLE) {
        if (thread_args->read_count > thread_args->write_count)
            thread_args->read_count = thread_args->write_count;
        consumer(thread_args->child_id, thread_args->read_count);
    } else {
        printf("RUOLO SCONOSCIUTO: %d\n", thread_args->role);
    }
    
    pthread_exit(NULL);
}

void child_routine(int child_id) {
    srand(SEED);
    
    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - inizializzare i semafori necessari
     * - creare un thread producer ed uno consumer; entrambi devono eseguire in 
     *   parallelo la funzione thread_routine(); per ognuno, preparare 
     *   un'istanza di struttura dati thread_args_t assegnando ai suoi campi dei
     *   valori opportuni (vedere le macro definite all'inizio di questo 
     *   sorgente)
     * - dopo aver creato questi due thread, il main thread deve attenderne la
     *   terminazione
     * - successivamente, il main thread deve rilasciare tutte le risorse da lui
     *   allocate
     * - gestire gli errori
     *
     */
    
    int ret = sem_init(&filled_sem, 0, 0);
    ERROR_HELPER(ret, "Errore inizializzazione filled_sem");

    ret = sem_init(&empty_sem, 0, BUFFER_LENGTH);
    ERROR_HELPER(ret, "Errore inizializzazione empty_sem");
    
    pthread_t consumer_thread, producer_thread;
    thread_args_t *consumer_args = malloc(sizeof(thread_args_t));
    thread_args_t *producer_args = malloc(sizeof(thread_args_t));
    consumer_args->child_id = producer_args->child_id = child_id;
    consumer_args->read_count = producer_args->read_count = READ_COUNT;
    consumer_args->write_count = producer_args->write_count = WRITE_COUNT;
    consumer_args->role = CONS_ROLE;
    producer_args->role = PROD_ROLE;
    
    ret = pthread_create(&consumer_thread, NULL, thread_routine, consumer_args);
    PTHREAD_ERROR_HELPER(ret, "Errore creazione consumer thread");
    printf("Creato consumer thread per processo figlio %d\n", child_id);
    
    ret = pthread_create(&producer_thread, NULL, thread_routine, producer_args);
    PTHREAD_ERROR_HELPER(ret, "Errore creazione producer thread");
    printf("Creato producer thread per processo figlio %d\n", child_id);
    
    ret = pthread_join(producer_thread, NULL);
    PTHREAD_ERROR_HELPER(ret, "Errore join su producer thread");
    printf("Terminato producer thread per processo figlio %d\n", child_id);
    
    ret = pthread_join(consumer_thread, NULL);
    PTHREAD_ERROR_HELPER(ret, "Errore join su consumer thread");
    printf("Terminato consumer thread per processo figlio %d\n", child_id);
    
    free(consumer_args);
    free(producer_args);
    
    // chiusura semafori
    ret = sem_destroy(&filled_sem);
    ERROR_HELPER(ret, "Errore destroy filled_sem");
    
    ret = sem_destroy(&empty_sem);
    ERROR_HELPER(ret, "Errore destroy empty_sem");
}

int main(int argc, char* argv[]) {
    
    int ret, i = 0;
    
    // inizializzazioni
    read_index = write_index = 0;

    /**
     * SOLUZIONE
     *
     * Obiettivi:
     * - creare CHILD_COUNT processi figlio in modo che vengano eseguiti in
     *   parallelo
     * - il processo figlio i-esimo deve eseguire la funzione child_routine()
     *   con argomento i
     * - dopo aver creato tutti i processi figlio, il processo padre deve 
     *   attenderne la terminazione
     * - gestire gli errori
     * - VINCOLO: il codice scritto non deve contenere istruzioni di tipo
     *   exit o return che causino la terminazione del processo; deve
     *   esserci solo la "return EXIT_SUCCESS;" già presente alla fine
     *
     */
    pid_t pid;
    for (; i < CHILD_COUNT; i++) {
        pid = fork();
        if (pid == -1) ERROR_HELPER(-1, "Errore nella fork");
        if (pid == 0) {
            child_routine(i);
            break;
        }
    }

    if (i == CHILD_COUNT) {
        for (i = 0; i < CHILD_COUNT; i++) {
            ret = wait(NULL);
            ERROR_HELPER(ret, "Errore nella wait");
        }
        printf("Terminato processo padre\n");
    } else {
        printf("Terminato processo figlio %d\n", i);
    }
    
    return EXIT_SUCCESS;
}
