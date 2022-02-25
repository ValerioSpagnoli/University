package client;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.Random;

import javax.swing.*;

public class Frame extends JFrame{
	
	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	Container contentPane = frame.getContentPane();
	
	//north
	JPanel northPanel = new JPanel();
	JLabel ipAddressLabel = new JLabel("Server Address");
	JLabel portLabel = new JLabel("Port");
	JTextField ipAddressText = new JTextField("127.0.0.1");
	JTextField portText = new JTextField("4400");
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disonnect");
	
	//center
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(3,5);
	JTextField[][] ticketGrid = new JTextField[3][5];
	
	//south
	JPanel southPanel = new JPanel();
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	
	//east
	JPanel eastPanel = new JPanel();
	JTextArea elencoEstrattiText = new JTextArea(15,20);
	JScrollPane elencoEstrattiScroll = new JScrollPane(elencoEstrattiText);
	
	ActionListener listener = new ClientListener(this, ipAddressText, portText);
	
	public Frame() {
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		frame.setTitle("Valerio Spagnoli 1887715");
		
		
		//north
		northPanel.add(ipAddressLabel);
		northPanel.add(ipAddressText);
		northPanel.add(portLabel);
		northPanel.add(portText);
		northPanel.add(connectBtn);
		northPanel.add(disconnectBtn);
		
		//center
		centerPanel.setLayout(centerLayout);
		for(int i = 0; i<3; i++) {
			for(int j = 0; j<5; j++) {
				JTextField ticket = new JTextField("");
				ticket.setEditable(false);
				centerPanel.add(ticket);
				ticketGrid[i][j] = ticket;
			}
		}
		
		//south
		southPanel.add(startBtn);
		southPanel.add(stopBtn);
		
		//east
		eastPanel.add(elencoEstrattiScroll);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		contentPane.add(eastPanel, BorderLayout.EAST);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.setSize(700, 350);
		frame.setLocationRelativeTo(null);
	
		//settings listener
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand("connect");
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand("disconnect");
		startBtn.addActionListener(listener);
		startBtn.setActionCommand("start");
		stopBtn.addActionListener(listener);
		stopBtn.setActionCommand("stop");
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			startBtn.setEnabled(false);
			stopBtn.setEnabled(false);
		}
		else {
			frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
			if(!transmitting) {
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);;
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
			}
		}
	}
	
	static int[] number = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
    public static void generaNumeri(int[] number) {
		Random random = new Random();
		int k = 0;
		while(k<15) {
			 boolean inserito = false;
			 int n = random.nextInt(90);
			 for(int i = 0; i<15 && !inserito; i++) {
				 if(number[i]==n) {
					 inserito = true;
				 }
			 }
			 if(!inserito) {
				 number[k] = n;
				 k++;
			 }
		}
		Arrays.sort(number);
	}
	
	
}
