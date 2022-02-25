#include "../e1A.h"

int most_freq_char(const char* s, int* map) {
    int i;
    int max = 0;
    clear(map, 256);
L1:;int tmp = *s;
    if (tmp == 0)
        goto E1;
    map[tmp]++;
    s++;
    goto L1;
E1: i=0;
L2: if (i>=256)
        goto E2;
    tmp = map[i];
    if (tmp > map[max])
        max = i;
    i++;
    goto L2;
E2: return max;
}
