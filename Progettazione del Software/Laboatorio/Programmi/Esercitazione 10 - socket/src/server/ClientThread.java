package server;

import java.io.*;

import java.net.*;

import java.util.Scanner;



public class ClientThread implements Runnable {



	private Socket sock;

	private boolean fired = false;

	private SenderThread st = null;



	Server parent;



	public ClientThread(Socket s, Server parent) {

		sock = s;



		this.parent = parent;

	}



	@Override

	public void run() {

		if (fired)

			return;

		fired = true;

		boolean running = true;

		Scanner in = null;

		PrintWriter pw = null;

		try {

			in = new Scanner(sock.getInputStream());

			pw = new PrintWriter(sock.getOutputStream());

		} catch (IOException e) {

			e.printStackTrace();

		}



		while (running) {

			String cmd = in.nextLine();

			System.out.println("Ricevuto: "+ cmd);

			if (cmd.equals("start")) {

				

				st = new SenderThread(pw);

				Thread t = new Thread(st);

				t.start();

			} else if (cmd.equals("stop")) {

				st.stop();

			} else {

				running = false;

			}

		}

		try {

			pw.close();

			in.close();

			sock.close();

		} catch (IOException e1) {

			e1.printStackTrace();

		}

	}

}