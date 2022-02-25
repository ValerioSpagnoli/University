#include "list.h"
#include <stdlib.h>

typedef struct node node;

struct node {
    int   elem;
    node* next;
};

struct list {
    node* head;
};

list* list_new() {
    return calloc(1, sizeof(list));
}

void list_add(list* s, int x) {
    node* p = malloc(sizeof(node));
    p->elem = x;
    p->next = s->head;
    s->head = p;
}

int list_contains(list* s, int x) {
    node* p;
    for (p = s->head; p != NULL; p = p->next)
        if (p->elem == x) return 1;
    return 0;
}

void list_delete(list* s) {
    node* p = s->head;
    while (p != NULL) {
        node* dead = p;
        p = p->next;
        free(dead);
    }
    free(s);
}
