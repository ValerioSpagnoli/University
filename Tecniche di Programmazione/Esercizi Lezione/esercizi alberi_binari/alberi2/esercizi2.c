#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>  // std::max, std::min

#include "albbin.h"

/*** Implementazioni funzionali ***/

// copia di un albero
TipoAlbero copia(TipoAlbero a) {
    if (estVuoto(a))
        return albBinVuoto();
    else
        return creaAlbBin(radice(a),
            copia(sinistro(a)),
            copia(destro(a)));
}



// Verifica se nodo è una foglia
// (funzione ausiliaria)
bool foglia(TipoAlbero a) {
    return (estVuoto(sinistro(a)) && estVuoto(destro(a)));
}

// restituisce un albero pari all'albero a senza foglie (funzionale)
TipoAlbero senzaFoglie(TipoAlbero a) {
    if (estVuoto(a))
        return albBinVuoto();
    else if (foglia(a))
        return albBinVuoto();
    else // nodo intermedio (non foglia)
        return creaAlbBin(radice(a), 
            senzaFoglie(sinistro(a)),
            senzaFoglie(destro(a)));
}



// Restituisce la foglia estrema sinistra di a
TipoAlbero fogliaSinistra(TipoAlbero a){
  if (estVuoto(a)) 
    return albBinVuoto();
  else if (!estVuoto(sinistro(a))) 
    return fogliaSinistra(sinistro(a));
  else if (!estVuoto(destro(a))) 
    return fogliaSinistra(destro(a));
  else // a la foglia estrema a sinistra
    return a;
}




/*** Implementazioni con side-effect ***/

// Passaggio di parametri per valore 

// Scambia tutti i sotto-alberi
void scambiaSottoAlberi(TipoAlbero a) {
    if (a!=NULL) {
        TipoAlbero t = a->sinistro;
        a->sinistro = a->destro;
        a->destro = t;
        scambiaSottoAlberi(a->sinistro);
        scambiaSottoAlberi(a->destro);
    }
}

// Passaggio di parametri tramite puntatore

/* 
  In tutte le funzioni, si assume che a sia sempre != NULL
  ovvero che sia sempre un puntatore valido ad un albero
  (eventualmente vuoto, ovvero *a == NULL)

  Si può aggiungere un eventuale controllo 
  che la funzione sia chiamata correttamente:

  if ( a==NULL ) {
    printtf("ERRORE\n");
    return;
  }
*/

// Aggiunge una copia di b come sottoalbero estremo a sinistra
// Se a è vuoto, copia b.
void aggiungiSinistra(TipoAlbero *a, TipoAlbero b) {
    if (*a==NULL)
        *a = copia(b);
    else
        aggiungiSinistra(&((*a)->sinistro), b);
}

// Analogo al precedente, considerando il sottoalbero estremo a destra
void aggiungiDestra(TipoAlbero *a, TipoAlbero b) {
    if (*a==NULL)
        *a = copia(b);
    else
        aggiungiDestra(&((*a)->destro), b);
}


// elimina tutti i nodi
void dealloca(TipoAlbero *a) {
    if (*a!=NULL) {
        dealloca(&((*a)->sinistro));
        dealloca(&((*a)->destro));
        free(*a);
        *a = NULL;  // side-effect su a
    }
}




// Elimina foglie di un albero (side-effect)
// Se a è una foglia, diventa albero vuoto
void rimuoviFoglie(TipoAlbero *a) {
    if (*a==NULL)
        return;
    else if (foglia(*a))
        dealloca(a);
    else {
        rimuoviFoglie(&((*a)->sinistro));
        rimuoviFoglie(&((*a)->destro));
    }
}

// Elimina sotto-albero con info e (side-effect)
// Se a è una foglia con info e, diventa albero vuoto
void eliminaSottoAlberoInfo(TipoAlbero *a, TipoInfoAlbero e) {
    if (*a==NULL)
        return;
    else if ((*a)->info==e)
        dealloca(a);
    else {
        eliminaSottoAlberoInfo(&((*a)->sinistro),e);
        eliminaSottoAlberoInfo(&((*a)->destro),e);
    }
}



///////////////////////////

// inserire foglia che diventerà estrema sinistra
void inserisciFogliaSinistra(TipoAlbero* a, TipoInfoAlbero e){
    if (*a==NULL) {
        *a = creaAlbBin(e,NULL,NULL);
    }
    else 
      inserisciFogliaSinistra(&((*a)->sinistro), e);
}

