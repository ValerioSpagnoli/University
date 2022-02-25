package server;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

class Sender  implements Runnable {
    // si occupa solamente di inviare al client le coppie di numeri
    private final ArrayList<Integer> indexList = new ArrayList<>();
    private final PrintWriter output;
    private final File imageX;
    public boolean interrupted = false;

    public Sender(PrintWriter output, String imageX) {
        this.output = output;
        for (int i=0;i<5;i++) {
            indexList.add(i);
        }

        this.imageX = new File("/home/studente/Desktop/esame/12-05-20/e151020/Server/" + imageX);

    }

    @Override
    public void run() {
        if (!imageX.exists()) {
            System.out.println("File not found");
            output.println("File Not Found");
            output.flush();
            return;
        }
        Scanner scan = null;
        try {
            scan = new Scanner(imageX);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println("Image Found!");


        while (scan.hasNextLine() && !interrupted) {
            String s = scan.nextLine();
            System.out.println("Sent: " + s);
            output.println(s);
            output.flush();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (interrupted) {
            output.println("INTERRUPTED");
            output.flush();
            System.out.println("Forced termination sent");
        } else {
            output.println("END");
            output.flush();
            System.out.println("Ending sent");
        }
    }
}
