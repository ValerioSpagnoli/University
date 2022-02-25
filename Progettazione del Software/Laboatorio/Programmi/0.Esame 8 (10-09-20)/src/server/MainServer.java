package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class MainServer {

    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(4400);
        while (true) {
            Socket cs = ss.accept();
            Thread t = new Thread(new ClientHandler(cs));
            t.start();
        }

    }
}
