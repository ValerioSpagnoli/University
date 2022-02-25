package libro;

import persona.Persona;

public class Libro {
	
	//campi dati
	
	private final Persona[] autori;
	private final String titolo;
	private final int annoPubblicazione;
	private String editore;
	private double prezzo;
	
	//costruttore
	
	public Libro(Persona[] autori, String titolo, int annoPubblicazione, String editore, double prezzo) {
		super();
		this.autori = autori;
		this.titolo = titolo;
		this.annoPubblicazione = annoPubblicazione;
		this.editore = editore;
		this.prezzo = prezzo;
	}
	
	//metodi
	
	public Persona[] getAutori() {
		return autori;
	}
	
	public String getTitolo() {
		return titolo;
	}
	
	public int getAnnoPubblicazione() {
		return annoPubblicazione;
	}
	
	public String getEditore() {
		return editore;
	}
	
	public double getPrezzo() {
		return prezzo;
	}
	
	public void setEditore(String editore) {
		this.editore = editore;
	}
	
	public void setPrezzo(double prezzo) {
		this.prezzo = prezzo;
	}
	
	public String toString() {
		
		String r = "";
		
		for(int i = 0; i < autori.length; i++) {
			r = r + autori[i].getCognome();
			if(i<autori.length-1) {
				r = r + ",";
			}
		}
		
		r = r + ";" + titolo + ";" + annoPubblicazione + ";" + editore + ";" + prezzo;
		return r;	
	}
	
}
