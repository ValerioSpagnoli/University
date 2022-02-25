#include <stdio.h>
#include <stdlib.h>

void vec_print(int v[], int dim){
	printf("[ ");
	for(int i=0; i<dim; i++){
		printf("%d ", *(v+i));
		}
	printf("]\n");
}

////////////////////////////////////////////////////////////
				   	 //ALGORITIMI DI RICERCA//
////////////////////////////////////////////////////////////
bool ricercaSequenziale(int *v, int dim, int k){
	bool r = false;                   
	for(int i = 0; i<dim && !r; i++){ 
		r = r || (v[i] == k); 			 
	}
	return r;								 
}
/* O(n)
	r = false
	fino a che i è minore della dim dell'array o r == false...
	confronta l'i-esima componente di v con k e esegui un OR con r. Assegna il
   risultato ad r.
   ritorna r.
*/

//---------------------------------------------------------//

bool ricercaBinaria(int *v, int dim, int k){
	int left = 0, right = dim-1;
	while(left <= right){
		int med = (left + right) / 2;
		if(v[med] == k) return true;
		else if (v[med] < k) left = med + 1;
		else if (v[med] > k) right = med - 1;
	}
	return false;
}
/* O(n)
	Se right > left 
		termina.
	Altrimenti
		Se (v[med] == k) 
			ritorna true.
		Se (v[med] < k)
			cercha nella metà destra del vettore.
			left = med.
		Se (v[med] > k) 	
			cerca nella metà sinistra del vettore.
			right = med.
*/


////////////////////////////////////////////////////////////
				    //ALGORITIMI DI ORDINAMENTO//
////////////////////////////////////////////////////////////

void selectionSort(int *v, int dim){
	for(int i = 0; i< dim-1; i++){
		int jmin = i;
		for(int j = i+1; j<dim; j++){
			if(v[j]<v[jmin]) jmin = j;
		}
		int aux = v[jmin];
		v[jmin] = v[i];
		v[i] = aux;
	}
}
/* O(n^2)
	for(int i = 0; i<dim-<; i++){
		int jmin = i;
		for(int j = i+1; j<dim; j++){
			trovo l'indice del valore minore nell'array e lo assegno a jmin.
		}
		scambio il valore con indice i dell'array con il valore in indice jmin.
	}
*/

//---------------------------------------------------------//

void bubbleSort(int *v, int dim){
	bool ordinato = false;
	for(int i = 0; i < dim-1 && !ordinato; i++){
		ordinato = true;
		for(int j = dim-1; j>i; j++){
			if(v[j-1] > v[j]){
				int aux = v[j-1];
				v[j-1] = v[j];
				v[j] = aux;
				ordinato = false;
			}
		}
	}
}
/* O(n^2)
	bool ordinato = false.
	for(int i = 0, i < dim-1 && !ordinato; i++)
		ordinato = true
		for(int j = dim - 1, j>i, j++)
		Se due elementi adiacenti non sono ordinati
			scambiali
			ordinato = false
		Altrimenti 
			termina se non è stato fatto nessun scambio.
	}	
*/

//---------------------------------------------------------//

//funzione di fusione
void merge(int* v, int inf, int med, int sup){
	int m = sup - inf + 1; //dimensinoe array ausiliario
	int a[m]; //array ausiliario
	int i1 = inf; //indice array [inf, med]
	int i2 = med+1; // indice array [med+1, sup]
	int i = 0; // indice array ausiliario
	while((i1<=med) && (i2<=sup)){ // nessuno dei due vettori è stato scansionato 												 completamente.
		if(v[i1] <= v[i2]){ // se v[i1] <= v[i1]
			a[i] = v[i1];	  // assegna ad a[i] il valore di v[i1]	
			i1++;				  // incrementa i1 (NON viene incrementato i2)
			i++;             // incrementa i 
		}
		else if(v[i1] > v[i2]){
			a[i] = v[i2];	  // assegna ad a[i] il valore di v[i2]	
			i2++;				  // incrementa i2 (NON viene incrementato i1)
			i++;             // incrementa i 
		}
	}
	if(i2 > sup){ // termina prima la seconda parte del vettore
		for(int k = i1; k<=med; k++){ // da dove sta i1 fino a med
			a[i] = v[k];					// copia in a i valori di v
			i++;								// incrementa i
		}
	}
	else if(i1 > med){ //termina prima la prima parte del vettore
		for(int k = i2; k<=sup; k++){ // da dove sta i2 fino a sup
			a[i] = v[k]; 					// copia in a i valori di v
			i++; 								// incrementa i
		}
	}
	for(int k = 0; k<m; k++){ // per tutta la lunghezza del vettore ausiliario 
		v[inf+k] = a[k];		  // copia nel vettore originale il vettore ausiliario
	}
}

