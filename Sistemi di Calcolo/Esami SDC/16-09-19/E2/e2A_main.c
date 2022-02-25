#include "e2A.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int score, trials;

static void setup() {
    int i;
    char* k[] = { "UNO", "DUE", "TRE", "QUATTRO" };
    char* v[] = { "1", "2", "3", "4" };
    for (i=0; i<sizeof(k)/sizeof(char*); ++i) setenv(k[i], v[i], 1);
}

static int check(const char** v, char** r, int n) {
    int i;
    for (i=0; i<n; ++i) {
        if ((v[i] == NULL || r[i] == NULL) && v[i] != r[i]) return 0;
        if (v[i] != NULL && r[i] != NULL && strcmp(v[i], r[i])) return 0;
    }
    return 1;
}

static void test(const char** k, const char** v, int n) {
    int i;
    char** r = NULL;
    trials++;
    multi_get_env(k, &r, n);
    int ok = check(v, r, n);
    for (i=0; i<n; ++i)
        if (r[i] != NULL) free(r[i]);
    free(r);
    printf("Test %d: %s\n", trials, ok ? "ok" : "errore");
    score += ok;
}

int main() {

    setup();

    const char* k1[] = { "UNO", "MIAPROVA23", "QUATTRO" };
    const char* v1[] = { "1", NULL, "4"};
    test(k1, v1, sizeof(k1)/sizeof(char*));

    const char* k2[] = { "MIAPROVA79" };
    const char* v2[] = { NULL};
    test(k2, v2, sizeof(k2)/sizeof(char*));

    const char* k3[] = { "TRE", "UNO" };
    const char* v3[] = { "3", "1"};
    test(k3, v3, sizeof(k3)/sizeof(char*));

    const char* k4[] = { };
    const char* v4[] = { };
    test(k4, v4, sizeof(k4)/sizeof(char*));

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
