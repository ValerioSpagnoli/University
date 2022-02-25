package Servizi_Auto;

import Automobile.Automobile;
import Persona.Persona;

public class Servizi_Auto {
	
	//set colore
	public static void verniciatura(Automobile auto, String colore) {
		auto.setColore(colore);
	}
	
	//immatricolazione auto full
	public static Automobile immatricolazione_full(String tar, String modello, String colore, Persona p) {
		return new Automobile(tar, modello, colore, p);
	}
	
	//immatricolazione auto targa-modello-colore
	public static Automobile immatricolazione_tmc(String tar, String modello, String colore, Persona p) {
		return new Automobile(tar, modello, colore);
	}
	
	//immatricolazione auto targa-modello
	public static Automobile immatricolazione_tm(String tar, String modello, String colore, Persona p) {
		return new Automobile(tar, modello);
	}

	
}
