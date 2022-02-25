package server;

public class Main {

	public static void main(String[] args) {



		Server serv = new Server();

		Thread avv = new Thread(serv);

		avv.start();

	}

}

