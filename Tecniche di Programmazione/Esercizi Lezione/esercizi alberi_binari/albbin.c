#include <stdio.h>
#include <stdlib.h>

// Tipo info dell'albero
typedef char TipoInfoAlbero;

// Valore di errore
TipoInfoAlbero ERRORE_InfoAlbBin='*';

// Albero con strutture collegate
typedef struct StructAlbero {
  TipoInfoAlbero info;
  struct StructAlbero* destro;
  struct StructAlbero* sinistro;
} TipoNodoAlbero;

typedef TipoNodoAlbero* TipoAlbero;

// Funzioni del tipo astratto

TipoAlbero albBinVuoto();
TipoAlbero creaAlbBin(TipoInfoAlbero info, TipoAlbero sx, TipoAlbero dx);
bool estVuoto(TipoAlbero a);
TipoInfoAlbero radice(TipoAlbero a);
TipoAlbero sinistro(TipoAlbero a);
TipoAlbero destro(TipoAlbero a);


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

int main() {
    TipoAlbero A = creaAlbBin ( 'A' , albBinVuoto(), albBinVuoto() ) ;
    TipoAlbero B = creaAlbBin ( 'B' , albBinVuoto(), albBinVuoto() ) ;
    TipoAlbero C = creaAlbBin ( 'C' , albBinVuoto(), albBinVuoto() ) ;
    TipoAlbero D = creaAlbBin ( 'D' , albBinVuoto(), albBinVuoto() ) ;
    TipoAlbero E = creaAlbBin ( 'E' , A, B);
    TipoAlbero F = creaAlbBin ( 'F' , C, D);
    TipoAlbero G = creaAlbBin ( 'G' , E, F);

    stampaAlbero("G", G);
}


