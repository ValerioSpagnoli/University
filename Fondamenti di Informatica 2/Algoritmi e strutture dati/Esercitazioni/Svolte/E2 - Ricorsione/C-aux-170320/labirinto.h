#ifndef LABIRINTO_H
#define	LABIRINTO_H

typedef void labirinto;

#define LABIRINTO_PIENA 1
#define LABIRINTO_VUOTA 0

#define LABIRINTO_FALSE 0
#define LABIRINTO_TRUE 1

labirinto * labirinto_new(int n);

void labirinto_setpiena(labirinto * lab, int r, int c);

int labirinto_risolvibile(labirinto * lab);

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size);

void labirinto_delete(labirinto * lab);

int labirinto_uscita(labirinto * lab, int r, int c);

int labirinto_percorribile(labirinto * lab, int r, int c);

int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c);

#endif	/* LABIRINTO_H */

