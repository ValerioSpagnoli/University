#include "e6_correttore.h"

int main(int argc, char **argv) {
		
	printf("\n");

	//inizializza parametri stringhe
	char s[10] = "ASsfQg\0";
	char s_sol[10] = "ASsfQg\0";

	//calcolo lunghezza
	printf("input lunghezza: %s \n", s);
	int value_sol = _lunghezza(s);
	int value = lunghezza(s);
	printf("La stringa è lunga: %d\n", value);
	printf("soluzione: %d\n\n", value_sol);

	//check carattere
	char ch = 's';
	int index_sol = _char_in_posizione(s,ch);
	int index = char_in_posizione(s,ch);
	printf("input char_in_piszione: %s\t%c \n", s,ch);
	( index >= 0 ) ? printf("il carattere %c è presente in indice %d\n", ch, index) : printf("il carattere %c non è presente\n", ch);
	printf("soluzione: ");
	( index_sol >= 0 ) ? printf("il carattere %c è presente in indice %d\n\n", ch, index_sol) : printf("il carattere %c non è presente\n\n", ch);

	
	//vec_integral
	int vec_size = 10;
	float vec[10] = {3.1, -2.3, 5.8, 1.4, -0.3, 4.1, 9.1, -3.7, 2.9, -4.9};
	float vec_sol[10] = {3.1, -2.3, 5.8, 1.4, -0.3, 4.1, 9.1, -3.7, 2.9, -4.9};
	
	printf("input vec_integral: \n");
	vec_print(vec,vec_size);
	printf("\n");
	_vec_integral(vec_sol, 10);
	vec_integral(vec, 10);
	
	printf("risultato vec_inegral: \n");
	vec_print(vec, vec_size);
	printf("\n soluzione: \n");
	vec_print(vec_sol, vec_size);
	printf("\n");

	//vec_dot
	int vecs_size = 5;
	float vec1[5] = {5.7, 2.3, -3.6, 8.1, -0.1};
	float vec2[5] = {-5.2, 1.3, -2.1, 1.2, 0.1};
	printf("input prodotto scalare: \n");
	vec_print(vec1, 5);
	printf("\n");
	vec_print(vec2, 5);
	
	float vec_dot_result_sol = _vec_dot(vec1, vec2, vecs_size);
	float vec_dot_result = vec_dot(vec1, vec2, vecs_size);
	printf("\n il risultato del prodotto scalare è: %f\n", vec_dot_result);
	printf("\n soluzione: \n");
	printf("%f\n\n", vec_dot_result_sol);

	
	return 0;
}