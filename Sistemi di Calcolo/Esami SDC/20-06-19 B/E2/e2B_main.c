#include "e2B.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int score, trials;

static void _check_error(int res, char* msg) {
    if (res != -1) return;
    perror(msg);
    exit(EXIT_FAILURE);
}

static int check(int n, void (*f)(int i, char name[64], char buf[256])) {
    int i;
    for (i=0; i<n; ++i) {
        int fd = -1;
        char name[64];
        char buf_ok[256];
        char buf[256];
        f(i, name, buf_ok);
        fd = open(name, O_RDONLY);
        if (fd == -1) goto err;
        int size = read(fd, buf, 256);
        if (size != 256 || strcmp(buf, buf_ok) != 0) goto err;
        close(fd);
        _check_error(fd, "close in main");
        continue;
    err:
        if (fd != -1) close(fd);
        return 0;
    }
    return 1;
}

static void test(int n, void (*f)(int i, char name[64], char buf[256])) {
    trials++;
    make_files(n, f);
    int ok = check(n, f);
    printf("Test %d: %s\n", trials, ok ? "OK" : "errore");
    score += ok;
}

void f1(int i, char name[64], char buf[256]) {
    memset(buf, ' ', 256);
    sprintf(name, "f1-%d.txt", i);
    sprintf(buf, "Hallowed Be Thy Name [%d]\n", i);
}

void f2(int i, char name[64], char buf[256]) {
    memset(buf, ' ', 256);
    sprintf(name, "f2-%d.txt", i);
    sprintf(buf, "Harvester of Sorrow [%d]\n", i);
}

void f3(int i, char name[64], char buf[256]) {
    memset(buf, ' ', 256);
    sprintf(name, "f3-%d.txt", i);
    sprintf(buf, "Autumn Lords [%d]\n", i);
}

int main() {

    test(1, f1);
    test(2, f2);
    test(3, f3);

    printf("Risultato: %d/%d\n", score, trials);

    return EXIT_SUCCESS;
}
