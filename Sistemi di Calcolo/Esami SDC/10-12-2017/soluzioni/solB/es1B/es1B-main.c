#include <stdio.h>

int confronta(short* a, short* b, unsigned n);

int main() {
    short a[] = { 1, -3,  0 };
    short b[] = { 7, -2,  1 };
    short c[] = { 2,  1,  3 };
    unsigned n = sizeof(a)/sizeof(*a);
    printf(" %d [corretto: 1]\n", confronta(a, b, n));
    printf(" %d [corretto: 0]\n", confronta(b, a, n));
    printf(" %d [corretto: 1]\n", confronta(a, c, n));
    printf(" %d [corretto: 0]\n", confronta(b, c, n));
    return 0;
}
