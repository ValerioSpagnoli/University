package client;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JOptionPane;

public class ClientListener implements ActionListener{
	
	public static final String START = "start";
	public static final String STOP = "stop";
	public static final String CONNECT = "connect";
	public static final String DISCONNECT = "disconnect";
	public static final String CLEAR = "clear";
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader = null;
	
	private PrintWriter printWriter;										//serve per inviare al server
	private OutputStream outputStream;										//serve per inviare al server
	private Scanner scanner;												//serve per leggere dal server
	private Socket socket;													//serve per il collegamento con il server
											
	private Frame frame;
	
	private static Logger logger = Logger.getLogger("client.ClientListener");
	
	public ClientListener(Frame frame) {
		this.frame = frame;
	}
	
	public void setupConnection() throws UnknownHostException, IOException {
		socket = new Socket(frame.ipAddressText.getText(), Integer.parseInt(frame.portText.getText()));
		outputStream = socket.getOutputStream();
		printWriter = new PrintWriter(outputStream);
		scanner = new Scanner(socket.getInputStream());
	}
	
	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(START)) {
			downloader = new Downloader(scanner, frame);
			transmitting = true;
			printWriter.println(command);
			printWriter.flush();
			
			Thread downloaderThread = new Thread(downloader);
			downloaderThread.start();
			logger.log(Level.INFO, "Download avviato");
			JOptionPane.showMessageDialog(null, "Download avviato");
		}
		
		else if(command.equals(STOP)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			JOptionPane.showMessageDialog(null, "Download interrotto");
			logger.log(Level.INFO, "Download interrotto");
		}
		
		else if(command.equals(CONNECT)) {
			try {
				setupConnection();
				connected = true;
				logger.log(Level.INFO, "Connessione stabilita");
			} catch (IOException ioe) {
				logger.log(Level.SEVERE, "Errore nella connessione" + ioe.getMessage() + ioe.getStackTrace());
				JOptionPane.showMessageDialog(null, "Errore nella connessione");
				return;
			}
			JOptionPane.showMessageDialog(null, "Connessione stabilita");
		}
		
		else if(command.equals(DISCONNECT)) {
			printWriter.println(command);
			printWriter.flush();
			printWriter.close();
			scanner.close();
			connected = false;
			try {
				socket.close();
			} catch (IOException ioe) {
				logger.log(Level.SEVERE, "Errore nella chiusura");
			}
			JOptionPane.showMessageDialog(null, "Connessione interrotta");
		}
		
		else if(command.equals(CLEAR)) {
			for(int i = 0; i<16; i++) {
				for(int j = 0; j<16; j++) {
					frame.gridPanel[i][j].setBackground(Color.LIGHT_GRAY);
				}
			}
		}
		
		frame.setButtons(connected, transmitting);
		
	}

}
