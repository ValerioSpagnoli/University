package client;

import java.util.Scanner;

import javax.swing.JOptionPane;

public class Downloader implements Runnable{

	private Frame frame;
	private Scanner scanner;
	private boolean running;
	private boolean stop = false;
	
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
				
				if(stringa.equals("done")) {
					running = false;
				}
				
				else if(stringa.equals("interrupted")) {
					JOptionPane.showMessageDialog(null, "Partita interrotta");
					for(int i = 0; i<10; i++) {
						for(int j = 0; j<10; j++) {
							frame.btnGrid[i][j].setSelected(true);
						}
					}
					frame.setButtons(true, false);
					running = false;
					stop = true;
				}
				
				else {
					String[] dati = stringa.split(":");
					String indiceRiga = dati[0];
					String indiceColonna = dati[1];
					String contenutoCasella = dati[2];
				
					int i = Integer.parseInt(indiceRiga);
					int j = Integer.parseInt(indiceColonna);
				
					if(contenutoCasella.equals("-1")) {
						frame.btnGrid[i][j].setMine(true);
					}
					else {
						frame.btnGrid[i][j].setAdjacentMines(Integer.parseInt(contenutoCasella));
					}
				}
			}
			
			if(!stop) {
				frame.setButtons(true, false);
				for(int i = 0; i<10; i++) {
					for(int j = 0; j<10; j++) {
						frame.btnGrid[i][j].setEnabled(true);
					}
				}
				JOptionPane.showMessageDialog(null, "Partita iniziata");
			}
		}
		
	}

}
