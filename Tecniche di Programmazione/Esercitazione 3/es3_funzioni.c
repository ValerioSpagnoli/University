#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* allocaInt();

void inizializzaInt(int* i1, int* i2, int matricola);

void printInt(int *i1, int *i2);

int MCD(int i1, int i2);

int mcm(int i1, int i2);

void conversioneTemperatura(int t, char c);

void* conversioneTemperatura(int* t, char c);

void printConversione(void* temperatura);

void soluzioneSistemaLineare(int i1, int i2);

void differenzaPuntatori(int *i1, int *i2);

void fibonacci(int N);



int main(int argc, char **argv) {
  int *i1 = allocaInt();
  int *i2 = allocaInt();
  printf("\n");

  /********************************************************
   *              TEST inizializzaArrayRandom             *
   ********************************************************/
  //printf("Inizializzo i due interi con numeri random...");
  //inizializzaInt(i1, i2, 18081988);
  //printf(" done.\n\n");

  /********************************************************
   *                    TEST vec_print     v1             *
   ********************************************************/
  //printf("i1, i2: ");
  //printInt(i1, i2);
  //printf("\n\n");

  /********************************************************
   *                    TEST MCD e mcm                    *
   ********************************************************/
  //printf("calcolo il MCD...\n");
  //int mcd = MCD(*i1, *i2);
  //printf("il MCD è %d\n\n", mcd);

  //printf("calcolo il mcm...\n");
  //int res = mcm(*i1, *i2);
  //printf("il mcm è %d\n\n", res);

  /********************************************************
   *                    TEST conversioneTemperatura       *
   ********************************************************/
  //printf("test conversioneTemperatura...\n");
  //conversioneTemperatura(*i1, 'C');
  //void* temperatura = conversioneTemperatura(i1, 'C');
  //printf("\n");
  //printConversione(temperatura);
  //free(temperatura);
  //printf("\n");

  /********************************************************
   *                    TEST soluzione sistema lineare    *
   ********************************************************/
  //printf("Calcolo la soluzione del sistema lineare...");
  //soluzioneSistemaLineare(*i1, *i2);
  //printf("\n");

  /********************************************************
   *                    TEST scambia puntatori            *
   ********************************************************/
  //printf("Cambio del valore puntato da i2...\n");
  //differenzaPuntatori(i1, i2);
  //printf("i2 : %d\n\n", *i2);


  /********************************************************
   *                    TEST fibonacci                    *
   ********************************************************/
  //printf("Calcolo dei primi %d numeri della serie di Fibonacci ...", *i1);
  //fibonacci(*i1);
  //printf("\n");  

  free(i1);
  free(i2);

  return 0;
}

int* allocaInt(){
  // completare
}

void inizializzaInt(int* i1, int* i2, int matricola){
  //srand(matricola); // decommentare per avere sempre gli stessi due numeri (utile per debug)
  srand(time(0)); // decommentare per avere numeri diversi ad ogni esecuzione
  *i1=rand() % 20;
  *i2=rand() % 20;

  while(*i1 ==0)
	*i1=rand() % 20;

  while(*i2 ==0)
	*i2=rand() % 20;
}

void printInt(int *i1, int *i2){
  // completare
}

int MCD(int i1, int i2){
  // completare
}

int mcm(int i1, int i2){
  // completare
}

void conversioneTemperatura(int t, char c){
  // completare
}

void* conversioneTemperatura(int* t, char c){
  // completare
}

void printConversione(void* temperatura){
  // completare
}

void soluzioneSistemaLineare(int i1, int i2){
  // completare
}

void differenzaPuntatori(int *i1, int *i2){
  // completare
}

void fibonacci(int N){
  // completare
  printf("\n");
}
