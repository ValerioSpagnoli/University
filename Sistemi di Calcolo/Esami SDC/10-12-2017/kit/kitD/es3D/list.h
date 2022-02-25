#ifndef __LIST__
#define __LIST__

typedef struct list list;

list* list_new      ();
void  list_add      (list* s, int x);
int   list_contains (list* s, int x);
void  list_delete   (list* s);

#endif
