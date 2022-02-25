#pragma once

typedef int TipoInfoSCL;

struct ElemSCL {
  TipoInfoSCL info;
  struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;

TipoSCL newNode(TipoInfoSCL info);
void addSCL (TipoSCL *scl, TipoInfoSCL e);
void delSCL (TipoSCL *scl);
bool emptySCL (TipoSCL scl);
void creaRandomSCL (TipoSCL *scl, int n);
void freeSCL(TipoSCL *scl);
void writeTipoInfo (TipoInfoSCL d);
void writeSCL (TipoSCL scl);
int lengthSCL ( TipoSCL scl );
int countPosSCL ( TipoSCL scl );
bool isinSCL (TipoSCL scl, TipoInfoSCL e);
bool allPosSCL (TipoSCL scl);
float sumSCL (TipoSCL scl);
float max(float a, float b);
float maxSCL (TipoSCL scl);
