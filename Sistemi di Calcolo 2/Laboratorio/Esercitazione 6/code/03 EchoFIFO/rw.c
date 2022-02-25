#include <unistd.h>
#include <errno.h>
#include "common.h"


int readOneByOne(int fd, char* buf, char separator) {

    int ret;

    /** [TO DO] READ THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can read from a FIFO as from a regular file descriptor
     * - since you don't know the length of the message, just
     *   read one byte at a time from the socket
     * - leave the cycle when 'separator' ('\n') is encountered
     * - repeat the read() when interrupted before reading any data
     * - return the number of bytes read
     * - reading 0 bytes means that the other process has closed
     *   the FIFO unexpectedly: this is an error that should be
     *   dealt with!
     **/
    int read_bytes = 0;
    while(ret = read(fd, buf + read_bytes, 1) != '\n'){
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("[readOnebyOne] errore read");
        if(ret == 0){
            handle_error("[readOnebyOne] errore read");
            fflush(stdout);
        }
        read_bytes++;
    }
    fflush(stdout);
    return read_bytes;
}

void writeMsg(int fd, char* buf, int size) {

    int ret;
    /** [TO DO] SEND THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can write on the FIFO as on a regular file descriptor
     * - make sure that all the bytes have been written: use a while
     *   cycle in the implementation as we did for file descriptors!
     **/

    int written_bytes = 0;

    while(written_bytes < size){
        ret = write(fd, buf+written_bytes, size-written_bytes);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("[writeMsg] errore write");
        written_bytes += ret;
    }
    fflush(stdout);
}
