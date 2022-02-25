package server;

import java.io.IOException;

import java.net.*;



import javax.swing.JOptionPane;



public class Server implements Runnable {



	private ServerSocket lis = null;



	public void run() {



		try {

			// attendo nuove connessioni

			lis = new ServerSocket(5555);

		} catch (IOException e1) {

			e1.printStackTrace();

			JOptionPane.showMessageDialog(null, "Errore nella creazione del ServerSocket, applicazione dismessa", null,

					0);

			System.exit(1);

		}

		System.out.println("Server Avviato");

		Socket sock = null;



		while (true) {

			try {

				// accetto nuove connessioni

				sock = lis.accept();

			} catch (IOException e) {

				break;

			}

			System.out.println("Socket creata, connessione accettata");

			ClientThread cl = new ClientThread(sock, this);

			Thread tr = new Thread(cl);

			tr.start();

		}

	}

}