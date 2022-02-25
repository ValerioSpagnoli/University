#include <stdio.h>

int search_max(int * x, unsigned xn, int * sorted_v, unsigned vn);

#define N 20000000

int main() {

    int x[] = {7, 4, 2, 1, 12, 7, 4, 2, 1, 12, 7, 4, 2, 1, 12, 7, 4, 2, 1, 12};
    int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

    int k;
    while(k++ < N) {
        int res = search_max(x, sizeof(x) / sizeof(int), v, sizeof(v) / sizeof(int));    
        if (res != 9) {
            printf("ris %d (corretto: 9)\n", res); 
            return 1;
        }
    }

    printf("Output corretto.\n");
    return 0;
}