#ifndef __ES3C__
#define __ES3C__

#include <stdlib.h>

typedef struct node_t {
    unsigned elem[2];
    struct node_t* next;
} node_t;

unsigned sum(const node_t* list);

#endif
