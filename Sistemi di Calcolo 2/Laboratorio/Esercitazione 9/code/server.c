#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/socket.h>

#include "common.h"

#ifdef SERVER_SERIAL
// nothing to do here
#elif SERVER_MPROC
// nothing to do here
#elif SERVER_MTHREAD
#include <pthread.h>
typedef struct handler_args_s
{
    /** COMPLETE THE FOLLOWING CODE BLOCK
     *
     * Specify fields for the arguments that will be populated in the
     * main thread and then accessed in thread_connection_handler(void* arg).
     **/
     int client_desc;
     struct sockaddr_in client_addr;

} handler_args_t;
#endif

void connection_handler(int socket_desc, struct sockaddr_in* client_addr) {
    int ret, recv_bytes, bytes_sent;

    char buf[1024];
    size_t buf_len = sizeof(buf);
    int msg_len;
    memset(buf, 0, buf_len);

    char* quit_command = SERVER_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Suggestions:
    * - Parse the ip address of the client and the port number of the client
    **/

    char client_ip[INET_ADDRSTRLEN] = {0};
    uint16_t client_port = 0;

    sprintf(buf, "Hi! I'm an echo server. You are %s talking on port %hu.\nI will send you back whatever"
            " you send me. I will stop if you send me %s :-)\n", client_ip, client_port, quit_command);
    msg_len = strlen(buf);

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Suggestions:
    * - Send to the client the welcome message written in buf
    **/

    bytes_sent = 0;
    while(bytes_sent < msg_len){
        ret = send(socket_desc, buf+bytes_sent, msg_len-bytes_sent, 0);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("[Server] Errore send");
        bytes_sent+=ret;
    }

    if(DEBUG) fprintf(stderr, "Sent welcome message of %d bytes\n", bytes_sent);

    while (1) {

        /** COMPLETE THE FOLLOWING CODE BLOCK
        *
        * Suggestions:
        * - Read the message from, the client;
        * - Check if it is the quit message, in that case exit from the loop;
        * - Otherwise send back to the client the received message;
        **/
        memset(buf, 0, sizeof(buf));

        recv_bytes = 0;
        do{
            ret = recv(socket_desc, buf+recv_bytes, 1, 0);
            if(ret == -1 && errno == EINTR) continue;
            if(ret == -1) handle_error("[Server] Errore recv");
            if(ret == 0) break;
            recv_bytes+=ret;
        } while(buf[recv_bytes-1] != '\n' && recv_bytes < buf_len);

        if(DEBUG) fprintf(stderr, "Recived message of %d bytes\n", recv_bytes);

        if(recv_bytes == quit_command_len && !memcmp(buf, quit_command, quit_command_len)){
            if(DEBUG) fprintf(stderr, "Recived QUIT message\n");
            break;
        }

        msg_len = sizeof(buf);

        bytes_sent = 0;
        while(bytes_sent < msg_len){
            ret = send(socket_desc, buf+bytes_sent, msg_len-bytes_sent, 0);
            if(ret == -1 && errno == EINTR) continue;
            if(ret == -1) handle_error("[Server] Errore send");
            bytes_sent+=ret;
        }

        if(DEBUG) fprintf(stderr, "Sent message of %d bytes back\n", bytes_sent);

    }

    // close socket
    ret = close(socket_desc);
    if(ret) handle_error("Cannot close socket for incoming connection");
}

#ifdef SERVER_SERIAL
void serialServer(int server_desc) {
    // we initialize client_addr to zero
    struct sockaddr_in client_addr = {0};

    // loop to handle incoming connections serially
    int sockaddr_len = sizeof(struct sockaddr_in);
    while (1) {
        int client_desc = accept(server_desc, (struct sockaddr*) &client_addr, (socklen_t*) &sockaddr_len);
        if(client_desc == -1 && errno == EINTR) continue; // check for interruption by signals
        if(client_desc < 0) handle_error("Cannot open socket for incoming connection");

        if (DEBUG) fprintf(stderr, "Incoming connection accepted...\n");

        /* We pass the socket descriptor and the address information
         * for the incoming connection to the handler. */
        connection_handler(client_desc, &client_addr);

        if (DEBUG) fprintf(stderr, "Done!\n");

        // reset fields in client_addr
        memset(&client_addr, 0, sizeof(struct sockaddr_in));
    }
}

#elif SERVER_MPROC

