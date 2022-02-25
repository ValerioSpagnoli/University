package client;

import java.util.Scanner;

public class Downloader implements Runnable{

	Frame frame;
	Scanner scanner;
	boolean running = false;
	
	public Downloader(Frame frame, Scanner scanner) {
		this.frame = frame;
		this.scanner = scanner;
	}
	
	@Override
	public void run() {
		if(!running) {
			running = true;
			while(running) {
				String stringa = scanner.nextLine();
				if(stringa.equals("END")) {
					frame.centerArea.setText(frame.centerArea.getText() + "\n******** DOWNLOAD COMPLETATO ********\n");
					frame.setButtons(true, false);
					running = false;
				}
				else if(stringa.equals("INTERRUPTED")) {
					frame.centerArea.setText(frame.centerArea.getText() + "\n******** DOWNLOAD INTERROTTO ********\n");
					frame.setButtons(true, false);
					running = false;
				}
				else if(stringa.equals("ERROR")) {
					frame.centerArea.setText(frame.centerArea.getText() + "\n******** ERRORE ********\n");
					frame.setButtons(true, false);
					running = false;
				}
				else {
					frame.centerArea.setText(frame.centerArea.getText() + stringa + "\n");
				}
			}
			frame.setButtons(true, false);
		}
		
	}

}
