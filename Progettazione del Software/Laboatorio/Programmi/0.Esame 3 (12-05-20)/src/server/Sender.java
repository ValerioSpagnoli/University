package server;
//import sun.security.util.ArrayUtil;

import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;

class Sender  implements Runnable {
    private final ArrayList<Integer> indexList = new ArrayList<>();
    private final PrintWriter output;
    public boolean interrupted = false;

    public Sender(PrintWriter output, ClientSender cs) {
        this.output = output;
        for (int i=0;i<5;i++) {
            indexList.add(i);
        }
    }

    @Override
    public void run() {
        while (indexList.size()!=0 && !interrupted) {
            int randomIndex = (int) (Math.random()*indexList.size());
            int randomDigit = (int) (Math.random()*10);
            output.println(indexList.get(randomIndex) + ";" + randomDigit);
            output.flush();
            System.out.println("Sent: " + indexList.get(randomIndex) + ";" + randomDigit);
            indexList.remove(randomIndex);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (interrupted) {
            output.println("-1;-1");
            output.flush();
            System.out.println("Forced termination sent");
        } else {
            output.println("*;*");
            output.flush();
            System.out.println("Ending sent");
        }
    }
}
