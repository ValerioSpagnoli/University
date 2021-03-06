package display;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import java.util.logging.*;


public class Listener implements ActionListener{
	
	public static final String START = "Start";
	public static final String STOP = "Stop";
	public static final String CONNECT = "Connect";
	public static final String DISCONNECT = "Disconnect";
	
	private JTextField IPaddressField;
	private JTextField portaField;
	private JTextField matricolaField;
	
	private boolean connect = false;
	private boolean transmitting = false;
	
	private Display display;
	private boolean connected;
	
	//private static Logger logger = Logger.getLogger("Connect App");
	
	public Listener(Display display, JTextField ipAddress, JTextField porta, JTextField matricola) {
		this.display = display;
		this.IPaddressField = ipAddress;
		this.matricolaField = matricola;
		this.portaField = porta;
	}
	
	private void setupConnection() {
		//logger.log(Level.INFO, "connect " + this.IPaddressField.getText() + ":" + this.portaField.getText());
		System.out.println("connect " + this.IPaddressField.getText() + ":" + this.portaField.getText());
	}
	
	//Override
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		if(cmd.equals(Listener.CONNECT)) {
			setupConnection();
			connected = true;
			JOptionPane.showMessageDialog(null, "Connessione stabilita");
		}
		else if(cmd.equals(Listener.START)){
			transmitting = true;
			//logger.log(Level.INFO, "Start");
			System.out.println("Start");
			JOptionPane.showMessageDialog(null, "Interazione avviata");
		}
		else if(cmd.equals(Listener.STOP)){
			transmitting = false;
			//logger.log(Level.INFO, "Stop");
			System.out.println("Stop");
			JOptionPane.showMessageDialog(null, "Interazione interrotta");
		}
		else if(cmd.equals(Listener.DISCONNECT)){
			connected = false;
			//logger.log(Level.INFO, "Disconnected");
			System.out.println("Disconnect");
			JOptionPane.showMessageDialog(null, "Connessione interrotta");
		}
		display.setButtons(connected, transmitting);
	}
	
}










