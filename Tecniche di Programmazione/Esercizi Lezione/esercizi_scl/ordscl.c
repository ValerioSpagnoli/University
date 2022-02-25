#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct {
  int matricola;
  int voto;
} TipoInfoSCL;

struct ElemSCL {
  TipoInfoSCL info;
  struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;


void addSCL (TipoSCL *scl, TipoInfoSCL e) {
  TipoSCL temp = *scl;
  *scl = (TipoNodoSCL *) malloc(sizeof(TipoNodoSCL));
  (*scl)->info = e;  // copia di record 
  (*scl)->next = temp;
}

void delSCL (TipoSCL *scl) {
  TipoSCL temp = *scl;
  *scl = (*scl)->next;
  free(temp);
}

// restituisce true se scl e’ vuota
bool emptySCL (TipoSCL scl) {
  return scl==NULL;
}

// dealloca tutta la scl
void freeSCL(TipoSCL *scl) {
  if (!emptySCL(*scl)) {
    delSCL(scl);  // side-effect su scl
    freeSCL(scl);
  }
}



/*  schema ricorsione su SCL

funzioni che non modificano scl

... f(TipoSCL scl, ...) {

  if (emptySCL(scl))
    // passo base
  else {
    // passo ricorsivo
    // operazione sul primo elemento
    ... scl->info
    // ricorsione sul resto della scl
    ... f(scl->next, ...)
  }


funzioni che modificano la struttura della scl

... f(TipoSCL *scl, ...) {

  if (emptySCL(*scl))
    // passo base
  else {
    // passo ricorsivo
    // operazione sul primo elemento
    ... (*scl)->info
    // ricorsione sul resto della scl
    ... f(&((*scl)->next), ...)
  }

*/

// scrittura dell'informazione nel nodo
void writeTipoInfo (TipoInfoSCL d) {
  printf("%d  %d\n", d.matricola, d.voto);
}

// scrittura della SCL
void writeSCL (TipoSCL scl) {
  if (emptySCL(scl))
    printf("\n");
  else {
    writeTipoInfo(scl->info);
    writeSCL(scl->next);
  }
}

// inserisci e in scl ordinata (per matricola)
void insOrdSCL(TipoSCL *scl, TipoInfoSCL e) {
  if (emptySCL(*scl))
    // passo base
    addSCL(scl,e);
  else if (e.matricola < (*scl)->info.matricola)
    // passo base
    addSCL(scl,e);
  else {
    // passo ricorsivo
    // ricorsione sul resto della scl
    insOrdSCL(&((*scl)->next),e);
  }
}

// elimina elemento con matricola
void delElemSCL(TipoSCL *scl, int matr) {
  if (emptySCL(*scl))
    // passo base
    return;
  else if ((*scl)->info.matricola == matr) 
    // passo base
    delSCL(scl);
  else {
    // passo ricorsivo
    // ricorsione sul resto della scl
    delElemSCL(&((*scl)->next), matr);
  }
}

// funzione ausiliaria
void randomElemSCL(TipoInfoSCL *e) {
  e->matricola = rand()%100000 + 100000;
  e->voto = rand()%13 + 18;
}

// creazione scl random ordinata
void creaRandomOrdSCL (TipoSCL *scl, int n) {
  if (n==0)
    // passo base
    return;
  else {
    // passo ricorsivo
    // operazione sul primo elemento
    TipoInfoSCL e;
    randomElemSCL(&e);
    insOrdSCL(scl,e);
    // ricorsione sul resto della scl
    creaRandomOrdSCL(scl, n-1);
  }
}

// verifica se la scl è ordinata per matricola
// Schema Accumulazione su AND
bool isOrderedSCL (TipoSCL scl) {
  if (emptySCL(scl))  // scl == NULL
    // passo base
    return true;
  else if (emptySCL(scl->next)) // scl->next == NULL
    // passo base
    return true;
  else { // contiene almeno due elementi
    // passo ricorsivo
    // operazione sul primo elemento
    bool t = (scl->info.matricola <= scl->next->info.matricola);
    // ricorsione sul resto della scl
    return t && isOrderedSCL(scl->next);
  }
}


// restituisce true se trova matricola in scl
// Schema Accumulazione su OR
bool isinSCL (TipoSCL scl, int matr) {
  if (emptySCL(scl))
    return false;
  else
    return (scl->info.matricola == matr) || isinSCL(scl->next, matr);
}

// conta coppie di valori (matricole) uguali 
// anche se la scl non è ordinata
// Schema Contatore condizionato
int contaDuplicatiSCL (TipoSCL scl) {
  if (emptySCL(scl))
    return 0;
  else if (isinSCL(scl->next, scl->info.matricola))
    return 1 + contaDuplicatiSCL(scl->next);
  else
    return contaDuplicatiSCL(scl->next);
}

// copia SCL
void copiaSCL(TipoSCL *dst, TipoSCL src) {
  if (emptySCL(src))
    return;
  else {
    TipoInfoSCL e = src->info;
    copiaSCL(dst,src->next);
    addSCL(dst,e);
  }
}

// copia SCL inversa
void invertiSCL(TipoSCL *dst, TipoSCL src) {
  if (emptySCL(src))
    return;
  else {
    TipoInfoSCL e = src->info;
    addSCL(dst,e);
    invertiSCL(dst,src->next);
  }
}

// funzione ausiliaria
// assumiamo scl sia non vuota
float mediaVoti_r(TipoSCL scl, int s, int n) {
  if (emptySCL(scl))
    // passo base 
    return (float)s / (float)n;
  else
    return mediaVoti_r(scl->next, s + scl->info.voto, n+1);
}

float mediaVoti(TipoSCL scl) {
  return mediaVoti_r(scl,0,0);
}


// funzione ausiliaria
// verifica presenza matr in array vmatr
bool isinArray(int *vmatr, int n, int matr) {
  if (n==0)
    return false;
  else
    return (vmatr[0]==matr) || isinArray(vmatr+1, n-1, matr);
}

// aggiunge il bonus alle matricole presenti in vmatr
void addBonus(TipoSCL scl, int* vmatr, int n) {
  if (emptySCL(scl))
    return;
  else {
    if (isinArray(vmatr, n, scl->info.matricola)) 
      scl->info.voto += 1;
    addBonus(scl->next, vmatr, n);
  }
}


// inserisci e in scl ordinata (per voto decrescente)
void insOrdVotoSCL(TipoSCL *scl, TipoInfoSCL e) {
  if (emptySCL(*scl))
    // passo base
    addSCL(scl,e);
  else if (e.voto >= (*scl)->info.voto)
    // passo base
    addSCL(scl,e);
  else {
    // passo ricorsivo
    // ricorsione sul resto della scl
    insOrdVotoSCL(&((*scl)->next),e);
  }
}

// copia ordinata per voto decrescente
void ordVotoSCL(TipoSCL *dst, TipoSCL src) {
  if (emptySCL(src))
    return;
  else {
    TipoInfoSCL e = src->info;
    ordVotoSCL(dst,src->next);
    insOrdVotoSCL(dst,e);
  }
}

int main() {

  srand(20200417);
  // srand(time(NULL));

  TipoSCL scl1 = NULL;
  creaRandomOrdSCL(&scl1, 10);
  writeSCL(scl1);

  int o1 = isOrderedSCL(scl1);
  printf("ordinata: %d\n\n", o1);

  int c1 = contaDuplicatiSCL(scl1);
  printf("duplicati: %d\n\n", c1);

  float m1 = mediaVoti(scl1);
  printf("media voti: %.2f\n\n", m1);

  TipoSCL scl2 = NULL;
  TipoSCL scl3 = NULL;
  TipoSCL scl4 = NULL;

  copiaSCL(&scl2, scl1);
  writeSCL(scl2);

  invertiSCL(&scl3, scl1);
  writeSCL(scl3);

  int vmatr[] = { 157010, 157103 };
  addBonus(scl1,vmatr,2);
  writeSCL(scl1);

  TipoSCL scl5 = NULL;
  ordVotoSCL(&scl5, scl1);
  writeSCL(scl5);

  delElemSCL(&scl5, 157010);
  delElemSCL(&scl5, 157103);
  writeSCL(scl5);

  freeSCL(&scl1);
  freeSCL(&scl2);
  freeSCL(&scl3);
  freeSCL(&scl4);
  freeSCL(&scl5);

}




