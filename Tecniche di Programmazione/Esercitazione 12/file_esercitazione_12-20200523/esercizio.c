#include "esercizio.h"


//////////////////////////////////////////////////////
//////////// Alberi
//////////////////////////////////////////////////////

TipoAlbero albBinVuoto () {
	return 0;
}

TipoAlbero creaAlbBin( TipoInfoAlbero infoRadice, TipoAlbero sx, TipoAlbero dx ) {
	TipoAlbero a = ( TipoAlbero ) malloc ( sizeof (TipoNodoAlbero) ) ;
	a->info = infoRadice ;
	a->sinistro = sx ;
	a->destro = dx ;
	return a ;
}



bool estVuoto ( TipoAlbero a ) {
	return ( a == NULL );
}

TipoInfoAlbero radice ( TipoAlbero a ) {
	if ( a == NULL ) {
		printf ( " ERRORE accesso albero vuoto \n " );
		return ERRORE_InfoAlbero;
	}
	else
		return a->info;
}

TipoAlbero sinistro ( TipoAlbero a ) {
	if ( a == NULL ) {
		printf ( " ERRORE accesso albero vuoto \n " );
	return NULL;
	}
	else
		return a->sinistro ;
}

TipoAlbero destro ( TipoAlbero a ) {
	if ( a == NULL ) {
		printf ( " ERRORE accesso albero vuoto \n " );
		return NULL;
	}
	else
		return a->destro;
}

// Funzioni esterne

// Dealloca albero
void dealloca(TipoAlbero *a) {
    if (*a!=NULL) {
        dealloca(&((*a)->sinistro));
        dealloca(&((*a)->destro));
        free(*a);
        *a = NULL;  // side-effect su a
    }
}



// Stampa
void stampaParentetica(TipoAlbero a) {
    if (estVuoto(a)) {
        printf("()");
    }
    else {
        printf("( %d ", radice(a));
        stampaParentetica(sinistro(a));
        printf(" ");
        stampaParentetica(destro(a));
        printf(" )");
    }
}

void stampaAlbero(const char* astr, TipoAlbero a) {
    printf("Albero %s: ",astr);
    stampaParentetica(a);
    printf("\n");
}



void disegnaAlbero_r(TipoAlbero a, char *s) {
  if (estVuoto(a))
    return;
  else {
    printf("    %s %d\n", s, radice(a));
    int l = strlen(s);
    s[l+1]='\0';
    s[l]='s';
    disegnaAlbero_r(sinistro(a), s);
    s[l]='d';    
    disegnaAlbero_r(destro(a), s);
    s[l]='\0';
  }
}

void disegnaAlbero(const char* astr, TipoAlbero a) {
    char s[20]; // max profondità
    s[0]='\0';
    printf("Albero %s:\n",astr);
    disegnaAlbero_r(a,s);
    printf("\n");
}


// Lettura da file

void leggiParentesi(FILE *file_albero) {
  char c = ' ';
  while (c!='(' && c!=')')
    c = fgetc(file_albero);
}

TipoAlbero leggiSottoAlbero(FILE *file_albero) {
  char c;
  TipoInfoAlbero i;
  TipoAlbero r;

  leggiParentesi(file_albero);   /* legge la parentesi aperta */
  c = fgetc(file_albero);   /* carattere successivo */
  if (c == ')')
    return albBinVuoto();   /* se legge () allora l'albero e' vuoto */
  else {
    fscanf(file_albero, "%d", &i);   /* altrimenti legge la radice */

    /* legge i sottoalberi */
    TipoAlbero s = leggiSottoAlbero(file_albero);
    TipoAlbero d = leggiSottoAlbero(file_albero);

    r = creaAlbBin(i,s,d);

    leggiParentesi(file_albero);   /* legge la parentesi chiusa */

    return r;
  }
}


TipoAlbero leggiAlbero(char *nome_file) {
  TipoAlbero result;
  FILE *file_albero;
  file_albero = fopen(nome_file, "r");
  if (file_albero==NULL) {
      printf("File %s non trovato.\n",nome_file);
      return NULL;
  }
  result = leggiSottoAlbero(file_albero);
  fclose(file_albero);
  return result;
}

TipoAlbero randomAlbero(int size) {
    if (size==0)
        return albBinVuoto();
    else if (size==1) {
        TipoInfoAlbero c = rand()%10;
        return creaAlbBin(c,albBinVuoto(),albBinVuoto());
    }
    else {
        TipoInfoAlbero c = rand()%10;
        int l = rand()%(size-1);
        int r = size - 1 - l;
        return creaAlbBin(c,randomAlbero(l),randomAlbero(r));
    }
}



//////////////////////////////////////////////////////
//////////// Liste
//////////////////////////////////////////////////////
Lista listaVuota() {
    return NULL;
}

bool estVuota(Lista p) {
    return p == NULL;
}

Lista cons(InfoLista e, Lista p) {
    NodoListaSCL *n = (NodoListaSCL *)malloc(sizeof(NodoListaSCL));
    n->info = e;
    n->next = p;
    return n;
}

Lista cdr(Lista p) {
    return p->next;
}

InfoLista car(Lista p) {
    return p->info;
}

void stampaInfoLista(InfoLista i) {
    printf("%d ",i);
}

void stampaLista(Lista l) {
    NodoListaSCL *t = l;
    while (t!=NULL) {
        stampaInfoLista(t->info);
        t = t->next;
    }    
    printf("\n");
}

Lista append(Lista l1, Lista l2) {
    if (estVuota(l1))
        return l2;
    else
        return cons(car(l1),append(cdr(l1),l2));
}



int lunghezzaLista(Lista l){
	int lun = 0;
	if(l == NULL)
		return 0;
	lun = 1;
	Lista aux = l;
	while(aux->next != NULL){
		aux = aux->next;
		lun++;
	}
	return lun;
}

//////////////////////////////////////////////////////
//////////// Code
//////////////////////////////////////////////////////

Coda* codaVuota() {
    Coda* q = (Coda *)malloc(sizeof(Coda));
    NodoCodaSCL *n = (NodoCodaSCL *)malloc(sizeof(NodoCodaSCL));  // nodo generatore
    n->next = NULL;
    q->head = n;
    q->tail = n;
    return q;
}

bool estVuota(Coda *q) {
    return q->head->next == NULL;
}

void inCoda(Coda *q, InfoCoda e) {  // inserimento in coda
    NodoCodaSCL *n = (NodoCodaSCL *)malloc(sizeof(NodoCodaSCL));
    n->info = e;
    n->next = NULL;
    q->tail->next = n;
    q->tail = n;
}

void outCoda(Coda *q) { // eliminazione in testa
    NodoCodaSCL *InfoCoda = q->head->next;
    if (InfoCoda!=NULL) {
        q->head->next = q->head->next->next;
        free(InfoCoda);
    }
    if (estVuota(q)) // coda vuota -> reset tail
        q->tail = q->head;
}

InfoCoda primo(Coda *q) {
    InfoCoda r = CODAERROR;
    if (q->head->next!=NULL) {
        r = q->head->next->info;
    }
    return r;
}

void stampaInfoCoda(InfoCoda i) {
    printf("%d ",i);
}

void stampaCoda(Coda *q) {
    NodoCodaSCL *t = q->head->next;
    while (t!=NULL) {
        stampaInfoCoda(t->info);
        t = t->next;
    }    
    printf("\n");
}

