package client;

import java.util.Scanner;

public class Downloader implements Runnable{
	
	private Scanner scanner;
	private Frame frame;
	private boolean running = false;
	
	public Downloader(Frame frame, Scanner scanner) {
		this.frame = frame;
		this.scanner = scanner;
	}

	public void run() {
		if(!running) {
			running = true;
			while(running) {
				String stringa = scanner.nextLine();
				if(stringa.equals("+")) {
					running = false;
				}
				
				else {
					frame.hexadecimalText.setText(frame.hexadecimalText.getText()+stringa);
				}	
			}
			frame.setButtons(true, false);
		}
	}
}
