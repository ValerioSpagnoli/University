#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>  // std::max, std::min

#include "albbin.h"

/*** Calcoli su alberi binari ***/

// dimensione albero (contatore)
int size(TipoAlbero a) {
    if (estVuoto(a))
        return 0;
    else
        return 1 + size(sinistro(a)) + size(destro(a));
}

// calcola il numero di foglie dell'albero
// (contatore condizionato)
int numeroFoglie(TipoAlbero a) {
    if (estVuoto(a))
        return 0;
    else if (estVuoto(sinistro(a)) && estVuoto(destro(a)))
        return 1;
    else
        return numeroFoglie(sinistro(a)) + numeroFoglie(destro(a));
}

// verifica presenza elemento (accumulazione OR)
bool presente(TipoAlbero a, TipoInfoAlbero e) {
    if (estVuoto(a))
        return false;
    else
        return (radice(a)==e) || 
               presente(sinistro(a),e) || 
               presente(destro(a),e);
}


// tutti maiuscoli (accumulazione AND)
bool maiuscoli(TipoAlbero a) {
    if (estVuoto(a))
        return true;
    else {
        TipoInfoAlbero c = radice(a);
        bool r = (c>='A') && (c<='Z');
        return r && maiuscoli(sinistro(a)) && maiuscoli(destro(a));
    }
}

// Profondità albero
int profondita(TipoAlbero a) {
    if (estVuoto(a))
        return -1;
    else {
        int ps = profondita(sinistro(a));
        int pd = profondita(destro(a));
        return (std::max(ps,pd)+1);
    }
}


/*** Accesso ai nodi tramite livello ***/

// Stampa il contenuto dei nodi al livello l
void stampaNodiLivello(TipoAlbero a, int l) {
    if (estVuoto(a)) 
        return;
    else if (l == 0)
        printf("%c ", radice(a));
    else {
        stampaNodiLivello(sinistro(a), l-1); 
        stampaNodiLivello(destro(a), l-1);
        // attenzione: l'uso delle espressioni l-- o --l anziché l-1 porta
        // a risultati errati in qunto il valore di l viene modificato
        // tra una chiamata e l'altra !!! 
    }
}


// Conta i nodi che si trovano ad un certo livello
int contaNodiLivello(TipoAlbero a, int l) {
    if (estVuoto(a)) 
        return 0;
    else if (l==0)
        return 1;
    else
        return contaNodiLivello(sinistro(a),l-1) +
               contaNodiLivello(destro(a),l-1);
}

// Trova il livello in cui si trova l'informazione x
// albero contenente tutti valori distinti
int trovaLivello(TipoAlbero a, TipoInfoAlbero x) {
    if (estVuoto(a))
        return -1;
    else if (radice(a)==x)
        return 0;
    else {
        int ls = trovaLivello(sinistro(a),x);
        int ld = trovaLivello(destro(a),x);
        if ((ls<0) && (ld<0))
            return -1;
        else
            return 1+std::max(ls,ld);
    }
}


// Stampa il livello in cui si trova l'informazione x
// (funzione ausiliaria)
void infoLivello_r(TipoAlbero a, TipoInfoAlbero x, int l) {
    if (estVuoto(a))
        return;
    else if (radice(a)==x)
        printf("info:%c livello:%d\n", x, l);
    else {
        infoLivello_r(sinistro(a), x, l+1);
        infoLivello_r(destro(a), x, l+1);
    }
}

// Stampa il livello in cui si trova l'informazione x
// (funzione principale)
void infoLivello(TipoAlbero a, TipoInfoAlbero x) {
    infoLivello_r(a, x, 0);
}


/*** Alberi binari di ricerca ***/

// Creazione albero ricerca da array ordinato
// (funzione ausiliaria)
TipoAlbero creaAlberoBinarioRicerca_r(const char *s, int kmin, int kmax) {
    if (kmin > kmax)
        return albBinVuoto();
    else if (kmin == kmax)
        return creaAlbBin(s[kmin], albBinVuoto(), albBinVuoto());
    else { // kmin < kmax
        int m = (kmax + kmin)/2;
        TipoAlbero ts = creaAlberoBinarioRicerca_r(s, kmin, m-1);
        TipoAlbero td = creaAlberoBinarioRicerca_r(s, m+1, kmax);
        return creaAlbBin(s[m], ts, td);
    }
}

// Creazione albero ricerca da array ordinato
// (funzione principale)
TipoAlbero creaAlberoBinarioRicerca(const char *s) {
    return creaAlberoBinarioRicerca_r(s, 0, strlen(s)-1);
}


// Stampa ordinata albero ricerca
// funzione ausiliaria (visita simmetrica)
void stampaAlbRic_r(TipoAlbero a) {
    if (estVuoto(a))
        return;
    else {
        stampaAlbRic_r(sinistro(a));
        printf("%c ", radice(a));
        stampaAlbRic_r(destro(a));
    }
}

// Stampa ordinata albero ricerca
// funzione principale
void stampaAlbRic(const char* astr, TipoAlbero a) {
    printf("Albero %s: ",astr);
    stampaAlbRic_r(a);
    printf("\n");
}

// Ricerca su albero binario di ricerca bilanciato  ->  O(log(n))
bool presenteAlbRic(TipoAlbero a, TipoInfoAlbero x) {
    if (estVuoto(a))
        return false;
    else if (x == radice(a))
        return true;
    else if (x < radice(a))
        return presenteAlbRic(sinistro(a),x);
    else // (x > radice(a))
        return presenteAlbRic(destro(a),x);
}

// Verifica bilanciato (accumulazione AND)
// Esercizio: Calcolare il costo di questa funzione
bool bilanciato(TipoAlbero a) {
    if (estVuoto(a))
        return true;
    else {
        int ps = profondita(sinistro(a));
        int pd = profondita(destro(a));
        return (abs(ps-pd)<=1) &&
               bilanciato(sinistro(a)) &&
               bilanciato(destro(a));
    }
}




int main() {
    TipoAlbero a = randomAlbero(12);

    stampaAlbero("a", a);

    // Calcoli su alberi binari

    int s = size(a);
    printf("size: %d\n", s);

    int f = numeroFoglie(a);
    printf("foglie: %d\n", f);

    bool b1 = presente(a,'A');
    bool b2 = presente(a,'Z');
    printf("presente A: %d, presente Z: %d\n", b1,b2);

    bool b3 = maiuscoli(a);
    printf("tutti maiuscoli: %d\n", b3);

    int p = profondita(a);
    printf("profondità: %d\n", p);
    
    bool b4 = bilanciato(a);
    printf("bilanciato: %d\n", b4);
    

    // Accesso per livelli

    stampaNodiLivello(a, 2); printf("\n");
    int c = contaNodiLivello(a, 2);
    printf("nodi a livello 2: %d\n", c);

    int l1 = trovaLivello(a, 'A');
    int l2 = trovaLivello(a, 'Z');
    printf("livello A: %d, livello Z: %d\n", l1,l2);

    infoLivello(a, 'A');


    // Alberi binari di ricerca

    TipoAlbero b = creaAlberoBinarioRicerca("ACDFGHLNPQW");
    stampaAlbero("b", b);
    stampaAlbRic("b", b);

    bool b5 = presenteAlbRic(b,'A');
    bool b6 = presenteAlbRic(b,'Z');
    printf("presente A: %d, presente Z: %d\n", b5,b6);

    bool b7 = bilanciato(b);
    printf("bilanciato: %d\n", b7);

}


