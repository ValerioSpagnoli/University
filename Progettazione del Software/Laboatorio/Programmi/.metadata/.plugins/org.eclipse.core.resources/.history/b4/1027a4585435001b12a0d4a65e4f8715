package display;

import java.awt.event.*;
import javax.swing.*;

class Listener implements ActionListener{
	
	private Display frame;
	public final static String DELETE = "Delete";
	public final static String SHOW = "Show";
	
	/*per gestire la "password" inserita dall'utente tramite 
	 * il tastierino, si utilizza una stringa che viene aggiornata ad ogni pressione di un tasto numerico
	*/
	
	private String inseretedText = "";
	
	public Listener(Display aFrame) {
		frame = aFrame;
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().equals(SHOW)) {
			//è stato premuto il tasto "Show"
			frame.codiceVisibileText.setText(inseretedText);
		}
		else if(e.getActionCommand().equals(DELETE)) {
			//è stato premuto il bottone "C"
			int choice = JOptionPane.showConfirmDialog(frame, "Cancellare il codice digitato?", frame.getTitle(), 
													   JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
			if(choice == JOptionPane.YES_OPTION) {
				inseretedText = "";
				frame.codiceVisibileText.setText("");
				frame.passwordText.setText("");
			}
		}
		else {
			//è stato premuto un bottone numerico
			try {
				Integer.parseInt(e.getActionCommand());
			}
			catch(NumberFormatException err){
				throw(new IllegalArgumentException());
			}
			//usiamo l'actionCommand come stringa
			inseretedText = inseretedText + e.getActionCommand();
			frame.passwordText.setText(inseretedText);
		}
	}	
}
