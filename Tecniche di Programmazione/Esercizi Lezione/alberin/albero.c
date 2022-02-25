#include "albero.h"

// Funzioni del tipo astratto

TipoAlbero alberoVuoto() {
  return NULL;
}

TipoAlbero creaAlbero(TipoInfoAlbero info, TipoFigli f) {
  TipoAlbero a = (TipoAlbero) malloc(sizeof(struct StructAlbero));
  a->info = info;
  a->figli = f;
  return a;
}


bool estVuoto(TipoAlbero a) {
  return (a == NULL);
}

TipoInfoAlbero radice(TipoAlbero a) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
    return ERRORE_InfoAlbero;
  } else {
    return a->info;
  }
}


TipoFigli figli(TipoAlbero a) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
    return NULL;
  } else {
    return a->figli;
  }
}

TipoFigli add(TipoFigli f, TipoAlbero a) {
    TipoFigli n = (TipoFigli)malloc(sizeof(struct StructNodoFiglio));
    n->albero = a;
    n->next = f;
    return n;
    
}

void aggiungiFiglio(TipoAlbero a, TipoAlbero f) {
  if (a == NULL) {
    printf ("ERRORE accesso albero vuoto \n");
  } else {
    a->figli = add(a->figli, f);
  }
}



// Funzioni esterne

void stampaParentetica(TipoAlbero a) {
    if (a==NULL) {
        printf("()");
    }
    else {
        printf("( %d ",a->info);
        TipoFigli p = a->figli;
        while (p!=NULL) {
            stampaParentetica(p->albero);
            printf(" ");
            p = p->next;
        }
        printf("() )");
    }
}

void stampaAlbero(const char* astr, TipoAlbero a) {
    printf("Albero %s: ",astr);
    stampaParentetica(a);
    printf("\n");
}


void leggiParentesi(FILE *file_albero) {
  char c = ' ';
  while (c!='(' && c!=')')
    c = fgetc(file_albero);
}

TipoAlbero leggiSottoAlbero(FILE *file_albero);

TipoFigli leggiFigli(FILE *file_albero) {
    TipoAlbero f = leggiSottoAlbero(file_albero);
    if (f==NULL)
        return NULL;
    else {
        // printf("aggiungi figlio %d\n", f->info);
        return add(leggiFigli(file_albero), f);    
    }
}

TipoAlbero leggiSottoAlbero(FILE *file_albero) {
  char c;
  TipoInfoAlbero i;
  TipoAlbero r;
  leggiParentesi(file_albero);   // legge la parentesi aperta
  c = fgetc(file_albero);   // carattere successivo
  if (c == ')')
    return NULL;   // se legge () allora l'albero e' vuoto
  else {
    fscanf(file_albero, "%d", &i);   // altrimenti legge la radice

    // printf("crea alb %d\n", i);
    r = creaAlbero(i, leggiFigli(file_albero));

    leggiParentesi(file_albero);   // legge la parentesi chiusa

    return r;
  }
}

TipoAlbero leggiAlbero(const char *nomefile) {
  TipoAlbero result;
  FILE *fileAlbero;
  fileAlbero = fopen(nomefile, "r");
  if (fileAlbero==NULL) {
      printf("File %s non trovato.\n",nomefile);
      return alberoVuoto();
  }
  result = leggiSottoAlbero(fileAlbero);
  fclose(fileAlbero);
  return result;
}

