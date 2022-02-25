#include "correttore_esercizio_1.h"
#include <time.h>

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
  int total_test_number = 5, successes = 0;
  srand(time(NULL));
  int seed = rand()%10;
  float v1_1[5];
  float v1_2[5];
  generateRandomArray(v1_1,5, 1 );
  generateRandomArray(v1_2,5, 2);


  printf("Test numero 1 su %d\n", total_test_number);
  if(checkResult(v1_1, v1_2, 5, 5))
    {
      printf("SUCCESS\n");
      successes++;
    }
  else
  {
    printf("FAILURE\n");
  }
  printf("Current success rate: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
  printf("\n*************************************************\n\n");
  
  float v2_1[8];
  float v2_2[8];

  generateRandomArray(v2_1,8, seed + 3);
  generateRandomArray(v2_2,8, seed + 4);

  printf("Test numero 2 su %d\n", total_test_number);
  if(checkResult(v2_1, v2_2, 8, 8))
    {
      printf("SUCCESS\n");
      successes++;
    }
  else
  {
    printf("FAILURE\n");
  }
  printf("Current success rate: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
  printf("\n*************************************************\n\n");
  

  float v3_1[5];
  float v3_2[7];

  generateRandomArray(v3_1,5, seed + 5);
  generateRandomArray(v3_2,7, seed + 6);
  
  printf("Test numero 3 su %d\n", total_test_number);
  if(checkResult(v3_1, v3_2, 5, 7))
    {
      printf("SUCCESS\n");
      successes++;
    }
  else
  {
    printf("FAILURE\n");
  }
  printf("Current success rate: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
  printf("\n*************************************************\n\n");
  

  float v4_1[7];
  float v4_2[5];

  generateRandomArray(v4_1,7, seed + 7);
  generateRandomArray(v4_2,5, seed + 8);

  printf("Test numero 4 su %d\n", total_test_number);
  if(checkResult(v4_1, v4_2, 7, 5))
    {
      printf("SUCCESS\n");
      successes++;
    }
  else
  {
    printf("FAILURE\n");
  }
  printf("Current success rate: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
  printf("\n*************************************************\n\n");
  
  
  
  float *v5_1;
  float v5_2[5];
  generateRandomArray(v5_1,0, seed + 9);
  generateRandomArray(v5_2,5, seed + 10);

  printf("Test numero 5 su %d\n", total_test_number);
  if(checkResult(v5_1, v5_2, 0, 5))
    {
      printf("SUCCESS\n");
      successes++;
    }
  else
  {
    printf("FAILURE\n");
  }
  printf("Current success rate: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
  printf("\n*************************************************\n\n");
  
  
  printf("FINAL SUCCESS RATE: %0.02f%%\n", (float)(successes) * 100.0f / (float)(total_test_number));


  return 0;
}
