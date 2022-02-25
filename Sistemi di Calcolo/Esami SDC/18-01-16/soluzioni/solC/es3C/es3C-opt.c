#include "es3C.h"

unsigned get(const node_t* node, int i) { return node->elem[i]; }

unsigned sum(const node_t* list) {
    const node_t* p;
    unsigned sum = 0;
    for (p=list; p != NULL; p = p->next)
        sum += get(p, 0) + get(p, 1);
    return sum;
}
