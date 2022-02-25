#include <math.h>

int radice(int a);

int sumRangeSqrt(int a, int b) {

    int i, sum = 0;
    int r0 = radice(a + 0);
    int r1 = radice(a + 1);
    for (i = a; i < b; i++) {
        int c = 0;
        if (i % 2) c = r0;
        else c = r1;
        sum += a + b + c;
    }

    return sum;
}
