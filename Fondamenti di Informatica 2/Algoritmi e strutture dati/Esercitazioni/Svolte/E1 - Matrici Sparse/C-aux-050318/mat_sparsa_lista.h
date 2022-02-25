#ifndef __MAT_SPARSA_LISTA__
#define __MAT_SPARSA_LISTA__

//Il tipo matrice sparsa
typedef struct matrice_sparsa matrice_sparsa;

//Costruttore di una matrice ad m righe ed n colonne
matrice_sparsa* matrice_sparsa_new(int m, int n);

//Restituisce il numero di colonne di mat
int get_num_col(matrice_sparsa* mat);

//Restituisce il numero di righe di mat
int get_num_row(matrice_sparsa* mat);

//Distruttore
void matrice_sparsa_delete(matrice_sparsa* mat);

//Applicata a mat, imposta il valore della cella <i,j> ad x
void mat_set(matrice_sparsa* mat, int i, int j, int x);

//Funziona che ritorna il valore in <i,j> di mat
int mat_get(matrice_sparsa* mat, int i, int j);

//Stampa a video la matrice mat
void mat_print(matrice_sparsa* mat);

//Ritorna mat1+mat2 come una nuova matrice
matrice_sparsa* mat_add(matrice_sparsa* mat1, matrice_sparsa* mat2);

//Ritorna mat^t come una nuova matrice
matrice_sparsa* mat_tra(matrice_sparsa* mat);

//Ritorna mat1*mat2 come una nuova matrice
matrice_sparsa* mat_mul(matrice_sparsa* mat1, matrice_sparsa* mat2);

#endif // !__MAT_SPARSA_LISTA__
