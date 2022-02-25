#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common.h"

int pipefd_pTOc[2];
int pipefd_cTOp[2];

void send_over_pipe(int write_desc, char* buf, size_t data_len) {

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - scrivere sulla pipe tutti i data_len byte contenuti nel buffer buf
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i byte siano stati scritti
     */

    int ret;
    int written_bytes = 0;
    while(written_bytes < data_len){
        ret = write(write_desc, buf+written_bytes, data_len-written_bytes);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("Errore write");
        written_bytes += ret;
    }

}

int read_from_pipe(int read_desc, char* buf, size_t buf_len) {

	/**
	 * COMPLETARE QUI
     *
     * Obiettivi:
     * - leggere un messaggio dalla pipe e salvarlo nel buffer buf
     * - il valore di ritorno di questa funzione deve essere pari al numero di
     *   byte letto dalla pipe (incluso il delimitatore di fine messaggio)
     * - gestire eventuali chiusure della pipe da parte dell'altro processo come se fosse un errore
     * - gestire come un errore il caso in cui il messaggio sia troppo grande rispetto al buffer a disposizione
     * - gestire eventuali interruzioni ed errori
     *
     * Il delimitatore di fine messaggio è il terminatore di riga '\n'.
	 **/

    int ret;
    int read_bytes = 0;

    do{
        ret = read(read_desc, buf+read_bytes, 1);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("Errore read");
        if(ret == 0) handle_error("Chiusura inaspettata");
        read_bytes += ret;
        if(read_bytes == buf_len) handle_error("Messaggio troppo lungo");
    } while(buf[read_bytes-1] != '\n');

    return read_bytes;

}

void child_loop(int write_desc, int read_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int num = rand() % MAX_NUM;
        sprintf(buf, "%d\n", num);
        //printf("[FIGLIO] Scrivo sulla pipe\n");
        send_over_pipe(write_desc, buf, strlen(buf));

        //printf("[FIGLIO] Leggo dalla pipe\n");
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[Figlio] ricevuto msg #%d: %s\n", i, buf);
    }
}

void parent_loop(int read_desc, int write_desc) {
    char buf[BUF_SIZE];

    int i;
    for (i = 0; i < NUM_MSG; ++i){
        //printf("[PADRE] Leggo dalla pipe\n");
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[Padre] ricevuto msg #%d: %s\n", i, buf);

        int num = atoi(buf);
        sprintf(buf, "%d\n", 2*num);
        //printf("[PADRE] Scrivo sulla pipe\n");
        send_over_pipe(write_desc, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]) {

    srand(SEED);

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
	 * - creare due pipe
     * - creare un processo figlio
     * - chiudere i descrittori di pipe non utilizzati nel padre e nel figlio
     * - il processo figlio chiama child_loop(), che prende come argomenti i
     *   descrittori di pipe per scrivere/leggere (vedere signature funzione)
     * - il processo padre chiama parent_loop(), che prende come argomenti i
     *   descrittori di pipe per leggere/scrivere (vedere signature funzione)
	 * - il padre deve attendere il termine del figlio prima di terminare a sua
     *   volta
	 * - chiudere i descrittori di pipe in fase di uscita
     * - gestire eventuali errori
     */

    int ret;

    ret = pipe(pipefd_pTOc); //padre scrive al figlio
    if(ret == -1) handle_error("Errore creazione pipe pTOc");

    ret = pipe(pipefd_cTOp); //figlio scrive al padre
    if(ret == -1) handle_error("Errore creazione pipe cTOp");

    pid_t pid = fork();
    if(pid == -1) handle_error("Errore fork");
    else if(pid == 0){
        if(close(pipefd_cTOp[0]) == -1) handle_error("Errore close(pipefd_cTOp[0])");
        if(close(pipefd_pTOc[1]) == -1) handle_error("Errore close(pipefd_pTOc[1])");

        child_loop(pipefd_cTOp[1], pipefd_pTOc[0]); //prende il descrittore per scrivere al padre e per leggere dal padre

        if(close(pipefd_cTOp[1]) == -1) handle_error("Errore close(pipefd_cTOp[1])");
        if(close(pipefd_pTOc[0]) == -1) handle_error("Errore close(pipefd_pTOc[0])");

        _exit(EXIT_SUCCESS);
    }
    else{
        if(close(pipefd_cTOp[1]) == -1) handle_error("Errore close(pipefd_cTOp[1])");
        if(close(pipefd_pTOc[0]) == -1) handle_error("Errore close(pipefd_pTOc[0])");

        parent_loop(pipefd_cTOp[0], pipefd_pTOc[1]); //prende il descrittore per scrivere al figlio e per leggere dal figlio

        int status;
        ret = wait(&status);
        if(ret == -1) handle_error("Errore wait");
        if(WEXITSTATUS(status)) handle_error("Errore figlio");

        if(close(pipefd_cTOp[0]) == -1) handle_error("Errore close(pipefd_cTOp[0])");
        if(close(pipefd_pTOc[1]) == -1) handle_error("Errore close(pipefd_pTOc[1])");
    }

    return 0;
}
