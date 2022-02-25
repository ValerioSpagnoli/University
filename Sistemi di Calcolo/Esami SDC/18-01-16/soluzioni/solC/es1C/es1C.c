int diff(int x, char y);

int check(int* a, char* b, unsigned n) {
    int* pa = a + n - 1;
    while (pa >= a) {
        int res = diff(*pa--, *b++);
        if (res & 8 || res & 128 || res & 2048) return 1;
    }
    return 0;
}
