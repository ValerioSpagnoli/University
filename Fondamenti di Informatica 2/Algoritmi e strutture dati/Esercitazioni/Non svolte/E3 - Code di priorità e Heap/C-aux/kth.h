#ifndef KTH_H
#define	KTH_H
    
typedef struct kth {
	heap * min_heap;
	heap * max_heap;
	int k;
} kth;

kth * kth_new(int k);
void kth_delete(kth * d);
void kth_insert(kth * d, int key);
int kth_get(kth * d);
void kth_remove(kth * k);


#endif	/* KTH_H */

