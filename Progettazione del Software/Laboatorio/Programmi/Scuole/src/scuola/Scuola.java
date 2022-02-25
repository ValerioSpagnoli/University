package scuola;

public class Scuola {
	
	//campi dati
	
	private final String nome, indirizzo, provveditorato;
	
	//costruttore
	
	public Scuola(String nome, String indirizzo, String provveditorato) {
		this.nome = nome;
		this.indirizzo = indirizzo;
		this.provveditorato = provveditorato;
	}
	
	//metodi 
	
	public String getNome() {
		return nome;
	}
	
	public String getIndirizzo() {
		return indirizzo;
	}
	
	public String getProvveditorato() {
		return provveditorato;
	}
	
	public void stampaScuola() {
		System.out.println("Stampo dati scuola . . .");
		System.out.println("Scuola: " + nome + "\n" + "Indirizzo: " + indirizzo + "\n" + "Provveditorato: " + provveditorato + "\n");
	}
	
}











