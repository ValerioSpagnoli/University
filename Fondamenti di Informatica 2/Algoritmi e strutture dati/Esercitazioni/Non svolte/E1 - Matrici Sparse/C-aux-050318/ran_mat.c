#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PERCENTAGE 10

int main(int argc, char** argv){
	int m, n, p;
	if (argc != 3) {
		printf("Usage: ./main m n\n");
		exit(1);
	}
	m = strtol(argv[1], NULL,10);
	n = strtol(argv[2], NULL, 10);
	if (m <= 0 || n <= 0) {
		printf("Error: please use positive integers\n");
		exit(1);
	}
	srand(time(NULL));
	FILE* fp;
	fp = fopen("mat.dat", "w+");
	fprintf(fp, "%d %d\n", m, n);
	int i,j,r;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			p = rand() % 100;
			if (p < 10)
				r = rand() % 100;
			else
				r = 0;
			fprintf(fp, "%d ", r);
			
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return(0);
}