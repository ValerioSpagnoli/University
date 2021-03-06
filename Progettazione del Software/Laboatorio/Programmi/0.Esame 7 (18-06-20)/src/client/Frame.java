package client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class Frame extends JFrame{
	
	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	//north 
	JPanel northPanel = new JPanel();
	JLabel ipAddressLabel = new JLabel("Server Address");
	JTextField ipAddressText = new JTextField("127.0.0.1");
	JLabel portLabel = new JLabel("Port");
	JTextField portText = new JTextField("4400");
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disonnect");
	
	//center
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(10,10);
	BoardButton[][] btnGrid = new BoardButton[10][10];
	
	//south
	JPanel southPanel = new JPanel();
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	JButton rivelaBtn = new JButton("Rivela");
	
	ActionListener listener = new ClientListener(this, ipAddressText, portText);
	
	public Frame() {
		frame.setTitle("Valerio Spagnoli 1887715");
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		Container contentPane = frame.getContentPane();
		
		//north
		northPanel.add(ipAddressLabel);
		northPanel.add(ipAddressText);
		northPanel.add(portLabel);
		northPanel.add(portText);
		northPanel.add(connectBtn);
		northPanel.add(disconnectBtn);
	
		//center
		centerPanel.setLayout(centerLayout);
		for(int i = 0; i<10; i++) {
			for(int j = 0; j<10; j++) {
				BoardButton btn = new BoardButton(this);
				btn.setEnabled(false);
				centerPanel.add(btn);
				btnGrid[i][j] = btn;
			}
		}
		
		//south
		southPanel.add(startBtn);
		southPanel.add(stopBtn);
		southPanel.add(rivelaBtn);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.setSize(500, 550);
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
		rivelaBtn.addActionListener(listener);
		rivelaBtn.setActionCommand("rivela");
		
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			startBtn.setEnabled(false);
			stopBtn.setEnabled(false);
			rivelaBtn.setEnabled(false);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				rivelaBtn.setEnabled(true);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				rivelaBtn.setEnabled(false);
			}
		}
	}
	
	
	
}
