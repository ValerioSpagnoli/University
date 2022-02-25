#include <stdio.h>
#include <stdlib.h>

#include "esercizio_2.h"

/*

Esercizio 2

Sia data una lista i cui elementi appartengono alla seguente struttura ListNode:

struct ListNode {
  Data info;
  ListNode *next;
};

dove ogni elemento contiene un valore intero:

typedef int Data;

Implementare la seguente funzione C:

ListNode *subset(ListNode *list, Data m);

che data in input una lista concatenata list, restituisca il puntatore ad una nuova lista concatenata che contine i soli elementi di list i cui valori sono maggiori di m. L'ordine degli elementi della lista ritornata dovra' essere quello della lista di input.

Si gestisca il caso in cui il puntatore list è nullo, restituendo un puntatore nullo. La lista in ingresso alla funzione non deve essere modificata in alcun modo. 

*/

ListNode* aggiungi (ListNode* l, Data e){
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp -> info = e;
	temp -> next = l;
	return temp;
}

ListNode *subset(ListNode *list, Data m) {
	if(list == NULL) return NULL;
	else{
		ListNode* l = subset((list)->next, m);
		if((list)->info > m){
			l = aggiungi(l, (list)->info);
		}
		return l;
	}
}

