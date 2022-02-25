#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ERRORE_InfoAlbero -9999999;

typedef int TipoInfoAlbero;

// SCL ALBERO BINARIO
struct StructAlbero {
	TipoInfoAlbero info;
	struct StructAlbero *destro , *sinistro;
};

typedef struct StructAlbero TipoNodoAlbero;
typedef TipoNodoAlbero *TipoAlbero;

///////////////////////////////////////////////////////////// SCL LISTA
typedef int InfoLista;

// Valore errore di tipo InfoLista
const InfoLista LISTAERROR = -999;

// Tipo Lista
struct NodoListaSCL {
    InfoLista info;
    NodoListaSCL* next;
};

typedef NodoListaSCL* Lista;


//////////////////////////////////////////////////////////// SCL CODA
typedef int InfoCoda;

// Valore errore di tipo InfoCoda
const InfoCoda CODAERROR = -999;

// Tipo Nodo Coda
struct NodoCodaSCL {
    InfoCoda info;
    NodoCodaSCL* next;
};

struct Coda {
    NodoCodaSCL *head;  // eliminazione in testa
    NodoCodaSCL *tail;  // inserimento in coda
};


///////////////////////////////// Funzione fornite per Alberi Binari
TipoAlbero albBinVuoto ();
TipoAlbero creaAlbBin ( TipoInfoAlbero infoRadice , TipoAlbero sx , TipoAlbero dx );
bool estVuoto ( TipoAlbero a );
TipoInfoAlbero radice ( TipoAlbero a );
TipoAlbero sinistro ( TipoAlbero a );
TipoAlbero destro ( TipoAlbero a );
// Funzioni esterne
void dealloca(TipoAlbero *a);
void stampaAlbero(const char* astr, TipoAlbero a);
void disegnaAlbero(const char* astr, TipoAlbero a);
TipoAlbero leggiAlbero(char *nome_file);
TipoAlbero randomAlbero(int size);



///////////////////////////////////Funzioni fornite per Liste
// Funzioni del tipo astratto
Lista listaVuota();                 
bool estVuota(Lista p);
Lista cons(InfoLista e, Lista p);   
Lista cdr(Lista p);
InfoLista car(Lista p);
int lunghezzaLista(Lista l);
// Funzioni sulla Lista
void stampaLista(Lista l);
Lista append(Lista l1, Lista l2);


//////////////////////////////////////// Funzioni fornite Code 
// Funzioni del tipo astratto
Coda* codaVuota();
bool estVuota(Coda *q);
void inCoda(Coda *q, InfoCoda e);
void outCoda(Coda *q);
InfoCoda primo(Coda *q);
// Funzioni sulla coda
void stampaCoda(Coda *q);


