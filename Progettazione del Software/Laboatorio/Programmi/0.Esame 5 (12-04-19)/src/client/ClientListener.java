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
	private static final String DOWNLOAD = "download";
	private static final String INTERROMPI = "interrompi";
	private static final String STARK = "stark";
	private static final String TARGARYAN = "targaryen";
	private static final String LANNISTER = "lannister";
	
	private Downloader downloader;
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
	
	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(CONNECT)) {
			try {
				setupConnection();
			} catch (IllegalArgumentException e) {
				logger.log(Level.SEVERE, "Errore nell'inserimento della porta");
				return;
			} catch (UnknownHostException e) {
				logger.log(Level.SEVERE, "Errore, server sconosciuto");
				return;
			} catch (IOException e) {
				logger.log(Level.SEVERE, "Errore nella connessione al server");
				return;
			}
			logger.log(Level.INFO, "Connessione al server riuscita");
			connected = true;
		}
		else if(command.equals(DISCONNECT)) {
			printWriter.println(command);
			printWriter.flush();
			printWriter.close();
			scanner.close();
			try {
				socket.close();
			} catch (IOException e) {
				logger.log(Level.SEVERE, "Errore nella chiusura della socket");
			}
			connected = false;
			logger.log(Level.INFO, "Connessione interrotta");
		}
		else if(command.equals(DOWNLOAD)) {
			downloader = new Downloader(frame, scanner);
			printWriter.println(command);
			printWriter.flush();
			Thread downloaderThread = new Thread(downloader);
			downloaderThread.start();
			transmitting = true;
			logger.log(Level.INFO, "Download avviato");
		}
		else if(command.equals(INTERROMPI)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			logger.log(Level.INFO, "Download interrotto");
		}
		else if(command.equals(STARK)) {
			printWriter.println(command);
			printWriter.flush();
		}
		else if(command.equals(TARGARYAN)) {
			printWriter.println(command);
			printWriter.flush();
		}
		else if(command.equals(LANNISTER)) {
			printWriter.println(command);
			printWriter.flush();
		}
		frame.setButtons(connected, transmitting);
		
	}

}
