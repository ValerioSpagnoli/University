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

// Method for processing incoming requests. The method takes as argument
// the socket descriptor for the incoming connection.
void* connection_handler(int socket_desc) {
    int ret, recv_bytes, bytes_sent;

    char buf[1024];
    size_t buf_len = sizeof(buf);
    int msg_len;
    memset(buf,0,buf_len);

    char* quit_command = SERVER_COMMAND;
    size_t quit_command_len = strlen(quit_command);

    // send welcome message
    sprintf(buf, "Hi! I'm an echo server. I will send you back whatever"
            " you send me. I will stop if you send me %s", quit_command);
    msg_len = strlen(buf);
    /**
     *  TODO: Sending welcome message
     *
     * Suggestions:
     * - send() with flags = 0 is equivalent to write() to a descriptor
     * - the message you have to send has been written in buf
     * - deal with partially sent messages (message size is not buffer size)
     */

    bytes_sent = 0;
    while(bytes_sent < msg_len){
        ret = send(socket_desc, buf+bytes_sent, msg_len-bytes_sent, 0);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("send error");
        bytes_sent += ret;
    }

    if (DEBUG) fprintf(stderr, "Welcome message <<%s>> has been sent\n",buf);

    // echo loop
    while (1) {
		/**
         *  TODO: Receive the command
         *
         * Suggestions:
         * - recv() with flags = 0 is equivalent to read() from a descriptor
         * - store the number of received bytes in recv_bytes
         * - for sockets, we get a 0 return value only when the peer closes
         *   the connection: if there are no bytes to read and we invoke
         *   recv() we will get stuck, because the call is blocking!
         * - deal with partially sent messages (we do not know the message size)
         */

        recv_bytes = 0;
        do{
            ret = recv (socket_desc, buf+recv_bytes, 1, 0);
            if(ret == -1 && errno == EINTR) continue;
            if(ret == -1) handle_error("recv error");
            if(ret == 0) handle_error("connection closed");
            recv_bytes += ret;
        } while(buf[recv_bytes-1] != '\n');

        if (DEBUG) fprintf(stderr, "Received command of %d bytes...\n",recv_bytes);

        /**
         *  TODO: check if the quit_command is received
         *  TODO: in this case we have to quit from the echo loop
         *
         * Suggestions:
         * - compare the number of bytes received with the length of the
         *   quit command that tells the server to close the connection
         *   (see SERVER_COMMAND macro in common.h)
         * - perform a byte-to-byte comparsion when required using
         *   memcmp(const void *ptr1, const void *ptr2, size_t num)
         * - exit from the cycle when there is nothing to send back
         */

        if(recv_bytes == quit_command_len && !memcmp(buf, quit_command, quit_command_len)) break;

        // ...or I have to send the message back
        /**
         * TODO: echo the received message back to the client
         *
         *
         * Suggestions:
         * - send() with flags = 0 is equivalent to write() on a descriptor
         * - deal with partially sent messages
         * - message size IS NOT buf size
         */

        bytes_sent = 0;

        while(bytes_sent < recv_bytes){
            ret = send(socket_desc, buf+bytes_sent, recv_bytes-bytes_sent, 0);
            if(ret == -1 && errno == EINTR) continue;
            if(ret == -1) handle_error("send error");
            bytes_sent += ret;
        }

        if (DEBUG) fprintf(stderr, "Sent message of %d bytes back...\n", bytes_sent);
    }


    /**
     *  TODO: close socket and release unused resources
     */

    if(close(socket_desc) == -1) handle_error("close error");

    if (DEBUG) fprintf(stderr, "Socket closed...\n");

    return NULL;
}

int main(int argc, char* argv[]) {
    int ret;

    int socket_desc, client_desc;

    // some fields are required to be filled with 0
    struct sockaddr_in server_addr = {0}, client_addr = {0};

    int sockaddr_len = sizeof(struct sockaddr_in); // we will reuse it for accept()

    /**
     *  TODO: Create a socket for listening
     *
     * Suggestions:
     * - protocollo AF_INET
     * - tipo SOCK_STREAM
     */

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1) handle_error("socket error");

    if (DEBUG) fprintf(stderr, "Socket created...\n");

    /* We enable SO_REUSEADDR to quickly restart our server after a crash:
     * for more details, read about the TIME_WAIT state in the TCP protocol */
    int reuseaddr_opt = 1;
    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt));
    if (ret < 0)
        handle_error("Cannot set SO_REUSEADDR option");

    /**
     *  TODO: set server address and bind it to the socket
     *
     * Suggestions:
     * - set the 3 fields of server:
     * - - server_addr.sin_addr.s_addr: we want to accept connections from any interface
     * - - server_addr.sin_family,
     * - - server_addr.sin_port (using htons() method)
     * - bind address to socket
     * - - attention to the bind method:
     * - - it requires as second field struct sockaddr* addr, but our address is a struct sockaddr_in, hence we must cast it (struct sockaddr*) &server_addr
     */

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    ret = bind(socket_desc, (struct sockaddr*) &server_addr, sockaddr_len);
    if(ret == -1) handle_error("bind error");

    if (DEBUG) fprintf(stderr, "Binded address to socket...\n");

    /**
     *  TODO: start listening
     *
     * Suggestions:
     * - set the number of pending connections to as MAX_CONN_QUEUE
     */

    ret = listen(socket_desc, MAX_CONN_QUEUE);
    if(ret == -1) handle_error("listen error");

    if (DEBUG) fprintf(stderr, "Socket is listening...\n");

    // loop to handle incoming connections (sequentially)
    while (1) {
        /**
         * TODO: accept an incoming connection
         *
         * Suggestions:
         * - the descriptor returned by accept() should be stored in the
         *   client_desc variable (declared at the beginning of main)
         * - pass the address of the client_addr variable (casting it to
         *   struct sockaddr* is recommended) as second argument to
         *   accept()
         * - the size of the client_addr structure has been stored in
         *   the sockaddr_len variable, so simply use it! (note that as
         *   the variable is an int, casting its address to socklen_t*
         *   is recommended)
         * - check the return value of accept() for errors!
         */

        client_desc = accept(socket_desc, (struct sockaddr*) &client_addr, (socklen_t*) &sockaddr_len);
        if(client_desc == -1) handle_error("accept error");

        if (DEBUG) fprintf(stderr, "Incoming connection accepted...\n");

        connection_handler(client_desc);

        if (DEBUG) fprintf(stderr, "Done!\n");
    }

    exit(EXIT_SUCCESS); // this will never be executed
}
