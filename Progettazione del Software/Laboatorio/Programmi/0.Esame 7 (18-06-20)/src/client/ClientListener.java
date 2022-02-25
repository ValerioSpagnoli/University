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

import javax.swing.JTextField;

public class ClientListener implements ActionListener{
	
	private static final String CONNECT = "connect";
	private static final String DISCONNECT = "disconnect";
	private static final String START = "start";
	private static final String STOP = "stop";
	private static final String RIVELA = "rivela";
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader;
	
	private Logger logger = Logger.getLogger("client.ClientListener");
	
	private Socket socket;
	private OutputStream outputStream;
	private PrintWriter printWriter;
	private Scanner scanner;
	
	public ClientListener(Frame frame, JTextField ipAddress, JTextField port) {
		this.frame = frame;
		this.ipAddress = ipAddress;
		this.port = port;
	}
	
	public void setupConnection() throws IllegalArgumentException, UnknownHostException, IOException {
		socket = new Socket(ipAddress.getText(), Integer.parseInt(port.getText()));
		outputStream = socket.getOutputStream();
		printWriter = new PrintWriter(outputStream);
		scanner = new Scanner(socket.getInputStream());
	}
	
	@Override
	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(CONNECT)) {
			try {
				setupConnection();
			} catch (IllegalArgumentException | IOException e) {
				logger.log(Level.SEVERE, "Errore nel collegamento al server");
				return;
			}
			connected = true;
			logger.log(Level.INFO, "Connessione al server riuscita");	
		}
		else if(command.equals(DISCONNECT)) {
			printWriter.println(command);
			printWriter.flush();
			printWriter.close();
			scanner.close();
			try {
				socket.close();
			} catch (IOException e) {
				logger.log(Level.INFO, "Errore nella chiusura della socket");
				return;
			}
			connected = false;
			transmitting = false;
			for(int i = 0; i<10; i++) {
				for(int j = 0; j<10; j++) {
					frame.btnGrid[i][j].reset();
				}
			}
			
			
			logger.log(Level.INFO, "Connessione al server interrotta");
			
		}
		else if(command.equals(START)) {
			
			for(int i = 0; i<10; i++) {
				for(int j = 0; j<10; j++) {
					frame.btnGrid[i][j].reset();
					frame.btnGrid[i][j].setEnabled(false);
				}
			}
			
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
		else if(command.equals(RIVELA)) {
			for(int i = 0; i<10; i++) {
				for(int j = 0; j<10; j++) {
					frame.btnGrid[i][j].setSelected(true);
				}
			}
			transmitting = false;
		}
		frame.setButtons(connected, transmitting);
	}

}
