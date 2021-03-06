package esercizio_2;
import esercizio_1.Esercizio_1;

public class Esercizio_2 {
	
	public static void main(String[] args) {
		System.out.println("Genero una matrice . . .\n");
		int[][] mat = generaMatrice(3 , 3);
		Esercizio_1.stampaMatrice(mat);
		System.out.println();
		
		System.out.println("Applico differenzaVicini . . .\n");
		
		int[][] mat1 = differenzaVicini(mat);
		Esercizio_1.stampaMatrice(mat1);
		
	}
	
	public static int [][] generaMatrice(int n, int m) {
		int [][] mat = new int [n][m];
		for(int i = 0; i < mat.length; i++) {
			for(int j = 0; j < mat[0].length; j++) {
				mat[i][j] = (int) (100*Math.random());
			}
		}
		return mat;
	}
	
	private static boolean cellaInMatrice (int[][] mat, int i, int j) {
		if(i < mat.length && i >= 0 && j < mat[0].length && j >= 0) return true;
		else return false;
	}
	
	private static int sommaVicini(int[][] mat, int i, int j) {
		int somma = 0;
		for(int k = i-1; k <= i+1; k++) {
			for(int h = j-1; h <= j+1; h++) {
				if (cellaInMatrice(mat, k, h)) {
					somma = somma + mat[k][h];
				}
			}
		}
		return somma - mat[i][j];
	}
	
	public static int[][] differenzaVicini(int[][] mat){
		int r = mat.length;
		int c = mat[0].length;
		int[][] matReturn = new int [r][c];
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				matReturn [i][j] = mat[i][j] - sommaVicini(mat, i, j);

			}
		}
		return matReturn;
	}
}
