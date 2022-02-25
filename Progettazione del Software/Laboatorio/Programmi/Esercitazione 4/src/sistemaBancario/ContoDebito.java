package sistemaBancario;

public class ContoDebito extends ContoCorrente {
	
	public ContoDebito (String codice, int saldoIniziale) {
		super(codice, saldoIniziale);
	}
	
	public void riconosciInteresse(double interesse) {
		int aumento = (int)(this.saldo * interesse);
		this.deposito(aumento);
	}
}
