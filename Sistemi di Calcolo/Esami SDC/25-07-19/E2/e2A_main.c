#include "e2A.h"
#include <stdlib.h>
#include <stdio.h>

int score, trials;

static void test(char* s, char c, int n, int correct) {
    trials++;
    int res = contains(s, c, n);
    int ok = res == correct;
    printf("Test %d: %s\n", trials, ok ? "OK" : "errore");
    score += ok;
}

int main() {

    test("One", 'o', 2, 0);
    test("Blackened", 'l', 1, 1);
    test("This is the longest text we ever wrote for an exercise", 'x', 6, 1);
    test("Harvester of sorrow", 'l', 4, 0);
    test("This is the longest text we ever wrote for an SC exercise!", '!', 3, 1);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
