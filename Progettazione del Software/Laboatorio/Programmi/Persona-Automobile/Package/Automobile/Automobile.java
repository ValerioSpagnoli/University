package Automobile;
import Persona.Persona;
public class Automobile {
	
	//campi dati
	private String targa;
	private String modello;
	private String colore;
	private Persona proprietario;
	
	//costruttori
	
	//base
	public Automobile() {
		targa = "AA000AA";
		modello = null;
		colore = "Bianco";
		proprietario = new Persona("Concessionario");
	}
	
	//only targa
	public Automobile(String t) {
		targa = t;
		modello = null;
		colore = "Bianco";
		proprietario = new Persona("Concessionario");
	}
	
	//targa+modello
	public Automobile(String t, String m) {
		targa = t;
		modello = m;
		colore = "Bianco";
		proprietario = new Persona("Concessionario");
	}
	
	//targa+modello+colore
	public Automobile(String t, String m, String c) {
		targa = t;
		modello = m;
		colore = c;
		proprietario = null;
	}
	
	//full
	public Automobile(String t, String m, String c, Persona p) {
		targa = t;
		modello = m;
		colore = c;
		proprietario = p;
	}

	//campi funzione (possono essere settati solo colore e proprietario)
	
	public String getTarga() {
		return targa;
	}
	
	public String getModello() {
		return modello;
	}
	
	public String getColore() {
		return colore;
	}
	
	public Persona getProprietario() {
		return proprietario;
	}
	
	public void setColore(String nuovoColore) {
		colore = nuovoColore;
	}
	
	public void setProprietario(Persona nuovoProprietario) {
		proprietario = nuovoProprietario;
	}
	
}











