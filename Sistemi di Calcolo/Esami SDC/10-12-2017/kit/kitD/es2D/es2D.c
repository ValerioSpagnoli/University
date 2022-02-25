int veclen(int x, int y, int* d) {
    return x >= 0 && y >= 0 && x*x+y*y < (*d)*(*d);
}
