import java.util.LinkedList;
import java.util.ArrayList;

public class OpenHashTable extends AbstractHashTable {
	// Un array di Entry per la tabella
	private Entry[] table;
	// marcatore di cella vuota ma da esaminare durante probing
	private final Entry DEFUNCT = new Entry(null, 0); 
	
	// Costruttori
	public OpenHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
	}
	public OpenHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
	}
	public OpenHashTable(int cap) {
		super(cap); // primo predefinito
	}
	public OpenHashTable() {
		super(); // capacità predefinita
	}
		
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
		table = new Entry[getCapacity()];
		for(int i = 0; i<getCapacity(); i++) table[i] = null;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		int h = hashFunction(k);
		if(table[h] != null){
			if(table[h].getKey() == k){
				return table[h].getValue();
			}
			else{
				int i = 0;
				int h1 = Math.abs((h + i*i)%getCapacity());
				while(table[h1] != null || table[h1] == DEFUNCT){
					if(table[h1].getKey() == k){
						return table[h1].getValue();
					}
					i++;
					h1 = Math.abs((h + i*i)%getCapacity());
				}
			}
		}
		return -1;	
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		if((size())/getCapacity() >= getMaxLambda()) resize(2*getCapacity());
		
		int old = -1;
		int h = hashFunction(k);
	
		if(table[h] != null){
			if(table[h].getKey() == k){
				old = table[h].getValue();
				table[h].setValue(value);
				return old;
			}
			else{
				int indexSlot = h;
				boolean findSlot = false;
				boolean findKey = false;
				int i = 0; 
				int h1 = Math.abs((h + i*i)%getCapacity());
				while(h1 < getCapacity() && table[h1] != null){
					if(table[h1].getKey() == k){
						old = table[h].getValue();
						table[h].setValue(value);
						return old;
					}
					if(table[h1] == DEFUNCT && findSlot == false){
						indexSlot = h1;
						findSlot = true;
					}
					i++;
					h1 = Math.abs((h + i*i)%getCapacity());
				}	
				
				if(findKey == false && findSlot == true){
					Entry e = new Entry(k,value);
					table[indexSlot] = e;
					incSize();
				}
				else if(findKey == false){
					Entry e = new Entry(k,value);
					table[h1] = e;
					incSize();
				}
			}
			
		}
		else{
			Entry e = new Entry(k, value);
			table[h] = e;
			incSize();
		}
		return old;
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		int old = -1;
		int h = hashFunction(k);
		if(table[h]!=null){
			if(table[h].getKey() == k){
				old = table[h].getValue();
				table[h] = DEFUNCT;
				decSize();
				return old;
			}
			else{
				int i = 0;
				int h1 = Math.abs((h + i*i)%getCapacity());
				while(table[h1] != null || table[h1] == DEFUNCT){
					if(table[h1].getKey() == k){
						old = table[h1].getValue();
						table[h1] = DEFUNCT;
						decSize();
						return old;
					} 
					i++;
					h1 = Math.abs((h + i*i)%getCapacity());
				}
			}
		}
		return old;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		ArrayList<Entry> buf = new ArrayList<>(size());
		for(int i = 0; i<getCapacity(); i++){
			if(table[i]!=null){
				buf.add(table[i]);
			}
		}
		return buf;
	}
	
}


