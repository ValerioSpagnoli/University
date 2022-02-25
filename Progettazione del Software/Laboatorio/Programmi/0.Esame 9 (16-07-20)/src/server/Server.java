package server;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

class Server implements Runnable {
    private Gui mainFrame;
    private ServerSocket server;
    private Socket socket;
    private Scanner scan;
    private PrintWriter out;
    
    private boolean finish = false;
    private String command;
    private File folder;
    private File[] listOfFiles;
    private Sender sender;
    private Thread thread;
    
    private Logger logger = Logger.getLogger("ServerDownloader");
    
    public Server(int porta, Gui m) throws IOException{
        server = new ServerSocket(porta);
        mainFrame = m;  
    }

    @Override
    public void run() {
        while(!finish){
            logger.log(Level.INFO,"waiting a client...");
            try {
                
                socket = server.accept();
            } catch (IOException ex) {
                logger.log(Level.INFO,"connection non established");
                ex.printStackTrace();
            }
            
            try {
                scan = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream());
            } catch (IOException ex) {
                logger.log(Level.WARNING,"ERROR: STREAM NOT OPEN");
                ex.printStackTrace();
            }
           
            
            folder = new File("/home/studente/eclipse-workspace/0.Esame 9/src/");
            listOfFiles = folder.listFiles();
            try{
            while(true){
                try{
                   logger.log(Level.INFO,"waiting a command");
                   command = scan.nextLine(); 
                }
                catch(Exception e){
                    logger.log(Level.INFO,"ERROR: line not found");
                    e.printStackTrace();
                    break;
                }
                logger.log(Level.INFO,"string recived");
                
               switch(command){
                   case "LIST":
                       logger.log(Level.INFO,"sending names of files");
                       for(int i=0; i<listOfFiles.length; i++){
                       System.out.println("sending: " + listOfFiles[i]);
                       out.println(listOfFiles[i]);
                       out.flush();
                       }
                   logger.log(Level.INFO,"names of files sent");
                   out.println("END");
                   out.flush();
                   break;
                   
                   case "GET:divinaCommedia":
                       logger.log(Level.INFO,"sending divinaCommedia");
                       sender = new Sender(out,"/home/studente/eclipse-workspace/0.Esame 9/src/divinaCommedia");
                       thread = new Thread(sender);
                       thread.start();
                       break;
                   case "GET:promessiSposi":
                       logger.log(Level.INFO,"sending promessiSposi");
                       sender = new Sender(out,"/home/studente/eclipse-workspace/0.Esame 9/src/promessiSposi");
                       thread = new Thread(sender);
                       thread.start();
                       break;
                   case "GET:canto1":
                       logger.log(Level.INFO,"sending canto1");
                       sender = new Sender(out,"/home/studente/eclipse-workspace/0.Esame 9/src/canto1");
                       thread = new Thread(sender);
                       thread.start();
                       break;
                   case "INTERRUPT":
                       sender.stopThread();
                       break;
                   default: System.out.println("command not found");
                            out.println("file not found");
                            out.flush();
                            break;
                  
                       
               }
                
                
            }
            }
            catch(Exception e){
                logger.log(Level.WARNING,"ERROR: TIMEDOUT CONNECTION");
                e.printStackTrace();
            }
            scan.close();
            out.close();
        }
    }
    
    
    public void close() throws IOException {
        finish = true;
        if(scan != null) scan.close();
        if(out != null) out.close();
        if(socket != null) socket.close();
        if(server != null) server.close();
    }
    
    public PrintWriter getPrintWriter(){
        return out;
    }
}
