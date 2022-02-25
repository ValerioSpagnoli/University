package client;

import java.awt.Color;
import java.util.Scanner;

import javax.swing.JOptionPane;

public class Downloader implements Runnable{

	private Scanner scanner;
	private Frame frame;
	private boolean running = false;
	private String UserColor;
	private boolean stop = false;
	
	public Downloader(Frame frame, Scanner scanner, String color) {
		this.frame = frame;
		this.scanner = scanner;
		UserColor = color;
	}
	
	
	public void run() {
		if(!running) {
			running = true;
			while(running) {
				String stringa = scanner.nextLine();
				
				if(stringa.equals("*")) { //partita terminata
					running = false;
				}
				else if(stringa.equals("-1")) { //sessione conclusa
					running = false;
					stop = true;
				}
				else {
					String[] dati = stringa.split(";");
					int posizioneInGriglia = Integer.parseInt(dati[0]);
					String colorePedina = dati[1];
					
					for(int i = 0; i<4; i++) {
						for(int j = 0; j<4; j++) {
							if(((i*4)+j) == posizioneInGriglia) {
								if(colorePedina.equals("cyan")) {
									frame.pedinaGrid[i][j].setCyanColor();
								}
								else if(colorePedina.equals("yellow")) {
									frame.pedinaGrid[i][j].setYellowColor();
								}
							}
						}
					}
				}
			}
			if(!stop) {
				if(checkCyanWin() && checkYellowWin()){ //pareggio
					JOptionPane.showMessageDialog(null, "Esito della partita: pareggio.");
				}
				else {
					if(checkCyanWin()) { //ha vinto cyan
						if(UserColor.equals("cyan")) {
							JOptionPane.showMessageDialog(null, "Esito della partita: vince User.");
						}
						else {
							JOptionPane.showMessageDialog(null, "Esito della partita: vince Server.");
						}
					}
					else if(checkYellowWin()) { //ha vinto yellow
						if(UserColor.equals("yellow")) {
							JOptionPane.showMessageDialog(null, "Esito della partita: vince User.");
						}
						else {
							JOptionPane.showMessageDialog(null, "Esito della partita: vince Server.");
						}
					}
					else { //non ha vinto nessuno, pareggio
						JOptionPane.showMessageDialog(null, "Esito della partita: pareggio.");
					}
					frame.setButtons(true, false);
				}
			}
			else {
				JOptionPane.showMessageDialog(null, "Esito della partita: vince Server.");
			}
		}
	}
	
	public boolean checkCyanWin() {
		boolean win = false;
		for(int i = 0; i<4; i++) { //controllo per righe
			int counter = 0;
			for(int j = 0; j<4; j++) {
				if(frame.pedinaGrid[i][j].getColor().equals(Color.CYAN)) {
				 counter++;
				}
			}
			if(counter == 4) {
				win = true;
			}
		}
		for(int j = 0; j<4; j++) { //controllo per colonne
			int counter = 0;
			for(int i = 0; i<4; i++) {
				if(frame.pedinaGrid[i][j].getColor().equals(Color.CYAN)) {
					counter++;
				}
			}
			if(counter == 4) {
				win = true;
			}
		}
		if(frame.pedinaGrid[0][0].getColor().equals(Color.CYAN) && //controllo diagonale principale
		   frame.pedinaGrid[1][1].getColor().equals(Color.CYAN) &&
		   frame.pedinaGrid[2][2].getColor().equals(Color.CYAN) &&
	       frame.pedinaGrid[3][3].getColor().equals(Color.CYAN)) {
			win = true;
		}
		if(frame.pedinaGrid[0][3].getColor().equals(Color.CYAN) && //controllo diagonale secondaria
		   frame.pedinaGrid[1][2].getColor().equals(Color.CYAN) &&
     	   frame.pedinaGrid[2][1].getColor().equals(Color.CYAN) &&
     	   frame.pedinaGrid[3][0].getColor().equals(Color.CYAN)) {
					win = true;
		}
		return win;
	}
	
	public boolean checkYellowWin() {
		boolean win = false;
		for(int i = 0; i<4; i++) { //controllo per righe
			int counter = 0;
			for(int j = 0; j<4; j++) {
				if(frame.pedinaGrid[i][j].getColor().equals(Color.YELLOW)) {
				 counter++;
				}
			}
			if(counter == 4) {
				win = true;
			}
		}
		for(int j = 0; j<4; j++) { //controllo per colonne
			int counter = 0;
			for(int i = 0; i<4; i++) {
				if(frame.pedinaGrid[i][j].getColor().equals(Color.YELLOW)) {
					counter++;
				}
			}
			if(counter == 4) {
				win = true;
			}
		}
		if(frame.pedinaGrid[0][0].getColor().equals(Color.YELLOW) && //controllo diagonale principale
		   frame.pedinaGrid[1][1].getColor().equals(Color.YELLOW) &&
		   frame.pedinaGrid[2][2].getColor().equals(Color.YELLOW) &&
	       frame.pedinaGrid[3][3].getColor().equals(Color.YELLOW)) {
			win = true;
		}
		if(frame.pedinaGrid[0][3].getColor().equals(Color.YELLOW) && //controllo diagonale secondaria
		   frame.pedinaGrid[1][2].getColor().equals(Color.YELLOW) &&
     	   frame.pedinaGrid[2][1].getColor().equals(Color.YELLOW) &&
     	   frame.pedinaGrid[3][0].getColor().equals(Color.YELLOW)) {
					win = true;
		}
		return win;
	}
	
	public boolean isRunning() {
		return running;
	}
	

}
