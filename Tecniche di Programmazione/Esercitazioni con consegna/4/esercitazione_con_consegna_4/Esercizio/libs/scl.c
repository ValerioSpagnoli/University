#include <stdlib.h>
#include <stdio.h>
#include "scl.h"

void print(TipoSCL list_) {
  if (!list_) {
    return;
  }

  //ds print head
  printf("[%i]", list_->info);
  list_ = list_->next;

  //ds print the rest of the list
  while (list_) {
    printf(" -> [%i]", list_->info);
    list_ = list_->next;
  }
  printf("\n");
}

TipoSCL generate(const int& number_of_nodes_) {
  TipoSCL head = 0;
  
  //ds allocate a list with n elements and random values [0, 10]
  TipoSCL node_previous = 0;
  for (int u = 0; u < number_of_nodes_; ++u) {
    TipoSCL node = new TipoNodoSCL();
    node->info     = rand()%11;

    //ds if the head is not set yet
    if (!head) {
      head = node;
    } else {

      //ds link previous node to this
      node_previous->next = node;
    }
    node_previous = node;
  }
  return head;
}


void freeSCL(TipoSCL list_) {
  if (!list_) {
    return;
  }
  while (list_) {
    TipoSCL list_next = list_->next;
    delete list_;
    list_ = list_next;
  }
}

bool listCompare(TipoSCL l1, TipoSCL l2){
    if(l1 == NULL && l2 == NULL){
        return true;
    }else if( (l1 == NULL && l2 != NULL) || (l1 != NULL && l2 == NULL) ){
        return false;
    }
    
    if(l1-> info != l2->info){
        return false;
    }else{
        return listCompare(l1->next, l2->next);
    }
}

TipoSCL array_generate (const int &number_of_nodes_, int *arr)
{
  TipoSCL head = NULL;

  //ds allocate a list with n elements and random values [0, 10]
  TipoSCL node_previous = 0;
  for (int u = 0; u < number_of_nodes_; ++u)
    {
      TipoSCL node = new TipoNodoSCL ();
      node->info = arr[u];

      //ds if the head is not set yet
      if (!head)
  {
    head = node;
  }
      else
  {

    //ds link previous node to this
    node_previous->next = node;
  }
      node_previous = node;
    }
  return head;
}