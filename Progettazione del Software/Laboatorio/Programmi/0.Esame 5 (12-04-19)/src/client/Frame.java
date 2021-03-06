package client;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;

public class Frame extends JFrame{
	
	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	//north
	JPanel northPanel = new JPanel();
	JPanel panel1 = new JPanel();
	JPanel panel2 = new JPanel();
	BorderLayout northLayout = new BorderLayout();
	GridLayout panel2Layout = new GridLayout(1,3);
	JLabel ipAddressLabel = new JLabel("IP Address");
	JLabel portLabel = new JLabel("Port");
	JTextField ipAddressText = new JTextField(10);
	JTextField portText = new JTextField(10);
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disconnect");
	JButton starkBtn = new JButton("STARK");
	JButton targaryenBtn = new JButton("TARGARYEN");
	JButton lannisterBtn = new JButton("LANNISTER");
	
	//center
	JPanel centerPanel = new JPanel();
	GridLayout centerLayout = new GridLayout(1,3);
	JTextArea starkText = new JTextArea(25,20);
	JTextArea targaryenText = new JTextArea(25,20);
	JTextArea lannisterText = new JTextArea(25,20);
	
	//south
	JPanel southPanel = new JPanel();
	JButton downloadBtn = new JButton("Download");
	JButton interrompiBtn = new JButton("Interrompi");
	
	ActionListener listener = new ClientListener(this, ipAddressText, portText);
	
	public Frame() {
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		frame.setTitle("Valerio Spagnoli 1887715");
		Container contentPane = frame.getContentPane();
		
		//north
		northPanel.setLayout(northLayout);
		
		panel1.add(ipAddressLabel);
		panel1.add(ipAddressText);
		panel1.add(portLabel);
		panel1.add(portText);
		panel1.add(connectBtn);
		panel1.add(disconnectBtn);
		
		panel2.setLayout(panel2Layout);
		panel2.add(starkBtn);
		panel2.add(targaryenBtn);
		panel2.add(lannisterBtn);
		
		northPanel.add(panel1, BorderLayout.NORTH);
		northPanel.add(panel2, BorderLayout.SOUTH);
		
		//center
		centerPanel.setLayout(centerLayout);
		
		centerPanel.add(starkText);
		centerPanel.add(targaryenText);
		centerPanel.add(lannisterText);
		
		starkText.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		targaryenText.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		lannisterText.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		
		//south
		southPanel.add(downloadBtn);
		southPanel.add(interrompiBtn);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);
		frame.pack();
		
		//settings listener
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand("connect");
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand("disconnect");
		downloadBtn.addActionListener(listener);
		downloadBtn.setActionCommand("download");
		interrompiBtn.addActionListener(listener);
		interrompiBtn.setActionCommand("interrompi");
		starkBtn.addActionListener(listener);
		starkBtn.setActionCommand("stark");
		targaryenBtn.addActionListener(listener);
		targaryenBtn.setActionCommand("targaryen");
		lannisterBtn.addActionListener(listener);
		lannisterBtn.setActionCommand("lannister");
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			downloadBtn.setEnabled(false);
			interrompiBtn.setEnabled(false);
			starkBtn.setEnabled(false);
			targaryenBtn.setEnabled(false);
			lannisterBtn.setEnabled(false);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				downloadBtn.setEnabled(true);
				interrompiBtn.setEnabled(false);
				starkBtn.setEnabled(false);
				targaryenBtn.setEnabled(false);
				lannisterBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				downloadBtn.setEnabled(false);
				interrompiBtn.setEnabled(true);
				starkBtn.setEnabled(true);
				targaryenBtn.setEnabled(true);
				lannisterBtn.setEnabled(true);
			}
		}
	}
	
	
}
