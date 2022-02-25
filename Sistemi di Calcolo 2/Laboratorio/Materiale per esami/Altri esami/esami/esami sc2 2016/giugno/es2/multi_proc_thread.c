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
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */

//sem_t sem_cs;
sem_t sem_filled;
sem_t sem_empty;

void enqueue(int x) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */

    sem_wait(&sem_empty);
   // sem_wait(&sem_cs);

    buffer[write_index] = x;
    write_index = (write_index + 1) % BUFFER_LENGTH;

   // sem_post(&sem_cs);
    sem_post(&sem_filled);

}

int dequeue() {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */
    int x;

    sem_wait(&sem_filled);
    //sem_wait(&sem_cs);

    x = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_LENGTH;

    //sem_post(&sem_cs);
    sem_post(&sem_empty);

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
     * COMPLETARE QUI
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

    thread_args_t* arg = (thread_args_t*)args;

    if(arg->role == PROD_ROLE){
        producer(arg->child_id, arg->write_count);
    }
    else if(arg->role == CONS_ROLE){
        if(arg->read_count>arg->write_count) arg->read_count = arg->write_count;
        consumer(arg->child_id, arg->read_count);
    }

     pthread_exit(NULL);
}

void child_routine(int child_id) {
    srand(SEED);

    /**
     * COMPLETARE QUI
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

    //if(sem_init(&sem_cs, 0, 1) != 0) printf("Errore sem_init");
    if(sem_init(&sem_empty, 0, BUFFER_LENGTH) != 0) printf("Errore sem_init");
    if(sem_init(&sem_filled, 0 ,0) != 0) printf("Errore sem_init");

    pthread_t prod_t, cons_t;

    thread_args_t* args_prod = (thread_args_t*)malloc(sizeof(thread_args_t));
    args_prod->child_id = child_id;
    args_prod->role = PROD_ROLE;
    args_prod->read_count = READ_COUNT;
    args_prod->write_count = WRITE_COUNT;

    thread_args_t* args_cons = (thread_args_t*)malloc(sizeof(thread_args_t));
    args_cons->child_id = child_id;
    args_cons->role = CONS_ROLE;
    args_cons->read_count = READ_COUNT;
    args_cons->write_count = WRITE_COUNT;

    int ret;
    ret = pthread_create(&prod_t, NULL, thread_routine, args_prod);
    if(ret != 0) printf("Errore pthread_create");

    ret = pthread_create(&cons_t, NULL, thread_routine, args_cons);
    if(ret != 0) printf("Errore pthread_create");

    ret = pthread_join(prod_t, NULL);
    if(ret != 0) printf("Errore pthread_join");

    ret = pthread_join(cons_t, NULL);
    if(ret != 0) printf("Errore pthread_join");

    free(args_prod);
    free(args_cons);

    //ret = sem_destroy(&sem_cs);
    //if(ret != 0) printf("Errore sem_destroy");
    ret = sem_destroy(&sem_empty);
    if(ret != 0) printf("Errore sem_destroy");
    ret = sem_destroy(&sem_filled);
    if(ret != 0) printf("Errore sem_destroy");

}

int main(int argc, char* argv[]) {

    // inizializzazioni
    read_index = write_index = 0;

    /**
     * COMPLETARE QUI
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

    int i;
    for(i = 0; i<CHILD_COUNT; i++){
        pid = fork();
        if(pid == -1){
            printf("Errore fork");
        }
        else if(pid == 0){
            child_routine(i);
            break;
        }
    }

    if(i == CHILD_COUNT){
        for(i = 0; i<CHILD_COUNT; i++){
            int ret = wait(NULL);
            ERROR_HELPER(ret, "Errore nella wait");
        }
    }

    return EXIT_SUCCESS;
}
