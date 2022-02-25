package client;

import java.awt.Color;
import java.io.PrintWriter;
import java.util.Scanner;

public class Downloader implements Runnable{

	private Scanner scanner;
	private boolean running;
	private Frame frame;

	public Downloader(Scanner scanner, Frame frame) {
		this.scanner = scanner;
		this.frame = frame;
		running = false;
	}
	
	
	public void run() {
		if(!running) {
			running = true;
			for(int i = 0; i<16; i++) {
				for(int j = 0; j<16; j++) {
					frame.gridPanel[i][j].setBackground(Color.LIGHT_GRAY);
				}
			}
				while(running) {
					String stringa = scanner.nextLine();
					String[] dati = stringa.split(";");
					String posizioneInGriglia = dati[0];
					
					String codiceColore = dati[1];
					
					if(posizioneInGriglia.equals("-1") && codiceColore.equals("-1")) {
						running  = false;
					}
					
					else {
						for(int i = 0; i<16; i++) {
							for(int j = 0; j<16; j++) {
								if(((i*16)+j) == Integer.parseInt(posizioneInGriglia)) {
									frame.gridPanel[i][j].setBackground(new Color(Integer.parseInt(codiceColore)));
								}
							}
						}
					}
				}
			}
		}
}

