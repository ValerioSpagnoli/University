#include<stdio.h>
#include<stdlib.h>
#include"mat.h"

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




// matrice opposta
Mat *neg(Mat *a) {
    int rr = a->r, rc = a->c;
    Mat *r = mat_alloc(rr,rc);

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = - a->punt[i][j];
      }
    }
    return r;
}

// matrice trasposta
Mat *transpose(Mat *a) {
    int rr = a->c, rc = a->r;
    Mat *r = mat_alloc(rr,rc);

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = a->punt[j][i];
      }
    }


    return r;
}


// moltiplicazione
Mat *multiply(Mat *a, Mat *b) {
    if (a->c!=b->r) return NULL;
    int rr = a->r, rc = b->c;
    Mat *r = mat_alloc(rr,rc);	

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = 0;
        for (int k=0; k<a->c; k++) {
          r->punt[i][j] += a->punt[i][k] * b->punt[k][j];
        }
      }
    }

    return r;
}

// funzione ausiliaria
int max9ij(Mat *a, int i, int j) {
    int m = a->punt[i][j];
    for (int u=i-1; u<=i+1; u++) {
      for (int v=j-1; v<=j+1; v++) {
        if ( (u>=0) && (u<a->r) && (v>=0) && (v<a->c) )  // elemento valido
          if (a->punt[u][v]>m) {
            m = a->punt[u][v];
          }
        //else  // elemento non valido
        //  ...
      }
    }
    return m;
}

// max9: matrice output contiene in i,j il massimo tra i valori
//       adiacenti a i,j nella matrice in input
Mat *max9(Mat *a) {
    int rr = a->r, rc = a->c;
    Mat *r = mat_alloc(rr,rc);

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = max9ij(a,i,j);  // a[i][j] a[i-1][j-1] ... a[i+1][j+1]
      }
    }

    return r;
}

// max9step: matrice output contiene in i,j il massimo tra i valori
//        adiacenti a i,j nella matrice in input
//        step k
Mat *max9step(Mat *a, int k) {
    int rr = a->r/k + (a->r%k==0?0:1), rc = a->c/k + (a->c%k==0?0:1);
    Mat *r = mat_alloc(rr,rc);

    for (int i=0; i<r->r; i++) {
      for (int j=0; j<r->c; j++) {
        r->punt[i][j] = max9ij(a,i*k,j*k);
      }
    }

    return r;
}

/*
Restituisce una nuova matrice ottenuta dal
contenuto del file identificato da file_path

Assegna alle variabili puntate da r e c ()
rispettivamente i numeri di righe e colonne della
matrice letta

Il file deve essere formattato come segue:

N: numero di righe
M: numero di colonne
e_00 ... e_0M
...
e_n0 .... e_NM
*/

Mat* read_from_file(char* file_path, int* r, int* c){
	FILE* pfile = fopen(file_path, "r");
	if (pfile == NULL){
		printf("Errore apertura file: %s\n",file_path);
		exit(1);
	}
	fscanf(pfile, "%d", r); //legge primo valore (# righe)
	fscanf(pfile, "%d", c); //legge secondo valore (# colonne)
	Mat* risultato = mat_alloc(*r,*c);
	int elem = 0;

	int i = 0;
	int j = 0;
	while (fscanf(pfile, "%d", &elem) != EOF){
		risultato->punt[i][j]=elem;
		j = (1 + j) % *c;
		if (j==0) i++;
	}

	//Oppure:
	/*
	for(int i = 0; i < *r; i++){
		for (int j = 0; j < *c; j++){
			fscanf(pfile, "%d", &elem);
			risultato->punt[i][j]=elem;
		}
	}
	*/

	int close = fclose(pfile);
	if (close == EOF){
		printf("Impossibile chiudere il file: %s", file_path);
		exit(1);
	}
	return risultato;
}

/*
Scrive il contenuto della matrice mat letta per righe
nel file identificato da file_path
Il file viene formattato come in read_from_file
*/

void write_to_file(Mat* mat, char* file_path){
	FILE* pfile = fopen(file_path, "w");
	if (pfile == NULL){
		printf("Errore apertura file: %s\n",file_path);
		exit(1);
	}
	fprintf(pfile, "%d\n%d\n",mat->r,mat->c);

	for(int i = 0; i < mat->r; i++){
		for(int j = 0; j < mat->c; j++){
			fprintf(pfile, "%d", mat->punt[i][j]);
			if (j == mat->c-1){
				fprintf(pfile, "\n");
			}
			else{
				fprintf(pfile, " ");
			}
		}
	}

	int close = fclose(pfile);
	if (close == EOF){
		printf("Impossibile chiudere il file: %s", file_path);
		exit(1);
	}
	return;
}

/*
Compilazione: g++ -o mat_struct mat_struct.c

Esempio di invocazione:
./mat_struct mat.txt out.txt
*/

int main(int argc, char** argv) {
	if(argc != 3){
		printf("\n%s: \n",argv[0]);
		printf("ERRORE: specificare un file di input e uno di output\n\n");
		exit(1);
	}

	char* in = argv[1];
	char* out = argv[2];

    int N = 0, M = 0;

	Mat *m = read_from_file(in, &N, &M);

    print(m);

    Mat *n = neg(m);
    print(n);

    Mat *t = transpose(m);
    print(t);

    Mat *c = multiply(t,n);
    print(c);

    Mat *g = max9(c);
    print(g);

    int k=2;
    Mat *h = max9step(c,k);
    print(h);
	write_to_file(h, out);

    mat_free(m);
    mat_free(n);
    mat_free(t);
    mat_free(c);
    mat_free(g);
    mat_free(h);

}
