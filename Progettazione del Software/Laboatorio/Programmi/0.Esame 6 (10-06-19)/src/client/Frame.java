package client;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;

public class Frame extends JFrame{

	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	//northPanel
	JPanel northPanel = new JPanel();
	JLabel ipAddressLabel = new JLabel("IP Address");
	JLabel portLabel = new JLabel("Port");
	JTextField ipAddressText= new JTextField(10);
	JTextField portText = new JTextField(10);
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disconnect");
	
	//centerPanel
	JPanel centerPanel = new JPanel();
	JPanel panel1 = new JPanel();
	JPanel panel2 = new JPanel();
	JPanel panel3 = new JPanel();
	GridLayout centerLayout = new GridLayout(3,1);
	JLabel hexadecimalLabel = new JLabel("hexadecimal");
	JLabel decimalLabel = new JLabel("decimal        ");
	JLabel binaryLabel = new JLabel("binary          ");
	JTextField hexadecimalText = new JTextField(45);
	JTextField decimalText = new JTextField(45);
	JTextField binaryText = new JTextField(45);
	
	//southPanel
	JPanel southPanel = new JPanel();
	JButton startBtn = new JButton("Start");
	JButton stopBtn = new JButton("Stop");
	JButton convertiBtn = new JButton("Converti");
	
	//westPanel
	JPanel westPanel = new JPanel();
	JButton lettereBtn = new JButton("A-F");
	JButton cifreBtn = new JButton("0-9");
	
	ActionListener listener = new ClientListener(this, ipAddressText, portText);
	
	public Frame() {
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		frame.setTitle("Valerio Spagnoli 1887715");
		Container contentPane = frame.getContentPane();
		
		//northPanel
		northPanel.add(ipAddressLabel);
		northPanel.add(ipAddressText);
		northPanel.add(portLabel);
		northPanel.add(portText);
		northPanel.add(connectBtn);
		northPanel.add(disconnectBtn);
		
		//centerPanel
		centerPanel.setLayout(centerLayout);
		panel1.add(hexadecimalLabel);
		panel1.add(hexadecimalText);
		panel2.add(decimalLabel);
		panel2.add(decimalText);
		panel3.add(binaryLabel);
		panel3.add(binaryText);
		centerPanel.add(panel1);
		centerPanel.add(panel2);
		centerPanel.add(panel3);
		
		hexadecimalText.setEditable(false);
		decimalText.setEditable(false);
		binaryText.setEditable(false);
		
		//southPanel
		southPanel.add(startBtn);
		southPanel.add(stopBtn);
		southPanel.add(convertiBtn);
		
		//westPanel
		westPanel.add(lettereBtn);
		westPanel.add(cifreBtn);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		contentPane.add(westPanel, BorderLayout.WEST);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);
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
		convertiBtn.addActionListener(listener);
		convertiBtn.setActionCommand("converti");
		lettereBtn.addActionListener(listener);
		lettereBtn.setActionCommand("lettere");
		cifreBtn.addActionListener(listener);
		cifreBtn.setActionCommand("cifre");
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			startBtn.setEnabled(false);
			stopBtn.setEnabled(false);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			convertiBtn.setEnabled(false);
			lettereBtn.setEnabled(false);
			cifreBtn.setEnabled(false);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				convertiBtn.setEnabled(true);
				lettereBtn.setEnabled(false);
				cifreBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				convertiBtn.setEnabled(false);
				lettereBtn.setEnabled(true);
				cifreBtn.setEnabled(true);
			}
		}
	}
	
	
}
