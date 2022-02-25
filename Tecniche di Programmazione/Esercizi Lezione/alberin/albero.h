#pragma once
#include <stdio.h>
#include <stdlib.h>


#define ERRORE_InfoAlbero -99999
typedef int TipoInfoAlbero;

struct StructNodoFiglio;

// Albero n-ario
struct StructAlbero {
  TipoInfoAlbero info;
  struct StructNodoFiglio* figli;
};

// SCL di alberi
struct StructNodoFiglio {
  struct StructAlbero* albero;
  struct StructNodoFiglio* next;
};

typedef struct StructAlbero* TipoAlbero;
typedef struct StructNodoFiglio* TipoFigli;


// Funzioni del tipo primitivo
TipoAlbero alberoVuoto();
TipoAlbero creaAlbero(TipoInfoAlbero info, TipoFigli f);
bool estVuoto(TipoAlbero a);
TipoInfoAlbero radice(TipoAlbero a); 
// restituisce i figli di a
TipoFigli figli(TipoAlbero a);
// aggiunge l'albero a nella lista di figli f
TipoFigli add(TipoFigli f, TipoAlbero a);
// aggiunge f come figlio di a
void aggiungiFiglio(TipoAlbero a, TipoAlbero f);

// Funzioni esterne
void stampaAlbero(const char* astr, TipoAlbero a);
TipoAlbero leggiAlbero(const char *nome_file);

