#include <stdlib.h>
#include <stdio.h>
#include <ctime>

// T(n) = O(log n)
int f1(int* a, int n){
	int c = 1;
	int r = 0;
	while (c < n && a[c] != 0){
		r += a[c];//operazione dominante
		c += c; // 1,2,4,8,16,32,...
	}
	return r;
}

// T(n) = O(n)
int f2(int* a, int n){
	int c = 1;
	int r = 0;
	while (c < n && a[c] != 0){
		r += a[c];
		for (int j=c; j>0; j--){
			c++; // operazione dominante: n volte
		}
	}
	return r;
}

/*
Crea un array con un numero casuale di elementi tra 0 e 50,
lo popola con valori compresi tra 0 e 10,
ne restituisce il puntatore,
assegna alla variabile puntata da n la dimensione dell'array
*/

int* creaRandomArray(int* n){
	*n = (rand() % 50);
	int* r = (int*) malloc((*n)*sizeof(int));
	for (int i = 0; i < *n; i++){
		r[i] = rand() % 10;
	}
	return r;
}

void stampaArray(int* a, int n){
	printf("n = %d\n",n);
	printf("a = [");
	for (int i = 0; i < n; i++){
		printf("%d",a[i]);
		if (i < n-1){
			printf(" ");
		}
		else{
			printf("]");
		}
	}
}


int main(){
	srand(time(NULL));// per generazione valori random
	int n = 0;
	int* a = creaRandomArray(&n);
	stampaArray(a,n);
	printf("\n");
	int v1 = f1(a,n);
	int v2 = f2(a,n);
	printf("f1(a,n); = %d\n", v1);
	printf("f2(a,n); = %d\n", v2);
}
