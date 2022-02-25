void fetch(short u, short* p);

void update(short* v, int n) {
    int i;
    short x;
    for (i=0; i<n; ++i) {
        fetch(v[i], &x);
        v[i] = x;
    }
}
