package client;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
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
	private static final String IMAGE1 = "image1";
	private static final String IMAGE2 = "image2";
	private static final String IMAGE3 = "image3";
	private static final String IMAGE4 = "image4";
	private static final String IMAGE5 = "image5";
	private static final String STOP = "stop";
	
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
			frame.centerArea.setText("");
			try {
				setupConnection();
			} catch (NumberFormatException | IOException e) {
				logger.log(Level.SEVERE, "Errore nel collegamento al server");
				System.exit(0);
			}
			logger.log(Level.INFO, "Connessione al server riuscita");
			connected = true;
			transmitting = false;
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
			logger.log(Level.INFO, "Connessione al server interrotta");
			connected = false;
			transmitting = false;
			
		}
		else if(command.equals(IMAGE1)) {
			downloader = new Downloader(frame, scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println("start:image1");
			printWriter.flush();
			downloaderThread.start();
			frame.centerArea.setText("******** DOWNLOAD INIZIATO ********\n\n");
			transmitting = true;
			logger.log(Level.INFO, "Avviato download Image 1");
		}
		else if(command.equals(IMAGE2)) {
			downloader = new Downloader(frame, scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println("start:image2");
			printWriter.flush();
			downloaderThread.start();
			frame.centerArea.setText("******** DOWNLOAD INIZIATO ********\n\n");
			transmitting = true;
			logger.log(Level.INFO, "Avviato download Image 2");
		}
		else if(command.equals(IMAGE3)) {
			downloader = new Downloader(frame, scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println("start:image3");
			printWriter.flush();
			downloaderThread.start();
			frame.centerArea.setText("******** DOWNLOAD INIZIATO ********\n\n");
			transmitting = true;
			logger.log(Level.INFO, "Avviato download Image 3");
		}
		else if(command.equals(IMAGE4)) {
			downloader = new Downloader(frame, scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println("start:image4");
			printWriter.flush();
			downloaderThread.start();
			frame.centerArea.setText("******** DOWNLOAD INIZIATO ********\n\n");
			transmitting = true;
			logger.log(Level.INFO, "Avviato download Image 4");
		}
		else if(command.equals(IMAGE5)) {
			downloader = new Downloader(frame, scanner);
			Thread downloaderThread = new Thread(downloader);
			printWriter.println("start:image5");
			printWriter.flush();
			downloaderThread.start();
			frame.centerArea.setText("******** DOWNLOAD INIZIATO ********\n\n");
			transmitting = true;
			logger.log(Level.INFO, "Avviato download Image 5");
		}
		else if(command.equals(STOP)) {
			printWriter.println(command);
			printWriter.flush();
			transmitting = false;
			logger.log(Level.INFO, "Download interrotto");
		}
		frame.setButtons(connected, transmitting);
	}

}
