package clientApp;
import client.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;



public class ClientListener implements ActionListener{
	
	public static final String START = "start";
	public static final String STOP = "stop";
	public static final String CONNECT = "connect";
	public static final String DISCONNECT = "disconnect";
	
	private JTextField ipAddressField;
	private JTextField portaField;
	private JTextField matricolaField;
	
	private boolean connected = false;
	private boolean transmitting = false;
	
	private Downloader downloader = null;
	
	private PrintWriter netPw;
	private Scanner scan;
	private Socket sock;
	private Display display;

	
	
	public ClientListener(Display display, JTextField ipAddr, JTextField porta, JTextField matricola) {
		this.display = display;	
		ipAddressField = ipAddr;
		portaField = porta;
		matricolaField = matricola;	
	}
	
	private void setupConnection() throws UnknownHostException, IOException{
		sock = new Socket(ipAddressField.getText(), Integer.parseInt(portaField.getText()));
		OutputStream os = sock.getOutputStream();
		netPw = new PrintWriter(new OutputStreamWriter(os));
		scan = new Scanner(sock.getInputStream());
	}
	
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		
		if(cmd.equals(ClientListener.CONNECT)) {
			try {
				setupConnection();
				connected = true;
				System.out.println("Connected");
			} catch(IOException ioe ) {
				JOptionPane.showMessageDialog(null, "Impossibile connettersi al server: \n" + ioe.getMessage());
				ioe.printStackTrace();
				return;
			}
			JOptionPane.showMessageDialog(null, "Connessione stabilita");
		}
		
		else if(cmd.equals(ClientListener.START)){
			try {
				downloader = new Downloader(matricolaField.getText(), scan);
			} catch(IOException ioe) {
				JOptionPane.showMessageDialog(null, "Impossibile creare il fle: \n" + ioe.getMessage());
				ioe.printStackTrace();
			}

			transmitting = true;
			netPw.println(cmd);
			netPw.flush();

			Thread t = new Thread(downloader);
			t.start();
			JOptionPane.showMessageDialog(null, "Download avviato");
		}
		
		else if(cmd.equals(ClientListener.STOP)){
			netPw.println(cmd);
			netPw.flush();
			transmitting = false;
			JOptionPane.showMessageDialog(null, "Download fermato");
		}
		
		else if(cmd.equals(ClientListener.DISCONNECT)){
			netPw.println(ClientListener.DISCONNECT);
			netPw.flush();
			netPw.close();
			scan.close();
			connected = false;
			try {
				sock.close();
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
			JOptionPane.showMessageDialog(null, "Connessione chiusa");
		}
		
		display.setButtons(connected, transmitting);
	}
}










