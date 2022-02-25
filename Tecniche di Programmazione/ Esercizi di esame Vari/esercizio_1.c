#include <stdio.h>
#include <stdlib.h>

#include "esercizio_1.h"

/*

Esercizio 1

Sia data la seguente struttura Mat:

struct Mat {
  int cols; // numero di colonne
  int rows; // numero di righe
  int** row_ptrs; // puntatori alle righe
};

Implementare la seguente funzione C:

void prodCont(Mat* src, Mat* dst);

che, date in input una matrice src e una matrice dst (gia' allocata e contenente valori nulli), assegni alla cella [r,c] della matrice di output dst, il valore src[r,c] sommato al prodotto dei 2 elementi a destra e a sinistra di src[r,c]. Se una cella si trova sul bordo, l'elemento mancante vale src[r,c]. 

*/

void prodCont( Mat* src, Mat* dst ) {
	int r = src->rows;
	int c = src->cols;
	for(int i = 0; i<r; i++){
		for(int j = 0; j<c; j++){
			if(j==0|| j==c-1 ){
				dst->row_ptrs[i][j] = src->row_ptrs[i][j];
			}
			else{
				dst->row_ptrs[i][j] =  src->row_ptrs[i][j] + ((src->row_ptrs[i][j-1]) * (src->row_ptrs[i][j+1]));
			}
		}
	}
}


//SOLUZIONE

/*void prodCont( Mat* src, Mat* dst ) {

  int rows = src->rows, cols = src->cols;
  
  for( int r = 0; r < rows; r++ ) {   
    for( int c = 0; c < cols; c++ ) {
      int val = src->row_ptrs[r][c];
      int ll=0, rr=0;
	  if (c == 0)
        ll = val;
      else
        ll = src->row_ptrs[r][c-1];
	  if (c == cols-1)
        rr = val;
      else
        rr = src->row_ptrs[r][c+1];
      dst->row_ptrs[r][c] = val + ll*rr;
    }    
  }  
}*/
