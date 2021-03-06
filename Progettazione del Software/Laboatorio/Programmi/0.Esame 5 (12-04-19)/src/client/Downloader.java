package client;

import java.util.Arrays;
import java.util.Scanner;

public class Downloader implements Runnable{
	
	private Frame frame;
	private Scanner scanner;
	private boolean running = false;
	
	Character[] stark = new Character[100];
	Character[] targaryen = new Character[100];
	Character[] lannister = new Character[100];
	
	public Downloader(Frame frame, Scanner scanner) {
		this.frame = frame;
		this.scanner = scanner;
	}
	
	public void run() {
		if(!running) {
			running = true;
			
			for(int i = 0; i<100; i++) {
				stark[i] = null;
				targaryen[i] = null;
				lannister[i] = null;
			}
			
			while(running) {
				String stringa = scanner.nextLine();
				System.out.println(stringa + "\n");
				if(stringa.equals("end")) {
					running = false;
				}
				else {
					String[] dati = stringa.split(",");
					String nome = dati[0];
					String cognome = dati[1];
					String casata = dati[2];
					String ruolo = dati[3];
					
					int doppioneConsecutivoS = 0;
					int doppioneConsecutivoT = 0;
					int doppioneConsecutivoL = 0;
					
					if(casata.equals("STARK")) {
						Character c = new Character(nome, cognome, casata, ruolo);
						String testo = "";
						
						for(int i = 0; i<100 && !(stark[i]==null); i++) {
							testo = testo + stark[i].toString() + "\n";
						}
						
						boolean doppione = false;
						String doppioneRicevuto = "";
						
						
						if(stark[0] == null) {
							System.out.println(c.toString() + "\n");
							stark[0] = c;
							testo = c.toString() + "\n";
						}
						else {
							int compare;
							int i = 0;
							boolean inserito = false;
							
							while(!(stark[i] == null) && !inserito) {
								compare = stark[i].compareTo(c);
								if(compare<0) {
									i++;
								}
								else if(compare>0) {
									doppione = false;
									i++;
								}
								else if(compare == 0) {
									doppione = true;
									doppioneConsecutivoS ++;
									i++;
								}
							}
							if(!inserito) {
								if(!doppione) {
									int z = 0;
									Character[] aus = Arrays.copyOf(stark, stark.length);
									for(int j = 0; j<100 && !(stark[j]==null); j++) {
										compare = stark[j].compareTo(c);
										if(compare>0) {
											z = j;
										}
									}
									for(int k = stark.length-1; k>z; k--) {
										aus[k] = aus[k-1];
									}
									for(int j = 0; j<100; j++) {
										 stark[j] = aus[j];
									}
									stark[z] = c;
									inserito = true;
									doppioneConsecutivoS = 0;
									System.out.println(c.toString() + "\n");
								}
								else {
									doppioneRicevuto = "DOPPIONE RICEVUTO";
									System.out.println("doppione");
								}
							}
						}	
						
						if(doppione) {
							String testoDoppione = "";
							for(int i = 0; i<doppioneConsecutivoS; i++) {
								testoDoppione = testoDoppione + "DOPPIONE RICEVUTO";
							}
							testo = testo + "\n" + testoDoppione;
						}
						
						frame.starkText.setText(testo);
						System.out.println(testo);
					}
					
					else if(casata.equals("TARGARYEN")) {
						Character c = new Character(nome, cognome, casata, ruolo);
						String testo = "";
						boolean doppione = false;
						String doppioneRicevuto = "";
						
						if(targaryen[0] == null) {
							targaryen[0] = c;
							testo = c.toString() + "\n";
							System.out.println(c.toString() + "\n");
						}
						else {
							int compare;
							int i = 0;
							boolean inserito = false;
							
							while(!(targaryen[i] == null) && !inserito) {
								compare = targaryen[i].compareTo(c);
								if(compare<0) {
									i++;
								}
								else if(compare>0) {
									Character[] aus = Arrays.copyOf(targaryen, targaryen.length);
									for(int k = targaryen.length-1; k>i; k--) {
										aus[k] = aus[k-1];
									}
									for(int j = 0; j<100; j++) {
										 targaryen[j] = aus[j];
									}
									targaryen[i] = c;
									inserito = true;
									System.out.println(c.toString() + "\n");
								}
								else if(compare == 0) {
									doppione = true;
									i++;
								}
							}
							if(!inserito) {
								if(!doppione) {
									targaryen[i] = c;
									inserito = true;
									System.out.println(c.toString() + "\n");
								}
								else {
									doppioneRicevuto = "DOPPIONE RICEVUTO";
									System.out.println("doppione");
								}
							}
						}
						
						for(int j = 0; j<100 && !(targaryen[j]==null); j++) {
							testo = testo + targaryen[j].toString() + "\n";
						}
						if(doppione) {
							testo = testo + "\n\n" + doppioneRicevuto;
						}
						frame.targaryenText.setText(testo);
						System.out.println(testo);
					}
					
					else if(casata.equals("LANNISTER")) {
						Character c = new Character(nome, cognome, casata, ruolo);
						String testo = "";
						boolean doppione = false;
						String doppioneRicevuto = "";
						if(lannister[0] == null) {
							lannister[0] = c;
							testo = c.toString() + "\n";
							System.out.println(c.toString() + "\n");
						}
						else {
							int compare;
							int i = 0;
							boolean inserito = false;
							
							
							while(!(lannister[i] == null) && !inserito) {
								compare = lannister[i].compareTo(c);
								if(compare<0) {
									i++;
								}
								else if(compare>0) {
									Character[] aus = Arrays.copyOf(lannister, lannister.length);
									for(int k = lannister.length-1; k>i; k--) {
										aus[k] = aus[k-1];
									}
									for(int j = 0; j<100; j++) {
										 lannister[j] = aus[j];
									}
									lannister[i] = c;
									inserito = true;
									System.out.println(c.toString() + "\n");
								}
								else if(compare == 0) {
									doppione = true;
									i++;
								}
							}
							if(!inserito) {
								if(!doppione) {
									lannister[i] = c;
									inserito = true;
									System.out.println(c.toString() + "\n");
								}
								else {
									doppioneRicevuto = "DOPPIONE RICEVUTO";
									System.out.println("doppione");
								}
							}	
						}
						
						for(int j = 0; j<100 && !(lannister[j]==null); j++) {
							testo = testo + lannister[j].toString() + "\n";
						}
						if(doppione) {
							testo = testo + "\n\n" + doppioneRicevuto;
						}
						frame.lannisterText.setText(testo);
						System.out.println(testo);
					}	
				}
			}
			frame.setButtons(true,false);
		}
	}
	


}
