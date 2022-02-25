#include "e1B.h"

int has_duplicates(short* v, unsigned n) {
    unsigned i,j;
    for (i=0; i<n; ++i)
        for (j=i+1; j<n; ++j)
            if (v[i] == v[j]) return 1;
    return 0;
}
