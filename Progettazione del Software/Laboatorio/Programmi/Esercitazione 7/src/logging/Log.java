package logging;

import java.util.logging.*;

public class Log {

	//prende un logger								"package.Classe"
	private static Logger logger = Logger.getLogger("logging.Log");
	
	private static void metodoEsempio() { //questo metodo lancia un eccezione di tipo IndexOutOfBounds
		int[] a = new int[10];
		for(int i = 0 ; i < 11; i++) {
			a[i] = i;
		}
	}
	
	public static void main(String [] args) {
		
		try { //prova a fare il metodo esempio
			Log.metodoEsempio();
		} catch (Exception e){ //se cattura un'eccezione la stampa nel logger
			logger.log(Level.WARNING, "problemi nel metodo", e); //stampa da level warning in su
		}
		
		logger.log(Level.INFO, "fatto");
	}
	
}

/*
	private static Logger nomeLogger = Logger.getLogger("nomePackage.nomeClasse") CREA UN LOGGER
	try{ 
		Log.metodoEsempio() CHIAMA IL METODO "metodoEsempio"
 	} catch (Excp e) { SE CATTURA L'ECCEZIONE E LANCIATA DA metodoEsempio
 		logger.log(Level.<LIVELLO>, "messaggio", e); AGGIUNGE AL FILE DI LOG IL MESSAGGIO MANDATO DALL'ECCEZIONE 
 															  E IL MESSAGGIO "messaggio". 
 															  LIVELLO : SEVERE problema molto grave
 															  			WARNING avvertimento pot. grave 
 															  			INFO messaggio informativo
 															  			FINE messaggio di tracing
 															  			FINEST messaggio di tracing dettagliato
 		}
 		logger.log(Level.INFO, "fatto"); STAMPA IL MESSAGGIO "fatto" NEL FILE DI LOGGING
 	}







*/










