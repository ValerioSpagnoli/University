#include <stdio.h>
#include <stdlib.h>

#include "albbin.h"

// Implementazioni del tipo astratto

TipoAlbero albBinVuoto() {
  return NULL;
}

TipoAlbero creaAlbBin(TipoInfoAlbero info, TipoAlbero sx, TipoAlbero dx) {
  TipoAlbero a = (TipoAlbero) malloc(sizeof(TipoNodoAlbero));
  a->info = info;
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


// Funzioni esterne

// Stampa

void stampaParentetica(TipoAlbero a) {
    if (estVuoto(a)) {
        printf("()");
    }
    else {
        printf("( %c ", radice(a));
        stampaParentetica(sinistro(a));
        printf(" ");
        stampaParentetica(destro(a));
        printf(" )");
    }
}

void stampaAlbero(const char* astr, TipoAlbero a) {
    printf("Albero %s: ",astr);
    stampaParentetica(a);
    printf("\n");
}

// Lettura da file

void leggiParentesi(FILE *file_albero) {
  char c = ' ';
  while (c!='(' && c!=')')
    c = fgetc(file_albero);
}

TipoAlbero leggiSottoAlbero(FILE *file_albero) {
  char c;
  TipoInfoAlbero i;
  TipoAlbero r;

  leggiParentesi(file_albero);   /* legge la parentesi aperta */
  c = fgetc(file_albero);   /* carattere successivo */
  if (c == ')')
    return albBinVuoto();   /* se legge () allora l'albero e' vuoto */
  else {
    fscanf(file_albero, "%c", &i);   /* altrimenti legge la radice */

    /* legge i sottoalberi */
    TipoAlbero s = leggiSottoAlbero(file_albero);
    TipoAlbero d = leggiSottoAlbero(file_albero);

    r = creaAlbBin(i,s,d);

    leggiParentesi(file_albero);   /* legge la parentesi chiusa */

    return r;
  }
}


TipoAlbero leggiAlbero(char *nome_file) {
  TipoAlbero result;
  FILE *file_albero;
  file_albero = fopen(nome_file, "r");
  if (file_albero==NULL) {
      printf("File %s non trovato.\n",nome_file);
      return NULL;
  }
  result = leggiSottoAlbero(file_albero);
  fclose(file_albero);
  return result;
}

TipoAlbero randomAlbero(int size) {
    if (size==0)
        return albBinVuoto();
    else if (size==1) {
        TipoInfoAlbero c = 'A'+rand()%26;
        return creaAlbBin(c,albBinVuoto(),albBinVuoto());
    }
    else {
        TipoInfoAlbero c = 'A'+rand()%26;
        int l = rand()%(size-1);
        int r = size - 1 - l;
        return creaAlbBin(c,randomAlbero(l),randomAlbero(r));
    }
}


