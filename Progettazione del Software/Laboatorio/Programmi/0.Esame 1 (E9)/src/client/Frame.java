package client;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Frame extends JFrame{
	
	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	//north
	JPanel northPanel = new JPanel();
	
	//center
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(4,2);
	
	JLabel matricolaLabel = new JLabel("Matricola");
	JLabel ipAddressLabel = new JLabel("IP Address");
	JLabel portaLabel = new JLabel("Porta");
	
	JTextField matricolaText = new JTextField();
	JTextField ipAddressText = new JTextField();
	JTextField portaText = new JTextField();
	
	JLabel spazio1 = new JLabel();
	JLabel spazio2 = new JLabel();
	
	//south
	JPanel southPanel = new JPanel();
	FlowLayout southLayout = new FlowLayout();
	
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disconnect");
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	
	//listener
	ActionListener listener = new ClientListener(this, matricolaText, ipAddressText, portaText);
	
	public Frame() {
		
		Container contentPane = frame.getContentPane();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);

		//costruzione center
		centerPanel.setLayout(centerLayout);
		centerPanel.add(matricolaLabel);
		centerPanel.add(ipAddressLabel);
		centerPanel.add(matricolaText);
		centerPanel.add(ipAddressText);
		centerPanel.add(portaLabel);
		centerPanel.add(spazio1);
		centerPanel.add(portaText);
		centerPanel.add(spazio2);
		
		//costruzione south
		southPanel.setLayout(southLayout);
		southPanel.add(connectBtn);
		southPanel.add(disconnectBtn);
		southPanel.add(startBtn);
		southPanel.add(stopBtn);
		
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
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
			}
		}
	}
	
	
}
