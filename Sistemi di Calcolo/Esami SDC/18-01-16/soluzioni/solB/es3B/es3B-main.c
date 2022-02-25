#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3000

void bazinga(char ** m, int n);

int main() {

    int k, j;

    char ** m = malloc(sizeof(char *) * N);
    for (k = 0; k < N; k++) {
        m[k] = malloc(sizeof(char) * N);
        for (j = 0; j < N; j++) m[k][j] = k + j * 2;
    }

    bazinga(m, N);

    int sum = 0;
    for (k = 0; k < N; k++) {
        for (j = 0; j < N; j++) {
            sum += m[k][j];
        }
    }

    printf("Output %d (atteso: %d)\n", sum, -17924496);
    return 0;
}
