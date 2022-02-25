#include "e1A.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int score, trials;

short value(unsigned i, unsigned j) {
    short res;
    asm("movl $0xDEADBEEF, %%ecx\n\t"
        "movl $0xABADCAFE, %%edx\n\t"
        "movw %1, %0\n\t"
        "addw %2, %0\n\t"
        "incw %0"
        :"=r" (res)
        :"r" ((short)i), "r" ((short)j)
        :"ecx", "edx");
    return res;
}

static short** new_matrix(unsigned n) {
    unsigned i;
    short** m = malloc(n*sizeof(short*));
    assert(m != NULL);
    for (i=0; i<n; ++i)
        m[i] = calloc(n,sizeof(short));
    return m;
}

static void delete_matrix(short **m, unsigned n) {
    unsigned i;
    for (i=0; i<n; ++i)
        free(m[i]);
    free(m);
}

int check_matrix(short** m, unsigned n) {
    unsigned i,j;
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            if (m[i][j] != value(i,j)) return 0;
    return 1;
}

void test(short** m, unsigned n) {
    trials++;
    init_matrix(m, n);
    int ok = check_matrix(m, n);
    printf("Test %d: [corretto=%d]\n", trials, ok);
    score += ok;
}

int main() {

    short **m0, **m1, **m2, **m3;
    m0 = new_matrix(0);
    m1 = new_matrix(1);
    m2 = new_matrix(2);
    m3 = new_matrix(1000);

    test(m1, 0);
    test(m1, 1);
    test(m2, 2);
    test(m3, 1000);

    delete_matrix(m0, 0);
    delete_matrix(m1, 1);
    delete_matrix(m2, 2);
    delete_matrix(m3, 1000);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
