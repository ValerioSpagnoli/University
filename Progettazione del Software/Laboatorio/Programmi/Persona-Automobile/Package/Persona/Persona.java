package Persona;
public class Persona {
	//campi dati (variabili di istanza)
	private String nome;
	private String residenza;
	
	//costruttori
	
	//costruttore base
	public Persona() { 
		nome = "Mario Rossi";
		residenza = null; 
	}
	
	//costruttore solo nome
	public Persona(String n) { 
		nome = n;
		residenza = null;
	}
	
	//costruttore nome-residenza
	public Persona(String n, String r) { 
		nome = n;
		residenza = r;
	}
	
	//campi funzione
	
	//prende il nome
	public String getNome() {
		return nome;
	}
	
	//prende la residenza
	public String getResidenza() {
		return residenza;
	}
	
	
	//prende una nuova residenza e cambia la precedente
	public void setResidenza(String nuovaResidenza) {
		residenza  = nuovaResidenza;
	}
	
}





