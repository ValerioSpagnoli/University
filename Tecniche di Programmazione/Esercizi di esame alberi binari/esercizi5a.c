#include "albero_binario.h"

// g++ -Wno-write-strings -o es5a esercizi5a.c


// Implementazioni con side-effect

// Elimina tutte le foglie di un albero
// contenenti valori maggiori di x
void rimuoviFoglieGrandi(TipoAlbero *a, int x) {
	if(estVuoto(*a)) return;
	else{
		if(foglia(sinistro(*a))){
			if(sinistro(*a)->info > x){
				dealloca(&((*a)->sinistro));
			}
		}
		if(foglia(destro(*a))){
			if(destro(*a)->info > x){
				dealloca(&((*a)->destro));
			}
		}
		rimuoviFoglieGrandi(&((*a)->sinistro), x);
		rimuoviFoglieGrandi(&((*a)->destro), x);
	}
}


// Ad ogni foglia contenente un valore maggiore di x
// aggiunge due figli con valori pari a 2*x
void aggiungiFoglieGrandi(TipoAlbero* a, int x){
	if(estVuoto(*a)) return;
	else{
		if(foglia(*a) && radice(*a)>x){
			(*a)->sinistro = creaAlbBin(2*x, NULL, NULL);
			(*a)->destro = creaAlbBin(2*x, NULL, NULL);
		}
		else{
			aggiungiFoglieGrandi(&((*a)->sinistro), x);
			aggiungiFoglieGrandi(&((*a)->destro), x);
		}
	}
}


// Aggiunge nuovi figli con valore x a tutti i nodi 
// al livello l che non hanno già figli
void completaLivello(TipoAlbero* a, int l, int x){
	if(estVuoto(*a))return;
	else{
		if(l == 0){
			if(sinistro(*a)==NULL){
				(*a)->sinistro = creaAlbBin(x, NULL, NULL);
			}
			if(destro(*a)==NULL){
				(*a)->destro = creaAlbBin(x, NULL, NULL);
			}
		}
		completaLivello(&((*a)->sinistro), l-1, x);
		completaLivello(&((*a)->destro), l-1, x);
	}
}


// Elimina tutte le foglie che sono a destra del nodo padre
// Se l'albero è costituito da un solo nodo, eliminare tale nodo.
void eliminaFoglieDestra(TipoAlbero* a){
	if(estVuoto(*a))return;
	else if((*a)->sinistro == NULL && (*a)->destro == NULL){
		free(*a);
		*a = NULL;
	}
	else{
		if(foglia(destro(*a))){
			free(destro(*a));	
			(*a)->destro = NULL;
		}
		else{
			eliminaFoglieDestra(&((*a)->sinistro));
			eliminaFoglieDestra(&((*a)->destro));
		}
	}

}



int main() {
    TipoAlbero a1 = LeggiAlbero("a1.txt");
    TipoAlbero a2 = LeggiAlbero("a2.txt");
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n\n");
    printf("rimuoviFoglieGrandi(a,5)\n");
    rimuoviFoglieGrandi(&a1,5);
    rimuoviFoglieGrandi(&a2,5);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n\n");
    printf("aggiungiFoglieGrandi(a,1)\n");
    aggiungiFoglieGrandi(&a1,1);
    aggiungiFoglieGrandi(&a2,1);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n\n");
    printf("completaLivello(a,3,9)\n");
    completaLivello(&a1,3,9);
    completaLivello(&a2,3,9);    
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
 	 printf("\n\n");   
    printf("eliminaFoglieDestra(a)\n");
    eliminaFoglieDestra(&a1);
    eliminaFoglieDestra(&a2);
    StampaAlbero("a1",a1);
    StampaAlbero("a2",a2);
	 printf("\n\n");
    dealloca(&a1);
    dealloca(&a2);
}
