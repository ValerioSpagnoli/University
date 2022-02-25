#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "common.h"

int send_over_fifo(int fifo_desc, void* data, size_t data_len) {
    /**
     * SOLUZIONE
     * 
     * Obiettivi:
     * - inviare al client i primi 'data_len' bytes contenuti in data
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i 'data_len' byte siano stati scritti
     * - restituire il numero di bytes scritti
     **/
    int ret, bytes_sent = 0;

    while (bytes_sent < data_len) {
        ret = write(fifo_desc, data + bytes_sent, data_len - bytes_sent);
        
        if (ret == -1 && errno == EINTR) continue;
        ERROR_HELPER(ret, "Impossibile scrivere su FIFO");
        
        bytes_sent += ret;
    }
    
    return bytes_sent;
}

int read_from_fifo(int fifo_desc, void* data, size_t data_len) {
     /**
     * SOLUZIONE
     * 
     * Obiettivi:
     * - ricevere dal client 'data_len' bytes e memorizzarli in data
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i 'data_len' bytes siano stati letti
     * - restituire il numero di bytes letti
     **/   
    int ret, bytes_read = 0;

    while (bytes_read < data_len) {
        ret = read(fifo_desc, data + bytes_read, data_len - bytes_read);
        
        if (ret == -1 && errno == EINTR) continue;
        if (ret == 0) ERROR_HELPER(-1, "Chiusura inattesa FIFO nello slave");
        ERROR_HELPER(ret, "Impossibile scrivere su FIFO");
        
        bytes_read += ret;
    }
    
    return bytes_read;
}

void create_fifo(char* name, mode_t mode) {
    /**
     * SOLUZIONE
     * 
     * Obiettivi:
     * - creare una FIFO con nome e permessi specificati dagli argomenti
     * - gestire eventuali errori
     * - BONUS: se la creazione fallisce perché la FIFO richiesta è già
     *   esistente, tentare di risolvere l'errore
     **/   
    
    int ret = mkfifo(name, mode);
    if (ret == -1 && errno == EEXIST) {
        ret = unlink(name);
        ERROR_HELPER(ret, "Impossibile rimuovere FIFO");
        
        printf("[WARNING] FIFO \"%s\" preesistente rimossa!\n", name);
        
        ret = mkfifo(name, mode);
    }
    ERROR_HELPER(ret, "Impossibile creare FIFO");
}

int main(int args, char* argv[]) {    
    /**
     * SOLUZIONE
     * 
     * Obiettivi:
     * - creare tramite la create_fifo() definita in alto due FIFO con
     *   nomi specificati dalle macro FIRST_FIFO_NAME e SECOND_FIFO_NAME
     * - nell'ordine seguente, aprire FIRST_FIFO_NAME in modo che il
     *   processo corrente possa scriverci ed aprire SECOND_FIFO_NAME per
     *   leggere le risposte dal client; salvare i descrittori ottenuti
     *   rispettivamente in 'first_fifo' e 'second_fifo'
     * - gestire eventuali errori di apertura
     **/
    
    create_fifo(FIRST_FIFO_NAME, 0666);
    create_fifo(SECOND_FIFO_NAME, 0666);
    
    int first_fifo = open(FIRST_FIFO_NAME, O_WRONLY);
    ERROR_HELPER(first_fifo, "Impossibile aprire FIFO");
    
    int second_fifo = open(SECOND_FIFO_NAME, O_RDONLY);
    ERROR_HELPER(second_fifo, "Impossibile aprire FIFO");
        
    myStruct* S = initialize_struct();
    uint32_t checksum = get_struct_checksum(S);
    printf("Checksum: %u\n", checksum);
    
    void* data = get_struct_for_fifo_write(S);
    size_t len = get_struct_len_for_fifo_write(S);
    
    send_over_fifo(first_fifo, &len, sizeof(len));
    send_over_fifo(first_fifo, data, len);
    
    uint32_t slave_checksum;
    read_from_fifo(second_fifo, &slave_checksum, sizeof(slave_checksum));
    
    if (checksum == slave_checksum) {
        printf("Invio riuscito, checksum ricevuto coincide!\n");
    } else {
        fprintf(stderr, "Errore! Checksum ricevuto: %u\n", slave_checksum);
    }
 
    /**
     * SOLUZIONE
     * 
     * Obiettivi:
     * - chiusura descrittori e rimozione delle FIFO dal sistema
     * - gestire eventuali errori
     **/
    
    int ret = close(first_fifo);
    ERROR_HELPER(ret, "Impossibile chiudere prima FIFO");
    
    ret = close(second_fifo);
    ERROR_HELPER(ret, "Impossibile chiudere seconda FIFO");
    
    ret = unlink(FIRST_FIFO_NAME);
    ERROR_HELPER(ret, "Impossibile rimuovere prima FIFO");
    
    ret = unlink(SECOND_FIFO_NAME);
    ERROR_HELPER(ret, "Impossibile rimuovere seconda FIFO");
    
    free(data);
    free_struct(S);
    
    return 0;
}
