#pragma once

#include <stdio.h>
#include "albbin.h"

typedef TipoAlbero InfoPila;


// Valore errore di tipo InfoPila
const InfoPila PILAERROR = {NULL};

// Tipo Pila
struct NodoPilaSCL {
    InfoPila info;
    NodoPilaSCL* next;
};

struct Pila {
    NodoPilaSCL *head;
};


Pila* pilaVuota();
bool estVuota(Pila *p);
void push(Pila *p, InfoPila e);
void pop(Pila *p);
InfoPila top(Pila *p);


