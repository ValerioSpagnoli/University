#include "labirinto.h"

#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int **matrix;
    int **marcata;
} labirinto_struct ;

labirinto * labirinto_new(int n) {
    // TODO: Da completare
	return NULL;
}

void labirinto_delete(labirinto * lab) {
    // TODO: Da completare
}

void labirinto_setpiena(labirinto * lab, int r, int c) {
    // TODO: Da completare
}

int labirinto_uscita(labirinto * lab, int r, int c) {
    // TODO: Da completare
	return 0;
}

int labirinto_percorribile(labirinto * lab, int r, int c) {
    // TODO: Da completare
	return 0;
}

int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c) {
    // TODO: Da completare
	return 0;
}

int labirinto_risolvibile(labirinto * lab) {
    // TODO: Da completare
	return 0;
}

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size) {
	labirinto_struct * ptr = (labirinto_struct *) lab;
        assert(buffer_size >= (ptr->n + 1) * ptr->n);
    buffer[0] = '\0';
    char *buffer_ptr = buffer;
    int i;
    for (i = 0; i < ptr->n; i++) {
        int j;
        for (j = 0; j < ptr->n; j++) {
            char c;
            if(ptr->matrix[i][j] == LABIRINTO_PIENA)
                c = '#';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_FALSE)
                c = '.'; 
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_TRUE)
                c = '+'; 
            buffer_ptr[0] = c;
            buffer_ptr++;
        }
        buffer_ptr[0] = '\n';
        buffer_ptr++;
    }
    buffer_ptr[0] = '\0';
}