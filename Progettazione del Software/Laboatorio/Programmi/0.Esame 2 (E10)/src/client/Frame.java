package client;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;

public class Frame extends JFrame{
	
	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	
	//northPanel
	JPanel northPanel = new JPanel();
	FlowLayout northLayout = new FlowLayout();
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	JLabel ipAddressLabel = new JLabel("IP Address");
	JLabel portLabel = new JLabel("Port");
	JTextField ipAddressText = new JTextField(10);
	JTextField portText = new JTextField(10);
	
	//centerPanel
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(16,16);
	JPanel[][] gridPanel = new JPanel[16][16];
	
	//southPanel
	JPanel southPanel = new JPanel();
	FlowLayout southLayout = new FlowLayout();
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disonnect");
	JButton clearBtn = new JButton("Clear");
	
	ActionListener listener = new ClientListener(this);
	
	public Frame() {
		frame.setTitle("Valerio Spagnoli 1887715");
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		Container contentPane = frame.getContentPane();
		
		//costruzione northPanel
		northPanel.setLayout(northLayout);
		northPanel.add(startBtn);
		northPanel.add(ipAddressLabel);
		northPanel.add(ipAddressText);
		northPanel.add(portLabel);
		northPanel.add(portText);
		northPanel.add(stopBtn);
		
		//costruzione centerPanel
		centerPanel.setLayout(centerLayout);
		for(int i = 0; i<16; i++) {
			for(int j = 0; j<16; j++) {
				JPanel tessera = new JPanel();
				tessera.setBackground(Color.LIGHT_GRAY);
				//tessera.setBorder(BorderFactory.createLineBorder(Color.black));
				centerPanel.add(tessera);
				gridPanel[i][j] = tessera;
			}
		}
		
		//costruzone southPanel
		southPanel.setLayout(southLayout);
		southPanel.add(connectBtn);
		southPanel.add(disconnectBtn);
		southPanel.add(clearBtn);
		
		//costruzione frame
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false, false);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
		frame.pack();
		
		//settings listener
		startBtn.addActionListener(listener);
		startBtn.setActionCommand("start");
		stopBtn.addActionListener(listener);
		stopBtn.setActionCommand("stop");
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand("connect");
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand("disconnect");
		clearBtn.addActionListener(listener);
		clearBtn.setActionCommand("clear");
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			startBtn.setEnabled(false);
			stopBtn.setEnabled(false);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			clearBtn.setEnabled(false);
		}
		else {
			if(transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				clearBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				clearBtn.setEnabled(true);
			}
		}
	}
	
	
}
