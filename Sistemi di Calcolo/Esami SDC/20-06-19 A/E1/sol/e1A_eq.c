#include "../e1A.h"

void init_matrix(short** m, unsigned n) {
    unsigned i,j;
    i=0;
L1: if (i>=n) goto E1;
    j=0;
L2: if (j>=n) goto E2;
    short tmp = value(i,j);
    short* tmp2 = m[i];
    tmp2[j] = tmp;
    j++;
    goto L2;
E2: i++;
    goto L1;
E1:;
}
