#ifndef UTILS_H
#define	UTILS_H

#define MIN_SIZE 4
#define MAX_SIZE 400000000
#define MAX_INT_COEFF 100
#define OK 1
#define KO 0

#define STEP 6          // max passo aritmetico di crescita/decrescita per array ordinato
#define NUM_INV .1      // percentuale inversioni in array quasi-ordinato
#define MAXMIN 10       // massimo valore per il minimo di un sorted array

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef void (*fptr)(array*);

array* createArray(int n);

/* restituisce un int random fra 0 e max */
int nextInt(int max);

/* genera array random di dim n */
array *genRandomArray(int n);

/* genera array ordinato di dim n */
array *genSortedArray(int n);

/* genera array ordinato al contrario di dim n */
array *genRevSortedArray(int n);

/* genera num inversioni random nell'array
 * un'inversione è uno swap di due elementi */
void genInversioni(array *a, int num);

/* genera un array ordinato e introduce alcune inversioni random
 * numero inversioni: NUM_INV
 * una inversione è uno swap fra due posizioni */
array *genQuasiSortedArray(int n);


/* genera un array ordinato al contrario e introduce alcune inversioni random
 * numero inversioni: NUM_INV
 * una inversione è uno swap fra due posizioni */
array *genQuasiRevSortedArray(int n);

/* scarica array su file di testo */
void array2file(array *a, char *filename);

/* carica array da file di testo */
array *file2array(char *filename);

/* scarica array su stdout */
void stampaArray(array *a);

/* clona l'array a e restituisce il clone */
array *clone(array *a);

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q);

/* clona a; ordina a con sort_alg (puntatore a funzione); ordina il clone con libreria; confronta risultati */
int testSort(array *a, void (*sort_alg)(array*));


/* clona a due volte; ordina a con sort_alg1 (puntatore a funzione);
* ordina il clone con sort_alg2; 
* ordina secondo clone con quicksort di libreria qsort
* confronta risultati */
int cmpSort(array *a, void (*sort_alg1)(array*), void (*sort_alg2)(array*));

/* lancia il sorting alg su a e stampa il tempo di CPU
 * TO DO: usare        int getrusage(int who, struct rusage *usage); */
void sortAlgCaller(void (*sort_alg)(array*), array *a);

fptr selectSortAlg(char *s);

/* Stampa info su come usare il Driver */
void printHelp();
 
/* Stampa quali algoritmi di ordinamento possono essere dati in input al Driver */
void printHelpSort();

#endif	/* UTILS_H */

