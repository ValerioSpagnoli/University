#pragma once

#include <stdio.h>

typedef int InfoLista;

// Valore errore di tipo InfoLista
const InfoLista LISTAERROR = -999;

// Tipo Lista
struct NodoListaSCL {
    InfoLista info;
    NodoListaSCL* next;
};

typedef NodoListaSCL* Lista;

// Funzioni del tipo astratto
Lista listaVuota();
bool estVuota(Lista p);
Lista cons(InfoLista e, Lista p);
Lista cdr(Lista p);
InfoLista car(Lista p);

// Funzioni sulla Lista
void stampaLista(Lista l);
Lista append(Lista l1, Lista l2);

