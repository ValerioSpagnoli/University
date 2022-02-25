#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

TipoGrafo grafoVuoto() {
  return NULL;
}

TipoGrafo creaGrafo(TipoInfoGrafo info,
                    TipoSuccessori s) {
  TipoGrafo a = (TipoGrafo) malloc(sizeof(struct StructNodo));
  a->info = info;
  a->succ = s;
  return a;
}


bool estVuoto(TipoGrafo a) {
  return (a == NULL);
}

TipoInfoGrafo radice(TipoGrafo a) {
  if (a == NULL) {
    printf ("ERRORE accesso grafo vuoto \n");
    return ERRORE_InfoGrafo;
  } else {
    return a->info;
  }
}


TipoSuccessori successori(TipoGrafo a) {
  if (a == NULL) {
    printf ("ERRORE accesso grafo vuoto \n");
    return NULL;
  } else {
    return a->succ;
  }
}

TipoSuccessori add(TipoSuccessori l, TipoGrafo a) {
    TipoSuccessori n = (TipoSuccessori)malloc(sizeof(struct StructNodoSucc));
    n->nodo = a;
    n->next = l;
    return n;
}

void aggiungiArco(TipoGrafo a, TipoGrafo b) {
  if (a == NULL) {
    printf ("ERRORE accesso grafo vuoto \n");
  } else {
    a->succ = add(a->succ, b);
  }
}

