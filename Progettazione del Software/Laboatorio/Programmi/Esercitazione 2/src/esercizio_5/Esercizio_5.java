package esercizio_5;

import javax.swing.*;

public class Esercizio_5 {
	
	public static void main(String[] args) {
		
		int x1 = 0;
		int x2 = 0;
		
		String s1;
		String s2;
		
		s1 = JOptionPane.showInputDialog("Inserire prima stringa");
		s2 = JOptionPane.showInputDialog("Inserire seconda stringa");
		
		for(int i = 0; i< s1.length(); i++) {
			x1 = x1 + (int)s1.charAt(i);
		}
		
		for(int i = 0; i< s2.length(); i++) {
			x2 = x2 + (int)s2.charAt(i);
		}
		
		if(x1 > x2) {
			System.out.println("La stringa con il codice ASCII più alto è: " + s1);
		}
		else {
			System.out.println("La stringa con il codice ASCII più alto è: " + s2);
		}
	}
}
