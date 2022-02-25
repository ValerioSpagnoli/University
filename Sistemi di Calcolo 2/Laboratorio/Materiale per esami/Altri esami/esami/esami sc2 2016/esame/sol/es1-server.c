#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "common.h"

// array di N semafori per accedere in mutua esclusione ad N contatori
sem_t semaphores[N];
unsigned int shared_counters[N];

// struttura dati con gli argomenti per thread connection_handler
typedef struct handler_args_s {
    int socket_desc;
    struct sockaddr_in* client_addr;
	unsigned int client_id;
} handler_args_t;

unsigned int process_resource(unsigned int client_id, unsigned int resource_id) {
    /**
	 * SOLUZIONE
     * 
	 * Obiettivi:
	 * - gestire la mutua esclusione tra thread che provano ad accedere
     *   alla cella 'resource_id'-esima nella sezione critica
     * - gestire eventuali errori
	 **/	 
	// wait sul semaforo resource_id-esimo per entrare in sezione critica
	int ret = sem_wait(&semaphores[resource_id]);
	ERROR_HELPER(ret, "sem_wait fallita");
	printf("Risorsa %u LOCKED dal client %u! Processamento in corso...\n", resource_id, client_id);
	
	/* inizio sezione critica */
	unsigned int counter_updated = ++shared_counters[resource_id];
	printf("Nuovo contatore per risorsa %u: %u\n", resource_id, counter_updated);
    sleep(SLEEP_TIME);
	/* fine sezione critica */
	
    // post sul semaforo per riabilitare l'accesso alla cella resource_id-esima
	ret = sem_post(&semaphores[resource_id]);
	ERROR_HELPER(ret, "sem_post fallita");
	printf("Risorsa %u UNLOCKED\n", resource_id);
	
	return counter_updated;
}		


