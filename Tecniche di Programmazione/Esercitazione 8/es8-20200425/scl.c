#pragma once
#include "scl.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>



TipoSCL newNode(TipoInfoSCL info)
{
  TipoSCL result = (TipoNodoSCL*)malloc(sizeof(TipoNodoSCL));
  result->info = info;
  result->next = NULL;
  return result;
}

void addSCL (TipoSCL *scl, TipoInfoSCL e) {
  TipoSCL temp = *scl;
  *scl = (TipoNodoSCL *) malloc(sizeof(TipoNodoSCL));
  (*scl)->info = e;
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


// creazione scl random
void creaRandomSCL (TipoSCL *scl, int n) {
  if (n>0) {
    float e = ((float)rand()/(float)(RAND_MAX)) * 20 - 10;
    addSCL(scl, e);
    creaRandomSCL(scl,n-1);
  }
}

// dealloca tutta la scl
void freeSCL(TipoSCL *scl) {
  if (!emptySCL(*scl)) {
    delSCL(scl);  // side-effect su scl
    freeSCL(scl);
  }
}



/*  schema ricorsione su SCL

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

}

*/

// scrittura dell'informazione nel nodo ( float )
void writeTipoInfo (TipoInfoSCL d) {
  printf("%d ", d);
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


// restituisce la lunghezza della scl
// Schema Contatore
int lengthSCL ( TipoSCL scl ) {
  if (emptySCL(scl))
    return 0;
  else
    return 1 + lengthSCL(scl->next);
}


// conta i valori positivi
// Schema Contatore condizionato
int countPosSCL ( TipoSCL scl ) {
  if (emptySCL(scl))
    return 0;
  else if (scl->info > 0)
    return 1 + countPosSCL(scl->next);
  else
    return countPosSCL(scl->next);
}


// restituisce true se trova e in scl
// Schema Accumulazione su OR
bool isinSCL (TipoSCL scl, TipoInfoSCL e) {
  if (emptySCL(scl))
    return false;
  else
    return (fabs(scl->info-e)<0.01) || isinSCL(scl->next,e);
}


// restituisce true se tutti i valori in scl sono positivi
// Schema Accumulazione su AND
bool allPosSCL (TipoSCL scl) {
  if (emptySCL(scl))
    return true;
  else
    return (scl->info>0) && allPosSCL(scl->next);
}


// restituisce la somma dei valori in scl
// Schema Accumulazione su +
float sumSCL (TipoSCL scl) {
  if (emptySCL(scl))
    return 0;
  else
    return scl->info + sumSCL(scl->next);
}

// funzione ausiliaria
float max(float a, float b) {
  return (a>b)?a:b;
}

// restituisce il valore massimo in scl
// Schema Accumulazione su max
float maxSCL (TipoSCL scl) {
  if (emptySCL(scl))
    return -999;
  else
    return max(scl->info, maxSCL(scl->next));
}






