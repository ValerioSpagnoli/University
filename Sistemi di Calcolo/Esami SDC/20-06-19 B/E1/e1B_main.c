#include "e1B.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int score, trials;

static short* make_no_duplicates(unsigned n){
    unsigned i;
    short* v = malloc(n*sizeof(short));
    assert(v != NULL);
    for (i=0; i<n; ++i) v[i] = i+1;
    return v;
}

static short* make_duplicates(unsigned n){
    unsigned i;
    assert(n > 1);
    short* v = malloc(n*sizeof(short));
    assert(v != NULL);
    for (i=0; i<n-1; ++i) v[i] = i+1;
    v[n-1] = v[n-2];
    return v;
}

static void test(short* v, unsigned n, int correct) {
    trials++;
    int res = has_duplicates(v, n);
    int ok = res == correct;
    printf("Test %d: [corretto=%d]\n", trials, ok);
    score += ok;
}

int main() {

    short* v1 = make_no_duplicates(0);
    short* v2 = make_no_duplicates(1);
    short* v3 = make_duplicates(2);
    short* v4 = make_duplicates(1000);
    short* v5 = make_no_duplicates(1000);
    short* v6 = make_duplicates(3);

    test(v1, 0, 0);
    test(v2, 1, 0);
    test(v3, 2, 1);
    test(v4, 1000, 1);
    test(v5, 1000, 0);
    test(v6, 3, 1);

    free(v1);
    free(v2);
    free(v3);
    free(v4);
    free(v5);
    free(v6);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
