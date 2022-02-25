#include <stdio.h>
#include <string.h>

extern void goParse(char*);
extern void ll1_goParse(char*);


/*
 * uso
 * 
 * ./driver brute stringa1, stringa2, .....
 * per il parsing di un numero arbitrario di stringhe "brute-force"
 * 
 * ./driver ll1 stringa1, stringa2, .....
 * per il parsing LL(1) di un numero arbitrario di stringhe 
 * 
 */


int main (int argc, char **argv) {
	int i = 2;
    void (*launcher)(char*) = NULL;
	if(argc < 3) {
		printf("Errore invocazione; v. commento su main.\n");
		return 1;
	}
	if(strcmp(argv[1], "brute") == 0) 
		launcher = goParse;
	else if(strcmp(argv[1], "ll1") == 0) 
		launcher = ll1_goParse;
	else {
		printf("Errore invocazione; v. commento su main.\n");
		return 2;
	}
	while(i < argc) {
		printf("Lancio parsing di %s\n", argv[i]);
		(*launcher)(argv[i]);
		printf("\n\n");
		i++;
	}
	return 0;
}
