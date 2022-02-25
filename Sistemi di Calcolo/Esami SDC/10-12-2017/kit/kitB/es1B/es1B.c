int minore(short x, short y);

int confronta(short* a, short* b, unsigned n) {
    short* end = a + n;
    while (a < end)
        if (!minore(*a++, *b++)) return 0;
    return 1;
}
