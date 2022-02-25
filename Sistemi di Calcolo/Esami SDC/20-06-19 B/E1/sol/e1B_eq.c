#include "../e1B.h"

int has_duplicates(short* v, unsigned n) {
    unsigned i,j;
    int res = 1;
    i=0;
L1: if (i>=n)
        goto E1;
    j=i+1;
L2: if (j>=n)
        goto E2;
    short tmp = v[i];
    if (tmp == v[j])
        goto F;
    j++;
    goto L2;
E2: i++;
    goto L1;
E1: res = 0;
F:  return res;
}
