void load(int * a);

int get(int* x) {
    int z;
    load(&z);
    return x[0] <= z && z <= x[1] && !(x[0]<0);
}
