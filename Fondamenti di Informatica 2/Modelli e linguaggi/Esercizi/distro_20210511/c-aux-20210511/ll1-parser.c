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




int ll1_acceptChar(char *input, char c, int position);
// potrebbero essere utili funz associate alle produz
/*
static int ll1_prod1(char * input, int position);
static int ll1_prod2(char * input, int position);
static int ll1_prod3(char * input, int position);
*/
static int ll1_S(char * input, int position);
static int ll1_T(char * input, int position);
void ll1_goParse(char *input);


/*
 * acceptChar verifica se nella posizione corrente (position) della 
 * stringa in input (input)
 * vi sia il carattere atteso (c); se sì, stampa messaggio di conferma
 * e termina restituendo la posizione del prossimo simbolo da
 * analizzare; se no, stampa diagnostica e ritorna la posizione 
 * inizialmente
 * ricevuta in input, ma cambiata di segno per segnalare errore
 */
int ll1_acceptChar(char *input, char c, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

// potrebbero essere utili funzioni associate alle produz.
/*
static int ll1_prod1(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int ll1_prod2(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

static int ll1_prod3(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}
*/

/*
 * non-terminale S
 * 
 * usare la produzione selezionata da SELECT e dal simbolo corrente
 * input[position]
 */
static int ll1_S(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

/*
 * non-terminale T
 * 
 * usare la produzione selezionata da SELECT e dal simbolo corrente
 * input[position]
 */
static int ll1_T(char * input, int position) {
    // TO IMPLEMENT
    return 0; // solo ai fini della compilazione
}

/*
 * avvia il parsing chiamando la produz. sull'assioma e quindi prende
 * atto dell'esito del parsing, stampando a schermo info finali
 */
void ll1_goParse(char *input) {
    // TO IMPLEMENT
    return; // solo ai fini della compilazione
}
