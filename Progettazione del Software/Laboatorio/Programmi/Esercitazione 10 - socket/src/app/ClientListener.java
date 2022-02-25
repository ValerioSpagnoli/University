package app;

import client.Downloader;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;

import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class ClientListener implements ActionListener{

	public static final String START = "start";
	public static final String STOP = "stop";
	public static final String CONNECT = "connect";
	public static final String DISCONNECT = "disconnect";
	public static final String CLEAR = "clear";
	
	private Frame frame;
	
	private boolean connected = false;
	private boolean downloading = false;
	
	private Downloader downloader;
	
	private PrintWriter netPw;
	private Scanner scan;
	private Socket socket;
	
	
	public ClientListener(Frame f) {
		frame = f;
		frame.setButton(connected, downloading);
	}
	
	private void setupConnection() throws UnknownHostException, IOException {
		socket = new Socket(frame.ipAddressField.getText(), Integer.parseInt(frame.portField.getText()));
		OutputStream os = socket.getOutputStream();
		netPw = new PrintWriter(new OutputStreamWriter(os));
		scan = new Scanner(socket.getInputStream());
	}

	
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		
		if(e.getActionCommand().equals(CONNECT)) {
			try {
				setupConnection();
				connected = true;
				downloading = false;
				frame.setButton(connected, downloading);
				System.out.println("Connected");
			} catch (IOException ioe) {
				JOptionPane.showMessageDialog(null, "Impossibile connettersi");
				ioe.printStackTrace();
				return;
			}
		}
		
		else if(e.getActionCommand().equals(START)) {
			downloader = new Downloader(scan, frame);
			connected = true;
			downloading = true;
			frame.setButton(connected, downloading);
			netPw.println(cmd);
			netPw.flush();
			
			Thread t = new Thread(downloader);
			t.start();
			JOptionPane.showMessageDialog(null, "Download avviato");
		}
		
		else if(e.getActionCommand().equals(STOP)) {
			netPw.println(cmd);
			netPw.flush();
			connected = true;
			downloading = false;
			frame.setButton(connected, downloading);
			JOptionPane.showMessageDialog(null, "Download fermato");
		}
		else if(e.getActionCommand().equals(DISCONNECT)) {
			netPw.println(cmd);
			netPw.flush();
			netPw.close();
			scan.close();
			try {
				socket.close();
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
			connected = false;
			downloading = false;
			frame.setButton(connected, downloading);
			JOptionPane.showMessageDialog(null, "Connessione chiusa");
		}
		else if(e.getActionCommand().equals(CLEAR)) {
			frame.clear();
			connected = true;
			downloading = false;
			frame.setButton(connected, downloading);
		}	
	}
}
