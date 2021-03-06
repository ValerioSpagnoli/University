package sistemaBancario;

public class ContoCredito extends ContoCorrente {
	
	private int numeroOperazioni;
	private int costoCommissione;
	private static final int SOGLIA_NO_COMMISSIONE = 2;
	
	public ContoCredito(String codice, int saldoIniziale) {
		super(codice, saldoIniziale);
		numeroOperazioni = 0;
		costoCommissione = 0;
	}
	
	private void applicaCommissione() {
		if(numeroOperazioni > ContoCredito.SOGLIA_NO_COMMISSIONE) {
			saldo = saldo - costoCommissione;
		}
	}
	
	public void deposito(int cifra) {
		super.deposito(cifra);
		numeroOperazioni = numeroOperazioni + 1;
		applicaCommissione();
	}
	
	public void prelievo(int cifra) {
		super.prelievo(cifra);
		numeroOperazioni = numeroOperazioni + 1;
		applicaCommissione();
	}
	
	public void reset() {
		numeroOperazioni = 0;
	}
	
	public int getCostoCommissione() {
		return costoCommissione;
	}
	
	public void setCostoCommissione(int commissione) {
		costoCommissione = commissione;
	}
}
