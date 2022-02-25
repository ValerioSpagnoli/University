#pragma once

#include <stdlib.h>
#include <stdio.h>




void printList(TipoSCL l){
  if(l == NULL)
    return;
  TipoSCL aux=l;
  int pos=0;
  while(aux!=NULL){
    printf("pos: %d, info: %.1f\n", pos, aux->info);
    aux=aux->next;
    pos++;
  }
}

TipoSCL listPushFront(TipoSCL p0, int info){
  TipoSCL new_element=(TipoSCL)malloc(sizeof(TipoNodoSCL));
  new_element->next=p0;
  new_element->info=info;
  return new_element;
}

TipoSCL listPushBack(TipoSCL l, int info){
  TipoSCL new_element=(TipoSCL)malloc(sizeof(TipoNodoSCL));
  new_element->next=NULL;
  new_element->info=info;
  
  if (l==NULL){
    return new_element;
  }
  TipoSCL aux=l;
  while(aux->next!=NULL){
    aux=aux->next;
  }
  aux->next=new_element;
  return l;
}


TipoSCL copyList(TipoSCL list) {
  TipoSCL head = NULL;

  while(list){
    head = listPushBack(head, list->info);
    list = list->next;
  }
  return head;
}

TipoSCL createRandomList(int size){
  TipoSCL random_list = NULL;
  for(int i=0; i<size; ++i)
    random_list = listPushFront(random_list, rand()%20 - 10);
  return random_list;
}

int compareList(TipoSCL l1, TipoSCL l2){
  if(!l1 || !l2)
    return 0;
  while(l1 || l2) {
    if(!(l1 && l2))
      return 0;
    if(l1->info != l2->info)
      return 0;
    l1 = l1->next;
    l2 = l2->next;
  }
  return 1;
}

void freeList(TipoSCL list){
  if(!list)
    return;
  if(list->next)
    freeList(list->next);
  else
    free(list);
  return;
}



