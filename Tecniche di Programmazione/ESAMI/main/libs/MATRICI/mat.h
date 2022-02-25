#ifndef MAT_H
#define MAT_H

typedef struct {
  int r,c;     // numero di righe e numero di colonne
  int **punt;  // array di puntatori alle righe
} Mat;

Mat* mat_alloc(int r, int c);
void mat_free(int **m, int r, int c);
void print(int **m, int r, int c);
#endif

