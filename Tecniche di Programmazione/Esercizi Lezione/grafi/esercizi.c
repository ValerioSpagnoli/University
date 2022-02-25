#include<stdlib.h>
#include<stdio.h>

#include "grafo.h"
#include "ins_sclord.h"

// Le seguenti funzioni assumono grafi senza duplicati.
// Il valore di un nodo è quindi univoco nel grafo.


// Dato un nodo di un grafo, stampa le informazioni contenute
// in tutti i nodi raggiungibili da tale nodo.

void stampaNodi_r(TipoGrafo a, Insieme* i) {
    if (a==NULL) {
        printf(" ");
    }
    else {
        printf(" %d ",a->info);
        inserisci(i,a->info);
        TipoSuccessori p = a->succ;
        while (p!=NULL) {
            if (!membro(i,p->nodo->info)) {
                stampaNodi_r(p->nodo, i);
            }
            p = p->next;
        }
    }
}

void stampaNodi(TipoGrafo a) {
    stampaNodi_r(a, insiemeVuoto());
}


// Dato un nodo di un grafo, stampa tutti gli archi 
// uscenti dai nodi raggiungibili da tale nodo. 

void stampaArchi_r(TipoGrafo a, Insieme* i) {
    if (a==NULL) {
        printf(" ");
    }
    else {    
        TipoSuccessori p = a->succ;
        while (p!=NULL) {
            printf("( %d %d ) ",a->info,p->nodo->info);
            p = p->next;
        }
        inserisci(i,a->info);
        // chiama ricorsivamente su tutti gli altri nodi
        p = a->succ;
        while (p!=NULL) {
            if (!membro(i,p->nodo->info)) {
                stampaArchi_r(p->nodo, i);
            }
            p = p->next;
        }
    }
}

void stampaArchi(TipoGrafo a) {
    stampaArchi_r(a, insiemeVuoto());    
}


// Dato un nodo di un grafo, restituisce la somma dei valori
// di tutti i nodi raggiungibili da tale nodo. 

int sommaNodi_r(TipoGrafo a, Insieme* i) {
    if (a==NULL) {
        return 0;
    }
    else {
        int r = a->info;
        inserisci(i,a->info);
        TipoSuccessori p = a->succ;
        while (p!=NULL) {
            if (!membro(i,p->nodo->info)) {
                r += sommaNodi_r(p->nodo, i);
            }
            p = p->next;
        }
        return r;
    }
}

int sommaNodi(TipoGrafo a) {
    return sommaNodi_r(a, insiemeVuoto());
}


// Dati due nodi di un grafo, verificare se esiste un percorso
// che collega il primo con il secondo nodo.

bool esistePercorso_r(TipoGrafo a, TipoGrafo b, Insieme* i) {
    if (a==NULL) {
        return false;
    }
    else if (a->info == b->info) {
        return true;
    }
    else {
        bool r = false;
        inserisci(i,a->info);
        TipoSuccessori p = a->succ;
        while (p!=NULL && !r) {
            if (!membro(i,p->nodo->info)) {
                r = esistePercorso_r(p->nodo, b, i);
            }
            p = p->next;
        }
        return r;
    }
}

bool esistePercorso(TipoGrafo a, TipoGrafo b) {
    return esistePercorso_r(a, b, insiemeVuoto());
}



int main() {
    TipoGrafo n1 = creaGrafo(15, NULL);
    TipoGrafo n2 = creaGrafo(5, NULL);
    TipoGrafo n3 = creaGrafo(3, NULL);
    TipoGrafo n4 = creaGrafo(7, NULL);
    TipoGrafo n5 = creaGrafo(9, NULL);
    aggiungiArco(n1,n2); aggiungiArco(n2,n3); aggiungiArco(n3,n1);
    aggiungiArco(n3,n4); aggiungiArco(n4,n5); aggiungiArco(n5,n4);
    aggiungiArco(n5,n5);
    
    printf("Nodi del grafo: "); stampaNodi(n1); printf("\n");
    printf("Archi del grafo: "); stampaArchi(n1); printf("\n");
    printf("Somma valori del grafo: %d \n",sommaNodi(n1));

    printf("Esiste percorso 5 -> 9: %d \n",esistePercorso(n2,n5));
    printf("Esiste percorso 9 -> 5: %d \n",esistePercorso(n5,n2));    
}

