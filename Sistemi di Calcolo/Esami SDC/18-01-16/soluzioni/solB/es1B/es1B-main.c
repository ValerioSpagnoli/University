#include <stdio.h>

int check(short* a, char* b, unsigned n);

int main() {
    short a[] = { 1, -3,  0 };
    char  b[] = { 7, -2,  1 };
    char  c[] = { 7,  2,  1 };
    short d[] = { 6,  -3,  0 };
    char  e[] = { 7,  2,  2 };
    unsigned n = sizeof(a)/sizeof(*a);
    printf(" %d [corretto: 1]\n", check(a, b, n));
    printf(" %d [corretto: 0]\n", check(a, c, n));
    printf(" %d [corretto: 1]\n", check(d, b, n));
    printf(" %d [corretto: 1]\n", check(d, c, n));
    printf(" %d [corretto: 0]\n", check(d, e, n));
    printf(" %d [corretto: 0]\n", check(a, e, n));
    return 0;
}
