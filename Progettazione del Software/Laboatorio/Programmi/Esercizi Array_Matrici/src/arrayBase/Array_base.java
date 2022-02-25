package arrayBase;

import java.util.Arrays;

public class Array_base {
	
	public static void main(String[] args) {
		
		int [] array1; // dichiarazione - tipo[] nomeArray;
		
		array1 = new int[10]; // creazione -  nomeArray[] = new tipo[dimesione];
		
		int l = array1.length; // lunghezza - int variabile = nomeArray.length;
		
		for(int i = 0; i<l; i++) {
			array1[i] = i*i;
		}
		
		String a1 = Arrays.toString(array1); // Arrays.toString(nomeArray) - restituisce una stringa con la rappresentazione dell'array
		System.out.println("Array1 = " + a1 + "\n");
		
		int [] copiaArray1 = Arrays.copyOf(array1, array1.length); /* Arrays.copyOf(arrayDaCopiare, dimensioneArrayDaCopiare) - 
																	  restituisce la cpia dell'array passato come argomento   */
		String a1copia = Arrays.toString(copiaArray1);
		System.out.println("copiaArray1 = " + a1copia + "\n");
		
		int [] array2 = {3, 5, 1, 10, 2, 9, 7}; // dichiarazione con parentesi graffe - tipo[] = {elemento 1 , ... , elemento n};
		
		array2 = new int[] {10, 50, 23, 33, 11, 67}; /*dichiarazione su array esistente - 
													   nomeArrayEsistente = new tipo[] {elemento 1 , ... , elemento n};  */
		
		String a2 = Arrays.toString(array2);
		System.out.println("Array2 = " + a2 + "\n");
		
		Arrays.sort(array2); // Arrays.sort(array2) - ordina l'array passato per argomento secondo l'ordinamento prederfinito 
		
		String a2ordinato = Arrays.toString(array2);
		System.out.println("Array2ordinato = " + a2ordinato + "\n");
		
		int [] array3 = {1, 2, 3, 4, 5};
		
		int somma = 0;
		
		for(int e : array3) {  /*ciclo for migliorato - for(tipo i : array) i non è un numero, ma è il valore nella casella dell'array
		 						 scandita dal ciclo. In questo caso e = array3[i] in un ciclo for classico.*/
			somma = somma + e;
		}
		
		String a3 = Arrays.toString(array3);
		System.out.println("Array3 = " + a3 + "\nLa somma degli elementi di array3 è : " + somma);
			
	}
}
