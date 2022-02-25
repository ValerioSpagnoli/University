#pragma once

// SCL di T, side-effect
// Rappresentazione con SCL
typedef int T;

// Valore errore di tipo T (per iteratore)
#define TERRORVALUE -999999

struct NodoSCL {
    T info;
    struct NodoSCL* next;
};

typedef  NodoSCL* Insieme;

typedef struct{
  NodoSCL* ptr;
} IteratoreInsieme;

// Funzioni primitive del tipo

Insieme* insiemeVuoto();
bool estVuoto(Insieme *ins);
void inserisci(Insieme *ins, T e);
void elimina(Insieme *ins, T e);
bool membro(Insieme* ins, T e);

// Iteratore

IteratoreInsieme* creaIteratoreInsieme(Insieme *ins);
bool hasNext(IteratoreInsieme* it);
T next(IteratoreInsieme *it);

// Funzioni aggiuntive

void stampaInsieme(Insieme *i);
Insieme* intersezione(Insieme* i1, Insieme* i2);
Insieme* unione(Insieme* i1, Insieme* i2);
bool uguali(Insieme* i1, Insieme* i2);
Insieme* insiemeRandom(int n);
