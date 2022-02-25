package esercizio_4;

import javax.swing.*;

public class Esercizio_4 {
	
	public static void main(String [] args) {

		String s1;
		String s2;
		
		s1 = JOptionPane.showInputDialog("Inserire prima stringa");
		s2 = JOptionPane.showInputDialog("Inserire seconda stringa");
		
		int l1 = s1.length();
		int l2 = s2.length();
		
		System.out.println("Il rapporto s1/s2 = " + ((double)l1/(double)l2));
		
		
	}

}
