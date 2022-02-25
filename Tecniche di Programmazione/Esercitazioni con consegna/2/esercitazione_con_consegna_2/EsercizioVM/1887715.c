#include "esercizio_1.h"

int cm(Mat* src, int rr, int rc, int i, int j){
	int input = src->row_ptrs[i][j];
	if(input == -1){
		return -1;
		}
	else if(input == 0){
		int contatore = 0;
		for(int k=i-1; k<=i+1; k++){
			for(int p=j-1; p<=j+1; p++){
		 		if(k>=0 && k<rr && p>=0 && p<rc){
					if(src->row_ptrs[k][p]==-1){
						contatore = contatore + 1;
					}	
				}
			}
		}
	return contatore;
	}
}


Mat* campo_minato(Mat* src){
	int rig = src->rows, coln = src->cols;
	Mat *out = allocMatrix(rig, coln); 

	for(int i=0; i<rig; i++){
		for(int j=0; j<coln; j++){
		out->row_ptrs[i][j] = cm(src, rig, coln, i, j);
		}
	}	
	return out;
}
	

