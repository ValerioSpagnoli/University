#pragma once

#include <stdio.h>

typedef int InfoPila;


// Valore errore di tipo InfoPila
const InfoPila PILAERROR = -999;

// Tipo Pila
struct NodoPilaSCL {
    InfoPila info;
    NodoPilaSCL* next;
};

struct Pila {
    NodoPilaSCL *head;
};

// Funzioni del tipo astratto
Pila* pilaVuota();
bool estVuota(Pila *p);
void push(Pila *p, InfoPila e);
void pop(Pila *p);
InfoPila top(Pila *p);

// Funzioni sulla pila
void stampaPila(Pila *p);
int size(Pila* p);

