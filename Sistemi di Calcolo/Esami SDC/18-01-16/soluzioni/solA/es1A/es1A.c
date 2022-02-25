#include <stdio.h>
#include <stdlib.h>
#include "mtrace.h"

// ------------------------------------------------------------

int** alloc_diagonal_matrix(int n) {
    int **m, i;
    m = malloc(n*sizeof(int*));
    for (i=0; i<n; ++i) m[i] = calloc(i+1, sizeof(int));
    return m;
}

void make_square(int** m, int n) {
    int i, j;
    for (i=0; i<n-1; ++i) {
        int* temp = calloc(n, sizeof(int));
        my_free(m[i]);
        m[i] = temp;
    }
}

int main() {
    int** m = alloc_diagonal_matrix(3);
    make_square(m, 3);
    return 0;
}
