package app;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Frame extends JFrame{
	
	
	final JFrame frame = new JFrame();
	final Container contentPane = frame.getContentPane();
	final BorderLayout frameLayout = new BorderLayout();
	
	//northPanel
	
	JPanel northPanel = new JPanel();
	FlowLayout northLayout = new FlowLayout();
	
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	JLabel ipAddressLabel = new JLabel("IP Address");
	JTextField ipAddressField = new JTextField(10);
	JLabel portLabel = new JLabel("Port");
	JTextField portField = new JTextField(10);
	
	//centerPanel
	
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(16, 16);
	public JPanel[][] ijMat;
	
	//southPanel
	
	JPanel southPanel = new JPanel();
	FlowLayout southLayout = new FlowLayout();
	
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disconnect");
	JButton clearBtn = new JButton("Clear");
	
	//Listener
	ActionListener listener = new ClientListener(this);
	
	public Frame() {
		frame.setTitle("Valerio Spagnoli 1887715");
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		
		//northPanel
		
		northPanel.setLayout(northLayout);
		northPanel.add(startBtn);
		northPanel.add(ipAddressLabel);
		northPanel.add(ipAddressField);
		northPanel.add(portLabel);
		northPanel.add(portField);
		northPanel.add(stopBtn);
		
		//centerPanel
		
		centerPanel.setLayout(centerLayout);
		
		ijMat = new JPanel[16][16];
		
		for(int i = 0; i <16; i++) {
			for(int j = 0; j<16; j++) {
				JPanel ijPanel = new JPanel();
				ijPanel.setBackground(Color.LIGHT_GRAY);
				centerPanel.add(ijPanel);
				ijMat[i][j] = ijPanel; 
			}
		}
		
		//southPanel
		
		southPanel.setLayout(southLayout);
		southPanel.add(connectBtn);
		southPanel.add(disconnectBtn);
		southPanel.add(clearBtn);
		
		//listener settings
		
		startBtn.addActionListener(listener);
		startBtn.setActionCommand(ClientListener.START);
		stopBtn.addActionListener(listener);
		stopBtn.setActionCommand(ClientListener.STOP);
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand(ClientListener.CONNECT);
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand(ClientListener.DISCONNECT);
		clearBtn.addActionListener(listener);
		clearBtn.setActionCommand(ClientListener.CLEAR);
		
		//add on contentPanel
		
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		
		frame.pack();
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
			
	}
	
	public void clear() {
		for(int i = 0; i<16; i++) {
			for(int j = 0; j<16; j++) {
				ijMat[i][j].setBackground(Color.LIGHT_GRAY);
			}
		}
	}
	
	public void setButton(boolean connected, boolean downloading) {
		if(!connected) {
			startBtn.setEnabled(false);
			stopBtn.setEnabled(false);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			clearBtn.setEnabled(false);
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		}
		else {
			if(!downloading) {
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				clearBtn.setEnabled(true);
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
			}
			else {
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				clearBtn.setEnabled(false);
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
			}
		}
	}
}
