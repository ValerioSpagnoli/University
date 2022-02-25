#include <stdio.h>

char* get(int i);

int main() {
    char* s0 = get(0);
    printf("%s [corretto: bazinga!]\n", s0);
    char* s1 = get(1);
    printf("%s [corretto: azinga!]\n", s1);
    char* s2 = get(2);
    printf("%s [corretto: zinga!]\n", s2);
    return 0;
}