void* connection_handler(void* arg) {
    int ret;
    
	handler_args_t* args = (handler_args_t*)arg;
	int socket_desc = args->socket_desc;
    struct sockaddr_in* client_addr = args->client_addr;
	unsigned int client_id = args->client_id;
	
    char buf[1024];
	
    char* quit_command = SERVER_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    // parso il client IP address e la porta
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr->sin_addr), client_ip, INET_ADDRSTRLEN);
    uint16_t client_port = ntohs(client_addr->sin_port); // port number is an unsigned short
	printf("Client %u connesso sulla porta %u \n", client_id, client_port);
	
    // ciclo di scambio messaggi
    unsigned int resource_id;
    while (1) {
		/**
		 * SOLUZIONE
         *
         * Obiettivi:
		 * - leggere un messaggio dal client e salvarlo nel buffer buf
         * - gestire eventuali interruzioni ed errori
         * - salvare il numero di byte ricevuti nella variabile 'bytes_read'
         *   e il valore restituito da una singola lettura in 'ret' 
         * - gestire chiusure inattese della connessione da parte del
         *   client uscendo dal loop usato per la lettura
         * 
         * Si tenga a mente che l'ultimo byte valido in un messaggio (la
         * cui lunghezza NON è nota a priori) è il terminatore di riga '\n'.
		 **/
		
        int bytes_read, bytes_sent;
        
        bytes_read = 0;
		while (1) {
            ret = recv(socket_desc, buf + bytes_read, 1, 0);
			
            if (ret == -1 && errno == EINTR) continue;
            ERROR_HELPER(ret, "Impossibile leggere dalla socket");
            
            if (ret == 0) {
                fprintf(stderr, "Endpoint disconnesso.\n");
                break;
            }
            
            if (buf[bytes_read++] == '\n') break;
			
			if (bytes_read == sizeof(buf)) ERROR_HELPER(-1, "Messaggio ill-formed");
        }
		
		size_t msg_len = bytes_read - 1;
        
        // verifico se devo terminare (comando "QUIT" ricevuto, o endpoint chiuso)
        if ((msg_len == quit_command_len && !memcmp(buf, quit_command, quit_command_len)) || ret == 0) break;
     
        // avvio il processamento della risorsa, aggiorno il relativo contatore e lo salvo in buf
        buf[msg_len] = '\0';
        int tmp = atoi(buf); // devo usare un int per gestire numeri negativi
        resource_id = (tmp > 0 && tmp < N) ? tmp : 0;
        unsigned int counter_updated = process_resource(client_id, resource_id);
        
        sprintf(buf, "[risorsa %u] contatore: %u", resource_id, counter_updated);
        msg_len = strlen(buf);
        buf[msg_len] = '\0';
			
        /**
		 * SOLUZIONE
		 * 
         * Obiettivi:
		 * - inviare al client i primi msg_len bytes contenuti in buf
         * - gestire eventuali interruzioni ed errori
         * - assicurarsi che tutti i byte siano stati scritti
		 **/
        // invio risposta al client
        bytes_sent = 0;
        while (bytes_sent < msg_len) {
            ret = send(socket_desc, buf + bytes_sent, msg_len - bytes_sent, 0);
            if (ret == -1 && errno == EINTR) continue;
            ERROR_HELPER(ret, "Impossibile scrivere sulla socket");
            bytes_sent += ret;
        }
    }

	/**
	 * SOLUZIONE
     * 
	 * Obiettivi:
	 * - chiudere descrittori in uso
     * - gestire eventuali errori
     * - liberare memoria in uso al thread
	 */
	 
    // close socket
    ret = close(socket_desc);
    ERROR_HELPER(ret, "Chiusura client socket fallita");

    printf("Thread connection_handler terminato\n");

	// libero la memoria allocata ed esco
    free(args->client_addr); 
    free(args);
	
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {	  	
	/**
	 * SOLUZIONE
     * 
	 * Obiettivi:
	 * - inizializzare gli N semafori nell'array 'semaphores'
	 * - gestire eventuali errori di inizializzazione
	 **/
	int i, ret;
	for (i = 0; i < N; i++) {
		ret = sem_init(&semaphores[i], 0, 1);
		ERROR_HELPER(ret, "Impossibile inizializzare il semaforo");
	}
	
	// creo le strutture per la socket
	int socket_desc, client_desc;
    struct sockaddr_in server_addr = {0};

    int sockaddr_len = sizeof(struct sockaddr_in); // da riusare per le accept()

    // inizializzo la socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    ERROR_HELPER(socket_desc, "Impossibile creare la socket");

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT);

    // abilito l'opzione SO_REUSEADDR per riavviare il server dopo un crash
    int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    ERROR_HELPER(ret, "Impossibile settare l'opzione SO_REUSEADDR");

    // bind & listen
    ret = bind(socket_desc, (struct sockaddr*) &server_addr, sockaddr_len);
    ERROR_HELPER(ret, "Impossibile fare il binding indirizzo-socket");

    ret = listen(socket_desc, 16);
    ERROR_HELPER(ret, "Impossibile ascoltare dalla socket");

    // alloco client_addr dinamicamente e lo inizializzo a zero
    struct sockaddr_in* client_addr = calloc(1, sizeof(struct sockaddr_in));

    // loop per gestire connessioni in ingresso con nuovi thread
	printf("Server pronto ad accettare connessioni!\n");
	unsigned int client_id = 0;
    while (1) {		 
        // accetto connessioni in ingresso
        client_desc = accept(socket_desc, (struct sockaddr*) client_addr, (socklen_t*) &sockaddr_len);
        if (client_desc == -1 && errno == EINTR) continue; // check per segnali di interruzione
        ERROR_HELPER(client_desc, "Impossibile aprire la socket per connessioni in ingresso.");

        printf("Connessione accettata\n");
        
        /**
		 * SOLUZIONE
		 * 
         * Obiettivi:
		 * - preparare gli argomenti da passare al thread che eseguirà
         *   connection_handler (si veda handler_args_t all'inizio)
         * - creare un thread che esegua connection_handler() passando
         *   la struct con gli argomenti predisposta
         * - gestire eventuali errori
         * 
         * Si tenga a mente che NON verranno effettuate in futuro
         * operazioni di join sul thread appena creato.
		 **/

        pthread_t thread;

        // setto gli argomenti del nuovo thread nel buffer
        handler_args_t* thread_args = malloc(sizeof(handler_args_t));
        thread_args->socket_desc = client_desc;
        thread_args->client_addr = client_addr;
		thread_args->client_id   = client_id;
		
        ret = pthread_create(&thread, NULL, connection_handler, (void*)thread_args);
        PTHREAD_ERROR_HELPER(ret, "pthread_create per connection_handler fallita");            

        ret = pthread_detach(thread); // non voglio fare join su questo thread
        PTHREAD_ERROR_HELPER(ret, "pthread_detach per connection_handler fallita");            
        
        // alloco un nuovo buffer client_addr per la prossima connessione
        client_addr = calloc(1, sizeof(struct sockaddr_in));
        
        // incremento il client ID dopo ogni connessione accettata
        client_id++;
    }

    return 0;
}
