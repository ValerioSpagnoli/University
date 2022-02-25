#include <stdio.h>
#include "es3A.h"

int main() {

	// generazione lookup table
	unsigned year = 0;
	printf("unsigned table[] = {\n");
	while (year <= MAX_YEAR) {
		printf("    %d,\n", quanti_bisestile(year));
		year += 1;
	}
	printf("};\n");

	return 0;
}
