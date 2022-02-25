#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

// allocazione dinamica della matrice
Mat *mat_alloc(int r, int c) {
    // Allocazione struttura Mat
    Mat *m = (Mat *)malloc(sizeof(Mat));
    // campi riga e colonna
    m->r = r; m->c = c;
    // campo array di puntatori
    m->punt = (int **)malloc(m->r*sizeof(int *)); 
    for (int i=0; i<m->r; i++) {
      m->punt[i] = (int *)malloc(m->c*sizeof(int));
    }
    return m;
}

// deallocazione della matrice
void mat_free(Mat *m) {
    if (m==NULL) return;
    for (int i=0; i<m->r; i++) {
      free(m->punt[i]);
    }
    free(m->punt);
    free(m);
}

// stampa per righe
void print(Mat *m) {
    if (m==NULL) return;
    for (int i=0; i<m->r; i++) {
      for (int j=0; j<m->c; j++) {
        printf("%3d ", m->punt[i][j]);
      }
      printf("\n");
    }
    printf("\n");
}

/* funzione template

Mat *f (....) {
    int rr = ..., rc = ...;
    Mat *r = mat_alloc(rr,rc);

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = ...;
      }
    }

    return r;
}

*/
