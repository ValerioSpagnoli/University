package main;
import scuola.Scuola;
import insegnante.Insegnante;
import classe.Classe;

public class Main {
	public static void main(String[] args) {
		
		Scuola scuola1 = new Scuola("ISIS Enrico Mattei", "Via Paolo Borsellino - Cerveteri", "Roma");
		
		Insegnante insegnante1 = new Insegnante("Mario", "Rossi", 1995, scuola1);
		Insegnante insegnante2 = new Insegnante("Luigi", "Impastato", 2002, scuola1);
		Insegnante insegnante3 = new Insegnante("Gennaro", "De Curtis", 1999, scuola1);
		
		Insegnante[] insegnanti1 = {insegnante1, insegnante2, insegnante3};

		
		Classe classe1 = new Classe("3^A", scuola1, insegnanti1, 24);

		scuola1.stampaScuola();
		classe1.stampaClasse();
		
		for(Insegnante ins : insegnanti1) {
			ins.stampaInsegnante();
		}
		
		
		
	}
}
