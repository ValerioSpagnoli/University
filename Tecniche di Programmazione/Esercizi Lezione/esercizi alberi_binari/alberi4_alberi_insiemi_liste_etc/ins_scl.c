#include<stdlib.h>
#include<stdio.h>
#include"ins_scl.h"

// O(1)
Insieme* insiemeVuoto() {
  Insieme* r = (Insieme*) malloc(sizeof(Insieme*));
  *r = NULL;
  return r;
}

// O(1)
bool estVuoto(Insieme* ins) {
    return *ins == NULL;
}

// O(n)
void inserisci(Insieme *ins, T e) {
    if (!membro(ins,e)) {
        NodoSCL* n = (NodoSCL*) malloc(sizeof(NodoSCL));
        n->info = e;
        n->next = *ins;
        *ins = n;
    }
}

// O(n)
void elimina(Insieme *ins, T e) {
    if (*ins == NULL){
      return;
    }
    NodoSCL* p = *ins;
    if (p->info == e){
      *ins = p->next;
      free(p);
      return;
    }
    elimina(&((*ins) -> next),e);
}

// O(n)
bool  membro(Insieme* ins, T e) {
    NodoSCL* p = *ins;
    while (p!=NULL) {
        if (p -> info == e){
          return true;
        }
        p = p->next;
    }
    return false;
}

// O(1)
IteratoreInsieme* creaIteratoreInsieme(Insieme* ins) {
  IteratoreInsieme* r = (IteratoreInsieme*) malloc(sizeof(IteratoreInsieme));
  r->ptr = *ins;
  return r;
}

// O(1)
bool hasNext(IteratoreInsieme* it) {
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

// Funzioni su insiemi

void stampaInsieme(Insieme *i) {
    IteratoreInsieme* it = creaIteratoreInsieme(i);
    while (hasNext(it)) {
        T e = next(it);
        printf("%d ",e);
    }
    free(it);
    printf("\n");
}

Insieme* intersezione(Insieme* i1, Insieme* i2) {
  IteratoreInsieme* it = creaIteratoreInsieme(i1);
  Insieme* r = insiemeVuoto();
  while (hasNext(it)) {
    T e = next(it);
    if (membro(i2,e)) {
      inserisci(r,e);
    }
  }
  free(it);
  return r;
}

Insieme* unione(Insieme* i1, Insieme* i2) {
  IteratoreInsieme* it = creaIteratoreInsieme(i1);
  Insieme* r = insiemeVuoto();
  while (hasNext(it)) {
      inserisci(r,next(it));
  }
  free(it);
  it = creaIteratoreInsieme(i2);
  while (hasNext(it)) {
      inserisci(r,next(it));
  }
  free(it);
  return r;
}

bool uguali(Insieme* i1, Insieme* i2) {
  IteratoreInsieme* it = creaIteratoreInsieme(i1);
  while (hasNext(it)) {
    if (!membro(i2,next(it))) {
      return false;
    }
  }
  free(it);
  it = creaIteratoreInsieme(i2);
  while (hasNext(it)) {
    if (!membro(i1,next(it))) {
      return false;
    }
  }
  free(it);
  return true;
}

Insieme* insiemeRandom(int n){
	if (n == 0){
		return insiemeVuoto();
	}
	Insieme* r = insiemeRandom(n-1);
	int v = rand() % (3*n);
	while(membro(r,v)){
		v = rand() % 10;
	}
	inserisci(r,v);
	return r;
}
