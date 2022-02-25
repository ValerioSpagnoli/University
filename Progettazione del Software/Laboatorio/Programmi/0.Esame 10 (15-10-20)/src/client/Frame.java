package client;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.border.TitledBorder;

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
	JButton disconnectBtn = new JButton("Disconnect");
	
	//centerpanel
	JPanel centerPanel = new JPanel();
	TitledBorder centerTitle = new TitledBorder("Image");
	JTextArea centerArea = new JTextArea(25,80);
	JScrollPane centerScroll = new JScrollPane(centerArea);
	
	//southPanel
	JPanel southPanel = new JPanel();
	JButton image1Btn = new JButton("Image 1");
	JButton image2Btn = new JButton("Image 2");
	JButton image3Btn = new JButton("Image 3");
	JButton image4Btn = new JButton("Image 4");
	JButton image5Btn = new JButton("Image 5");
	JButton stopBtn = new JButton("Stop");
	
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
		centerPanel.add(centerScroll);
		centerArea.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 18));
		centerArea.setEditable(false);
		centerPanel.setBorder(centerTitle);
		
		//southPanel
		southPanel.add(image1Btn);
		southPanel.add(image2Btn);
		southPanel.add(image3Btn);
		southPanel.add(image4Btn);
		southPanel.add(image5Btn);
		southPanel.add(stopBtn);
	
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false,false);
		frame.setVisible(true);
		frame.pack();
		frame.setLocationRelativeTo(null);
		
		//listener settings
		connectBtn.addActionListener(listener);
		connectBtn.setActionCommand("connect");
		disconnectBtn.addActionListener(listener);
		disconnectBtn.setActionCommand("disconnect");
		image1Btn.addActionListener(listener);
		image1Btn.setActionCommand("image1");
		image2Btn.addActionListener(listener);
		image2Btn.setActionCommand("image2");
		image3Btn.addActionListener(listener);
		image3Btn.setActionCommand("image3");
		image4Btn.addActionListener(listener);
		image4Btn.setActionCommand("image4");
		image5Btn.addActionListener(listener);
		image5Btn.setActionCommand("image5");
		stopBtn.addActionListener(listener);
		stopBtn.setActionCommand("stop");
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(!connected) {
			frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
			connectBtn.setEnabled(true);
			disconnectBtn.setEnabled(false);
			image1Btn.setEnabled(false);
			image2Btn.setEnabled(false);
			image3Btn.setEnabled(false);
			image4Btn.setEnabled(false);
			image5Btn.setEnabled(false);
			stopBtn.setEnabled(false);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				image1Btn.setEnabled(true);
				image2Btn.setEnabled(true);
				image3Btn.setEnabled(true);
				image4Btn.setEnabled(true);
				image5Btn.setEnabled(true);
				stopBtn.setEnabled(false);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				image1Btn.setEnabled(false);
				image2Btn.setEnabled(false);
				image3Btn.setEnabled(false);
				image4Btn.setEnabled(false);
				image5Btn.setEnabled(false);
				stopBtn.setEnabled(true);
			}
		}
	}
	
}
