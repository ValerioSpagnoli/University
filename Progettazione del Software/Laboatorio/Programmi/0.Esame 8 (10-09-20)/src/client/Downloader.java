package client;

import java.awt.Color;
import java.util.Scanner;

public class Downloader implements Runnable{

	private Frame frame;
	private Scanner scanner;
	private boolean running;
	
	public Downloader(Frame frame, Scanner scanner) {
		this.frame = frame;
		this.scanner = scanner;
		running = false;
	}
	
	@Override
	public void run() {
		if(!running) {
			running = true;
			while(running) {
				String stringa = scanner.nextLine();
				if(stringa.equals("+")) {
					running = false;
					String nuovoTesto = frame.elencoEstrattiText.getText() + "--- Fine Partita --- \n";
					frame.elencoEstrattiText.setText(nuovoTesto);
					frame.setButtons(true, false);
				}
				else {
					String numeroEstratto = stringa;
					int numero = Integer.parseInt(numeroEstratto);
					String nuovoTesto = frame.elencoEstrattiText.getText() + "Estratto: " + numeroEstratto + "\n";
					frame.elencoEstrattiText.setText(nuovoTesto);
					
					for(int i = 0; i<3; i++) {
						for(int j = 0; j<5; j++) {
							if(frame.ticketGrid[i][j].getText().equals(numeroEstratto)) {
								System.out.println("yes");
								frame.ticketGrid[i][j].setBackground(Color.GREEN);
							}
						}
					}
				}
			}
		}
	}

}
