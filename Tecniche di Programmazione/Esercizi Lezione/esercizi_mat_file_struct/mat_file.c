#include<stdio.h>
#include<stdlib.h>

// allocazione dinamica della matrice
int** mat_alloc(int r, int c) {
    int **m = (int **)malloc(r*sizeof(int *)); // array di puntatori
    for (int i=0; i<r; i++) {
      m[i] = (int *)malloc(c*sizeof(int));
    }
    return m;
}

// deallocazione della matrice
void mat_free(int **m, int r, int c) {  // c non usata
    if (m==NULL) return;
    for (int i=0; i<r; i++) {
      free(m[i]);
    }
    free(m);
}

// stampa per righe
void print(int **m, int r, int c) {
    if (m==NULL) return;
    for (int i=0; i<r; i++) {
      for (int j=0; j<c; j++) {
        printf("%3d ", m[i][j]);
      }
      printf("\n");
    }
    printf("\n");
}

/* funzione template

int **f (....) {
    int rr = ..., rc = ...;
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = ...;
      }
    }

    return r;
}

*/




// matrice opposta
int **neg(int **a, int ar, int ac) {
    int rr = ar, rc = ac;
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = - a[i][j];
      }
    }
    return r;
}

// matrice trasposta
int **transpose(int **a, int ar, int ac) {
    int rr = ac, rc = ar;
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = a[j][i];
      }
    }

    return r;
}


// moltiplicazione
int **multiply(int **a, int ar, int ac, int **b, int br, int bc) {
    if (ac!=br) return NULL;
    int rr = ar, rc = bc;
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = 0;
        for (int k=0; k<ac; k++) {
          r[i][j] += a[i][k] * b[k][j];
        }
      }
    }

    return r;
}

// funzione ausiliaria
int max9ij(int **a, int ar, int ac, int i, int j) {
    int m = a[i][j];
    for (int u=i-1; u<=i+1; u++) {
      for (int v=j-1; v<=j+1; v++) {
        if ( (u>=0) && (u<ar) && (v>=0) && (v<ac) )  // elemento valido
          if (a[u][v]>m) {
            m = a[u][v];
          }
        //else  // elemento non valido
        //  ...
      }
    }
    return m;
}

// max9: matrice output contiene in i,j il massimo tra i valori
//       adiacenti a i,j nella matrice in input
int **max9(int **a, int ar, int ac) {
    int rr = ar, rc = ac;
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = max9ij(a,ar,ac,i,j);  // a[i][j] a[i-1][j-1] ... a[i+1][j+1]
      }
    }

    return r;
}

// max9step: matrice output contiene in i,j il massimo tra i valori
//        adiacenti a i,j nella matrice in input
//        step k
int **max9step(int **a, int ar, int ac, int k) {
    int rr = ar/k + (ar%k==0?0:1), rc = ac/k + (ac%k==0?0:1);
    int **r = mat_alloc(rr,rc);

    for (int i=0; i<rr; i++) {
      for (int j=0; j<rc; j++) {
        r[i][j] = max9ij(a,ar,ac,i*k,j*k);
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

int** read_from_file(char* file_path, int* r, int* c){
	FILE* pfile = fopen(file_path, "r");
	if (pfile == NULL){
		printf("Errore apertura file: %s\n",file_path);
		exit(1);
	}
	fscanf(pfile, "%d", r); //legge prima riga (# righe)
	fscanf(pfile, "%d", c); //legge seconda riga (# colonne)
	int** risultato = mat_alloc(*r,*c);
	int elem = 0;

	int i = 0;
	int j = 0;
	while (fscanf(pfile, "%d", &elem) != EOF){
		risultato[i][j]=elem;
		j = (1 + j) % *c;
		if (j==0) i++;
	}

	//Oppure:
	/*
	for(int i = 0; i < *r; i++){
		for (int j = 0; j < *c; j++){
			fscanf(pfile, "%d", &elem);
			risultato[i][j]=elem;
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

void write_to_file(int** mat, int r, int c, char* file_path){
	FILE* pfile = fopen(file_path, "w");
	if (pfile == NULL){
		printf("Errore apertura file: %s\n",file_path);
		exit(1);
	}
	fprintf(pfile, "%d\n%d\n",r,c);

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			fprintf(pfile, "%d", mat[i][j]);
			if (j == c-1){
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
Compilazione: g++ -o mat_file mat_file.c

Esempio di invocazione:
mat_file mat.txt out.txt
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

	int** m = read_from_file(in, &N, &M);

    print(m,N,M);

    int **n = neg(m,N,M);
    print(n,N,M);

    int **t = transpose(m,N,M);
	write_to_file(t, M, N, out);
    print(t,M,N);

    int **c = multiply(t,M,N,n,N,M);
    print(c,M,M);

    int **g = max9(c,M,M);
    print(g,M,M);

    int k=2;
    int hr = M/k+(M%k==0?0:1), hc = M/k+(M%k==0?0:1);
    int **h = max9step(c,M,M,k);
    print(h,hr,hc);

    mat_free(m,N,M);
    mat_free(n,N,M);
    mat_free(t,M,N);
    mat_free(c,M,M);
    mat_free(g,M,M);
    mat_free(h,hr,hc);

}
