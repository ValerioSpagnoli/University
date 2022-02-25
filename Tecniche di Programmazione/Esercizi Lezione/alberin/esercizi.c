#include <algorithm> // std::max, std::min
#include "albero.h"

int size(TipoAlbero a);

// dimensione sottoaberi figli
// funzione ausiliaria
int size_f(TipoFigli f) {
    if (f==NULL)
        return 0;
    else
        return size(f->albero) + size_f(f->next);
}

// dimensione albero
int size(TipoAlbero a) {
    if (a==NULL)
        return 0;
    else
        return 1 + size_f(a->figli);
}


// profondita albero
int profondita(TipoAlbero a) {
    if (a==NULL)
        return -1;
    else {
        TipoFigli f = a->figli;
        int pmax = -1;
        while (f!=NULL) {
            int p = profondita(f->albero);
            pmax = std::max(pmax,p);
            f = f->next;
        }
        return pmax+1;
    }
}


// Deallocazione di un albero
void dealloca(TipoAlbero *a) {
    if (*a!=NULL) {
        TipoFigli f = (*a)->figli;
        while (f!=NULL) {
            dealloca(&(f->albero));
            TipoFigli p = f;
            f = f->next;
            free(p);
        }
        free(*a);
        *a = NULL;
    }
}

TipoFigli copiaFigli(TipoFigli f);

// Copia di un albero
// funzione principale
TipoAlbero copia(TipoAlbero a) {
    if (a==NULL)
        return NULL;
    else
        return creaAlbero(a->info,copiaFigli(a->figli));
}

// Copia di un albero
// funzione ausiliaria
TipoFigli copiaFigli(TipoFigli f) {
    if (f==NULL)
        return NULL;
    else
        return add(copiaFigli(f->next),copia(f->albero));
}


int sommaFigli(TipoFigli f);

// Somma dei valori dei nodi
// funzione principale
int somma(TipoAlbero a) {
    if (a==NULL)
        return 0;
    else
        return a->info + sommaFigli(a->figli);
}

// Somma dei valori dei nodi
// funzione ausiliaria
int sommaFigli(TipoFigli f) {
    if (f==NULL)
        return 0;
    else
        return somma(f->albero) + sommaFigli(f->next);
}



int main() {
    TipoAlbero a1 = leggiAlbero("a1.txt");
    stampaAlbero("a1",a1);
    TipoAlbero a2 = leggiAlbero("a2.txt");
    stampaAlbero("a2",a2);

    printf("Dimensione a1: %d\n",size(a1));
    printf("Dimensione a2: %d\n",size(a2));
    printf("Profondità a1: %d\n",profondita(a1));
    printf("Profondità a2: %d\n",profondita(a2));
    printf("Somma a1: %d\n",somma(a1));
    printf("Somma a2: %d\n",somma(a2));

    TipoAlbero a3 = copia(a1);
    TipoAlbero a4 = copia(a2);
    stampaAlbero("a3",a3);
    stampaAlbero("a4",a4);
    
    dealloca(&a1);
    dealloca(&a2);
    dealloca(&a3);
    dealloca(&a4);

}

