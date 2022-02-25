package esercizio_3;

import java.util.*;

public class Esercizio_3 {
	public static void main (String[] args) {
		
		Scanner s = new Scanner(System.in);
		
		int anno = Integer.parseInt(s.nextLine());
		
		if(anno % 4 == 0 && anno % 100 != 0 || anno % 400 == 0) {
			System.out.println(anno + " è bisestile.");
		}
		else {
			System.out.println(anno + " non è bisestile.");
		}
	}
}
