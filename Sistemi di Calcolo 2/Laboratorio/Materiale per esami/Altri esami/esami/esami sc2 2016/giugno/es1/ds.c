#include <stdlib.h>

#include "common.h"

myStruct* initialize_struct() {
    myStruct* S = malloc(sizeof(myStruct));
    
    srand(SEED);
    int N = 1 + rand() % 1000;
    S->vec = malloc(N * sizeof(int));
    S->elems = N;
    
    // popola array con numeri pseudo-casuali
    while (N--) S->vec[N] = rand();
    
    return S;
}

void* get_struct_for_fifo_write(myStruct* S) {
    size_t len = get_struct_len_for_fifo_write(S);
    
    // basta trasferire il solo vec
    void* buf = malloc(len);
    memcpy(buf, S->vec, len);
    
    return buf;
}

size_t get_struct_len_for_fifo_write(myStruct* S) {
    return S->elems * sizeof(int);
}

uint32_t get_struct_checksum(myStruct* S) {
    int N = S->elems;
    
    uint32_t checksum = 0;
    while (N--) checksum ^= S->vec[N];
    
    return checksum;
}

myStruct* reconstruct_from_fifo_read(void* data, size_t len) {
    myStruct* S = malloc(sizeof(myStruct));
    
    S->elems = len/sizeof(int);
    S->vec = malloc(len);
    memcpy(S->vec, data, len);
    
    return S;
}

void free_struct(myStruct* S) {
    free(S->vec);
    free(S);
}
