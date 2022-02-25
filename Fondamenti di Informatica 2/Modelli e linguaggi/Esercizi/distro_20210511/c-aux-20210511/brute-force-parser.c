#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ERRMSG1 "A posizione %d, trovato %c, ma atteso %c\n"
#define ERRMSGKO "Parsing fallito; processo terminato\n"
#define ERRMSGKO2 "Parsing terminato prima che l'input sia terminato; processo terminato\n"
#define OKFINALMSG "Parsing correttamente terminato; processo terminato\n"
#define ERRMSGOVF "Tentativo di leggere oltre la fine dell'input\n"
#define OKMSG "A posizione %d, trovato ed accettato %c\n"




int acceptChar(char *input, char c, int position);
// potrebbero essere utili funzioni associate alle produz.
/*
static int prod1(char * input, int position);
static int prod2(char * input, int position);
static int prod3(char * input, int position);
static int prod4(char * input, int position);
static int prod5(char * input, int position);
static int prod6(char * input, int position);*/
static int S(char * input, int position);
void goParse(char *input);


/*
 * acceptChar verifica se nella posizione corrente (position) della 
 * stringa in input (input)
 * vi sia il carattere atteso (c); se sì, stampa messaggio di conferma
 * e termina restituendo la posizione del prossimo simbolo da
 * analizzare; se no, stampa diagnostica e ritorna la posizione 
 * inizialmente
 * ricevuta in input, ma cambiata di segno per segnalare errore
 */
int acceptChar(char *input, char c, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}




// potrebbero essere utili funzioni associate alle produz.

/*
static int prod1(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int prod2(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int prod3(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int prod4(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int prod5(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int prod6(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}
*/


/*
 * tentare tutte le produzioni in ordine decrescente di lunghezza
 * prima la prod. più lunga, poi la seconda ecc.
 * (altrimenti se un prefisso dell'input appartiene al linguaggio
 * verrà derivato quello e non tutto l'input)
 * 
 * in caso di produzioni con la stessa lunghezza il problema 
 * potrebbe permanere
 * 
 * nel caso generale: applicare produzioni in sequenze ordinate
 * alfabeticamente (qui non considerato)
 */
static int S(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

/*
 * avvia il parsing chiamando la produz. sull'assioma e quindi prende
 * atto dell'esito del parsing, stampando a schermo info finali
 */
void goParse(char *input) {
    // TO IMPLEMENT
    return; // solo ai fini della compilazione
}
