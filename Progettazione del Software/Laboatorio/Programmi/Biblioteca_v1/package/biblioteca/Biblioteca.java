package biblioteca;

import persona.*;
import libro.Libro;
import java.io.*;
import java.util.*;


public class Biblioteca {
	
	//Costanti
	private static final int maxAutori = 100;
	private static final int maxLibri = 100;
	
	//Variabili di istanza (campi dati)
	private Persona[] elencoAutori;
	private Libro[] elencoLibri;
	
	//Costruttore
	public Biblioteca() {
		elencoAutori = new Persona[maxAutori];
		elencoLibri = new Libro[maxLibri];
	}
	
	//Metodi
	
	//Inserisci un nuovo libro
	public boolean inserisciLibro(Libro l) {
		boolean inserito = false;
		for(int i = 0; i < maxLibri && !inserito; i++) {
			if(elencoLibri[i] == null) {
				elencoLibri[i] = l;
				inserito = true;
			}
		}
		return inserito;
	}
	
	//Rimuovere un libro dato il titolo
	public void rimuoviLibro(String titolo) {
		boolean rimosso = false;
		for(int i = 0; i < maxLibri && !rimosso; i++) {
			if(elencoLibri[i] != null && elencoLibri[i].getTitolo().equals(titolo)) {
				elencoLibri[i] = null;
				rimosso = true;
			}
		}
	}
	
	//Inserisce autore a nell'elenco degli autori
	public void inserisciAutore(Persona a) {
		boolean inserito = false;
		for(int i = 0; i < maxAutori && !inserito; i++) {
			if(elencoAutori[i] == null) {
				elencoAutori[i] = a;
				inserito = true;
			}
		}
	}
	
	//Restituisce l'elenco dei libri di cui a è autore
	public Libro[] elencoAutore(Persona a) {
		Libro[] res = new Libro[maxLibri];
		int j = 0;
		for(int i = 0; i < maxLibri; i++) {
			if(elencoLibri[i] != null && isAutoreLibro(a, elencoLibri[i])) {
				res[j] = elencoLibri[i]; j++;
			}
		}
		return res;
	}
	
	//Verifica se a è autore del libro
	private boolean isAutoreLibro(Persona a, Libro l) {
		Persona[] aa = l.getAutori();
		boolean trovato = false;
		for(int i = 0; i<aa.length && !trovato; i++) {
			trovato = trovato || (aa[i].getCognome().equals(a.getCognome()) && aa[i].getNome().equals(a.getNome()));
		}
		return trovato;
	}
	
	// Stampa gli elenchi degli autori e dei libri
	public void stampaTabulato() {
		System.out.println("=== Elenco autori ===");
		stampaElencoAutori(elencoAutori);
		System.out.println("=== Elenco libri ===");
		stampaElencoLibri(elencoLibri);
	}

    // Stampa l'elenco di libri fornito in ingresso
	public void stampaElencoLibri(Libro[] elenco) {
		for (int i=0; i<elenco.length; i++) {
			if (elenco[i]!=null) {
				System.out.println(elenco[i]);
			}
		}	
	}

    // Stampa l'elenco di autori fornito in ingresso
	public void stampaElencoAutori(Persona[] elenco) {
		for (int i=0; i<elenco.length; i++) {
			if (elenco[i]!=null) {
				System.out.println(elenco[i]);
			}
		}	
	}

	// Legge gli autori da console fino a che non si digita stop
	public void leggiAutori() {	
		Scanner scan = new Scanner(System.in);
	   	String line = scan.nextLine();
		while (!line.equals("stop")) {
			Persona p = leggiPersona(line);
			inserisciAutore(p);
			line = scan.nextLine();
		}
	}

	// Legge i libri da console fino a che non si digita stop
	public void leggiLibri() {	
		Scanner scan = new Scanner(System.in);
	   	String line = scan.nextLine();
		while (!line.equals("stop")) {
			Libro l = leggiLibro(line);
			inserisciLibro(l);
			line = scan.nextLine();
		}
	}

	// Crea un oggetto Persona con i dati presenti nella stringa s
    // corrispondente ad una linea 
	private Persona leggiPersona(String s) {	
		StringTokenizer st = new StringTokenizer(s,";");
		String nome = st.nextToken();
		String cognome = st.nextToken();
		Data dataNascita = new Data(st.nextToken());
		String nazionalita = st.nextToken();
		String residenza = st.nextToken();
		return new Persona(nome,cognome,dataNascita,nazionalita,residenza);

		}

	// Crea un oggetto Libro con i dati presenti nella stringa s
    // corrispondente ad una linea 
	private Libro leggiLibro(String s) {
		StringTokenizer st = new StringTokenizer(s,";");
		Persona[] autori = arrayPersone(st.nextToken());
		String titolo = st.nextToken();
		int annoPubblicazione = Integer.parseInt(st.nextToken());
		String editore = st.nextToken();
		double prezzo = Double.parseDouble(st.nextToken());
		return new Libro(autori,titolo,annoPubblicazione,editore,prezzo);
	}

	// Crea un array di oggetti Persona con i dati presenti nella stringa s
	// corrispondente ad una lista di cognomi separati da virgole
	private Persona[] arrayPersone(String s) {
        // restituisce un array di persone da un array di stringhe (cognomi) separate da virgole
		StringTokenizer st = new StringTokenizer(s,",");
		int n=st.countTokens();
		Persona[] a = new Persona[n];
		for (int i=0; i<n; i++) {
			String cognome = st.nextToken();
			a[i] = trovaPersona(cognome);  // se persona non presente a[i]=null
		}
		return a;
	}

	// Restituisce la persona con il dato cognome, oppure null se una persona con tale cognome non è presente nell'elenco degli autori
	public Persona trovaPersona(String cognome) {
        for (int i=0; i<elencoAutori.length; i++) {
			if (elencoAutori[i]!=null && elencoAutori[i].getCognome().equals(cognome)) {
				return elencoAutori[i];
			}
		}
		return null;
	}
		
}


























