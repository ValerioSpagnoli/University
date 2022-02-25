#include <stdio.h>
#include "es3A.h"

#define N 500000

int main() {

	int k;
	for (k = 0; k < N; k++) {
		unsigned year = 0;
		if (quanti_bisestile(year) != 1) return (printf("Errore: %ul\n", year),1);
		year = 1000;
		if (quanti_bisestile(year) != 243) return (printf("Errore: %ul\n", year),1);
		year = 2000;
		if (quanti_bisestile(year) != 486) return (printf("Errore: %ul\n", year),1);
		year = 3000;
		if (quanti_bisestile(year) != 728) return (printf("Errore: %ul\n", year),1);
	}

    printf("Output corretto.\n");
	return 0;
}
