#pragma once

#include <stdio.h>
#include "albbin.h"

struct InfoCoda {
  TipoAlbero alb;
  int val;
};

// Valore errore di tipo InfoCoda
const InfoCoda CODAERROR = {NULL, 0};

// Tipo Nodo Coda
struct NodoCodaSCL {
    InfoCoda info;
    NodoCodaSCL* next;
};

struct Coda {
    NodoCodaSCL *head;  // eliminazione in testa
    NodoCodaSCL *tail;  // inserimento in coda
};


Coda* codaVuota();
bool estVuota(Coda *q);
void inCoda(Coda *q, InfoCoda e);
void outCoda(Coda *q);
InfoCoda primo(Coda *q);


