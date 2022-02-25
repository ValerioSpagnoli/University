#include<stdio.h>

/*

TEMPLATE DI FUNZIONI RICORSIVE PER ACCEDERE 
A TUTTI GLI ELEMENTI DI UNA STRUTTURA DATI
INDICIZZATA

void fn_r(FILE *f) {
  char c = fgetc(f);
  if (c==EOF) {
     // caso base
     ...
  }
  else {
     // caso ricorsivo
     ... c 
     fn_r(f);
  }
}


void fn_r(char *s) {
  if (*s=='\0') { // stringa vuota
     // caso base
     ...
  }
  else {
     // caso ricorsivo
     char c = *s; // primo carattere
     ... c ...
     fn_r(s+1);
  }

}


void fn_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     ...
  }
  else {
     // caso ricorsivo
     float c = v[0]; // prima componente
     ... c ...
     fn_r(v+1, n-1);
  }

}


// contatore
int fn_r(char *s) {
  if (*s=='\0') { // stringa vuota
     // caso base
     return 0;
  }
  else {
     // caso ricorsivo
     return 1 + fn_r(s+1);
  }
}



// contatore condizionato
int fn_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return 0;
  }
  else if (<condizione>) {
     // caso ricorsivo
     return 1 + fn_r(v+1, n-1);
  }
  else {
     // caso ricorsivo
     return 0 + fn_r(v+1, n-1);
  }

}


// accumulazione
float fn_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return <op_neutro>;
  }
  else {
     // caso ricorsivo
     float c = v[0];
     return c <op> fn_r(v+1, n-1);
  }

}



*/

// stampa una stringa
void strprint_r(const char *s) {
  if (*s=='\0') { // stringa vuota
     // caso base
     printf("\n");
  }
  else {
     // caso ricorsivo
     char c = *s; // primo carattere
     printf("%c", c); // stampa c
     strprint_r(s+1);
  }

}


// copia la stringa s in d
// s e d già allocate
void strcpy_r(char *d, const char *s) {
  if (*s=='\0') {
     // caso base
     *d = '\0';
  }
  else {
     // caso ricorsivo
     char c = *s;
     *d = c;
     strcpy_r(d+1,s+1);
  }

}


// lunghezza di una stringa
int strlen_r(char *s) {
  if (*s=='\0') { // stringa vuota
     // caso base
     return 0;
  }
  else {
     // caso ricorsivo
     return 1 + strlen_r(s+1);
  }
}


// stampa elementi di un array
void arrprint_r(const float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     printf("\n");
  }
  else {
     // caso ricorsivo
     float c = v[0]; // prima componente
     printf("%.2f ", c);
     arrprint_r(v+1, n-1);
  }
}


// copia elementi di un array v in un array w
// array già allocati
void arrcpy_r(float *w, const float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return;
  }
  else {
     // caso ricorsivo
     float c = v[0]; // prima componente
     w[0] = c;
     arrcpy_r(w+1, v+1, n-1);
  }

}


// calcola il numero di elementi positivi
int arrcntpos_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return 0;
  }
  else if (v[0]>0) {
     // caso ricorsivo
     return 1 + arrcntpos_r(v+1, n-1);
  }
  else {
     // caso ricorsivo
     return 0 + arrcntpos_r(v+1, n-1);
  }

}


// somma dei valori di un array
float arrsum_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return 0;
  }
  else {
     // caso ricorsivo
     float c = v[0];
     return c + arrsum_r(v+1, n-1);
  }
}


// verifica che tutti gli elementi sono positivi
// accumulazione su AND &&
bool arrallpos_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return true;
  }
  else {
     // caso ricorsivo
     float c = v[0];
     return (c>0) && arrallpos_r(v+1, n-1);
  }
}




// verifica esistenza di almeno un elemento negativo
// accumulazione su OR ||
bool arroneneg_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return false;
  }
  else {
     // caso ricorsivo
     float c = v[0];
     return (c<0) || arroneneg_r(v+1, n-1);
  }
}


float max(float a, float b) {
    return (a>b)?a:b;
}

