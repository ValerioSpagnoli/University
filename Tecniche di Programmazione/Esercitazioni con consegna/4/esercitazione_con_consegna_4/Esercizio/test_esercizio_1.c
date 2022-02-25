#include <stdio.h>
#include <esercizio_1.h>

TipoSCL listProvider(int i);
TipoSCL solutionProvider(int i);

int main ()
{
  int test_cases = 5;
  int success = 0;
  for (int i = 0; i < test_cases; i++)
    {
      
      TipoSCL scl = listProvider(i);
      TipoSCL sol = solutionProvider(i);
      TipoSCL t = palindroma (scl);
      printf("Test numero %d di 10 \nINPUT \n",i+1);
      print(scl);
      printf("\nOUTPUT\n");
      print (t);
      if(listCompare(t,sol)){
          success ++;
          printf("SUCCESS\n");
      }else{
          printf("FAIL\n");
      }
      printf("\n****************\n");
      freeSCL (scl);
      freeSCL (t);

    }
  int success_rate = ( (float)(success)/(float)(test_cases) ) * 100;
  printf("TOTAL SUCCESS RATE = %d%% \n", success_rate);
  return 0;
}

TipoSCL listProvider(int i){
    TipoSCL input = NULL;
    switch(i){
        case 0:{ int arr[5] = {1,2,3,4,5}; input = array_generate(5,arr); break;}
        case 1:{ int arr[6] = {2,5,7,8,9,1}; input = array_generate(6,arr); break;}
        case 2:{ int arr[2] = {2,2}; input = array_generate(2,arr); break;}
        case 3:{ int arr[1] = {8}; input = array_generate(1,arr); break;}
        case 4:{ break;}
        
        
    }
    return input;
}


TipoSCL solutionProvider(int i){
    TipoSCL input = NULL;
    switch(i){
        case 0:{ int arr[10] = {1,2,3,4,5,5,4,3,2,1}; input = array_generate(10,arr); break;}
        case 1:{ int arr[12] = {2,5,7,8,9,1,1,9,8,7,5,2}; input = array_generate(12,arr); break;}
        case 2:{ int arr[4] = {2,2,2,2}; input = array_generate(4,arr); break;}
        case 3:{ int arr[2] = {8,8}; input = array_generate(2,arr); break;}
        case 4:{ break;}
        
        
    }
    return input;
}

