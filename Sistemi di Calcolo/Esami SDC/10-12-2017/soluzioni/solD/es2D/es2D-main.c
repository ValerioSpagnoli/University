#include <stdio.h>

int veclen(int x, int y, int* d);

int main() {
    int x, y, d, res;

    x = 1, y = 3, d = 4;
    printf("%d [corretto: 1]\n", veclen(x, y, &d));

    x = -1, y = 3, d = 4;
    printf("%d [corretto: 0]\n", veclen(x, y, &d));

    x = 1, y = -3, d = 4;
    printf("%d [corretto: 0]\n", veclen(x, y, &d));

    x = 2, y = 3, d = 4;
    printf("%d [corretto: 1]\n", veclen(x, y, &d));

    x = 3, y = 3, d = 4;
    printf("%d [corretto: 0]\n", veclen(x, y, &d));

    return 0;
}
