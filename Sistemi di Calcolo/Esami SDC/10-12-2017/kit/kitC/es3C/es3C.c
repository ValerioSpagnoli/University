int contain(int * x, unsigned xn, int v) {
    int k = 0;
    while (k < xn) if (x[k++] == v) return 1;
    return 0;
}

// Dato l'array x e l'array ordinato sorted_v, ritorna
// l'indice del piu' grande elemento di sorted_v che è anche
// presente in x, o -1 se i due array non hanno elementi
// in comune
int search_max(int * x, unsigned xn, int * sorted_v, unsigned vn) {
    int k;
    int k_max = -1;
    for (k = 0; k < vn; k++) {
        if (contain(x, xn, sorted_v[k]))
            k_max = k;
    }
    return k_max; 
}
