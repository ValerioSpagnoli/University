#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "sort.h"
#include "utils.h"

int main (int argc, char *argv[]) {
    if((argc < 4) || (argc > 6)) {
        printHelp();
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));   /* inizializzazione per rand - chiamare una volta sola */
    void (*sort_alg)(array*);
    array *a;

    // CMP
    if (strcmp(argv[1], "cmp") == 0) {
        if(argc != 6) {
            printHelp();
            return EXIT_FAILURE;
        }
		void (*sort_alg1)(array*);
		void (*sort_alg2)(array*);
        sort_alg1 = selectSortAlg(argv[2]);
        sort_alg2 = selectSortAlg(argv[3]);
        int size = atoi(argv[5]);
        if(strcmp(argv[4], "C") == 0)
            a = genSortedArray(size);
        else if(strcmp(argv[4], "D") == 0)
            a = genRevSortedArray(size);
        else if(strcmp(argv[4], "c") == 0)
            a = genQuasiSortedArray(size);
        else if(strcmp(argv[4], "d") == 0)
            a = genQuasiRevSortedArray(size);
        else if(strcmp(argv[4], "R") == 0)
            a = genRandomArray(size);
        else {
            printHelp();
            return EXIT_FAILURE;
        }
        int res = cmpSort(a, sort_alg1, sort_alg2);
        if(res == OK) fprintf(stdout, "Esito test algoritmo OK.\n");
        else fprintf(stdout, "Esito test algoritmo ERRORE (sorry).\n");
        return EXIT_SUCCESS;
    }
    // TEST
    else if (strcmp(argv[1], "test") == 0) {
        if(argc != 5) {
            printHelp();
            return EXIT_FAILURE;
        }
        sort_alg = selectSortAlg(argv[2]);
        int size = atoi(argv[4]);
        if(strcmp(argv[3], "C") == 0)
            a = genSortedArray(size);
        else if(strcmp(argv[3], "D") == 0)
            a = genRevSortedArray(size);
        else if(strcmp(argv[3], "c") == 0)
            a = genQuasiSortedArray(size);
        else if(strcmp(argv[3], "d") == 0)
            a = genQuasiRevSortedArray(size);
        else if(strcmp(argv[3], "R") == 0)
            a = genRandomArray(size);
        else {
            printHelp();
            return EXIT_FAILURE;
        }
        int res = testSort(a, sort_alg);
        if(res == OK) fprintf(stdout, "Esito test algoritmo OK.\n");
        else fprintf(stdout, "Esito test algoritmo ERRORE (sorry).\n");
        return EXIT_SUCCESS;
    } 
    // RUN
    else if (strcmp(argv[1], "run") == 0) {
        if(argc != 5) {
            printHelp();
            return EXIT_FAILURE;
        }
        sort_alg = selectSortAlg(argv[2]);
        int size = atoi(argv[4]);
        if(strcmp(argv[3], "C") == 0)
            a = genSortedArray(size);
        else if(strcmp(argv[3], "D") == 0)
            a = genRevSortedArray(size);
        else if(strcmp(argv[3], "c") == 0)
            a = genQuasiSortedArray(size);
        else if(strcmp(argv[3], "d") == 0)
            a = genQuasiRevSortedArray(size);
        else if(strcmp(argv[3], "R") == 0)
            a = genRandomArray(size);
        else {
            printHelp();
            return EXIT_FAILURE;
        }
        sortAlgCaller(sort_alg, a);
        return EXIT_SUCCESS;
    }
    // FILE
    else if (strcmp(argv[1], "file") == 0) {
        if(argc != 4) {
            printHelp();
            return EXIT_FAILURE;
        }
        sort_alg = selectSortAlg(argv[2]);
        a = file2array(argv[3]);
        sortAlgCaller(sort_alg, a);
        return EXIT_SUCCESS;
    } 
    // GEN
    else if (strcmp(argv[1], "gen") == 0) {
        if(argc != 5) {
            printHelp();
            return EXIT_FAILURE;
        }
        int size = atoi(argv[3]);
        if(strcmp(argv[2], "C") == 0)
            a = genSortedArray(size);
        else if(strcmp(argv[2], "D") == 0)
            a = genRevSortedArray(size);
        else if(strcmp(argv[2], "c") == 0)
            a = genQuasiSortedArray(size);
        else if(strcmp(argv[2], "d") == 0)
            a = genQuasiRevSortedArray(size);
        else if(strcmp(argv[2], "R") == 0)
            a = genRandomArray(size);
        else {
            printHelp();
            return EXIT_FAILURE;
        }
        array2file(a, argv[4]);
        fprintf(stdout, "array creato e scaricato su file %s \n", argv[4]);
        return EXIT_SUCCESS;
    } 
    else{
        fprintf(stdout,"\nComando non implementato\n\n");
        printHelp();
    }

    return EXIT_SUCCESS;
}