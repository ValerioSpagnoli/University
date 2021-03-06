package esempio1;

import javax.swing.*;	
import java.awt.*; //per usare la classe Container

public class Frame1 {
	
	public static void main (String[] args) {
		
		//crea una finestra con il titolo HelloWorld
		JFrame frame = new JFrame("Titolo"); 
		
		//visualizza (true) o nasconde (false) la finestra
		frame.setVisible(true);
		
		//assegna il titolo all'oggetto di invocazione
		frame.setTitle("Hello World!");
		
		//assegna le dimensioni specificate (largezza, altezza) (in px) alla finestra
		frame.setSize(300, 200);
		
		//assegna la posizione specifica (x, y) (coordinate in px) con origine in alto a sinistra
		frame.setLocation(500, 300);
		
		/*stabilice il comportamento del pulsante close (x):
		 * EXIT_ON_CLOSE: forza la chiusura incodizionata del programma
		 * DISPOSE_ON_CLOSE: elimina la finestra liberando la memoria allocata
		 * HIDE_ON_CLOSE: nasconde la finesta mantenendola in memoria
		 * DO_NOTHING_ON_CLOSE: non ha alcun effetto
		*/
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
		
		//Ottiene il riferimento al Content Pane del JFrame
		Container frameContentPane = frame.getContentPane();
		
		//Viene usato il riferimento al Content Pane per aggiungere elementi grafici
		frameContentPane.add(new JLabel("Ciao Mondo!"));
		
		//Crea un bottone
		JButton bottone1 = new JButton("Bottone 1");

		/*Gestisce il layout della finestra:
		 * FlowLayout(FlowLayout.CENTER): alleamento per righe. Si può specificare se a sinistra (LEADING), centro (CENTER), destra (TRAILNG)
		 * GridLayout(righe, colonne): allineamnto a griglia
		 * BorderLayout(): allineamento in 5 zone. Per aggiungere un elemento bisogna fare add(elemento, posizione), dove posizione  può essere NORTH, CENTER, SOUTH, WEST, OVEST
		 
		   frameContentPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		   frameContentPane.add(bottone1);
		
		   frameContentPane.setLayout(new BorderLayout());
		   frameContentPane.add(bottone1, BorderLayout.SOUTH);
		
		   frameContentPane.setLayout(new GridLayout(3, 3));
		   frameContentPane.add(bottone1);
		*/
		
		frameContentPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		frameContentPane.add(bottone1);

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

	}
}
