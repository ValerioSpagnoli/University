#include "es3A.h"

static unsigned anno_bisestile(unsigned short anno) {
	if (anno % 4 != 0)
		return 0;
	else if (anno % 100 != 0)
		return 1;
	else if (anno % 400 != 0)
		return 0;
	else
		return 1;  
}

int quanti_bisestile(unsigned short anno) {
	unsigned count = 0;
	unsigned short k;
	for (k = 0; k <= anno; k++) {
		count += anno_bisestile(k);
	}
	return count;
}