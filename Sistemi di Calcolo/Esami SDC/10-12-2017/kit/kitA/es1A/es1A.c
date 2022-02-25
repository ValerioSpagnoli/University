void assoluto(short * v);

void update(short* v, unsigned n) {
    int i;
    for (i=0; i<n; i++)
        if (v[i] < 0) assoluto(&v[i]);
}
