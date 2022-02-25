#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "functions.h"


void vec_print(float v[], int dim);

int _lunghezza(char *s);

bool _tuttiMinuscoli(char *s);

void _converti(char* s);

int _contaParentesi(char *s);

void _concatenate(char* dest, char* src);
void _copia(char* dest, char* s);

float _prodotto(float a[], int n);

/*********************************
* SCL_media
***********************************/
float _SCL_media(TipoSCL head_ptr);

float _SCL_media_aux1(TipoSCL head_ptr);

int _SCL_media_aux2(TipoSCL head_ptr);
/****************************
 * SCL_integral
 *
 * scrivere, ricorsivamente, in ogni elemento della lista la somma degli elementi precedenti
 **************************** */
void _SCL_integral(TipoSCL head_ptr);
int _SCL_integral_aux(TipoSCL ptr, float sum);

/****************************
 * SCL_dot
 *
 * ritorna il prodotto scalare, calcolato ricorsivamente, delle liste con puntatori
 * alla testa head1_ptr e head2_ptr
 **************************** */
float _SCL_dot(TipoSCL head1_ptr, TipoSCL head2_ptr);


