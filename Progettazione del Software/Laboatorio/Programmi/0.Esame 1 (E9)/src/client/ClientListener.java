package client;

import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import java.util.logging.*;
import javax.swing.*;

public class ClientListener implements ActionListener{
	
	public static final String CONNECT = "connect";
	public static final String DISCONNECT = "disconnect";
	public static final String START = "start";
	public static final String STOP = "stop";
	
	private JTextField matricola;
	private JTextField ipAddress;
	private JTextField porta;
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader = null;
	
	private PrintWriter printWriter;
	private Scanner scanner;
	private Socket socket;
	private Frame frame;
	private static Logger logger = Logger.getLogger("client.ClientListener");
	
	public ClientListener(Frame frame, JTextField matricola, JTextField ipAddress, JTextField porta) {
		this.frame = frame;
		this.matricola = matricola;
		this.ipAddress = ipAddress;
		this.porta = porta;
	}
	
	public void setupConnection() throws UnknownHostException, IOException {
		socket = new Socket(ipAddress.getText(), Integer.parseInt(porta.getText()));//inizializza la socket con ipAddress e porta
		OutputStream outputStream = socket.getOutputStream();						//crea l'outputStram per inviare informazioni
		printWriter = new PrintWriter(outputStream);								//inizializza il printWriter con outputStream
		scanner = new Scanner(socket.getInputStream());								//inizializza lo scanner per leggere informazioni
	}

	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(CONNECT)) {
			try {
				setupConnection();													//si connette al server
				connected = true;
				logger.log(Level.INFO, "Connessione al server riuscita");
			} catch(IOException ioe){
				JOptionPane.showMessageDialog(null, "Impossibile connettersi.");
				logger.log(Level.SEVERE, "Connessione al server non riuscita" + 
										  ioe.getMessage() + ioe.getStackTrace());
				return;
			}
			JOptionPane.showMessageDialog(null, "Connessione stabilita");
		}
		
		else if(command.equals(DISCONNECT)) {
			printWriter.println(command);											//invia al server il comando "disconnect"
			printWriter.flush();
			printWriter.close();													//chiude il printWriter
			scanner.close();														//chiude lo scanner
			connected = false;
			try {
				socket.close();
			} catch (IOException ioe) {
				logger.log(Level.SEVERE, "Errore nella chiusura della socket" + 
										  ioe.getMessage() + ioe.getStackTrace());
			}
			JOptionPane.showMessageDialog(null, "Connessione interrotta");
		}
		
		else if(command.equals(START)) {
			try {
				downloader = new Downloader (matricola.getText(), scanner);			//inizializza l'oggetto downloader
			} catch(IOException ioe) {
				JOptionPane.showMessageDialog(null, "Impossibile creare il file");
				logger.log(Level.SEVERE, "Impossibile creare il file" + 
										  ioe.getMessage() + ioe.getStackTrace());
			}
			
			transmitting = true;
			printWriter.println(command);											//invia al server il comando "start"
			printWriter.flush();
			
			Thread downloaderThread = new Thread(downloader);						//crea il thread per il downloader
			downloaderThread.start();												//fa partire il thread
			JOptionPane.showMessageDialog(null, "Download avviato");
			logger.log(Level.INFO, "Download avviato");
		}
		
		else if(command.equals(STOP)) {
			printWriter.println(command);											//invia al server comando "stop"
			printWriter.flush();
			transmitting = false;
			JOptionPane.showMessageDialog(null, "Download fermato");
			logger.log(Level.INFO, "Download fermato");
		}		
		
		frame.setButtons(connected, transmitting);	
	}
}
