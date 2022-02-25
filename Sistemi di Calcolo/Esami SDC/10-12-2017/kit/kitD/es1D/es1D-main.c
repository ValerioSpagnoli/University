#include <stdio.h>

void update(short* v, int n);

void print_array(short* v, int n) {
    int i;
    printf("{");
    for (i=0; i<n; ++i) printf("%d%s", v[i], i<n-1 ? ", " : "");
    printf("}");
}

void test(short* v, short* c, int n) {
    update(v, n);
    print_array(v, n);
    printf(" [corretto: ");
    print_array(c, n);
    printf("]\n");
}

int main() {
    short v1[] = {1, 2, 3, 4}, c1[] = {10, 20, 30, 40};
    int n1 = sizeof(v1)/sizeof(short);

    short v2[] = { }, c2[] = { };
    int n2 = sizeof(v2)/sizeof(short);

    test(v1, c1, n1);
    test(v2, c2, n2);

    return 0;
}
