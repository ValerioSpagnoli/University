#pragma once

#include <stdio.h>

typedef int InfoCoda;

// Valore errore di tipo InfoCoda
const InfoCoda CODAERROR = -999;

// Tipo Nodo Coda
struct NodoCodaSCL {
    InfoCoda info;
    NodoCodaSCL* next;
};

struct Coda {
    NodoCodaSCL *head;  // eliminazione in testa
    NodoCodaSCL *tail;  // inserimento in coda
};

// Funzioni del tipo astratto
Coda* codaVuota();
bool estVuota(Coda *q);
void inCoda(Coda *q, InfoCoda e);
void outCoda(Coda *q);
InfoCoda primo(Coda *q);

// Funzioni sulla coda
void stampaCoda(Coda *q);


