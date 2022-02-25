#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>  // std::max, std::min

#include "albbin.h"
#include "albbin_ascii.h"

#include "lista_scl.h"
#include "ins_scl.h"
#include "pila_scl.h"
#include "coda_scl.h"

// Insieme dei valori dell'albero
void insiemeValori(TipoAlbero a, Insieme *i) {
    if (!estVuoto(a)) {
        inserisci(i, radice(a));
        insiemeValori(sinistro(a),i);
        insiemeValori(destro(a),i);
    }
}

// Lista valori dell'albero in pre-ordine
Lista listaValori(TipoAlbero a) {
    if (estVuoto(a))
        return listaVuota();
    else
        return cons(radice(a),
                    append(listaValori(sinistro(a)),
                           listaValori(destro(a)) ) );
}


// Pila dei valori dell'albero in pre-ordine
void pilaValori(TipoAlbero a, Pila *p) {
    if (!estVuoto(a)) {
        pilaValori(destro(a),p);
        pilaValori(sinistro(a),p);
        push(p,radice(a));
    }
}


// Coda dei valori dell'albero in pre-ordine
void codaValori(TipoAlbero a, Coda *q) {
    if (!estVuoto(a)) {
        inCoda(q,radice(a));
        codaValori(sinistro(a),q);
        codaValori(destro(a),q);
    }
}


/* Restituisce pila contenente i valori contenuti nei nodi
appartenenti ad un percorso radice -> nodo contenente informazione e.
Pila vuota se l'elemento non è presente.
Ricerca in pre-ordine.
*/

Pila* path(TipoAlbero a, TipoInfoAlbero e) {
    if (estVuoto(a)){
        return pilaVuota();
    }
    else if (radice(a) == e){
        Pila* p = pilaVuota();
        push(p,e);
        return p;
    }
  else {
    Pila* p;
    // cerca a sinistra
    p = path(sinistro(a),e);
    if (!estVuota(p)) {
        // trovato percorso sottoalbero sx
        push(p,radice(a));
    }
    else {
      // cerca a destra
      p = path(destro(a),e);
      if (!estVuota(p)) {
        // trovato percorso sottoalbero dx
        push(p,radice(a));
      }
    }
    // se e non trovato, p è vuota
    return p;
  }
}



/*
Restituisce pila contenente i valori contenuti nei nodi
appartenenti ad un percorso radice -> nodo contenente informazione e
di lunghezza minima.
Pila vuota se l'elemento non è presente.
*/

Pila* pathMin(TipoAlbero a, TipoInfoAlbero e){
    if (estVuoto(a)){
        return pilaVuota();
    }
    else if (radice(a) == e) {
        Pila* p = pilaVuota();
        push(p,e);
        return p;
    }
    else {

      Pila *sub_path_sx = pathMin(sinistro(a),e);
      Pila *sub_path_dx = pathMin(destro(a),e);

      // confronta i risultati e restituisce la pila non vuota più corta
      int size_sx = size(sub_path_sx);
      int size_dx = size(sub_path_dx);
      if (size_sx==0 && size_dx==0) // elemento non trovato -> pila vuota
        return pilaVuota(); 
      else if (size_dx==0) { // elemento trovato solo a sinistra
        push(sub_path_sx, radice(a));
        return sub_path_sx; 
      }
      else if (size_sx==0) { // elemento trovato solo a destra
        push(sub_path_dx, radice(a));
        return sub_path_dx; 
      }
      else if (size_sx <= size_dx) { // elemento a sinistra più vicino
        push(sub_path_sx, radice(a));
        return sub_path_sx; 
      }
      else {  // elemento a destra più vicino
        push(sub_path_dx, radice(a));
        return sub_path_dx; 
      }
    }
}



/*
Restituisce l'insieme dei valori dei nodi che hanno valore
maggiore di quello dei propri figli
*/

