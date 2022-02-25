#include "esercizio_1.h"
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
    
    int stud = conta_doppie(str);
    
    printf("Input: %s \n", str);
    printf("Output %d \n", stud);
    
    printf("\n******************************\n");

    
  }
  
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
