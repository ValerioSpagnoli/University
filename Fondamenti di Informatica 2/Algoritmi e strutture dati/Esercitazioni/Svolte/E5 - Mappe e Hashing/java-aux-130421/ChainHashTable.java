import java.util.LinkedList;
import java.util.ArrayList;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkedList per le liste di trabocco 
	// L'array table implementa la tabella hash
	private LinkedList<Entry> [] table;
	
	// Costruttori
	public ChainHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
	}
	public ChainHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
	}
	public ChainHashTable(int cap) {
		super(cap); // primo predefinito
	}
	public ChainHashTable() {
		super(); // capacità predefinita
	}
	
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
		table = new LinkedList[getCapacity()];
		for(int i = 0; i<getCapacity(); i++) table[i] = null;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		int h = hashFunction(k);
		LinkedList<Entry> l = table[h];
		for(int i = 0; i<l.size(); i++){
			if(l.get(i).getKey() == k) return l.get(i).getValue();
		}
		return -1;
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		if((size()/getCapacity()) >= getMaxLambda()) resize(2*getCapacity());
		int old = -1;
		int h = hashFunction(k);
		if(table[h] != null){
			LinkedList<Entry> l = table[h];
			boolean presente = false;
			for(int i = 0; i<l.size(); i++){
				if(l.get(i).getKey() == k){
					old = l.get(i).getValue();
					l.get(i).setValue(value);
					presente = true;
				}
			}
			if(presente == false){
				Entry e = new Entry(k, value);	
				table[h].add(e);
				incSize();
			}
		}
		else{
			Entry e = new Entry(k, value);
			table[h] = new LinkedList<>();
			table[h].add(e);
			incSize();
		}
		return old;
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		int old = -1;
		int h = hashFunction(k);
		LinkedList<Entry> l = table[h];
		for(int i = 0; i<l.size(); i++){
			if(l.get(i).getKey() == k){
				old = l.get(i).getValue();
				l.remove(i);
				decSize();
			}
		}
		return old;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		ArrayList<Entry> buf = new ArrayList<>();
		for(int i = 0; i<getCapacity(); i++){
			if(table[i] != null){
				for(int j = 0; j < table[i].size(); j++){
					buf.add(table[i].get(j));
				}
			}
		}
		return buf;
	}

}


