#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <algorithm> // std::max, std::min

#define ERRORE_InfoAlbBin -99999
typedef int TipoInfoAlbero;

// Dynamic Tree
typedef struct StructAlbero {
  TipoInfoAlbero info;
  struct StructAlbero* destro = NULL;
  struct StructAlbero* sinistro = NULL;
} TipoNodoAlbero;

typedef TipoNodoAlbero* TipoAlbero;

TipoNodoAlbero* nodoalb_alloc(TipoInfoAlbero e) {
  TipoNodoAlbero* r = (TipoNodoAlbero*) malloc(sizeof(TipoNodoAlbero));
  r->info = e;
  r->destro = NULL;
  r->sinistro = NULL;
  return r;
}

TipoAlbero albBinVuoto() {
  return NULL;
}

TipoAlbero creaAlbBin(TipoInfoAlbero infoRadice,
		      TipoAlbero sx,
		      TipoAlbero dx) {
  TipoAlbero a = (TipoAlbero) malloc(sizeof(TipoNodoAlbero));
  a->info = infoRadice;
  a->sinistro = sx;
  a->destro = dx;
  return a;
}


bool estVuoto(TipoAlbero a) {
  return (a == NULL);
}

TipoInfoAlbero radice(TipoAlbero a) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
    return ERRORE_InfoAlbBin;
  } else {
    return a->info;
  }
}


TipoAlbero sinistro(TipoAlbero a) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
    return NULL;
  } else {
    return a->sinistro;
  }
}


TipoAlbero destro(TipoAlbero a) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
    return NULL;
  } else {
    return a->destro;
  }
}

void stampa_parentetica(TipoAlbero a) {
    if (a==NULL) {
        printf("()");
    }
    else {
        printf("( %d ",a->info);
        stampa_parentetica(a->sinistro);
        printf(" ");
        stampa_parentetica(a->destro);
        printf(" )");
    }
}

void StampaAlbero(const char* astr, TipoAlbero a) {
    printf("Albero %s: ",astr);
    stampa_parentetica(a);
    printf("\n");
}

void LeggiParentesi(FILE *file_albero) {
  char c = ' ';
  while (c!='(' && c!=')')
    c = fgetc(file_albero);
}

TipoAlbero LeggiSottoAlbero(FILE *file_albero) {
  char c;
  TipoInfoAlbero i;
  TipoAlbero r;
  LeggiParentesi(file_albero);   /* legge la parentesi aperta */
  c = fgetc(file_albero);   /* carattere successivo */
  if (c == ')')
    return NULL;   /* se legge () allora l'albero e' vuoto */
  else {
    fscanf(file_albero, "%d", &i);   /* altrimenti legge la radice */

    r = creaAlbBin(i, NULL,NULL);

    /* legge i sottoalberi */
    r->sinistro = LeggiSottoAlbero(file_albero);
    r->destro = LeggiSottoAlbero(file_albero);

    LeggiParentesi(file_albero);   /* legge la parentesi chiusa */

    return r;
  }
}  /* LeggiSottoAlbero */


TipoAlbero LeggiAlbero(char *nome_file) {
  TipoAlbero result;
  FILE *file_albero;
  file_albero = fopen(nome_file, "r");
  if (file_albero==NULL) {
      printf("File %s non trovato.\n",nome_file);
      return NULL;
  }
  result = LeggiSottoAlbero(file_albero);
  fclose(file_albero);
  return result;
}


// dimensione albero
int size(TipoAlbero a) {
    if (a==NULL)
        return 0;
    else
        return 1 + size(a->sinistro) + size(a->destro);
}

// profondita albero
int profondita(TipoAlbero a) {
    if (a==NULL)
        return -1;
    else {
        int ps = profondita(a->sinistro);
        int pd = profondita(a->destro);
        return (std::max(ps,pd)+1);
    }
}


// elimina tutti i nodi
void dealloca(TipoAlbero *a) {
    if (*a!=NULL) {
        dealloca(&((*a)->sinistro));
        dealloca(&((*a)->destro));
        free(*a);
        *a = NULL;
    }
}


// verifica se a è una foglia
bool foglia(TipoAlbero a) {
    return (a!=NULL && a->sinistro==NULL && a->destro==NULL);
}
