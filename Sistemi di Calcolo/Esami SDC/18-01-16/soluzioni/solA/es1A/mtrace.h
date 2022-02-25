#ifndef __MY_MTRACE__
#define __MY_MTRACE__

#include <stdlib.h>
#include <stdio.h>

static void* my_malloc(int n) {
    void* p = malloc(n);
    fprintf(stderr, "malloc(%d) == %p\n", n, p);
    return p;
}

static void* my_calloc(int n, int m) {
    void* p = calloc(n,m);
    fprintf(stderr, "calloc(%d) == %p\n", n*m, p);
    return p;
}

static void* my_free(void* p) {
    fprintf(stderr, "free(%p)\n", p);
    free(p);
}

#define malloc my_malloc
#define calloc my_calloc
#define free my_free

#endif
