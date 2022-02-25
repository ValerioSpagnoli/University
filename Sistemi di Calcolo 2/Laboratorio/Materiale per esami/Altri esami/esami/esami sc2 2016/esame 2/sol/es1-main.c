#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common.h"

int send_over_pipe(int write_desc, char* buf, size_t data_len) {
    int ret, bytes_sent = 0;

	/**
     * SOLUZIONE
     *
     * Obiettivi:
     * - inviare sulla pipe tutti i data_len byte contenuti nel buffer buf 
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i byte siano stati scritti
     */
	 
    while (bytes_sent < data_len) {
        ret = write(write_desc, buf + bytes_sent, data_len - bytes_sent);
        
        if (ret == -1 && errno == EINTR) continue;
        ERROR_HELPER(ret, "Impossibile scrivere su pipe");
        
        bytes_sent += ret;
    }
    
    return bytes_sent;
}

int read_from_pipe(int read_desc, char* buf, size_t buf_len) {
    int ret, bytes_read = 0;
    
	/**
	 * SOLUZIONE
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
	 
    while (1) {
        ret = read(read_desc, buf + bytes_read, 1);
        
        if (ret == -1 && errno == EINTR) continue;
        ERROR_HELPER(ret, "Impossibile leggere da pipe");
        
        if (ret == 0) ERROR_HELPER(-1, "Chiusura inattesa pipe");
            
        if (buf[bytes_read++] == '\n') break;
        
        if (bytes_read == buf_len) ERROR_HELPER(-1, "Messaggio troppo lungo");
    }
    
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
    pid_t pid;
	
    srand(SEED);
    
	/**
     * SOLUZIONE
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
    ERROR_HELPER(ret, "Impossibile creare pipe");
    
    ret = pipe(second_pipe);
    ERROR_HELPER(ret, "Impossibile creare pipe");
    
    pid = fork();
    
    if (pid == -1) {
        ERROR_HELPER(-1, "Impossibile fare fork()");
    } else if (pid == 0) {
        // processo figlio
        ret = close(first_pipe[0]);
        ERROR_HELPER(ret, "[figlio] impossibile chiudere first_pipe[0]");
        
        ret = close(second_pipe[1]);
        ERROR_HELPER(ret, "[figlio] impossibile chiudere second_pipe[1]");
        
        child_loop(first_pipe[1], second_pipe[0]);
        
        ret = close(first_pipe[1]);
        ERROR_HELPER(ret, "[figlio] impossibile chiudere first_pipe[1]");
        
        ret = close(second_pipe[0]);
        ERROR_HELPER(ret, "[figlio] impossibile chiudere second_pipe[0]");
    } else {
        // processo padre
        ret = close(first_pipe[1]);
        ERROR_HELPER(ret, "[padre] impossibile chiudere first_pipe[1]");
        
        ret = close(second_pipe[0]);
        ERROR_HELPER(ret, "[padre] impossibile chiudere second_pipe[0]");
        
        parent_loop(first_pipe[0], second_pipe[1]);
        
        ret = wait(0);
        ERROR_HELPER(ret, "[padre] wait sul processo figlio fallita");
        
        ret = close(first_pipe[0]);
        ERROR_HELPER(ret, "[padre] impossibile chiudere first_pipe[0]");
        
        ret = close(second_pipe[1]);
        ERROR_HELPER(ret, "[padre] impossibile chiudere second_pipe[1]");
    }
    
    
    return 0;
}
