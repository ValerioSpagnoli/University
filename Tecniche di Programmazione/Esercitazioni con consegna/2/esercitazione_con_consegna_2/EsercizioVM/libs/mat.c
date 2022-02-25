#include "mat.h"

Mat *allocMatrix(int rows, int cols)
{
  Mat *m = (Mat*)malloc(sizeof(Mat));
  m->rows = rows;
  m->cols = cols;
  
  m->row_ptrs = (int **)malloc(sizeof(int*)*rows);
  for(int r = 0; r < rows; r++)
    m->row_ptrs[r] = (int *)malloc(sizeof(int)*cols);
 
  return m;
}

void freeMatrix(Mat* src) 
{
  if( src == NULL )
    return;
  int rows = src->rows;
  //  int cols = src->cols;
  for(int r=0; r<rows; ++r)
    free(src->row_ptrs[r]);

  free(src);
}

Mat *randomMat( int rows, int cols, int max )
{
  Mat *m = allocMatrix(rows, cols);

  max++;
  for( int r = 0; r < rows; r++ )
    for( int c = 0; c < cols; c++ )
      m->row_ptrs[r][c] = rand()%max;
    
  return m;
}

Mat *uniformMat( int rows, int cols, int val )
{
  Mat *m = allocMatrix(rows, cols);

  for( int r = 0; r < rows; r++ )
    for( int c = 0; c < cols; c++ )
      m->row_ptrs[r][c] = val;
    
  return m;
}

void printMatrix(Mat* src) 
{
  if(src == NULL){
    printf("NULL\n");
    return;
  }
  int rows = src->rows;
  int cols = src->cols;
  for(int r=0; r<rows; ++r) {
    for(int c=0; c<cols; ++c) {
      printf("%d\t", src->row_ptrs[r][c]);
    }
    printf("\n");
  }
  fflush(stdout);
}
