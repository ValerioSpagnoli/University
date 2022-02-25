#include "es3D.h"
#include <stdlib.h>

struct charset {
    int map[256];
};

charset* charset_new() {
    return calloc(1, sizeof(charset));
}

void charset_add(charset* s, unsigned char c) {
    s->map[c] = 1;
}

int charset_contains(charset* s, unsigned char c) {
    return s->map[c];
}

void charset_delete(charset* s) {
    free(s);
}
