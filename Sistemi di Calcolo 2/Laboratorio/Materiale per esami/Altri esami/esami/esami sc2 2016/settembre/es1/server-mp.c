#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "common.h"

#define BUFFER_LENGTH 1024

void connection_handler(int socket_desc, struct sockaddr_in* client_addr) {
    int ret, bytes_read, bytes_sent;

    char buf[BUFFER_LENGTH];
    size_t msg_len;

    char* quit_command = SERVER_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    // parse client IP address and port
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr->sin_addr), client_ip, INET_ADDRSTRLEN);
    uint16_t client_port = ntohs(client_addr->sin_port); // port number is an unsigned short

	printf("[child] client connesso sulla porta %u\n", client_port);

    // echo loop
    while (1) {
		/**
		 * COMPLETARE QUI
		 *
		 * Obiettivi:
		 * - leggere un messaggio dal client e salvarlo nel buffer buf
		 * - gestire eventuali interruzioni ed errori
		 * - salvare il numero di byte ricevuti nella variabile 'bytes_read'
		 *   e il valore restituito da una singola lettura in 'ret' 
		 * - gestire chiusure inattese della connessione da parte del
		 *   client uscendo dal loop usato per la lettura
		 * - BONUS: gestire la ricezione di messaggi più lunghi di 
		 *   BUFFER_LENGTH terminando l'applicazione
		 * 
		 * Si tenga a mente che l'ultimo byte valido in un messaggio (la
         * cui lunghezza NON è nota a priori) è il terminatore di riga '\n'.
		 **/
		bytes_read = 0;
		
        
        
		
		
        // dal messaggio ricevuto ignoriamo il terminatore di linea
        msg_len = bytes_read - 1;
        buf[msg_len] = '\0';
		
        // verifico se devo terminare (comando "QUIT" ricevuto o connessione chiusa)
        if ((msg_len == quit_command_len && !memcmp(buf, quit_command, quit_command_len)) || ret == 0) break;
		
		printf("[child] msg da client@%u: %s\n", client_port, buf);
		
		
		
		
		
		/**
		 * COMPLETARE QUI
		 * 
         * Obiettivi:
		 * - inviare al client i primi msg_len bytes contenuti in buf
         * - gestire eventuali interruzioni ed errori
         * - assicurarsi che tutti i byte siano stati scritti
		 **/
		bytes_sent = 0; 
		
        
		
		
		
    }

	
    /**
	 * COMPLETARE QUI
     * 
	 * Obiettivi:
	 * - chiudere descrittori in uso
     * - gestire eventuali errori
	 */
	 
	 
	 
}

void parent(int client_desc, struct sockaddr_in* client_addr){
	/**
	 * COMPLETARE QUI
     * 
	 * Obiettivi:
	 * - chiudere descrittori non utilizzati
     * - gestire eventuali errori
	 */
	int ret;
	
	
	
	
	
	// resetto i campi in client_addr
	memset(client_addr, 0, sizeof(struct sockaddr_in));
}

void child(int socket_desc, int client_desc, struct sockaddr_in* client_addr){
	/**
	 * COMPLETARE QUI
     * 
	 * Obiettivi:
	 * - chiudere descrittori non utilizzati
     * - gestire eventuali errori
	 * - al termine della chiamata a connection_handler(), liberare la memoria allocata dinamicamente
	 */
	int ret;
	
	
	
	
	
	printf("[child] gestisco comunicazione con processo client.\n");
	connection_handler(client_desc, client_addr);
	printf("[child] conversazione con client terminata.\n");
	
	
	exit(EXIT_SUCCESS);
}	

int main(int argc, char* argv[]) {
    int ret;

    int socket_desc, client_desc;

    struct sockaddr_in server_addr = {0};
    int sockaddr_len = sizeof(struct sockaddr_in); // we will reuse it for accept()

    // inizializzo la socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    ERROR_HELPER(socket_desc, "[server] ERRORE: impossibile creare la socket");

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT);

    // abilito SO_REUSEADDR per riavviare il server dopo un crash
	int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    ERROR_HELPER(ret, "[server] ERRORE: impossibile settare SO_REUSEADDR");

    // bind address to socket
    ret = bind(socket_desc, (struct sockaddr*) &server_addr, sockaddr_len);
    ERROR_HELPER(ret, "[server] ERRORE: impossibile fare binf indirizzo socket");

    // start listening
    ret = listen(socket_desc, MAX_CONN_QUEUE);
    ERROR_HELPER(ret, "[server] ERRORE: impossibile ascoltare dalla socket");

    // alloco client_addr dinamicamente e lo setto a zero
    struct sockaddr_in* client_addr = calloc(1, sizeof(struct sockaddr_in));

	printf("[server] server avviato, mi metto in attesa di connessioni.\n");
	
    // loop per gestire connessioni seriali
    while (1) {
        client_desc = accept(socket_desc, (struct sockaddr*) client_addr, (socklen_t*) &sockaddr_len);
        if (client_desc == -1 && errno == EINTR) continue; // controllo interrupt
        ERROR_HELPER(client_desc, "[server] ERRORE: impossibile aprire connessione");

        printf("[server] connesione accettata.\n");

		
		/**
		 * COMPLETARE QUI
		 * 
		 * Obiettivi:
		 * - creare un processo figlio
		 * - gestire eventuali errori
		 * - far eseguire la routine parent() al processo padre
		 * - far eseguire la routine child() al processo figlio
		 */
		pid_t pid;

		
    }

    exit(EXIT_SUCCESS); // mai eseguita
}
