import java.util.*;

public class Sort {

    /* Disponibile in libreria java */
    public void quickSortDefault(int[] array) {
        Arrays.sort(array);
    }

//####################################################################//
// MERGE SORT //

    public void mergeSort(int[] array) {
		if(array.length < 2) return;

		int mid = array.length/2;
		
		int L[] = Arrays.copyOfRange(array, 0, mid);
		int R[] = Arrays.copyOfRange(array, mid, array.length);		
		mergeSort(L);
		mergeSort(R);
		
		merge(array, L, R);
    }
    
    public void merge(int[] array, int[] L, int[] R){
		int i = 0, j = 0;
		while(i < L.length && j < R.length){
			if(L[i] < R[j]) array[i+j] = L[i++];
			else array[i+j] = R[j++];
		}	
		
		if(i >= L.length && j < R.length){
			while(j<R.length) array[i+j] = R[j++];
		}
		else if(j >= R.length && i < L.length){
			while(i<L.length) array[i+j] = L[i++];
		}
	
	}

//####################################################################//
// HEAP SORT //

/*
    public void heapSort(int[] array) {
		Heap heap = Heap.array2heap(array, Heap.HEAP_TYPE.MIN_HEAP);
		for(int i = 0; i<array.length; i++){
			array[i] = heap.poll();
		}
    }
*/ 

// HEAP SORT IN-PLACE    
    
    public void heapify(int[] array){	//costruzione heap-max da array
		int size = array.length;
		int start = (size-2)/2;
		for(int i = start; i>=0; i--){
			downHeap(array, i, size);
		}
	}
    
    public void downHeap(int[] array, int i, int size){  //mantere ordinamento
		while(2*i+1<size){
			int left = 2*i+1;
			int small = left;
			if(2*i+2<size){
				int right = 2*i+2;
				if(array[left] < array[right]){
					small = right;
				}
			}
			if(array[small] < array[i]) break;
			else{
				int temp = array[i];
				array[i] = array[small];
				array[small] = temp;
				i = small;
			}
		}
	}
    
    public void heapSort(int[] array) {
		heapify(array);					//costruzione heapMax da array, il valore massimo si trova nella radice (array[0])
		int n = array.length;			//Ad ogni passo scambia il valore della radice con quello in posizione j ed fa il	
		int j = n-1;				    //downHeap del valore messo nella radice.
		while(j>0){						//In questo modo al primo passo mette il valore massimo in ultima posizione, 
			int temp = array[0];		//poi diminuisce la dimensione dell'array su cui lavorare e prende il secondo
			array[0] = array[j];		//valore piu grande e lo mette in penultima posizione, ecc..
			array[j] = temp;
			n--;						
			downHeap(array, 0, n);		
			j--;						
		}
    }

//####################################################################//
// INSERTION SORT //


    public void insertionSort(int[] array) {
		for(int i = 1; i<array.length-1; i++){	//ciclo for per scansionare tutto l'array
			int k, j;			
			k = i;								//k identifica l'elemento precendente					
			j = i+1;							//j identifica l'elemento da ordinare
			while(k>=0){						//finchè k è maggiore di zero
				if(array[k] > array[j]){		//se array[k] > array[j] 
					int temp = array[k];		//scambio gli elementi, quindi l'elemento da ordinare si trova una posizione prima
					array[k] = array[j];		//quindi diminuisco k in modo che punta di nuovo all'elemnto precendente
					array[j] = temp;			//e diminusco j in modo che punta di nuovo all'elemento da ordinare 
					k--;
					j--;
				}
				else break;						//se array[k] <= array[j] l'ordinamento è rispettato e quindi si passa 
			}									//all'elemento successivo incrementando i
		}
    }

//####################################################################//
// SELECTION SORT //

    public void selectionSort(int[] array) {	 
		int min;
		for(int i = 0; i<array.length; i++){	//ciclo esterno scandisce l'array
			min = i;							//impostiamo l'indice del valore minimo ad i
			for(int j = i; j<array.length; j++){//con il ciclo interno cerchiamo l'effettivo indice del valore minimo
				if(array[j]<array[min]) min = j;
			}
			int temp = array[i];				//scambiamo quindi il valore puntato da i con il valore puntato dal minimo
			array[i] = array[min];				//e avanziamo di una posizione
			array[min] = temp;
		}
    }
    
//####################################################################//    

    public void quickSort(int[] array) {
		quickSortInPlace(array, 0, array.length-1);		
    }
    
    public void quickSortInPlace(int[] array, int a, int b){		
		if(a>=b) return;										//se a>=b, la porzione di array ha 1 o 0 elementi qundi è ordinata
		int left = a;											//indice sinistro = a
		int right = b-1;										//indice destro = b-1
		int pivot = array[b];									//pivot = ultimo elemento	
		int temp;
		
		while(left<=right){										//finchè left <= right
			while(left<=right && array[left] < pivot) left++;	//se left<=right e array[left] < pivot incrementa left di 1
			while(left<=right && array[right] > pivot) right--;	//se left<=right e array[right] > pivot decrementa right di 1
			if(left<=right){									//se left<=right scambia left con right e incrementa left di 1
				temp = array[left];								//e decrementa right di 1
				array[left] = array[right];
				array[right] = temp;
				left++;
				right--;	
			}		
		}
		
		temp = array[left];										//dato che left ha superato right, scambia left con il pivot
		array[left] = array[b];									//il pivot si trova al posto giusto
		array[b] = temp;
		quickSortInPlace(array, a, left-1);						//fai ricorsione sulla porzione dell'array a sinistra del pivot
		quickSortInPlace(array, left+1, b);						//fai ricorsione sulla porzione dell'array a destra del pivot
		
	}
  
//####################################################################//    

    public void radixSort(int[] array) {
		
    }
    
//####################################################################//    

    public void bucketSort(int[] array) {							//si assume che i valori nell'array siano compresi tra 0 e n
        int n = array.length;										//dove n è la lunghezza dell'array
        
        ArrayList<Integer>[] bucket = new ArrayList[n];				//viene creato un array contenente n = array.length sotto-array
        for(int i = 0; i < n; i++){
			bucket[i] = new ArrayList<Integer>();
		}
			
		for(int i = 0; i < n; i++){									//il valore di array[i], viene usato come indice e viene	
			int bucketIndex = array[i];								//inserito nel sotto-array indicizzato proprio dal valore di 	
			bucket[bucketIndex].add(bucketIndex);					//array[i]	
		}
		
		int index = 0;												//per ogni bucket nell'array, vengono estratti in ordine i valori
		for(int i = 0; i < n; i++){									//contenuti e rinseriti nell'array originario.	
			for(int j = 0, size = bucket[i].size(); j<size; j++){
				array[index++] = bucket[i].get(j);
			}
		}
		
         
        
        
        
    }
}
