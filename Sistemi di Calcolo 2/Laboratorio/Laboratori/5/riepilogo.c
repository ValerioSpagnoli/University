#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>

// macros for error handling
#include "common.h"

#define N 10     // child process count
#define M 3      // thread per child process count
#define T 1      // time to sleep for main process

#define FILENAME	"accesses.log"

#define SHM_NAME "/shm_notify"
#define SEM_CS "/sem_cs"
#define SEM_CHILDTOMAIN "/sem_childTOmain"
#define SEM_MAINTOCHILD "/sem_mainTOchild"

/*
 * data structure required by threads
 */
typedef struct thread_args_s {
    unsigned int child_id;
    unsigned int thread_id;
} thread_args_t;

/*
 * parameters can be set also via command-line arguments
 */
int n = N, m = M, t = T;


sem_t* sem_cs;          //semaforo per la sezione critica
sem_t* sem_mainTOchild; //il main deve aspettare che tutti i figli inizino
sem_t* sem_childTOmain; //i figli devono attendere la notifica del main per iniziare
int shm;                //descrittore shm per notifica
int* notify;            //shm: se 0 i figli non possono procedere o devono terminare, 1 altrimenti


/*
 * Ensures that an empty file with given name exists.
 */
void init_file(const char *filename) {
    printf("[Main] Initializing file %s...", FILENAME);
    fflush(stdout);
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd<0) handle_error("error while initializing file");
    close(fd);
    printf("closed...file correctly initialized!!!\n");
}

/*
 * Create a named semaphore with a given name, mode and initial value.
 * Also, tries to remove any pre-existing semaphore with the same name.
 */
sem_t *create_named_semaphore(const char *name, mode_t mode, unsigned int value) {
    printf("[Main] Creating named semaphore %s...", name);
    fflush(stdout);

    sem_unlink(name);
    sem_t* sem = sem_open(name, O_CREAT | O_EXCL, mode, value);
    if(sem == SEM_FAILED) handle_error("sem_open error");

    printf("done!!!\n");
    return sem;
}


void parseOutput() {
    // identify the child that accessed the file most times
    int* access_stats = calloc(n, sizeof(int)); // initialized with zeros
    printf("[Main] Opening file %s in read-only mode...", FILENAME);
	fflush(stdout);
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) handle_error("error while opening output file");
    printf("ok, reading it and updating access stats...");
	fflush(stdout);

    size_t read_bytes;
    int index;
    do {
        read_bytes = read(fd, &index, sizeof(int));
        if (read_bytes > 0)
            access_stats[index]++;
    } while(read_bytes > 0);
    printf("ok, closing it...");
	fflush(stdout);

    close(fd);
    printf("closed!!!\n");

    int max_child_id = -1, max_accesses = -1, i;
    for (i = 0; i < n; i++) {
        printf("[Main] Child %d accessed file %s %d times\n", i, FILENAME, access_stats[i]);
        if (access_stats[i] > max_accesses) {
            max_accesses = access_stats[i];
            max_child_id = i;
        }
    }
    printf("[Main] ===> The process that accessed the file most often is %d (%d accesses)\n", max_child_id, max_accesses);
    free(access_stats);
}


void* thread_function(void* x) {
    thread_args_t *args = (thread_args_t*)x;

    int ret;

    ret = sem_wait(sem_cs);
    if(ret == -1) handle_error("sem_wait error");

    // open file, write child identity and close file
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd < 0) handle_error("error while opening file");
    printf("[Child#%d-Thread#%d] File %s opened in append mode!!!\n", args->child_id, args->thread_id, FILENAME);



    write(fd, &(args->child_id), sizeof(int));
    printf("[Child#%d-Thread#%d] %d appended to file %s opened in append mode!!!\n", args->child_id, args->thread_id, args->child_id, FILENAME);

    ret = sem_post(sem_cs);
    if(ret == -1) handle_error("sem_post error");

    close(fd);
    printf("[Child#%d-Thread#%d] File %s closed!!!\n", args->child_id, args->thread_id, FILENAME);

    free(x);
    pthread_exit(NULL);
}

