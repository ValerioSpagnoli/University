#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "sort.h"
#include "utils.h"

array* createArray(int n) {
    if((n < MIN_SIZE) || (n > MAX_SIZE)) {
        fprintf(stderr, "Dimensioni richieste fuori standard. Array non generato.\n");
        exit(1);
    }
    array *a = malloc(sizeof(array*));
    assert(a != NULL);
    a->size = n;
    a->arr = malloc(a->size*sizeof(int));
    assert(a->arr != NULL);
    return a;
}

int nextInt(int max) {
/* restituisce un int random fra 0 e max */
    return (int)(.5+rand()*(double)max/RAND_MAX);
}

array *genRandomArray(int n) {
/* genera array random di dim n */
    array *a = createArray(n);
    if(a == NULL) return NULL;
    int i = 0;
    while(i < n) a->arr[i++] = nextInt(MAX_INT_COEFF*n);
    return a;
}

array *genSortedArray(int n) {
/* genera array ordinato di dim n */
    array *a = createArray(n);
    if(a == NULL) return NULL;
    if(n == 0) return a;
    a->arr[0] = nextInt(MAXMIN);
    int i = 1;
    while(i < n) { a->arr[i] = a->arr[i-1]+nextInt(STEP); i++; }
    return a;
}

array *genRevSortedArray(int n) {
/* genera array ordinato al contrario di dim n */
    array *a = createArray(n);
    if(a == NULL) return NULL;
    if(n == 0) return a;
    a->arr[n-1] = nextInt(MAXMIN);
    int i = n-2;
    while(i >= 0) { a->arr[i] = a->arr[i+1]+nextInt(STEP); i--; }
    return a;
}

void genInversioni(array *a, int num) {
/*
 * genera num inversioni random nell'array
 * un'inversione è uno swap di due elementi
 */
    int i = 0;
    while(i < num) {
        int p = nextInt(a->size-1);
        int q = nextInt(a->size-1);
        swap(&a->arr[p], &a->arr[q]);
        i++;
    }
}

array *genQuasiSortedArray(int n) {
/*
 * genera un array ordinato e introduce alcune inversioni random
 * numero inversioni: NUM_INV
 * una inversione è uno swap fra due posizioni
 */
    array *a = genSortedArray(n);
    genInversioni(a, (int)(NUM_INV*n+.5));
    return a;
}

array *genQuasiRevSortedArray(int n) {
/*
 * genera un array ordinato al contrario e introduce alcune inversioni random
 * numero inversioni: NUM_INV
 * una inversione è uno swap fra due posizioni
 */
    array *a = genRevSortedArray(n);
    genInversioni(a, (int)(NUM_INV*n+.5));
    return a;
}



void array2file(array *a, char *filename) {
/* scarica array su file di testo */
    if(a == NULL) {
        fprintf(stderr, "Nessun array da scrivere su file. File non creato.\n");
        exit(1);
    }
    if((filename == NULL)||(*filename==0)) {
        fprintf(stderr, "Nessun nome file. File non creato.\n");
        exit(1);
    }
    FILE *outfile = fopen (filename, "w");
    assert(outfile != NULL);
    int i = 0;
    fprintf(outfile, "%d\n", a->size);
    while(i < a->size) { fprintf(outfile, "%d\t%d\n", i, a->arr[i]); i++; }
    fclose(outfile);
    return;
}

array *file2array(char *filename) {
/* carica array da file di testo */
    if((filename == NULL)||(*filename==0)) {
        fprintf(stderr, "Nessun nome file. File non creato.\n");
        exit(1);
    }
    FILE *in = fopen (filename, "r");
    assert(in != NULL);
    int size;
    fscanf(in, "%d\n", &size);
    array *a = createArray(size);
    int i = 0, dummy;
    while(i < a->size) assert(fscanf(in, "%d\t%d\n", &dummy, &(a->arr[i++])) == 2);
    fclose(in);
    return a;
}

void stampaArray(array *a) {
/* scarica array su stdout */
    if(a == NULL) {
        fprintf(stderr, "Nessun array da stampare. No output.\n");
        exit(1);
    }
    int i = 0;
    fprintf(stdout, "%d\n", a->size);
    while(i < a->size) { fprintf(stdout, "%6d: %6d\n", i, a->arr[i]); i++; }
    return;
}

array *clone(array *a) {
/* clona l'array a e restituisce il clone */
    if(a == NULL) {
        fprintf(stderr, "Nessun array da clonare. Clone è NULL.\n");
        exit(1);
    }
    array *clone = malloc(sizeof(array*));
    assert(clone != NULL);
    clone->size = a->size;
    clone->arr = malloc(clone->size*sizeof(int));
    assert(clone->arr != NULL);
    int i = 0;
    while(i < a->size) { clone->arr[i] = a->arr[i]; i++; }
    return clone;
}

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order.
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order.

    return 0;
}


