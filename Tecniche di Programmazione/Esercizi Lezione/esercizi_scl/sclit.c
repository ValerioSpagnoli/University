#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef float TipoInfoSCL;

struct ElemSCL {
  TipoInfoSCL info;
  struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;

// inserisce un elemento in testo
void addSCL (TipoSCL *scl, TipoInfoSCL e) {
  TipoSCL temp = *scl;
  *scl = (TipoNodoSCL *) malloc(sizeof(TipoNodoSCL));
  (*scl)->info = e;
  (*scl)->next = temp;
}

// elimina e dealloca il primo elemento
void delSCL (TipoSCL *scl) {
  TipoSCL temp = *scl;
  *scl = (*scl)->next;
  free(temp);
}

// restituisce true se scl e’ vuota
bool emptySCL (TipoSCL scl) {
  return scl==NULL;
}


// creazione scl random
void creaRandomSCL (TipoSCL *scl, int n) {
  for (int i=0; i<n; i++) {
    float e = ((float)rand()/(float)(RAND_MAX)) * 20 - 10;
    addSCL(scl, e); // side-effect su scl   
  }
}

// dealloca tutta la scl
void freeSCL(TipoSCL *scl) {
  while (!emptySCL(*scl)) {
    delSCL(scl);  // side-effect su scl
  }
}


/*  schema iterativo su SCL

... f(TipoSCL scl, ...) {

  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    ... scl->info
    // spostamento al prossimo nodo
    scl = scl->next;
  }

}

*/


// scrittura dell'informazione nel nodo ( float )
void writeTipoInfo (TipoInfoSCL d) {
  printf("%.2f ", d);
}

// scrittura della SCL
void writeSCL (TipoSCL scl) {
  while (! emptySCL(scl)) {
    writeTipoInfo(scl->info);
    scl = scl->next;
  }
  printf("\n");
}


// modifica la scl con tutti valori assoluti
void absSCL(TipoSCL scl) {
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    if (scl->info < 0) {
      scl->info = -scl->info;
    }
    // spostamento al prossimo nodo
    scl = scl->next;
  }
}


// modifica il primo valore negativo nella scl con il valore assoluto
void absFirstSCL(TipoSCL scl) {
  bool primo = false;
  while (! emptySCL(scl)  && ! primo) {
    // operazione sull'elemento corrente
    if (scl->info < 0) {
      scl->info = -scl->info;
      primo = true;
    }
    // spostamento al prossimo nodo
    scl = scl->next;
  }
}


// restituisce la lunghezza della scl
// Schema Contatore
int lengthSCL (TipoSCL scl) {
  int c = 0;
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    c++; // scl->info
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return c;
}


// conta i valori positivi
// Schema Contatore condizionato
int countPosSCL (TipoSCL scl) {
  int c = 0;
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    if (scl->info > 0)
      c++;
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return c;
}


// restituisce true se trova e in scl (fabs(scl->info-e)<0.01)
// Schema Accumulazione su OR
bool isinSCL (TipoSCL scl, TipoInfoSCL e) {
  bool r = false;
  while (! emptySCL(scl) && !r) {
    // operazione sull'elemento corrente
    r = r || (fabs(scl->info-e)<0.01);
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return r;
}


// restituisce true se tutti i valori in scl sono positivi
// Schema Accumulazione su AND
bool allPosSCL (TipoSCL scl) {
  bool r = true;
  while (! emptySCL(scl) && r) {
    // operazione sull'elemento corrente
    r = r && (scl->info>0);
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return r;
}


// restituisce la somma dei valori in scl
// Schema Accumulazione su +
float sumSCL (TipoSCL scl) {
  float r = 0.0;
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    r = r + scl->info;
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return r;
}

// funzione ausiliaria
float max(float a, float b) {
  return (a>b)?a:b;
}

// restituisce il valore massimo in scl
// Schema Accumulazione su max
float maxSCL (TipoSCL scl) {
  float r = -999;
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    r = max(r,scl->info);
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return r;
}



// restituisce il valore massimo in scl non vuota
// Schema Accumulazione su max
float max2SCL (TipoSCL scl) {
  float r;
  if (!emptySCL(scl))
    r = scl->info;
  while (! emptySCL(scl)) {
    // operazione sull'elemento corrente
    r = max(r,scl->info);
    // spostamento al prossimo nodo
    scl = scl->next;
  }
  return r;
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

  absFirstSCL(scl2);
  writeSCL(scl2);

  absSCL(scl2);
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