void childProcess(int child_id) {

    int ret;

    printf("CHILD_%d -> Notifico al main che sono pronto\n", child_id);
    ret = sem_post(sem_mainTOchild);
    if(ret == -1) handle_error("sem_post error");

    printf("CHILD_%d -> Attendo che il main mi notifichi di iniziare le attività\n", child_id);
    ret = sem_wait(sem_childTOmain);
    if(ret == -1) handle_error("sem_wait error");

    pthread_t* thread = (pthread_t*)malloc(m*sizeof(pthread_t));

    while(1){
        memset(thread, 0, m*sizeof(pthread_t));

        printf("CHILD_%d -> Creo %d thread.\n", child_id, m);
        int i;
        for(i = 0; i<m; i++){
            thread_args_t* args = (thread_args_t*)malloc(sizeof(thread_args_t));
            args->child_id = child_id;
            args->thread_id = i;
            if(pthread_create(&thread[i], NULL, thread_function, args) == -1) handle_error("pthread_create error");
        }

        printf("CHILD_%d -> Aspetto che terminano tutti i thread.\n", child_id);
        for(i = 0; i<m; i++){
            ret = pthread_join(thread[i], NULL);
            if(ret == -1) handle_error("pthread_join error");
        }
        printf("CHILD_%d -> I thread hanno terminato\n", child_id);

        printf("CHILD_%d -> Controllo che il mainProcess abbia notificato la terminazione\n", child_id);
        if(*notify == 0){
            printf("CHILD_%d -> Il mainProcess ha notificato la terminazione ... termino\n", child_id);
            break;
        }
        else{
            printf("CHILD_%d -> Il mainProcess non ha notificato la terminazione ... continuo\n", child_id);
        }
    }


    if(sem_close(sem_cs) == -1) handle_error("sem_close error");
    if(sem_close(sem_childTOmain) == -1) handle_error("sem_close error");
    if(sem_close(sem_mainTOchild) == -1) handle_error("sem_close error");
    if(munmap(notify, sizeof(int)) == -1) handle_error("munmap error");
    if(close(shm) == -1) handle_error("close shm error");
}


void mainProcess() {
    int ret;

    printf("MAIN_PROCESS -> Creo %d processi figli\n", n);

    int i;
    for(i = 0; i<n; i++){
        printf("MAINPROCESS -> **** Creo child_%d ****\n", i);
        pid_t pid = fork();
        if(pid == -1){
            handle_error("fork error");
        }
        else if(pid == 0){
            childProcess(i);
            _exit(EXIT_SUCCESS);
        }
        printf("MAINPROCESS -> **** CREATO child_%d ****\n", i);
    }

    printf("MAIN_PROCESS -> I processi figli sono stati creati, aspetto che siano tutti pronti\n");
    for(i = 0; i<n; i++){
        printf("MAIN_PROCESS -> **** Aspetto child_%d ****\n", i);
        ret = sem_wait(sem_mainTOchild);
        if(ret == -1) handle_error("sem_wait error");
    }
    printf("MAIN_PROCESS -> I processi figli sono pronti\n");

    printf("MAIN_PROCESS -> Notifico ai processi figli che possono iniziare le loro attività\n");
    for(i = 0; i<n; i++){
        ret = sem_post(sem_childTOmain);
        if(ret == -1) handle_error("sem_post error");
    }
    printf("MAIN_PROCESS -> I processi figli sono stati tutti notificati\n");

    printf("MAIN_PROCESS -> Dormo per %d secondi\n", t);
    sleep(t);

    printf("MAIN_PROCESS -> Notifico ai processi figli che devono terminare le loro attività\n");
    *notify = 1;

    printf("MAIN_PROCESS -> Attendo la terminazione di tutti i processi figli\n");

    for(i = 0; i<n; i++){
        int status;
        if(wait(&status) == -1) handle_error("wait error");
        if (WEXITSTATUS(status)) handle_error("child error");
    }

    printf("MAIN_PROCESS -> Tutti i processi figli hanno terminato le loro attività\n");
    printf("MAIN_PROCESS -> Identifico il processo che ha fatto più accessi in sezione critica\n");

    parseOutput();

}


int main(int argc, char **argv) {
    // arguments
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) m = atoi(argv[2]);
    if (argc > 3) t = atoi(argv[3]);

    // initialize the file
    init_file(FILENAME);

    sem_cs = create_named_semaphore(SEM_CS, 0600, 1);
    sem_childTOmain = create_named_semaphore(SEM_CHILDTOMAIN, 0600, 0);
    sem_mainTOchild = create_named_semaphore(SEM_MAINTOCHILD, 0600, 0);

    notify = (int*)malloc(sizeof(int));

    shm_unlink(SHM_NAME);
    shm = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    if(shm == -1) handle_error("shm_open error");
    if(ftruncate(shm, sizeof(int)) == -1) handle_error("ftruncate error");
    notify = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    *notify = 0;

    mainProcess();

    printf("[Main] Libero le risorse ...\n");

    if(sem_close(sem_cs) == -1) handle_error("sem_close error");
    if(sem_unlink(SEM_CS) == -1) handle_error("sem_unlink error");

    if(sem_close(sem_childTOmain) == -1) handle_error("sem_close error");
    if(sem_unlink(SEM_CHILDTOMAIN) == -1) handle_error("sem_unlink error");

    if(sem_close(sem_mainTOchild) == -1) handle_error("sem_close error");
    if(sem_unlink(SEM_MAINTOCHILD) == -1) handle_error("sem_unlink error");

    if(munmap(notify, sizeof(int)) == -1) handle_error("munmap error");
    if(close(shm) == -1) handle_error("close shm error");
    if(shm_unlink(SHM_NAME) == -1) handle_error("shm_unlink error");

    printf("[Main] Fatto!\n");

    exit(EXIT_SUCCESS);
}
