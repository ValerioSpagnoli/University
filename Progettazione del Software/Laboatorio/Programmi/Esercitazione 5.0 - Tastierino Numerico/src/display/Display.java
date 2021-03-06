package display;

import java.awt.*;
import javax.swing.*;

public class Display extends JFrame {
	
	final FlowLayout flowLayout = new FlowLayout();
	
	//pannello sinistra
	final JPanel leftPanel = new JPanel();
	final BorderLayout leftBorderLayout = new BorderLayout();
	final JPasswordField passwordText = new JPasswordField();
	final JPanel keypad = new JPanel();
	
	final JButton uno = new JButton("1");
	final JButton due = new JButton("2");
	final JButton tre = new JButton("3");
	final JButton quattro = new JButton("4");
	final JButton cinque = new JButton("5");
	final JButton sei = new JButton("6");
	final JButton sette = new JButton("7");
	final JButton otto = new JButton("8");
	final JButton nove = new JButton("9");
	final JButton zero = new JButton("0");
	final JButton delete = new JButton("C");
	final JButton show = new JButton("Show");
	
	//pannello destra
	final JPanel rightPanel = new JPanel();
	final BorderLayout rightBorderLayout = new BorderLayout();
	final JLabel codiceVisibileLabel = new JLabel("Codice digitato:");
	final JTextArea codiceVisibileText = new JTextArea(1, 10);
	
	final Listener ascoltatore = new Listener(this);
	
	public Display() {
		super ("Pannello Digitale");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(flowLayout);
		
		//costruzione leftPanel
		leftPanel.setLayout(leftBorderLayout);
		leftPanel.add(passwordText, BorderLayout.NORTH);
		leftPanel.add(keypad, BorderLayout.CENTER);
		passwordText.setEditable(false);
		keypad.setLayout(new GridLayout(4,3));
		keypad.add(sette);
		keypad.add(otto);
		keypad.add(nove);
		keypad.add(quattro);
		keypad.add(cinque);
		keypad.add(sei);
		keypad.add(uno);
		keypad.add(due);
		keypad.add(tre);
		keypad.add(delete);
		keypad.add(zero);
		keypad.add(show);
		keypad.setBorder(BorderFactory.createLineBorder(Color.black));
		
		//costruzione rightPanel
		rightPanel.setLayout(rightBorderLayout);
		rightPanel.add(codiceVisibileLabel, BorderLayout.NORTH);
		rightPanel.add(codiceVisibileText, BorderLayout.CENTER);
		codiceVisibileText.setBorder(BorderFactory.createLineBorder(Color.black));
		codiceVisibileText.setEditable(false);
		
		//aggiunta del leftPanel e del rightPanel al contentPane
		this.getContentPane().add(leftPanel, null);
		this.getContentPane().add(rightPanel, null);
		
		/*Assegnazione comandi ed ascoltatori. L'ascoltatore ?? lo stesso per tutti i bottoni, ad ogni bottone numerico ?? 
		 * associato un ActionCommand (stringa) che corrisponde alla cifra visualizzata (vedi Listener)
		 */
		zero.addActionListener(ascoltatore);
		zero.setActionCommand("0");
		uno.addActionListener(ascoltatore);
		uno.setActionCommand("1");
		due.addActionListener(ascoltatore);
		due.setActionCommand("2");
		tre.addActionListener(ascoltatore);
		tre.setActionCommand("3");
		quattro.addActionListener(ascoltatore);
		quattro.setActionCommand("4");
		cinque.addActionListener(ascoltatore);
		cinque.setActionCommand("5");
		sei.addActionListener(ascoltatore);
		sei.setActionCommand("6");
		sette.addActionListener(ascoltatore);
		sette.setActionCommand("7");
		otto.addActionListener(ascoltatore);
		otto.setActionCommand("8");
		nove.addActionListener(ascoltatore);
		nove.setActionCommand("9");
		delete.addActionListener(ascoltatore);
		delete.setActionCommand(Listener.DELETE);
		show.addActionListener(ascoltatore);
		show.setActionCommand(Listener.SHOW);
		
		//altre impostazioni grafiche
		this.pack();
		//centra il frame nello schemo
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}
}
