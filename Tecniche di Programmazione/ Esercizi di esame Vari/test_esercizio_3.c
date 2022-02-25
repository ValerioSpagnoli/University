#include "esercizio_3.h"
#include <stdio.h>
#include <stdlib.h>

// g++ -o e3 test_esercizio_3.c esercizio_3.c


TipoNodoAlbero * allocNode() {
  TipoNodoAlbero *t = (TipoNodoAlbero *)malloc(sizeof(TipoNodoAlbero));
  t->info = rand()%10; 
  t->sinistro = NULL;  t->destro = NULL; 
  return t;
}


TipoNodoAlbero *generate() {
    TipoNodoAlbero *t = allocNode();
    if (rand()%10>5) { 
        t->sinistro = generate();
        t->destro = generate(); 
    }
    return t;
}

void print(TipoNodoAlbero *a) {    
    if (a==NULL) {
        printf("()");
    }
    else {
        printf("( %d ",a->info);
        print(a->sinistro);
        printf(" ");
        print(a->destro);
        printf(" )");
    }
}


void freeAlb(TipoNodoAlbero *a) {
    if (a!=NULL) {
        freeAlb(a->sinistro);
        freeAlb(a->destro);
        free(a);
    }
}

int main(int argc, char** argv) {

  srand(10);
  
  // configuration
  const int number_of_tests      = 10;
  int number_of_successful_tests = 0;

  // binary trees
  TipoNodoAlbero* albero;

  // test loop
  for (int i = 0; i < number_of_tests; ++i) {
  
    printf("Test number %d out of %d\n", i + 1, number_of_tests);
    fflush(stdout);
    
    // generate a random input tree
    albero = generate();

    // print the generated tree
    printf("\nInput:\n");
    print(albero);
    fflush(stdout);

    // compute student's result
    scambiaPuntatori(albero);
    printf("\nOutput:\n");
    print(albero);
    fflush(stdout);

    // free memory
    freeAlb(albero);

    printf("\n*************************************************\n\n");
    fflush(stdout);
  }

  return 0;
}

