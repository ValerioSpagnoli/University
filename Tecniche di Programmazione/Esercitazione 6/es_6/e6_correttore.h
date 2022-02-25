#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "e6_esercizio.h"


void vec_print(float v[], int dim);

int _lunghezza(char *s);

int _char_in_posizione(char* s, char ch);
int _char_in_posizione_aux(char* s, char ch, int i);


void _vec_integral(float* v, int n);
void _vec_integral_aux(float* v, int n, int i, float sum_till_now);
    
float _vec_dot(float* v1, float* v2, int n);
float _vec_dot_aux(float* v1, float* v2, int n, int i);



