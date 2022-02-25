package client;

import java.util.Scanner;

public class Downloader implements Runnable{

	private Frame frame;
	private Scanner scanner;
	private boolean running = false;
	
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
					System.out.println("END: " + stringa);
					frame.consoleText.setText(frame.consoleText.getText() + "\n" + "|||| DOWNLOAD COMPLETATO ||||\n");
					frame.setButtons(true, false);
					running = false;
				}
				else if(stringa.equals("INTERRUPTED")) {
					System.out.println("INTERRUPTED: " + stringa);
					frame.consoleText.setText(frame.consoleText.getText() + "\n" + "|||| DOWNLOAD INTERROTTO ||||\n");
					frame.setButtons(true, false);
					running = false;
				}
				else if(stringa.equals("ERROR")) {
					System.out.println("ERROR: " + stringa);
					frame.consoleText.setText(frame.consoleText.getText() + "\n" + "|||| COMANDO ERRATO ||||\n");
					frame.setButtons(false, false);
					running = false;
				}
				else {
					System.out.println(stringa);
					frame.consoleText.setText(frame.consoleText.getText() + "\n" + stringa);
				}
			}
			frame.setButtons(true, false);
		}
		
	}

}
