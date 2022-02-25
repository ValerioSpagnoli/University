#include "e1A.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int score, trials;

void clear(int* map, int n) {
    memset(map, 0, n*sizeof(int));
    asm("movl $0xDEADBEEF, %%ecx\n\t"
        "movl $0xABADCAFE, %%edx"
        :
        :
        : "ecx", "edx");
}

static void test(const char* s, int correct) {
    trials++;
    int map[256];
    char res[2] = { 0 };
    char cor[2] = { 0 };
    res[0] = most_freq_char(s, map);
    cor[0] = correct;
    int ok = res[0] == cor[0];
    printf("Test %d: '%s' [corretto='%s']\n", trials, res[0] == 0 ? "\\0": res, cor[0] == 0 ? "\\0" : cor);
    score += ok;
}

int main() {

    test("aaaaaaaaa", 'a');
    test("questa e' una prova di testo", ' ');
    test("?", '?');
    test("", '\0');

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
