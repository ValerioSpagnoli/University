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
	public static final String CONVERTI = "converti";
	public static final String LETTERE = "lettere";
	public static final String CIFRE = "cifre";
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Socket socket;
	private OutputStream outputStream;
	private PrintWriter printWriter;
	private Scanner scanner;
	private Logger logger = Logger.getLogger("client.ClientListener");
	
	private Downloader downloader;
	
	public ClientListener(Frame frame, JTextField ipAddress, JTextField port) {
		this.frame = frame;
		this.ipAddress = ipAddress;
		this.port = port;
	}
	
	public void setupConnection() throws UnknownHostException, IOException {
		socket = new Socket(ipAddress.getText(), Integer.parseInt(port.getText()));
		outputStream = socket.getOutputStream();
		printWriter = new PrintWriter(outputStream);
		scanner = new Scanner(socket.getInputStream());
	}

	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(START)) {
			frame.hexadecimalText.setText("");
			frame.decimalText.setText("");
			frame.binaryText.setText("");
			downloader = new Downloader(frame, scanner);
			printWriter.println(command);
			printWriter.flush();
			Thread downloaderThread = new Thread(downloader);
			downloaderThread.start();
			transmitting = true;
			logger.log(Level.INFO, "Download avviato");
		}
		
		else if(command.equals(STOP)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			logger.log(Level.INFO, "Download interrotto");
		}
		
		else if(command.equals(CONNECT)) {
			try {
				setupConnection();
			} catch (IOException ioe) {
				logger.log(Level.SEVERE, "Errore di connessione al server");
				return;
			}
			connected = true;
			logger.log(Level.INFO, "Connessione riuscita");
			frame.hexadecimalText.setText("");
			frame.decimalText.setText("");
			frame.binaryText.setText("");
		}
		
		else if(command.equals(DISCONNECT)) {
			printWriter.println("disconnect");
			printWriter.flush();
			printWriter.close();
			scanner.close();
			try {
				socket.close();
			} catch (IOException ioe) {
				logger.log(Level.SEVERE, "Errore nella chiusura della socket");
			}
			connected = false;
			logger.log(Level.INFO, "Connessione interrotta");
		}
		
		else if(command.equals(CONVERTI)) {
			if(frame.hexadecimalText.getText().equals("")) {
				JOptionPane.showMessageDialog(null, "Errore. Effettuare prima il download");
			}
			else {
				Long decimaleLong = Long.parseUnsignedLong(frame.hexadecimalText.getText(), 16);
				String binario = Long.toBinaryString(decimaleLong);
				String decimale = "" + decimaleLong;
				frame.decimalText.setText(decimale);
				frame.binaryText.setText(binario);
			}
			transmitting = false;
		}
		
		else if(command.equals(LETTERE)) {
			printWriter.println(command);
			printWriter.flush();
		}
		
		else if(command.equals(CIFRE)) {
			printWriter.println(command);
			printWriter.flush();
		}
		
		frame.setButtons(connected, transmitting);
		
	}

	
	
	
	
	
	
	
	
	
	
	
	
	
}
