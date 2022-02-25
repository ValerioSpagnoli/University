void pass(int* in, int n, int stride) {
    int i;
    for (i=0; i+stride<n; i+=stride)
        if (in[i] > in[i+stride]) {
            int temp = in[i];
            in[i] = in[i+stride];
            in[i+stride] = temp;
        }
}

#include <stdlib.h>

int main() {

    int* in = calloc(1024, sizeof(int));

    pass(in, 1024, 8);

    free(in);
    return 0;
}
