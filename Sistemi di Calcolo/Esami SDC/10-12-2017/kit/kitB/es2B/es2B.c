void loads(char**);

char* get(int i) {
    char* b;
    loads(&b);
    return b + i;
}
