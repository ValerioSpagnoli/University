#include <stdio.h>

int fetch_elem_ptr(int** buf_ptr, int* v, int i);

int main() {
    int v[] = { 2, 5, 1, 7, 4 }, res, *ptr;

    res = fetch_elem_ptr(NULL, v, 9173);
    printf("%d [corretto: -1]\n", res);

    res = fetch_elem_ptr(&ptr, v, 1);
    printf("(%d,%d) [corretto: (0,5)]\n", res, *ptr);

    res = fetch_elem_ptr(&ptr, v, 3);
    printf("(%d,%d) [corretto: (0,7)]\n", res, *ptr);

    return 0;
}
