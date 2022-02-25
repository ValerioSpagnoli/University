#include <stdio.h>
#include <stdlib.h>

void inizializzaArrayRandom(double v[], int dim, double max_value);

void vec_scale(double v[], int dim, double scale);

double vec_dot(double src1[], double src2[], int dim);

double* vec_clone(double v[], int dim);

bool vec_positive_check(double v[], int dim);

int main(int argc, char **argv) {
  int dim1 = 10;
  double max_value = 10;
  
  /********************************************************
   *              TEST inizializzaArrayRandom             *
   ********************************************************/
  printf("Inizializzo l'array con numeri random...");
  double v1[dim1];
  inizializzaArrayRandom(v1, dim1, max_value);
  printf(" done.\n\n");

  /********************************************************
   *                    TEST vec_scale  v3                *
   ********************************************************/
  // printf("Scalo v3 di un fattore di 0.5...");
  // vec_scale(v3, dim3, 0.5);
  // printf(" done.\n");
  // printf("v3: ");
  // vec_print(v3, dim3);  
  // printf("\n");

  /********************************************************
   *                    TEST vec_dot  v2°v3
   *
   ********************************************************/
  // printf("Calcolo il prodotto scalare tra v2 e v3...");
  // double dot = vec_dot(v2, v3, dim2);
  // printf(" done.\n");
  // printf("Il prodotto scalare tra v2 e v3 e': %lf\n\n", dot);

  /********************************************************
   *                    TEST vec_clone  v2                *
   ********************************************************/
  // printf("Clono v2...");
  // double *copy_v2 = vec_clone(v2, dim2);
  // printf(" done.\n");
  // printf("Copia v2: ");
  // vec_print(copy_v2, dim2);  

  /********************************************************
  *                    TEST vec_positive_check  v2        *
  ********************************************************/
  //printf("Controllo che tutti i numeri di v2 siano positivi...\n");
  //printf( "%s\n", vec_clone(v2, dim2) ? "true: tutti i numeri sono positivi" : "false: almeno un numero è negativo" );

  // free(copy_v2);
  // free(v3);

  return 0;
}

void inizializzaArrayRandom(double v[], int dim, double max_value) {
  srand(3);
  for (int i=0;i<dim;i++){
    v[i]=rand() % 10;
  }
}

// da qui in poi definire le funzioni chiamate nel main.
