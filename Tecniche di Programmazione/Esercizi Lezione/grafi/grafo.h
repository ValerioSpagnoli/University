#pragma once

// Rappresentazione di grafi mediante doppia lista collegata.
// StructNodo contiene informazione del grafo e puntatore a lista dei successori
// StructNodoSucc contiene il puntatore al nodo successore e il puntatore
// alla parte restante della lista di successori

// Questa rappresentazione è efficiente in termini di uso di memoria e
// di tempo di esecuzione delle operazioni.

#define ERRORE_InfoGrafo -99999
typedef int TipoInfoGrafo;

struct StructNodo;

struct StructNodo {
  TipoInfoGrafo info;
  struct StructNodoSucc* succ;
};

struct StructNodoSucc {
  struct StructNodo* nodo;
  struct StructNodoSucc* next;
};

typedef struct StructNodo* TipoGrafo;
typedef struct StructNodoSucc* TipoSuccessori;

// restituisce un grafo vuoto
TipoGrafo grafoVuoto();
// crea un grafo
TipoGrafo creaGrafo(TipoInfoGrafo info, TipoSuccessori s);
// verifica se il grafo è vuoto
bool estVuoto(TipoGrafo a);
// restituisce l'informazione nel nodo
TipoInfoGrafo radice(TipoGrafo a);
// restituisce la lista dei successori
TipoSuccessori successori(TipoGrafo a);
// aggiunge il nodo a alla lista di successori l
TipoSuccessori add(TipoSuccessori l, TipoGrafo a);
// aggiunge arco tra a e b
void aggiungiArco(TipoGrafo a, TipoGrafo b); 

