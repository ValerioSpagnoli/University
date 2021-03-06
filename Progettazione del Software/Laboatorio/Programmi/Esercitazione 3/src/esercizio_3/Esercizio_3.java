package esercizio_3;
import esercizio_1.Esercizio_1;
import esercizio_2.Esercizio_2;

import java.util.*;

public class Esercizio_3 {
	
	public static void main(String[] args) {
		int r, c;
		Scanner scan = new Scanner(System.in);
		String line = scan.nextLine();
		StringTokenizer tk = new StringTokenizer (line, ",");
		
		r = Integer.parseInt(tk.nextToken());
		c = Integer.parseInt(tk.nextToken());
		
		int[][] mat = new int [r][c];
		
		for(int i = 0; i < r; i++) {
			line = scan.nextLine();
			tk = new StringTokenizer(line, ",");
			
			for(int j = 0; j < c; j++) {
				mat[i][j] = Integer.parseInt(tk.nextToken());
			}
		}
		
		Esercizio_1.stampaMatrice(mat);
		int[][] mat1 = Esercizio_2.differenzaVicini(mat);
		System.out.println();
		Esercizio_1.stampaMatrice(mat1);
		
		
		
	}

}
