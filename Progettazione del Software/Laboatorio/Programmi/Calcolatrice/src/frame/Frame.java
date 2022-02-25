package frame;

import java.awt.*;
import javax.swing.*;

public class Frame extends JFrame{
	
	final BorderLayout borderLayout = new BorderLayout();
	
	//pannello nord
	final JPanel nordPanel = new JPanel();
	final JTextArea schermo = new JTextArea(5, 20);
	
	//pannello sud
	final JPanel sudPanel = new JPanel();
	final JPanel tastiera = new JPanel();
	final GridLayout tastieraLayout = new GridLayout(4,5);
	
	final JButton zero = new JButton("0");
	final JButton uno = new JButton("1");
	final JButton due = new JButton("2");
	final JButton tre = new JButton("3");
	final JButton quattro = new JButton("4");
	final JButton cinque = new JButton("5");
	final JButton sei = new JButton("6");
	final JButton sette = new JButton("7");
	final JButton otto = new JButton("8");
	final JButton nove = new JButton("9");
	final JButton somma = new JButton("+");
	final JButton differenza = new JButton("-");
	final JButton moltiplicazione = new JButton("x");
	final JButton divisione = new JButton("/");
	final JButton punto = new JButton(".");
	final JButton delete = new JButton("C");
	final JButton uguale = new JButton("=");
	final JButton nullBtn1 = new JButton("");
	final JButton nullBtn2 = new JButton("");
	final JButton nullBtn3 = new JButton("");
	
	//pannello centro
	final JPanel centroPanel = new JPanel();
	final JLabel centro = new JLabel();
	
	//listener
	final Listener listener = new Listener(this);
	
	//cotruttore
	public Frame() {
		super("Calcolatrice");
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.getContentPane().setLayout(borderLayout);
		
		//costruzione nordPanel
		nordPanel.add(schermo);
		schermo.setBorder(BorderFactory.createLineBorder(Color.black));
		schermo.setEditable(false);
		
		//costruzione centroPanel
		centroPanel.add(centro);
		
		//costruzione sudPanel
		sudPanel.add(tastiera);
		tastiera.setLayout(tastieraLayout);
		tastiera.add(sette);
		tastiera.add(otto);
		tastiera.add(nove);
		tastiera.add(somma);
		tastiera.add(delete);
		tastiera.add(quattro);
		tastiera.add(cinque);
		tastiera.add(sei);
		tastiera.add(differenza);
		tastiera.add(nullBtn1);
		tastiera.add(uno);
		tastiera.add(due);
		tastiera.add(tre);
		tastiera.add(moltiplicazione);
		tastiera.add(nullBtn2);
		tastiera.add(zero);
		tastiera.add(punto);
		tastiera.add(uguale);
		tastiera.add(divisione);
		tastiera.add(nullBtn3);
		tastiera.setBorder(BorderFactory.createLineBorder(Color.black));
		
		//costruzione contentPane
		this.getContentPane().add(nordPanel, BorderLayout.NORTH);
		this.getContentPane().add(centroPanel, BorderLayout.CENTER);
		this.getContentPane().add(sudPanel, BorderLayout.SOUTH);
		
		//comandi - listener
		zero.addActionListener(listener);
		zero.setActionCommand("0");
		uno.addActionListener(listener);
		uno.setActionCommand("1");
		due.addActionListener(listener);
		due.setActionCommand("2");
		tre.addActionListener(listener);
		tre.setActionCommand("3");
		quattro.addActionListener(listener);
		quattro.setActionCommand("4");
		cinque.addActionListener(listener);
		cinque.setActionCommand("5");
		sei.addActionListener(listener);
		sei.setActionCommand("6");
		sette.addActionListener(listener);
		sette.setActionCommand("7");
		otto.addActionListener(listener);
		otto.setActionCommand("8");
		nove.addActionListener(listener);
		nove.setActionCommand("9");
		somma.addActionListener(listener);
		somma.setActionCommand(listener.SOMMA);
		differenza.addActionListener(listener);
		differenza.setActionCommand(listener.DIFFERENZA);
		moltiplicazione.addActionListener(listener);
		moltiplicazione.setActionCommand(listener.MOLTIPLICAZIONE);
		divisione.addActionListener(listener);
		divisione.setActionCommand(listener.DIVISIONE);
		uguale.addActionListener(listener);
		uguale.setActionCommand(listener.UGUALE);
		punto.addActionListener(listener);
		punto.setActionCommand(listener.PUNTO);
		delete.addActionListener(listener);
		delete.setActionCommand(listener.DELETE);
		
		//impostazioni
		this.pack();
		this.setLocationRelativeTo(null);
		this.setVisible(true);
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

