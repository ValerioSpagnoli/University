package client;

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
import javax.swing.JTextField;

public class ClientListener implements ActionListener{
	
	public static final String START = "start";
	public static final String STOP = "stop";
	public static final String CONNECT = "connect";
	public static final String DISCONNECT = "disconnect";
	public static final String CLEAR = "clear";
	
	private boolean connected = false;
	private boolean transmitting = false;
	private boolean check = false;
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	
	private Downloader downloader;
	private OutputStream outputStream;
	private PrintWriter printWriter;
	private Scanner scanner;
	private Socket socket;
	private Logger logger = Logger.getLogger("client.ClientListener");
	
	public ClientListener(Frame frame, JTextField ipAddress, JTextField port) {
		this.frame = frame;
		this.ipAddress = ipAddress;
		this.port = port;
	}
	
	public void setupConnection() throws NumberFormatException, UnknownHostException, IOException {
		socket = new Socket(ipAddress.getText(), Integer.parseInt(port.getText()));
		outputStream = socket.getOutputStream();
		printWriter = new PrintWriter(outputStream);
		scanner = new Scanner(socket.getInputStream());	
	}
	
	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(START)) {
			for(int i = 0; i<5; i++) {
				frame.gridBlock[i].setNumber(frame.gridBlock[i].getText());
				frame.gridBlock[i].setDefaultColor();
			}
			check();
			downloader = new Downloader(frame, scanner);
			printWriter.println(command);
			printWriter.flush();
			transmitting = true;
			Thread downloaderThread = new Thread(downloader);
			downloaderThread.start();
			JOptionPane.showMessageDialog(null, "Start Game");
			logger.log(Level.INFO, "Download avviato");
		}
		
		else if(command.equals(STOP)) {
			printWriter.println("interrompi");
			printWriter.flush();
			transmitting = false;
			JOptionPane.showMessageDialog(null, "Stop Game");
			logger.log(Level.INFO, "Download Interrotto");
		}
		
		else if(command.equals(CONNECT)) {
			try {
				setupConnection();
				connected = true;
				logger.log(Level.INFO, "Connessione riuscita");
			} catch (NumberFormatException e) {
				logger.log(Level.SEVERE, "Errore nell'inserimento della porta");
				return;
			} catch (UnknownHostException e) {
				logger.log(Level.SEVERE, "Errore nell'inserimento dell'indirizzo IP");
				return;
			} catch (IOException e) {
				logger.log(Level.SEVERE, "Errore di connessione");
				return;
			}
			JOptionPane.showMessageDialog(null, "Connessione stabilita");
			JOptionPane.showMessageDialog(null, "Inserire 5 numeri");
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
				logger.log(Level.SEVERE, "Errore nella chiusura della socket");
			}
			JOptionPane.showMessageDialog(null, "Connessione interrotta");
		}
		
		else if(command.equals(CLEAR)) {
			for(int i = 0; i<5; i++) {
				frame.gridBlock[i].setDefaultColor();
				frame.gridBlock[i].setText("");
				frame.gridBlock[i].setEditable(true);
			}
			transmitting = false;
		}
		
		frame.setButtons(connected, transmitting);
		
	}
	
	private void check() {
		check = false;
		if(!frame.block1.checkNumber()) {
			JOptionPane.showMessageDialog(null, "Inserire un valore tra 1 e 9 nella casella uno.");
			check = true;
		}
		else if(!frame.block2.checkNumber()) {
			JOptionPane.showMessageDialog(null, "Inserire un valore tra 1 e 9 nella casella due.");
			check = true;
		}
		else if(!frame.block3.checkNumber()) {
			JOptionPane.showMessageDialog(null, "Inserire un valore tra 1 e 9 nella casella tre.");
			check = true;
		}
		else if(!frame.block4.checkNumber()) {
			JOptionPane.showMessageDialog(null, "Inserire un valore tra 1 e 9 nella casella quattro.");
			check = true;
		}
		else if(!frame.block5.checkNumber()) {
			JOptionPane.showMessageDialog(null, "Inserire un valore tra 1 e 9 nella casella cinque.");
			check = true;
		}
		if(check) {
			check();
		}
	}

}
