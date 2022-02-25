package server;

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.logging.*;

public class Server {
	
	private static Logger logger = Logger.getLogger("server.Server");
	
	private Socket socket = null;
	private ServerSocket server = null;
	private Scanner scan = null;
	
	public Server (int port) {
		try {
			logger.log(Level.INFO, "Collegamento alla porta: " + port);
			server = new ServerSocket(port);
			logger.log(Level.INFO, "Server started: " + server);
			
			logger.log(Level.INFO, "Aspetto un client . . .");
			socket = server.accept();
			logger.log(Level.INFO, "Client accettato: " + socket);
			
			open();
			boolean done = false;
			while(!done) {
				String line = scan.nextLine();
				System.out.println(line);
				done = line.equals("bye");
			}
			close();
			
		} catch(IOException IOe) {
			logger.log(Level.SEVERE, IOe.getMessage(), IOe.getStackTrace());
		}
	}
	
	private void open() throws IOException{
		scan = new Scanner (socket.getInputStream());
	}
	private void close() throws IOException{
		if(socket != null) socket.close();
		if(scan != null) scan.close();
	}
	
	
	public static void main(String[] args) {
		Server server = null;
		if(args.length != 1) System.out.println("Usage: java Server port");
		else  server = new Server(Integer.parseInt(args[0]));
	}
	
	
}
