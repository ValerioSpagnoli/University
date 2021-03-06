package sistemaBancario;

public abstract class ContoCorrente implements Comparable <ContoCorrente> {
	
	//campi dati
	private String codice;
	protected int saldo;
	private String nomeProprietario;
	private String cognomeProprietario;
	
	//override di compareTo in Comparable
	public int compareTo(ContoCorrente c) {
		if(this.saldo > c.getSaldo()) { return 1; }
		else if(this.saldo == c.getSaldo()) {return 0;}
		else {return -1;}
	}
	
	//override di toString
	public String toString() {
		return this.codice + " di " + this.nomeProprietario + " " + this.cognomeProprietario + " con saldo " + this.getSaldo() + " €.\n";
	}
	
	//costruttore
	public ContoCorrente(String codiceConto, int saldoIniziale) {
		codice = codiceConto;
		saldo = saldoIniziale;
	}
	
	//medoti
	public String getCodice() {
		return codice;
	}
	
	public int getSaldo() {
		return saldo;
	}
	
	public String getNomeProprietario() {
		return nomeProprietario;
	}
	
	public String getCognomeProprietario() {
		return cognomeProprietario;
	}
	
	public void setNomeProprietario(String nome) {
		nomeProprietario = nome;
	}
	
	public void setCognomeProprietario(String cognome) {
		cognomeProprietario = cognome;
	}
	
	public void deposito(int cifra) {
		saldo = saldo + cifra;
	}
	
	public void prelievo(int cifra) {
		saldo = saldo - cifra;
	}
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
}