//funzione ausiliaria ricorsiva
void mergeSort_r(int* v, int inf, int sup){
	if(inf < sup){
		int med = (inf + sup) / 2;
		mergeSort_r(v, inf, med);
		mergeSort_r(v, med+1, sup);
		merge(v, inf, med, sup);
	}
}

//funzione principale
void mergeSort(int*v, int dim){
	mergeSort_r(v, 0, dim-1);
}

/* O(log(n))
	Se dimensnione < 2
		array è gia ordinato. Termina.
	Altrimenti se dimensione >= 2
		ordina la metà sinistra dell'array
		ordina la metà destra dell'array
		fondi le due parti in un array ordinato
*/

//---------------------------------------------------------//

void quickSort_r(int* v, int inf, int sup){
	if(inf<sup) {
		int i = inf, j = sup, pivot = v[inf];
		while(i < j){
			while(v[j] > pivot){
				j--;
			}
			while(i < j && v[i] <= pivot){
            i++;
			}
			if (i < j) {
				int a = v[i];
				v[i] = v[j];
				v[j] = a;
			}
		}
		if (inf != j) {
			v[inf] = v[j];
			v[j] = pivot;
		}
		if (inf < j-1) quickSort_r(v,inf,j-1); 
		if (sup > j+1) quickSort_r(v,j+1,sup);
	}
}

void quickSort(int* v, int dim){
	quickSort_r(v, 0, dim-1);
}
/* O(n^2), ma nella maggior parte dei casi tende a O(log(n))
	Scegli il pivot come primo elementi
	conta quanti elementi sono più piccoli del pivot e mettili prima del pivot
	esegui la ricorsione a sinistra del pivot
	esegui la ricorsione a destra del pivot
*/

int main(){


	printf("\n                ***** ARRAY ***** \n\n");

	printf("ARRAY 1: ");
	int v1[10];
	v1[0] = 10; v1[1] = 61; v1[2] = 8; v1[3] = 22; v1[4] = 1; v1[5] = 9; v1[6] = 13;
	v1[7] = 37; v1[8] = 16; v1[9] = 20;
	vec_print(v1, 10); 

	printf("\n\n");

	printf("ARRAY 2: ");
	int v2[10];
	v2[0] = 12; v2[1] = 50; v2[2] = 8; v2[3] = 30; v2[4] = 15; v2[5] = 9; v2[6] = 18;
	v2[7] = 33; v2[8] = 7; v2[9] = 21;
	vec_print(v2, 10); 

	printf("\n\n");

	printf("ARRAY 3: ");
	int v3[10];
	v3[0] = 76; v3[1] = 51; v3[2] = 3; v3[3] = 23; v3[4] = 15; v3[5] = 17; v3[6] = 11;
	v3[7] = 5; v3[8] = 6; v3[9] = 30;
	vec_print(v3, 10); 
	
	printf("\n\n");

	printf("ARRAY 4: ");
	int v4[10];
	v4[0] = 14; v4[1] = 2; v4[2] = 7; v4[3] = 28; v4[4] = 34; v4[5] = 75; v4[6] = 13;
	v4[7] = 48; v4[8] = 61; v4[9] = 4;
	vec_print(v4, 10);
	
	printf("\n\n"); 

	printf("\n\n         ***** ALGORITMI DI RICERCA *****\n\n");
	
	printf("RICERCA SEQUENZIALE:\n\n");
	printf("Cerco il numero 10 nell'array 1 ... ");
	bool b = (ricercaSequenziale(v1, 10, 10)) ? printf("trovato.\n\n") : 																	       printf("non trovato.\n\n");
	
	printf("\n");	

	printf("RICERCA BINARIA:\n\n");
	printf("Cerco il numero 18 nell'array 2 ... ");
	bool b1 = (ricercaBinaria(v2, 10, 18)) ? printf("trovato.\n\n") : 														  printf("non trovato.\n\n");

	printf("\n");

	printf("\n\n       ***** ALGORITMI DI ORDINAMENTO *****\n\n");

	printf("SELECTION SORT:\n\n");
	printf("Ordino l'ARRAY 1 ... ");
	selectionSort(v1, 10);
	vec_print(v1, 10);
	printf("\n\n");

	printf("BUBBLE SORT:\n\n");
	printf("Ordino l'ARRAY 2 ... ");
	selectionSort(v2, 10);
	vec_print(v2, 10);
	printf("\n\n");

	printf("MERGE SORT:\n\n");
	printf("Ordino l'ARRAY 3 ... ");
	mergeSort(v3, 10);
	vec_print(v3, 10);
	printf("\n\n");

	printf("QUICK SORT:\n\n");
	printf("Ordino l'ARRAY 4 ... ");
	quickSort(v4, 10);
	vec_print(v4, 10);
	printf("\n\n");
}