// massimo valore in un array
// accumulazione su max
float arrmax_r(float *v, int n) {
  if (n==0) { // array vuoto
     // caso base
     return -999;  // valore più piccolo degli elementi dell'insieme
  }
  else {
     // caso ricorsivo
     float c = v[0];
     return max(c, arrmax_r(v+1, n-1));

/*   // soluzione alternativa
     float x = arrmax(v+1, n-1);
     if (c>x)
        return c;
     else
        return x;
*/
  }
}



// confronta due stringhe
// -1 : s precede t
//  0 : s è uguale a t
// +1 : s succcede t
int strcmp_r(const char *s, const char *t) {
  if (*s=='\0' && *t=='\0') { // stringhe s e t vuote
     // caso base
     return 0;
  }
  else if (*s=='\0' && *t!='\0') { // solo stringa s vuota
     // caso base
     return -1;
  }
  else if (*s!='\0' && *t=='\0') { // solo stringa t vuota
     // caso base
     return +1;
  }
  else {  // *s!='\0' && *t!='\0'
     
     if (s[0] < t[0]) {  // s[0] precede t[0]
        // caso base
        return -1;
     }
     else if (s[0] > t[0]) { // s[0] segue t[0]
        // caso base
        return +1;
     }
     else { // s[0] == t[0]
         // caso ricorsivo
         return strcmp_r(s+1,t+1);
     }
  }
}



// confronta due caratteri
// nota: '\0' < altri caratteri
int cmp(char c, char d) {
   if (c < d)
        return -1;
    else if (c > d)
        return +1;
    else // c == d
        return 0;
}

// operatore di confronto tra stringhe
int strcmp_op(int a, int b) {
  if (a<0)
    return a;
  else if (a>0)
    return a;
  else // a==0
    return b;
}

// confronta due stringhe
// -1 : s precede t
//  0 : s è uguale a t
// +1 : s succcede t
// accumulazione su strcmp_op
int strcmp2_r(const char *s, const char *t) {
  if (*s=='\0' || *t=='\0') { // una stringa vuota
     // caso base
     return cmp(s[0],t[0]);
  }
  else {
     // caso ricorsivo
     return strcmp_op (cmp(s[0],t[0]), strcmp2_r(s+1,t+1));
  }
}


int main() {

  const char *s = "ciao";
  strprint_r(s);

  char t[10];

  strcpy_r(t,s);
  strprint_r(t);

  printf("%s %s\n" ,s,t);

  int l = strlen_r(t);
  printf("lunghezza stringa %s: %d\n", t,l);

  int na = 4;
  float a[] = { 1.1, 2.2, 4.109, -1.5 };
  float b[4];

  arrprint_r(a,na);
  arrcpy_r(b,a,na);
  arrprint_r(b,na);
  
  int npos = arrcntpos_r(a,na);
  printf("valori positivi in a: %d\n", npos);

  float asum = arrsum_r(a,na);
  printf("somma valori a: %.2f\n", asum);
  
  bool r = arrallpos_r(a,na);
  printf("tutti elementi di a positivi: %d\n", r);

  b[3] = -b[3];
  arrprint_r(b,na);

  r = arrallpos_r(b,na);
  printf("tutti elementi di b positivi: %d\n", r);

  r = arroneneg_r(a,na);
  printf("almeno un elemento di a negativo: %d\n", r);

  r = arroneneg_r(b,na);
  printf("almeno un elemento di b negativo: %d\n", r);


  float m = arrmax_r(a,na);
  printf("valore massimo di a: %.2f\n", m);

  const char *s0 = "";
  const char *s1 = "aa";
  const char *s2 = "aaa";
  const char *s3 = "b";

  printf("strcmp_r: %d %d %d\n",
      strcmp_r(s1,s2), strcmp_r(s2,s2), strcmp_r(s3,s2));

  printf("strcmp_r: %d %d %d\n",
      strcmp_r(s0,s2), strcmp_r(s3,s3), strcmp_r(s3,s0));

  printf("strcmp2_r: %d %d %d\n",
      strcmp2_r(s1,s2), strcmp_r(s2,s2), strcmp_r(s3,s2));

  printf("strcmp2_r: %d %d %d\n",
      strcmp2_r(s0,s2), strcmp_r(s2,s2), strcmp_r(s3,s0));

}


