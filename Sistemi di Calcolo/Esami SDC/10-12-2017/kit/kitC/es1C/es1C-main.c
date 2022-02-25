#include <stdio.h>

int is_reversed(short* a, short* b, unsigned n);

int main() {

    short v1[] = {1, 2, 3, 4};
    short v2[] = {4, 3, 2, 1};
    short v3[] = {4, 3, 1, 2};

    printf("ris: %d (corretto: 0)\n", is_reversed(v1, v1, 4));
    printf("ris: %d (corretto: 1)\n", is_reversed(v1, v2, 4));
    printf("ris: %d (corretto: 0)\n", is_reversed(v1, v3, 4));
    printf("ris: %d (corretto: 0)\n", is_reversed(v2, v3, 4));

    return 0;
}
