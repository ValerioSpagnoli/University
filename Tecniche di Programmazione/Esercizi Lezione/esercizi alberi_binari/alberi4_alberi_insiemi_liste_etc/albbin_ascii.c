#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>

#include "albbin_ascii.h"


struct qInfoCoda {
    TipoAlbero alb;
    int val;
    int drawdash_before;  // 0: no, 1: first half, 2: second half, 3: full
    bool root;
    bool leaf;
};

// Valore errore di tipo qInfoCoda
const qInfoCoda QCodaERROR = {NULL, -999};

// Tipo Nodo Coda
struct qNodoCodaSCL {
    qInfoCoda info;
    qNodoCodaSCL* next;
};

struct QCoda {
    qNodoCodaSCL *head;  // eliminazione in testa
    qNodoCodaSCL *tail;  // inserimento in coda
};

// Funzioni del tipo astratto

QCoda* qCodaVuota() {
    QCoda* q = (QCoda *)malloc(sizeof(QCoda));
    qNodoCodaSCL *n = (qNodoCodaSCL *)malloc(sizeof(qNodoCodaSCL));  // nodo generatore
    n->next = NULL;
    q->head = n;
    q->tail = n;
    return q;
}


bool qEstVuota(QCoda *q) {
    return q->head->next == NULL;
}

// O(1)
void qInCoda(QCoda *q, qInfoCoda e) {  // inserimento in coda
    qNodoCodaSCL *n = (qNodoCodaSCL *)malloc(sizeof(qNodoCodaSCL));
    n->info = e;
    n->next = NULL;
    q->tail->next = n;
    q->tail = n;
}

// O(1)
void qOutCoda(QCoda *q) { // eliminazione in testa
    qNodoCodaSCL *qInfoCoda = q->head->next;
    if (qInfoCoda!=NULL) {
        q->head->next = q->head->next->next;
        free(qInfoCoda);
    }
    if (qEstVuota(q)) // coda vuota -> reset tail
        q->tail = q->head;
}

// O(1)
qInfoCoda qPrimo(QCoda *q) {
    qInfoCoda r = QCodaERROR;
    if (q->head->next!=NULL) {
        r = q->head->next->info;
    }
    return r;
}




int aaSpaces(int livello, int maxlivello) {
    return pow(2,maxlivello) / pow(2,livello);
}


// Profondità albero
int aaDepth(TipoAlbero a) {
    if (estVuoto(a))
        return -1;
    else {
        int ps = aaDepth(sinistro(a));
        int pd = aaDepth(destro(a));
        return (std::max(ps,pd)+1);
    }
}


// disegna albero ASCII
void alberoASCII(TipoAlbero a) {

    if (estVuoto(a)) {
        printf("Albero vuoto.");
        return;
    }

    int maxlivello = aaDepth(a) + 1;
    int nstr = pow(2,maxlivello+1) + 1;

    char s1[nstr], s2[nstr], s3[nstr];
    s1[0]='\0';  s2[0]='\0'; s3[0]='\0';
    QCoda *q = qCodaVuota();
    qInfoCoda i; 
    i.alb=a; i.val=0; i.drawdash_before = 0; 
    i.root = true;
    i.leaf = (a->sinistro==NULL && a->destro==NULL);
    qInCoda(q,i);
    int livello = -1;
    int sp = 0;

    while (!qEstVuota(q)) {
        qInfoCoda p = qPrimo(q);
        TipoAlbero t = p.alb;

        if (p.val>livello) {
            // vai al prossimo livello
            livello = p.val;
            if (s1[0]!='\0') { // non stampare prima della radice
                printf("%s\n", s1);
                printf("%s\n", s2);
                printf("%s\n", s3);
            }
            sp = aaSpaces(livello, maxlivello);
            s1[0]='\0';  s2[0]='\0'; s3[0]='\0';
            for (int k=0; k<sp; k++) { 
                strcat(s1," "); strcat(s2," "); strcat(s3," ");
            }
        }
        else {

            if (sp>2) {

                for (int k=0; k<sp*2-3; k++) { 
                    strcat(s2," "); strcat(s3," ");
                }

                if (p.drawdash_before == 3) { // all
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1,"_");
                    }
                    strcat(s1,"/ \\");
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1,"_");
                    }
                }
                else if (p.drawdash_before == 1) { // only left
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1,"_");
                    }
                    strcat(s1,"/  ");
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1," ");
                    }
                }
                else if (p.drawdash_before == 2) { // only right
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1," ");
                    }
                    strcat(s1,"  \\");
                    for (int k=0; k<sp-3; k++) { 
                        strcat(s1,"_");
                    }
                }
                else { // none
                    for (int k=0; k<sp*2-3; k++) { 
                        strcat(s1," "); 
                    }
                }
            }
            else if (sp==2) {
                if (p.drawdash_before > 0)
                    strcat(s1,"|"); 
                else
                    strcat(s1," "); 
                strcat(s2," "); strcat(s3," "); 
            }

        }

        char si[8], si2[8]; si[0]='\0'; si2[0]='\0';
        if (t!=NULL) {
            stringaInfoAlbero(si2,t->info);
            strcat(si," "); strcat(si,si2); strcat(si," ");
            if (p.root) {
                strcat(s1,"   ");  strcat(s2,"   "); strcat(s3,si); 
            }
            else if (p.leaf) {
                strcat(s1,"   ");
                if ((p.drawdash_before == 3) || (p.drawdash_before == 2)) 
                    strcat(s2,"\\  "); 
                else
                    strcat(s2,"  /");
                strcat(s3,si); 
            }
            else {
                strcat(s1,"   ");  
                if ((p.drawdash_before == 3) || (p.drawdash_before == 2)) 
                    strcat(s2,"\\  "); 
                else
                    strcat(s2,"  /"); 
                strcat(s3,si);
            }
        }
        else {
            strcat(s1,"   ");  strcat(s2,"   "); strcat(s3,"   ");
        }

        qOutCoda(q);

        if (t!=NULL) {
            i.val=p.val+1;
            i.drawdash_before = 0; 
            i.alb=t->sinistro;  // anche alberi vuoti
            i.root = false;
            i.leaf = false;
            if (t->sinistro != NULL)
                i.leaf = (t->sinistro->sinistro==NULL && t->sinistro->destro==NULL);
            qInCoda(q,i);
            if (t->sinistro==NULL && t->destro==NULL)
                i.drawdash_before = 0;
            else if (t->destro==NULL)
                i.drawdash_before = 1;
            else if (t->sinistro==NULL)
                i.drawdash_before = 2;
            else // (t->sinistro!=NULL && t->destro!=NULL)
                i.drawdash_before = 3;
            i.alb=t->destro; 
            i.root = false;
            i.leaf = false;
            if (t->destro != NULL)
                i.leaf = (t->destro->sinistro==NULL && t->destro->destro==NULL);
            qInCoda(q,i);
        }
        else if (livello < maxlivello) { 
            // questo nodo è vuoto ma ce ne sono altri a questo livello
            // aggiungere figli vuoti...
             
            i.val=p.val+1;

            i.drawdash_before = 0;
            i.alb=NULL;
            i.root = false;
            i.leaf = false;
            qInCoda(q,i);

            i.drawdash_before = 0;
            i.alb=NULL; 
            i.root = false;
            i.leaf = false;
            qInCoda(q,i);

        }

    }
    printf("\n");
}

void stampaAlberoASCII(const char* astr, TipoAlbero a) {
    printf("Albero %s:\n",astr);
    alberoASCII(a);
    printf("\n");
}


