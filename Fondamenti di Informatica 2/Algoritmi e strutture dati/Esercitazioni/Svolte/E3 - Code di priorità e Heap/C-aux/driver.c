#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "kth.h"

void print_help() {
    printf("Richiesto argomento: {min_heap, array, sort, change, k}\n");
}

void print_array(int * array, int size) {
    int k;
    for (k = 0; k < size; k++)
        printf(" %d", array[k]);
    printf("\n");
}

int main(int argc, char** argv) {

    if (argc != 2) {
        print_help();
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "min_heap") == 0) {
        
        printf("Building a min heap with 10 items\n");
        heap * h = heap_new(MIN_HEAP, 10);

        heap_add(h, 5);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 5 \n");
        printf("------------------\n");

        heap_add(h, 10);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 5 10 \n");
        printf("------------------\n");

        heap_add(h, 15);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 5 10 15 \n");
        printf("------------------\n");

        heap_add(h, 9);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 5 9 15 10\n");
        printf("------------------\n");

        heap_add(h, 4);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 4 5 15 10 9\n");
        printf("------------------\n");

        heap_add(h, 13);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 4 5 13 10 9 15\n");
        printf("------------------\n");

        heap_add(h, 3);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 3 5 4 10 9 15 13\n");
        printf("------------------\n");

        heap_add(h, 2);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 2 3 4 5 9 15 13 10\n");
        printf("------------------\n");

        heap_poll(h);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 3 5 4 10 9 15 13\n");
        printf("------------------\n");        

        heap_delete(h);

    } else if (strcmp(argv[1], "array") == 0) {
        
        int a[] = {17, 3, 100, 25, 1, 2, 7, 19, 36};
        heap * h = array2heap(a, sizeof(a) / sizeof(int), MAX_HEAP);
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 100 36 17 25 1 2 7 19 3\n");
        heap_delete(h);

    } else if (strcmp(argv[1], "sort") == 0) {

        int a[] = {17, 3, 100, 25, 1, 2, 7, 19, 36};
        heap_sort(a, sizeof(a) / sizeof(int));
        printf("Array is:\n\t");
        print_array(a, sizeof(a) / sizeof(int));
        printf("Should be:\n\t 1 2 3 7 17 19 25 36 100\n");

    } else if (strcmp(argv[1], "change") == 0) {

        printf("Building a min heap with 10 items\n");
        heap * h = heap_new(MIN_HEAP, 10);

        heap_add(h, 5);
        heap_add(h, 10);
        heap_add(h, 15);
        heap_add(h, 9);
        heap_add(h, 4);
        heap_add(h, 13);
        heap_add(h, 3);
        heap_entry * e = heap_add(h, 2);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("------------------\n");

        printf("Updating last inserted node from 2 to 11...\n");

        heap_update_key(h, e, 11);
        printf("------------------\n");
        printf("Heap is:\n\t");
        heap_print(h);
        printf("Should be:\n\t 3 5 4 10 9 15 13 11\n");
        printf("------------------\n");

        heap_delete(h);

    } else if (strcmp(argv[1], "k") == 0) {

        int a[] = {17, 3, 100, 25, 1, 2, 7, 19, 36};
        kth * d = kth_new(4);

        kth_insert(d, a[0]);
        kth_insert(d, a[1]);
        kth_insert(d, a[2]);
        kth_insert(d, a[3]);
        printf("k-th is %d should be %d\n", kth_get(d), 100);
        kth_insert(d, a[4]);
        printf("k-th is %d should be %d\n", kth_get(d), 25);
        kth_remove(d);
        printf("k-th is %d should be %d\n", kth_get(d), 100);
        kth_insert(d, a[3]);
        kth_insert(d, a[5]);
        kth_insert(d, a[6]);
        kth_insert(d, a[8]);
        printf("k-th is %d should be %d\n", kth_get(d), 7);
        kth_remove(d);
        kth_remove(d);
        kth_remove(d);
        kth_remove(d);
        kth_remove(d);
        printf("k-th is %d should be %d\n", kth_get(d), 3);

        kth_delete(d);

    } else {

    	print_help();
    	return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
