#include <stdio.h>

// Stampa tutti i naturali i t.c. n>=i>=1 in ordine decrescente
void print_dec(int n){
	if (n < 1){//Passo base
		return;
	}
	printf("%d ", n);
	print_dec(n-1); // Passo ricorsivo
}

// Stampa tutti i naturali i t.c. n>=i>=1 in ordine crescente
void print_inc(int n){
	if (n < 1){//Passo base
		return;
	}
	print_inc(n-1);//Passo ricorsivo
	printf("%d ", n);
}

// Stampa tutti i naturali i t.c. n>=i>=1 in ordine decrescente, quindi crescente
void print_dec_inc(int n){
	if (n < 1){//Passo base
		return;
	}
	printf("%d ", n);
	print_dec_inc(n-1);//Passo ricorsivo
	printf("%d ", n);
}

int main(){
	printf("print_dec():\n");
	print_dec(10);
	printf("\n");
	printf("print_inc():\n");
	print_inc(10);
	printf("\n");
	printf("print_dec_inc():\n");
	print_dec_inc(10);
	printf("\n");
}
