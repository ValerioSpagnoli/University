#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "max_gap.h"
#include "labirinto.h"

void inverti_lista_test() {

    linked_list * l = linked_list_new();
    linked_list_add(l, 10);
    linked_list_add(l, 20);
    linked_list_add(l, 5);
    linked_list_add(l, 6);
    linked_list_add(l, 8);
    printf("Lista originale: ");
    print_linked_list(l);
    
    inverti_lista(l);
    printf("List Invertita: ");
    print_linked_list(l);
		
    linked_list_delete(l);
}

void max_gap_test() {

	int array[] = {0, 5, 8, 10, 15, 27, 32, 43, 45};

	int size = (sizeof(array) / sizeof(int));
	int i;
	printf("[");
	for (i = 0; i < size; i++) {
		printf("%s%d", i == 0 ? " " : ", ", array[i]);
	}
	printf(" ]\n");

	printf("massimo gap: %d\n", maxGap(array, 0, size));
}

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Rihiesto argomento: {inverti, maxGap, labirinto}\n");
		return EXIT_FAILURE;
	}

    if (strcmp(argv[1], "inverti") == 0)
        inverti_lista_test();

    else if (strcmp(argv[1], "maxGap") == 0) {
        max_gap_test();

    } else if (strcmp(argv[1], "labirinto") == 0) {

    	int max_size = 1024;
        char buffer[max_size];
        int n;
        printf ("Inserisci n (dimensione del labirinto): ");
        fscanf(stdin, "%d", &n);
        
        if (n > max_size) {
        	printf("Dimensione massima: %d", max_size);
        	return EXIT_FAILURE;
        }

        labirinto *lab = labirinto_new(n);
        
        printf("\nInserisci %d righe di %d caratteri, '.'=vuoto '#'=pieno : \n", n, n);
        int i;
        fgets(buffer, max_size, stdin); // clean stdin
        for (i = 0; i < n; i++) {

            fgets(buffer, max_size, stdin);
            printf("Parsing line: %s\n", buffer);
            int j;
            for (j = 0; j < n; j++) {
                if (buffer[j] == '#') {
                    labirinto_setpiena(lab, i, j);
                } else if (buffer[j] != '.') {
                	printf("Invalid input: %c\n", buffer[j]);
                	return EXIT_FAILURE;
                }
            }
        }


        int found = labirinto_risolvibile(lab);
        printf("Percorso%s trovato.\n", (found == LABIRINTO_TRUE ? "" : " NON"));
        labirinto_tostring(lab, buffer, max_size);
        printf("%s", buffer);
        labirinto_delete(lab);

    } else {
    	printf("Rihiesto argomento: {inverti, maxGap, labirinto}\n");
    	return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

