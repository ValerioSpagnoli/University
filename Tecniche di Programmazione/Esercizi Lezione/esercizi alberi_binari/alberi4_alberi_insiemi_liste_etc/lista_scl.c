#include <stdio.h>
#include <stdlib.h>

#include "lista_scl.h"


// O(1)
Lista listaVuota() {
    return NULL;
}

// O(1)
bool estVuota(Lista p) {
    return p == NULL;
}

// O(1)
Lista cons(InfoLista e, Lista p) {
    NodoListaSCL *n = (NodoListaSCL *)malloc(sizeof(NodoListaSCL));
    n->info = e;
    n->next = p;
    return n;
}

// O(1)
Lista cdr(Lista p) {
    return p->next;
}

// O(1)
InfoLista car(Lista p) {
    return p->info;
}


// Funzioni sui tipi

void stampaInfoLista(InfoLista i) {
    printf("%d ",i);
}

void stampaLista(Lista l) {
    NodoListaSCL *t = l;
    while (t!=NULL) {
        stampaInfoLista(t->info);
        t = t->next;
    }    
    printf("\n");
}

Lista append(Lista l1, Lista l2) {
    if (estVuota(l1))
        return l2;
    else
        return cons(car(l1),append(cdr(l1),l2));
}


