static int contain(int * x, unsigned xn, int v) {
    int k = 0;
    while (k < xn) if (x[k++] == v) return 1;
    return 0;
}

// Dato l'array x e l'array ordinato sorted_v, ritorna
// il piu' grande elemento di sorted_v che è anche
// presente in x, o -1 se i due array non hanno elementi
// in comune
int search_max(int * x, unsigned xn, int * sorted_v, unsigned vn) {
    int k;
    for (k = vn - 1; k >= 0; k--) {
        if (contain(x, xn, sorted_v[k]))
            return k;
    }
    return -1; 
}
