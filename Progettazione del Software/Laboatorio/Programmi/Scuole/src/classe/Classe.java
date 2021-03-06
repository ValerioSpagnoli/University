package classe;

import insegnante.Insegnante;
import scuola.Scuola;

public class Classe {
	
	//costanti
	private static final int numeroInsegnanti = 3;
	
	//campi dati 
	
	private final Scuola scuolaAppartenenza;
	private final String nome;
	private Insegnante[] insegnanti;
	private int numeroAlunni;
	
	//costruttore
	
	public Classe(String nome, Scuola scuolaAppartenenza, Insegnante[] insegnanti, int numeroAlunni) {
		this.nome = nome;
		this.scuolaAppartenenza = scuolaAppartenenza;
		this.insegnanti = insegnanti;
		this.numeroAlunni = numeroAlunni;
	}
	
	//metodi
	
	public String getNome() {
		return nome;
	}
	
	public Scuola getScuolaAppartenenza() {
		return scuolaAppartenenza;
	}
	
	public Insegnante[] getInsegnanti(){
		return insegnanti;
	}
	
	public int getNumeroAlunni() {
		return numeroAlunni;
	}
	
	
	//sostituisci insegnante
	public void sostituisciInsegnante(Insegnante insOut, Insegnante insIn) {
		boolean trovato = false;
		if(insegnanteInClasse(insOut)) {
			
			for(int i = 0; i < numeroInsegnanti && !trovato; i++) {
				if(insegnanti[i].equals(insOut)) {
					insegnanti[i] = null;
					insegnanti[i] = insIn;
					trovato = true;
				}
			}
			
		}
		else {
			System.out.println("Errore: l'insegnante da sostituire non fa parte di questa classe.");
		}
	}
	
	
	//verifica se insegnante ins appartiene a quella classe
	public boolean insegnanteInClasse(Insegnante ins) {
		boolean trovato = false;
		for(int i = 0; i < numeroInsegnanti && !trovato; i++) {
			if(insegnanti[i].equals(ins)) trovato = true;
		}
		return trovato;
	}
	
	public void stampaInsegnantiClasse(){
		for(Insegnante ins : insegnanti) {
			ins.stampaNomeInsegnante();
		}
	}
	
	
	//stampa i dati della classe
	public void stampaClasse() {
		System.out.println("Stampo dati classe . . .");
		System.out.print("Classe " + nome + "\n" + "Scuola: " + scuolaAppartenenza.getNome() + "\n" + "Insegnanti: ");
		for(Insegnante ins : insegnanti) {
			ins.stampaNomeInsegnante();
			System.out.print("   ");
		}
		System.out.println("\nNumero alunni: " + numeroAlunni);
		System.out.println();
		
	}
	
}







