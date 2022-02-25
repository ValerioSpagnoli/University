package client;

import javax.swing.*;
import javax.swing.border.TitledBorder;

import java.awt.*;
import java.awt.event.ActionListener;

public class Frame extends JFrame{

	JFrame frame = new JFrame();
	BorderLayout frameLayout = new BorderLayout();
	
	//northPanel
	JPanel northPanel = new JPanel();
	JLabel ipAddressLabel = new JLabel("Server Address");
	JLabel portLabel = new JLabel("Port");
	JTextField ipAddressText = new JTextField("127.0.0.1");
	JTextField portText = new JTextField("4400");
	JButton connectBtn = new JButton("Connect");
	JButton disconnectBtn = new JButton("Disonnect");
	
	//centerPanel
	JPanel centerPanel = new JPanel();
	TitledBorder centerTitle = new TitledBorder("Console");
	JTextArea consoleText = new JTextArea(25, 80);
	JScrollPane consoleSroll = new JScrollPane(consoleText);

	//southPanel
	JPanel southPanel = new JPanel();
	JLabel commandLabel = new JLabel("Command");
	JTextField commandText = new JTextField(20);
	JButton executeBtn = new JButton("Execute");
	JButton interruptBtn = new JButton("Interrupt");
	
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
		centerPanel.setBorder(centerTitle);
		centerPanel.add(consoleSroll);
		consoleText.setEditable(false);
		consoleText.setText("Comandi disponibili: \n\n- LIST\n- GET:nome_file\n\n"
				+ "*********************************************************************************");
		
		//southPanel
		southPanel.add(commandLabel);
		southPanel.add(commandText);
		southPanel.add(executeBtn);
		southPanel.add(interruptBtn);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.pack();
		frame.setLocationRelativeTo(null);
		
		//settings listener
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand("CONNECT");
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand("DISCONNECT");
		executeBtn.addActionListener(listener);
		executeBtn.setActionCommand("EXECUTE");
		interruptBtn.addActionListener(listener);
		interruptBtn.setActionCommand("INTERRUPT");	
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			executeBtn.setEnabled(false);
			interruptBtn.setEnabled(false);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				executeBtn.setEnabled(true);
				interruptBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				executeBtn.setEnabled(false);
				interruptBtn.setEnabled(true);
			}
		}
	}
	
	
}
