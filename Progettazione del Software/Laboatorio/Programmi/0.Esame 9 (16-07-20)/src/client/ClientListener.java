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

	private static final String CONNECT = "CONNECT";
	private static final String DISCONNECT = "DISCONNECT";
	private static final String EXECUTE = "EXECUTE";
	private static final String INTERRUPT = "INTERRUPT";
	
	private Frame frame;
	private JTextField ipAddress;
	private JTextField port;
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader;
	private Logger logger = Logger.getLogger("client.ClientListener");
	private Socket socket;
	private PrintWriter printWriter;
	private Scanner scanner;
	
	public ClientListener(Frame frame, JTextField ipAddress, JTextField port) {
		this.frame = frame;
		this.ipAddress = ipAddress;
		this.port = port;
	}
	
	private void setupConnection() throws NumberFormatException, UnknownHostException, IOException {
		socket = new Socket(ipAddress.getText(), Integer.parseInt(port.getText()));
		printWriter = new PrintWriter(socket.getOutputStream());
		scanner = new Scanner(socket.getInputStream());
	}
	
	@Override
	public void actionPerformed(ActionEvent event) {
		String command = event.getActionCommand();
		
		if(command.equals(CONNECT)) {
			frame.consoleText.setText("Comandi disponibili: \n\n- LIST\n- GET:nome_file\n\n"
					+ "*********************************************************************************");
			try {
				setupConnection();
			} catch (NumberFormatException | IOException e) {
				logger.log(Level.SEVERE,"Errore durante la connessione al server");
				System.exit(0);
			}
			connected = true;
			transmitting = false;
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
				System.exit(0);
			}
			connected = false;
			transmitting = true;
			logger.log(Level.INFO, "Connessione al server interrotta");
		}
		else if(command.equals(EXECUTE)) {
			downloader = new Downloader(frame,scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println(frame.commandText.getText());
			printWriter.flush();
			downloaderThread.start();
			transmitting = true;
			logger.log(Level.INFO,"Download avviato");	
		}
		else if(command.equals(INTERRUPT)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			logger.log(Level.INFO, "Download interrotto");
		}
		frame.setButtons(connected, transmitting);
	}
}
