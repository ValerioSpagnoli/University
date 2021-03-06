package Main;

import Persona.Persona;
import Automobile.Automobile;
import Servizi_Auto.Servizi_Auto;

public class Main {
	public static void main(String [] args) {
		
		Automobile a = new Automobile("FG 211 XW", "FIAT 500L");
		stampaDatiAuto(a);
		System.out.println("");
		
		System.out.println("Set proprietario automobile " + a.getTarga() + " . . . \n");
		
		Persona p1 = new Persona("Valerio Spagnoli", "Cerveteri");
		a.setProprietario(p1);
		stampaDatiAuto(a);
		System.out.println("");
		
		System.out.println("Verniciatura automobile " + a.getTarga() + " . . . \n");
		Servizi_Auto.verniciatura(a, "Verde");
		stampaDatiAuto(a);
		System.out.println("");
		
		Persona p2 = new Persona("Giuseppe Minetti", "Catanzaro");
		Automobile b = Servizi_Auto.immatricolazione_full("ZX 501 CY", "Renault Clio", "Grigio Metallizzato", p2);
		stampaDatiAuto(b);
	
	}
	
	public static void stampaDatiAuto(Automobile a) {
		System.out.println("Automobile: " + a.getTarga() + ", " + 
											a.getModello() + ", " +
											a.getColore() + ", " + 
											a.getProprietario().getNome());
	}
	
	public static void stampaDatiProprietario(Automobile a) {
		System.out.println("Proprietario: " + a.getProprietario().getNome() + ", " + 
											  a.getProprietario().getResidenza());
	}

}
