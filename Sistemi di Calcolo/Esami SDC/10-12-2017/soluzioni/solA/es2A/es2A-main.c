#include <stdio.h>

int get(int* x);

int main() {
    int v1[] = {   0, 100 };
    int v2[] = {  20, 100 };
    int v3[] = { -10, 100 };
    int v4[] = {   0,   5 };
    int v5[] = {  10,  10 };
    printf("%d [corretto: 1]\n", get(v1));
    printf("%d [corretto: 0]\n", get(v2));
    printf("%d [corretto: 0]\n", get(v3));
    printf("%d [corretto: 0]\n", get(v4));
    printf("%d [corretto: 1]\n", get(v5));
    return 0;
}

