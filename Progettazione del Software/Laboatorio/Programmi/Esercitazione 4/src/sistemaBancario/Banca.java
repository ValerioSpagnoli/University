package sistemaBancario;

import java.util.Arrays;

public class Banca {
	
	private String nome;
	private ContoCorrente[] conti;
	private int index;
	private static final int MAX = 10;

	public Banca(String nome) {
		this.nome = nome;
		conti = new ContoCorrente[MAX];
		index = 0;
	}
	
	public void aggiugniConto(ContoCorrente c) throws Exception {
		if(index == MAX) throw new Exception("Raggiunta massima dimensione banca.");
		conti[index] = c;
		index = index + 1;
		ContoCorrente[] buffer = Arrays.copyOf(conti, index);
		Arrays.sort(buffer);
		for(int i = 0; i<buffer.length; i++) {
			conti[i] = buffer[i];
		}
	}
	
	public int getBilancioTotale() {
		int totale = 0;
		for(int i = 0; i<index; i++) {
			totale = totale + conti[i].getSaldo();
		}
		return totale;
	}
	
	public String toString() {
		String buffer = "La banca " + this.nome;
		buffer = buffer + " ha un bilancio di " + this.getBilancioTotale() + "€.\n";
		
		for(ContoCorrente c : conti) {
			buffer = buffer + "** Conto **\n" + c;
		}
		return buffer;
	}
	
	
	
	
	
	
	
}
