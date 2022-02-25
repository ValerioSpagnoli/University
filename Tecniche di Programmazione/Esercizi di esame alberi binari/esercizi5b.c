#include "albero_binario.h"

// g++ -Wno-write-strings -o es5b esercizi5b.c


// Implementazioni funzionali

// Elimina tutte le foglie di un albero
// contenenti valori maggiori di x
TipoAlbero rimuoviFoglieGrandi(TipoAlbero a, int x) {
	if(estVuoto(a)) return albBinVuoto();
	else if(foglia(a) && (a)->info>x){
			return NULL;
		}
	else{
		return creaAlbBin( radice(a), rimuoviFoglieGrandi(sinistro(a), x), 													rimuoviFoglieGrandi(destro(a), x) );
	}
}


// Ad ogni foglia contenente un valore maggiore di x
// aggiunge due figli con valori pari a 2*x
TipoAlbero aggiungiFoglieGrandi(TipoAlbero a, int x) {
	if(estVuoto(a))return NULL;
	else if(foglia(a) && (a)->info>x){
		return creaAlbBin(a->info, creaAlbBin(2*x, NULL, NULL), creaAlbBin(2*x, NULL, NULL));
	}
	else{
		return creaAlbBin(radice(a), aggiungiFoglieGrandi(sinistro(a), x), 												  aggiungiFoglieGrandi(destro(a), x));
	}
}


// Aggiunge nuovi figli con valore x a tutti i nodi 
// al livello l che non hanno già figli
TipoAlbero completaLivello(TipoAlbero a, int l, int x){
 	if(estVuoto(a)) return NULL;
	else if(l == 0){
		if(sinistro(a) == NULL && destro(a)!=NULL){
			return creaAlbBin(a->info, creaAlbBin(x, NULL, NULL), completaLivello(destro(a), l-1, x));
		}
		else if(destro(a) == NULL && sinistro(a)!=NULL){
			return creaAlbBin(a->info, completaLivello(sinistro(a), l-1, x), creaAlbBin(x, NULL, NULL));
		}
		else if(sinistro(a) == NULL && destro(a) == NULL){
			return creaAlbBin(a->info, creaAlbBin(x, NULL, NULL), creaAlbBin(x, NULL, NULL));
		}
	}
	else{
		return creaAlbBin(a->info, completaLivello(sinistro(a), l-1, x), completaLivello(destro(a), l-1, x));
	}
}


// Elimina tutte le foglie che sono a destra del nodo padre
// Se l'albero è costituito da un solo nodo, eliminare tale nodo.
TipoAlbero eliminaFoglieDestra(TipoAlbero a) {
	if(estVuoto(a))return NULL;
	else if(sinistro(a) == NULL && destro(a) == NULL) return NULL;
	else if(foglia(sinistro(a)) && !foglia(destro(a))){
		return creaAlbBin(a->info, creaAlbBin(sinistro(a)->info, NULL, NULL), eliminaFoglieDestra(destro(a)));
	}
	else if(foglia(destro(a)) && !foglia(sinistro(a))){
		return creaAlbBin(a->info, eliminaFoglieDestra(sinistro(a)), NULL);
	}
	else if(foglia(destro(a)) && foglia(sinistro(a))){
		return creaAlbBin(a->info, creaAlbBin(sinistro(a)->info, NULL, NULL), NULL);
	}
	else{
		return creaAlbBin(a->info, eliminaFoglieDestra(sinistro(a)), eliminaFoglieDestra(destro(a)));
	}
	
}


int main() {
    TipoAlbero a1 = LeggiAlbero("a1.txt");
    TipoAlbero a2 = LeggiAlbero("a2.txt");
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n");
    printf("rimuoviFoglieGrandi(a,5)\n");
    a1 = rimuoviFoglieGrandi(a1,5);
    a2 = rimuoviFoglieGrandi(a2,5);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n");
    printf("aggiungiFoglieGrandi(a,1)\n");
    a1 = aggiungiFoglieGrandi(a1,1);
    a2 = aggiungiFoglieGrandi(a2,1);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n");
    printf("completaLivello(a,3,9)\n");
    a1 = completaLivello(a1,3,9);
    a2 = completaLivello(a2,3,9);    
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
    printf("\n");
    printf("eliminaFoglieDestra(a)\n");
    a1 = eliminaFoglieDestra(a1);
    a2 = eliminaFoglieDestra(a2);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
    printf("\n");
    dealloca(&a1);
    dealloca(&a2);
}
