#include "correttore_esercizio_1.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

char * stringProvider(int i);

int main()
{
  int total_test_number = 10, successes = 0;

  for(int i = 0; i < total_test_number; ++i)
  {
    printf("Test numero %d su %d\n", i + 1, total_test_number);
    char *str = stringProvider(i);
    
    int sol = conta_doppie_soluzione(str);
    int stud = conta_doppie(str);
    
    printf("Input: %s \n", str);
    printf("Output atteso: %d \n", sol);
    
    printf("\n");

    if( checkResult(sol, stud))
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

    
  }

  printf("Percentuale di successo finale: %0.02f%%\n", (float)(successes) * 100.0f / (float)(total_test_number));
  
  
  return 0;
}


char * stringProvider(int i){
  char *str = (char *)(malloc(sizeof(char)*15));
  switch(i){

    case 0: str = "aabbcc"; break;
    case 1: str = "aa aa b"; break;
    case 2: str = "aaab"; break;
    case 3: str = "porro"; break;
    case 4: str = "soprattutto"; break;
    case 5: str = "arrtur"; break;
    case 6: str = "alLuce"; break;
    case 7: str = "aaHhKklL"; break;
    case 8: str = "tre"; break;
    case 9: str = "all l m m c"; break;
    
  }

  return str;
}