int testSort(array *a, void (*sort_alg)(array*)) {
/* clona a; ordina a con sort_alg (puntatore a funzione);
   ordina il clone con libreria; confronta risultati */
    array *cl = clone(a);
/*    (*sort_alg)(a);*/
    sortAlgCaller(sort_alg, a);

    clock_t begin = clock();
    qsort(cl->arr, cl->size, sizeof(int), compare_ints); /* libreria */
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stdout, "Tempo CPU (qsort di libreria): %g msec.\n", time_spent*1000);

    int i = 0;
    while(i < cl->size) { /* scegliamo clone, perché, se sbagliamo, a->size == ? */
        if(cl->arr[i] != a->arr[i]) {
            stampaArray(a);
            stampaArray(cl);
            return KO;
        }
        i++;
    }
    return OK;
}

int cmpSort(array *a, void (*sort_alg1)(array*), void (*sort_alg2)(array*)) {
    array *cl1 = clone(a);
    array *cl2 = clone(a);

    sortAlgCaller(sort_alg1, a);
    sortAlgCaller(sort_alg2, cl1);

    clock_t begin = clock();
    qsort(cl2->arr, cl2->size, sizeof(int), compare_ints); /* libreria */
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stdout, "Tempo CPU (qsort di libreria): %g msec.\n", time_spent*1000);

    int i = 0;
    while(i < cl2->size) { /* scegliamo cl2, perché, se sbagliamo, a->size == ? */
        if((cl1->arr[i] != cl2->arr[i]) || (cl2->arr[i] != a->arr[i])) {
            stampaArray(a);
            stampaArray(cl1);
            stampaArray(cl2);
            return KO;
        }
        i++;
    }
    return OK;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(array *a) {
/* ordina con bubbleSort */
    int i, j;
    for (i = 0; i < a->size-1; i++) {
        int anySwap = 0;
        for (j = 0; j < a->size-i-1; j++)
            if (a->arr[j] > a->arr[j+1]) {
                anySwap = 1;
                swap(&a->arr[j], &a->arr[j+1]);
            }
        if(!anySwap) return; /* no swap --> già ordinato */
    }
}

void purposelyWrongBubbleSort(array *a) {
/* ordina con bubbleSort - ma fa errori deliberatamente introdotti */
    int i, j;
    for (i = 0; i < a->size-2; i++) {
        int anySwap = 0;
        for (j = 0; j < a->size-i-2; j++)
            if (a->arr[j] > a->arr[j+1]) {
                anySwap = 1;
                swap(&a->arr[j], &a->arr[j+1]);
            }
        if(!anySwap) return; /* no swap --> già ordinato */
    }
}


void sortAlgCaller(void (*sort_alg)(array*), array *a) {
    if(sort_alg == NULL) {
        fprintf(stderr, "Algoritmo NULL. Nulla da eseguire.\n");
        exit(1);
    }
    clock_t begin = clock();
    (*sort_alg)(a);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stdout, "Tempo CPU: %g msec.\n", time_spent*1000);
    return;
}

void printHelp() {
    fprintf(stdout, "\nCome usare:\n./driver test <sort_alg> <tipo_input> <size_input>\n./driver run <sort_alg> <tipo_input> <size_input>\n./driver gen <tipo_input> <size_input> <file_name>\n./driver cmp <nome-alg1> <nome-alg2> <tipoInput> <size>\n./driver file <sort_alg> <file_name>\n\nVedere il testo dell'esercitazione per info più specifiche\n\n");
}

void printHelpSort(){
    fprintf(stdout, "\nAlgoritmi da implementare e testare:\nmergeSort\nheapSort\nselectionSort\ninsertionSort\nquickSort\nradixSort\nbucketSort\n\n\nVedere il testo dell'esercitazione per info più specifiche\n\n");
}

fptr selectSortAlg(char *s) {
    void (*sort_alg)(array*) = NULL;
    if(strcmp(s, "mergeSort") == 0)
        sort_alg = mergeSort;
    else if(strcmp(s, "heapSort") == 0)
        sort_alg = heapSort;
    else if(strcmp(s, "selectionSort") == 0)
        sort_alg = selectionSort;
    else if(strcmp(s, "insertionSort") == 0)
        sort_alg = insertionSort;
    else if(strcmp(s, "quickSort") == 0)
        sort_alg = quickSort;
    else if(strcmp(s, "radixSort") == 0)
        sort_alg = radixSort;
    else if(strcmp(s, "bucketSort") == 0)
        sort_alg = bucketSort;
    else if(strcmp(s, "bubbleSort") == 0)
        sort_alg = bubbleSort;
    else if(strcmp(s, "wrongBubbleSort") == 0)
        sort_alg = purposelyWrongBubbleSort;
    else{
        fprintf(stdout,"\n%s non è stato incluso nei sorgenti; puoi aggiungerlo se vuoi!\n", s);
        printHelpSort();
        exit(1);
    }
    return sort_alg;
}