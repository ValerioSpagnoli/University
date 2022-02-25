package matriciBase;

public class Matrici_base {
	
	public static void main(String [] args) {
		
		int [][] matrice1; // dichiarazione - tipo [][] nomeMatrice;
		
		matrice1 = new int [3][3]; // creazione - nomeMatrice = new tipo[#righe][#colonne];
		
		int righe = matrice1.length;      // #righe   - int righe = nomeMatrice.length 
		int colonne = matrice1[0].length; // #colonne - int colonne = nomeMatrice[0].length
		
		for(int i = 0; i < righe; i++) {		// scansione per righe - riempimento matrice
			for(int j = 0; j < colonne; j++) {
				matrice1[i][j] = (i+1)*(j+1);
			}
		}
		
		for(int i = 0; i < righe; i++) {		// scansione per righe - stampa matrice
			for(int j = 0; j < colonne; j++) {
				System.out.print(matrice1[i][j] + " ");
			}
			System.out.println();
		}
		
		System.out.println();
		
		// Triangolo di Tartaglia (esempio colonne variabili)
		
		int [][] triangoloTartaglia = new int [10][];
		
		for (int i = 0; i < 10; i++) {
			triangoloTartaglia[i] = new int [i+1]; //creazione colonna ad ogni scansione di riga
			triangoloTartaglia[i][0] = 1; 
			triangoloTartaglia[i][i] = 1;
			for(int j = 1; j < i; j++) {
				triangoloTartaglia [i][j] = triangoloTartaglia[i-1][j-1] + triangoloTartaglia[i-1][j];
			}
		}
		
		for(int i = 0; i < triangoloTartaglia.length; i++) {		// scansione per righe - stampa con colonne variabili
			for(int j = 0; j < triangoloTartaglia[i].length; j++) {
				System.out.printf("%4d", triangoloTartaglia[i][j]);
			}
			System.out.println();
		}
		
	}
}
