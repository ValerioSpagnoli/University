package persona;

import java.util.StringTokenizer;


public class Persona {
	
	//campi dati
	
	private final String nome, cognome;
	private final Data dataNascita;
	private String nazionalità;
	private String residenza;
	
	//costruttore
	
	public Persona(String nome, String cognome, Data dataNascita, String nazionalità, String residenza) {
		super();
		this.nome = nome;
		this.cognome = cognome;
		this.dataNascita = dataNascita;
		this.nazionalità = nazionalità;
		this.residenza = residenza;
	}
	
	//metodi
	
	public String getNome() {
		return nome;
	}
	
	public String getCognome() {
		return cognome;
	}
	
	public Data getDataNascita() {
		return dataNascita;
	}
	
	public String getNazionalità() {
		return nazionalità;
	}
	
	public String getResidenza() {
		return residenza;
	}
	
	public void setNazionalità(String nazionalità) {
		this.nazionalità = nazionalità;
	}
	
	public void setResidenza(String residenza) {
		this.residenza = residenza;
	}
	
	public String toString() {
		String r = nome + ";" + cognome + ";" + dataNascita.giorno + "/" + dataNascita.mese + "/" + dataNascita.anno + ";" +
				   nazionalità + ";" + residenza;
		return r;
	}
	
}
	
	
	
	
	
	
	
	







