#include <stdio.h>
#include <stdlib.h>

#include "./libs/SCL/scl.c"
#include "./libs/INSIEMI/ins_scl.c"
#include "./libs/LISTE/lista_scl.c"
#include "./libs/CODE/coda_scl.c"
#include "./libs/PILE/pila_scl.c"
#include "./libs/ALBBIN/albbin.c"
#include "./libs/MATRICI/mat.c"

//IGNORARE WARNING STRINGHE: g++ -Wno-write-strings -o main main.c



//------------------------------------------------------------------------------//
//----------------------------------- ESAME 0 ----------------------------------//
//------------------------------------------------------------------------------//


void comprimiSCL(TipoSCL* scl){
	if(emptySCL(*scl)) return;
	else{
		if((*scl)->next != NULL){
			if((*scl)->next->info > (*scl)->info){
				(*scl)->info = (*scl)->info + (*scl)->next->info;
				delSCL(&((*scl)->next));
				comprimiSCL(&((*scl)));
			}
			else{
				comprimiSCL(&((*scl)->next));
			}
		}
	}
}
//------------------------------------------------------------------------------//
void nodiMinori(TipoAlbero a, Insieme* ins){
	if(estVuoto(a)) return;
	else {
		if(sinistro(a) != NULL && destro(a) != NULL){
			if(radice(a) <= radice(sinistro(a)) + radice(destro(a))){
				inserisci(ins, radice(a));
			}
			nodiMinori(sinistro(a), ins);
			nodiMinori(destro(a), ins);
		}
		else if(sinistro(a) == NULL && destro(a) != NULL){
			if(radice(a) <= radice(destro(a))){
				inserisci(ins, radice(a));
			}
			nodiMinori(destro(a), ins);
		}
		else if(sinistro(a) != NULL && destro(a) == NULL){
			if(radice(a) <= radice(sinistro(a))){
				inserisci(ins, radice(a));
			}
			nodiMinori(sinistro(a), ins);
		}
		else if(sinistro(a) == NULL && destro(a) == NULL){
			if(radice(a) <= 0){
				inserisci(ins, radice(a));
			}
		}
		else{
			nodiMinori(sinistro(a), ins);
			nodiMinori(destro(a), ins);
		}
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 1 ----------------------------------//
//------------------------------------------------------------------------------//


int max (int a, int b){
	if(a>b) return a;
	else return b;}

int massimoSCL(TipoSCL* scl){
	if(emptySCL(*scl)) return -99999;
	else return max((*scl)->info, massimoSCL(&((*scl)->next)));}

void inserisciMassimo(TipoSCL *scl){
	if(emptySCL(*scl)) addSCL(scl, 0);
	else addSCL(scl, massimoSCL(scl));
}

void anteponiMassimo(TipoSCL* scl){
	if(!emptySCL(*scl)){
		inserisciMassimo(scl);
		anteponiMassimo(&((*scl)->next->next));	
	}
}
//------------------------------------------------------------------------------//
Lista sinistroMinoreDestro(TipoAlbero a){
	Lista l = listaVuota();
	if(!estVuoto(a)){
		if(sinistro(a)!=NULL && destro(a)!=NULL){
			if(a->sinistro->info < a->destro->info){
				 l = cons(radice(a), l);
			}
			l = append(l, sinistroMinoreDestro(sinistro(a)));
			l = append(l, sinistroMinoreDestro(destro(a)));
		}
		else if(sinistro(a)==NULL && destro(a)!=NULL){	
			if(a->destro->info > 0){
				 l = cons(radice(a), l);
			}
			l = append(l, sinistroMinoreDestro(destro(a)));
		}
		else if(sinistro(a)!=NULL && destro(a)==NULL){
			if(a->sinistro->info < 0){
				 l = cons(radice(a), l);
			}
			l = append(l, sinistroMinoreDestro(sinistro(a)));
		}
	}
	return l;
}
//------------------------------------------------------------------------------//
Mat* sommaSudEst(Mat* m){
	Mat *r = mat_alloc(m->r, m->c);
	for(int i = 0; i< m->r; i++){
		for(int j = 0; j< m->c; j++){
			if(i < (m->r - 1) && j < (m->c - 1)){
				r->punt[i][j] = m->punt[i][j] + m->punt[i+1][j] + m->punt[i][j+1] + m->punt[i+1][j+1];
			}
			else if(i == (m->r - 1) && j < (m->c - 1)){
				r->punt[i][j] = m->punt[0][j] + m->punt[1][j] + m->punt[0][j+1] + m->punt[1][j+1];
			}
			else if(i < (m->r - 1) && j == (m->c -1)){
				r->punt[i][j] = m->punt[i][0] + m->punt[i+1][0] + m->punt[i][1] + m->punt[i+1][1];
			}
			
			else if(i == (m->r - 1) && j == (m->c -1)){
				r->punt[i][j] = m->punt[0][0] + m->punt[1][0] + m->punt[0][1] + m->punt[1][1];
			}
		}	
	}
	return r;
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 2 ----------------------------------//
//------------------------------------------------------------------------------//


Mat* mirror(Mat *m){
	Mat *r = mat_alloc(m->r, 2*(m->c));
	for(int i = 0; i< m->r; i++){
		for(int j = 0; j< m->c; j++){
			r->punt[i][j] = m->punt[i][j];
		}
	}
	for(int i = 0; i< m->r; i++){
		for(int j = m->c; j< r->c; j++){
			r->punt[i][j] =  r->punt[i][(r->c) - j - 1];
		}
	}
	return r;
}
//------------------------------------------------------------------------------//
int sommaCoda(TipoSCL scl){
	if(scl->next == NULL) return 0;
	else{
		return (scl->next->info) + sommaCoda(scl->next);
	}
}

void eliminaTuttiSommaValori(TipoSCL* scl){
	if(!emptySCL(*scl)){
		if((*scl)->info < sommaCoda(*scl)){
			delSCL(scl);
			eliminaTuttiSommaValori(scl);
		}
		else{
			eliminaTuttiSommaValori(&(*scl)->next);
		}
	}
}
//------------------------------------------------------------------------------//
Lista foglieFratelli(TipoAlbero a){
	Lista l = listaVuota();
	if(estVuoto(a)) return listaVuota();
	else{
		if(sinistro(a) != NULL && estFoglia(sinistro(a)) && destro(a) != NULL && estFoglia(destro(a))){
			l = cons(sinistro(a)->info, l);
			l = cons(destro(a)->info, l);
			return l;
		}
		Lista s = foglieFratelli(sinistro(a));
		Lista d = foglieFratelli(destro(a));
		return append(s, d);		
	}	
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 3 ----------------------------------//
//------------------------------------------------------------------------------//


int isPalindrome(TipoNodoSCL* src){
	int dim = 0;
	TipoNodoSCL *p = src;
	while(p!=NULL){
		dim = dim+1;
		p = p->next;
	}
	char *c = (char*)malloc(dim*sizeof(char));
	p = src;
	for(int i = dim-1; i>=0; i--){
		c[i] = p->info;
		p = p->next;
	}
	p = src;
	int m = 1;
	for(int i = 0; i<dim; i++){
		if(c[i] != p->info){
			m = 0;
		}
		p = p->next;
	}
	free(c);
	return m;
}
//------------------------------------------------------------------------------//
typedef struct MatList {
		Mat* m;
		struct MatList* next;
	}MatList; 

MatList* add_lista(MatList* l, Mat* r){
	MatList* l1 = (MatList*)malloc(sizeof(MatList));
	l1->m = r;
	l1 -> next = l;
	return l1;
}

MatList* matrixRealization(int r_c_sum, int e){
	MatList* l = (MatList*)malloc(sizeof(MatList));
	for(int i = 1; i < r_c_sum; i++){
		Mat* r = mat_alloc(r_c_sum - i, i);	
		for(int j = 0; j < r->r; j++){
			for(int k = 0; k < r->c; k++){
				r->punt[j][k] = e;
			}
		}
		l = add_lista(l, r);
	}
	return l;
}
//------------------------------------------------------------------------------//
void removeChar( char *input_s, char c, char* output_s ){
	int i = 0;
	int j = 0;
	while(input_s[i] != '\0'){	
		if(input_s[i] == c){
			i = i+1;
		}
		else{
			output_s[j] = input_s[i];
			i = i+1;
			j = j+1;
		}
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 4 ----------------------------------//
//------------------------------------------------------------------------------//


void trasforma( Mat* m, int* v){
	int i = 0;
	while(i < m->r){
		int j = i;
		int k = 0;
		int s = 0;	
		while(j < m->r){
			s = s + m->punt[j][k];
			k = k+1;
			j = j+1;
		}
		v[i] = s;
		i = i + 1;
	}
}
//------------------------------------------------------------------------------//
TipoSCL subset(TipoSCL scl){
	if(emptySCL(scl)) return NULL;
	else{
		TipoSCL r = NULL;
		while(scl->next != NULL){
			if(scl->next->info < scl->info){
				addSCL(&r, scl->info);
				scl = scl->next;
			}
			else{
				scl = scl->next;
			}
		}
		addSCL(&r, scl->info);
		invertiSCL(&r);
		return r;
	}
}
//------------------------------------------------------------------------------//
void aus_maxSCL1_SCL2(TipoSCL scl1, TipoSCL scl2, TipoSCL *r){
	if( scl1 != NULL){
		if(scl1->info > scl2->info){
			addSCL(&(*r), scl1->info);
		}
		else{
			addSCL(&(*r), scl2->info);
		}
		aus_maxSCL1_SCL2(scl1->next, scl2->next, &((*r)->next));
	}
}

TipoSCL maxSCL1_SCL2(TipoSCL scl1, TipoSCL scl2){
	TipoSCL r = NULL;
	if(emptySCL(scl1)) return scl2;
	else if(emptySCL(scl2)) return scl1;
	else{
		aus_maxSCL1_SCL2(scl1, scl2, &r);
	}
	return r;	
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 5 ----------------------------------//
//------------------------------------------------------------------------------//


int mat_max(Mat* m){
	int c = 0;
	int k = 0;
	int mx = 0;
	for(int j = 0; j<m->c; j++){
		int s = 0;
		for(int i = 0; i<m->r; i++){
			s = s + m->punt[i][j];
		}
		if(s > mx){
			mx = s;
			c = j;
		}
	}
	int r = 0;
	for(int i = 0; i<m->r; i++){	
		r = max(r, m->punt[i][c]);
	}
	return r;
}
//------------------------------------------------------------------------------//
TipoSCL subSCL(TipoSCL scl){
	if(emptySCL(scl)) return NULL;
	else{
		TipoSCL r = NULL;
		addSCL(&r, scl->info);
		while(scl->next->next != NULL){
			if(scl->next->info < scl->info){
				addSCL(&r, scl->next->info);
				scl = scl->next;
			}
			else scl = scl->next;
		}
		invertiSCL(&r);
		return r;
	}
}
//------------------------------------------------------------------------------//
/*void aus_erase(TipoSCL scl, int index, TipoSCL *r, int i){
	if(scl != NULL){
		if(i!=index){
			addSCL(&(*r), scl->info);
			aus_erase(scl->next, index, &((*r)->next), i+1);
		}
		else{
			aus_erase(scl->next, index, &(*r), i+1);
		}
	}
	
}

TipoSCL erase(TipoSCL scl, int index){
	TipoSCL r = NULL;
	int i = 0;
	if(emptySCL(scl)) return NULL;
	else{
		aus_erase(scl, index, &r, i);
	}
	return r;
}*/

TipoSCL erase(TipoSCL scl, int index){
	TipoSCL r;
	if(scl == NULL) return NULL;
	else{
		r = erase(scl->next, index-1);
		if(index != 0){
			addSCL(&r, scl->info);
		}
		else{
			scl = scl->next;	
		}
		return r;
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 6 ----------------------------------//
//------------------------------------------------------------------------------//


Mat* matrixRepeat(Mat* m, int r, int c){
	int rr = r*r;
	int cc = c*c;
	Mat *mat = mat_alloc(rr, cc);
	int i = 0;
	int j = 0;
	for(i = 0; i<=rr-r; i=i+r){
		for(j = 0; j<=cc-c; j=j+c){
			for(int k = 0; k<r; k++){
				for(int q = 0; q<c; q++){
					mat->punt[i+k][q+j] = m->punt[k][q];
				}
			}
		}		
	}	
	
	return mat;
}
//------------------------------------------------------------------------------//
  
  //SCL 1 NON SVOLTO

//------------------------------------------------------------------------------//
TipoSCL squaredValues(TipoSCL scl1, TipoSCL scl2){
	if(scl1 == NULL || scl2 == NULL) return NULL;
	else{
			TipoSCL scl = squaredValues(scl1->next, scl2->next);
			int p = (scl1->info) *( scl2->info);
			addSCL(&scl, p);
			return scl;
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 7 ----------------------------------//
//------------------------------------------------------------------------------//


void matrix_compute_neighboor_sub(Mat* m1, Mat* m2){
	int rr = m1->r;
	int cc = m1->c;
	int s;
	for(int i = 0; i<rr; i++){
		for(int j = 0; j<cc; j++){
			//ANGOLI
			if(i == 0 && j == 0){
				s = m1->punt[i+1][j] + m1->punt[i+1][j+1] + m1->punt[i][j+1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(i == 0 && j == cc-1){
				s = m1->punt[i+1][j] + m1->punt[i+1][j-1] + m1->punt[i][j-1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(i == rr-1 && j == 0){
				s = m1->punt[i-1][j] + m1->punt[i-1][j+1] + m1->punt[i][j+1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(i == rr-1 && j == cc-1){
				s = m1->punt[i-1][j] + m1->punt[i-1][j-1] + m1->punt[i][j-1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			//SPIGOLI
			else if(i == 0 && j != 0 && j != cc-1){
				s = m1->punt[i][j-1] + m1->punt[i+1][j-1] + m1->punt[i+1][j] + m1->punt[i+1][j+1] + m1->punt[i][j+1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(j == 0 && i != 0 && i != rr-1){
				s = m1->punt[i-1][j] + m1->punt[i-1][j+1] + m1->punt[i][j+1] + m1->punt[i+1][j+1] + m1->punt[i+1][j];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(i == rr-1 && j != 0 && j != cc-1){
				s = m1->punt[i][j-1] + m1->punt[i-1][j-1] + m1->punt[i-1][j] + m1->punt[i-1][j+1] + m1->punt[i][j+1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			else if(j == cc-1 && i != 0 && i != rr-1){
				s = m1->punt[i-1][j] + m1->punt[i-1][j-1] + m1->punt[i][j-1] + m1->punt[i+1][j-1] + m1->punt[i+1][j];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
			//CENTRO
			else{
				s = m1->punt[i-1][j-1] + m1->punt[i-1][j] + m1->punt[i-1][j+1] + m1->punt[i][j-1] + m1->punt[i][j+1] + m1->punt[i+1][j-1] + 						 m1->punt[i+1][j] + m1->punt[i+1][j+1];
				m2->punt[i][j] = m1->punt[i][j] - s;
			}
		}
	}
}
//------------------------------------------------------------------------------//
TipoSCL merge_elements(TipoSCL scl1, TipoSCL scl2){
	TipoSCL scl = NULL;
	if(emptySCL(scl1)) return scl2;
	else if(emptySCL(scl2)) return scl1;
	else if(emptySCL(scl1) && emptySCL(scl2)) return NULL;
	else{
		while(scl1 != NULL && scl2 != NULL){
			if(scl1->info < scl2->info){
				addSCL(&scl, scl1->info);	
				scl1 = scl1->next;
			}
			else{
				addSCL(&scl, scl2->info);
				scl2 = scl2->next;
			}
		}
		if(scl1 == NULL){
			while(scl2->next != NULL){
				addSCL(&scl, scl2->info);
				scl2 = scl2->next;
			}
		}
		if(scl2 == NULL){
			while(scl1->next != NULL){
				addSCL(&scl, scl1->info);
				scl1 = scl1->next;
			}
		}
	}
	invertiSCL(&scl);
	return scl;
}
//------------------------------------------------------------------------------//
TipoSCL scl_multipliers(TipoSCL scl, int n){
	if(scl == NULL) return NULL;
	else{
		TipoSCL r = scl_multipliers(scl->next, n);
		if((scl->info) % n == 0){
			addSCL(&r, scl->info);
		}
		else{
			scl = scl->next;
		}
		return r;
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 8 ----------------------------------//
//------------------------------------------------------------------------------//


void mat_rotate_90_clockwise(Mat* m1, Mat* m2){
	for(int i = m1->r -1; i>=0; i--){
		for(int j = 0; j<m1->c; j++){
			m2->punt[j][m2->c-i-1] = m1->punt[i][j];
		}
	}	
}
//------------------------------------------------------------------------------//
TipoSCL fetch_elements(TipoSCL scl_pos, int* v, int dim){
	TipoSCL r = NULL;
	while((scl_pos) != NULL){
		int p = (scl_pos)->info;
		int e = v[p];
		addSCL(&r, e);
		(scl_pos) = (scl_pos)->next;
	}
	invertiSCL(&r);
	return r;
}
//------------------------------------------------------------------------------//
float recursive_norm(TipoSCL scl){
	int c;
	if(scl == NULL) return 0;
	else{
		float r = pow((scl->info), 2) + pow(recursive_norm(scl->next), 2);
		return sqrt(r);
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 9 ----------------------------------//
//------------------------------------------------------------------------------//


int matrix_block_sum(Mat* m1, Mat* m2, int r_start, int c_start){
	if(r_start + m2->r > m1->r || c_start + m2->c > m1->c) return 0;
	else{
		int s = 0;
		for(int i = 0; i<m2->r; i++){
			for(int j = 0; j<m2->c; j++){
				m1->punt[r_start + i][c_start + j] = m1->punt[r_start + i][c_start + j] + m2->punt[i][j];
				s = s+1;
			}
		}
		return s;
	}
}
//------------------------------------------------------------------------------//
/*TipoSCL lowerValues(Mat* m, int value){
	TipoSCL r = NULL;
	for(int i = 0; i<m->r; i++){
		for(int j = 0; j<m->c; j++){
			if(m->punt[i][j] < value){
				addSCL(&r, m->punt[i][j]);
			}
		}
	}
	invertiSCL(&r);
	return r;
}*/

TipoSCL lowerValues(Mat* m, int value){
	TipoSCL r = (TipoSCL)malloc(sizeof(TipoNodoSCL));
	r = NULL;
	for(int i = 0; i<m->r; i++){
		for(int j = 0; j<m->c; j++){
			if(m->punt[i][j] < value){
				TipoSCL n = newNode(m->punt[i][j]);
				TipoSCL temp = r;
				r = n;
				r->next = temp;
			}
		}
	}
	invertiSCL(&r);
	return r;
}
//------------------------------------------------------------------------------//
TipoSCL aus_compute_derivative(int* v, int dim, int i){
	TipoSCL scl;
	if(i == dim-1){
		return scl;
	}
	else{
		scl = aus_compute_derivative(v, dim, i+1);
		addSCL(&scl, v[dim-i-1]- v[dim -i-2]);
		return scl;
	}
}

TipoSCL compute_derivative(int* v, int dim){
	if(dim<2)return NULL;
	else{
		TipoSCL scl = aus_compute_derivative(v, dim, 0);
		invertiSCL(&scl);
		return scl;
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 10 ---------------------------------//
//------------------------------------------------------------------------------//


float mat_sum(Mat* m, int i, int j){
	float s = 0;
	for(int k = 0; k<=i; k++){
		for(int h = 0; h<=j; h++){
			s = s+ m->punt[k][h];
		}
	}
	return s;
}

int compute_diagonal_integral(float** v , Mat* m){
	float *vec = (float*)malloc((m->r)*sizeof(float));
	int i = 0;
	int j = 0;
	while(i<m->r){
		float s = mat_sum(m, i, j);
		vec[i] = s;
		i = i+1;
		j = j+1; 
	}
	printf("  VEC = [ ");
	for(int i=0; i<3; i++){
		printf("%.2f ", vec[i]);
	}
	printf("]\n\n");
	v = &vec;	
	return i;	
}
//------------------------------------------------------------------------------//
TipoSCL find_consecutivevalues(int* v, int dim){
	TipoSCL scl = NULL;
	for(int i = 0; i<dim-1; i++){
		if(v[i] == v[i+1]){
			addSCL(&scl, i);
		}
	}
	invertiSCL(&scl);
	return scl;
}
//------------------------------------------------------------------------------//
int compute_prefix_length(TipoSCL scl1, TipoSCL scl2){
	if(scl1 == NULL || scl2 == NULL){
		return 0;
	}
	else{
		if(scl1->info == scl2->info){
			return 1 + compute_prefix_length(scl1->next, scl2->next);
		}
		else{
			return compute_prefix_length(scl1->next, scl2->next);
		}
	}
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 11 ---------------------------------//
//------------------------------------------------------------------------------//


int aus_matrix_compute_integral(Mat* m, int i, int j){
	int s = 0;
	for(int k = 0; k <= i; k++){
		for(int h = 0; h <= j; h++){
			s = s + m->punt[k][h];
		}
	}
	return s;
}

void matrix_compute_integral(Mat* m1, Mat* m2){
	int s = 0;
	for(int i = 0; i< m1->r; i++){
		for(int j = 0; j<m1->c; j++){
			s = aus_matrix_compute_integral(m1 , i, j);
			m2->punt[i][j] = s;
		}
	}
}
//------------------------------------------------------------------------------//
TipoSCL find_transitions(int* v, int dim){
	TipoSCL scl = NULL;
	for(int i = 0; i<dim-1; i++){
		if(v[i] != v[i+1]){
			addSCL(&scl, i);
		}
	}
	invertiSCL(&scl);
	return scl;
}


//------------------------------------------------------------------------------//
//----------------------------------- ESAME 12 ---------------------------------//
//------------------------------------------------------------------------------//


int matrixBlockCopy(Mat* m1, Mat* m2, int row_start, int col_start){
	if(m2->r + row_start > m1->r || m2->c + col_start > m1->c ) return 0;
	else{
		int s = 0;
		for(int i = 0; i< m2->r; i++){
			for(int j = 0; j< m2->r; j++){
				s = s+1;
				m1->punt[i+row_start][j+col_start] = m2->punt[i][j];
			}
		}
		return s;
	}
}
//------------------------------------------------------------------------------//
int scl_lung(TipoSCL scl){
	if(scl == NULL) return 0;
	else return 1+scl_lung(scl->next);
}

int rotateList(int** v, TipoSCL scl, int num){
	int l = scl_lung(scl);
	int *vec = (int*)malloc(l*sizeof(int));
	int i = num;
	int j = 0;
	while(i < l){
		vec[i] = scl->info;
		scl = scl->next;
		i = i+1;
	}
	while(j<num){
		vec[j] = scl->info;
		scl = scl->next;
		j = j+1;
	}
	printf("  VEC = [ ");
	for(int i=0; i<7; i++){
		printf("%d ", vec[i]);
	}
	printf("]\n\n");
	v = &vec;	
	return l;
}
//------------------------------------------------------------------------------//
TipoSCL minElements(TipoSCL scl1, TipoSCL scl2){
	if(emptySCL(scl1) && emptySCL(scl2)) return NULL;
	else{
		TipoSCL scl = minElements(scl1->next, scl2->next);
		if(scl1->info <= scl2->info) addSCL(&scl, scl1->info);
		else addSCL(&scl, scl2->info);
		return scl;
	}
}
//------------------------------------------------------------------------------//
int main(){



	printf("\n**************************************************\n");
	printf("******************** ESAME 0 *********************");
	printf("\n****************** 03/06/2019 ********************\n");
	//ESERCITAZIONE IN MODALITA' ESAME 2018/2019.

	printf("\n--------------------- SCL ----------------------\n\n");

	TipoSCL scl_1 = NULL;
	addSCL(&scl_1, 10);
	addSCL(&scl_1, 7);
	addSCL(&scl_1, 1);
	addSCL(&scl_1, 4);
	addSCL(&scl_1, 5);
	addSCL(&scl_1, 3);
	printf("  SCL_1 = "); writeSCL(scl_1);
	printf("\n");
	comprimiSCL(&scl_1);
	printf("  SCL = "); writeSCL(scl_1);
//------------------------------------------------------------------------------//
	printf("\n-------------------- ALBERI --------------------\n\n");

	TipoAlbero g = creaAlbBin(9, NULL, NULL);
	TipoAlbero f = creaAlbBin(6, NULL, NULL);
	TipoAlbero e = creaAlbBin(-1, NULL, NULL);
	TipoAlbero d = creaAlbBin(4, f, NULL);
	TipoAlbero c = creaAlbBin(5, NULL, g);
	TipoAlbero b = creaAlbBin(7, d, e);
	TipoAlbero a = creaAlbBin(3, b, c);
	stampaParentetica(a);
	printf("\n\n");
	Insieme *ins = insiemeVuoto();
	nodiMinori(a, ins);
	printf("  Insieme = "); stampaInsieme(ins);


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 1 *********************");
	printf("\n****************** 12/06/2019 ********************\n");
	

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m = mat_alloc(3, 4);
	m->punt[0][0] = 1 ; m->punt[0][1] = 2 ; m->punt[0][2] = 3 ; m->punt[0][3] = 4 ;
	m->punt[1][0] = 5 ; m->punt[1][1] = 6 ; m->punt[1][2] = 7 ; m->punt[1][3] = 8 ;
	m->punt[2][0] = 0 ; m->punt[2][1] = 0 ; m->punt[2][2] = 0 ; m->punt[2][3] = 0 ;
	print(m);
	printf("\n");
	Mat* q = sommaSudEst(m);
	print(q);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	TipoSCL scl_2 = NULL;
	addSCL(&scl_2, 7);
	addSCL(&scl_2, 1);
	addSCL(&scl_2, 5);
	addSCL(&scl_2, 6);
	addSCL(&scl_2, 10);
	addSCL(&scl_2, 3);
	printf("  SCL = "); writeSCL(scl_2);
	printf("\n");
	inserisciMassimo(&scl_2);
	printf("  SCL = "); writeSCL(scl_2);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");

	TipoSCL scl_3 = NULL;
	addSCL(&scl_3, 7);
	addSCL(&scl_3, 1);
	addSCL(&scl_3, 5);
	addSCL(&scl_3, 6);
	addSCL(&scl_3, 10);
	addSCL(&scl_3, 3);
	printf("  SCL = "); writeSCL(scl_3);
	printf("\n");
	anteponiMassimo(&scl_3);
	printf("  SCL = "); writeSCL(scl_3);
//------------------------------------------------------------------------------//
	printf("\n-------------------- ALBERI --------------------\n\n");

	TipoAlbero n1 = creaAlbBin(12, NULL, NULL);
	TipoAlbero m1 = creaAlbBin(11, NULL, NULL);
	TipoAlbero l1 = creaAlbBin(10, NULL, NULL);
	TipoAlbero i1 = creaAlbBin(9, NULL, NULL);
	TipoAlbero h1 = creaAlbBin(8, NULL, NULL);
	TipoAlbero g1 = creaAlbBin(7, NULL, n1);
	TipoAlbero f1 = creaAlbBin(6, m1, NULL);
	TipoAlbero e1 = creaAlbBin(5, i1, l1);
	TipoAlbero d1 = creaAlbBin(4, h1, NULL);
	TipoAlbero c1 = creaAlbBin(3, f1, g1);
	TipoAlbero b1 = creaAlbBin(2, d1, e1);
	TipoAlbero a1 = creaAlbBin(1, b1, c1);
	stampaParentetica(a1);
	printf("\n\n");
	Lista l = sinistroMinoreDestro(a1);
	printf("  Lista = "); stampaLista(l); 

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 2 *********************");
	printf("\n****************** 10/07/2019 ********************\n");
	

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* w = mirror(m);
	print(w);	
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");
	
	TipoSCL scl_4 = NULL;
	addSCL(&scl_4, 2);
	addSCL(&scl_4, 1);
	addSCL(&scl_4, 4);
	addSCL(&scl_4, 2);
	addSCL(&scl_4, 10);
	addSCL(&scl_4, 1);
	printf("  SCL = "); writeSCL(scl_4);
	printf("\n");
	printf("  Somma_Coda = %d\n\n", sommaCoda(scl_4));
	eliminaTuttiSommaValori(&scl_4);
	printf("  SCL = "); writeSCL(scl_4);
//------------------------------------------------------------------------------//
	printf("\n-------------------- ALBERI --------------------\n\n");
	
	stampaParentetica(a1);
	printf("\n\n");
	Lista l2 = foglieFratelli(a1);
	printf("  Lista = "); stampaLista(l2); 

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 3 *********************");
	printf("\n****************** 17/01/2018 ********************\n");


	printf("\n--------------------- SCL  ---------------------\n\n");
	TipoSCL scl_char= NULL;
	addSCL(&scl_char, 'a');
	addSCL(&scl_char, 'n');
	addSCL(&scl_char, 'n');
	addSCL(&scl_char, 'a');
	printf("  SCL_1 = "); writeSCL_char(scl_char);
	printf("\n");
	int q1 = (isPalindrome(scl_char) == 1 ) ? printf("  ANNA è palindroma.\n\n") : 																printf("  ANNA non è palindroma.\n\n");
	TipoSCL scl_char1= NULL;
	addSCL(&scl_char1, 'o');
	addSCL(&scl_char1, 'i');
	addSCL(&scl_char1, 'r');
	addSCL(&scl_char1, 'e');	
	addSCL(&scl_char1, 'l');
	addSCL(&scl_char1, 'a');
	addSCL(&scl_char1, 'v');
	printf("  SCL_2 = "); writeSCL_char(scl_char1);
	printf("\n");
	int q2 = (isPalindrome(scl_char1) == 1 ) ? printf("  VALERIO è palindroma.\n") : 															 printf("  VALERIO non è palindroma.\n");
//------------------------------------------------------------------------------//
	printf("\n-------------------- MATRICI --------------------\n\n");
	MatList* l3 = matrixRealization( 6, 0);
	int i = 1;
	while(l3 != NULL && i<6){
		printf("  MatList Elem %d:\n\n", i);
		print(l3->m);
		i = i+1;
		l3 = l3->next;
	}
//------------------------------------------------------------------------------//
	printf("\n-------------------- STRINGHE --------------------\n\n");
	char* input_s = (char*)malloc(30*sizeof(char));
	input_s = "  Use gcc to compile your C programs.\0";
	i = 0;
	while(input_s[i] != '\0'){
		printf("%c", input_s[i]);
		i++;
	}
	printf("\n\n");
	char* output_s = (char*)malloc(30*sizeof(char));
	printf("  Applico removeChar ... \n\n");
	removeChar(input_s, 'c', output_s);
	i = 0;
	while(output_s[i] != '\0'){
		printf("%c", output_s[i]);
		i++;
	}
	printf("\n\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 4 *********************");
	printf("\n****************** 11/07/2018 ********************\n");
	
	printf("\n-------------------- MATRICI --------------------\n\n");	

	Mat* m2 = mat_alloc(3, 4);
	m2->punt[0][0] = 4 ; m2->punt[0][1] = 2 ; m2->punt[0][2] = 6 ; m2->punt[0][3] = 10 ;
	m2->punt[1][0] = 2 ; m2->punt[1][1] = 9 ; m2->punt[1][2] = 3 ; m2->punt[1][3] = 0 ;
	m2->punt[2][0] = 1 ; m2->punt[2][1] = 3 ; m2->punt[2][2] = 2 ; m2->punt[2][3] = 12 ;
	print(m2);

	int* v = (int*)calloc(3, sizeof(int));

	trasforma(m2, v);

	printf("  VEC = [ ");
	for(int i=0; i<3; i++){
		printf("%d ", v[i]);
	}
	printf("]\n");
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	TipoSCL scl_5 = NULL;
	addSCL(&scl_5, 30);
	addSCL(&scl_5, 40);
	addSCL(&scl_5, 31);
	addSCL(&scl_5, 35);
	addSCL(&scl_5, 8);
	addSCL(&scl_5, 36);
	addSCL(&scl_5, 39);
	printf("  SCL = "); writeSCL(scl_5);
	printf("\n");
	scl_5 = subset(scl_5);
	printf("  Applico subset ... \n\n");
	printf("  SCL = "); writeSCL(scl_5);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");

	TipoSCL scl_6 = NULL;
	addSCL(&scl_6, -5);
	addSCL(&scl_6, 10);
	addSCL(&scl_6, -10);
	addSCL(&scl_6, 4);
	addSCL(&scl_6, -5);
	addSCL(&scl_6, -3);
	printf("  SCL 1 = "); writeSCL(scl_6);
	printf("\n");

	TipoSCL scl_7 = NULL;
	addSCL(&scl_7, -1);
	addSCL(&scl_7, -2);
	addSCL(&scl_7, 1);
	addSCL(&scl_7, -5);
	addSCL(&scl_7, -5);
	addSCL(&scl_7, 6);
	printf("  SCL 2 = "); writeSCL(scl_7);
	printf("\n");
	TipoSCL scl_8 = maxSCL1_SCL2(scl_6, scl_7);
	printf("  SCL risultato = "); writeSCL(scl_8);

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 5 *********************");
	printf("\n****************** 10/09/2018 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m3 = mat_alloc(3, 4);
	m3->punt[0][0] = 1 ; m3->punt[0][1] = 1 ; m3->punt[0][2] = 1 ; m3->punt[0][3] = 0 ;
	m3->punt[1][0] = 0 ; m3->punt[1][1] = 2 ; m3->punt[1][2] = 1 ; m3->punt[1][3] = 4 ;
	m3->punt[2][0] = 0 ; m3->punt[2][1] = 3 ; m3->punt[2][2] = 0 ; m3->punt[2][3] = 0 ;
	print(m3);
	printf("  Il valore massimo nella colonna a somma massima è: %d \n", mat_max(m3));
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	TipoSCL scl_9 = NULL;
	addSCL(&scl_9, 11);
	addSCL(&scl_9, 0);
	addSCL(&scl_9, 7);
	addSCL(&scl_9, 8);
	addSCL(&scl_9, 8);
	addSCL(&scl_9, 3);
	addSCL(&scl_9, 5);
	printf("  SCL = "); writeSCL(scl_9);
	printf("\n");
	printf("  Applico SubSCL ... \n\n");
	scl_9 = subSCL(scl_9);
	printf("  SCL = "); writeSCL(scl_9);
	//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");
	TipoSCL scl_10 = NULL;
	addSCL(&scl_10, 5);
	addSCL(&scl_10, 3);
	addSCL(&scl_10, 1);
	addSCL(&scl_10, 4);
	printf("  SCL = "); writeSCL(scl_10);
	printf("\n");
	scl_10 = erase(scl_10, 0);
	printf("  Applico erase ... \n\n");
	printf("  SCL = "); writeSCL(scl_10);


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 6 *********************");
	printf("\n****************** 23/01/2017 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");
	
	Mat* m4 = mat_alloc(2, 3);
	m4->punt[0][0] = 1 ; m4->punt[0][1] = 2 ; m4->punt[0][2] = 3 ; 
	m4->punt[1][0] = 1 ; m4->punt[1][1] = 3 ; m4->punt[1][2] = 1 ; 
	print(m4);
	Mat* m5 = matrixRepeat(m4,2,3);
	print(m5);
//------------------------------------------------------------------------------//
	//printf("\n--------------------- SCL 1 --------------------\n\n");
	//NON SVOLTO

//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");
	TipoSCL scl_11 = NULL;
	addSCL(&scl_11, 9);
	addSCL(&scl_11, 3);
	addSCL(&scl_11, 5);
	addSCL(&scl_11, 4);
	addSCL(&scl_11, 2);
	addSCL(&scl_11, 1);
	addSCL(&scl_11, 1);
	printf("  SCL 1 = "); writeSCL(scl_11);
	printf("\n");

	TipoSCL scl_12 = NULL;
	addSCL(&scl_12, 2);
	addSCL(&scl_12, 1);
	addSCL(&scl_12, 1);
	addSCL(&scl_12, 9);
	addSCL(&scl_12, 3);
	addSCL(&scl_12, 2);
	addSCL(&scl_12, 7);
	printf("  SCL 2 = "); writeSCL(scl_12);
	printf("\n");
	
	TipoSCL scl_13 = squaredValues(scl_11, scl_12);
	printf("  Applico squaredValues ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_13);

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 7 *********************");
	printf("\n****************** 17/06/2016 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m6 = mat_alloc(3, 6);
	m6->punt[0][0] = 3 ; m6->punt[0][1] = 4 ; m6->punt[0][2] = 3 ; m6->punt[0][3] = 3 ; m6->punt[0][4] = 4 ; m6->punt[0][5] = 2 ;
	m6->punt[1][0] = 4 ; m6->punt[1][1] = 4 ; m6->punt[1][2] = 1 ; m6->punt[1][3] = 0 ; m6->punt[1][4] = -3 ; m6->punt[1][5] = 3 ;
	m6->punt[2][0] = 3 ; m6->punt[2][1] = -4 ; m6->punt[2][2] = 1 ; m6->punt[2][3] = -2 ; m6->punt[2][4] = 1 ; m6->punt[2][5] = -2 ;
	print(m6);
	Mat* m7 = mat_alloc(3, 6);
	matrix_compute_neighboor_sub(m6, m7);
	printf("\n");
	print(m7);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	TipoSCL scl_14 = NULL;
	addSCL(&scl_14, 29);
	addSCL(&scl_14, 27);
	addSCL(&scl_14, 16);
	addSCL(&scl_14, 0);
	addSCL(&scl_14, -13);
	printf("  SCL 1 = "); writeSCL(scl_14);
	printf("\n");

	TipoSCL scl_15 = NULL;
	addSCL(&scl_15, 23);
	addSCL(&scl_15, 4);
	addSCL(&scl_15, 3);
	printf("  SCL 2 = "); writeSCL(scl_15);
	printf("\n");

	TipoSCL scl_16 = merge_elements(scl_14, scl_15);
	printf("  Applico merge_elements ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_16);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");
	TipoSCL scl_17 = NULL;
	addSCL(&scl_17, -4);
	addSCL(&scl_17, 3);
	addSCL(&scl_17, 0);
	addSCL(&scl_17, 5);
	addSCL(&scl_17, -6);
	addSCL(&scl_17, 8);
	addSCL(&scl_17, 7);
	addSCL(&scl_17, -6);
	addSCL(&scl_17, 9);
	addSCL(&scl_17, -9);
	printf("  SCL = "); writeSCL(scl_17);
	printf("\n");

	TipoSCL scl_18 = scl_multipliers(scl_17, 4);
	printf("  Applico scl_multipliers ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_18);
	
	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 8 *********************");
	printf("\n****************** 24/10/2016 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m8 = mat_alloc(4, 8);
	m8->punt[0][0] = 1 ; m8->punt[0][1] = 2 ; m8->punt[0][2] = 3 ; m8->punt[0][3] = 1 ; m8->punt[0][4] = 3 ; m8->punt[0][5] = 3 ; m8->punt[0][6] = 2 ; m8->punt[0][7] = 1 ;
	m8->punt[1][0] = 2 ; m8->punt[1][1] = 3 ; m8->punt[1][2] = 1 ; m8->punt[1][3] = 3 ; m8->punt[1][4] = 3 ; m8->punt[1][5] = 2 ; m8->punt[1][6] = 1 ; m8->punt[1][7] = 0 ;
	m8->punt[2][0] = 1 ; m8->punt[2][1] = 3 ; m8->punt[2][2] = 3 ; m8->punt[2][3] = 2 ; m8->punt[2][4] = 1 ; m8->punt[2][5] = 2 ; m8->punt[2][6] = 1 ; m8->punt[2][7] = 1 ;
	m8->punt[3][0] = 1 ; m8->punt[3][1] = 2 ; m8->punt[3][2] = 3 ; m8->punt[3][3] = 1 ; m8->punt[3][4] = 3 ; m8->punt[3][5] = 3 ; m8->punt[3][6] = 2 ; m8->punt[3][7] = 1 ;
	print(m8);

	Mat* m9 = mat_alloc(8, 4);
	mat_rotate_90_clockwise(m8, m9);
	printf("  Applico mat_rotate_90_clockwise ...\n\n");
	print(m9);

//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");
	
	TipoSCL scl_19 = NULL;
	addSCL(&scl_19, 3);
	addSCL(&scl_19, 0);
	addSCL(&scl_19, 3);
	addSCL(&scl_19, 0);
	addSCL(&scl_19, 5);
	addSCL(&scl_19, 1);
	printf("  SCL = "); writeSCL(scl_19);
	printf("\n");
	
	int v1[6]; v1[0] = 2; v1[1] = -3; v1[2] = 2; v1[3] = -1; v1[4] = 4; v1[5] = 3;
	printf("  VEC = [ ");
	for(int i=0; i<6; i++){
		printf("%d ", v1[i]);
	}
	printf("]\n");
	printf("\n");
	TipoSCL scl_20 = fetch_elements(scl_19, v1, 6);
	printf("  Applico fetch_elements ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_20);
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");

	TipoSCL scl_21 = NULL;
	addSCL(&scl_21, 2);
	addSCL(&scl_21, -4);
	addSCL(&scl_21, 5);
	addSCL(&scl_21, 3);
	addSCL(&scl_21, -7);
	addSCL(&scl_21, -2);
	printf("  SCL = "); writeSCL(scl_21);
	printf("\n");

	printf("  La norma di SCL è : %f\n", recursive_norm(scl_21)); 

	printf("\n");
	

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************** ESAME 9 *********************");
	printf("\n****************** 16/09/2016 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m10 = mat_alloc(8, 8);
	m10->punt[0][0] = 1 ; m10->punt[0][1] = 2 ; m10->punt[0][2] = 3 ; m10->punt[0][3] = 1 ; m10->punt[0][4] = 3 ; m10->punt[0][5] = 3;m10->punt[0][6] = 2;m10->punt[0][7] = 1;
	m10->punt[1][0] = 2 ; m10->punt[1][1] = 3 ; m10->punt[1][2] = 1 ; m10->punt[1][3] = 3 ; m10->punt[1][4] = 3 ; m10->punt[1][5] = 2;m10->punt[1][6] = 1;m10->punt[1][7] = 0;
	m10->punt[2][0] = 1 ; m10->punt[2][1] = 3 ; m10->punt[2][2] = 3 ; m10->punt[2][3] = 2 ; m10->punt[2][4] = 1 ; m10->punt[2][5] = 2;m10->punt[2][6] = 1;m10->punt[2][7] = 1;
	m10->punt[3][0] = 1 ; m10->punt[3][1] = 2 ; m10->punt[3][2] = 3 ; m10->punt[3][3] = 1 ; m10->punt[3][4] = 3 ; m10->punt[3][5] = 3;m10->punt[3][6] = 2;m10->punt[3][7] = 1;
	m10->punt[4][0] = 1 ; m10->punt[4][1] = 3 ; m10->punt[4][2] = 3 ; m10->punt[4][3] = 2 ; m10->punt[4][4] = 1 ; m10->punt[4][5] = 2;m10->punt[4][6] = 1;m10->punt[4][7] = 1;
	m10->punt[5][0] = 1 ; m10->punt[5][1] = 2 ; m10->punt[5][2] = 3 ; m10->punt[5][3] = 1 ; m10->punt[5][4] = 3 ; m10->punt[5][5] = 3;m10->punt[5][6] = 2;m10->punt[5][7] = 1;
	m10->punt[6][0] = 2 ; m10->punt[6][1] = 3 ; m10->punt[6][2] = 1 ; m10->punt[6][3] = 2 ; m10->punt[6][4] = 2 ; m10->punt[6][5] = 1;m10->punt[6][6] = 2;m10->punt[6][7] = 1;
	m10->punt[7][0] = 2 ; m10->punt[7][1] = 3 ; m10->punt[7][2] = 1 ; m10->punt[7][3] = 3 ; m10->punt[7][4] = 3 ; m10->punt[7][5] = 2;m10->punt[7][6] = 1;m10->punt[7][7] = 0;
	print(m10);

	Mat* m11 = mat_alloc(3, 3);
	m11->punt[0][0] = 5 ; m11->punt[0][1] = 4 ; m11->punt[0][2] = 7 ; 
	m11->punt[1][0] = 4 ; m11->punt[1][1] = 4 ; m11->punt[1][2] = 4 ;
	m11->punt[2][0] = 6 ; m11->punt[2][1] = 4 ; m11->punt[2][2] = 6 ;
	print(m11);
	int r_start = 2;
	int c_start = 2;
	printf("  Il numeri sommati sono ... %d\n\n", matrix_block_sum(m10, m11, r_start, c_start));
	printf("  e la matrice m1 è stata modificata ...\n\n");
	print(m10);

	//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	Mat* m12 = mat_alloc(2, 3);
	m12->punt[0][0] = 3 ; m12->punt[0][1] = 1 ; m12->punt[0][2] = 2 ; 
	m12->punt[1][0] = 1 ; m12->punt[1][1] = 3 ; m12->punt[1][2] = 4 ;
	print(m12);
	
	TipoSCL scl_22 = lowerValues(m12, 3);
	printf("  Applico lowerValues ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_22);

	//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");
	
	int v2[9]; v2[0] = 7; v2[1] = 6; v2[2] = -5; v2[3] = 5; v2[4] = 5; v2[5] = -4; v2[6] = 4; v2[7] = 4; v2[8] = -7;
	printf("  VEC = [ ");
	for(int i=0; i<9; i++){
		printf("%d ", v2[i]);
	}
	printf("]\n");
	printf("\n");

   TipoSCL scl_23 = compute_derivative(v2, 9);
	printf("  Applico compute_derivative ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_23);
	
	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************* ESAME 10 *********************");
	printf("\n***************** 08/07/2016 A *******************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m13 = mat_alloc(3, 3);
	m13->punt[0][0] = 3 ; m13->punt[0][1] = 4 ; m13->punt[0][2] = 3 ; 
	m13->punt[1][0] = 4 ; m13->punt[1][1] = 4 ; m13->punt[1][2] = 1 ;
	m13->punt[2][0] = 3 ; m13->punt[2][1] = -4 ; m13->punt[2][2] = 1 ;
	print(m13);
	
	float* v3;
	printf("  La dimensione dell'array è: %d\n", compute_diagonal_integral(&v3, m13));

//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	int v4[10]; v4[0] = 0; v4[1] = 0; v4[2] = 0; v4[3] = 1; v4[4] = 1; v4[5] = 1; v4[6] = 0; v4[7] = 1; 
					v4[8] = 0; v4[9] = 0;
	
	printf("  VEC = [ ");
	for(int i=0; i<10; i++){
		printf("%d ", v4[i]);
	}
	printf("]\n");
	printf("\n");
	TipoSCL scl_24 =  find_consecutivevalues(v4, 10);
	printf("  Applico find_consecutivevalues ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_24);

//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");

	TipoSCL scl_25 = NULL;
	addSCL(&scl_25, 1);
	addSCL(&scl_25, 9);
	addSCL(&scl_25, 7);
	addSCL(&scl_25, 5);
	printf("  SCL 1 = "); writeSCL(scl_25);

	printf("\n");	

	TipoSCL scl_26 = NULL;
	addSCL(&scl_26, 2);
	addSCL(&scl_26, 13);
	addSCL(&scl_26, 11);
	addSCL(&scl_26, 9);
	addSCL(&scl_26, 7);
	addSCL(&scl_26, 5);
	printf("  SCL 2 = "); writeSCL(scl_26);
	printf("\n");	

	printf("  Il prefisso comune delle SCL è di %d elementi.\n", compute_prefix_length(scl_25, scl_26));

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************* ESAME 11 *********************");
	printf("\n***************** 08/07/2016 B *******************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	//USO MATRICE m6 DELL'ESAME 7 (17/06/2016)
	print(m6);
	Mat* m14 = mat_alloc(3, 6);
	matrix_compute_integral(m6, m14);
	printf("  Applico matrix_compute_integral ...\n\n");
	print(m14);
	
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	int v5[8]; v5[0] = 1; v5[1] = 1; v5[2] = 0; v5[3] = 0; v5[4] = 1; v5[5] = 1; v5[6] = 0; v5[7] = 1; 
	
	printf("  VEC = [ ");
	for(int i=0; i<8; i++){
		printf("%d ", v5[i]);
	}
	printf("]\n");
	printf("\n");	

	TipoSCL scl_27 = find_transitions(v5, 8);
	printf("  Applico find_transitions ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_27);

//------------------------------------------------------------------------------//
	//printf("\n--------------------- SCL 2 --------------------\n\n");
	
	//ESERCIZIO UGUALE A SCL 2 ESAME 9 (08/07/2016)

	printf("\n");


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


	printf("\n**************************************************\n");
	printf("******************* ESAME 12 *********************");
	printf("\n****************** 11/09/2015 ********************\n");

	printf("\n-------------------- MATRICI --------------------\n\n");

	Mat* m15 = mat_alloc(8, 8);
	m15->punt[0][0] = 1 ; m15->punt[0][1] = 2 ; m15->punt[0][2] = 3 ; m15->punt[0][3] = 1 ; m15->punt[0][4] = 3 ; m15->punt[0][5] = 3;m15->punt[0][6] = 2;m15->punt[0][7] = 1;
	m15->punt[1][0] = 2 ; m15->punt[1][1] = 3 ; m15->punt[1][2] = 1 ; m15->punt[1][3] = 3 ; m15->punt[1][4] = 3 ; m15->punt[1][5] = 2;m15->punt[1][6] = 1;m15->punt[1][7] = 0;
	m15->punt[2][0] = 1 ; m15->punt[2][1] = 3 ; m15->punt[2][2] = 3 ; m15->punt[2][3] = 2 ; m15->punt[2][4] = 1 ; m15->punt[2][5] = 2;m15->punt[2][6] = 1;m15->punt[2][7] = 1;
	m15->punt[3][0] = 1 ; m15->punt[3][1] = 2 ; m15->punt[3][2] = 3 ; m15->punt[3][3] = 1 ; m15->punt[3][4] = 3 ; m15->punt[3][5] = 3;m15->punt[3][6] = 2;m15->punt[3][7] = 1;
	m15->punt[4][0] = 1 ; m15->punt[4][1] = 3 ; m15->punt[4][2] = 3 ; m15->punt[4][3] = 2 ; m15->punt[4][4] = 1 ; m15->punt[4][5] = 2;m15->punt[4][6] = 1;m15->punt[4][7] = 1;
	m15->punt[5][0] = 2 ; m15->punt[5][1] = 3 ; m15->punt[5][2] = 1 ; m15->punt[5][3] = 2 ; m15->punt[5][4] = 2 ; m15->punt[5][5] = 1;m15->punt[5][6] = 2;m15->punt[5][7] = 1;
	m15->punt[6][0] = 1 ; m15->punt[6][1] = 2 ; m15->punt[6][2] = 3 ; m15->punt[6][3] = 1 ; m15->punt[6][4] = 3 ; m15->punt[6][5] = 3;m15->punt[6][6] = 2;m15->punt[6][7] = 1;
	m15->punt[7][0] = 2 ; m15->punt[7][1] = 3 ; m15->punt[7][2] = 1 ; m15->punt[7][3] = 3 ; m15->punt[7][4] = 3 ; m15->punt[7][5] = 2;m15->punt[7][6] = 1;m15->punt[7][7] = 0;
	print(m15);

	Mat* m16 = mat_alloc(3, 3);
	m16->punt[0][0] = 5 ; m16->punt[0][1] = 9 ; m16->punt[0][2] = 7 ; 
	m16->punt[1][0] = 9 ; m16->punt[1][1] = 9 ; m16->punt[1][2] = 9 ;
	m16->punt[2][0] = 8 ; m16->punt[2][1] = 9 ; m16->punt[2][2] = 6 ;
	print(m16);
	int row_start = 2;
	int col_start = 2;

	printf("  I numeri sostituiti nella matrice grande sono %d \n\n", matrixBlockCopy(m15, m16, row_start, col_start));
	printf("  e la matrice è modificata nel seguente modo ...\n\n");
	print(m15);

//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 1 --------------------\n\n");

	TipoSCL scl_28 = NULL;
	addSCL(&scl_28, 7);
	addSCL(&scl_28, 6);
	addSCL(&scl_28, 5);
	addSCL(&scl_28, 4);
	addSCL(&scl_28, 3);
	addSCL(&scl_28, 2);
	addSCL(&scl_28, 1);
	printf("  SCL = "); writeSCL(scl_28);
	printf("\n");	

	int *v6;
	printf("  La lughezza della lista e dell'array è: %d\n\n", rotateList(&v, scl_28, 2));
	
//------------------------------------------------------------------------------//
	printf("\n--------------------- SCL 2 --------------------\n\n");
	TipoSCL scl_29 = NULL;
	addSCL(&scl_29, 7);
	addSCL(&scl_29, 6);
	addSCL(&scl_29, 5);
	addSCL(&scl_29, 4);
	addSCL(&scl_29, 3);
	addSCL(&scl_29, 1);
	addSCL(&scl_29, 1);
	printf("  SCL 1 = "); writeSCL(scl_29);
	printf("\n");	

	TipoSCL scl_30 = NULL;
	addSCL(&scl_30, 2);
	addSCL(&scl_30, 1);
	addSCL(&scl_30, 1);
	addSCL(&scl_30, 9);
	addSCL(&scl_30, 3);
	addSCL(&scl_30, 2);
	addSCL(&scl_30, 7);
	printf("  SCL 2 = "); writeSCL(scl_30);
	printf("\n");	
	
	TipoSCL scl_31 = minElements(scl_29, scl_30);
	printf("  Applico minElements ...\n\n");
	printf("  SCL risultato = "); writeSCL(scl_31);

	printf("\n");
}
