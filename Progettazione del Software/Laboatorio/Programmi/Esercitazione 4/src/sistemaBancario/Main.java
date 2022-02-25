package sistemaBancario;

public class Main {
	public static void main(String[] args) throws Exception{
		
		Banca bank = new Banca("Bank Intesa");
		
		ContoDebito d1 = new ContoDebito("D-002", 50);
		d1.setNomeProprietario("Flavio");
		d1.setCognomeProprietario("Rossi");
		d1.riconosciInteresse(0.65);
		
		bank.aggiugniConto(d1);
		
		ContoDebito d2 = new ContoDebito("D-001", 200);
		d2.setNomeProprietario("Paolo");
		d2.setCognomeProprietario("Liberatore");
		
		bank.aggiugniConto(d2);
		
		ContoCredito c1 = new ContoCredito("C-001", 400);
		c1.setNomeProprietario("Mario");
		c1.setCognomeProprietario("Zucchi");
		
		bank.aggiugniConto(c1);
		
		c1.setCostoCommissione(10);
		c1.prelievo(100);
		c1.prelievo(200);
		c1.deposito(30);
		
		System.out.println(bank);
		
	}

}
