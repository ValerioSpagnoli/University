#include <math.h>

int radice(int a);

int sumRangeSqrt(int a, int b) {

    int i, sum = 0;
    for (i = a; i < b; i++) {
        int c = i % 2;
        sum += a + b + radice(a + c);
    }

    return sum;
}