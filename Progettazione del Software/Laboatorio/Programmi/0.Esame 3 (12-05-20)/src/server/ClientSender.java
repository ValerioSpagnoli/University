package server;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ClientSender implements Runnable {
    private final Socket client;
    private final Scanner input;
    private final PrintWriter output;
    public boolean running = true;
    private Sender sender;

    public ClientSender(Socket client) throws IOException {
        this.client = client;
        input = new Scanner(client.getInputStream());
        output = new PrintWriter(client.getOutputStream());

    }

    @Override
    public void run() {
        System.out.println("New Client accepted");
        while (running) {
            //System.out.println("waiting for input...");
            getCmd();
        }
        System.out.println("Client dismissed");

    }

    private void start() {
        System.out.println("Starting sending digits");
        sender = new Sender(output, this);
        Thread t = new Thread(sender);
        t.start();
    }

    private void stop() {
        running = false;
        try {
            client.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void interrupt() {
        sender.interrupted = true;
    }

    private void getCmd() {
        if (input.hasNext()) {
            String cmd = input.nextLine();
            if (!running) { return; }
            System.out.println("Received: " + cmd);
            switch (cmd) {
                case "start":
                    start();
                    break;
                case "disconnect":
                    stop();
                    break;
                case "interrompi":
                    interrupt();
                    break;
            }
        }
    }
}
