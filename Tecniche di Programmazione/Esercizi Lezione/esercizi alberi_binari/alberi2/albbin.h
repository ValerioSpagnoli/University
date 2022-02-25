#pragma once

#include <stdio.h>
#include <stdlib.h>

// Tipo info dell'albero
typedef int TipoInfoAlbero;

// Valore di errore
const TipoInfoAlbero ERRORE_InfoAlbBin=-999;

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

// Funzioni esterne

void stampaAlbero(const char* astr, TipoAlbero a);
void disegnaAlbero(const char* astr, TipoAlbero a);
TipoAlbero leggiAlbero(char *nome_file);
TipoAlbero randomAlbero(int size);

