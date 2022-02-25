package logging;

import java.io.IOException;
import java.util.logging.*;

public class Log_2 {
	
	private static Logger logger = Logger.getLogger("logging.Log_2");
	
	private static void metodoEsempio() { //questo metodo lancia un eccezione di tipo IndexOutOfBounds
		int[] a = new int[10];
		for(int i = 0 ; i < 11; i++) {
			a[i] = i;
		}
	}
	
	public static void main(String [] args) throws SecurityException, IOException {
		//richiede che ogni dettaglio venga loggato
		logger.setLevel(Level.ALL);
		
		//manda il log su file
		FileHandler fh = new FileHandler("log.txt");
		logger.addHandler(fh);
		
		try {
			Log_2.metodoEsempio();
		} catch (Exception e) {
			logger.log(Level.WARNING, "problemi nel metodo", e);
		}
		
		logger.log(Level.FINE, "fatto");
	}
	
}
