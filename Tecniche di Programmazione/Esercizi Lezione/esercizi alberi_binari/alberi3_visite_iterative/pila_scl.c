#include <stdio.h>
#include "pila_scl.h"


// O(1)
Pila* pilaVuota() {
    Pila* p = (Pila *)malloc(sizeof(Pila));
    p->head = NULL;
    return p;
}

// O(1)
bool estVuota(Pila *p) {
    return p->head == NULL;
}

// O(1)
void push(Pila *p, InfoPila e) {
    NodoPilaSCL *n = (NodoPilaSCL *)malloc(sizeof(NodoPilaSCL));
    n->info = e;
    n->next = p->head;
    p->head = n;
}

// O(1)
void pop(Pila *p) {
    NodoPilaSCL *InfoPila = p->head;
    if (InfoPila!=NULL) {
        p->head = p->head->next;
        free(InfoPila);
    }
}

// O(1)
InfoPila top(Pila *p) {
    InfoPila r = PILAERROR;
    if (p->head!=NULL) {
        r = p->head->info;
    }
    return r;
}

void stampaInfoPila(InfoPila i) {
    if (i!=NULL)
        printf("%d ",i->info);
}

void StampaPila(Pila *p) {
    NodoPilaSCL *t = p->head;
    while (t!=NULL) {
        stampaInfoPila(t->info);
        t = t->next;
    }    
}

