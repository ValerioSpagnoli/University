#include <stdio.h>
#include <stdlib.h>

void inizializzaArrayRandom(double v[], int dim, double max_value);

void vec_print(double v[], int dim);

void vec_print(double v[], int dim);

double* vec_sum(double v[], int dim);

double* vec_rec(double v1[], double v2[], int dim1, int dim2);

int main(int argc, char **argv) {
  int dim1 = 10;
  double max_value = 10;
  
  /********************************************************
   *              TEST inizializzaArrayRandom             *
   ********************************************************/
  /*printf("Inizializzo l'array con numeri random...");
  double v1[dim1];
  inizializzaArrayRandom(v1, dim1, max_value);
  printf(" done.\n\n");
 */
  /********************************************************
   *                    TEST vec_print     v1             *
   ********************************************************/
  /*printf("v1: ");
  vec_print(v1, dim1);
  printf("\n\n");
  */
  /********************************************************
   *                    TEST allocate vectors             *
   ********************************************************/
  /*printf("Alloco il vettore v2...\n");
  
  printf("Alloco il vettore v3...\n");
  
  printf("v2: ");
  vec_print(v2, dim2);
  printf("\n");
  // 
  printf("v3: ");
  vec_print(v3, dim3);
  printf("\n\n");
  */
  
   /********************************************************
   *                    TEST vec_sum   v3                *
   ********************************************************/
   /*printf("Calcolo il vettore somma...\n\n");
   double *sum = vec_sum(v3, dim3);
   vec_print(sum, dim3);
   printf("\n");
   free(sum);
   */
   
   /********************************************************
   *                    TEST vec_rec  v3                *
   ********************************************************/
   /*printf("Calcolo il vettore v3 a meno delle ricorrenze dei valori in v4...\n\n");
   double* v4=( double *) malloc (dim3*sizeof(double));
   v4[0]= 4.8;
   v4[1]= 0.5;
   v4[2]= -4.2;
   v4[3]= -2.5;
   v4[4]= 2.3;
   double *v2_rec = vec_rec(v3, v4, dim2, dim3);
   vec_print(v2_rec, dim3);
   printf("\n");
   free(v2_rec);
   */

  return 0;
}

void inizializzaArrayRandom(double v[], int dim, double max_value) {
  srand(3);
  int i;
  for (i=0;i<dim;i++){
    v[i]=rand() % 10;
  }
}

// da qui in poi definire le funzioni chiamate nel main.
