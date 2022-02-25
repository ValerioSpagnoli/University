#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int rows; 
  int cols;
  float **row_ptrs;
} Mat;

Mat* Mat_alloc(int rows, int cols);
Mat* Mat_read(const char *filename);

int main(int argc, char **argv) {
  //  ...

  return 0;
}

Mat* Mat_alloc(int rows, int cols) {
  Mat* m;
  // IMPLEMENT ME
  return m;
}

Mat* Mat_read(const char *filename) {
  Mat *m;
  // IMPLEMENT ME
  return m;
}


