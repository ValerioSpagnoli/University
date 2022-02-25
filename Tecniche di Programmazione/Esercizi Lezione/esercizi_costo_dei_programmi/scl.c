#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<float.h>

typedef float TipoInfoSCL;

struct ElemSCL {
  TipoInfoSCL info ;
  struct ElemSCL *next ;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;


void addSCL (TipoSCL *scl, TipoInfoSCL e) {
  TipoSCL temp = * scl ;
  *scl = (TipoNodoSCL *) malloc(sizeof(TipoNodoSCL));
  (*scl)->info = e;
  (*scl)->next = temp;
}

void delSCL (TipoSCL *scl) {
  TipoSCL temp = *scl;
  *scl = (*scl)->next;
  free(temp);
}


void creaSCL (TipoSCL *scl, int n, float e) {
	if (n<=0){
		*scl = NULL;
		return;
	}
	*scl = (TipoNodoSCL*) malloc(sizeof(TipoNodoSCL));
	*scl -> info = e;
	creaSCL(&((*scl)->next),n-1,e);
}


// creazione scl random
void creaRandomSCL (TipoSCL *scl, int n) {
	if (n<=0){
		*scl = NULL;
		return;
	}
	*scl = (TipoNodoSCL*) malloc(sizeof(TipoNodoSCL));
	*scl -> info = ...;
	creaRandomSCL(&((*scl)->next),n-1);

}

// restituisce true se scl e’ vuota
bool emptySCL (TipoSCL scl) {
  return scl==NULL;
}

// dealloca tutta la scl
void freeSCL(TipoSCL *scl) {
  if (*scl!=NULL) {
    delSCL(scl);
    freeSCL(scl);
  }
}

// scrittura dell’ informazione nel nodo ( float )
void writeTipoInfo (TipoInfoSCL d) {
  printf("%.2f ", d);
}

void writeSCL (TipoSCL scl) {
  if (emptySCL(scl))
    printf("\n");
  else {
    writeTipoInfo(scl->info);
    writeSCL(scl->next);
  }
}

// restituisce la lunghezza della scl
// Schema Contatore
int lengthSCL ( TipoSCL scl ) {
	if (emptySCL(scl)){
		return 0;
	}
	return 1 + lengthSCL(scl -> next);
}

// conta i valori positivi
// Schema Contatore condizionato
int countPosSCL ( TipoSCL scl ) {
	if (emptySCL(scl)){ // 1
		return 0; // 1
	}
	if (scl -> info > 0){ // 1
		return 1 + countPosSCL(scl -> next); // 1
	}
	return countPosSCL(scl -> next); // 1
}

//costo della funzione ricorsiva (per input di dimensione n) =
							//numero di chiamate ricorsive (per input di dim n)*
							//costo di ogni chiamata

// costo (su input dim n) = n * (1+1+1) = 3n = O(n) <--

// costo (su input dim n) = n * 5 = 5n = O(n) <--

// restituisce true se trova e in scl
// Schema Accumulazione su OR
bool isinSCL (TipoSCL scl, TipoInfoSCL e) {
	if (emptySCL(scl))
		return false;
	return ((scl -> info == e) || isinSCL(scl->next,e));
}

// restituisce true se tutti i valori in scl sono positivi
// Schema Accumulazione su AND
bool allPosSCL (TipoSCL scl) {
	if (emptySCL(scl)){
		return true;
	}
	return (scl -> info > 0) && (allPosSCL(scl -> next));
}


// restituisce la somma dei valori in scl
// Schema Accumulazione su +
float sumSCL (TipoSCL scl) {
	if (emptySCL(scl)){
		return 0;
	}
	return (scl -> info) + sumSCL(scl -> next);
}

// funzione ausiliaria
float max(float a, float b) {
  return (a>b)?a:b;
}

// restituisce il valore massimo in scl
// Schema Accumulazione su max
float maxSCL (TipoSCL scl) {
	if (emptySCL(scl)){
		return -FLT_MAX;
	}
	return max(scl->info,maxSCL(scl -> next));
}




int main() {
  srand(20200416);
  // srand(time(NULL));

  TipoSCL scl1 = NULL;
  TipoSCL scl2 = NULL;
  creaRandomSCL(&scl1, 10);
  creaRandomSCL(&scl2, 10);
  writeSCL(scl1);
  writeSCL(scl2);


  int l1 = lengthSCL(scl1);
  int l2 = lengthSCL(scl2);
  printf("length: %d %d\n", l1, l2);

  int p1 = countPosSCL(scl1);
  int p2 = countPosSCL(scl2);
  printf("count pos: %d %d\n", p1, p2);

  float e = -5.55;
  bool i1 = isinSCL(scl1, e);
  bool i2 = isinSCL(scl2, e);
  printf("isin %.2f: %d %d\n", e, i1, i2);

  bool a1 = allPosSCL(scl1);
  bool a2 = allPosSCL(scl2);
  printf("all pos: %d %d\n", a1, a2);

  float s1 = sumSCL(scl1);
  float s2 = sumSCL(scl2);
  printf("sum: %.2f %.2f\n", s1, s2);

  float m1 = maxSCL(scl1);
  float m2 = maxSCL(scl2);
  printf("max: %.2f %.2f\n", m1, m2);

  freeSCL(&scl1);
  freeSCL(&scl2);

}
