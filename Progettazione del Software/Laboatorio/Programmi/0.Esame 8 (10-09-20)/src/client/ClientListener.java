package client;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
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

import javax.swing.JPanel;
import javax.swing.JTextField;

public class ClientListener implements ActionListener{
	
	private static final String CONNECT = "connect";
	private static final String DISCONNECT = "disconnect";
	private static final String START = "start";
	private static final String STOP = "stop";
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	private Logger logger = Logger.getLogger("client.ClientListener");
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader;
	
	private Socket socket;
	private OutputStream outputStream;
	private PrintWriter printWriter;
	private Scanner scanner;
	
	public ClientListener(Frame frame, JTextField ipAddress, JTextField port) {
		this.frame = frame;
		this.ipAddress = ipAddress;
		this.port = port;
	}
	
	private void setupConnection() throws NumberFormatException, UnknownHostException, IOException {
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
			} catch (NumberFormatException | IOException e) {
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
				logger.log(Level.SEVERE, "Errore nella chiusura della socket");
				return;
			}
			connected = false;
			logger.log(Level.INFO, "Connessione al server interrotta");	
		}
		else if(command.equals(START)) {
			nuovaCartella();
			frame.elencoEstrattiText.setText("");
			for(int i = 0; i<3; i++) {
				for(int j = 0; j<5; j++) {
					frame.ticketGrid[i][j].setBackground(Color.WHITE);
				}
			}
			downloader = new Downloader(frame,scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println(command);
			printWriter.flush();
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
		frame.setButtons(connected, transmitting);
		
	}

	public void nuovaCartella() {
		int[] number = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int k = 0;
		frame.generaNumeri(number);
		for(int j = 0; j<5; j++) {
			for(int i = 0; i<3; i++) {
				frame.ticketGrid[i][j].setText("" + number[k]);
				k++;
			}
		}
	}
	
	
	
	
	
	
	
}
