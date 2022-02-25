int prod(short x, char y, int * res);

int check(short* a, char* b, unsigned n) {
    short* pa = a + n - 1;
    while (pa >= a) {
	int res;
	prod(*pa--, *b++, &res);
        if (res == 6) return 1;
    }
    return 0;
}
