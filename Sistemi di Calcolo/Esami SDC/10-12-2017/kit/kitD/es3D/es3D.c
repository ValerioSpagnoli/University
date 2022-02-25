#include "es3D.h"
#include "list.h"
#include <stdlib.h>

struct charset {
    list* l;
};

charset* charset_new() {
    charset *s = malloc(sizeof(charset));
    s->l = list_new();
    return s;
}

void charset_add(charset* s, unsigned char c) {
    if (!list_contains(s->l, c)) list_add(s->l, c);
}

int charset_contains(charset* s, unsigned char c) {
    return list_contains(s->l, c);
}

void charset_delete(charset* s) {
    list_delete(s->l);
    free(s);
}
