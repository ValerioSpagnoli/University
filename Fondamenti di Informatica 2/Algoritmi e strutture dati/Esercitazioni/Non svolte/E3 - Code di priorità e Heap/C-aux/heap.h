#ifndef HEAP_H
#define	HEAP_H
    
typedef int HEAP_TYPE;
#define MIN_HEAP 1
#define MAX_HEAP 0

typedef struct heap_entry{
	int key;
	int position;
} heap_entry;

typedef struct {
	heap_entry ** array;
	int size;
	int used;
	int is_min_heap;
} heap;

heap * heap_new(HEAP_TYPE type, int capacity);
HEAP_TYPE heap_type(heap * h);
int heap_peek(heap * h);
int heap_poll(heap * h);
heap_entry * heap_add(heap * h, int key);
int get_key_entry(heap_entry * e);
int heap_size(heap * h);
void heap_delete(heap * h);
void heap_print(heap * h);

heap * array2heap(int * array, int size, HEAP_TYPE type);

void heap_sort(int * array, int size);

void heap_update_key(heap * h, heap_entry * e, int key);

#endif	/* HEAP_H */

