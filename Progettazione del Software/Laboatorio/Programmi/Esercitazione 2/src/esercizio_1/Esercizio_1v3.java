package esercizio_1;

import java.util.*;

public class Esercizio_1v3 {
	public static void main(String[] args) {
		String s1;
		String s2;
		
		Scanner scan = new Scanner (System.in);
		s1 = scan.nextLine();
		s2 = scan.nextLine();
		
		System.out.println(s1.contains(s2) || s2.contains(s1));
	}

}