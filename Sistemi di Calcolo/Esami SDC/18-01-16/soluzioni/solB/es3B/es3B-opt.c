int bazinga(char ** m, int n) {

    #if OPT == 1
    int i, j, k;
    for (i = 0; i < n; i++) {

        int suffix = 0;
        for (j = 0; j < n; j++) suffix += m[i][j];

        for (j = 0; j < n; j++) {
            int v = m[i][j];
            m[i][j] = suffix;
            suffix -= v;
        }        
    }

    #elif OPT == 2 // ottimizzazione naive

    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = j; k < n; k++) sum += m[i][k];
            m[i][j] = sum;
        }        
    }
    #endif
}
