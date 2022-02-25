#include <stdio.h>
#include <stdlib.h>
#include "es3C.h"

#define N 1000000
#define M 400

node_t* push(node_t* list, unsigned A, unsigned B) {
    node_t* node = malloc(sizeof(node_t));
    node->elem[0] = A;
    node->elem[1] = B;
    node->next = list;
    return node;
}

void delete(node_t* list) {
    while (list != NULL) {
        node_t* dead = list;
        list = list->next;
        free(dead);
    }
}

int main() {

    unsigned i, s;
    node_t* list = NULL;

    for (i=0; i<N; ++i)
        list = push(list, N-i, i);

    for (i=0; i<M; ++i)
        s = sum(list);

    delete(list);

    printf("Output %u (atteso: %u) %s\n", s, 3567587328U, s == 3567587328U ? "-- OK" : "-- ERRORE");

    return 0;
}
