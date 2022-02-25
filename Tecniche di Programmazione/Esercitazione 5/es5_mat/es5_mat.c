#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "es5_mat.h"






//////////////////////////////////////utility function implementation
Mat* Mat_alloc(int rows, int cols) {
  Mat* m = (Mat*)malloc(sizeof(Mat));
  m->rows = rows;
  m->cols = cols;
  m->row_ptrs = (float**)malloc(rows * sizeof(float*));
  for(int i = 0; i < m->rows; ++i) {
    m->row_ptrs[i] = (float*)malloc(m->cols * sizeof(float));
  }
  return m;
}

Mat* Mat_read(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if(fp == NULL) {
    printf("Errore nell'apertura del file %s... esco!\n", filename);
    fclose(fp);
    return NULL;
  }

  int rows = 0;
  if(fscanf(fp, "%d", &rows) != 1) {
    printf("Errore durante la lettura del file %s, non riesco a leggere il numero di righe... esco!\n", filename);
    fclose(fp);
    return NULL;
  }
  if(rows == 0) {
    return NULL;
  }

  int cols = 0; 
  if(fscanf(fp, "%d", &cols) != 1) {
    printf("Errore durante la lettura del file %s, non riesco a leggere il numero di colonne... esco!\n", filename);
    fclose(fp);
    return NULL;
  }
  if(cols == 0) {
    return NULL;
  }

  Mat *m = Mat_alloc(rows, cols);
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      float valore = 0.0f;
      if(fscanf(fp, "%f", &valore) != 1) {
        printf("Errore durante la lettura del file %s, non riesco a leggere tutti gli elementi... esco!\n", filename);
        fclose(fp);
        return NULL;
      }
      m->row_ptrs[r][c] = valore;
    }
  }

  fclose(fp);
  return m;
}

void Mat_print(Mat *m) {
  for(int r = 0; r < m->rows; ++r) {
    for(int c = 0; c < m->cols; ++c) {
      printf("%lf ", m->row_ptrs[r][c]);
    }
    printf("\n");
  }
}

void Mat_write(const char *filename, Mat *m) {
  FILE *fp = fopen(filename, "w");
  if(fp == NULL) {
    printf("Errore nell'apertura del file %s... esco!\n", filename);
    return;
  }
  
  fprintf(fp, "%d ", m->rows);
  fprintf(fp, "%d\n", m->cols);
  for(int r = 0; r < m->rows; ++r) {
    for(int c = 0; c < m->cols; ++c) {
      fprintf(fp, "%f ", m->row_ptrs[r][c]);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void Mat_free(Mat *m) {  
  for(int i = 0; i < m->rows; ++i) {
    free(m->row_ptrs[i]);
  }
  free(m->row_ptrs);
  free(m);
}

////////////////////////////////////////////////////functions to implement
bool  Mat_is_symmetric(Mat *m) {

  // IMPLEMENT ME
  return true;
}

void Mat_normalize_rows(Mat *m) {

  // IMPLEMENT ME
}

Mat* Mat_clone(Mat *m) {

  Mat *copy;
  // IMPLEMENT ME
  return copy;
}

Mat* Mat_sum(Mat *m1, Mat *m2){

  Mat *output;
  // IMPLEMENT ME
  return output;
}


Mat* Mat_product(Mat *m1, Mat *m2){

  Mat *output;
  // IMPLEMENT ME
  return output;
}


