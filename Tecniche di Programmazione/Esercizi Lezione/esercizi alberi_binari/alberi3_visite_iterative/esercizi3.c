#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>  // std::max, std::min

#include "albbin.h"
#include "pila_scl.h"
#include "coda_scl.h"

/*** Visite in profondità iterative ***/

// visita in pre-ordine
void preordine(TipoAlbero a) {
    Pila *p = pilaVuota();
    push(p,a); 
    while (!estVuota(p)) {
        TipoAlbero t = top(p);
        pop(p);
        if (t!=NULL) {
            printf("%d ",t->info); 
            push(p,t->destro);
            push(p,t->sinistro);
        }
    }
    printf("\n");
}


// somma dei valori dei nodi dell'albero
int somma(TipoAlbero a) {
    Pila *p = pilaVuota();
    push(p,a);
    int s = 0;
    while (!estVuota(p)) {
        TipoAlbero t = top(p);
        pop(p);
        if (t!=NULL) {
            s += t->info;
            push(p,t->destro);
            push(p,t->sinistro);
        }
    }
    return s;
}


// dealloca tutti i nodi dell'albero
void dealloca(TipoAlbero *a) {
    Pila *p = pilaVuota();
    push(p,*a);
    while (!estVuota(p)) {
        TipoAlbero t = top(p);
        pop(p);
        if (t!=NULL) {
            push(p,t->destro); 
            push(p,t->sinistro);
            free(t);            
        }
    }
    *a=NULL;
}


/*** Visite in ampiezza iterative ***/

// visita in ampiezza (o per livelli)
void visitaAmpiezza(TipoAlbero a) {
    Coda *q = codaVuota();
    InfoCoda i; i.alb=a;
    inCoda(q,i);
    while (!estVuota(q)) {
        InfoCoda p = primo(q);
        TipoAlbero t = p.alb;
        outCoda(q);
        if (t!=NULL) {
            printf("%d ",t->info);
            i.alb=t->sinistro;
            inCoda(q,i);
            i.alb=t->destro;
            inCoda(q,i);
        }
    }
    printf("\n");
}


// stampa informazioni per livelli
void stampaLivelli(TipoAlbero a) {
    if (estVuoto(a)) {
        printf("Albero vuoto.");
        return;
    }
    Coda *q = codaVuota();
    InfoCoda i; i.alb=a; i.val=0;
    inCoda(q,i);
    int livello = 0;
    printf("Livello %d: ",livello);
    while (!estVuota(q)) {
        InfoCoda p = primo(q);
        TipoAlbero t = p.alb;
        if (p.val>livello) {
           livello = p.val;
           printf("\n");
           for (int k=0; k<livello; k++) printf("  ");
           printf("Livello %d: ",livello);
        }
        printf("%d ",t->info);
        outCoda(q);
        i.val=p.val+1;
        if (t->sinistro!=NULL) { // solo alberi non vuoti
            i.alb=t->sinistro; 
            inCoda(q,i);
        }
        if (t->destro!=NULL) { // solo alberi non vuoti
            i.alb=t->destro; 
            inCoda(q,i);
        }
    }
    printf("\n");
}


int main() {

    TipoAlbero a1 = randomAlbero(12);
    stampaAlbero("a1",a1);
    disegnaAlbero("a1",a1);

    printf("visita in preordine: ");
    preordine(a1);


    int s = somma(a1);
    printf("Somma: %d\n",s);
    printf("visita in ampiezza: ");
    visitaAmpiezza(a1);
    stampaLivelli(a1);

    dealloca(&a1);
}

