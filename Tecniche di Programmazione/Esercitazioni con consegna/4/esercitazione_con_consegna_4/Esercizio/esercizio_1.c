#include "esercizio_1.h"

void addSCL (TipoSCL *scl, TipoInfoSCL e) {
  TipoSCL temp = *scl;
  *scl = (TipoNodoSCL *) malloc(sizeof(TipoNodoSCL));
  (*scl)->info = e;
  (*scl)->next = temp;
}


TipoSCL palindroma (TipoSCL h){
	TipoSCL c = h;
	TipoSCL p = NULL;
	TipoSCL p1 = NULL;
	if(h == NULL){
		
		return NULL;
	}
	else{
		while(h != NULL){
			addSCL(&p, h->info);
			addSCL(&p1, h->info);
			h = h->next;
		}	
	}
	while(p1 != NULL){
			addSCL(&p, p1->info);
			p1 = p1->next;
		}
	return p;	
}
