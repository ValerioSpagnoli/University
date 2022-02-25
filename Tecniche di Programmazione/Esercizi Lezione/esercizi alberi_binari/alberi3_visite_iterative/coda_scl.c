#include <stdio.h>
#include "coda_scl.h"


// O(1)
Coda* codaVuota() {
    Coda* q = (Coda *)malloc(sizeof(Coda));
    NodoCodaSCL *n = (NodoCodaSCL *)malloc(sizeof(NodoCodaSCL));  // nodo generatore
    n->next = NULL;
    q->head = n;
    q->tail = n;
    return q;
}

// O(1)
bool estVuota(Coda *q) {
    return q->head->next == NULL;
}

// O(1)
void inCoda(Coda *q, InfoCoda e) {  // inserimento in coda
    NodoCodaSCL *n = (NodoCodaSCL *)malloc(sizeof(NodoCodaSCL));
    n->info = e;
    n->next = NULL;
    q->tail->next = n;
    q->tail = n;
}

// O(1)
void outCoda(Coda *q) { // eliminazione in testa
    NodoCodaSCL *InfoCoda = q->head->next;
    if (InfoCoda!=NULL) {
        q->head->next = q->head->next->next;
        free(InfoCoda);
    }
    if (estVuota(q)) // coda vuota -> reset tail
        q->tail = q->head;
}

// O(1)
InfoCoda primo(Coda *q) {
    InfoCoda r = CODAERROR;
    if (q->head->next!=NULL) {
        r = q->head->next->info;
    }
    return r;
}

void stampaInfoCoda(InfoCoda i) {
    if (i.alb!=NULL)
        printf("%d ",i.alb->info);
}

void StampaCoda(Coda *q) {
    NodoCodaSCL *t = q->head->next;
    while (t!=NULL) {
        stampaInfoCoda(t->info);
        t = t->next;
    }    
}