///////////////////////////

// Inserisce foglia con informazione e in posizione data dal percorso p
void inserisciFogliaInPosizione(TipoAlbero* a, TipoInfoAlbero e, 
                                const char* p){
    if (*a==NULL)
        *a = creaAlbBin(e,NULL,NULL);
    else if (*p=='\0')  // percorso termina in un nodo dell'albero
      return;  
    else if (*p=='s') 
      inserisciFogliaInPosizione(&((*a)->sinistro), e, p+1);
    else if (*p=='d') 
      inserisciFogliaInPosizione(&((*a)->destro), e, p+1);
}

///////////////////////////

// Inserisci nodo con informazione e in posizione data dal percorso p
// mettendo il sottoalbero corrispondente al nodo corrente
// a sinistra o a destra, a seconda del valore di f
void inserisciInPosizione(TipoAlbero* a, TipoInfoAlbero e, 
                          const char* p, char f) {

  if ( *a==NULL ) { // albero vuoto
    *a = creaAlbBin(e,NULL,NULL);
  }
  else if(*p=='\0') {
    if (f == 'd'){
      *a = creaAlbBin(e,NULL,*a);
    }
    else if (f == 's'){
      *a = creaAlbBin(e,*a,NULL);
    }
  }
  else if(*p=='s') 
    inserisciInPosizione(&((*a)->sinistro), e, p+1, f);
  else if(*p=='d') 
    inserisciInPosizione(&((*a)->destro), e, p+1, f);
}


// Elimina il primo nodo (visita in pre-ordine) che contiene
// l'informazione e, effettuando la seguente operazione sui
// sotto-alberi del nodo da eliminare:
// il sottoalbero destro del nodo da eliminare viene posto come
// sottoalbero sinistro della foglia piu' a sinistra di tale nodo
// Restituisce true se viene effettuata l'operazione di eliminazione,
// false altrimenti.

bool eliminaNodo(TipoAlbero* a, TipoInfoAlbero e) {
  if(estVuoto(*a)){
    return false;
  }
  if ((*a)->info == e) {
    // il sottoalbero destro di *a diventa il
    // sottoalbero sinistro della foglia piu' a sinistra di *a
    if ((*a)->destro != NULL){      
      TipoAlbero f = fogliaSinistra(*a);
      f->sinistro = (*a)->destro;
    }
    // Elimina il nodo *a
    TipoAlbero n = *a;
    *a = (*a)->sinistro;
    free(n); // Dealloca il nodo eliminato
    return true;
  }
  return (eliminaNodo(&((*a)->sinistro),e) || eliminaNodo(&((*a)->destro),e));
}


int main() {

    TipoAlbero a1 = randomAlbero(12);
    stampaAlbero("a1",a1);
    disegnaAlbero("a1",a1);

    TipoAlbero a2 = randomAlbero(15);
    stampaAlbero("a2",a2);
    
    scambiaSottoAlberi(a1);
    scambiaSottoAlberi(a2);
    stampaAlbero("a1",a1);
    stampaAlbero("a2",a2);

    TipoAlbero a3 = senzaFoglie(a1);
    TipoAlbero a4 = senzaFoglie(a2);
    stampaAlbero("a3",a3);
    stampaAlbero("a4",a4);

    aggiungiSinistra(&a3,a4);
    aggiungiDestra(&a3,a1);
    stampaAlbero("a3",a3);
    
    TipoAlbero a5 = copia(a2);
    while (!estVuoto(a3)) {
        rimuoviFoglie(&a3);
        stampaAlbero("a3",a3);
    }

    stampaAlbero("a2",a2);
    eliminaSottoAlberoInfo(&a2,1);
    
    stampaAlbero("a2",a2);
    eliminaSottoAlberoInfo(&a2,5);

    stampaAlbero("a2",a2);
    eliminaSottoAlberoInfo(&a2,2);

    stampaAlbero("a2",a2);
    eliminaSottoAlberoInfo(&a2,9);

    stampaAlbero("a2",a2);
    
    inserisciFogliaSinistra(&a5,10);
    inserisciFogliaInPosizione(&a5,20,"sds");
    stampaAlbero("a5",a5);

    inserisciInPosizione(&a5,15,"sds",'d');
    stampaAlbero("a5",a5);

    eliminaNodo(&a5, 7);
    stampaAlbero("a5",a5);

    dealloca(&a1);
    dealloca(&a2);
    dealloca(&a3);
    dealloca(&a4);
    dealloca(&a5);
}

