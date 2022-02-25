package client;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;

public class Frame extends JFrame{
	
	private JFrame frame = new JFrame();
	private BorderLayout frameLayout = new BorderLayout();
	
	//northPanel
	private JPanel northPanel = new JPanel();
	private FlowLayout northLayout = new FlowLayout();
	private JButton startBtn = new JButton("Start");
	private JButton stopBtn = new JButton("Stop");
	private JLabel ipAdrressLabel = new JLabel("IP Address");
	private JLabel portLabel = new JLabel("Port");
	private JTextField ipAddressText = new JTextField(10);
	private JTextField portText = new JTextField(10);
	
	//centerPanel
	private JPanel centerPanel = new JPanel();
	private GridLayout centerLayout = new GridLayout(1, 5);
	ColoredButton block1 = new ColoredButton();
	ColoredButton block2 = new ColoredButton();
	ColoredButton block3 = new ColoredButton();
	ColoredButton block4 = new ColoredButton();
	ColoredButton block5 = new ColoredButton();
	ColoredButton[] gridBlock = new ColoredButton[5];
	
	//southPanel
	private JPanel southPanel = new JPanel();
	private FlowLayout southLayout = new FlowLayout();
	private JButton connectBtn = new JButton("Connect");
	private JButton disconnectBtn = new JButton("Disonnect");
	private JButton clearBtn = new JButton("Clear");
	
	private ActionListener listener = new ClientListener(this, ipAddressText, portText);
	
	public Frame() {
		
		frame.setTitle("Valerio Spagnoli 1887715");
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLayout(frameLayout);
		
		Container contentPane = frame.getContentPane();
		
		//northPanel
		northPanel.setLayout(northLayout);
		northPanel.add(startBtn);
		northPanel.add(ipAdrressLabel);
		northPanel.add(ipAddressText);
		northPanel.add(portLabel);
		northPanel.add(portText);
		northPanel.add(stopBtn);
		
		//centerPanel
		centerPanel.setLayout(centerLayout);;
		centerPanel.add(block1);
		gridBlock[0] = block1;
		centerPanel.add(block2);
		gridBlock[1] = block2;
		centerPanel.add(block3);
		gridBlock[2] = block3;
		centerPanel.add(block4);
		gridBlock[3] = block4;
		centerPanel.add(block5);
		gridBlock[4] = block5;
		
		//southPanel
		southPanel.setLayout(southLayout);
		southPanel.add(connectBtn);
		southPanel.add(disconnectBtn);
		southPanel.add(clearBtn);
		
		//contentPane
		contentPane.add(northPanel, BorderLayout.NORTH);
		contentPane.add(centerPanel, BorderLayout.CENTER);
		contentPane.add(southPanel, BorderLayout.SOUTH);
		
		//settings
		setButtons(false, false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);
		frame.setSize(700, 200);
		
		//listener settings
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
			clearBtn.setEnabled(true);
		}
		else {
			if(!transmitting) {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(true);
				stopBtn.setEnabled(false);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(true);
				clearBtn.setEnabled(true);
			}
			else {
				frame.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				startBtn.setEnabled(false);
				stopBtn.setEnabled(true);
				connectBtn.setEnabled(false);
				disconnectBtn.setEnabled(false);
				clearBtn.setEnabled(false);
			}
		}
	}
	
	
	
}
