
#pragma once
#include "e7_correttore.h"
#include "utils.h"
#include "functions.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
		
	printf("\n");

	//inizializza parametri stringhe
	char s[10] = "ASsfQg\0";
	char s_sol[10] = "ASsfQg\0";

	//check maiuscole
	bool check_minuscole_sol = _tuttiMinuscoli(s);
	bool check_minuscole = tuttiMinuscoli(s);
	check_minuscole ? printf("sono tutte minuscole\n") : printf("C'è almeno un carattere maiuscolo\n");
	printf("soluzione: ");
	check_minuscole_sol ? printf("sono tutte minuscole\n\n") : printf("C'è almeno un carattere maiuscolo\n\n");

	//converti maiuscole-minuscole
	_converti(s_sol);
	converti(s);
	printf("stringa convertita in caratteri minuscoli: %s\n", s);
	printf("soluzione: %s\n\n", s_sol);
       
	int vecs_size = 5;
	float vec1[5] = {5.7, 2.3, -3.6, 8.1, -0.1};

	char s_par[12] = "()ar[Z}az{\0";
	int num_parentesi_sol = _contaParentesi(s_par);
	int num_parentesi = contaParentesi(s_par);
	printf("ci sono %d parentesi \n", num_parentesi);
	printf("soluzione :");
	printf("%d \n\n", num_parentesi_sol);
		
	char dest[20] = "TDP è\0";
	char dest_sol[20] = "TDP è\0";
	char src[20] = " interessante\0";
	_concatenate(dest_sol, src);
	concatenate(dest, src);
	printf("stringa concatenata: %s\n", dest);
	printf("soluzione: ");
	printf("%s\n\n", dest_sol);

	float prodotto_res_sol = _prodotto(vec1, vecs_size);
	float prodotto_res = prodotto(vec1, vecs_size);
	printf("il prodotto è: %f\n", prodotto_res);
	printf("soluzione: ");
	printf(" %f\n\n", prodotto_res_sol);




        printf("*****************\n SCL\n*****************\n");
        printf("\nRandom SCL list created: \n");
        int list_size = 6;
        TipoSCL list = createRandomList(list_size);
        printList(list);
        
  
        printf("\nTest of SCL_media\n");
        float list_media = SCL_media(list);
        printf("media della lista: %.1f\n",list_media); 
        float list_media_sol = _SCL_media(list);
        printf("soluzione: %.1f\n",list_media_sol);

  
        printf("\nTest of SCL_integral\n");
        TipoNodoSCL* list_integrated = copyList(list);
        SCL_integral(list_integrated);
        printf("computed integrated list\n");
        printList(list_integrated);
        list_integrated = copyList(list);
        _SCL_integral(list_integrated);
        printf("soluzione\n");
        printList(list_integrated);
  
  
        printf("\nTest of SCL_dot\n");
        float list_dot_product = SCL_dot(list, list_integrated);
        printf("computed list dot product: %.1f\n",list_dot_product); 
        float list_dot_product_sol = _SCL_dot(list, list_integrated);
        printf("soluzione: %.1f\n",list_dot_product_sol);  
  
        freeList(list);
        freeList(list_integrated);

	return 0;

}
