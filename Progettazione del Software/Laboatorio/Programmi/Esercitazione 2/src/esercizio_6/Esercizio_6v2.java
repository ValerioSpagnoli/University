package esercizio_6;

import javax.swing.*;

public class Esercizio_6v2 {
	
	public static void main(String[] args) {
		int h = 0;
		int b = 0;
		
		while(h>=0 && b>=0) {

			h = Integer.parseInt(JOptionPane.showInputDialog("Inserire l'altezza del triangolo"));
			if(h<0) {
				JOptionPane.showMessageDialog(null ,"Hai inserito un numero negativo.");
				return;
			}

			b = Integer.parseInt(JOptionPane.showInputDialog("Inserire la base del triangolo"));
			if(b<0) {
				JOptionPane.showMessageDialog(null ,"Hai inserito un numero negativo.");
				return;
			}
			
			double Area = h * b;
			JOptionPane.showMessageDialog(null, "L'area del triangolo è: " + Area + " u^2 \n");
			
		}	
	}
}