Insieme* maggioriDiFigli(TipoAlbero a) {
    Insieme* ins = insiemeVuoto();
    if (estVuoto(a)){
        return ins;
    }
    else {
      if ( (estVuoto(sinistro(a)) || radice(a) > radice(sinistro(a))) &&
           (estVuoto(destro(a)) || radice(a) > radice(destro(a)))) {
              inserisci(ins,radice(a));
      }
      Insieme* ins_sx = maggioriDiFigli(sinistro(a));
      Insieme* ins_dx = maggioriDiFigli(destro(a));
      return unione(ins,unione(ins_sx,ins_dx));
    }
}


// Elimina tutte le foglie con valore presente in ins
void eliminaFoglieDaInsieme(TipoAlbero* a, Insieme* ins){
    if (estVuoto(*a)) {
        return;
    }
    else if (estFoglia(*a) && membro(ins,radice(*a))) {
        free(*a); *a=NULL;
    }
    else {
        eliminaFoglieDaInsieme(&((*a)->sinistro), ins);
        eliminaFoglieDaInsieme(&((*a)->destro), ins);
    }
}


// Elimina tutti i nodi che hanno esattamente un figlio
// (Procedendo in post-ordine)

void cancellaPadriFiglioUnico(TipoAlbero* a) {
    if (estVuoto(*a)){
        return;
    }

    cancellaPadriFiglioUnico(&(*a)->sinistro);
    cancellaPadriFiglioUnico(&(*a)->destro);

    TipoAlbero sx = sinistro(*a);
    TipoAlbero dx = destro(*a);

    if (!estVuoto(sx) && estVuoto(dx)) {
        TipoAlbero aux = *a;
        *a = (*a)->sinistro;
        free(aux);
    }
    else if (estVuoto(sx) && !estVuoto(dx)) {
        TipoAlbero aux = *a;
        *a = (*a)->destro;
        free(aux);
    }

}


int main() {

    srand(time(0));

    printf("\n==================================================================");
    printf("==================================================================\n");

    TipoAlbero a1 = randomAlbero(12);
    stampaAlbero("a1",a1);
    stampaAlberoASCII("a1",a1);

    Insieme *i1 = insiemeVuoto();
    insiemeValori(a1,i1);
    printf("Insieme dei valori di a1: "); stampaInsieme(i1);

    Lista l1 = listaValori(a1);
    printf("Lista dei valori di a1: "); stampaLista(l1);

    Pila *p1 = pilaVuota();
    pilaValori(a1, p1);
    printf("Pila dei valori di a1: "); stampaPila(p1);

    Coda *q1 = codaVuota();
    codaValori(a1, q1);
    printf("Coda dei valori di a1: "); stampaCoda(q1);

    TipoInfoAlbero e = 9;
    Pila *p2 = path(a1,e);
    printf("Percorso in a1 da radice a %d: ", e);
    stampaPila(p2);

    e = 2;
    Pila *p3 = pathMin(a1,e);
    printf("Percorso minimo in a1 da radice a %d: ", e);
    stampaPila(p3);

    Insieme *i2 = maggioriDiFigli(a1);
    printf("Insieme dei valori maggiori di quello dei propri figli: ");
    stampaInsieme(i2);

    printf("\n==================================================================");
    printf("==================================================================\n");

    TipoAlbero a2 = randomAlbero(12);
    stampaAlbero("a2",a2);
    stampaAlberoASCII("a2",a2);

    printf("Eliminazione delle foglie con valori presenti in i3\n");
    Insieme* i3 = insiemeRandom(5);
    inserisci(i3,2);
    printf("insieme i3: ");
    stampaInsieme(i3);

    eliminaFoglieDaInsieme(&a2,i3);
    stampaAlbero("a2",a2);
    stampaAlberoASCII("a2",a2);

    printf("\n==================================================================");
    printf("==================================================================\n");

    TipoAlbero a3 = randomAlbero(12);
    stampaAlbero("a3",a3);
    stampaAlberoASCII("a3",a3);

    printf("Cancella padri con figlio unico\n");

    cancellaPadriFiglioUnico(&a3);

    stampaAlbero("a3",a3);
    stampaAlberoASCII("a3",a3);

    printf("\n==================================================================");
    printf("==================================================================\n");

    dealloca(&a1);
    dealloca(&a2);
    dealloca(&a3);
    // Dealloca code, pile, insiemi (ESERCIZIO)
}
