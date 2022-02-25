#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char* copia(char s[], int N);

void seleziona_alcuni_char(char s[], int idxs[], int dim);

char* copia_con_eliminazione(char s1[], char s2[]);

char* inverti(char s[]);

void print_vocali(char s[]);

char* sostituisci_carattere(char s[], char c1, char c2);

bool minuscole_check(char s[]);

char* sostituisci_maiuscole(char s[]);

int main(void){

	int N = 7;
	int n = 5;
	char s[11] = "puntatore\0";
	 
	/********************************************************
    *              TEST copia                               *
    ********************************************************/
    //printf("Copio i primi %d valori della stringa s...\n", N);
	//char* char_copiato = copia(s, N);
	//printf("%s", char_copiato);
    //printf("\n\n");

	/********************************************************
    *              TEST seleziona_alcuni_char               *
    ********************************************************/
    //printf("Stampo i valori con indici idxs della stringa s...\n");
	//int dims = 4;
	//int idxs[dims] = {1, 3, 5, 11};
	//seleziona_alcuni_char(s, idxs, dims);
    //printf("\n");
	
    /********************************************************
    *              TEST copia_con_eliminazione              *
    ********************************************************/
	//printf("Elimino dalla stringa s tutti i char non presenti in s2...\n");
	//char s2[6] = "ptar\0";
	//char* char_eliminato = copia_con_eliminazione(s, s2);
	//printf("%s", char_eliminato);
	//printf("\n\n");

	/********************************************************
    *              TEST inverti                             *
    ********************************************************/
	//printf("Inverto la stringa s...\n");
	//char* char_invertito = inverti(s);
	//printf("%s", char_invertito);
	//printf("\n\n");

	/********************************************************
    *              TEST print_vocali                        *
    ********************************************************/
    //printf("Stampo le vocali contenute in s...\n");
	//print_vocali(s);
	//printf("\n\n");

	/********************************************************
    *              TEST sostituisci_carattere               *
    ********************************************************/
    //char c1 = 't';
	//char c2 = 'm';
    //printf("stostituisco in s il carattere %c con il carattere %c le vocali contenute in s...\n", c1, c2);
	//char* char_sostituito = sostituisci_carattere(s, c1, c2);
	//printf("%s", char_sostituito);
	//printf("\n\n");

	/********************************************************
    *              TEST sostituisci_carattere               *
    ********************************************************/
    //printf("controllo che tutti i caratteri siano minuscoli...\n");
	//printf( "%s\n", minuscole_check(s) ? "true: tutti i caratteri sono minuscoli" : "false: almeno un carattere è maiuscolo" );
	//printf("\n\n");

	/********************************************************
    *              TEST sostituisci_maiuscole               *
    ********************************************************/
	//printf("Sostituisco le lettere maiuscole nella stringa s3...\n");
	//char s3[39] = "cHE bEllA e rIlAssANTe lEZIonE dI TDp\0";
	//char *char_maiuscolo = sostituisci_maiuscole(s3);
	//printf("%s", char_maiuscolo);
	//printf("\n");

	//free(char_copiato);
	//free(char_eliminato);
	//free(char_invertito);
	//free(char_sostituito);	
	//free(char_maiuscolo);
}

// da qui in poi definire le funzioni chiamate nel main.