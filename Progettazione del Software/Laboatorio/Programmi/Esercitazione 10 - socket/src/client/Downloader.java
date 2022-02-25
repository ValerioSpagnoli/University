package client;

import app.*;

import java.awt.Color;
import java.util.*;

public class Downloader implements Runnable{
	
	private Scanner scan;
	private boolean running;
	private String posizioneInGriglia;
	private String codiceColore;
	private Frame frame;

	public Downloader(Scanner sc, Frame fr) {
		posizioneInGriglia = "";
		codiceColore = "";
		this.scan = sc;
		this.frame = fr;
		running = false;	
	}
	

	public void run() {
		if(!running) {
			running = true;
			while(running) {
				String s = scan.nextLine();
				String[] r = s.split(";");
				posizioneInGriglia = r[0];
				codiceColore = r[1];
				if(codiceColore.equals("-1") && posizioneInGriglia.equals("-1")) {
					running = false;
				}
				else {
					Color color = new Color(Integer.parseInt(codiceColore));
					int contaCella = 0;
					for(int i = 0 ; i<16; i++) {
						for(int j = 0; j<16; j++) {
							contaCella = contaCella + 1;
							if(contaCella == Integer.parseInt(posizioneInGriglia)) {
								frame.ijMat[i][j].setBackground(color);
							}
						}
					}
				}
			}
		}
	}
	
	public String getPosizioneInGriglia() {
		return posizioneInGriglia;
	}
	public String getCodiceColore() {
		return codiceColore;
	}
	
	public boolean isRunning() {
		return running;
	}
	

}