void mprocServer(int server_desc) {
    int ret = 0;
    // we initialize client_addr to zero
    struct sockaddr_in client_addr = {0};

    // loop to manage incoming connections forking the server process
    int sockaddr_len = sizeof(struct sockaddr_in);
    while (1) {
        // accept incoming connection
        int client_desc = accept(server_desc, (struct sockaddr *) &client_addr, (socklen_t *)&sockaddr_len);
        // check for interruption by signals
        if(client_desc == -1 && errno == EINTR) continue;
        if(client_desc < 0) handle_error("Cannot open socket for incoming connection");

        if (DEBUG) fprintf(stderr, "Incoming connection accepted...\n");

        /** COMPLETE THE FOLLOWING CODE BLOCK
         *
         * Suggestions:
         * - use fork() to create a child process to handle the request
         * - close descriptors that are not used in the parent and the
         *   child process: note that a connection is closed only when
         *   all the descriptors associated with it have been closed!
         * - connection_handler(client_desc, client_addr) should be
         *   executed by the child process to handle the request
         * - memset(client_addr, 0, sizeof(struct sockaddr_in)) should
         *   be performed in order to be able to accept a new request
         * - free memory where needed
         * - add a debug message in the parent process to inform the
         *   user that a child process has been created
         * - add a debug message in the child process to inform the
         *   user that the request has been handled
         **/

        pid_t p_ret = fork();
        if(p_ret == -1){
            handle_error("[Server] Errore fork");
        }
        else if(p_ret == 0){
            if(DEBUG) fprintf(stderr, "Child process has been created\n");
            ret = close(server_desc);
            if(ret == -1) handle_error("[Server] Errore close(server_desc)");
            if(DEBUG) fprintf(stderr, "Child process has closed server descriptor \n");
            connection_handler(client_desc, &client_addr);
            _exit(0);
        }
        else{
            ret = close(client_desc);
            if(ret == -1) handle_error("[Server] Errore close(client_desc)");
            if(DEBUG) fprintf(stderr, "Parent process has closed server descriptor \n");
            memset(&client_addr, 0, sizeof(struct sockaddr_in));
        }
    }
}

#elif SERVER_MTHREAD

void *thread_connection_handler(void *arg) {

    /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * This is a wrapper method to call connection_handler from the thread.
    * Suggestions:
    * - Use the struct handler_args_t and wrap the argument to call the
    *   method connection_handler
    * - After calling connection_handler free all the resources used by the thread
    *   and close the thread;
    **/
    handler_args_t *args = (handler_args_t*) arg;
    connection_handler(args->client_desc, &args->client_addr);
    free(args);
    pthread_exit(0);
}

void mthreadServer(int server_desc) {
    int ret = 0;
    // we allocate client_addr dynamically and initialize it to zero
    struct sockaddr_in* client_addr = calloc(1, sizeof(struct sockaddr_in));

    // loop to manage incoming connections spawning handler threads
    int sockaddr_len = sizeof(struct sockaddr_in);
    while (1) {
        // accept incoming connection
        int client_desc = accept(server_desc, (struct sockaddr*) client_addr, (socklen_t*) &sockaddr_len);
        if(client_desc == -1 && errno == EINTR) continue; // check for interruption by signals
        if(client_desc < 0) handle_error("Cannot open socket for incoming connection");

        if (DEBUG) fprintf(stderr, "Incoming connection accepted...\n");

         /** COMPLETE THE FOLLOWING CODE BLOCK
         *
         * Suggestions:
         * - thread_connection_handler(void* arg) is the method to execute in
         *   the thread we are going to spawn, this method is a wrapper that will
         *   call connection_handler with the right arguments.
         * - allocate a handler_args_t data structure and populate it
         *   with the arguments that will be passed to the thread
         * - print a debug message to inform the user that a new thread
         *   has been created to handle the request
         * - since we don't need to pthread_join(), release libpthread's
         *   internal resources after pthread_create()
         * - to accept a new connection while a thread is executing, be
         *   careful: resetting fields in client_addr won't work!
         **/
        pthread_t thread;
        handler_args_t* t_args = malloc(sizeof(handler_args_t));
        t_args->client_desc = client_desc;
        t_args->client_addr = *client_addr;

        ret = pthread_create(&thread, NULL, thread_connection_handler, (void*)t_args);
        if(ret == -1) handle_error("[Server] Errore pthread_create");
        ret = pthread_detach(thread);
        if(ret == -1) handle_error("[Server] Errore pthread_detach");
    }
}

#endif

int main(int argc, char* argv[]) {
    int ret;

    int socket_desc;

    // some fields are required to be filled with 0
    struct sockaddr_in server_addr = {0};

     // we will reuse it for accept()

    // initialize socket for listening
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_desc < 0) handle_error("Could not create socket");

    server_addr.sin_addr.s_addr = INADDR_ANY; // we want to accept connections from any interface
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT); // don't forget about network byte order!

    /* We enable SO_REUSEADDR to quickly restart our server after a crash:
     * for more details, read about the TIME_WAIT state in the TCP protocol */
    int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    if(ret) handle_error("Cannot set SO_REUSEADDR option");

    // bind address to socket
    ret = bind(socket_desc, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in));
    if(ret) handle_error("Cannot bind address to socket");

    // start listening
    ret = listen(socket_desc, MAX_CONN_QUEUE);
    if(ret) handle_error("Cannot listen on socket");

#ifdef SERVER_MPROC
    mprocServer(socket_desc);
#elif SERVER_MTHREAD
    mthreadServer(socket_desc);
#elif SERVER_SERIAL
    serialServer(socket_desc);
#endif

    exit(EXIT_SUCCESS); // this will never be executed
}
