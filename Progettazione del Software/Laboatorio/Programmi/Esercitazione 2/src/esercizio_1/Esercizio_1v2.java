package esercizio_1;

import javax.swing.*;

public class Esercizio_1v2 {
	
	public static void main (String[] args) {
		
		String s1;
		String s2;
		
		s1 = JOptionPane.showInputDialog("Inserire prima stringa");
		if(s1 == null) return;
		
		s2 = JOptionPane.showInputDialog("Inserie seconda stringa");
		if(s2 == null) return;
		
		System.out.println(s1.contains(s2) || s2.contains(s1));
		
	}
}
