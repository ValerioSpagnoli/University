#include <stdio.h>

int check(int* a, char* b, unsigned n);

int main() {
    int   a[] = { 3, 72,  34 };
    char  b1[] = { 1, 2,  3 };
    char  b2[] = { 4, 2,  3 };
    char  b3[] = { 1, -56,  3 };
    char  b4[] = { 1, 2,  50 };
    unsigned n = sizeof(a)/sizeof(*a);
    printf("%d [corretto: 0]\n", check(a, b1, n));
    printf("%d [corretto: 1]\n", check(a, b2, n));
    printf("%d [corretto: 1]\n", check(a, b3, n));
    printf("%d [corretto: 1]\n", check(a, b4, n));
    return 0;
}
