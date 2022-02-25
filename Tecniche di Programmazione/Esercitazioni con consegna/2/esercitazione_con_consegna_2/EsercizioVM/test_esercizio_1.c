#include "correttore_esercizio_1.h"

int main()
{
		
  int total_test_number = 10, successes = 0;

  for(int i = 0; i < total_test_number; ++i)
  {
    printf("Test numero %d su %d\n", i + 1, total_test_number);

    int rows = rand()%7 + 1, cols = rand()%7 + 1;
    if (rows%2==1)
        rows++;

    Mat *src = create_campo_minato(rows, cols, (int)((rows+cols)/3));
    Mat *dst = campo_minato_soluzione(src);

    printf("Input:\n");
    printMatrix(src);
    printf("\n");
    printf("Output atteso:\n");
    printMatrix(dst);
    printf("\n");

    if( checkResult(src, dst))
    {
      printf("SUCCESS\n");
      successes++;
    }
    else
    {
      printf("FAILURE\n");
    }
    printf("Percentuale di successo corrente: %0.02f%%\n", (float)(successes) * 100.0f/ (float)(total_test_number));
    printf("\n*************************************************\n\n");

    freeMatrix(src);
    freeMatrix(dst);

  }

  printf("Percentuale di successo finale: %0.02f%%\n", (float)(successes) * 100.0f / (float)(total_test_number));

  return 0;
}
