package esercizio_1;

import java.util.Scanner;

public class Esercizio_1 {
	
	public static void main(String [] args) {
		int n;
		int m;
		
		Scanner scan = new Scanner(System.in);
		n = Integer.parseInt(scan.nextLine());
		m = Integer.parseInt(scan.nextLine());
		
		double[][] mat = generaMatrice(n, m);
		stampaMatrice(mat);
		
		double[] v = diagonale(mat);
		stampaArray(v);
		
		System.out.println("La somma è: " + sommaArray(v));
		
		
	}
	
	
	public static double [][] generaMatrice(int n, int m) {
		double [][] mat = new double [n][m];
		for(int i = 0; i < mat.length; i++) {
			for(int j = 0; j < mat[0].length; j++) {
				mat[i][j] = 100*Math.random();
			}
		}
		return mat;
	}
	
	
	public static void stampaMatrice(double[][] mat){
		
		/* for(riga : mat){
		 * 		for(e : riga){
		 * 			System.out.print(e + "\t");
		 * 		}
		 * 		System.out.println();
		 * }
		 */
		
		for(int i = 0; i < mat.length; i++) {
			for(int j = 0; j < mat[0].length; j++) {
				System.out.print(mat[i][j] + "\t");
			}
			System.out.println();
		}
	}
	
	public static void stampaMatrice(int[][] mat) {
		for(int [] riga : mat){
			 for(int e : riga){
			 		System.out.print(e + "\t");
			 	}
			 System.out.println();
		}
	}
	
	
	public static void stampaArray(double[] v) {
		
		/*	System.out.print("[   ");
		 *  for(e : v){
				System.out.print(e + "   ");
		 *  }
		 *  System.out.println("]");
		 */
		
		System.out.print("[   ");
		for(int i = 0; i < v.length; i++) {
			System.out.print(v[i] + "   ");
		}
		System.out.println("]");
	}
	
	
	public static double [] diagonale(double[][] mat) { 
		
		double[] v;
		
		if(mat.length > mat[0].length) {
			v = new double[mat[0].length];
			for(int i = 0; i < mat[0].length; i++) {
				for(int j = 0; j < mat.length; j++) {
					if(i == j) v[i] = mat[i][j];
				}
			}
		}
		
		else {
			v = new double[mat.length];
			for(int i = 0; i < mat.length; i++) {
				for(int j = 0; j < mat[0].length; j++) {
					if(i == j) v[i] = mat[i][j];
				}
			}
		}
		return v;
	}
	
	
	public static double sommaArray(double[] v) {
		double somma = 0;
		for(int i = 0; i < v.length; i++) {
			somma = somma + v[i];
		}
		return somma;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}







