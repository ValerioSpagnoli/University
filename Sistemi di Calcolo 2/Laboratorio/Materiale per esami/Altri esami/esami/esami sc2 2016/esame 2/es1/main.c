#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common.h"

int send_over_pipe(int write_desc, char* buf, size_t data_len) {
    int ret, bytes_sent = 0;

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - inviare sulla pipe tutti i data_len byte contenuti nel buffer buf
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i byte siano stati scritti
     */

    while(bytes_sent < data_len){
        ret = write(write_desc, buf+bytes_sent, data_len-bytes_sent);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) printf("Errore send");
        bytes_sent += ret;
    }


    return bytes_sent;
}

int read_from_pipe(int read_desc, char* buf, size_t buf_len) {
    int ret, bytes_read = 0;

	/**
	 * COMPLETARE QUI
     *
     * Obiettivi:
	 * - leggere un messaggio dalla pipe e salvarlo nel buffer buf
     * - gestire eventuali interruzioni ed errori
     * - salvare il numero di byte ricevuti nella variabile 'bytes_read'
     *   e il valore restituito da una singola lettura in 'ret'
     * - gestire chiusure inattese della connessione da parte del
     *   client uscendo dal loop usato per la lettura
     *
     * Si tenga a mente che l'ultimo byte valido in un messaggio (la
     * cui lunghezza NON è nota a priori) è il terminatore di riga '\n'.
	 **/

    do{
        ret = read(read_desc, buf+bytes_read, 1);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) printf("Errore send");
        if(ret == 0) break;
        bytes_read += ret;

    } while(buf[bytes_read-1] != '\n');


    return bytes_read;
}

void child_loop(int write_desc, int read_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int num = rand() % MAX_NUM;
        sprintf(buf, "%d\n", num);
        send_over_pipe(write_desc, buf, strlen(buf));
        //printf("[figlio] %s", buf);

        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[figlio] msg %d: %s\n", i, buf);
    }
}

void parent_loop(int read_desc, int write_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[padre]  msg %d: %s\n", i, buf);

        int num = atoi(buf);
        sprintf(buf, "%d\n", 2*num);
        send_over_pipe(write_desc, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]) {
    int ret, first_pipe[2], second_pipe[2];

    srand(SEED);

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
	 * - creazione di due pipe: utilizzare 'first_pipe' e 'second_pipe':
     * - creazione processo figlio
     * - un processo userà 'first_pipe' per comunicare dati all'altro e
     *   'second_pipe' per ricevere dati, l'altro farà il viceversa
	 * - chiusura estremità pipe non utilizzate in padre e figlio
     * - il processo figlio chiama child_loop() che prende come 1° arg.
     *   il descrittore pipe in scrittura per inviare dati al padre e
     *   e come 2° arg. il descrittore pipe in lettura da cui ricevere
     *   dati dal padre
     * - il processo padre chiama parent_loop() che prende come 1° arg.
     *   il descrittore pipe in lettura per ricevere dati dal figlio e
     *   e come 2° arg. il descrittore pipe in scrittura per inviare
     *   dati al figlio
	 * - il padre deve attendere la terminazione del figlio per uscire
	 * - chiusura descrittori pipe in fase di uscita
     * - gestire eventuali errori
     */

    ret = pipe(first_pipe);
    if(ret != 0) printf("Errore pipe");
    ret = pipe(second_pipe);
    if(ret != 0) printf("Errore pipe");

    pid_t pid = fork();
    if(pid == -1){
        printf("Errore fork");
    }
    else if(pid == 0){
        ret = close(first_pipe[1]);
        if(ret != 0) printf("Errore close1");
        ret = close(second_pipe[0]);
        if(ret != 0) printf("Errore close2");

        child_loop(second_pipe[1], first_pipe[0]);

        ret = close(first_pipe[0]);
        if(ret != 0) printf("Errore close3");
        ret = close(second_pipe[1]);
        if(ret != 0) printf("Errore close4");

        _exit(EXIT_SUCCESS);
    }
    else{
        ret = close(first_pipe[0]);
        if(ret != 0) printf("Errore close5");
        ret = close(second_pipe[1]);
        if(ret != 0) printf("Errore close6");

        parent_loop(second_pipe[0], first_pipe[1]);

        ret = wait(NULL);

        ret = close(first_pipe[1]);
        if(ret != 0) printf("Errore close7");
        ret = close(second_pipe[0]);
        if(ret != 0) printf("Errore close8");
    }





    return 0;
}
