#include <stdio.h>

void update(short* v, unsigned n);

int main() {
    short v[] = { 1, -3, -1, 7, 22, 4 };
    unsigned i, n = sizeof(v)/sizeof(short);
    update(v, n);
    for (i=0; i<n; i++) printf("%u ", v[i]);
    printf(" [corretto: 1 3 1 7 22 4]\n");
    return 0;
}
