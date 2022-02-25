#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef int TipoInfoSCL;

struct ElemSCL {
  TipoInfoSCL info;
  struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;

// Funzioni primitive

bool emptySCL(TipoSCL scl){
	return (scl == NULL);
}

TipoInfoSCL primoSCL(TipoSCL scl){
	if (!emptySCL(scl)){
		return scl -> info;
	}
	else{
		printf("SCL vuota!\n");
		return INT_MIN;
	}
}

TipoSCL restoSCL(TipoSCL scl) {
	if (!emptySCL(scl)){
		return scl -> next;
	}
	else{
		printf("Resto di una SCL vuota\n");
		return NULL;
	}
}

// Inserimento in testa alla scl
TipoSCL addSCL(TipoSCL scl, TipoInfoSCL e){
	TipoSCL temp = (TipoNodoSCL*) malloc(sizeof(TipoNodoSCL));
	temp -> info = e;
	temp -> next = scl;
	return temp;
}


// Funzioni ausiliarie

// stampa della SCL
void printSCL (TipoSCL scl) {
  if (emptySCL(scl))
    printf("\n");
  else {
    printf("%d ", scl->info);
    printSCL(scl->next);
  }
}

///////////////////////////////////////////


// copia SCL
TipoSCL copySCL(TipoSCL scl){
	if (emptySCL(scl)){
		return NULL;
	}
	else{
		TipoSCL resto = restoSCL(scl);
		TipoSCL c = copySCL(resto);
		return addSCL(c,primoSCL(scl));
	}
}

// aggiunge e in posizione n >= 0
// assume che la SCL contenga almeno n-1 elementi

TipoSCL addPosSCL(TipoSCL scl, TipoInfoSCL e, int n){
	if (n==0){
		//return addSCL(scl,e); // Condivisione di memoria
		return addSCL(copySCL(scl),e); // Senza condivisione (con copia)
	}
	else{
		/*
		TipoInfoSCL primo = primoSCL(scl);
		TipoSCL resto = restoSCL(scl);
		TipoSCL resto_add = addPosSCL(resto,e,n-1);
		return addSCL(resto_add,primo);
		*/

		return addSCL(addPosSCL(restoSCL(scl),e,n-1),primoSCL(scl));
	}
}

// restituisce una SCL senza l'elemento in posizione n
// assume che la SCL contenga almeno n elementi
TipoSCL delPosSCL(TipoSCL scl, int n) {
	if (n==0){
		//return restoSCL(scl); // Con condivisione di memoria
		return copySCL(restoSCL(scl));	// 	Senza condivisione di memoria (con copia)
	}
	else{
		return addSCL(delPosSCL(restoSCL(scl),n-1),primoSCL(scl));
	}
}


// modifica elemento in posizione n > 0 con valore e
// assume che la SCL contenga almeno n-1 elementi

// Implementazione con condivisione di memoria
TipoSCL setPosSCL(TipoSCL scl, TipoInfoSCL e, int n) {
	if (n==0) {
		// return addSCL(restoSCL(scl),e);// Con condivisione di memoria
		return addSCL(copySCL(restoSCL(scl)),e); // Senza condivizione di memoria (con copia)
	}
	else{
		return addSCL(setPosSCL(restoSCL(scl),e,n-1),primoSCL(scl));
	}
}


int main(){
	TipoSCL scl = NULL; // Lista vuota
	if (emptySCL(scl)){
		printf("La SCL e'vuota\n");
	}
	printf("Il primo valore e': %d\n", primoSCL(scl));

	TipoSCL scl1 = addSCL(scl,1);
	TipoSCL scl2 = addSCL(scl1,3);

	printf("scl1 = ");
	printSCL(scl1);

	scl2 = addSCL(scl2,7);
	printf("scl2 = ");
	printSCL(scl2);

	TipoSCL scl3 = copySCL(scl2);
	printf("scl3 = ");
	printSCL(scl3);

	scl3 = addPosSCL(scl3,9,1);
	printf("scl3 = ");
	printSCL(scl3);

	TipoSCL scl4 = addPosSCL(scl2,9,1);
	printf("scl4 = ");
	printSCL(scl4);

	TipoSCL scl5 = delPosSCL(scl4,2);
	printf("scl5 = ");
	printSCL(scl5);

	TipoSCL scl6 = setPosSCL(scl5,10,1);
	printf("scl6 = ");
	printSCL(scl6);


}
