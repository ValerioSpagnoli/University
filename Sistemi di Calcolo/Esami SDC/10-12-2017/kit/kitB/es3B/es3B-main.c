#include <math.h>
#include <stdio.h>

#define N 100000

int sumRangeSqrt(int a, int b);

int radice(int a) {
    return sqrt(a);
}

int main() {

    int i;
    for (i = 0; i < N; i++) {
        int r = sumRangeSqrt(21, 4001);
        if (r!= 16023480) {
            printf("*** Errore: %d [corretto: 16023480]\n", r);
            return 1;
        }
    }

    printf("Output corretto.\n");
    return 0;
}
