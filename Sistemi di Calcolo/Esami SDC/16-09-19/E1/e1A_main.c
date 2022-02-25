#include "e1A.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int score, trials;

static void test(const char* s, const char* t, int corretto) {
    trials++;
    int res = is_prefix(s, t);
    int ok = res == corretto;
    printf("Test %d: %d [corretto=%d]\n", trials, res, corretto);
    score += ok;
}

int main() {

    test("a", "aaaa", 1);
    test("questa e' una", "questa e' una prova di testo", 1);
    test("prova lunga", "lunga", 0);
    test("", "", 1);
    test("a", "", 0);
    test("a", "ab", 1);
    test("", "a", 1);
    test("ab", "a", 0);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
