#pragma once

// SCL ordinata di T, side-effect
typedef int T;

// Valore errore di tipo T
#define TERRORVALUE -999999

// Tipo Insieme
struct NodoSCL {
    T info;
    NodoSCL* next;
};

struct Insieme {
    NodoSCL *head;
};

struct IteratoreInsieme {
    Insieme *ins;
    NodoSCL *ptr; // ptr al prossimo elemento
};

Insieme* insiemeVuoto();
bool estVuoto(Insieme *ins);
void inserisci(Insieme *ins, T e);
void elimina(Insieme *ins, T e);
bool membro(Insieme *ins, T e);

IteratoreInsieme* creaIteratoreInsieme(Insieme *ins);
bool hasNext(IteratoreInsieme *it);
T next(IteratoreInsieme *it);


