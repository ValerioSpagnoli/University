unsigned char eq(short * x, short * y);

int is_reversed(short* a, short* b, unsigned n) {
    int k;
    short * pa = a;
    short * pb = b + n - 1;
    for (k = 0; k < n; k++)
        if (!eq(pa + k, pb - k)) return 0;
    return 1;
}