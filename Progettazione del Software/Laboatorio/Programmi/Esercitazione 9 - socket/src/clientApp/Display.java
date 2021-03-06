package clientApp;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;


public class Display extends JFrame{
	
	
	final BorderLayout borderLayout = new BorderLayout();
	
	//pannello centro
	final JPanel centroPanel = new JPanel();
	final GridLayout centroGridLayout = new GridLayout(4,8);
	final JLabel matricolaText = new JLabel("Matricola");
	final JTextField matricola = new JTextField(20);
	final JLabel IPaddressText = new JLabel("IP Address");
	final JTextField IPaddress = new JTextField(20);
	final JLabel portaText = new JLabel("Porta");
	final JTextField porta = new JTextField(20);
	final JLabel nullText = new JLabel("");
	
	//pannello sud
	final JPanel sudPanel = new JPanel();
	final FlowLayout sudFlowLayout = new FlowLayout();
	final JButton connect = new JButton("Connect");
	final JButton disconnect = new JButton("Disconnect");
	final JButton start = new JButton("Start");
	final JButton stop = new JButton("Stop");
	
	//final Listener ascoltatore = new Listener(this);
	
	public Display(){
		super ("Connection App");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(borderLayout);
		
		//costruzione centroPanel
		centroPanel.setLayout(centroGridLayout);
		centroPanel.add(matricolaText);
		centroPanel.add(IPaddressText);
		centroPanel.add(matricola);
		centroPanel.add(IPaddress);
		centroPanel.add(portaText);
		centroPanel.add(nullText);
		centroPanel.add(porta);
		matricola.setBorder(BorderFactory.createLineBorder(Color.black));
		IPaddress.setBorder(BorderFactory.createLineBorder(Color.black));
		porta.setBorder(BorderFactory.createLineBorder(Color.black));
		
		
		//costruzione pannelllo sud
		sudPanel.setLayout(sudFlowLayout);
		sudPanel.add(connect);
		sudPanel.add(disconnect);
		sudPanel.add(start);
		sudPanel.add(stop);
		
		//aggiunta del centroPanel e del sudPanel al contentPane
		this.getContentPane().add(centroPanel, BorderLayout.CENTER);
		this.getContentPane().add(sudPanel, BorderLayout.SOUTH);
		
		//Listener
		ActionListener listener = new ClientListener(this, IPaddress, porta, matricola);
		
		connect.setActionCommand(ClientListener.CONNECT);
		connect.addActionListener(listener);
		disconnect.setActionCommand(ClientListener.DISCONNECT);
		disconnect.addActionListener(listener);
		start.setActionCommand(ClientListener.START);
		start.addActionListener(listener);
		stop.setActionCommand(ClientListener.STOP);
		stop.addActionListener(listener);
		
		//altre impostazioni grafiche
		this.setLocationRelativeTo(null);
		setButtons(false, false);	
	}
	
	public void setButtons(boolean connected, boolean transmitting) {
		if(connected) {
			connect.setEnabled(false);
			setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
			
			if(transmitting) {
				disconnect.setEnabled(false);
				stop.setEnabled(true);
				start.setEnabled(false);
			}
			else {
				stop.setEnabled(false);
				start.setEnabled(true);
				disconnect.setEnabled(true);
			}
		}
		else {
			setDefaultCloseOperation(EXIT_ON_CLOSE);
			connect.setEnabled(true);
			disconnect.setEnabled(false);
			stop.setEnabled(false);
			start.setEnabled(false);	
		}
	}
	
}
