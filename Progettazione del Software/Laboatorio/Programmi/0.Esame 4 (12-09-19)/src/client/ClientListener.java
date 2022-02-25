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
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	
	private Downloader downloader;
	private PrintWriter printWriter;
	private OutputStream outputStream;
	private Scanner scanner;
	private Socket socket;
	private Logger logger = Logger.getLogger("client.ClientListener");
	
	
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
			for(int i = 0; i<4; i++) {
				for(int j = 0; j<4; j++) {
					frame.pedinaGrid[i][j].setDefaultColor();
				}
			}
			String color = "";
			String[] possibleColors = {"cyan", "yellow"};
			color = JOptionPane.showInputDialog(null, "Scegli il colore della pedina.", "Scelta perdina", 
										JOptionPane.INFORMATION_MESSAGE, null, possibleColors, possibleColors[0]).toString();
			logger.log(Level.INFO, "Colore scelto: " + color);
			JOptionPane.showMessageDialog(null, "Hai scelto: " + color);
			
			downloader = new Downloader(frame, scanner, color);
			transmitting = true;
			printWriter.println(command);
			printWriter.flush();
			
			Thread downloaderThread = new Thread(downloader);
			downloaderThread.start();
			logger.log(Level.INFO, "Download avviato");
			JOptionPane.showMessageDialog(null, "Start Game");
		}
		
		else if(command.equals(STOP)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			logger.log(Level.INFO, "Download interrotto");
			JOptionPane.showMessageDialog(null, "Stop Game");
		}
		
		else if(command.equals(CONNECT)) {
			try {
				setupConnection();
				connected = true;
			} catch (UnknownHostException e) {
				logger.log(Level.SEVERE, "Errore nella connessione al server. Host sconosciuto.");
				return;
			} catch (IOException e) {
				logger.log(Level.SEVERE, "Errore nella connessione al server.");
				return;
			}
			logger.log(Level.INFO, "Connessione riuscita.");
			JOptionPane.showMessageDialog(null, "Connessione riuscita");
		}
		
		else if(command.equals(DISCONNECT)) {
			printWriter.println(command);
			printWriter.flush();
			printWriter.close();
			scanner.close();
			connected = false;
			try {
				socket.close();
			} catch (IOException e) {
				logger.log(Level.SEVERE, "Errore nella chiusura della socket");
			}
			logger.log(Level.INFO, "Connessione interrotta");
			JOptionPane.showMessageDialog(null, "Connessione interrotta");
		}
		
		else if(command.equals(CLEAR)) {
			for(int i = 0; i<4; i++) {
				for(int j = 0; j<4; j++) {
					frame.pedinaGrid[i][j].setDefaultColor();
				}
			}
			transmitting = false;
		}
		
		frame.setButtons(connected, transmitting);
	}
	


}
