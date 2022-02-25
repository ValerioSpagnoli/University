package esercizio_6;

import java.util.*;

public class Esercizio_6v1 {
	
	public static void main(String[] args) {
		int h = 0;
		int b = 0;
		
		while(h>=0 && b>=0) {
			Scanner scan = new Scanner(System.in);
		
			System.out.print("Inserire l'altezza del triangolo: ");
			h = Integer.parseInt(scan.nextLine());
			if(h<0) {
				System.out.print("\nHai inserito un numero negativo.");
				return;
			}
		
			System.out.print("Inserire la base del triangolo: ");
			b = Integer.parseInt(scan.nextLine());
			if(b<0) {
				System.out.print("\nHai inserito un numero negativo.");
				return;
			}
			System.out.println("");
			
		
			double Area = h * b;
		
			System.out.println("L'area del triangolo è: " + Area + "\n");
		}	
	}
}
