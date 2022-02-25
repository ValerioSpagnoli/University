#include "e2A.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int score, trials;

static int check(int* v, int n, int (*f)(int i)) {
    int i, j;
    for (i=0; i<n; ++i) {
        for (j=0; j<n; ++j)
            if (v[j] == f(i)) break;
        if (j>=n) return 0;
    }
    return 1;
}

static void test(int n, int (*f)(int i)) {
    trials++;
    int* v = malloc(n*sizeof(int));
    assert(v != NULL);
    run(v, n, f);
    int ok = check(v, n, f);
    free(v);
    printf("Test %d: %s\n", trials, ok ? "OK" : "errore");
    score += ok;
}

int f1(int i) {
    return i;
}

int f2(int i) {
    return 2*(i+1);
}

int main() {

    test(1, f1);
    test(5, f1);
    test(10, f2);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
