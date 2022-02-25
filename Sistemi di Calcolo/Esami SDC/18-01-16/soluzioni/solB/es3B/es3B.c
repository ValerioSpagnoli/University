int get(char ** m, int a, int b) { return m[a][b]; }

int bazinga(char ** m, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = i; k < n; k++) sum += get(m, j, k);
            m[j][i] = sum;
        }        
    }
}
