int fetch_elem_ptr(int** buf_ptr, int* v, int i) {
    if (!buf_ptr) return -1;
    *buf_ptr = v + i;
    return 0;
}
