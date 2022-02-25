#include <stdio.h>
#include <stdlib.h>

#ifndef SCL_H
#define SCL_H

typedef int TipoInfoSCL;

struct TipoNodoSCL{
	TipoInfoSCL info;
	struct TipoNodoSCL* next;
};

typedef struct TipoNodoSCL* TipoSCL;


// prints a list to stdout
void print(TipoSCL list_);
TipoSCL generate(const int& number_of_nodes_);
TipoSCL copySCL(TipoSCL src);
void freeSCL(TipoSCL list_);
bool listCompare(TipoSCL l1, TipoSCL l2);
TipoSCL array_generate (const int &number_of_nodes_, int *arr);


#endif
