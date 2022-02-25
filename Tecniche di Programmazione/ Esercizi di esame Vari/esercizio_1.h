#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Mat {
  int cols; // numero di colonne
  int rows; // numero di righe
  int** row_ptrs; // puntatori alle righe
};

void prodCont( Mat* src, Mat* dst );

