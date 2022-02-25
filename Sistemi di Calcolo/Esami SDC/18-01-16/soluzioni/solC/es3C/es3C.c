#include "es3C.h"

unsigned get(const node_t* node, int i) { return node->elem[i]; }

unsigned sum_i(const node_t* list, int i) {
    const node_t* p;
    unsigned sum = 0;
    for (p=list; p != NULL; p = p->next) sum += get(p, i);
    return sum;
}

unsigned sum(const node_t* list) {
    return sum_i(list, 0) + sum_i(list, 1);
}
