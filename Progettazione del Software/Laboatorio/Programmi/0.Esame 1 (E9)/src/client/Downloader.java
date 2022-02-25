package client;
import java.io.*;
import java.util.*;
import client.ClientListener;

public class Downloader implements Runnable{
	
	private PrintWriter printWriter;
	private Scanner scanner;
	private boolean running;
	private String stringaRicevuta;

	public Downloader(String fileName, Scanner scanner) throws IOException {
		stringaRicevuta = "";													//inizializza la stringa
		File file = new File(fileName+".txt");									//crea il file
		printWriter = new PrintWriter(new FileWriter(file));					//inizializza il printWriter
		this.scanner = scanner;													//inizializza lo scanner
		running = false;														
	}
	
	public void run() {
		if(!running) {																								
			running = true;		
			while(running) {													//finche è running		
				String stringa = scanner.nextLine();							//legge la stringa dal server
				if(stringa.equals("*")) {										//se la stringa è * (vedi protocollo)
					printWriter.println(stringaRicevuta);						//stampa sul file tutta la stringa ricevuta
					printWriter.flush();
					String codiceChiusura = scanner.nextLine();					//legge il codice di chiusuta (vedi protocollo)
					printWriter.println(codiceChiusura);						//stampa il codice di chiusura
					printWriter.flush();
					printWriter.close();										//chiude la printWriter
					String comandoStop = scanner.nextLine();					//legge la stringa "stop" (vedi protocollo)
					running = !comandoStop.equals(ClientListener.STOP);			//mette running a false
				}
				else {														
					stringaRicevuta = stringaRicevuta + stringa;				//concatena la stringa a strinaRicevuta
				}
			}
		}
	}
	
	public boolean isRunning() {
		return running;
	}
}
