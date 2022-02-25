package client;

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.logging.*;

public class Client {
	private static Logger logger = Logger.getLogger("client.Client");
	
	private Socket socket = null;
	private Scanner console = null;
	private PrintWriter streamOut = null;
	
	public Client(String serverName, int serverPort) {
		logger.log(Level.INFO, "Stabilendo la connesione. Please wait ...");
		try {
			socket = new Socket(serverName, serverPort);
			logger.log(Level.INFO, "Connected: " + socket);
			start();
		} 
		catch(UnknownHostException uhe) {
			logger.log(Level.SEVERE, "Host unknown: " + uhe.getMessage(), uhe.getStackTrace());
		}
		catch(IOException ioe) {
			logger.log(Level.SEVERE, "Unexpeted exception: " + ioe.getMessage() , ioe.getStackTrace());
		}
		String line = console.nextLine();
		while(!line.equals("bye")) {
			logger.log(Level.INFO, "Read: " + line);
			streamOut.println(line);
			streamOut.flush();
			logger.log(Level.INFO, "Sent: " + line);
			line = console.nextLine();
		}
		streamOut.println("bye");
		streamOut.flush();
		stop();
	}
	
	public void start () throws IOException {
		console = new Scanner(System.in);
		streamOut = new PrintWriter(socket.getOutputStream());
	}
	
	public void stop() {
		try {
			if(console != null) console.close();
			if(streamOut != null) streamOut.close();
			if(socket != null) socket.close();
		} catch (IOException IOe) {
			System.out.println("Error closing ...");
		}
	}
	
	public static void main(String[] args) {
		Client client = null;
		if(args.length != 2) {
			System.out.println("Usage: java Client host port");
		}
		else {
			client = new Client(args[0], Integer.parseInt(args[1]));
		}
	}
	
	
}
