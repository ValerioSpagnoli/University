package frame;

import java.awt.event.*;
import javax.swing.*;

public class Listener implements ActionListener{
	public final static String SOMMA = "Somma";
	public final static String DIFFERENZA = "Differenza";
	public final static String MOLTIPLICAZIONE = "Moltiplicazione";
	public final static String DIVISIONE = "Divisione";
	public final static String UGUALE = "Uguale";
	public final static String DELETE = "Delete";
	public final static String PUNTO = "Punto";
	
	private double risultato = 0;
	private int i = 0;
	private String operazione = "";
	private String numero = "";
	
	private Frame display;
	
	private String Tinserito = "";
	
	public Listener(Frame displayA) {
		this.display = displayA;
	}
	
	public void actionPerformed(ActionEvent e) {
				
		if(e.getActionCommand().equals(SOMMA)) {
			Tinserito = Tinserito + " + ";
			display.schermo.setText(Tinserito);
			operazione = "+";
		}
		else if(e.getActionCommand().equals(DIFFERENZA)) {
			Tinserito = Tinserito + " - ";
			display.schermo.setText(Tinserito);
			operazione = "-";
		}
		else if(e.getActionCommand().equals(MOLTIPLICAZIONE)) {
			Tinserito = Tinserito + " x ";
			display.schermo.setText(Tinserito);
			operazione = "x";
		}
		else if(e.getActionCommand().equals(DIVISIONE)) {
			Tinserito = Tinserito + " / ";
			display.schermo.setText(Tinserito);
			operazione = "/";
		}
		else if(e.getActionCommand().equals(PUNTO)) {
			
		}
		else if(e.getActionCommand().equals(UGUALE)) {
			Tinserito = Tinserito + " = " + risultato;
			display.schermo.setText(Tinserito);
			risultato = 0;
	
			}
		else if(e.getActionCommand().equals(DELETE)) {
			Tinserito = "";
			display.schermo.setText(Tinserito);
			risultato = 0;
			operazione = "";
			i = 0;
			numero = "";
			
		}
		else {
			if(i<1) {
				numero = numero + e.getActionCommand();
				double x = Double.parseDouble(numero);
				risultato = risultato + x;
				Tinserito = Tinserito + numero;
				display.schermo.setText(Tinserito);
				i = i+1;
			}
			else {
				if(operazione == "+") {
					numero = numero + e.getActionCommand();
					double x = Double.parseDouble(numero);
					Tinserito = Tinserito + numero;
					display.schermo.setText(Tinserito);
					risultato = risultato + x;
					i = 0;
					numero = "";
				}
				else if(operazione == "-") {
					double x = Double.parseDouble(e.getActionCommand());
					Tinserito = Tinserito + e.getActionCommand();
					display.schermo.setText(Tinserito);
					risultato = risultato - x;
					i = 0;
					numero = "";
				}
				else if(operazione == "x") {
					double x = Double.parseDouble(e.getActionCommand());
					Tinserito = Tinserito + e.getActionCommand();
					display.schermo.setText(Tinserito);
					risultato = risultato * x;
					i = 0;
					numero = "";
				}
				else if(operazione == "/") {
					double x = Double.parseDouble(e.getActionCommand());
					Tinserito = Tinserito + e.getActionCommand();
					display.schermo.setText(Tinserito);
					risultato = risultato / x;
					i = 0;
					numero = "";
				}
				else {
					numero = numero + e.getActionCommand();
					Tinserito = Tinserito + e.getActionCommand();
					display.schermo.setText(Tinserito);
					risultato = Double.parseDouble(numero);
				}
			}
		}	
	}
}











