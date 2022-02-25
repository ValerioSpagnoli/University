#include "esercizio_1.h"
#include <time.h>

void print_array(float* a, int n){
  if(a == NULL){return;}
  if (n == 0) return;
  printf("%0.2f ", *a);
  print_array(a+1, n-1);
}

void generateRandomArray(float *v, int dim, int seed){
	srand(seed);
	int i = 0;
	while(i < dim){
		v[i] = rand()%10;
		i++;
	}
	return;
}

int main()
{
  int seed;
  float *newArr;
  srand(time(NULL));
  seed = rand()%10;
  printf("Input 1 \n");  
  float v1_1[5];
  float v1_2[5];
  generateRandomArray(v1_1,5, seed + 1 );
  generateRandomArray(v1_2,5, seed + 2);

  print_array(v1_1, 5);
  printf("\n");
  print_array(v1_2, 5);
  printf("\n\n");
  newArr = maxDispari(v1_1,v1_2,5,5);
  printf("output 1:\n");
  print_array(newArr, 5);
  printf("\n\n**********************************\n\n");
  
  printf("Input 2 \n");
  float v2_1[8];
  float v2_2[8];
  generateRandomArray(v2_1,8, seed + 3);
  generateRandomArray(v2_2,8, seed + 4);
  
  print_array(v2_1, 8);
  printf("\n");
  print_array(v2_2, 8);
  printf("\n\n");
  newArr = maxDispari(v2_1,v2_2,8,8);
  printf("output 2:\n");
  print_array(newArr, 8);
  printf("\n\n**********************************\n\n");
  
  
  printf("Input 3 \n");
  float v3_1[5];
  float v3_2[7];
  generateRandomArray(v3_1,5, seed + 5);
  generateRandomArray(v3_2,7, seed + 6);
  
  print_array(v3_1, 5);
  printf("\n");
  print_array(v3_2, 7);
  printf("\n\n");
  newArr = maxDispari(v3_1,v3_2,5,7);
  printf("output 3:\n");
  print_array(newArr, 5);
  printf("\n\n**********************************\n\n");
  
  
  printf("Input 4 \n");
  float v4_1[7] = {1,2,3,4,5,2,1};
  float v4_2[5] = {1,4,3,2,5};
  generateRandomArray(v4_1,7, seed + 7);
  generateRandomArray(v4_2,5, seed + 8);
  
  print_array(v4_1, 7);
  printf("\n");
  print_array(v4_2, 5);
  printf("\n\n");

  newArr = maxDispari(v4_1,v4_2,7,5);
  
  printf("output 4:\n");
  print_array(newArr, 7);
  printf("\n\n**********************************\n\n");
  
  
  printf("Input 5 \n");
  float *v5_1;
  float v5_2[5] = {1,4,3,2,5};
  generateRandomArray(v5_1,0, seed + 9);
  generateRandomArray(v5_2,5, seed + 10);
  
  
  print_array(v5_1, 0);
  printf("\n");
  print_array(v5_2, 5);
  printf("\n\n");
  newArr = maxDispari(v5_1,v5_2,0,5);
  printf("output 5:\n");
  print_array(newArr, 0);
  printf("\n\n**********************************\n\n");
  
  

  return 0;
}
