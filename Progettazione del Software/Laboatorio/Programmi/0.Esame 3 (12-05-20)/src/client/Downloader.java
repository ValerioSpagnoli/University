package client;

import java.util.Scanner;

import javax.swing.JOptionPane;

public class Downloader implements Runnable{
	
	private Scanner scanner;
	private boolean running;
	private boolean stop;
	private Frame frame;
	
	private int counterWin;
	
	public Downloader(Frame frame, Scanner scanner) {
		this.frame = frame;
		this.scanner = scanner;
		running = false;
		stop = false;
	}
	
	public void run() {
		if(!running) {
			running = true;
			while(running) {
				for(int i = 0; i<5; i++) {
					frame.gridBlock[i].setEditable(false);
					//frame.gridBlock[i].setDefaultColor();
				}
				
				String stringa = scanner.nextLine();
				String[] dati = stringa.split(";");
				String posizioneInGriglia = dati[0];
				String numeroEstratto = dati[1];
				
				if(posizioneInGriglia.equals("*") && numeroEstratto.equals("*")) {
					running = false;
				}
				else if(posizioneInGriglia.equals("-1") && numeroEstratto.equals("-1")) {
					running = false;
					stop =  true;
				}
				else {
					ColoredButton block = frame.gridBlock[Integer.parseInt(posizioneInGriglia)];
					if(block.getNumber().equals(numeroEstratto)) {
						block.setWinColor();
						counterWin ++;
					}
					else {
						block.setLoseColor();
					}
				}
			}
			if(counterWin>0 && !stop) {
				JOptionPane.showMessageDialog(null, "User Wins");
			}
			else {
				JOptionPane.showMessageDialog(null, "Server Wins");
			}
			for(int i = 0; i<5; i++) {
				frame.gridBlock[i].setEditable(true);
			}
			frame.setButtons(true, false);
		}
	}

}
