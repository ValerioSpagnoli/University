#include "esercizio_1.h"
#include <stdio.h>
#include <stdlib.h>

int conta_doppie(char *s){
	if(*s=='\0'){
		return 0;
	}
	else{
		if(*(s+1) != '\0'){
			if(*s == *(s+1) || *s == *(s+1) - 'A' + 'a' || *s == *(s+1) - 'a' + 'A') {
				return 1+ conta_doppie(s+1);
			}
			else{
				return conta_doppie(s+1);
			}
		}
		else{
			return conta_doppie(s+1);
		}
	}
}


