package insegnante;
import scuola.Scuola;

public class Insegnante {
	
	//campi dati
	
	private final String nome, cognome;
	private final int annoVincitaConcorso;
	private Scuola scuolaAppartenenza;
	
	//costruttore
	
	public Insegnante(String nome, String cognome, int annoVincitaConcorso, Scuola scuolaAppartenenza) {
		this.nome = nome;
		this.cognome = cognome;
		this.annoVincitaConcorso = annoVincitaConcorso;
		this.scuolaAppartenenza = scuolaAppartenenza;
	}
	
	//metodi
	
	public String getNome() {
		return nome;
	}

	public String getCognome() {
		return cognome;
	}
	
	public String getNomeCompleto() {
		return nome + " " + cognome; 
	}
	
	
	public int getAnnoVincitaConcorso() {
		return annoVincitaConcorso;
	}
	
	public Scuola getScuolaAppartenenza() {
		return scuolaAppartenenza;
	}
	
	public void setScuolaAppartenenza(Scuola nuovaScuolaAppartenenza) {
		scuolaAppartenenza = nuovaScuolaAppartenenza;
	}
	
	public void stampaInsegnante() {
		System.out.println("Stampo dati insegnante . . .");
		System.out.println("Insegnante: " + nome + " " + cognome + "\n" + 
							"Anno di vincita del concorso: " + annoVincitaConcorso + "\n" + 
							"Scuola di appartenenza: " + scuolaAppartenenza.getNome() + "\n");
	}
	
	public void stampaNomeInsegnante() {
		System.out.print(nome + " " + cognome);
	}
}











