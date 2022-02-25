#include<stdlib.h>
#include<stdio.h>
#include "ins_sclord.h"


// O(1)
Insieme* insiemeVuoto() {
    Insieme* ins = (Insieme *)malloc(sizeof(Insieme));
    ins->head = (NodoSCL *)malloc(sizeof(NodoSCL)); // nodo generatore
    ins->head->next = NULL;
    return ins;
}

// O(1)
bool estVuoto(Insieme *ins) {
    return ins->head->next == NULL;
}

// O(n)
void inserisci(Insieme *ins, T e) {
    NodoSCL *p = ins->head;
    while (p->next!=NULL && p->next->info<e)
        p = p->next;
    if (p->next==NULL || p->next->info>e) {
        NodoSCL *n = (NodoSCL *)malloc(sizeof(NodoSCL));
        n->info = e;
        n->next = p->next;
        p->next = n;
    }
}

// O(n)
void elimina(Insieme *ins, T e) {
    NodoSCL *p = ins->head;
    while (p->next!=NULL && p->next->info!=e)
        p = p->next;
    if (p->next!=NULL) {
        NodoSCL *q = p->next;
        p->next = p->next->next;
        free(q);
    }
}

// O(n)
bool membro(Insieme *ins, T e) {
    bool r = false;
    NodoSCL *p = ins->head->next;
    while (p!=NULL && !r) {
        r = (p->info==e);
        p = p->next;
    }
    return r;
}

// O(1)
IteratoreInsieme* creaIteratoreInsieme(Insieme *ins) {
    IteratoreInsieme *it = (IteratoreInsieme *)malloc(sizeof(IteratoreInsieme));
    it->ins = ins;
    it->ptr = ins->head->next;
    return it;
}

// O(1)
bool hasNext(IteratoreInsieme *it) {
    return it->ptr!=NULL;
}

// O(1)
T next(IteratoreInsieme *it) {
    T r = TERRORVALUE;
    if (it->ptr!=NULL) {
        r = it->ptr->info;
        it->ptr = it->ptr->next;
    }
    else
        printf("ERRORE Iteratore non valido.\n");
    return r;
}

