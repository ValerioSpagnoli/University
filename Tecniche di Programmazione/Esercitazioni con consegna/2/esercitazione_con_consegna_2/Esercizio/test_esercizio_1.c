#include "esercizio_1.h"

Mat* create_campo_minato(int rows, int cols, int bombe){
	
	Mat * m;
	m = uniformMat( rows,  cols, 0 );
	int i = 0;
	for(i = 0; i < bombe; i++){
		m->row_ptrs[(int)(rand()%rows)][(int)(rand()%cols)] = -1;
	}
	return m;
}

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
    Mat *dst = campo_minato(src);

    printf("Input:\n");
    printMatrix(src);
    printf("\n");
    printf("Output :\n");
    printMatrix(dst);
    printf("\n");

    
    printf("\n*************************************************\n\n");

    freeMatrix(src);
    freeMatrix(dst);

  }

  
  return 0;
}
